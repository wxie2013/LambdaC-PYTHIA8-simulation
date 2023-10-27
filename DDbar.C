#include <iostream>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/EvtGen.h"

// ROOT, for histogramming.
#include "TNtuple.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"

using namespace Pythia8;
//
pair<bool, bool> is_C_B_hadron_decay(vector<pair<int,int>> ancestor_list, Pythia &pythia);
void create_ancestor_list(
        vector<pair<int,int>> &ancestor_status_index, 
        Pythia &pythia, 
        int idx_D0
        );
int classifier(
        vector<pair<int,int>> & ancestor1, 
        vector<pair<int,int>> & ancestor2, 
        Pythia &pythia
        );
vector<tuple<int, int, int>> production_category(
        vector<vector<pair<int,int>>> & ancestor_info, 
        vector<int> D0_indices,
        Pythia &pythia
        );
//
int main(int argc, char* argv[]) {

    // Check arguments.
    if (argc != 8) {
        cerr << " Unexpected number of command-line arguments. \n You are"
            << " expected to provide the arguments \n"
            << " 1. output file name \n"
            << " 2. number of events to generate \n"
            << " 3. random number seed \n"
            << " 4. Flag to use EvtGen (true or false) \n"
            << " 5. phys_process (HardQCD_ON, SoftQCD_Nondiff_ON)\n"
            << " 6. tune (Monash, CUETP8M1, CR0, CR2)\n"
            << " 7. debug\n"
            << " Program stopped. " << endl;
        return 1;
    }
    char* filename = argv[1];
    int nevt = atoi(argv[2]);
    int seed = atoi(argv[3]);
    bool useEvtGen(string(argv[4]) == "true");
    string phys_process = argv[5];
    string tune = argv[6];
    bool debug = argv[7];

    cout<<"outfile: "<<filename<<" nevt: "<<nevt<<" seed: "<<seed<<" useEvtGen:"<<useEvtGen<<endl;

    if(useEvtGen) {
        cout<<"==============================================="<<endl;
        cout<<"==        using EvtGen to decay              =="<<endl;
        cout<<"==============================================="<<endl;
    } else {
        cout<<"==============================================="<<endl;
        cout<<"==        using PYTHIA to decay              =="<<endl;
        cout<<"==============================================="<<endl;
    }
    // Create the ROOT application environment.
    TApplication theApp("hist", &argc, argv);

    // Create Pythia instance and set it up to generate hard QCD processes
    // above pTHat = 0 GeV for pp collisions at 5.02 TeV.
    Pythia pythia;

    //Pick new random number seed for each run, based on clock.
    pythia.readString("Random:setSeed = on");
    string set_seed = "Random:seed ="+std::to_string(seed);
    pythia.readString(set_seed.c_str());

    pythia.readString("PhaseSpace:pTHatMin = 0.");
    pythia.readString("Beams:eCM = 5020.");
    //pythia.readString("Beams:eCM = 200.");
    //pythia.readString("Beams:eCM = 7000.");
    //
    if(phys_process=="HardQCD_ON") {
        cout<<" -- HardQCD:all = on ---"<<endl;
        pythia.readString("HardQCD:all = on");

    } else if(phys_process=="SoftQCD_Nondiff_ON") {

        cout<<" -- SoftQCD:nonDiffractive = ON ---"<<endl;
        pythia.readString("SoftQCD:nonDiffractive = on"); // shouldn't use HardQCD:all= on, which is only valid at high pT, e.g. pT > ~10 GeV/c

    } else {
        cout<<" !!! choose one: HardQCD_ON  or SoftQCD_Nondiff_ON !!!"<<endl;
        return 1;
    }

    // pythia tune
    if(tune == "Monash") {
        cout<<" -- Monash tune --"<<endl;
        pythia.readString("Tune:ee 7");
        pythia.readString("Tune:pp 14");
    } else if (tune == "CUETP8M1") {
        cout<<" -- CUETP8M1 tune --"<<endl;
        pythia.readString("Tune:pp 18");
    } else if (tune =="CR0") {
        cout<<" -- Color reconnection tune (CR) mode0 ---"<<endl;
        pythia.readString("Tune:ee 7");
        pythia.readString("Tune:pp 14");
        pythia.readString("MultipartonInteractions:ecmPow=0.215");
        pythia.readString("MultipartonInteractions:expPow=1.85");
        pythia.readString("StringPT:sigma =0.335");
        pythia.readString("StringZ:aLund =0.36");
        pythia.readString("StringZ:bLund =0.56");
        pythia.readString("StringFlav:probQQtoQ =0.078");
        pythia.readString("StringFlav:ProbStoUD =0.2");
        pythia.readString("StringFlav:probQQ1toQQ0join = 0.0275,0.0275,0.0275, 0.0275");
        pythia.readString("MultiPartonInteractions:pT0Ref =2.12");
        pythia.readString("BeamRemnants:remnantMode =1");
        pythia.readString("BeamRemnants:saturation= 5");
        pythia.readString("ColourReconnection:mode = 1");
        pythia.readString("ColourReconnection:allowDoubleJunRem =off");
        pythia.readString("ColourReconnection:m0=2.9");
        pythia.readString("ColourReconnection:allowJunctions =on");
        pythia.readString("ColourReconnection:junctionCorrection=1.43");
        pythia.readString("ColourReconnection:timeDilationMode=0");
    } else if (tune =="CR2") {
        cout<<" -- Color reconnection tune (CR) mode2 ---"<<endl;
        pythia.readString("Tune:ee 7");
        pythia.readString("Tune:pp 14");
        pythia.readString("MultipartonInteractions:ecmPow=0.215");
        pythia.readString("MultipartonInteractions:expPow=1.85");
        pythia.readString("StringPT:sigma =0.335");
        pythia.readString("StringZ:aLund =0.36");
        pythia.readString("StringZ:bLund =0.56");
        pythia.readString("StringFlav:probQQtoQ =0.078");
        pythia.readString("StringFlav:ProbStoUD =0.2");
        pythia.readString("StringFlav:probQQ1toQQ0join = 0.0275,0.0275,0.0275,0.0275");
        pythia.readString("MultiPartonInteractions:pT0Ref =2.15");
        pythia.readString("BeamRemnants:remnantMode =1");
        pythia.readString("BeamRemnants:saturation= 5");
        pythia.readString("ColourReconnection:mode = 1");
        pythia.readString("ColourReconnection:allowDoubleJunRem =off");
        pythia.readString("ColourReconnection:m0=0.3");
        pythia.readString("ColourReconnection:allowJunctions =on");
        pythia.readString("ColourReconnection:junctionCorrection=1.2");
        pythia.readString("ColourReconnection:timeDilationMode=2");
        pythia.readString("ColourReconnection:timeDilationPar=0.18");
    } else {
        cout<<"!!! choose one: Monash, CUETP8M1, CR0, CR2 !!!"<<endl;
        return 1;
    }

    //
    pythia.init();

    // Initialize EvtGen.
    EvtGenDecays *evtgen = 0;
    if (useEvtGen) {
        //setenv("PYTHIA8DATA", "/home/wxie/py8_evtgen_HepMC/share/Pythia8/xmldoc", 1);
        evtgen = new EvtGenDecays(&pythia, "/home/wxie/local_pkgs/py8_evtgen_HepMC/share/EvtGen/DECAY.DEC", "/home/wxie/local_pkgs/py8_evtgen_HepMC/share/EvtGen/evt.pdl");
    }


    // Create file on which histogram(s) can be saved.
    TFile* outFile = new TFile(filename, "RECREATE");

    // Book histogram.
    TNtuple* ddbar = new TNtuple("ddbar", "", "pid1:pid2:pt1:pt2:y1:y2:phi1:phi2:chadr_decay1:chadr_decay2:bhadr_decay1:bhadr_decay2:category:nD0:ievt");

    // Begin event loop. Generate event; skip if generation aborted.
    for (int iEvent = 0; iEvent < nevt; ++iEvent) {
        if (!pythia.next()) continue;

        if(useEvtGen)
            evtgen->decay();

        // charged multiplicity
        int    nCh   = 0;
        for (int i = 0; i < pythia.event.size(); ++i) {
            if (pythia.event[i].isFinal() && pythia.event[i].isCharged()) 
                ++nCh;
        }

        vector<int> D0_indices;
        vector<vector<pair<int,int>>> ancestor_info; // all D0/D0bar ancestors status and index
        for (int i = 0; i < pythia.event.size(); ++i) {
            int pid = pythia.event[i].id();
            if (abs(pid) == 421) {//.. D0
                vector<pair<int, int>> ancestor_status_index;
                create_ancestor_list(ancestor_status_index, pythia, i);
                ancestor_info.push_back(ancestor_status_index);
                D0_indices.push_back(i);

                if(debug) {
                    cout<<" pid: "<<pid<<endl;
                    for(int m=0; m<ancestor_status_index.size(); m++) {
                        cout<<"("<<ancestor_status_index[m].first<<"|"<<ancestor_status_index[m].second<<") ";
                    }
                    cout<<endl;
                }
            }
        }
        //
        if(D0_indices.size()==0) 
            continue;

        if(debug) {
            if(D0_indices.size()>=2) {
                cout<<" nD0: "<<D0_indices.size()<<endl;
                pythia.event.list(false, false);
            }
        }
        
        // categorize all D0-D0bar pairs
        auto category_list =  production_category(ancestor_info, D0_indices, pythia);

        vector<pair<bool, bool>> is_cb_hadr_decay;
        for(int i = 0; i<D0_indices.size(); i++) {
            int m = D0_indices[i];
            is_cb_hadr_decay.push_back(is_C_B_hadron_decay(ancestor_info[i], pythia));
        }

        for(int i = 0; i<D0_indices.size()-1; i++) {
            int m = D0_indices[i];
            for(int j = i+1; j<D0_indices.size(); j++) {
                int n = D0_indices[j];

                auto it = std::find_if(category_list.begin(), category_list.end(), 
                        [&m, &n](const tuple<int, int, int>& element)
                        { return std::get<1>(element)==m && std::get<2>(element)==n;});

                int category = -1;
                if(it != category_list.end()) {
                    category = std::get<0>(*it);
                } else {
                    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                    cout<<" !!!!!  No ancestor for: D0 index1="<<m<<" D0 index2 ="<<n<<". Stop the run !!!!! "<<endl;
                    cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
                    exit(0);
                }
                ddbar->Fill(
                        pythia.event[m].id(), 
                        pythia.event[n].id(), 
                        pythia.event[m].pT(), 
                        pythia.event[n].pT(), 
                        pythia.event[m].y(), 
                        pythia.event[n].y(), 
                        pythia.event[m].phi(), 
                        pythia.event[n].phi(), 
                        is_cb_hadr_decay[i].first, 
                        is_cb_hadr_decay[j].first, 
                        is_cb_hadr_decay[i].second, 
                        is_cb_hadr_decay[j].second, 
                        category, 
                        D0_indices.size(), 
                        iEvent
                        );
            }
        }
    }

    // Statistics on event generation.
    pythia.stat();

    cout<<" cs: "<<pythia.info.sigmaGen()<<" weight: "<<pythia.info.nAccepted()<<endl;

    ddbar->Write();
    delete outFile;

    if(evtgen) delete evtgen;
    // Done.
    return 0;
}

// check if a ancestor is B or charm hadron
pair<bool, bool> is_C_B_hadron_decay(vector<pair<int,int>> ancestor_list, Pythia &pythia)
{
    bool is_Bhadron_decay = false;
    bool is_Chadron_decay = false;
    for (int i = 0; i<ancestor_list.size(); i++) {
        int idx = ancestor_list[i].first;
        int pid = pythia.event[idx].id();
        if(abs(int(pid/100)%10)==5 || abs(int(pid/1000)%10)==5) 
            is_Bhadron_decay = true;

        if(abs(int(pid/100)%10)==4 || abs(int(pid/1000)%10)==4) 
            is_Chadron_decay = true;
    }
    return std::make_pair(is_Chadron_decay, is_Bhadron_decay);
}

// check if a ancestor is B hadron
void create_ancestor_list(
        vector<pair<int,int>> &ancestor_status_index, 
        Pythia &pythia, 
        int idx_D0
        )
{
    for (int i = 0; i<pythia.event[idx_D0].motherList().size(); i++) {
        int midx = pythia.event[idx_D0].motherList()[i];
        int status = pythia.event[midx].status();
        ancestor_status_index.push_back(std::make_pair(midx, status));
        create_ancestor_list(ancestor_status_index, pythia, midx);
    }
}

// which of the production classes it belong to
vector<tuple<int, int, int>> production_category(
        vector<vector<pair<int,int>>> & ancestor_info, 
        vector<int> D0_indices,
        Pythia &pythia
        )
{
    // tuple<string, int, int>: 
    //      1st int: "FCR", "FEX", "GSP" 
    //      2nd/3rd int, int: the index of the heavy quarks produced together
    //Note: index of D0_indices and ancestor_info syncronize

    vector<tuple<int, int, int>> result;
    for(int i = 0; i<ancestor_info.size()-1; i++) {
        for(int j = i+1; j<ancestor_info.size(); j++) {
            int category =  classifier(ancestor_info[i], ancestor_info[j], pythia);
            result.push_back(std::make_tuple(category, D0_indices[i], D0_indices[j]));
        }
    }

    return result;
}

// classify a pair of D0 are from FCR, FEX, GSP or different hard collision
int classifier(
        vector<pair<int,int>> & ancestor1, 
        vector<pair<int,int>> & ancestor2, 
        Pythia &pythia
        )
{
    // 0: uncorrelated DDbar
    // 1: Flavor creation 
    // 2: Flavor excitation
    // 3: Gluon splitting 

    // check if they have a common ancestor gluon
    bool same_ancestor = false;
    for(int i = 0; i<ancestor1.size(); i++) {
        int idx1 = ancestor1[i].first;
        auto it = std::find_if(ancestor2.begin(), ancestor2.end(), 
                [&idx1](const pair<int, int>& element)
                { return element.first == idx1;} );

        if(it==ancestor2.end())
            continue;

        if(abs(pythia.event[idx1].id()) == 21 || abs(pythia.event[idx1].id()) == 9) {
            same_ancestor = true;
            break;
        }
    }

    if(same_ancestor == false)
        return 0;

    // now check status of 1st charm quark 
    bool charm1_from_hard_scattering = false;
    bool charm1_from_initial_state = false;
    for(int i = 0; i<ancestor1.size(); i++) {
        int idx1 = ancestor1[i].first;

        if(abs(pythia.event[idx1].id()) == 4) {
            int status = ancestor1[i].second;
            if(abs(status) >= 21 && abs(status) <=29) 
               charm1_from_hard_scattering = true; 

            if(abs(status) >= 41 && abs(status) <=49) 
                charm1_from_initial_state = true;
        }
    }
    // now check status of 2nd charm quark 
    bool charm2_from_hard_scattering = false;
    bool charm2_from_initial_state = false;
    for(int i = 0; i<ancestor1.size(); i++) {
        int idx1 = ancestor1[i].first;

        if(abs(pythia.event[idx1].id()) == 4) {
            int status = ancestor1[i].second;
            if(abs(status) >= 21 && abs(status) <=29) 
               charm2_from_hard_scattering = true; 

            if(abs(status) >= 41 && abs(status) <=49) 
                charm2_from_initial_state = true;
        }
    }

    if(charm1_from_hard_scattering && charm2_from_hard_scattering) {
        return 1;
    } else if(charm1_from_hard_scattering && !charm2_from_hard_scattering ||
            !charm1_from_hard_scattering && charm2_from_hard_scattering) {
        if(!charm1_from_initial_state && !charm2_from_initial_state)
            cout<<" !!!!  none from initial state for FEX category !!!"<<endl;
        return 2;
    } else if(!charm1_from_hard_scattering && !charm2_from_hard_scattering) {
        return 3;
    }
}

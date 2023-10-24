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

bool debug = false;

using namespace Pythia8;

bool is_nonprompt(Pythia &pythia, Particle &ptl);
bool is_decay_from_charm_hadron(Pythia &pythia, Particle &ptl);
void ancestor_list(vector<int> & index_list, Pythia &pythia, Particle &ptl);

int main(int argc, char* argv[]) {

  // Check arguments.
  if (argc != 7) {
    cerr << " Unexpected number of command-line arguments. \n You are"
      << " expected to provide the arguments \n"
      << " 1. output file name \n"
      << " 2. number of events to generate \n"
      << " 3. random number seed \n"
      << " 4. Flag to use EvtGen (true or false) \n"
      << " 5. phys_process (HardQCD_ON, SoftQCD_Nondiff_ON)\n"
      << " 6. tune (Monash, CUETP8M1, CR0, CR2)\n"
      << " Program stopped. " << endl;
    return 1;
  }
  char* filename = argv[1];
  int nevt = atoi(argv[2]);
  int seed = atoi(argv[3]);
  bool useEvtGen(string(argv[4]) == "true");
  string phys_process = argv[5];
  string tune = argv[6];

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
  TNtuple* ddbar = new TNtuple("ddbar", "", "pt1:pt2:y1:y2:phi1:phi2:bhadr_decay1:bhadr_decay2:chadr_decay1:chadr_decay2");

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
    for (int i = 0; i < pythia.event.size(); ++i) {
      int pid = pythia.event[i].id();
      if (abs(pid) == 421) {//.. D0
          cout<<" ievt: "<<iEvent<<" i:  "<<i<<" pid: "<<pid<<endl;
          bool from_Bhadr_decay = is_nonprompt(pythia, pythia.event[i]);
          bool from_Chadr_decay = is_decay_from_charm_hadron(pythia, pythia.event[i]);
          if(from_Chadr_decay)
              cout<<" --- from charm hadron decay "<<endl;
          if(from_Bhadr_decay)
              cout<<" --- from B-hadron decay "<<endl;
          vector<int> index_list;
          vector<int> pid_list;
          ancestor_list(index_list, pythia, pythia.event[i]);
          cout<<" num of ancesters: "<<index_list.size()<<endl;
          for(int m = 0; m<index_list.size(); m++) {
              int aidx = index_list[m];
              pid_list.push_back(pythia.event[aidx].id());
              //cout<<"     aidx: "<<aidx<<" apid: "<<pythia.event[aidx].id()<<endl;
          }
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

// check if a ancestor is B hadron
bool is_nonprompt(Pythia &pythia, Particle &ptl)
{
    auto mother_list = ptl.motherList();
    for (int i = 0; i<mother_list.size(); i++) {
        int midx = mother_list[i];
        int mpid = pythia.event[midx].id();
        int m1idx = pythia.event[midx].mother1();
        int m2idx = pythia.event[midx].mother2();
        cout<<" 0-- mpid: "<<mpid<<"  grandparent1: "<<pythia.event[m1idx].id()<<" grandparent2: "<<pythia.event[m2idx].id()<<endl;
        if(abs(int(mpid/100)%10)==5 || abs(int(mpid/1000)%10)==5) 
            return true;
        else
            return is_nonprompt(pythia, pythia.event[midx]);
    }
    return false;
}
// check if a ancestor is B hadron
bool is_decay_from_charm_hadron(Pythia &pythia, Particle &ptl)
{
    auto mother_list = ptl.motherList();
    for (int i = 0; i<mother_list.size(); i++) {
        int midx = mother_list[i];
        int mpid = pythia.event[midx].id();
        if(abs(int(mpid/100)%10)==4 || abs(int(mpid/1000)%10)==4) 
            return true;
        else
            return is_decay_from_charm_hadron(pythia, pythia.event[midx]);
    }
    return false;
}
// check if a ancestor is B hadron
void ancestor_list(vector<int> & index_list, Pythia &pythia, Particle &ptl)
{
    for (int i = 0; i<ptl.motherList().size(); i++) {
        int midx = ptl.motherList()[i];
        int mpid = pythia.event[midx].id();
        index_list.push_back(midx);
        //cout<<"   mpid: "<<mpid<<endl;
        ancestor_list(index_list, pythia, pythia.event[midx]);
    }
}

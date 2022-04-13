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

bool daughter_is_not_Bhadron(Pythia &py, int index1, int index2);

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
    evtgen = new EvtGenDecays(&pythia, "/home/wxie/py8_evtgen_HepMC/share/EvtGen/DECAY.DEC", "/home/wxie/py8_evtgen_HepMC/share/EvtGen/evt.pdl");
  }


  // Create file on which histogram(s) can be saved.
  TFile* outFile = new TFile(filename, "RECREATE");

  // Book histogram.
  TNtuple* Lc = new TNtuple("Lc", "inclusive Lc", "m:pt:y:nch");
  TNtuple* B2Lc = new TNtuple("B2Lc", "B->Lc", "m:pt:y:nch:mpt:my:mid");
  TNtuple* D0 = new TNtuple("D0", "inclusive D0", "m:pt:y:nch");
  TNtuple* B2D0 = new TNtuple("B2D0", "B->D0", "m:pt:y:nch:mpt:my:mid");
  TNtuple* B = new TNtuple("B", "all B hadrons", "m:pt:y:id:nch");

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
      if (abs(pid) == 4122) {//.. Lc

        // inclusive Lc
        Lc->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), nCh);

        // B->Lc
        int midx = pythia.event[i].mother1();  // mother index
        int mpid = pythia.event[midx].id();  // mother pid
        if(abs(int(mpid/100)%10)==5 || abs(int(mpid/1000)%10)==5) {
          float mpt = pythia.event[midx].pT();  // mother pT
          float my = pythia.event[midx].y();  // mother y

          B2Lc->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), nCh, mpt, my, mpid);
        }
      } else if((abs(int(pid/100)%10)==5 || abs(int(pid/1000)%10)==5)) { // inc B-hadron
        int dau_index1 =pythia.event[i].daughter1(); 
        int dau_index2 = pythia.event[i].daughter2();
        if(debug) cout<<"0___ pid: "<<pid<<endl;
        if(daughter_is_not_Bhadron(pythia, dau_index1, dau_index2))  
          B->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), pid, nCh);
      } else if (abs(pid) == 421) {//.. D0

        // inclusive D0
        D0->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), nCh);

        // B->D0
        int midx = pythia.event[i].mother1();  // mother index
        int mpid = pythia.event[midx].id();  // mother pid
        if(abs(int(mpid/100)%10)==5 || abs(int(mpid/1000)%10)==5) {
          float mpt = pythia.event[midx].pT();  // mother pT
          float my = pythia.event[midx].y();  // mother y

          B2D0->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), nCh, mpt, my, mpid);
        }
      }
    }
  }

  // Statistics on event generation.
  pythia.stat();

  cout<<" cs: "<<pythia.info.sigmaGen()<<" weight: "<<pythia.info.nAccepted()<<endl;

  Lc->Write();
  B2Lc->Write();
  D0->Write();
  B2D0->Write();
  B->Write();
  delete outFile;

  if(evtgen) delete evtgen;
  // Done.
  return 0;
}
//
bool daughter_is_not_Bhadron(Pythia &py, int index1, int index2)
{
  if(index1 < index2 && index1 >0) {
    for(int i = index1; i<=index2; i++) {
      int pid = py.event[i].id();
      if(abs(int(pid/100)%10)==5 || abs(int(pid/1000)%10)==5) {
        if(debug) cout<<"1__: "<<pid<<endl;
        return false;
      }
    }
  } else if(index1 == index2 && index1>0) {
    int pid = py.event[index1].id();
    if((abs(int(pid/100)%10)==5 || abs(int(pid/1000)%10)==5)){
      if(debug) cout<<"2__: "<<pid<<endl;
      return false;
    }
  } else if(index2 < index1 && index2>0) {
    for(int i = index2; i<=index1; i++) {
      int pid = py.event[i].id();
      if(abs(int(pid/100)%10)==5 || abs(int(pid/1000)%10)==5) {
        if(debug) cout<<"3__: "<<pid<<endl;
        return false;
      }
    }
  } else if(index1 >0 && index2==0) {
    int pid = py.event[index1].id();
    if((abs(int(pid/100)%10)==5 || abs(int(pid/1000)%10)==5)) {
      if(debug) cout<<"4__: "<<pid<<endl;
      return false;
    }
  }

  return true;
}

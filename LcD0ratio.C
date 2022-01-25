#include <iostream>

// Header file to access Pythia 8 program elements.
#include "Pythia8/Pythia.h"

// ROOT, for histogramming.
#include "TNtuple.h"

// ROOT, for interactive graphics.
#include "TVirtualPad.h"
#include "TApplication.h"

// ROOT, for saving file.
#include "TFile.h"

using namespace Pythia8;

int main(int argc, char* argv[]) {

  char* filename = argv[1];
  int nevt = atoi(argv[2]);

  cout<<"outfile: "<<filename<<" nevt: "<<nevt<<endl;

  // Create the ROOT application environment.
  TApplication theApp("hist", &argc, argv);

  // Create Pythia instance and set it up to generate hard QCD processes
  // above pTHat = 0 GeV for pp collisions at 5.02 TeV.
  Pythia pythia;

  //Pick new random number seed for each run, based on clock.
  pythia.readString("Random:setSeed = on");
  pythia.readString("Random:seed = 0");

  pythia.readString("PhaseSpace:pTHatMin = 0.");
  pythia.readString("Beams:eCM = 5020.");
  //pythia.readString("Beams:eCM = 200.");
  //pythia.readString("Beams:eCM = 7000.");
  //
  //pythia.readString("HardQCD:all = on");
  pythia.readString("SoftQCD:nonDiffractive = on"); // shouldn't use HardQCD:all= on, which is only valid at high pT, e.g. pT > ~10 GeV/c
  // the following is the Monash tune
  //pythia.readString("Tune:pp 14");
  //pythia.readString("Tune:ee 7");

  // the following is the CUEP8M1 tune
  //pythia.readString("Tune:pp 14");
  //pythia.readString("Tune:ee 7");
  //pythia.readString("MultipartonInteractions:ecmPow=0.25208");
  //pythia.readString("MultipartonInteractions:expPow=1.6");
  //pythia.readString("MultiPartonInteractions:pT0Ref =2.4024");

  // Color reconnection tune (CR) mode0 
  //pythia.readString("Tune:pp 14");
  //pythia.readString("Tune:ee 7");
  //pythia.readString("MultipartonInteractions:ecmPow=0.215");
  //pythia.readString("MultipartonInteractions:expPow=1.85");
  //pythia.readString("StringPT:sigma =0.335");
  //pythia.readString("StringZ:aLund =0.36");
  //pythia.readString("StringZ:bLund =0.56");
  //pythia.readString("StringFlav:probQQtoQ =0.078");
  //pythia.readString("StringFlav:ProbStoUD =0.2");
  //pythia.readString("StringFlav:probQQ1toQQ0join = 0.0275,0.0275,0.0275, 0.0275");
  //pythia.readString("MultiPartonInteractions:pT0Ref =2.12");
  //pythia.readString("BeamRemnants:remnantMode =1");
  //pythia.readString("BeamRemnants:saturation= 5");
  //pythia.readString("ColourReconnection:mode = 1");
  //pythia.readString("ColourReconnection:allowDoubleJunRem =off");
  //pythia.readString("ColourReconnection:m0=2.9");
  //pythia.readString("ColourReconnection:allowJunctions =on");
  //pythia.readString("ColourReconnection:junctionCorrection=1.43");
  //pythia.readString("ColourReconnection:timeDilationMode=0");

  // Color reconnection tune (CR) mode2 
  pythia.readString("Tune:pp 14");
  pythia.readString("Tune:ee 7");
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

  // the following is the ALICE's mode0 (private communication)
  //pythia.readString("HardQCD:all = OFF");
  //pythia.readString("HardQCD:gg2ccbar = on");
  //pythia.readString("HardQCD:qqbar2ccbar = on");
  //pythia.readString("Tune:pp 14");
  //pythia.readString("Tune:ee 7");
  //pythia.readString("MultipartonInteractions:pT0Ref=2.4024");
  //pythia.readString("MultipartonInteractions:ecmPow=0.215");
  //pythia.readString("MultipartonInteractions:expPow=1.85");
  //pythia.readString("StringPT:sigma =0.335");
  //pythia.readString("StringZ:aLund =0.36");
  //pythia.readString("StringZ:bLund =0.56");
  //pythia.readString("StringFlav:probQQtoQ =0.078");
  //pythia.readString("StringFlav:ProbStoUD =0.2");
  //pythia.readString("StringFlav:probQQ1toQQ0join = 0.0275,0.0275,0.0275, 0.0275");
  //pythia.readString("MultiPartonInteractions:pT0Ref =2.12");
  //pythia.readString("BeamRemnants:remnantMode =1");
  //pythia.readString("BeamRemnants:saturation= 5");
  //pythia.readString("ColourReconnection:mode = 1");
  //pythia.readString("ColourReconnection:allowDoubleJunRem =off");
  //pythia.readString("ColourReconnection:m0=2.9");
  //pythia.readString("ColourReconnection:allowJunctions =on");
  //pythia.readString("ColourReconnection:junctionCorrection=1.43");
  //pythia.readString("ColourReconnection:timeDilationMode=0");


  pythia.init();

  // Create file on which histogram(s) can be saved.
  //TFile* outFile = new TFile("hist.root", "RECREATE");
  TFile* outFile = new TFile(filename, "RECREATE");

  // Book histogram.
  TNtuple* Lc = new TNtuple("Lc", "", "m:pt:y:nch");
  TNtuple* B2Lc = new TNtuple("B2Lc", "", "m:pt:y:nch:mpt:my:mid");
  //TNtuple* D0 = new TNtuple("D0", "", "m:pt:y:nch");
  //TNtuple* B = new TNtuple("B", "", "m:pt:y");
  //TNtuple* B0 = new TNtuple("B0", "", "m:pt:y");
  //TNtuple* Lb = new TNtuple("Lb", "", "m:pt:y");
  //TNtuple* Lb_jpsi = new TNtuple("Lb_jpsi", "", "m:pt:y");
  //TNtuple* nt = new TNtuple("nt", "", "m:pt:y");

  // Begin event loop. Generate event; skip if generation aborted.
  for (int iEvent = 0; iEvent < nevt; ++iEvent) {
    if (!pythia.next()) continue;

    // charged multiplicity
    int    nCh   = 0;
    for (int i = 0; i < pythia.event.size(); ++i) {
      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()) 
        ++nCh;
    }

    for (int i = 0; i < pythia.event.size(); ++i)
      if (abs(pythia.event[i].id()) == 4122) {//.. Lc

        // inclusive Lc
        Lc->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), nCh);

        // B->Lc
        int midx = pythia.event[i].mother1();  // mother index
        if(abs(pythia.event[midx].id())==5122 || abs(pythia.event[midx].id())==511  || 
           abs(pythia.event[midx].id())==521  || abs(pythia.event[midx].id())==10511|| 
           abs(pythia.event[midx].id())==10521|| abs(pythia.event[midx].id())==513  || 
           abs(pythia.event[midx].id())==523  || abs(pythia.event[midx].id())==10513|| 
           abs(pythia.event[midx].id())==10523|| abs(pythia.event[midx].id())==20513|| 
           abs(pythia.event[midx].id())==20523|| abs(pythia.event[midx].id())==515  || 
           abs(pythia.event[midx].id())==525  || abs(pythia.event[midx].id())==531  || 
           abs(pythia.event[midx].id())==10531|| abs(pythia.event[midx].id())==533  || 
           abs(pythia.event[midx].id())==10533|| abs(pythia.event[midx].id())==20533|| 
           abs(pythia.event[midx].id())==535  || abs(pythia.event[midx].id())==541  || 
           abs(pythia.event[midx].id())==10541|| abs(pythia.event[midx].id())==543  || 
           abs(pythia.event[midx].id())==10543|| abs(pythia.event[midx].id())==20543|| 
           abs(pythia.event[midx].id())==545)  // all B hadrons from PDG manual
        {
          float mpt = pythia.event[midx].pT();  // mother pT
          float my = pythia.event[midx].y();  // mother y
          int mid = pythia.event[midx].id();  // mother PDG id

          B2Lc->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), nCh, mpt, my, mid);
        }
      } 
     // else if(abs(pythia.event[i].id()) == 421) {//. D0

     //   //cout<<" +++"<<pythia.event[i].name()<<"++++"<<endl;
     //   D0->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y(), nCh);

     // } else if(abs(pythia.event[i].id()) == 511) { //.. B0

     //   //cout<<" +++"<<pythia.event[i].name()<<"++++"<<endl;
     //   B0->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y());

     // } else if(abs(pythia.event[i].id()) == 5122) { //lambda_b

     //   //cout<<" +++"<<pythia.event[i].name()<<"++++"<<endl;
     //   Lb->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y());

     // } else if(abs(pythia.event[i].id()) == 443) { // Lb->J/psi

     //   int midx = pythia.event[i].mother1();  // mother index
     //   if(abs(pythia.event[midx].id())==5122 || abs(pythia.event[midx].id())==511  || 
     //      abs(pythia.event[midx].id())==521  || abs(pythia.event[midx].id())==10511|| 
     //      abs(pythia.event[midx].id())==10521|| abs(pythia.event[midx].id())==513  || 
     //      abs(pythia.event[midx].id())==523  || abs(pythia.event[midx].id())==10513|| 
     //      abs(pythia.event[midx].id())==10523|| abs(pythia.event[midx].id())==20513|| 
     //      abs(pythia.event[midx].id())==20523|| abs(pythia.event[midx].id())==515  || 
     //      abs(pythia.event[midx].id())==525  || abs(pythia.event[midx].id())==531  || 
     //      abs(pythia.event[midx].id())==10531|| abs(pythia.event[midx].id())==533  || 
     //      abs(pythia.event[midx].id())==10533|| abs(pythia.event[midx].id())==20533|| 
     //      abs(pythia.event[midx].id())==535  || abs(pythia.event[midx].id())==541  || 
     //      abs(pythia.event[midx].id())==10541|| abs(pythia.event[midx].id())==543  || 
     //      abs(pythia.event[midx].id())==10543|| abs(pythia.event[midx].id())==20543|| 
     //      abs(pythia.event[midx].id())==545)
     //     Lb_jpsi->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y());

     // } else if(abs((int(pythia.event[i].id()/100)%10)) == 5 || abs((int(pythia.event[i].id()/1000)%10))==5) {

     //   //cout<<" +++"<<pythia.event[i].name()<<"++++"<<endl;
     //   B->Fill(pythia.event[i].m(), pythia.event[i].pT(), pythia.event[i].y());
     // } 
  }

  // Statistics on event generation.
  pythia.stat();

  cout<<" cs: "<<pythia.info.sigmaGen()<<" weight: "<<pythia.info.nAccepted()<<endl;

  Lc->Write();
  B2Lc->Write();
  //D0->Write();
  //B->Write();
  //B0->Write();
  //Lb->Write();
  //Lb_jpsi->Write();
  delete outFile;

  // Done.
  return 0;
}

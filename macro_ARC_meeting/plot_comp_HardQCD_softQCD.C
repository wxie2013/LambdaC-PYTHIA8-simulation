{
  TFile f1("root_file/cross_CUETP8M1_HardQCD_ON_5B_EvtGen.root");
  TFile f2("root_file/cross_CUETP8M1_soft_nonDiffractive_ON_1B_EvtGen.root");
  //TFile f3("/mnt/c/Users/puppy/Desktop/HIN-21-004/Rui_ana_code/B2Lc_Pythia/root_file/abs_y_7/cross_B2Lc_CUETP8M1_HardQCD_ON.root");
  //TFile f4("/mnt/c/Users/puppy/Desktop/HIN-21-004/Rui_ana_code/B2Lc_Pythia/root_file/abs_y_2/cross_B2Lc_CUETP8M1_HardQCD_ON.root");

  TH1F* hB_hard = (TH1F*)f1.Get("hB")->Clone("hB_hard");
  TH1F* hB_soft= (TH1F*)f2.Get("hB")->Clone("hB_soft");

  hB_hard->SetLineColor(1);
  hB_soft->SetLineColor(2);

  hB_hard->SetLineWidth(2);
  hB_soft->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1", "", 700, 500);
  gPad->SetLogy(1);
  hB_hard->Draw("");
  hB_soft->Draw("same");

  c1->SaveAs("figure/HardQCD_softQCD.gif");
}

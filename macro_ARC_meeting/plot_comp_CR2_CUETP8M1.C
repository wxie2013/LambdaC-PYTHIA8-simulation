{
  TFile f1("root_file/cross_CR2_soft_nonDiffractive_ON_1B_EvtGen.root");
  TFile f2("root_file/cross_CUETP8M1_soft_nonDiffractive_ON_1B_EvtGen.root");

  TH1F* hB_cr2 = (TH1F*)f1.Get("hB")->Clone("hB_cr2");
  TH1F* hB_cuet= (TH1F*)f2.Get("hB")->Clone("hB_cuet");

  hB_cr2->SetLineColor(1);
  hB_cuet->SetLineColor(2);

  hB_cr2->SetLineWidth(2);
  hB_cuet->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1", "", 700, 500);
  gPad->SetLogy(1);
  hB_cr2->Draw("");
  hB_cuet->Draw("same");

  c1->SaveAs("figure/cr2_CUETP8M1.gif");
}

{
  TFile f1("root_file/inc_bhadron_weight_CR2_soft_nonDiffractive_ON_1B_EvtGen.root");
  TFile f2("root_file/inc_bhadron_weight_CUETP8M1_HardQCD_ON_5B_EvtGen.root");

  TH1F* hweight_cr2 = (TH1F*)f1.Get("hweight")->Clone("hweight_cr2");
  TH1F* hweight_cuet = (TH1F*)f2.Get("hweight")->Clone("hweight_cuet");

  hweight_cr2->SetLineColor(2);
  hweight_cuet->SetLineColor(1);

  hweight_cr2->SetLineWidth(2);
  hweight_cuet->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1", "", 700, 500);
  hweight_cr2->Draw("");
  hweight_cr2->SetMaximum(1);
  hweight_cr2->SetMinimum(0);
  hweight_cr2->GetXaxis()->SetRangeUser(0, 60);
  hweight_cuet->Draw("same");
  hweight_cr2->Draw("same");


  c1->SaveAs("figure/weight.gif");
}

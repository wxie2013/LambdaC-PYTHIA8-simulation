{
  TFile f0("root_file/Bhadron_y7_weight_1b1events_09082019_fit.root");
  TFile f1("root_file/FONLL_Bhadron_y7.root");
  TFile f2("root_file/cross_CUETP8M1_HardQCD_ON_5B_EvtGen.root");
  TFile f3("root_file/inc_bhadron_weight_CUETP8M1_HardQCD_ON_5B_EvtGen.root");

  TH1F* h_Bhadron_pt_y7 = (TH1F*)f0.Get("h_Bhadron_pt_y7")->Clone();
  TH1F* hB = (TH1F*)f2.Get("hB")->Clone();
  TGraph* hB_fonll = (TGraph*)f1.Get("FONLL_Bhadrons_crosssection")->Clone();
  TH1F* hweight = (TH1F*)f3.Get("hweight")->Clone();
  hweight->SetLineColor(2);
  TGraphErrors* Bhadron_ptweight = (TGraphErrors*)f0.Get("Bhadron_ptweight")->Clone();

  TCanvas* c1 = new TCanvas("c1", "", 1400, 500);
  c1->Divide(2, 1);
  c1->cd(1);
  gPad->SetLogy(1);
  hB_fonll->GetXaxis()->SetRangeUser(0, 100);
  hB_fonll->Draw("acp");
  hB_fonll->SetMaximum(1e9);
  h_Bhadron_pt_y7->Draw("same");
  hB->SetLineColor(2);
  hB->Draw("same");

  c1->cd(2);
  Bhadron_ptweight->SetMaximum(1);
  Bhadron_ptweight->SetMinimum(0);
  Bhadron_ptweight->Draw("acp");
  hweight->Draw("same");

  c1->SaveAs("figure/compare_with_Rui.gif");
}

{
  TFile f1("root_file/cross_CR2_soft_nonDiffractive_ON_1B_PY.root");
  TFile f2("root_file/cross_CR2_soft_nonDiffractive_ON_1B_EvtGen.root");

  TH1F* hB2Lc_py = (TH1F*)f1.Get("hB2Lc")->Clone("hB2Lc_py");
  TH1F* hB2Lc_evtg = (TH1F*)f2.Get("hB2Lc")->Clone("hB2Lc_evtg");

  hB2Lc_py->SetLineColor(1);
  hB2Lc_evtg->SetLineColor(2);

  hB2Lc_py->SetLineWidth(2);
  hB2Lc_evtg->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1", "", 1400, 500);
  c1->Divide(2, 1);
  c1->cd(1);
  gPad->SetLogy(1);
  hB2Lc_py->Draw("");
  hB2Lc_evtg->Draw("same");

  c1->cd(2);
  TH1F* ratio = (TH1F*)hB2Lc_evtg->Clone("ratio");
  ratio->Divide(hB2Lc_py);
  ratio->Draw();

  c1->SaveAs("figure/evtgen_py.gif");
}

{
  TFile f1("root_file/result_prompt_ratio_CR2_soft_nonDiffractive_ON_1B_EvtGen.root");
  TFile f2("root_file/result_prompt_ratio_weight_from_CUETP8M1_HardQCD_ON_5B_EvtGen.root");

  TH1F* py_cr2 = (TH1F*)f1.Get("prompt_ratio_py")->Clone("py_cr2");
  TH1F* fonll_cr2= (TH1F*)f1.Get("prompt_ratio_FONLL")->Clone("fonll_cr2");

  TH1F* py_cuet = (TH1F*)f2.Get("prompt_ratio_py")->Clone("py_cuet");
  TH1F* fonll_cuet= (TH1F*)f2.Get("prompt_ratio_FONLL")->Clone("fonll_cuet");

  py_cr2->SetLineColor(2);
  fonll_cr2->SetLineColor(2);

  py_cr2->SetLineWidth(2);
  fonll_cr2->SetLineWidth(2);
  py_cuet->SetLineWidth(2);
  fonll_cuet->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1", "", 700, 500);
  py_cr2->SetMaximum(1);
  py_cr2->SetMinimum(0.5);
  py_cr2->Draw("");
  fonll_cr2->Draw("same");
  py_cuet->Draw("same");
  fonll_cuet->Draw("same");

  c1->SaveAs("figure/prompt_ratio_using weight_from_cr2_CUETP8M1.gif");
}

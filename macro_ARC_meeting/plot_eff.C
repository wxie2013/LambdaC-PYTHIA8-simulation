{
  TFile f1("root_file/prompt_pt2_pt4_pt10_combine_fifthturn.root");
  TFile f2("root_file/nonprompt_pt2_pt4_pt10_combine.root");

  TH1F* eff_prompt = (TH1F*)f1.Get("hrecoeff_combine")->Clone("eff_prompt");
  TH1F* eff_np = (TH1F*)f2.Get("hrecoeff_combine")->Clone("eff_np");

  eff_prompt->SetLineColor(1);
  eff_np->SetLineColor(2);

  eff_prompt->SetLineWidth(2);
  eff_np->SetLineWidth(2);

  TCanvas* c1 = new TCanvas("c1", "", 700, 500);
  eff_prompt->SetMaximum(0.5);
  eff_prompt->SetMinimum(0);
  eff_prompt->Draw("");
  eff_np->Draw("same");

  c1->SaveAs("figure/eff.gif");
}

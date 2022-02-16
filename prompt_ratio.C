#include "common.h"

void prompt_ratio()
{
  TFile result("root_file/result_prompt_ratio.root", "RECREATE");
  TFile f0("/depot/cms/users/wxie/B2Lc/tot_1B_CR2_soft_non_diff_on.root");
  TFile f1("root_file/inc_bhadron_weight.root");
  TFile f2("root_file/cross_B2Lc.root");
  TFile f3("root_file/prompt_pt2_pt4_pt10_combine_fifthturn.root"); // accp*eff prompt Lc
  TFile f4("root_file/nonprompt_pt2_pt4_pt10_combine.root"); // accp*eff non-prompt Lc

  f0.cd(); //ROOT bug. need to add this to avoid crash
  TNtuple* Lc = (TNtuple*)f0.Get("Lc")->Clone("Lc");
  TNtuple* B2Lc = (TNtuple*)f0.Get("B2Lc")->Clone("B2Lc");
  TH1D* hweight = (TH1D*) f1.Get("hweight")->Clone("hweight");
  TF1* fun_btw_15_100GeV = (TF1*) f1.Get("fun_btw_15_100GeV")->Clone("fun_btw_15_100GeV");
  TH1F* eff_prompt = (TH1F*)f3.Get("hrecoeff_combine")->Clone("eff_prompt");
  TH1F* eff_nonprompt = (TH1F*)f4.Get("hrecoeff_combine")->Clone("eff_nonprompt");

  // CR2 describe prompt data well, thus treat it the same for PYTHIA and FONLL
  TH1F* h_inc = (TH1F*) f2.Get("hLc")->Clone("h_inc"); 
  TH1F* h_B2Lc_py = (TH1F*) f2.Get("hB2Lc")->Clone("h_B2Lc_py");
  TH1F* h_prompt = (TH1F*)h_inc->Clone("h_prompt");
  h_prompt->Add(h_B2Lc_py, -1);

  //
  TH1F* h_B2Lc_FONLL = new TH1F("h_B2Lc_FONLL", "FONLL B->Lc pT spectrum", nbins, bin_edge);
  float pt, y, mpt;
  B2Lc->SetBranchAddress("pt", &pt);
  B2Lc->SetBranchAddress("y", &y);
  B2Lc->SetBranchAddress("mpt", &mpt);
  for(int i = 0; i<B2Lc->GetEntries(); i++) {
    B2Lc->GetEntry(i);

    if(fabs(y)>1 || mpt>mpt_fit_high)
      continue;

    float weight;
    if(mpt<mpt_fit_low) {
      int ib = hweight->FindBin(mpt);
      weight = hweight->GetBinContent(ib);
    } else {
      weight = fun_btw_15_100GeV->Eval(mpt);
    } 

    h_B2Lc_FONLL->Fill(pt, weight);
  }
  divideBinWidth(h_B2Lc_FONLL);
  h_B2Lc_FONLL->Scale(1/(lum*2));

  // now apply accp*eff 
  h_prompt->Multiply(eff_prompt);
  h_B2Lc_FONLL->Multiply(eff_nonprompt);
  h_B2Lc_py->Multiply(eff_nonprompt);

  TH1F* h_inc_py = (TH1F*)h_prompt->Clone("h_inc_py");
  h_inc_py->Add(h_B2Lc_py);

  TH1F* h_inc_FONLL = (TH1F*)h_prompt->Clone("h_inc_FONLL");
  h_inc_FONLL->Add(h_B2Lc_FONLL);

  // now prompt ratio
  TH1F* prompt_ratio_py = (TH1F*)h_prompt->Clone("prompt_ratio_py");
  prompt_ratio_py->Divide(h_inc_py);

  TH1F* prompt_ratio_FONLL = (TH1F*)h_prompt->Clone("prompt_ratio_FONLL");
  prompt_ratio_FONLL->Divide(h_inc_FONLL);

  result.cd();
  h_prompt->Write();
  h_B2Lc_FONLL->Write();
  h_B2Lc_py->Write();
  h_inc_py->Write();
  h_inc_FONLL->Write();
  prompt_ratio_py->Write();
  prompt_ratio_FONLL->Write();
  result.Close();
}

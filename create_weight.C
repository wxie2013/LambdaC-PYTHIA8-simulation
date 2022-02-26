#include "common.h"

//
void create_weight()
{
  TFile f0("root_file/FONLL_Bhadron_y7.root");
  //string infile = "root_file/cross_CUETP8M1_HardQCD_ON_5B_EvtGen.root";
  //string outfile = "root_file/inc_bhadron_weight_CUETP8M1_HardQCD_ON_5B_EvtGen.root";
  //string infile = "root_file/cross_CR2_soft_nonDiffractive_ON_1B_EvtGen.root";
  //string outfile = "root_file/inc_bhadron_weight_CR2_soft_nonDiffractive_ON_1B_EvtGen.root";
  string infile = "root_file/cross_CUETP8M1_soft_nonDiffractive_ON_1B_EvtGen.root";
  string outfile = "root_file/inc_bhadron_weight_CUETP8M1_soft_nonDiffractive_ON_1B_EvtGen.root";

  TFile f1(infile.c_str());
  TFile* result = new TFile(outfile.c_str(), "recreate");

  TH1D* hB = (TH1D*)f1.Get("hB")->Clone();
  TGraph* FONLL_Bhadrons_crosssection = (TGraph*)f0.Get("FONLL_Bhadrons_crosssection")->Clone(); // |y|<7

  TH1D* hweight = (TH1D*)hB->Clone("hweight");

  for (int i = 0; i<hweight->GetNbinsX(); i++) {
    float pt = hweight->GetBinCenter(i+1);
    if (hB->GetBinContent(i+1) == 0)
      continue;
    float con = FONLL_Bhadrons_crosssection->Eval(pt)/hB->GetBinContent(i+1);
    float err = FONLL_Bhadrons_crosssection->Eval(pt)/pow(hB->GetBinContent(i+1),2)*hB->GetBinError(i+1);
    hweight->SetBinContent(i+1, con);
    hweight->SetBinError(i+1, err);
  }

  //.. use fit function from 15-100 GeV/c to avoid fluctuation
  hweight->Fit("pol1", "", "", mpt_fit_low, mpt_fit_high);
  TF1* fun_btw = hweight->GetFunction("pol1");
  fun_btw->SetName("fun_btw");
  result->cd();
  hweight->Write();
  fun_btw->Write();
  FONLL_Bhadrons_crosssection->Write();
  //result->Close();
}

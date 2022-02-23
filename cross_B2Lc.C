#include "common.h"

//
void cross_B2Lc()
{
    //---------------------------------------------------------------------------------------
    // Note: when switch files, need to update the N_pp and sig_pp in common.h correspondingly 
    //---------------------------------------------------------------------------------------
    string infile = "/depot/cms/users/wxie/B2Lc/CR2_Soft_nonDiffractive_ON_1B_EvtGen/tot_1B_CR2_soft_non_diff_on_EvtGen.root";
    string outfile = "root_file/cross_B2Lc_CR2_soft_non_diff_on_EvtGen.root";
    //string infile = "/depot/cms/users/wxie/B2Lc/CR2_Soft_nonDiffractive_ON_1B/tot_1B_CR2_soft_non_diff_on.root";
    //string outfile = "root_file/cross_B2Lc_CR2_soft_non_diff_on.root";
    //string infile = "/depot/cms/users/wxie/B2Lc/CUETP8M1_HardQCD_ON_10B/tot_10B_CUETP8M1_HardQCD_ON.root";
    //string outfile = "root_file/cross_B2Lc_CUETP8M1_HardQCD_ON.root";
    //string infile = "/depot/cms/users/wxie/B2Lc/CR2_HardQCD_ON_5B/tot_5B_CR2_HardQCD_ON.root";
    //string outfile = "root_file/cross_B2Lc_CR2_HardQCD_ON.root";

    TFile *f_in = new TFile(infile.c_str());

    TNtuple* Lc = (TNtuple*)f_in->Get("Lc")->Clone("Lc");
    TNtuple* B2Lc = (TNtuple*)f_in->Get("B2Lc")->Clone("B2Lc");
    TNtuple* B = (TNtuple*)f_in->Get("B")->Clone("B");

    TH1 *hLc = new TH1D("hLc","incl. Lc", nbins, bin_edge);
    TH1 *hB2Lc = new TH1D("hB2Lc","B->Lc", nbins, bin_edge);
    TH1 *hB = new TH1D("hB","incl. B-hadron", 400, 0, 100);
    hLc->Sumw2();
    hB2Lc->Sumw2();
    hB->Sumw2();

    B->Project("hB", "pt", "abs(y)<2"); // |y(B)|<2 for all |y(Lc)|<1
    B2Lc->Project("hB2Lc", "pt", "abs(y)<1");
    Lc->Project("hLc", "pt", "abs(y)<1");

    divideBinWidth(hB);
    divideBinWidth(hB2Lc);
    divideBinWidth(hLc);

    hB->Scale(1/(lum*2)); 
    hB2Lc->Scale(1/(lum*2));
    hLc->Scale(1/(lum*2));

    TFile *f_out = new TFile(outfile.c_str(), "recreate");
    hB2Lc->Write();
    hLc->Write();
    hB->Write();
}

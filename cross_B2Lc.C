#include "common.h"

//
void cross_B2Lc()
{
    TFile *f_in = new TFile("/depot/cms/users/wxie/B2Lc/tot_1B_CR2_soft_non_diff_on.root");

    TNtuple* Lc = (TNtuple*)f_in->Get("Lc")->Clone("Lc");
    TNtuple* B2Lc = (TNtuple*)f_in->Get("B2Lc")->Clone("B2Lc");
    TNtuple* B = (TNtuple*)f_in->Get("B")->Clone("B");

    TH1 *hLc = new TH1D("hLc","incl. Lc", nbins, bin_edge);
    TH1 *hB2Lc = new TH1D("hB2Lc","B->Lc", nbins, bin_edge);
    TH1 *hB = new TH1D("hB","incl. B-hadron", 100, 0, 100);

    B->Project("hB", "pt");
    B2Lc->Project("hB2Lc", "pt", "abs(y)<1");
    Lc->Project("hLc", "pt", "abs(y)<1");

    divideBinWidth(hB);
    divideBinWidth(hB2Lc);
    divideBinWidth(hLc);

    hB->Scale(1/(lum*2)); 
    hB2Lc->Scale(1/(lum*2));
    hLc->Scale(1/(lum*2));

    TFile *f_out = new TFile("root_file/cross_B2Lc.root", "recreate");
    hB2Lc->Write();
    hLc->Write();
    hB->Write();
}

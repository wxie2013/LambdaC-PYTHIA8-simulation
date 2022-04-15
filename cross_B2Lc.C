#include "common.h"

//
void cross_B2Lc()
{
    //---------------------------------------------------------------------------------------
    // Note: when switch files, need to update the N_pp and sig_pp in common.h correspondingly 
    //---------------------------------------------------------------------------------------
    string infile = "/depot/cms/users/wxie/B2Lc/CR2_soft_nonDiffractive_ON_1B_EvtGen_wD0/tot.root";
    string outfile = "root_file/cross_CR2_soft_nonDiffractive_ON_1B_EvtGen_wD0.root";

    TFile *f_in = new TFile(infile.c_str());

    TNtuple* Lc = (TNtuple*)f_in->Get("Lc")->Clone("Lc");
    TNtuple* B2Lc = (TNtuple*)f_in->Get("B2Lc")->Clone("B2Lc");
    TNtuple* B = (TNtuple*)f_in->Get("B")->Clone("B");
    TNtuple* D0 = (TNtuple*)f_in->Get("D0")->Clone("D0");
    TNtuple* B2D0 = (TNtuple*)f_in->Get("B2D0")->Clone("B2D0");

    TH1 *hLc = new TH1D("hLc","incl. Lc", nbins, bin_edge);
    TH1 *hB2Lc = new TH1D("hB2Lc","B->Lc", nbins, bin_edge);
    TH1 *hB = new TH1D("hB","incl. B-hadron", 400, 0, 100);
    TH1 *hD0 = new TH1D("hD0","incl. D0", nbins, bin_edge);
    TH1 *hB2D0 = new TH1D("hB2D0","B->D0", nbins, bin_edge);
    hLc->Sumw2();
    hB2Lc->Sumw2();
    hB->Sumw2();
    hD0->Sumw2();
    hB2D0->Sumw2();

    B->Project("hB", "pt");
    B2Lc->Project("hB2Lc", "pt", "abs(y)<1");
    Lc->Project("hLc", "pt", "abs(y)<1");
    B2D0->Project("hB2D0", "pt", "abs(y)<1");
    D0->Project("hD0", "pt", "abs(y)<1");

    divideBinWidth(hB);
    divideBinWidth(hB2Lc);
    divideBinWidth(hLc);
    divideBinWidth(hB2D0);
    divideBinWidth(hD0);

    hB->Scale(1/(lum*2)); 
    hB2Lc->Scale(1/(lum*2));
    hLc->Scale(1/(lum*2));
    hB2D0->Scale(1/(lum*2));
    hD0->Scale(1/(lum*2));

    TFile *f_out = new TFile(outfile.c_str(), "recreate");
    hB2Lc->Write();
    hLc->Write();
    hB2D0->Write();
    hD0->Write();
    hB->Write();
}

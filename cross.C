void divideBinWidth(TH1* h)
{
    for(int i=1;i<=h->GetNbinsX();i++)
    {   
        Float_t contentvalue=h->GetBinContent(i);
        Float_t content_err=h->GetBinError(i);
        contentvalue/=h->GetBinWidth(i);
        content_err/=h->GetBinWidth(i);
        h->SetBinContent(i,contentvalue);
        h->SetBinError(i,content_err);
    }   
}





void cross()
{
    //TFile *f_in = new TFile("data_softQCD_on/oo.root");
    TFile *f_in = new TFile("oo.root");

    TNtuple* D0 = (TNtuple*)f_in->Get("D0")->Clone("D0");
    TNtuple* Lc = (TNtuple*)f_in->Get("Lc")->Clone("Lc");
    TNtuple* B = (TNtuple*)f_in->Get("B")->Clone("B");

    int N_pp = 1.2e5;
    //float sig_pp = 1.009e6;
    float sig_pp = 47720;

    float lum = N_pp/sig_pp;

    const Int_t NBINS = 5;
    Double_t edges[NBINS + 1]={4,5,6,8,10,20};
    TH1 *hLc = new TH1D("hLc","Lc",NBINS,edges);
    TH1 *hD0 = new TH1D("hD0","D0",NBINS,edges);
    TH1 *hB = new TH1D("hB","B",10,0, 25);

    B->Project("hB", "pt", "abs(y)<1");
    D0->Project("hD0", "pt", "abs(y)<1");
    Lc->Project("hLc", "pt", "abs(y)<1");

    divideBinWidth(hB);
    divideBinWidth(hD0);
    divideBinWidth(hLc);

    hB->Scale(1/(lum*2));
    hD0->Scale(1/(lum*2));
    hLc->Scale(1/(lum*2));

    TFile *f_out = new TFile("cross.root", "recreate");
    hD0->Write();
    hLc->Write();
    hB->Write();
}


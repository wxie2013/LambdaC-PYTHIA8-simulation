const int nbins = 9;
const float bin_edge[nbins+1] = {3, 4, 5, 6, 8, 10, 12.5, 15, 20, 30};
const float mpt_fit_low = 26; //lower edge of weight fit
const float mpt_fit_high = 60; //upper edge of weight fit above which too large fluctuation

const float N_pp = 1.0e9;
const float sig_pp = 4.772e10; // unit: pb (SoftQCD_nonDiffractive = on)
//const float sig_pp = 1.005e+12; // unit: pb(HardQCD_ON)

float lum = N_pp/sig_pp;

//
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


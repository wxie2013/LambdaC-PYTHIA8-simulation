{
	TFile *f_on = new TFile("mode2_softNonDiff/oo.root");
	TFile *f_off = new TFile("mode2/oo.root");
	TNtuple* D0_on = (TNtuple*)f_on->Get("D0");
	TNtuple* D0_off = (TNtuple*)f_off->Get("D0");
	TNtuple* Lc_on = (TNtuple*)f_on->Get("Lc");
	TNtuple* Lc_off = (TNtuple*)f_off->Get("Lc");
	TH1F* h0_on = new TH1F("h0_on", "", 20, 0, 20);
	TH1F* h1_on = new TH1F("h1_on", "", 20, 0, 20);
	TH1F* h0_off = new TH1F("h0_off", "", 20, 0, 20);
	TH1F* h1_off = new TH1F("h1_off", "", 20, 0, 20);

	D0_on->Project("h0_on", "pt", "abs(y)<0.5");
	Lc_on->Project("h1_on", "pt", "abs(y)<0.5");
	D0_off->Project("h0_off", "pt", "abs(y)<0.5");
	Lc_off->Project("h1_off", "pt", "abs(y)<0.5");

	h0_on->Sumw2();
	h1_on->Sumw2();
	h1_on->Divide(h0_on);

	h0_off->Sumw2();
	h1_off->Sumw2();
	h1_off->Divide(h0_off);
	
	h1_on->SetMarkerStyle(20);
	h1_off->SetMarkerStyle(24);

	h1_on->SetMaximum(1.0);
	h1_on->Draw();
	h1_off->Draw("same");

	TFile f("m.root", "recreate");
	h1_on->Write();
	h1_off->Write();
	f.Close();
}

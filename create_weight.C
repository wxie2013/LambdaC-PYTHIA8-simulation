// read FONLL txt file 
TGraph read_FONLL_inc_Bhadron_Y_pm2()
{
  ifstream fin;
  fin.open ("FONLL_inc_Bhadron_Y_pm2.txt");
  float x, y;

  vector<float>vx, vy;
  while(true) {
    fin>>x>>y;

    if(fin.eof())
      break;

    vx.push_back(x);
    vy.push_back(y);
  }

  TGraph gra(vx.size(), vx.data(), vy.data());

  return gra;
}
//
void create_weight()
{
  TFile f0("root_file/FONLL_Bhadron_y7.root");
  TFile f1("root_file/cross_B2Lc.root");
  TFile* result = new TFile("root_file/inc_bhadron_weight.root", "recreate");

  TH1D* hB = (TH1D*)f1.Get("hB")->Clone();
  //TGraph* FONLL_Bhadrons_crosssection = (TGraph*)f0.Get("FONLL_Bhadrons_crosssection")->Clone(); // |y|<7
  TGraph gra = read_FONLL_inc_Bhadron_Y_pm2();
  TGraph* FONLL_Bhadrons_crosssection = &gra; //|y|<2
  FONLL_Bhadrons_crosssection->SetName("FONLL_Bhadrons_crosssection");

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
  hweight->Fit("pol1", "", "", 15, 100);
  TF1* fun_btw_15_100GeV = hweight->GetFunction("pol1");
  fun_btw_15_100GeV->SetName("fun_btw_15_100GeV");
  result->cd();
  hweight->Write();
  fun_btw_15_100GeV->Write();
  FONLL_Bhadrons_crosssection->Write();
  //result->Close();
}

{
    D0->Draw("pt>>h0(20, 0, 20)", "abs(y)<1");
    Lc->Draw("pt>>h1(20, 0, 20)", "abs(y)<1");
    h0->Sumw2();
    h1->Sumw2();

    h1->Divide(h0);

    h1->Draw();

    TFile f("m.root", "recreate");
    h1->Write();
    f.Close();
}

{
  gStyle->SetOptStat(0);

  //TFile *f = new TFile("/global/homes/j/jrager/LowE/Data/EfficiencyFineBinn/EfficiencyDS1chan692.root");
  TFile *f = new TFile("/global/homes/j/jrager/LowE/Data/EfficiencyDS2chan592.root");
  TH1F *h0 = (TH1F*)f->Get("Eff");
  //h0->Rebin(4);
  //h0->Scale(1/4.);
  h0->Sumw2();
  h0->Draw("E1");
}

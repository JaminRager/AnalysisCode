{
  gStyle->SetOptStat(0);
    
  TFile *f = new TFile("UnscaledEnrDS0orig.root");
  TH1D *h0 = (TH1D*)f->Get("LE");
  h0->GetYaxis()->SetTitle("cts/kg/d/keV");
  Double_t DS0ExposureEnr = 4/473.8;
  Double_t DS0ExposureNat = 4/184.1;
  Double_t DS1ExposureEnr = 4/669.303;
  Double_t DS1ExposureNat = 4/63.327;
  Double_t DS2ExposureEnr = 4/106.089;
  Double_t DS2ExposureNat = 4/10.672;
  Double_t DS5aExposureEnr = 4/1249.103;
  Double_t DS5aExposureNat = 4/630.069;
  Double_t DS6ExposureEnr = 4/1079.0;
  Double_t DS6ExposureNat = 4/506.0;
  h0->Scale(DS0ExposureEnr);
  h0->Draw("HIST");
  TLine *line = new TLine(20, 0.0105466, 100, 0.0105466);
  line->SetLineColor(kRed);
  //line->Draw()
}

{
  gStyle->SetOptStat(0);

  //.x MJDTalkPlotStyle.C

  TFile *f = new TFile("CombinedDS4_Newest.root");
  TH1F *h0 = (TH1F*)f->Get("natHE");
  TH1F *h1 = (TH1F*)f->Get("enrHE");

  TLegend *legend = new TLegend(0.1, 0.7, 0.48, 0.9);
  legend->AddEntry(natHE, "natural", "f");
  legend->AddEntry(enrHE, "enriched", "f");

  //Double_t DS0ExposureEnr = 1/473.735;
  //Double_t DS0ExposureNat = 1/184.1;
  //Double_t DS0ExposureNat = 1/(2*184.1);
  //Double_t DS0ExposureEnr = 1/(2*473.735);
  //Double_t DS1ExposureEnr = 1/661.730;
  //Double_t DS1ExposureNat = 1/63.195;
  //Double_t DS1ExposureEnr = 1/(2*661.730);
  //Double_t DS1ExposureNat = 1/(2*63.195);
  //Double_t DS2ExposureEnr = 1/106.286;
  //Double_t DS2ExposureNat = 1/10.679;
  //Double_t DS2ExposureEnr = 1/(2*106.286);
  //Double_t DS2ExposureNat = 1/(2*10.679);
  //Double_t DS3ExposureEnr = 1/367.811;
  //Double_t DS3ExposureNat = 1/81.484;
  //Double_t DS3ExposureEnr = 1/(2*367.811);
  //Double_t DS3ExposureNat = 1/(2*81.484);
  Double_t DS4ExposureEnr = 1/102.189;
  Double_t DS4ExposureNat = 1/73.845;
  //Double_t DS4ExposureEnr = 1/(2*102.189);
  //Double_t DS4ExposureNat = 1/(2*73.845);
  //Double_t DS5aExposureEnr = 1/1236.6;
  //Double_t DS5aExposureNat = 1/627.6;
  //Double_t DS5aExposureEnr = 1/(2*1236.6);
  //Double_t DS5aExposureNat = 1/(2*627.6);
  //Double_t DS5bExposureEnr = 1/667.7;
  //Double_t DS5bExposureNat = 1/336.2;
  //Double_t DS5bExposureEnr = 1/(2*667.7);
  //Double_t DS5bExposureNat = 1/(2*336.2);
  //Double_t DS6ExposureEnr = 1/1028.0;
  //Double_t DS6ExposureNat = 1/471.0;
  //Double_t DS6ExposureEnr = 1/(2*1028.0);
  //Double_t DS6ExposureNat = 1/(2*471.0);

  h0->Rebin(4);
  h1->Rebin(4);
  h0->GetXaxis()->SetRange(21,100);
  h1->GetXaxis()->SetRange(21,100);

  //h0->Rebin(8);
  //h0->Rebin(4);
  //h0->Scale(DS4ExposureNat);  
  //h0->SetLineColor(kBlue);
  //h0->Draw("HIST");
  //h0->Draw();
  //h1->Rebin(8);
  //h1->Rebin(4);
  h1->Scale(DS4ExposureEnr);
  h1->SetLineColor(kRed);
  h1->Draw("HIST");
  //h1->Draw("same");
  //h1->Draw("HIST");
}

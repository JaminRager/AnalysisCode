{
  gStyle->SetOptStat(0);

  TFile *f = new TFile("1DTETM_Superimposed.root");
  TH1F *h0 = (TH1F*)f->Get("htrapETailMin0");
  TH1F *h1 = (TH1F*)f->Get("htrapETailMin1");
  TH1F *h2 = (TH1F*)f->Get("htrapETailMin2");
  TH1F *h3 = (TH1F*)f->Get("htrapETailMin3");
  TH1F *h4 = (TH1F*)f->Get("htrapETailMin4");
  TH1F *h5 = (TH1F*)f->Get("htrapETailMin5");
  TH1F *h6 = (TH1F*)f->Get("htrapETailMin6");

  TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->AddEntry(htrapETailMin0,"DS0","f");
  legend->AddEntry(htrapETailMin1,"DS1","f");
  legend->AddEntry(htrapETailMin2,"DS2","f");
  legend->AddEntry(htrapETailMin3,"DS3","f");
  legend->AddEntry(htrapETailMin4,"DS4","f");
  legend->AddEntry(htrapETailMin5,"DS5","f");
  legend->AddEntry(htrapETailMin6,"DS6","f");

  h0->Draw();
  h0->SetLineColor(kBlack);
  h1->Draw("same");
  h1->SetLineColor(kRed);
  h2->Draw("same");
  h2->SetLineColor(kCyan);
  h3->Draw("same");
  h3->SetLineColor(kOrange);
  h4->Draw("same");
  h4->SetLineColor(kGreen);
  h5->Draw("same");
  h5->SetLineColor(kBlue);
  h6->Draw("same");
  h6->SetLineColor(kViolet);
  TLine *line95 = new TLine(0.542249, 0, 0.542249, 7000000);
  line95->SetLineColor(kPink);
  line95->Draw();
  legend->Draw()
}

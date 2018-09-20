{
  gStyle->SetOptStat(0);

  TFile *f = new TFile("ToEDS6.root");
  TH2F *h0 = (TH2F*)f->Get("ToE");
  h0->Draw();
  TLine *line95 = new TLine(0, 2, 20, 2);
  line95->SetLineColor(kRed);
  line95->Draw();
  TLine *line96 = new TLine(0, 1, 20, 1);
  line96->SetLineColor(kRed);
  line96->Draw();
}

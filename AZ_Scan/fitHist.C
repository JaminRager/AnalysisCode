{
  gROOT->ForceStyle();
  //gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TFile *dataFile = new TFile("D2AZang10.root");
  TH1D *PWidth = (TH1D*)dataFile->Get("PWidth");
  TH1 *rebin = PWidth->Rebin(4,"rebin");
  rebin->Fit("gaus");

  new TBrowser();

}

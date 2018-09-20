{
  gROOT->ForceStyle();
  //gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TFile *dataFile1 = new TFile("pw35006445rt10.root");
  TH1D *PWidth = (TH1D*)dataFile1->Get("PWidth");
  TH1 *rebin1 = PWidth->Rebin(2,"rebin");
  TH1 *rebin12 = PWidth->Rebin(4,"rebin1");
  rebin12->Fit("gaus");

  TFile *dataFile2 = new TFile("pw35006445rt50.root");
  TH1D *PWidth2 = (TH1D*)dataFile2->Get("PWidth");
  TH1 *rebin2 = PWidth2->Rebin(2,"rebin");
  TH1 *rebin22 = PWidth2->Rebin(4,"rebin1");
  //rebin22->Fit("gaus");

  TFile *dataFile3 = new TFile("pw35006445rt99.root");
  TH1D *PWidth3 = (TH1D*)dataFile3->Get("PWidth");
  TH1 *rebin3 = PWidth3->Rebin(2,"rebin"); 
  TH1 *rebin32 = PWidth3->Rebin(4,"rebin1");

  TFile *dataFile4 = new TFile("pw35006450rt10.root");
  TH1D *PWidth4 = (TH1D*)dataFile4->Get("PWidth");
  TH1 *rebin4 = PWidth4->Rebin(2,"rebin");
  TH1 *rebin42 = PWidth4->Rebin(4,"rebin1");
  rebin42->Fit("gaus");

  TFile *dataFile5 = new TFile("pw35006450rt50.root");
  TH1D *PWidth5 = (TH1D*)dataFile5->Get("PWidth");
  TH1 *rebin5 = PWidth5->Rebin(2,"rebin");
  TH1 *rebin52 = PWidth5->Rebin(4,"rebin1");

  TFile *dataFile6 = new TFile("pw35006450rt99.root");
  TH1D *PWidth6 = (TH1D*)dataFile6->Get("PWidth");
  TH1 *rebin6 = PWidth6->Rebin(2,"rebin");
  TH1 *rebin62 = PWidth6->Rebin(4,"rebin1");

  TFile *dataFile7 = new TFile("pw35006455rt10.root");
  TH1D *PWidth7 = (TH1D*)dataFile7->Get("PWidth");
  TH1 *rebin7 = PWidth7->Rebin(2,"rebin");
  TH1 *rebin72 = PWidth7->Rebin(4,"rebin1"); 
  rebin72->Fit("gaus");

  TFile *dataFile8 = new TFile("pw35006455rt50.root");
  TH1D *PWidth8 = (TH1D*)dataFile8->Get("PWidth");
  TH1 *rebin8 = PWidth8->Rebin(2,"rebin");
  TH1 *rebin82 = PWidth8->Rebin(4,"rebin1");

  TFile *dataFile9 = new TFile("pw35006455rt99.root");
  TH1D *PWidth9 = (TH1D*)dataFile9->Get("PWidth");
  TH1 *rebin9 = PWidth9->Rebin(2,"rebin");
  TH1 *rebin92 = PWidth9->Rebin(4,"rebin1");

  new TBrowser();
}

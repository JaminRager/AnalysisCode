{
  gROOT->ForceStyle();
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
    
  TFile *dataFile = new TFile("normCuts.root");
  TH2D *EHists = (TH2D*)dataFile->Get("EHists");
  TH2D *TPHists = (TH2D*)dataFile->Get("TPHists");
  EHists->GetYaxis()->SetRangeUser(2000,10000);
  EHists->GetXaxis()->SetRangeUser(18000,25000);
  TPHists->GetYaxis()->SetRangeUser(3000,6000);
  TPHists->GetXaxis()->SetRangeUser(3000,7000);
    
  TFile *dataFile1 = new TFile("wideNaI.root");
  TH2D *EHists1 = (TH2D*)dataFile1->Get("EHists");
  TH2D *TPHists1 = (TH2D*)dataFile1->Get("TPHists");
  EHists1->GetYaxis()->SetRangeUser(2000,10000);
  EHists1->GetXaxis()->SetRangeUser(18000,25000);
  TPHists1->GetYaxis()->SetRangeUser(3000,6000);
  TPHists1->GetXaxis()->SetRangeUser(3000,7000);
    
  TFile *dataFile2 = new TFile("wideBoth.root");
  TH2D *EHists2 = (TH2D*)dataFile2->Get("EHists");
  TH2D *TPHists2 = (TH2D*)dataFile2->Get("TPHists");
  EHists2->GetYaxis()->SetRangeUser(2000,10000);
  EHists2->GetXaxis()->SetRangeUser(18000,25000);
  TPHists2->GetYaxis()->SetRangeUser(3000,6000);
  TPHists2->GetXaxis()->SetRangeUser(3000,7000);
    
  TFile *dataFile3 = new TFile("noNaI.root");
  TH2D *EHists3 = (TH2D*)dataFile3->Get("EHists");
  TH2D *TPHists3 = (TH2D*)dataFile3->Get("TPHists");
  EHists3->GetYaxis()->SetRangeUser(2000,10000);
  EHists3->GetXaxis()->SetRangeUser(18000,25000);
  TPHists3->GetYaxis()->SetRangeUser(3000,6000);
  TPHists3->GetXaxis()->SetRangeUser(3000,7000);
    
  TFile *dataFile4 = new TFile("noCuts.root");
  TH2D *EHists4 = (TH2D*)dataFile4->Get("EHists");
  TH2D *TPHists4 = (TH2D*)dataFile4->Get("TPHists");
  EHists4->GetYaxis()->SetRangeUser(2000,10000);
  EHists4->GetXaxis()->SetRangeUser(18000,25000);
  TPHists4->GetYaxis()->SetRangeUser(3000,6000);
  TPHists4->GetXaxis()->SetRangeUser(3000,7000);

  TFile *dataFile5 = new TFile("centeredCuts.root");
  TH2D *EHists5 = (TH2D*)dataFile5->Get("EHists");
  TH2D *TPHists5 = (TH2D*)dataFile5->Get("TPHists");
  EHists5->GetYaxis()->SetRangeUser(2000,10000);
  EHists5->GetXaxis()->SetRangeUser(18000,25000);
  TPHists5->GetYaxis()->SetRangeUser(3000,6000);
  TPHists5->GetXaxis()->SetRangeUser(3000,7000);
}

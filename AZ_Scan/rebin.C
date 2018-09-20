{
  TFile *dataFile = new TFile("D2AZScanColzFull4.root");
  TH2D *DriftT = (TH2D*)dataFile->Get("DriftT");
  TH2 *rebin10y = DriftT->RebinY(10,"rebin10y");
    
}

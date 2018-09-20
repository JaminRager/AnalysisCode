{
  gStyle->SetOptStat(0);
    
  TFile *f = new TFile("DetectorToECalib_6.root");
  TH2F *h0 = (TH2F*)f->Get("htrapENFCalHG584");
  h0->SetOption("colz");
  h0->Write();
  f->Close();
}

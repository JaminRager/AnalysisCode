{
  gStyle->SetOptStat(0);
    
  //.x MJDTalkPlotStyle.C
    
  TFile *f1 = new TFile("CombinedDS0RebinOrig.root");
  TH1F *h1 = (TH1F*)f1->Get("natHE");
  TH1F *h2 = (TH1F*)f1->Get("enrHE");
    
    
  //TLegend *legend = new TLegend(0.1, 0.7, 0.48, 0.9);
  //legend->AddEntry(natHE, "natural", "f");
  //legend->AddEntry(enrHE, "enriched", "f");
    
  h1->Rebin(2);
  h2->Rebin(2);
  h1->Scale(5/(2*195.));
  h2->Scale(5/(2*478.));
  h1->SetLineColor(kBlue);
  h2->SetLineColor(kRed);
  h1->Draw("HIST");
  h2->Draw("HIST same");
}

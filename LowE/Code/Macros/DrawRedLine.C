{
  gStyle->SetOptStat(0);
  TFile *f = new TFile("/global/homes/j/jrager/LowE/AnalysisPlots/most_latest/Compton/ComptonEventsDS1.root");
  //TFile *f = new TFile("~/LowE/Data/CombinedEfficiencies/NormalizedEfficiencyDS1_6.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/Data/PassFailPlots/EfficiencyDS1chan582.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/Data/SumSpectra/SumSpectrumDS1.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/AnalysisPlots/most_latest/Compton/ComptonEventsDS1.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/AnalysisPlots/most_latest/DetSelection/DetSelectDS5b_5kThresh_correctedCuts.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/AnalysisPlots/latest/TETM1/DetectorTETM1D_1.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/AnalysisPlots/latest/TETM1/DetectorTETMvE_1.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/AnalysisPlots/latest/ToE1/TuneToECutDS1_chan664.root");
  //TFile *f = new TFile("/global/homes/j/jrager/LowE/Data/EnrToEDS1Ch664.root");
  //TFile *f = new TFile("~/LowE/AnalysisPlots/oldest/DetectorToECalib_1.root");
  //TFile *f = new TFile("~/LowE/AnalysisPlots/oldest/TuneWFCutsDS0.root");
  //TFile *f = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch582.root");
  //TFile *f = new TFile("~/LowE/Data/EffCorrectedSpectra/DS1ScaledSpectEnr_TGraph.root");
  //TFile *f = new TFile("~/LowE/Data/CombinedEfficiencies/ClopperErrorDS1Enr.root");
  //TH2F *h0 = (TH2F*)f->Get("htrapENFCalHG664");
  //TH2F *h0 = (TH2F*)f->Get("ToE");
  //TH2F *h0 = (TH2F*)f->Get("final");
  //TH2F *h0 = (TH2F*)f->Get("at20k");
  //TH2F *h0 = (TH2F*)f->Get("TETMvsE578");
  //TH2F *h0 = (TH2F*)f->Get("TETMvsE664");
  //TH2F *h0 = (TH2F*)f->Get("TETMHG578");
  //TH2F *h0 = (TH2F*)f->Get("TETMHG664");
  //TH2F *h0 = (TH2F*)f->Get("detVrun");
  //TH2F *h0 = (TH2F*)f->Get("Basic");
  //TH2F *h0 = (TH2F*)f->Get("Pass");
  //TH2F *h1 = (TH2F*)f->Get("Tot");
  TH1F *h0 = (TH1F*)f->Get("Basic");
  //h0->SetLineColor(kBlue);
  //h1->SetLineColor(kRed);
  //h0->SetMarkerStyle(21);
  //h1->SetMarkerStyle(21);
  //h0->SetMarkerColor(kBlue);
  //h1->SetMarkerColor(kRed);
  h0->Draw();
  //h0->Draw("colz");
  //h0->Draw("E1 X0");
  //h1->Draw("E1 X0 same");
  //Graph->SetLineColor(1);
  //Graph->SetMarkerColor(2);
  //Graph->SetMarkerStyle(21);
  //Graph->Draw("AP");
  TLine *line1 = new TLine(123.3, 0, 123.3, 600);
  line1->SetLineColor(kRed);
  line1->SetLineWidth(3);
  line1->Draw();
  //TLine *line1 = new TLine(237.3, 0, 237.3, 1600000);
  //line1->SetLineColor(kRed);
  //line1->SetLineWidth(3);
  //line1->Draw();
  //TLine *line2 = new TLine(239.6, 0, 239.6, 1600000);
  //line2->SetLineColor(kRed);
  //line2->SetLineWidth(3);
  //line2->Draw();
  //TLine *line1 = new TLine(0.4, 0, 0.4, 12000);
  //line1->SetLineColor(kRed);
  //line1->SetLineWidth(3);
  //line1->Draw();
  //TLine *line1 = new TLine(1.4, 0, 1.4, 120);
  //line1->SetLineColor(kRed);
  //line1->SetLineWidth(3);
  //line1->Draw();
  //TLine *line2 = new TLine(1.04, 0, 1.04, 120);
  //line2->SetLineColor(kRed);
  //line2->SetLineWidth(3);
  //line2->Draw();
  //TLine *line1 = new TLine(20, 0, 20, 2.5);
  //line1->SetLineColor(kRed);
  //line1->SetLineWidth(3);
  //line1->Draw();
  //TLine *line2 = new TLine(25, 0, 25, 2.5);
  //line2->SetLineColor(kRed);
  //line2->SetLineWidth(3);
  //line2->Draw();
  //TLine *line1 = new TLine(5, 1.1, 100, 1.1);
  //line1->SetLineColor(kRed);
  //line1->SetLineWidth(3);
  //line1->Draw();
  //TLine *line2 = new TLine(5, 2.1, 100, 2.1);
  //line2->SetLineColor(kRed);
  //line2->SetLineWidth(3);
  //line2->Draw();
  //h0->GetXaxis()->SetTitle("Energy (keV)");
  //TLine *line1 = new TLine(5, 0.74, 9, 0.74);
  //line1->SetLineColor(kRed);
  //line1->SetLineWidth(3);
  //line1->Draw();
  //TLine *line2 = new TLine(5, 1.76, 9, 1.76);
  //line2->SetLineColor(kRed);
  //line2->SetLineWidth(3);
  //line2->Draw();
  //TLine *line3 = new TLine(9, 0.93, 20, 0.93);
  //line3->SetLineColor(kRed);
  //line3->SetLineWidth(3);
  //line3->Draw();
  //TLine *line4 = new TLine(9, 1.53, 20, 1.53);
  //line4->SetLineColor(kRed);
  //line4->SetLineWidth(3);
  //line4->Draw();
  //TLine *line5 = new TLine(20, 1.04, 100, 1.04);
  //line5->SetLineColor(kRed);
  //line5->SetLineWidth(3);
  //line5->Draw();
  //TLine *line6 = new TLine(20, 1.4, 100, 1.4);
  //line6->SetLineColor(kRed);
  //line6->SetLineWidth(3);
  //line6->Draw();
}

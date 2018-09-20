{
    gStyle->SetOptStat(0);

    TFile *f1 = new TFile("EnrSpectDS0.root");
    TH1F *h1 = (TH1F*)f1->Get("WFCut");
    TFile *f2 = new TFile("UnscaledEnrSpectDS12345ab6.root");
    TH1F *h2 = (TH1F*)f2->Get("WFCut");

    TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry(WFCut,"DS0","f1");
    legend->AddEntry(WFCut,"DS12345b6","f2");

    //Double_t ExposureEnr = 4/2890.0;
    Double_t ExposureEnr = 4/4152.0;

    h1->Scale(1);
    h1->Draw("HIST");
    h1->SetLineColor(kBlack);
    h2->Scale(ExposureEnr);
    h2->Draw("HIST same");
    h2->SetLineColor(kBlue);
  
    TLine *line1 = new TLine(20, 0.038, 40, 0.038);
    line1->SetLineColor(kRed);
    line1->Draw();
    TLine *line2 = new TLine(20, 0.017, 40, 0.017);
    line2->SetLineColor(kRed);
    line2->Draw();

    //legend->Draw()
}

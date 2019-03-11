// This script demonstrates how to use TEfficiency to calculate Clopper-Pearson intervals
// See here: https://root.cern.ch/doc/master/classTEfficiency.html#ae80c3189bac22b7ad15f57a1476ef75b
void ClopperPearsonExample()
{
  TH1D *hFull = new TH1D("hFull", "Histogram before Cuts", 100, 0, 100);
  TH1D *hCut = new TH1D("hCut", "Histogram after Cuts", 100, 0, 100);
  TEfficiency *eff = new TEfficiency("eff","Efficiency", 100, 0, 100);

  // Loop through and fill histograms with dummy values
  for(int i = 0; i < hFull->GetNbinsX(); i++)
  {
    // Assume full histogram has 100 counts per bin
    // Randomly distribute the counts after the cut (between 0 and 100)
    hFull->SetBinContent(i, 100.);
    hCut->SetBinContent(i, gRandom->Rndm()*100.);
  }

  // Draw stuff
  TCanvas *c1 = new TCanvas("c1","c1",800,600);
  hFull->SetLineColor(kBlack);
  hCut->SetLineColor(kRed);
  hFull->Draw();
  hCut->Draw("SAME");

  // Dummy variables
  double deffHi = 0;
  double deffLo = 0;
  double dFull = 0;
  double dCut = 0;

  // Arrays for the efficiencies and intervals
  double x[100] = {};
  double xerr[100] = {};
  double effArr[100] = {};
  double effHi[100] = {};
  double effLo[100] = {};

  // Calculate the upper and lower for each bin
  for(int i = 0; i < hFull->GetNbinsX(); i++)
  {
    dFull = hFull->GetBinContent(i);
    dCut = hCut->GetBinContent(i);
    deffHi = eff->ClopperPearson(dFull, dCut, 0.9, true);
    deffLo = eff->ClopperPearson(dFull, dCut, 0.9, false);
    cout <<"Bin: " << i << " Full Counts: " << dFull << " Cut Counts: " << dCut << " Upper CL: " << deffHi << " Lower CL: " << deffLo << endl;

    x[i] = i;
    xerr[i] = 0;
    effArr[i] = dCut/dFull;
    // Here make sure the error bars are calculated properly
    effHi[i] = deffHi - dCut/dFull;
    effLo[i] = dCut/dFull - deffLo;
  }

  TGraphAsymmErrors *geff = new TGraphAsymmErrors(100, x, effArr, xerr, xerr, effLo, effHi);
  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  geff->SetMarkerStyle(21);
  geff->SetMarkerColor(kRed);
  geff->SetTitle("Efficiency with ClopperPearson intervals");
  geff->Draw("AP");

}

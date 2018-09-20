// This script demonstrates how to use TEfficiency to calculate Clopper-Pearson intervals
// See here: https://root.cern.ch/doc/master/classTEfficiency.html#ae80c3189bac22b7ad15f57a1476ef75b
void ClopperPearsonError()
{
  TFile *f1 = new TFile("/global/homes/j/jrager/LowE/EfficiencyDS3chan624_2k.root");
  TH1F *hFull= (TH1F*)f1->Get("Tot");
  TH1F *hCut = (TH1F*)f1->Get("Pass");
  TEfficiency *eff = new TEfficiency("eff","Efficiency", 50, 0, 100);

  //string outFile = "/global/u1/j/jrager/LowE/ClopperErrorDS2Ch592.root";

  //TFile *f2 = new TFile(outFile.c_str(),"RECREATE");
  //cout << "Creating outpout file" <<  endl;
  //f2->cd();

  //TCanvas *c1 = new TCanvas("c1","c1",800,600);
  //hFull->SetLineColor(kBlack);
  //hCut->SetLineColor(kRed);
  //hFull->Draw();
  //hCut->Draw("SAME");

  // Dummy variables
  double deffHi = 0;
  double deffLo = 0;
  double dFull = 0;
  double dCut = 0;

  // Arrays for the efficiencies and intervals
  double x[50] = {};
  double xerr[50] = {};
  double effArr[50] = {};
  double effHi[50] = {};
  double effLo[50] = {};

  // Calculate the upper and lower for each bin
  for(int i = 1; i < ((hFull->GetNbinsX())+1); i++)
  {
    dFull = hFull->GetBinContent(i);
    dCut = hCut->GetBinContent(i);
    deffHi = eff->ClopperPearson(dFull, dCut, 0.9, true);
    deffLo = eff->ClopperPearson(dFull, dCut, 0.9, false);
    cout <<"Bin: " << i << " Full Counts: " << dFull << " Cut Counts: " << dCut << " Upper CL: " << deffHi << " Lower CL: " << deffLo << endl;
    cout << "Bin center:" << hFull->GetBinCenter(i) << endl;

    x[i-1] = (i*2.0)-1.0;
    xerr[i-1] = 0;
    effArr[i-1] = dCut/dFull;
    // Here make sure the error bars are calculated properly
    effHi[i-1] = deffHi - dCut/dFull;
    effLo[i-1] = dCut/dFull - deffLo;
  }
  //f1->Close();

  TGraphAsymmErrors *geff = new TGraphAsymmErrors(50, x, effArr, xerr, xerr, effLo, effHi);
  TCanvas *c2 = new TCanvas("c2","c2",800,600);
  geff->SetMarkerStyle(21);
  geff->SetMarkerColor(kRed);
  geff->SetTitle("DS3 ch 624, 2keV binning");
  geff->GetXaxis()->SetTitle("trapENFCal (keV)");
  geff->GetYaxis()->SetTitle("efficiency");
  geff->Draw("AP");
  //geff->Write();
  //f2->Close();
}

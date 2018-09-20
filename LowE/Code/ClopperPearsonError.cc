// This script uses TEfficiency to calculate Clopper-Pearson intervals
// See here: https://root.cern.ch/doc/master/classTEfficiency.html#ae80c3189bac22b7ad15f57a1476ef75b

#include <stdio.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <stdlib.h>

#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"

#include "GATDataSet.hh"
#include <string>

#include <TROOT.h>
#include <TStyle.h>
#include "TColor.h"

int main()
{
  TFile *f1 = new TFile("/global/u1/j/jrager/LowE/ClopperErrorDS2Ch592.root");
  cout << "Creating outpout file" <<  endl;
  
  TFile *f2 = new TFile("/global/homes/j/jrager/LowE/Data/EfficiencyDS2chan592.root");
  TH1F *hFull= (TH1F*)f->Get("Tot");
  TH1F *hCut = (TH1F*)f->Get("Pass");
  TEfficiency *eff = new TEfficiency("eff","Efficiency", 25, 0, 100);
  f1.cd();
    
  // Dummy variables
  double deffHi = 0;
  double deffLo = 0;
  double dFull = 0;
  double dCut = 0;

  // Arrays for the efficiencies and intervals
  double x[25] = {};
  double xerr[25] = {};
  double effArr[25] = {};
  double effHi[25] = {};
  double effLo[25] = {};

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

  TGraphAsymmErrors *geff = new TGraphAsymmErrors(25, x, effArr, xerr, xerr, effLo, effHi);
  geff->SetMarkerStyle(21);
  geff->SetMarkerColor(kRed);
  geff->SetTitle("Efficiency with ClopperPearson intervals");
  //geff->Draw("AP");
  geff->Write();

  return 0;
}

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
#include "TEfficiency.h"

#include "GATDataSet.hh"
#include <string>

#include <TROOT.h>
#include <TStyle.h>
#include "TColor.h"

int main(int argc, char *argv[])
{ 
  std::cout << "Efficiency with Clopper-Pearson error bars." << std::endl;
  
  if(argc != 2) {
    std::cout << "Need 1 arguments to give detector channel!" << std::endl;
    std::cout << "Usage: ClopperPearsonError chan#" << std::endl;
    std::cout << "For example, detector channel 582." << std::endl;
    return 0;
  }

  // Data file
  std::string dataFile; 

  // Path to data file.  
  std::string dataPath("/global/homes/j/jrager/LowE/Data/PassFailPlots/");
  std::cout << "data path" << dataPath << std::endl;

  // File where output will be saved
  std::string outFile; 

  // Directory where file will be saved.  
  std::string savePath("/global/homes/j/jrager/LowE/Data/IndivEfficiencies/");
  std::cout << "save path" << savePath << std::endl;

  dataFile = dataPath + "EfficiencyDS4chan" + std::string(argv[1]) + ".root";
  std::cout << "data file" << dataFile << std::endl;
  TFile f1(dataFile.c_str());
  //TFile *f1 = new TFile("/global/homes/j/jrager/LowE/Data/EfficiencyDS1chan582.root");
  outFile = savePath + "ClopperErrorDS4Ch" + std::string(argv[1]) + ".root";
  std::cout << "output path" << outFile << std::endl;
  TFile f2(outFile.c_str(), "RECREATE");
  f2.cd();

  TH1F *hFull= (TH1F*)f1.Get("Tot");
  TH1F *hCut = (TH1F*)f1.Get("Pass");
  TEfficiency *eff = new TEfficiency("eff","Efficiency", 20, 0, 100);
    
  // Dummy variables
  double deffHi = 0;
  double deffLo = 0;
  double dFull = 0;
  double dCut = 0;

  // Arrays for the efficiencies and intervals
  double x[20] = {};
  double xerr[20] = {};
  double effArr[20] = {};
  double effHi[20] = {};
  double effLo[20] = {};

  // Calculate the upper and lower for each bin
  // It is important to start at i=1, and  stop at GetNbinsX()+1
  for(int i = 1; i < ((hFull->GetNbinsX())+1); i++)
  {
    dFull = hFull->GetBinContent(i);
    dCut = hCut->GetBinContent(i);
    deffHi = eff->ClopperPearson(dFull, dCut, 0.9, true);
    deffLo = eff->ClopperPearson(dFull, dCut, 0.9, false);
    std::cout <<"Bin: " << i << " Full Counts: " << dFull << " Cut Counts: " << dCut << " Upper CL: " << deffHi << " Lower CL: " << deffLo << std::endl;

    x[i-1] = (i*5.0)-5.0;
    xerr[i-1] = 0;
    effArr[i-1] = dCut/dFull;
    // Here make sure the error bars are calculated properly
    effHi[i-1] = deffHi - dCut/dFull;
    effLo[i-1] = dCut/dFull - deffLo;
  }

  TGraphAsymmErrors *geff = new TGraphAsymmErrors(20, x, effArr, xerr, xerr, effLo, effHi);
  //TCanvas *c2 = new TCanvas("c2","c2",800,600);
  geff->SetMarkerStyle(21);
  geff->SetMarkerColor(kRed);
  //geff->SetTitle("Efficiency with ClopperPearson intervals");
  geff->GetXaxis()->SetTitle("trapENFCal (keV)");
  geff->GetYaxis()->SetTitle("efficiency");
  //geff->Draw("AP");
  //geff->SetDrawOption("AP");
  geff->Write();
  f2.Close();

  return 0;
}

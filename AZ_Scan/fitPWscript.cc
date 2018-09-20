//
//  fitPWscript.cc
//
//
//  Created by Jamin on 3/28/17.
//
//  Fits the peaks in the 1D histograms created by PeakWidth.cc
//

#include <stdio.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <stdlib.h>

//#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
//#include "TH2.h"

//#include "GATDataSet.hh"
#include <string>

#include <TROOT.h>

int main()
{
  std::cout << "Generating drift-time histogram..." << std::endl;
    
  // Data file
  std::string dataFile;

  // Directory where data is found.
  std::string dataPath("/global/u1/j/jrager/AZ_Scan/CrudePeakFit/");

  UInt_t runNumb;
  for (runNumb = 1; runNumb < 25; runNumb++) {
        
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = dataPath + std::string("D2AZang") + buffer + ".root";
    std::cout<<"Opening file"<<dataFile<<std::endl;
    //TFile f2(dataFile.c_str());
    TFile *f2 = new TFile(dataFile.c_str());

    TH1D *PWidth = (TH1D*)f2->Get("PWidth");
    TH1 *rebin = PWidth->Rebin(4,"rebin");
    rebin->Fit("gaus","N");

  }

  return 0;

}

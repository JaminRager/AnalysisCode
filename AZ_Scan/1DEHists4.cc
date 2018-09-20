//
//  1DEHists.cpp
//
//
//  Created by Jamin on 9/12/16.
//
//  Makes 1D energy histograms for Ge and NaI detector.
//

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
#include "TH2.h"

#include "GATDataSet.hh"
#include <string>

#include <TROOT.h>
#include <TStyle.h>
#include "TColor.h"

int main()
{
  std::cout << "Generating drift-time histogram..." << std::endl;
    
  // Data file
  std::string dataFile;
    
  // File where histograms will be saved
  std::string outFileName;
    
  // Directory where file will be saved. Change this to your own directory.
  std::string savePath("");
    
  // Directory where data is found.
  std::string dataPath("/global/project/projectdirs/majorana/users/jrager/AzScan/data/");
    
  // "energy" is raw (offline computed) energy.
  TH1D *GeHist = new TH1D("GeHist", "GeHist", 2000, 0., 100000.);
  GeHist->GetXaxis()->SetTitle("energy");
  TH1D *NaIHist = new TH1D("NaIHist", "NaIHist", 200, 0., 10000.);
  NaIHist->GetXaxis()->SetTitle("energy");

    
  //Loop over data files
  UInt_t runNumb;
  for (runNumb = 146; runNumb < 194; runNumb+=2) {
    std::cout << "Processing run # "  << runNumb-1 << std::endl;
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = dataPath + std::string("angle") + buffer + ".root";
    std::cout<<"Opening file"<<dataFile<<std::endl;
    TFile f2(dataFile.c_str());
    TChain *chain = new TChain("mjdTree");
    chain->Add(dataFile.c_str());
    //Crate output file
    outFileName = savePath + "D2EHists" + buffer + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    TFile f1(outFileName.c_str(), "RECREATE");
    f1.cd();
        
    // Identify and assign memory to TTree variables of interest.
    std::vector<Double_t> *channel = 0;
    chain->SetBranchAddress("channel", &channel);
    std::vector<Double_t> *energy = 0;
    chain->SetBranchAddress("energy", &energy);
    std::cout << "Finished Assigning Variables for TTree output." << std::endl;
        
    // Event loop!
    // Ge is channel 160, NaI is 166.
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
            
      if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum << std::endl;
      chain->GetEvent(eventNum);
            
      if((*channel)[0]==160){
	GeHist->Fill((*energy)[0]);
	NaIHist->Fill((*energy)[1]);
      }
            
      else if((*channel)[0]==166){
	GeHist->Fill((*energy)[1]);
	NaIHist->Fill((*energy)[0]);
      }
            
    } // for event loop
    // Write output to file
    GeHist->Write();
    NaIHist->Write();
    std::cout << "Done writing, closing file." << std::endl;
    f1.Close();
    f2.Close();
    std::cout << "Finished Event Loop." << std::endl;
  }
  std::cout << "Finished run loop." << std::endl;
    
  std::cout << "Done!" << std::endl;
    
  return 0;
}

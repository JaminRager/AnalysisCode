//
//  NoMiddleMan.cpp
//  
//
//  Created by Jamin on 6/8/16.
//
//  Makes 2D histograms of drift time vs. z (or theta)
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

void set_plot_style()
{
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
}

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
  std::string dataPath("/global/projecta/projectdirs/majorana/users/jrager/AzScan/data/");
    
  // Load the set of run files given in command line.
  outFileName = savePath + "D2AZWideNaI4.root";
  std::cout << "Output will be written to file " << outFileName << std::endl;
  TFile f1(outFileName.c_str(), "RECREATE");
  f1.cd();
    
  // Ge is channel 160, NaI is 166.
  // "energy" is raw (offline computed) energy.
  TH2D *DriftT = new TH2D("DriftT", "DriftT", 97, 0, 194, 1200, 0., 1200. );
  DriftT->GetYaxis()->SetTitle("drift-time (ns)");
  DriftT->GetXaxis()->SetTitle("angle (deg)");
    
  //Loop over files
  UInt_t runNumb;
  for (runNumb = 146; runNumb < 194; runNumb+=2) {
    std::cout << "Processing run # "  << runNumb << std::endl;
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = dataPath + std::string("angle") + buffer + ".root";
    std::cout<<"Opening file"<<dataFile<<std::endl;
    TFile f2(dataFile.c_str());
    TChain *chain = new TChain("mjdTree");
    chain->Add(dataFile.c_str());
    f1.cd();

    // Identify and assign memory to TTree variables of interest.
    std::vector<Double_t> *channel = 0;
    chain->SetBranchAddress("channel", &channel);
    std::vector<Double_t> *energy = 0;
    chain->SetBranchAddress("energy", &energy);
    std::vector<Double_t> *blrwfFSR50 = 0;
    chain->SetBranchAddress("blrwfFSR50", &blrwfFSR50);
    std::vector<Double_t> *negblrmFSR50 = 0;
    chain->SetBranchAddress("negblrmFSR50", &negblrmFSR50);
    std::cout << "Finished Assigning Variables for TTree output." << std::endl;
        
    // Create drift time variable "dt"
    Double_t dt = 0;
        
        
    
    // Event loop!
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        
      if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;
      chain->GetEvent(eventNum);
        
      if((*channel)[0]==160 && (*energy)[0]>20900 && (*energy)[0]<21500 && (*energy)[1]>=3000 && (*energy)[1]<=8000){
	dt = (*blrwfFSR50)[0] - (*negblrmFSR50)[1];
	DriftT->Fill(runNumb, dt);
      }
        
      else if((*channel)[0]==166 && (*energy)[1]>20900 && (*energy)[1]<21500 && (*energy)[0]>=3000 && (*energy)[0]<=8000){
	dt = (*blrwfFSR50)[1] - (*negblrmFSR50)[0];
	DriftT->Fill(runNumb, dt);
      }
        
      //DriftT->Fill(dt);
        
    } // for event loop
    f2.Close();
    std::cout << "Finished Event Loop." << std::endl;
  }
  std::cout << "Finished run loop." << std::endl;
  // Write output to file
  DriftT->SetOption("colz");
  DriftT->Write();
  std::cout << "Done writing, closing file." << std::endl;
  f1.Close();
    
  std::cout << "Done!" << std::endl;
    
  return 0;
}

//
//  2DHistsCutsAzimuthal.cpp
//
//  2D hist of E_Ge vs E_NaI.
//
//  Created by Jamin on 9/7/16.
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
  std::string dataPath("/global/project/projectdirs/majorana/users/jrager/AzScan/data/");
    
  // Load the set of run files given in command line.
  outFileName = savePath + "D2AZScan2DHistsCuts1.root";
  std::cout << "Output will be written to file " << outFileName << std::endl;
  TFile f1(outFileName.c_str(), "RECREATE");
  f1.cd();
    
  // Create histograms.
  TH2D *EHists = new TH2D("EHists", "OfflineEnergy", 1480, 0., 74000, 240, 0., 12000.);
  EHists->GetXaxis()->SetTitle("Ge energy");
  EHists->GetYaxis()->SetTitle("NaI energy");
  TH2D *TPHists = new TH2D("TPHists", "TimePoints", 200, 0., 10000, 200, 0., 10000.);
  TPHists->GetXaxis()->SetTitle("Ge tp (ns)");
  TPHists->GetYaxis()->SetTitle("NaI tp (ns)");
    
  //Loop over files
  UInt_t runNumb;
  for (runNumb = 0; runNumb < 48; runNumb+=2) {
    std::cout << "Processing run # "  << runNumb-1 << std::endl;
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
    std::vector<Double_t> *negblrmFSR99 = 0;
    chain->SetBranchAddress("negblrmFSR99", &negblrmFSR99);
    std::cout << "Finished Assigning Variables for TTree output." << std::endl;
            
    // Event loop!
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
            
      if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;
      chain->GetEvent(eventNum);
            
      if((*channel)[0]==160 && (*energy)[0]>21100 && (*energy)[0]<21750 && (*energy)[1]>=4700 && (*energy)[1]<=5900){
	EHists->Fill((*energy)[0],(*energy)[1]);
	TPHists->Fill((*blrwfFSR50)[0],(*negblrmFSR99)[1]);
      }
            
      else if((*channel)[0]==166 && (*energy)[1]>21100 && (*energy)[1]<21750 && (*energy)[0]>=4700 && (*energy)[0]<=5900){
	EHists->Fill((*energy)[1],(*energy)[0]);
	TPHists->Fill((*blrwfFSR50)[1],(*negblrmFSR99)[0]);
      }
                        
    } // for event loop
    f2.Close();
    std::cout << "Finished Event Loop." << std::endl;
  }
  std::cout << "Finished run loop." << std::endl;
  // Write output to file
  EHists->SetOption("colz");
  TPHists->SetOption("colz");
  EHists->Write();
  TPHists->Write();
  std::cout << "Done writing, closing file." << std::endl;
  f1.Close();
    
  std::cout << "Done!" << std::endl;
    
  return 0;
}

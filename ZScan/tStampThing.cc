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
#include "Rtypes.h"

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
  std::string dataPath("/global/project/projectdirs/majorana/users/cmoshaug/surfst/data/built/P3JHY/");
    
  // Load the set of run files given in command line.
  outFileName = savePath + "TStampThing1.root";
  std::cout << "Output will be written to file " << outFileName << std::endl;
  TFile f1(outFileName.c_str(), "RECREATE");
  f1.cd();
    
  // Ge is channel 162, NaI is 166.
  // "energy" is raw (offline computed) energy.
  TH2D *GeTP = new TH2D("GeTP", "GeTP", 19, 0, 38, 100, 8460000000000., 8520000000000. );
  GeTP->GetYaxis()->SetTitle("time (time units)");
  GeTP->GetXaxis()->SetTitle("z (mm)");
  TH2D *NaITP = new TH2D("NaITP", "NaITP", 19, 0, 38, 100, 8460000000000., 8520000000000. );
  NaITP->GetYaxis()->SetTitle("time (time units)");
  NaITP->GetXaxis()->SetTitle("z (mm)");
  //TH2D *Offset = new TH2D("Offset", "Offset", 19, 0, 38, 24, 0., 1200. );
  //Offset->GetYaxis()->SetTitle("time (time units)");
  //Offset->GetXaxis()->SetTitle("z (mm)");
    
  //Loop over files
  UInt_t runNumb;
  UInt_t z = 0;
  for (runNumb = 35006441; runNumb < 35006442; runNumb++, z+=2) {
    std::cout << "Processing run # "  << runNumb-1 << std::endl;
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = dataPath + std::string("OR_run") + buffer + ".root";
    std::cout<<"Opening file"<<dataFile<<std::endl;
    TFile f2(dataFile.c_str());
    TChain *chain = new TChain("MGTree");
    chain->Add(dataFile.c_str());
    f1.cd();

    // Identify and assign memory to TTree variables of interest.
    ULong_t *tsa[2] = { 0 };
    chain->SetBranchAddress("fDigitizerData.fTimeStamp", &tsa);
    UInt_t *fID[2] = { 0 };
    chain->SetBranchAddress("fDigitizerData.fID", &fID);
    
    std::cout << "Finished Assigning Variables for TTree output." << std::endl;
        
    // Create drift time variable "dt"
    Double_t dt = 0;
        
        
    
    // Event loop!
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        
      if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;
      chain->GetEvent(eventNum);
        
      if((*fID)[0]==160){
	dt = (*tsa)[0] - (*tsa)[1];
	GeTP->Fill(z, (*tsa)[0]);
	NaITP->Fill(z,(*tsa)[1]);
	//Offset->Fill(z, dt);
      }
        
      else if((*fID)[0]==166){
	dt = (*tsa)[1] - (*tsa)[0];
	GeTP->Fill(z, (*tsa)[1]);
        NaITP->Fill(z,(*tsa)[0]);
	//Offset->Fill(z, dt);
      }
        
      //DriftT->Fill(dt);
        
    } // for event loop
    f2.Close();
    std::cout << "Finished Event Loop." << std::endl;
  }
  std::cout << "Finished run loop." << std::endl;
  // Write output to file
  GeTP->SetOption("colz");
  NaITP->SetOption("colz");
  //Offset->SetOption("colz");
  GeTP->Write();
  NaITP->Write();
  //Offset->Write();
  std::cout << "Done writing, closing file." << std::endl;
  f1.Close();
    
  std::cout << "Done!" << std::endl;
    
  return 0;
}

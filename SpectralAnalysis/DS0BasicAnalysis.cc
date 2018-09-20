//
// Simple analysis that generates and energy spectrum for a single
// detector (P1D1) in a range of data. 
//
// Based upon script by R. Henning, 10/15/15
//
// Modifies Reyco's script to build spectra for multiple (all good) detectors at once for a given run range.

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

int main(int argc, char *argv[])
{
  std::cout << "Energy spectrum for M1 good detectors." << std::endl;

  // Find datasets.
  if(argc != 3) {
    std::cout << "Need 2 arguments to give range of runs!" << std::endl;
    std::cout << "Usage: BasicAnalysis Run#1 Run#2" << std::endl;
    std::cout << "For example, runs 6906 and 6907 are calibration runs." << std::endl;
    return 0;
  }

  // File where histograms will be saved
  std::string outFileName; 

  // Directory where file will be saved. Change this to your own directory.  
  std::string savePath("");

  // Load the set of run files given in command line. 
  GATDataSet dataSet(atoi(argv[1]),atoi(argv[2]));
  TChain *chain = dataSet.GetChains();
  std::cout << "Processing runs " << argv[1] << " to " << argv[2] <<std::endl;
  outFileName = savePath + "spectrum" + std::string(argv[1]) + "_" + std::string(argv[2]) + ".root";
  std::cout << "Output will be written to file " << outFileName << std::endl;
  TFile f1(outFileName.c_str(), "RECREATE");
  f1.cd();
		     
  // Identify and assign memory to TTree variables of interest. 
  std::vector<Double_t> *trapECal = 0;
  chain->SetBranchAddress("trapECal", &trapECal);
  std::vector<Double_t> *channel = 0;
  chain->SetBranchAddress("channel", &channel);
  std::cout << "Finished Assigning Variables for TTree output." << std::endl;

  // trapECal is in offline computed energy from a trap filter that has been calibrated. 
  TH1D *htrapECalP1D1 = new TH1D("trapECalM1", "htrapECalM1", 10, 660., 670.);

  // Event loop!
  UInt_t nHit;
  for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){

    if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;   
    chain->GetEvent(eventNum);

    for(nHit = 0; nHit < (*channel).size(); nHit++) 
	if((*channel)[nHit] == 692) 
	  htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 690)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 688)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 640)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    //else if((*channel)[nHit] == 674)
    //htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 576)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 610)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 608)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 598)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 600)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 594)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 592)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 664)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 662)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 656)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 696)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 626)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 624)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 646)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 644)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
    else if((*channel)[nHit] == 642)
        htrapECalP1D1->Fill((*trapECal)[nHit]);
  } // for event loop
  std::cout << "Finished Event Loop." << std::endl;

  // Write output to file
  htrapECalP1D1->Write();
  std::cout << "Done writing, closing file." << std::endl;
  f1.Close();

  std::cout << "Done!" << std::endl;

  return 0;
}

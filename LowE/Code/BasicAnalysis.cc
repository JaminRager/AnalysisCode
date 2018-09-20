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
#include "TGraph.h"

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
  outFileName = savePath + "BaselineRMS" + std::string(argv[1]) + "_" + std::string(argv[2]) + ".root";
  std::cout << "Output will be written to file " << outFileName << std::endl;
  TFile f1(outFileName.c_str(), "RECREATE");
  f1.cd();
		     
  // Identify and assign memory to TTree variables of interest. 
  std::vector<Double_t> *RawWFblSlope = 0;
  chain->SetBranchAddress("RawWFblSlope", &RawWFblSlope);
  std::vector<Double_t> *channel = 0;
  chain->SetBranchAddress("channel",&channel);
  Int_t run;
  chain->SetBranchAddress("run", &run);
  std::cout << "Finished Assigning Variables for TTree output." << std::endl;
  UInt_t eventNum;      // event iterator
  UInt_t nHit;          // hit iterator
  Double_t sum1 = 0;    // sum of squares for hits within an event
  Double_t sum2 = 0;    // sum of squares for 
  Double_t square = 0;  // squares
  UInt_t counter1 = 0;  // counts hits looped through in the event
  UInt_t counter2 = 0;  // counts total number of hits for selected channel
  Double_t RMS = 0;     // root mean square
  UInt_t nRuns;

  // Event loop
  for(eventNum = 1; eventNum < chain->GetEntries(); eventNum++){   
    chain->GetEvent(eventNum);

    // Hit loop
    for(nHit = 0; nHit < (*channel).size(); nHit++){
      if((*channel)[nHit] == 662){
	square = (*RawWFblSlope)[nHit] * (*RawWFblSlope)[nHit];
	sum1 = sum1 + square;
	counter1 = counter1 + 1;
	
      }
    }

    counter2 = counter2 + counter1;
    sum2 = sum2 + sum1;

  }

  std::cout << "Finished Event Loop." << std::endl;

  RMS = sqrt(sum2/counter2);
  std::cout << "RMS" << RMS <<std::endl;

  //nRuns = atoi(argv[2]) - atoi(argv[1]);
  //TGraph *gr = new TGraph(run,RMS);
  //gr->Write();

  // Write output to file.
  std::cout << "Done writing, closing file." << std::endl;
  f1.Close();

  std::cout << "Done!" << std::endl;

  return 0;
}

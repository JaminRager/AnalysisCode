//
// Simple analysis that generates and energy spectrum for a single
// detector (P1D1) in a range of data. 
//
// Based upon script by R. Henning, 10/15/15
//
// Tries to use skim files

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
  if(argc != 2) {
    std::cout << "Need 1 arguments to give range of runs!" << std::endl;
    return 0;
  }

  // Path to skim files
  std::string dataPath("/global/u1/j/jrager/SpectralAnalysis/Official/spectra/DS1/skim/");

  // Skim file
  std::string skimfile;

  // File where histograms will be saved
  std::string outFileName; 

  // Directory where file will be saved. Change this to your own directory.  
  std::string savePath("");

  // Load the set of run files given in command line. 
  skimfile = dataPath + std::string("skimP3KJR_") + std::string(argv[1]) + ".root";
  TChain *chain = new TChain("skimTree");
  chain->Add(skimfile.c_str());
  //chain->AddFile("mjd_run35005568.root");
  std::cout << "Processing file " + skimfile << std::endl;
  outFileName = savePath + "EHist" + std::string(argv[1]) + ".root";
  std::cout << "Output will be written to file " << outFileName << std::endl;
  TFile f1(outFileName.c_str(), "RECREATE");
  f1.cd();
		     
  // Identify and assign memory to TTree variables of interest. 
  std::vector<Double_t> *trapENFCal = 0;
  chain->SetBranchAddress("trapENFCal", &trapENFCal);
  std::vector<Double_t> *channel = 0;
  chain->SetBranchAddress("channel", &channel);
  //std::vector<Double_t> *isLNFill = 0;
  //chain->SetBranchAddress("isLNFill", &isLNFill);
  //std::vector<Double_t> *muVeto1ms = 0;
  //chain->SetBranchAddress("muVeto1ms", &muVeto1ms);
  //std::vector<Double_t> *wfDCBits = 0;
  //chain->SetBranchAddress("wfDCBits", &wfDCBits);
  //std::vector<Double_t> *isGood = 0;
  //chain->SetBranchAddress("isGood", &isGood);
  std::vector<Double_t> *aenorm = 0;
  chain->SetBranchAddress("aenorm", &aenorm);
  std::vector<Double_t> *gain = 0;
  chain->SetBranchAddress("gain", &gain);
  std::vector<Double_t> *mH = 0;
  chain->SetBranchAddress("mH", &mH);
  std::vector<Double_t> *dcrSlope99 = 0;
  chain->SetBranchAddress("dcrSlope99", &dcrSlope99);

  std::cout << "Finished Assigning Variables for TTree output." << std::endl;

  // trapECal is in offline computed energy from a trap filter that has been calibrated. 
  TH1D *htrapENFCal = new TH1D("trapENFCalM1", "htrapENFCalM1", 40, 642., 682.);

  // Event loop!
  UInt_t nHit;
  for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){

    if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;   
    chain->GetEvent(eventNum);

    for(nHit = 0; nHit < (*channel).size(); nHit++){
      if ((*aenorm)[nHit]>1 && (*gain)[nHit]==0 && (*mH)[nHit]<2 && (*dcrSlope99)[nHit]<0){
        htrapENFCal->Fill((*trapENFCal)[nHit]);
      }
    }
  } // for event loop
  std::cout << "Finished Event Loop." << std::endl;

  // Write output to file
  htrapENFCal->Write();
  std::cout << "Done writing, closing file." << std::endl;
  f1.Close();

  std::cout << "Done!" << std::endl;

  return 0;
}

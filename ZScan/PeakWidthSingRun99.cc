//
// Creates 1D peak width histogram for Z-Scans, for single run.
//
//
// J. Rager
// 03/21/17
//

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

int main(int argc, char *argv[])
{
    std::cout << "Generating drift-time histogram..." << std::endl;

    // Find datasets.
  if(argc != 2) {
    std::cout << "Need 1 argument to give run number!" << std::endl;
    std::cout << "Usage: BasicAnalysis Run#" << std::endl;
    return 0;
  }
    
    // Data file
    std::string dataFileName;

    // File where histograms will be saved
    std::string outFileName;
    
    // Directory where file will be saved. Change this to your own directory.
    std::string savePath("");

    // Directory where data is found.
    std::string dataPath("/global/projecta/projectdirs/majorana/users/cmoshaug/surfst/data/gatified/P3JHY/");
    
    // Load the set of run files given in command line.
    dataFileName = dataPath + std::string("mjd_run") + std::string(argv[1]) + ".root";
    TChain *chain = new TChain("mjdTree");
    chain->Add(dataFileName.c_str());
    //chain->AddFile("mjd_run35005568.root");
    std::cout << "Processing file " + dataFileName << std::endl;
    std::cout << "Processing run " << argv[1] <<std::endl;
    outFileName = savePath + "pw" + std::string(argv[1]) + "rt99" + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    TFile f1(outFileName.c_str(), "RECREATE");
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
    
    // Create drift time variable "dt"
    Double_t dt = 0;
    
    // Ge is channel 160, NaI is 166.
    TH1D *PWidth = new TH1D("PWidth", "PWidth", 70, 300., 1000.);
    PWidth->GetXaxis()->SetTitle("drift-time (ns)");
    
    // Event loop!
    // UInt_t nHit;
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        
        if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;
        chain->GetEvent(eventNum);
        
        if((*channel)[0]==160 && (*energy)[0]>20900 && (*energy)[0]<21500 && (*energy)[1]>=4000 && (*energy)[1]<=7000){
	    dt = (*blrwfFSR50)[0] - (*negblrmFSR99)[1];
	    PWidth->Fill(dt);
        }
        
        else if((*channel)[0]==166 && (*energy)[1]>20900 && (*energy)[1]<21500 && (*energy)[0]>=4000 && (*energy)[0]<=7000){
	    dt = (*blrwfFSR50)[1] - (*negblrmFSR99)[0];
	    PWidth->Fill(dt);
        }
        
    } // for event loop
    std::cout << "Finished Event Loop." << std::endl;
    
    // Write output to file
    PWidth->Write();
    std::cout << "Done writing, closing file." << std::endl;
    f1.Close();
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}

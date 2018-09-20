//
// Calculates drift times.  Accepts run number as from standard input.
//
//
// J. Rager
// 03/05/16
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
    std::string dataPath("/global/project/projectdirs/majorana/users/cmoshaug/surfst/data/gatified/P3JHY/");
    
    // Load the set of run files given in command line.
    dataFileName = dataPath + std::string("mjd_run") + std::string(argv[1]) + ".root";
    TChain *chain = new TChain("mjdTree");
    chain->Add(dataFileName.c_str());
    //chain->AddFile("mjd_run35005568.root");
    std::cout << "Processing file " + dataFileName << std::endl;
    std::cout << "Processing run " << argv[1] <<std::endl;
    outFileName = savePath + "2DhistsCuts" + std::string(argv[1]) + ".root";
    //outFileName = savePath + "2Dhists" + ".root";
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
    
    // Create histograms.
    TH2D *EHists = new TH2D("EHists", "OfflineEnergy", 1480, 0., 74000, 240, 0., 12000.);
    EHists->GetXaxis()->SetTitle("Ge energy");
    EHists->GetYaxis()->SetTitle("NaI energy");
    TH2D *TPHists = new TH2D("TPHists", "TimePoints", 200, 0., 10000, 200, 0., 10000.);
    TPHists->GetXaxis()->SetTitle("Ge tp");
    TPHists->GetYaxis()->SetTitle("NaI tp");

    // Event loop!
    // UInt_t nHit;
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        
        if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;
        chain->GetEvent(eventNum);
        
        if((*channel)[0]==160 && (*energy)[0]>20900 && (*energy)[0]<21500 && (*energy)[1]>=4000 && (*energy)[1]<=7000){
	    EHists->Fill((*energy)[0],(*energy)[1]);
	    TPHists->Fill((*blrwfFSR50)[0],(*negblrmFSR99)[1]);
        }
        
        else if((*channel)[0]==166 && (*energy)[1]>20900 && (*energy)[1]<21500 && (*energy)[0]>=4000 && (*energy)[0]<=7000){
	    EHists->Fill((*energy)[1],(*energy)[0]);
            TPHists->Fill((*blrwfFSR50)[1],(*negblrmFSR99)[0]);
        }
        
    } // for event loop
    std::cout << "Finished Event Loop." << std::endl;
    
    // Write output to file
    EHists->Write();
    TPHists->Write();
    std::cout << "Done writing, closing file." << std::endl;
    f1.Close();
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}

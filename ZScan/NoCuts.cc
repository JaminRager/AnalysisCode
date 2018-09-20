//
// NoCuts.cc
//
// Just like BasicAnalysis.cc except without cuts.
//
//
// J. Rager
// 05/11/16
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
    outFileName = savePath + "dt" + std::string(argv[1]) + ".root";
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
    
    // Ge is channel 162, NaI is 166.
    // "energy" is raw (offline computed) energy.
    TH1D *GeHist = new TH1D("GeHist", "GeHist", 20000, 0., 1000000.);
    GeHist->GetXaxis()->SetTitle("energy");
    TH1D *NaIHist = new TH1D("NaIHist", "NaIHist", 20000, 0., 1000000.);
    NaIHist->GetXaxis()->SetTitle("energy");
    TH1D *GeTP = new TH1D("GeTP", "GeTP", 20000, 0., 1000000.);
    GeTP->GetXaxis()->SetTitle("time (10's of ns)");
    TH1D *NaITP = new TH1D("NaITP", "NaITP", 20000, 0., 1000000.);
    NaITP->GetXaxis()->SetTitle("time (10's of ns)");
    TH1D *DriftT = new TH1D("DriftT", "DriftT", 20000, 0., 1000000.);
    DriftT->GetXaxis()->SetTitle("time (10's of ns)");
    
    // Event loop!
    // UInt_t nHit;
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        
        if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;
        chain->GetEvent(eventNum);
        
        if((*channel)[0]==162){
            GeHist->Fill((*energy)[0]);
            NaIHist->Fill((*energy)[1]);
            GeTP->Fill((*blrwfFSR50)[0]);
            NaITP->Fill((*negblrmFSR99)[1]);
            dt = (*blrwfFSR50)[0] - (*negblrmFSR99)[1];
	    DriftT->Fill(dt);
        }
        
        else if((*channel)[0]==166){
            GeHist->Fill((*energy)[1]);
            NaIHist->Fill((*energy)[0]);
            GeTP->Fill((*blrwfFSR50)[1]);
            NaITP->Fill((*negblrmFSR99)[0]);
            dt = (*blrwfFSR50)[1] - (*negblrmFSR99)[0];
	    DriftT->Fill(dt);
        }
        
        //DriftT->Fill(dt);
        
    } // for event loop
    std::cout << "Finished Event Loop." << std::endl;
    
    // Write output to file
    GeHist->Write();
    NaIHist->Write();
    GeTP->Write();
    NaITP->Write();
    DriftT->Write();
    std::cout << "Done writing, closing file." << std::endl;
    f1.Close();
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}

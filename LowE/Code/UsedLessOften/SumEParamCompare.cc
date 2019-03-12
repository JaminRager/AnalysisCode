//
//  DetectorToE.cpp
//  
//
//  Created by Jamin on 7/31/17.
//
//
//#include "TROOT.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TEntryList.h"
#include "TLine.h"

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

#include "GATDataSet.hh"
#include "DataSetInfo.hh"

using namespace std;

int main()
{
    UInt_t runNumb;
    std::string dataFile;

    std::string DSets = "3";
    std::stringstream ss;  // General use stream for string to number conversion.
    std::string outFileName;
    std::cout << "std::string things initialized." << std::endl;
    

    TChain *chain = new TChain("skimTree");
    if(DSets.find("0") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
	std::cout << "Added skimfiles and detectors for DS-0" << std::endl;
    }

    if(DSets.find("1") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS1*.root");
	std::cout << "Added skimfiles and detectors for DS-1" << std::endl;
    }

    if(DSets.find("2") != std::string::npos) {
	chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
	std::cout << "Added skimfiles and detectors for DS-2" << std::endl;
    }

    if(DSets.find("3") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS3*.root");
	std::cout << "Added skimfiles and detectors for DS-3" << std::endl;
    }

    if(DSets.find("4") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
	std::cout << "Added skimfiles and detectors for DS-4" << std::endl;
    }

    if(DSets.find("5") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
	std::cout << "Added skimfiles and detectors for DS-5a" << std::endl;
    }

    if(DSets.find("6") != std::string::npos) {
	chain->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
        std::cout << "Added skimfiles and detectors for DS-6" << std::endl;
    }
    
    // Output File. Added dataset name to file name.
    outFileName = "/global/homes/j/jrager/LowE/ManualOverSumEVRun" + DSets + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    std::cout << "Output file initialized." << std::endl;

    // Identify and assign memory to TTree variables of interest.
    Double_t sumEH;
    chain->SetBranchAddress("sumEH", &sumEH);
    std::vector<int> *C = 0;
    chain->SetBranchAddress("C", &C);
    std::vector<int> *P = 0;
    chain->SetBranchAddress("P", &P);
    std::vector<int> *D = 0;
    chain->SetBranchAddress("D", &D);
    std::vector<Double_t> *trapENFCal = 0;
    chain->SetBranchAddress("trapENFCal", &trapENFCal);
    std::vector<int> *gain = 0;
    chain->SetBranchAddress("gain", &gain);
    std::vector<bool> *isGood = 0;
    chain->SetBranchAddress("isGood", &isGood);
    bool isLNFill1;
    chain->SetBranchAddress("isLNFill1", &isLNFill1);
    bool isLNFill2;
    chain->SetBranchAddress("isLNFill2", &isLNFill2);
    std::vector<Double_t> *kvorrT = 0;
    chain->SetBranchAddress("kvorrT", &kvorrT);
    std::vector<Double_t> *trapETailMin = 0;
    chain->SetBranchAddress("trapETailMin", &trapETailMin);
    bool muVeto;
    chain->SetBranchAddress("muVeto", &muVeto);
    Int_t mH;
    chain->SetBranchAddress("mH", &mH);
    Int_t iEvent;
    chain->SetBranchAddress("iEvent", &iEvent);
    Int_t run;
    chain->SetBranchAddress("run", &run);
    std::cout << "Set branchaddresses." << std::endl;
    
    // Create histograms.
    TH2D *EHist = new TH2D("EHist", "EHist", 2557, 16031., 18588., 3000, 0., 3000.);
    EHist->GetXaxis()->SetTitle("run number");
    EHist->GetYaxis()->SetTitle("(trapENFCal[0] + trapENFCal[1])/sumEH");

    // Cut for DS5 & earlier
    // (*gain)[nhit] == 0 && (*isGood)[nhit] && mH==1 && (*P)[nhit] != 0 && (*D)[nhit] != 0 && !muVeto && !isLNFill1 && !isLNFill2)

    // Event loop!
    std::cout << chain->GetEntries() << " events to be processed" << std::endl;
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        chain->GetEvent(eventNum);

	if(mH==2) 
	{
	  EHist->Fill(run,((*trapENFCal)[0] + (*trapENFCal)[1])/sumEH);
        }                    
    }
    std::cout << "End event loop." << std::endl;
    
    TFile f1(outFileName.c_str(), "RECREATE");
    f1.cd();
    std::cout << "cd to output file." << std::endl;

    EHist->SetOption("colz");
    EHist->Write();

    std::cout << "Write to output file." << std::endl;

    f1.Close();
    std::cout << "Output file closed." << std::endl;
    
    return 0;
    
}

//
// DataCleaningDS6.cc
//
// Makes data cleaning/monitoring plots for gatified DS6 data over a user-specified run range.
//
// 6/10/17
//
// Starting run is 25672.  End run as of 6/10/17 is 26677.

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
    std::unordered_set<int> detectorChannels;
    std::unordered_set<int>::iterator detectorChannelsIt;
    
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
    //Enriched detectors
    detectorChannels.insert(678); // DS-6 has Module 1 & 2 detectors
    detectorChannels.insert(674);
    detectorChannels.insert(672);
    detectorChannels.insert(632);
    detectorChannels.insert(630);
    detectorChannels.insert(626);
    detectorChannels.insert(690);
    detectorChannels.insert(648);
    detectorChannels.insert(640);
    detectorChannels.insert(642);
    detectorChannels.insert(664);
    detectorChannels.insert(662);
    detectorChannels.insert(660);
    detectorChannels.insert(658);
    detectorChannels.insert(610);
    detectorChannels.insert(608);
    detectorChannels.insert(584);
    detectorChannels.insert(598);
    detectorChannels.insert(592);
    detectorChannels.insert(696);
    detectorChannels.insert(1204);
    detectorChannels.insert(1110);
    detectorChannels.insert(1126);
    detectorChannels.insert(1202);
    detectorChannels.insert(1172);
    detectorChannels.insert(1176);
    detectorChannels.insert(1236);
    detectorChannels.insert(1238);
    detectorChannels.insert(1234);
    detectorChannels.insert(1328);
    detectorChannels.insert(1298);
    detectorChannels.insert(1296);
    detectorChannels.insert(1302);
    detectorChannels.insert(1332);
    detectorChannels.insert(1304);
    
    //Natural detectors
    detectorChannels.insert(680);
    detectorChannels.insert(692);
    detectorChannels.insert(616);
    detectorChannels.insert(600);
    detectorChannels.insert(624);
    detectorChannels.insert(628);
    detectorChannels.insert(688);
    detectorChannels.insert(694);
    detectorChannels.insert(614);
    detectorChannels.insert(1122);
    detectorChannels.insert(1108);
    detectorChannels.insert(1106);
    detectorChannels.insert(1128);
    detectorChannels.insert(1124);
    detectorChannels.insert(1170);
    detectorChannels.insert(1174);
    detectorChannels.insert(1168);
    detectorChannels.insert(1120);
    detectorChannels.insert(1206);
    detectorChannels.insert(1208);
    detectorChannels.insert(1232);
    detectorChannels.insert(1268);
    detectorChannels.insert(1330);
    std::cout << "Added detectors for DS-6" << std::endl;
    
    std::cout << "Processing runs " << argv[1] << " to " << argv[2] <<std::endl;
    outFileName = savePath + "dataCleaning" + std::string(argv[1]) + "_" + std::string(argv[2]) + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    TFile f1(outFileName.c_str(), "RECREATE");
    f1.cd();
    
    // Identify and assign memory to TTree variables of interest.
    std::vector<Double_t> *trapENFCal = 0;
    chain->SetBranchAddress("trapENFCal", &trapENFCal);
    std::vector<int> *_P = 0;
    chain->SetBranchAddress("P", &_P);
    std::vector<int> *_D = 0;
    chain->SetBranchAddress("D", &_D);
    ULong_t *mH;
    chain->SetBranchAddress("mH", &mH);
    //std::vector<Double_t> *run = 0;
    //chain->SetBranchAddress("run", &run);
    //Int_t run;
    //chain->SetBranchAddress("run", &run);
    std::vector<Double_t> *channel = 0;
    chain->SetBranchAddress("channel", &channel);
    std::cout << "Finished Assigning Variables for TTree output." << std::endl;
    
    // trapECal is in offline computed energy from a trap filter that has been calibrated.
    //TH1D *hrun = new TH1D("hrun", "hrun", 2, 25676, 25678);
    TH1D *hchannel = new TH1D("hchannel", "hchannel", 1440, 0, 1440);
    TH1D *hchannelCuts = new TH1D("hchannelCuts", "hchannelCuts", 1440, 0, 1440);
    //TH2F *EvsRun = new TH2F("EvsRun", "EvsRun", 3000, 0, 3000, 50, 0, 50);
    //TH1D *htrapENFCal = new TH1D("htrapECal", "htrapECal", 3000, 0, 3000);
    //TH1D *htrapENFCalCuts = new TH1D("htrapECalCuts", "htrapECalCuts", 3000, 0, 3000);

    // Event loop!
    UInt_t nHit;
    //UInt_t runNumb;
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        
        if(eventNum % 100000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;
        chain->GetEvent(eventNum);
        
        for(nHit = 0; nHit < (*channel).size(); nHit++){
            
	  hchannel->Fill((*channel)[nHit]);
	  //htrapENFCal->Fill((*trapENFCal)[nHit]);

	  if ((*_P)[nHit]>0 && (*_D)[nHit]>0 && *mH==1){
	       //runNumb = run;
	       hchannelCuts->Fill((*channel)[nHit]);
	       //hrun->Fill(runNumb);
	       //EvsRun->Fill((*run)[nHit], (*trapENFCal)[nHit]);
               //htrapENFCalTot->Fill((*trapENFCal)[nHit]);
	   }    
	}
    } // for event loop
    std::cout << "Finished Event Loop." << std::endl;
    
    // Write output to file
    //EvsRun->SetOption("colz");
    hchannel->Write();
    hchannelCuts->Write();
    //hrun->Write();
    //EvsRun->Write();
    //htrapENFCalTot->Write();
    std::cout << "Done writing, closing file." << std::endl;
    f1.Close();
    
    std::cout << "Done!" << std::endl;
    
    return 0;
}

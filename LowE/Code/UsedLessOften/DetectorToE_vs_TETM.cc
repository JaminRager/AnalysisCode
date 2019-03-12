///
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
    std::string DSets = "4";
    std::stringstream ss;  // General use stream for string to number conversion.
    std::string outFileName;
    std::cout << "std::string things initialized." << std::endl;
    
    // Channels of interest are saved in this set.
    std::unordered_set<Double_t> detectorChannels;
    std::unordered_set<Double_t>::iterator detectorChannelsIt;
    std::cout << "Containers initialized." << std::endl;

    TChain *chain = new TChain("skimTree");
    if(DSets.find("1") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS1*.root");
	detectorChannels.insert(582);
	detectorChannels.insert(580);
	detectorChannels.insert(578);
	detectorChannels.insert(692);
	detectorChannels.insert(648);
	detectorChannels.insert(640);
	detectorChannels.insert(610);
	detectorChannels.insert(608);
	detectorChannels.insert(664);
	detectorChannels.insert(672);
	detectorChannels.insert(632);
	detectorChannels.insert(626);
	detectorChannels.insert(690);
	detectorChannels.insert(600);
	detectorChannels.insert(598);
	detectorChannels.insert(594);
	detectorChannels.insert(592);
    }

    if(DSets.find("2") != std::string::npos) {
	chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
	detectorChannels.insert(582);
	detectorChannels.insert(580);
	detectorChannels.insert(578);
	detectorChannels.insert(692);
	detectorChannels.insert(648);
	detectorChannels.insert(640);
	detectorChannels.insert(610);
	detectorChannels.insert(608);
	detectorChannels.insert(664);
	detectorChannels.insert(672);
	detectorChannels.insert(632);
	detectorChannels.insert(626);
	detectorChannels.insert(690);
	detectorChannels.insert(600);
	detectorChannels.insert(598);
	detectorChannels.insert(592);
    }

    if(DSets.find("3") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS3*.root");
	detectorChannels.insert(580); // DS-3 only has Module 1 detectors
	detectorChannels.insert(582);
	detectorChannels.insert(578);
	detectorChannels.insert(692);
	detectorChannels.insert(648);
	detectorChannels.insert(640);
	detectorChannels.insert(610);
	detectorChannels.insert(608);
	detectorChannels.insert(664);
	detectorChannels.insert(624);
	detectorChannels.insert(694);
	detectorChannels.insert(614);
	detectorChannels.insert(678);
	detectorChannels.insert(672);
	detectorChannels.insert(632);
	detectorChannels.insert(626);
	detectorChannels.insert(690);
	detectorChannels.insert(600);
	detectorChannels.insert(598);
	detectorChannels.insert(592);
	std::cout << "Added skimfiles and detectors for DS-3" << std::endl;
    }

    if(DSets.find("4") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
	detectorChannels.insert(1204);// DS-4 only has Module 1 detectors
	detectorChannels.insert(1174);
	detectorChannels.insert(1144);
	detectorChannels.insert(1106);
	detectorChannels.insert(1176);
	detectorChannels.insert(1172);
	detectorChannels.insert(1170);
	detectorChannels.insert(1136);
	detectorChannels.insert(1330);
	detectorChannels.insert(1332);
	detectorChannels.insert(1296);
	detectorChannels.insert(1298);
	detectorChannels.insert(1236);
	detectorChannels.insert(1232);
	std::cout << "Added skimfiles and detectors for DS-4" << std::endl;
    }

    if(DSets.find("5") != std::string::npos) {
        chain->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/cal-lat/latSkimDS2*.root");
	detectorChannels.insert(662);
	detectorChannels.insert(660);
	detectorChannels.insert(658);
	detectorChannels.insert(692);
	detectorChannels.insert(648);
	detectorChannels.insert(640);
	detectorChannels.insert(610);
	detectorChannels.insert(608);
	detectorChannels.insert(584);
	detectorChannels.insert(624);
	detectorChannels.insert(628);
	detectorChannels.insert(688);
	detectorChannels.insert(694);
	detectorChannels.insert(614);
	detectorChannels.insert(598);
	detectorChannels.insert(592);
	detectorChannels.insert(632);
	detectorChannels.insert(626);
	detectorChannels.insert(690);
	detectorChannels.insert(680);
	detectorChannels.insert(678);
	detectorChannels.insert(674);
	detectorChannels.insert(672);
	detectorChannels.insert(1124);
	detectorChannels.insert(1204);
	detectorChannels.insert(1174);
	detectorChannels.insert(1128);
	detectorChannels.insert(1106);
	detectorChannels.insert(1176);
	detectorChannels.insert(1172);
	detectorChannels.insert(1170);
	detectorChannels.insert(1208);
	detectorChannels.insert(1120);
	detectorChannels.insert(1330);
	detectorChannels.insert(1332);
	detectorChannels.insert(1302);
	detectorChannels.insert(1298);
	detectorChannels.insert(1236);
	detectorChannels.insert(1232);
    }

    if(DSets.find("6") != std::string::npos) {
        //chain->Add("/global/u1/j/jrager/low_energy_skim/output/skimDS6_0_low.root");
	chain->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/*.root");
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
        std::cout << "Added skimfiles and detectors for DS-6" << std::endl;
    }
    
    // Output File. Added dataset name to file name.
    outFileName = "DetectorToECalib_" + DSets + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    std::cout << "Output file initialized." << std::endl;

    // Identify and assign memory to TTree variables of interest.
    std::vector<Double_t> *trapECal = 0;
    chain->SetBranchAddress("trapECal", &trapECal);
    std::vector<int> *C = 0;
    chain->SetBranchAddress("C", &C);
    std::vector<int> *P = 0;
    chain->SetBranchAddress("P", &P);
    std::vector<int> *D = 0;
    chain->SetBranchAddress("D", &D);
    std::vector<Double_t> *trapENFCal = 0;
    chain->SetBranchAddress("trapENFCal", &trapENFCal);
    std::vector<int> *channel = 0;
    chain->SetBranchAddress("channel", &channel);
    std::vector<int> *gain = 0;
    chain->SetBranchAddress("gain", &gain);
    std::vector<bool> *isGood = 0;
    chain->SetBranchAddress("isGood", &isGood);
    std::vector<bool> *isEnr = 0;
    chain->SetBranchAddress("isEnr", &isEnr);
    std::vector<bool> *isNat = 0;
    chain->SetBranchAddress("isNat", &isNat);
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
    Int_t run;
    chain->SetBranchAddress("run", &run);
    Int_t iEvent;
    chain->SetBranchAddress("iEvent", &iEvent);
    std::cout << "Set branchaddresses." << std::endl;
    
    // Allocate individual detector histograms
    std::map<Double_t, TH2F*> ToEHG;
    std::map<Double_t, TH2F*>::iterator ToEHGIt;
    std::cout << "Allocated individual detector histograms." << std::endl;

    // Cut for DS5 & earlier
    // (*gain)[nhit] == 0 && (*isGood)[nhit] && mH==1 && (*P)[nhit] != 0 && (*D)[nhit] != 0 && !muVeto && !isLNFill1 && !isLNFill2)

    for(detectorChannelsIt = detectorChannels.begin(); detectorChannelsIt != detectorChannels.end(); detectorChannelsIt++) {
        ss.str("");
        ss << "htrapENFCalHG" << *detectorChannelsIt;
        ToEHG.insert(std::pair<Double_t, TH2F*>(*detectorChannelsIt,
						new TH2F(ss.str().c_str(),ss.str().c_str(), 300, -20., 10., 400, 0., 10)));
    }
    std::cout << "Detector channels iterator loop." << std::endl;

    // Event loop!
    std::cout << chain->GetEntries() << " events to be processed" << std::endl;
    //ofstream Pb210EvtList("PbEvtList.txt");
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        chain->GetEvent(eventNum);
	//std::cout << "First for loop." << std::endl;

        for(UInt_t nhit = 0; nhit < (*channel).size(); nhit++) {
	    //std::cout << "Second for loop." << std::endl;
             
	  if ((*gain)[nhit] == 0 && (*isGood)[nhit] && mH==1 && (*P)[nhit] != 0 && (*D)[nhit] != 0) {

            if(detectorChannels.find((*channel)[nhit]) != detectorChannels.end()) {
	      (ToEHG.find((*channel)[nhit]))->second->Fill((*trapETailMin)[nhit],(*kvorrT)[nhit]/(*trapENFCal)[nhit]);
	       //std::cout << "Detector histogram filled." << std::endl;
            }                
          }            
        }        
    }
    std::cout << "End event loop." << std::endl;
    
    TFile f1(outFileName.c_str(), "RECREATE");
    f1.cd();
    std::cout << "cd to output file." << std::endl;

    for(ToEHGIt = ToEHG.begin(); ToEHGIt != ToEHG.end(); ToEHGIt++){
        ToEHGIt->second->SetOption("colz");
        ToEHGIt->second->Write();
    }
    std::cout << "Write to output file." << std::endl;

    f1.Close();
    std::cout << "Output file closed." << std::endl;
    
    return 0;
    
}

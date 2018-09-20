//
//  LoadDS5Proto.cpp
//  
//
//  Created by Jamin on 5/24/17.
//
//

//#include <stdio.h>
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
#include <string>

using namespace std;

int main(){
    
    std::string DSets = "5";  // Set to 3 to do DS3, to 4 to do DS4, etc.
    std::string outFileName;
    
    // Channels of interest are saved in this set.
    std::unordered_set<int> detectorChannels;
    
    // Load skimfiles and select detectors that are biased for each DS.
    // DS3-4 list of detectors taken from Clara's CD-4 doc.
    // DS5 list created by duming channel map for a DS5 data file and comparing to list of biased
    // detectors on Ferersa on 5/15/17.
    TChain *chain = new TChain("skimTree");
    if(DSets.find("3") != std::string::npos) {
        chain->Add("/global/project/projectdirs/majorana/data/mjd/surfmjd/analysis/skim/DS3/skimgatrev_86288584/*.root");
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
        chain->Add("/global/project/projectdirs/majorana/data/mjd/surfmjd/analysis/skim/DS4/skimgatrev_86288584/*.root");
        detectorChannels.insert(1205);// DS-4 only has Module 1 detectors
        detectorChannels.insert(1175);
        detectorChannels.insert(1145);
        detectorChannels.insert(1107);
        detectorChannels.insert(1177);
        detectorChannels.insert(1173);
        detectorChannels.insert(1171);
        detectorChannels.insert(1137);
        detectorChannels.insert(1331);
        detectorChannels.insert(1333);
        detectorChannels.insert(1297);
        detectorChannels.insert(1299);
        detectorChannels.insert(1237);
        detectorChannels.insert(1233);
        std::cout << "Added skimfiles and detectors for DS-4" << std::endl;
    }
    
    if(DSets.find("5") != std::string::npos) {
        chain->Add("/global/project/projectdirs/majorana/data/mjd/surfmjd/analysis/skim/DS5/skimgatrev_7938486/*.root");
        //Enriched detectors
        detectorChannels.insert(678); // DS-5 has Module 1 & 2 detectors
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
        std::cout << "Added skimfiles and detectors for DS-5" << std::endl;
    }
    
    
    // Output File. Added dataset name to file name.
    outFileName = "ROOTOutput_" + DSets + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    
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
    std::vector<UInt_t> *wfDCBits = 0;
    chain->SetBranchAddress("wfDCBits", &wfDCBits);
    Int_t mH;
    chain->SetBranchAddress("mH", &mH);
    std::vector<Double_t> *kvorrT = 0;
    chain->SetBranchAddress("kvorrT", &kvorrT);
    std::vector<bool> *muVeto = 0;
    chain->SetBranchAddress("muVeto", &muVeto);
    std::vector<Double_t> *avse = 0;
    chain->SetBranchAddress("avse", &avse);
    std::vector<Double_t> *dcr90 = 0;
    chain->SetBranchAddress("dcr90", &dcr90);
    
    TH1F* htrapENFCalEnr = new TH1F("trapENFCalEnr", "trapENFCalEnr", 60, 0., 60.);
    TH1F* htrapENFCalNat = new TH1F("trapENFCalNat", "trapENFCalNat", 60, 0., 60.);
    TH1F* htrapENFCalwAECutEnr = new TH1F("trapENFCalwAECutEnr", "trapENFCalwAECutEnr", 60, 0., 60.);
    TH1F* htrapENFCalwAECutNat = new TH1F("trapENFCalwAECutNat", "trapENFCalwAECutNat", 60, 0., 60.);
    TH1F* htrapENFCalwAEDCRCutEnr = new TH1F("trapENFCalwAEDCRCutEnr", "trapENFCalwAEDCRCutEnr", 60, 0., 60.);
    TH1F* htrapENFCalwAEDCRCutNat = new TH1F("trapENFCalwAEDCRCutNat", "trapENFCalwAEDCRCutNat", 60, 0., 60.);
    TH2F* hkvorrT_E = new TH2F("hkvorrT_E", "hkvorrT_E", 120, 0., 120., 120, 0., 3.);
    
    //  Numbers taken from a 5/15/17 email from Clint about DS0-5 Livetime and Exposure compiled for LEGEND meeting.
    Double_t DS3exposureEnr = 1/360.346;
    Double_t DS3exposureNat = 1/83.231;
    Double_t DS4exposureEnr = 1/130.098;
    Double_t DS4exposureNat = 1/93.926;
    Double_t DS5exposureEnr = 1/2142.41;
    Double_t DS5exposureNat = 1/1008.01;
    
    if(DSets.find("3") != std::string::npos) {
        htrapENFCalEnr->Scale(DS3exposureEnr);
        htrapENFCalNat->Scale(DS3exposureNat);
        htrapENFCalwAECutEnr->Scale(DS3exposureEnr);
        htrapENFCalwAECutNat->Scale(DS3exposureNat);
        htrapENFCalwAEDCRCutEnr->Scale(DS3exposureEnr);
        htrapENFCalwAEDCRCutNat->Scale(DS3exposureNat);
    }
    
    if(DSets.find("4") != std::string::npos) {
        htrapENFCalEnr->Scale(DS4exposureEnr);
        htrapENFCalNat->Scale(DS4exposureNat);
        htrapENFCalwAECutEnr->Scale(DS4exposureEnr);
        htrapENFCalwAECutNat->Scale(DS4exposureNat);
        htrapENFCalwAEDCRCutEnr->Scale(DS4exposureEnr);
        htrapENFCalwAEDCRCutNat->Scale(DS4exposureNat);
    }
    
    if(DSets.find("5") != std::string::npos) {
        htrapENFCalEnr->Scale(DS5exposureEnr);
        htrapENFCalNat->Scale(DS5exposureNat);
        htrapENFCalwAECutEnr->Scale(DS5exposureEnr);
        htrapENFCalwAECutNat->Scale(DS5exposureNat);
        htrapENFCalwAEDCRCutEnr->Scale(DS5exposureEnr);
        htrapENFCalwAEDCRCutNat->Scale(DS5exposureNat);
    }
    
    TFile f1(outFileName.c_str(), "RECREATE");
    f1.cd();
    htrapENFCalEnr->Write();
    htrapENFCalNat->Write();
    htrapENFCalwAECutEnr->Write();
    htrapENFCalwAECutNat->Write();
    htrapENFCalwAEDCRCutEnr->Write();
    htrapENFCalwAEDCRCutNat->Write();
    hkvorrT_E->Write();
    f1.Close();
    
    return 0;
}

//  ReycoLowE.cc
//
//  Created by Reyco for Low E analysis
//
//  Coppied down by Jamin, 4/05/17
//


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
    std::string DSets = "3";
    std::stringstream ss;  // General use stream for string to number conversion.
    std::string outFileName;
    
    // Channels of interest are saved in this set.
    std::unordered_set<int> detectorChannels;
    std::unordered_set<int>::iterator detectorChannelsIt;
    
    
    // Load skimfiles and select detectors that are biased for each DS.
    // List of detectors taken from Clara's CD-4 doc.
    TChain *chain = new TChain("skimTree");
    if(DSets.find("3") != std::string::npos) {
        chain->Add("/global/homes/w/wisecg/project/skim/*.root");
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
    if(DSets.find("6") != std::string::npos) {
        chain->Add("/global/u1/j/jrager/low_energy_skim/output/skimDS6*.root");
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
    outFileName = "ROOTOutput_" + DSets + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    
    // Identify and assign memory to TTree variables of interest.
    std::vector<Double_t> *trapECal = 0;
    chain->SetBranchAddress("trapECal", &trapECal);
    std::vector<int> *_P = 0;
    chain->SetBranchAddress("P", &_P);
    std::vector<int> *_D = 0;
    chain->SetBranchAddress("D", &_D);
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
    std::vector<int> *module = 0;
    chain->SetBranchAddress("C", &module);
    std::vector<int> *detectorString = 0;
    chain->SetBranchAddress("P", &detectorString);
    std::vector<int> *detectorPosition = 0;
    chain->SetBranchAddress("D", &detectorPosition);
    std::vector<Double_t> *avse = 0;
    chain->SetBranchAddress("avse", &avse);
    std::vector<Double_t> *dcr90 = 0;
    chain->SetBranchAddress("dcr90", &dcr90);
    std::vector<Double_t> *kvorrT = 0;
    chain->SetBranchAddress("kvorrT", &kvorrT);
    std::vector<UInt_t> *wfDCBits = 0;
    chain->SetBranchAddress("wfDCBits", &wfDCBits);
    std::vector<bool> *muVeto = 0;
    chain->SetBranchAddress("muVeto", &muVeto);
    Int_t mH;
    chain->SetBranchAddress("mH", &mH);
    Int_t run;
    chain->SetBranchAddress("run", &run);
    Int_t iEvent;
    chain->SetBranchAddress("iEvent", &iEvent);
    
    std::cout << "Set branchaddresses" << std::endl;
    
    // Allocate individual detector histograms
    std::map<UInt_t, TH1F*> htrapENFCalHG;
    std::map<UInt_t, TH1F*>::iterator htrapENFCalHGIt;
    
    for(detectorChannelsIt = detectorChannels.begin(); detectorChannelsIt != detectorChannels.end(); detectorChannelsIt++) {
        ss.str("");
        ss << "htrapENFCalHG" << *detectorChannelsIt;
        htrapENFCalHG.insert(std::pair<UInt_t, TH1F*>(*detectorChannelsIt,
                                                      new TH1F(ss.str().c_str(),ss.str().c_str(), 10000, 0., 3000)));
    }
    
    //Allocate histograms
    TH1F *hnhits = new TH1F("nhit", "nhit", 30, -0.5, 29.5);
    TH1F *hmHgood = new TH1F("mHgood", "mHgood", 30, -0.5, 29.5);
    TH1F *hchannels = new TH1F("channels", "channels", 150, 550.5, 700.5);
    TH1F *hchannels47 = new TH1F("channels47", "channels47", 150, 550.5, 700.5);
    TH1F *hrun47 = new TH1F("run47", "run47",17981-16796+1 , 16796, 17982 );
    TH1F *htrapENFCal = new TH1F("trapENFCal", "trapENFCal", 3000, 0., 3000.);
    TH1F *htrapENFCal511Coin = new TH1F("trapENFCal511Coin", "trapENFCal511Coin", 3000, 0., 3000.);
    TH1F *htrapENFCalSum = new TH1F("trapENFCalSum", "trapENFCalSum", 6000, 0., 6000.);
    TH1F *htrapENFCalTotalSum = new TH1F("trapENFCalTotalSum", "trapENFCalTotalSum", 6000, 0., 6000.);
    TH1F *htrapENFCalAll = new TH1F("trapENFCalAll", "trapENFCalAll", 3000, 0., 3000.);
    TH1F *htrapENFCalEnr = new TH1F("trapENFCalEnr", "trapENFCalEnr", 3000, 0., 3000.);
    TH1F *htrapENFCalNat = new TH1F("trapENFCalNat", "trapENFCalNat", 3000, 0., 3000.);
    TH1F *htrapENFCalwAECutEnr = new TH1F("trapENFCalwAECutenr", "trapENFCalwAECutsenr", 3000, 0., 3000.);
    TH1F *htrapENFCalwAECutNat = new TH1F("trapENFCalwAECutNat", "trapENFCalwAECutsNat", 3000, 0., 3000.);
    TH1F *htrapENFCalwAEDCRCutEnr = new TH1F("trapENFCalwAEDCRCutenr", "trapENFCalwAEDCRCutsenr", 3000, 0., 3000.);
    TH1F *htrapENFCalwAEDCRCutNat = new TH1F("trapENFCalwAEDCRCutNat", "trapENFCalwAEDCRCutsNat", 3000, 0., 3000.);
    TH2F *hECoincNoCut = new TH2F("hECoinNoCut", "hECoingNoCut", 3000, 0., 3000., 3000, 0., 3000.);
    TH2F *hkvorrT_E = new TH2F("hkvorrT_E", "hkvorrT_E", 3000, 0., 3000., 200, 0., 5.);
    
    // Event loop!
    std::cout << chain->GetEntries() << " events to be processed" << std::endl;
    Double_t E1, E2, totalE;
    ofstream Pb210EvtList("PbEvtList.txt");
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++){
        chain->GetEvent(eventNum);
        hnhits->Fill((*channel).size());
        totalE = 0;
        if(eventNum % 100000 == 0) std::cout << "Processing # "  << eventNum << std::endl;
        for(UInt_t nhit = 0; nhit < (*channel).size(); nhit++) {
            hchannels->Fill((*channel)[nhit]);
            if((*gain)[nhit] == 0 && (*isGood)[nhit] && !(*wfDCBits)[nhit] && !(*muVeto)[nhit]){
                // Only events that pass DC cuts.
                hmHgood->Fill(mH);
                if(mH == 2) { // Multiplicitiy 2 events
                    E1 = E2 = -1e6;
                    for(UInt_t nhit2 = 0; nhit2 < (*channel).size(); nhit2++) {
                        if(detectorChannels.find((*channel)[nhit2]) != detectorChannels.end()) {
                            if(E1 < -1e5)
                                E1 = (*trapENFCal)[nhit2];
                            else if(E2 < -1e5)
                                E2 = (*trapENFCal)[nhit2];
                            else
                                std::cout << "not mh == 2 ";
                        }
                    }
                    hECoincNoCut->Fill(E1, E2);
                    hECoincNoCut->Fill(E2, E1);
                    htrapENFCalSum->Fill(E1+E2);
                }
                
                if((*dcr90)[nhit] < 0) { // Only HG channels that pass DCR cut
                    htrapENFCalAll->Fill((*trapENFCal)[nhit]);
                    totalE += (*trapENFCal)[nhit];
                }
                
                if(mH==1 && (*trapENFCal)[nhit] > 45.3 && (*trapENFCal)[nhit] < 47.7) {
                    hchannels47->Fill((*channel)[nhit]);
                    hrun47->Fill(run);
                    std::cout << "Run: " << run << " iEvent: " << iEvent << " channel: " <<  (*channel)[nhit] << " trapeENDFCal: " << (*trapENFCal)[nhit] << " nhit:" << nhit << std::endl;
                    Pb210EvtList << run << " " << iEvent << " " << nhit << std::endl;
                }
                
                if(mH > 1 && (*trapENFCal)[nhit] > 509.0 && (*trapENFCal)[nhit] < 513.0){
                    for(UInt_t coincI = 0; coincI < (*channel).size(); coincI++)
                        if(nhit != coincI && (*gain)[coincI] == 0)
                            htrapENFCal511Coin->Fill((*trapENFCal)[coincI]);
                }
                
                if(mH == 1){
                    hkvorrT_E->Fill((*trapENFCal)[nhit], (*kvorrT)[nhit]/(*trapENFCal)[nhit]);
                    if((*isEnr)[nhit] && (*kvorrT)[nhit]/(*trapENFCal)[nhit]>0.6 && (*kvorrT)[nhit]/(*trapENFCal)[nhit]<2) {
                        htrapENFCalEnr->Fill((*trapENFCal)[nhit]);
                    } else if ((*isNat)[nhit] && (*kvorrT)[nhit]/(*trapENFCal)[nhit]>0.6 && (*kvorrT)[nhit]/(*trapENFCal)[nhit]<2) {
                        htrapENFCalNat->Fill((*trapENFCal)[nhit]);
                    }
                    //Clara's CD-4 cuts
                    if((*avse)[nhit] > -1){
                        if((*isEnr)[nhit]) {
                            htrapENFCalwAECutEnr->Fill((*trapENFCal)[nhit]);
                        }
                        else if ((*isNat)[nhit]) {
                            htrapENFCalwAECutNat->Fill((*trapENFCal)[nhit]);
                        }
                        if((*dcr90)[nhit] < 0) {
                            if((*isEnr)[nhit]) {
                                htrapENFCalwAEDCRCutEnr->Fill((*trapENFCal)[nhit]);
                            }
                            else if ((*isNat)[nhit]) {
                                htrapENFCalwAEDCRCutNat->Fill((*trapENFCal)[nhit]);
                            }
                            if(detectorChannels.find((*channel)[nhit]) != detectorChannels.end()) {
                                (htrapENFCalHG.find((*channel)[nhit]))->second->Fill((*trapENFCal)[nhit]);
                            }
                        }
                    }
                }
            } //       if((*isGood)[nhit] && !(*wfDCBits)[nhit]){ /
        } //  if((*isGood)[nhit] && !(*wfDCBits)[nhit]){ // Only events that pass DC cuts.
        htrapENFCalTotalSum->Fill(totalE);
    } // for loop
    
    Pb210EvtList.close();
    
    //Post-processing of histograms
    Double_t DS3exposureEnr = 1/377.82; // kg.days from Calra's CD-4 doc. 
    Double_t DS3exposureNat = 1/83.19;
    Double_t DS3exposureAll = 1/466.1;
    Double_t DS4exposureEnr = 1/130.0; // kg.days from Calra's CD-4 doc. 
    Double_t DS4exposureNat = 1/94.0;
    Double_t DS4exposureAll = 1/224.0;
    Double_t DS6exposureEnr = 1/439.02;
    Double_t DS6exposureNat = 1/217.12;
    Double_t DS6exposureAll = 1/656.14;

    if(DSets.find("3") != std::string::npos) {
      htrapENFCal->Scale(DS3exposureAll);
      htrapENFCalEnr->Scale(DS3exposureEnr);
      htrapENFCalNat->Scale(DS3exposureNat);
      htrapENFCalwAECutEnr->Scale(DS3exposureEnr);
      htrapENFCalwAECutNat->Scale(DS3exposureNat);
      htrapENFCalwAEDCRCutEnr->Scale(DS3exposureEnr);
      htrapENFCalwAEDCRCutNat->Scale(DS3exposureNat);
    }
    
    if(DSets.find("4") != std::string::npos) {
      htrapENFCal->Scale(DS4exposureAll);
      htrapENFCalEnr->Scale(DS4exposureEnr);
      htrapENFCalNat->Scale(DS4exposureNat);
      htrapENFCalwAECutEnr->Scale(DS4exposureEnr);
      htrapENFCalwAECutNat->Scale(DS4exposureNat);
      htrapENFCalwAEDCRCutEnr->Scale(DS4exposureEnr);
      htrapENFCalwAEDCRCutNat->Scale(DS4exposureNat);
    }
    
    if(DSets.find("6") != std::string::npos) {
      htrapENFCal->Scale(DS6exposureAll);
      htrapENFCalEnr->Scale(DS6exposureEnr);
      htrapENFCalNat->Scale(DS6exposureNat);
      htrapENFCalwAECutEnr->Scale(DS6exposureEnr);
      htrapENFCalwAECutNat->Scale(DS6exposureNat);
      htrapENFCalwAEDCRCutEnr->Scale(DS6exposureEnr);
      htrapENFCalwAEDCRCutNat->Scale(DS6exposureNat);
    }

    
    // Write output to file
    TFile f1(outFileName.c_str(), "RECREATE");
    f1.cd();
    hnhits->Write();
    hchannels->Write();
    hchannels47->Write();
    hrun47->Write();
    htrapENFCal->Write();
    htrapENFCalEnr->Write();
    htrapENFCalNat->Write();
    htrapENFCalwAECutEnr->Write();
    htrapENFCalwAECutNat->Write();
    htrapENFCalwAEDCRCutEnr->Write();
    htrapENFCalwAEDCRCutNat->Write();
    hmHgood->Write();
    htrapENFCal511Coin->Write();
    htrapENFCalSum->Write();
    htrapENFCalTotalSum->Write();
    htrapENFCalAll->Write();
    hECoincNoCut->Write();
    hkvorrT_E->Write();
    std::cout << "1173.23: " << htrapENFCalAll->Integral(1173.23-1.5, 1173.23+1.5)/3. << "   "
    << htrapENFCalAll->Integral(1173.23-50, 1173.23+50)/100. << std::endl;
    std::cout << "1332.5: " << htrapENFCalAll->Integral(1332.5-1.5, 1332.5+1.5)/3. << "   "
    << htrapENFCalAll->Integral(1332.5-50, 1332.5+50)/100. << std::endl;
    for(htrapENFCalHGIt = htrapENFCalHG.begin(); htrapENFCalHGIt != htrapENFCalHG.end(); htrapENFCalHGIt++) 
        htrapENFCalHGIt->second->Write();
    
    f1.Close();
    
    return 0;
}

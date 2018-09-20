//
//  DetectorEfficiency.cpp
//  
//
//  Created by Jamin on 8/25/18.
//
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
#include "TROOT.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TEntryList.h"
#include "TLine.h"

#include "GATDataSet.hh"
#include "DataSetInfo.hh"

using namespace std;

char cut1[10000];
char tetmCut[] = "(((channel==582 || channel==632) && trapETailMin<0.3) || ((channel==580 || channel==598 || channel==600 || channel==608 || channel==610 || channel==648 || channel==664 || channel==692) && trapETailMin<0.4) || ((channel==640 || channel==672) && trapETailMin<0.5) || ((channel==578 || channel==594 || channel==626 || channel==690) && trapETailMin<0.6))";
char ToE_EDependent[] = "((trapENFCal>=5 && trapENFCal<9 && ((channel!=580 && channel!=664 && kvorrT/trapENFCal>0.84 && kvorrT/trapENFCal<1.92) || (channel==580 && kvorrT/trapENFCal>0.65 && kvorrT/trapENFCal<1.37) || (channel==664 && kvorrT/trapENFCal>0.74 && kvorrT/trapENFCal<1.76))) || (trapENFCal>=9 && trapENFCal<20 && ((channel!=580 && channel!=664 && kvorrT/trapENFCal>1.01 && kvorrT/trapENFCal<1.73) || (channel==580 && kvorrT/trapENFCal>0.76 && kvorrT/trapENFCal<1.24) || (channel==664 && kvorrT/trapENFCal>0.93 && kvorrT/trapENFCal<1.53))) || (trapENFCal>=20 && ((channel!=580 && channel!=664 && kvorrT/trapENFCal>1.16 && kvorrT/trapENFCal<1.64) || (channel==580 && kvorrT/trapENFCal>0.84 && kvorrT/trapENFCal<1.14) || (channel==664 && kvorrT/trapENFCal>1.04 && kvorrT/trapENFCal<1.40))))";
char HEDetCut[] = "channel!=584 && channel!=585 && channel!=642 && channel!=643 && channel!=616 && channel!=617 && channel!=624 && channel!=625 && channel!=628 && channel!=629 && channel!=688 && channel!=689 && channel!=694 && channel!=695 && channel!=614 && channel!=615 && channel!=680 && channel!=681 && channel!=678 && channel!=679 && channel!=696 && channel!=697 && channel!=630 && channel!=631";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>237.35 && (trapENFCal[0] + trapENFCal[1])<239.57)";

int main()
{
  std::string DSets = "1";
  std::stringstream ss;  // General use stream for string to number conversion.
  std::string outFileName;
  std::cout << "Stringstream stuff" << std::endl;
    
  // Channels of interest are saved in this set.
  std::unordered_set<int> detectorChannels;
  std::unordered_set<int>::iterator detectorChannelsIt;
  std::cout << "Unordered set for storing channel numbers " << std::endl;
  
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
  std::cout << "Data files and channels loaded" << std::endl;

  // Output File. Added dataset name to file name.
  outFileName = "/global/u1/j/jrager/LowE/DetectorEfficiencyDS_" + DSets + ".root";
  std::cout << "Output will be written to file " << outFileName << std::endl;
    
  // Define the cut
  //sprintf(cut1,"%s && %s && %s && %s",tetmCut,ComptonManual,ToE_EDependent,HEDetCut);
    
  // Allocate individual detector histograms
  std::map<UInt_t, TH1F*> Pass;
  std::map<UInt_t, TH1F*>::iterator PassIt;
  std::cout << "Container of detector histograms" << std::endl;
    
  // Create a histogram for all the channels
  for(detectorChannelsIt = detectorChannels.begin(); detectorChannelsIt != detectorChannels.end(); detectorChannelsIt++) {
    ss.str("");
    ss << "Pass" << *detectorChannelsIt;
    Pass.insert(std::pair<UInt_t, TH1F*>(*detectorChannelsIt,
					 new TH1F(ss.str().c_str(),ss.str().c_str(), 400, 0., 100)));
  }
  std::cout << "Histograms created" << std::endl;

  TFile f1(outFileName.c_str(), "RECREATE");
  f1.cd();
  std::cout << "cd to outfile" << std::endl;
    
  for(PassIt = Pass.begin(); PassIt != Pass.end(); PassIt++){
    TChain *skimTree = new TChain("skimTree");
    //sprintf(cut1,"%s && %s && %s && %s",tetmCut,ComptonManual,ToE_EDependent,HEDetCut);
    //skimTree->Project("PassIt", "trapENFCal", cut1);
    skimTree->Project("PassIt->second", "trapENFCal");
    //PassIt->second->Draw("trapENFCal",cut1);
    PassIt->second->Write();
  }
  std::cout << "Fill histograms" << std::endl;
  
  f1.Close();
  std::cout << "Close output file" << std::endl;
    
  return 0;
    
}

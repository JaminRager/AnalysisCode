//
//  LiveTimeSacrifice.cpp
//  
//
//  Created by Jamin on 1/25/19.
//

#include <stdio.h>

#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <numeric>

#include "TChain.h"
#include "TFile.h"
#include "TROOT.h"
#include "TH1.h"
#include "TStyle.h"
#include "TEntryList.h"
#include "TH1.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLine.h"

#include "DataSetInfo.hh"



using namespace std;

int main()
{
    // Input file
    TChain *chain = new TChain("dsTree");
    chain->Add("~/lat/data/ds_6_livetime.root");
    cout << "Adding data files" <<  endl;
    
    // Identify and assign memory to TTree variables of interest.
    Int_t run;
    chain->SetBranchAddress("run", &run);
    std::vector<Int_t> *channel = 0;
    chain->SetBranchAddress("channel", &channel);
    std::vector<Double_t> *livetime = 0;
    chain->SetBranchAddress("livetime", &livetime);
    std::vector<Double_t> lt;
    Int_t c = 0;
    Double_t l = 0.0;
    std::cout << "Finished Assigning Variables for TTree output." << std::endl;
    
    // Loop through events, or entries
    std::cout << "Entering event loop." << std::endl; 
    for(UInt_t eventNum = 1; eventNum < chain->GetEntries(); eventNum++) {
        chain->GetEvent(eventNum);
        
	//if(eventNum % 1000 == 1) std::cout << "Processing Event # "  << eventNum-1 << std::endl;

        // For each entry, loop through detector channels
        for(UInt_t nhit = 0; nhit < (*channel).size(); nhit++) {

	  //if ((run>=25704 && run <=43625) && (*channel)[nhit]==674) {
	  if ((run>=36029 && run<=36047) && (*channel)[nhit]==674) {  
	      c = (*channel)[nhit];
	      l = (*livetime)[nhit];
	      lt.push_back((*livetime)[nhit]);
	      std::cout << "run " << run << " channel " << c << " livetime " << l << std::endl;
	  }
        }
    }
    std::cout << "End event loop." << std::endl;
    
    Double_t sum_of_elems = std::accumulate(lt.begin(), lt.end(), 0.0);
    std::cout << "Sum of LT:"<< sum_of_elems << std::endl;

    std::cout << "Done writing, closing file." << std::endl;

    std::cout << "Done!" << std::endl;

    return 0;
}

//char DS5aSelection[] = "((channel==1332 && run>=19708 && run<=19722) || ((channel==584 || channel==610 || channel==614 || channel==648 || channel==658 || channel==660 || channel==692 || channel==1172 || channel==1332) && run>=20218 && run<=21453) || (channel==692 && run>=21767 && run<=21769) || (channel==692 && run==20489) || (channel==692 && run>=21568 && run<=21612) || (channel==692 && run>=21763 && run<=21781) || (run==692 && run>=20218 && run<=21453))";
//char DS5bSelection[] = "(channel==692 && (run==22937 || run==22946 || run==22952 || run==22954))";
//char DS6Selection[] = "(channel==674 && run>=36034 && run<=36047)";


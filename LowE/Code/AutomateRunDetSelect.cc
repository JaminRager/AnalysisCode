//
//  AutomateRunDetSelect.cpp
//  
//
//  Created by Jamin on 1/29/19.
//
//  Automates run and detector selection by picking outliers using z-scores.

#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include "TFile.h"
#include "TROOT.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TEntryList.h"



using namespace std;


int main()
{
    // Load input files
    string inFile1 = "~/LowE/AnalysisPlots/latest/DetectorSelection/DetSelectDS5a_5kThresh.root";
    TFile *f1 = new TFile(inFile1.c_str());
    
    // Load TH2's
    TH2F *h1 = (TH2F*)f1->Get("detVrun");
    
    // Initialize vectors
    std::vector<double> ctsTally;
    
    // Caluclate Total number of bins in histogram including underflow and overflow bins
    Int_t numberofbins = h1->GetSize();
    
    // have to do binx, biny and convert these into global bin number
        //two nested for loops
    // just use offset method to get x,y coordinates of binx, biny
    for(int i=1; i<=numberofbins; i++) {
        Int_t cts = h1->GetBinContent(i);
        if (cts != 0) {
            ctsTally.push_back(cts);
        }
    }
    
    double sum = std::accumulate(ctsTally.begin(), ctsTally.end(), 0.0);
    double mean = sum / ctsTally.size();
    double sq_sum = std::inner_product(ctsTally.begin(), ctsTally.end(), ctsTally.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / ctsTally.size() - mean * mean);
    cout << "sum " << sum << " mean " << mean << " sq_sum " << sq_sum << " stdev " << stdev << endl;
    
    for(int i=1; i<=numberofbins; i++) {
        Int_t cts = h1->GetBinContent(i);
        if (cts != 0) {
            double z = (cts - mean)/stdev;
            if (z>=3)
	    //if (cts >= 10*mean)  
            {
	        int binx, biny, binz;
	        h1->GetBinXYZ(i,binx,biny,binz);
		//int run = binx + 8722 - 1;  //DS1
		//int run = binx + 14508 - 1;  //DS2
		//int run = binx + 16031 - 1;  //DS3
		//int run = binx + 60000550 - 1;  //DS4
		int run = binx + 18623 - 1;  //DS5a
		//int run = binx + 22393 - 1;  //DS5b
		//int run = binx + 23975 - 1;  //DS5c
		//int run = binx + 25704 - 1;  //DS6
		int channel = biny - 1;
                cout << "run: " << run << " channel: " << channel << " counts: " << cts << " z score: " << z << endl;
            }
        }
    }
    
    
    return 0;
}

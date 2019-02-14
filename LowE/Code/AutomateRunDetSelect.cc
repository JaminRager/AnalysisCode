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
#include <stdio.h>
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
#include "TGraph.h"


using namespace std;


int main()
{
    // Load input files
    string inFile1 = "/global/homes/j/jrager/LowE/AnalysisPlots/most_latest/DetSelection/DetSelectDS5b_5kThresh_correctedCuts.root";
    TFile *f1 = new TFile(inFile1.c_str());
    //string inFile2 = "~/LowE/Data/DS5aDetSelect_5kThresh_CleanRuns.root";
    //TFile *f2 = new TFile(inFile2.c_str());

    // Output file
    ofstream myfile ("/global/homes/j/jrager/LowE/DS5bRejectedRuns_Dets.txt");
    //ofstream myfile ("/global/homes/j/jrager/LowE/DS6RejectedRuns_Dets_ZScores.txt");

    // Load TH2's
    TH2F *h1 = (TH2F*)f1->Get("detVrun");
    //TH2F *h2 = (TH2F*)f2->Get("detVrun");

    // Initialize vectors
    std::vector<double> ctsTally;
    //std::vector<int> v_run;
    //std::vector<int> v_channel;

    // Caluclate Total number of bins in histogram including underflow and overflow bins
    //Int_t numberofbins = h1->GetSize();
    
    // have to do binx, biny and convert these into global bin number
        //two nested for loops
    // just use offset method to get x,y coordinates of binx, biny
    for(int i=1; i<=h1->GetSize(); i++) {
        Int_t cts = h1->GetBinContent(i);
        if (cts != 0) {
            ctsTally.push_back(cts);
        }
    }

    // mean and stdev
    double sum = std::accumulate(ctsTally.begin(), ctsTally.end(), 0.0);
    double mean = sum / ctsTally.size();
    double sq_sum = std::inner_product(ctsTally.begin(), ctsTally.end(), ctsTally.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / ctsTally.size() - mean * mean);
    
    // median, first and third quartiles
    // didn't work, junk code
    //double med, Q1, Q3;
    //int size = ctsTally.size();
    //sort(ctsTally.begin(), ctsTally.end());
    //if (size % 2 == 0)
      //{
        //med = (ctsTally[size / 2 - 1] + ctsTally[size / 2]) / 2;
	//Q1 = (ctsTally[size / 2 - 1] + ctsTally[size / 2]) / 4;
	//Q3 = med + Q1;
      //}
    //else 
      //{
        //med =  ctsTally[size / 2];
	//Q1 = ctsTally[size / 4];
	//Q3 = med + Q1;
      //}

    //cout << "sum " << sum << " mean " << mean << " sq_sum " << sq_sum << " stdev " << stdev << endl;
    myfile << "sum " << sum << " mean " << mean << " sq_sum " << sq_sum << " stdev " << stdev << "\n";

    for(int i=1; i<=h1->GetSize(); i++) {
        Int_t cts = h1->GetBinContent(i);
        if (cts != 0) {
            double z = (cts - mean)/stdev;
            //if (z>=3)
	    if (cts >= 10*mean)  
            {
                int binx, biny, binz;
	        h1->GetBinXYZ(i,binx,biny,binz);
		//int run = binx + 8722 - 1;  //DS1
		//int run = binx + 14508 - 1;  //DS2
		//int run = binx + 16031 - 1;  //DS3
		//int run = binx + 60000550 - 1;  //DS4
		//int run = binx + 18623 - 1;  //DS5a
		int run = binx + 22393 - 1;  //DS5b
		//int run = binx + 23975 - 1;  //DS5c
		//int run = binx + 25704 - 1;  //DS6
		int channel = biny - 1;
                //cout << "run: " << run << " channel: " << channel << " counts: " << cts << " z score: " << z << endl;
		myfile << "run: " << run << " channel: " << channel << " counts: " << cts << " z score: " << z << "\n";
		//myfile << run,channel,cts,z,"\n";
		//v_run.push_back(run);
		//v_channel.push_back(channel);
            }
        }
    }   
   
    return 0;
}

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
    string inFile1 = "~/LowE/Data/BlindRunSelectDS5b_5kThresh.root";
    TFile *f1 = new TFile(inFile1.c_str());
    string inFile2 = "~/LowE/AnalysisPlots/latest/DetectorSelection/DetSelectDS5b_5kThresh.root";
    TFile *f2 = new TFile(inFile2.c_str());

    // Load TH2's
    TH1F *h1 = (TH1F*)f1->Get("run");
    TH1F *h2 = (TH1F*)f2->Get("det");

    // Initialize vectors
    std::vector<double> run;
    std::vector<double> chan;

    //Run loop
    //DS5b: i=0; i<1565
    for (Int_t i=7; i<1565; i++)
      {
        double ctsRun = h1->Integral(i,i);
	run.push_back(ctsRun);
	//cout << "i " << i << " ctsRun " << ctsRun << endl;
      }

    double sumR = std::accumulate(run.begin(), run.end(), 0.0);
    double meanR = sumR / run.size();
    double sq_sumR = std::inner_product(run.begin(), run.end(), run.begin(), 0.0);
    double stdevR = std::sqrt(sq_sumR / run.size() - meanR * meanR);
    cout << "sumR " << sumR << " meanR " << meanR << " sq_sumR " << sq_sumR << " stdevR " << stdevR << endl;

    //Channel loop
    //DS5b: j=584; j<1331;
    for (Int_t j=584; j<1331; j++)
      {
        double ctsDet = h2->Integral(j,j);
        chan.push_back(ctsDet);
      }

    double sumC = std::accumulate(chan.begin(), chan.end(), 0.0);
    double meanC = sumC / chan.size();
    double sq_sumC = std::inner_product(chan.begin(), chan.end(), chan.begin(), 0.0);
    double stdevC = std::sqrt(sq_sumC / chan.size() - meanC * meanC);
    cout << "sumC " << sumC << " meanC " << meanC << " sq_sumC " << sq_sumC << " stdevC " << stdevC << endl;
    
    //seems to be skipping this part of the program. maybe if I try looping over vectors run and chan instead?
    //would have to change ranges on loops to go through entier range of run and channel in data files
    //DS5b: i=0; i<1565
    for (Int_t k=7; k<1565; k++)
      {
        Int_t r = k+22393;
        double ctsRun = run[k];
        double zRun = (ctsRun - meanR)/stdevR;
        if (zRun>=3)
	  {
            for (Int_t l=584; l<1331; l++)
	      {
                double ctsDet = chan[l];
                double zDet = (ctsDet - meanC)/stdevC;
                if (zDet>=3)
		  {
		    cout << "run: " << r << " zRun: " << zRun << " channel: " << l << " zDet: " << zDet << endl;
		  }
	      }
	  }
      }
    

    cout << "done" <<  endl;

    return 0;
}

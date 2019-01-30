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

void Method1();
void Method2();

int main()
{
    //Method1();
    Method2();
}

void Method1()
{
    // Load input files
    string inFile1 = "~/LowE/Data/BlindRunSelectDS5b_5kThresh.root";
    TFile *f1 = new TFile(inFile1.c_str());
    string inFile2 = "~/LowE/AnalysisPlots/latest/DetSelectDS5b_5kThresh.root";
    TFile *f2 = new TFile(inFile2.c_str());
    
    // Create output file
    //string outFile = "/global/u1/j/jrager/LowE/Data/ZScores.txt";
    //TFile *f3 = new TFile(outFile.c_str(),"RECREATE");
    //cout << "Creating outpout file" <<  endl;
    
    // Load TH2's
    TH1F *h1 = (TH1F*)f1->Get("run");
    TH1F *h2 = (TH1F*)f2->Get("det");
    
    // Get stats from plots
    Int_t axis;
    Double_t meanRun = h1->GetMean(axis = 2);
    Double_t stdevRun = h1->GetStdDev(axis = 2);
    Double_t meanDet = h2->GetMean(axis = 2);
    Double_t stdevDet = h2->GetStdDev(axis = 2);
    
    cout << "meanRun: " << meanRun << " stdevRun: " << stdevRun << " meanDet: " << meanDet << " stdevDet: " << stdevDet << endl;
    
    Int_t run;

    //DS5b: i=0; i<1565
    for (Int_t i=7; i<1565; i++)
    {
        run = i+22393;
        Double_t ctsRun = h1->Integral(i,i);
        Double_t zRun = (ctsRun - meanRun)/stdevRun;
        if (zRun>=3)
        {
            for (Int_t j=584; j<1331; j++)
            {
                Double_t ctsDet = h2->Integral(j,j);
                Double_t zDet = (ctsDet - meanDet)/stdevDet;
                if (zDet>=3)
                {
		   cout << "run: " << run << " zRun: " << zRun << " channel: " << j << " zDet: " << zDet << endl;
                }
            }
        }
    }
}

void Method2()
{
    // Load input files
    string inFile1 = "~/LowE/Data/BlindRunSelectDS5b_5kThresh.root";
    TFile *f1 = new TFile(inFile1.c_str());
    //string inFile2 = "~/LowE/AnalysisPlots/latest/DetSelectDS5b_5kThresh.root";
    //TFile *f2 = new TFile(inFile2.c_str());

    // Load TH2's
    TH1F *h1 = (TH1F*)f1->Get("run");
    //TH1F *h2 = (TH1F*)f2->Get("det");

    // Initialize vectors
    std::vector<double> *runCts = 0;
    //std::vector<double> *chan = 0;

    //Run loop
    //DS5b: i=0; i<1565
    for (Int_t i=7; i<1565; i++)
      {
        double ctsRun = h1->Integral(i,i);
	runCts->push_back(ctsRun);
      }

    //Channel loop
    //DS5b: j=584; j<1331;
    //for (Int_t j=584; j<1331; j++)
      //{
        //double ctsDet = h2->Integral(j,j);
	//chan->push_back(ctsDet);
      //}

    double sum = std::accumulate((*runCts).begin(), (*runCts).end(), 0.0);
    double mean = sum / (*runCts).size();
    double sq_sum = std::inner_product((*runCts).begin(), (*runCts).end(), (*runCts).begin(), 0.0);
    double stdev = std::sqrt(sq_sum / (*runCts).size() - mean * mean);

    cout << "sum " << sum << " mean " << mean << " sq_sum " << sq_sum << "stdev" << stdev << endl;

    cout << "done" <<  endl;
}

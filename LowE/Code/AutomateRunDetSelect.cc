//
//  AutomateRunDetSelect.cpp
//  
//
//  Created by Jamin on 1/29/19.
//
//  Automates run and detector selection by picking outliers using z-scores.

#include <iostream>
#include <fstream>
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

void MakeZScores();
//void PlotZScores();

int main()
{
    MakeZScores();
    //PlotZScores();
}

void MakeZScores()
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
    Double_t meanRun = h1->GetMean(Int_t axis = 2);
    Double_t stdevRun = h1->GetStdDev(Int_t axis = 2);
    Double_t meanDet = h2->GetMean(Int_t axis = 2);
    Double_t stdevDet = h2->GetStdDev(Int_t axis = 2);
    
    cout << "meanRun: " << meanRun << " stdevRun: " << stdevRun << " meanDet: " << meanDet << " stdevDet: " << stdevDet << endl;
    
    //DS5b: i=0; i<1565
    for (Int_t i=7; i<1565; i++)
    {
        Double_t ctsRun = h1->Integral(i,i);
        Doublt_t zRun = (ctsRun - meanRun)/stdevRun;
        if (zRun>=3)
        {
            for (Int_t j=584; j<1331; j++)
            {
                Double_t ctsDet = h2->Integral(j,j);
                Doublt_t zDet = (ctsDet - meanDet)/stdevDet;
                if (zDet>=3)
                {
                    cout << "run: " << run << " zRun: " << zRun << " channel: " << channel << " zDet: " zDet << endl;
                }
            }
        }
    }
}

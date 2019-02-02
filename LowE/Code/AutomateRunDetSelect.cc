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
    //for (Int_t k=7; k<1565; k++)
      //{
        //Int_t r = k+22393;
        //double ctsRun = run[k];
        //double zRun = (ctsRun - meanR)/stdevR;
        //if (zRun>=3)
          //{
            //for (Int_t l=584; l<1331; l++)
              //{
                //double ctsDet = chan[l];
                //double zDet = (ctsDet - meanC)/stdevC;
                //if (zDet>=3)
                  //{
                      //cout << "run: " << r << " zRun: " << zRun << " channel: " << l << " zDet: " << zDet << endl;
                  //}
              //}
          //}
      //}
    
    int r = 22400;
    int c = 584;
    // loop over runs
    for (std::vector<int>::iterator it = run.begin() ; it != run.end(); ++it)
      {
        double zRun = ((*it) - meanR)/stdevR;
        if (zRun>=3)
          {
            // loop over channels
            for (std::vector<int>::iterator iter = chan.begin() ; iter != chan.end(); ++iter)
              {
                double zDet = ((*iter) - meanC)/stdevC;
                if (zDet>=3)
                  {
                      cout << "run: " << r << " zRun: " << zRun << " channel: " << l << " zDet: " << zDet << endl;
                  }
                ++c;
              }
          }
        ++r;
      }
    

    cout << "done" <<  endl;
}

void Method2()
{
    // Load input files
    string inFile1 = "~/LowE/AnalysisPlots/latest/DetectorSelection/DetSelectDS5b_5kThresh.root";
    TFile *f1 = new TFile(inFile2.c_str());
    
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
    cout << "sum " << sum << " mean " << mean << " sq_sum " << sq_sumR << " stdev " << stdevR << endl;
    
    //for(int i=0; i<=(numberofbins - 1); i++) {
        //Int_t cts = h1->GetBinContent(i);
        //if (cts != 0) {
            //double z = (cts - mean)/stdev;
            //if (zRun>=3)
            //{
                //double run = h->GetXaxis()->GetBinCenter(i); //need to double check that this line works
                //double channel = h->GetYaxis()->GetBinCenter(i); //need to double check that this line works
                //cout << "run: " << run << " z score: " << z << " channel: " << channel << endl;
            //}
        //}
    //}
    
    
    
}

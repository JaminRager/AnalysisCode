  #include <stdio.h>
  #include <iostream>
  #include <set>  
  #include <map>
  #include <vector>
  #include <sstream>
  #include <stdlib.h>

  #include "TChain.h"
  #include "TFile.h"
  #include "TH1.h"
  #include "TGraphAsymmErrors.h"
  #include "TEfficiency.h"

  #include "GATDataSet.hh"
  #include <string>

  #include <TROOT.h>
  #include <TStyle.h>
  #include "TColor.h"

  using namespace std;
  // Calculates the combined efficiency weighted by exposure from two DS1 detectors
  // The individual detector efficiencies have Clopper-Pearson error bars
  // Uses propagation or error to find error bars for combined efficiency
  int main()
  {
	//Load individual detector efficiencies
    //TGraphAsymmErrors *geff[2];
    TFile *f1 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch578.root");
    TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
    //geff[0] = (TGraphAsymmErrors*)f1->Get("Graph");
    //TFile *f2 = new TFile("~/LowE/Data/ClopperErrorDS1Ch580.root");
    //geff[1] = (TGraphAsymmErrors*)f2->Get("Graph");
    //cout << "Loading data files" << endl;

    // Initialize arrays
    double effSum[20] = {};
    double errSumhi[20] = {};
    double errSumlow[20] = {};
    double x[20] = {};
    double xerr[20] = {};
    double eff[2][20] = {};
    double errhi[2][20] = {};
    double errlow[2][20] = {};
    cout << "Initializing arrays" << endl;
      
    // Live time and active masses for detectors
    double LT = 58.7676;
    //double M_1 = 0.968;
    //double errM_1 = 0.013;
    //double M_2 = 0.811;
    //double errM_2 = 0.012;
    double M[2] = {0.968,0.811};
    //double errM[2] = {0.013,0.012};

    // Loop through individual detector efficiencies in 5keV steps, weight them by exposure,
    // and calculate the combined exposure weighted efficiency
    cout << "Beginning bin loop" << endl;
    for(int i = 0; i < 20; i++)
    {
        cout << "Beginning detector loop" << endl;
        for(int j = 0; j < 2; i++)
        {
            eff[j][i] = geff1->Eval(i*5);
            //eff2[i] = geff2->Eval(i*5);
            errhi[j][i] = geff1->GetErrorYhigh(i*5);
            errlow[j][i] = geff1->GetErrorYlow(i*5);
            effSum[i] = effSum[i] + (LT*M[j]*eff[j][i]);
            // Calculate error bars using propagation of erros, ignoring uncertainty on exposure for simplicity
            errSumhi[i] = errSumhi[i] + (((errhi[j][i]-eff[j][i])*M[j]*LT)*((errhi[j][i]-eff[j][i])*M[j]*LT));
	    errSumlow[i] = errSumlow[i] + (((eff[j][i]-errlow[j][i])*M[j]*LT)*((eff[j][i]-errlow[j][i])*M[j]*LT));
            x[i] = i*5;
            xerr[i] = 0;
        }
    }
    
    cout << "Loop ended" << endl;
    f1->Close();
    //f2->Close();
    cout << "Data files closed" << endl;

    // Create output file to store combined efficiency
    string outFile = "ClopperErrorDS1Combined_Alt.root";
    TFile *f3 = new TFile(outFile.c_str(),"recreate");
    cout << "Creating outpout file" <<  endl;
    f3->cd();

    // Graph the combined uncertainty
    cout << "Creating new TGraph" << endl;
    TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, errSumlow, errSumhi);
    //TCanvas *c2 = new TCanvas("c2","c2",800,600);
    geffSum->SetMarkerStyle(21);
    geffSum->SetMarkerColor(kRed);
    geffSum->SetTitle("DS1 ch 578+580 efficiency weighted exposure");
    geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
    geffSum->GetYaxis()->SetTitle("eff wt expos (1/kg*d)");
    ////geffSum->Draw("AP");
    geffSum->Write();
    f3->Close();
    cout << "Finished" << endl;
  }

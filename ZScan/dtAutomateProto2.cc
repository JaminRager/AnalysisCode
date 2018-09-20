//
//  dtAutomateProto2.cc
//
//  Created by Jamin on 4/27/16.
//
//  Accompanies dtAutomateProto1.cc but calculates RMS of DrifT after final
//  setting of range so you can see what you are taking the mean of.

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <stdlib.h>

#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"

#include "GATDataSet.hh"
#include <string>

int main(int argc, char *argv[])
{
    std::cout << "Calculating drift times..." << std::endl;
    
    // Find datasets.
    if(argc != 2) {
        std::cout << "Need 1 argument to give run number!" << std::endl;
        std::cout << "Usage: dtAutomate Run#" << std::endl;
        return 0;
    }
    
    // Data file
    std::string dataFileName;

    // File where histograms will be saved
    std::string outFileName;
    
    // Directory where data is found.
    std::string dataPath("/global/u1/j/jrager/ZScan/firstRun/D2/");

    // Directory where file will be saved. Change this to your own directory.
    std::string savePath("/global/u1/j/jrager/ZScan/firstRun/D2/RMS/hists/largeRange/250mw/");
    
    // Load the set of data files given in command line.
    dataFileName = dataPath + "dt" + std::string(argv[1]) + ".root";
    TFile *dataFile = new TFile(dataFileName.c_str());
    TH1D *DriftT = (TH1D*)dataFile->Get("DriftT");  //is this line even necessary?
   
    // Create root file for zoomed DriftT histograms.
    outFileName = savePath + "dtZoomed" + std::string(argv[1]) + ".root";
    std::cout << "Output will be written to file " << outFileName << std::endl;
    TFile f1(outFileName.c_str(), "RECREATE");
    f1.cd();

    // .csv file where data is stored
    std::ofstream ofs;
    ofs.open ("250rms.csv", std::ofstream::out | std::ofstream::app);
    
    std::cout << "Processing file " + dataFileName << std::endl;
    std::cout << "Processing run " << argv[1] <<std::endl;
    
    double xmin = 0;
    double xmax = 2300;
    double center;
    double bmin;
    double bmax;
    double bcenter;
    double rms;
    double leftSum;
    double rightSum;
    double minWindow = 250;
    TAxis *axis = DriftT->GetXaxis();


    
    do {
        center = xmin + (xmax - xmin)/2;
        bmin = axis->FindBin(xmin);
        bmax = axis->FindBin(xmax);
        bcenter = axis->FindBin(center);
        
        axis->SetRange(bmin,bmax);
        rms = DriftT->GetRMS();
        
        leftSum = DriftT->Integral(bmin,bcenter);
        rightSum = DriftT->Integral(bcenter,bmax);
        
        if (leftSum > rightSum) {
            xmax = center;
        }
        
        if (leftSum < rightSum) {
            xmin = center;
        }
        
        else if (leftSum == rightSum) {
            break;
            std::cout << "Error: could not resolve peak from background." << std::endl;
        }
    } while ((xmax-xmin) > minWindow);
    
    ofs << rms << "\n";
    DriftT->Write();
    ofs.close();
    std::cout << "Done writing, closing file." << std::endl;
    f1.Close();

    std::cout << "Done!" << std::endl;
    
    return 0;
    
}

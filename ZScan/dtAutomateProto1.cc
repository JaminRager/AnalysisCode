//
//  dtAutomateProto1.cpp
//
//  Created by Jamin on 4/15/16.
//
//  Automates drift time calculation.

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
    
    // Directory where data is found.
    std::string dataPath("/global/u1/j/jrager/ZScan/firstRun/D2/");
    
    // Load the set of data files given in command line.
    dataFileName = dataPath + "dt" + std::string(argv[1]) + ".root";
    TFile *dataFile = new TFile(dataFileName.c_str());
    TH1D *DriftT = (TH1D*)dataFile->Get("DriftT");  //is this line even necessary?
    std::ofstream ofs;
    ofs.open ("250.csv", std::ofstream::out | std::ofstream::app);
    
    std::cout << "Processing file " + dataFileName << std::endl;
    std::cout << "Processing run " << argv[1] <<std::endl;
    
    double xmin = 0;
    double xmax = 2300;
    double center;
    double bmin;
    double bmax;
    double bcenter;
    double mean;
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
        mean = DriftT->GetMean();
        
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
    
    ofs << mean << "\n";
    ofs.close();
    
    return 0;
    
}

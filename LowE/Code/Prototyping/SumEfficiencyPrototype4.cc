//
//  SumEfficiencyPrototype.cpp
//  
//  Adds individual detector efficiencies together into single efficiency weighted exposure
//
//  Created by Jamin on 2/27/19.
//

#include <stdio.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <numeric>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include "TEntryList.h"
#include "TProfile.h"
#include "TColor.h"
#include "TLegend.h"
#include "TLine.h"

#include <TROOT.h>
#include <TStyle.h>

#include "GATDataSet.hh"

using namespace std;

int main()
{

// Info file
string info_file = "det_info_lowE.txt";
cout << "det_info file loaded" << endl;

// maps of detector mass, detector livetime, detector efficiency TFile, detector efficiency TGraph
std::map<int, double> det_mass;
std::map<int, double> det_mass_err;
std::map<int, double> det_lt;
std::map<int, TFile*> f;
std::map<int, TGraphAsymmErrors*> geff;
cout << "detector mass and livetime maps created" << endl;

// Variables to assign to info file columns
int idx, ds, chan, cpd;
string serial_num;
double mass, mass_err, lt;
// buffer stuff for file name
int n,m;
string path;
char buffer1[50];
char buffer2[50];
cout << "map variables initialized" << endl;
    
ifstream infile(info_file);
while (infile >> idx >> ds >> cpd >> chan >> serial_num >> mass >> mass_err >> lt)
{
    det_mass[idx] = mass/1000;
    det_mass_err[idx] = mass_err/1000;
    det_lt[idx] = lt;
    n = sprintf(buffer1,"%i",ds);
    m = sprintf(buffer2,"%i",chan);
    path = std::string("~/LowE/Data/IndivEfficiencies/ClopperErrorDS") + buffer1 + "Ch" + buffer2 + ".root";
    f[idx] = new TFile(path.c_str());
    geff[idx] = (TGraphAsymmErrors*)f[idx]->Get("Graph");
}
cout << "mass, livetime, TFile, and TGraph maps filled" << endl;

// chop these up into smaller arrays!
double eff12[29][20] = {{}};
double eff34[22][20] = {{}};
//double eff5b[38][20] = {{}};
//double eff5c[34][20] = {{}};
//double eff6[35][20] = {{}};
double errHi12[7][20] = {{}};
double errHi34[8][20] = {{}};
//double errHi12[29][20] = {{}};
//double errHi34[22][20] = {{}};
//double errHi5b[38][20] = {{}};
//double errHi5c[34][20] = {{}};
//double errHi6[35][20] = {{}};
double errLow12[29][20] = {{}};
double errLow34[22][20] = {{}};
double effSum12[20] = {};
double effSum34[20] = {};
double errSumHi12[20] = {};
double errSumHi34[20] = {};
double errSumLow12[20] = {};
double errSumLow34[20] = {};
double effSumTot[20] = {};
double errSumHiSqrt[20] = {};
double errSumLowSqrt[20] = {};
double x[20] = {};
double xerr[20] = {};
cout << "arrays initialized" << endl;

for(int i = 0; i < 20; i++){
    for(int j = 0; j < 7; j++){
        eff12[j][i] = geff[j]->Eval(i*5);
        errHi12[j][i] = geff[j]->GetErrorYhigh(i);
        errLow12[j][i] = geff[j]->GetErrorYlow(i);
        cout << "eff[j][i], errHi[j][i], errLow[j][i], " << j << ", " << i << ", " << eff12[j][i]  << " " << errHi12[j][i] << " " << errLow12[j][i] << " det_mass[j], " << det_mass[j] << endl;
        effSum12[i] = effSum12[i] + (eff12[j][i]*det_mass[j]*det_lt[j]);
        errSumHi12[i] = errSumHi12[i] + ((errHi12[j][i]*det_mass[j]*det_lt[j])*(errHi12[j][i]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*eff12[j][i]*det_lt[j])*(det_mass_err[j]*eff12[j][i]*det_lt[j]));
        errSumLow12[i] = errSumLow12[i] + ((errLow12[j][i]*det_mass[j]*det_lt[j])*(errLow12[j][i]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*eff12[j][i]*det_lt[j])*(det_mass_err[j]*eff12[j][i]*det_lt[j]));
	
    }
    for(int j = 7; j < 15; j++){
        eff34[j-7][i] = geff[j]->Eval(i*5);
        errHi34[j-7][i] = geff[j]->GetErrorYhigh(i);
        errLow34[j-7][i] = geff[j]->GetErrorYlow(i);
        cout << "eff[j][i], errHi[j][i], errLow[j][i], " << j << ", " << i << ", " << eff34[j-7][i]  << " " << errHi34[j-7][i] << " " << errLow34[j-7][i] << " det_mass[j], " << det_mass[j] << endl;
        effSum34[i] = effSum34[i] + (eff34[j-7][i]*det_mass[j]*det_lt[j]);
        errSumHi34[i] = errSumHi34[i] + ((errHi34[j-7][i]*det_mass[j]*det_lt[j])*(errHi34[j-7][i]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*eff34[j-7][i]*det_lt[j])*(det_mass_err[j]*eff34[j-7][i]*det_lt[j]));
        errSumLow34[i] = errSumLow34[i] + ((errLow34[j-7][i]*det_mass[j]*det_lt[j])*(errLow34[j-7][i]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*eff34[j-7][i]*det_lt[j])*(det_mass_err[j]*eff34[j-7][i]*det_lt[j]));
        
    }
    effSumTot[i] = effSum12[i] + effSum34[i];
    errSumHiSqrt[i] = sqrt(errSumHi12[i] + errSumHi34[i]);
    errSumLowSqrt[i] = sqrt(errSumLow12[i] + errSumLow34[i]);
    x[i] = i*5;
    cout << "x[i]" << x[i] << endl;
    xerr[i] = 0;
}
cout << "Loop through data points and map indices" << endl;

string outFile = "~/LowE/Code/Prototyping/Prototype4.root";
TFile *f0 = new TFile(outFile.c_str(),"recreate");
cout << "Creating outpout file" <<  endl;
f0->cd();

cout << "Creating new TGraph" << endl;
TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSumTot, xerr, xerr, errSumLowSqrt, errSumHiSqrt);
geffSum->SetMarkerStyle(21);
geffSum->SetMarkerColor(kRed);
geffSum->SetTitle("DS1 efficiency weighted exposure");
geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
geffSum->GetYaxis()->SetTitle("eff wt expos (kg*d)");
geffSum->Write();
f0->Close();
    
cout << "Finished" << endl;

}

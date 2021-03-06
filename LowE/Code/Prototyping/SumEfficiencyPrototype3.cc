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

//int no_of_cols = 20;
//int no_of_rows = 14;
//int initial_value = 0;

std::vector<std::vector<double>> eff;
//eff->resize(no_of_rows, std::vector<double>(no_of_cols, initial_value));
std::vector<std::vector<double>> errHi;
//errHi->resize(no_of_rows, std::vector<double>(no_of_cols, initial_value));
std::vector<std::vector<double>> errLow;
//errLow->resize(no_of_rows, std::vector<double>(no_of_cols, initial_value));
cout << "pointers to vectors initialized" << endl;

//Chop these up into smaller arrays!
//double eff[158][20] = {{}};
//double errHi[158][20] = {{}};
//double errLow[158][20] = {{}};
double effSum[20] = {};
double errSumHi[20] = {};
double errSumLow[20] = {};
double errSumHiSqrt[20] = {};
double errSumLowSqrt[20] = {};
double x[20] = {};
double xerr[20] = {};
cout << "arrays initialized" << endl;

//double a = 0;
//double b = 0;
//double c = 0;
cout << "initialized placeholders" << endl;

for(int i = 0; i < 20; i++){
    eff.push_back(std::vector<double>());
    errHi.push_back(std::vector<double>());
    errLow.push_back(std::vector<double>());
    cout << "first loop" << endl;
    for(int j = 0; j < 15; j++){
        eff[i].push_back(j);
	errHi[i].push_back(j);
	errLow[i].push_back(j);
	cout << "push_back 2D vectors" << endl;
	eff[i][j] = geff[j]->Eval(i*5);
	errHi[i][j] = geff[j]->GetErrorYhigh(i);
	errLow[i][j] = geff[j]->GetErrorYlow(i);
	cout << "vector indices set" << endl;
        cout << "eff[i][j], errHi[i][j], errLow[i][j], " << i << ", " << j << ", " << eff[i][j]  << " " << errHi[i][j] << " " << errLow[i][j] << endl;
        effSum[i] = effSum[i] + (eff[i][j]*det_mass[j]*det_lt[j]);
        errSumHi[i] = errSumHi[i] + ((errHi[i][j]*det_mass[j]*det_lt[j])*(errHi[i][j]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*eff[i][j]*det_lt[j])*(det_mass_err[j]*eff[i][j]*det_lt[j]));
        errSumLow[i] = errSumLow[i] + ((errLow[i][j]*det_mass[j]*det_lt[j])*(errLow[i][j]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*eff[i][j]*det_lt[j])*(det_mass_err[j]*eff[i][j]*det_lt[j]));
	cout << "arithmetic" << endl;
	
    }
    errSumHiSqrt[i] = sqrt(errSumHi[i]);
    errSumLowSqrt[i] = sqrt(errSumLow[i]);
    x[i] = i*5;
    cout << "x[i]" << x[i] << endl;
    xerr[i] = 0;
}
cout << "Loop through data points and map indices" << endl;

string outFile = "~/LowE/Code/Prototyping/CombinedEffDS1.root";
TFile *f0 = new TFile(outFile.c_str(),"recreate");
cout << "Creating outpout file" <<  endl;
f0->cd();

cout << "Creating new TGraph" << endl;
TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, errSumLowSqrt, errSumHiSqrt);
geffSum->SetMarkerStyle(21);
geffSum->SetMarkerColor(kRed);
geffSum->SetTitle("DS1 efficiency weighted exposure");
geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
geffSum->GetYaxis()->SetTitle("eff wt expos (kg*d)");
geffSum->Write();
f0->Close();
    
cout << "Finished" << endl;

}

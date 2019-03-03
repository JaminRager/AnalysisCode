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
    
ifstream infile(info_file);
while (infile >> idx >> ds >> cpd >> chan >> serial_num >> mass >> mass_err >> lt)
{
    det_mass[idx] = mass;
    det_mass_err[idx] = mass_err
    det_lt[idx] = lt;
    n = sprintf(buffer1,"%i",ds);
    m = sprintf(buffer2,"%i",chan);
    path = std::string("~/LowE/Data/IndivEfficiencies/ClopperErrorDS") + buffer1 + "Ch" + buffer2 + ".root";
    f[idx] = new TFile(path.c_str());
    geff[idx] = (TGraphAsymmErrors*)f[idx]->Get("Graph");
}
cout << "mass, livetime, TFile, and TGraph maps filled" << endl;
    
double *eff[15][20] = {{}};
double *errHi[15][20] = {{}};
double *errLow[15][20] = {{}};
double effSum[20] = {};
double sumErrHi[20] = {};
double sumSumLow[20] = {};
double x[20] = {};
double xerr[20] = {};
cout << "arrays initialized" << endl;

for(int i = 0; i < 20; i++){
    for(int j = 0; j < 15; j++){
        (*eff)[j][i] = geff[j]->Eval(i*5);
        cout << "eff[j][i], " << j << ", " << i << ", " << (*eff)[j][i] << endl;
        effSum[i] = effSum[i] + ((*eff)[j][i] * det_mass[j] * det_lt[j]);
        sumErrHi[i] = sqrt(sumErrHi[i] + (((*errHi)[j][i]*det_mass[j]*det_lt[j])*((*errHi)[j][i]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*(*eff)[j][i]*det_lt[j])*(det_mass_err[j]*(*eff)[j][i]*det_lt[j])));
        sumErrLow[i] = sqrt(sumErrLow[i] + (((*errLow)[j][i]*det_mass[j]*det_lt[j])*((*errLow)[j][i]*det_mass[j]*det_lt[j])) + ((det_mass_err[j]*(*eff)[j][i]*det_lt[j])*(det_mass_err[j]*(*eff)[j][i]*det_lt[j])));
	
    }
    x[i] = i*5;
    cout << "x[i]" << x[i] << endl;
    xerr[i] = 0;
}
cout << "Loop through data points and map indices" << endl;

string outFile = "~/LowE/Code/Prototyping/CombinedEffPrototype3.root";
TFile *f0 = new TFile(outFile.c_str(),"recreate");
cout << "Creating outpout file" <<  endl;
f0->cd();

cout << "Creating new TGraph" << endl;
TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, effErr, effErr);
geffSum->SetMarkerStyle(21);
geffSum->SetMarkerColor(kRed);
geffSum->SetTitle("DS1 efficiency weighted exposure");
geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
geffSum->GetYaxis()->SetTitle("eff wt expos (kg*d)");
geffSum->Write();
f0->Close();
    
cout << "Finished" << endl;

}

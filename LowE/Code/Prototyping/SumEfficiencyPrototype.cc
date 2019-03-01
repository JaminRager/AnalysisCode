//
//  SumEfficiencyPrototype.cpp
//  
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

string info_file = "det_info_proto.txt";
cout << "det_info file loaded" << endl;

std::map<int, double> det_mass;
std::map<int, double> det_lt;
 cout << "detector mass and livetime maps created" << endl;

int idx, ds, chan, cpd;
string serial_num;
double mass, mass_unc, lt;

ifstream infile(info_file);
while (infile >> idx >> ds >> cpd >> chan >> serial_num >> mass >> mass_unc >> lt)
{
    det_mass[idx] = mass;
    det_lt[idx] = lt;
}
cout << "massa and livetimes maps filled" << endl;

std::map <int, TGraphAsymmErrors*> geff_map;
 cout << "map of TGraphs" << endl;

TFile *f1 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch592.root");
TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
TFile *f2 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch594.root");
TGraphAsymmErrors *geff2 = (TGraphAsymmErrors*)f2->Get("Graph");
cout << "Data files loaded" << endl;

geff_map.insert(std::pair<int,TGraphAsymmErrors*>(0,geff1));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(1,geff2));
cout << "map of TGraphs filled" << endl;

double eff[2][20] = {{}};
//double** eff = new double*[2];
//for (int i = 0; i < 20; i++){
  //eff[i] = new double[20];
//}
double effSum[20] = {};
double effErr[20] = {};
double x[20] = {};
double xerr[20] = {};
cout << "arrays initialized" << endl;

for(int i = 0; i < 20; i++){
    for(int j = 0; j < 2; j++){
        eff[j][i] = geff_map[j]->Eval(i*5);
	cout << "eff[j][i], " << j << ", " << i << ", " << eff[j][i] << endl;
        effSum[i] = effSum[i] + (eff[j][i] * det_mass[j] * det_lt[j]);
	//cout << "det_mass[j]" << det_mass[j] << endl;
	//cout << "det_lt[j]" << det_lt[j] << endl;
	//cout << "effSum[j]" << effSum[j] << endl;
    }
    x[i] = i*5;
    cout << "x[i]" << x[i] << endl;
    xerr[i] = 0;
    effErr[i] = 0;
}
cout << "Loop through data points and map indices" << endl;


f1->Close();
f2->Close();
cout << "Data files closed" << endl;

string outFile = "~/LowE//Code/Prototyping/CombinedEffPrototype.root";
TFile *f0 = new TFile(outFile.c_str(),"recreate");
cout << "Creating outpout file" <<  endl;
f0->cd();

cout << "Creating new TGraph" << endl;
TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, effErr, effErr);
//TGraph *geffSum =  new TGraph(20,x,effSum);
//TCanvas *c2 = new TCanvas("c2","c2",800,600);
geffSum->SetMarkerStyle(21);
geffSum->SetMarkerColor(kRed);
geffSum->SetTitle("DS1 efficiency weighted exposure");
geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
geffSum->GetYaxis()->SetTitle("eff wt expos (kg*d)");
//geffSum->Draw("AP");
geffSum->Write();
f0->Close();
    
cout << "Finished" << endl;

}

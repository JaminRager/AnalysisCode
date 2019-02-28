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

int main()
{

string info_file = "det_info_proto.txt";

using namespace std;

std::map<int, double> det_mass;
std::map<int, double> det_lt;

int idx, ds, chan;
double mass, mass_unc, lt;

ifstream infile(info_file);
while (infile >> idx >> ds >> cpd >> chan >> serial_num >> act_mass >> act_mass_unc >> lt)
{
    det_mass[idx] = mass;
    det_lt[idx] = lt;
}

std::map <int, TGraphAsymmErrors*> geff_map;

TFile *f1 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch592.root");
TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
TFile *f2 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch594.root");
TGraphAsymmErrors *geff2 = (TGraphAsymmErrors*)f2->Get("Graph");

geff_map.insert(std::pair<int,TGraphAsymmErrors*>(0,*geff1));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(1,*geff2));

double eff[2][20] = {{}};
double effSum[20] = {};
double effErr[20] = {};
double x[20] = {};
double xerr[20] = {};

for(int i = 0; i < 20; i++){
    for(int j = 0; j < 2; j++){
        eff[j][i] = geff_map[j]->Eval(i*5);
        effsum[i] = effsum[i] + (eff[j][i] * det_mass[i] * det_lt[i]);
        effErr[j][i] = 0;
    }
    x[i] = i*5;
    xerr[i] = 0;
    effErr[i] = 0;
}

cout << "Loop ended" << endl;

f1->Close();
f2->Close();
cout << "Data files closed" << endl;

string outFile = "~/LowE/";
TFile *f0 = new TFile(outFile.c_str(),"recreate");
cout << "Creating outpout file" <<  endl;
f0->cd();

cout << "Creating new TGraph" << endl;
TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, effErr, effErr);
//TGraph *geffSum =  new TGraph(20,x,effSum);
TCanvas *c2 = new TCanvas("c2","c2",800,600);
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

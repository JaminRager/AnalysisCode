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

// Info file
string info_file = "det_info_proto.txt";
cout << "det_info file loaded" << endl;

// maps of detector mass, detector livetime, detector efficiency TFile, detector efficiency TGraph
std::map<int, double> det_mass;
std::map<int, double> det_lt;
std::map<int, TFile*> f;
std::map<int, TGraphAsymmErrors*> geff;

 cout << "detector mass and livetime maps created" << endl;

// Variables to assign to info file columns
int idx, ds, chan, cpd;
string serial_num;
double mass, mass_unc, lt;
// buffer stuff for file name
int n,m;
string path;
char buffer1[50];
char buffer2[50];
    
//string path1 = "~/LowE/Data/IndivEfficiencies/ClopperErrorDS";
//string path2 = "Ch";
//string path2 = ".root";
    
ifstream infile(info_file);
while (infile >> idx >> ds >> cpd >> chan >> serial_num >> mass >> mass_unc >> lt)
{
    det_mass[idx] = mass;
    det_lt[idx] = lt;
    n = sprintf(buffer1,"%i",ds);
    m = sprintf(buffer2,"%i",chan);
    path = "~/LowE/Data/IndivEfficiencies/ClopperErrorDS" + n + "Ch" + m +".root"
    f[idx] = new TFile(path.c_str());
    geff[idx] = (TGraphAsymmErrors*)f[idx]->Get("Graph");
}
cout << "mass, livetime, TFile, and TGraph maps filled" << endl;

//std::map <int, TGraphAsymmErrors*> geff_map;
//cout << "map of TGraphs" << endl;

// I could have made the f1,f2... into a vector, the same with g, then use something like argc argv to loop through det_info_lowE.txt
//TFile *f1 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch592.root");
//TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
//TFile *f2 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch594.root");
//TGraphAsymmErrors *geff2 = (TGraphAsymmErrors*)f2->Get("Graph");

    
// I have a total of 158 of these.  That's a lot to type.  Would be nice if I could use some kind of loop to open them.  Like a while loop of for loop.
    
//cout << "Data files loaded" << endl;

// Same here, would be nice if I could assign all these with a loop
// If geff was a vector, this would be easy with a for loop
//geff_map.insert(std::pair<int,TGraphAsymmErrors*>(0,geff1));
//geff_map.insert(std::pair<int,TGraphAsymmErrors*>(1,geff2));

    
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
    for(int j = 0; j < 15; j++){
        eff[j][i] = geff[j+1]->Eval(i*5);
	cout << "eff[j][i], " << j << ", " << i << ", " << eff[j][i] << endl;
        effSum[i] = effSum[i] + (eff[j][i] * det_mass[j+1] * det_lt[j+1]);
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

string outFile = "~/LowE/Code/Prototyping/CombinedEffPrototype3.root";
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

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

// I could have made the f1,f2... into a vector, the same with g, then use something like argc argv to loop through det_info_lowE.txt
TFile *f1 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch592.root");
TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
TFile *f2 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch594.root");
TGraphAsymmErrors *geff2 = (TGraphAsymmErrors*)f2->Get("Graph");
TFile *f3 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch608.root");
TGraphAsymmErrors *geff3 = (TGraphAsymmErrors*)f3->Get("Graph");
TFile *f4 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch632.root");
TGraphAsymmErrors *geff4 = (TGraphAsymmErrors*)f4->Get("Graph");
TFile *f5 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch580.root");
TGraphAsymmErrors *geff5 = (TGraphAsymmErrors*)f5->Get("Graph");
TFile *f6 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch578.root");
TGraphAsymmErrors *geff6 = (TGraphAsymmErrors*)f6->Get("Graph");
TFile *f7 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch672.root");
TGraphAsymmErrors *geff7 = (TGraphAsymmErrors*)f7->Get("Graph");
TFile *f8 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch664.root");
TGraphAsymmErrors *geff8 = (TGraphAsymmErrors*)f8->Get("Graph");
TFile *f9 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch648.root");
TGraphAsymmErrors *geff9 = (TGraphAsymmErrors*)f9->Get("Graph");
TFile *f10 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch610.root");
TGraphAsymmErrors *geff10 = (TGraphAsymmErrors*)f10->Get("Graph");
TFile *f11 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch598.root");
TGraphAsymmErrors *geff11 = (TGraphAsymmErrors*)f11->Get("Graph");
TFile *f12 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch690.root");
TGraphAsymmErrors *geff12 = (TGraphAsymmErrors*)f12->Get("Graph");
TFile *f13 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch582.root");
TGraphAsymmErrors *geff13 = (TGraphAsymmErrors*)f13->Get("Graph");
TFile *f14 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch640.root");
TGraphAsymmErrors *geff14 = (TGraphAsymmErrors*)f14->Get("Graph");
TFile *f15 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch626.root");
TGraphAsymmErrors *geff15 = (TGraphAsymmErrors*)f15->Get("Graph");
TFile *f16 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch592.root");
TGraphAsymmErrors *geff16 = (TGraphAsymmErrors*)f16->Get("Graph");
TFile *f17 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch608.root");
TGraphAsymmErrors *geff17 = (TGraphAsymmErrors*)f17->Get("Graph");
TFile *f18 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch632.root");
TGraphAsymmErrors *geff18 = (TGraphAsymmErrors*)f18->Get("Graph");
TFile *f19 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch580.root");
TGraphAsymmErrors *geff19 = (TGraphAsymmErrors*)f19->Get("Graph");
TFile *f20 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch578.root");
TGraphAsymmErrors *geff20 = (TGraphAsymmErrors*)f20->Get("Graph");
TFile *f21 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch672.root");
TGraphAsymmErrors *geff21 = (TGraphAsymmErrors*)f21->Get("Graph");
TFile *f22 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch664.root");
TGraphAsymmErrors *geff22 = (TGraphAsymmErrors*)f22->Get("Graph");
TFile *f23 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch648.root");
TGraphAsymmErrors *geff23 = (TGraphAsymmErrors*)f23->Get("Graph");
TFile *f24 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch610.root");
TGraphAsymmErrors *geff24 = (TGraphAsymmErrors*)f24->Get("Graph");
TFile *f25 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch598.root");
TGraphAsymmErrors *geff25 = (TGraphAsymmErrors*)f25->Get("Graph");
TFile *f26 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch690.root");
TGraphAsymmErrors *geff26 = (TGraphAsymmErrors*)f26->Get("Graph");
TFile *f27 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch582.root");
TGraphAsymmErrors *geff27 = (TGraphAsymmErrors*)f27->Get("Graph");
TFile *f28 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch626.root");
TGraphAsymmErrors *geff28 = (TGraphAsymmErrors*)f28->Get("Graph");
TFile *f29 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS2Ch626.root");
TGraphAsymmErrors *geff29 = (TGraphAsymmErrors*)f29->Get("Graph");
TFile *f30 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch592.root");
TGraphAsymmErrors *geff30 = (TGraphAsymmErrors*)f30->Get("Graph");
TFile *f31 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch594.root");
TGraphAsymmErrors *geff31 = (TGraphAsymmErrors*)f31->Get("Graph");
TFile *f32 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch608.root");
TGraphAsymmErrors *geff32 = (TGraphAsymmErrors*)f32->Get("Graph");
TFile *f33 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch632.root");
TGraphAsymmErrors *geff33 = (TGraphAsymmErrors*)f33->Get("Graph");
TFile *f34 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch580.root");
TGraphAsymmErrors *geff34 = (TGraphAsymmErrors*)f34->Get("Graph");
TFile *f35 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch578.root");
TGraphAsymmErrors *geff35 = (TGraphAsymmErrors*)f35->Get("Graph");
TFile *f36 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch672.root");
TGraphAsymmErrors *geff36 = (TGraphAsymmErrors*)f36->Get("Graph");
TFile *f37 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch664.root");
TGraphAsymmErrors *geff37 = (TGraphAsymmErrors*)f37->Get("Graph");
TFile *f38 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch648.root");
TGraphAsymmErrors *geff38 = (TGraphAsymmErrors*)f38->Get("Graph");
TFile *f39 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch678.root");
TGraphAsymmErrors *geff39 = (TGraphAsymmErrors*)f39->Get("Graph");
TFile *f40 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch610.root");
TGraphAsymmErrors *geff40 = (TGraphAsymmErrors*)f40->Get("Graph");
TFile *f41 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch598.root");
TGraphAsymmErrors *geff41 = (TGraphAsymmErrors*)f41->Get("Graph");
TFile *f42 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch690.root");
TGraphAsymmErrors *geff42 = (TGraphAsymmErrors*)f42->Get("Graph");
TFile *f43 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch582.root");
TGraphAsymmErrors *geff43 = (TGraphAsymmErrors*)f43->Get("Graph");
TFile *f44 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch640.root");
TGraphAsymmErrors *geff44 = (TGraphAsymmErrors*)f44->Get("Graph");
TFile *f45 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS3Ch626.root");
TGraphAsymmErrors *geff45 = (TGraphAsymmErrors*)f45->Get("Graph");
    
    
    
    
    
    
    
    
    
// I have a total of 158 of these.  That's a lot to type.  Would be nice if I could use some kind of loop to open them.  Like a while loop of for loop.
    
cout << "Data files loaded" << endl;

// Same here, would be nice if I could assign all these with a loop
// If geff was a vector, this would be easy with a for loop
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(0,geff1));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(1,geff2));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(2,geff3));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(3,geff4));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(4,geff5));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(5,geff6));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(6,geff7));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(7,geff8));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(8,geff9));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(9,geff10));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(10,geff11));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(11,geff12));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(12,geff13));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(13,geff14));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(14,geff15));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(15,geff16));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(16,geff17));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(17,geff18));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(18,geff19));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(19,geff20));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(20,geff21));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(21,geff22));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(22,geff23));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(23,geff24));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(24,geff25));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(25,geff26));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(26,geff27));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(27,geff28));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(28,geff29));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(29,geff30));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(30,geff31));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(31,geff32));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(32,geff33));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(33,geff34));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(34,geff35));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(35,geff36));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(36,geff37));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(37,geff38));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(38,geff39));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(39,geff40));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(40,geff41));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(41,geff42));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(42,geff43));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(43,geff44));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(44,geff45));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(45,geff46));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(46,geff47));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(47,geff48));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(48,geff49));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(49,geff45));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(50,geff51));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(51,geff52));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(52,geff53));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(53,geff54));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(54,geff55));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(55,geff56));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(56,geff57));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(57,geff58));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(58,geff59));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(59,geff60));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(60,geff61));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(61,geff62));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(62,geff63));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(63,geff64));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(64,geff65));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(65,geff66));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(66,geff67));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(67,geff68));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(68,geff69));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(69,geff70));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(70,geff71));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(71,geff72));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(72,geff73));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(73,geff74));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(74,geff75));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(75,geff76));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(76,geff77));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(77,geff78));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(78,geff79));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(79,geff80));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(80,geff81));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(81,geff82));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(82,geff83));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(83,geff84));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(84,geff85));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(85,geff86));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(86,geff81));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(87,geff88));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(88,geff89));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(89,geff90));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(90,geff91));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(91,geff92));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(92,geff93));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(93,geff94));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(94,geff95));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(95,geff96));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(96,geff97));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(97,geff98));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(98,geff99));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(99,geff100));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(100,geff101));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(101,geff102));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(102,geff103));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(103,geff104));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(104,geff105));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(105,geff106));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(106,geff107));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(107,geff108));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(108,geff109));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(109,geff110));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(110,geff111));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(111,geff112));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(112,geff113));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(113,geff114));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(114,geff115));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(115,geff116));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(116,geff117));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(117,geff118));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(118,geff119));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(119,geff120));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(120,geff121));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(121,geff122));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(122,geff123));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(123,geff124));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(124,geff125));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(125,geff126));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(126,geff127));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(127,geff128));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(128,geff129));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(129,geff130));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(130,geff131));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(131,geff132));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(132,geff133));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(133,geff134));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(134,geff135));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(135,geff136));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(136,geff137));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(137,geff138));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(138,geff139));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(139,geff140));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(140,geff141));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(141,geff142));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(142,geff143));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(143,geff144));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(144,geff145));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(145,geff146));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(146,geff147));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(147,geff148));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(148,geff149));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(149,geff150));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(150,geff151));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(151,geff152));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(152,geff153));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(153,geff154));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(154,geff155));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(155,geff156));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(156,geff157));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(157,geff158));
geff_map.insert(std::pair<int,TGraphAsymmErrors*>(158,geff159));
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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

//  LiveTimeSacrifice.cc
//  Created by Jamin on 1/19/19.

#include <stdio.h>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TH1.h"
#include "TStyle.h"
#include "TEntryList.h"
#include "TH1.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLine.h"
#include <numeric>

#include "DataSetInfo.hh"

using namespace std;

void method_1();
void method_2();
void load_maps();
void method_3();

int main()
{
  // method_1();
  method_2();
  // load_maps();
  // method_3(); // <-- use this one
}

void method_1()
{
  string inFile = "/global/u1/j/jrager/lat/data/ds_5B_livetime.root";

  TFile *f = new TFile(inFile.c_str());
  TTree *dsTree = (TTree*)f->Get("dsTree");

  //std::ofstream out("out.txt");
  //std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
  //std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

  int run;
  vector<int> *channel = 0;
  vector<double> *livetime = 0;
  dsTree->SetBranchAddress("run", &run);
  dsTree->SetBranchAddress("channel", &channel);
  dsTree->SetBranchAddress("livetime", &livetime);
  //vector<int> *ch = 0;
  //vector<double> *lt = 0;
  //int i = 0;

  for(UInt_t iE = 0; iE < dsTree->GetEntries(); iE++)
    {
      dsTree->GetEvent(iE);

      if(iE % 1000 == 1)
	cout << "Processing Event # "  << iE << endl;

      for(UInt_t nhit = 0; nhit < (*channel).size(); nhit++)
        {
	  if (run>=36034 && run<=36047) {
	    int r = run;
	    //(*ch)[i] = (*channel)[nhit];
	    int c = (*channel)[nhit];
	    //(*lt)[i] = (*livetime)[nhit];
	    double l = (*livetime)[nhit];
	    //i = i + 1;
	    cout << "run " << r << " channel " << c << " livetime " << l << endl;

	  }
        }
    }
}

void method_2()
{
  string inFile = "/global/u1/j/jrager/lat/data/ds_5B_livetime.root";
  TFile *f = new TFile(inFile.c_str());
  TTree *dsTree = (TTree*)f->Get("dsTree");

  freopen("output.txt","w",stdout);

  // try a few different cuts here.
  // 36866: last run of ds6a, 43625: last run of ds6b
  string myCut = "(run==22954 || run==22952) && channel==692"; // i find 0 entries after this.
  // string myCut = "";

  int n = dsTree->Draw("run:channel:livetime", myCut.c_str(),"goff");

  cout << Form("Found %i entries passing cut.\n", n);

  // fill these exposures
  // double enr_exp = 0, nat_exp = 0;

  double *runs = dsTree->GetV1();
  double *chans = dsTree->GetV2();
  double *ltimes = dsTree->GetV3();
  for (int i = 0; i < 2; i++)
  {
       // need to add a way to get the detector mass here, preferably a map<int, double>
       int run = (int)runs[i];
       int chan = (int)chans[i];
       double lt = ltimes[i];

       cout << Form("run %i  chan %i  livetime %.2f\n", run, chan, lt);
  }
  for(std::vector<int>::iterator it = ltimes.begin(); it != ltimes.end(); ++it){
    sum_of_elems += *it;
  }

  cout << Form("livetime %.2f\n", ltsum);

}

void load_maps()
{
  // -- load data into maps
  string info_file = "det_info.txt";

  // create lookup maps
  // use a nested map to get: ds, chan, det_mass
  // NOTE: these are not the only maps possible from this input file
  map<int, map<int, double>> det_mass;
  map<int, map<int, double>> det_mass_unc;

  int ds, cpd, chan;
  string serial_num;
  double act_mass, act_mass_unc;

  ifstream infile(info_file);
  while (infile >> ds >> cpd >> chan >> serial_num >> act_mass >> act_mass_unc)
    {
      // cout << Form("%i  %i  %i  %s  %.2f  %.2f\n",
      // ds, cpd, chan, serial_num.c_str(), act_mass, act_mass_unc);
      det_mass[ds][chan] = act_mass;
      det_mass_unc[ds][chan] = act_mass_unc;
    }

  // -- now look up the mass of a channel
  // NOTE: this is what you put in your loop over the livetime file
  ds = 6;
  chan = 662;
  double mass = det_mass[ds][chan];
  cout << Form("Check:  DS %i  chan %i  mass: %.2f g\n", ds, chan, mass);

  // example 2: print the entire map
  //
  // note, we can also loop this way:
  // for (int ds = 0; ds < (int)det_mass.size(); ds++)
  //
  for (auto &map_top : det_mass) {
    ds = map_top.first;
    for (auto &map_2 : det_mass[ds]) {
      chan = map_2.first;
      mass = det_mass[ds][chan];
      cout << Form("ds %i  chan %i  mass %.2f\n", ds, chan, mass);
    }
  }

}

void method_3()
{
  // load maps
  string info_file = "det_info.txt";
  map<int, map<int, double>> det_mass;
  map<int, map<int, double>> det_mass_unc;
  int ds, cpd, chan;
  string serial_num;
  double act_mass, act_mass_unc;
  ifstream infile(info_file);
  while (infile >> ds >> cpd >> chan >> serial_num >> act_mass >> act_mass_unc)
    {
      det_mass[ds][chan] = act_mass;
      det_mass_unc[ds][chan] = act_mass_unc;
    }

  string inFile = "ds_6_livetime.root";
  TFile *f = new TFile(inFile.c_str());
  TTree *dsTree = (TTree*)f->Get("dsTree");

  // try a few different cuts here.
  // 36866: last run of ds6a, 43625: last run of ds6b
  // string myCut = "run > 36866"; // i find 0 entries after this.
  string myCut = "";

  int n = dsTree->Draw("run:channel:livetime", myCut.c_str(),"goff");

  cout << Form("Found %i entries passing cut.\n", n);

  // fill these exposures
  double enr_exp = 0, nat_exp = 0;

  double *runs = dsTree->GetV1();
  double *chans = dsTree->GetV2();
  double *ltimes = dsTree->GetV3();
  for (int i = 0; i < 50; i++)
    {
      int run = (int)runs[i];
      int chan = (int)chans[i];
      double lt = ltimes[i];
      double mass = det_mass[ds][chan]; // <<--- use our map lookup here

      cout << Form("run %i  chan %i  livetime %.2f  mass %.2f\n", run, chan, lt, mass);

      // NOTE: now you can increment enr_exp, and nat_exp, that we declared above.
      // I would proceed by making another map from the given input
      // that allows you to identify if a given channel is enriched or natural,
      // by looking at the detector serial number and checking if it is
      // over 1000000, so 1425730 is tagged as enriched but 28465 is not.
    }


}

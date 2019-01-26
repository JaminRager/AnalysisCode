#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TROOT.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TEntryList.h"
#include "GATDataSet.hh"
#include "TLine.h"
#include <v5/TFormula.h>

using namespace std;

void CutEfficiency1();
void CutEfficiency2();
void CutEfficiency3();

int main()
{
  CutEfficiency1();
  CutEfficiency2();
  CutEfficiency3();
}

char cut3[10000];
char cut2[10000];
char cut1[100000];
char cut0[10000];
char theCut[10000];
char tetmCut[] = "(((channel==632 || channel==1168 || channel==1298) && trapETailMin<0.0) || ((channel==598 || channel==614 || channel==648 || channel==660 || channel==662 || channel==678 || channel==1172) && trapETailMin<0.2) || ((channel==608 || channel==626 || channel==674 || channel==690 || channel==1124) && trapETailMin<0.3) || ((channel==584 || channel==610 || channel==640 || channel==1170 || channel==1208) && trapETailMin<0.4) || ((channel==658 || channel==694 || channel==1106 || channel==1174 || channel==1232 || channel==1232 || channel==1302) && trapETailMin<0.5) || ((channel==1120 ||channel==1176 || channel==1204 || channel==1330 || channel==1332) && trapETailMin<0.6) || (channel==688 && trapETailMin<0.7) || ((channel==592 || channel==624 || channel==680 || channel==692 || channel==1128) && trapETailMin<1.0) || (channel==628 && trapETailMin<1.5))";
char ToE_EDependent[] = "((trapENFCal<9 && ((channel!=660 && kvorrT/trapENFCal>0.87 && kvorrT/trapENFCal<1.95) || (channel==660 && kvorrT/trapENFCal>0.56 && kvorrT/trapENFCal<1.40))) || (trapENFCal>=9 && trapENFCal<20 && ((channel!=660 && kvorrT/trapENFCal>0.94 && kvorrT/trapENFCal<1.84) || (channel==660 && kvorrT/trapENFCal>0.71 && kvorrT/trapENFCal<1.25))) || (trapENFCal>=20 && ((channel!=660 && kvorrT/trapENFCal>1.11 && kvorrT/trapENFCal<1.65) || (channel==660 && kvorrT/trapENFCal>0.82 && kvorrT/trapENFCal<1.12))))";
char HEDetCut[] = "(channel!=664 && channel!=665 && channel!=642 && channel!=643 && channel!=616 && channel!=617 && channel!=600 && channel!=601 && channel!=696 && channel!=697 && channel!=630 && channel!=631 && channel!=1126 && channel!=1127 && channel!=1110 && channel!=1111 && channel!=1108 && channel!=1109 && channel!=1122 && channel!=1123 && channel!=1202 && channel!=1203 && channel!=1206 && channel!=1207 && channel!=1168 && channel!=1169 && channel!=1304 && channel!=1305 && channel!=1296 && channel!=1297 && channel!=1328 && channel!=1329 && channel!=1234 && channel!=1235 && channel!=1268 && channel!=1269 && channel!=1238 && channel!=1239)";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>236.69 && (trapENFCal[0] + trapENFCal[1])<240.13)";
char chan1298[] = "channel==1298";
char chan1236[] = "channel==1236";
char chan1232[] = "channel==1232";

void CutEfficiency1()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5achan1298.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Data files added" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);  //Overwrite the hardcoded root formula length limit to be 2000 char long
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1298);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1298);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 20, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 20, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}
                                                                          
void CutEfficiency2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5achan1236.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Data files added" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1236);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1236);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 20, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 20, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}
                                                                          
void CutEfficiency3()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5achan1232.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Data files added" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1232);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1232);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 20, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 20, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

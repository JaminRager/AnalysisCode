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
#include "TFormula.h"
#include <v5/TFormula.h>

using namespace std;

void CutEfficiency1();
void CutEfficiency2();
void CutEfficiency3();
void CutEfficiency4();
void CutEfficiency5();

int main()
{
  CutEfficiency1();
  CutEfficiency2();
  CutEfficiency3();
  CutEfficiency4();
  CutEfficiency5();
}

char cut3[10000];
char cut2[10000];
char cut1[10000];
char cut0[10000];
char theCut[100000];
char tetmCut[] = "((channel==1296 && trapETailMin<0.0) || (channel==1332 && trapETailMin<0.2) || (channel==1176 && trapETailMin<0.3) || ((channel==1136 || channel==1172 || channel==1174 || channel==1232 || channel==1330) && trapETailMin<0.4) || ((channel==1204 || channel==1236 || channel==1298) && trapETailMin<0.5) || ((channel==1144 || channel==1170) && trapETailMin<0.6) || (channel==1106 && trapETailMin<0.7))";
char ToE_EDependent[] = "((trapENFCal<9 && ((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal>0.91 && kvorrT/trapENFCal<1.81) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal>0.87 && kvorrT/trapENFCal<1.71) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal>0.84 && kvorrT/trapENFCal<1.50) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal>0.68 && kvorrT/trapENFCal<1.40) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal>0.63 && kvorrT/trapENFCal<1.29) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal>1.01 && kvorrT/trapENFCal<1.85) || (run>=60001914 && (channel==1106 || channel==1107 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.85))) || (trapENFCal>=9 && trapENFCal<20 && ((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal>1.06 && kvorrT/trapENFCal<1.66) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal>0.99 && kvorrT/trapENFCal<1.53) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal>0.93 && kvorrT/trapENFCal<1.35) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal>0.78 && kvorrT/trapENFCal<1.26) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal>0.74 && kvorrT/trapENFCal<1.16) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal>1.14 && kvorrT/trapENFCal<1.74) || (run>=60001914 && (channel==1106 || channel==1107 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal>1.01 && kvorrT/trapENFCal<1.67))) || (trapENFCal>=20 && ((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal>1.18 && kvorrT/trapENFCal<1.54) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal>1.09 && kvorrT/trapENFCal<1.39) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal>1.00 && kvorrT/trapENFCal<1.24) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal>0.88 && kvorrT/trapENFCal<1.18) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal>0.82 && kvorrT/trapENFCal<1.06) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal>1.21 && kvorrT/trapENFCal<1.69) || (run>=60001914 && (channel==1106 || channel==1107 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal>1.14 && kvorrT/trapENFCal<1.56))))";
char HEDetCut[] = "(channel!=1140 && channel!=1141 && channel!=1142 && channel!=1143 && channel!=1110 && channel!=1111 && channel!=1108 && channel!=1109 && channel!=1138 && channel!=1139 && channel!=1202 && channel!=1203 && channel!=1208 && channel!=1209 && channel!=1206 && channel!=1207 && channel!=1168 && channel!=1169 && channel!=1304 && channel!=1305 && channel!=1302 && channel!=1303 && channel!=1328 && channel!=1329 && channel!=1234 && channel!=1235 && channel!=1268 && channel!=1269 && channel!=1238 && channel!=1239)";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>237.49 && (trapENFCal[0] + trapENFCal[1])<239.67)";
char chan1204[] = "channel==1204";
char chan1174[] = "channel==1174";
char chan1144[] = "channel==1144";
char chan1106[] = "channel==1106";
char chan1176[] = "channel==1176";
char chan1172[] = "channel==1172";
char chan1170[] = "channel==1170";
char chan1136[] = "channel==1136";
char chan1330[] = "channel==1330";
char chan1332[] = "channel==1332";
char chan1296[] = "channel==1296";
char chan1298[] = "channel==1298";
char chan1236[] = "channel==1236";
char chan1232[] = "channel==1232";

void CutEfficiency1()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS4chan1204.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000); // manually overwrite root's hardcoded limit on formula length
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1204);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1204);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS4chan1172.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1172);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1172);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS4chan1170.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1170);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1170);
    
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
                                                                          
void CutEfficiency4()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS4chan1136.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1136);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1136);
    
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
                                                                          
void CutEfficiency5()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS4chan1330.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1330);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1330);
    
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

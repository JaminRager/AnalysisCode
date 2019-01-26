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
void CutEfficiency4();
void CutEfficiency5();
void CutEfficiency6();
                                                                          
int main()
{
  CutEfficiency1();
  CutEfficiency2();
  CutEfficiency3();
  CutEfficiency4();
  CutEfficiency5();
  CutEfficiency6();
}
                                                                          
char cut3[10000];
char cut2[10000];
char cut1[100000];
char cut0[10000];
char theCut[10000];
char tetmCut[] = "(((channel==632 || channel==662) && trapETailMin<0.1) || ((channel==584 || channel==608 || channel==610 || channel==648 || channel==660 || channel==672 || channel==674 || channel==678 || channel==1172) && trapETailMin<0.2) ||  ((channel==598  || channel==640 || channel==658 || channel==680 || channel==690 || channel==692 || channel==694) && trapETailMin<0.3) || ((channel==614 || channel==688 || channel==1174 || channel==1204) && trapETailMin<0.4) || ((channel==592 || channel==626 || channel==1120 || channel==1124 || channel==1170 || channel==1208 || channel==1236 || channel==1298) && trapETailMin<0.5) || ((channel==624 || channel==1176) && trapETailMin<0.6) || ((channel==1106 || channel==1302) && trapETailMin<0.7) || ((channel==1128 || channel==1232) && trapETailMin<0.8) || (channel==1330 && trapETailMin<0.9) || (channel==628 && trapETailMin<1.3))";
char ToE_EDependent[] = "((trapENFCal<9 && ((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal>0.89 && kvorrT/trapENFCal<1.91) || ((channel==660 || channel==1302) && kvorrT/trapENFCal>0.52 && kvorrT/trapENFCal<1.60) || (channel==628 && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.67))) || (trapENFCal>=9 && trapENFCal<20 && ((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal>1.03 && kvorrT/trapENFCal<1.75) || ((channel==660 || channel==1302) && kvorrT/trapENFCal>0.69 && kvorrT/trapENFCal<1.41) || (channel==628 && kvorrT/trapENFCal>0.94 && kvorrT/trapENFCal<1.48))) || (trapENFCal>=20 && ((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal>1.12 && kvorrT/trapENFCal<1.66) || ((channel==660 || channel==1302) && kvorrT/trapENFCal>0.81 && kvorrT/trapENFCal<1.23) || (channel==628 && kvorrT/trapENFCal>1.09 && kvorrT/trapENFCal<1.33))))";
char HEDetCut[] = "channel!=664 && channel!=665 && channel!=642 && channel!=643 && channel!=616 && channel!=617 && channel!=600 && channel!=601 && channel!=696 && channel!=697 && channel!=630 && channel!=631 && channel!=1126 && channel!=1127 && channel!=1110 && channel!=1111 && channel!=1108 && channel!=1109 && channel!=1122 && channel!=1123 && channel!=1202 && channel!=1203 && channel!=1206 && channel!=1207 && channel!=1168 && channel!=1169 && channel!=1304 && channel!=1305 && channel!=1296 && channel!=1297 && channel!=1328 && channel!=1329 && channel!=1234 && channel!=1235 && channel!=1268 && channel!=1269 && channel!=1238 && channel!=1239";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>237.04 && (trapENFCal[0] + trapENFCal[1])<239.69)";
char chan688[] = "channel==688";
char chan694[] = "channel==694";
char chan614[] = "channel==614";
char chan598[] = "channel==598";
char chan592[] = "channel==592";
char chan632[] = "channel==632";
char chan626[] = "channel==626";
char chan690[] = "channel==690";
char chan680[] = "channel==680";
char chan678[] = "channel==678";
char chan674[] = "channel==674";
char chan672[] = "channel==672";
char chan1124[] = "channel==1124";
char chan1204[] = "channel==1204";
char chan1174[] = "channel==1174";
char chan1128[] = "channel==1128";
char chan1106[] = "channel==1106";
char chan1176[] = "channel==1176";
char chan1172[] = "channel==1172";
char chan1170[] = "channel==1170";
char chan1208[] = "channel==1208";
char chan1120[] = "channel==1120";
char chan1330[] = "channel==1330";
char chan1332[] = "channel==1332";
char chan1302[] = "channel==1302";
char chan1298[] = "channel==1298";
char chan1236[] = "channel==1236";
char chan1232[] = "channel==1232";

void CutEfficiency1()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5bchan626.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan626);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan626);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5bchan690.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan690);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan690);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5bchan680.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan680);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan680);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5bchan678.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan678);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan678);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5bchan674.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan674);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan674);
    
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

void CutEfficiency6()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS5bchan672.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan672);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan672);
    
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

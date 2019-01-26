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

void ToEvsRun();
void TETMvsRun();
void TETMvsEnergy();
void Blob();
void CutEfficiency1();
void CutEfficiency2();
void CutEfficiency3();
void CutEfficiency4();
void CutEfficiency5();
void CompareSumEParam();
void ComptonSpectrum();
void BlindRunSelect();
void SpectraNoCuts();
void FinalCombinedSpectrum();
void TuneToECut1();
void TuneToECut2();
void TuneToECut3();
void TuneToECut4();
void TuneToECut5();
void NatToEFinal();
void EnrToEFinal();
void ToEComp();
void FinalEnrichedSpectrum();
void ToEAllCuts();
void DetectorSelection();
void EvsRunGood();
void TestWFCuts();
void TuneWFCuts1();
void TuneWFCuts2();
void TuneWFCuts3();
void TuneWFCuts4();
void TuneWFCuts5();
void TETMCutStudy2D();
void TETMCutStudy1D();
void RunsAndDets();

int main()
{
  //ToEvsRun();
  //TETMvsRun();
  //TETMvsEnergy();
  //Blob();
  //CutEfficiency1();
  //CutEfficiency2();
  //CutEfficiency3();
  //CutEfficiency4();
  //CutEfficiency5();
  //CompareSumEParam();
  //ComptonSpectrum();
  //BlindRunSelect();
  //SpectraNoCuts();             // Spectra without T/E or pulser retrigger (trapETailMin) cut.
  //FinalCombinedSpectrum();
  //TuneToECut1();
  //TuneToECut2();
  //TuneToECut3();
  //TuneToECut4();
  //TuneToECut5();
  //NatToEFinal();
  //EnrToEFinal();
  //ToEComp();
  //FinalEnrichedSpectrum();
  //ToEAllCuts();
  DetectorSelection();
  EvsRunGood();
  //TestWFCuts();
  //TuneWFCuts1();                //  For tuning waveform (ToE & trapETailMin) cuts.
  //TuneWFCuts2();
  //TuneWFCuts3();
  //TuneWFCuts4();
  //TuneWFCuts5();
  //TETMCutStudy2D();          // 1. Makes 2D plots for TETM cut study and saves to output file.
  //TETMCutStudy1D();          // 2. Makes 1D plots for TETM cut study and saves to output file.
  //RunsAndDets();             // 3. 1D Hists of run and detector (channel) to help me pick out noisy runs/detectors.

}

char cut8[10000];
char cut7[10000];
char cut6[10000];
char cut5[10000];
char cut4[10000];
char cut3[10000];
char cut2[10000];
char cut1[10000];
char cut0[10000];
char theCut[100000];
char EwindowCut1[] = "trapENFCal>9 && trapENFCal<14";
char EwindowCut1Mod[] = "trapENFCal>8.9 && trapENFCal<19.9";
char EwindowCut2[] = "trapENFCal>20 && trapENFCal<25";
char EwindowCut2Mod[] = "trapENFCal>19.9 && trapENFCal<25.0";
char EwindowCut3[] = "trapENFCal<0.2";
char EwindowCut4[] = "trapENFCal>=5";
char EwindowCut5[] = "trapENFCal>5 && trapENFCal<10";
char EwindowCut5Mod[] = "trapENFCal>4.9 && trapENFCal<9.9";
char enrCut[] = "isEnr";
char natCut[] = "isNat";
char basicCut[] = "(gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0)";
//char wfdcCut[] = "!wfDCBits";
char tetmCut[] = "((channel==1296 && trapETailMin<0.0) || (channel==1332 && trapETailMin<0.2) || (channel==1176 && trapETailMin<0.3) || ((channel==1136 || channel==1172 || channel==1174 || channel==1232 || channel==1330) && trapETailMin<0.4) || ((channel==1204 || channel==1236 || channel==1298) && trapETailMin<0.5) || ((channel==1144 || channel==1170) && trapETailMin<0.6) || (channel==1106 && trapETailMin<0.7))";
char tetmOldCut[] = "trapETailMin < 0.2";
char tetmKrisCut[] = "trapETailMin < 0";
char oldLEtoe[] = "(((channel==1106 || channel==1144 || channel==1174 || channel==1236 || channel==1330 || channel==1332 || channel==1296) && kvorrT/trapENFCal < 2.1 && kvorrT/trapENFCal > 1.1) || ((channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204 || channel==1232 || channel==1298) && kvorrT/trapENFCal < 2 && kvorrT/trapENFCal > 0.8))";
char oldHEtoe[] = "(((channel==1106 || channel==1144 || channel==1236 || channel==1296 || channel==1332) && kvorrT/trapENFCal<1.59 && kvorrT/trapENFCal>1.13) || ((channel==1174 || channel==1330) && kvorrT/trapENFCal<1.36 && kvorrT/trapENFCal>1.12) || (channel==1232 && kvorrT/trapENFCal<1.28 && kvorrT/trapENFCal>0.96) || ((channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204 || channel==1298) && kvorrT/trapENFCal<1.13 && kvorrT/trapENFCal>0.82))";
char toeAltCut[] = "((channel!=1106 && channel!=1144 && channel!=1174 && channel!=1236 && channel!=1330 && channel!=1332 && channel!=1296 && kvorrT/trapENFCal < 2.0 && kvorrT/trapENFCal > 0.8) || (channel!=1136 && channel!=1170 && channel!=1172 && channel!=1176 && channel!=1204 && channel!=1232 && channel!=1298 && kvorrT/trapENFCal < 2.1 && kvorrT/trapENFCal > 1.1))";
char toeKrisCut[] = "kvorrT/trapENFCal>1.1 && kvorrT/trapENFCal<2.1";
char toeWideCut[] = "kvorrT/trapENFCal>0.8 && kvorrT/trapENFCal<2.1";
char LEtoe[] = "((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal<1.7 && kvorrT/trapENFCal>1.05) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal<1.6 && kvorrT/trapENFCal>1.0) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal<1.4 && kvorrT/trapENFCal>0.95) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal<1.3 && kvorrT/trapENFCal>0.8) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal<1.2 && kvorrT/trapENFCal>0.75) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal<1.7 && kvorrT/trapENFCal>1.1) || (run>=60001914 && (channel==1106 || channel==1170 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal<1.65 && kvorrT/trapENFCal>1.1))";
char HEtoe[] = "((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal<1.6 && kvorrT/trapENFCal>1.15) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal<1.45 && kvorrT/trapENFCal>1.1) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal<1.3 && kvorrT/trapENFCal>1.0) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal<1.2 && kvorrT/trapENFCal>0.9) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal<1.1 && kvorrT/trapENFCal>0.8) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal<1.65 && kvorrT/trapENFCal>1.25) || (run>=60001914 && (channel==1106 || channel==1170 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal<1.6 && kvorrT/trapENFCal>1.15))";
char ToE5k[] = "((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal>0.91 && kvorrT/trapENFCal<1.81) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal>0.87 && kvorrT/trapENFCal<1.71) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal>0.84 && kvorrT/trapENFCal<1.50) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal>0.68 && kvorrT/trapENFCal<1.40) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal>0.63 && kvorrT/trapENFCal<1.29) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal>1.01 && kvorrT/trapENFCal>1.85) || (run>=60001914 && (channel==1106 || channel==1170 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.85))";
char ToE_EDependent[] = "((trapENFCal<9 && ((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal>0.91 && kvorrT/trapENFCal<1.81) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal>0.87 && kvorrT/trapENFCal<1.71) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal>0.84 && kvorrT/trapENFCal<1.50) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal>0.68 && kvorrT/trapENFCal<1.40) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal>0.63 && kvorrT/trapENFCal<1.29) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal>1.01 && kvorrT/trapENFCal<1.85) || (run>=60001914 && (channel==1106 || channel==1107 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.85))) || (trapENFCal>=9 && trapENFCal<20 && ((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal>1.06 && kvorrT/trapENFCal<1.66) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal>0.99 && kvorrT/trapENFCal<1.53) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal>0.93 && kvorrT/trapENFCal<1.35) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal>0.78 && kvorrT/trapENFCal<1.26) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal>0.74 && kvorrT/trapENFCal<1.16) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal>1.14 && kvorrT/trapENFCal<1.74) || (run>=60001914 && (channel==1106 || channel==1107 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal>1.01 && kvorrT/trapENFCal<1.67))) || (trapENFCal>=20 && ((run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332) && kvorrT/trapENFCal>1.18 && kvorrT/trapENFCal<1.54) || (run<=60001868 && (channel==1174 || channel==1330) && kvorrT/trapENFCal>1.09 && kvorrT/trapENFCal<1.39) || (run<=60001868 && channel==1232 && kvorrT/trapENFCal>1.00 && kvorrT/trapENFCal<1.24) || (run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204) && kvorrT/trapENFCal>0.88 && kvorrT/trapENFCal<1.18) || (run<=60001868 && channel==1298 && kvorrT/trapENFCal>0.82 && kvorrT/trapENFCal<1.06) || (run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232) && kvorrT/trapENFCal>1.21 && kvorrT/trapENFCal<1.69) || (run>=60001914 && (channel==1106 || channel==1107 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332) && kvorrT/trapENFCal>1.14 && kvorrT/trapENFCal<1.56))))";
//char advCut[] = "avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2";
//char noisyRunsCut[] = "run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run<20966) && !(run>21133 && run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952";
//char noisyDetCut[] = "channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
//char finalCut[] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0 && !wfDCBits && avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2 && run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run<	20966) && !(run>21133 && run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952 && channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
char HEDetCut[] = "(channel!=1140 && channel!=1141 && channel!=1142 && channel!=1143 && channel!=1110 && channel!=1111 && channel!=1108 && channel!=1109 && channel!=1138 && channel!=1139 && channel!=1202 && channel!=1203 && channel!=1208 && channel!=1209 && channel!=1206 && channel!=1207 && channel!=1168 && channel!=1169 && channel!=1304 && channel!=1305 && channel!=1302 && channel!=1303 && channel!=1328 && channel!=1329 && channel!=1234 && channel!=1235 && channel!=1268 && channel!=1269 && channel!=1238 && channel!=1239)";
char cut1296[] = "channel == 1296"; 
//char RunDetCut[] = "!(channel==1332 && (run==60001079 || run==60001309 || run==60001408 || run==60001426 || run==60001427 || run==60001428 || run==60001432 || run==60001435 || run==60001436 || run==60001437 || run==60001438 || run==60001615 || run==60001635 || run==60001677 || run==60001678 || run==60001679))";
//char bottomBand[] = "(channel==1336 || channel==1170 || channel==1172 || channel==1176 || channel==1204 || channel==1298)";
//char midBottom[] = "channel==1232";
//char midTop[] = "(channel==1174 || channel==1330)";
//char topBand[] = "(channel==1106 || channel==1144 || channel==1236 || channel==1296 || channel==1332)";
char runG1detG1[] = "(run<=60001868 && (channel==1106 || channel==1144 || channel==1236 || channel==1332))";
char runG1detG2[] = "(run<=60001868 && (channel==1174 || channel==1330))";
char runG1detG3[] = "(run<=60001868 && (channel==1232))";
char runG1detG4[] = "(run<=60001868 && (channel==1136 || channel==1170 || channel==1172 || channel==1176 || channel==1204))";
char runG1detG5[] = "(run<=60001868 && (channel==1298))";    
char runG2detG1[] = "(run>=60001914 && (channel==1136 || channel==1144 || channel==1172 || channel==1232))";
char runG2detG2[] = "(run>=60001914 && (channel==1106 || channel==1170 || channel==1174 || channel==1176 || channel==1204 || channel==1236 || channel==1298 || channel==1330 || channel==1332))";
char calib9[] = "(run>=60001720 && run<=60001732)";
char calib10[] = "(run>=60001855 && run<=60001868)";
char calib11[] = "(run>=60001914 && run<=60001962)";
char LEcutoff[] = "(trapENFCal>=9)";
char ComptonEvents[] = "mH==2 && sumEH>237.49 && sumEH<239.67";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>237.49 && (trapENFCal[0] + trapENFCal[1])<239.67)";
char detC1P7D4[] = "C==1 && P==7 && D==4";
char Mult2Events[] = "mH==2";
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
char blob[] = "((channel==1106 || channel==1144 || channel==1236 || channel==1332) && trapENFCal>37 && trapENFCal<38 && kvorrT/trapENFCal>3.45 && kvorrT/trapENFCal<3.65)";
char runG1[] = "(run<=60001868)";
char runG2[] = "(run>=60001914)";

void ToEvsRun()
{
  string outFile = "/global/u1/j/jrager/LowE/ToEvsRunDS4_1296_cal.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,chan1296);
    
  TH2F *ToEVrun = new TH2F("ToEVrun","ToEVrun", 1845, 60000550, 60002395, 400, 0, 10);
  ToEVrun->GetYaxis()->SetTitle("trapETailMin");
  ToEVrun->GetXaxis()->SetTitle("run");
  skimTree->Project("ToEVrun","trapETailMin/trapENFCal:run",cut1);
  ToEVrun->SetOption("colz");
  ToEVrun->Write();
  cout << "Writing histogram ToEVrun" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TETMvsRun()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMvsRunDS4_1296.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,chan1296);
    
  TH2F *tetmVrun = new TH2F("tetmVrun","tetmVrun", 1845, 60000550, 60002395, 300, -20, 10);
  tetmVrun->GetYaxis()->SetTitle("trapETailMin");
  tetmVrun->GetXaxis()->SetTitle("run");
  skimTree->Project("tetmVrun","trapETailMin:run",cut1);
  tetmVrun->SetOption("colz");
  tetmVrun->Write();
  cout << "Writing histogram tetmVrun" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TETMvsEnergy()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMvsEnergyDS4_1296_cal.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,chan1296);
    
  TH2F *tetmVEnergy = new TH2F("tetmVEnergy", "tetmVEnergy", 1000, 0, 100, 300, -20, 10);
  tetmVEnergy->GetYaxis()->SetTitle("trapETailMin");
  tetmVEnergy->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("tetmVEnergy","trapETailMin:trapENFCal",cut1);
  tetmVEnergy->SetOption("colz");
  tetmVEnergy->Write();
  cout << "Writing histogram tetmVEnergy" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void Blob()
{
  string outFile = "/global/u1/j/jrager/LowE/DS4runG1detG1Blob.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s",blob);

  TH1D *Blob = new TH1D("Blob", "Blob", 1318, 60000550, 60001868);
  Blob->GetXaxis()->SetTitle("run");
  Blob->GetYaxis()->SetTitle("cts");
  skimTree->Project("Blob", "run", cut1);
  Blob->Write();
  cout << "Writing histogram Blob" <<  endl;

  cout << "done" <<  endl;

  f->Close();

}

void CutEfficiency1()
{
  string outFile = "/global/u1/j/jrager/LowE/EfficiencyDS4chan1296_ToE.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;

  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000); // manually overwrite root's hardcoded limit on formula length
  sprintf(cut1,"%s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,chan1296);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1296);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 20, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  //TH1D *Tot = new TH1D("Tot", "Tot", 20, 0, 100);
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("cts");
  //skimTree->Project("Tot", "trapENFCal", cut2);
  //Tot->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("cts");
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS4chan1296.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan1296);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan1296);
    
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
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("cts");
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency3()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS4chan1298.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
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
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("cts");
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency4()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan1236.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
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
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("cts");
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency5()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan1232.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
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
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("cts");
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CompareSumEParam()
{
  string outFile = "/global/u1/j/jrager/LowE/CompareSumEParamDS4.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s",Mult2Events);
    
  TH2F *compare = new TH2F("compare", "compare", 3000, 0, 3000, 3000, 0, 3000);
  compare->GetXaxis()->SetTitle("trapENFCal[0] + trapENFCal[1]");
  compare->GetYaxis()->SetTitle("sumEH");
  skimTree->Project("compare","sumEH:(trapENFCal[0] + trapENFCal[1])",cut1);
  compare->SetOption("colz");
  compare->Write();
  cout << "Writing histogram compare" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void ComptonSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/DS4BkgSpectBasic1296.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS4*.root");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s",ComptonEvents,HEDetCut);
  //sprintf(cut2,"%s",HEDetCut);
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,chan1296);

  TH1D *Basic = new TH1D("Basic", "Basic", 12000, 0, 3000);
  Basic->GetXaxis()->SetTitle("sumEH (keV)");
  Basic->GetYaxis()->SetTitle("cts");
  skimTree->Project("Basic", "sumEH", cut1);
  Basic->Write();
  cout << "Writing histogram Basic" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void BlindRunSelect()
{
  string outFile = "/global/u1/j/jrager/LowE/BlindRunSelectDS4_5kThresh.root";
  cout << "Creating outpout file" << outFile <<  endl;
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" << cout << outFile <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(theCut,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);
        
  cout << "Usig cut" << theCut << endl;
        
  TH1F *run = new TH1F("run", "run",  1845, 60000550, 60002395);
  run->GetXaxis()->SetTitle("run number");
  run->GetYaxis()->SetTitle("counts");
  skimTree->Project("run","run",theCut);
  run->Write();
  cout << "Writing histogram det" <<  endl;
        
  cout << "done" <<  endl;
        
  f->Close();
}

void SpectraNoCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/DS4NoCuts.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,enrCut);
  //sprintf(cut2,"%s",enrCut);
  //sprintf(cut3,"%s && %s && %s",basicCut,HEDetCut,natCut);
  //sprintf(cut4,"%s",natCut);
    
  TH1D *enrBasic = new TH1D("enrBasic", "enrBasic", 12000, 0, 3000);
  enrBasic->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrBasic->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrBasic", "trapENFCal", cut1);
  enrBasic->Write();
  cout << "Writing histogram enrBasic" <<  endl;
    
  TH1D *enrNoCut = new TH1D("enrNoCut", "enrNoCut", 12000, 0, 3000);
  enrNoCut->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrNoCut->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrNoCut", "trapENFCal", cut2);
  enrNoCut->Write();
  cout << "Writing histogram enrNoCut" <<  endl;
    
  TH1D *natBasic = new TH1D("natBasic", "natBasic", 12000, 0, 3000);
  natBasic->GetXaxis()->SetTitle("trapENFCal (keV)");
  natBasic->GetYaxis()->SetTitle("cts");
  skimTree->Project("natBasic", "trapENFCal", cut3);
  natBasic->Write();
  cout << "Writing histogram natBasic" <<  endl;
    
  TH1D *natNoCut = new TH1D("natNoCut", "natNoCut", 12000, 0, 3000);
  natNoCut->GetXaxis()->SetTitle("trapENFCal (keV)");
  natNoCut->GetYaxis()->SetTitle("cts");
  skimTree->Project("natNoCut", "trapENFCal", cut4);
  natNoCut->Write();
  cout << "Writing histogram natNoCut" <<  endl;

  cout << "done" <<  endl;
    
  f->Close();
}

void FinalCombinedSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/CombinedDS4_Newest.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut,RunDetCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,natCut,RunDetCut);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,natCut);
  //sprintf(cut4,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut,RunDetCut);
  //sprintf(cut5,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,enrCut,RunDetCut);
  //sprintf(cut6,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,enrCut);
    
  TH1D *natHE = new TH1D("natHE", "natHE", 12000, 0, 3000);
  natHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  natHE->GetYaxis()->SetTitle("cts");
  skimTree->Project("natHE", "trapENFCal", cut1);
  natHE->Write();
  cout << "Writing histogram natHE" <<  endl;
    
  TH1D *natLE = new TH1D("natLE", "natLE", 100, 5, 30);
  natLE->GetXaxis()->SetTitle("trapENFCal (keV)");
  natLE->GetYaxis()->SetTitle("cts");
  skimTree->Project("natLE", "trapENFCal", cut2);
  natLE->Write();
  cout << "Writing histogram natLE" <<  endl;
    
  TH1D *enrHE = new TH1D("enrHE", "enrHE", 12000, 0, 3000);
  enrHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrHE->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrHE", "trapENFCal", cut4);
  enrHE->Write();
  cout << "Writing histogram enrHE" <<  endl;
    
  TH1D *enrLE = new TH1D("enrLE", "enrLE", 100, 5, 30);
  enrLE->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrLE->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrLE", "trapENFCal", cut5);
  enrLE->Write();
  cout << "Writing histogram enrLE" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void NatToEFinal()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/ToE_Basic_ch1106r1720.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,natCut);
  //sprintf(cut1,"%s && %s && %s",basicCut,chan1106,calib9);

  TH2F *final = new TH2F("final", "final", 1000, 0, 100, 400, 0, 10);
  final->GetYaxis()->SetTitle("T/E (arb)");
  final->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("final","kvorrT/trapENFCal:trapENFCal",cut1);
  final->SetOption("colz");
  final->Write();
  cout << "Writing histogram final" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void EnrToEFinal()
{
  string outFile = "/global/u1/j/jrager/LowE/ToEDS4EnrFinal.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,enrCut);
    
  TH2F *final = new TH2F("final", "final", 1000, 0, 100, 400, 0, 10);
  final->GetYaxis()->SetTitle("T/E (arb)");
  final->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("final","kvorrT/trapENFCal:trapENFCal",cut1);
  final->SetOption("colz");
  final->Write();
  cout << "Writing histogram final" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void ToEComp()
{
  string outFile = "/global/u1/j/jrager/LowE/ToEDS4_TopBand.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/bg-skim/skimDS4_*_low.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,topBand);

  TH2F *final = new TH2F("final", "final", 1000, 0, 100, 400, 0, 10);
  final->GetYaxis()->SetTitle("T/E (arb)");
  final->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("final","kvorrT/trapENFCal:trapENFCal",cut1);
  final->SetOption("colz");
  final->Write();
  cout << "Writing histogram final" <<  endl;

  TLine *L1 = new TLine(0, 1.13, 100, 1.13);
  L1->SetLineColor(kRed);
  L1->Draw();
  TLine *L2 = new TLine(0, 1.59, 100, 1.59);
  L2->SetLineColor(kRed);
  L2->Draw();
  cout << "Drawing cuts" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void FinalEnrichedSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/AnalysisSpectDS4Enr.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;

  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(theCut,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,enrCut);
  //sprintf(theCut,"%s",basicCut);
  //TFormula *form = new TFormula("form",theCut);
  //form->SetMaxima(2000,2000,2000);

  TH1D *spect = new TH1D("spect", "spect", 12000, 0, 3000);
  spect->GetXaxis()->SetTitle("trapENFCal (keV)");
  spect->GetYaxis()->SetTitle("cts/kg/day/keV");
  skimTree->Project("spect", "trapENFCal", theCut);
  spect->SetOption("HIST");
  spect->Write();
  cout << "Writing histogram spect" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void ToEAllCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/FinalToEDS4.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/bg-skim/skimDS4_*_low.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut);
  //sprintf(cut2,"%s && %s",basicCut,HEDetCut);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,enrCut);
  //sprintf(cut4,"%s && %s && %s",basicCut,HEDetCut,enrCut);
  //sprintf(cut5,"%s",enrCut);
  //sprintf(cut6,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,natCut);
  //sprintf(cut7,"%s && %s && %s",basicCut,HEDetCut,natCut);
  //sprintf(cut8,"%s",natCut);

  TH2F *final = new TH2F("final", "final", 1000, 0, 100, 400, 0, 10);
  final->GetYaxis()->SetTitle("T/E (arb)");
  final->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("final","kvorrT/trapENFCal:trapENFCal",cut1);
  final->SetOption("colz");
  final->Write();
  cout << "Writing histogram final" <<  endl;

  TH2F *basic = new TH2F("basic", "basic", 1000, 0, 100, 400, 0, 10);
  basic->GetYaxis()->SetTitle("T/E (arb)");
  basic->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("basic","kvorrT/trapENFCal:trapENFCal",cut2);
  basic->SetOption("colz");
  basic->Write();
  cout << "Writing histogram basic" <<  endl;

  TH2F *noCuts = new TH2F("noCuts", "noCuts", 1000, 0, 100, 400, 0, 10);
  noCuts->GetYaxis()->SetTitle("T/E (arb)");
  noCuts->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("noCuts","kvorrT/trapENFCal:trapENFCal");
  noCuts->SetOption("colz");
  noCuts->Write();
  cout << "Writing histogram noCuts" <<  endl;

  TH2F *finalEnr = new TH2F("finalEnr", "finalEnr", 1000, 0, 100, 400, 0, 10);
  finalEnr->GetYaxis()->SetTitle("T/E (arb)");
  finalEnr->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("finalEnr","kvorrT/trapENFCal:trapENFCal",cut3);
  finalEnr->SetOption("colz");
  finalEnr->Write();
  cout << "Writing histogram finalEnr" <<  endl;

  TH2F *basicEnr = new TH2F("basicEnr", "basicEnr", 1000, 0, 100, 400, 0, 10);
  basicEnr->GetYaxis()->SetTitle("T/E (arb)");
  basicEnr->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("basicEnr","kvorrT/trapENFCal:trapENFCal",cut4);
  basicEnr->SetOption("colz");
  basicEnr->Write();
  cout << "Writing histogram basicEnr" <<  endl;

  TH2F *noCutsEnr = new TH2F("noCutsEnr", "noCutsEnr", 1000, 0, 100, 400, 0, 10);
  noCutsEnr->GetYaxis()->SetTitle("T/E (arb)");
  noCutsEnr->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("noCutsEnr","kvorrT/trapENFCal:trapENFCal",cut5);
  noCutsEnr->SetOption("colz");
  noCutsEnr->Write();
  cout << "Writing histogram noCutsEnr" <<  endl;

  TH2F *finalNat = new TH2F("finalNat", "finalNat", 1000, 0, 100, 400, 0, 10);
  finalNat->GetYaxis()->SetTitle("T/E (arb)");
  finalNat->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("finalNat","kvorrT/trapENFCal:trapENFCal",cut6);
  finalNat->SetOption("colz");
  finalNat->Write();
  cout << "Writing histogram finalNat" <<  endl;

  TH2F *basicNat = new TH2F("basicNat", "basicNat", 1000, 0, 100, 400, 0, 10);
  basicNat->GetYaxis()->SetTitle("T/E (arb)");
  basicNat->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("basicNat","kvorrT/trapENFCal:trapENFCal",cut7);
  basicNat->SetOption("colz");
  basicNat->Write();
  cout << "Writing histogram basicNat" <<  endl;

  TH2F *noCutsNat = new TH2F("noCutsNat", "noCutsNat", 1000, 0, 100, 400, 0, 10);
  noCutsNat->GetYaxis()->SetTitle("T/E (arb)");
  noCutsNat->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("noCutsNat","kvorrT/trapENFCal:trapENFCal",cut8);
  noCutsNat->SetOption("colz");
  noCutsNat->Write();
  cout << "Writing histogram noCutsNat" <<  endl;

  cout << "done" <<  endl;

  f->Close();

}

void DetectorSelection()
{
  string outFile = "/global/u1/j/jrager/LowE/DetSelectDS4_5kThresh_correctedCuts.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;

  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(theCut,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,EwindowCut4);

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  det->GetYaxis()->SetTitle("counts");
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH2F *detVrun = new TH2F("detVrun", "detVrun", 1845, 60000550, 60002395, 800, 550, 1350);
  det->GetXaxis()->SetTitle("run");
  det->GetYaxis()->SetTitle("detector channel");
  skimTree->Project("detVrun","channel:run",theCut);
  detVrun->SetOption("colz");
  detVrun->Write();
  cout << "Writing histogram detVrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void EvsRunGood()
{
  string outFile = "/global/u1/j/jrager/LowE/RunSelectDS4_5kThresh_correctedCuts.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;

  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  //sprintf(cut0,"%s && %s",HEDetCut,EwindowCut4);
  //sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,chan1296);
  sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,EwindowCut4);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmOldCut,LEtoe,HEDetCut,EwindowCut4);
    
  //TH2F *EVrun = new TH2F("EVrun","EVrun", 1845, 60000550, 60002395, 2000, 0, 500);
  //EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
  //EVrun->GetXaxis()->SetTitle("run");
  //skimTree->Project("EVrun","trapENFCal:run");
  //EVrun->SetOption("colz");
  //EVrun->Write();
  //cout << "Writing histogram EVrun" <<  endl;

  //TH2F *EVrunBasic = new TH2F("EVrunBasic","EVrunBasic", 1845, 60000550, 60002395, 2000, 0, 500);
  //EVrunBasic->GetYaxis()->SetTitle("trapENFCal (keV)");
  //EVrunBasic->GetXaxis()->SetTitle("run");
  //skimTree->Project("EVrunBasic","trapENFCal:run",cut1);
  //EVrunBasic->SetOption("colz");
  //EVrunBasic->Write();
  //cout << "Writing histogram EVrunBasic" <<  endl;

  TH2F *EVrunAdv = new TH2F("EVrunAdv","EVrunAdv", 1845, 60000550, 60002395, 2000, 0, 500);
  EVrunAdv->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunAdv->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunAdv","trapENFCal:run",cut2);
  EVrunAdv->SetOption("colz");
  EVrunAdv->Write();
  cout << "Writing histogram EVrunAdv" <<  endl;

  //TH2F *EVrunOld = new TH2F("EVrunOld","EVrunOld", 1845, 60000550, 60002395, 2000, 0, 500);
  //EVrunOld->GetYaxis()->SetTitle("trapENFCal (keV)");
  //EVrunOld->GetXaxis()->SetTitle("run");
  //skimTree->Project("EVrunOld","trapENFCal:run",cut3);
  //EVrunOld->SetOption("colz");
  //EVrunOld->Write();
  //cout << "Writing histogram EVrunOld" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TestWFCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/TestWFCutsDS4.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/cal-lat/latSkimDS4*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s",basicCut,tetmCut,HEDetCut);
  //sprintf(cut2,"%s && %s && %s",basicCut,toeCut,HEDetCut);

  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",cut1);
  ToE->SetOption("colz");
  ToE->Write();

  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",cut2);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;

  cout << "Writing histogram TuneToE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TuneToECut1()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneToECutDS4_1296_G1.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chan1296,runG1);
  sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chan1296,runG1);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,chan1296,runG1);

  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut3);
  at5k->Write();
  cout << "Writing histogram at5k" <<  endl;

  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut1);
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;
    
  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut2);
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneToECut2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneToECutDS4_1296_G2.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chan1296,runG2);
  sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chan1296,runG2);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,chan1296,runG2);

  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut3);
  at5k->Write();
  cout << "Writing histogram at5k" <<  endl;

  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut1);
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;
    
  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut2);
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneToECut3()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneToECutDS4_runG1detG3.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,runG1detG3);
  //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,runG1detG3);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,runG1detG3);

  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut3);
  at5k->Write();
  cout << "Writing histogram at5k" <<  endl;
  
  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut1);
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;
    
  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut2);
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneToECut4()
{
    string outFile = "/global/u1/j/jrager/LowE/Data/TuneToECutDS4_runG1detG4.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,runG1detG4);
    //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,runG1detG4);
    //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,runG1detG4);

    TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
    at5k->GetYaxis()->SetTitle("counts");
    at5k->GetXaxis()->SetTitle("T/E (arb)");
    skimTree->Project("at5k","kvorrT/trapENFCal",cut3);
    at5k->Write();
    cout << "Writing histogram at5k" <<  endl;

    TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
    at9k->GetYaxis()->SetTitle("counts");
    at9k->GetXaxis()->SetTitle("T/E (arb)");
    skimTree->Project("at9k","kvorrT/trapENFCal",cut1);
    at9k->Write();
    cout << "Writing histogram at9k" <<  endl;

    TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
    at20k->GetYaxis()->SetTitle("counts");
    at20k->GetXaxis()->SetTitle("T/E (arb)");
    skimTree->Project("at20k","kvorrT/trapENFCal",cut2);
    at20k->Write();
    cout << "Writing histogram at20k" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void TuneToECut5()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneToECutDS4_runG1detG5.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
        
  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,runG1detG5);
  //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,runG1detG5);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,runG1detG5);

  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut3);
  at5k->Write();
  cout << "Writing histogram at5k" <<  endl;

  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut1);
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;
        
  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut2);
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;
        
  cout << "done" <<  endl;
        
  f->Close();
}

void TuneWFCuts1()
{
  string outFile = "/global/u1/j/jrager/LowE/TuneWFCutsDS4_1296_cal.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(theCut,"%s && %s && %s",basicCut,HEDetCut,chan1296);
    
  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram ToE" <<  endl;
    
  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneWFCuts2()
{
  string outFile = "/global/u1/j/jrager/LowE/DS4TETMvsE_1296.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(theCut,"%s && %s && %s",basicCut,HEDetCut,chan1296);
    
  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram ToE" <<  endl;
    
  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -10, 5);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneWFCuts3()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS4_runG1detG3_Compton.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,runG1detG3);
    
  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram ToE" <<  endl;
    
  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneWFCuts4()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS4_runG1detG4_Compton.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,runG1detG4);
    
  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram ToE" <<  endl;

  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TuneWFCuts5()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS4_runG1detG5_Compton.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS4*.root");
  cout << "Adding data files" <<  endl;
        
  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,runG1detG5);
        
  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram ToE" <<  endl;
        
  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;
        
  cout << "done" <<  endl;
        
  f->Close();
}

void TETMCutStudy2D()
{

    string outFile = "/global/u1/j/jrager/LowE/TETMstudyImprovedDS4.root";
  
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS4*.root");
    cout << "Adding data files" <<  endl;

    TH2F *twoD = new TH2F("twoD", "twoD", 120, 0, 30, 160, -30, 10);
    twoD->GetYaxis()->SetTitle("trapETailMin");
    twoD->GetXaxis()->SetTitle("trapENFCal (keV)");
    //sprintf(theCut,"%s && %s", basicCut, wfdcCut);
    skimTree->Project("twoD","trapETailMin:trapENFCal",theCut);
    twoD->SetOption("colz");
    twoD->Write();
    cout << "Writing histogram twoD" <<  endl;
    
    TProfile *tprof = new TProfile("tprof", "tprof", 180, 5, 50, -20, 5);
    tprof->GetYaxis()->SetTitle("trapETailMin");
    tprof->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("tprof","trapETailMin:trapENFCal",theCut);
    tprof->Write();
    cout << "Writing histogram tprof" <<  endl;
    
    TH2F *EVrun = new TH2F("EVrun","EVrun", 1845, 60000550, 60002395, 120, 0, 30);
    EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
    EVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("EVrun","trapENFCal:run",theCut);
    EVrun->SetOption("colz");
    EVrun->Write();
    cout << "Writing histogram EVrun" <<  endl;
    
    TH2F *trapVrun = new TH2F("trapVrun","trapVrun", 1845, 60000550, 60002395, 160, -30, 10);
    trapVrun->GetYaxis()->SetTitle("trapETailMin");
    trapVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("trapVrun","trapETailMin:run",theCut);
    trapVrun->SetOption("colz");
    trapVrun->Write();
    cout << "Writing histogram trapVrun" <<  endl;

    cout << "done" <<  endl;
    
    f->Close();
}

void TETMCutStudy1D()
{
    string outFile = "/global/u1/j/jrager/LowE/TETMcutRecImprovedDS4.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS4*.root");
    cout << "Adding data files" <<  endl;

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 130, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    //sprintf(theCut,"%s && %s", basicCut, wfdcCut);
    skimTree->Project("htrapETailMin","trapETailMin",theCut);
    htrapETailMin->Write();
    //TLine *line95 = new TLine();
    //line95->SetLineColor(kRed);
    //line95->PaintLine(0.0732813, 0, 0.0732813, 5000000);
    cout << "Writing histogram htrapETailMin" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void RunsAndDets()
{
  string outFile = "/global/u1/j/jrager/LowE/TETMrunsAndDetsImprovedDS4.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS4*.root");

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  //sprintf(theCut,"%s && %s", basicCut, wfdcCut);
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH1F *hrun = new TH1F("hrun", "hrun", 1845, 60000550, 60002395);
  hrun->GetXaxis()->SetTitle("run");
  skimTree->Project("hrun","run",theCut);
  hrun->Write();
  cout << "Writing histogram hrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

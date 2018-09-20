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
void Baseline();
void ComptonSpectrum();
void BlindRunSelect();
void TETM1D();
void TETMvsDetChan();
void TETMvsRun();
void TETMvsEnergy();
void SpectraNoCuts();
void ToEFinal();
void DebuggingSpectrum();
void FinalCombinedSpectrum();
void TuneToECut1();
void TuneToECut2();
void NatToEFinal();
void EnrToEFinal();
void FinalNaturalSpectrum();
void FinalEnrichedSpectrum();
void ToEAllCuts();
void DetectorSelection();
void EvsRunGood();
void TestWFCuts();
void TuneWFCuts1();
void TuneWFCuts2();
void TETMCutStudy2D();
void TETMCutStudy1D();
void RunsAndDets();

int main()
{
  //CutEfficiency1();
  //CutEfficiency2();
  //CutEfficiency3();
  //CutEfficiency4();
  //CutEfficiency5();
  //Baseline();
  //ComptonSpectrum();
  //BlindRunSelect();
  //TETM1D();
  //TETMvsDetChan();
  //TETMvsRun();
  //TETMvsEnergy();
  //BlindRunSelect();
  //SpectraNoCuts();             // Spectra without T/E or pulser retrigger (trapETailMin) cut.
  //ToEFinal();
  //DebuggingSpectrum();
  //FinalCombinedSpectrum();
  //TuneToECut1();
  //TuneToECut2();
  //NatToEFinal();
  //EnrToEFinal();
  FinalNaturalSpectrum();
  FinalEnrichedSpectrum();
  //ToEAllCuts();
  //DetectorSelection();
  //EvsRunGood();
  //TestWFCuts();
  //TuneWFCuts1();              //  For tuning waveform (ToE & trapETailMin) cuts.
  //TuneWFCuts2();
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
char cut1[100000];
char cut0[10000];
char theCut[10000];
char EwindowCut1[] = "(trapENFCal>9 && trapENFCal<11)";
char EwindowCut1Mod[] = "(trapENFCal>8.9 && trapENFCal<19.9)";
char EwindowCut2[] = "(trapENFCal>20 && trapENFCal<22)";
char EwindowCut2Mod[] = "(trapENFCal>19.9 && trapENFCal<25.0)";
char EwindowCut3[] = "(trapENFCal<0.2)";
char EwindowCut4[] = "(trapENFCal>20 && trapENFCal<30)";
char EwindowCut5[] = "(trapENFCal>=5)";
char EwindowCut6[] = "(trapENFCal>5 && trapENFCal<7)";
char EwindowCut6Mod[] = "(trapENFCal>4.9 && trapENFCal<9.9)";
char enrCut[] = "isEnr";
char natCut[] = "isNat";
char basicCut[] = "(gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0)";
char tetmCut[] = "(((channel==632 || channel==1168 || channel==1298) && trapETailMin<0.0) || ((channel==598 || channel==614 || channel==648 || channel==660 || channel==662 || channel==678 || channel==1172) && trapETailMin<0.2) || ((channel==608 || channel==626 || channel==674 || channel==690 || channel==1124) && trapETailMin<0.3) || ((channel==584 || channel==610 || channel==640 || channel==1170 || channel==1208) && trapETailMin<0.4) || ((channel==658 || channel==694 || channel==1106 || channel==1174 || channel==1232 || channel==1232 || channel==1302) && trapETailMin<0.5) || ((channel==1120 || channel==1176 || channel==1204 || channel==1330 || channel==1332) && trapETailMin<0.6) || (channel==688 && trapETailMin<0.7) || ((channel==592 || channel==624 || channel==680 || channel==692 || channel==1128) && trapETailMin<1.0) || (channel==628 && trapETailMin<1.5))";
char tetmOldCut[] = "(trapETailMin < 0.0)";
char tetmKrisCut[] = "(trapETailMin < 0.0)";
char oldLEtoe[] = "((channel != 660 && channel != 672 && kvorrT/trapENFCal < 2.1 && kvorrT/trapENFCal > 1.1) || ((channel == 660 || channel == 672) && kvorrT/trapENFCal < 2.0 && kvorrT/trapENFCal > 0.8))";
char oldHEtoe[] = "((channel != 660 && channel != 672 && kvorrT/trapENFCal < 1.6 && kvorrT/trapENFCal > 1.12) || ((channel == 660 || channel == 672) && kvorrT/trapENFCal < 1.37 && kvorrT/trapENFCal > 1.21))";
char olderHEtoe[] = "((channel != 660 && channel != 672 && kvorrT/trapENFCal < 1.54 && kvorrT/trapENFCal > 1.26) || ((channel == 660 || channel == 672) && kvorrT/trapENFCal < 1.33 && kvorrT/trapENFCal > 1.25))";
char toeKrisCut[] = "(kvorrT/trapENFCal>1.1 && kvorrT/trapENFCal<2.1)";
char LEtoe[] = "((channel!=660 && kvorrT/trapENFCal<1.8 && kvorrT/trapENFCal>1.1) || (channel==660 && kvorrT/trapENFCal<1.2 && kvorrT/trapENFCal>0.85))";
char HEtoe[] = "((channel!=660 && kvorrT/trapENFCal<1.7 && kvorrT/trapENFCal>1.1) || (channel==660 && kvorrT/trapENFCal<1.1 && kvorrT/trapENFCal>0.85))";
char ToE5k[] = "((channel!=660 && kvorrT/trapENFCal>0.91 && kvorrT/trapENFCal<1.93) || (channel==660 && kvorrT/trapENFCal>0.56 && kvorrT/trapENFCal<1.40))";
char ToE_EDependent[] = "((trapENFCal<9 && ((channel!=660 && kvorrT/trapENFCal>0.87 && kvorrT/trapENFCal<1.95) || (channel==660 && kvorrT/trapENFCal>0.56 && kvorrT/trapENFCal<1.40))) || (trapENFCal>=9 && trapENFCal<20 && ((channel!=660 && kvorrT/trapENFCal>0.94 && kvorrT/trapENFCal<1.84) || (channel==660 && kvorrT/trapENFCal>0.71 && kvorrT/trapENFCal<1.25))) || (trapENFCal>=20 && ((channel!=660 && kvorrT/trapENFCal>1.11 && kvorrT/trapENFCal<1.65) || (channel==660 && kvorrT/trapENFCal>0.82 && kvorrT/trapENFCal<1.12))))";
char HEDetCut[] = "(channel!=664 && channel!=665 && channel!=642 && channel!=643 && channel!=616 && channel!=617 && channel!=600 && channel!=601 && channel!=696 && channel!=697 && channel!=630 && channel!=631 && channel!=1126 && channel!=1127 && channel!=1110 && channel!=1111 && channel!=1108 && channel!=1109 && channel!=1122 && channel!=1123 && channel!=1202 && channel!=1203 && channel!=1206 && channel!=1207 && channel!=1168 && channel!=1169 && channel!=1304 && channel!=1305 && channel!=1296 && channel!=1297 && channel!=1328 && channel!=1329 && channel!=1234 && channel!=1235 && channel!=1268 && channel!=1269 && channel!=1238 && channel!=1239)";
char HERunCut[] = "(run!=18627 && run!=18706 && run!=18752 && !(run>=18803 && run<=18807) && run!=18960 && !(run>=18962 && run<=19001) && !(run>=19003 && run<=19012) && run!=19026 && !(run>=19032 && run<=19048) && !(run>=19052 && run<=19053) && !(run>=19075 && run<=19092) && !(run>=19111 && run<=19234) && run!=19236 && run!=19239 && run!=19241 && run!=19304 && run!=19386 && run!=19678 && run!=19695 && run!=19732 && run!=19900 && run!=19908 && run!=19967 && run!=20017 && run!=20020 && run!=20131 && run!=20318 && run!=20334 && run!=20376 && run!=20492 && run!=20493 && run!=20521 && run!=20635 && run!=20639 && run!=20643 && run!=20683 && run!=20685 && run!=20757 && run!=20757 && !(run>=21148 && run<=21150) && run!=21157 && run!=21168 && run!=21390 && run!=21425 && run!=21500 && run!=21894 && run!=21921)";
//char OldestRunDetCut[] = "!(channel==660 && run>=20755 && run<=20756) && !(channel==678 && run>=20762 && run<=20795) && !(channel==678 && run>=20797 && run<=20838) && !(channel==678 && run>=20840 && run<=20882) && !(channel==678 && run>=20884 && run<=20972) && !(channel==678 && run>=20929 && run<=20953) && !(channel==678 && run>=20955 && run<=20957) && !(channel==678 && run>=20964 && run<=21012) && !(channel==678 && run>=21014 && run<=21058) && !(channel==678 && run>=21060 && run<=21104) && !(channel==678 && run>=21106 && run<=21136) && !(channel==678 && run>=21158 && run<=21167) && !(channel==660 && run>=21169 && run<=21178) && !(channel==1236 && run>=21169 && run<=21178) && !(channel==1332 && run>=21169 && run<=21178)";
//char OldRunDetCut[] = "!(channel==660 && run>=20755 && run<=20756) && !(channel==678 && run>=20762 && run<=20795) && !(channel==678 && run>=20797 && run<=20838) && !(channel==678 && run>=20840 && run<=20882) && !(channel==678 && run>=20884 && run<=20972) && !(channel==678 && run>=20929 && run<=20953) && !(channel==678 && run>=20955 && run<=20957) && !(channel==678 && run>=20964 && run<=21012) && !(channel==678 && run>=21014 && run<=21058) && !(channel==678 && run>=21060 && run<=21104) && !(channel==678 && run>=21106 && run<=21136) && !(channel==678 && run>=21158 && run<=21167) && !(channel==660 && run>=21169 && run<=21178) && !(channel==1236 && run>=21169 && run<=21178) && !(channel==1332 && run>=21169 && run<=21178) && !(channel==692 && run>=20755 && run<=21380)";
char RunDetCut9kThresh[] = "(!(channel==692 && run>=20483 && run<=20487) && !(channel==692 && run>=20611 && run<=20628))";
char RunDetCut5kThresh[] = "(!(channel==1332 && run>=19708 && run<=19722) && !((channel==584 || channel==610 || channel==614 || channel==648 || channel==658 || channel==660 || channel==692 || channel==1172 || channel==1332) && run>=20218 && run<=21453) && !(channel==692 && run>=21767 && run<=21769) && !(channel==692 && run==20489) && !(channel==692 && run>=21568 && run<=21612) && !(channel==692 && run>=21763 && run<=21781) && !(run==692 && run>=20218 && run<=21453))";
char cut660[] = "(channel!=660)";
char cutTwoChan[] = "!(channel==660 && channel==672)";
char TETMg1[] = "(trapETailMin > 1.0)";
char TETMl1[] = "(trapETailMin < 1.0)";
char TETMg0[] = "(trapETailMin > 0.0)";
char TETMl0[] = "(trapETailMin < 0.0)";
char TETMg2_9[] = "(trapETailMin > -2.9)";
char TETMl2_9[] = "(trapETailMin < -2.9)";
char chan584[] = "(channel==584)";
char chan1106[] = "(channel==1106)";
char runCut[] = "((run>=18754 && run<=18756) || (run>=19243 && run<=19246) || (run>=19255 && run<=19257) || (run>=20067 && run<=20069) || (run>=20809 && run<=20811) || (run>=21825 && run<=21827) || (run>=22287 && run<=22289) || (run>=22298 && run<=22300))";
char LEcutoff[] = "(trapENFCal>=9)";
char ComptonEvents[] = "(mH==2 && sumEH>237.28 && sumEH<239.46)";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>237.28 && (trapENFCal[0] + trapENFCal[1])<239.46)";
char Mult2Events[] = "mH==2";
char detC1P7D4[] = "(C==1 && P==7 && D==4)";
char chan662[] = "channel==662";
char chan660[] = "channel==660";
char chan658[] = "channel==658";
char chan692[] = "channel==692";
char chan648[] = "channel==648";

void CutEfficiency1()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan662.root";
    
  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan662);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan662);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 25, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 25, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  Eff->Divide(Tot);
  Eff->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan660.root";
    
  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan660);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan660);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 25, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 25, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  Eff->Divide(Tot);
  Eff->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency3()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan658.root";
    
  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan658);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan658);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 25, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 25, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  Eff->Divide(Tot);
  Eff->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency4()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan692.root";
    
  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan692);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan692);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 25, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 25, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  Eff->Divide(Tot);
  Eff->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency5()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan648.root";

  UInt_t runNumb;
  std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan648);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan648);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 25, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 25, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  Eff->Divide(Tot);
  Eff->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void Baseline()
{
  string outFile = "/global/u1/j/jrager/LowE/BaselineRMS_DS6_Ch662.root";
  cout << "Creating outpout file" << outFile <<  endl;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" << cout << outFile <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;

  sprintf(theCut,"%s && %s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,EwindowCut5,RunDetCut5kThresh,chan662);

  TH2F *BLvRun = new TH2F("BLvRun","BLvRun", 3769, 18623, 22392, 90, -0.006, 0.006);
  BLvRun->GetYaxis()->SetTitle("trapENFCal (keV)");
  BLvRun->GetXaxis()->SetTitle("run");
  skimTree->Project("BLvRun","RawWFblSlope:run",theCut);
  BLvRun->SetOption("colz");
  BLvRun->Write();
  cout << "Writing histogram BLvRun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void ComptonSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/SumSpectrumDS5a.root";
        
  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
               
  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  //cout << "Adding data files" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  //sprintf(cut1,"%s",ComptonEvents);
  sprintf(cut1,"%s && %s && %s",Mult2Events,HEDetCut,HERunCut);
        
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
  string outFile = "/global/u1/j/jrager/LowE/BlindRunSelectDS5a_5kThresh.root";
  cout << "Creating outpout file" << outFile <<  endl;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" << cout << outFile <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(theCut,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut5);
    
  cout << "Usig cut" << theCut << endl;
    
  TH1F *run = new TH1F("run", "run",  3769, 18623, 22392);
  run->GetXaxis()->SetTitle("run number");
  run->GetYaxis()->SetTitle("counts");
  skimTree->Project("run","run",theCut);
  run->Write();
  cout << "Writing histogram det" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TETM1D()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMoE1D_1106_DS5a.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(theCut,"%s && %s",basicCut,chan1106);

  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 300, -20, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin/trapENFCal",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;

  cout << "Writing histogram TuneToE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TETMvsDetChan()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMvsDetChanD5a.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;
        
  //sprintf(cut1,"%s && %s && %s",basicCut,toeCut,chan584);
        
  TH2F *tetmVDetChan = new TH2F("tetmVDetChan", "tetmVDetChan", 1440, 0, 1440, 150, -5, 10);
  tetmVDetChan->GetXaxis()->SetTitle("detector channel");
  tetmVDetChan->GetYaxis()->SetTitle("trapENFCal");
  skimTree->Project("tetmVDetChan","trapETailMin:channel",cut1);
  tetmVDetChan->SetOption("colz");
  tetmVDetChan->Write();
  cout << "Writing histogram tetmVDetChan" <<  endl;
        
  cout << theCut << endl;
        
  cout << "done" <<  endl;
        
  f->Close();
}

void TETMvsRun()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMoEvsRun_1106_DS5a.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Adding data files" <<  endl;
        
  //sprintf(cut1,"%s && %s",basicCut,chan1106);
        
  TH2F *tetmVrun = new TH2F("tetmVrun","tetmVrun", 3769, 18623, 22392, 300, -20, 10);
  tetmVrun->GetYaxis()->SetTitle("trapETailMin");
  tetmVrun->GetXaxis()->SetTitle("run");
  skimTree->Project("tetmVrun","trapETailMin/trapENFCal:run",cut1);
  tetmVrun->SetOption("colz");
  tetmVrun->Write();
  cout << "Writing histogram tetmVrun" <<  endl;
        
  cout << "done" <<  endl;
        
  f->Close();
}


void TETMvsEnergy()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMvsEnergyDS5a_Bkg.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;
        
  //sprintf(cut1,"%s",basicCut);
        
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

void SpectraNoCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/DS5aNoCuts.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
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

void ToEFinal()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS5aToE_TETMg0.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,enrCut);
  //sprintf(cut1,"%s && %s",basicCut,TETMg0);

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

void DebuggingSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS5aSpect_TETMg0.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Adding data files" <<  endl;
        
  //sprintf(theCut,"%s && %s",basicCut,TETMg0);
        
  TH1D *WFCut = new TH1D("WFCut", "WFCut", 12000, 0, 3000);
  WFCut->GetXaxis()->SetTitle("trapENFCal (keV)");
  WFCut->GetYaxis()->SetTitle("cts/kg/day/keV");
  skimTree->Project("WFCut", "trapENFCal", theCut);
  WFCut->SetOption("HIST");
  WFCut->Write();
  cout << "Writing histogram WFCut" <<  endl;
        
  cout << "done" <<  endl;
        
  f->Close();
}

void FinalCombinedSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/Enr&NatSeparate5a_EDepToE.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut,RunDetCutNew);
  sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,ToE_EDependent,RunDetCut5kThresh,natCut);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,natCut);
  //sprintf(cut4,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut,RunDetCutNew);
  sprintf(cut5,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,ToE_EDependent,RunDetCut5kThresh,enrCut);
  //sprintf(cut6,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,enrCut);

  //TH1D *natHE = new TH1D("natHE", "natHE", 12000, 0, 3000);
  //natHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  //natHE->GetYaxis()->SetTitle("cts");
  //skimTree->Project("natHE", "trapENFCal", cut1);
  //natHE->Write();
  //cout << "Writing histogram natHE" <<  endl;

  TH1D *natLE = new TH1D("natLE", "natLE", 180, 5, 50);
  natLE->GetXaxis()->SetTitle("trapENFCal (keV)");
  natLE->GetYaxis()->SetTitle("cts");
  skimTree->Project("natLE", "trapENFCal", cut2);
  natLE->Write();
  cout << "Writing histogram natLE" <<  endl;

  //TH1D *enrHE = new TH1D("enrHE", "enrHE", 12000, 0, 3000);
  //enrHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  //enrHE->GetYaxis()->SetTitle("cts");
  //skimTree->Project("enrHE", "trapENFCal", cut4);
  //enrHE->Write();
  //cout << "Writing histogram enrHE" <<  endl;

  TH1D *enrLE = new TH1D("enrLE", "enrLE", 180, 5, 50);
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
  string outFile = "/global/u1/j/jrager/LowE/NatToEDS5aFinal.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,natCut);

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
  string outFile = "/global/u1/j/jrager/LowE/EnrToEDS5aFinal.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,enrCut);

  TH2F *final = new TH2F("final", "final", 1000, 0, 100, 400, 0, 10);
  final->GetYaxis()->SetTitle("T/E (arb)");
  final->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("final","kvorrT/trapENFCal:trapENFCal",cut1);
  final->SetOption("colz");
  final->Write();
  cout << "Writing histogram final" <<  endl;

  //TLine *L1 = new TLine(0, 1.12, 100, 1.12);
  //L1->SetLineColor(kRed);
  //L1->Draw();
  //TLine *L2 = new TLine(0, 1.6, 100, 1.6);
  //L2->SetLineColor(kRed);
  //L2->Draw();
  //cout << "Drawing cuts" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void FinalEnrichedSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/AnalysisSpectDS5aEnr.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/skimDS5_1_low.root");
  cout << "Adding data files" <<  endl;

  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,HERunCut,enrCut,RunDetCut5kThresh);
  //sprintf(cut1,"%s",HERunCut);
  
  TH1D *spect = new TH1D("spect", "spect", 12000, 0, 3000);
  spect->GetXaxis()->SetTitle("trapENFCal (keV)");
  spect->GetYaxis()->SetTitle("cts");
  skimTree->Project("spect", "trapENFCal", cut1);
  spect->Write();
  cout << "Writing histogram spect" <<  endl;

  cout << "done" <<  endl;

  cout << cut1 << endl;

  f->Close();
}

void FinalNaturalSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/AnalysisSpectDS5aNat.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;

  ROOT::v5::TFormula::SetMaxima(2000, 2000, 2000);
  sprintf(cut1,"%s && %s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,HERunCut,natCut,RunDetCut5kThresh);

  TH1D *spect = new TH1D("spect", "spect", 12000, 0, 3000);
  spect->GetXaxis()->SetTitle("trapENFCal (keV)");
  spect->GetYaxis()->SetTitle("cts");
  skimTree->Project("spect", "trapENFCal", cut1);
  spect->Write();
  cout << "Writing histogram spect" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void ToEAllCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/FinalToEDS5a.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/DetSelectBlindDS5a_wRunDetCut_2ndIt.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    //char buffer[50];
    //int n;
    //n = sprintf(buffer,"%d",runNumb);
    //dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/bkg/skimDS5_run") + buffer + "_low.root";
    //skimTree->Add(dataFile.c_str());
    //std::cout << "Adding run # "  << runNumb << std::endl;
  //}
  //cout << "Data files added" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut5,RunDetCut5kThresh);

  TH1F *det = new TH1F("det", "det", 1440, 0, 1440);
  det->GetXaxis()->SetTitle("detector channel");
  det->GetYaxis()->SetTitle("counts");
  skimTree->Project("det","channel",cut1);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH2F *detVrun = new TH2F("detVrun", "detVrun", 3769, 18623, 22392, 1440, 0, 1440);
  det->GetXaxis()->SetTitle("run");
  det->GetYaxis()->SetTitle("detector channel");
  skimTree->Project("detVrun","channel:run",cut1);
  detVrun->SetOption("colz");
  detVrun->Write();
  cout << "Writing histogram detVrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void EvsRunGood()
{
  string outFile = "/global/u1/j/jrager/LowE/RunSelectDS5a_wRunDetCut_2ndIt.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aBG/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut0,"%s && %s",HEDetCut,EwindowCut5);
  //sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,EwindowCut5);
  sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut5,RunDetCut5kThresh);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmKrisCut,LEtoe,HEDetCut,EwindowCut5);
    
  //TH2F *EVrun = new TH2F("EVrun","EVrun", 3769, 18623, 22392, 2000, 0, 500);
  //EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
  //EVrun->GetXaxis()->SetTitle("run");
  //skimTree->Project("EVrun","trapENFCal:run",cut0);
  //EVrun->SetOption("colz");
  //EVrun->Write();
  //cout << "Writing histogram EVrun" <<  endl;

  //TH2F *EVrunBasic = new TH2F("EVrunBasic","EVrunBasic", 3769, 18623, 22392, 2000, 0, 500);
  //EVrunBasic->GetYaxis()->SetTitle("trapENFCal (keV)");
  //EVrunBasic->GetXaxis()->SetTitle("run");
  //skimTree->Project("EVrunBasic","trapENFCal:run",cut1);
  //EVrunBasic->SetOption("colz");
  //EVrunBasic->Write();
  //cout << "Writing histogram EVrunBasic" <<  endl;

  TH2F *EVrunAdv = new TH2F("EVrunAdv","EVrunAdv", 3769, 18623, 22392, 2000, 0, 500);
  EVrunAdv->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunAdv->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunAdv","trapENFCal:run",cut2);
  EVrunAdv->SetOption("colz");
  EVrunAdv->Write();
  cout << "Writing histogram EVrunAdv" <<  endl;

  //TH2F *EVrunOld = new TH2F("EVrunOld","EVrunOld", 3769, 18623, 22392, 2000, 0, 500);
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
  string outFile = "/global/u1/j/jrager/LowE/TestWFCutsDS5aCut.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s",basicCut,HEDetCut);
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
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS5a_cut660_noTETM.root";

  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  //cout << "Adding data files" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,cut660);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,cut660);
  //sprintf(cut1,"%s",cutTwoChan);
  //sprintf(cut2,"%s",cutTwoChan);
  //sprintf(cut4,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut6,cut660);

  //TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  //at5k->GetYaxis()->SetTitle("counts");
  //at5k->GetXaxis()->SetTitle("T/E (arb)");
  //skimTree->Project("at5k","kvorrT/trapENFCal",cut4);
  //at5k->Write();
  //cout << "Writing histogram at5k" <<  endl;

  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut1);
  skimTree->Project("at9k","kvorrT/trapENFCal");
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;

  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut2);
  skimTree->Project("at20k","kvorrT/trapENFCal");
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TuneToECut2()
{
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS5a_chan660.root";

  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  //cout << "Adding data files" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  //cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chan660,tetmCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chan660,tetmCut);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut3,twoChan);
  //sprintf(cut4,"%s && %s && %s && %s && %s",basicCut,HEDetCut,EwindowCut6,chan660,tetmCut);

  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut4);
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
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS5a_detC1P7D4_Compton.root";

  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  //cout << "Adding data files" <<  endl;

  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,detC1P7D4);

  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram ToE" <<  endl;

  TH2F *tetmVEnergy = new TH2F("tetmVEnergy", "tetmVEnergy", 1000, 0, 100, 300, -20, 10);
  tetmVEnergy->GetYaxis()->SetTitle("trapETailMin");
  tetmVEnergy->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("tetmVEnergy","trapETailMin:trapENFCal",theCut);
  tetmVEnergy->SetOption("colz");
  tetmVEnergy->Write();
  cout << "Writing histogram tetmVEnergy" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TuneWFCuts2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS5a_chan660.root";
    
  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5aCal/*.root");
  //cout << "Adding data files" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 18713; runNumb <= 22392; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  //sprintf(theCut,"%s && %s && %s && %s",basicCut,HEDetCut,chan660,tetmCut);
    
  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram ToE" <<  endl;
    
  TH2F *tetmVEnergy = new TH2F("tetmVEnergy", "tetmVEnergy", 1000, 0, 100, 300, -20, 10);
  tetmVEnergy->GetYaxis()->SetTitle("trapETailMin");
  tetmVEnergy->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("tetmVEnergy","trapETailMin:trapENFCal",theCut);
  tetmVEnergy->SetOption("colz");
  tetmVEnergy->Write();
  cout << "Writing histogram tetmVEnergy" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TETMCutStudy2D()
{

    string outFile = "/global/u1/j/jrager/LowE/TETMstudyImprovedDS5.root";
  
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_66_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_67_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_68_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_69_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_7*.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_8*.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_9*.root");
    cout << "Adding data files" <<  endl;

    TH2F *twoD = new TH2F("twoD", "twoD", 120, 0, 30, 160, -30, 10);
    twoD->GetYaxis()->SetTitle("trapETailMin");
    twoD->GetXaxis()->SetTitle("trapENFCal (keV)");
    //sprintf(theCut,"%s && %s", basicCut, wfdcCut);
    //skimTree->Project("twoD","trapETailMin:trapENFCal",theCut);
    twoD->SetOption("colz");
    twoD->Write();
    cout << "Writing histogram twoD" <<  endl;
    
    TProfile *tprof = new TProfile("tprof", "tprof", 180, 5, 50, -20, 5);
    tprof->GetYaxis()->SetTitle("trapETailMin");
    tprof->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("tprof","trapETailMin:trapENFCal",theCut);
    tprof->Write();
    cout << "Writing histogram tprof" <<  endl;
    
    TH2F *EVrun = new TH2F("EVrun","EVrun", 7049, 18623, 25672, 120, 0, 30);
    EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
    EVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("EVrun","trapENFCal:run",theCut);
    EVrun->SetOption("colz");
    EVrun->Write();
    cout << "Writing histogram EVrun" <<  endl;
    
    TH2F *trapVrun = new TH2F("trapVrun","trapVrun", 7049, 18623, 25672, 160, -30, 10);
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
    string outFile = "/global/u1/j/jrager/LowE/TETMcutRecImprovedDS5.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_66_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_67_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_68_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_69_low.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_7*.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_8*.root");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5_9*.root");
    cout << "Adding data files" <<  endl;

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 130, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    //sprintf(theCut,"%s && %s", basicCut, wfdcCut);
    //skimTree->Project("htrapETailMin","trapETailMin",theCut);
    htrapETailMin->Write();
    //TLine *line95 = new TLine();
    //line95->SetLineColor(kRed);
    //line95->PaintLine(0.0732813, 0, 0.0732813, 5000000);
    cout << "Writing histogram htrapETailMin" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}


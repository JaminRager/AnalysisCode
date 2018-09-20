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

using namespace std;

void CutEfficiency1();
void CutEfficiency2();
void CutEfficiency3();
void CutEfficiency4();
void CutEfficiency5();
void ComptonSpectrum();
void BlindRunSelect();
void SpectraNoCuts();
void FinalCombinedSpectrum();
void TuneToECut1();
void TuneToECut2();
void TuneToECut3();
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
  //ComptonSpectrum();
  //BlindRunSelect();
  //SpectraNoCuts();             // Spectra without T/E or pulser retrigger (trapETailMin) cut.
  //FinalCombinedSpectrum();
  //TuneToECut1();
  //TuneToECut2();
  //TuneToECut3();
  //NatToEFinal();
  //EnrToEFinal();
  //FinalNaturalSpectrum();
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
char cut1[10000];
char cut0[10000];
char theCut[10000];
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
char basicCut[] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0";
//char wfdcCut[] = "!wfDCBits";
char tetmCut[] = "(((channel==632 || channel==662) && trapETailMin<0.1) || ((channel==584 || channel==608 || channel==610 || channel==648 || channel==660 || channel==672 || channel==674 || channel==678 || channel==1172) && trapETailMin<0.2) ||  ((channel==598  || channel==640 || channel==658 || channel==680 || channel==690 || channel==692 || channel==694) && trapETailMin<0.3) || ((channel==614 || channel==688 || channel==1174 || channel==1204) && trapETailMin<0.4) || ((channel==592 || channel==626 || channel==1120 || channel==1124 || channel==1170 || channel==1208 || channel==1236 || channel==1298) && trapETailMin<0.5) || ((channel==624 || channel==1176) && trapETailMin<0.6) || ((channel==1106 || channel==1302) && trapETailMin<0.7) || ((channel==1128 || channel==1232) && trapETailMin<0.8) || (channel==1330 && trapETailMin<0.9))";
char tetmOldCut[] = "trapETailMin < 0";
char tetmKrisCut[] = "trapETailMin < 0";
char oldLEtoe[] = "((channel != 660 && channel != 628 && channel != 1302 && kvorrT/trapENFCal < 2.1 && kvorrT/trapENFCal > 1.1) || ((channel == 660 || channel == 628 || channel == 1302) && kvorrT/trapENFCal < 2.0 && kvorrT/trapENFCal > 0.8))";
char oldHEtoe[] = "((channel != 660 && channel != 628 && channel != 1302 && kvorrT/trapENFCal < 1.6 && kvorrT/trapENFCal > 1.15) || ((channel == 660 || channel == 628 || channel == 1302) && kvorrT/trapENFCal < 1.27 && kvorrT/trapENFCal > 1.11))";
char LEtoe[] = "((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal<1.8 && kvorrT/trapENFCal>1.0) || ((channel==660 || channel==1302) && kvorrT/trapENFCal<1.35 && kvorrT/trapENFCal>0.85) || (channel==628 && kvorrT/trapENFCal<1.5 && kvorrT/trapENFCal>1.00))";
char HEtoe[] = "((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal<1.75 && kvorrT/trapENFCal>1.15) || ((channel==660 || channel==1302) && kvorrT/trapENFCal<1.2 && kvorrT/trapENFCal>0.85) || (channel==628 && kvorrT/trapENFCal<1.35 && kvorrT/trapENFCal>1.05))";
char ToE5k[] = "((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal>0.89 && kvorrT/trapENFCal<1.91) || ((channel==660 || channel==1302) && kvorrT/trapENFCal>0.52 && kvorrT/trapENFCal<1.60) || (channel==628 && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.67))";
char ToE_EDependent[] = "((trapENFCal>=5 && trapENFCal<9 && ((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal>0.89 && kvorrT/trapENFCal<1.91) || (channel==660 && channel==1302 && kvorrT/trapENFCal>0.52 && kvorrT/trapENFCal<1.60) || (channel==628 && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.67))) || (trapENFCal>=9 && trapENFCal<20 && ((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal>1.03 && kvorrT/trapENFCal<1.75) || (channel==660 && channel==1302 && kvorrT/trapENFCal>0.69 && kvorrT/trapENFCal<1.41) || (channel==628 && kvorrT/trapENFCal>0.94 && kvorrT/trapENFCal<1.48))) || (trapENFCal>=20 && ((channel!=660 && channel!=1302 && channel!=628 && kvorrT/trapENFCal>1.12 && kvorrT/trapENFCal<1.66) || (channel==660 && channel==1302 && kvorrT/trapENFCal>0.81 && kvorrT/trapENFCal<1.23) || (channel==628 && kvorrT/trapENFCal>1.09 && kvorrT/trapENFCal<1.33))))";
char toeKrisCut[] = "kvorrT/trapENFCal>1.1 && kvorrT/trapENFCal<2.1";
//char advCut[] = "avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2";
//char noisyRunsCut[] = "run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run<20966) && !(run>21133 && run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952";
//char noisyDetCut[] = "channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
//char finalCut[] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0 && !wfDCBits && avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2 && run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run< 20966) && !(run>21133 &C& run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952 && channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
char HEDetCut[] = "channel!=664 && channel!=665 && channel!=642 && channel!=643 && channel!=616 && channel!=617 && channel!=600 && channel!=601 && channel!=696 && channel!=697 && channel!=630 && channel!=631 && channel!=1126 && channel!=1127 && channel!=1110 && channel!=1111 && channel!=1108 && channel!=1109 && channel!=1122 && channel!=1123 && channel!=1202 && channel!=1203 && channel!=1206 && channel!=1207 && channel!=1168 && channel!=1169 && channel!=1304 && channel!=1305 && channel!=1296 && channel!=1297 && channel!=1328 && channel!=1329 && channel!=1234 && channel!=1235 && channel!=1268 && channel!=1269 && channel!=1238 && channel!=1239";
char HERunCut[] = "run!=22645 && !(run>=22782 && run<=22784) && !(run>=22787 && run<=22805) && !(run>=22810 && run<=22811) && run!=22997 && run!=23434 && run!=23929";
//char RunDetCut[] = "!(channel==692 && run>=22937 && run<=22954) && !((channel==1172 || channel==1302) && run>=23939 && run<=23957) && !(channel==1302 && run>=23725 && run<=23881)";
char RunDetCut[] = "!(channel==692 && run==22937 && run==22946 && run==22952 && run==22954)";
char twoChan[] = "(channel==660 || channel==1302)";
char cutTwoChan[] = "!(channel==660 || channel==1302 || channel==628)";
char chan628[] = "(channel==628)";
char ComptonEvents[] = "mH==2 && sumEH>237.28 && sumEH<239.46";
char Mult2Events[] = "mH==2";
char detC1P7D4[] = "C==1 && P==7 && D==4";
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
  for (runNumb = 22514; runNumb <= 23959; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan662);
  //sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan662);
    
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
  for (runNumb = 22514; runNumb <= 23959; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan660);
  //sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan660);
    
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
  for (runNumb = 22514; runNumb <= 23959; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan658);
  //sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan658);
    
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
  for (runNumb = 22514; runNumb <= 23959; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan692);
  //sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan692);
    
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
  for (runNumb = 22514; runNumb <= 23959; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan648);
  //sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan648);
    
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

void ComptonSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/SumSpectrumDS5b.root";

  UInt_t runNumb;
  std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 22514; runNumb <= 23959; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
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
  string outFile = "/global/u1/j/jrager/LowE/BlindRunSelectDS5b_5kThresh.root";
  cout << "Creating outpout file" << outFile <<  endl;
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" << cout << outFile <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(theCut,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);
        
  cout << "Usig cut" << theCut << endl;        

  TH1F *run = new TH1F("run", "run",  1565, 22393, 23958);
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
  string outFile = "/global/u1/j/jrager/LowE/DS5bNoCuts.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/CombinedDS5b_Newest.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/NatToEDS5bFinal.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,natCut);

  TH2F *final = new TH2F("final", "final", 1000, 0, 100, 400, 0, 10);
  final->GetYaxis()->SetTitle("T/E (arb)");
  final->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("final","kvorrT/trapENFCal:trapENFCal",cut1);
  final->SetOption("colz");
  final->Write();
  cout << "Writing histogram final" <<  endl;

  //TLine *L1 = new TLine(0, 1.15, 100, 1.15);
  //L1->SetLineColor(kRed);
  //L1->Draw();
  //TLine *L2 = new TLine(0, 1.6, 100, 1.6);
  //L2->SetLineColor(kRed);
  //L2->Draw();
  //cout << "Drawing cuts" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void EnrToEFinal()
{
  string outFile = "/global/u1/j/jrager/LowE/ToEDS5bFinal.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/FinalToEDS5bTest1.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,tetmCut,RunDetCut);
  //sprintf(cut2,"%s && %s",basicCut,HEDetCut);

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

  cout << "done" <<  endl;

  f->Close();
}

void FinalNaturalSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/UnscaledNatSpectDS5b.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmOldCut,HEtoe,HEDetCut,natCut,RunDetCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmOldCut,toeCut,HEDetCut,natCut,RunDetCut);
  //Double_t DS5bexposureEnr = 4/667.736;

  TH1D *HE = new TH1D("HE", "HE", 11920, 20, 3000);
  HE->GetXaxis()->SetTitle("trapENFCal (keV)");
  HE->GetYaxis()->SetTitle("cts");
  skimTree->Project("HE", "trapENFCal", cut1);
  //HE->Scale(DS6exposureEnr);
  HE->Write();
  cout << "Writing histogram HE" <<  endl;

  TH1D *LE = new TH1D("LE", "LE", 120, 0, 30);
  LE->GetXaxis()->SetTitle("trapENFCal (keV)");
  LE->GetYaxis()->SetTitle("cts");
  skimTree->Project("LE", "trapENFCal", cut2);
  //LE->Scale(DS6exposureEnr);
  LE->Write();
  cout << "Writing histogram LE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void FinalEnrichedSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/AnalysisSpectDS5bNat.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,HERunCut,natCut,RunDetCut);
  
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
  string outFile = "/global/u1/j/jrager/LowE/FinalToEDS5b.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/DetSelectDS5b_5kThresh.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
  cout << "Adding data files" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //for (runNumb = 22513; runNumb <= 23509; runNumb++) {
    //char buffer[50];
    //int n;
    //n = sprintf(buffer,"%d",runNumb);
    //dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS5_run") + buffer + "_low.root";
    //skimTree->Add(dataFile.c_str());
    //std::cout << "Adding run # "  << runNumb << std::endl;
  //}
  //cout << "Data files added" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);

  TH1F *det = new TH1F("det", "det", 1440, 0, 1440);
  det->GetXaxis()->SetTitle("detector channel");
  det->GetYaxis()->SetTitle("counts");
  skimTree->Project("det","channel",cut1);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH2F *detVrun = new TH2F("detVrun", "detVrun", 1565, 22393, 23958, 1440, 0, 1440);
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
  string outFile = "/global/u1/j/jrager/LowE/RunSelectDS5b_5kThresh.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bBG/*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut0,"%s && %s",HEDetCut,EwindowCut4);
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,EwindowCut4);
  sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmKrisCut,LEtoe,HEDetCut,EwindowCut4);
    
  TH2F *EVrun = new TH2F("EVrun","EVrun", 1565, 22393, 23958, 2000, 0, 500);
  EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrun->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrun","trapENFCal:run",cut0);
  EVrun->SetOption("colz");
  EVrun->Write();
  cout << "Writing histogram EVrun" <<  endl;

  TH2F *EVrunBasic = new TH2F("EVrunBasic","EVrunBasic", 1565, 22393, 23958, 2000, 0, 500);
  EVrunBasic->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunBasic->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunBasic","trapENFCal:run",cut1);
  EVrunBasic->SetOption("colz");
  EVrunBasic->Write();
  cout << "Writing histogram EVrunBasic" <<  endl;

  TH2F *EVrunAdv = new TH2F("EVrunAdv","EVrunAdv", 1565, 22393, 23958, 2000, 0, 500);
  EVrunAdv->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunAdv->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunAdv","trapENFCal:run",cut2);
  EVrunAdv->SetOption("colz");
  EVrunAdv->Write();
  cout << "Writing histogram EVrunAdv" <<  endl;

  TH2F *EVrunOld = new TH2F("EVrunOld","EVrunOld", 1565, 22393, 23958, 2000, 0, 500);
  EVrunOld->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunOld->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunOld","trapENFCal:run",cut3);
  EVrunOld->SetOption("colz");
  EVrunOld->Write();
  cout << "Writing histogram EVrunOld" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TuneToECut1()
{
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS5b_cutTwoChan.root";
    
  UInt_t runNumb;
  std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 22513; runNumb <= 23509; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,cutTwoChan);
  //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,cutTwoChan);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,cutTwoChan);

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
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS5b_twoChan.root";

  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  //cout << "Adding data files" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 22513; runNumb <= 23509; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,twoChan);
  //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,twoChan);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,twoChan);

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
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS5b_chan628.root";
    
  UInt_t runNumb;
  std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 22513; runNumb <= 23509; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chan628);
  //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chan628);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,chan628);
    
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

void TestWFCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/TestWFCutsDS5b_C1P7D4_Compton.root";

  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  //cout << "Adding data files" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 22513; runNumb <= 23509; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  //sprintf(cut1,"%s && %s && %s",ComptonEvents,HEDetCut,detC1P7D4);

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

void TuneWFCuts2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS5b_twoChan_Compton.root";
    
  UInt_t runNumb;
  std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 22513; runNumb <= 23509; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;
    
  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,twoChan);
 
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

void TuneWFCuts1()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS5b_C1P7D4_Compton.root";

  UInt_t runNumb;
  std::string dataFile;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  //TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS5bCal/*.root");
  //cout << "Adding data files" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  for (runNumb = 22513; runNumb <= 23509; runNumb++) {
    char buffer[50];
    int n;
    n = sprintf(buffer,"%d",runNumb);
    dataFile = std::string("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS5_run") + buffer + "_low.root";
    skimTree->Add(dataFile.c_str());
    std::cout << "Adding run # "  << runNumb << std::endl;
  }
  cout << "Data files added" <<  endl;

  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,detC1P7D4);

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
  string outFile = "/global/u1/j/jrager/LowE/TETMrunsAndDetsImprovedDS5.root";

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

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  //sprintf(theCut,"%s && %s", basicCut, wfdcCut);
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH1F *hrun = new TH1F("hrun", "hrun", 7049, 18623, 25672);
  hrun->GetXaxis()->SetTitle("run");
  //sprintf(theCut,"%s && %s", basicCut, wfdcCut);
  hrun->Write();
  cout << "Writing histogram hrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

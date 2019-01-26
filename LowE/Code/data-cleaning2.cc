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
#include "TGraph.h"

using namespace std;

void CompareSumEParam();
void ComptonSpectrum();
void CutEfficiency1();
void CutEfficiency2();
void CutEfficiency3();
void CutEfficiency4();
void CutEfficiency5();
void Baseline();
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
void TuneWFCuts3();
void TETMCutStudy2D();
void TETMCutStudy1D();
void RunsAndDets();

int main()
{
  //CompareSumEParam();
  //ComptonSpectrum();
  CutEfficiency1();
  CutEfficiency2();
  CutEfficiency3();
  CutEfficiency4();
  //CutEfficiency5();
  //Baseline();
  //BlindRunSelect();
  //SpectraNoCuts();            // Spectra without T/E or pulser retrigger (trapETailMin) cut.
  //FinalCombinedSpectrum();
  //TuneToECut1();
  //TuneToECut2();
  //TuneToECut3();
  //NatToEFinal();
  //EnrToEFinal();
  //FinalNaturalSpectrum();
  //FinalEnrichedSpectrum();
  //ToEAllCuts();
  //DetectorSelection();
  //EvsRunGood();
  //TestWFCuts();
  //TuneWFCuts1();              //  For tuning waveform (ToE & trapETailMin) cuts.
  //TuneWFCuts2();
  //TuneWFCuts3();
  //TETMCutStudy2D();          //  Makes 2D plots for TETM cut study and saves to output file.
  //TETMCutStudy1D();          //  Makes 1D plots for TETM cut study and saves to output file.
  //RunsAndDets();             //  1D Hists of run and detector (channel) to help me pick out noisy runs/detectors.

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
char tetmCut[] = "(((channel==578 || channel==592 || channel==608 || channel==632 || channel==648 || channel==664 || channel==692) && trapETailMin<-0.1) || ((channel==580 || channel==598 || channel==600 || channel==626 || channel==640 || channel==690) && trapETailMin<-0.2) || (channel==582 && trapETailMin<-0.3) || ((channel==610 || channel==672) && trapETailMin<0.0))";
char tetmOldCut[] = "trapETailMin < -0.1";
char tetmKrisCut[] = "trapETailMin < 0";
char oldLEtoe[] = "((channel != 664 && channel != 580 && kvorrT/trapENFCal < 2.1 && kvorrT/trapENFCal > 1.1) || (channel == 580 && kvorrT/trapENFCal < 1.5 && kvorrT/trapENFCal > 0.8) || (channel == 664 && kvorrT/trapENFCal < 2 && kvorrT/trapENFCal > 1))";
char oldHEtoe[] = "((channel != 664 && channel != 580 && kvorrT/trapENFCal < 1.6 && kvorrT/trapENFCal > 1.15) || (channel == 580 && kvorrT/trapENFCal < 1.2 && kvorrT/trapENFCal > 0.8) || (channel == 664 && kvorrT/trapENFCal < 1.47 && kvorrT/trapENFCal > 0.99))";
char toeKrisCut[] = "kvorrT/trapENFCal>1.1 && kvorrT/trapENFCal<2.1";
char LEtoe[] = "((channel!=580 && channel!=664 && kvorrT/trapENFCal<1.75 && kvorrT/trapENFCal>1.0) || (channel==580 && kvorrT/trapENFCal<1.25 && kvorrT/trapENFCal>0.75) || (channel==664 && kvorrT/trapENFCal<1.5 && kvorrT/trapENFCal>1.0))";
char HEtoe[] = "((channel!=580 && channel!=664 && kvorrT/trapENFCal<1.57 && kvorrT/trapENFCal>1.15) || (channel==580 && kvorrT/trapENFCal<1.15 && kvorrT/trapENFCal>0.85) || (channel==664 && kvorrT/trapENFCal<1.35 && kvorrT/trapENFCal>1.1))";
char ToE5k[] = "((channel!=580 && channel!=664 && kvorrT/trapENFCal>0.87 && kvorrT/trapENFCal<1.89) || (channel==580 && kvorrT/trapENFCal>0.65 && kvorrT/trapENFCal<1.37) || (channel==664 && kvorrT/trapENFCal>0.75 && kvorrT/trapENFCal<1.77))";
char ToE_EDependent[] = "((trapENFCal<9 && ((channel!=580 && channel!=664 && kvorrT/trapENFCal>0.87 && kvorrT/trapENFCal<1.89) || (channel==580 && kvorrT/trapENFCal>0.65 && kvorrT/trapENFCal<1.37) || (channel==664 && kvorrT/trapENFCal>0.75 && kvorrT/trapENFCal<1.77))) || (trapENFCal>=9 && trapENFCal<20 && ((channel!=580 && channel!=664 && kvorrT/trapENFCal>1.01 && kvorrT/trapENFCal<1.73) || (channel==580 && kvorrT/trapENFCal>0.76 && kvorrT/trapENFCal<1.24) || (channel==664 && kvorrT/trapENFCal>0.93 && kvorrT/trapENFCal<1.53))) || (trapENFCal>=20 && ((channel!=580 && channel!=664 && kvorrT/trapENFCal>1.15 && kvorrT/trapENFCal<1.57) || (channel==580 && kvorrT/trapENFCal>0.84 && kvorrT/trapENFCal<1.14) || (channel==664 && kvorrT/trapENFCal>1.07 && kvorrT/trapENFCal<1.37))))";
//char wfdcCut[] = "!wfDCBits";
//char advCut[] = "avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2";
//char noisyRunsCut[] = "run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run<20966) && !(run>21133 && run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952";
//char noisyDetCut[] = "channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
//char finalCut[] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0 && !wfDCBits && avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2 && run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run<	20966) && !(run>21133 && run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952 && channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
char HEDetCut[] = "channel!=584 && channel!=585 && channel!=642 && channel!=643 && channel!=616 && channel!=617 && channel!=624 && channel!=625 && channel!=628 && channel!=629 && channel!=688 && channel!=689 && channel!=694 && channel!=695 && channel!=614 && channel!=615 && channel!=680 && channel!=681 && channel!=678 && channel!=679 && channel!=696 && channel!=697 && channel!=630 && channel!=631 && channel!=594 && channel!=595";
//char RunDetCut[10000];
char cutTwoChan[] = "!(channel==580 || channel==664)";
char ComptonEvents[] = "mH==2 && sumEH>237.35 && sumEH<239.58";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>237.35 && (trapENFCal[0] + trapENFCal[1])<239.58)";
char detC1P7D4[] = "C==1 && P==7 && D==4";
char Mult2Events[] = "mH==2";
char chan582[] = "channel==582";
char chan580[] = "channel==580";
char chan578[] = "channel==578";
char chan692[] = "channel==692";
char chan648[] = "channel==648";
char chan640[] = "channel==640";
char chan610[] = "channel==610";
char chan608[] = "channel==608";
char chan664[] = "channel==664";
char chan672[] = "channel==672";
char chan632[] = "channel==632";
char chan626[] = "channel==626";
char chan690[] = "channel==690";
char chan600[] = "channel==600";
char chan598[] = "channel==598";
char chan592[] = "channel==592";

void CompareSumEParam()
{
  string outFile = "/global/u1/j/jrager/LowE/CompareSumEParamDS2.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/ComptonSpectrumDS2.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s",ComptonEvents,HEDetCut);
  sprintf(cut2,"%s",HEDetCut);
    
  TH1D *Basic = new TH1D("Basic", "Basic", 12000, 0, 3000);
  Basic->GetXaxis()->SetTitle("trapENFCal (keV)");
  Basic->GetYaxis()->SetTitle("cts");
  skimTree->Project("Basic", "trapENFCal", cut1);
  Basic->Write();
  cout << "Writing histogram Basic" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency1()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan600.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan600);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan600);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 20, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  //Pass->Sumw2();
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 20, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  //Tot->Sumw2();
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Eff->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Eff->GetYaxis()->SetTitle("efficiency (%)");
  //Eff->Sumw2();
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan598.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan598);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan598);
    
  TH1D *Pass = new TH1D("Pass", "Pass", 20, 0, 100);
  Pass->GetXaxis()->SetTitle("trapENFCal (keV)");
  Pass->GetYaxis()->SetTitle("cts");
  //Pass->Sumw2();
  skimTree->Project("Pass", "trapENFCal", cut1);
  Pass->Write();
  cout << "Writing histogram Pass" <<  endl;
    
  TH1D *Tot = new TH1D("Tot", "Tot", 20, 0, 100);
  Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  Tot->GetYaxis()->SetTitle("cts");
  //Tot->Sumw2();
  skimTree->Project("Tot", "trapENFCal", cut2);
  Tot->Write();
  cout << "Writing histogram Tot" <<  endl;
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("efficiency (%)");
  //Eff->Sumw2();
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency3()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan592.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan592);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan592);
    
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
  //Tot->GetYaxis()->SetTitle("efficiency (%)");
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void CutEfficiency4()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan594.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan594);
  //sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan594);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS2chan690.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
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
    
  //TH1D *Eff = (TH1D*)Pass->Clone("Eff");
  //Tot->GetXaxis()->SetTitle("trapENFCal (keV)");
  //Tot->GetYaxis()->SetTitle("cts");
  //Eff->Divide(Tot);
  //Eff->Write();
  //cout << "Writing histogram Tot" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void Baseline()
{
  string outFile = "/global/u1/j/jrager/LowE/BaselineRMS_DS2_Ch580.root";
  cout << "Creating outpout file" << outFile <<  endl;

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" << cout << outFile <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;

  sprintf(theCut,"%s",chan580);  

  TH2F *BLvRun = new TH2F("BLvRun","BLvRun", 1376, 14508, 15884, 90, -0.0006, 0.0012);
  BLvRun->GetYaxis()->SetTitle("trapENFCal (keV)");
  BLvRun->GetXaxis()->SetTitle("run");
  skimTree->Project("BLvRun","RawWFblSlope:run",theCut);
  BLvRun->SetOption("colz");
  BLvRun->Write();
  cout << "Writing histogram BLvRun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void BlindRunSelect()
{
  string outFile = "/global/u1/j/jrager/LowE/BlindRunSelectDS2_5kThresh.root";
  cout << "Creating outpout file" << outFile <<  endl;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" << cout << outFile <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
 
  sprintf(theCut,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);
    
  cout << "Usig cut" << theCut << endl;
    
  TH1F *run = new TH1F("run", "run",  1376, 14508, 15884);
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
  string outFile = "/global/u1/j/jrager/LowE/DS2NoCuts.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS2*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/CombinedDS2_Newest.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,natCut);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,natCut);
  //sprintf(cut4,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut);
  //sprintf(cut5,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,enrCut);
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
  string outFile = "/global/u1/j/jrager/LowE/NatToEDS2Final.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS2_*_low.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s",basicCut,tetmCut,HEDetCut,natCut);

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
  string outFile = "/global/u1/j/jrager/LowE/ToEDS2EnrFinal.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS2_*_low.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s",basicCut,tetmCut,HEDetCut,enrCut);

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

void FinalNaturalSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/UnscaledNatSpectDS2.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,natCut);
  //Double_t DS3exposureEnr = 4/106.56;

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
  string outFile = "/global/u1/j/jrager/LowE/AnalysisSpectDS2Enr.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,enrCut);

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
  string outFile = "/global/u1/j/jrager/LowE/FinalToEDS2.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/bg-skim/skimDS2_*_low.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s",basicCut,tetmCut,HEDetCut);
  //sprintf(cut2,"%s && %s",basicCut, HEDetCut);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,enrCut);
  //sprintf(cut4,"%s && %s && %s",basicCut,HEDetCut,enrCut);
  //sprintf(cut5,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,natCut);
  //sprintf(cut6,"%s && %s && %s",basicCut,HEDetCut,natCut);

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

void DetectorSelection()
{
  string outFile = "/global/u1/j/jrager/LowE/DetSelectDS2_5kThresh.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;

  sprintf(theCut,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  det->GetYaxis()->SetTitle("counts");
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH2F *detVrun = new TH2F("detVrun", "detVrun", 1376, 14508, 15884, 800, 550, 1350);
  det->GetXaxis()->SetTitle("run");
  det->GetYaxis()->SetTitle("detector channel");
  skimTree->Project("detVrun","channel:run",theCut);
  detVrun->SetOption("colz");
  detVrun->Write();
  cout << "Writing histogram detVrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TestWFCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/TestWFCutsDS2.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/cal-lat/latSkimDS2*.root");
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

void EvsRunGood()
{
  string outFile = "/global/u1/j/jrager/LowE/RunSelectDS2_5kThresh.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
  
  sprintf(cut0,"%s && %s",HEDetCut,EwindowCut4);
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,EwindowCut4);
  sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmKrisCut,LEtoe,HEDetCut,EwindowCut4);
    
  TH2F *EVrun = new TH2F("EVrun","EVrun", 1376, 14508, 15884, 2000, 0, 500);
  EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrun->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrun","trapENFCal:run");
  EVrun->SetOption("colz");
  EVrun->Write();
  cout << "Writing histogram EVrun" <<  endl;

  TH2F *EVrunBasic = new TH2F("EVrunBasic","EVrunBasic", 1376, 14508, 15884, 2000, 0, 500);
  EVrunBasic->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunBasic->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunBasic","trapENFCal:run",cut1);
  EVrunBasic->SetOption("colz");
  EVrunBasic->Write();
  cout << "Writing histogram EVrunBasic" <<  endl;

  TH2F *EVrunAdv = new TH2F("EVrunAdv","EVrunAdv", 1376, 14508, 15884, 2000, 0, 500);
  EVrunAdv->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunAdv->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunAdv","trapENFCal:run",cut2);
  EVrunAdv->SetOption("colz");
  EVrunAdv->Write();
  cout << "Writing histogram EVrunAdv" <<  endl;

  TH2F *EVrunOld = new TH2F("EVrunOld","EVrunOld", 1376, 14508, 15884, 2000, 0, 500);
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
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS2_cutTwoChan.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
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
  string outFile = "/global/homes/j/jrager/LowE/Data/TuneToECutDS2_chan580.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chan580);
  //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chan580);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,chan580);

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
  string outFile = "/global/homes/j/jrager/LowE/Data/TuneToECutDS2_chan664.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chan664);
  //sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chan664);
  //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,chan664);

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
    string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS2_C1P7D4_Compton.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2_run*_low.root");
    cout << "Adding data files" <<  endl;

    //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,detC1P7D4);

    TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
    ToE->GetYaxis()->SetTitle("T/E (arb)");
    ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
    ToE->SetOption("colz");
    ToE->Write();
    cout << "Writing histogram TuneToE" <<  endl;

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
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS2_cut2Chan_Compton.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2_run*_low.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,cutTwoChan);
    
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

void TuneWFCuts3()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS2_chan580_Compton.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS2_run*_low.root");
  cout << "Adding data files" <<  endl;

  //sprintf(theCut,"%s && %s && %s",ComptonEvents,HEDetCut,chan580);

  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  ToE->SetOption("colz");
  ToE->Write();
  cout << "Writing histogram TuneToE" <<  endl;

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

    string outFile = "/global/u1/j/jrager/LowE/TETMstudyImprovedDS2.root";
  
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS2*.root");
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
    
    TH2F *EVrun = new TH2F("EVrun","EVrun", 1376, 14508, 15884, 120, 0, 30);
    EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
    EVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("EVrun","trapENFCal:run",theCut);
    EVrun->SetOption("colz");
    EVrun->Write();
    cout << "Writing histogram EVrun" <<  endl;
    
    TH2F *trapVrun = new TH2F("trapVrun","trapVrun", 1376, 14508, 15884, 160, -30, 10);
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
    string outFile = "/global/u1/j/jrager/LowE/TETMcutRecImprovedDS2.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS2*.root");
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
  string outFile = "/global/u1/j/jrager/LowE/RunSellectDS2.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/bg-skim/skimDS2_*_low.root");

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  //sprintf(theCut,"%s && %s && %s",basicCut, tetmCut, toeCut);
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH1F *hrun = new TH1F("hrun", "hrun", 1376, 14508, 15884);
  hrun->GetXaxis()->SetTitle("run");
  skimTree->Project("hrun","run",theCut);
  hrun->Write();
  cout << "Writing histogram hrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

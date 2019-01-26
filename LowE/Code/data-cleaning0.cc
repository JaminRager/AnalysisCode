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

void TETM1D();
void TETMvsDetChan();
void TETMvsRun();
void TETMvsEnergy();
void ToEDebuggingTETMg0();
void ToEDebuggingTETMg2l0();
void ToEDebuggingTETMl2();
void DebuggingSpectrumTETMg0();
void DebuggingSpectrumTETMg2l0();
void DebuggingSpectrumTETMl2();
void TestScaling();
void SpectraNoCuts();
void FinalCombinedSpectrum();
void FinalNaturalSpectrum();
void FinalEnrichedSpectrum();
void ToEBands();
void NatToEFinal();
void EnrToEFinal();
void DetectorSelection();
void RunSelection();
void TuneToECut1();
void TuneToECut2();
void TuneToECut3();
void TuneWFCuts();
void TETMCutStudy2D();
void TETMCutStudy1D();
void RunsAndDets();

int main()
{
  //TETM1D();
  //TETMvsDetChan();
  //TETMvsRun();
  TETMvsEnergy();
  //ToEDebuggingTETMg0();
  //ToEDebuggingTETMg2l0();
  //ToEDebuggingTETMl2();
  //DebuggingSpectrumTETMg0();
  //DebuggingSpectrumTETMg2l0();
  //DebuggingSpectrumTETMl2();
  //TestScaling();
  //SpectraNoCuts();             // Spectra without T/E or pulser retrigger (trapETailMin) cut.
  //FinalCombinedSpectrum();
  //FinalNaturalSpectrum();
  //FinalEnrichedSpectrum();
  //ToEBands();
  //NatToEFinal();
  //EnrToEFinal();
  //DetectorSelection();
  //RunSelection();
  //TuneToECut1();
  //TuneToECut2();
  //TuneToECut3();
  //TuneWFCuts();
  //TETMCutStudy2D();          // 1. Makes 2D plots for TETM cut study and saves to output file.
  //TETMCutStudy1D();          // 2. Makes 1D plots for TETM cut study and saves to output file.
  //RunsAndDets();             // 3. 1D Hists of run and detector (channel) to help me pick out noisy runs/detectors.

}
char cut6[10000];
char cut5[10000];
char cut4[10000];
char cut3[10000];
char cut2[10000];
char cut1[100000];
char cut0[10000];
char theCut[10000];
char EwindowCut1[] = "trapENFCal>4.9 && trapENFCal<5.1";
char EwindowCut2[] = "trapENFCal>8.9 && trapENFCal<9.1";
char EwindowCut3[] = "trapENFCal>19.9 && trapENFCal<20.1";
char EwindowCut4[] = "trapENFCal<0.2";
char enrCut[] = "isEnr";
char natCut[] = "isNat";
char tetmCut[] = "trapETailMin < 0";
char toeCut[] = "(((channel==576 || channel==592 || channel==594 || channel==600 || channel==608 || channel==674) && kvorrT/trapENFCal<2.1 && kvorrT/trapENFCal>1.3) || ((channel==598 || channel ==610 || channel==624 || channel==626 || channel==640 || channel==642 || channel==644 || channel==646 || channel==662 || channel==664 || channel==688 || channel==690 || channel==692 || channel==696) && kvorrT/trapENFCal<2.1 && kvorrT/trapENFCal>1.1))";
char HEtoe[] = "((channel==608 && kvorrT/trapENFCal<1.69 && kvorrT/trapENFCal>1.45) || ((channel==576 || channel==592 || channel==594 || channel==600 || channel==674) && kvorrT/trapENFCal<1.57 && kvorrT/trapENFCal>1.33) || ((channel==598 || channel==610 || channel==624 || channel==626 || channel==640 || channel==642 || channel==644 || channel==646 || channel==662 || channel==664 || channel==688 || channel==690 || channel==692 || channel==696) && kvorrT/trapENFCal<1.48 && kvorrT/trapENFCal>1.2))";
char toeOldCut[] = "kvorrT/trapENFCal>1.1 && kvorrT/trapENFCal<2.1";
char basicCut[] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0";
char HEDetCut[] = "channel!=584 && channel!=680 && channel!=676 && channel!=616 && channel!=614 && channel!=656 && channel!=628 && channel!=632 && channel!=630";
char LERunCut[] = "run!=2610 && run!=3341 && run!=3523 && run!=3524 && run!=3529 && run!=3530 && run!=4057 && run!=4125 && run!=4473 && run!=4554 && run!=5248 && run!=5249 && !(run>=5888 && run<=5890) && !(run>=5894 && run<=5902) && run!=6775";
char RunDetCut[] = "!(channel==690 && (run==3523 || run==3524 || run==3530))";
char chanCut1[] = "channel==608";
char chanCut2[] = "(channel==576 || channel==592 || channel==594 || channel==600 || channel==674)"; 
char chanCut3[] = "(channel==598 || channel==610 || channel==624 || channel==626 || channel==640 || channel==642 || channel==644 || channel==646 || channel==662 || channel==664 || channel==688 || channel==690 || channel==692 || channel==696)";
char TETMg0[] = "trapETailMin > 0.0";
char TETMg2l0[] = "trapETailMin > -2.0 && trapETailMin < 0.0";
char TETMl2[] = "trapETailMin < -2.0";
char chan576[] = "(channel==576)";
char chan662[] = "(channel==662)";

void TETM1D()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETM1D_All_DS0.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(theCut,"%s",basicCut);

  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 300, -20, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;

  cout << "Writing histogram TuneToE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}


void TETMvsDetChan()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMvsDetChanDS0.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(cut1,"%s",basicCut);
        
  TH2F *tetmVDetChan = new TH2F("tetmVDetChan", "tetmVDetChan", 800, 550, 1350, 150, -5, 10);
  tetmVDetChan->GetXaxis()->SetTitle("detector channel");
  tetmVDetChan->GetYaxis()->SetTitle("trapETailMin");
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
  string outFile = "/global/u1/j/jrager/LowE/Data/TETMvsRun_ToE_DS0_662.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(cut1,"%s && %s && %s",basicCut,toeCut,chan662);
        
  TH2F *tetmVrun = new TH2F("tetmVrun","tetmVrun", 5847, 2337, 8184, 300, -20, 10);
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
  string outFile = "/global/u1/j/jrager/LowE/TETMvsEnergyDS0bkg.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bkg/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,LERunCut);
        
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

void ToEDebuggingTETMg0()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS0ToE_noTETM.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(cut1,"%s",basicCut);
        
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

void ToEDebuggingTETMg2l0()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS0ToE_TETMg2l0.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(cut1,"%s && %s",basicCut,TETMg2l0);
        
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

void ToEDebuggingTETMl2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS0ToE_TETMl2.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(cut1,"%s && %s",basicCut,TETMl2);
        
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

void DebuggingSpectrumTETMg0()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS0Spect_noTETM.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(theCut,"%s",basicCut);
        
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

void DebuggingSpectrumTETMg2l0()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS0Spect_TETMg2l0.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(theCut,"%s && %s",basicCut,TETMg2l0);
        
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

void DebuggingSpectrumTETMl2()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/DS0Spect_TETMl2.root";
        
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
        
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
        
  sprintf(theCut,"%s && %s",basicCut,TETMl2);
        
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

void TestScaling()
{
  string outFile = "/global/u1/j/jrager/LowE/DS0TestScaling.root";
  cout << "Initalizing outpout file" <<  endl;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut,RunDetCut);
  cout << "Defining cut" <<  endl;
 
  TH1D *enrHE = new TH1D("enrHE", "enrHE", 3000, 0, 3000);
  enrHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrHE->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrHE", "trapENFCal", cut1);
  enrHE->Write();
  cout << "Writing histogram enrHE" <<  endl;

  cout << "done" <<  endl;
    
  f->Close();
}

void SpectraNoCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/DS0NoCuts.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,enrCut);
  sprintf(cut2,"%s",enrCut);
  sprintf(cut3,"%s && %s && %s",basicCut,HEDetCut,natCut);
  sprintf(cut4,"%s",natCut);
    
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
  string outFile = "/global/u1/j/jrager/LowE/CombinedDS0RebinOrig2nd.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut,RunDetCut);
  sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,natCut,RunDetCut);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,natCut);
  sprintf(cut4,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut,RunDetCut);
  sprintf(cut5,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,enrCut,RunDetCut);
  sprintf(cut6,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,enrCut);

  TH1D *natHE = new TH1D("natHE", "natHE", 15000, 0, 3000);
  natHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  natHE->GetYaxis()->SetTitle("cts");
  skimTree->Project("natHE", "trapENFCal", cut3);
  natHE->Write();
  cout << "Writing histogram natHE" <<  endl;

  //TH1D *natLE = new TH1D("natLE", "natLE", 125, 5, 30);
  //natLE->GetXaxis()->SetTitle("trapENFCal (keV)");
  //natLE->GetYaxis()->SetTitle("cts");
  //skimTree->Project("natLE", "trapENFCal", cut2);
  //natLE->Write();
  //cout << "Writing histogram natLE" <<  endl;

  TH1D *enrHE = new TH1D("enrHE", "enrHE", 15000, 0, 3000);
  enrHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrHE->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrHE", "trapENFCal", cut6);
  enrHE->Write();
  cout << "Writing histogram enrHE" <<  endl;

  //TH1D *enrLE = new TH1D("enrLE", "enrLE", 125, 5, 30);
  //enrLE->GetXaxis()->SetTitle("trapENFCal (keV)");
  //enrLE->GetYaxis()->SetTitle("cts");
  //skimTree->Project("enrLE", "trapENFCal", cut5);
  //enrLE->Write();
  //cout << "Writing histogram enrLE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void ToEBands()
{
  string outFile = "/global/u1/j/jrager/LowE/ToEDS0BandsCalib.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,chanCut1);
  sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,chanCut2);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,chanCut3);

  TH2F *top = new TH2F("top", "top", 1000, 0, 100, 400, 0, 10);
  top->GetYaxis()->SetTitle("T/E (arb)");
  top->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("top","kvorrT/trapENFCal:trapENFCal",cut1);
  top->SetOption("colz");
  top->Write();
  cout << "Writing histogram top" <<  endl;

  TH2F *mid = new TH2F("mid", "mid", 1000, 0, 100, 400, 0, 10);
  mid->GetYaxis()->SetTitle("T/E (arb)");
  mid->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("mid","kvorrT/trapENFCal:trapENFCal",cut2);
  mid->SetOption("colz");
  mid->Write();
  cout << "Writing histogram mid" <<  endl;

  TH2F *bottom = new TH2F("bottom", "bottom", 1000, 0, 100, 400, 0, 10);
  bottom->GetYaxis()->SetTitle("T/E (arb)");
  bottom->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("bottom","kvorrT/trapENFCal:trapENFCal",cut3);
  bottom->SetOption("colz");
  bottom->Write();
  cout << "Writing histogram bottom" <<  endl;

  cout << "done" <<  endl;

  f->Close();

}

void NatToEFinal()
{
  string outFile = "/global/u1/j/jrager/LowE/NatToEDS0Final.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,natCut);
    
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
  string outFile = "/global/u1/j/jrager/LowE/ToEDS0EnrFinal.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,enrCut);
    
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

void FinalNaturalSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/UnscaledNatDS0orig.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut,RunDetCut);
  sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,natCut,RunDetCut);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,natCut);
  //Double_t DS0exposureEnr = 4/478.0;

  //TH1D *HE = new TH1D("HE", "HE", 11920, 20, 3000);
  //HE->GetXaxis()->SetTitle("trapENFCal (keV)");
  //HE->GetYaxis()->SetTitle("cts");
  //skimTree->Project("HE", "trapENFCal", cut1);
  //HE->Scale(DS0exposureEnr);
  //HE->Write();
  //cout << "Writing histogram HE" <<  endl;

  TH1D *LE = new TH1D("LE", "LE", 12000, 0, 3000);
  LE->GetXaxis()->SetTitle("trapENFCal (keV)");
  LE->GetYaxis()->SetTitle("cts");
  skimTree->Project("LE", "trapENFCal", cut3);
  //LE->Scale(DS0exposureEnr);
  LE->Write();
  cout << "Writing histogram LE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void FinalEnrichedSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/UnscaledEnrDS0orig.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut,RunDetCut);
  sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,enrCut,RunDetCut);
  sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,enrCut);
  //sprintf(cut1,"%s",EwindowCut1);
  //Double_t DS0exposureEnr = 4/478.0;

  //TH1D *HE = new TH1D("HE", "HE", 11920, 20, 3000);
  //HE->GetXaxis()->SetTitle("trapENFCal (keV)");
  //HE->GetYaxis()->SetTitle("cts");
  //skimTree->Project("HE", "trapENFCal", cut1);
  //HE->Scale(DS0exposureEnr);
  //HE->Write();
  //cout << "Writing histogram HE" <<  endl;

  TH1D *LE = new TH1D("LE", "LE", 12000, 0, 3000);
  LE->GetXaxis()->SetTitle("trapENFCal (keV)");
  LE->GetYaxis()->SetTitle("cts");
  skimTree->Project("LE", "trapENFCal", cut3);
  //LE->Scale(DS0exposureEnr);
  LE->Write();
  cout << "Writing histogram LE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void DetectorSelection()
{
  string outFile = "/global/u1/j/jrager/LowE/DetSelectDS0.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(theCut,"%s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut);

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  det->GetYaxis()->SetTitle("counts");
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH2F *detVrun = new TH2F("detVrun", "detVrun", 5847, 2337, 8184, 800, 550, 1350);
  det->GetXaxis()->SetTitle("run");
  det->GetYaxis()->SetTitle("detector channel");
  skimTree->Project("detVrun","channel:run",theCut);
  detVrun->SetOption("colz");
  detVrun->Write();
  cout << "Writing histogram detVrun" <<  endl;

  cout << theCut << endl;

  cout << "done" <<  endl;

  f->Close();
}

void RunSelection()
{
  string outFile = "/global/u1/j/jrager/LowE/RunSelectDS0.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/bg-skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut0,"%s",HEDetCut);
  sprintf(cut1,"%s && %s",basicCut,HEDetCut);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut);
  sprintf(cut3,"%s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut);

  TH2F *EVrun = new TH2F("EVrun","EVrun", 5847, 2337, 8184, 2000, 0, 500);
  EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrun->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrun","trapENFCal:run",cut0);
  EVrun->SetOption("colz");
  EVrun->Write();
  cout << "Writing histogram EVrun" <<  endl;
  cout << "cut0" << endl;
  cout << cut0 << endl;

  TH2F *EVrunBasic = new TH2F("EVrunBasic","EVrunBasic", 5847, 2337, 8184, 2000, 0, 500);
  EVrunBasic->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunBasic->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunBasic","trapENFCal:run",cut1);
  EVrunBasic->SetOption("colz");
  EVrunBasic->Write();
  cout << "Writing histogram EVrunBasic" <<  endl;
  cout << "cut1" << endl;

  TH2F *EVrunAdv = new TH2F("EVrunAdv","EVrunAdv", 5847, 2337, 8184, 2000, 0, 500);
  EVrunAdv->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunAdv->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunAdv","trapENFCal:run",cut2);
  EVrunAdv->SetOption("colz");
  EVrunAdv->Write();
  cout << "Writing histogram EVrunAdv" <<  endl;
  cout << "cut2" << endl;
  cout << cut2 << endl;

  TH2F *EVrunOld = new TH2F("EVrunOld","EVrunOld", 5847, 2337, 8184, 2000, 0, 500);
  EVrunOld->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunOld->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunOld","trapENFCal:run",cut3);
  EVrunOld->SetOption("colz");
  EVrunOld->Write();
  cout << "Writing histogram EVrunOld" <<  endl;
  cout << "cut3" << endl;
  cout << cut3 << endl;

  cout << "done" <<  endl;

  f->Close();
}

void TuneToECut1()
{
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS0_topBand.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chanCut1);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chanCut1);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut3,chanCut1);
    
  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut1);
  at5k->Write();
  cout << "Writing histogram at5k" <<  endl;
    
  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut2);
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;
    
  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut3);
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneToECut2()
{
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS0_middleBand.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chanCut2);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chanCut2);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut3,chanCut2);
    
  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut1);
  at5k->Write();
  cout << "Writing histogram at5k" <<  endl;
    
  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut2);
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;
    
  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut3);
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void TuneToECut3()
{
  string outFile = "/global/u1/j/jrager/LowE/TuneToECutDS0_bottomBand.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,chanCut3);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,chanCut3);
  sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut3,chanCut3);

  TH1F *at5k = new TH1F("at5k", "at5k", 400, 0, 10);
  at5k->GetYaxis()->SetTitle("counts");
  at5k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at5k","kvorrT/trapENFCal",cut1);
  at5k->Write();
  cout << "Writing histogram at5k" <<  endl;

  TH1F *at9k = new TH1F("at9k", "at9k", 400, 0, 10);
  at9k->GetYaxis()->SetTitle("counts");
  at9k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at9k","kvorrT/trapENFCal",cut2);
  at9k->Write();
  cout << "Writing histogram at9k" <<  endl;

  TH1F *at20k = new TH1F("at20k", "at20k", 400, 0, 10);
  at20k->GetYaxis()->SetTitle("counts");
  at20k->GetXaxis()->SetTitle("T/E (arb)");
  skimTree->Project("at20k","kvorrT/trapENFCal",cut3);
  at20k->Write();
  cout << "Writing histogram at20k" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TuneWFCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/TuneWFCutsDS0.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/wisecg/cal/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;

  sprintf(theCut,"%s && %s && %s",basicCut,HEDetCut,toeCut);

  //TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  //ToE->GetYaxis()->SetTitle("T/E (arb)");
  //ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  //skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",theCut);
  //ToE->SetOption("colz");
  //ToE->Write();

  TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
  htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
  skimTree->Project("htrapETailMin","trapETailMin",theCut);
  htrapETailMin->Write();
  cout << "Writing histogram htrapETailMin" <<  endl;

  cout << "Writing histogram TuneToE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TETMCutStudy2D()
{
    gStyle->SetOptStat(0);

    string outFile = "/global/u1/j/jrager/LowE/TETMstudyImprovedDS0.root";
  
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS0*.root");
    cout << "Adding data files" <<  endl;

    TH2F *twoD = new TH2F("twoD", "twoD", 120, 0, 30, 160, -30, 10);
    twoD->GetYaxis()->SetTitle("trapETailMin");
    twoD->GetXaxis()->SetTitle("trapENFCal (keV)");
    //sprintf(theCut,"%s && %s",basicCut, wfdcCut);
    sprintf(theCut,"%s",basicCut);
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
    
    TH2F *EVrun = new TH2F("EVrun","EVrun", 5847, 2337, 8184, 120, 0, 30);
    EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
    EVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("EVrun","trapENFCal:run",theCut);
    EVrun->SetOption("colz");
    EVrun->Write();
    cout << "Writing histogram EVrun" <<  endl;
    
    TH2F *trapVrun = new TH2F("trapVrun","trapVrun", 5847, 2337, 8184, 160, -30, 10);
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
    string outFile = "/global/u1/j/jrager/LowE/TETMcutRecDS0.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS0*.root");
    cout << "Adding data files" <<  endl;

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 130, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    //sprintf(theCut,"%s && %s",basicCut, wfdcCut);
    sprintf(theCut,"%s",basicCut);
    skimTree->Project("htrapETailMin","trapETailMin",theCut);
    htrapETailMin->Write();
    cout << "Writing histogram htrapETailMin" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void RunsAndDets()
{
  string outFile = "/global/u1/j/jrager/LowE/TETMrunsAndDetsImprovedDS0.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS0*.root");

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  //sprintf(theCut,"%s && %s",basicCut, wfdcCut);
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH1F *hrun = new TH1F("hrun", "hrun", 5847, 2337, 8184);
  hrun->GetXaxis()->SetTitle("run");
  skimTree->Project("hrun","run",theCut);
  hrun->Write();
  cout << "Writing histogram hrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

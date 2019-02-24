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
void AnalysisSpectrumCombined();
void ComptonSpectrum();
void BlindRunSelect();
void SpectraNoCuts();
void FinalCombinedSpectrumOld();
void TuneToECut1();
void TuneToECut2();
void ToEBands();
void NatToEFinal();
void EnrToEFinal();
void FinalNaturalSpectrum();
void FinalEnrichedSpectrum();
void NatToENoCuts();
void EnrToENoCuts();
void DetectorSelection();
void ToE1D();
void TuneWFCuts1();
void TuneWFCuts2();
void TestWFCuts();
void Band();
void Channel();
void RunSelection();
void EvsRunBad();
void TETMCutStudy2D();
void ToverEGood();
void ToverEBad();
void EnrichedSpectrumGood();
void EnrichedSpectrumBad();
void NaturalSpectrum();
void TETMCutStudy1D();
void RunsAndDets();
void AddDS0();
void AddDS1();
void AddDS2();
void AddDS3();
void AddDS4();
void AddDS5();
void AddDS6();

int main()
{
  //CutEfficiency1();
  //CutEfficiency2();
  //CutEfficiency3();
  //CutEfficiency4();
  //CutEfficiency5();
  //AnalysisSpectrumCombined();
  //ComptonSpectrum();
  //BlindRunSelect();
  //SpectraNoCuts();         // Spectra without T/E or pulser retrigger (trapETailMin) cut. 
  //FinalCombinedSpectrumOld();
  //TuneToECut1();              // 1D histograms of T/E at 10 & 20k.  For tuning T/E cut.
  //TuneToECut2();
  //ToEBands();
  //NatToEFinal();             // Official analysis stream. Final ToE distribution for natural detectors with all cuts.
  //EnrToEFinal();             // Official analysis stream. Final ToE distribution for enriched detectors with all cuts.
  //FinalNaturalSpectrum();    // Official analysis stream. Final natural spectrum after all cuts have been tuned and applied, also with run/detector selection.
  //FinalEnrichedSpectrum();   // Official analysis stream. Final enriched spectrum after all cuts have been tuned and applied, also with run/detector selection.    
  //NatToENoCuts();            // Official analysis stream. ToE distribution for natural detectors, no cuts.
  //EnrToENoCuts();            // Official analysis stream. ToE distribution for enriched detectors, no cuts.
  //DetectorSelection();       // Official analysis stream. Let's me do my final run/detector selection.  Applies tuned TETM and ToE cut as well as HE detector selection.
  //ToE1D();                   // Relic. Crazy idea I had to make a 1D histogram of T/E
  //Band();                    // Relic. Used when was confused about the double peak in the T/E distributions.  Makes energy histograms for different T/E - compare signal to noise.
  //TestWFCuts();              // Relic. Applies ToE cut to TETM histogram and TETM cut to ToE distribution to see what effect each cut has on other parameter. CALIBRATION DATA.
  TuneWFCuts1();
  //TuneWFCuts2();              // Official analysis stream. Tunes TETM and ToE cuts with CALIBRATION DATA.  Only applies the basicCut in making it's histograms.  
  //Channel();                 // Relic. 1D histogrrams of channel rate with and withoug cuts. Some early code when I was develooping procedure for detector selection.
  //RunSelection();              // Official analysis stream.  Run this before DetectorSelection() to pick out the noisy runs.  Applies tuned TETM & ToE cuts + HE detector selection.  Also makes distributions with only basicCut and with Vorren's ToE cut to make sure I am not overcuting with my ToE.
  //EvsRunBad();               // Relic. Don't use.  E vs Run 2D histograms of rejected runs.
  //TETMCutStudy2D();          // Relic. When I was helping Clint tune TETM cuts.
  //ToverEGood();              // Relic. Don't use. T/E distribution of accepted runs.
  //ToverEBad();               // Relic. Don't use. T/E distribution of rejected runs.
  //EnrichedSpectrumGood();    // Relic. Don't use. Enriched spectra for accepted runs.
  //EnrichedSpectrumBad();     // Relic. Don't use. Enriched spectra for bad runs
  //NaturalSpectrum();         // Relic. Natural detector spectrum.
  //TETMCutStudy1D();          // Relic. Makes 1D plots for TETM cut study and saves to output file.
  //RunsAndDets();             // Relic. When I was still developing run/detector selection procedure. 1D Hists of run and detector to help me pick out noisy runs/detectors.
  //AddDS0();                  // For adding histograms from multiple files together into a single composite histogram.  Might be useful in future.
  //AddDS1();
  //AddDS2();
  //AddDS3();
  //AddDS4();
  //AddDS5();
  //AddDS6();
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
char EwindowCut1[] = "trapENFCal>9 && trapENFCal<14";
char EwindowCut2[] = "trapENFCal>20 && trapENFCal<25";
char EwindowCut3[] = "trapENFCal<0.2";
char EwindowCut4[] = "trapENFCal>=5";
char EwindowCut5[] = "trapENFCal>5 && trapENFCal<10";
char basicCut[] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0";
char invBasicCut[] = "gain!=0 && mH=!1 && !isGood && P==0 && D==0";
char tetmCut[] = "(((channel==584 || channel==610 || channel==658 || channel==660 || channel==1172 || channel==1176) && trapETailMin<-0.1) || ((channel==592 || channel==608 || channel==624 || channel==626 || channel==628 || channel==632 || channel==640 || channel==648 || channel==662 || channel==672 || channel==674 || channel==680 || channel==688 || channel==690 || channel==694 || channel==1106 || channel==1124 || channel==1128 || channel==1204 || channel==1232 || channel==1236 || channel==1298 || channel==1302 || channel==1330) && trapETailMin<-0.2) || ((channel==598 || channel==1120 || channel==1170 || channel==1174 || channel==1208 || channel==1332) && trapETailMin<-0.3) || (channel==614 && trapETailMin<-0.4) || (channel==678 && trapETailMin<0.1))";
char tetmOldCut[] = "trapETailMin < -0.2";
char invTETMCut[] = "trapETailMin >= 0.3";
char tetmKrisCut[] = "trapETailMin < 0";
char enrCut[] = "isEnr";
char natCut[] = "isNat";
char toeKrisCut[] = "kvorrT/trapENFCal>1.1 && kvorrT/trapENFCal<2.1";
char oldLEtoe[] = "((channel!=660 && channel!=1302 && kvorrT/trapENFCal<2.1 && kvorrT/trapENFCal>1.1) || ((channel==660 || channel==1302) && kvorrT/trapENFCal<1.7 && kvorrT/trapENFCal>0.7))";
char oldHEtoe[] = "((channel!=660 && channel!=1302 && kvorrT/trapENFCal<1.66 && kvorrT/trapENFCal>1.12) || ((channel==660 || channel==1302) && kvorrT/trapENFCal<1.24 && kvorrT/trapENFCal>0.82))";
char LEtoe[] = "((channel!=660 && channel!=1302 && kvorrT/trapENFCal<2.0 && kvorrT/trapENFCal>1.05) || ((channel==660 || channel==1302) && kvorrT/trapENFCal<1.5 && kvorrT/trapENFCal>0.85))";
char HEtoe[] = "((channel!=660 && channel!=1302 && kvorrT/trapENFCal<1.75 && kvorrT/trapENFCal>1.05) || ((channel==660 || channel==1302) && kvorrT/trapENFCal<1.25 && kvorrT/trapENFCal>0.8))";
char ToE5k[] = "((channel!=660 && channel!=1302 && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.97) || ((channel==660 || channel==1302) && kvorrT/trapENFCal>0.49 && kvorrT/trapENFCal<1.63))";
char ToE_EDependent[] = "((trapENFCal<9 && ((channel!=660 && channel!=1302 && kvorrT/trapENFCal>0.83 && kvorrT/trapENFCal<1.97) || ((channel==660 || channel==1302) && kvorrT/trapENFCal>0.49 && kvorrT/trapENFCal<1.63))) || (trapENFCal>=9 && trapENFCal<20 && ((channel!=600 && channel!=1302 && kvorrT/trapENFCal>1.00 && kvorrT/trapENFCal<1.78) || ((channel==600 || channel==1302) && kvorrT/trapENFCal>0.70 && kvorrT/trapENFCal<1.42))) || (trapENFCal>=20 && ((channel!=660 && channel!=1302 && kvorrT/trapENFCal>1.12 && kvorrT/trapENFCal<1.66) || ((channel==660 || channel==1302) && kvorrT/trapENFCal>0.82 && kvorrT/trapENFCal<1.24))))";
char invToECut[] = "kvorrT/trapENFCal<=1 || kvorrT/trapENFCal>=2";
char toeBand[] = "kvorrT/trapENFCal>0.9 && kvorrT/trapENFCal<1.1";
char toeSig[] = "kvorrT/trapENFCal>1.15 && kvorrT/trapENFCal<1.55";
char toeNoise[] = "kvorrT/trapENFCal<0.9";
//char noisyRunsCut[] = "run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run<20966) && !(run>21133 && run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952";
//char noisyDetCut[] = "channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
char HEDetCut[] = "channel!=664 && channel!=665 && channel!=692 && channel!=693 && channel!=642 && channel!=643 && channel!=616 && channel!=617 && channel!=600 && channel!=601 && channel!=696 && channel!=697 && channel!=630 && channel!=631 && channel!=1124 && channel!=1125 && channel!=1126 && channel!=1127 && channel!=1110 && channel!=1111 && channel!=1108 && channel!=1109 && channel!=1122 && channel!=1123 && channel!=1202 && channel!=1203 && channel!=1206 && channel!= 1207 && channel!=1168 && channel!=1169 && channel!=1304 && channel!= 1305 && channel!=1332 && channel!=1333 && channel!=1296 && channel!=1297 && channel!=1328 && channel!=1329 && channel!=1234 && channel!=1235 && channel!=1268 && channel!=1269 && channel!=1238 && channel!=1239";
char HERunCut[] = "run!=25672 && run!=25936 && run!=26748 && !(run>=26773 && run<=26776) && !(run>=26780 && run<=26805) && !(run>=28300 && run<=28320) && run!=30985";
char HEDetailedSelection[] = "!(channel==1126 && run>=30058 && run<=30325) && !(channel==1110 && run>=29697 && run<=30325) && !(channel==1204 && run>=29697 && run<=29913) && !(channel==1204 && run>=30346 && run<=30941) && !(channel==1204 && run>=33509 && run<=33908) && !(channel==1174 && run>=29697 && run<=30325) && !(channel==626 && run>=35954 && run<=36537) && !(channel==616 && run>=25676 && run<=37086) && !(channel==1170 && run>=25676 && run<=34180) && !(channel==1174 && run>=30861 && run<=37086) && !(channel==1332 && run>=25676 && run<=29988) && !(channel==584 && run>=36124 && run<=36146) && !(channel==674 && run>=36029 && run<=36047) && !(channel>=1100 && channel<=1400 && run>=29884 && run<=29889) && !(channel>=1100 && channel<=1400 && run>=30284 && run<=30285) && !(channel>=1100 && channel<=1400 && run>=33886 && run<=33889) && !(channel==584 && run>=28300 && run<=29355) && !(channel==584 && run>=36053 && run<=37088) && !(channel==592 && run>=28300 && run<=28750) && !(channel==598 && run>=28300 && run<=28750) && !(channel==608 && run>=28300 && run<=29355) && !(channel==608 && run>=36053 && run<=37088) && !(channel==610 && run>=28300 && run<=28467) && !(channel==610 && run>=36053 && run<=37088) && !(channel==614 && run>=28300 && run<=29355) && !(channel==624 && run>=28300 && run<=29355) && !(channel==624 && run>=36053 && run<=37088) && !(channel==626 && run>=28300 && run<=29355) && !(channel==626 && run>=36053 && run<=36537) && !(channel==628 && run>=28300 && run<=32416) && !(channel==628 && run>=36053 && run<=37088) && !(channel==632 && run>=28300 && run<=28467) && !(channel==632 && run>=36053 && run<=37088) && !(channel==658 && run>=28300 && run<=28750) && !(channel==662 && run>=28300 && run<=29355) && !(channel==674 && run>=28300 && run<=29524) && !(channel==678 && run>=28300 && run<=28969) && !(channel==678 && run>=36053 && run<=37088) && !(channel==688 && run>=28300 && run<=31684) && !(channel==688 && run>=36053 && run<=37088) && !(channel==690 && run>=28300 && run<=30327) && !(channel==690 && run>=36053 && run<=37088) && !(channel==694 && run>=28300 && run<=28969) && !(channel==694 && run>=36053 && run<=37088) && !(channel==1106 && run>=28300 && run<=32416) && !(channel==1106 && run>=33710 && run<=34500) && !(channel==1120 && run>=28300 && run<=29355) && !(channel==1120 && run>=29718 && run<=30783) && !(channel==1120 && run>=31791 && run<=32160) && !(channel==1120 && run>=33710 && run<=34074) && !(channel==1174 && run>=28300 && run<=28969) && !(channel==1204 && run>=28300 && run<=29355) && !(channel==1204 && run>=30078 && run<=31324) && !(channel==1204 && run>=31791 && run<=32416) && !(channel==1208 && run>=28300 && run<=33059) && !(channel==1208 && run>=33710 && run<=35030) && !(channel==1236 && run>=28300 && run<=28467) && !(channel==1298 && run>=28300 && run<=28969) && !(channel==1302 && run>=25672 && run<=34456) && !(channel==1330 && run>=33710 && run<=33909) && !(channel==1332 && run>=28300 && run<=28467) && !(channel==1332 && run>=29718 && run<=29989) && !(channel==1302 && run>=25672 && run<=26236) && !(channel==1302 && run>=28322 && run<=28990) && !(channel==1332 && run>=29915 && run<=29934) && !(channel==626 && run>=36008 && run<=36100) && !(channel==678 && run>=36008 && run<=36100)";
//char RunDetCutOld[] = "!(channel==1106 && run<26806)";
char RunDetCut[] = "!(channel==674 && run>=36034 && run<=36047)";
char twoChan[] = "(channel==660 || channel==1302)";
char cutTwoChan[] = "(channel!=660 && channel!=1302)";
char HECut[] = "trapENFCal>=80 && trapENFCal<=2000";
char LECut[] = "trapENFCal<80";
char LEcutoff[] = "trapENFCal>=36";  // setting cutoff at 9keV with 0.25keV binning
char Mult2Events[] = "mH==2";
char ComptonManual[] = "(mH==2 && (trapENFCal[0] + trapENFCal[1])>237.12 && (trapENFCal[0] + trapENFCal[1])<239.55)";
char chan662[] = "channel==662";
char chan660[] = "channel==660";
char chan658[] = "channel==658";
char chan648[] = "channel==648";
char chan640[] = "channel==640";
char chan610[] = "channel==610";
char chan608[] = "channel==608";
char chan584[] = "channel==584";
char chan624[] = "channel==624";
char chan628[] = "channel==628";
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
  string outFile = "/global/u1/j/jrager/LowE/EfficiencyDS6chan640.root";
    
  //UInt_t runNumb;
  //std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan640);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan640);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS6chan610.root";
    
  //UInt_t runNumb;
  //std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan610);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan610);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS6chan648.root";
    
  //UInt_t runNumb;
  //std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan648);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan648);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS6chan640.root";
    
  //UInt_t runNumb;
  //std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan640);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan640);
    
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
  string outFile = "/global/u1/j/jrager/LowE/Data/EfficiencyDS6chan640.root";
    
  //UInt_t runNumb;
  //std::string dataFile;
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
  cout << "Data files added" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",HEDetCut,ComptonManual,ToE_EDependent,tetmCut,chan640);
  sprintf(cut2,"%s && %s && %s",HEDetCut,ComptonManual,chan640);
    
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

void AnalysisSpectrumCombined()
{
  string outFile = "/global/u1/j/jrager/LowE/AnalysisSpectDS6Nat.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6BG_Official/*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,HERunCut,RunDetCut,natCut);
  
  TH1D *spect = new TH1D("spect", "spect", 12000, 0, 3000);
  spect->GetXaxis()->SetTitle("trapENFCal (keV)");
  spect->GetYaxis()->SetTitle("cts");
  skimTree->Project("spect", "trapENFCal", cut1);
  spect->Write();
  cout << "Writing histogram spect" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void ComptonSpectrum()
{
  string outFile = "/global/u1/j/jrager/LowE/Data/SumSpectrumDS6.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/LATDATADIR/cal/skim/skimDS6_*_low.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s",Mult2Events,HEDetCut,HERunCut,RunDetCut);
    
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
  string outFile = "/global/u1/j/jrager/LowE/BlindRunSelectDS6_5kThresh.root";
  cout << "Creating outpout file" << outFile <<  endl;
   
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" << cout << outFile <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V4Skim3-19-18/*.root");
  cout << "Adding data files" <<  endl;
    
  sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,ToE5k,HEDetCut,EwindowCut4);
    
  cout << "Usig cut" << cut1 << endl;
    
  TH1F *run = new TH1F("run", "run",  11182, 25704, 36886);
  run->GetXaxis()->SetTitle("run number");
  run->GetYaxis()->SetTitle("counts");
  skimTree->Project("run","run",cut1);
  run->Write();
  cout << "Writing histogram det" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
}

void SpectraNoCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/DS6NoCuts.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V3Skim12-05-17/*.root");
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

void FinalCombinedSpectrumOld()
{
  string outFile = "/global/u1/j/jrager/LowE/CombinedDS6_Newest.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V3Skim12-05-17/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut,RunDetCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,natCut,RunDetCut);
  //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,natCut);
  //sprintf(cut4,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut,RunDetCut);
  //sprintf(cut5,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,enrCut,RunDetCut);
  //sprintf(cut6,"%s && %s && %s && %s && %s",basicCut,tetmCut,toeOldCut,HEDetCut,enrCut);

  TH1D *natHE = new TH1D("natHE", "natHE", 15000, 0, 3000);
  natHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  natHE->GetYaxis()->SetTitle("cts");
  skimTree->Project("natHE", "trapENFCal", cut1);
  natHE->Write();
  cout << "Writing histogram natHE" <<  endl;

  TH1D *natLE = new TH1D("natLE", "natLE", 125, 5, 30);
  natLE->GetXaxis()->SetTitle("trapENFCal (keV)");
  natLE->GetYaxis()->SetTitle("cts");
  skimTree->Project("natLE", "trapENFCal", cut2);
  natLE->Write();
  cout << "Writing histogram natLE" <<  endl;

  TH1D *enrHE = new TH1D("enrHE", "enrHE", 15000, 0, 3000);
  enrHE->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrHE->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrHE", "trapENFCal", cut4);
  enrHE->Write();
  cout << "Writing histogram enrHE" <<  endl;

  TH1D *enrLE = new TH1D("enrLE", "enrLE", 125, 5, 30);
  enrLE->GetXaxis()->SetTitle("trapENFCal (keV)");
  enrLE->GetYaxis()->SetTitle("cts");
  skimTree->Project("enrLE", "trapENFCal", cut5);
  enrLE->Write();
  cout << "Writing histogram enrLE" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void ToEBands()
{
  string outFile = "/global/u1/j/jrager/LowE/ToEDS6BandsCalib.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  TChain *skimTree = new TChain("skimTree");
  //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V3Skim12-05-17/*.root");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/*.root");
  cout << "Adding data files" <<  endl;
    
  //sprintf(cut1,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,cutTwoChan);
  //sprintf(cut2,"%s && %s && %s && %s && %s",basicCut,tetmCut,HEDetCut,RunDetCut,twoChan);
       
  TH2F *top = new TH2F("top", "top", 1000, 0, 100, 400, 0, 10);
  top->GetYaxis()->SetTitle("T/E (arb)");
  top->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("top","kvorrT/trapENFCal:trapENFCal",cut1);
  top->SetOption("colz");
  top->Write();
  cout << "Writing histogram top" <<  endl;
    
  TH2F *bottom = new TH2F("bottom", "bottom", 1000, 0, 100, 400, 0, 10);
  bottom->GetYaxis()->SetTitle("T/E (arb)");
  bottom->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("bottom","kvorrT/trapENFCal:trapENFCal",cut2);
  bottom->SetOption("colz");
  bottom->Write();
  cout << "Writing histogram bottom" <<  endl;
    
  cout << "done" <<  endl;
    
  f->Close();
    
}

void NatToEFinal()
{
  string outFile = "/global/u1/j/jrager/LowE/NatToEDS6Final.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V4Skim3-19-18/*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s",basicCut,tetmCut,HEDetCut,natCut);

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
  string outFile = "/global/u1/j/jrager/LowE/EnrToEDS6Final.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V4Skim3-19-18/*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s",basicCut,tetmCut,HEDetCut,enrCut);

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
  string outFile = "/global/u1/j/jrager/LowE/UnscaledNatSpectDS6.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V3Skim12-05-17/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,natCut,RunDetCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,natCut,RunDetCut);
  //sprintf(cut1,"%s",EwindowCut1);
  //Double_t DS6exposureEnr = 6/603.6;

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
  string outFile = "/global/u1/j/jrager/LowE/UnscaledEnrSpectDS6.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V3Skim12-05-17/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,HEtoe,HEDetCut,enrCut,RunDetCut);
  //sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,toeCut,HEDetCut,enrCut,RunDetCut);
  //sprintf(cut1,"%s",EwindowCut1);
  //Double_t DS6exposureEnr = 6/603.6;

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

void NatToENoCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/NatToENoCuts.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V3Skim12-05-17/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s",natCut);

  TH2F *noCuts = new TH2F("noCuts", "noCuts", 1000, 0, 100, 400, 0, 10);
  noCuts->GetYaxis()->SetTitle("T/E (arb)");
  noCuts->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("noCuts","kvorrT/trapENFCal:trapENFCal",cut1);
  noCuts->SetOption("colz");
  noCuts->Write();
  cout << "Writing histogram noCuts" <<  endl;

  cout << "done" <<  endl;

  f->Close();

}

void EnrToENoCuts()
{
  string outFile = "/global/u1/j/jrager/LowE/EnrToENoCuts.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V3Skim12-05-17/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s",enrCut);

  TH2F *noCuts = new TH2F("noCuts", "noCuts", 1000, 0, 100, 400, 0, 10);
  noCuts->GetYaxis()->SetTitle("T/E (arb)");
  noCuts->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("noCuts","kvorrT/trapENFCal:trapENFCal",cut1);
  noCuts->SetOption("colz");
  noCuts->Write();
  cout << "Writing histogram noCuts" <<  endl;

  cout << "done" <<  endl;

  f->Close();

}

void DetectorSelection()
{
  string outFile = "/global/u1/j/jrager/LowE/DS6DetSelect_5kThresh_correctedCuts.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6BG_Official/*.root");
  cout << "Adding data files" <<  endl;

  sprintf(cut1,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,HERunCut,EwindowCut4);

  TH1F *det = new TH1F("det", "det", 1440, 0, 1440);
  det->GetXaxis()->SetTitle("detector channel");
  det->GetYaxis()->SetTitle("counts");
  skimTree->Project("det","channel",cut1);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH2F *detVrun = new TH2F("detVrun", "detVrun", 11182, 25704, 36886, 1440, 0, 1440);
  det->GetXaxis()->SetTitle("run");
  det->GetYaxis()->SetTitle("detector channel");
  skimTree->Project("detVrun","channel:run",cut1);
  detVrun->SetOption("colz");
  detVrun->Write();
  cout << "Writing histogram detVrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void ToE1D()
{
    string outFile = "/global/u1/j/jrager/LowE/ToE1D_DS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s",basicCut);

    TH1F *ToE1D = new TH1F("ToE1D", "ToE1D", 400, 0, 10);
    ToE1D->GetXaxis()->SetTitle("T/E (arb)");
    ToE1D->GetYaxis()->SetTitle("cts");
    skimTree->Project("ToE1D","kvorrT/trapENFCal",cut1);
    ToE1D->Write();
    cout << "Writing histogram ToE1D" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void Band()
{
    string outFile = "/global/u1/j/jrager/LowE/BandDS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/*.root");

    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s && %s && %s", basicCut, enrCut, toeBand);
    //sprintf(cut2,"%s && %s && %s", basicCut, enrCut, toeSig);
    //sprintf(cut3,"%s && %s && %s", basicCut, enrCut, toeNoise);

    TH1D *Band = new TH1D("Band", "Band", 12000, 0, 3000);
    Band->GetXaxis()->SetTitle("trapENFCal (keV)");
    Band->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("Band", "trapENFCal", cut1);
    //Double_t DS6exposureEnr = 4/537;
    //Band->Scale(DS6exposureEnr);
    Band->Write();

    TH1D *Sig = new TH1D("Sig", "Sig", 12000, 0, 3000);
    Sig->GetXaxis()->SetTitle("trapENFCal (keV)");
    Sig->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("Sig", "trapENFCal", cut2);
    //Sig->Scale(DS6exposureEnr);
    Sig->Write();

    TH1D *Noise = new TH1D("Noise", "Noise", 12000, 0, 3000);
    Noise->GetXaxis()->SetTitle("trapENFCal (keV)");
    Noise->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("Noise", "trapENFCal", cut3);
    //Noise->Scale(DS6exposureEnr);
    Noise->Write();

    cout << "Writing histogram EnrSpect" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void TestWFCuts()
{
    string outFile = "/global/u1/j/jrager/LowE/TestWFCutsS1.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/cal-lat/latSkimDS1*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s && %s",basicCut,tetmCut);
    //sprintf(cut2,"%s && %s",basicCut,toeCut);

    TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
    ToE->GetYaxis()->SetTitle("T/E (arb)");
    ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",cut1);
    ToE->SetOption("colz");
    ToE->Write();
    cout << "Writing histogram TuneToE" <<  endl;

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    skimTree->Project("htrapETailMin","trapETailMin",cut2);
    htrapETailMin->Write();
    cout << "Writing histogram htrapETailMin" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void TuneToECut1()
{
    string outFile = "/global/u1/j/jrager/LowE/Data/TuneToECutDS6_cutTwoChan.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/LATDATADIR/cal/skim/skimDS6_*_low.root");
    cout << "Adding data files" <<  endl;

    sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,cutTwoChan);
    sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,cutTwoChan);
    sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,cutTwoChan);

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
    string outFile = "/global/u1/j/jrager/LowE/Data/TuneToECutDS6_twoChan.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/LATDATADIR/cal/skim/skimDS6_*_low.root");
    cout << "Adding data files" <<  endl;

    sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut1,twoChan);
    sprintf(cut2,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut2,twoChan);
    //sprintf(cut3,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut3,twoChan);
    sprintf(cut4,"%s && %s && %s && %s",basicCut,HEDetCut,EwindowCut5,twoChan);

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
    string outFile = "/global/u1/j/jrager/LowE/TuneWFCutsDS6_Compton.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
    cout << "Adding data files" <<  endl;

    sprintf(cut1,"%s && %s && %s",ComptonManual,HEDetCut,HERunCut);

    TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
    ToE->GetYaxis()->SetTitle("T/E (arb)");
    ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",cut1);
    ToE->SetOption("colz");
    ToE->Write();

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    skimTree->Project("htrapETailMin","trapETailMin",cut1);
    htrapETailMin->Write();
    cout << "Writing histogram htrapETailMin" <<  endl;

    cout << "Writing histogram TuneToE" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void TuneWFCuts2()
{
    string outFile = "/global/u1/j/jrager/LowE/TuneWFCutsDS6_cut2chan.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6Cal/*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s && %s && %s && %s",basicCut,HEDetCut,cutTwoChan,tetmCut);

    TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
    ToE->GetYaxis()->SetTitle("T/E (arb)");
    ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",cut1);
    ToE->SetOption("colz");
    ToE->Write();

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 150, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    skimTree->Project("htrapETailMin","trapETailMin",cut1);
    htrapETailMin->Write();
    cout << "Writing histogram htrapETailMin" <<  endl;
  
    cout << "Writing histogram TuneToE" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void Channel()
{
    string outFile = "/global/u1/j/jrager/LowE/ChanSellDS6Bad.root";
    
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/BadRuns/*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s",basicCut);
    //sprintf(cut2,"%s && %s && %s",basicCut,tetmCut,toeCut);

    TH1D *noCuts = new TH1D("noCuts", "noCuts", 1440, 0, 1440);
    noCuts->GetXaxis()->SetTitle("channel");
    skimTree->Project("noCuts","channel");
    noCuts->Write();
    cout << "Writing histogram noCuts" <<  endl;

    TH1D *dataCleaning = new TH1D("dataCleaning", "dataCleaning", 1440, 0, 1440);
    dataCleaning->GetXaxis()->SetTitle("channel");
    skimTree->Project("dataCleaning","channel",cut1);
    dataCleaning->Write();
    cout << "Writing histogram dataCleaning" <<  endl;

    TH1D *wfCuts = new TH1D("wfCuts", "wfCuts", 1440, 0, 1440);
    wfCuts->GetXaxis()->SetTitle("channel");
    skimTree->Project("wfCuts","channel",cut2);
    wfCuts->Write();
    cout << "Writing histogram wfCuts" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void RunSelection()
{
    string outFile = "/global/u1/j/jrager/LowE/DS6RunSelect_5kThresh_correctedCuts.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    //skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V4Skim3-19-18/*.root");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/DS6BG_Official/*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut0,"%s && %s",HEDetCut,EwindowCut4);
    //sprintf(cut1,"%s && %s && %s",basicCut,HEDetCut,EwindowCut4);
    sprintf(cut2,"%s && %s && %s && %s && %s && %s",basicCut,tetmCut,ToE_EDependent,HEDetCut,HERunCut,EwindowCut4);
    //sprintf(cut3,"%s && %s && %s && %s && %s",basicCut,tetmKrisCut,LEtoe,HEDetCut,EwindowCut4);
    
    //TH2F *EVrun = new TH2F("EVrun","EVrun", 11182, 25704, 36886, 2000, 0, 500);
    //EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
    //EVrun->GetXaxis()->SetTitle("run");
    //skimTree->Project("EVrun","trapENFCal:run",cut0);
    //EVrun->SetOption("colz");
    //EVrun->Write();
    //cout << "Writing histogram EVrun" <<  endl;

    //TH2F *EVrunBasic = new TH2F("EVrunBasic","EVrunBasic", 11182, 25704, 36886, 2000, 0, 500);
    //EVrunBasic->GetYaxis()->SetTitle("trapENFCal (keV)");
    //EVrunBasic->GetXaxis()->SetTitle("run");
    //skimTree->Project("EVrunBasic","trapENFCal:run",cut1);
    //EVrunBasic->SetOption("colz");
    //EVrunBasic->Write();
    //cout << "Writing histogram EVrunBasic" <<  endl;

    TH2F *EVrunAdv = new TH2F("EVrunAdv","EVrunAdv", 11182, 25704, 36886, 2000, 0, 500);
    EVrunAdv->GetYaxis()->SetTitle("trapENFCal (keV)");
    EVrunAdv->GetXaxis()->SetTitle("run");
    skimTree->Project("EVrunAdv","trapENFCal:run",cut2);
    EVrunAdv->SetOption("colz");
    EVrunAdv->Write();
    cout << "Writing histogram EVrunAdv" <<  endl;

    //TH2F *EVrunOld = new TH2F("EVrunOld","EVrunOld", 11182, 25704, 36886, 2000, 0, 500);
    //EVrunOld->GetYaxis()->SetTitle("trapENFCal (keV)");
    //EVrunOld->GetXaxis()->SetTitle("run");
    //skimTree->Project("EVrunOld","trapENFCal:run",cut3);
    //EVrunOld->SetOption("colz");
    //EVrunOld->Write();
    //cout << "Writing histogram EVrunOld" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void EvsRunBad()
{
  string outFile = "/global/u1/j/jrager/LowE/EvsRunDS6Bad.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/BadRuns/*.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut1,"%s",basicCut);
  //sprintf(cut2,"%s && %s && %s",basicCut,tetmCut,toeCut);

  TH2F *EVrun = new TH2F("EVrun","EVrun", 3420, 25704, 29124, 2000, 0, 500);
  EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrun->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrun","trapENFCal:run");
  EVrun->SetOption("colz");
  EVrun->Write();
  cout << "Writing histogram EVrun" <<  endl;

  TH2F *EVrunBasic = new TH2F("EVrunBasic","EVrunBasic", 3420, 25704, 29124, 2000, 0, 500);
  EVrunBasic->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunBasic->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunBasic","trapENFCal:run",cut1);
  EVrunBasic->SetOption("colz");
  EVrunBasic->Write();
  cout << "Writing histogram EVrunBasic" <<  endl;

  TH2F *EVrunAdv = new TH2F("EVrunAdv","EVrunAdv", 3420, 25704, 29124, 2000, 0, 500);
  EVrunAdv->GetYaxis()->SetTitle("trapENFCal (keV)");
  EVrunAdv->GetXaxis()->SetTitle("run");
  skimTree->Project("EVrunAdv","trapENFCal:run",cut2);
  EVrunAdv->SetOption("colz");
  EVrunAdv->Write();
  cout << "Writing histogram EVrunAdv" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void TETMCutStudy2D()
{
    string outFile = "/global/u1/j/jrager/LowE/TETMstudyCalDS6.root";
  
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/skimDS6_37_low.root");
    cout << "Adding data files" <<  endl;

    TH2F *twoD = new TH2F("twoD", "twoD", 120, 0, 30, 160, -30, 10);
    twoD->GetYaxis()->SetTitle("trapETailMin");
    twoD->GetXaxis()->SetTitle("trapENFCal (keV)");
    sprintf(cut1,"%s",basicCut);
    skimTree->Project("twoD","trapETailMin:trapENFCal",cut1);
    twoD->SetOption("colz");
    twoD->Write();
    cout << "Writing histogram twoD" <<  endl;
    
    TProfile *tprof = new TProfile("tprof", "tprof", 180, 5, 50, -20, 5);
    tprof->GetYaxis()->SetTitle("trapETailMin");
    tprof->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("tprof","trapETailMin:trapENFCal",cut1);
    tprof->Write();
    cout << "Writing histogram tprof" <<  endl;
    
    TH2F *EVrun = new TH2F("EVrun","EVrun", 27, 28582, 28608, 120, 0, 30);
    EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
    EVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("EVrun","trapENFCal:run",cut1);
    EVrun->SetOption("colz");
    EVrun->Write();
    cout << "Writing histogram EVrun" <<  endl;
    
    TH2F *trapVrun = new TH2F("trapVrun","trapVrun", 27, 28582, 28608, 160, -30, 10);
    trapVrun->GetYaxis()->SetTitle("trapETailMin");
    trapVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("trapVrun","trapETailMin:run",cut1);
    trapVrun->SetOption("colz");
    trapVrun->Write();
    cout << "Writing histogram trapVrun" <<  endl;
	      
    cout << "done" <<  endl;
    
    f->Close();
}

void ToverEGood()
{
    string outFile = "/global/u1/j/jrager/LowE/ToEDS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V1Skim*.root");
    //skimTree->Add("/global/u1/j/jrager/low_energy_skim/output/skimDS6_1_low.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut3,"%s && %s && %s",basicCut,tetmCut,HEDetCut);
    //sprintf(cut2,"%s && %s",basicCut,HEDetCut);
    //sprintf(cut1,"%s",HEDetCut);

    TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
    ToE->GetYaxis()->SetTitle("T/E (arb)");
    ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal",cut1);
    ToE->SetOption("colz");
    ToE->Write();

    TH2F *ToEBasic = new TH2F("ToEBasic", "ToEBasic", 1000, 0, 100, 400, 0, 10);
    ToEBasic->GetYaxis()->SetTitle("T/E (arb)");
    ToEBasic->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("ToEBasic","kvorrT/trapENFCal:trapENFCal",cut2);
    ToEBasic->SetOption("colz");
    ToEBasic->Write();
    //TLine *line95 = new TLine(0, 2, 100, 2);
    //line95->SetLineColor(kRed);
    //line95->Draw();
    //TLine *line96 = new TLine(0, 1, 100, 1);
    //line96->SetLineColor(kRed);
    //line96->Draw();
    cout << "Writing histogram ToEBasic" <<  endl;

    TH2F *ToEAdv = new TH2F("ToEAdv", "ToEAdv", 1000, 0, 100, 400, 0, 10);
    ToEAdv->GetYaxis()->SetTitle("T/E (arb)");
    ToEAdv->GetXaxis()->SetTitle("trapENFCal (keV)");
    skimTree->Project("ToEAdv","kvorrT/trapENFCal:trapENFCal",cut3);
    ToEAdv->SetOption("colz");
    ToEAdv->Write();
    //TLine *line87 = new TLine(0, 2, 100, 2);
    //line87->SetLineColor(kRed);
    //line87->Draw();
    //TLine *line88 = new TLine(0, 1, 100, 1);
    //line88->SetLineColor(kRed);
    //line88->Draw();
    cout << "Writing histogram ToEAdv" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void ToverEBad()
{
  string outFile = "/global/u1/j/jrager/LowE/ToEDS6Bad.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/BadRuns/*.root");
  //skimTree->Add("/global/u1/j/jrager/low_energy_skim/output/skimDS6_1_low.root");
  cout << "Adding data files" <<  endl;

  //sprintf(cut2,"%s && %s",basicCut,tetmCut);
  //sprintf(cut1,"%s",basicCut);

  TH2F *ToE = new TH2F("ToE", "ToE", 1000, 0, 100, 400, 0, 10);
  ToE->GetYaxis()->SetTitle("T/E (arb)");
  ToE->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToE","kvorrT/trapENFCal:trapENFCal");
  ToE->SetOption("colz");
  ToE->Write();

  TH2F *ToEBasic = new TH2F("ToEBasic", "ToEBasic", 1000, 0, 100, 400, 0, 10);
  ToEBasic->GetYaxis()->SetTitle("T/E (arb)");
  ToEBasic->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToEBasic","kvorrT/trapENFCal:trapENFCal",cut1);
  ToEBasic->SetOption("colz");
  ToEBasic->Write();
  TLine *line95 = new TLine(0, 2, 100, 2);
  line95->SetLineColor(kRed);
  line95->Draw();
  TLine *line96 = new TLine(0, 1, 100, 1);
  line96->SetLineColor(kRed);
  line96->Draw();
  cout << "Writing histogram ToEBasic" <<  endl;

  TH2F *ToEAdv = new TH2F("ToEAdv", "ToEAdv", 1000, 0, 100, 400, 0, 10);
  ToEAdv->GetYaxis()->SetTitle("T/E (arb)");
  ToEAdv->GetXaxis()->SetTitle("trapENFCal (keV)");
  skimTree->Project("ToEAdv","kvorrT/trapENFCal:trapENFCal",cut2);
  ToEAdv->SetOption("colz");
  ToEAdv->Write();
  TLine *line97 = new TLine(0, 2, 100, 2);
  line97->SetLineColor(kRed);
  line97->Draw();
  TLine *line98 = new TLine(0, 1, 100, 1);
  line98->SetLineColor(kRed);
  line98->Draw();
  cout << "Writing histogram ToEAdv" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

void EnrichedSpectrumGood()
{
    string outFile = "/global/u1/j/jrager/LowE/EnrDS6Physics.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V1Skim/*.root");
    //skimTree->Add("/global/projecta/projectdirs/majorana/users/bxyzhu/lat/latSkimDS4*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s && %s", enrCut, HEDetCut);
    //sprintf(cut2,"%s && %s && %s", basicCut, enrCut, HEDetCut);
    //sprintf(cut3,"%s && %s && %s && %s && %s", basicCut, enrCut, tetmCut, toeCut, HEDetCut);
    //sprintf(cut4,"%s && %s && %s && %s && %s", basicCut, enrCut, tetmOldCut, toeOldCut, HEDetCut);

    TH1D *NoCut = new TH1D("NoCut", "NoCut", 12000, 0, 3000);
    NoCut->GetXaxis()->SetTitle("trapENFCal (keV)");
    NoCut->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("NoCut", "trapENFCal", cut1);
    Double_t DS6exposureEnr = 4/610.98;
    NoCut->Scale(DS6exposureEnr);
    NoCut->Write();
    cout << "Writing histogram BasicCut" <<  endl;

    TH1D *BasicCut = new TH1D("BasicCut", "BasicCut", 12000, 0, 3000);
    BasicCut->GetXaxis()->SetTitle("trapENFCal (keV)");
    BasicCut->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("BasicCut", "trapENFCal", cut2);
    //Double_t DS1exposureEnr = 4/656.90;
    //Double_t DS0exposureEnr = 4/473.55;
    //Double_t DS5exposureEnr = 4/1028.6;
    //Double_t DS2exposureEnr = 4/108.92;
    //Double_t DS3exposureEnr = 4/336.14;
    //Double_t DS4exposureEnr = 4/99.749;
    BasicCut->Scale(DS6exposureEnr);
    BasicCut->Write();
    cout << "Writing histogram BasicCut" <<  endl;

    TH1D *WFCut = new TH1D("WFCut", "WFCut", 12000, 0, 3000);
    WFCut->GetXaxis()->SetTitle("trapENFCal (keV)");
    WFCut->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("WFCut", "trapENFCal", cut3);
    WFCut->Scale(DS6exposureEnr);
    WFCut->Write();
    cout << "Writing histogram WFCut" <<  endl;

    TH1D *OldWFCut = new TH1D("OldWFCut", "OldWFCut", 12000, 0, 3000);
    OldWFCut->GetXaxis()->SetTitle("trapENFCal (keV)");
    OldWFCut->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("OldWFCut", "trapENFCal", cut4);
    OldWFCut->Scale(DS6exposureEnr);
    OldWFCut->Write();
    cout << "Writing histogram OldWFCut" <<  endl;
    
    cout << "done" <<  endl;

    f->Close();
}

void EnrichedSpectrumBad()
{
    string outFile = "/global/u1/j/jrager/LowE/EnrDS6Bad.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/BadRuns/*.root");

    cout << "Adding data files" <<  endl;

    TH1D *NoCut = new TH1D("NoCut", "NoCut", 12000, 0, 3000);
    NoCut->GetXaxis()->SetTitle("trapENFCal (keV)");
    NoCut->GetYaxis()->SetTitle("cts/kg/day/keV");
    sprintf(cut2,"%s", enrCut);
    skimTree->Project("NoCut", "trapENFCal", cut2);
    //Double_t DS6exposureEnr = 4/3.625;
    //NoCut->Scale(DS6exposureEnr);
    NoCut->Write();

    TH1D *BasicCut = new TH1D("BasicCut", "BasicCut", 12000, 0, 3000);
    BasicCut->GetXaxis()->SetTitle("trapENFCal (keV)");
    BasicCut->GetYaxis()->SetTitle("cts/kg/day/keV");
    sprintf(cut1,"%s && %s", basicCut, enrCut);
    skimTree->Project("BasicCut", "trapENFCal", cut1);
    //Double_t DS6exposureEnr = 4/3.625;
    //BasicCut->Scale(DS6exposureEnr);
    BasicCut->Write();

    TH1D *WFCut = new TH1D("WFCut", "WFCut", 12000, 0, 3000);
    WFCut->GetXaxis()->SetTitle("trapENFCal (keV)");
    WFCut->GetYaxis()->SetTitle("cts/kg/day/keV");
    //sprintf(cut2,"%s && %s && %s && %s", basicCut, enrCut, tetmCut, toeCut);
    skimTree->Project("WFCut", "trapENFCal", cut2);
    //Double_t DS6exposureEnr = 4/3.625;
    //WFCut->Scale(DS6exposureEnr);
    WFCut->Write();

    cout << "Writing histogram EnrSpect" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void NaturalSpectrum()
{
    string outFile = "/global/u1/j/jrager/LowE/NaturalDS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/V1Skim/*.root");
    cout << "Adding data files" <<  endl;

    //sprintf(cut1,"%s && %s", basicCut, natCut);

    TH1D *NatSpect = new TH1D("NatSpect", "NatSpect", 12000, 0, 3000);
    NatSpect->GetXaxis()->SetTitle("trapENFCal (keV)");
    NatSpect->GetYaxis()->SetTitle("cts/kg/day/keV");
    skimTree->Project("NatSpect", "trapENFCal", cut1);
    //Double_t DS6exposureNat = 1/217.12;
    //Double_t natBinning = 4;
    //Double_t natScaling = DS6exposureNat*natBinning;
    //NatSpect->Scale(natScaling);
    NatSpect->Write();
    cout << "Writing histogram NatSpect" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}


void TETMCutStudy1D()
{
    string outFile = "/global/u1/j/jrager/LowE/TETMcutRecCalDS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/skimDS6_37_low.root");
    cout << "Adding data files" <<  endl;

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 130, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    sprintf(cut1,"%s",basicCut);
    skimTree->Project("htrapETailMin","trapETailMin",cut1);
    htrapETailMin->Write();
    TLine *line95 = new TLine(-0.301396, 0, -0.301396, 5000000);
    line95->SetLineColor(kRed);
    line95->Draw();
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
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5*.root");

    TH1F *det = new TH1F("det", "det", 800, 550, 1350);
    det->GetXaxis()->SetTitle("detector channel");
    sprintf(cut1,"%s",basicCut);
    skimTree->Project("det","channel",cut1);
    det->Write();
    cout << "Writing histogram det" <<  endl;

    TH1F *hrun = new TH1F("hrun", "hrun", 7049, 18623, 25672);
    hrun->GetXaxis()->SetTitle("run");
    skimTree->Project("hrun","run",cut1);
    hrun->Write();
    cout << "Writing histogram hrun" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void AddDS0()
{
  string outFile = "/global/u1/j/jrager/LowE/1DTETM_Superimposed.root";
    
  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;
    
  //TCanvas c1 = new TCanvas("c1");
    
  TChain *skimTree = new TChain("skimTree");
    
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS0*.root");
  cout << "Adding data files" <<  endl;
  TH1F *htrapETailMin0 = new TH1F("htrapETailMin0","htrapETailMin0", 130, -5, 10);
  htrapETailMin0->GetXaxis()->SetTitle("trapETailMin");
  sprintf(cut1,"%s",basicCut);
  skimTree->Project("htrapETailMin0","trapETailMin",cut1);
  htrapETailMin0->Write();
  cout << "Writing histogram htrapETailMin0" <<  endl;
  cout << "done" <<  endl;
  f->Close();
}

void AddDS1()
{
  string outFile = "/global/u1/j/jrager/LowE/1DTETM_Superimposed.root";
  TFile *f = new TFile(outFile.c_str(),"update");
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS1*.root");
  TH1F *htrapETailMin1 = new TH1F("htrapETailMin1","htrapETailMin1", 130, -5, 10);
  htrapETailMin1->GetXaxis()->SetTitle("trapETailMin");
  sprintf(cut1,"%s",basicCut);
  skimTree->Project("htrapETailMin1","trapETailMin",cut1);
  htrapETailMin1->Write();
  cout << "Writing histogram htrapETailMin1" <<  endl;
  cout << "done" <<  endl;
  f->Close();
}

void AddDS2()
{
  string outFile = "/global/u1/j/jrager/LowE/1DTETM_Superimposed.root";
  TFile *f = new TFile(outFile.c_str(),"update");
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS2*.root");
  TH1F *htrapETailMin2 = new TH1F("htrapETailMin2","htrapETailMin2", 130, -5, 10);
  htrapETailMin2->GetXaxis()->SetTitle("trapETailMin");
  sprintf(cut1,"%s",basicCut);
  skimTree->Project("htrapETailMin2","trapETailMin",cut1);
  htrapETailMin2->Write();
  cout << "Writing histogram htrapETailMin2" <<  endl;
  cout << "done" <<  endl;
  f->Close();
}

void AddDS3()
{
  string outFile = "/global/u1/j/jrager/LowE/1DTETM_Superimposed.root";
  TFile *f = new TFile(outFile.c_str(),"update");
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS3*.root");
  TH1F *htrapETailMin3 = new TH1F("htrapETailMin3","htrapETailMin3", 130, -5, 10);
  htrapETailMin3->GetXaxis()->SetTitle("trapETailMin");
  sprintf(cut1,"%s",basicCut);
  skimTree->Project("htrapETailMin3","trapETailMin",cut1);
  htrapETailMin3->Write();
  cout << "Writing histogram htrapETailMin3" <<  endl;
  cout << "done" <<  endl;
  f->Close();
}

void AddDS4()
{
  string outFile = "/global/u1/j/jrager/LowE/1DTETM_Superimposed.root";
  TFile *f = new TFile(outFile.c_str(),"update");
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS4*.root");
  TH1F *htrapETailMin4 = new TH1F("htrapETailMin4","htrapETailMin4", 130, -5, 10);
  htrapETailMin4->GetXaxis()->SetTitle("trapETailMin");
  sprintf(cut1,"%s",basicCut);
  skimTree->Project("htrapETailMin4","trapETailMin",cut1);
  htrapETailMin4->Write();
  cout << "Writing histogram htrapETailMin4" <<  endl;
  cout << "done" <<  endl;
  f->Close();
}

void AddDS5()
{
  string outFile = "/global/u1/j/jrager/LowE/1DTETM_Superimposed.root";
  TFile *f = new TFile(outFile.c_str(),"update");
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5*.root");
  TH1F *htrapETailMin5 = new TH1F("htrapETailMin5","htrapETailMin5", 130, -5, 10);
  htrapETailMin5->GetXaxis()->SetTitle("trapETailMin");
  sprintf(cut1,"%s",basicCut);
  skimTree->Project("htrapETailMin5","trapETailMin",cut1);
  htrapETailMin5->Write();
  cout << "Writing histogram htrapETailMin5" <<  endl;
  cout << "done" <<  endl;
  f->Close();
}

void AddDS6()
{
  string outFile = "/global/u1/j/jrager/LowE/1DTETM_Superimposed.root";
  TFile *f = new TFile(outFile.c_str(),"update");
  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/skimDS6*.root");
  TH1F *htrapETailMin6 = new TH1F("htrapETailMin6","htrapETailMin6", 130, -5, 10);
  htrapETailMin6->GetXaxis()->SetTitle("trapETailMin");
  sprintf(cut1,"%s",basicCut);
  skimTree->Project("htrapETailMin6","trapETailMin",cut1);
  htrapETailMin6->Write();
  cout << "Writing histogram htrapETailMin6" <<  endl;
  cout << "done" <<  endl;
  f->Close();
}

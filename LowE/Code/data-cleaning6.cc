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

void Band();
void TuneWFCuts();
void TETMCutStudy2D();
void TETMCutStudy1D();
void RunsAndDets();
int main()
{

  //Band();
  TuneWFCuts();                  //  For tuning waveform (ToE & trapETailMin) cuts.
  //TETMCutStudy2D();          // 1. Makes 2D plots for TETM cut study and saves to output file.
  //TETMCutStudy1D();          // 2. Makes 1D plots for TETM cut study and saves to output file.
  //RunsAndDets();             // 3. 1D Hists of run and detector (channel) to help me pick out noisy runs/detectors.

}
char theCut[1000];
char cut1[1000];
char cut2[1000];
char cut3[1000];
char basicCut[1000] = "gain==0 && mH==1 && isGood && !muVeto && P!=0 && D!=0";
char toeBand[1000] = "kvorrT/trapENFCal>0.9 && kvorrT/trapENFCal<1.1";
char toeSig[1000] = "kvorrT/trapENFCal>1.15 && kvorrT/trapENFCal<1.55";
char toeNoise[1000] = "kvorrT/trapENFCal<0.9";
char enrCut[1000] = "isEnr";
char wfdcCut[1000] = "!wfDCBits";
char advCut[1000] = "avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2";
char noisyRunsCut[1000] = "run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run<20966) && !(run>21133 && run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952";
char noisyDetCut[1000] = "channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";
char finalCut[1000] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0 && !wfDCBits && avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2 && run!=20643 && run!=20639 && run!=20635 && !(run>20611 && run<20627) && !(run>20876 && run<20878) && run!=20910 && !(run>20955 && run<20957) && !(run>20964 && run< \
20966) && !(run>21133 &C& run<21136) && !(run>21157 && run<21165) && !(run>21778 && run<21781) && !(run>21768 && run<21776) && !(run>20955 && run<20957) && run!=22954 && run!=22952 && channel!=614 && channel!=678 && channel!=692 && channel!=1172 && channel!=1232 && channel!=1303 && channel!=1332";

void Band()
{
    string outFile = "/global/u1/j/jrager/LowE/BandDS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/*.root");

    cout << "Adding data files" <<  endl;

    sprintf(cut1,"%s && %s && %s", basicCut, enrCut, toeBand);
    sprintf(cut2,"%s && %s && %s", basicCut, enrCut, toeSig);
    sprintf(cut3,"%s && %s && %s", basicCut, enrCut, toeNoise);

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

void TuneWFCuts()
{
    string outFile = "/global/u1/j/jrager/LowE/TuneWFCutsDS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/projecta/projectdirs/majorana/users/jrager/Skim/228Th/*.root");
    cout << "Adding data files" <<  endl;

    sprintf(theCut,"%s",basicCut);

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

    string outFile = "/global/u1/j/jrager/LowE/TETMstudyImprovedDS6.root";
  
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/u1/j/jrager/low_energy_skim/output/skimDS6*.root");
    cout << "Adding data files" <<  endl;

    TH2F *twoD = new TH2F("twoD", "twoD", 120, 0, 30, 160, -30, 10);
    twoD->GetYaxis()->SetTitle("trapETailMin");
    twoD->GetXaxis()->SetTitle("trapENFCal (keV)");
    sprintf(theCut,"%s && %s", basicCut, wfdcCut);
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
    
    TH2F *EVrun = new TH2F("EVrun","EVrun", 1520, 25676, 27196, 120, 0, 30);
    EVrun->GetYaxis()->SetTitle("trapENFCal (keV)");
    EVrun->GetXaxis()->SetTitle("run");
    skimTree->Project("EVrun","trapENFCal:run",theCut);
    EVrun->SetOption("colz");
    EVrun->Write();
    cout << "Writing histogram EVrun" <<  endl;
    
    TH2F *trapVrun = new TH2F("trapVrun","trapVrun", 1520, 25676, 27196, 160, -30, 10);
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
    string outFile = "/global/u1/j/jrager/LowE/TETMcutRecImprovedDS6.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/u1/j/jrager/low_energy_skim/output/skimDS6*.root");
    cout << "Adding data files" <<  endl;

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 130, -5, 10);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    sprintf(theCut,"%s && %s", basicCut, wfdcCut);
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
  string outFile = "/global/u1/j/jrager/LowE/TETMrunsAndDetsImprovedDS6.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/u1/j/jrager/low_energy_skim/output/skimDS6*.root");

  TH1F *det = new TH1F("det", "det", 800, 550, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  sprintf(theCut,"%s && %s", basicCut, wfdcCut);
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH1F *hrun = new TH1F("hrun", "hrun", 1520, 25676, 27196);
  hrun->GetXaxis()->SetTitle("run");
  sprintf(theCut,"%s && %s", basicCut, wfdcCut);
  hrun->Write();
  cout << "Writing histogram hrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

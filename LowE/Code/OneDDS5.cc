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

void TETMCutStudy2D();
void TETMCutStudy1D();
void RunsAndDets();
int main()
{

  //TETMCutStudy2D();          // 1. Makes 2D plots for TETM cut study and saves to output file.
  TETMCutStudy1D();          // 2. Makes 1D plots for TETM cut study and saves to output file.
  //RunsAndDets();             // 3. 1D Hists of run and detector (channel) to help me pick out noisy runs/detectors.

}

char theCut[1000];
char basicCut[1000] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0";
char wfdcCut[1000] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0 && !wfDCBits";
char uberCut[1000] = "gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0 && !wfDCBits && avse>-1 && dcr90<0 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2";

void TETMCutStudy2D()
{

    string outFile = "/global/u1/j/jrager/LowE/TETMstudyDS5.root";
  
    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5*.root");
    cout << "Adding data files" <<  endl;

    TH2F *twoD = new TH2F("twoD", "twoD", 120, 0, 30, 160, -30, 10);
    twoD->GetYaxis()->SetTitle("trapETailMin");
    twoD->GetXaxis()->SetTitle("trapENFCal (keV)");
    sprintf(theCut,"%s",uberCut);
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
    string outFile = "/global/u1/j/jrager/LowE/TETMcutRecDS5.root";

    TFile *f = new TFile(outFile.c_str(),"RECREATE");
    cout << "Creating outpout file" <<  endl;

    TChain *skimTree = new TChain("skimTree");
    skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5*.root");
    cout << "Adding data files" <<  endl;

    TH1F *htrapETailMin = new TH1F("htrapETailMin","htrapETailMin", 122, -5, 7);
    htrapETailMin->GetXaxis()->SetTitle("trapETailMin");
    sprintf(theCut,"%s",uberCut);
    skimTree->Project("htrapETailMin","trapETailMin",theCut);
    htrapETailMin->Write();
    TLine *line95 = new TLine();
    line95->SetLineColor(kRed);
    line95->PaintLine(5.469, 0, 5.469, 5000000);
    cout << "Writing histogram htrapETailMin" <<  endl;

    cout << "done" <<  endl;

    f->Close();
}

void RunsAndDets()
{
  string outFile = "/global/u1/j/jrager/LowE/TETMruns&detsDS5.root";

  TFile *f = new TFile(outFile.c_str(),"RECREATE");
  cout << "Creating outpout file" <<  endl;

  TChain *skimTree = new TChain("skimTree");
  skimTree->Add("/global/homes/w/wisecg/project/skim/skimDS5*.root");

  TH1F *det = new TH1F("det", "det", 800, 500, 1350);
  det->GetXaxis()->SetTitle("detector channel");
  sprintf(theCut,"%s",uberCut);
  skimTree->Project("det","channel",theCut);
  det->Write();
  cout << "Writing histogram det" <<  endl;

  TH1F *hrun = new TH1F("hrun", "hrun", 7049, 18623, 25672);
  hrun->GetXaxis()->SetTitle("run");
  sprintf(theCut,"%s",uberCut);
  skimTree->Project("hrun","run",theCut);
  hrun->Write();
  cout << "Writing histogram hrun" <<  endl;

  cout << "done" <<  endl;

  f->Close();
}

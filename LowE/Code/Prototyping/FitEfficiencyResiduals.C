// Macro to fit my efficiency to an error function or something
// Created by Jamin Rager
// 03/19/19

#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TVirtualFitter.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "TFile.h"
#include "TROOT.h"
#include "TF1.h"
#include "TStyle.h"
#include "TEntryList.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLine.h"
#include <numeric>


{    
    TFile *f1 = new TFile("~/LowE/Data/CombinedEfficiencies/NormalizedEfficiencyDS1_6.root");
    TGraphAsymmErrors *geff = (TGraphAsymmErrors*)f1->Get("Graph");
    
    //TFile *f1 = new TFile("~/LowE/Data/CombinedEfficiencies/ClopperPearsonDS1_6Combined.root");
    //TGraphAsymmErrors *geff = (TGraphAsymmErrors*)f1->Get("Graph");

    //string outFile = "/global/homes/j/jrager/LowE/Data/CombinedEfficiencies/NormEffFunc.root";
    //TFile *f0 = new TFile(outFile.c_str(),"recreate");
    //cout << "Creating outpout file" <<  endl;
    //f0->cd();

    //Create the fitting function
    TF1 *effFit = new TF1(" effFit", "[0]*TMath::Erf((x-[1])/[2])", 0, 100);
    effFit->SetLineWidth(2);
    effFit->SetParameter(0, 0.9);
    effFit->SetParameter(1, -15);
    effFit->SetParameter(2, 20);
    //effFit->SetParameter(0, 3900);
    //effFit->SetParameter(1, -5);
    //effFit->SetParameter(2, 7);
    effFit->SetLineColor(2);
    effFit->SetLineWidth(1);
    geff->Fit(effFit);
    Double_t chi2 = effFit->GetChisquare();
    Double_t redChi2 = chi2/17;
    f1->Close();

    TFile f("NormEffFunc.root","recreate");
    cout << effFit->GetParameter(0) << endl;
    cout << effFit->GetParameter(1) << endl;
    cout << effFit->GetParameter(2) << endl;
    cout << "reduced chi2 " << redChi2 << endl;
    //geff->Draw("AP");
    //geff->Write();
    //effFit->Draw("same");
    //effFit->Write();
    //double feff = 0;
    //double eff = 0;
    //feff = effFit->Eval(10);
    //eff = geff->Eval(10);
    //std::cout << "feff @ 10 " << feff << " eff @ 10 " << eff << std::endl;
     
    double eff[20] = {};
    double errhi[20] = {};
    double errlo[20] = {};
    double feff[20] = {};
    double resid[20] = {};
    double square[20] = {};
    double Chi2Man = 0;
    double RedChi2Man = 0;
    double x[20] = {};
    double xerr[20] = {};
    cout << "Beginning loop" << endl;
    for(int i = 0; i < 20; i++)
    {
      eff[i] = geff->Eval(i*5);
      errhi[i] = geff->GetErrorYhigh(i);
      errlo[i] = geff->GetErrorYlow(i);
      feff[i] = effFit->Eval(i*5);
      resid[i] = eff[i] - feff[i];
      square[i] = (resid[i]*resid[i])/(errlo[i]*errlo[i]);
      Chi2Man = Chi2Man + square[i];
      x[i] = i*5;
      xerr[i] = 0;
    }

    RedChi2Man = Chi2Man/17;
    cout << "manual chi2 " << RedChi2Man << endl;

    TGraphAsymmErrors *residuals = new TGraphAsymmErrors(20, x, resid, xerr, xerr, errlo, errhi);
    TCanvas *c1 = new TCanvas("c1","c1",600,800);
    //TCanvas *c1 = new TCanvas("c1","c1");
    TPad* p1 = new TPad("p1", "p1", 0.0, .35, 1.0, 1.0);
    TPad* p2 = new TPad("p2", "p2", 0.0, 0.0, 1.0, 0.35);
    p1->Draw();
    p2->Draw();
    //c1->Divide(1,2);
    //c1->cd(1);
    p1->cd();
    geff->SetMarkerStyle(21);
    geff->SetMarkerColor(2);
    geff->SetMarkerSize(0.5);
    geff->GetXaxis()->SetTitle("Energy (keV)");
    geff->GetXaxis()->SetTitleSize(25);
    geff->GetYaxis()->SetTitle("Efficiency");
    geff->GetYaxis()->SetTitleSize(25);
    geff->Draw("AP");
    effFit->Draw("same");
    TPaveText *pt = new TPaveText(60,0.75,80,0.8);
    pt->AddText("#chi^{2}/NDF = 1.43");
    pt->SetFillColor(0);
    pt->SetBorderSize(0);
    pt->SetTextSize(20);
    pt->Draw();
    //c1->cd(2);
    p2->cd();
    residuals->SetMarkerStyle(21);
    residuals->SetMarkerColor(2);
    residuals->SetMarkerSize(0.5);
    residuals->GetXaxis()->SetTitle("Energy (keV)");
    residuals->GetXaxis()->SetTitleSize(25);
    residuals->GetYaxis()->SetTitle("Residuals (keV)");
    residuals->GetYaxis()->SetTitleSize(25);
    //gstyle->SetTitleXOffset(2.0);
    residuals->Draw("AP");
    TLine *line1 = new TLine(0, 0, 100, 0);
    line1->SetLineColor(1);
    line1->SetLineWidth(2);
    line1->SetLineStyle(7);
    line1->Draw();
}

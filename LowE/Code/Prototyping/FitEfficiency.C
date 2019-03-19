// Macro to fit my efficiency to an error function or something
// Created by Jamin Rager
// 03/19/19

#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TVirtualFitter.h"

{
    
    TFile *f1 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperPearsonDS1_6Combined.root");
    TGraphAsymmErrors *geff = (TGraphAsymmErrors*)f1->Get("Graph");
    
    //Create the fitting function
    TF1 * feff = new TF1(" feff", "[0]*TMath::Erf((x-[1])/[2])", 0, 100);
    feff->SetLineWidth(2);
    feff->SetParameter(0, 3000);
    feff->SetParameter(1, 0);
    feff->SetParameter(2, 1);
    feff->SetLineColor(2);
    feff->SetLineWidth(1);
    geff->Fit(feff);
    cout << fres->GetParameter(0) << endl;
    cout << fres->GetParameter(1) << endl;
    cout << fres->GetParameter(2) << endl;
    geff->Draw("AP");
    feff->Draw("same")

}

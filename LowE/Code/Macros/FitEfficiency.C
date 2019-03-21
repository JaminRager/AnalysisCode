// Macro to fit my efficiency to an error function or something
// Created by Jamin Rager
// 03/19/19

#include "TMath.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TVirtualFitter.h"

{
    
    TFile *f1 = new TFile("~/LowE/Data/CombinedEfficiencies/NormalizedEfficiencyDS1_6.root");
    TGraphAsymmErrors *geff = (TGraphAsymmErrors*)f1->Get("Graph");
    
    //string outFile = "~/LowE/Code/Prototyping/CombinedEfficiency.root";
    //TFile *f0 = new TFile(outFile.c_str(),"recreate");
    //cout << "Creating outpout file" <<  endl;
    //f0->cd();

    //Create the fitting function
    TF1 *effFit = new TF1(" effFit", "[0]*TMath::Erf((x-[1])/[2])", 0, 100);
    effFit->SetLineWidth(2);
    effFit->SetParameter(0, 0.85);
    effFit->SetParameter(1, -15);
    effFit->SetParameter(2, 20);
    effFit->SetLineColor(2);
    effFit->SetLineWidth(1);
    geff->Fit(effFit);

    f1->Close();

    TFile f("NormEffFunc.root","recreate");
    cout << effFit->GetParameter(0) << endl;
    cout << effFit->GetParameter(1) << endl;
    cout << effFit->GetParameter(2) << endl;
    //geff->Draw("AP");
    //geff->Write();
    //effFit->Draw("same");
    effFit->Write();
     
    //TGraphErrors *grint = new TGraphErrors(20);
    //grint->SetTitle("Fitted line with .95 conf. band");
    //for (int i=0; i<20; i++){
      //grint->SetPoint(i, geff->GetX()[i], 0);
    //}
    //Compute the confidence intervals at the x points of the created graph
    //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint);
    //grint->Draw("same");

}

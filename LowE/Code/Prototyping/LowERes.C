#include "TGraphErrors.h"
#include "TGraph2DErrors.h"
#include "TCanvas.h"
#include "TF2.h"
#include "TH1.h"
#include "TVirtualFitter.h"
#include "TRandom.h"

void LowERes()
{
    //Create data arrays
    double E[4] = {6.4898, 10.368, 46.487, 238.6};
    double x[4] = {6, 10, 46};
    double errE[4] = {0.0, 0.0, 0.0, 0.0};
    double sigma[4] = {0.15832, 0.16585, 0.19361, 0.346};
    double errSigHi[4] = {0.0117, 0.015, 0.0314, 0.05};
    double errSigLo[4] = {0.0105, 0.0139, 0.0275, 0.05};
    
    //Make and fill TGraphAsymmErrors
    TGraphAsymmErrors *gres = new TGraphAsymmErrors(4, E, sigma, errE, errE, errSigLo, errSigHi);
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    gres->SetMarkerStyle(21);
    gres->SetMarkerColor(kRed);
    gres->SetTitle("Peak Widths");
    //gres->Draw("AP");
    
    //Create the fitting function
    TF1 * fres = new TF1(" fres", "sqrt([0]+[1]*x+[2]*x*x)", 5, 100);
    fres->SetLineWidth(2);
    fres->SetParameter(0, 0.3);
    fres->SetParameter(1, 5e-3);
    fres->SetParameter(2, 5e-6);
    fres->SetLineColor(2);
    fres->SetLineWidth(1);
    gres->Fit(fres, "Q");
    cout << fres->GetParameter(0) << endl;
    cout << fres->GetParameter(1) << endl;
    cout << fres->GetParameter(2) << endl;
    gres->Draw("AP");

    //Create a TGraphErrors to hold the confidence intervals
    TGraphErrors *grint = new TGraphErrors(4);
    grint->SetTitle("Fitted line with .95 conf. band");
    for (int i=0; i<3; i++){
      grint->SetPoint(i, gres->GetX()[i], 0);
    }
    //Compute the confidence intervals at the x points of the created graph
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(grint);
    grint->Draw("same");
    //gres->Draw("psame");


}

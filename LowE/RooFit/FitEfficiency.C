#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooExponential.h"
#include "RooEffProd.h"
#include "RooFormulaVar.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
using namespace RooFit ;

void FitEfficiency()
{
  gSystem->Load("libRooFit");
  //using namespace RooFit;
    
  // Bind one-dimensional TMath::Erf function as RooAbsReal function
  //RooRealVar x("x","x",0,3) ;
  //RooAbsReal* erf = bindFunction("erf",TMath::Erf,x+1) ;
  
  // Declare observables
  RooRealVar t("t","t",-5,30) ;
  // Use error function to simulate turn-on slope
  //RooFormulaVar eff("eff","0.5*(TMath::Erf((t-1)/0.5)+1)",t) ;
  RooFormulaVar eff("eff","0.5*(TMath::Erf((t-15)/8)+1)",t) ;

  //TF1 *f1 = new TF1("f1","[0]*TMath::Erf((x-[1])/[2])",-0.00005,0.00005);    
  // Print erf definition
  eff.Print() ;
    
  // Plot erf on frame
  RooPlot* frame1 = t.frame() ;
  eff.plotOn(frame1) ;
  frame1->Draw() ;

}

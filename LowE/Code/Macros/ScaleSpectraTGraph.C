//  ScaleSpectra.c
//
//  Convolves the combined efficiency with the combined spectrum for Enr detectors in DS1
//  Outputs spectrum as TGraphAssymErrors
//
//  Created by Jamin on 12/3/18.
//

#include <math.h>

void ScaleSpectraTGraph()
{
    // Input files
    TFile *f1 = new TFile("/global/homes/j/jrager/LowE/Data/AnalSpect/AnalysisSpectrumDS1_6.root");
    TH1F *spect= (TH1F*)f1->Get("spect");
    TFile *f2 = new TFile("/global/homes/j/jrager/LowE/Data/CombinedEfficiencies/ClopperPearsonDS1_6Combined.root");
    TGraph *teff = (TGraph*)f2->Get("Graph");
    
    //string outFile = "/global/homes/j/jrager/LowE/Data/EffCorrectedSpectra/DS1ScaledSpectEnr_TGraph.root";
    //TFile *f3 = new TFile(outFile.c_str(),"recreate");
    //cout << "Creating outpout file" <<  endl;
    //f3->cd();
    
    double deff[500] = {};
    double effErrhi[500] = {};
    double effErrlow[500] = {};
    double rawCts[500] = {};
    double poissonErr[500] = {};
    double finalCts[500] = {};
    double finalErrhi[500] = {};
    double finalErrlow[500] = {};
    double x[500] = {};
    double xerr[500] = {};
                          
    // Loop through bins of spectrum (1keV binning), use interpolated value of efficiency
    for(int i = 0; i < 500; i++)
    {
        rawCts[i] = spect->GetBinContent(i);
        poissonErr[i] = sqrt(spect->GetBinContent(i));
        deff[i] = teff->Eval(i/5);
	effErrhi[i] = 0;
	effErrlow[i] = 0;
        x[i] = (i);
        xerr[i] = 0;
        if(i<25)
        {
            deff[i] = (teff->Eval(0)) + (((teff->Eval(5))-(teff->Eval(0)))/25)*(i);
            effErrhi[i] = fmax((teff->GetErrorYhigh(0)),(teff->GetErrorYhigh(1)));
            effErrlow[i] = fmax((teff->GetErrorYlow(0)),(teff->GetErrorYlow(1)));
        }
        else if(i>=25 && i<50)
        {
            deff[i] = (teff->Eval(5)) + (((teff->Eval(10))-(teff->Eval(5)))/25)*(i-25);
            effErrhi[i] = fmax((teff->GetErrorYhigh(1)),(teff->GetErrorYhigh(2)));
            effErrlow[i] = fmax((teff->GetErrorYlow(1)),(teff->GetErrorYlow(2)));
        }
        else if(i>=50 && i<75)
        {
            deff[i] = (teff->Eval(10)) + (((teff->Eval(15))-(teff->Eval(10)))/25)*(i-50);
            effErrhi[i] = fmax((teff->GetErrorYhigh(2)),(teff->GetErrorYhigh(3)));
            effErrlow[i] = fmax((teff->GetErrorYlow(2)),(teff->GetErrorYlow(3)));
        }
        else if(i>=75 && i<100)
        {
            deff[i] = (teff->Eval(15)) + (((teff->Eval(20))-(teff->Eval(15)))/25)*(i-75);
            effErrhi[i] = fmax((teff->GetErrorYhigh(3)),(teff->GetErrorYhigh(4)));
            effErrlow[i] = fmax((teff->GetErrorYlow(3)),(teff->GetErrorYlow(4)));
        }
        else if(i>=100 && i<125)
        {
            deff[i] = (teff->Eval(20)) + (((teff->Eval(25))-(teff->Eval(20)))/25)*(i-100);
            effErrhi[i] = fmax((teff->GetErrorYhigh(4)),(teff->GetErrorYhigh(5)));
            effErrlow[i] = fmax((teff->GetErrorYlow(4)),(teff->GetErrorYlow(5)));
        }
        else if(i>=125 && i<150)
        {
            deff[i] = (teff->Eval(25)) + (((teff->Eval(30))-(teff->Eval(25)))/25)*(i-125);
            effErrhi[i] = fmax((teff->GetErrorYhigh(5)),(teff->GetErrorYhigh(6)));
            effErrlow[i] = fmax((teff->GetErrorYlow(5)),(teff->GetErrorYlow(6)));
        }
        else if(i>=150 && i<175)
        {
            deff[i] = (teff->Eval(30)) + (((teff->Eval(35))-(teff->Eval(30)))/25)*(i-150);
            effErrhi[i] = fmax((teff->GetErrorYhigh(6)),(teff->GetErrorYhigh(7)));
            effErrlow[i] = fmax((teff->GetErrorYlow(6)),(teff->GetErrorYlow(7)));
        }
        else if(i>=175 && i<200)
        {
            deff[i] = (teff->Eval(35)) + (((teff->Eval(40))-(teff->Eval(35)))/25)*(i-175);
            effErrhi[i] = fmax((teff->GetErrorYhigh(7)),(teff->GetErrorYhigh(8)));
            effErrlow[i] = fmax((teff->GetErrorYlow(7)),(teff->GetErrorYlow(8)));
        }
        else if(i>=200 && i<225)
        {
            deff[i] = (teff->Eval(40)) + (((teff->Eval(45))-(teff->Eval(40)))/25)*(i-200);
            effErrhi[i] = fmax((teff->GetErrorYhigh(8)),(teff->GetErrorYhigh(9)));
            effErrlow[i] = fmax((teff->GetErrorYlow(8)),(teff->GetErrorYlow(9)));
        }
        else if(i>=225 && i<250)
        {
            deff[i] = (teff->Eval(45)) + (((teff->Eval(50))-(teff->Eval(45)))/25)*(i-225);
            effErrhi[i] = fmax((teff->GetErrorYhigh(9)),(teff->GetErrorYhigh(10)));
            effErrlow[i] = fmax((teff->GetErrorYlow(9)),(teff->GetErrorYlow(10)));
        }
        else if(i>=250 && i<275)
        {
            deff[i] = (teff->Eval(50)) + (((teff->Eval(55))-(teff->Eval(50)))/25)*(i-250);
            effErrhi[i] = fmax((teff->GetErrorYhigh(10)),(teff->GetErrorYhigh(11)));
            effErrlow[i] = fmax((teff->GetErrorYlow(10)),(teff->GetErrorYlow(11)));
        }
        else if(i>=275 && i<300)
        {
            deff[i] = (teff->Eval(55)) + (((teff->Eval(60))-(teff->Eval(55)))/25)*(i-275);
            effErrhi[i] = fmax((teff->GetErrorYhigh(11)),(teff->GetErrorYhigh(12)));
            effErrlow[i] = fmax((teff->GetErrorYlow(11)),(teff->GetErrorYlow(12)));
        }
        else if(i>=300 && i<325)
        {
            deff[i] = (teff->Eval(60)) + (((teff->Eval(65))-(teff->Eval(60)))/25)*(i-300);
            effErrhi[i] = fmax((teff->GetErrorYhigh(12)),(teff->GetErrorYhigh(13)));
            effErrlow[i] = fmax((teff->GetErrorYlow(12)),(teff->GetErrorYlow(13)));
        }
        else if(i>=325 && i<350)
        {
            deff[i] = (teff->Eval(65)) + (((teff->Eval(70))-(teff->Eval(65)))/25)*(i-325);
            effErrhi[i] = fmax((teff->GetErrorYhigh(13)),(teff->GetErrorYhigh(14)));
            effErrlow[i] = fmax((teff->GetErrorYlow(13)),(teff->GetErrorYlow(14)));
        }
        else if(i>=350 && i<375)
        {
            deff[i] = (teff->Eval(70)) + (((teff->Eval(75))-(teff->Eval(70)))/25)*(i-350);
            effErrhi[i] = fmax((teff->GetErrorYhigh(14)),(teff->GetErrorYhigh(15)));
            effErrlow[i] = fmax((teff->GetErrorYlow(14)),(teff->GetErrorYlow(15)));
        }
        else if(i>=375 && i<400)
        {
            deff[i] = (teff->Eval(75)) + (((teff->Eval(80))-(teff->Eval(75)))/25)*(i-375);
            effErrhi[i] = fmax((teff->GetErrorYhigh(15)),(teff->GetErrorYhigh(16)));
            effErrlow[i] = fmax((teff->GetErrorYlow(15)),(teff->GetErrorYlow(16)));
        }
        else if(i>=400 && i<425)
        {
            deff[i] = (teff->Eval(80)) + (((teff->Eval(85))-(teff->Eval(80)))/25)*(i-400);
            effErrhi[i] = fmax((teff->GetErrorYhigh(16)),(teff->GetErrorYhigh(17)));
            effErrlow[i] = fmax((teff->GetErrorYlow(16)),(teff->GetErrorYlow(17)));
        }
        else if(i>=425 && i<450)
        {
            deff[i] = (teff->Eval(85)) + (((teff->Eval(90))-(teff->Eval(85)))/25)*(i-425);
            effErrhi[i] = fmax((teff->GetErrorYhigh(17)),(teff->GetErrorYhigh(18)));
            effErrlow[i] = fmax((teff->GetErrorYlow(17)),(teff->GetErrorYlow(18)));
        }
        else if(i>=450 && i<475)
        {
            deff[i] = (teff->Eval(90)) + (((teff->Eval(95))-(teff->Eval(90)))/25)*(i-450);
            effErrhi[i] = fmax((teff->GetErrorYhigh(18)),(teff->GetErrorYhigh(19)));
            effErrlow[i] = fmax((teff->GetErrorYlow(18)),(teff->GetErrorYlow(19)));
        }
        else if(i>=475 && i<500)
	{
        deff[i] = teff->Eval(95);
        effErrhi[i] = teff->GetErrorYhigh(19);
        effErrlow[i] = teff->GetErrorYlow(19);
	}

	double p0 = 3967.24; double p1=-5.248; double p2=7.48109;
        //finalCts[i] = spect->GetBinContent(i)/(deff[i]);
	finalCts[i] = spect->GetBinContent(i)/(p0*TMath::Erf(((i/5)-p1)/p2));
        finalErrhi[i] = finalCts[i]*sqrt((1/rawCts[i]) + (effErrhi[i]/deff[i])*(effErrhi[i]/deff[i]));
        finalErrlow[i] = finalCts[i]*sqrt((1/rawCts[i]) + (effErrlow[i]/deff[i])*(effErrlow[i]/deff[i]));
        
    }
    f1->Close();
    f2->Close();

    // Create the TGraph
    //TGraph *geff = new TGraph(400
    TGraphAsymmErrors *geff = new TGraphAsymmErrors(500, x, finalCts, xerr, xerr, finalErrlow, finalErrhi);
    //TCanvas *c2 = new TCanvas("c2","c2",800,600);
    geff->SetMarkerStyle(2);
    geff->SetMarkerColor(kRed);
    geff->SetTitle("DS1 Efficiency Corrected Spectrum, Enriched Detectors");
    geff->GetXaxis()->SetTitle("trapENFCal (keV)");
    geff->GetYaxis()->SetTitle("cts/kg/d/keV");
    geff->Draw("AP");
    //geff->Write();
    //f3->Close();
                      
    cout << "Done" << endl;
}

double GetEff(double x)
{
  // double sig = std::sqrt(std::pow(sig0,2) + eps * F * energy);
  double p0 = 3967.24; double p1=-5.248; double p2=7.48109;
  double sig = p0*TMath::Erf((x-p1)/p2);

  return sig;
}

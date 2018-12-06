//  ScaleSpectra.c
//
//  Convolves the combined efficiency with the combined spectrum for Enr detectors in DS1
//  Outputs spectrum as TGraphAssymErrors
//
//  Created by Jamin on 12/3/18.
//

#include <math.h>
{
    // Input files
    TFile *f1 = new TFile("/global/homes/j/jrager/LowE/AnalSpect/AnalysisSpectDS1Enr_1kBinn.root");
    TH1F *spect= (TH1F*)f1->Get("spect");
    TFile *f2 = new TFile("/global/homes/j/jrager/LowE/Data/CombinedEfficiencies/ClopperErrorDS1Enr.root");
    TGraph *teff = (TGraph*)f2->Get("Graph");
    
    string outFile = "/global/homes/j/jrager/LowE/Data/EffCorrectedSpectra/DS1ScaledSpectEnr_TGraph.root";
    TFile *f3 = new TFile(outFile.c_str(),"recreate");
    cout << "Creating outpout file" <<  endl;
    f3->cd();
    
    double deff[100] = {};
    double effErrhi[100] = {};
    double effErrlow[100] = {};
    double rawCts[400] = {};
    double poissonErr[400] = {};
    double finalCts[400] = {};
    double finalErrhi[400] = {};
    double finalErrlow[400] = {};
    double x[100] = {};
    double xerr[100] = {};
                          
    // Loop through bins of spectrum (1keV binning), use interpolated value of efficiency
    for(int i = 0; i < 100; i++)
    {
        rawCts[i] = spect->GetBinContent(i);
        poissonErr[i] = sqrt(spect->GetBinContent(i));
        deff[i] = teff->Eval(i);
        effErrhi[i] = 0;
        effErrlow[i] = 0;
        x[i] = (i);
        xerr[i] = 0;
        if(i<5)
        {
            deff[i] = (teff->Eval(0)) + (((teff->Eval(5))-(teff->Eval(0)))/5)*(i);
            effErrhi[i] = fmax((teff->GetErrorYhigh(0)),(teff->GetErrorYhigh(1)));
            effErrlow[i] = fmax((teff->GetErrorYlow(0)),(teff->GetErrorYlow(1)));
        }
        else if(i>=5 && i<10)
        {
            deff[i] = (teff->Eval(5)) + (((teff->Eval(10))-(teff->Eval(5)))/5)*(i-5);
            effErrhi[i] = fmax((teff->GetErrorYhigh(1)),(teff->GetErrorYhigh(2)));
            effErrlow[i] = fmax((teff->GetErrorYlow(1)),(teff->GetErrorYlow(2)));
        }
        else if(i>=10 && i<15)
        {
            deff[i] = (teff->Eval(10)) + (((teff->Eval(15))-(teff->Eval(10)))/5)*(i-10);
            effErrhi[i] = fmax((teff->GetErrorYhigh(2)),(teff->GetErrorYhigh(3)));
            effErrlow[i] = fmax((teff->GetErrorYlow(2)),(teff->GetErrorYlow(3)));
        }
        else if(i>=15 && i<20)
        {
            deff[i] = (teff->Eval(15)) + (((teff->Eval(20))-(teff->Eval(15)))/5)*(i-15);
            effErrhi[i] = fmax((teff->GetErrorYhigh(3)),(teff->GetErrorYhigh(4)));
            effErrlow[i] = fmax((teff->GetErrorYlow(3)),(teff->GetErrorYlow(4)));
        }
        else if(i>=20 && i<25)
        {
            deff[i] = (teff->Eval(20)) + (((teff->Eval(25))-(teff->Eval(20)))/5)*(i-20);
            effErrhi[i] = fmax((teff->GetErrorYhigh(4)),(teff->GetErrorYhigh(5)));
            effErrlow[i] = fmax((teff->GetErrorYlow(4)),(teff->GetErrorYlow(5)));
        }
        else if(i>=25 && i<30)
        {
            deff[i] = (teff->Eval(25)) + (((teff->Eval(30))-(teff->Eval(25)))/5)*(i-25);
            effErrhi[i] = fmax((teff->GetErrorYhigh(5)),(teff->GetErrorYhigh(6)));
            effErrlow[i] = fmax((teff->GetErrorYlow(5)),(teff->GetErrorYlow(6)));
        }
        else if(i>=30 && i<35)
        {
            deff[i] = (teff->Eval(30)) + (((teff->Eval(35))-(teff->Eval(30)))/5)*(i-30);
            effErrhi[i] = fmax((teff->GetErrorYhigh(6)),(teff->GetErrorYhigh(7)));
            effErrlow[i] = fmax((teff->GetErrorYlow(6)),(teff->GetErrorYlow(7)));
        }
        else if(i>=35 && i<40)
        {
            deff[i] = (teff->Eval(35)) + (((teff->Eval(40))-(teff->Eval(35)))/5)*(i-35);
            effErrhi[i] = fmax((teff->GetErrorYhigh(7)),(teff->GetErrorYhigh(8)));
            effErrlow[i] = fmax((teff->GetErrorYlow(7)),(teff->GetErrorYlow(8)));
        }
        else if(i>=40 && i<45)
        {
            deff[i] = (teff->Eval(40)) + (((teff->Eval(45))-(teff->Eval(40)))/5)*(i-40);
            effErrhi[i] = fmax((teff->GetErrorYhigh(8)),(teff->GetErrorYhigh(9)));
            effErrlow[i] = fmax((teff->GetErrorYlow(8)),(teff->GetErrorYlow(9)));
        }
        else if(i>=45 && i<50)
        {
            deff[i] = (teff->Eval(45)) + (((teff->Eval(50))-(teff->Eval(45)))/5)*(i-45);
            effErrhi[i] = fmax((teff->GetErrorYhigh(9)),(teff->GetErrorYhigh(10)));
            effErrlow[i] = fmax((teff->GetErrorYlow(9)),(teff->GetErrorYlow(10)));
        }
        else if(i>=50 && i<55)
        {
            deff[i] = (teff->Eval(50)) + (((teff->Eval(55))-(teff->Eval(50)))/5)*(i-50);
            effErrhi[i] = fmax((teff->GetErrorYhigh(10)),(teff->GetErrorYhigh(11)));
            effErrlow[i] = fmax((teff->GetErrorYlow(10)),(teff->GetErrorYlow(11)));
        }
        else if(i>=55 && i<60)
        {
            deff[i] = (teff->Eval(55)) + (((teff->Eval(60))-(teff->Eval(55)))/5)*(i-55);
            effErrhi[i] = fmax((teff->GetErrorYhigh(11)),(teff->GetErrorYhigh(12)));
            effErrlow[i] = fmax((teff->GetErrorYlow(11)),(teff->GetErrorYlow(12)));
        }
        else if(i>=60 && i<65)
        {
            deff[i] = (teff->Eval(60)) + (((teff->Eval(65))-(teff->Eval(60)))/5)*(i-60);
            effErrhi[i] = fmax((teff->GetErrorYhigh(12)),(teff->GetErrorYhigh(13)));
            effErrlow[i] = fmax((teff->GetErrorYlow(12)),(teff->GetErrorYlow(13)));
        }
        else if(i>=65 && i<70)
        {
            deff[i] = (teff->Eval(65)) + (((teff->Eval(70))-(teff->Eval(65)))/5)*(i-65);
            effErrhi[i] = fmax((teff->GetErrorYhigh(13)),(teff->GetErrorYhigh(14)));
            effErrlow[i] = fmax((teff->GetErrorYlow(13)),(teff->GetErrorYlow(14)));
        }
        else if(i>=70 && i<75)
        {
            deff[i] = (teff->Eval(70)) + (((teff->Eval(75))-(teff->Eval(70)))/5)*(i-70);
            effErrhi[i] = fmax((teff->GetErrorYhigh(14)),(teff->GetErrorYhigh(15)));
            effErrlow[i] = fmax((teff->GetErrorYlow(14)),(teff->GetErrorYlow(15)));
        }
        else if(i>=75 && i<80)
        {
            deff[i] = (teff->Eval(75)) + (((teff->Eval(80))-(teff->Eval(75)))/5)*(i-75);
            effErrhi[i] = fmax((teff->GetErrorYhigh(15)),(teff->GetErrorYhigh(16)));
            effErrlow[i] = fmax((teff->GetErrorYlow(15)),(teff->GetErrorYlow(16)));
        }
        else if(i>=80 && i<85)
        {
            deff[i] = (teff->Eval(80)) + (((teff->Eval(85))-(teff->Eval(80)))/5)*(i-80);
            effErrhi[i] = fmax((teff->GetErrorYhigh(16)),(teff->GetErrorYhigh(17)));
            effErrlow[i] = fmax((teff->GetErrorYlow(16)),(teff->GetErrorYlow(17)));
        }
        else if(i>=85 && i<90)
        {
            deff[i] = (teff->Eval(85)) + (((teff->Eval(90))-(teff->Eval(85)))/5)*(i-85);
            effErrhi[i] = fmax((teff->GetErrorYhigh(17)),(teff->GetErrorYhigh(18)));
            effErrlow[i] = fmax((teff->GetErrorYlow(17)),(teff->GetErrorYlow(18)));
        }
        else if(i>=90 && i<95)
        {
            deff[i] = (teff->Eval(90)) + (((teff->Eval(95))-(teff->Eval(90)))/5)*(i-90);
            effErrhi[i] = fmax((teff->GetErrorYhigh(18)),(teff->GetErrorYhigh(19)));
            effErrlow[i] = fmax((teff->GetErrorYlow(18)),(teff->GetErrorYlow(19)));
        }
        else if(i>=95 && i<100)
	{
        deff[i] = teff->Eval(95);
        effErrhi[i] = teff->GetErrorYhigh(19);
        effErrlow[i] = teff->GetErrorYlow(19);
	}
        
        finalCts[i] = spect->GetBinContent(i)/(teff->Eval(i));
        finalErrhi[i] = finalCts[i]*sqrt((1/rawCts[i]) + (effErrhi[i]/deff[i])*(effErrhi[i]/deff[i]));
        finalErrlow[i] = finalCts[i]*sqrt((1/rawCts[i]) + (effErrlow[i]/deff[i])*(effErrlow[i]/deff[i]));
        
    }
    f1->Close();
    f2->Close();

    // Create the TGraph
    TGraphAsymmErrors *geff = new TGraphAsymmErrors(100, x, finalCts, xerr, xerr, finalErrlow, finalErrhi);
    //TCanvas *c2 = new TCanvas("c2","c2",800,600);
    geff->SetMarkerStyle(2);
    geff->SetMarkerColor(kRed);
    geff->SetTitle("DS1 Efficiency Corrected Spectrum, Enriched Detectors");
    geff->GetXaxis()->SetTitle("trapENFCal (keV)");
    geff->GetYaxis()->SetTitle("cts/kg/d/keV");
    //geff->Draw("AP");
    geff->Write();
    f3->Close();
                      
    cout << "Done" << endl;
}

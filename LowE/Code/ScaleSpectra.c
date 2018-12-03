//  ScaleSpectra.c
//
//  Convolves the combined efficiency with the combined spectrum for two detectors in DS1
//
//  Created by Jamin on 10/1/18.
//

{
    // Input files
    TFile *f1 = new TFile("/global/homes/j/jrager/LowE/Data/Test/DS1EnrSpecCombined.root);
    TH1F *spect= (TH1F*)f1->Get("spect");
    TFile *f2 = new TFile("ClopperErrorDS1Combined.root");
    TGraph *eff = (TGraph*)f2->Get("Graph");
    
    // Output file
    string outFile = "DS1ScaledSpectCombined.root";
    TFile *f3 = new TFile(outFile.c_str(),"recreate");
    cout << "Creating outpout file" <<  endl;
    f3->cd();
                          
    // Output file
    TFile *f0 = new TFile(outFile.c_str(),"recreate");
    cout << "Creating outpout file" <<  endl;
    f0->cd();
    
    // Loop through bins of spectrum (1keV binning), use interpolated value of efficiency
    for(int i = 0; i < spect->GetNbinsX(); i++)
    {
        spect->SetBinContent(i, spect->GetBinContent(i)/(eff->Eval(i)));
    }
    spect->Write();

    double cts[100] = {};
    
                          
                          
    for(int i = 1; i < ((spect->GetNbinsX())+1); i++)
    {
        
        
        
    }
    // Create the TGraph
    TGraphAsymmErrors *geff = new TGraphAsymmErrors(50, x, effArr, xerr, xerr, effLo, effHi);
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    geff->SetMarkerStyle(21);
    geff->SetMarkerColor(kRed);
    geff->SetTitle("DS3 ch 624, 2keV binning");
    geff->GetXaxis()->SetTitle("trapENFCal (keV)");
    geff->GetYaxis()->SetTitle("efficiency");
    //geff->Draw("AP");
                          
    cout << "Done" << endl;
}

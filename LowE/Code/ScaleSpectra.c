//  ScaleSpectra.c
//
//  Convolves the combined efficiency with the combined spectrum for two detectors in DS1
//
//  Created by Jamin on 10/1/18.
//

{
    // Input files
    TFile *f1 = new TFile("/global/homes/j/jrager/LowE/Data/Test/DS1EnrSpecCombined.root);
    TH1F *spect= (TH1F*)f1->Get("enrLE");
    TFile *f2 = new TFile("ClopperErrorDS1Combined.root");
    TGraph *eff = (TGraph*)f2->Get("Graph");
    
    // Output file
    string outFile = "DS1ScaledSpectCombined.root";
    TFile *f3 = new TFile(outFile.c_str(),"recreate");
    cout << "Creating outpout file" <<  endl;
    f3->cd();
                  
    // Loop through bins of spectrum (1keV binning), use interpolated value of efficiency
    for(int i = 0; i < spect->GetNbinsX(); i++)
    {
        spect->SetBinContent(i, spec->GetBinContent(i)/(eff->Eval(i)));
    }
    spect->Write();
    cout << "Done" << endl;
}

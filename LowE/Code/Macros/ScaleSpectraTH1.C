//
//  ScaleSpectra.c
//  
//
//  Created by Jamin on 10/1/18.
//

{
  TFile *f1 = new TFile("~/LowE/AnalSpect/AnalysisSpectDS1Enr.root");
  TH1F *spect= (TH1F*)f1->Get("spect");
  TFile *f2 = new TFile("~/LowE/Data/CombinedEfficiencies/ClopperErrorDS1Enr.root");
  TGraph *eff = (TGraph*)f2->Get("Graph");
  //string outFile = "~/LowE/Data/EffCorrectedSpectra/DS1ScaledSpectEnr.root";
  //TFile *f0 = new TFile(outFile.c_str(),"recreate");
  //cout << "Creating outpout file" <<  endl;
  //f0->cd();
                          
  for(int i = 0; i < spect->GetNbinsX(); i++)
  {
      spect->SetBinContent(i, spect->GetBinContent(i)/(eff->Eval(i)));
  }

  //f1->Close();
  //f2->Close();

  //Double_t ScaleFactor = 4;
  //spect->Scale(ScaleFactor);
  
  //spect->Write();
  spect->Draw();
  
  //f0->Close();

  cout << "Done" << endl;
}

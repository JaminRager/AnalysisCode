{
  TChain* ch = new TChain("skimTree", "skimTree");
  ch->Add("/global/u1/j/jrager/SpectralAnalysis/Official/spectra/DS1/skim/newDS1/skimP3KJR*.root");

  Double_t scale = 1/ch->Integral();
  ch->Scale(scale);
  
  ch->Draw("trapECal >> h(160, 582, 742)", "!isLNFill && !muVeto1ms && !wfDCBits && isGood && gain==0 && mH<2 && dcrSlope99<0 && !(time_s > 2192e3 && time_s < 2195e3) && !(time_s > 7370e3 && time_s <7371e3) && !(time_s > 7840e3 && time_s < 7860e3) && !(time_s > 8384e3 && time_s < 8387e3) && !(time_s > 8984e3 && time_s < 8985e3) && !(time_s > 9002e3 && time_s < 9005e3) && run != 13075 && run != 13093 && run != 13116");
}

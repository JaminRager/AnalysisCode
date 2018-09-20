{
  TChain* ch = new TChain("skimTree", "skimTree");
  ch->Add("/global/project/projectdirs/majorana/data/mjd/surfmjd/analysis/skim/DS1/20160621_265313037/skimDS1_*.root");

  ch->Draw("trapECal >> h(40, 776, 816)", "!isLNFill && !muVeto && !wfDCBits && isGood && gain==0 && !(time_s > 2192e3 && time_s < 2195e3) && !(time_s > 7370e3 && time_s <7371e3) && !(time_s > 7840e3 && time_s < 7860e3) && !(time_s > 8384e3 && time_s < 8387e3) && !(time_s > 8984e3 && time_s < 8985e3) && !(time_s > 9002e3 && time_s < 9005e3) && run != 13075 && run != 13093 && run != 13116");
}

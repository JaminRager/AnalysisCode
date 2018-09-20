{
  TChain* ch = new TChain("skimTree", "skimTree");
  ch->Add("/global/project/projectdirs/majorana/data/mjd/surfmjd/analysis/skim/DS0/20160621_265313037/skimDS0_*.root");

  ch->Draw("trapECal >> h(40, 652, 672)", "!isLNFill && !muVeto && !wfDCBits && isGood && gain==0");
}

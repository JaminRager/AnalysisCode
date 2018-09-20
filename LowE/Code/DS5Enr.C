{
  TChain* ch = new TChain("skimTree", "skimTree");
  ch->Add("/global/project/projectdirs/majorana/data/mjd/surfmjd/analysis/skim/DS5/skimgatrev_7938486/skimDS5_0.root");

  ch->Draw("trapENFCal >> h(60, 0, 60)", "isEnr && !muVeto && !wfDCBits && isGood && gain==0 && mH==1 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2");
}

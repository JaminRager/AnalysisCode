{
  TChain* ch = new TChain("skimTree", "skimTree");
  ch->Add("/global/project/projectdirs/majorana/data/mjd/surfmjd/analysis/skim/DS3/skimgatrev_86288584/*.root");

  ch->Draw("trapENFCal >> h(60, 0, 60)", "isNat && !muVeto && !wfDCBits && isGood && gain==0 && mH==1 && kvorrT/trapENFCal>0.6 && kvorrT/trapENFCal<2 && channel != 680 ");
}

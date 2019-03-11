{
  TChain* ch = new TChain("skimTree", "skimTree");
  ch->Add("/global/u1/j/jrager/low_energy_skim/output/*.root");
  //TH1F *trapETailMin = new TH1F("trapETailMin", "trapETailMin", 59, 0.5, 30);
  //TH1F *trapENFCal = new TH1F("trapENFCal", "trapENFCal", 59, 0.5, 30);
  TH2F *twoD = new TH2F("twoD", "twoD", 59, 0.5, 30, 100, -50, 0);
  //TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
  //legend->AddEntry(trapETailMin,"trapETailMin","f");
  //legend->AddEntry(trapENFCal,"trapENFCal","f");
  char theCut[1000];
  sprintf(theCut,"gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0");
  //ch->Project("trapENFCal","trapENFCal",theCut);
  //ch->Project("trapETailMin","trapETailMin",theCut);
  ch->Project("twoD","trapETailMin:trapENFCal");
  //twoD->SetOption("colz");
  twoD->Draw();
  //trapETailMin->Draw();
  //trapETailMin->SetLineColor(kRed);
  //trapENFCal->Draw("same");
  //trapENFCal->SetLineColor(kBlue);
  //legend->Draw();
}

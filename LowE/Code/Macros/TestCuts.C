{
  TChain* ch = new TChain("skimTree", "skimTree");
  ch->Add("/global/u1/j/jrager/low_energy_skim/output/*.root");
  TH1F *hmHgood = new TH1F("mHgood", "mHgood", 30, -0.5, 29.5);
  TH1F *htrapENFCalAll = new TH1F("trapENFCalAll", "trapENFCalAll", 30, 0., 30.);
  TH1F *hchannels47 = new TH1F("channels47", "channels47", 150, 550.5, 700.5);
  TH1F *hrun47 = new TH1F("run47", "run47",17981-16796+1 , 16796, 17982 );
  TH1F *htrapENFCal511Coin = new TH1F("trapENFCal511Coin", "trapENFCal511Coin", 30, 0., 30.);
  TH2F *hkvorrT_E = new TH2F("hkvorrT_E", "hkvorrT_E", 30, 0., 30., 200, 0., 5.);
  TH1F *htrapENFCalEnr = new TH1F("trapENFCalEnr", "trapENFCalEnr", 30, 0., 30.);
  TH1F *htrapENFCalNat = new TH1F("trapENFCalNat", "trapENFCalNat", 30, 0., 30.);
  TH1F *htrapENFCalwAECutEnr = new TH1F("trapENFCalwAECutenr", "trapENFCalwAECutsenr", 30, 0., 30.);
  TH1F *htrapENFCalwAECutNat = new TH1F("trapENFCalwAECutNat", "trapENFCalwAECutsNat", 30, 0., 30.);
  TH1F *htrapENFCalwAEDCRCutEnr = new TH1F("trapENFCalwAEDCRCutenr", "trapENFCalwAEDCRCutsenr", 30, 0., 30.);
  TH1F *htrapENFCalwAEDCRCutNat = new TH1F("trapENFCalwAEDCRCutNat", "trapENFCalwAEDCRCutsNat", 30, 0., 30.);
  
  TLegend *legend = new TLegend(0.1,0.7,0.48,0.9);
  legend->AddEntry(hmHgood,"hmHgood","f");
  legend->AddEntry(htrapENFCalAll,"htrapENFCalAll","f");
  legend->AddEntry(hchannels47,"hchannels47","f");
  legend->AddEntry(hrun47,"hrun47","f");
  legend->AddEntry(htrapENFCal511Coin,"htrapENFCal511Coin","f");
  legend->AddEntry(hkvorrT_E,"hkvorrT_E","f");
  legend->AddEntry(htrapENFCalEnr,"htrapENFCalEnr","f");
  legend->AddEntry(htrapENFCalNat,"htrapENFCalNat","f");
  legend->AddEntry(htrapENFCalwAECutEnr,"htrapENFCalwAECutEnr","f");
  legend->AddEntry(htrapENFCalwAECutNat,"htrapENFCalwAECutNat","f");
  legend->AddEntry(htrapENFCalwAEDCRCutEnr,"htrapENFCalwAEDCRCutEnr","f");
  legend->AddEntry(htrapENFCalwAEDCRCutNat,"htrapENFCalwAEDCRCutNat","f");
  ch->Project("hmHgood","mH","gain==0 && isGood && !wfDCBits && !muVeto");
  ch->Project("htrapENFCalAll","mH","gain==0 && isGood && !wfDCBits && !muVeto dcr90<0");
  ch->Project("hmHgood","mH","gain==0 && isGood && !wfDCBits && !muVeto");


  ch->Project("cuts","trapENFCal","trapENFCal>0.8 && gain==0 && mH==1 && isGood && !muVeto && !isLNFill1 && !isLNFill2 && P!=0 && D!=0 && trapETailMin<0.5");
  
  nocuts->Draw();
  nocuts->SetLineColor(kRed);
  cuts->Draw("same");
  cuts->SetLineColor(kBlue);
  legend->Draw();
}

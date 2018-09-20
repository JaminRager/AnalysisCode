{
  // gStyle->SetOptStat(0);
    
  //.x MJDTalkPlotStyle.C
    
  TFile *d1 = new TFile("CombinedDS1_Newest.root");
  TH1F *h1 = (TH1F*)d1->Get("enrHE");
  TH1F *h2 = (TH1F*)d1->Get("natHE");
  TFile *d2 = new TFile("CombinedDS2_Newest.root");
  TH1F *h3 = (TH1F*)d2->Get("enrHE");
  TH1F *h4 = (TH1F*)d2->Get("natHE");    
  TFile *d3 = new TFile("CombinedDS3_Newest.root");
  TH1F *h5 = (TH1F*)d3->Get("enrHE");
  TH1F *h6 = (TH1F*)d3->Get("natHE");
  TFile *d4 = new TFile("CombinedDS4_Newest.root");
  TH1F *h7 = (TH1F*)d4->Get("enrHE");
  TH1F *h8 = (TH1F*)d4->Get("natHE");
  TFile *d5 = new TFile("CombinedDS5a_Newest.root");
  TH1F *h9 = (TH1F*)d5->Get("enrHE");
  TH1F *h10 = (TH1F*)d5->Get("natHE");
  TFile *d6 = new TFile("CombinedDS5b_Newest.root");
  TH1F *h11 = (TH1F*)d6->Get("enrHE");
  TH1F *h12 = (TH1F*)d6->Get("natHE");

  TFile *e1 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isEnr_DS1.root");
  TH1F *g1 = (TH1F*)e1->Get("DS1_isEnr_UnCorr");   
  TFile *e2 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isNat_DS1.root");
  TH1F *g2 = (TH1F*)e2->Get("DS1_isNat_UnCorr");
  TFile *e3 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isEnr_DS2.root");
  TH1F *g3 = (TH1F*)e3->Get("DS2_isEnr_UnCorr");
  TFile *e4 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isNat_DS2.root");
  TH1F *g4 = (TH1F*)e4->Get("DS2_isNat_UnCorr");
  TFile *e5 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isEnr_DS3.root");
  TH1F *g5 = (TH1F*)e5->Get("DS3_isEnr_UnCorr");
  TFile *e6 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isNat_DS3.root");
  TH1F *g6 = (TH1F*)e6->Get("DS3_isNat_UnCorr");
  TFile *e7 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isEnr_DS4.root");
  TH1F *g7 = (TH1F*)e7->Get("DS4_isEnr_UnCorr");
  TFile *e8 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isNat_DS4.root");
  TH1F *g8 = (TH1F*)e8->Get("DS4_isNat_UnCorr");
  TFile *e9 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isEnr_DS5b.root");
  TH1F *g9 = (TH1F*)e9->Get("DS5b_isEnr_UnCorr");
  TFile *e10 = new TFile("/global/projecta/projectdirs/majorana/users/jrager/LAT_Spectra/Bkg_isNat_DS5b.root");
  TH1F *g10 = (TH1F*)e10->Get("DS5b_isNat_UnCorr");

  //TFile *f1 = new TFile("DS1NoCuts.root");
  //TH1F *z1 = (TH1F*)f1->Get("enrNoCut");
  //TH1F *z2 = (TH1F*)f1->Get("natNoCut");
  //TFile *f2 = new TFile("DS2NoCuts.root");
  //TH1F *z3 = (TH1F*)f2->Get("enrNoCut");
  //TH1F *z4 = (TH1F*)f2->Get("natNoCut");
  //TFile *f3 = new TFile("DS3NoCuts.root");
  //TH1F *z5 = (TH1F*)f3->Get("enrNoCut");
  //TH1F *z6 = (TH1F*)f3->Get("natNoCut");
  //TFile *f4 = new TFile("DS4NoCuts.root");
  //TH1F *z7 = (TH1F*)f4->Get("enrNoCut");
  //TH1F *z8 = (TH1F*)f4->Get("natNoCut");
  //TFile *f5 = new TFile("DS5aNoCuts.root");
  //TH1F *z9 = (TH1F*)f5->Get("enrNoCut");
  //TH1F *z10 = (TH1F*)f5->Get("natNoCut");
  //TFile *f6 = new TFile("DS5bNoCuts.root");
  //TH1F *z11 = (TH1F*)f6->Get("enrNoCut");
  //TH1F *z12 = (TH1F*)f6->Get("natNoCut");

  TList *list1 = new TList;
  list1->Add(h1);
  //list1->Add(h2);
  list1->Add(h3);
  //list1->Add(h4);
  list1->Add(h5);
  //list1->Add(h6);
  list1->Add(h7);
  //list1->Add(h8);
  //list1->Add(h9);
  //list1->Add(h10);
  list1->Add(h11);
  list1->Add(h12);
    
  TList *list2 = new TList;
  list2->Add(g1);
  //list2->Add(g2);
  list2->Add(g3);
  //list2->Add(g4);
  list2->Add(g5);
  //list2->Add(g6);
  list2->Add(g7);
  //list2->Add(g8);
  list2->Add(g9);
  list2->Add(g10);

  //TList *list3 = new TList;
  //list3->Add(z1);
  //list3->Add(z2);
  //list3->Add(z3);
  //list3->Add(z4);
  //list3->Add(z5);
  //list3->Add(z6);
  //list3->Add(z7);
  //list3->Add(z8);
  //list3->Add(z9);
  //list3->Add(z10);
  //list3->Add(z11);
  //list3->Add(z12);
  
  Double_t Exposure1 = 4/4106.0;
  Double_t Exposure2 = 10/4106.0;
  
  TH1F *h = (TH1F*)h1->Clone("h");
  h->Reset();
  h->Merge(list1);
  h->Rebin(4);
  h->Scale(Exposure1);
  h->SetTitle("DS1-4 enr,5b enr + nat: 2242 kg-d");
  h->SetLineColor(kBlack);
  h->Draw("HIST");
    
  TH1F *g = (TH1F*)g1->Clone("g");
  g->Reset();
  g->Merge(list2);
  g->Rebin(10);
  g->Scale(Exposure2);
  g->SetLineColor(kBlue);
  g->Draw("same");
    
  //TH1F *z = (TH1F*)z1->Clone("z");
  //z->Reset();
  //z->Merge(list3);
  //z->Rebin(4);
  //z->Scale(Exposure1);
  //z->SetLineColor(kRed);
  //z->Draw("HIST same");
}

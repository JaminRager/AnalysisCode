{
  // gStyle->SetOptStat(0);
    
  //.x MJDTalkPlotStyle.C
    
  TFile *f1 = new TFile("CombinedDS1_Newest.root");
  TH1F *h1 = (TH1F*)f1->Get("enrHE");
    
  TFile *f2 = new TFile("CombinedDS2_Newest.root");
  TH1F *h2 = (TH1F*)f2->Get("enrHE");
    
  TFile *f3 = new TFile("CombinedDS3_Newest.root");
  TH1F *h3 = (TH1F*)f3->Get("enrHE");
    
  TFile *f4 = new TFile("CombinedDS4_Newest.root");
  TH1F *h4 = (TH1F*)f4->Get("enrHE");
    
  TFile *f5a = new TFile("CombinedDS5a_Newest.root");
  TH1F *h5a = (TH1F*)f5a->Get("enrHE");
  TH1F *h6a = (TH1F*)f5a->Get("natHE");
    
  TFile *f5b = new TFile("CombinedDS5b_Newest.root");
  TH1F *h5b = (TH1F*)f5b->Get("enrHE");
  TH1F *h6b = (TH1F*)f5b->Get("natHE");

  TFile *f6 = new TFile("CombinedDS6_Newest.root");
  TH1F *h6 = (TH1F*)f6->Get("enrHE");
  TH1F *h7 = (TH1F*)f6->Get("natHE");
    
  //TFile *f7 = new TFile("DS6NoCuts.root");
  //TH1F *h8 = (TH1F*)f7->Get("enrNoCut");
  //TH1F *h9 = (TH1F*)f7->Get("natNoCut");

  TList *list1 = new TList;
  list1->Add(h1);
  list1->Add(h2);
  list1->Add(h3);
  list1->Add(h4);
  list1->Add(h5a);
  list1->Add(h6a);
  list1->Add(h5b);
  list1->Add(h6b);
  list1->Add(h6);
  list1->Add(h7);

  //TList *list2 = new TList;
  //list2->Add(h8);
  //list2->Add(h9);

  //Double_t Exposure = 1/4106.0;
  //Double_t Exposure = 1/1499.0;
  Double_t Exposure = 1/5606.0;
    
  TH1F *h = (TH1F*)h1->Clone("h");
  h->Reset();
  h->Merge(list1);
  h->Scale(Exposure);
  h->Rebin(4);
  //h->SetTitle("0nbb Data Sets: 4106 kg-d");
  //h->SetTitle("DS6 Through 12/05/17: 1499 kg-d");
  h->SetTitle("DS1-6 through 12/05/17: 5606 kg-d");
  h->GetYaxis()->SetTitle("cts/kg/d/keV");
  h->SetLineColor(kBlack);
  h->Draw("HIST");

  //TH1F *h0 = (TH1F*)h8->Clone("h0");
  //h0->Reset();
  //h0->Merge(list2);
  //h0->Scale(Exposure);
  //h0->SetLineColor(kRed);
  //h0->Draw("HIST same");
}

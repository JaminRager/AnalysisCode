  // Calculate efficiency weighted exposure 
  // Combines data from two TGraphs with efficiency and Clopper-Pearson error bars
  #include "TMath.h"
  {	
    TFile *f1 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1204.root");
    TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
    //TFile *f2 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1174.root");
    //TGraphAsymmErrors *geff2 = (TGraphAsymmErrors*)f2->Get("Graph");
    //TFile *f3 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1144.root");
    //TGraphAsymmErrors *geff3 = (TGraphAsymmErrors*)f3->Get("Graph");
    //TFile *f4 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1106.root");
    //TGraphAsymmErrors *geff4 = (TGraphAsymmErrors*)f4->Get("Graph");
    TFile *f5 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1176.root");
    TGraphAsymmErrors *geff5 = (TGraphAsymmErrors*)f5->Get("Graph");
    TFile *f6 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1172.root");
    TGraphAsymmErrors *geff6 = (TGraphAsymmErrors*)f6->Get("Graph");
    //TFile *f7 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1170.root");
    //TGraphAsymmErrors *geff7 = (TGraphAsymmErrors*)f7->Get("Graph");
    //TFile *f8 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1136.root");
    //TGraphAsymmErrors *geff8 = (TGraphAsymmErrors*)f8->Get("Graph");
    //TFile *f9 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1330.root");
    //TGraphAsymmErrors *geff9 = (TGraphAsymmErrors*)f9->Get("Graph");
    TFile *f10 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1332.root");
    TGraphAsymmErrors *geff10 = (TGraphAsymmErrors*)f10->Get("Graph");
    TFile *f11 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1296.root");
    TGraphAsymmErrors *geff11 = (TGraphAsymmErrors*)f11->Get("Graph");
    TFile *f12 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1298.root");
    TGraphAsymmErrors *geff12 = (TGraphAsymmErrors*)f12->Get("Graph");
    TFile *f13 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1236.root");
    TGraphAsymmErrors *geff13 = (TGraphAsymmErrors*)f13->Get("Graph");
    //TFile *f14 = new TFile("~/LowE/Data/IndivEfficiencies/ClopperErrorDS1Ch1232.root");
    //TGraphAsymmErrors *geff14 = (TGraphAsymmErrors*)f14->Get("Graph");
      
    cout << "Loading data files" << endl;

    double eff1[20] = {};
    //double eff2[20] = {};
    //double eff3[20] = {};
    //double eff4[20] = {};
    double eff5[20] = {};
    double eff6[20] = {};
    //double eff7[20] = {};
    //double eff8[20] = {};
    //double eff9[20] = {};
    double eff10[20] = {};
    double eff11[20] = {};
    double eff12[20] = {};
    double eff13[20] = {};
    //double eff14[20] = {};
    double effSum[20] = {};
    double errhi1[20] = {};
    double errlow1[20] = {};
    //double errhi2[20] = {};
    //double errlow2[20] = {};
    //double errhi3[20] = {};
    //double errlow3[20] = {};
    //double errhi4[20] = {};
    //double errlow4[20] = {};
    double errhi5[20] = {};
    double errlow5[20] = {};
    double errhi6[20] = {};
    double errlow6[20] = {};
    //double errhi7[20] = {};
    //double errlow7[20] = {};
    //double errhi8[20] = {};
    //double errlow8[20] = {};
    //double errhi9[20] = {};
    //double errlow9[20] = {};
    double errhi10[20] = {};
    double errlow10[20] = {};
    double errhi11[20] = {};
    double errlow11[20] = {};
    double errhi12[20] = {};
    double errlow12[20] = {};
    double errhi13[20] = {};
    double errlow13[20] = {};
    //double errhi14[20] = {};
    //double errlow14[20] = {};
    double errSumhi[20] = {};
    double errSumlow[20] = {};
    double x[20] = {};
    double xerr[20] = {};
    cout << "Initializing arrays" << endl;

    double LT1 = 18.7355;
    double M1 = 0.917;
    double errM1 = 0.012;
    //double M2 = 0.581;
    //double errM2 = 0.013;
    //double M3 = 0.562;
    //double errM3 = 0.013;
    //double M4 = 0.559;
    //double errM4 = 0.013;
    double LT5 = 18.7360;
    double M5 = 0.872;
    double errM5 = 0.012;
    double LT6 = 18.7369;
    double M6 = 0.852;
    double errM6 = 0.011;
    //double M7 = 0.558;
    //double errM7 = 0.013;
    //double M8 = 0.566;
    //double errM8 = 0.013;
    //double M9 = 0.557;
    //double errM9 = 0.013;
    double LT10 = 18.8582;
    double M10 = 1.031;
    double errM10 = 0.013;
    double LT11 = 18.8611;
    double M11 = 0.4462;
    double errM11 = 0.0084;
    double LT12 = 18.8615;
    double M12 = 0.775;
    double errM12 = 0.012;
    double LT13 = 18.8582;
    double M13 = 0.562;
    double errM13 = 0.01;
    //double M14 = 0.567;
    //double errM14 = 0.013;
    

    cout << "Beginning loop" << endl;
    for(int i = 0; i < 20; i++)
    {
	eff1[i] = geff1->Eval(i*5);
	//eff2[i] = geff2->Eval(i*5);
    //eff3[i] = geff3->Eval(i*5);
    //eff4[i] = geff4->Eval(i*5);
    eff5[i] = geff5->Eval(i*5);
    eff6[i] = geff6->Eval(i*5);
    //eff7[i] = geff7->Eval(i*5);
    //eff8[i] = geff8->Eval(i*5);
    //eff9[i] = geff9->Eval(i*5);
    eff10[i] = geff10->Eval(i*5);
    eff11[i] = geff11->Eval(i*5);
    eff12[i] = geff12->Eval(i*5);
    eff13[i] = geff13->Eval(i*5);
    //eff14[i] = geff14->Eval(i*5);
    eff15[i] = geff15->Eval(i*5);
    eff16[i] = geff16->Eval(i*5);
    eff17[i] = geff17->Eval(i*5);
	errhi1[i] = geff1->GetErrorYhigh(i);
	errlow1[i] = geff1->GetErrorYlow(i);
	//errhi2[i] = geff2->GetErrorYhigh(i);
    //errlow2[i] = geff2->GetErrorYlow(i);
    //errhi3[i] = geff3->GetErrorYhigh(i);
    //errlow3[i] = geff3->GetErrorYlow(i);
    //errhi4[i] = geff4->GetErrorYhigh(i);
    //errlow4[i] = geff4->GetErrorYlow(i);
    errhi5[i] = geff5->GetErrorYhigh(i);
    errlow5[i] = geff5->GetErrorYlow(i);
    errhi6[i] = geff6->GetErrorYhigh(i);
    errlow6[i] = geff6->GetErrorYlow(i);
    //errhi7[i] = geff7->GetErrorYhigh(i);
    //errlow7[i] = geff7->GetErrorYlow(i);
    //errhi8[i] = geff8->GetErrorYhigh(i);
    //errlow8[i] = geff8->GetErrorYlow(i);
    //errhi9[i] = geff9->GetErrorYhigh(i);
    //errlow9[i] = geff9->GetErrorYlow(i);
    errhi10[i] = geff10->GetErrorYhigh(i);
    errlow10[i] = geff10->GetErrorYlow(i);
    errhi11[i] = geff11->GetErrorYhigh(i);
    errlow11[i] = geff11->GetErrorYlow(i);
    errhi12[i] = geff12->GetErrorYhigh(i);
    errlow12[i] = geff12->GetErrorYlow(i);
    errhi13[i] = geff13->GetErrorYhigh(i);
    errlow13[i] = geff13->GetErrorYlow(i);
    //errhi14[i] = geff14->GetErrorYhigh(i);
    //errlow14[i] = geff14->GetErrorYlow(i);
    effSum[i] = (LT1*M1*eff1[i]) + (LT5*M5*eff5[i]) + (LT6*M6*eff6[i]) + (LT10*M10*eff10[i]) + (LT11*M11*eff11[i]) + (LT12*M12*eff12[i]) + (LT13*M13*eff13[i]);
    errSumhi[i] = sqrt(((errhi1[i]*M1*LT1)*(errhi1[i]*M1*LT1)) + ((errM1*eff1[i]*LT1)*(errM1*eff1[i]*LT1)) + ((errhi5[i]*M5*LT5)*(errhi5[i]*M5*LT5)) + ((errM5*eff5[i]*LT5)*(errM5*eff5[i]*LT5)) + ((errhi6[i]*M6*LT6)*(errhi6[i]*M6*LT6)) + ((errM6*eff6[i]*LT6)*(errM6*eff6[i]*LT6)) + ((errhi10[i]*M10*LT10)*(errhi10[i]*M10*LT10)) + ((errM10*eff10[i]*LT10)*(errM10*eff10[i]*LT10)) + ((errhi11[i]*M11*LT11)*(errhi11[i]*M11*LT11)) + ((errM11*eff11[i]*LT11)*(errM11*eff11[i]*LT11)) + ((errhi12[i]*M12*LT12)*(errhi12[i]*M12*LT12)) + ((errM12*eff12[i]*LT12)*(errM12*eff12[i]*LT12)) + ((errhi13[i]*M13*LT13)*(errhi13[i]*M13*LT13)) + ((errM13*eff13[i]*LT13)*(errM13*eff13[i]*LT13)));
    errSumlow[i] = sqrt(((errlow1[i]*M1*LT1)*(errlow1[i]*M1*LT1)) + ((errM1*eff1[i]*LT1)*(errM1*eff1[i]*LT1)) + ((errlow5[i]*M5*LT5)*(errlow5[i]*M5*LT5)) + ((errM5*eff5[i]*LT5)*(errM5*eff5[i]*LT5)) + ((errlow6[i]*M6*LT6)*(errlow6[i]*M6*LT6)) + ((errM6*eff6[i]*LT6)*(errM6*eff6[i]*LT6)) + ((errlow10[i]*M10*LT10)*(errlow10[i]*M10*LT10)) + ((errM10*eff10[i]*LT10)*(errM10*eff10[i]*LT10)) + ((errlow11[i]*M11*LT11)*(errlow11[i]*M11*LT11)) + ((errM11*eff11[i]*LT11)*(errM11*eff11[i]*LT11)) + ((errlow12[i]*M12*LT12)*(errlow12[i]*M12*LT12)) + ((errM12*eff12[i]*LT12)*(errM12*eff12[i]*LT12)) + ((errlow13[i]*M13*LT13)*(errlow13[i]*M13*LT13)) + ((errM13*eff13[i]*LT13)*(errM13*eff13[i]*LT13)));
	x[i] = i*5;
    xerr[i] = 0;
    }
    cout << "Loop ended" << endl;

    f1->Close();
    //f2->Close();
    //f3->Close();
    //f4->Close();
    f5->Close();
    f6->Close();
    //f7->Close();
    //f8->Close();
    //f9->Close();
    f10->Close();
    f11->Close();
    f12->Close();
    f13->Close();
    //f14->Close();
    cout << "Data files closed" << endl;

    string outFile = "~/LowE/Data/CombinedEfficiencies/ClopperErrorDS4Combined.root";
    TFile *f0 = new TFile(outFile.c_str(),"recreate");
    cout << "Creating outpout file" <<  endl;
    f0->cd();

    cout << "Creating new TGraph" << endl;
    TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, errSumlow, errSumhi);
    //TGraph *geffSum =  new TGraph(20,x,effSum);
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    geffSum->SetMarkerStyle(21);
    geffSum->SetMarkerColor(kRed);
    geffSum->SetTitle("DS4 efficiency weighted exposure");
    geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
    geffSum->GetYaxis()->SetTitle("eff wt expos (kg*d)");
    //geffSum->Draw("AP");
    geffSum->Write();
    f0->Close();
    cout << "Finished" << endl;
  }

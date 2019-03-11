  // Calculate efficiency weighted exposure 
  // Combines data from two TGraphs with efficiency and Clopper-Pearson error bars
  #include "TMath.h"
  {
	
    TFile *f1 = new TFile("ClopperErrorDS1Ch578.root");
    TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
    TFile *f2 = new TFile("ClopperErrorDS1Ch580.root");
    TGraphAsymmErrors *geff2 = (TGraphAsymmErrors*)f2->Get("Graph");
    TFile *f3 = new TFile("ClopperErrorDS1Ch578.root");
    TGraphAsymmErrors *geff4 = (TGraphAsymmErrors*)f4->Get("Graph");
    TFile *f4 = new TFile("ClopperErrorDS1Ch592.root");


    cout << "Loading data files" << endl;



    double eff1[20] = {};
    double eff2[20] = {};
    double effSum[20] = {};
    double errhi1[20] = {};
    double errlow1[20] = {};
    double errhi2[20] = {};
    double errlow2[20] = {};
    double errSumhi[20] = {};
    double errSumlow[20] = {};
    double x[20] = {};
    double xerr[20] = {};
    cout << "Initializing arrays" << endl;

    double LT = 58.7676;
    double M1 = 0.968;
    double errM1 = 0.013;
    double M2 = 0.811;
    double errM2 = 0.012;
    //double LT = 1.0;
    //double M1 = 1.0;
    //double errM1 = 1.0;
    //double M2 = 1.0;
    //double errM2 = 1.0;


    cout << "Beginning loop" << endl;
    for(int i = 0; i < 20; i++)
      {
	eff1[i] = geff1->Eval(i*5);
	eff2[i] = geff2->Eval(i*5);
	errhi1[i] = geff1->GetErrorYhigh(i);
	errlow1[i] = geff1->GetErrorYlow(i);
	errhi2[i] = geff2->GetErrorYhigh(i);
        errlow2[i] = geff2->GetErrorYlow(i);
	effSum[i] = (LT*M1*eff1[i]) + (LT*M2*eff2[i]);
	errSumhi[i] = sqrt(((errhi1[i]*M1*LT)*(errhi1[i]*M1*LT)) + ((errM1*eff1[i]*LT)*(errM1*eff1[i]*LT)) + ((errhi2[i]*M2*LT)*(errhi2[i]*M2*LT)) + ((errM2*eff2[i]*LT)*(errM2*eff2[i]*LT)));
        errSumlow[i] = sqrt(((errlow1[i]*M1*LT)*(errlow1[i]*M1*LT)) + ((errM1*eff1[i]*LT)*(errM1*eff1[i]*LT)) + ((errlow2[i]*M2*LT)*(errlow2[i]*M2*LT)) + ((errM2*eff2[i]*LT)*(errM2*eff2[i]*LT)));
	//errSumhi[i] = sqrt(((errhi1[i]*M1*LT)^2) + ((errhi2[i]*M2*LT)^2));
	//errSumlow[i] = sqrt(((errlow1[i]*M1*LT)*(errlow1[i]*M1*LT)) + ((errlow2[i]*M2*LT)*(errlow2[i]*M2*LT)));
	//errSumhi[i] = errhi1[i] + errhi2[i];
	//errSumlow[i] = errlow1[i] + errlow2[i];
	x[i] = i*5;
        xerr[i] = 0;
      }
    cout << "Loop ended" << endl;

    f1->Close();
    f2->Close();
    cout << "Data files closed" << endl;

    //string outFile = "ClopperErrorDS1Combined.root";
    //TFile *f3 = new TFile(outFile.c_str(),"recreate");
    //cout << "Creating outpout file" <<  endl;
    //f3->cd();

    cout << "Creating new TGraph" << endl;
    TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, errSumlow, errSumhi);
    //TGraph *geffSum =  new TGraph(20,x,effSum);
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    geffSum->SetMarkerStyle(21);
    geffSum->SetMarkerColor(kRed);
    geffSum->SetTitle("DS1 ch 578+580 efficiency weighted exposure");
    geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
    geffSum->GetYaxis()->SetTitle("eff wt expos (1/kg*d)");
    geffSum->Draw("AP");
    //geffSum->Write();
    //f3->Close();
    cout << "Finished" << endl;
  }

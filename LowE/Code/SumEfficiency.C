  // Calculates the combined efficiency weighted by exposure from two DS1 detectors
  // The individual detector efficiencies have Clopper-Pearson error bars
  // Uses propagation or error to find error bars for combined efficiency
  {
	//Load individual detector efficiencies
    TFile *f1 = new TFile("ClopperErrorDS1Ch578.root");
    TGraphAsymmErrors *geff1 = (TGraphAsymmErrors*)f1->Get("Graph");
    TFile *f2 = new TFile("ClopperErrorDS1Ch580.root");
    TGraphAsymmErrors *geff2 = (TGraphAsymmErrors*)f2->Get("Graph");
    cout << "Loading data files" << endl;

    // Initialize arrays
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
    
    // Live time and active masses for the two detectors
    double LT = 58.7676;
    double M1 = 0.968;
    double errM1 = 0.013;
    double M2 = 0.811;
    double errM2 = 0.012;

    // Loop through individual detector efficiencies in 5keV steps, weight them by exposure,
    // and calculate the combined exposure weighted efficiency
    cout << "Beginning loop" << endl;
    for(int i = 0; i < 20; i++)
      {
	eff1[i] = geff1->Eval(i*5);
	eff2[i] = geff2->Eval(i*5);
	errhi1[i] = geff1->GetErrorYhigh(i*5);
	errlow1[i] = geff1->GetErrorYlow(i*5);
	errhi2[i] = geff2->GetErrorYhigh(i*5);
        errlow2[i] = geff2->GetErrorYlow(i*5);
	effSum[i] = (LT*M1*eff1[i]) + (LT*M2*eff2[i]);
    // Calculate error bars using propagation of erros, ignoring uncertainty on exposure for simplicity
	errSumhi[i] = sqrt((((errhi1[i]-eff1[i])*M1*LT)*((errhi1[i]-eff1[i])*M1*LT)) + (((errhi2[i]-eff2[i])*M2*LT)*((errhi2[i]-eff2[i])*M2*LT)));
	errSumlow[i] = sqrt((((eff1[i]-errlow1[i])*M1*LT)*((eff1[i]-errlow1[i])*M1*LT)) + (((eff2[i]-errlow2[i])*M2*LT)*((eff2[i]-errlow2[i])*M2*LT)));
	x[i] = i*5;
    xerr[i] = 0;
      }
    cout << "Loop ended" << endl;
    f1->Close();
    f2->Close();
    cout << "Data files closed" << endl;

    // Create output file to store combined efficiency
    string outFile = "ClopperErrorDS1Combined.root";
    TFile *f3 = new TFile(outFile.c_str(),"recreate");
    cout << "Creating outpout file" <<  endl;
    f3->cd();

    // Graph the combined uncertainty
    cout << "Creating new TGraph" << endl;
    TGraphAsymmErrors *geffSum = new TGraphAsymmErrors(20, x, effSum, xerr, xerr, errSumlow, errSumhi);
    ////TGraph *geffSum =  new TGraph(20,x,effSum);
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    geffSum->SetMarkerStyle(21);
    geffSum->SetMarkerColor(kRed);
    geffSum->SetTitle("DS1 ch 578+580 efficiency weighted exposure");
    geffSum->GetXaxis()->SetTitle("trapENFCal (keV)");
    geffSum->GetYaxis()->SetTitle("eff wt expos (1/kg*d)");
    ////geffSum->Draw("AP");
    geffSum->Write();
    f3->Close();
    cout << "Finished" << endl;
  }

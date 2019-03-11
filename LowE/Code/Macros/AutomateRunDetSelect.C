//
//  AutomateRunDetSelect.C
//  
//
//  Created by Jamin on 2/08/19.
//
//  Automates run and detector selection by picking outliers using z-scores or some other method
//  and then plots rejected runs and dets

{
    // Load input files
    string inFile1 = "/global/homes/j/jrager/LowE/AnalysisPlots/most_latest/DetSelection/DetSelectDS6_5kThresh_correctedCuts.root";
    TFile *f1 = new TFile(inFile1.c_str());
    //string inFile2 = "~/LowE/Data/DS5aDetSelect_5kThresh_CleanRuns.root";
    //TFile *f2 = new TFile(inFile2.c_str());

    // Load TH2's
    TH2F *h1 = (TH2F*)f1->Get("detVrun");
    //TH2F *h2 = (TH2F*)f2->Get("detVrun");

    // Initialize vectors
    std::vector<double> ctsTally;
    std::vector<int> v_run;
    std::vector<int> v_channel;
    
    for(int i=1; i<=h1->GetSize(); i++) {
        Int_t cts = h1->GetBinContent(i);
        if (cts != 0) {
            ctsTally.push_back(cts);
        }
    }
    
    double sum = std::accumulate(ctsTally.begin(), ctsTally.end(), 0.0);
    double mean = sum / ctsTally.size();
    double sq_sum = std::inner_product(ctsTally.begin(), ctsTally.end(), ctsTally.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / ctsTally.size() - mean * mean);
    //cout << "sum " << sum << " mean " << mean << " sq_sum " << sq_sum << " stdev " << stdev << endl;

    for(int i=1; i<=h1->GetSize(); i++) {
        Int_t cts = h1->GetBinContent(i);
        if (cts != 0) {
            double z = (cts - mean)/stdev;
            //if (z>=2.0)
	    if (cts >= 10*mean)  
            {
                int binx, biny, binz;
	        h1->GetBinXYZ(i,binx,biny,binz);
		//int run = binx + 8722 - 1;  //DS1
		//int run = binx + 14508 - 1;  //DS2
		//int run = binx + 16031 - 1;  //DS3
		//int run = binx + 60000550 - 1;  //DS4
		//int run = binx + 18623 - 1;  //DS5a
		//int run = binx + 22393 - 1;  //DS5b
		//int run = binx + 23975 - 1;  //DS5c
		int run = binx + 25704 - 1;  //DS6
		int channel = biny - 1;
		v_run.push_back(run);
		v_channel.push_back(channel);
            }
        }
    }   

    TGraph *g = new TGraph(v_run.size(), &v_run[0], &v_channel[0]);
    g->SetMarkerStyle(6);
    g->SetMarkerColor(kRed);
    g->SetTitle("DS6 Bad Runs/Dets: cts >= 10*mean");
    g->GetXaxis()->SetTitle("run number");
    g->GetYaxis()->SetTitle("detector channel");
    g->Draw("AP");

    TLine *line1 = new TLine(19707, 1334, 19722, 1334);
    line1->SetLineColor(kBlue);
    line1->SetLineWidth(4);
    line1->Draw();
    TLine *line2 = new TLine(19707, 1330, 19722, 1330);
    line2->SetLineColor(kBlue);
    line2->SetLineWidth(4);
    line2->Draw();
    TLine *line3 = new TLine(19707, 1330, 19707, 1334);
    line3->SetLineColor(kBlue);
    line3->SetLineWidth(4);
    line3->Draw();
    TLine *line4 = new TLine(19722, 1330, 19722, 1334);
    line4->SetLineColor(kBlue);
    line4->SetLineWidth(4);
    line4->Draw();

    TLine *line5 = new TLine(20218, 1334, 21453, 1334);
    line5->SetLineColor(kBlue);
    line5->SetLineWidth(4);
    line5->Draw();
    TLine *line6 = new TLine(20218, 1170, 21453, 1170);
    line6->SetLineColor(kBlue);
    line6->SetLineWidth(4);
    line6->Draw();
    TLine *line7 = new TLine(20218, 1170, 20218, 1334);
    line7->SetLineColor(kBlue);
    line7->SetLineWidth(4);
    line7->Draw();
    TLine *line8 = new TLine(21453, 1170, 21453, 1334);
    line8->SetLineColor(kBlue);
    line8->SetLineWidth(4);
    line8->Draw();

    TLine *line9 = new TLine(20218, 693, 21453, 693);
    line9->SetLineColor(kBlue);
    line9->SetLineWidth(3);
    line9->Draw();
    TLine *line10 = new TLine(20218, 583, 21453, 583);
    line10->SetLineColor(kBlue);
    line10->SetLineWidth(3);
    line10->Draw();
    TLine *line11 = new TLine(20218, 583, 20218, 693);
    line11->SetLineColor(kBlue);
    line11->SetLineWidth(3);
    line11->Draw();
    TLine *line12 = new TLine(21453, 583, 21453, 693);
    line12->SetLineColor(kBlue);
    line12->SetLineWidth(3);
    line12->Draw();

    TLine *line13 = new TLine(21568, 693, 21612, 693);
    line13->SetLineColor(kBlue);
    line13->SetLineWidth(3);
    line13->Draw();
    TLine *line14 = new TLine(21568, 691, 21612, 691);
    line14->SetLineColor(kBlue);
    line14->SetLineWidth(3);
    line14->Draw();
    TLine *line15 = new TLine(21568, 691, 21568, 693);
    line15->SetLineColor(kBlue);
    line15->SetLineWidth(3);
    line15->Draw();
    TLine *line16 = new TLine(21612, 691, 21612, 693);
    line16->SetLineColor(kBlue);
    line16->SetLineWidth(3);
    line16->Draw();

    TLine *line17 = new TLine(21763, 693, 21781, 693);
    line17->SetLineColor(kBlue);
    line17->SetLineWidth(3);
    line17->Draw();
    TLine *line18 = new TLine(21763, 691, 21781, 691);
    line18->SetLineColor(kBlue);
    line18->SetLineWidth(3);
    line18->Draw();
    TLine *line19 = new TLine(21763, 691, 21763, 693);
    line19->SetLineColor(kBlue);
    line19->SetLineWidth(3);
    line19->Draw();
    TLine *line20 = new TLine(21781, 691, 21781, 693);
    line20->SetLineColor(kBlue);
    line20->SetLineWidth(3);
    line20->Draw();
}

#include "TMath.h"
{
    double bin[20] = {1086444, 1086445, 1086446, 1086449, 1086450, 1086452, 1086453, 1086457, 1086460, 1086462, 1086468, 1086476, 1086485, 1086491, 1086493};
    double cts[20] = {1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1, 66, 141, 573, 3192};
    
    cout << "Creating new TGraph" << endl;
    TGraph *g = new TGraph(20, bin, cts);
    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    
    g->SetMarkerStyle(21);
    g->SetMarkerColor(kRed);
    g->SetTitle("DS5b: Transient Noise Flagging");
    g->GetXaxis()->SetTitle("bin number");
    g->GetYaxis()->SetTitle("counts");
    g->Draw("AP");
    cout << "Finished" << endl;
}


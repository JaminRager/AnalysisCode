#include <string>

{
  std::string dataPath("/global/u1/j/jrager/ZScan/");

  std::string dataFile;
    
  UInt_t runNumb;
  for (runNumb = 45; runNumb < 60; runNumb+=5) {
    
    char buffer[10];
    int n;
    //n = sprintf(buffer,"%d",runNumb);
    n = itoa(runNumb,buffer,10);
    dataFile = dataPath + std::string("pw350064") + buffer + "rt10.root";
    std::cout<<"Opening file"<<dataFile<<std::endl;
    TFile f2(dataFile.c_str());
    //TFile *p2 = &f2;
        
    //gROOT->ForceStyle();
    //gStyle->SetOptStat(0);
    //gStyle->SetOptTitle(0);
    //TH1D *PWidth = (TH1D*)p2->Get("PWidth");
    //TH1 *rebin = PWidth->Rebin(4,"rebin");
    //rebin->Fit("gaus","N");
        
  }
    
  //new TBrowser();
    
}

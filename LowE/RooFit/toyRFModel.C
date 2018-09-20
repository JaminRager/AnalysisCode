{
  gSystem->Load("libRooFit");
  using namespace RooFit;

  //Plotting two Gaussians on the same plot
  //RooRealVar x("x","x",-10,10);
  //RooRealVar mean("mean","Mean of Gaussian",0,-10,10);
  //RooRealVar sigma("sigma","Width of Gaussian",3,-10,10);
  //RooGaussian gauss("gauss","gauss(x,mean,sigma)",x,mean,sigma);
  //RooPlot* xframe = x.frame();
  //gauss.plotOn(xframe);
  //sigma = 2;
  //gauss.plotOn(xframe,LineColor(kRed));
  //xframe->Draw();

  //For fitting data
  //RooRealVar x("x","x",0,3000);
  //RooRealVar mean("mean","Mean of Gaussian",46,47.5);
  //RooRealVar sigma("sigma","Width of Gaussian",0,5);
  //RooGaussian gauss("gauss","gauss(x,mean,sigma)",x,mean,sigma);

  //Import histogram from binned data file and fit a spectral peak to a Gaussian.
  //TFile *file = new TFile("CombinedDS0.root");
  //TH1* hh = (TH1*) gDirectory->Get("natLE");
  //hh->GetXaxis()->SetLimits(5,30);
  //RooRealVar x("x","x",5,30);
  //RooDataHist data("data","dataset with enrHE",x,hh); 
  //RooRealVar mean("mean","Mean of Gaussian",10.3,5,15);
  //RooRealVar sigma("sigma","Width of Gaussian",1,0,20);
  //RooGaussian gauss("gauss","gauss(x,mean,sigma)",x,mean,sigma);
  //RooPlot* xframe = x.frame();
  //gauss.fitTo(data, Range(9.8,10.7));
  //data.plotOn(xframe);
  //mean.Print();
  //sigma.Print();
  //gauss.plotOn(xframe);
  //xframe->Draw();

  //Import root file containing tree and plot unbinned data
  //TFile *file = new TFile("skimDS6_0_low.root");
  //TTree* skimTree = (TTree*) gDirectory->Get("skimTree");
  //RooRealVar trapENFCal("trapENFCal","trapENFCal",0,100);
  //RooDataSet data("data","dataset with trapENFCal",skimTree,trapENFCal);
  //RooPlot* xframe = trapENFCal.frame();
  //data.plotOn(xframe,Binning(100));
  //xframe->Draw()

  //For fitting data
  //RooDataHist data("data","dataset with x",x,hh);
  //RooPlot* xframe = x.frame();
  //data.plotOn(xframe);
  //gauss.fitTo(data, Range(46,47.5));
  //mean.Print();
  //sigma.Print();
  //gauss.plotOn(xframe);
  //xframe->Draw()

  //Sampling data from my model
  //RooRealVar x("x","x",46,47.5);
  //RooRealVar mean("mean","Mean of Gaussian",46.6,46,47.5);
  //RooRealVar sigma("sigma","Width of Gaussian",0.3,0,5);
  //RooGaussian gauss("gauss","gauss(x,mean,sigma)",x,mean,sigma);
  //RooDataSet* data = gauss.generate(x,2000);
  //gauss.fitTo(*data);
  //RooPlot* xframe = x.frame(); 
  //data->plotOn(xframe); 
  //gauss.plotOn(xframe); 
  //xframe->Draw();
  //mean.Print();
  //sigma.Print();
  
  //delete data;

  ///Build composite model with fractions
  //RooRealVar x("x","x",-10,10);
  //RooRealVar mean("mean","mean",0,-10,10);
  //RooRealVar sigma("sigma","sigma",2,0.,10.);
  //RooGaussian sig("sig","signal p.d.f.",x,mean,sigma);
  //RooRealVar c0("c0","coefficient #0", 1.0,-1.,1.);
  //RooRealVar c1("c1","coefficient #1", 0.1,-1.,1.);
  //RooRealVar c2("c2","coefficient #2",-0.1,-1.,1.);
  //RooChebychev bkg("bkg","background p.d.f.",x,RooArgList(c0,c1,c2));
  //RooRealVar fsig("fsig","signal fraction",0.5,0.,1.);
  ///model(x) = fsig*sig(x) + (1-fsig)*bkg(x)
  //RooAddPdf model("model","model",RooArgList(sig,bkg),fsig);
  ///Plot composite model
  //RooPlot* frame = x.frame();
  //model.plotOn(frame);
  //model.plotOn(frame, Components(bkg),LineStyle(kDashed));
  //frame->Draw();

  ///Build composite model recursively
  //RooRealVar x("x","x",-10,10);
  //RooRealVar mean("mean","mean",0,-10,10);
  //RooRealVar sigma("sigma","sigma",2,0.,10.);
  //RooGaussian sig("sig","signal p.d.f.",x,mean,sigma);
  //RooRealVar c0("c0","coefficient #0", 1.0,-1.,1.);
  //RooRealVar c1("c1","coefficient #1", 0.1,-1.,1.);
  //RooRealVar c2("c2","coefficient #2",-0.1,-1.,1.);
  //RooChebychev bkg("bkg","background p.d.f.",x,RooArgList(c0,c1,c2));
  //RooRealVar fsig("fsig","signal fraction",0.5,0.,1.);
  //RooRealVar mean_bkg("mean_bkg","mean",5,-10,10);
  //RooRealVar sigma_bkg("sigma_bkg","sigma",1,0.,10.);
  //RooGaussian bkg_peak("bkg_peak","peaking bkg p.d.f.",x,mean_bkg,sigma_bkg);
  ///First add sig and peak together with fraction fpeak
  //RooRealVar fpeak("fpeak","peaking background fraction",0.1,0.,1.); 
  //RooAddPdf sigpeak("sigpeak","sig+peak",RooArgList(bkg_peak,sig),fpeak);
  ///Next add (sig+peak) to bkg with fraction fpeak
  //RooRealVar fbkg("fbkg","background fraction",0.5,0.,1.);
  //RooAddPdf model("model","bkg+(sig+peak)",RooArgList(bkg,sigpeak),fbkg);
  ///Plot composite model
  //RooPlot* frame = x.frame();
  //model.plotOn(frame);
  //model.plotOn(frame, Components(bkg),LineStyle(kDashed));
  //frame->Draw();

  ///Import histogram from binned data file and fit to a composite model built recursively
  ///"High Energy" model: fiting the 47keV peak in the 20-100keV spectrum
  ///First import data
  //TFile *file = new TFile("CombinedDS6_Newest.root");
  //TH1* hh = (TH1*) gDirectory->Get("natHE");
  //hh->GetXaxis()->SetLimits(0,3000);  
  //RooRealVar x("x","x",0,12000);
  //RooDataHist data("data","dataset with enrHE",x,hh);
  ///Now build model
  //RooRealVar mean("mean","mean",47.,45.,49.);
  //RooRealVar sigma("sigma","sigma",0.2,0.,1.);
  //RooGaussian bkg_peak("bkg_peak","bkg peak p.d.f.",x,mean,sigma);
  //RooRealVar c0("c0","coefficient #0", 0.,0.,1.);
  //RooPolynomial flat("flat","flat bkg",x,RooArgList(c0));
  //RooRealVar fpeak("fpeak","peaking background fraction",0.6,0.,1.);
  //RooAddPdf model("model","bkg_peak+flat",RooArgList(bkg_peak,flat),fpeak);
  ///Plot model and data
  //RooPlot* xframe = x.frame();
  ////RooBinning tbins(40,50);
  ////tbins.addUniform(40,40,50);
  //model.fitTo(data,Range(20.,100.));
  ////data.plotOn(xframe,Binning(tbins));
  //data.plotOn(xframe);
  //model.plotOn(xframe);
  //xframe->Draw();

  ///High Energy model done as extended likelihood - USE THIS!
  ///First import data
  //TFile *file = new TFile("CombinedDS6_NewestRebin.root");
  //TH1* hh = (TH1*) gDirectory->Get("natHE");
  //hh->GetXaxis()->SetLimits(0,3000);
  //RooRealVar x("x","x",0,12000);
  //RooDataHist data("data","dataset with enrHE",x,hh);
  ///Now build model
  //RooRealVar mean("mean","mean",47.,45.,49.);
  //RooRealVar sigma("sigma","sigma",0.05,0.,1.);
  //RooGaussian bkg_peak("bkg_peak","bkg peak p.d.f.",x,mean,sigma);
  //RooRealVar npeak("npeak","npeak",15,0,100.);
  //RooExtendPdf epeak("epeak","epeak",bkg_peak,npeak);
  //RooRealVar c0("c0","coefficient #0", 0.,0.,1.);
  //RooChebychev flat("flat","flat bkg",x,RooArgList(c0));
  //RooRealVar nflat("nflat","nflat",500,0,1000.);
  //RooExtendPdf eflat("eflat","eflat",flat,nflat);
  //RooAddPdf model("model","model",RooArgList(epeak,eflat));
  //RooPlot* xframe = x.frame();
  //model.fitTo(data,Range(20.,100.));
  //data.plotOn(xframe);
  //model.plotOn(xframe);
  //xframe->Draw();


  ///Import histogram from binned data file and fit to a composite model built recursively
  ///Fiting the tritium spectrum and cosmogenic peak(s) in the < 20keV spectrum
  ///First import data
  //TFile *file = new TFile("CombinedDS6_Newest.root");
  //TH1* hh = (TH1*) gDirectory->Get("natHE");
  //hh->GetXaxis()->SetLimits(0,3000);
  //RooRealVar x("x","x",0,12000);
  ////RooRealVar x("x","x",9,20);
  //RooDataHist data("data","dataset with enrHE",x,hh);
  ///Now build model
  //RooRealVar mean1("mean1","cosmogenic peak 1 mean",9.,8.,10.);
  //RooRealVar sigma1("sigma1","cosmogenic peak 1 sigma",0.1,0.,1.);
  //RooGaussian peak1("peak1","cosmogenic peak 1 p.d.f.",x,mean1,sigma1);
  //RooRealVar mean2("mean2","cosmogenic peak 2 mean",10.5,10.,11.);
  //RooRealVar sigma2("sigma2","cosmogenic peak 2 sigma",0.1,0.,1.);
  //RooGaussian peak2("peak2","cosmogenic peak 2 p.d.f.",x,mean2,sigma2);
  //RooRealVar lambda("lambda", "decay const", -1., -5., 0.);
  //RooExponential tritium("tritium", "exponential PDF", x, lambda);
  ////RooRealVar c0("c0","coefficient #0", 0.,0.,1.);
  ////RooPolynomial flat("flat","flat bkg",x,RooArgList(c0));
  //RooRealVar fpeak1("fpeak1","peaking background fraction",0.5,0.,1.);
  //RooRealVar fpeak2("fpeak2","tritium background fraction",0.5,0.,1.);
  ////RooRealVar fflat("fflat","flat background",0.1,0.,1.);
  //RooAddPdf step1("step1","peak1+tritium",RooArgList(peak1,tritium),fpeak1);
  //RooAddPdf step2("step2","peak2+step1",RooArgList(peak2,step1),fpeak2);
  ////RooAddPdf model("model","flat+step2",RooArgList(flat,step2),fflat);
  ///Plot model and data
  //RooPlot* xframe = x.frame();
  ////RooBinning tbins(40,50);
  ////tbins.addUniform(40,40,50);
  //step2.fitTo(data,Range(7.9,20.));
  ////data.plotOn(xframe,Binning(tbins));
  //data.plotOn(xframe);
  //step2.plotOn(xframe);
  //xframe->Draw();

  ///Low energy model done as extended likelihood - USE THIS!
  ///First import data
  TFile *file = new TFile("CombinedDS6_Newest.root");
  TH1* hh = (TH1*) gDirectory->Get("natHE");
  hh->GetXaxis()->SetLimits(0,3000);
  RooRealVar x("x","x",0,12000);
  RooDataHist data("data","dataset with enrHE",x,hh);
  ///Now build model
  RooRealVar mean1("mean1","cosmogenic peak 1 mean",9.,8.,10.);
  RooRealVar sigma1("sigma1","cosmogenic peak 1 sigma",0.05,0.,1.);
  RooGaussian peak1("peak1","cosmogenic peak 1 p.d.f.",x,mean1,sigma1);
  RooRealVar npeak1("npeak1","npeak1",1000,0,10000.);
  RooExtendPdf epeak1("epeak1","epeak1",peak1,npeak1);
  RooRealVar mean2("mean2","cosmogenic peak 2 mean",10.5,10.,11.);
  RooRealVar sigma2("sigma2","cosmogenic peak 2 sigma",0.05,0.,1.);
  RooGaussian peak2("peak2","cosmogenic peak 2 p.d.f.",x,mean2,sigma2);
  RooRealVar npeak2("npeak2","npeak2",1000,0,10000.);
  RooExtendPdf epeak2("epeak2","epeak2",peak2,npeak2);
  RooRealVar lambda("lambda", "decay const", -1., -5., 0.);
  RooExponential tritium("tritium", "exponential PDF", x, lambda);
  RooRealVar ntritium("ntritium","ntritium",2000,0,100000.);
  RooExtendPdf etritium("etritium","etritium",tritium,ntritium);
  RooAddPdf model("model","model",RooArgList(epeak2,etritium));
  RooPlot* xframe = x.frame();
  model.fitTo(data,Range(9.9,20.));
  data.plotOn(xframe);
  model.plotOn(xframe);
  xframe->Draw();

}

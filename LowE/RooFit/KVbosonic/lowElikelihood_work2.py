#! /usr/bin/python

###############################
# lowElikelihood.py
###############################
# ----DESCRIPTION---
# This script uses the the RooFit frameworking
# to perform a profile likelihood analysis on the
# low energy data from dataset 0.
# The goal is to set upper limits on bosonic dark
# matter interactions in the detector
#################################
# Written by Kris Vorren, email: krisvorren@unc.edu
#
# ---Version History---
# 4/16/2016: Created.
# 6/13/2016: Rewrite to be like plan email
# 6/27/2016: Don't use the x variable anymore (only uncertainty in E0)
# 7/19/2016: A little cleanup, take care of the T/E eff
# 1/4/2017: Modified a bit for upload to GAT
##################################

import sys, os, re, glob, ROOT, array, numpy
from ROOT import RooFit as RF
from ROOT import gROOT
from ROOT import gPad
from ROOT import kGreen
from ROOT import kRed
from ROOT import kDotted

#ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.WARNING)
#-------INITIALIZATION---------
ROOT.gROOT.Reset()
#ROOT.gApplication.ExecuteFile("/project/projectdirs/majorana/software/sl64/mjsw/mjsw201807Prod/MGDO/Root/LoadMGDOClasses.C" %os.environ['MGDODIR'])
#from ROOT import CLHEP

#MJD style: (Link to your own)
#ROOT.gApplication.ExecuteFile("/Users/krvorren/Project/M1background/scripts/MJDTalkPlotStyle.C")
#ROOT.gROOT.ForceStyle()

vectorDM = False #Probably deprecated

def WaitForReturn():
    x = raw_input("Press RETURN or 'q' to quit: ")
    if (x == "q"):
        sys.exit(0)

def AxioElectric(En): #This function computes the axio-electric cross section
    ## Makes sure energy parameter is in range?  Not sure what this does.
    ## "if En &lt; 1" -> "if En < 1"
    ## gt means >
    ## stupid python notation
    ## I'll want to go through and remove every conditional where it checks if E<20 b.c. I want the same analysis over whole range
    if En < 1:
        print "TOO SMALL"
        return 0
    if En > 100:
        print "TOO BIG"
        return 0
    ## Photoelectric effect energy:cross section.  A python dictionary
    peDict = {
        2.195:2155.306, 2.239:2047.98, 2.283:1955.055, 2.328:1857.7, 2.374:1765.193, 2.421:1685.1, 2.469:1601.188, 2.517:1521.455, 2.567:1452.42,
        2.618:1380.095, 2.669:1311.371, 2.722:1251.869, 2.776:1189.531, 2.831:1130.296, 2.886:1079.01, 2.943:1025.28, 3.001:974.224, 3.061:921.423,
        3.121:879.614, 3.183:831.941, 3.246:786.851, 3.31:747.668, 3.375:710.437, 3.442:671.933, 3.51:641.444, 3.579:606.679, 3.649:576.469, 3.722:547.763,
        3.795:518.075, 3.87:489.996, 3.946:467.763, 4.024:442.411, 4.104:420.38, 4.185:399.447, 4.267:377.797, 4.351:360.655, 4.437:342.696, 4.525:325.631,
        4.614:307.982, 4.705:294.008, 4.798:278.073, 4.893:264.226, 4.99:251.069, 5.088:237.461, 5.188:226.687, 5.291:214.4, 5.395:202.78, 5.502:192.683,
        5.61:183.088, 5.721:173.165, 5.834:163.779, 5.949:156.348, 6.067:147.874, 6.186:139.86, 6.309:132.279, 6.433:125.11, 6.56:118.329, 6.69:111.916,
        6.822:105.85, 6.956:100.579, 7.094:95.571, 7.234:90.391, 7.376:85.492, 7.522:80.859, 7.671:76.476, 7.822:72.331, 7.976:68.411, 8.134:64.703,
        8.294:61.196, 8.458:57.88, 8.625:54.743, 8.795:51.776, 8.969:49.426, 9.146:46.748, 9.327:44.214, 9.511:41.818, 9.698:39.551, 9.89:37.408,
        10.085:35.38, 10.284:33.618, 10.487:31.944, 10.694:30.495, 10.947:28.879, 11.021:28.152, 11.17:192.719, 11.34:190.017, 11.564:181.395,
        11.792:171.564, 12.025:163.021, 12.262:154.903, 12.504:146.507, 12.751:139.86, 13.003:132.279, 13.26:125.692, 13.521:119.433,
        13.788:112.96, 14.06:107.835, 14.338:101.99, 14.621:96.912, 14.91:92.086, 15.204:87.095, 15.504:83.143, 15.81:78.637, 16.122:74.721, 16.44:71,
        16.765:67.152, 17.096:64.105, 17.433:60.631, 17.777:57.611, 18.128:54.743, 18.486:51.776, 18.851:49.426, 19.223:46.748, 19.603:44.42, 19.99:42.208,
        20.384:39.92, 20.787:37.757, 21.197:35.71, 21.615:34.09, 22.042:32.242, 22.477:30.495, 22.921:28.842, 23.373:27.279, 23.835:25.8,
        24.305:24.516, 24.785:23.295, 25.274:22.032, 25.773:20.838, 26.282:19.709, 26.801:18.641, 27.33:17.63, 27.869:16.675, 28.419:15.918,
        28.98:15.055, 29.552:14.239, 30.136:13.468, 30.731:12.738, 31.337:12.047, 31.956:11.394, 32.587:10.777, 33.23:10.193, 33.886:9.64,
        34.555:9.118, 35.237:8.624, 35.932:8.156, 36.642:7.714, 37.365:7.296, 38.103:6.901, 38.855:6.527, 39.622:6.173, 40.404:5.838,
        41.201:5.522, 42.015:5.223, 42.844:4.94, 43.69:4.672, 44.552:4.419, 45.432:4.141, 46.328:3.916, 47.243:3.704,
        48.176:3.503, 49.127:3.313, 50.096:3.134, 51.085:2.95, 52.094:2.777, 53.122:2.627, 54.171:2.461, 55.24:2.328,
        56.33:2.192, 57.442:2.063, 58.576:1.951, 59.732:1.829, 60.912:1.73, 62.114:1.636, 63.34:1.547, 64.59:1.456,
        65.865:1.371, 67.165:1.297, 68.491:1.227, 69.843:1.16, 71.222:1.097, 72.628:1.038, 74.062:0.982, 75.524:0.92,
        77.014:0.87, 78.535:0.823, 80.085:0.778, 81.666:0.733, 83.278:0.69, 84.922:0.652, 86.598:0.611, 88.307:0.575, 90.051:0.542, 91.828:0.508,
        93.641:0.48, 95.489:0.452, 97.374:0.425, 100.0:0.383
    }
    ## photoelectric energy
    peInput = [
        2.195, 2.239, 2.283, 2.328, 2.374, 2.421, 2.469, 2.517, 2.567, 2.618, 2.669, 2.722, 2.776, 2.831, 2.886, 2.943, 3.001, 3.061, 3.121, 3.183, 3.246, 3.31, 3.375, 3.442,
        3.51, 3.579, 3.649, 3.722, 3.795, 3.87, 3.946, 4.024, 4.104, 4.185, 4.267, 4.351, 4.437, 4.525, 4.614, 4.705, 4.798, 4.893, 4.99, 5.088, 5.188, 5.291, 5.395, 5.502,
        5.61, 5.721, 5.834, 5.949, 6.067, 6.186, 6.309, 6.433, 6.56, 6.69, 6.822, 6.956, 7.094, 7.234, 7.376, 7.522, 7.671, 7.822, 7.976, 8.134, 8.294, 8.458, 8.625, 8.795,
        8.969, 9.146, 9.327, 9.511, 9.698, 9.89, 10.085, 10.284, 10.487, 10.694, 10.947, 11.021, 11.17, 11.34, 11.564, 11.792, 12.025, 12.262, 12.504, 12.751, 13.003,
        13.26, 13.521, 13.788, 14.06, 14.338, 14.621, 14.91, 15.204, 15.504, 15.81, 16.122, 16.44, 16.765, 17.096, 17.433, 17.777, 18.128, 18.486, 18.851, 19.223,
        19.603, 19.99, 20.384, 20.787, 21.197, 21.615, 22.042, 22.477, 22.921, 23.373, 23.835, 24.305, 24.785, 25.274, 25.773, 26.282, 26.801, 27.33, 27.869, 28.419,
        28.98, 29.552, 30.136, 30.731, 31.337, 31.956, 32.587, 33.23, 33.886, 34.555, 35.237, 35.932, 36.642, 37.365, 38.103, 38.855, 39.622, 40.404, 41.201,
        42.015, 42.844, 43.69, 44.552, 45.432, 46.328, 47.243, 48.176, 49.127, 50.096, 51.085, 52.094, 53.122, 54.171, 55.24, 56.33, 57.442, 58.576, 59.732,
        60.912, 62.114, 63.34, 64.59, 65.865, 67.165, 68.491, 69.843, 71.222, 72.628, 74.062, 75.524, 77.014, 78.535, 80.085, 81.666, 83.278, 84.922,
        86.598, 88.307, 90.051, 91.828, 93.641, 95.489, 97.374, 100.0
    ]
    ## if intput energy peVal is one of the values in array peInput then return corresponding cross section value from the dictionary.
    ## otherwise it linearly interpolates between values
    peVal = 0
    if(En in peInput):
        peVal = peDict[En]
    else:
        inputPos = 0
        while En > peInput[inputPos]:
            inputPos+=1
        m = (peDict[peInput[inputPos]] - peDict[peInput[inputPos-1]])/(peInput[inputPos] - peInput[inputPos-1])
        b = -1*m*peInput[inputPos-1] + peDict[peInput[inputPos-1]]
        peVal = m*En+b
    #print "peVal = " + str(peVal)
    ## not sure what this stuff does, check the physics formulas in Kris's dissertation, chapter 6
    if vectorDM:
        return peVal #*(72.63 /75.23)#/ 72.64 #Formulas in papers are structured differently
    else:
        return peVal/.001*3*En*En/(16*numpy.pi*1.0/137*511*511)*(1-0.01/3) * 1000 * (72.63 / 75.23)

def SigErrProp(en, func, mat): #To estimate the uncertainty in the sigma values (**DEPRECATED**)
    errProp = 0
    partialList = [func.GetParameter(2)*en*en, func.GetParameter(1)*en, func.GetParameter(0)]
    for iterI in xrange(3):
        for iterJ in xrange(3):
            errProp += partialList[iterI]*partialList[iterJ]*mat(iterI, iterJ)
            #print mat(iterI, iterJ)

    errProp = 1./(func(en)*func(en))*errProp
    return errProp

#-----Channel initialization-----
channelDict = {692.0:"P1D1", 690.0:"P1D2", 688.0:"P1D3", 640.0:"P1D4",
               584.0:"P2D1", 674.0:"P2D2", 576.0:"P2D3", 680.0:"P2D4",
               676.0:"P3D1", 616.0:"P3D2", 614.0:"P3D3", 610.0:"P3D4",
               608.0:"P4D1", 598.0:"P4D2", 600.0:"P4D3", 594.0:"P4D4", 592.0:"P4D5",
               664.0:"P5D1", 662.0:"P5D2", 656.0:"P5D3", 696.0:"P5D4",
               628.0:"P6D1", 626.0:"P6D2", 624.0:"P6D3", 632.0:"P6D4",
               646.0:"P7D1", 644.0:"P7D2", 642.0:"P7D3", 630.0:"P7D4"
               }

channelList = [692.0, 690.0, 688.0, 640.0,
                      674.0, 576.0,
                                    610.0,
               608.0, 598.0, 600.0, 594.0, 592.0,
               664.0, 662.0,        696.0,
                      626.0, 624.0, 
               646.0, 644.0, 642.0        ]#enriched + natural

channelList = [692.0, 690.0, 688.0, 640.0,
                      674.0, 576.0,
                                    610.0,
               
                      662.0,        696.0,
                      626.0, 624.0, 
                      644.0, 642.0        ] #enriched

massDict = {"P1D1":0.5099, "P1D2":0.9788, "P1D3":0.8113, "P1D4":0.9679,
            "P2D1":0.587, "P2D2":0.7229, "P2D3":0.6591, "P2D4":0.6886,
            "P3D1":0.5776, "P3D2":0.8863, "P3D3":0.949, "P3D4":1.0238,
            "P4D1":0.5842, "P4D2":0.5908, "P4D3":0.5945, "P4D4":0.5711, "P4D5":0.5933,
            "P5D1":0.5795, "P5D2":0.7306, "P5D3":0.6320, "P5D4":0.9820,
            "P6D1":0.7316, "P6D2":0.6755, "P6D3":0.7014, "P6D4":0.5723,
            "P7D1":0.588, "P7D2":0.7099, "P7D3":0.5909, "P7D4":0.9643
            } #Active Mass

#---------CANVAS SETUP---------
canvas = ROOT.TCanvas("canvas", "canvas", 800, 600)

##--------OUTPUT FILE----------
text_file1 = open("ALP_MJD5_20.txt", "w")
text_file2 = open("Vec_MJD5_20.txt", "w")

#---------LOAD DATA FROM TREE------
inFileDir = "/global/homes/j/jrager/LowE/RooFit/KVbosonic/"
#inFileName = "m1DiagnosticTree2Aug2016.root" #this file has .23 keV shift
inFileName = "m1DiagnosticTree4Aug2016.root"
inFile = ROOT.TFile(inFileDir + inFileName)
dataTree = inFile.Get("diagTree").Clone()
dataTree.SetDirectory(0) #TTrees need this before closing the file, otherwise segfault
inFile.Close()

## Manually program in the resolution curve, easy enough
#THE RESOLUTION CURVE
sigmaFunc = ROOT.TF1("sigmaFunc", "TMath::Sqrt([0]*[0] + [1]*[1]*x + [2]*[2]*x*x)", 5, 200)
#sigmaFunc.SetParameter(0, 0.235653) #calibration parameters from Pinghan's fit
#sigmaFunc.SetParameter(1, 0.042941)
#sigmaFunc.SetParameter(2, 0.000903)
sigmaFunc.SetParameter(0, 0.1) #calibration parameters from Ian's fit (**DEPRECATED** use sigConfHist)
sigmaFunc.SetParameter(1, 0.02)
sigmaFunc.SetParameter(2, 0.0002)
## I don't understand what this file is
sigConfFileName = "sigConfHist19Oct16.root"
sigConfFile = ROOT.TFile(inFileDir + sigConfFileName)
sigConfHist = sigConfFile.Get("confHist").Clone()
sigConfHist.SetDirectory(0)
sigConfFile.Close()

## the efficiency fit curve and bin by bin efficiency
#THE T/E EFF CURVE
#etaFileName = "toeEffCurves19Jul2016.root"
etaFileName = "P5D2_12Sep16.root"
etaFile = ROOT.TFile(inFileDir + etaFileName)
etaFunc = etaFile.Get("effFit").Clone()
etaInterval = etaFile.Get("fInts").Clone()
etaInterval.SetDirectory(0) #TH1s need this, otherwise segfault.
etaFile.Close()

#THE TRITIUM HISTOGRAM
tritFileName = "TritSpec.root"
tritFile = ROOT.TFile(inFileDir + tritFileName)
tritSpec = tritFile.Get("tritHist").Clone()
tritSpec.SetBins(500, 0., 100.)
tritSpec.SetDirectory(0)
tritFile.Close()

#----------DATA SETUP---------------
## python lists
energyList = [] #setup a list of energies and a list of limits (for easy copying output)
alpList = []
vecList = []

drawFlag = True #*!*!*!*SET TO TRUE TO SEE PLOTS, FALSE TO GENERATE LIMITS ONLY*!*!*!*

#lowEnRange = [x / 5.0 for x in range(int(5.6*5), 20*5+1)] #At low energy, set limit every 0.2 keV (start at 5.6)
lowEnRange = [10.3] #UNCOMMENT ABOVE LINE for 5 - 20 keV

for enVal in lowEnRange: #EXCHANGE THIS LINE FOR NEXT LINE FOR 21 - 100 keV
##for enVal in xrange(21, 94): #(end at 93)
#for enVal in xrange(21, 23):
    #try: #python no garbage collecty, so keep doing this until we run out of memory. I know, I know...
        energyList.append(enVal)
        enLowBound = 5.0 #Jason wants BG to cover entire 5 - 100 keV range
        enUpBound = 100.0
            
        #----read criterion from tree
        ## the energy parameter
        calE = ROOT.RooRealVar("calENF", "Calibrated Energy", enLowBound, enUpBound, "keV") #change this range to fit parameters of interest
        #calENF = ROOT.RooRealVar("calENF", "Calibrated Energy", enLowBound, enUpBound, "keV") #change this range to fit parameters of interest
        ## The RooCategory thing probably isn't necessary for what I'm doing because I'm not going to switch back and forth from natural to enriched
        enr = ROOT.RooCategory("enr", "Enriched or Natural")
        enr.defineType("Enr.", 1)
        
        ## RooDataSet is a container class to hold unbinned data
        ## Kris did an unbinned analysis, I might to a binned analysis because it's easier and quicker
        data = ROOT.RooDataSet("data", "data", dataTree, ROOT.RooArgSet(calE, enr))

        print "NOW WE TRY TO FIT SOMETHING"

        #---------Signal Peak-----------
        ## define nuisance parameters and energy variable
        alpha = ROOT.RooRealVar("alpha", "Scale correction", -0.0014, -.01, -0.000001)
        E0 = ROOT.RooRealVar("E0", "Offset correction", -0.256, -.4, -.00001)
        envalRoo = ROOT.RooRealVar("envalRoo", "Real Energy", enVal)
        mAList = ROOT.RooArgList(alpha, envalRoo, E0)
        mA = ROOT.RooFormulaVar("mA", "envalRoo + alpha*(envalRoo - 95.0) + E0", mAList)
        #mA = ROOT.RooRealVar("mA", "mA", enVal)
        print "SIGNAL MODEL NUISANCE MARAMETERS"

        #INIT RESOLUTION BASED ON RES CURVE
        #resList = ROOT.RooArgList(mA)
        #res = ROOT.RooFormulaVar("res", "TMath::Sqrt(0.00000004*mA*mA + 0.0004*mA*mA + .01*mA*mA)", resList)
        #resValInit = sigmaFunc(enVal) #Parameters fit for sigma
        ## define nuisance parameters and energy variable
        resValInit = sigConfHist.GetBinContent(sigConfHist.GetXaxis().FindBin(enVal))
        res = ROOT.RooRealVar("res", "Resolution, Sigma(E)", resValInit + 0.0000002, 0.001, 2.0, "keV")
        print "RESOLUTION CURVE"

        #INIT eff
        ## where cut efficiency gets applied
        eff = ROOT.RooRealVar("eff", "T/E Efficiency", etaFunc(enVal)+.000001, 0.9, 1.0)
        print "EFFICIENCY CURVE"

        peakGaus = ROOT.RooGaussian("peak_gaus", "gaussian for DM signal", calE, mA, res) #change to x for the alphas
        peakYieldInit = ROOT.RooRealVar("peakYieldInit", "yield signal peak", 0.1, 0.0, 10000.)
        peakYieldList = ROOT.RooArgList(eff, peakYieldInit)
        peakYield = peakYieldInit
        if enVal < 20: #Only worry about eff for less than 20 keV, 1 otherwise
            peakYield = ROOT.RooFormulaVar("peakYield", "eff*peakYieldInit", peakYieldList)
        print "GAUSSIAN FOR DARK MATTER SIGNAL"

        #---------Linear background--------
        m = ROOT.RooRealVar("m", "background slope", 0.00002, -0.1, 0.1)
        mList = ROOT.RooArgList(m)
        background = ROOT.RooPolynomial("background", "Linear background function", calE, mList)
        bkgdYield = ROOT.RooRealVar("bkgdYield", "yield of background", 20.0, 0.0, 10000.)
        print "LINEAR BACKGROUND"

        #---------10.3 keV cosmogenic peak------
        energy10p3 = ROOT.RooRealVar("energy10p3", "True Energy of 10.36 keV peak", 10.36, "keV")
        kLineList = ROOT.RooArgList(alpha, energy10p3, E0)
        cent10p3 = ROOT.RooFormulaVar("cent10p3", "energy10p3 + alpha*(energy10p3 - 95.0) + E0", kLineList)
        sig10p3val = sigConfHist.GetBinContent(sigConfHist.GetXaxis().FindBin(10.36))
        #sig10p3List = ROOT.RooArgList(cent10p3)
        #sig10p3 = ROOT.RooFormulaVar("sig10p3", "TMath::Sqrt(0.00000004*cent10p3*cent10p3 + 0.0004*cent10p3*cent10p3 + .01*cent10p3*cent10p3)", sig10p3List)
        sig10p3 = ROOT.RooRealVar("sig10p3", "Sigma of 10.36 keV peak", sig10p3val, sig10p3val - 0.04, sig10p3val + 0.04)
        geGauss = ROOT.RooGaussian("geGauss", "Gaussian for 10.36 keV peak", calE, cent10p3, sig10p3)
        geGaussYield = ROOT.RooRealVar("geGaussYield", "Yield of 10.3 keV peak", 10.0, 0.0, 10000.)
        print "10.3 COSMOGENIC PEAK"

        #--------Tritium background----------
        tritList = ROOT.RooArgList(calE)
        tritSet = ROOT.RooArgSet(calE)
        tritRooHist = ROOT.RooDataHist("trit", "Tritium Histogram", tritList, tritSpec)
        tritPdf = ROOT.RooHistPdf("tritPdf", "TritiumPdf", tritSet, tritRooHist, 1) #1 means linear interpolation
        tritYield = ROOT.RooRealVar("tritYield", "Yield of tritium", 0.02, 0.0, 10000.)
        print "TRITIUM PARAMETERS"

        #---------Signal Plus BG PDF = total Pdf--------
        ## Make the composite probability distribution function
        shapes = ROOT.RooArgList()
        shapes.add(background)
        shapes.add(peakGaus) #SWITCH COMMENT WITH BELOW FOR FASTER
        shapes.add(geGauss)
        shapes.add(tritPdf)

        yields = ROOT.RooArgList()
        yields.add(bkgdYield)
        yields.add(peakYield)
        yields.add(geGaussYield)
        yields.add(tritYield)

        totalPdf = ROOT.RooAddPdf("totalPdf", "sum of signal and background PDF", shapes, yields)
        print "COMPOSITE PDF"

        #----------Constraint/Penaltie Values------------
        print "Start building constraints"
        mA.Print()
        ##if drawFlag:
            ##WaitForReturn()

        mean_alpha = ROOT.RooRealVar("mean_alpha", "Best Guess Alpha", -0.0014)
        mean_E0 = ROOT.RooRealVar("mean_E0", "Best Guess E0", -0.256)
        #sigma_mA = ROOT.RooRealVar("sigma_calE", "Uncertainty of Centroid", 0.28)
        print "SIGNAL NUISANCE PARAMETERS CONSTRAINTS"

        ## I still don't understand this  stuff well
        mean_res = ROOT.RooRealVar("mean_res", "Res Value from function", resValInit)
        sigErr = sigConfHist.GetBinError(sigConfHist.GetXaxis().FindBin(enVal))
        sigma_res = ROOT.RooRealVar("sigma_res", "Resolution Uncertainty", sigErr)#resValRange (was .06/2.355)
        print "RESOLUTION FUNCTION CONSTRAINTS"

        mean_eff = ROOT.RooRealVar("mean_eff", "Eff Val from function", eff.getVal())
        effErr = etaInterval.GetBinError(etaInterval.GetXaxis().FindBin(enVal))
        sigma_eff = ROOT.RooRealVar("sigma_eff", "Eff. Unc", effErr)
        print "EFFICIENCY CONSTRAINTS"

        mean_exp = ROOT.RooRealVar("mean_exp", "Exp Val", 1./478.0)
        sigma_exp = ROOT.RooRealVar("sigma_exp", "Exp. Unc", 0.000026)
        print "EXPOSURE"

        #mean_sig10p3 = ROOT.RooRealVar("mean_sig10p3", "Exp 10p3 val", sig10p3val)
        ## I need to figure out how to get these  values in the covariance matrix
        #--------Covariance Matrix-----------
        elArray = numpy.array(
                [8.1e-7,         -3.0e-6,     0.0,    #0.0,
                 -3.0e-6,      0.000256,        0.0,    #0.0, 
                  0.0,            0.0,           (sigma_res.getVal())**2],# 0.0,#],
                  #0.0, 0.0, 0.0, 0.004*0.004],
                 dtype=numpy.float64)
        print "HIGH ENERGY COVARIANCE MATRIX"
        ## I'll want to delete this because my efficiency above 20keV isn't as good as Kris's
        ## Why is the covariance matrix below 20 keV bigger in dimension than the general one?
        if enVal < 20: #Only worry about eff at less than 20 keV
                elArray = numpy.array(
                        [8.1e-7,       -3.0e-6,     0.0,                             0.0, #0.0,          
                        -3.0e-6,    0.000256,         0.0,                             0.0, #0.0,
                        0.0,          0.0,             (sigma_res.getVal())**2,          0.0, #0.0,
                        0.0,          0.0,             0.0,         (sigma_eff.getVal())**2],# 0.0,#],
                        #0.0, 0.0, 0.0, 0.0, 0.004*0.004],
                        dtype=numpy.float64)
        print "LOW ENERGY COVARIANCE MATRIX"
        covMatrix = ROOT.TMatrixDSym(3,elArray)
        if enVal < 20:
                covMatrix = ROOT.TMatrixDSym(4,elArray)
        print "COVARIANCE MATRICES INITIALIZED"

        #--------Constraint Pdf-------------
        ## The multivariate Gaussian that constrains all the floated nuissance parameters
        xVec = ROOT.RooArgList(alpha, E0, res)#, sig10p3)
        muVec = ROOT.RooArgList(mean_alpha, mean_E0, mean_res)#, mean_sig10p3)
        if enVal < 20:
                xVec = ROOT.RooArgList(alpha, E0, res, eff)#, sig10p3)
                muVec = ROOT.RooArgList(mean_alpha, mean_E0, mean_res, mean_eff)#, mean_sig10p3)
        constrainGauss = ROOT.RooMultiVarGaussian("constrainGauss", "Multivariate Constraint Gaussian", xVec, muVec, covMatrix)
        constrainGauss.covarianceMatrix().Print()
        #if drawFlag:
            #WaitForReturn()

        pdfList = ROOT.RooArgList(totalPdf, constrainGauss)
        ## RooProdPdf = a PDF made from a product of PDF's
        totalPdfConstrain = ROOT.RooProdPdf("total_cons", "Total Product Constraint Pdf", pdfList)
        print "MULTIVARIATE GAUSSIAN CONSTRAINT"

        #===============================
        #==========DO THE FIT===========
        #===========AND PLOT============
        ## mA is signal peak formula, RF is RooFit
        ## fit entire model to data, with constraint on signal model?
        constrainSet = ROOT.RooArgSet(mA, res)#, exp)
        if enVal < 20:
                constrainSet = ROOT.RooArgSet(mA, res, eff)#, exp)
        r1 = totalPdfConstrain.fitTo(data, RF.Constrain(constrainSet), RF.Save())
        print "MODEL FIT TO DATA"

        r1.Print("v")
        
        ### It's good until here.  It doesn't get to DRAW ON PLOT so the draw stuff is crashing it

        #if drawFlag:
            ##WaitForReturn()

        #Draw on a plot
        xframe = calE.frame(RF.Title(";Energy(keV)"))
        bins = ROOT.RooBinning(enLowBound, enUpBound)
        bins.addUniform(int(enUpBound - enLowBound), enLowBound, enUpBound)
        data.plotOn(xframe, RF.Binning(bins))
        print "DRAW ON PLOT"

        #Change THIS for COMPONENTS
        ## I don't understand the Chi squared stuff very well - need to brush up on this
        totalPdfConstrain.plotOn(xframe, RF.LineColor(ROOT.kRed))
        ##totalPdfConstrain.plotOn(xframe)
        print "checkpoint 1"
        if enVal <= 20:
                chiSquared = xframe.chiSquare(0)#chiSquare(10)
        else:
                chiSquared = xframe.chiSquare(9)
        print "The chi-squared / ndf =" + str(chiSquared)
        setWrapPeak = ROOT.RooArgSet(peakGaus)
        totalPdfConstrain.plotOn(xframe, RF.Components(setWrapPeak), RF.LineStyle(ROOT.kDotted))
        ##totalPdfConstrain.plotOn(xframe)
        #constrainPdf.plotOn(xframe, RF.LineColor(ROOT.kRed))
        #setWrapPeak = ROOT.RooArgSet(sigGaus)
        #constrainPdf.plotOn(xframe, RF.Components(setWrapPeak), RF.LineStyle(ROOT.kDotted))
        print "checkpoint 2"

        xframe.SetMinimum(0.001)
        xframe.SetMaximum(100)
        print "set xframe limits"

        leg = ROOT.TPaveText(70, 80, 95, 90, "NB")
        leg.SetTextFont(133)
        leg.SetFillColor(0)
        leg.SetBorderSize(1)
        leg.SetTextSize(22)
        leg.AddText("#chi^{2}/NDF = %.3f" %(chiSquared))
        xframe.addObject(leg)
        print "canvas legend"

        xframe.Draw()
        print "draw xframe"
        #ROOT.gPad.SetLogy()
        if drawFlag:
            canvas.Update()
            #WaitForReturn()


        ## Dealing with the machinery of Minuit
        #nll = totalPdf.createNLL(data, RF.NumCPU(2))
        nll = totalPdfConstrain.createNLL(data, RF.NumCPU(4))
        ROOT.RooMinuit(nll).migrad()

        xframe2 = peakYieldInit.frame(ROOT.RooFit.Bins(50), ROOT.RooFit.Range(0., 50.), ROOT.RooFit.Title("LL and profileLL in peakYield"))
        #nll.plotOn(xframe2, ROOT.RooFit.ShiftToZero())

        pll_pkYield = nll.createProfile(ROOT.RooArgSet(peakYieldInit))
        pll_pkYield.Print()
        peakFitVal = pll_pkYield.bestFitObs().getRealValue("peakYieldInit")
        peakFitRooVal = ROOT.RooRealVar("peakFitLoc", "Location of best fit", peakFitVal)
        print "THE DAMN min is " + str(pll_pkYield.getVal()) + " at " + str(peakFitVal)
        print peakFitRooVal.getVal()
        #WaitForReturn()

        p_mu = 0
        print "line alpha"
        if peakFitVal >= 0:
            print "line beta"
            pll_pkYield.plotOn(xframe2, ROOT.RooFit.LineColor(ROOT.kRed))#, ROOT.RooFit.ShiftToZero())
            ##pll_pkYield.plotOn(xframe2)
            print "first line"
            p_mu = ROOT.RooFormulaVar("p_mu","p_{#mu} using asymptotic formulae","TMath::Prob(2*@0,1.)",ROOT.RooArgList(pll_pkYield))
            print "second line"
        else:
            shiftVal = pll_pkYield.asTF(ROOT.RooArgList(peakYield))(0.0)
            print "third line"
            strVal = str(shiftVal)
            print "fourth line"
            pll_pkYield.plotOn(xframe2, ROOT.RooFit.LineColor(ROOT.kRed))#, ROOT.RooFit.ShiftToZero())
            ##pll_pkYield.plotOn(xframe2)
            print "fifth line"
            pll_pkYield.plotOn(xframe2, ROOT.RooFit.LineColor(ROOT.kBlue), ROOT.RooFit.ShiftToZero())
            ##pll_pkYield.plotOn(xframe2, ROOT.RooFit.ShiftToZero())
            print "sixth line"
            p_mu = ROOT.RooFormulaVar("p_mu","p_{#mu} using asymptotic formulae","TMath::Prob(2*(@0 - "+ strVal +"),1.)",ROOT.RooArgList(pll_pkYield))
        print "checkpoint 3"

        xframe2.SetMinimum(0)
        xframe2.SetMaximum(3)
        print "checkpoint 4"

        #canvas.Update()
        #WaitForReturn()

        #p_mu.plotOn(xframe2,ROOT.RooFit.LineColor(ROOT.kGreen))
        xframe2.SetTitle("; S (peak yield); -Log #lambda(S)")
        xframe2.Draw()

        xframe2.Print("v")
        print "checkpoint 5"

        #plCurve = xframe2.getCurve("nll_totalPdf_data_Profile[peakYield]_Norm[peakYield]")
        #plCurve.SetName("plCurve")


        ROOT.gPad.SetLogy(0) #Pump$&G@ug3$
        print "checkpoint 6"

        limit = 0
        if peakFitVal > 0:
            limit = p_mu.findRoot(peakYieldInit, peakFitVal+1.0,50,0.1) #peakYield instead of zero
        else:
            limit = p_mu.findRoot(peakYieldInit, 1,50,0.1)
        print "The limit in signal counts is: " + str(limit)
        #print str(enVal) + " " + str(ROOT.TMath.Sqrt(limit / (9.0E15*.001/enVal * 86400 * AxioElectric(enVal) * 478)))
        vectorDM = True
        alpList.append(limit / (0.664*1.0E24/enVal * AxioElectric(mA.getVal()) * 478)) #0.664 = 10^24 / 6.02E23 * 0.4 (see Pospelov Form)
        print "checkpoint 7"
        #above has to convert cm^2/g to barn / atom, the Ge atomic mass cancels out with A in conversion 
        vectorDM = False
        vecList.append(ROOT.TMath.Sqrt(limit / (9.0E15*.001/enVal * 86400 * AxioElectric(mA.getVal()) * 478)))
        print "checkpoint 8"
        line = ROOT.TLine()
        line.SetLineColor(ROOT.kGreen + 3)
        line.DrawLine(limit, 0, limit, 3)
        line.DrawLine(0, 1.355, 50, 1.355)
        print "checkpoint 9"

        print "ENERGY " + str(mA.getVal()) + " DONE!!"

        if drawFlag:
            canvas.Update()
            #WaitForReturn()

        calE.IsA().Destructor(calE)
        enr.IsA().Destructor(enr)
        data.IsA().Destructor(data)
        mA.IsA().Destructor(mA)
        res.IsA().Destructor(res)
        eff.IsA().Destructor(eff)
        #eff10p3.IsA().Destructor(eff10p3)
        alpha.IsA().Destructor(alpha)
        E0.IsA().Destructor(E0)
        envalRoo.IsA().Destructor(envalRoo)
        mAList.IsA().Destructor(mAList)
        mean_alpha.IsA().Destructor(mean_alpha)
        mean_E0.IsA().Destructor(mean_E0)
        peakGaus.IsA().Destructor(peakGaus)
        peakYieldList.IsA().Destructor(peakYieldList)
        peakYieldInit.IsA().Destructor(peakYieldInit)
        if enVal< 20:
                peakYield.IsA().Destructor(peakYield)
        m.IsA().Destructor(m)
        mList.IsA().Destructor(mList)
        background.IsA().Destructor(background)
        bkgdYield.IsA().Destructor(bkgdYield)
        cent10p3.IsA().Destructor(cent10p3)
        sig10p3.IsA().Destructor(sig10p3)
        geGauss.IsA().Destructor(geGauss)
        geGaussYield.IsA().Destructor(geGaussYield)
        tritList.IsA().Destructor(tritList)
        tritSet.IsA().Destructor(tritSet)
        tritRooHist.IsA().Destructor(tritRooHist)
        tritPdf.IsA().Destructor(tritPdf)
        tritYield.IsA().Destructor(tritYield)
        shapes.IsA().Destructor(shapes)
        yields.IsA().Destructor(yields)
        totalPdf.IsA().Destructor(totalPdf)
        #mean_mA.IsA().Destructor(mean_mA)
        #sigma_mA.IsA().Destructor(sigma_mA)
        mean_res.IsA().Destructor(mean_res)
        sigma_res.IsA().Destructor(sigma_res)
        mean_eff.IsA().Destructor(mean_eff)
        sigma_eff.IsA().Destructor(sigma_eff)
        #elArray.IsA().Destructor(elArray)
        covMatrix.IsA().Destructor(covMatrix)
        xVec.IsA().Destructor(xVec)
        muVec.IsA().Destructor(muVec)
        constrainGauss.IsA().Destructor(constrainGauss)
        pdfList.IsA().Destructor(pdfList)
        totalPdfConstrain.IsA().Destructor(totalPdfConstrain)
        constrainSet.IsA().Destructor(constrainSet)
        r1.IsA().Destructor(r1)
        xframe.IsA().Destructor(xframe)
        #leg.IsA().Destructor(leg)
        bins.IsA().Destructor(bins)
        setWrapPeak.IsA().Destructor(setWrapPeak)
        nll.IsA().Destructor(nll)
        xframe2.IsA().Destructor(xframe2)
        pll_pkYield.IsA().Destructor(pll_pkYield)
        peakFitRooVal.IsA().Destructor(peakFitRooVal)
        #exp.IsA().Destructor(exp)
        mean_exp.IsA().Destructor(mean_exp)
        sigma_exp.IsA().Destructor(sigma_exp)
    #except:
    #    break

for i in xrange(len(alpList)):
    ##print str(energyList[i]) + " " + str(alpList[i])
    text_file1.write(str(energyList[i]) + ", " + str(alpList[i]) + "\n")

for i in xrange(len(vecList)):
    print str(energyList[i]) + " " + str(vecList[i])
    text_file2.write(str(energyList[i]) + ", " + str(vecList[i]) + "\n")

#!/usr/bin/python
#$ -V
#$ -j y
#$ -l gscratchio=1
#$ -l  projectio=1
#$ -o /project/projectdirs/majorana/users/krvorren/rateOutput
########################
# This script attempts to roughly calculate the 90% UL of
# hadronic (14.4 keV) GIVEN THE RATE FROM THE SIGNAL COUNTS
# FROM lowElikelihood_work.py
#
# Created by Kris Vorren, krisvorren@unc.edu
#
# -Version History/Notes-
# Jul 7, 2016: Created
########################
import sys, os, re, glob, ROOT, array, numpy
#ROOT.gROOT.SetBatch(True)

#----INITIALIZATION----
#Load some MGDO classes
ROOT.gROOT.Reset()
ROOT.gApplication.ExecuteFile("%s/Root/LoadMGDOClasses.C" %os.environ['MGDODIR'])
from ROOT import CLHEP

#Set up the styles...
#ROOT.gApplication.ExecuteFile("/Users/krvorren/Project/M1background/scripts/MJDTalkPlotStyle.C")
#ROOT.gROOT.ForceStyle()

#Simple wait for return fuction
def WaitForReturn():
    val = raw_input("Hit enter or 'q' to quit:   ")
    if val == 'q':  sys.exit()

#Status bar output
def StatusBar(i, total):
    sys.stdout.write('\r')
    sys.stdout.write("[%-20s] %.2f%%" % ('='*(100*(i+1)/total/5), 100.*(i+1)/total))
    sys.stdout.flush()
    if(i==total):print ""

#*******Initialization******

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
               
                      662.0,        696.0,
                      626.0, 624.0, 
                      644.0, 642.0        ] #good enriched removed 688, 626

massDict = {"P1D1":0.5099, "P1D2":0.9788, "P1D3":0.8113, "P1D4":0.9679,
            "P2D1":0.587, "P2D2":0.7229, "P2D3":0.6591, "P2D4":0.6886,
            "P3D1":0.5776, "P3D2":0.8863, "P3D3":0.949, "P3D4":1.0238,
            "P4D1":0.5842, "P4D2":0.5908, "P4D3":0.5945, "P4D4":0.5711, "P4D5":0.5933,
            "P5D1":0.5795, "P5D2":0.7306, "P5D3":0.6320, "P5D4":0.9820,
            "P6D1":0.7316, "P6D2":0.6755, "P6D3":0.7014, "P6D4":0.5723,
            "P7D1":0.588, "P7D2":0.7099, "P7D3":0.5909, "P7D4":0.9643
            } #Active Mass

#Experimental Parameters
totExposure = 478.1 # kg d (good enriched only)
temporalExp = 47.3 # in days (good enriched only)
#sigma = 0.3/2.355 #FWHM in keV / 2.355 (const for now)
lowEbound = 5.0 # (keV)
upEbound = 99.0 # (keV)
binsPerKeV = 5.0

#Declare globals for later
fitOffset = 0
fitSlope = 1

#Annoying Functions
def AxioElectric(En, beta): #This function computes the axio-electric cross section
    if En < 1:
        print "TOO SMALL"
        return 0
    if En > 100:
        print "TOO BIG"
        return 0
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
    
    return peVal/beta*3*En*En/(16*CLHEP.pi*1.0/137.0*511.0*511.0)*(1-ROOT.TMath.Power(beta, 2./3.)/3) * 1000 * (72.63 / 75.23)

## def LogLikelihood(hist, mA, estimator, beta): #HIST COMING IN MUST BE IN COUNTS PER BIN FOR BINNED LIKELIHOOD
##     logLike = 0

##     #PARAMETERS FOR THIS ANALYSIS
##     #beta = 1 #Change this for massive axions???
##     dmFlux = beta*beta*beta*39400 #/barn/d

##     lowBin = hist.GetXaxis().FindBin(lowEbound)
##     highBin = hist.GetXaxis().FindBin(upEbound)
##     for iBin in range(lowBin, highBin + 1):
##         Ei = (upEbound - lowEbound)/(highBin - lowBin)*(iBin-lowBin) + lowEbound
##         if 1/(ROOT.TMath.Sqrt(2*ROOT.TMath.Pi()))*ROOT.TMath.Exp(-(Ei-mA)*(Ei-mA)/(2)) < 0.0005:
##             continue #Just to speed things up a bit, at some point we don't need to spin gears so much
##         #print Ei
##         dmCounts = 0
##         for iChan in channelList:
##             detExposure = massDict[channelDict[iChan]]*temporalExp #grab the individual mass based on the channel
##             sigma = sigmaFuncDict[channelDict[iChan]](mA)
##             dmCounts += toeEffFunc(Ei)*1.0E-34*AxioElectric(mA, beta)*dmFlux*detExposure\
##               *1/(ROOT.TMath.Sqrt(2*ROOT.TMath.Pi())*sigma)*ROOT.TMath.Exp(-(Ei-mA)*(Ei-mA)/(2*sigma*sigma))
##         yi = estimator*dmCounts + fitSlope*Ei + fitOffset #This time the estimator is the axion coupling product (more outside func)
##         yi = (upEbound - lowEbound)/(highBin - lowBin)*yi #need to total unitless counts so mult by bin width in keV
##         ni = hist.GetBinContent(iBin)*(upEbound - lowEbound)/(highBin - lowBin)  #need total, unitless counts
##         logLike += -yi + ni*ROOT.TMath.Log(yi) - ROOT.TMath.Log(ROOT.TMath.Factorial(int(ni)))
##     return logLike

#********Canvas Setup************
canvas = ROOT.TCanvas("canvas", "canvas", 800, 600)
canvas.SetLeftMargin(.15)
canvas.SetTopMargin(0.07)
canvas.SetBottomMargin(.15)
#ROOT.gStyle.SetOptStat(0)
#ROOT.gPad.SetLogz()
#canvas.Divide(1,2)

drawFlag = True

if drawFlag:
    ROOT.gPad.SetLogy()
    ROOT.gPad.SetTickx()
    ROOT.gPad.SetTicky()
    massVals = numpy.array([0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5,
                           11, 11.5, 12, 12.5, 13, 13.5, 14, 14.2, 14.3, 14.35, 14.39, 14.399, 14.3999])
    ## coupVals = numpy.array([2.03306E-17, 2.03634E-17, 2.03961E-17, 2.04287E-17, 2.04939E-17, 2.05913E-17, 2.07204E-17, 2.08806E-17, 2.10396E-17,
    ##                         2.12289E-17, 2.14787E-17, 2.17256E-17, 2.20303E-17, 2.23905E-17, 2.28035E-17, 2.32666E-17, 2.37767E-17, 2.44131E-17,
    ##                         2.51131E-17, 2.59743E-17, 2.69815E-17, 2.81898E-17, 2.97097E-17, 3.16228E-17, 3.40588E-17, 3.75943E-17, 4.28952E-17,
    ##                         5.21536E-17, 7.59803E-17, 1.05515E-16, 1.47196E-16, 2.06235E-16, 4.54605E-16, 1.42127E-15, 4.47E-15])
    coupVals = numpy.zeros(len(massVals), dtype=numpy.float64)
    for i in xrange(len(coupVals)):
        beta = ROOT.TMath.Sqrt((14.4*14.4 - massVals[i]*massVals[i]) / (14.4*14.4))
        coupVals[i] = ROOT.TMath.Sqrt(11.2/478./(beta*beta*beta)/4.56e23/86400.0/AxioElectric(14.4, beta))
        print coupVals[i]

    massValsEdel = numpy.array([3.98E-03, 8.78E-01, 1.20E+00, 1.52E+00, 1.81E+00, 2.66E+00, 3.30E+00, 3.90E+00, 5.07E+00, 5.90E+00, 6.67E+00,
                                7.30E+00, 7.86E+00, 8.34E+00, 8.79E+00, 9.18E+00, 9.52E+00, 9.85E+00, 1.02E+01, 1.08E+01, 1.12E+01, 1.16E+01,
                                1.19E+01, 1.23E+01, 1.27E+01, 1.30E+01, 1.34E+01, 1.38E+01, 1.40E+01, 1.41E+01, 1.41812E+01, 1.42393E+01, 1.42829E+01,
                                1.4312E+01, 1.44E+01, 1.44E+01, 1.44E+01, 1.44E+01, 1.44E+01, 1.44E+01, 1.44E+01])
    coupValsEdel = numpy.array([4.79E-17, 4.90E-17, 4.90E-17, 4.90E-17, 4.90E-17, 4.87E-17, 4.92E-17, 5.01E-17, 5.13E-17, 5.25E-17, 5.38E-17,
                                5.50E-17, 5.64E-17, 5.77E-17, 5.91E-17, 6.05E-17, 6.20E-17, 6.35E-17, 6.56E-17, 6.91E-17, 7.28E-17, 7.60E-17,
                                8.04E-17, 8.63E-17, 9.45E-17, 1.03E-16, 1.20E-16, 1.46E-16, 1.84E-16, 2.12E-16, 2.44E-16, 2.87E-16, 3.36E-16,
                                3.94E-16, 6.62E-16, 9.07E-16, 1.67E-15, 3.35E-15, 6.21E-15, 1.27E-14, 2.26E-14])
    betaPlot = ROOT.TGraph(34, massVals, coupVals)
    edelPlot = ROOT.TGraph(40, massValsEdel, coupValsEdel)
    betaPlot.GetXaxis().SetNdivisions(10)
    betaPlot.SetLineColor(ROOT.kRed)
    betaPlot.SetLineWidth(3)
    betaPlot.SetName("hadCoupling")
    betaPlot.SetTitle("; Axion Mass (keV); g_{Ae} #times g_{AN}^{eff}")
    betaPlot.GetXaxis().CenterTitle()
    betaPlot.GetYaxis().CenterTitle()
    betaPlot.SetMinimum(1e-17)
    betaPlot.SetMaximum(1e-15)
    #betaPlot.GetXaxis().SetTitleSize(0.06)
    #betaPlot.GetXaxis().SetTitleOffset(1.2)
    #betaPlot.GetXaxis().SetLabelSize(0.06)
    #betaPlot.GetYaxis().SetTitleSize(0.05)
    #betaPlot.GetYaxis().SetTitleOffset(1.3)
    #betaPlot.GetYaxis().SetLabelSize(0.045)
    betaPlot.GetXaxis().SetNdivisions(512)
    betaPlot.Draw("AL")

    edelPlot.SetLineColor(ROOT.kOrange)
    edelPlot.SetLineWidth(3)
    edelPlot.SetName("edelPlot")
    edelPlot.Draw("L SAME")

    #Legend
    leg1 = ROOT.TLegend(0.44, 0.65, 0.7, 0.85)
    leg2 = ROOT.TLegend(0.44, 0.65, 0.7, 0.85)
    leg1.SetTextFont(133)
    leg2.SetTextFont(133)
    leg1.SetTextSize(25)
    leg2.SetTextSize(25)
    leg1.SetFillStyle(0)
    leg2.SetFillStyle(0)
    leg1.AddEntry("edelPlot", "EDELWEISS", "")
    leg2.AddEntry("hadCoupling", "MAJORANA", "")

    leg1.Draw()
    leg2.Draw()
    canvas.Update()
    WaitForReturn()
    canvas.SaveAs("hadronic16Nov16.eps")
    


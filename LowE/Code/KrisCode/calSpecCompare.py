#!/usr/bin/python
########################
# This script is designed to add selected
# plots generated from M1.
#
# Created by Kris Vorren, krisvorren@unc.edu
#
# -Version History-
# Aug 6, 2015: Created.
########################
import sys, os, re, glob, ROOT, array, numpy

#----INITIALIZATION----
#Load some MGDO classes
ROOT.gROOT.Reset()
ROOT.gApplication.ExecuteFile("%s/Root/LoadMGDOClasses.C" %os.environ['MGDODIR'])
from ROOT import CLHEP

#Set up the styles...
ROOT.gApplication.ExecuteFile("/Users/krvorren/Project/M1background/scripts/MJDTalkPlotStyle.C")
ROOT.gROOT.ForceStyle()
ROOT.gStyle.SetOptStat(0)

#Simple wait for return fuction
def WaitForReturn():
    val = raw_input("Hit enter or 'q' to quit:   ")
    if val == 'q':  sys.exit()

#Start Filing
filesDir = "/Users/krvorren/Project/M1background/Spectra/"
enrSpecFilePath = filesDir + "enrSpec29Sep2016.root"
natSpecFilePath = filesDir + "natSpec29Sep2016.root"
unCalSpecPath = filesDir + "unCalSpec7Apr2016.root"
DS1SpecFilePath = filesDir + "DS1_100_TETMLin_EnrVsNat.root"
fitFilePath = filesDir + "bgFit_3Nov16.root"

#EXPOSURES
#ENR: 478 kg d
#NAT: 195 kg d

enrSpecFile = ROOT.TFile(enrSpecFilePath)
natSpecFile = ROOT.TFile(natSpecFilePath)
unCalSpecFile = ROOT.TFile(unCalSpecPath)
DS1file = ROOT.TFile(DS1SpecFilePath)
fitFile = ROOT.TFile(fitFilePath)

#canvas
canvas = ROOT.TCanvas("canvas", "canvas", 800, 600)
canvas.SetTickx()
canvas.SetTicky()
#ROOT.gPad.SetLogy()

#Get the histograms
enrSpec = enrSpecFile.Get("spec")
natSpec = natSpecFile.Get("spec")
unCalSpec = unCalSpecFile.Get("spec")
natDS1 = DS1file.Get("natural")
natDS1.Rebin(2)
natDS1.Scale(4)
natDS1.SetName("natDS1")
enrDS1 = DS1file.Get("enriched")
enrDS1.Rebin(2)
enrDS1.Scale(4)
enrDS1.SetName("enrDS1")

#---Deal with the fit graph---
fitGraph = fitFile.Get("bgFit")
fitGraph.SetMarkerStyle(0)
fitGraph.SetLineColor(ROOT.kBlack)
fitGraph.SetLineWidth(3)
fitGraph.SetLineStyle(ROOT.kDashed)
#fitGraph.SetPoint(58, 42.9, 20.29)
#fitGraph.SetPoint(59, 43.0, 20.29)
#fitGraph.SetPoint(60, 43.1, 20.29)
#fitGraph.SetPoint(61, 43.23, 20.29)
#fitGraph.SetPoint(62, 43.35, 20.29)
#fitGraph.SetPoint(63, 43.47, 20.29)
#fitGraph.SetPoint(64, 43.6, 20.29)
#fitGraph.SetPoint(65, 43.7, 20.29)
#fitGraph.SetPoint(66, 43.8, 20.29)
x = ROOT.Double()
y = ROOT.Double()
dummy = 0
for i in xrange(fitGraph.GetN()):
    dummy = fitGraph.GetPoint(i, x, y)
    fitGraph.SetPoint(i, x, y/478.0)

#--In case of rebinning, rescale so it's c/keV
rebinFactor = 2
scaleFactor = 1./rebinFactor
enrSpec.Rebin(rebinFactor)
enrSpec.Scale(478*scaleFactor)
natSpec.Rebin(rebinFactor)
natSpec.Scale(195*scaleFactor)
enrDS1.Rebin(rebinFactor)
enrDS1.Scale(scaleFactor)
natDS1.Rebin(rebinFactor)
natDS1.Scale(scaleFactor)

enrSpec.SetName("enr")
natSpec.SetName("nat")
unCalSpec.SetName("unCal")

#Fix Titles and axes (nat)
natSpec.SetTitle(";Energy (keV); counts / kg / d / keV")
natDS1.GetYaxis().SetTitle("counts / kg / d / keV")

natSpec.GetYaxis().CenterTitle()
natSpec.GetXaxis().CenterTitle()

natSpec.GetXaxis().SetRangeUser(5,30)
#natSpec.SetMinimum(0.001)
#natSpec.GetYaxis().SetRangeUser(0.01, 10)

#Fix Titles and axes (enr)
enrSpec.GetYaxis().SetTitle("counts / kg / d / keV")
enrDS1.GetYaxis().SetTitle("counts / kg / d / keV")

enrSpec.GetYaxis().CenterTitle()
enrSpec.GetXaxis().CenterTitle()

enrSpec.GetXaxis().SetRangeUser(5,30)
#enrSpec.GetYaxis().SetRangeUser(0.01, 0.15)
#enrSpec.SetMinimum(0.001)

#---Set Nat Spectra Color
natDS1.SetFillColor(ROOT.kBlue)
natSpec.SetLineWidth(2)
natSpec.SetLineColor(9)
natSpecClone = natSpec.Clone("natSpecClone")
natSpec.SetFillColor(9)
natSpec.SetMarkerStyle(0)

#---Set Enriched Spectra Color
enrSpec.SetLineColor(ROOT.kRed)
enrSpec.SetLineWidth(2)
enrSpecClone = enrSpec.Clone("enrSpecClone")
enrSpec.SetFillColor(ROOT.kRed)
enrSpec.SetMarkerStyle(0)

enrDS1.SetLineColor(ROOT.kRed)
enrDS1.SetFillColor(ROOT.kRed)

enrSpec.Sumw2()
natSpec.Sumw2()

enrSpecClone.Scale(1./478.)
natSpecClone.Scale(1./195.)

enrErr = ROOT.TH1F("enrErr", ";;", 500/rebinFactor, 0, 100)
for i in xrange(enrErr.GetNbinsX()):
    enrErr.SetBinContent(i,478)
    enrErr.SetBinError(i,6)
enrErr.Sumw2()

natErr = ROOT.TH1F("enrErr", ";;", 500/rebinFactor, 0, 100)
for i in xrange(enrErr.GetNbinsX()):
    natErr.SetBinContent(i,195)
    natErr.SetBinError(i,3)
natErr.Sumw2()

enrSpec.Divide(enrErr)
natSpec.Divide(natErr)


#---Draw Time
ROOT.gPad.SetLogy()
natSpecClone.Draw("")
natSpec.Draw("E1 same")
#natDS1.Draw("same")
enrSpecClone.Draw("same")
enrSpec.Draw("E1 same")
fitGraph.Draw("same")
#enrDS1.Draw("same")
#unCalSpec.Draw("same")

#---Inset Pad
insetPad = ROOT.TPad("insetPad", "insetPad", 0.42, 0.45, 0.89, 0.92)
insetPad.SetFillStyle(4000)
insetPad.Draw()

insetPad.cd()
#ROOT.gPad.SetLogy()
natSpecInset = natSpec.Clone("natSpecInset")
enrSpecInset = enrSpec.Clone("enrSpecInset")
natSpecInset.SetTitle(";;")
enrSpecInset.SetTitle(";;")
natSpecInset.Rebin(5)
natSpecInset.Scale(1./5.)
enrSpecInset.Rebin(5)
enrSpecInset.Scale(1./5.)
natSpecInset.GetXaxis().SetRangeUser(30, 100)
enrSpecInset.GetXaxis().SetRangeUser(30, 100)
enrSpecInset.GetYaxis().SetRangeUser(0, 0.1)
enrSpecInset.Draw()
enrSpecInset.GetYaxis().SetNdivisions(405)
natSpecInset.Draw("same")
fitGraph.Draw("same")

#---Legend
leg1 = ROOT.TLegend(0.59-.5, 0.65, 0.85-.5, 0.85)
leg1.SetTextFont(133)
leg1.SetTextSize(25)
leg1.SetFillStyle(0)
leg2 = ROOT.TLegend(0.59-.5, 0.65, 0.85-.5, 0.85)
leg2.SetTextFont(133)
leg2.SetTextSize(25)
leg2.SetFillStyle(0)
#leg.SetHeader("Legend")
#leg.AddEntry("unCal", "Natural, uncorrected", "L")
leg1.AddEntry("nat", "Natural", "")
leg1.SetTextColor(ROOT.kBlue)
#leg.AddEntry("natDS1", "Natural DS1", "L")
leg2.AddEntry("enr", "Enriched", "")
leg2.SetTextColor(ROOT.kRed)
#leg.AddEntry("enrDS1", "Enriched DS1", "L")
canvas.cd()
leg1.Draw()
leg2.Draw()

#----Arrows
arrow1 = ROOT.TArrow(10.2, 6, 10.2, 5, .012)
arrow1.Draw()
arrow2 = ROOT.TArrow(6.2, 4.5, 6.2, 3.8, .012)
arrow2.Draw()
arrow3 = ROOT.TArrow(8.6, 2.6, 8.6, 2.2, .012)
arrow3.Draw()

canvas.Update()
WaitForReturn()

canvas.SaveAs("tritium_6Mar17.eps")
#canvas.SaveAs("treatyum_log_29Jun16.root")

#outFile = ROOT.TFile("/Users/krvorren/Project/M1Background/lowEhistos_6Jun16.root", "RECREATE")
#outFile.WriteTObject(enrSpec, enrSpec.GetName())
#outFile.WriteTObject(natSpec, natSpec.GetName())
#outFile.WriteTObject(enrDS1, enrDS1.GetName())
#outFile.WriteTObject(natDS1, natDS1.GetName())



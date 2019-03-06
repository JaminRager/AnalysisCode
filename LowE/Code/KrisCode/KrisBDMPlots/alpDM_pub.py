#!/usr/bin/python

import sys, os, re, glob, ROOT, array, csv
import numpy as np

ds0_scale_min = 2.5
#ds0_scale_max = 3.3
ds0_scale_max = 3.0


ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetLabelFont(132, "XYZ")
ROOT.gStyle.SetTitleFont(132, "XYZ")
ROOT.gROOT.ForceStyle()

def read_CSV(fname):
    csv = np.genfromtxt (fname, delimiter=",")
    x = csv[:,0]
    y = csv[:,1]
    x, y =(list(z) for z in zip(*sorted(zip(x, y), key=lambda pair: pair[0])))
    return ROOT.TGraph(len(x), np.array(x), np.array(y))

def read_datathief(fname):
    f = open(fname)
    x = []
    y = []
    for line in f:
        if line.find('DataThief') >= 0 or len(line) == 0:
            continue
        sline = line.replace(' ', '').split(',')
        x.append(float(sline[0]))
        y.append(float(sline[1]))
    f.close()
    x, y =(list(z) for z in zip(*sorted(zip(x, y), key=lambda pair: pair[0])))
    return ROOT.TGraph(len(x), np.array(x), np.array(y))

ROOT.gStyle.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "canvas", 1200,800)
canvas.SetTopMargin(.095)
ROOT.gPad.SetLogx()
ROOT.gPad.SetLogy()
ROOT.gPad.SetLineWidth(2)
ROOT.gPad.SetTickx()
ROOT.gPad.SetTicky()

hist = ROOT.TH2D("hist", "", 100, 5.0, 120.0, 100, 5.0e-14, 2.0e-11)
hist.SetXTitle("m_{A} (keV)")
hist.SetYTitle("g_{Ae}")
hist.GetXaxis().SetTitleOffset(1.3)
hist.Draw()


#EDELWEISS
xEdel = [2.53, 2.64, 2.76, 2.87, 3, 3.13, 3.26, 3.4, 3.55, 3.7, 3.86, 4.02, 4.2, 4.38, 4.6, 4.76, 4.96, 5.18, 5.4, 5.63, 5.87, 6.08, 6.41, 6.66, 6.95, 7.19, 7.48, 7.77, 8.08, 8.32, 8.96, 9.3, 9.66, 9.96, 10.2, 10.4, 10.6, 10.6, 10.7, 10.8, 10.8, 10.9, 11, 11, 11.1, 11.2, 11.3, 11.5, 11.7, 11.9, 12.2, 12.5, 12.9, 13.5, 14.1, 14.7, 15.3, 15.9, 16.5, 17.3, 17.9, 18.6, 19.4, 20.3, 21, 21.5, 22, 22.5, 22.6, 23, 23.9, 24.4, 24.9, 25.5, 25.6, 26.1, 27, 27.9, 28.9, 29, 30.1, 31.1, 31.8, 33, 34, 34.4, 35, 35.5, 36.4, 37.3, 38.3, 39.6, 40.1, 41, 42, 43.3, 43.9, 45, 46.8, 48, 49.6, 51.8, 54, 55.3, 55.7, 57.7, 60, 62.1, 64.4, 66.7, 68.7, 70.7, 71, 71.7, 72.7, 74.9, 75.6, 76.8, 79.1, 80.2, 82.2, 85.6, 88.4, 90.2, 92.2, 92.7, 94.8, 97.4, 99.3, 102.]

yEdel = [2.28E-12, 2.03E-12, 1.91E-12, 1.81E-12, 1.72E-12, 1.67E-12, 1.71E-12, 1.81E-12, 1.87E-12, 1.85E-12, 1.83E-12, 1.84E-12, 2.02E-12, 2.35E-12, 2.97E-12, 3.56E-12, 4.03E-12, 4.28E-12, 4.3E-12, 4.31E-12, 4.62E-12, 5.2E-12, 6.3E-12, 6.5E-12, 6.24E-12, 5.59E-12, 5E-12, 4.99E-12, 5.37E-12, 6.29E-12, 7.83E-12, 8.94E-12, 1.07E-11, 1.29E-11, 1.56E-11, 1.7E-11, 1.36E-11, 1.12E-11, 9.35E-12, 7.91E-12, 6.85E-12, 5.83E-12, 4.72E-12, 3.78E-12, 3.21E-12, 2.77E-12, 2.35E-12, 1.94E-12, 1.62E-12, 1.36E-12, 1.14E-12, 1.11E-12, 1.26E-12, 1.34E-12, 1.29E-12, 1.45E-12, 1.45E-12, 1.26E-12, 1.1E-12, 1.09E-12, 1.28E-12, 1.22E-12, 1.19E-12, 1.24E-12, 1.3E-12, 1.6E-12, 1.88E-12, 1.84E-12, 1.56E-12, 1.4E-12, 1.51E-12, 1.81E-12, 2.15E-12, 2.13E-12, 1.8E-12, 1.58E-12, 1.71E-12, 2.1E-12, 1.99E-12, 1.75E-12, 2.05E-12, 2.46E-12, 2.92E-12, 3.32E-12, 3.54E-12, 2.98E-12, 2.51E-12, 2.41E-12, 2.9E-12, 3.41E-12, 4.02E-12, 3.96E-12, 3.43E-12, 2.89E-12, 2.56E-12, 3.19E-12, 4.02E-12, 4.64E-12, 4.21E-12, 3.57E-12, 3.03E-12, 2.93E-12, 3.16E-12, 3.84E-12, 4.66E-12, 5.24E-12, 5.65E-12, 5.05E-12, 5.65E-12, 5.85E-12, 6.95E-12, 6.78E-12, 5.87E-12, 4.85E-12, 4.3E-12, 5.35E-12, 6.44E-12, 7.16E-12, 6.34E-12, 7.67E-12, 8.82E-12, 7.99E-12, 6.74E-12, 5.41E-12, 6.72E-12, 8.2E-12, 9.84E-12, 9.09E-12, 8.03E-12, 8.2E-12]

#Xenon
xXenon = [1.298, 1.393, 1.495, 1.604, 1.721, 1.847, 1.983, 2.128, 2.283, 2.451, 2.63, 2.822, 3.029, 3.251, 3.489, 3.744, 4.018, 4.312, 4.554, 4.733, 4.998, 5.364, 5.757, 6.178, 6.63, 7.115, 7.636, 8.195, 8.794, 9.438, 10.129, 10.87, 11.666, 12.52, 13.436, 14.419, 15.474, 16.607, 17.822, 19.127, 20.526, 22.029, 23.641, 25.371, 27.228, 29.221, 31.359, 33.654, 35.542, 37.536, 39.515]

yXenon = [1.44E-12, 1.47E-12, 1.51E-12, 1.52E-12, 1.53E-12, 1.57E-12, 1.64E-12, 1.65E-12, 1.66E-12, 1.69E-12, 1.74E-12, 1.85E-12, 1.96E-12, 1.99E-12, 2.01E-12, 2.06E-12, 2.09E-12, 2.12E-12, 1.91E-12, 1.46E-12, 1.19E-12, 1.07E-12, 1.02E-12, 1.09E-12, 1.19E-12, 1.38E-12, 1.64E-12, 1.95E-12, 2.23E-12, 2.54E-12, 2.82E-12, 2.97E-12, 3.03E-12, 3.04E-12, 3E-12, 2.95E-12, 2.84E-12, 2.67E-12, 2.63E-12, 2.7E-12, 2.83E-12, 2.9E-12, 3.01E-12, 3.19E-12, 3.47E-12, 3.96E-12, 4.4E-12, 4.9E-12, 4.07E-12, 3.54E-12, 4.28E-12]

#XENON POSPO
#xXenonPo = [1.07037, 1.41133, 1.78919, 2.26821, 2.72807, 3.03196, 3.695, 4.44405, 5.1013, 5.27077, 6.0938, 6.59663, 7.38048, 7.73028, 7.83515, 8.26133, 8.82609, 9.63048, 10.6188, 13.8201, 14.7649, 15.7742, 17.3023, 18.7303, 19.7497, 20.8233, 22.5415, 24.7254, 26.7659, 28.8283, 29.8196, 31.3821, 34.3794, 35.7799, 36.0486]

#yXenonPo = [5.11731E-13, 3.78841E-13, 3.37933E-13, 3.01445E-13, 2.93559E-13, 3.16708E-13, 3.04611E-13, 2.93731E-13, 1.99879E-13, 1.63288E-13, 1.65861E-13, 1.85064E-13, 2.09676E-13, 2.32426E-13, 2.83956E-13, 3.29595E-13, 3.74814E-13, 4.24487E-13, 4.54496E-13, 3.77112E-13, 4.28536E-13, 4.8733E-13, 5.38207E-13, 6.08472E-13, 7.21399E-13, 8.17389E-13, 9.10692E-13, 1.01537E-12, 1.1404E-12, 1.27888E-12, 1.50385E-12, 1.78473E-12, 8.75088E-13, 1.00362E-12, 1.65142E-12]

xXenonPo = [2.01473, 2.17084, 2.33905, 2.52031, 2.71563, 2.9261, 3.15288, 3.39718, 3.66044, 3.94411, 4.24976, 4.56341, 4.89977, 5.27923, 5.68817, 6.12903, 6.60409, 7.11606, 7.66782, 8.26235, 8.90287, 9.59305, 10.3366, 11.1377, 12.0007, 12.9306, 13.9325, 15.0121, 16.1749, 17.4278, 18.7782, 20.2334, 21.8013, 23.4908, 25.3117, 27.2742, 29.3896, 31.6687, 34.1238, 36.0229, 38.0298, 39.8812]

yXenonPo = [3.05109E-13, 3.07295E-13, 3.10236E-13, 3.1773E-13, 3.32481E-13, 3.55058E-13, 3.73769E-13, 3.79155E-13, 3.91576E-13, 4.07314E-13, 4.20657E-13, 3.88208E-13, 2.73529E-13, 2.46509E-13, 2.34153E-13, 2.49456E-13, 2.69276E-13, 3.02002E-13, 3.51069E-13, 4.07621E-13, 4.56615E-13, 5.12109E-13, 5.59443E-13, 5.81928E-13, 5.91726E-13, 5.93832E-13, 5.97371E-13, 6.03089E-13, 5.64703E-13, 5.36398E-13, 5.351E-13, 5.56606E-13, 5.68691E-13, 5.93672E-13, 6.49321E-13, 7.51219E-13, 9.27045E-13, 1.12102E-12, 1.26027E-12, 8.95092E-13, 7.4793E-13, 8.58074E-13]

#XMASS_Old
#xXMASS = [40.9, 43.3, 45.7, 48.2, 50.6, 53.1, 55.5, 57.9, 60.4, 62.8, 65.3, 67.7, 70.1, 72.6, 75, 77.5, 79.9, 82.4, 84.8, 87.2, 89.7, 92.1, 94.6, 97, 99.4, 102, 104, 107, 109, 112, 114, 117, 119]

#yXMASS = [1.26E-12, 1.2E-12, 1.13E-12, 1.06E-12, 1E-12, 9.45E-13, 8.91E-13, 8.39E-13, 8.07E-13, 8.17E-13, 8.32E-13, 8.46E-13, 8.6E-13, 8.74E-13, 8.89E-13, 9.03E-13, 9.24E-13, 9.67E-13, 1.02E-12, 1.07E-12, 1.13E-12, 1.19E-12, 1.25E-12, 1.32E-12, 1.38E-12, 1.43E-12, 1.46E-12, 1.5E-12, 1.53E-12, 1.57E-12, 1.61E-12, 1.64E-12, 1.68E-12]

#XMass_New
xXMASS = [40.1, 42.4, 44.9, 47.5, 50.0, 52.5, 55.0, 57.6, 60.1, 62.4, 64.8, 67.3, 69.9, 72.6, 75.0, 79.8, 82.1, 84.8, 87.6, 91.9, 94.5, 100.0, 102.9, 104.8, 109.4, 112.0, 114.6, 117.4, 119.6]

yXMASS = [2.2E-13, 2.0E-13, 2.09E-13, 2.38E-13, 2.53E-13, 2.53E-13, 2.3E-13, 1.97E-13, 1.65E-13, 1.73E-13, 2.09E-13, 2.45E-13, 2.34E-13, 1.9E-13, 1.87E-13, 2.57E-13, 2.92E-13, 3.16E-13, 3.21E-13, 2.57E-13, 2.3E-13, 2.16E-13, 2.13E-13, 2.34E-13, 3.26E-13, 3.59E-13, 3.42E-13, 3.53E-13, 3.59E-13]

#CDEX
#xCDEX = [2.91522, 3.12208, 3.22036, 3.29638, 3.42722, 3.5302, 3.60171, 3.76062, 3.92475, 3.96947, 4.01821, 4.2143, 4.3062, 4.52827, 4.62625, 4.79838, 4.88551, 5.00859, 5.1384, 5.59147, 5.81325, 6.02223, 6.24746, 6.27091, 6.31069, 6.517, 6.55779, 6.57549, 6.59117, 6.79102, 6.9404, 7.18655, 7.18706, 7.20571, 7.28325, 7.59059, 7.77561, 7.88144, 8.15123, 8.48581, 8.56126, 8.9563, 8.97013, 9.01221, 9.03765, 9.13395, 9.42287, 9.61863, 9.68818, 9.72916, 9.78119, 9.78713, 9.88651, 9.96794, 10.0584, 10.1691, 10.2484, 10.3388, 10.3413, 10.3988, 10.4042, 10.4324, 10.4371, 10.4379, 10.7801, 11.0343, 11.199, 11.2986, 11.3122, 11.649, 11.9997, 12.414, 12.4797, 12.4832, 12.6348, 12.9749, 12.9758, 12.9768, 13.2227, 13.407, 13.4352, 13.7882, 13.823, 14.301, 14.3922, 14.486, 14.5636, 14.7782, 15.182, 15.5692, 15.828, 16.1137, 16.39, 16.4815, 16.5271, 16.6775, 16.7889, 16.8019, 17.6768, 17.7918, 17.8632, 18.4583, 18.5787, 19.31, 19.4276, 19.599, 19.8255, 20.2236]

xCDEX = [2.91522, 3.22036, 3.42722, 3.5302, 3.76062, 3.92475, 4.01821, 4.3062, 4.52827, 4.79838, 5.00859, 5.59147, 5.81325, 6.02223, 6.24746, 6.31069, 6.517, 6.57549, 6.79102, 6.9404, 7.18655, 7.59059, 7.77561, 7.88144, 8.15123, 8.48581, 8.9563, 9.13395, 9.42287, 9.61863, 9.88651, 10.0584, 10.2484, 10.4042, 10.7801, 11.0343, 11.199, 11.649, 11.9997, 12.414, 12.6348, 12.9749, 13.2227, 13.407, 13.7882, 13.823, 14.301, 14.486, 14.7782, 15.182, 15.5692, 15.828, 16.1137, 16.39, 16.5271, 16.7889, 17.6768, 17.8632, 18.4583, 18.5787, 19.4276, 19.599, 19.8255, 20.2236]

yCDEX = [1.1027E-12, 1.39001E-12, 1.75217E-12, 1.475E-12, 1.18587E-12, 9.85832E-13, 1.68667E-12, 1.97403E-12, 2.26277E-12, 3.30837E-12, 3.24887E-12, 2.64242E-12, 2.17485E-12, 4.74387E-12, 1.96572E-12, 1.35021E-12, 8.27022E-12, 3.17248E-12, 2.08709E-12, 2.63772E-12, 1.57484E-12, 3.1166E-12, 3.77667E-12, 4.52082E-12, 5.20736E-12, 4.30207E-12, 6.87707E-12, 1.14936E-11, 4.29165E-12, 3.35394E-12, 1.25401E-11, 2.76201E-12, 1.60829E-11, 8.98168E-12, 4.20852E-12, 2.95266E-12, 2.28608E-12, 1.23589E-12, 1.005E-12, 2.17445E-12, 1.1512E-12, 5.69064E-13, 1.00547E-12, 1.4298E-12, 1.17962E-12, 2.21104E-12, 1.02619E-12, 1.46435E-12, 9.70666E-13, 1.16526E-12, 1.47163E-12, 1.98929E-12, 2.40363E-12, 1.18387E-12, 7.22831E-13, 1.60517E-12, 8.30672E-13, 1.45956E-12, 1.97511E-12, 2.48171E-12, 1.93472E-12, 1.31231E-12, 9.22633E-13, 1.36573E-12]

#yCDEX = [1.1027E-12, 1.67288E-12, 1.39001E-12, 1.57484E-12, 1.75217E-12, 1.475E-12, 1.5249E-12, 1.18587E-12, 9.85832E-13, 1.32173E-12, 1.68667E-12, 2.44631E-12, 1.97403E-12, 2.26277E-12, 1.55374E-12, 3.30837E-12, 3.10185E-12, 3.24887E-12, 2.48709E-12, 2.64242E-12, 2.17485E-12, 4.74387E-12, 1.96572E-12, 1.60134E-12, 1.35021E-12, 8.27022E-12, 4.95819E-12, 3.17248E-12, 3.97829E-12, 2.08709E-12, 2.63772E-12, 1.57484E-12, 1.84367E-12, 2.3201E-12, 1.34024E-12, 3.1166E-12, 3.77667E-12, 4.52082E-12, 5.20736E-12, 4.30207E-12, 3.39753E-12, 6.87707E-12, 5.67481E-12, 1.57374E-11, 8.28242E-12, 1.14936E-11, 4.29165E-12, 3.35394E-12, 5.67098E-12, 2.73145E-12, 7.05792E-12, 9.00392E-12, 1.25401E-11, 2.33751E-12, 2.76201E-12, 4.24817E-12, 1.60829E-11, 1.0973E-11, 1.87168E-11, 7.24352E-12, 8.98168E-12, 1.24474E-11, 5.53872E-12, 3.29552E-12, 4.20852E-12, 2.95266E-12, 2.28608E-12, 1.82598E-12, 1.54142E-12, 1.23589E-12, 1.005E-12, 2.17445E-12, 1.74262E-12, 1.39013E-12, 1.1512E-12, 5.69064E-13, 6.68678E-13, 7.9895E-13, 1.00547E-12, 1.4298E-12, 1.82327E-12, 1.17962E-12, 2.21104E-12, 1.02619E-12, 2.41684E-12, 1.46435E-12, 1.91332E-12, 9.70666E-13, 1.16526E-12, 1.47163E-12, 1.98929E-12, 2.40363E-12, 1.18387E-12, 6.1652E-13, 7.22831E-13, 9.09676E-13, 1.60517E-12, 2.18542E-12, 8.30672E-13, 1.01484E-12, 1.45956E-12, 1.97511E-12, 2.48171E-12, 1.54448E-12, 1.93472E-12, 1.31231E-12, 9.22633E-13, 1.36573E-12]

#LUX

#xLUX = [2.02349, 2.16977, 2.32661, 2.4948, 2.67514, 2.86852, 3.07588, 3.29822, 3.53664, 3.7923, 4.06643, 4.36038, 4.67558, 5.01357, 5.37599, 5.7646, 6.18131, 6.62814, 7.10727, 7.62104, 8.17194, 8.76267, 9.3961, 10.0753, 10.8036, 11.5846, 12.422, 13.32, 14.2829, 15.3153, 15.9602]

#yLUX = [1.66145E-13, 1.83891E-13, 2.04386E-13, 2.27165E-13, 2.52748E-13, 2.80623E-13, 2.99429E-13, 2.99743E-13, 2.94151E-13, 2.92922E-13, 2.92922E-13, 2.99116E-13, 3.02262E-13, 3.06081E-13, 2.98491E-13, 2.90481E-13, 2.86257E-13, 2.91089E-13, 2.97556E-13, 3.1551E-13, 3.28649E-13, 3.21844E-13, 3.33848E-13, 3.67578E-13, 4.4097E-13, 5.22962E-13, 5.93538E-13, 6.41315E-13, 6.57622E-13, 5.80033E-13, 5.03105E-13]

xLUX = [1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 10.5, 11, 11.5, 12, 12.5, 13, 13.5, 14, 14.5, 15, 15.5, 16]

yLUX = [7.86163E-14, 1.01891E-13, 1.34923E-13, 1.80761E-13, 2.27173E-13, 2.13935E-13, 2.35091E-13, 3.01049E-13, 2.29973E-13, 1.91142E-13, 2.00515E-13, 2.03832E-13, 2.11441E-13, 2.09204E-13, 1.94275E-13, 1.67925E-13, 1.60627E-13, 1.91066E-13, 2.30121E-13, 2.69899E-13, 3.22808E-13, 3.64894E-13, 3.97169E-13, 4.17662E-13, 4.20078E-13, 4.05871E-13, 3.85021E-13, 3.41146E-13, 2.8835E-13, 2.58294E-13, 2.46682E-13]

#MJD DS0

#FULL RANGE NO INCLUDY A K-SHELL PEAK
## xDMlist = [5,5.2,5.4,5.6,5.8,6,6.2,6.4,6.6,6.8,7,7.2,7.4,7.6,7.8,8,8.2,8.4,8.6,8.8,9,9.2,9.4,9.6,9.8,10,10.2,10.4,10.6,10.8,11,11.2,
##            11.4,11.6,11.8,12,12.2,12.4,12.6,12.8,13,13.2,13.4,13.6,13.8,14,14.2,14.4,14.6,14.8,15,15.2,15.4,15.6,15.8,16,16.2,16.4,16.6,
##            16.8,17,17.2,17.4,17.6,17.8,18,18.2,18.4,18.6,18.8,19,19.2,19.4,19.6,19.8,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
##            36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,
##            77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100]

xDMlist = [5.6,5.8,6,6.2,6.4,6.6,6.8,7,7.2,7.4,7.6,7.8,8,8.2,8.4,8.6,8.8,9,9.2,9.4,9.6,9.8,10,10.2,10.4,10.6,10.8,11,11.2,
            11.4,11.6,11.8,12,12.2,12.4,12.6,12.8,13,13.2,13.4,13.6,13.8,14,14.2,14.4,14.6,14.8,15,15.2,15.4,15.6,15.8,16,16.2,16.4,16.6,
            16.8,17,17.2,17.4,17.6,17.8,18,18.2,18.4,18.6,18.8,19,19.2,19.4,19.6,19.8,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
            36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,
            77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93]
    
yDMlist = [1.1092E-12, 1.44542E-12, 1.55233E-12, 1.55504E-12, 1.37592E-12, 1.20145E-12, 1.05687E-12, 1.05641E-12, 1.02476E-12, 7.81029E-13, 8.29634E-13, 1.08806E-12, 1.16591E-12, 1.1647E-12, 1.3387E-12, 1.87631E-12, 2.1204E-12, 2.09864E-12, 1.68556E-12, 9.95057E-13, 7.9215E-13, 8.351E-13, 1.31467E-12, 2.84169E-12, 2.96551E-12, 2.14213E-12, 1.72935E-12, 1.55753E-12, 1.35917E-12, 6.62232E-13, 5.72292E-13, 4.5212E-13, 4.47828E-13, 4.92653E-13, 4.84064E-13, 4.70606E-13, 5.5266E-13, 6.36907E-13, 5.1182E-13, 4.4239E-13, 5.71403E-13, 7.79294E-13, 8.80986E-13, 8.9723E-13, 8.25865E-13, 6.02298E-13, 5.01904E-13, 6.11924E-13, 8.62332E-13, 1.00203E-12, 1.01851E-12, 8.52839E-13, 6.14327E-13, 5.68615E-13, 5.51398E-13, 4.70022E-13, 5.01443E-13, 7.2106E-13, 7.87182E-13, 7.37072E-13, 9.5677E-13, 1.05623E-12, 9.99299E-13, 9.3539E-13, 1.01329E-12, 1.024E-12, 9.26737E-13, 9.17561E-13, 1.09886E-12, 1.16532E-12, 1.05436E-12, 7.70749E-13, 7.40374E-13, 1.12901E-12, 8.93703E-13, 1.54326E-12, 9.20604E-13, 9.80438E-13, 1.31258E-12, 1.17286E-12, 1.2853E-12, 1.50534E-12, 7.80115E-13, 8.12105E-13, 1.21658E-12, 1.581E-12, 1.79589E-12, 1.16989E-12, 2.44499E-12, 1.08329E-12, 2.07707E-12, 1.13431E-12, 1.8001E-12, 1.23037E-12, 1.24662E-12, 2.01224E-12, 1.36626E-12, 1.4092E-12, 2.77492E-12, 1.40654E-12, 1.75448E-12, 2.59673E-12, 1.65723E-12, 2.32933E-12, 1.84481E-12, 2.76011E-12, 1.89349E-12, 1.85955E-12, 1.445E-12, 3.27298E-12, 1.76929E-12, 1.7622E-12, 1.86808E-12, 3.09603E-12, 1.74026E-12, 2.49099E-12, 2.12717E-12, 1.78431E-12, 2.13414E-12, 4.3157E-12, 2.00276E-12, 2.60857E-12, 2.54638E-12, 3.43581E-12, 1.98814E-12, 2.33686E-12, 2.21073E-12, 3.91597E-12, 3.23402E-12, 2.17201E-12, 4.47881E-12, 2.24521E-12, 2.83947E-12, 3.26565E-12, 3.36944E-12, 3.66631E-12, 3.89961E-12, 3.61792E-12, 4.93242E-12, 6.01356E-12, 2.87398E-12, 3.58794E-12, 3.43092E-12, 4.46888E-12, 4.09817E-12, 6.85061E-12]

band = False
yDMsmooth = []
yDMsmooth.append((yDMlist[0]+yDMlist[1])/2)
yDMsmooth.append((yDMlist[0]+yDMlist[1]+yDMlist[2])/3)
for i in xrange(2, len(xDMlist)-2):
    if xDMlist[i] < 20.0 or i >= len(xDMlist)-6:
        yDMsmooth.append(sum(yDMlist[i-2:i+3])/5)
    else:
        yDMsmooth.append(sum(yDMlist[i-6:i+7])/13)
yDMsmooth.append((yDMlist[-3]+yDMlist[-2]+yDMlist[-1])/3)
yDMsmooth.append((yDMlist[-2]+yDMlist[-1])/2)
for i in xrange(len(yDMsmooth)-1):
    if xDMlist[i] > 20:
        yDMsmooth[i] = sum(yDMsmooth[i-1:i+2])/3
yDMsmooth[-1] = (yDMsmooth[-1] + yDMsmooth[-1]) / 2
xMJDProj = np.array(xDMlist)
yMJDProj = np.array(yDMsmooth) / ds0_scale_min
for i in xrange(len(xDMlist)):
    xMJDProj = np.append(xMJDProj, [xDMlist[-(i+1)]])
    yMJDProj = np.append(yMJDProj, [yDMsmooth[-(i+1)] / ds0_scale_max])
xMJDProj = np.append(xMJDProj, [xMJDProj[0]])
yMJDProj = np.append(yMJDProj, [yMJDProj[0]])
if band:
    mjdProj = ROOT.TGraph(len(xMJDProj), xMJDProj, yMJDProj)
    mjdProj.SetName("mjdProj")
    mjdProj.SetFillColor(ROOT.kBlue-10)
else:
    n = (len(xMJDProj) - 1) / 2
    mjdProj0 = ROOT.TGraph(n, xMJDProj[0:n+1], yMJDProj[0:n+1])
    mjdProj0.SetName("mjdProj0")
    mjdProj0.SetLineColor(28)
    mjdProj0.SetLineStyle(2)
    mjdProj1 = ROOT.TGraph(n, xMJDProj[n:2*n], yMJDProj[n:2*n])
    mjdProj1.SetName("mjdProj1")
    mjdProj1.SetLineColor(ROOT.kBlack)
    mjdProj1.SetLineWidth(4)
    mjdProj1.SetLineStyle(5)

#Edelweiss Old
#edelLim = ROOT.TGraph(len(xEdel), np.array(xEdel), np.array(yEdel))
#edelLim.SetName("edelLim")
#edelLim.SetLineColor(ROOT.kOrange)
#edelLim.SetMarkerStyle(0)
#edelLim.SetLineWidth(2)

#EdelweissIII
edelLim = read_CSV("EdelweissIIIALP.csv")
edelLim.SetName("edelLim")
edelLim.SetLineColor(ROOT.kOrange-1)
edelLim.SetMarkerStyle(0)
edelLim.SetLineWidth(2)

#XENON
xenon = ROOT.TGraph(len(xXenon), np.array(xXenon), np.array(yXenon))
xenon = read_datathief("xenon100_pseudoscalar_9_2017.txt")
xenon.SetName("xenonLim")
xenon.SetLineColor(ROOT.kBlue)
xenon.SetLineWidth(2)

#XENON POSPO
xenonPo = ROOT.TGraph(len(xXenonPo), np.array(xXenonPo), np.array(yXenonPo))
xenonPo.SetName("xenonPo")
xenonPo.SetLineColor(ROOT.kBlue)
#xenonPo.SetLineStyle(ROOT.kDashed)
xenonPo.SetLineWidth(2)

#LUX
lux = ROOT.TGraph(len(xLUX), np.array(xLUX), np.array(yLUX))
lux.SetName("lux")
lux.SetLineColor(ROOT.kGreen + 1)
#lux.SetLineStyle(ROOT.kDashed)
lux.SetLineWidth(2)

#XMASS
xmass = ROOT.TGraph(len(xXMASS), np.array(xXMASS), np.array(yXMASS))
xmass.SetName("xmassLim")
xmass.SetLineColor(ROOT.kGreen - 1)
xmass.SetMarkerStyle(0)
xmass.SetLineWidth(2)

#CDEX
cdex = ROOT.TGraph(len(xCDEX), np.array(xCDEX), np.array(yCDEX))
cdex.SetName("cdexLim")
cdex.SetTitle("; m_{A} (keV); g_{Ae}")
cdex.SetLineColor(6)
#cdex.SetLineStyle(ROOT.kDashed)
cdex.SetMarkerStyle(0)
cdex.SetLineWidth(2)

#DS0 graph
alpLim  = ROOT.TGraph(len(xDMlist), np.array(xDMlist), np.array(yDMlist))
alpLim.SetName("alpLim")
alpLim.SetTitle("; m_{A} (keV); g_{Ae}")
alpLim.SetLineColor(ROOT.kBlack)
alpLim.SetMarkerStyle(0)
alpLim.SetLineWidth(3)

#PandaXII
pandaxII = read_datathief("pandaxII_pseudoscalar_7_2017.txt")
pandaxII.SetName("pandaxII")
pandaxII.SetLineColor(ROOT.kRed)
pandaxII.SetMarkerStyle(0)
pandaxII.SetLineWidth(2)
#pandaxII.SetLineStyle(2)


cdex.Draw("L")
if band:
    mjdProj.Draw("same F")
else:
    mjdProj1.Draw("L same")
lux.Draw("L same")
edelLim.Draw("L same")
#xenon.Draw("L same")
xmass.Draw("L same")
alpLim.Draw("L same")
xenonPo.Draw("L same")
pandaxII.Draw("L same")


legs = []
if True:
    legs.append(ROOT.TLegend(0.54, 0.68, 0.7, 0.78))
    legs.append(ROOT.TLegend(0.44, 0.65, 0.7, 0.85))
    #legs.append(ROOT.TLegend(0.7, 0.35, 0.8, 0.45))
    legs.append(ROOT.TLegend(0.68, 0.18, 0.78, 0.28))
    legs.append(ROOT.TLegend(0.08, 0.41, 0.3, 0.51))
    legs.append(ROOT.TLegend(0.37, 0.60, 0.5, 0.70))
    legs.append(ROOT.TLegend(0.4, 0.36, 0.6, 0.46))
    #legs.append(ROOT.TLegend(0.28, 0.2, 0.4, 0.3))
    legs.append(ROOT.TLegend(0.12, 0.21, 0.24, 0.31))
    if band:
        legs.append(ROOT.TLegend(0.52, 0.28, 0.72, 0.38))
    else:
        legs.append(ROOT.TLegend(0.53, 0.31, 0.73, 0.41))
    legs.append(ROOT.TLegend(0.2, 0.15, 0.3, 0.25))
for l in legs:
    l.SetTextFont(133)
    l.SetTextSize(25)
    l.SetFillStyle(0)
    l.SetBorderSize(0)
if True:
    legs[0].SetTextColor(ROOT.kOrange-1)
    legs[1].SetTextColor(ROOT.kBlue)
    legs[2].SetTextColor(ROOT.kGreen-1)
    legs[3].SetTextColor(ROOT.kBlack)
    legs[4].SetTextColor(6)
    legs[5].SetTextColor(ROOT.kBlue)
    legs[6].SetTextColor(ROOT.kGreen + 1)
    if band:
        legs[7].SetTextColor(ROOT.kBlue - 8)
    else:
        legs[7].SetTextColor(ROOT.kBlack)
    legs[8].SetTextColor(ROOT.kRed)
legs[0].AddEntry(edelLim, "#font[132]{EDELWEISS}", "")
#legs[1].AddEntry("xenonLim", "XENON100", "") #2014 XENON
legs[2].AddEntry("xmassLim", "XMASS", "")
legs[3].AddEntry("alpLim", "M#scale[0.7]{AJORANA} PRL", "")
legs[4].AddEntry("cdexLim", "CDEX", "")
legs[5].AddEntry("xenonPo", "XENON100", "") #XENON Erratum, use this
legs[6].AddEntry("lux", "LUX", "")
if band:
    legs[7].AddEntry("mjdProj", "DS0-6 Projection", "")
else:
    legs[7].AddEntry("mjdProj0", "M#scale[0.7]{AJORANA} Projected Sensitivity", "")
    #legs[7].AddEntry("mjdProj0", "  4106 kg-d, 0.01 c/keV/kg/d", "l")
    legs[7].AddEntry("mjdProj1", "11395 kg-d, 0.01 c/keV/kg/d", "l")
legs[8].AddEntry("pandaxII", "PandaX-II", "")

leg = ROOT.TLegend(0.6, 0.18, 0.8, 0.38)
leg.SetTextFont(133)
leg.SetTextSize(20)
leg.SetFillStyle(0)
leg.AddEntry("edelLim", "EDELWEISS", "l")
#leg.AddEntry("xenonLim", "XENON100", "l") #2014 XENON
leg.AddEntry("xmassLim", "XMASS", "l")
leg.AddEntry("alpLim", "MAJORANA", "l")
leg.AddEntry("cdexLim", "CDEX", "l")
leg.AddEntry("xenonPo", "XENON100", "l") #XENON Erratum, use this
leg.AddEntry("lux", "LUX", "l")
leg.AddEntry("mjdProj", "DS0-6 Projection", "l")
leg.AddEntry("pandaxII", "PandaX-II", "l")

if True:
    for i, l in enumerate(legs):
        if i != 1:
            l.Draw()
else:
    leg.Draw()

canvas.Update()
raw_input()

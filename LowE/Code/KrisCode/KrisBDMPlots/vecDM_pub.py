#!/usr/bin/python

import sys, os, re, glob, ROOT, array
import numpy as np

ds0_scale_min = 6.2
#ds0_scale_max = 10.7
ds0_scale_max = 9.1

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetLabelFont(132, "XYZ")
ROOT.gStyle.SetTitleFont(132, "XYZ")
ROOT.gStyle.SetLineWidth(2)
ROOT.gROOT.ForceStyle()

def read_CSV(fname):
    csv = np.genfromtxt (fname, delimiter=",")
    x = csv[:,0]
    y = csv[:,2]
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
        s = np.log10(float(sline[1].split('e')[0]))
        y.append(float(sline[1].split('e')[1]) + s)
    f.close()
    x, y =(list(z) for z in zip(*sorted(zip(x, y), key=lambda pair: pair[0])))
    for i in xrange(1, len(x)-1):
        y[i] = (y[i-1] + y[i] + y[i+1]) / 3
    return ROOT.TGraph(len(x), np.array(x), np.array(y))


canvas = ROOT.TCanvas("canvas", "canvas", 1200, 800)
canvas.SetTopMargin(.095)

zoom = True
amax = -14.0
if zoom:
    amax = -22.0
hist = ROOT.TH2D("hist", "", 100, 0.0, 100.0, 100, -30.0, amax)
hist.SetXTitle("m_{V} (keV)")
hist.SetYTitle("log(#alpha'/#alpha)")
hist.GetXaxis().SetTitleOffset(1.2)
hist.Draw()


xHB = [1.53586, 1.7063, 1.89563, 2.29397, 2.48674, 2.40192, 2.53481, 2.50098, 2.56909, 2.67587, 2.64019, 2.74929, 2.71265, 2.71203, 3.17346, 2.78639, 3.40163, 3.5669, 3.90419, 4.38355, 4.75172, 5.41096, 5.77437, 7.23314, 8.48879, 10.2422, 12.3866, 13.9017, 15.5198, 16.712, 18.5842, 20.6643, 22.9679, 25.5184, 28.3637, 31.5386, 35.0546, 39.0622, 43.5885, 47.4308, 49.7997, 100]

yHB = [-29.22647026, -29.36985395, -29.52470226, -29.79617055, -28.83410902, -29.89556752, -29.21915796, -29.37201796, -29.06629865, -28.35548657, -28.50070341, -27.93129478, -28.07268868, -28.21027055, -27.63927219, -27.79754165, -27.46831293, -27.28814471, -27.13024041, -26.99426196, -26.83603997, -26.69492607, -26.54273745, -26.43714827, -26.31745422, -26.19175593, -26.04482187, -25.89208149, -25.74993392, -25.64190518, -25.50271228, -25.36953246, -25.24157488, -25.1036579, -24.96267312, -24.82585584, -24.69343988, -24.53445506, -24.38333862, -24.25703698, -24.09918242, -23.32]

#RG stars
xRG = [3.02187, 4.36391, 8.41105, 13.1421, 16.2136, 17.0866, 20.5049, 22.8256, 24.0703, 26.0635, 30.5411, 37.7272, 47.8477, 65.7065, 83.412]
yRG = [-27.65483415, -27.95984088, -28.53932161, -28.89009088, -29.04261255, -29.1188374, -30.1094348, -28.84474293, -28.52477932, -28.09816476, -27.59541257, -26.97079079, -26.31570953, -25.24925254, -24.01512494]

#Gamma BG
xGamma = [13.62614577, 14.32610507, 15.02606438, 15.84268356, 16.54264287, 17.24260217, 17.94256148, 18.75918067, 19.69245974, 20.62573881,
          21.55901789, 22.49229696, 23.42557603, 24.35885511, 25.40879406, 26.45873302, 27.50867198, 28.67527082, 29.84186966, 31.12512838,
           32.52504699, 33.9249656, 35.32488421, 36.72480282, 38.12472143, 39.52464004, 40.92455865, 42.32447726, 43.72439587, 45.12431448,
           46.52423309, 47.9241517, 49.32407031, 50.72398892, 52.12390752, 53.52382613, 54.92374474, 56.32366335, 57.72358196, 59.12350057,
           60.52341918, 61.92333779, 63.3232564, 64.72317501, 66.12309362, 67.52301223, 68.92293084, 70.32284945, 71.72276806, 73.12268667,
           74.52260527, 75.92252388, 77.32244249, 78.60570122, 80.12227971, 81.52219832, 82.92211693, 84.32203554, 85.72195415, 87.12187276,
           88.52179137, 89.92170998, 91.32162859, 92.7215472, 94.12146581, 95.52138442, 96.92130303, 98.32122163, 99.72114024, 102.7542972,
           104.1542158, 105.5541344, 106.9540531, 108.3539717, 109.7538903, 111.1538089, 112.5537275, 113.9536461, 115.3535647, 116.7534833,
           118.1534019, 119.4366607]

yGamma = [-15.04414175, -15.23040925, -15.43902885, -15.62405457, -15.7929371, -15.96181963, -16.13070216, -16.3219368, -16.515655, -16.7093732,
          -16.90309139, -17.08190819, -17.26072499, -17.43209109, -17.60792761, -17.78227399, -17.95065981, -18.12053577, -18.28743145, -18.45283699,
            -18.61426882, -18.78315135, -18.95203388, -19.11594928, -19.24757832, -19.37424022, -19.50090212, -19.63253115, -19.74180808, -19.84611788,
            -19.94546055, -20.04480321, -20.14414588, -20.23355428, -20.32296268, -20.40988751, -20.48936164, -20.57628648, -20.65079348, -20.72530048,
            -20.79980748, -20.87183091, -20.94385434, -21.01091064, -21.07299981, -21.13508897, -21.19717814, -21.25678374, -21.31142221, -21.36606067,
            -21.42814984, -21.48278831, -21.53494321, -21.57964741, -21.63676944, -21.68644077, -21.73859567, -21.7808163, -21.8329712, -21.88015897,
            -21.92486317, -21.96956737, -22.01427157, -22.05897577, -22.1086471, -22.1459006, -22.1906048, -22.23034187, -22.28249677, -22.38929013,
            -22.4215765, -22.44641217, -22.4886328, -22.5482384, -22.5929426, -22.6376468, -22.67986743, -22.72953877, -22.77424297, -22.8239143,
            -22.8760692, -22.91878655]

#Abundance
xAbun = [6.509892836, 7.793151561, 9.19307017, 10.59298878, 11.99290739, 13.392826, 14.79274461, 16.19266322, 17.59258183, 18.99250044, 20.39241905, 21.79233765, 23.19225626, 24.59217487, 25.99209348, 27.39201209, 28.7919307, 30.19184931, 31.59176792, 32.99168653, 34.39160514, 35.79152375, 37.19144236, 38.59136097, 39.99127958, 41.39119819, 42.7911168, 44.1910354, 45.59095401, 46.99087262, 48.39079123, 49.79070984, 51.19062845, 52.59054706, 53.99046567, 55.39038428, 56.79030289, 58.1902215, 59.59014011, 60.99005872, 62.38997733, 63.78989594, 65.18981455, 66.58973316, 67.98965176, 69.38957037, 70.78948898, 72.18940759, 73.5893262, 74.98924481, 76.38916342, 77.78908203, 79.18900064, 80.58891925, 81.98883786, 83.38875647, 84.78867508, 86.18859369, 87.5885123, 88.98843091, 90.38834951, 91.78826812, 93.18818673, 94.58810534, 95.98802395, 97.38794256, 98.5545414, 100.8877391, 102.2876577, 103.6875763, 105.0874949, 106.4874135, 107.8873321, 109.2872507, 110.6871694, 112.087088, 113.5570025, 114.8869252, 116.2868438, 117.6867624, 118.7367014]

yAbun = [-19.54808988, -19.74180808, -19.91814131, -20.06467175, -20.19630078, -20.31302841, -20.41485464, -20.51171374, -20.59863858, -20.67811271, -20.75013614, -20.81470888, -20.87431448, -20.93640364, -20.98607497, -21.03574631, -21.08045051, -21.12267114, -21.16737534, -21.20214527, -21.24684947, -21.28161941, -21.31887291, -21.35115927, -21.38096207, -21.41324844, -21.43560054, -21.46540334, -21.49272257, -21.52004181, -21.54487747, -21.56971314, -21.5945488, -21.6169009, -21.64173657, -21.6616051, -21.68644077, -21.71127644, -21.73114497, -21.75598064, -21.7733656, -21.7957177, -21.8180698, -21.83793834, -21.86029044, -21.88015897, -21.89754394, -21.9149289, -21.937281, -21.9596331, -21.97701807, -21.99440304, -22.0192387, -22.03165654, -22.05152507, -22.0713936, -22.08381144, -22.11113067, -22.12603207, -22.14093347, -22.16576914, -22.1757034, -22.20053907, -22.21047334, -22.235309, -22.2725625, -22.28994747, -22.29739817, -22.31229957, -22.33465167, -22.35700377, -22.36693803, -22.384323, -22.40419153, -22.4215765, -22.4364779, -22.48664595, -22.49359993, -22.49856707, -22.5109849, -22.52836987]

#XMASS_Old
#xXMASS = [41.12882593, 43.56811332, 46.00740071, 48.4466881, 50.88597549, 53.32526288, 58.20383765, 60.64312504, 63.08241243, 65.59099776, 67.9748468, 70.4002746, 72.83956199, 75.27884937, 77.71813676, 80.15742415, 82.59671154, 85.03599893, 87.47528632, 89.91457371, 92.35386109, 94.79314848, 97.23243587, 99.67172326, 102.0186134, 104.550298, 114.3074476, 116.746735, 119.0325008]

#yXMASS = [-25.08524599, -25.09453321, -25.09538511, -25.11627088, -25.11712278, -25.12535558, -25.1428756, -25.13212894, -25.08342336, -25.04412781, -24.995835, -24.9499596, -24.90336285, -24.85782051, -24.81122376, -24.76146377, -24.69272432, -24.62293045, -24.55313658, -24.48439713, -24.41565768, -24.34586381, -24.27606994, -24.20310607, -24.16479212, -24.12468113, -23.96483023, -23.94933285, -23.87704707]

#XMASS_New
xXMASS = [40.0, 42.5, 45.1, 47.5, 50.0, 52.4, 53.7, 54.9, 57.3, 60.0, 62.6, 64.7, 67.5, 69.7, 72.4, 75.2, 79.1, 82.2, 84.9, 87.3, 92.4, 95.0, 99.1, 102.8, 104.8, 109.3, 111.9, 115.1, 117.8, 120.0]

yXMASS = [-26.63, -26.67, -26.59, -26.41, -26.31, -26.30, -26.30, -26.31, -26.42, -26.53, -26.45, -26.24, -26.09, -26.09, -26.24, -26.23, -25.94, -25.76, -25.67, -25.64, -25.79, -25.84, -25.86, -25.84, -25.76, -25.46, -25.31, -25.32, -25.29, -25.27]

#XENON100 Pospo
xXENON = [1.07037, 1.41133, 1.78919, 2.26821, 2.72807, 3.03196, 3.695, 4.44405, 5.1013, 5.27077, 6.0938, 6.59663, 7.38048, 7.73028, 7.83515, 8.26133, 8.82609, 9.63048, 10.6188, 13.8201, 14.7649, 15.7742, 17.3023, 18.7303, 19.7497, 20.8233, 22.5415, 24.7254, 26.7659, 28.8283, 29.8196, 31.3821, 34.3794, 35.7799, 36.0486]

yXENON = [-29.04572757, -29.06670713, -28.95990424, -28.85309713, -28.71577687, -28.55811485, -28.42015812, -28.2914202, -28.50598323, -28.65322077, -28.51361203, -28.34959047, -28.1436107, -28.01391921, -27.82828232, -27.65281835, -27.4837106, -27.29985465, -27.15566823, -27.0889154, -26.92044253, -26.75133781, -26.58477283, -26.40930749, -26.21540695, -26.06092176, -25.89817047, -25.72334292, -25.55359954, -25.38957834, -25.21946595, -25.02637023, -25.56617898, -25.41246526, -24.97338503]

xXenonME = [1.298, 1.393, 1.495, 1.604, 1.721, 1.847, 1.983, 2.128, 2.283, 2.451, 2.63, 2.822, 3.029, 3.251, 3.489, 3.744, 4.018, 4.312, 4.554, 4.733, 4.998, 5.364, 5.757, 6.178, 6.63, 7.115, 7.636, 8.195, 8.794, 9.438, 10.129, 10.87, 11.666, 12.52, 13.436, 14.419, 15.474, 16.607, 17.822, 19.127, 20.526, 22.029, 23.641, 25.371, 27.228, 29.221, 31.359, 33.654, 35.542, 37.536, 39.515]

yXenonME = [-27.97960438, -27.90034184, -27.81564247, -27.74878284, -27.68193414, -27.59814565, -27.49854562, -27.43196761, -27.36565075, -27.28841871, -27.20186875, -27.08742127, -26.97576806, -26.90113865, -26.83108469, -26.74847262, -26.67456631, -26.60084952, -26.64402596, -26.84390002, -26.97419232, -27.00513365, -26.98528594, -26.86632994, -26.72875777, -26.53877076, -26.32745921, -26.11571161, -25.9378961, -25.76345137, -25.61124739, -25.50490676, -25.42614954, -25.36192292, -25.31209625, -25.26536443, -25.23703688, -25.22927385, -25.18105437, -25.0968575, -24.99469723, -24.91209318, -24.81841407, -24.70662221, -24.57218831, -24.39609822, -24.24324898, -24.0884132, -24.2022062, -24.27597624, -24.06646723]

#MJD DS0
xDMlist = [5.6,5.8,6,6.2,6.4,6.6,6.8,7,7.2,7.4,7.6,7.8,8,8.2,8.4,8.6,8.8,9,9.2,9.4,9.6,9.8,10,10.2,10.4,10.6,10.8,11,11.2,
            11.4,11.6,11.8,12,12.2,12.4,12.6,12.8,13,13.2,13.4,13.6,13.8,14,14.2,14.4,14.6,14.8,15,15.2,15.4,15.6,15.8,16,16.2,16.4,16.6,
            16.8,17,17.2,17.4,17.6,17.8,18,18.2,18.4,18.6,18.8,19,19.2,19.4,19.6,19.8,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,
            36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,
            77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93]
    
yDMlist = [-26.88529995, -26.62443508, -26.53764763, -26.51133066, -26.58901855, -26.67780135, -26.76170195, -26.73518949, -26.73845137, -26.94935902, -26.87101871, -26.61255094, -26.53138881, -26.51022593, -26.36588593, -26.04860907, -25.92523435, -25.9198428, -26.09192876, -26.52764999, -26.7061194, -26.64070892, -26.22500921, -25.53307579, -25.49034622, -25.75989185, -25.9270251, -25.99917683, -26.10031886, -26.70996133, -26.82233132, -27.01130618, -27.00408904, -26.90676012, -26.908128, -26.91819186, -26.76405669, -26.62812351, -26.80538301, -26.91774731, -26.68137167, -26.39895212, -26.28054663, -26.25293464, -26.31369446, -26.57556194, -26.7208631, -26.53620705, -26.22573433, -26.08457428, -26.06095319, -26.20459517, -26.47749424, -26.53319822, -26.54946121, -26.67744388, -26.61006457, -26.2838127, -26.19851913, -26.24495965, -26.0072461, -25.91288867, -25.95179258, -25.99864675, -25.91936948, -25.90152513, -25.9788944, -25.97746554, -25.81110288, -25.75215987, -25.8309901, -26.09360385, -26.11903319, -25.70961755, -25.87245211, -25.35942329, -25.76978317, -25.6800973, -25.39220461, -25.45742172, -25.3455801, -25.17773034, -25.71931108, -25.65576297, -25.27728977, -25.02265143, -24.88573906, -25.23299669, -24.56839002, -25.25113422, -24.66234084, -25.16534472, -24.74193322, -25.05104506, -25.01868295, -24.58217444, -24.89847293, -24.85202443, -24.24396451, -24.81590877, -24.60547374, -24.2470059, -24.61947302, -24.30638112, -24.49201115, -24.12566974, -24.43657696, -24.43631743, -24.63967596, -23.91412965, -24.43325075, -24.4218254, -24.35653623, -23.9031709, -24.38954499, -24.06404088, -24.18752571, -24.32665802, -24.15787829, -23.53310352, -24.18705866, -23.94480315, -23.95326188, -23.68068819, -24.1436762, -23.99129615, -24.02765461, -23.51934089, -23.67400745, -24.00840396, -23.36861082, -23.95730235, -23.742397, -23.61011583, -23.57228357, -23.48838089, -23.42436301, -23.47918691, -23.1998109, -23.01760517, -23.64895643, -23.44640986, -23.47556318, -23.2363397, -23.30208178, -22.84640553]

band = False
yDMsmooth = []
yDMsmooth.append((yDMlist[0]+yDMlist[1])/2)
yDMsmooth.append((yDMlist[0]+yDMlist[1]+yDMlist[2])/3)
for i in xrange(2, len(xDMlist)-2):
    yDMsmooth.append(sum(yDMlist[i-2:i+3])/5)
yDMsmooth.append((yDMlist[-3]+yDMlist[-2]+yDMlist[-1])/3)
yDMsmooth.append((yDMlist[-2]+yDMlist[-1])/2)
xMJDProj = np.array(xDMlist)
yMJDProj = np.array(yDMsmooth) - np.log10(ds0_scale_min)
for i in xrange(len(xDMlist)):
    xMJDProj = np.append(xMJDProj, [xDMlist[-(i+1)]])
    yMJDProj = np.append(yMJDProj, [yDMsmooth[-(i+1)] - np.log10(ds0_scale_max)])
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

#EdelweissIII
edelLim = read_CSV("EdelweissIIIVector.csv")
edelLim.SetName("edelLim")
edelLim.SetLineColor(ROOT.kOrange-1)
edelLim.SetMarkerStyle(0)
edelLim.SetLineWidth(2)

#HB Stars
hbLim = ROOT.TGraph(len(xHB), np.array(xHB), np.array(yHB))
hbLim.SetName("hbLim")
hbLim.SetLineColor(ROOT.kBlue)
hbLim.SetLineStyle(ROOT.kDashed)
hbLim.SetLineWidth(2)

#RG Stars
rgLim = ROOT.TGraph(len(xRG), np.array(xRG), np.array(yRG))
rgLim.SetName("rgLim")
rgLim.SetLineColor(ROOT.kGreen + 1)
rgLim.SetLineStyle(ROOT.kDashed)
rgLim.SetLineWidth(2)

#Gamma BG
gammaLim = ROOT.TGraph(len(xGamma), np.array(xGamma), np.array(yGamma))
gammaLim.SetName("gammaLim")
gammaLim.SetLineColor(ROOT.kRed + 2)
gammaLim.SetLineStyle(ROOT.kDashed)
gammaLim.SetLineWidth(2)

#Abundance
abun = ROOT.TGraph(len(xAbun), np.array(xAbun), np.array(yAbun))
abun.SetName("abundance")
abun.SetLineColor(ROOT.kRed)
abun.SetLineStyle(ROOT.kDashed)
abun.SetLineWidth(2)

#XMASS
xmass = ROOT.TGraph(len(xXMASS), np.array(xXMASS), np.array(yXMASS))
xmass.SetName("xmass")
xmass.SetLineColor(ROOT.kGreen - 1)

#XENON
#xenon = ROOT.TGraph(len(xXENON), np.array(xXENON), np.array(yXENON))
xenon = read_datathief("xenon100_vector_9_2017.txt")
xenon.SetName("xenon")
xenon.SetLineColor(6)
#xenon.SetLineStyle(ROOT.kDashed)

#XENON Me
xenonMe = ROOT.TGraph(len(xXenonME), np.array(xXenonME), np.array(yXenonME))
xenonMe.SetName("xenonMe")
xenonMe.SetLineColor(ROOT.kBlack)

#DS0 graph
vecLim  = ROOT.TGraph(len(xDMlist), np.array(xDMlist), np.array(yDMlist))
vecLim.SetName("vecLim")
vecLim.SetTitle("; m_{V} (keV); log(#alpha'/#alpha)")
vecLim.SetLineColor(ROOT.kBlack)
vecLim.SetMarkerStyle(0)
vecLim.SetLineWidth(3)

if band:
    mjdProj.Draw("same F")
else:
    #mjdProj0.Draw("L same")
    mjdProj1.Draw("L same")
vecLim.Draw("L same")
#hbLim.Draw("L same")
#rgLim.Draw("L same")
if not zoom:
    gammaLim.Draw("L same")
    abun.Draw("L same")
xmass.Draw("L same")
xenon.Draw("L same")
edelLim.Draw("L same")
#xenonMe.Draw("same")

legs = []
if not zoom:
    legs.append(ROOT.TLegend(0.5, 0.40, 0.6, 0.50))
    legs.append(ROOT.TLegend(0.3, 0.35, 0.4, 0.45))
    legs.append(ROOT.TLegend(0.23, 0.75, 0.33, 0.85))
    legs.append(ROOT.TLegend(0.15, 0.58, 0.25, 0.68))
    legs.append(ROOT.TLegend(0.8, 0.3, 0.9, 0.4))
    legs.append(ROOT.TLegend(0.1, 0.35, 0.2, 0.45))
    legs.append(ROOT.TLegend(0.3, 0.13, 0.4, 0.23))
    legs.append(ROOT.TLegend(0.15, 0.14, 0.25, 0.24))
    #legs.append(ROOT.TLegend(0.59, 0.65, 0.85, 0.85))
    if band:
        legs.append(ROOT.TLegend(0.62, 0.28, 0.72, 0.38))
    else:
        legs.append(ROOT.TLegend(0.55, 0.18, 0.75, 0.28))
else:
    legs.append(ROOT.TLegend(0.5, 0.73, 0.6, 0.83))
    legs.append(ROOT.TLegend(0.25, 0.6, 0.35, 0.7))
    legs.append(ROOT.TLegend(0.23, 0.75, 0.33, 0.85))
    legs.append(ROOT.TLegend(0.15, 0.6, 0.25, 0.7))
    legs.append(ROOT.TLegend(0.8, 0.50, 0.9, 0.60))
    legs.append(ROOT.TLegend(0.1, 0.63, 0.2, 0.73))
    legs.append(ROOT.TLegend(0.3, 0.2, 0.4, 0.3))
    legs.append(ROOT.TLegend(0.15, 0.23, 0.25, 0.33))
    #legs.append(ROOT.TLegend(0.59, 0.65, 0.85, 0.85))
    if band:
        legs.append(ROOT.TLegend(0.62, 0.28, 0.72, 0.38))
    else:
        legs.append(ROOT.TLegend(0.55, 0.20, 0.75, 0.30))

legs[0].AddEntry("vecLim", "M#scale[0.7]{AJORANA} PRL", "")
legs[0].SetTextColor(ROOT.kBlack)
##legs[1].AddEntry("hbLim", "HB Stars", "")
##legs[1].SetTextColor(ROOT.kBlue)
if not zoom:
    legs[2].AddEntry("gammaLim", "#gamma BG", "")
    legs[2].SetTextColor(ROOT.kRed + 2)
    legs[3].AddEntry("abundance", "Abundance", "")
    legs[3].SetTextColor(ROOT.kRed)
legs[4].AddEntry("xmass", "XMASS", "")
legs[4].SetTextColor(ROOT.kGreen - 1)
legs[5].AddEntry("edelLim","Edelweiss", "")
legs[5].SetTextColor(ROOT.kOrange-1)
#legs[6].AddEntry("rgLim", "RG Stars", "")
#legs[6].SetTextColor(ROOT.kGreen + 1)
legs[7].AddEntry("xenon", "XENON100", "")
legs[7].SetTextColor(6)
#legs[7].AddEntry("xenonME", "XENON100*", "")
if band:
    legs[8].AddEntry("mjdProj", "DS0-6 Projection", "")
    legs[8].SetTextColor(ROOT.kBlue - 8)
else:
    legs[8].AddEntry("mjdProj0", "M#scale[0.7]{AJORANA} Projected Sensitivity", "")
    #legs[7].AddEntry("mjdProj0", "  4106 kg-d, 0.01 c/keV/kg/d", "l")
    legs[8].AddEntry("mjdProj1", "11395 kg-d, 0.01 c/keV/kg/d", "l")
    legs[8].SetTextColor(ROOT.kBlack)


for i, l in enumerate(legs):
    l.SetTextFont(133)
    l.SetTextSize(25)
    l.SetFillStyle(0)
    l.SetBorderSize(0)
    l.Draw()

canvas.Update()
raw_input()

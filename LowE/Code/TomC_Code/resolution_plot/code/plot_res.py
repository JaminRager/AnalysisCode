#!/usr/bin/env python

from chan_map import *
from exposure import *
from ROOT import *
import numpy as np

if __name__ == '__main__':

    gStyle.SetOptStat(0)
    gStyle.SetLabelFont(132, "XYZ")
    gStyle.SetTitleFont(132, "XYZ")
    gStyle.SetTitleOffset(1.2, "XYZ")

    datasets = ['0', '1', '2', '3', '4', '5a', '5b', '5c', '6']
    dsmap = ds_maps()
    ds_exp = []
    ds_expu = []
    for ds in datasets:
        ee, eu, ne, nu, m1, m2 = read_exposure(dsmap, ds)
        ds_exp.append(ee)
        ds_expu.append(eu)

    energy = [[] for d in datasets]
    resval = [[] for d in datasets]
    resunc = [[] for d in datasets]
    fres = open('../data/energy_resolution.txt')
    sds = ''
    efw = 0.0
    for line in fres:
        if line.find('DS') >= 0:
            sds = line.split()[0]
            continue
        if sds != '':
            if line.find("FWHM") >= 0:
                efw = float(line.split('{')[1].split('}')[0])
                energy[datasets.index(sds[2:len(sds)])].append(efw)
            elif efw != 0.0:
                v = float(line.split()[0])
                if efw > 0.0:
                    efw = -1.0
                    resval[datasets.index(sds[2:len(sds)])].append(v)
                else:
                    efw = 0.0
                    resunc[datasets.index(sds[2:len(sds)])].append(v)
    fres.close()

    h0 = 0.45
    h1 = 0.3
    h2 = 1 - h0 - h1
    emin =  200.0
    emax = 3000.0
    yoffset = 0.35
    
    E = energy[0]
    res = [0.0 for e in E]
    unc = [0.0 for e in E]
    for i in xrange(len(E)):
        for j in xrange(len(datasets)):
            res[i] += ds_exp[j] * resval[j][i] / sum(ds_exp)
            unc[i] += ds_exp[j] * pow(resunc[j][i], 2) / sum(ds_exp)
        unc[i] = pow(unc[i], 0.5)
        print res[i], unc[i]
    x = np.array(E, dtype=np.float64)
    y = np.array(res, dtype=np.float64)
    ux = np.array([2.0 for e in E], dtype=np.float64)
    uy = np.array(unc, dtype=np.float64)
    gres = TGraphErrors(len(x), x, y, ux, uy)
    gres.SetTitle('')
    hres = TH1F('hres', '', 100, emin, emax)
    hres.GetXaxis().SetRangeUser(emin, emax)
    hres.GetYaxis().SetRangeUser(-0.25, 3.75)
    hres.GetXaxis().SetTitle('Energy (keV)')
    hres.GetYaxis().SetTitle('FWHM (keV) ')
    hres.GetYaxis().SetTitleOffset(yoffset * h1 / h2)
    gres.SetHistogram(hres)
    gres.SetMarkerSize(1.5)
    gres.SetMarkerStyle(20)
    gres.SetMarkerColor(4)
    gres.SetLineColor(4)
    gres.SetLineWidth(1)
    rescale1 = gres.GetXaxis().GetLabelSize() / h1
    gres.GetXaxis().SetLabelSize(rescale1)
    gres.GetYaxis().SetLabelSize(rescale1)
    gres.GetXaxis().SetTitleSize(rescale1)
    gres.GetYaxis().SetTitleSize(rescale1)
    fres = TF1('fres', 'sqrt([0]+[1]*x+[2]*x*x)', emin, emax, 3)
    fres.SetParameter(0, 0.3)
    fres.SetParameter(1, 5e-3)
    fres.SetParameter(2, 5e-6)
    fres.SetLineColor(2)
    fres.SetLineWidth(1)
    gres.Fit(fres, 'QEMR+')
    res_roi = fres.Eval(2039.0)
    print pow(fres.GetParameter(0), 0.5)
    print pow(fres.GetParameter(1), 1)
    print pow(fres.GetParameter(2), 0.5)
    
    resid = [0.0 for e in E]
    for i in xrange(len(resid)):
        resid[i] = res[i] - fres.Eval(E[i])
    yr = np.array(resid, dtype=np.float64)
    gresid = TGraphErrors(len(x), x, yr, ux, uy)
    gresid.SetTitle('')
    hresid = TH1F('hresid', '', 100, emin, emax)
    hresid.GetXaxis().SetRangeUser(emin, emax)
    hresid.GetYaxis().SetRangeUser(-0.0055, 0.0055)
    hresid.GetXaxis().SetTitle('Energy (keV)')
    hresid.GetYaxis().SetTitle('Residual (keV)')
    hresid.GetYaxis().SetTitleOffset(yoffset)
    gresid.SetHistogram(hresid)
    gresid.SetMarkerSize(0.6)
    gresid.SetMarkerStyle(20)
    gresid.SetMarkerColor(4)
    gresid.SetLineColor(4)
    gresid.SetLineWidth(1)
    rescale2 = gresid.GetXaxis().GetLabelSize() / h2
    gresid.GetXaxis().SetLabelSize(rescale2)
    gresid.GetYaxis().SetLabelSize(rescale2)
    gresid.GetXaxis().SetTitleSize(rescale2)
    gresid.GetYaxis().SetTitleSize(rescale2)
    line = TLine()
    line.SetLineWidth(1)
    line.SetLineColor(1)
    line.SetLineStyle(2)

    tdir = gROOT.CurrentDirectory()
    sfile = TFile.Open('../data/energy_spectra_cal.root')
    sfile.cd('cut_comp/enr')
    scan = sfile.Get('cut_comp/enr/cenergy_cut_enr_' +
                     'ds012345a5b5c6_0100').Clone('cspec')
    gROOT.cd(tdir.GetPath())
    hspec = scan.FindObject('henergy_ds012345a5b5c6_both_enr_good_1_psd')
    hspec.GetXaxis().SetTitle('Energy (keV)')
    hspec.GetYaxis().SetTitle('c / keV / kg / day')
    hspec.GetXaxis().SetRangeUser(emin, emax)
    hspec.GetYaxis().SetRangeUser(2e-3, 2e5)
    hspec.GetYaxis().SetTitleOffset(yoffset * h0 / h2)
    hspec.SetLineWidth(1)
    hspec.SetLineColor(4)
    hspec.SetMarkerColor(4)
    rescale0 = hspec.GetXaxis().GetLabelSize() / h0
    hspec.GetXaxis().SetLabelSize(rescale0)
    hspec.GetYaxis().SetLabelSize(rescale0)
    hspec.GetXaxis().SetTitleSize(rescale0)
    hspec.GetYaxis().SetTitleSize(rescale0)
    y0 = []
    y1 = []
    for i in xrange(len(E)):
        y0.append(hspec.GetBinContent(hspec.FindBin(E[i])))
        y1.append(fres.Eval(E[i]))
    
    cres = TCanvas('cres', '', 0, 0, 2400, 1600)
    p0 = TPad('p0', '', 0.0, h1+h2, 1.0, 1.0)
    p0.SetTopMargin(0.2)
    p0.SetBottomMargin(0.0)
    p0.SetLeftMargin(0.1)
    p0.SetRightMargin(0.027)
    p0.Draw()
    p1 = TPad('p1', '', 0.0, h2, 1.0, h1+h2)
    p1.SetTopMargin(0.0)
    p1.SetBottomMargin(0.0)
    p1.SetLeftMargin(0.1)
    p1.SetRightMargin(0.027)
    p1.Draw()
    p2 = TPad('p2', '', 0.0, 0.0, 1.0, h2)
    p2.SetTopMargin(0.0)
    p2.SetBottomMargin(0.35)
    p2.SetLeftMargin(0.1)
    p2.SetRightMargin(0.027)
    p2.Draw()
    p0.cd()
    p0.cd().SetLogy(1)
    hspec.Draw('hist X+')
    line.SetLineColor(9)
    for i in xrange(len(E)): line.DrawLine(E[i], y0[i], E[i], 2e-3)
    p1.cd()
    gres.Draw('AP')
    line.SetLineColor(8)
    line.DrawLine(emin, res_roi, 2039.0, res_roi)
    line.DrawLine(2039.0, res_roi, 2039, -0.25)
    line.SetLineColor(9)
    for i in xrange(len(E)): line.DrawLine(E[i], 3.75, E[i], y1[i])
    p2.cd()
    gresid.Draw('AP')
    line.SetLineColor(1)
    line.DrawLine(emin, 0.0, emax, 0.0)
    cres.Update()
    cres.Print('../fig/energy_resolution.pdf')
    cres.Print('../fig/energy_resolution.C')
    
    raw_input()


    
        

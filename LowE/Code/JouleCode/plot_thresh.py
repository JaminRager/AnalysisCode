#!/usr/local/opt/python/bin/python2.7
#Originally written by Tom Caldwell for use on MJAM (original copy on MJAM in ~/mjusrs/tcald/plot_thresh.py )
#Modified by Gulden Othman for use on PDSF on 06/06/2017

import optparse
import os
import ROOT

if __name__ == '__main__':

    parser = optparse.OptionParser('%prog file [...]')
    parser.add_option('-o', type='str', dest='ornl', help='', default='')
    parser.add_option('-i', type='str', dest='infilename', help='',default='')
    parser.add_option('-f', type='int', dest='force', help='', default=0)
    options, args = parser.parse_args()
    if options.ornl[-1] != '/':
        options.ornl += '/'

    run = options.infilename[options.infilename.find('Run')+3:
                             len(options.infilename)]
    dname =  './run_data/'
    fname = 'run_data_for_plots_run' + run + '.dat'

    try:
        infile.close()
    except NameError:
        print 'computing thresholds for run ' + run
        os.system(options.ornl + '/sortrun ' +
                  options.infilename + ' > /dev/null 2>&1')
        try:
            os.system('mv run_data_for_plots.dat ' + dname + fname)
        except IOError:
            'failed to compute thresholds for run' + run
            exit()
    infile = open(dname + fname)

    ROOT.gStyle.SetLabelFont(132, 'XYZ')
    ROOT.gStyle.SetTitleFont(132, 'XYZ')
    ROOT.gStyle.SetOptStat(0)
    ROOT.gROOT.SetBatch(True)
        
    table0 = False
    table1 = False
    det0 = []
    thresh_hg = []
    thresh_lg = []
    det1 = []
    fwhm_hg = []
    fwhm_lg = []
    
    for line in infile:
        sline = line.split()
        if not table0 and len(det0) == 0:
            if line.find('ADC') >= 0:
                table0 = True
        elif table0:
            if len(sline) < 12:
                table0 = False
                continue
            det0.append(sline[-1])
            thresh_hg.append(float(sline[4]))
            thresh_lg.append(float(sline[9]))
        elif not table1 and len(det0) > 0:
            if line.find('ADC') >= 0:
                table1 = True
        elif table1:
            if len(sline) < 12:
                table1 = False
                continue
            det1.append(sline[-1])
            fwhm_hg.append(float(sline[4]))
            fwhm_lg.append(float(sline[11]))
    infile.close()
    h0 = ROOT.TH1D('hthresh_hg', '', len(det0), 0.0, len(det0))
    h0.SetTitle('#font[132]{Run ' + run + '}')
    h0.SetYTitle('Threshold (keV)')
    h0.SetMarkerStyle(20)
    h0.SetMarkerColor(4)
    h0.SetMarkerSize(1.2)
    h0.GetYaxis().SetTitleOffset(1.4)
    h1 = h0.Clone('hthresh_lg')
    h1.SetMarkerColor(2)
    for i, det in enumerate(det0):
        h0.GetXaxis().SetBinLabel(i+1, det)
        h1.GetXaxis().SetBinLabel(i+1, det)
        h0.SetBinContent(i+1, thresh_hg[i])
        h1.SetBinContent(i+1, thresh_lg[i])
    h2 = ROOT.TH1D('hfwhm_hg', '', len(det1), 0.0, len(det1))
    h2.SetYTitle('FWHM (keV)')
    h2.SetMarkerStyle(20)
    h2.SetMarkerColor(4)
    h2.SetMarkerSize(1.2)
    h2.GetYaxis().SetTitleOffset(1.4)
    h3 = h2.Clone('hfwhm_lg')
    h3.SetMarkerColor(2)
    for i, det in enumerate(det1):
        h2.GetXaxis().SetBinLabel(i+1, det)
        h3.GetXaxis().SetBinLabel(i+1, det)
        h2.SetBinContent(i+1, fwhm_hg[i])
        h3.SetBinContent(i+1, fwhm_lg[i])

    h0.LabelsOption('v')
    h1.LabelsOption('v')
    h2.LabelsOption('v')
    h3.LabelsOption('v')
    bline = ROOT.TLine()
    bline.SetLineColor(4)
    bline.SetLineWidth(2)
    bline.SetLineStyle(2)
    rline = ROOT.TLine()
    rline.SetLineColor(2)
    rline.SetLineWidth(2)
    rline.SetLineStyle(2)
    
    c = ROOT.TCanvas('c', '', 0, 0, 2000, 1000)
    c.Divide(2, 1)
    c.cd(1)
    h0.GetYaxis().SetRangeUser(min(min(thresh_hg), min(thresh_lg)) - 0.1,
                               max(max(thresh_hg), max(thresh_lg)) + 0.2)
    h0.Draw('p')
    h1.Draw('same p')
    l0 = ROOT.TLegend(0.78, 0.78, 0.88, 0.88)
    l0.SetLineColor(0)
    l0.SetFillColor(0)
    l0.AddEntry(h0, '#font[132]{LG}', 'p')
    l0.AddEntry(h1, '#font[132]{HG}', 'p')
    l0.Draw()
    bline.DrawLine(0.0, sum(thresh_hg) / len(thresh_hg),
                   len(thresh_hg) , sum(thresh_hg) / len(thresh_hg))
    rline.DrawLine(0.0, sum(thresh_lg) / len(thresh_lg),
                   len(thresh_lg), sum(thresh_lg) / len(thresh_lg))
    c.cd(2)
    h2.GetYaxis().SetRangeUser(min(min(fwhm_hg), min(fwhm_lg)) - 0.05,
                               max(max(fwhm_hg), max(fwhm_lg)) + 0.1)
    h2.Draw('p')
    h3.Draw('same p')
    l1 = ROOT.TLegend(0.78, 0.78, 0.88, 0.88)
    l1.SetLineColor(0)
    l1.SetFillColor(0)
    l1.AddEntry(h2, '#font[132]{LG}', 'p')
    l1.AddEntry(h3, '#font[132]{HG}', 'p')
    l1.Draw()
    bline.DrawLine(0.0, sum(fwhm_hg) / len(fwhm_hg),
                   len(fwhm_hg) , sum(fwhm_hg) / len(fwhm_hg))
    rline.DrawLine(0.0, sum(fwhm_lg) / len(fwhm_lg),
                   len(fwhm_lg), sum(fwhm_lg) / len(fwhm_lg))
    
    outfile = ROOT.TFile(dname + 'plot_thresh_' + run + '.root', 'recreate')
    outfile.cd()
    h0.Write()
    h1.Write()
    h2.Write()
    h3.Write()
    c.Write()
    outfile.Close()

    exit()

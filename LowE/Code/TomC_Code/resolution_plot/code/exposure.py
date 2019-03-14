#!/usr/bin/env python

from chan_map import *
#from ROOT import *

def read_exposure(dsmap, ds):
    chmap = dsmap.get_map(ds)
    enr_exp = 0.0
    enr_unc = 0.0
    nat_exp = 0.0
    nat_unc = 0.0
    m1_exp = 0.0
    m2_exp = 0.0
    try:
        f = open('../data/ds' + str(ds) + '_exposure.txt')
        iline = -1
        module = 0
        for line in f:
            if line.find('Module 1:') >= 0:
                module = 1
            elif line.find('Module 2:') >= 0:
                module = 2
            if line.find('Best Enr Exposure') >= 0:
                sline = line.split()
                try:
                    enr_exp += float(sline[4])
                    enr_unc += float(sline[6])
                    if module == 1:
                        m1_exp += float(sline[4])
                    elif module == 1:
                        m2_exp += float(sline[4])
                except ValueError:
                    enr_exp += float(sline[5])
                    enr_unc += float(sline[7])
                    if module == 1:
                        m1_exp += float(sline[5])
                    elif module == 2:
                        m2_exp += float(sline[5])
                continue
            elif line.find('Best Nat Exposure') >= 0:
                sline = line.split()
                try:
                    nat_exp += float(sline[4])
                    nat_unc += float(sline[6])
                    if module == 1:
                        m1_exp += float(sline[4])
                    elif module ==2:
                        m2_exp += float(sline[4])
                except ValueError:
                    nat_exp += float(sline[5])
                    nat_unc += float(sline[7])
                    if module == 1:
                        m1_exp += float(sline[5])
                    elif module ==2:
                        m2_exp += float(sline[5])
                continue
            if line.find('Detector summary with best') >= 0:
                iline = 0
                continue
            elif(iline >= 0 and line.find('Chan') >= 0):
                iline += 1
                continue
            if iline < 1:
                continue
            elif iline > 1:
                break
            else:
                sline = line.split()
                #print sline
                det = chmap.get_det('detID', int(sline[1]))
                det.add_data('mass',       float(sline[2]))
                det.add_data('runt',       float(sline[3]))
                det.add_data('livet',      float(sline[4]))
                det.add_data('exposure',   float(sline[5]))
                det.add_data('exp_uncert', float(sline[6]))
        f.close()
    except IOError:
        print 'DS' + str(ds), 'exposure not found'
    return enr_exp, enr_unc, nat_exp, nat_unc, m1_exp, m2_exp

def read_mass_uncert(dsmap):
    try:
        f = open('../data/mass_uncert.txt')
        for line in f:
            sline = line.split()
            err = float(sline[6])
            for chanmap in dsmap.maps:
                det = chanmap.get_det('pos', sline[0])
                try:
                    det.add_data('mass_uncert',
                                 det.get_value('mass') * err)
                except AttributeError:
                    continue
        f.close()
    except IOError:
        print 'active mass uncertainty file not found'

def read_containment(dsmap):
    try:
        f = open('../data/EnrEff.csv')
        for line in f:
            sline = line.split(',')
            try:
                pos='C'+sline[0][2]+'P'+sline[0][4]+'D'+sline[0][6]
                cont = float(sline[1])
                uncert = float(sline[2])
                for chanmap in dsmap.maps:
                    det = chanmap.get_det('pos', pos)
                    try:
                        det.add_data('cont', cont)
                        det.add_data('cont_uncert', uncert)
                    except AttributeError:
                        continue
            except ValueError:
                continue
        f.close()
    except IOError:
        print 'containment efficiency file not found'

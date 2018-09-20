#------
#First draft 03/21/2017 on MJAM
#Edited for use on PDSF 06/06/2017
#by Gulden Othman
#------
########################################
###This script makes use of ROOT Histograms of detector (name vs) thresholds and detector (name vs) FWHM values made by 
###Tom Caldwell's plot_thresh.py code (original copy on MJAM: ~/mjusrs/tcald/plot_thresh.py). The information in the histograms is obtained  
###by running David R's sortrun.c code (on MJAM: ~/ORNL/code/sortrun.c     on PDSF: $GATDIR/ORNLCode/sortrun.c). 
############## 
#Running this script will makes detector specific plots of run number vs threshold / run number vs FWHM
#and/or 2D histograms of all detectors vs threshold and all detectors vs FWHM
#########################################
#______________
#TO USE:
# 1. Create a directory on your own PDSF space, and copy this code along with Tom C's plot_thresh.py to that directory 
#    1a. Inside this drectory, create a directory called '/run_data/' and another called '/plots/'
#        (/run_data/ will store the output files of David's sortrun.c code, /plots/ will store the plots created by fwhm_plot.py)
# 2. On PDSF, find the directory $GATDIR/ORNLCode/ and copy ALL CONTENTS to your directory with fwhm_plot.py and plot_thresh.py
#    2a. in this directory, "make clean" then "make" to compile David R's sortrun.c code
# 3. Edit the low_run and high_run variables on this script to reflect the run range you are interested in plotting
#    NOTES: Depending on what DS you are intersted in, you will need to modify the -i flag directory (line  68) to where the 
#           raw data in the DS of interest lives.
#	        The high_run you specify is not inclusive, so if, for example, you want to plot up to run 200, high_run should be 201
# 4. Run this script (with the command 'python fwhm_plot.py') with the plotting function of interest uncommented (below main for loop)
# NOTE: Tom C's code does not work on transition runs, so those runs will be blank in the resulting plots
#The original intention is for this code to be a tool to determine what runs starting seeing more noise or
#higher thresholds, and cross-reference the run period with underground work or other external events. 
#______________

#______________________________________________________________________________________________________________________________________

import os
import collections as coll
import numpy as np 
import matplotlib.pyplot as plt
from ROOT import TFile, TH1D, TH2D, TCanvas, TLegend



def main():

	global low_run, high_run, run_range, thresh, fwhm, runs, runs2 

	#specify the run range of interest!!!!!!
	low_run = 22600
	high_run = 22605
	run_range = high_run- low_run
	
	#Since the detector names in the original histograms are strings, make a dictionary to keep each threshold value
	#or FWHM value tied to the detector name it's associated with.
	#Declare dictionary names:
	global thresh, fwhm, runs, runs2 
	thresh = {}
	fwhm = {}
	runs = {} 
	runs2 = {}

	## Begins by running Tom C's code, which in turn runs David's sortrun.c code and creates histograms of detector names vs FWHM and detector names vs Threshold
	## values, which are located in files of the structure plot_thresh_'run#'.root. Next, opens those root files and get the detector and threshold/FWHM information
	## from the histograms created in Tom C's code. Store the information in a dictionary, which will ultimately be used to make plots
    
    #####
	# REMINDER: You will need to modify the -i flag directory to where the raw data in the DS of interest lives!!!!!!!! 
	# the -o flag points to the directory where you have compiled the ORNLCode 
	#####

	for run in xrange(low_run, high_run):
		os.system('python plot_thresh.py -o ./ -i $MJDDATADIR/surfmjd/data/raw/P3LQK/Data/*P3LQK_Run' + str(run))
		f = TFile("./run_data/plot_thresh_" + str(run) + ".root")
		if f.IsZombie():     #Tom C.s code does not work on transition runs, so any transition run will be missing from 
			continue           #the specified run range. If that happens, continue to the next run in the loop
		thresh_hist = f.Get("hthresh_hg")       #get the (HG) threshold histogram
		fwhm_hist = f.Get("hfwhm_hg")           #get the (HG) FWHM histogram
		n = thresh_hist.GetNbinsX()             #number of bins (detecotrs)
		n2 = fwhm_hist.GetNbinsX()
		#Get detector names and threshold values and put them in the dictionary "thresh". Will have the format
		#thresh{} = {"Detector name": [threshold1, threshold2, ...], "Detector2 name": [threshold1, threshold 2...], etc }
		#also makes a dictionary of the corresponding run# (format: runs{} = {"Detector1 name": [run1, run2, ...], etc})          
		for i in range(1, n+1):
			label = thresh_hist.GetXaxis().GetBinLabel(i)       #label is the detector name (the "key" in the dictionary)
			#if this detector name is already in the dictionary, add the threshold value to the string associated with it
			#or else, add it to the dictionary, along with it's threshold as the value
			if label in thresh.keys():
				thresh[label].append(thresh_hist.GetBinContent(i))
				runs[label].append(run)
			else:
				thresh[label] = [thresh_hist.GetBinContent(i)]
				runs[label] = [run]
		#Get detector names and FWHM values and put them in the dictionary "fwhm". Will have the format
		#fwhm{} = {"Detector name": [FWHM1, FWHM2, ...], "Detector2 name": [FWHM1, FWHM2...], etc }
		#also makes a dictionary of the corresponding run# (format: runs2{} = {"Detector1 name": [run1, run2, ...], etc})
		for z in range(1, n2+1):
			label2 = fwhm_hist.GetXaxis().GetBinLabel(z)       #label2 is the detector name (the "key" in the dictionary)
			#if this detector name is already in the dictionary, add the fwhm value to the string associated with it
			#or else, add it to the dictionary, along with it's fwhm as the value
			if label2 in fwhm.keys():
				fwhm[label2].append(fwhm_hist.GetBinContent(z))
				runs2[label2].append(run)
			else:
				fwhm[label2] = [fwhm_hist.GetBinContent(z)]
				runs2[label2] = [run]
		f.Close()
	

	######
	# Uncomment the appropriate function(s) based on what you would like to plot
	#####
	# detectorSpecific_thresh() #Plot run v threshold for each detector on a separate plot
	# detectorSpecific_fwhm()   #Plot run v FWHM for each detector on a separate plot
	# allDetecors_thresh()      #Plot Histograms of all detectors and runs with the threshold as color
	allDetecors_fwhm()        #Plot Histograms of all detectors and runs with the FWHM as color

	

#_____________________________________________________________________________________________________________

#Create detector-specific threshold or FWHM plots, or plot the threshold or FWHM for all detectors on one plot

#_________________________

######plot (and save) the run number vs threshold and run numberfor each detector (detector-specific plots)
def detectorSpecific_thresh():
	print 'creating detector specific run vs threshold plots'
	for label in thresh:
		thresh_plot = plt.figure()
		ax = plt.subplot(111)
		plt.plot(runs[label], thresh[label], '.r')
		plt.title(label + ' Thresholds (HG)')
		plt.xlabel('Run Number')
		plt.ylabel('Threshold (keV)')
		plt.ylim(min(thresh[label])-0.002,max(thresh[label])+0.002)
		# plt.show()
	 	plt.savefig('./plots/' + label + '_thesholds_HG' + '.pdf')
	 	plt.close()

#______________________

#####Plot Histograms of all runs and detectors with the threshold as a color
def allDetecors_thresh():
	print 'creating 2D histogram of all detectors and threshold information'
	y = []
	sorted_thresh = coll.OrderedDict(sorted(thresh.items()))
	sorted_runs = coll.OrderedDict(sorted(runs.items()))

	m = np.empty((len(sorted_thresh), run_range))
	m.fill(0.0)

	for (i, label) in enumerate(sorted_thresh):
		y.append(label)
		for j in range(0, len(sorted_thresh[label])):
			m[i][(runs[label][j]-low_run)] = sorted_thresh[label][j]
				
	xbins = run_range
	ybins = len(y)
	c1 = TCanvas('c1')
	h = TH2D('h', '', xbins, low_run, high_run, ybins, 0.0, ybins)
	for (i,label) in enumerate(sorted_thresh):
		for j in range(0, run_range):
			h.SetBinContent(j+1, i+1, m[i,j])
		h.GetYaxis().SetBinLabel(i+1, y[i])
	h.SetStats(0)
	h.SetTitle('Detector Thresholds (keV)')
	h.SetXTitle("Run")
	h.Draw("colz")
	c1.Update
	c1.Print('./plots/allDet_Thresholds.pdf')

#__________________________
######plot (and save) the run number vs FWHM for each detector (detector-specific plots)
def detectorSpecific_fwhm():
	print 'creating detector specific run vs FWHM plots'
	for label2 in fwhm:
		fwhm_plot = plt.figure()
		ax2 = plt.subplot(111)
		plt.plot(runs2[label2], fwhm[label2], '.b')
		plt.title(label2 + ' FWHM (HG)')
		plt.xlabel('Run Number')
		plt.ylabel('FWHM (keV)')
		# plt.show()
		plt.savefig('./plots/'+ label2 + '_fwhm_HG' + '.pdf')
		plt.close()


def allDetecors_fwhm():
	print 'creating 2D histogram of all detectors and FWHM information'
	yf = []
	sorted_fwhm = coll.OrderedDict(sorted(fwhm.items()))
	sorted_runs2 = coll.OrderedDict(sorted(runs2.items()))

	mf = np.empty((len(sorted_fwhm), run_range))
	mf.fill(0.0)

	for (i, label2) in enumerate(sorted_fwhm):
		yf.append(label2)
		for j in range(0, len(sorted_fwhm[label2])):
			mf[i][(runs2[label2][j]-low_run)] = sorted_fwhm[label2][j]
	# print mf

	xfbins = run_range
	yfbins = len(yf)
	c2 = TCanvas('c2')
	hf = TH2D('hf', '', xfbins, low_run, high_run, yfbins, 0.0, yfbins)
	for (i,label) in enumerate(sorted_fwhm):
		for j in range(0, run_range):
			hf.SetBinContent(j+1, i+1, mf[i,j])
		hf.GetYaxis().SetBinLabel(i+1, yf[i])
	hf.SetStats(0)
	hf.SetTitle('Detector FWHM (keV)')
	hf.SetXTitle("Run")
	hf.Draw("colz")
	c2.Update
	c2.Print('./plots/allDet_FWHM.png')





if __name__ == '__main__':
	main()
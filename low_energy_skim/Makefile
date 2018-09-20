include $(MGDODIR)/buildTools/config.mk

# Give the list of applications, which must be the stems of cc files with 'main'.  There
# can be more than one.  In our example, this means there is a test.cc and a test1.cc
APPS = skim_mjd_data

# The next three lines are important
SHLIB =
ARCHIVE =
SOURCESSCRATCH = $(wildcard *.cc)
TAMDIR ?= $(ROOTSYS)
# Include the correct flags,
INCLUDEFLAGS = $(CLHEP_INCLUDE_FLAGS) -I$(MGDODIR)/Base -I$(MGDODIR)/Root -I$(MGDODIR)/Transforms
INCLUDEFLAGS += -I$(MGDODIR)/Majorana -I$(MGDODIR)/MJDB $(ROOT_INCLUDE_FLAGS) -I$(TAMDIR)/inc -I$(TAMDIR)/include -I$(MGDODIR)/Tabree
#INCLUDEFLAGS += -I../BaseClasses -I../MGTEventProcessing -I../MGOutputMCRunProcessing -I../Analysis -I../MJDAnalysis -I../DCProcs
LIBFLAGS = -L$(MGDODIR)/lib -lMGDORoot -lMGDOBase -lMGDOTransforms -lMGDOMajorana -lMGDOGerdaTransforms -lMGDOMJDB -lMGDOTabree
INCLUDEFLAGS += -I$(GATDIR)/Analysis -I$(GATDIR)/Apps -I$(GATDIR)/BaseClasses -I$(GATDIR)/buildTools -I$(GATDIR)/DCProcs -I$(GATDIR)/example -I$(GATDIR)/lib -I$(GATDIR)/MDStat -I$(GATDIR)/MGOutputMCRunProcessing -I$(GATDIR)/MGTEventProcessing -I$(GATDIR)/MJAMCode -I$(GATDIR)/MJBackgroundModel -I$(GATDIR)/MJDAnalysis -I$(GATDIR)/MJDApps -I$(GATDIR)/Apps -I$(GATDIR)/MJDCalibration -I$(GATDIR)/mjd-veto -I$(GATDIR)/ORNLCode -I$(GATDIR)/PFunc -I$(GATDIR)/Scripts -I$(GATDIR)/SiggenWrapper -I$(GATDIR)/tam
LIBFLAGS += -L$(GATDIR)/lib -lGATBaseClasses -lGATMGTEventProcessing -lGATMGOutputMCRunProcessing -lGATAnalysis -lGATMJDAnalysis -lGATDCProcs $(ROOT_LIB_FLAGS) -lSpectrum -lTreePlayer -L$(TAMDIR)/lib -lTAM
#ifdef SIGGENDIR
  #INCLUDEFLAGS += -I../SiggenWrapper -I$(SIGGENDIR)
  #LIBFLAGS += -lMGDOSiggenWrapper
  #APPS += siggen_test
  #ifeq (,$(findstring -DSIGGENDIR="$(SIGGENDIR)",$(CPPFLAGS)))
    #CPPFLAGS += -DSIGGENDIR
  #endif
  #else
  #SOURCESSCRATCH := $(filter-out siggen_test.cc, $(SOURCESSCRATCH))
#endif

include $(MGDODIR)/buildTools/BasicMakefile

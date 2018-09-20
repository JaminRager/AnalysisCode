include $(MGDODIR)/buildTools/config.mk

# Give the list of applications, which must be the stems of cc files with 'main'.  There
# can be more than one.  In our example, this means there is a test.cc and a test1.cc

# The next two lines are important
SHLIB = 
ARCHIVE = 
TAMDIR ?= $(ROOTSYS)
# Include the correct flags, 
INCLUDEFLAGS = $(CLHEP_INCLUDE_FLAGS) -I$(MGDODIR)/Base -I$(MGDODIR)/Root -I$(MGDODIR)/Transforms -I$(MGDODIR)/Tabree
INCLUDEFLAGS += -I$(MGDODIR)/Majorana $(ROOT_INCLUDE_FLAGS) -I$(TAMDIR)/inc -I$(TAMDIR)/include
INCLUDEFLAGS += -I$(GATDIR)/Analysis -I$(GATDIR)/BaseClasses -I$(GATDIR)/MGOutputMCRunProcessing -I$(GATDIR)/MGTEventProcessing -I$(GATDIR)/MJDAnalysis
INCLUDEFLAGS += -I$(MJSWDIR)/BaseClasses -I$(MJSWDIR)/MGTEventProcessing -I$(MJSWDIR)/MGOutputMCRunProcessing -I$(MJSWDIR)/Analysis -I$(MJSWDIR)/MJDAnalysis
LIBFLAGS = -L$(MGDODIR)/lib -lMGDORoot -lMGDOBase -lMGDOTransforms -lMGDOMajorana -lMGDOGerdaTransforms -lMGDOTabree
LIBFLAGS += -L$(GATDIR)/lib -lGATBaseClasses -lGATMGTEventProcessing -lGATMGOutputMCRunProcessing -lGATAnalysis -lGATMJDAnalysis $(ROOT_LIB_FLAGS) -lSpectrum -L$(TAMDIR)/lib -lTAM

INCLUDEFLAGS +=
LIBFLAGS += $(LDFLAGS) $(LIBS) $(CLHEP_LIB_FLAGS)

.PHONY: all bin

all: fitPWscript

fitPWscript: fitPWscript.cc

	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $(CPPFLAGS) $(LIBFLAGS) -o fitPWscript fitPWscript.cc

clean:
	rm fitPWscript

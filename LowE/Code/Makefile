include $(MGDODIR)/buildTools/config.mk
#include $(MGDODIR)/buildTools/BasicMakefile

# Give the list of applications, which must be the stems of cc files with 'main'.  There
# can be more than one.  In our example, this means there is a test.cc and a test1.cc

# The next two lines are important
SHLIB = 
ARCHIVE = 
#TAMDIR = /project/projectdirs/majorana/software/sl64/mjsw/mjsw201802Prod/MGDO/tam
#MGDODIR = /project/projectdirs/majorana/software/sl64/mjsw/mjsw201705Prod/MGDO
# Include the correct flags, 
INCLUDEFLAGS = $(CLHEP_INCLUDE_FLAGS) -I$(MGDODIR)/Base -I$(MGDODIR)/Root -I$(MGDODIR)/Transforms -I$(MGDODIR)/Tabree
INCLUDEFLAGS += -I$(MGDODIR)/Majorana $(ROOT_INCLUDE_FLAGS) -I$(TAMDIR)/inc -I$(TAMDIR)/include
INCLUDEFLAGS += -I$(GATDIR)/Analysis -I$(GATDIR)/BaseClasses -I$(GATDIR)/MGOutputMCRunProcessing -I$(GATDIR)/MGTEventProcessing -I$(GATDIR)/MJDAnalysis -I$(GATDIR)/Apps
INCLUDEFLAGS += -I$(MJSWDIR)/BaseClasses -I$(MJSWDIR)/MGTEventProcessing -I$(MJSWDIR)/MGOutputMCRunProcessing -I$(MJSWDIR)/Analysis -I$(MJSWDIR)/MJDAnalysis
LIBFLAGS = -L$(MGDODIR)/lib -lMGDORoot -lMGDOBase -lMGDOTransforms -lMGDOMajorana -lMGDOGerdaTransforms -lMGDOTabree
LIBFLAGS += -L$(GATDIR)/lib -lGATBaseClasses -lGATMGTEventProcessing -lGATMGOutputMCRunProcessing -lGATAnalysis -lGATMJDAnalysis $(ROOT_LIB_FLAGS) -lSpectrum -L$(TAMDIR)/lib -lTAM

INCLUDEFLAGS += 
LIBFLAGS += $(LDFLAGS) $(LIBS) $(CLHEP_LIB_FLAGS)

.PHONY: all bin

all:   data-cleaning5a

data-cleaning5a:   data-cleaning5a.cc
	$(CXX) $(CXXFLAGS) $(INCLUDEFLAGS) $(CPPFLAGS) $(LIBFLAGS) -o   data-cleaning5a   data-cleaning5a.cc

clean:
	rm   data-cleaning5a

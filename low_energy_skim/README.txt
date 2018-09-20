## Files ##
DataSetInfo.cc - this is the file you use to specify run ranges in current GAT versions.

DataSetInfo.hh - this used to be the file you used to specify run ranges in older GAT versions.

skim_mjd_data.cc - the skimmer. To compile and run the skimmer, you need to source EnvSetup.sh from the directory env in .bashrc.ext, and the correct environment variables have to be set in EnvSetup.sh.

Makefile - INCLUDEFLAGS must point to all the subdirectories within GATDIR that contain headder files referenced by the skimmer, by DataSetInfo.cc and by DataSetInfo.hh. If compiling fails and you get a log sequence of nonsense error messages, try "make clean"


## Directories ##
BadRuns - Contains DataSetInfo.hh for skimfiles associated with rejected runs from my first skimming.

Calibration - Contains DataSetInfo.hh for calibration runs.

junk - old code that I no longer use but keep around for reference.

new - Makefile, DataSetInfo.cc, DataSetInfo.hh and skim_mjd_data.cc for latest GAT version 201802

old - Makefile, DataSetInfo.hh and skim_mjd_data.cc for GAT version 201705

oldest - Very first version of skim_mjd_data.cc that I started using. I forget what GAT version it was associated with.

output - where output from skimmer (the skim files) are created


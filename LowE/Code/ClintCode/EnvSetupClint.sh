#!/bin/bash
# Now updated for bash! (7/20/16)
# Last update 03/08/18

echo "Hey Jamin, it's finding this file"

# Test for interactive shell
if [[ $- == *i* ]]; then

	export PS1="\[\033[38;5;14m\]\A\[$(tput sgr0)\]\[\033[38;5;15m\] \[$(tput sgr0)\]\[\033[38;5;10m\]\u@\h\[$(tput sgr0)\]\[\033[38;5;15m\]:\[$(tput bold)\]\[$(tput sgr0)\]\[\033[38;5;9m\]\W\[$(tput sgr0)\]\[$(tput sgr0)\]\[\033[38;5;15m\]\\$ \[$(tput sgr0)\]"

	if [ "${CHOS}" != "sl64" ]; then
		env CHOS=sl64 chos
	fi

	export HOMEDIR=/global/homes/j/jrager
	export SWDIR=/project/projectdirs/majorana/software/sl64
	export CXXFLAGS='-std=c++11'
	alias rootmj="root -b -l ~/env/rootlogon.C"
	alias qloginmj="qlogin -l h_vmem=2G -q mndl_prod.q"
	alias qsubmj="qsub -l h_vmem=2G -q mndl_prod.q"

        # MJ software version
	# Check for new versions in $SWDIR/mjsw
        # If you want to run a manual version:
        #   1. Uncomment MANUALSW   2. Comment out SETUP_MJSW****

	#export MJSWDIR=${SWDIR}/mjsw/mjsw201802Prod
	#export SETUP_MJSW201802PROD=true
        export MJSWDIR=${SWDIR}/mjsw/mjsw201807Prod
	export SETUP_MJSW201807PROD=true
        #export MANUALSW="Jamin is great"

	# The DTN's can't find these scripts, that's why there's an interactive check
	#source /etc/profile.d/modules.sh

	# run setup scripts
        source /project/projectdirs/majorana/setupMajorana.sh
	source /project/projectdirs/majorana/software/sl64/setupMajoranaSL64.sh

fi

# MANUAL SETUP --------------------------------------------------

# Choose custom ($HOMEDIR) or default ($MJSWDIR) installs of MJSW.
if [ -n "$MANUALSW" ]; then

	# ROOT --------------------------------------------------
	# Look for MJD's current ROOT version in:
	# /global/project/projectdirs/majorana/software/sl64/root

        #export ROOTSYS=${SWDIR}/root/root-6.08.02
	#source ${ROOTSYS}/bin/thisroot.sh
        #export ROOTSYS=${SWDIR}/root/root-6.08.06/install
        #export ROOTSYS=${SWDIR}/root/root-6.12.04/install
	#source ${ROOTSYS}/bin/thisroot.sh
	# -------------------------------------------------------

	# CLHEP -------------------------------------------------
	# Look for MJD's current CLHEP version in:
	# /global/project/projectdirs/majorana/software/sl64/CLHEP
	#export CLHEP_BASE_DIR=${HOMEDIR}/mgsw/CLHEP/2.3.2.2/install
        #export CLHEP_BASE_DIR=${SWDIR}/CLHEP/2.3.4.4/CLHEP
	#export CLHEP_BASE_DIR=${SWDIR}/CLHEP/2.4.0.1/CLHEP
	#export CLHEP_INCLUDE_DIR=${CLHEP_BASE_DIR}/include
	#export CLHEP_LIB_DIR=${CLHEP_BASE_DIR}/lib
	#export CLHEP_LIB=CLHEP
	#export PATH=$CLHEP_BASE_DIR/bin:${PATH}
	#export LD_LIBRARY_PATH=${CLHEP_LIB_DIR}:${LD_LIBRARY_PATH}
	# -------------------------------------------------------

	# MJSW --------------------------------------------------

	#export MGDODIR=${HOMEDIR}/mgsw/MGDO
	#export MJORDIR=${HOMEDIR}/mgsw/MJOR
	#export GATDIR=${HOMEDIR}/mgsw/GAT
	#export ORDIR=${HOMEDIR}/mgsw/OrcaRoot
	#export COOKIEDIR=${HOMEDIR}/mgsw/MGDO/MJDB/Apps/Cookies
	#export PATH=${COOKIEDIR}:${PATH}

        export MGDODIR=${MJSWDIR}/MGDO
	export GATDIR=${MJSWDIR}/GAT
        export MJORDIR=${MJSWDIR}/MJOR
	export ORDIR=${MJSWDIR}/OrcaRoot
        export MAGEDIR=${MJSWDIR}/MaGe

	export TAMDIR=${MGDODIR}/tam
	export PATH=$MGDODIR/install/bin:$MGDODIR/install/lib:$MJSWDIR/bin:$ORDIR/Applications:${MJORDIR}:${PATH}
	export PATH=${GATDIR}/Analysis:${GATDIR}/Apps:${GATDIR}/BaseClasses:${GATDIR}/DCProcs:${GATDIR}/MGTEventProcessing:${GATDIR}/MGTOutputMCRunProcessing:${GATDIR}/MJDAnalysis:${GATDIR}/Scripts:${PATH}
	#export LD_LIBRARY_PATH=${MJSWDIR}/lib:${MGDODIR}/install/lib:${TAMDIR}/lib:${ORDIR}/lib:${GATDIR}/lib:${LD_LIBRARY_PATH}
	export LD_LIBRARY_PATH=${MJSWDIR}/lib:${MGDODIR}/lib:${TAMDIR}/lib:${ORDIR}/lib:${GATDIR}/lib:${LD_LIBRARY_PATH}
	export ROOT_INCLUDE_PATH=$MGDODIR/Base:$MGDODIR/Gerda:$MGDODIR/GerdaTransforms:$MGDODIR/Majorana:$MGDODIR/MJDB:$MGDODIR/Root:$MGDODIR/Tabree:$MGDODIR/Tools:$MGDODIR/Transforms:$TAMDIR/inc:$MGDODIR/tam:$CLHEP_BASE_DIR/CLHEP/lib:${GATDIR}/BaseClasses:${GATDIR}/MGOutputMCRunProcessing
	# -------------------------------------------------------
fi

# Nukes current installs and starts from master branches.
function nukemgsw()
{
  cd $MGDODIR
  git pull upstream master

  cd $GATDIR
  git pull upstream master

  cd $MGDODIR
  make uninstall
  make clean
  ./configure --prefix=`pwd`/install --enable-majorana-all
  make
  make install

  cd $GATDIR
  make clean
  cd $GATDIR/MJDCalibration
  make clean
  make
  cd ..
  make
}

# Run a single run through the skim-clean routine.
function processCal()
{
  dsNum=$1
  runNum=$2
  ./skim_mjd_data -n -l -t 0.5 -f $runNum
  ./wave-skim -f $dsNum $runNum
  # ./process-waveforms.py -f $dsNum $runNum -b
}
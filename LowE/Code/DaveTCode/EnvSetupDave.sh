#!/bin/bash
# Examine this to see how default sl64 environments are set:
# /global/project/projectdirs/majorana/setupMajorana.sh
# Source this file in .bashrc.ext
#
# Clint Wiseman, USC/Majorana
# Dave Tedeschi, USC/Majorana
#
#
#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
function sourceEnvMJD {
  umask 027        # remove all access for world, write and execute for group

  export PATH=${HOMEDIR}:${PATH} # rmate
  export SWDIR=/global/project/projectdirs/majorana/software/sl64

  export MJSWDIR=${SWDIR}/mjsw/mjsw201807Prod
  export MJSWDEV=${SWDIR}/mjsw/mjsw201808Prod

  export MJHOME=/global/project/projectdirs/majorana

  if [ -z "$LD_LIBRARY_PATH" ]; then
      export LD_LIBRARY_PATH=/usr/local/lib
  else
      export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
  fi

  export MJDDATADIR=/global/project/projectdirs/majorana/data/mjd

  source ${SWDIR}/root/root-6.12.06/install/bin/thisroot.sh
  export CLHEP_BASE_DIR=${SWDIR}/CLHEP/2.4.0.4/CLHEP
  export CLHEP_INCLUDE_DIR=${CLHEP_BASE_DIR}/include
  export CLHEP_LIB_DIR=${CLHEP_BASE_DIR}/lib
  export CLHEP_LIB=CLHEP
  export PATH=$CLHEP_BASE_DIR/bin:${PATH}
  export LD_LIBRARY_PATH=${CLHEP_LIB_DIR}:${LD_LIBRARY_PATH}

  export MGDODIR=${MJSWDIR}/MGDO
  export GATDIR=${MJSWDIR}/GAT

  export TAMDIR=${MGDODIR}/tam
  export ORDIR=${MJSWDIR}/OrcaRoot
  export MJORDIR=${MJSWDIR}/MJOR
  export PATH=${MJSWDIR}/bin:${ORDIR}/Applications:${MJORDIR}:${GATDIR}/Apps:${GATDIR}/Scripts:${SIGGENDIR}:${MGDODIR}/bin:${PATH}
  export LD_LIBRARY_PATH=$MJSWDIR/lib:${ORDIR}/lib:${MGDODIR}/install/lib:${GATDIR}/lib:${LD_LIBRARY_PATH}:${MAGEDIR}/analysis
  export ROOT_INCLUDE_PATH=${CLHEP_INCLUDE_DIR}:${MGDODIR}/Base:${MGDODIR}/Gerda:${MGDODIR}/GerdaTransforms:${MGDODIR}/Majorana:${MGDODIR}/MJDB:${MGDODIR}/Root:${MGDODIR}/Tabree:${MGDODIR}/Tools:${MGDODIR}/Transforms:${TAMDIR}:${TAMDIR}/inc:${GATDIR}/BaseClasses:${GATDIR}/MGTEventProcessing:${GATDIR}/MGOutputMCRunProcessing:${GATDIR}/SiggenWrapper

  export MAGEDIR=${MJSWDIR}/MaGe
  source $MAGEDIR/setup.sh

#add mjdb Utils dir to PYTHONPATH
  if [ -z "$PYTHONPATH" ]; then
    export PYTHONPATH=/global/homes/m/mjd/production/Utils
  else
    export PYTHONPATH=$PYTHONPATH:/global/homes/m/mjd/production/Utils
  fi  
  export PATH=/global/homes/m/mjd/production/Utils:$PATH


}
#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

function sourceEnvUser {
  export PS1="\[\033[38;5;14m\]\A\[$(tput sgr0)\]\[\033[38;5;15m\] \[$(tput sgr0)\]\[\033[38;5;10m\]\u@\h\[$(tput sgr0)\]\[\033[38;5;15m\]:\[$(tput bold)\]\[$(tput sgr0)\]\[\033[38;5;9m\]\W\[$(tput sgr0)\]\[$(tput sgr0)\]\[\033[38;5;15m\]\\$ \[$(tput sgr0)\]"
  alias rootmj="root -b -l"
  alias atom='rmate -p "$RMATE_PORT"'
  alias ls="ls --color"
  alias inter="salloc -t 10:00:00 -p shared"
  alias which='alias | /usr/bin/which --tty-only --read-alias --show-dot --show-tilde'



if [ "$NERSC_HOST" = "pdsf" ]; then 
  alias mjd='module load osg; myproxy-logon -s nerscca.nersc.gov; gsissh -Y localhost -l mjd'
  alias mjdsim='module load osg; myproxy-logon -s nerscca.nersc.gov; gsissh -Y localhost -l mjdsim'
fi

if [ "$NERSC_HOST" = "cori" ]; then 
    alias mjd='module load globus; myproxy-logon -s nerscca.nersc.gov; gsissh -Y localhost -l mjd'
    alias mjdsim='module load globus; myproxy-logon -s nerscca.nersc.gov; gsissh -Y localhost -l mjdsim'
fi

  alias mjdiskspace='prjquota majorana | grep majorana | awk '\''{print "prjquota: " $3-$2" GB"}'\''; myquota -j /global/project/projectdirs/majorana | grep -e "^/global" | awk '\''{print "myquota (/project): " $3-$2 " TB"}'\''; myquota -j /global/projecta/projectdirs/majorana | grep -e "^/global" | awk '\''{print "myquota (/projecta): " $3-$2 " TB"}'\'''


}

function rpf {
  myarr=$(ps -u `whoami` | grep sshd | awk '{print $1}')
  kill $myarr
}

function loadModulesMJD {
  source /etc/profile.d/modules.sh
  export CC=/usr/common/usg/software/gcc/4.8.2/bin/gcc
  export CXX=/usr/common/usg/software/gcc/4.8.2/bin/g++

  export python_version=2.7-anaconda
  module load python/$python_version

  module load gcc/4.8.2
  module load ImageMagick
  module load curl
  module load git
  module load cmake/3.5.2
  module load latex
  module load valgrind
  module load oprofile

  findrun () { find $MJDDATADIR -name "*$1*";}

  alias mjdiskspace="prjquota majorana | grep majorana | awk '{print \"prjquota: \" \$3-\$2\" GB\"}'; myquota -j /global/project/projectdirs/majorana | grep -e \"^/global\" | awk '{print \"myquota (/project): \" \$3-\$2 \" TB\"}'; myquota -j /global/projecta/projectdirs/majorana | grep -e \"^/global\" | awk '{print \"myquota (/projecta): \" \$3-\$2 \" TB\"}'"
  gatTagFromDecRev () { echo "obase=16; $1" | bc | xargs -I{} echo 0x{} | xargs printf %07x | xargs git --git-dir=$MJSWDEV/GAT/.git describe; }
  alias countInodesHere="find . -printf \"%h\n\" | cut -d/ -f-2 | sort | uniq -c | sort -rn"
}

#-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
# we're on pdsf (interactive node)
if [ "$NERSC_HOST" = "pdsf" ] && [[ $- == *i* ]] && [ -z "$SLURM_JOB_ID" ]; then
  if [ "${CHOS}" != "sl64" ]; then
    export CHOS=sl64
    chos
  fi
  sourceEnvUser
  loadModulesMJD
  sourceEnvMJD
fi

# we're on pdsf (slurm job)
if [ "$NERSC_HOST" = "pdsf" ] && [ -n "$SLURM_JOB_ID" ]; then
  sourceEnvUser
  sourceEnvMJD
fi

# do for cron jobs
#if [[ $- == hB ]]; then
#  loadModulesMJD
#  sourceEnvMJD
#fi


# we're on cori main login - interactive, no shifter)
if [ "$NERSC_HOST" = "cori" ] && [[ $- == *i* ]] && [ -z "$SLURM_JOB_ID" ] && [ -z "$SHIFTER_RUNTIME" ]; then
  module load python/3.6-anaconda-4.4
  sourceEnvUser
  sourceEnvMJD
fi
# we're on cori, interactive, and in shifter image)
if [ "$NERSC_HOST" = "cori" ] && [[ $- == *i* ]] && [ -n "$SHIFTER_RUNTIME" ]; then
  sourceEnvUser
echo "in there"
fi

# we're on cori (slurm job)
if [ "$NERSC_HOST" = "cori" ] && [ -n "$SLURM_JOBID" ]; then
    echo "Cori Slurm"
fi

# we're on edison (interactive node)
if [ "$NERSC_HOST" = "edison" ] && [[ $- == *i* ]] && [ -z "$SLURM_JOB_ID" ]; then
  module load python/3.6-anaconda-4.4
  sourceEnvUser
  sourceEnvMJD
fi

# we're on edison (slurm job)
if [ "$NERSC_HOST" = "edison" ] && [ -n "$SLURM_JOBID" ]; then
  # module load python/3.5-anaconda
  module load python/3.6-anaconda-4.4
  sourceEnvUser
  sourceEnvMJD
fi

# do for only shifter jobs
# if [ -n "$SHIFTER_RUNTIME" ]; then
# fi

# do for pdsf slurm jobs
# if [ -n "$SLURM_JOB_ID" ]; then
# fi

# do for cori/edison slurm jobs
# if [ -n "$SLURM_JOB_ID" ]; then
# fi

# do for all interactive nodes
# if [[ $- == *i* ]]; then
# fi

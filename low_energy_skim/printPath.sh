#!/bin/bash
#$ -l projectio=1 -j y  -l h_cpu=24:00:00 -l h_vmem=4G -m e  -M ragerj@unc.edu
source ~/.bashrc.ext
#source ~/env/EnvSetup.sh
echo $PATH >> path6.txt

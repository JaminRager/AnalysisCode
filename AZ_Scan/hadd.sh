!/bin/bash
# Number of Azimuthal Steps (zero indexed)
for i in $(eval echo {0..192..2})
do
infiles="$infiles /global/u1/j/jrager/AZ_Scan/1DHists/D2EHists$i.root"
#echo $infiles
command="hadd -f fullRun.root $infiles"
echo $command
eval $command
done

#!/bin/bash
# A simple script to check the event number in all multicrab jobs agree

# Main directory (the one fed into the multicrab -c)
mainDir="/afs/cern.ch/work/a/afiqaize/hlt/Part2_OpenHLT/OpenHLT/CMSSW_7_2_1_patch2/src/HLTrigger/Configuration/test/Alt_Job/bar_only/"

# Common part of the name of individual multicrab directories; the differentiator should be at the end
jobName="dyll_"

# List of the differentiators
jobList="all
bar"

# The CRAB log file to be searched and other shit
crabLog="CMSSW_"
logExt='.log'

outDir=$mainDir"barOnly_log/dyll/"

#Define the directories and search the nEvt (for HLT log only atm) [match the desired pattern based on your job]
for eachJob in $jobList
do

inDir=$mainDir$jobName$eachJob"/res/"
jobLabel=$jobName$eachJob

grep "passed =" $inDir$crabLog"1.stdout" >& $outDir$jobLabel"_proEvt"$logExt

# This needs to be changed to match no. of jobs
# It starts at 2 since the first and creation is done above
for i in {2..500}
do

grep "passed =" $inDir$crabLog$i".stdout" >> $outDir$jobLabel"_proEvt"$logExt

done
done

# Now we diff the product to ensure all jobs processes the same event total

echo '## This file should be empty as all jobs are expected to process the same events'  >& $outDir$jobName"nEvt_diff.log"
firstJob=$jobName"all"

for eachLog in $jobList
do

jobLog=$outDir$jobName$eachLog"_proEvt"$logExt

diff $outDir$firstJob"_proEvt"$logExt $jobLog >> $outDir$jobName"nEvt_diff.log"

done

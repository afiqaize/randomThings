#!/bin/bash
# A simple script to check the event number in all crab jobs agree
# 29 Jan 2016 Modified for crab3
# Usage: . nEvt_check.sh

# Main directory (the top dir containing all job dirs)
mainDir="/afs/cern.ch/work/a/afiqaize/egm/eeAngEff_Jun13/CMSSW_8_0_11/src/HLTTest/MyCandidates/job/crab/"

# Common part of the name of the crab requests; the differentiator should be at the end
jobName="hltPhy_eeNon_"

# List of the differentiators
jobList="newAlign
oriAlign"

# The CRAB log file to be searched and other shit
crabLog="cmsRun-stdout-"
logExt='.log'
crabApp='crab_'

outDir=$mainDir"log_filt/"

#Define the directories and search the nEvt (for HLT log only atm) [match the desired pattern based on your job]
for eachJob in $jobList
do

jobLabel=$jobName$eachJob
inDir=$mainDir$crabApp$jobLabel"/results/"

grep "0 HLTriggerFinalPath" $inDir$crabLog"1"$logExt >& $outDir$jobLabel"_proEvt"$logExt

# This needs to be changed to match no. of jobs
# It starts at 2 since the first and creation is done above
for i in {2..285}
do

grep "0 HLTriggerFinalPath" $inDir$crabLog$i$logExt >> $outDir$jobLabel"_proEvt"$logExt

done
done

# Now we diff the product to ensure all jobs processes the same event total

echo '## This file should be empty as all jobs are expected to process the same events'  >& $outDir$jobName"nEvt_diff"$logExt
firstJob=$jobName"newAlign"

for eachLog in $jobList
do

jobLog=$outDir$jobName$eachLog"_proEvt"$logExt

diff $outDir$firstJob"_proEvt"$logExt $jobLog >> $outDir$jobName"nEvt_diff"$logExt

done

#!/bin/bash
# A simple script to retrieve the desired info in a log
# To be used with nEvt_check.sh
# Usage: . nEvt_retrieve.sh procName logLabel pathName
# No underscores in the args (except pathName)
# procName is a free parameter; adapt to taste

# Main directory (the one above those fed into the crab -d)
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

grep "0 $3" $inDir$crabLog"1"$logExt | head -1 >& $outDir$eachJob'_'$2$logExt

# This needs to be changed to match no. of jobs
# It starts at 2 since the first and creation is done above
for i in {2..285}
do

grep "0 $3" $inDir$crabLog$i$logExt | head -1 >> $outDir$eachJob'_'$2$logExt

done
done

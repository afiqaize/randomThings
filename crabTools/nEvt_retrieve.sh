#!/bin/bash
# A simple script to check the event number in all multicrab jobs agree
# Usage: . nEvt_retrieve.sh procName logLabel pathName
# No underscores in the args (except pathName)

# Main directory (the one fed into the multicrab -c)
mainDir="/afs/cern.ch/work/a/afiqaize/hlt/Part2_OpenHLT/OpenHLT/CMSSW_7_4_0_pre8/src/drawHist/drawVar/test/crab/"

# The CRAB log file to be searched and other shit
crabLog="CMSSW_"
logExt='.log'

# Common part of the name of individual multicrab directories; the differentiator should be at the end
jobName=$1'_'

# List of the differentiators
jobList="pu20
pu40"

outDir=$mainDir"../PUeWP_log/"$1'/'

#Define the directories and search the nEvt (for HLT log only atm) [match the desired pattern based on your job]
for eachJob in $jobList
do

inDir=$mainDir$jobName$eachJob"/res/"
jobLabel=$jobName$eachJob

grep "0 $3" $inDir$crabLog"1.stdout" >& $outDir$eachJob'_'$2$logExt

# This needs to be changed to match no. of jobs
# It starts at 2 since the first and creation is done above
for i in {2..500}
do

grep "0 $3" $inDir$crabLog$i".stdout" >> $outDir$eachJob'_'$2$logExt

done
done

#!/bin/bash
# adapted from condorRun.sh by joseph dulemba @ rochester

ulimit -s unlimited
set -e
cd ${cmssw_base}/src
export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd $TMPDIR

#### not meant to be run directly; simply a wrapper executable
echo 'Job execution starts at '$(date)' on host '${HOSTNAME}
echo

"$@"

if [ $? -eq 0 ]; then
    echo 'Job execution ends at '$(date)
fi

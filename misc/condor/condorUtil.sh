#!/bin/bash

## check all condor log files in a given dir
condor_check () 
{ 
    local logdir=$1
    if [ -z ${logdir} ]; then
        logdir="."
    fi

    local fname=$2
    if [ -z ${fname} ]; then
        fname='*.o*.*'
    else
        fname='*'${fname}'*.o*.*'
    fi

    find ${logdir} -type f -name "${fname}" | xargs -I % sh -c 'tail -1 % | grep -q -F "Job execution ends at"; if (($?)); then echo "%"; fi'
}
export -f condor_check

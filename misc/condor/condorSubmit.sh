#!/bin/bash

### This script creates the per-job condor submit file and does the linking with wrapper script, executable etc
### Usage: ./condorSubmit.sh -s CONDORSUBMITTEMPLATE -w WRAPPERSCRIPT -e EXECUTABLE (-a EXECARGS -n JOBNAME -d INITDIR -l LOGDIR -i JOBINPUT -h REQHDISK -m REQMEM -t REQTIME -p REQCPU -c JOBCOUNT -o JOBOFFSET)
### Long args reserved for flag switches for the moment; names should be self-explanatory

set -o noglob

## basic handles
jobSub=""
jobWrap=""
jobExec=""
jobArg=()
jobName=""
jobDir=""
logDir=""
jobInput=""
reqHDisk=() # in kb
reqMem=() # in Mb
reqTime="" # in seconds 
reqCpu=""
jobCount=""
jobMateria="200"
jobOffset="1"

runTmp=0
dbgRun=0
stdLog=1
cluLog=0
gridProxy=""
requireOS=""
singularitySL6=0

## parse command line options.
while getopts s:w:e:a:n:d:l:i:h:m:t:p:c:o:-: OPT; do
    case "$OPT" in
        s)
            jobSub=$OPTARG
            ;;
        w)
            jobWrap=$OPTARG
            ;;
        e)
            jobExec=$OPTARG
            ;;
        a)
            IFS=' '
            jobArg=($OPTARG)
            ;;
        n)
            jobName=$OPTARG
            ;;
        d)
            jobDir=$OPTARG
            ;;
        l)
            logDir=$OPTARG
            ;;
        i)
            jobInput=$OPTARG
            ;;
        h)
            IFS=' '
            reqHDisk=($OPTARG)
            ;;
        m)
            IFS=' '
            reqMem=($OPTARG)
            ;;
        t)
            reqTime=$OPTARG
            ;;
        p)
            reqCpu=$OPTARG
            ;;
        c)
            jobCount=$OPTARG
            ;;
        o)
            jobOffset=$OPTARG
            ;;
        -)
            # How it works: --string is in fact string as argument for option -
            # Decide what to do based on string to emulate the long option while staying within getopts
            # We're limiting ourselves to simple cases for now
            # In implementing more complex stunts, keep arg bookkeeping in mind
            # Search for the var name eg runTmp for comment in case flag name isn't clear enough
            # --grid-proxy :: provide as arg the tmp directory that is printed out when doing voauth/voms-proxy-init -voms cms
            # --require-os only takes SL6 or EL7 for now
            case $OPTARG in
                run-in-tmp) 
                    runTmp=1
                    ;;
                debug)
                    dbgRun=1
                    ;;
                no-std-log)
                    stdLog=0
                    ;;
                cluster-log)
                    cluLog=1
                    ;;
                grid-proxy)
                    gridProxy="${!OPTIND}"
                    OPTIND=$(( OPTIND + 1 ))
                ;;
                grid-proxy=*)
                    gridProxy=${OPTARG#*=}
                ;;
                require-os)
                    requireOS="${!OPTIND}"
                    OPTIND=$(( OPTIND + 1 ))
                ;;
                require-os=*)
                    requireOS==${OPTARG#*=}
                ;;
                sl6-singularity)
                    singularitySL6=1
                ;;
                *) 
                    echo "   Nothing is implemented for long option: "$OPTARG", exiting..."
                    exit 1
                    ;;
                esac
            ;;
    esac
done

## safety checks, default assignments
if [ -z ${jobExec} ]; then
   echo "Compulsory argument -e for executable name not provided!!"
   echo 'Usage: ./condorSubmit.sh -e EXECUTABLE (-s CONDORSUBMITTEMPLATE -w WRAPPERSCRIPT -a EXECARGS -n JOBNAME -d INITDIR -l LOGDIR -h REQHDISK -m REQMEM -t REQTIME -c JOBCOUNT)'
   echo "Additional settings: --run-in-tmp, --debug, --no-std-log, --cluster-log, --grid-proxy, --require-os, --sl6-singularity"
   exit 0
fi

if [ -z ${jobSub} ]; then
    jobSub=/nfs/dust/cms/user/afiqaize/cms/sft/condor/condorParam.txt
fi

if [ -z ${jobWrap} ]; then
    jobWrap=/nfs/dust/cms/user/afiqaize/cms/sft/condor/condorRun.sh
fi

if [ -z ${jobName} ]; then
    jobName=$(basename ${jobExec})
fi

if [ -z ${jobDir} ]; then
    jobDir=$(pwd -P)
fi

if [ -z ${logDir} ]; then
    logDir=${jobDir}
fi

if [ ! -d ${logDir} ]; then
  mkdir -p ${logDir}
fi

## print out arg count and actual arg
#echo ${#jobArg[@]} "${jobArg[@]}"

## ok let's get this done with...
cp ${jobSub} ./conSub_${jobName}.txt

sed -i "s?__EXEC__?${jobExec}?g" ./conSub_${jobName}.txt
sed -i "s?__WRAP__?${jobWrap}?g" ./conSub_${jobName}.txt
sed -i "s?__NAME__?${jobName}?g" ./conSub_${jobName}.txt
sed -i "s?__LOG__?${jobName}?g" ./conSub_${jobName}.txt
sed -i "s?__INITDIR__?${jobDir}?g" ./conSub_${jobName}.txt
sed -i "s?__LOGDIR__?${logDir}?g" ./conSub_${jobName}.txt
sed -i "s?__LD_L_P__?${LD_LIBRARY_PATH}?g" ./conSub_${jobName}.txt

if [ ${#jobArg[@]} -lt 1 ]; then
    sed -i "s?__ARGUMENTS__? ?g" ./conSub_${jobName}.txt
else
    sed -i "s?__ARGUMENTS__?$(echo ${jobArg[@]})?g" ./conSub_${jobName}.txt
fi

## manipulations for providing grid certificates
## grid cert should be the file generated by voauth - by default it is in of name /tmp/x509up_u{YOURUSERID}
if [ ! -z ${gridProxy} ]; then
    if ((runTmp)); then
        cp ${gridProxy} ${HOME}

        if [ -z ${jobInput} ]; then
            jobInput="${HOME}/$(basename ${gridProxy})"
        else
            jobInput="${jobInput}, ${HOME}/$(basename ${gridProxy})"
        fi
    else
        if [ -z $(find . -type f -name $(basename ${gridProxy})) ]; then
            cp ${gridProxy} .
        fi
    fi

    sed -i 's?Job_Proc_ID)"?Job_Proc_ID) X509_USER_PROXY=./__GRIDPROXY__"?g' ./conSub_${jobName}.txt 
    sed -i "s?__GRIDPROXY__?$(basename ${gridProxy})?g" ./conSub_${jobName}.txt
fi

## to provide input files for jobs
## don't use this for grid certs; instead use --grid-proxy above
if [ ! -z ${jobInput} ]; then
    sed -i "s?#transfer_input_files?transfer_input_files?g" ./conSub_${jobName}.txt
    sed -i "s?__INPUTFILE__?${jobInput}?g" ./conSub_${jobName}.txt
fi

## resources request - no arg means use HTC default
if [ ${#reqHDisk[@]} -lt 1 ]; then
    sed -i "s?RequestDisk?#RequestDisk?g" ./conSub_${jobName}.txt
else
    sed -i "s?__REQHDISK__?$(echo ${reqHDisk[@]})?g" ./conSub_${jobName}.txt
fi

if [ ${#reqMem[@]} -lt 1 ]; then
    sed -i "s?RequestMemory?#RequestMemory?g" ./conSub_${jobName}.txt
else
    sed -i "s?__REQMEM__?$(echo ${reqMem[@]})?g" ./conSub_${jobName}.txt
fi

if [ -z ${reqCpu} ]; then
    ## naf
    sed -i "s?request_cpus?#request_cpus?g" ./conSub_${jobName}.txt
    ## lxp
    #sed -i "s?+MaxRuntime?#+MaxRuntime?g" ./conSub_${jobName}.txt
else
    sed -i "s?__REQCPU__?${reqCpu}?g" ./conSub_${jobName}.txt
fi

if [ -z ${reqTime} ]; then
    ## naf
    sed -i "s?+RequestRuntime?#+RequestRuntime?g" ./conSub_${jobName}.txt
    ## lxp
    #sed -i "s?+MaxRuntime?#+MaxRuntime?g" ./conSub_${jobName}.txt
else
    sed -i "s?__REQTIME__?${reqTime}?g" ./conSub_${jobName}.txt
fi

## for array jobs
if [ -z ${jobCount} ]; then
    sed -i "s?__JOBCOUNT__? ?g" ./conSub_${jobName}.txt
else
    sed -i "s?__JOBCOUNT__?${jobCount}?g" ./conSub_${jobName}.txt

    ## does not work, as said in DESY manual
    #if [ ${jobCount} -gt 299 ]; then
    #    sed -i "s?#max_materia?max_materia?g" ./conSub_${jobName}.txt
    #    sed -i "s?__JOBMATERIALIZE__?${jobMateria}?g" ./conSub_${jobName}.txt
    #fi
fi

## To start counting from N (this default 1, HTC's default 0)
sed -i "s?__JOBOFFSET__?${jobOffset}?g" ./conSub_${jobName}.txt

## if we want to use instead HTC's tmpdir
if ((runTmp)); then
    sed -i "s?initialdir?#initialdir?g" ./conSub_${jobName}.txt
    sed -i "s?#should_transfer?should_transfer?g" ./conSub_${jobName}.txt
    sed -i "s?#when_to_?when_to_?g" ./conSub_${jobName}.txt
fi

## sometimes we dont want the logs
if ((! stdLog)); then
    sed -i "s?output =?#output =?g" ./conSub_${jobName}.txt
    sed -i "s?error =?#error =?g" ./conSub_${jobName}.txt
fi

## and some other times we want the cluster (machine) log
if ((cluLog)); then
    sed -i "s?#log =?log =?g" ./conSub_${jobName}.txt
fi

## SL6/EL7 choice
if [ -z ${requireOS} ] || [ "${requireOS}" = "EL7" ] || [ "${requireOS}" = "el7" ]; then
    sed -i "s?#__EL7__req?req?g" ./conSub_${jobName}.txt
elif [ "${requireOS}" = "SL6" ] || [ "${requireOS}" = "sl7" ]; then
    sed -i "s?#__SL6__req?req?g" ./conSub_${jobName}.txt
else
    echo "ERROR :: choice of OS not understood; only SL6 or EL7 accepted for now!"
    rm ./conSub_${jobName}.txt
    exit 0
fi

## need SL6 singularity?
if ((singularitySL6)); then
    sed -i "s?#+MySingularity?+MySingularity?g" ./conSub_${jobName}.txt
fi

## actually submit if not in debug mode
#if ((dbgRun)); then
    #echo "Debug mode: writing submit file "./conSub_${jobName}.txt
if ((! dbgRun)); then
    condor_submit ./conSub_${jobName}.txt
    wait

    ## seems needed to mitigate the LeakyCondor issue
    sleep 1
    rm ./conSub_${jobName}.txt
fi

# FIXME list of bugs/desiderata
# -i jobInput has problems with more than 1 input for now, to be solved

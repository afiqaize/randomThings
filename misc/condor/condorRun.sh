#!/bin/sh

set -o noglob

### not meant to be run directly; simply a wrapper executable
export LD_LIBRARY_PATH=${LD_LIB_PATH}

echo 'Job execution starts at '$(date)' on host '${HOSTNAME}
echo

"$@"

if [ $? -eq 0 ]; then
    echo 'Job execution ends at '$(date)
fi

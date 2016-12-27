#!/bin/bash
crt=`cat region.stat-file.csv |  grep "#" | grep 0x   | awk '
    BEGIN {count=0}
          {start[count] = $1; end[count] = $2; count++;}
    END {
            criteria="'\''forward-slice 1 " start[0] " "  end[0] " 1"
            for (i=1; i < count; i++)
                criteria = criteria " | forward-slice 1 " start[i] " " end[i] " 1 "
           criteria = criteria "'\''" 
            print criteria 
        }'`
echo "Running slicing on region pinball"
echo -n '$PIN_ROOT/extras/pinplay/scripts/replay --pintool_options ' 
echo " \" -trace 1 -slice $crt \" region.pinball/log_0"
$PIN_ROOT/extras/pinplay/scripts/replay --pintool_options " -trace 1 -slice $crt " region.pinball/log_0

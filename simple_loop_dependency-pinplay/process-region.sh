#!/bin/bash
echo "Running loop tracker 'simple_loop.c:5'"..
echo '$PIN_ROOT/extras/pinplay/scripts/replay --pintool $PIN_ROOT/extras/dcfg/bin/intel64/loop-tracker.so --pintool_options "-loop-tracker:dcfg-file region.pinball/log_0.dcfg.json.bz2 -loop-tracker:debug_level 0 -loop-tracker:loop_stat-file region.stat-file.csv -loop-tracker:trace-loops 'simple_loop.c:5'" region.pinball/log_0 '
$PIN_ROOT/extras/pinplay/scripts/replay --pintool $PIN_ROOT/extras/dcfg/bin/intel64/loop-tracker.so --pintool_options "-loop-tracker:dcfg-file region.pinball/log_0.dcfg.json.bz2 -loop-tracker:debug_level 0 -loop-tracker:loop_stat-file region.stat-file.csv -loop-tracker:trace-loops 'simple_loop.c:5'" region.pinball/log_0 

res=`./get-iteration-stats.sh region.stat-file.csv`
loopid=`echo $res | awk '{print $1}'`
startaddr=`echo $res | awk '{print $2}'`
startcount=`echo $res | awk '{print $3}'`
endaddr=`echo $res | awk '{print $4}'`
endcount=`echo $res | awk '{print $5}'`

echo "Creating region.dcfg.dot.."
echo '$PIN_ROOT/extras/dcfg/bin/intel64/dcfg-to-dot region.pinball/log_0.dcfg.json.bz2 region.dcfg.dot $loopid'
$PIN_ROOT/extras/dcfg/bin/intel64/dcfg-to-dot region.pinball/log_0.dcfg.json.bz2 region.dcfg.dot $loopid
echo "Creating region.dcfg.dot.pdf.."
echo 'dot -Tpdf -O region.dcfg.dot'
dot -Tpdf -O region.dcfg.dot


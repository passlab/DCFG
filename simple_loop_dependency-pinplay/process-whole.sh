#!/bin/bash
echo "Running whole-program loop tracker 'simple_loop.c:5'"
echo '$PIN_ROOT/extras/pinplay/scripts/replay --pintool $PIN_ROOT/extras/dcfg/bin/intel64/loop-tracker.so --pintool_options "-loop-tracker:dcfg-file whole.pinball/log_0.dcfg.json.bz2 -loop-tracker:debug_level 0 -loop-tracker:loop_stat-file whole.stat-file.csv -loop-tracker:trace-loops 'simple_loop.c:5'" whole.pinball/log_0 '
$PIN_ROOT/extras/pinplay/scripts/replay --pintool $PIN_ROOT/extras/dcfg/bin/intel64/loop-tracker.so --pintool_options "-loop-tracker:dcfg-file whole.pinball/log_0.dcfg.json.bz2 -loop-tracker:debug_level 0 -loop-tracker:loop_stat-file whole.stat-file.csv -loop-tracker:trace-loops 'simple_loop.c:5'" whole.pinball/log_0 

res=`./get-iteration-stats.sh whole.stat-file.csv`
loopid=`echo $res | awk '{print $1}'`
startaddr=`echo $res | awk '{print $2}'`
startcount=`echo $res | awk '{print $3}'`
endaddr=`echo $res | awk '{print $4}'`
endcount=`echo $res | awk '{print $5}'`

echo "Creating whole.dcfg.dot.."
echo '$PIN_ROOT/extras/dcfg/bin/intel64/dcfg-to-dot whole.pinball/log_0.dcfg.json.bz2  whole.dcfg.dot $loopid'
$PIN_ROOT/extras/dcfg/bin/intel64/dcfg-to-dot whole.pinball/log_0.dcfg.json.bz2  whole.dcfg.dot $loopid
echo "Creating whole.dcfg.dot.pdf.."
echo 'dot -Tpdf -O whole.dcfg.dot'
dot -Tpdf -O whole.dcfg.dot

echo "Relogging $startaddr:$startcount -- $endcount : start:address:$startaddr:count$startcount,stop:address:$endaddr:count$endcount "
echo '$PIN_ROOT/extras/pinplay/scripts/relog --pintool $PIN_ROOT/extras/dcfg/bin/intel64/dcfg-driver.so --pintool_options "-dcfg -dcfg:read_dcfg 1 -log:control start:address:$startaddr:count$startcount,stop:address:$endaddr:count$endcount " whole.pinball/log_0 region.pinball/log'
$PIN_ROOT/extras/pinplay/scripts/relog --pintool $PIN_ROOT/extras/dcfg/bin/intel64/dcfg-driver.so --pintool_options "-dcfg -dcfg:read_dcfg 1 -log:control start:address:$startaddr:count$startcount,stop:address:$endaddr:count$endcount " whole.pinball/log_0 region.pinball/log
touch region.pinball/log_0.0.race

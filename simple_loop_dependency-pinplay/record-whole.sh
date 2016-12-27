#!/bin/bash
echo "Running  Static Analysis for slicing"
echo '$PIN_ROOT/pin -t $PIN_ROOT/extras/pinplay/bin/intel64/pinplay-driver.so -target 1 -static_analysis $PIN_ROOT/extras/pinplay/bin/intel64/StaticAnalysis -- ./simple_loop '
$PIN_ROOT/pin -t $PIN_ROOT/extras/pinplay/bin/intel64/pinplay-driver.so -target 1 -static_analysis $PIN_ROOT/extras/pinplay/bin/intel64/StaticAnalysis -- ./simple_loop 
echo "Recording+DCFG generation for whole-program run "
echo '$PIN_ROOT/extras/pinplay/scripts/record --pintool $PIN_ROOT/extras/dcfg/bin/intel64/dcfg-driver.so --pinball whole.pinball/log --pintool_options "-dcfg " ./simple_loop'
$PIN_ROOT/extras/pinplay/scripts/record --pintool $PIN_ROOT/extras/dcfg/bin/intel64/dcfg-driver.so --pinball whole.pinball/log --pintool_options "-dcfg " ./simple_loop
touch whole.pinball/log_0.0.race

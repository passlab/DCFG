
### pinplay simple loop dependency example from [pinplay tutorial during PLDI 2016](https://sites.google.com/site/pinplaypldi2016tutorial/)
The example shows step-by-step using scripts how to generate dynamic control flow graph, 
loop region, and dynamic slicing using pinplay. The example currently only works on fornax due to 
some bugs mentioned in the README file for Ubuntu. 

### pintool examples for memory tracing, edge count of basic block and call tracing
The [pin_examples](pin_examples) folder contains three usefule examples, memory trace(pinatrace), 
edgecnt and calltrace for help understanding how to use [pin](http://pintool.org) to trace memory access, 
basic blocks and function calls. 

### dyninst example for statically generating static control flow graph
The [dyninst_CFG](dyninst_CFG) folder contains sources for generating dot-based CFG using dyninst and you need to follow
dyninst installation guild to make it work. Check the [dyninst_CFG/README.md](dyninst_CFG/README.md) file.

=============================================================
## General Steps

1. Use pinplay (check [simple_loop_dependency-pinplay](simple_loop_example-pinplay) folder) to generate 
DCFG, loop region and slicing information. Profiling (e.g. using PAPI or cycle info from pin if it can), and 
graph and binary analysis may be needed to identify the hotspot of performance loss (e.g. poor locality, cache/bus contention, etc). 
1. Use pintool pinatrace to generate traces of memory access (R/W and size) of instructions. 
1. Analyze the pinatrace memory traces and append the needed <instr><R|W><MemAddr><value> info to the memory-access instructions of the dyninst-loops of a function
1. For the memory access (particularly Load) instruction, perform analysis using SLICING to create links of the instructions who loads data and the instruction who uses that data (Load-USE relationship).
1. Perform cycle-distance analysis of the Load-USE instructions to identify the delay of USE instruction if the the Load is NOT from the cache.
1. For software prefetching, identify the slot for inserting the prefetching call for the Load
1. Extends the work to parallel program

### Others that may be helpful

1. Use Dyninst interfaces for retrieving function, loops and loop nest, and static CFG for a binary program. We will start with the [CFG.cpp](dyninst_CFG/CFG.cpp) file for the rest of the development.  
1. Analyze the edgecnt traces and append # of calls of each edge to the edge in the static CFG of the dyninst-loops of a function.
1. Use Dyninst DataFlowAPI and SLICING

The repository contains source code for a tool to create dynamic control- and 
data-flow graph with memory trace and NUMA/cache access behavior of a sequetial
and parallel program. The tool is developed on top of pintool for binary 
instrumentatio (http://pintool.org) and dyninst for binary analysis (http://www.dyninst.org/). 
You need to install the latest pintool and dyninst to make the program functional. 

### For installation on Linux

1. Download the latest pintool from http://www.pintool.org (currenly using rev 76991, version 3.0). 
The website also provide tutorial and guide for using pin.

1. Unzip the pintool and navigate to the source/tools folder of pinplay. Under the tool folder, 
clone this rep (https://github.com/passlab/DCFG). The DCFG compilation leverages pintool building framework.
So this is the easiest approach to have it running.

1. "make" command will create the pin tool binaries in the folder, including edgecount, calltrace and 
pinatrace (memory trace). Check the pintool tutorial for how to executing 
[pinatrace](https://software.intel.com/sites/landingpage/pintool/docs/76991/Pin/html/index.html#MAddressTrace).
The same link also contains other examples. 

1. The repo contains sample pin examples for edgecount, callgraph, calltrace and memory trace and 
related python scripts for generating related graph in graphml (or vcg/dot) based on tracing output. 
Please refer to each tracing python and example for how to use it. Those exampsl are modified from 
examples of pin distributions. You can find other examples in the source/tools folder

1. The CFG folder contains sources for generating dot-based CFG using dyninst and you need to follow
dyninst installation guild to make it work. Check the README.md file in the folder.

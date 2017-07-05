## Constructing Parallel Dynamic Control Flow Graph using Processor Tracing and OMPT



### Processor Tracing
 * https://hsdm.dorsal.polymtl.ca/system/files/10Dec2015_0.pdf, http://halobates.de/pt-tracing-summit15.pdf
 * https://github.com/01org/processor-trace
 
### Build PT
 * Use the following cmake command to turn on all the features and set the right location to xed
 ``
 cmake -DPTUNIT=ON -DPTDUMP=ON -DPTXED=ON -DPTTC=ON -DSIDEBAND=ON -DPEVENT=ON -DFEATURE_ELF=ON -DFEATURE_THREADS=ON -DXED_LIBDIR=/home/yan/tools/xed/kits/xed-install-base-2017-07-05-lin-x86-64/lib -DXED_INCLUDE=/home/yan/tools/xed/kits/xed-install-base-2017-07-05-lin-x86-64/include/xed ..
 ``
 
 ### Constructing Control Flow Graph 
 * [Dynamic Control-flow Graph Generation with PinPlay](https://software.intel.com/en-us/articles/pintool-dcfg)
 * [Transparent and Efficient CFI Enforcement with Intel Processor Trace](http://ipads.se.sjtu.edu.cn/lib/exe/fetch.php?media=publications:flowguard.pdf)
 * [Constructing Precise Control Flow Graphs from Binaries](https://pdfs.semanticscholar.org/1181/432dee62981c5a8ed5e9c16ec0a556f56b77.pdf)
 * [A Hybrid Aproach for Control Flow Graph Construction from
Binary Code](http://www.jaist.ac.jp/~mizuhito/papers/conference/APSEC13.pdf)
 * [Building a Control-flow Graph from Scheduled Assembly Code](http://www.hipersoft.rice.edu/grads/publications/pldicfg4.pdf)
 

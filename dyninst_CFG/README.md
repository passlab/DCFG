CFG is a simple tool built on ParseAPI and InstructionAPI of Dyninst to produce 
the static control flow graph of a binary file.

     Usage: ./CFG [options] binFile
     -i: Output the instructions in each basic blocks
     -n patterns: filter functions by matching the function names using the specified pattern
         Example: -n "foo bar" means only output CFG for functions with function names containing substring "foo" or "bar"
     -o outFileName: Specify the output file name

mem_count is a memory trace tool to print the memory access of the "hello" program when being executed. It has the same functionality
as the pinatrace tool, but it runs much slower than pinatrace

### Installation of dyninst and build CFG
1. Download dyninst version 9.2.0 (https://github.com/dyninst/dyninst/releases/tag/v9.2.0) (The latest git repo also works) and check the README for all the software dependencies (Boost, cmake, libdwarf, libelf and libiberty). On Ubuntu, those packages can be installed by using 
      
           sudo apt-get install libboost-dev libelf-dev libiberty-dev cmake libdwarf-dev

1. After all the prerequisite are installed, under the dyninst folder, run the following commands:
      
           cmake -DCMAKE_INSTALL_PREFIX=/home/yan/pintool/dyninst-install .   # change the target folder you want, it is for DYNINST_INSTALL later
           make
           make install
       
              
   The Ubuntu libdwarf-dev may not contain PIC-version of the libdwarf.a lib, thus the dyninst compilation will fail. 
   If this is the case for you, it is easier for just install it manually after downloading it from 
https://www.prevanders.net/dwarf.html. The installation is pretty easy, in the source folder, firing "configure", and then "make" commands. 
After than replace the system libdwarf installation by overwriting the two files "sudo cp libdwarf/libdwarf.a /usr/lib", and "sudo cp libdwarf/libdwarf.h /usr/include". After that, redo the cmake/make/make install steps for installation

1. cd to the dyninst_CFG folder and modify the setenv.sh file so the DYNINST_INSTALL env points to where the dyninst is installed
1. source the setenv.sh file: "source setenv.sh" (need to do this each time for a new shell environment/login). 
1. "cmake ." and "make" will build the CFG executable.
1. ./CFG hello will create the control-flow graph for hello

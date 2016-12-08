CFG is a simple tool built on ParseAPI and InstructionAPI of Dyninst to produce 
the control flow graph of a binary file.

Usage: ./CFG [options] binFile
-i: Output the instructions in each basic blocks
-n patterns: filter functions by matching the function names using the specified pattern
Example: -n "foo bar" means only output CFG for functions with function names containing substring "foo" or "bar"
-o outFileName: Specify the output file name

mem_count is a memory trace tool to print the memory access of the "hello" program

check the setenv.sh file for setting the env before running the CFG and mem_count

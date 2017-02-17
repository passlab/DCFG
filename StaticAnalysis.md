## StaticAnalysis options (version 3.2)
~~~~
[yan@fornax simple_loop_dependency-pinplay]$ $PIN_ROOT/extras/pinplay/bin/intel64/StaticAnalysis -h
This tool disassembles an image.


Pin tools switches

-IPD_Dir  [default ./cd/]
	output immediate postdominator info's to this directory
-TARGET_DIR  [default ./TARGET/]
	target directory
-func_base_name  [default function]
	when the function name is too long to be the ipd file name, we change
	the long function name to shorter name, this is the base function name
-func_name_map  [default func_name_map.ii]
	when the function name is too long to be the ipd file name,we change
	the function name to a shorter one, and we record this mapping here
-h  [default 0]
	Print help message (Return failure of PIN_Init() in order to allow the
	tool                             to print help message)
-help  [default 0]
	Print help message (Return failure of PIN_Init() in order to allow the
	tool                             to print help message)
-i  [default <imagenames>]
	specify  images to do static analysis
-ipd  [default 1]
	compute immediate post dominator
-logfile  [default pintool.log]
	The log file path and file name
-unique_logfile  [default 0]
	The log file names will contain the pid

Line information controls

-discard_line_info 
	Discard line information for specific module. Module name should be a
	short name without path, not a symbolic link
-discard_line_info_all  [default 0]
	Discard line information for all modules.
-dwarf_file 
	Point pin to a different file for debug information. Syntax:
	app_executable:<path_to_different_fileExaple (OS X): -dwarf_file
	get_source_app:get_s
	ource_app.dSYM/Contents/Resources/DWARF/get_source_app

Symbols controls

-ignore_debug_info  [default 0]
	Ignore debug info for the image. Symbols are taken from the symbol
	tables.
-reduce_rtn_size_mode  [default auto]
	Mode for RTN size reduction: delete trailing instructions after RET if
	there is no jump to the rtn part after the RET. Possible modes are:
	auto/never/always
-short_name  [default 0]
	Use the shortest name for the RTN. Names with version substrings are
	preferred over the same name without the substring.
-support_jit_api  [default 0]
	Enables the Jitted Functions Support
-unrestricted_rtn_size  [default 0]
	Use the unrestricted RTN size. When set the RTN size defined by the
	distance between RTN start to the beginning of next RTN.

Statistic switches

-profile  [default 0]
	print amount of memory dynamically allocated but not yet freed by the
	tool
-statistic  [default 0]
	print general statistics

General switches (available in pin and tool)

-slow_asserts  [default 0]
	Perform expensive sanity checks
  ~~~~

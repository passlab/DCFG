## pinplay (version 3.2) switches:
~~~~
[yan@fornax simple_loop_dependency-pinplay]$ $PIN_ROOT/pin -t $PIN_ROOT/extras/pinplay/bin/intel64/pinplay-driver.so --help -- ./simple_loop
Usage: /home/yan/tools/pintool/pinplay-drdebug-3.2-pin-3.2-81205-gcc-linux/intel64/bin/pinbin Args  -- app appargs ...
Arguments:

Pin tools switches

-IPD_Dir  [default ./cd]
	immediate postdominator info's directory
-TARGET_DIR  [default ./TARGET/]
	target directory
-break_on_slice  [default -1]
	Automatically set breakpoints on all statements in slice id N
	previously generated
-cd_file  [default controlD]
	a file containing the dynamic control dependence infomation
-disable_control_dependence  [default 0]
	Disable control dependencies
-forward_slice_limit  [default -1]
	Limit the number of trace blocks sliced
-func_base_name  [default function]
	when the function name is too long to be the ipd file name, we change
	the long function name to shorter name, this is the base function name
-func_name_map  [default func_name_map.ii]
	when the function name is too long to be the ipd file name, we change
	the function name to a shorter one, and we record this mapping here
-gdb:cmd_file  [default ]
	File where 'target remote' command will be output so a script can
	monitor it and invoke GDB.
-h  [default 0]
	Print help message (Return failure of PIN_Init() in order to allow the
	tool                             to print help message)
-help  [default 0]
	Print help message (Return failure of PIN_Init() in order to allow the
	tool                             to print help message)
-log  [default 0]
	Activate the pinplay logger
-log_file  [default compact_log]
	compact trace file
-logfile  [default pintool.log]
	The log file path and file name
-lp_file  [default limited_preprocess]
	do limited preprocessing to the given log file defined by log_file,
	and output the result into this file
-record_pc  [default 0]
	record previous program counter for stack smash bugs
-replay  [default 0]
	Activate the pinplay replayer
-slice  [default ]
	slice criterion
-static_analysis  [default ~/pin/pinplay-drdebug-1.3-pin-2.13-65163-gcc.4.4.7-linux/extras/pinplay/bin/intel64/StaticAnalysis]
	Static Analysis to compute IPD for control dependence
-target  [default 0]
	Collect Dynamic Jump Target
-trace  [default 0]
	Turn on tracing after specified instructions get executed
-unique_logfile  [default 0]
	The log file names will contain the pid
-variable_file  [default variable_name.out]
	variable names and addresses mapping file

Call Stack knobs

-callstack:source_locaion  [default 1]
	Emit source location (file,line,column) 

PinPlayLib Controller Knobs


PinPlayLib Code-exclusion Controller Knobs

-log:control 
	Define control events and conditions
-log:controller_default_start  [default 1]
	add default START event
-log:controller_log  [default 0]
	Emit the controller's events log
-log:controller_olog  [default controller-log.txt]
	file name to emit controller's event log
-log:exclude:control 
	Define control events and conditions
-log:exclude:controller_default_start  [default 1]
	add default START event
-log:exclude:controller_log  [default 0]
	Emit the controller's events log
-log:exclude:controller_olog  [default controller-log.txt]
	file name to emit controller's event log
-log:exclude:interactive_file 
	name of file used for interactive communication
-log:exclude:length  [default ]
	Number of instructions to execute before stopping
-log:exclude:regions:epilog  [default 0]
	# of instructions in the epilog region
-log:exclude:regions:in  [default ]
	Regions file
-log:exclude:regions:out  [default ]
	Output file containing regions skipped due to overlap
-log:exclude:regions:overlap_ok  [default 0]
	Allow overlap in regions.
-log:exclude:regions:prolog  [default 0]
	# of instructions in the prolog region
-log:exclude:regions:verbose  [default 0]
	Print information about regions/events 
-log:exclude:regions:warmup  [default 0]
	# of instructions in the warm-up region
-log:exclude:skip  [default ]
	number of instructions to skip
-log:exclude:start_address 
	Address and count to trigger a start
-log:exclude:start_category 
	Trigger a start on seeing an instruction from this XED ISA category
-log:exclude:start_extension 
	Trigger a start on seeing an instruction from this XED ISA extension
-log:exclude:start_int3 
	Trigger a start on seeing an 'int 3' instruction,Requires a count
	argument.
-log:exclude:start_itext 
	Trigger a start on seeing specified instruction bytes (max
	15Bytes=30nibbles)
-log:exclude:start_ssc_mark 
	Trigger a start on seeing specified SSC marker -- big-endian hex 
	without an 0x prefix
-log:exclude:stop_address 
	Address and count to trigger a start
-log:exclude:stop_category 
	Trigger a stop on seeing an instruction from this XED ISA category
-log:exclude:stop_extension 
	Trigger a stop on seeing an instruction from this XED ISA extension
-log:exclude:stop_int3 
	Trigger a stop on seeing an 'int 3' instruction,Requires a count
	argument.
-log:exclude:stop_itext 
	Trigger a stop on seeing specified instruction bytes (max
	15Bytes=30nibbles)
-log:exclude:stop_ssc_mark 
	Trigger a stop on seeing specified SSC marker -- big-endian hex 
	without an 0x prefix
-log:interactive_file 
	name of file used for interactive communication
-log:length  [default ]
	Number of instructions to execute before stopping
-log:regions:epilog  [default 0]
	# of instructions in the epilog region
-log:regions:in  [default ]
	Regions file
-log:regions:out  [default ]
	Output file containing regions skipped due to overlap
-log:regions:overlap_ok  [default 0]
	Allow overlap in regions.
-log:regions:prolog  [default 0]
	# of instructions in the prolog region
-log:regions:verbose  [default 0]
	Print information about regions/events 
-log:regions:warmup  [default 0]
	# of instructions in the warm-up region
-log:skip  [default ]
	number of instructions to skip
-log:start_address 
	Address and count to trigger a start
-log:start_category 
	Trigger a start on seeing an instruction from this XED ISA category
-log:start_extension 
	Trigger a start on seeing an instruction from this XED ISA extension
-log:start_int3 
	Trigger a start on seeing an 'int 3' instruction,Requires a count
	argument.
-log:start_itext 
	Trigger a start on seeing specified instruction bytes (max
	15Bytes=30nibbles)
-log:start_ssc_mark 
	Trigger a start on seeing specified SSC marker -- big-endian hex 
	without an 0x prefix
-log:stop_address 
	Address and count to trigger a start
-log:stop_category 
	Trigger a stop on seeing an instruction from this XED ISA category
-log:stop_extension 
	Trigger a stop on seeing an instruction from this XED ISA extension
-log:stop_int3 
	Trigger a stop on seeing an 'int 3' instruction,Requires a count
	argument.
-log:stop_itext 
	Trigger a stop on seeing specified instruction bytes (max
	15Bytes=30nibbles)
-log:stop_ssc_mark 
	Trigger a stop on seeing specified SSC marker -- big-endian hex 
	without an 0x prefix

Basic block profile knobs

-bbprofile  [default 0]
	Activate bbprofile / isimpoint.
-emit_first  [default 1]
	Emit the first interval (higher overhead to find out first IP)
-emit_last  [default 1]
	Emit the last interval even if it is less than slice_size
-emit_previous_block_counts  [default 0]
	Emit exec counts of preceding blocks in ( blk:count ... ) format
-emit_vectors  [default 1]
	Emit frequency (bb/reuse-dist) vectors at the end of each slice.
-ldv_type  [default none]
	Enable collection of LRU stack distance vectors (none(default),
	"approx", "exact" )
-lengthfile 
	Length(instruction count)  of execution regions: must specify ':tidN'
	suffix.
-nosymbolic  [default 0]
	Do not emit symbolic information for markers
-o  [default out]
	specify bb file name
-pid  [default 0]
	Use PID for naming files.
-slice_size  [default 100000000]
	slice size in instructions

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

PinPlayLib Knobs

-log:allow_cntg_hdr_only  [default 1]
	Logger: allow use of contiguous injection when whole value is in the
	header
-log:allow_deltas  [default 1]
	Logger: allow deltas
-log:allow_reg_deltas  [default 1]
	Logger: allow reg deltas
-log:allow_reg_repeats  [default 1]
	Logger: allow reg repeats
-log:allow_repeats  [default 1]
	Logger: allow repeats
-log:allow_size_reuse  [default 1]
	Logger: allow size reuse
-log:basename  [default log]
	Logger: Specify base name for log files.
-log:btrace  [default 0]
	Logger: Generate branch trace 
-log:check_locks  [default 0]
	Logger: Check locks released after each instruction
-log:compressed  [default none]
	Logger: "none", "gzip" or "bzip2"
-log:dynamic_focus  [default 0]
	Logger: Log dynamic focus thread according to start event
-log:early_detach  [default 0]
	Logger: Detach after generating the log-files for the first region.
-log:early_out  [default 0]
	Logger: Exit after generating the log-files for the first region.
-log:exclude_code  [default ]
	Enable code exclusion. [Range to exclude to be specified by
	'-log:exclude:...' knobs.]
-log:exclude_image 
	Images to exclude from log
-log:exclude_thread 
	Threads to exclude from relog
-log:fat  [default 0]
	Logger: shortcut for '-log:whole_image'             '-log:pages_early
	1' even if not touched)
-log:focus_thread  [default -1]
	Logger: Specifies which thread id to log (defaults to all)
-log:hash_size  [default 262144]
	Logger: Number of buckets in the shadow memory hash table
-log:ignore_thread_injection_event 
	Logger: Ignore injections stop events from the given tid.
-log:image_ops  [default 0]
	Logger: Log image load and unload operations (implies copying image
	files!)
-log:injections  [default 1]
	Logger: set to 0 in order to generate injection-less region.
-log:log_reg_names  [default 0]
	Logger: do not include register names in the *.reg file
-log:log_syscalls_to_sel  [default 0]
	log syscalls to sel file always
-log:mp_atomic  [default 0]
	Application uses atomic instructions  in multi process
-log:mp_attach  [default 0]
	Logger: Attach to an existing pool of processes for multiprocess
	tracing. Unless the key is specified it will attach to the default
	pool name.
-log:mp_create_pool  [default 0]
	Logger: Creates a pool of processes for multiprocess tracing but does
	not perform any tracing or locking.
-log:mp_delete_pool  [default 0]
	Logger: Deletes a pool of processes for multiprocess tracing.
-log:mp_key  [default 0]
	Logger: Key to uniquely identify the pool of processes for
	multiprocess tracing. Unless this knob is specified, the default pool
	name will be used.
-log:mp_mode  [default 0]
	Logger: Creates a process pool for multiprocess tracing.
-log:mp_mode_lock_only  [default 0]
	Logger: Creates a pool of processes for multiprocess tracing but does
	not collect any traces, only acquires the locks to ensure correct
	analysis.
-log:mp_process_names  [default all]
	Logger: Only include the processes whose binary names match the
	processes specified in this list in the process pool.
-log:mt  [default 1]
	Logger: Trace multi-threaded program
-log:non_canonical  [default 0]
	Logger: Support non canonical addresses
-log:page_size  [default 1024]
	Logger: Size of shadow memory page in bytes
-log:pages_early  [default 2]
	Logger: Log pages for dynamically loaded  libraries and for first data
	accesses to the initial memory image.specify 0 or 1.(default changed
	to 1 for ST or LIT, 0 otherwise)
-log:pid  [default 0]
	Logger: Use PID for naming files.
-log:race_data_size  [default 1024]
	Logger: Size of data per race entry in bytes
-log:region_id  [default 0]
	Logger: Use region number for naming files.
-log:stop_at_special_inst  [default 0]
	Logger: Stop log when hit a special inst, which requires an injection
-log:stop_at_syscall  [default 0]
	Logger: Stop log when hit a systemcall.
-log:stop_at_vsyscall  [default 0]
	Logger: Stop log when hit code at the vsyscall area.
-log:strace  [default 0]
	Logger: Generate a system call trace
-log:strict_smc  [default 0]
	Logger: Strict SMC support
-log:syminfo  [default 1]
	Logger: Generate procinfo XML file
-log:whole_image  [default 0]
	Logger: Log all image pages loaded ( even if not touched)
-log:whole_stack  [default 0]
	Logger: Log entire stack by monitoring stack-pointer register.
-pinplay:analysis_assertions  [default 0]
	insert instrumentation code for asserts
-pinplay:disasm  [default 0]
	Use disassembly in iptrace messages
-pinplay:max_threads  [default 32]
	Maximum number of threads allowed
-pinplay:msgfile  [default ]
	Base name of the message file. Any directory name embedded must exist.
	The base name of the pinball is used as the default.
-pinplay:msgon 
	PinPlay: Possible message types:
	info: Informational messages
	(enabled by default)
	all: Enable all messages
	log_syscall: Print
	syscall information during logging
	log_control: Print control (thread
	creation/termination) information during logging
	log_iptrace: Print
	IPs executed during logging
	log_instrument: Print info about
	instrumentation inserted by the logger
	log_mp: Print info about
	multi-process instrumentation and events
	log_signal: Print info about
	signal handling and logging
	log_shadow: Print info about operations
	and handling of the shadow-memory data structure
	log_mem: Print debug
	info on memory operations instrumentation/analysis
	log_data: Print
	debug info on memory values logging
	log_emu: Print debug info on
	emulated instructions
	log_warmup_emu: Print debug info on warmup
	generation for emulated instructions
	log_warmup: Print debug info on
	warmup generation
	log_debug: Print general debugging message during
	logging
	log_text: Print info abou text logging
	log_filehld: Print
	info about Handling of log files during logging
	log_lock: Print lock
	info during logging
	log_mplock: Print mp lock info during logging

	replay_signal: Print info about signal handling and replaying

	replay_syscall: Print syscall information during replay
	addrtx_info:
	Print info about address translation.
	addrtx_debug: Print detailed
	info about address translation.
	smc: Print info about self-modifying
	code checks.
	replay_instrument: Print instrumentation information

	replay_control: Print control (thread creation/termination)
	information during replay
	replay_iptrace: Print IPs executed during
	replay
	replay_image: Print image replay debug information

	replay_mem: Print memory restored during replay
	replay_sync: Print
	memory synchronization during replay
	pinplay_debug: Generic pinplay
	library debugging messages
	replay_text: Print text restoration
	debugging messages
	replay_emu: Print debug info on emulated
	instructions
	code_exclusion: Print info for code exclusion actions

	instrument: Print instrumentation debug info
	shim: Print info for
	shim layer actions
	inst_order: Print info for instrumentation order

	btrace: Print info for btrace processing
	non_canonical: Print info
	for non canonical addresses

-pinplay:work_dir  [default ]
	Pinplay working directory for files
-replay:addr_trans  [default 0]
	Replayer: Relocate address ranges and translate addresses
-replay:addr_trans_hash_size  [default 262144]
	Replayer: Set number of buckets in address translation hash table.
-replay:allow_native_expt  [default 0]
	Replayer: Does not allow native signals during replay.
-replay:app_debug  [default 0]
	Replayer: Enable application debug.
-replay:basename  [default log]
	Replayer: name of the log files
-replay:btrace  [default 0]
	Replayer: Validate branch trace 
-replay:exit_on_syscall  [default 0]
	Replayer: exit thread on seeing a system call ( Works only with
	'-replay:injection 0' )
-replay:fast  [default 0]
	Logger/Replayer: Restore memory values at system call boundaries
-replay:forced_exit  [default 1]
	Replayer: exit thread on reaching logged instruction count
-replay:image_ops  [default 1]
	Replayer: Replay image load and unload callbacks
-replay:injection  [default 1]
	Replayer: Instrument for register/memory injection and thread
	synchronization.
-replay:new_syscalls  [default 1]
	Replayer: use new syscall processing
-replay:pause  [default 0]
	Replayer: Pause the replay before first instruction until gdb is
	attached
-replay:pid  [default 0]
	Replayer: Use PID for naming the message file
-replay:playout  [default 1]
	Replayer: Replay writes to stdout and stderr
-replay:resultfile  [default ]
	Base name of the replay result file. Any directory name embedded must
	exist. The base name of the pinball is used as the default.
-replay:smc  [default 1]
	Enable support for self-modifying code.
-replay:strace  [default 0]
	Replayer: Generate a system call trace
-replay:strict_smc  [default 0]
	Force testing of self-modifying code.

PinPlayLib Logger Skipper Knobs

-log:skip_int3  [default 0]
	Skip 'int 3' instructions.

PinPlayLib Replayer Skipper Knobs

-replay:skip_int3  [default 0]
	Skip 'int 3' instructions.

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

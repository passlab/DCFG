## pin command options (version 3.2)
~~~~
[yan@fornax simple_loop_dependency-pinplay]$ /home/yan/tools/pintool/pinplay-drdebug-3.2-pin-3.2-81205-gcc-linux/pin -help
Pin 3.2
Copyright (c) 2003-2016, Intel Corporation. All rights reserved.
VERSION: 81201 DATE: Feb  2 2017
Usage: pin [OPTION] [-t <tool> [<toolargs>]] -- <command line>
Use -help for a description of options

General switches

-app_filename  [default ]
	filename to use for exec system call of application, empty string will
	use argv[0]
-debug_instrumented_processes  [default 0]
	Print message to allow debugger attach to instrumented processes
-detach_reattach  [default 0]
	Allow detach and reattach in probe mode
-error_file  [default ]
	The error file name
-follow_execv  [default 0]
	Execute with Pin all processes spawned by execv class system calls
-help  [default 0]
	Print help message
-ifeellucky  [default 0]
	skip warning message for unsupported platforms and convert some errors
	to warnings
-injection  [default dynamic]
	Type of injection: self, child, parent, dynamic
-inline  [default 1]
	inline simple analysis routines
-log_inline  [default 0]
	Prints if analysis routine is inlined or not
-logfile  [default pin.log]
	The log file path and file name
-move_then_to_stub  [default 1]
	Move the THEN sequence of IF-THEN instrumentation to the stub section
-mt  [default 1]
	Allow multithreaded programs
-p32  [default ]
	Specify Pin binary for IA-32 architecture
-p64  [default ]
	Specify Pin binary for Intel(R) 64 architecture
-pause_tool  [default 0]
	Print pid and pause for the specified number of seconds so debugger
	can attach just before tool is loaded
-pid  [default 0]
	Attach to process with PID
-probe  [default 0]
	Tool uses Pin Probes
-smc_strict  [default 0]
	Check for self-modifications inside basic block
-smc_support  [default 1]
	Support self-modifying code (SMC)
-t64  [default ]
	Specify tool binary for Intel(R) 64 architecture
-tool_load_option 
	additional options for loading the tool
-unique_error_file  [default 0]
	The error file name will contain the pid
-unique_logfile  [default 0]
	The log file names will contain the pid
-version  [default 0]
	Print version message
-version_long  [default 0]
	Print version/diagnostic message

General switches (available in pin and tool)

-slow_asserts  [default 0]
	Perform expensive sanity checks

Switches to debug the application

-appdebug  [default 0]
	Debug the application, stopping in the debugger as soon as the
	application is launched.
-appdebug_allow_remote  [default 0]
	When application debugging is enabled, the default behavior requires
	the debugger to run on the same system as Pin.  This knob allows Pin
	to connect to an external debugger that runs on a remote system.  This
	knob is ignored when -appdebug_connection is specified because
	-appdebug_connection explicitly specifies the machine on which the
		debugger runs.
-appdebug_connection  [default ]
	When application debugging is enabled, Pin's default behavior is to
	open a TCP port and wait for a debugger to connect.  This knob
	reverses the roles; the debugger opens a TCP port and waits for Pin to
	connect to the port specified in this knob.  The format of the knob
	value should be "[ip]:port".  If the "ip" address is specified, it
	should be in dot-decimal notation.  If "ip" is omitted, Pin connects
	to the specified port on the local machine.  The port number should be
	specified in decimal.  Note that this knob is never used when
	debugging with GDB.
-appdebug_enable  [default 0]
	Enable application level debugger support, but do not stop when the
	application is launched.  Instead, you can connect a debugger after
	launch.
-appdebug_exclude 
	When application debugging and -follow_execv are both specified, the
	default behavior is to enable debugging on all child processes.  This
	knob, which is repeatable, specifies an application name for which
	debugging is disabled.  Debugging is disabled for a process if it's
	argv[0] value matches one of the -appdebug_exclude names.
-appdebug_lldb_options  [default 0]
	Use when connecting with LLDB. This will change the protocol behavior
	to work correctly with LLDB.
-appdebug_server_port  [default 0]
	When application debugging is enabled, Pin's default behavior is to
	bind to a TCP port which is picked by the OS, and wait for a debugger
	to connect.  This knob overrides this behavior and tells PIN to bind
	to a specific TCP port so the debugger will have a well-known port
	where it can connect to the debugged application.
-appdebug_silent  [default 0]
	When application debugging is enabled, Pin normally prints a message
	telling how to connect an external debugger.  This knob disables the
	message.  Pin never prints this message when -appdebug_connection is
	specified.

Code cache switches

-cache_block_size  [default 262144]
	Size (in bytes) of the code cache allocation units. Set to a multiple
	of the pagesize() for best results.
-cc_memory_size  [default 0]
	Max (in bytes) code cache size (0==unlimited). Must be a
	multiplication of block size (see -cache_block_size)

Knobs for constraining memory usage

-pin_memory_range 
	Specify a virtual memory address range for Pin's and the tool's
	dynamic memory allocations. e.g. 0x80000000:0x90000000. The knob may
	be used several times for specifying multiple ranges.
-pin_memory_size  [default 0]
	Max number of bytes that can be dynamically allocated by PIN and tool
	(0 = unlimited, at least 30MB is recommended)
-restrict_memory 
	Restrict memory address ranges from PIN's dynamic loader e.g.:
	0x0:0x100000000

For usage information from a pintool, try pin -t <tool> -h -- <command line>

~~~~

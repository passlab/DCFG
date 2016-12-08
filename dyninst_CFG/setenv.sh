# Modify the following two line to point to the right location of your installation
export DYNINST_INSTALL=/home/yan/pintool/dyninst-install
export LIBDWARF_INSTALL=/home/yan/pintool/dwarf-20161021-install

export LD_LIBRARY_PATH=${DYNINST_INSTALL}/lib:${LIBDWARF_INSTALL}:$LD_LIBRARY_PATH
export DYNINSTAPI_RT_LIB=${DYNINST_INSTALL}/lib/libdyninstAPI_RT.so

# Modify the following two line to point to the right location of your installation
export DYNINST_INSTALL=/home/yan/pintool/dyninst-install

export LD_LIBRARY_PATH=${DYNINST_INSTALL}/lib:$LD_LIBRARY_PATH
export DYNINSTAPI_RT_LIB=${DYNINST_INSTALL}/lib/libdyninstAPI_RT.so

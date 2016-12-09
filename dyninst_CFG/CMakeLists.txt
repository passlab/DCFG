cmake_minimum_required(VERSION 3.5)
project(dyninst_CFG)

# set(DYNINST_INSTALL "/home/yan/pintool/dyninst-install")

# Retrieve shell environment variables for this, confusingly, the same name 
set(DYNINST_INSTALL $ENV{DYNINST_INSTALL})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${DYNINST_INSTALL}/include)
link_directories(${DYNINST_INSTALL}/lib)

add_executable(CFG CFG.cpp)
target_link_libraries(CFG parseAPI symtabAPI dynDwarf dynElf instructionAPI common dyninstAPI)

add_executable(mem_count mem_count.cpp)
target_link_libraries(mem_count parseAPI symtabAPI dynDwarf dynElf instructionAPI common dyninstAPI patchAPI stackwalk)

# add_executable(hello hello.c)

cmake_minimum_required(VERSION 3.28)
project(RISC_V_Tomasulo_CPU_Simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(RISC_V_Tomasulo_CPU_Simulator
        src/main.cpp
        include/Decoder.h
        include/Memory.h
        include/NaiveCPU.h
        src/NaiveCPU.cpp
        include/PC.h
        src/Memory.cpp
        src/Decoder.cpp
        src/RegFile.cpp
        include/ROB.h
        src/ROB.cpp
        include/CDB.h
        src/CDB.cpp
        src/RS.cpp
        include/LSQ.h
        src/LSQ.cpp
        src/ALU.cpp
        src/TomasuloCPU.cpp)

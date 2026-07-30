cmake_minimum_required(VERSION 3.28)
project(RISC_V_Tomasulo_CPU_Simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(RISC_V_Tomasulo_CPU_Simulator
        src/main.cpp
        include/Decoder.h
        include/Memory.h
        include/NaiveCPU.h
        include/PC.h
        include/RegFile.h
        include/ALU.h
        include/ROB.h
        include/CDB.h
        include/LSQ.h
        src/NaiveCPU.cpp
        src/Memory.cpp
        src/Decoder.cpp
        src/RegFile.cpp
        src/ROB.cpp
        src/CDB.cpp
        src/RS.cpp
        src/LSQ.cpp
        src/ALU.cpp
        src/TomasuloCPU.cpp)

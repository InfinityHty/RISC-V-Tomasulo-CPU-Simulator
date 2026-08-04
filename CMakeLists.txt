cmake_minimum_required(VERSION 3.28)
project(RISC_V_Tomasulo_CPU_Simulator)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(code
        src/main.cpp
        src/NaiveCPU.cpp
        src/Memory.cpp
        src/Decoder.cpp
        src/RegFile.cpp
        src/ROB.cpp
        src/CDB.cpp
        src/RS.cpp
        src/LSQ.cpp
        src/ALU.cpp
        src/TomasuloCPU.cpp
        src/AGU.cpp
        include/Commons.h
)

target_include_directories(code PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
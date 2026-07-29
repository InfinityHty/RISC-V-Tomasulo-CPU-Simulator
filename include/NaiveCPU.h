//
// Created by HTY on 2026/7/28.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_CPU_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_CPU_H
#include <iostream>
#include "Memory.h"
#include "Decoder.h"
#include "RegFile.h"
#include "ALU.h"
#include "PC.h"
class NaiveCPU {
public:
    NaiveCPU(Memory mem) {
        memory = mem;
    }
    bool Tick();
private:
    PC pc;
    Memory memory;
    Decoder decoder;
    RegFile reg;
    ALU alu;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_CPU_H
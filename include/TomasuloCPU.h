//
// Created by HTY on 2026/7/29.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_TOMASULOCPU_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_TOMASULOCPU_H
#include "Memory.h"
#include "Decoder.h"
#include "ALU.h"
#include "RegFile.h"
#include "PC.h"
#include "RS.h"
#include "RST.h"
#include "ROB.h"
#include "CDB.h"
#include "LSQ.h"
#include "AGU.h"
class TomasuloCPU {
public:
    TomasuloCPU(Memory& mem) {
        memory = mem;
        counter = 0;
    }
    bool Tick();
    int counter; // 不重复的ROB_id
private:

    Memory memory;
    Decoder decoder;
    ALU alu;
    RegFile reg;
    PC pc;
    RS rs;
    RST rst;
    CDB cdb;
    ROB rob;
    LSQ lsq;
    AGU agu;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_TOMASULOCPU_H
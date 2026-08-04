//
// Created by HTY on 2026/7/28.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_ALU_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_ALU_H
#include "Decoder.h"
#include "PC.h"
#include "RS.h"
#include "CDB.h"
#include <iostream>
class RS;
class ALU {
public:
    uint32_t Execute(InsType type,uint32_t data1,uint32_t data2,uint32_t imm,PC &pc);
    void Execute(RS &rs,CDB &cdb,PC &pc);
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_ALU_H
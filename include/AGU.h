//
// Created by HTY on 2026/8/3.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_AGU_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_AGU_H
#include "LSQ.h"
#include "CDB.h"
class AGU {
public:
    void Execute(LSQ &lsq,CDB &cdb);
    uint32_t Convert(InsType cur,InsType prev,uint32_t data);
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_AGU_H
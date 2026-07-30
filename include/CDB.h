//
// Created by HTY on 2026/7/29.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_CDB_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_CDB_H
#include <cstdint>
#include "ALU.h"
#include "RS.h"
#include "RST.h"
#include "ROB.h"
class ROB;
struct BroadcastContent;
class RS;
class CDB {
public:
    void Broadcast(BroadcastContent &in,RS &rs,ROB &rob);
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_CDB_H
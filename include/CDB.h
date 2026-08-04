//
// Created by HTY on 2026/7/29.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_CDB_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_CDB_H
#include <cstdint>
#include "ALU.h"
#include "RS.h"
#include "ROB.h"
#include "LSQ.h"
#include "Commons.h"
class ROB;
class LSQ;
struct BroadcastContent;
class RS;
class CDB {
public:
    CDB() {
        has_cur = has_nex = false;
    }
    void Broadcast(RS &rs,LSQ &lsq,ROB &rob);
    BroadcastContent cur,nex;
    bool has_cur,has_nex;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_CDB_H
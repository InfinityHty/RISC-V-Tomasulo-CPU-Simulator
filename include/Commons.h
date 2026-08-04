#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_COMMONS_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_COMMONS_H
#include <cstdint>
enum Prediction {
    StrongJump,WeakJump,WeakNotJump,StrongNotJump,NUL
};
struct BroadcastContent {
    int id;
    uint32_t value;
    Prediction pre;
    uint32_t PC_nex;
    BroadcastContent() {
        id = -1;
        value = 0;
        pre = NUL;
        PC_nex = 0;
    }
    BroadcastContent(int id,uint32_t value,Prediction pre,uint32_t PC_nex): id(id),value(value), pre(pre), PC_nex(PC_nex) {
    }
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_COMMONS_H
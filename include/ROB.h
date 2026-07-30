#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_ROB_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_ROB_H
#include <cstdint>
#include "Decoder.h"
#include "RegFile.h"
#include "Memory.h"
#include "RS.h"
class RS;
struct ROBContent {
    int id; // 和RS的id对应相同
    InsType op;
    uint8_t des;
    uint8_t source; // 专门用于store
    uint32_t value;
    bool ready;
    int tick;
    ROBContent() {
        op = unknown;
        source = des = value = 0;
        ready = false;
        id = 0;
        tick = 0;
    }
};
class ROB {
public:
    ROB() {
        head = 0;
        tail = 1;
        counter = 0;
    }
    void Add(Assembly ass);
    void Commit(RegFile &reg,Memory &mem,RST &rst,RS &rs);
    // 写一个循环队列
    ROBContent cont[MAXN];
    int head;
    int tail; // 指向最后一位的后一位
    int counter;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_ROB_H
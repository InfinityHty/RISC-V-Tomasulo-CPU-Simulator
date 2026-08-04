#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_ROB_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_ROB_H
#include <cstdint>
#include "Decoder.h"
#include "RegFile.h"
#include "Memory.h"
#include "RS.h"
#include "LSQ.h"
#include "PC.h"
#include "Commons.h"
#include "CDB.h"
const int ROB_SIZE = 64;
class RS;
class CDB;
struct ROBContent {
    int id; // 和RS的id对应相同
    InsType op;
    uint8_t des;
    uint8_t source; // 专门用于store
    uint32_t value;
    bool ready;
    int tick;
    Prediction pre; // 专门用于branch
    uint32_t PC_nex; // branch
    ROBContent() {
        op = unknown;
        source = des = value = 0;
        ready = false;
        id = 0;
        tick = 0;
        pre = NUL;
        PC_nex = 0;
        // for (int i = 0; i < 32; i++) Qi[i] = -1;
    }
};
class ROB {
public:
    ROB() {
        head = tail = 0;
    }
    void Add(Assembly ass,RST &rst,int ROB_id);
    bool Commit(RegFile &reg,Memory &mem,RST &rst,RS &rs,LSQ &lsq,PC &pc,CDB &cdb);
    void Flush() {
        tail = (head + 1) % ROB_SIZE;
    }
    bool Ready(const int id) const {
        int i = head;
        while (i != tail) {
            if (cont[i].id == id) {
                if (cont[i].ready) return true;
                else return false;
            }
            i = (i + 1) % ROB_SIZE;
        }
        return false;
    }
    uint32_t GetValue(const int id) const {
        int i = head;
        while (i != tail) {
            if (cont[i].id == id) {
                return cont[i].value;
            }
            i = (i + 1) % ROB_SIZE;
        }
        return 0;
    }
    // 写一个循环队列
    ROBContent cont[ROB_SIZE];
    int head;
    int tail; // 指向最后一位的后一位
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_ROB_H
#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_LSQ_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_LSQ_H
#include "Decoder.h"
#include "RegFile.h"
#include "RST.h"
// 只负责load和store的指令管理
struct LSQElement {
    int id;
    InsType op;
    int Qj,Qk;
    bool has_Vj,has_Vk;
    uint32_t data1,data2,imm;
    uint8_t des;
    uint32_t addr;
    bool has_addr;
    LSQElement() {
        id = 0;
        op = unknown;
        has_Vj = has_Vk = false;
        Qj = Qk = 0;
        data1 = data2 = imm = addr = 0;
        des = 0;
        has_addr = false;
    }
};
class LSQ {
public:
    LSQ() {
        total = 0;
    }
    void Add(RegFile &reg,Assembly ass,RST &rst,int ROB_id);
    void Flush() {
        total = 0;
    }
    void Pop() {
        for (int i = 0; i < total - 1; i++) waiting[i] = waiting[i + 1];
        total--;
    }
    LSQElement waiting[100];
    int total;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_LSQ_H
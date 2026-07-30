//
// Created by HTY on 2026/7/29.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_RS_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_RS_H
#include "Decoder.h"
#include "RegFile.h"
#include "CDB.h"
#include "RST.h"
class CDB;
enum Prediction {
    StrongJump,WeakJump,WeakNotJump,StrongNotJump
};
struct RSElement {
    int id; // 分配生产者编号
    InsType op;
    uint32_t data1,data2; // 操作数
    uint32_t imm;
    bool has_Vj,has_Vk;
    int Qj,Qk; // 生产者标签
    uint8_t des;
    uint8_t source; // store从哪里读取
    uint32_t PC_next; // PC下一步跳到哪里
    RSElement() {
        id = 0;
        op = unknown;
        data1 = data2 = imm = Qj = Qk = source = 0;
        des = 0;
        has_Vj = has_Vk = false;
        PC_next = 4;
    }
};
class RS {
public:
    RS() {
        total = 0;
        pre = WeakNotJump;
        counter = 0;
    }
    void Add(RegFile &reg,Assembly ass,RST &rst,uint32_t PC_cur);
    void Receive(CDB &cdb);
    RSElement waiting[1000];
    int total;
    Prediction pre;
private:
    int counter;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_RS_H
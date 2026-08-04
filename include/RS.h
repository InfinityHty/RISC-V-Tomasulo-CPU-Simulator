//
// Created by HTY on 2026/7/29.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_RS_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_RS_H
#include "Decoder.h"
#include "RegFile.h"
#include "RST.h"
#include "Commons.h"
#include "PC.h"
class CDB;
struct RSElement {
    int id; // 分配生产者编号
    InsType op;
    uint32_t data1,data2; // 操作数
    uint32_t imm;
    bool has_Vj,has_Vk;
    int Qj,Qk; // 生产者标签
    uint8_t des;
    uint32_t PC_cur; // PC下一步跳到哪里
    Prediction predict;
    RSElement() {
        id = 0;
        op = unknown;
        data1 = data2 = imm = Qj = Qk = 0;
        des = 0;
        has_Vj = has_Vk = false;
        PC_cur = 0;
        predict = NUL;
    }
};
class RS {
public:
    RS() {
        total = 0;
        pre = NUL;
    }
    void Add(RegFile &reg,Assembly ass,RST &rst,PC &pc,int ROB_id);
    void Flush() {
        total = 0;
    }
    RSElement waiting[1000];
    int total;
    Prediction pre;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_RS_H
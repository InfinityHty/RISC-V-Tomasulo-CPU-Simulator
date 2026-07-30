//
// Created by HTY on 2026/7/28.
//
#include "ALU.h"
uint32_t ALU::Execute(const InsType type, const uint32_t data1, const uint32_t data2,const uint32_t imm,PC &pc) {
    // Arithmetic
    uint32_t cur_cnt = pc.GetCounter();
    if (type == add) return data1 + data2;
    if (type == sub) return data1 - data2;
    if (type == and_) return data1 and data2;
    if (type == or_) return data1 or data2;
    if (type == xor_) return data1 xor data2;
    if (type == sll) return data1 << data2;
    if (type == srl) return data1 >> data2; // 逻辑右移 高位补0
    if (type == sra) return static_cast<int>(data1) >> data2; // 算数右移
    if (type == slt) return static_cast<int>(data1) < static_cast<int>(data2) ? 1: 0;
    if (type == sltu) return data1 < data2 ? 1 : 0;
    if (type == addi) {
        /// std::cerr << data1 + imm << '\n';
        return data1 + imm;
    }
    if (type == andi) return data1 and imm;
    if (type == ori) return data1 or imm;
    if (type == xori) return data1 xor imm;
    if (type == slli) return data1 << imm;
    if (type == srli) return data1 >> imm;
    if (type == srai) return static_cast<int>(data1) >> imm;
    if (type == slti) return static_cast<int>(data1) < static_cast<int>(imm) ? 1 : 0;
    if (type == sltiu) return data1 < imm ? 1 : 0;
    // Memory
    if (type == lb || type == lbu || type == lh || type == lhu || type == lw
        || type == sb || type == sh || type == sw) {
        return data1 + imm; // 返回内存地址
    }
    // Control
    if (type == jal) {
        pc.SetNext(cur_cnt + static_cast<int>(imm));
        // std::cerr << std::hex << cur_cnt << " " << imm << '\n';
        return cur_cnt + 4;
    }
    if (type == jalr) {
        pc.SetNext(data1 + imm);
        return cur_cnt + 4;
    }
    if (type == beq) {
        // std::cerr << "beq d1 " << data1 << " d2 " << data2 << '\n';
        if (data1 == data2) pc.SetNext(cur_cnt + imm);
        return data1 == data2;
    }
    if (type == bge) {
        if (static_cast<int>(data1) >= static_cast<int>(data2)) pc.SetNext(cur_cnt + imm);
        return static_cast<int>(data1) >= static_cast<int>(data2);
    }
    if (type == bgeu) {
        if (data1 >= data2) pc.SetNext(cur_cnt + imm);
        return data1 >= data2;
    }
    if (type == blt) {
        if (static_cast<int>(data1) < static_cast<int>(data2)) pc.SetNext(cur_cnt + imm);
        return static_cast<int>(data1) < static_cast<int>(data2);
    }
    if (type == bltu) {
        if (data1 < data2) pc.SetNext(cur_cnt + imm);
        return data1 < data2;
    }
    if (type == bne) {
        // std::cerr << "bne d1 " << data1 << " d2 " << data2 << '\n';
        if (data1 != data2) pc.SetNext(cur_cnt + imm);
        return data1 != data2;
    }
    // Other
    if (type == auipc) return cur_cnt + imm;
    if (type == lui) return imm;
}

BroadcastContent ALU::Execute(RS &rs) {
    // 一周期只执行一个运算
    BroadcastContent out;
    for (int i = 0; i < rs.total; i++) {
        if (rs.waiting[i].has_Vj && rs.waiting[i].has_Vk) {
            // 执行
            RSElement cur = rs.waiting[i];
            PC pc_tmp; // 不修改实际的pc
            uint32_t output = Execute(cur.op,cur.data1,cur.data2,cur.imm,pc_tmp);
            // 对于branch语句，output返回1说明实际jump
            out = BroadcastContent(cur.id,output);
            // 从RS中删除
            for (int j = i; j < rs.total; j++) {
                rs.waiting[j] = rs.waiting[j + 1];
            }
            rs.total--;
            break;
        }
    }
    return out;
}
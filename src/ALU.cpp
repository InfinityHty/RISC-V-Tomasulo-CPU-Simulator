//
// Created by HTY on 2026/7/28.
//
#include "../include/ALU.h"
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
        std::cerr << "beq d1 " << data1 << " d2 " << data2 << '\n';
        if (data1 == data2) pc.SetNext(cur_cnt + imm);
    }
    if (type == bge) {
        if (static_cast<int>(data1) >= static_cast<int>(data2)) pc.SetNext(cur_cnt + imm);
    }
    if (type == bgeu) {
        if (data1 >= data2) pc.SetNext(cur_cnt + imm);
    }
    if (type == blt) {
        if (static_cast<int>(data1) < static_cast<int>(data2)) pc.SetNext(cur_cnt + imm);
    }
    if (type == bltu) {
        if (data1 < data2) pc.SetNext(cur_cnt + imm);
    }
    if (type == bne) {
        std::cerr << "bne d1 " << data1 << " d2 " << data2 << '\n';
        if (data1 != data2) pc.SetNext(cur_cnt + imm);
    }
    // Other
    if (type == auipc) return cur_cnt + imm;
    if (type == lui) return imm;
    return 0;
}
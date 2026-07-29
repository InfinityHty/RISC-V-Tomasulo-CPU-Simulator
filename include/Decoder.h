//
// Created by HTY on 2026/7/27.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_DECODER_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_DECODER_H
#include <cstdint>
#include <iostream>
enum InsType {
    add,sub,and_,or_,xor_,sll,srl,sra,slt,sltu,
    addi,andi,ori,xori,slli,srli,srai,slti,sltiu,
    lb,lbu,lh,lhu,lw,sb,sh,sw,beq,bge,bgeu,blt,bltu,
    bne,jal,jalr,auipc,lui,unknown
}; // 加一个unknown
struct Assembly {
    InsType type;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t rd;
    uint32_t imm;
    bool quit = false;
    Assembly() {
        type = unknown;
        rs1 = rs2 = rd = imm = 0;
        // has_imm = false;
    }
};
class Decoder {
public:
    // 小端序
    Assembly Decode(const uint8_t *binary_ins);
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_DECODER_H
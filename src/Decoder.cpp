//
// Created by HTY on 2026/7/27.
//
#include "../include/Decoder.h"
Assembly Decoder::Decode(const uint8_t *binary_ins) {
    Assembly as;
    const uint32_t ins = binary_ins[0] + (binary_ins[1] << 8) + (binary_ins[2] << 16) + (binary_ins[3] << 24);
    uint8_t Opcode = ins & 0x7F;
    switch (Opcode) {
        case 0b0110011: {
            // R Type
            uint8_t func3 = (ins & 0x7000) >> 12;
            uint8_t func7 = (ins & 0x7F << 25) >> 25;
            if (func3 == 0b000 && func7 == 0b0000000) {
                as.type = add;
            }
            else if (func3 == 0b000 && func7 == 0b0100000) {
                as.type = sub;
            }
            else if (func3 == 0b111 && func7 == 0b0000000) {
                as.type = and_;
            }
            else if (func3 == 0b110 && func7 == 0b0000000) {
                as.type = or_;
            }
            else if (func3 == 0b100 && func7 == 0b0000000) {
                as.type = xor_;
            }
            else if (func3 == 0b001 && func7 == 0b0000000) {
                as.type = sll;
            }
            else if (func3 == 0b101 && func7 == 0b0000000) {
                as.type = srl;
            }
            else if (func3 == 0b101 && func7 == 0b0100000) {
                as.type = sra;
            }
            else if (func3 == 0b010 && func7 == 0b0000000) {
                as.type = slt;
            }
            else if (func3 == 0b011 && func7 == 0b0000000) {
                as.type = sltu;
            }
            as.rd = (ins & 0xF80) >> 7;
            as.rs1 = (ins & 0xF8000) >> 15;
            as.rs2 = (ins & 0x1F00000) >> 20;
            break;
        }
        case 0b0010011: {
            // Arithmetic部分的I指令和I*指令
            bool is_I = true;
            uint8_t func3 = (ins & 0x7000) >> 12;
            if (func3 == 0b000) {
                as.type = addi;
            }
            else if (func3 == 0b111) {
                as.type = andi;
            }
            else if (func3 == 0b110) {
                as.type = ori;
            }
            else if (func3 == 0b100) {
                as.type = xori;
            }
            else if (func3 == 0b001) {
                uint8_t func7 = (ins & 0x7F << 25) >> 25;
                if (func7 == 0b0000000) {
                    as.type = slli;
                    is_I = false;
                }
            }
            else if (func3 == 0b101) {
                uint8_t func7 = (ins & 0x7F << 25) >> 25;
                if (func7 == 0b0000000) {
                    as.type = srli;
                    is_I = false;
                }
                else if (func7 == 0b0100000) {
                    as.type = srai;
                    is_I = false;
                }
            }
            else if (func3 == 0b010) {
                as.type = slti;
            }
            else if (func3 == 0b011) {
                as.type = sltiu;
            }
            as.rd = (ins & 0xF80) >> 7;
            as.rs1 = (ins & 0xF8000) >> 15;
            if (is_I) {
                as.imm = static_cast<int>(ins >> 20);
            }
            else {
                as.imm = static_cast<int>(ins >> 20 & 0x1F);
            }
            break;
        }
        case 0b0000011: {
            // Memory里的I指令
            uint8_t func3 = (ins & 0x7000) >> 12;
            if (func3 == 0b000) {
                as.type = lb;
            }
            else if (func3 == 0b100) {
                as.type = lbu;
            }
            else if (func3 == 0b001) {
                as.type = lh;
            }
            else if (func3 == 0b101) {
                as.type = lhu;
            }
            else if (func3 ==0b010) {
                as.type = lw;
            }
            as.rd = (ins & 0xF80) >> 7;
            as.rs1 = (ins & 0xF8000) >> 15;
            as.imm = static_cast<int>(ins >> 20);
            break;
        }
        case 0b0100011: {
            // S指令
            uint8_t func3 = (ins & 0x7000) >> 12;
            if (func3 == 0b000) {
                as.type = sb;
            }
            else if (func3 == 0b001) {
                as.type = sh;
            }
            else if (func3 == 0b010) {
                as.type = sw;
            }
            as.rs1 = (ins & 0xF8000) >> 15;
            as.rs2 = (ins & 0x1F00000) >> 20;
            as.imm = static_cast<int>(((ins >> 25) << 5) + (ins >> 7) & 0x1F);
            break;
        }
        case 0b1100011: {
            // B指令
            uint8_t func3 = (ins & 0x7000) >> 12;
            if (func3 == 0b000) {
                as.type = beq;
            }
            else if (func3 == 0b101) {
                as.type = bge;
            }
            else if (func3 == 0b111) {
                as.type = bgeu;
            }
            else if (func3 == 0b100) {
                as.type = blt;
            }
            else if (func3 == 0b110) {
                as.type = bltu;
            }
            else if (func3 == 0b001) {
                as.type = bne;
            }
            as.rs1 = (ins & 0xF8000) >> 15;
            as.rs2 = (ins & 0x1F00000) >> 20;
            as.imm = static_cast<int>((((ins >> 8) & 0xF) + (((ins >> 25) & 0x3F) << 4) + (((ins >> 7) & 1) << 10) + ((ins >> 31) << 11)) << 1);
            break;
        }
        case 0b1101111: {
            // J指令
            as.type = jal;
            as.rd = (ins & 0xF80) >> 7;
            as.imm = static_cast<int>(((ins >> 21 & 0x3FF) + ((ins >> 20 & 1) << 10) + ((ins >> 12 & 0xFF) << 11) + ((ins >> 31) << 19)) << 1);
            break;
        }
        case 0b1100111: {
            // I指令
            uint8_t func3 = (ins & 0x7000) >> 12;
            if (func3 == 0b000) {
                as.type = jalr;
            }
            as.rd = (ins & 0xF80) >> 7;
            as.rs1 = (ins & 0xF8000) >> 15;
            as.imm = static_cast<int>(ins >> 20);
            break;
        }
        case 0b0010111: {
            // 第一个U指令
            as.type = auipc;
            as.rd = (ins & 0xF80) >> 7;
            as.imm = static_cast<int>(ins >> 12);
            break;
        }
        case 0b0110111: {
            // 第二个U指令
            as.type = lui;
            as.rd = (ins & 0xF80) >> 7;
            as.imm = static_cast<int>(ins >> 12);
            break;
        }
        case 0b1110011: {
            // ebreak/ecall 不实现
        }
        default: break;
            // mul是否需要实现？
    }
    return as;
}
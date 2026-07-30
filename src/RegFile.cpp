//
// Created by HTY on 2026/7/28.
//
#include "RegFile.h"
void RegFile::Write(InsType type, const uint8_t des,const uint32_t output,const uint32_t load) {
    if (type == add || type == sub || type == and_ || type == or_
        || type == xor_ || type == sll || type == srl || type == sra
        || type == slt || type == sltu || type == addi || type == andi
        || type == ori || type == xori || type == slli || type == srli
        || type == srai || type == slti || type == sltiu || type == jal
        || type == jalr || type == auipc || type == lui) {
        storage[des] = output;
    }
    if (type == lb || type == lbu || type == lh || type == lhu
        || type == lw) {
        storage[des] = load;
    }
}
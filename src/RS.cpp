//
// Created by HTY on 2026/7/29.
//
#include "RS.h"
void RS::Add(RegFile &reg,Assembly ass,RST &rst,uint32_t PC_cur) {
    RSElement cur;
    cur.id = counter++; // 分配唯一的标签
    cur.op = ass.type;
    cur.PC_next = PC_cur + 4;
    // Arithmetic
    if (ass.type == add || ass.type == sub || ass.type == and_ || ass.type == or_
        || ass.type == xor_ || ass.type == sll || ass.type == srl || ass.type == sra
        || ass.type == slt || ass.type == sltu) {
        // 左右运算数取自rs1 rs2
        if (rst.HasTag(ass.rs1)) cur.Qj = ass.rs1;
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1,0).data1;
        }
        if (rst.HasTag(ass.rs2)) cur.Qk = ass.rs2;
        else {
            cur.has_Vk = true;
            cur.data2 = reg.GetData(0,ass.rs2).data2;
        }
        cur.des = ass.rd;
        rst.Qi[ass.rd] = cur.id; // 更新寄存器状态表标签
    }
    if (ass.type == addi || ass.type == andi || ass.type == ori || ass.type == xori
        || ass.type == slli || ass.type == srli || ass.type == srai || ass.type == slti
        || ass.type == sltiu) {
        // 左运算数来自rs1 右运算数来自imm
        if (rst.HasTag(ass.rs1)) cur.Qj = ass.rs1;
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1,0).data1;
        }
        cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.des = ass.rd;
        rst.Qi[ass.rd] = cur.id;
    }
    // Load
    if (ass.type == lb || ass.type == lbu || ass.type == lh || ass.type == lhu || ass.type == lw) {
        if (rst.HasTag(ass.rs1)) cur.Qj = ass.rs1;
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1,0).data1;
        }
        cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.des = ass.rd;
        rst.Qi[ass.rd] = cur.id;
    }
    // Store
    if (ass.type == sb || ass.type == sh || ass.type == sw) {
        if (rst.HasTag(ass.rs1)) cur.Qj = ass.rs1;
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1,0).data1;
        }
        cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.source = ass.rs2;
    }
    // Branch
    if (ass.type == beq || ass.type == bge || ass.type == bgeu || ass.type == blt
        || ass.type == bltu || ass.type == bne || ass.type) {
        if (rst.HasTag(ass.rs1)) cur.Qj = ass.rs1;
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1).data1;
        }
        if (rst.HasTag(ass.rs2)) cur.Qk = ass.rs2;
        else {
            cur.has_Vk = true;
            cur.data2 = reg.GetData(0,ass.rs2).data2;
        }
        // 投机执行
        if (pre == StrongJump || pre == WeakJump) {
            cur.PC_next = PC_cur + ass.imm;
        }
    }
    // Jump And Link (TBD)
    if (ass.type == jal) {

    }
    if (ass.type == jalr) {
    }
    // Other
    if (ass.type == auipc) {

    }
    if (ass.type == lui) {

    }
    // 加入RS
    waiting[total++] = cur;
}
//
// Created by HTY on 2026/7/29.
//
#include "ROB.h"
void ROB::Add(Assembly ass) {
    ROBContent cur;
    cur.op = ass.type;
    if (ass.type == sb || ass.type == sh || ass.type == sw) {
        cur.source = ass.rd;
    }
    else {
        cur.des = ass.rd;
    }
    cur.id = counter++;
    cur.ready = false;
    cont[tail++] = cur;
    tail %= MAXN; // 模拟循环队列
}
void ROB::Commit(RegFile &reg,Memory &mem,RST &rst,RS &rs) {
    ROBContent cur = cont[head];
    if (cur.ready) {
        // 队首准备好了
        // 写入寄存器
        if (cur.op == add || cur.op == sub || cur.op == and_ || cur.op == or_
        || cur.op == xor_ || cur.op == sll || cur.op == srl || cur.op == sra
        || cur.op == slt || cur.op == sltu || cur.op == addi || cur.op == andi
        || cur.op == ori || cur.op == xori || cur.op == slli || cur.op == srli
        || cur.op == srai || cur.op == slti || cur.op == sltiu) {
            reg.Write(cur.op,cur.des,cur.value,0);
            if (rst.Qi[cur.des] == cur.id) rst.Qi[cur.des] = -1; // 去掉RST标记
        }
        // 模拟3周期内存读写
        if (cur.op == lb || cur.op == lbu || cur.op == lh || cur.op == lhu
            || cur.op == lw || cur.op == sb || cur.op == sh || cur.op == sw) {
            //
        }
        // 分支预测
        if (cur.op == beq || cur.op == bge || cur.op == bgeu || cur.op == blt
            || cur.op == bltu || cur.op == bne) {
            // 预测错误 需要撤销
            if (cur.value == 1) {
                if (rs.pre == StrongNotJump) {

                }
                if (rs.pre == WeakNotJump) {

                }
            }
            if (cur.value == 0) {
                if (rs.pre == StrongJump) {

                }
                if (rs.pre == WeakJump) {

                }
            }
        }
        // 跳转
        head++;
        head %= MAXN;
    }
}
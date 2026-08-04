//
// Created by HTY on 2026/7/30.
//
#include "LSQ.h"
void LSQ::Add(RegFile &reg,Assembly ass,RST &rst,ROB &rob,PC &pc,int ROB_id) {
    if (ass.type != lb && ass.type != lbu && ass.type != lh && ass.type != lhu
        && ass.type != lw && ass.type != sb && ass.type != sh && ass.type != sw) return;
    if (rob.Full()) {
        pc.SetCounter(pc.GetCounter());
        return;
    }
    LSQElement cur;
    cur.id = ROB_id;
    cur.op = ass.type;
    // Load
    if (ass.type == lb || ass.type == lbu || ass.type == lh || ass.type == lhu || ass.type == lw) {
        if (rst.HasTag(ass.rs1)) {
            if (!rob.Ready(rst.Qi[ass.rs1]))
                cur.Qj = rst.Qi[ass.rs1];
            else {
                cur.has_Vj = true;
                cur.data1 = rob.GetValue(rst.Qi[ass.rs1]);
            }
        }
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
        if (rst.HasTag(ass.rs1)) {
            if (!rob.Ready(rst.Qi[ass.rs1]))
                cur.Qj = rst.Qi[ass.rs1];
            else {
                cur.has_Vj = true;
                cur.data1 = rob.GetValue(rst.Qi[ass.rs1]);
            }
        }
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1,0).data1;
        }
        if (rst.HasTag(ass.rs2)) {
            if (!rob.Ready(rst.Qi[ass.rs2]))
                cur.Qk = rst.Qi[ass.rs2];
            else {
                cur.has_Vk = true;
                cur.data2 = rob.GetValue(rst.Qi[ass.rs2]);
            }
        }
        else {
            cur.has_Vk = true;
            cur.data2 = reg.GetData(0,ass.rs2).data2;
        }
        cur.imm = ass.imm;
    }
    waiting[total++] = cur;
}
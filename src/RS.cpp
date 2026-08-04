#include "RS.h"
void RS::Add(RegFile &reg,Assembly ass,RST &rst,PC &pc,int ROB_id) {
    if (ass.type == lb || ass.type == lbu || ass.type == lh || ass.type == lhu
        || ass.type == lw || ass.type == sb || ass.type == sh || ass.type == sw) return;
    RSElement cur;
    cur.id = ROB_id; // 分配唯一的标签
    cur.op = ass.type;
    cur.PC_cur = pc.GetCounter();
    pc.SetNext(cur.PC_cur + 4);
    // Arithmetic
    if (ass.type == add || ass.type == sub || ass.type == and_ || ass.type == or_
        || ass.type == xor_ || ass.type == sll || ass.type == srl || ass.type == sra
        || ass.type == slt || ass.type == sltu) {
        // 左右运算数取自rs1 rs2
        if (rst.HasTag(ass.rs1)) cur.Qj = rst.branch[rst.num].Qi[ass.rs1];
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1,0).data1;
        }
        if (rst.HasTag(ass.rs2)) cur.Qk = rst.branch[rst.num].Qi[ass.rs2];
        else {
            cur.has_Vk = true;
            cur.data2 = reg.GetData(0,ass.rs2).data2;
        }
        cur.des = ass.rd;
        rst.branch[rst.num].Qi[ass.rd] = cur.id; // 更新寄存器状态表标签
    }
    if (ass.type == addi || ass.type == andi || ass.type == ori || ass.type == xori
        || ass.type == slli || ass.type == srli || ass.type == srai || ass.type == slti
        || ass.type == sltiu) {
        // 左运算数来自rs1 右运算数来自imm
        if (rst.HasTag(ass.rs1)) cur.Qj = rst.branch[rst.num].Qi[ass.rs1];
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1,0).data1;
        }
        cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.des = ass.rd;
        rst.branch[rst.num].Qi[ass.rd] = cur.id;
    }
    // Branch
    if (ass.type == beq || ass.type == bge || ass.type == bgeu || ass.type == blt
        || ass.type == bltu || ass.type == bne) {
        if (rst.HasTag(ass.rs1)) cur.Qj = rst.branch[rst.num].Qi[ass.rs1];
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1).data1;
        }
        if (rst.HasTag(ass.rs2)) cur.Qk = rst.branch[rst.num].Qi[ass.rs2];
        else {
            cur.has_Vk = true;
            cur.data2 = reg.GetData(0,ass.rs2).data2;
        }
        cur.imm = ass.imm;
        // rst里开一个新的branch 把上一个版本的copy过去
        rst.num++;
        rst.Copy();
        // 投机执行
        cur.predict = pre;
        if (pre == StrongJump || pre == WeakJump) {
            pc.SetNext(cur.PC_cur + ass.imm); // 直接改pc
        }
    }
    // Jump And Link
    if (ass.type == jal) {
        cur.has_Vj = cur.has_Vk = true;
        pc.SetNext(cur.PC_cur + ass.imm);
        cur.des = ass.rd;
    }
    // 等待
    if (ass.type == jalr) {
        if (rst.HasTag(ass.rs1)) cur.Qj = rst.branch[rst.num].Qi[ass.rs1];
        else {
            cur.has_Vj = true;
            cur.data1 = reg.GetData(ass.rs1).data1;
        }
        cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.des = ass.rd;
        if (cur.has_Vj) {
            pc.SetNext(cur.data1 + cur.imm);
        }
        else {
            pc.SetNext(cur.PC_cur); // 停在这一步直到准备好 先不加入RS
            return;
        }
    }
    // Other
    if (ass.type == auipc) {
        cur.has_Vj = cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.des = ass.rd;
    }
    if (ass.type == lui) {
        cur.has_Vj = cur.has_Vk = true;
        cur.des = ass.rd;
        cur.imm = ass.imm;
    }
    // 加入RS
    waiting[total++] = cur;
}

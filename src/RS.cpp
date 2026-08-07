#include "RS.h"
void RS::Fetch(Assembly ass,PC &pc) {
    if (!has_append) {
        // Successfully fetch
        has_append = true;
        append.ass = ass;
        append.pc = pc;
        append.pre = pre;
        uint32_t cur_cnt = pc.GetCounter();
        pc.SetNext(cur_cnt + 4);
        if (ass.type == beq || ass.type == bge || ass.type == bgeu || ass.type == bltu
            || ass.type == blt || ass.type == bne) {
            if (pre == WeakJump || pre == StrongJump) {
                pc.SetNext(cur_cnt + ass.imm); // 投机执行
            }
        }
        if (ass.type == jal) {
            pc.SetNext(cur_cnt + ass.imm);
        }
        if (ass.type == jalr) {
            pc.SetNext(cur_cnt);
        }
    }
    else {
        // Unsuccessful fetch
        pc.SetNext(pc.GetCounter());
    }
}
void RS::Issue(RegFile &reg,RST &rst,ROB &rob,PC &pc,int ROB_id) {
    if (!has_append) return;
    // 这些都是预先存在append里的
    Assembly ass = append.ass;

    if (rob.Full()) {
        pc.SetNext(pc.GetCounter()); // jammed
        return;
    }
    if (ass.type == lb || ass.type == lbu || ass.type == lh || ass.type == lhu
        || ass.type == lw || ass.type == sb || ass.type == sh || ass.type == sw) {
        has_append = false;
        return;
    }

    RSElement cur;
    cur.id = ROB_id; // 分配唯一的标签
    cur.op = ass.type;
    cur.PC_cur = append.pc.GetCounter();

    // Arithmetic
    if (ass.type == add || ass.type == sub || ass.type == and_ || ass.type == or_
        || ass.type == xor_ || ass.type == sll || ass.type == srl || ass.type == sra
        || ass.type == slt || ass.type == sltu) {
        // 左右运算数取自rs1 rs2
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
        cur.des = ass.rd;
        rst.Qi[ass.rd] = cur.id; // 更新寄存器状态表标签
    }
    if (ass.type == addi || ass.type == andi || ass.type == ori || ass.type == xori
        || ass.type == slli || ass.type == srli || ass.type == srai || ass.type == slti
        || ass.type == sltiu) {
        // 左运算数来自rs1 右运算数来自imm
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
    // Branch
    if (ass.type == beq || ass.type == bge || ass.type == bgeu || ass.type == blt
        || ass.type == bltu || ass.type == bne) {
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
            cur.data1 = reg.GetData(ass.rs1).data1;
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
        // 投机执行记录
        cur.predict = append.pre;
    }
    // Jump And Link
    if (ass.type == jal) {
        cur.has_Vj = cur.has_Vk = true;
        cur.des = ass.rd;
        rst.Qi[ass.rd] = cur.id;
    }
    // 等待
    if (ass.type == jalr) {
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
            cur.data1 = reg.GetData(ass.rs1).data1;
        }
        cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.des = ass.rd;
        if (cur.has_Vj) {
            pc.SetNext(cur.data1 + cur.imm); // 修改一下next_step
            rst.Qi[ass.rd] = cur.id;
        }
        else {
            // 停在这一步直到准备好 先不加入RS
            return;
        }
    }
    // Other
    if (ass.type == auipc) {
        cur.has_Vj = cur.has_Vk = true;
        cur.imm = ass.imm;
        cur.des = ass.rd;
        rst.Qi[ass.rd] = cur.id;
    }
    if (ass.type == lui) {
        cur.has_Vj = cur.has_Vk = true;
        cur.des = ass.rd;
        cur.imm = ass.imm;
        rst.Qi[ass.rd] = cur.id;
    }
    // Issue successfully
    waiting[total++] = cur;
    rob.Add(ass,rst,ROB_id);
    has_append = false; // delete from append
}

#include "ROB.h"
void ROB::Add(Assembly ass,RST &rst,int ROB_id) {
    if (ass.type == jalr && rst.HasTag(ass.rs1)) return;
    ROBContent cur;
    cur.op = ass.type;
    cur.pre = NUL; // 专门接收分支预测结果
    if (ass.type == sb || ass.type == sh || ass.type == sw) {
        cur.source = ass.rd;
    }
    else {
        cur.des = ass.rd;
    }
    cur.id = ROB_id;
    cur.ready = false;
    cont[tail++] = cur;
    tail %= 128; // 模拟循环队列
}
bool ROB::Commit(RegFile &reg,Memory &mem,RST &rst,RS &rs,LSQ &lsq,PC &pc,CDB &cdb) {
    ROBContent& cur = cont[head];
    if (cur.op == quit) {
        std::cout << (reg.GetData(10).data1 & 0xFF) << '\n';
        return true;
    }
    if (cur.ready) {
        // 队首准备好了
        // 写入寄存器
        if (cur.op == add || cur.op == sub || cur.op == and_ || cur.op == or_
        || cur.op == xor_ || cur.op == sll || cur.op == srl || cur.op == sra
        || cur.op == slt || cur.op == sltu || cur.op == addi || cur.op == andi
        || cur.op == ori || cur.op == xori || cur.op == slli || cur.op == srli
        || cur.op == srai || cur.op == slti || cur.op == sltiu ||cur.op == lb
        || cur.op == lbu || cur.op == lh || cur.op == lhu || cur.op == lw
        || cur.op == jal || cur.op == jalr || cur.op == auipc || cur.op == lui) {
            reg.Write(cur.op,cur.des,cur.value,cur.value);
            if (cur.op == lb || cur.op == lbu || cur.op == lh || cur.op == lhu || cur.op == lw) lsq.Pop();
            if (rst.branch[rst.num].Qi[cur.des] == cur.id) rst.branch[rst.num].Qi[cur.des] = -1; // 去掉RST标记
            head++;
            head %= 128;
        }
        // 分支预测
        if (cur.op == beq || cur.op == bge || cur.op == bgeu || cur.op == blt
            || cur.op == bltu || cur.op == bne) {
            // 预测正确与否判断
            if (cur.value == 1) {
                // 正确
                if (cur.pre == StrongJump) {
                    rs.pre = StrongJump;
                }
                if (cur.pre == WeakJump) {
                    rs.pre = StrongJump;
                }
                if (cur.pre == WeakNotJump) {
                    // 预测错误 需要flush
                    rs.Flush();
                    lsq.Flush();
                    Flush();
                    rst.num--;
                    rs.pre = WeakJump;
                    pc.SetCounter(cur.PC_nex);
                }
                if (cur.pre == StrongNotJump) {
                    rs.Flush();
                    lsq.Flush();
                    Flush();
                    rst.num--;
                    rs.pre = WeakNotJump;
                    pc.SetCounter(cur.PC_nex);
                }
            }
            else if (cur.value == 0) {
                if (cur.pre == StrongJump) {
                    rs.Flush();
                    lsq.Flush();
                    Flush();
                    rst.num--;
                    rs.pre = WeakJump;
                    pc.SetCounter(cur.PC_nex);
                }
                if (cur.pre == WeakJump) {
                    rs.Flush();
                    lsq.Flush();
                    Flush();
                    rst.num--;
                    rs.pre = WeakNotJump;
                    pc.SetCounter(cur.PC_nex);
                }
                if (cur.pre == WeakNotJump) {
                    rs.pre = StrongNotJump;
                }
                if (cur.pre == StrongNotJump) {
                    rs.pre = StrongNotJump;
                }
            }
        }

    }
    else {
        // 没准备好 只能是文件读写
        // 进行真正的文件读写 模拟3个周期
        // if (cur.tick < 2) {
        //     cur.tick++;
        //     return false;
        // }
        // store
        if (cur.op == sb || cur.op == sh || cur.op == sw) {
            // 真正写入内存
            mem.AccessData(cur.op,lsq.waiting[0].data2,lsq.waiting[0].addr);
            head++;
            head %= 128;
            lsq.Pop();
        }
        if (cur.op == lb || cur.op == lbu || cur.op == lh || cur.op == lhu || cur.op == lw) {
            // 读取
            if (!cdb.has_nex) {
                cur.value = mem.AccessData(cur.op,0,lsq.waiting[0].addr);
                cur.ready = true; // 下一个周期写入寄存器
                cdb.has_nex = true;
                cdb.nex = BroadcastContent(cur.id,cur.value,NUL,0);
            }
        }
    }
    return false;
}
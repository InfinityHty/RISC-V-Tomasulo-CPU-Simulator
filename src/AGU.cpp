#include "AGU.h"
void AGU::Execute(LSQ &lsq ,CDB &cdb) {
    for (int i = 0; i < lsq.total; i++) {
        LSQElement& cur = lsq.waiting[i];
        if (cur.has_Vj && cur.has_Vk && !cur.has_addr) {
            // 每一个周期AGU计算一个 和ALU并行
            cur.addr = cur.imm + cur.data1;
            cur.has_addr = true;
            break;
        }
    }
    if (cdb.has_nex) return; // CDB已经被占
    // 旁路检测 如果可以直接赋值就发布
    for (int i = 0; i < lsq.total; i++) {
        LSQElement& cur = lsq.waiting[i];
        if (!cur.has_addr) break;
        if (cur.op == lb || cur.op == lbu || cur.op == lh || cur.op == lhu || cur.op == lw) {
            for (int j = i - 1; j >= 0; j--) {
                LSQElement prev = lsq.waiting[j];
                if (prev.addr == cur.addr && (prev.op == sb || prev.op == sh || prev.op == sw) && prev.has_Vk) {
                    cdb.nex = BroadcastContent(cur.id,Convert(cur.op,prev.op,prev.data2),NUL,0);
                    cdb.has_nex = true;
                    return; // CDB广播
                }
            }
        }
    }
}
uint32_t AGU::Convert(InsType cur,InsType prev,uint32_t data) {
    uint32_t ans = data;
    if (prev == sb) ans = ans & 0xFF;
    if (prev == sh) ans = ans & 0xFFFF;

    if (cur == lb) ans = static_cast<int>((ans & 0xFF) << 24) >> 24;
    if (cur == lbu) ans = ans & 0xFF;
    if (cur == lh) ans = static_cast<int>((ans & 0xFFFF) << 16) >> 16;
    if (cur == lhu) ans = ans & 0xFFFF;
    return ans;
}
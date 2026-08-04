//
// Created by HTY on 2026/7/29.
//
#include "CDB.h"
void CDB::Broadcast(RS &rs,LSQ &lsq,ROB &rob) {
    if (has_cur) {
        for (int i = 0; i < rs.total; i++) {
            // RS接受Vj/Vk
            if (rs.waiting[i].Qj == cur.id) {
                rs.waiting[i].data1 = cur.value;
                rs.waiting[i].has_Vj = true;
            }
            if (rs.waiting[i].Qk == cur.id) {
                rs.waiting[i].data2 = cur.value;
                rs.waiting[i].has_Vk = true;
            }
        }
        for (int i = 0; i < lsq.total; i++) {
            // LSQ
            if (lsq.waiting[i].Qj == cur.id) {
                lsq.waiting[i].data1 = cur.value;
                lsq.waiting[i].has_Vj = true;
            }
            if (lsq.waiting[i].Qk == cur.id) {
                lsq.waiting[i].data2 = cur.value;
                lsq.waiting[i].has_Vk = true;
            }
        }
        for (int i = rob.head; i < rob.tail; i++) {
            // ROB写入
            if (rob.cont[i].id == cur.id) {
                rob.cont[i].value = cur.value;
                rob.cont[i].ready = true;
                rob.cont[i].pre = cur.pre; // 分支预测专用
                rob.cont[i].PC_nex = cur.PC_nex;
            }
        }
    }
    if (has_nex) {
        cur = nex;
        has_cur = true;
        has_nex = false;
    }
}
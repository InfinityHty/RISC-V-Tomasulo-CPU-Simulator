//
// Created by HTY on 2026/7/29.
//
#include "CDB.h"
void CDB::Broadcast(BroadcastContent &in,RS &rs,ROB &rob) {
    for (int i = 0; i < rs.total; i++) {
        // RS接受Vj/Vk
        if (rs.waiting[i].Qj == in.id) {
            rs.waiting[i].data1 = in.value;
            rs.waiting[i].has_Vj = true;
        }
        if (rs.waiting[i].Qk == in.id) {
            rs.waiting[i].data2 = in.value;
            rs.waiting[i].has_Vk = true;
        }
    }
    for (int i = rob.head; i < rob.tail; i++) {
        // ROB写入
        if (rob.cont[i].id == in.id) {
            rob.cont[i].value = in.value;
            rob.cont[i].ready = true;
        }
    }
}
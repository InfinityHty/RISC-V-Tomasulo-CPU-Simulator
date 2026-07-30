//
// Created by HTY on 2026/7/29.
//
#include "../include/TomasuloCPU.h"
// 模拟线缆广播传输
bool CPU::Tick(BroadcastContent &in,BroadcastContent &out) {
    // set zero 0
    reg.SetZero();
    // Instruction Fetch
    uint8_t binary_ins[4];
    uint32_t cur_cnt = pc.GetCounter();
    std::cerr << std::hex << cur_cnt << std::dec << '\n';
    for (int i = 0; i < 4; i++) {
        binary_ins[i] = memory.GetBinaryIns(cur_cnt + i);
    }
    // Instruction Decode
    Assembly assembly_ins = decoder.Decode(binary_ins);
    // Issue
    rs.Add(reg,assembly_ins,rst,cur_cnt);
    rob.Add(assembly_ins);
    // Execute
    out = alu.Execute(rs);
    // Write Result
    cdb.Broadcast(in,rs,rob);
    // Commit
    rob.Commit(reg,memory,rst,rs);
}
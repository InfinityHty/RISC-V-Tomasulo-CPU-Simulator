//
// Created by HTY on 2026/7/29.
//
#include "TomasuloCPU.h"
bool TomasuloCPU::Tick() {
    // set zero 0
    reg.SetZero();
    // Dispatch ROB_ID
    counter++;
    // Instruction Fetch
    uint8_t binary_ins[4];
    uint32_t cur_cnt = pc.GetCounter();
    std::cerr << std::hex << cur_cnt << std::dec << '\n';
    std::cerr << (reg.GetData(10).data1 & 0xFF) << '\n';
    for (int i = 0; i < 4; i++) {
        binary_ins[i] = memory.GetBinaryIns(cur_cnt + i);
    }
    // Instruction Decode
    Assembly assembly_ins = decoder.Decode(binary_ins);

    // Issue
    rs.Add(reg,assembly_ins,rst,pc,counter);
    lsq.Add(reg,assembly_ins,rst,counter);
    rob.Add(assembly_ins,rst,counter);
    // Execute
    alu.Execute(rs,cdb,pc);
    agu.Execute(lsq,cdb);
    // Write Result
    cdb.Broadcast(rs,lsq,rob);
    // Commit
    bool flag = rob.Commit(reg,memory,rst,rs,lsq,pc,cdb);
    pc.Tick();
    return flag;
}
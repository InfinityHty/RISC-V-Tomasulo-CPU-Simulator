//
// Created by HTY on 2026/7/28.
//
// 先写一个单级流水(naive simulator)
#include "NaiveCPU.h"
bool NaiveCPU::Tick() {
    // set zero 0
    reg.SetZero();
    // Instruction Fetch
    uint8_t binary_ins[4];
    uint32_t cur_cnt = pc.GetCounter();
    // std::cerr << std::hex << cur_cnt << std::dec << '\n';
    for (int i = 0; i < 4; i++) {
        binary_ins[i] = memory.GetBinaryIns(cur_cnt + i);
    }
    // Instruction Decode
    Assembly assembly_ins = decoder.Decode(binary_ins);
    // Execute
    DataPair data = reg.GetData(assembly_ins.rs1,assembly_ins.rs2);
    // Exit
    if (assembly_ins.quit) {
        std::cout << (data.data1 & 0xFF) << '\n';
        return true;
    }
    uint32_t output = alu.Execute(assembly_ins.type,data.data1,data.data2,assembly_ins.imm,pc);
    // Memory Access
    uint32_t load = memory.AccessData(assembly_ins.type,data.data2,output);
    // Write Back
    reg.Write(assembly_ins.type,assembly_ins.rd,output,load);
    pc.Tick();
    return false;
}

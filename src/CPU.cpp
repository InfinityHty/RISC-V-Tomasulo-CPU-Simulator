//
// Created by HTY on 2026/7/28.
//
#include "../include/CPU.h"
bool CPU::Tick() {
    // Instruction Fetch
    uint8_t binary_ins[4];
    int cur_cnt = pc.GetCounter();
    for (int i = 0; i < 4; i++) {
        binary_ins[i] = memory.GetBinaryIns(cur_cnt + i);
    }
    // Instruction Decode
    Assembly assembly_ins = decoder.Decode(binary_ins);
    // Execute
    alu.Execute(assembly_ins,pc,);
    // Memory Access
    memory.GetData();
    // Write Back
    reg.Write();
    return false;
}

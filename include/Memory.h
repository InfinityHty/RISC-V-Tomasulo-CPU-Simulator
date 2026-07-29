//
// Created by HTY on 2026/7/28.
//
#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_MEMORY_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_MEMORY_H
#include <cstdint>
#include <iostream>
#include "Decoder.h"
const int MAXN = 1e6 + 5;
class Memory {
public:
    Memory() {
        for (int i = 0; i < MAXN; i++) {
            instructions[i] = 0;
            data[i] = 0;
        }
    }
    void Load();
    uint8_t GetBinaryIns(const uint32_t addr) const {
        return instructions[addr];
    }
    uint32_t AccessData(InsType type,uint32_t cont,uint32_t addr);
private:
    uint8_t instructions[MAXN]{}; // 指令
    uint8_t data[MAXN]{}; // 数据
    static int AddressToIndex(const char *addr) {
        int index = 0,digit = 0;
        for (int i = 7; i >= 0; i--) {
            index += (addr[i] - '0') * (1 << (digit * 4));
            digit++;
        }
        return index;
    }
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_MEMORY_H
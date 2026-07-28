//
// Created by HTY on 2026/7/28.
//
#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_MEMORY_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_MEMORY_H
#include<cstdint>
const long long MAXN = 1e5 + 5;
class Memory {
public:
    Memory() {
        for (int i = 0; i < MAXN; i++) {
            instructions[i] = 0;
            data[i] = 0;
        }
    }
    void Load();
    uint8_t GetBinaryIns(const int addr) const {
        return instructions[addr];
    }
    void GetData();
private:
    uint8_t instructions[MAXN]{}; // 指令
    int data[MAXN]{}; // 数据
    static int AddressToIndex(const char *addr) {
        int index = 0,digit = 0;
        for (int i = 7; i >= 0; i--) {
            index += addr[i] * (1 << (digit * 4));
            digit++;
        }
        return index;
    }
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_MEMORY_H
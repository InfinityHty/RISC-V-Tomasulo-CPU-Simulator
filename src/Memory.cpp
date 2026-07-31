//
// Created by HTY on 2026/7/28.
//
#include "Memory.h"
#include <iostream>
void Memory::Load() {
    char line[100];
    int cur_add = 0;
    // std::cin.ignore();
    while (std::cin.getline(line,50)) {
        if (line[0] == '\0') break;
        if (line[0] == '@') {
            cur_add = AddressToIndex(line + 1);
        }
        else {
            int i = 0;
            while (line[i] != '\0') {
                // Read 1 byte
                if (line[i] >= '0' && line[i] <= '9') mem[cur_add] = (line[i] - '0') * 16;
                else mem[cur_add] = (line[i] - 'A' + 10) * 16;
                if (line[i + 1] >= '0' && line[i + 1] <= '9') mem[cur_add] += line[i + 1] - '0';
                else mem[cur_add] += line[i + 1] - 'A' + 10;
                cur_add++;
                i += 2;
                if (line[i] == ' ') i++;
            }
        }
    }
}
uint32_t Memory::AccessData(InsType type,uint32_t cont,uint32_t addr) {
    // Load
    // 小端序
    if (type == lb) {
        return static_cast<int>(mem[addr] << 24) >> 24;
    }
    if (type == lbu) return mem[addr];
    if (type == lh) {
        return static_cast<int>((mem[addr] + (mem[addr + 1] << 8)) << 16) >> 16;
    }
    if (type == lhu) return mem[addr] + (mem[addr + 1] << 8);
    if (type == lw) {
        // std::cerr << "addr: " << addr << '\n';
        return mem[addr] + (mem[addr + 1] << 8) + (mem[addr + 2] << 16) + (mem[addr + 3] << 24);
    }
    // Store
    if (type == sb) {
        mem[addr] = cont & 0xFF;
    }
    if (type == sh) {
        mem[addr] = cont & 0xFF;
        mem[addr + 1] = (cont >> 8) & 0xFF;
    }
    if (type == sw) {
        // std::cerr << "cont: " << cont << "addr: " << addr << '\n';
        mem[addr] = cont & 0xFF;
        mem[addr + 1] = (cont >> 8) & 0xFF;
        mem[addr + 2] = (cont >> 16) & 0xFF;
        mem[addr + 3] = (cont >> 24) & 0xFF;
    }
    // default
    return 0;
}
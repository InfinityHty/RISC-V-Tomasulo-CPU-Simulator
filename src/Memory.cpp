//
// Created by HTY on 2026/7/28.
//
#include "../include/Memory.h"
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
                if (line[i] >= '0' && line[i] <= '9') instructions[cur_add] = (line[i] - '0') * 16;
                else instructions[cur_add] = (line[i] - 'A' + 10) * 16;
                if (line[i + 1] >= '0' && line[i + 1] <= '9') instructions[cur_add] += line[i + 1] - '0';
                else instructions[cur_add] += line[i + 1] - 'A' + 10;
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
        return static_cast<int>(data[addr] << 24) >> 24;
    }
    if (type == lbu) return data[addr];
    if (type == lh) {
        return static_cast<int>((data[addr] + (data[addr + 1] << 8)) << 16) >> 16;
    }
    if (type == lhu) return data[addr] + (data[addr + 1] << 8);
    if (type == lw) {
        // std::cerr << "addr: " << addr << '\n';
        return data[addr] + (data[addr + 1] << 8) + (data[addr + 2] << 16) + (data[addr + 3] << 24);
    }
    // Store
    if (type == sb) {
        data[addr] = cont & 0xFF;
    }
    if (type == sh) {
        data[addr] = cont & 0xFF;
        data[addr + 1] = (cont >> 8) & 0xFF;
    }
    if (type == sw) {
        // std::cerr << "cont: " << cont << "addr: " << addr << '\n';
        data[addr] = cont & 0xFF;
        data[addr + 1] = (cont >> 8) & 0xFF;
        data[addr + 2] = (cont >> 16) & 0xFF;
        data[addr + 3] = (cont >> 24) & 0xFF;
    }
    // default
    return 0;
}
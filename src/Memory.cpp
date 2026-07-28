//
// Created by HTY on 2026/7/28.
//
#include "../include/Memory.h"
#include<cstring>
#include <iostream>
void Memory::Load() {
    char line[50];
    int cur_add = 0;
    while (std::cin.getline(line,50)) {
        if (line[0] == '@') {
            cur_add = AddressToIndex(line + 1);
        }
        else {
            int i = 0;
            while (line[i] != '\0') {
                instructions[cur_add++] = line[i] + line[i + 1] * 16;
                i += 2;
                if (line[i] == ' ') i++;
            }
        }
    }
}

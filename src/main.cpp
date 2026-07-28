//
// Created by HTY on 2026/7/27.
//
// 先写一个单级流水(naive simulator)
#include "../include/CPU.h"
#include <iostream>
int main(){
    int clock = 0;
    int max_clock;
    Memory memory;
    std::cin >> max_clock; // 检测有没有死循环
    memory.Load();
    CPU cpu;
    bool finish = false;
    while (clock < max_clock && !finish) {
        clock++;
        finish = cpu.Tick();
    }
    std::cout << "Total clock time: " << clock << '\n';
    return 0;
}
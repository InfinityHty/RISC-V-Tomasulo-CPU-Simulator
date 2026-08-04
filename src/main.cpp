//
// Created by HTY on 2026/7/27.
#include "TomasuloCPU.h"
#include <iostream>
int main(){
    int clock = 0;
    int max_clock;
    Memory memory;
    //std::cin >> max_clock; // 检测有没有死循环
    //std::cin.ignore();
    memory.Load();
    TomasuloCPU cpu(memory);
    bool finish = false;
    // clock < max_clock &&
    while (!finish) {
        clock++;
        finish = cpu.Tick();
    }
    std::cout << "Total clock time: " << clock << '\n';
    return 0;
}
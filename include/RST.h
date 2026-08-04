//
// Created by HTY on 2026/7/29.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_RST_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_RST_H
#include <cstdint>
struct RSTBranch {
    int Qi[32]{};
    int id; // 分支标签
    RSTBranch() {
        for (int i = 0; i < 32; i++) Qi[i] = -1; // -1表示没有等待写入的指令
        id = 0;
    }
};
class RST {
public:
    RST() {
        num = 0;
    }
    bool HasTag(uint8_t id) {
        return branch[num].Qi[id] >= 0;
    }
    void Copy() {
        for (int i = 0; i < 32; i++) {
            branch[num].Qi[i] = branch[num - 1].Qi[i];
        }
    }
    RSTBranch branch[16];
    int num;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_RST_H
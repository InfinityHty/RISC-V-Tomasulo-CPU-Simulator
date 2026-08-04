//
// Created by HTY on 2026/7/29.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_RST_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_RST_H
#include <cstdint>
class RST {
public:
    RST() {
        for (int i = 0; i < 32; i++) Qi[i] = -1;
    }
    bool HasTag(uint8_t id) {
        return Qi[id] >= 0;
    }
    int Qi[32];
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_RST_H
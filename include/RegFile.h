//
// Created by HTY on 2026/7/28.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_REGFILE_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_REGFILE_H
#include <cstdint>
#include "Decoder.h"
enum RegName {
    zero,ra,sp,gp,tp,t0,t1,t2,s0,s1,
    a0,a1,a2,a3,a4,a5,a6,a7,s2,s3,s4,
    s5,s6,s7,s8,s9,s10,s11,t3,t4,t5,t6,
};
struct DataPair {
    uint32_t data1;
    uint32_t data2;
    DataPair(): data1(0),data2(0){}
    DataPair(const uint32_t d1,const uint32_t d2): data1(d1),data2(d2){}
};
class RegFile {
public:
    RegFile() {
        for (uint32_t & i : storage) i = 0;
    }
    DataPair GetData(uint8_t reg1,uint8_t reg2 = 0) {
        return {storage[reg1],storage[reg2]};
    }
    void Write(InsType type,uint8_t des,uint32_t output,uint32_t load);
    void SetZero() {
        storage[0] = 0;
    }
private:
    uint32_t storage[32]{};
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_REGFILE_H
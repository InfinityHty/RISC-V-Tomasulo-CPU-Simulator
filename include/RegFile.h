//
// Created by HTY on 2026/7/28.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_REGFILE_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_REGFILE_H
enum RegName {
    zero,ra,sp,gp,tp,t0,t1,t2,s0,s1,
    a0,a1,a2,a3,a4,a5,a6,a7,s2,s3,s4,
    s5,s6,s7,s8,s9,s10,s11,t3,t4,t5,t6,
}; // s0 也叫 fp
class RegFile {
public:
    RegFile() {
        for (int & i : storage) i = 0;
    }
    void Write();
private:
    int storage[32]{};
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_REGFILE_H
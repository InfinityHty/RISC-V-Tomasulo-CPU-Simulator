//
// Created by HTY on 2026/7/28.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_PC_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_PC_H
class PC {
public:
    PC():counter(0){}
    int GetCounter() const {
        return counter;
    }
    void SetCounter(const int new_counter) {
        counter = new_counter;
    }
private:
    int counter;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_PC_H
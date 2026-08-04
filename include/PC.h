//
// Created by HTY on 2026/7/28.
//

#ifndef RISC_V_TOMASULO_CPU_SIMULATOR_PC_H
#define RISC_V_TOMASULO_CPU_SIMULATOR_PC_H
class PC {
public:
    PC():counter(0),next_step(4){}
    uint32_t GetCounter() const {
        return counter;
    }
    void SetCounter(const uint32_t new_counter) {
        counter = new_counter;
    }
    void SetNext(uint32_t next) {
        next_step = next;
    }
    void Tick() {
        counter = next_step;
        next_step = counter + 4; // default value
    }
private:
    uint32_t counter;
    uint32_t next_step;
};
#endif //RISC_V_TOMASULO_CPU_SIMULATOR_PC_H
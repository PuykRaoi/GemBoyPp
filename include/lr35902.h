/*
 * File: lr35902.h
 * Description: Header definitions for the LR35902 cpu class.
 */

#ifndef LR35902_H
#define LR35902_H

#include <cstdint>
#include "Instructions.h"

// Processor flags
struct Processor_flags {
    uint8_t     z   : 1; // Zero flag
    uint8_t     n   : 1; // Subtraction
    uint8_t     h   : 1; // Half carry flag (BCD)
    uint8_t     c   : 1; // Carry flag
    uint8_t     pad : 4;
};

// cpu registers
struct Cpu_registers {
    u8 a;   // Accumulator
    u8 f;   // processor flags
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 h;   // high
    u8 l;   // low
    u16 pc; // program counter
    u16 sp; // stack pointer

class LR35902 {
public:
    void Init();
    bool step();
private:
    Processor_flags flags;
    Cpu_registers regs;
    // current fetch...
    u16 fetch_data;
    u16 mem_dest;
    u8 curr_opcode;
    Instruction* current_instruction;
    bool halted;
    bool stepping;
};


#endif

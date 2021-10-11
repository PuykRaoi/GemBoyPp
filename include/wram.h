/*
 * File: wram.h
 * Description: Header definitions for the work ram class.
 */

#ifndef WRAM_H
#define WRAM_H

#define WRAMSIZE 0x1000

#include <cstdint>
#include <string>

class WRAM {
private:
    uint8_t Ram [WRAMSIZE];

public:
    uint8_t Read(uint16_t address);
    void Write(uint16_t address, uint8_t data);
    void Initialize();
};

#endif

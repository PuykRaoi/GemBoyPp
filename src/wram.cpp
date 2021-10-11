#include <iostream>
#include "wram.h"

uint8_t WRAM::Read(uint16_t address)
{
    // Memory boundary protection
    if (address >= WRAMSIZE) {
        std::cout << "Error! Invalid WRAM address." << std::endl;
        exit(1);
    }
    return Ram[address];
}

void WRAM::Write(uint16_t address, uint8_t data)
{
    // Memory boundary protection
    if (address >= WRAMSIZE) {
        std::cout << "Error! Invalid WRAM address." << std::endl;
        exit(1);
    }
    Ram[address] = data;
}

void WRAM::Initialize()
{
    for (int i=0; i<WRAMSIZE; i++) {
        Ram[i] = 0x00;
    }
}

/*
 * File: cartridge.h
 * Description: Header definitions for the cartridge class.
 */

#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <string>

class Cartridge {
private:
    uint8_t RomData [0x10000];

public:
    uint8_t Read(uint16_t address);
    void LoadRom(std::string filename);
};

#endif

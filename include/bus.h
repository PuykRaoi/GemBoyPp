/*
 * File: bus.h
 * Description: Header definitions for the system bus class.
 * The system bus is the bus that every component in the GBC is
 * connected to.
 */

#ifndef BUS_H
#define BUS_H

#include <cstdint>

// Forward declarations
class LR35902;
class Cartridge;
class WRAM;

class SystemBus {
// Connected devices
private:
    Cartridge* cartridge;

// Interface
public:
    uint8_t Read(uint16_t address);
    void    Write(uint16_t address, uint8_t data);
    /* void    Connect(Cartridge* l_cartridge, WRAM* l_wram); */
};

#endif

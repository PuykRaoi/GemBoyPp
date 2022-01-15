#include "bus.h"
#include "cartridge.h"
#include "wram.h"
#include "common.h"

// Implements the memory map
// 0000 - 3FFF : 16 KiB ROM bank 00
// 4000 - 7FFF : 16 KiB ROM Bank 01~NN
// 8000 - 9FFF : 8 KiB Video RAM (VRAM)
// A000 - BFFF : 8 KiB External RAM
// C000 - CFFF : 4 KiB Work RAM (WRAM)
// D000 - DFFF : 4 KiB Work RAM (WRAM)
// E000 - FDFF : Mirror of C000~DDFF (ECHO RAM)
// FE00 - FE9F : Sprite attribute table (OAM)
// FEA0 - FEFF : Not Usable
// FF00 - FF7F : I/O Registers
// FF80 - FFFE : High RAM (HRAM)
// FFFF - FFFF : Interrupt Enable register (IE)
uint8_t SystemBus::Read(uint16_t address)
{
    if (address < 0x8000) {
        return cartridge->Read(address);
    }

    NO_IMPL
}

void SystemBus::Write(uint16_t address, uint8_t data)
{
    if (address < 0x8000) {
        cartridge->Write(address, data);
    }

    NO_IMPL
}

/* void SystemBus::Connect(Cartridge* l_cartridge, WRAM* l_wram) */
/* { */
/*     cartridge = l_cartridge; */
/*     wram = l_wram; */
/* } */

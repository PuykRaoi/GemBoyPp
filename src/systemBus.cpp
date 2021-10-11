#include "systemBus.h"
#include "cartridge.h"
#include "wram.h"

uint8_t SystemBus::Read(uint16_t address)
{
    return cartridge->Read(address);
}

void SystemBus::Write(uint16_t address, uint8_t data)
{
    if ((address >= 0xc000) && (address < 0xd000)) {
        wram->Write(address-0xc000, data);
    }
}

void SystemBus::Connect(Cartridge* l_cartridge, WRAM* l_wram)
{
    cartridge = l_cartridge;
    wram = l_wram;
}

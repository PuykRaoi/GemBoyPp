#include "systemBus.h"
#include "cartridge.h"

uint8_t SystemBus::Read(uint16_t address)
{
    return cartridge->Read(address);
}

void SystemBus::Write(uint16_t address, uint8_t data)
{
    //TODO
}

void SystemBus::Connect(Cartridge* l_cartridge)
{
    cartridge = l_cartridge;
}

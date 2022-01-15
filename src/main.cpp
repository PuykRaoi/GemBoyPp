#include <iostream>

#include "lr35902.h"
#include "bus.h"
#include "cartridge.h"
#include "wram.h"

int main()
{
    SystemBus bus;
    Cartridge cartridge("roms/cpu_instrs.gb");
    LR35902 cpu;
    WRAM wram;

    wram.Initialize();

    std::cout << "Hello Gemboy!" << std::endl;

}

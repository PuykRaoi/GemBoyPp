#include <iostream>

#include "lr35902.h"
#include "systemBus.h"
#include "cartridge.h"
#include "wram.h"

int main()
{
    SystemBus bus;
    Cartridge cartridge("roms/cpu_instrs.gb");
    LR35902 cpu;
    WRAM wram;

    wram.Initialize();

    cpu.Connect(&bus);
    bus.Connect(&cartridge, &wram);

    std::cout << "Hello Gemboy!" << std::endl;

    //cartridge.LoadRom("test.gb");   

    /*
    while(cpu.Running()) {
        cpu.PrintState();
        cpu.ExecuteInstruction();
        //getchar();
    }
    */
}

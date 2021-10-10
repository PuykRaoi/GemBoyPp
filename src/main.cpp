#include <iostream>

#include "lr35902.h"
#include "systemBus.h"
#include "cartridge.h"

int main()
{
    SystemBus bus;
    Cartridge cartridge;
    LR35902 cpu;

    cpu.Connect(&bus);
    bus.Connect(&cartridge);

    std::cout << "Hello Gemboy!" << std::endl;

    cartridge.LoadRom("test.gb");

    while(cpu.Running()) {
        cpu.PrintState();
        cpu.ExecuteInstruction();
        //getchar();
    }
}

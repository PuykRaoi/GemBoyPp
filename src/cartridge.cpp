#include <fstream>
#include <vector>
#include <iostream>
#include "cartridge.h"

using namespace std;

const char* Cartridge::Licensee_code(u8 id)
{
    switch(id) {
        case 0x00: return "None"; break;
        case 0x01: return "Nintendo R&D1"; break;
        case 0x08: return "Capcom"; break;
        case 0x13: return "Electronic Arts"; break;
        case 0x18: return "Hudson Soft"; break;
        case 0x19: return "b-ai"; break;
        case 0x20: return "kss"; break;
        case 0x22: return "pow"; break;
        case 0x24: return "PCM Complete"; break;
        case 0x25: return "san-x"; break;
        case 0x28: return "Kemco Japan"; break;
        case 0x29: return "seta"; break;
        case 0x30: return "Viacom"; break;
        case 0x31: return "Nintendo"; break;
        case 0x32: return "Bandai"; break;
        case 0x33: return "Ocean/Acclaim"; break;
        case 0x34: return "Konami"; break;
        case 0x35: return "Hector"; break;
        case 0x37: return "Taito"; break;
        case 0x38: return "Hudson"; break;
        case 0x39: return "Banpresto"; break;
        case 0x41: return "Ubi Soft"; break;
        case 0x42: return "Atlus"; break;
        case 0x44: return "Malibu"; break;
        case 0x46: return "angel"; break;
        case 0x47: return "Bullet-Proof"; break;
        case 0x49: return "irem"; break;
        case 0x50: return "Absolute"; break;
        case 0x51: return "Acclaim"; break;
        case 0x52: return "Activision"; break;
        case 0x53: return "American sammy"; break;
        case 0x54: return "Konami"; break;
        case 0x55: return "Hi tech entertainment"; break;
        case 0x56: return "LJN"; break;
        case 0x57: return "Matchbox"; break;
        case 0x58: return "Mattel"; break;
        case 0x59: return "Milton Bradley"; break;
        case 0x60: return "Titus"; break;
        case 0x61: return "Virgin"; break;
        case 0x64: return "LucasArts"; break;
        case 0x67: return "Ocean"; break;
        case 0x69: return "Electronic Arts"; break;
        case 0x70: return "Infogrames"; break;
        case 0x71: return "Interplay"; break;
        case 0x72: return "Broderbund"; break;
        case 0x73: return "sculptured"; break;
        case 0x75: return "sci"; break;
        case 0x78: return "THQ"; break;
        case 0x79: return "Accolade"; break;
        case 0x80: return "misawa"; break;
        case 0x83: return "lozc"; break;
        case 0x86: return "Tokuma Shoten Intermedia"; break;
        case 0x87: return "Tsukuda Original"; break;
        case 0x91: return "Chunsoft"; break;
        case 0x92: return "Video system"; break;
        case 0x93: return "Ocean/Acclaim"; break;
        case 0x95: return "Varie"; break;
        case 0x96: return "Yonezawa/s'pal"; break;
        case 0x97: return "Kaneko"; break;
        case 0x99: return "Pack in soft"; break;
        case 0xA4: return "Konami (Yu-Gi-Oh!)"; break;
        default: return "Unknown";
    }
};

const char* Cartridge::Cartridge_type(u8 id)
{
    switch(id) {
        case 0x00: return "ROM ONLY"; break;
        case 0x01: return "MBC1"; break;
        case 0x02: return "MBC1+RAM"; break;
        case 0x03: return "MBC1+RAM+BATTERY"; break;
        case 0x05: return "MBC2"; break;
        case 0x06: return "MBC2+BATTERY"; break;
        case 0x08: return "ROM+RAM 1"; break;
        case 0x09: return "ROM+RAM+BATTERY 1"; break;
        case 0x0B: return "MMM01"; break;
        case 0x0C: return "MMM01+RAM"; break;
        case 0x0D: return "MMM01+RAM+BATTERY"; break;
        case 0x0F: return "MBC3+TIMER+BATTERY"; break;
        case 0x10: return "MBC3+TIMER+RAM+BATTERY 2"; break;
        case 0x11: return "MBC3"; break;
        case 0x12: return "MBC3+RAM 2"; break;
        case 0x13: return "MBC3+RAM+BATTERY 2"; break;
        case 0x19: return "MBC5"; break;
        case 0x1A: return "MBC5+RAM"; break;
        case 0x1B: return "MBC5+RAM+BATTERY"; break;
        case 0x1C: return "MBC5+RUMBLE"; break;
        case 0x1D: return "MBC5+RUMBLE+RAM"; break;
        case 0x1E: return "MBC5+RUMBLE+RAM+BATTERY"; break;
        case 0x20: return "MBC6"; break;
        case 0x22: return "MBC7+SENSOR+RUMBLE+RAM+BATTERY"; break;
        case 0xFC: return "POCKET CAMERA"; break;
        case 0xFD: return "BANDAI TAMA5"; break;
        case 0xFE: return "HuC3"; break;
        case 0xFF: return "HuC1+RAM+BATTERY"; break;
        default: return "Unknown"; break;
    }
};

const char* Cartridge::ROM_size(u8 code)
{
    switch(code) {
        case 0x00: return "32 KByte"; break;
        case 0x01: return "64 KByte"; break;
        case 0x02: return "128 KByte"; break;
        case 0x03: return "256 KByte"; break;
        case 0x04: return "512 KByte"; break;
        case 0x05: return "1 MByte"; break;
        case 0x06: return "2 MByte"; break;
        case 0x07: return "4 MByte"; break;
        case 0x08: return "8 MByte"; break;
        case 0x52: return "1.1 MByte"; break;
        case 0x53: return "1.2 MByte"; break;
        case 0x54: return "1.5 MByte"; break;
        default: return "Unknown"; break;
    }
};

const char* Cartridge::RAM_size(u8 code)
{
    switch(code) {
        case 0x00: return "No RAM 4"; break;
        case 0x01: return "Unused 5"; break;
        case 0x02: return "8 KB	1 bank"; break;
        case 0x03: return "32 KB"; break;
        case 0x04: return "128 KB"; break;
        case 0x05: return "64 KB"; break;
        default: return "Unknown"; break;
    }
};

Cartridge::Cartridge(string file_name)
{
    if (load(file_name)) {
        cout << "Cartridge loaded into memory" << endl;
        print_info();
    }
    else {
        cout << "Something went wrong..." << endl;
    }
    // Calculating checksum
    u16 x = 0;
    u16 i;
    for (i = 0x0134;i <= 0x014c; i++) {
        x = x - rom_data[i] - 1;
        cout << (x&0xff) << "," << endl;
    }
    if (rom_data[0x014d] != (x & 0xFF)) {
        cout << "Checksum error: "
             << std::hex << (u16)rom_data[0x014d]
             << " and " << (u16)(x & 0xFF) << endl;
    }
    else {
        cout << "ROM loaded correctly " << endl;
    }

}

bool Cartridge::load(std::string file_name)
{
    vector<char> data;
    char current;

    ifstream in{ file_name };
    if(!in.good()) { return false; }

    while(in.good()) {
        in >> current;
        rom_data.push_back(current);
    }

    return true;
}


uint8_t Cartridge::Read(uint16_t address)
{
    // Just ROM ONLY type supported
    return rom_data[address];
}

void Cartridge::Write(uint16_t address, u8 data)
{
    NO_IMPL;
}

void Cartridge::print_info()
{
    Rom_header* header = reinterpret_cast<Rom_header*>(&rom_data[0x100]);
    cout << "Title    :" << header->title << endl;
    cout << "Type     :" << Cartridge_type(header->type) << endl;
    cout << "ROM size :" << ROM_size(header->rom_size) << endl;
    cout << "RAM size :" << RAM_size(header->ram_size) << endl;
    cout << "Lic code :" << Licensee_code(header->lic_code) << endl;
    cout << "Checksum :" << (u16)header->checksum << endl;
}

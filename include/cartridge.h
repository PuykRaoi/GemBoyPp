/*
 * File: cartridge.h
 * Description: Header definitions for the cartridge class.
 */

#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <cstdint>
#include <string>
#include <vector>
#include "common.h"

struct Rom_header
{
    u8 entry[4];
    u8 logo[0x30];

    char title[16];
    u16 new_lic_code;
    u8 sgb_flag;
    u8 type;
    u8 rom_size;
    u8 ram_size;
    u8 dest_code;
    u8 lic_code;
    u8 version;
    u8 checksum;
    u16 global_checksum;
};

class Cartridge
{
private:
    std::vector<u8> rom_data;
    Rom_header header;
    u16 rom_size;
public:
    Cartridge(std::string file_name);
    uint8_t Read(uint16_t address);

// These seem to be internal functions...
public:
    bool load(std::string file_name);
    const char* Licensee_code(u8 id);
    const char* Cartridge_type(u8 id);
    const char* ROM_size(u8 code);
    const char* RAM_size(u8 code);
    void print_info();
};

#endif

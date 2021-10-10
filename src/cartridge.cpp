#include <iostream>
#include "cartridge.h"

void Cartridge::LoadRom(std::string filename)
{
    std::cout << "Loading file " << filename << std::endl;

    FILE * pFile;
    long lSize;
    unsigned char * buffer;
    size_t result;

    const char * fname = filename.c_str();
    pFile = fopen ( fname, "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (unsigned char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    /* the whole file is now loaded in the memory buffer. */


    // transfer the contents of buffer to the memory starting
    // at address 0x0
    for(int i = 0; i < lSize; ++i)
    {
        if(i<10){
            printf("%02x \n", buffer[i]);
        }
        RomData[i] = buffer[i];
    }

    // terminate
    fclose (pFile);
    free(buffer);
}


uint8_t Cartridge::Read(uint16_t address)
{
    return RomData[address];
}

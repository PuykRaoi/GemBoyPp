/*
 * Common definitions.
 */
#include <cstdint>
#include <iostream>

typedef uint8_t u8;
typedef uint16_t u16;

#define NO_IMPL { std::cout << "Not implemented yet\n"; exit(-1); }

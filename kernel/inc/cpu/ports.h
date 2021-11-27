#ifndef __CPU_PORTS
#define __CPU_PORTS

#include <stdint.h>

// Read a byte from a port
uint8_t byte_in(uint16_t port);

// Write a byte to a port
void byte_out(uint16_t port, uint8_t data);

#endif
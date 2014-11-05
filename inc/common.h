/* Common.h */

#include "stdint.h"

#define bitSet(reg, bit) ((reg) |= (bit))
#define bitClear(reg, bit) ((reg) &= (~(bit)))


typedef uint8_t status_t;
#define STATUS_SUCCESS 0
#define STATUS_RINGBUFFER_EMPTY 80
#define STATUS_TXBUFFER_FULL 81
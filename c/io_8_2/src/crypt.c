// TODO: hash function
//       mask generating function
#include "crypt.h"

uint8_t *
mgf(uint8_t seed[], size_t seed_len, uint32_t length)
{
    uint64_t hLen = 160;
    if (length > (hLen << 32))
    {
        return NULL;
    }
    char T[] = {};

    uint32_t counter;
    while (strlen(T) < length) {
        uint8_t C[] = {(uint8_t) counter>>3*8, (uint8_t) counter>>2*8, (uint8_t)counter>>8, (uint8_t)counter};
        size_t C_len = 4;
        SHA1();
    }
}

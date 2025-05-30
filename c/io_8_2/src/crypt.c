// TODO: hash function
//       mask generating function
#include "crypt.h"

uint8_t *
mgf(uint8_t seed, uint32_t length)
{
    uint64_t hLen = 160;
    if (length > (hLen << 32))
    {
        return NULL;
    }
    char *T;

    uint32_t counter;
    while (strlen(T) < length) {

    }
}

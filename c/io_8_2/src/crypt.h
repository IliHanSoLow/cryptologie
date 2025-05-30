#ifndef CRYPT_H_
#define CRYPT_H_

#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

uint8_t *mgf(uint8_t seed, uint32_t length);

#endif // CRYPT_H_

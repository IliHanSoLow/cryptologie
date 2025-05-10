#pragma once
#include <assert.h>
#include <endian.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define SET_UINT128(left, right) (((__uint128_t)(left) << 64) | (right))

// Rotating function
__uint128_t rotl128 (__uint128_t n, unsigned int c);
// Little endian to big endian
__uint128_t htobe128 (__uint128_t x);
// Print 128 bit ints
void print_uint128 (__uint128_t value);

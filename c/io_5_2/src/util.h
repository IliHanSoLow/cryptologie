#pragma once
#include <assert.h>
#include <endian.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#define SET_UINT128(left, right) (((__uint128_t)(left) << 64) | (right))

__uint128_t rotl128 (__uint128_t n, unsigned int c);
__uint128_t rotr128 (__uint128_t n, unsigned int c);
__uint128_t htobe128 (__uint128_t x);
void print_uint128 (__uint128_t value);

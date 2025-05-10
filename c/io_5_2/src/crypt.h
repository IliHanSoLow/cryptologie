#pragma once
#include "util.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct cyphertext
{
  uint8_t *bytes;
  size_t len;
} typedef cyphertext_T;

// Generate the sbox to the array given it s_box[0] needs to be 170
void gen_s_box (uint8_t s_box[256]);

// Generate round keys
void init_keys (__uint128_t key, __uint128_t keys[32]);

// Feistul function that is executed after split and before merge
uint64_t feistel (uint64_t input, __uint128_t key);

// F in task 1
__uint128_t f_round (__uint128_t input, __uint128_t keys[]);

// Wrapper for F
__uint128_t schiffi (__uint128_t input, __uint128_t master_key);

// encrypt message to file
void encrypt_msg_to_file (char *input, __uint128_t master_key,
                          char *file_path);

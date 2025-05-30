#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t multiply (uint8_t a, uint8_t b);
uint16_t multiply_raw (uint8_t a, uint8_t b);
uint8_t reduce_x8 (uint16_t a);
char *polToStr (uint16_t a);

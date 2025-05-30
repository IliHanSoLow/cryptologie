#include "crypto.h"

void
gen_s_box (uint8_t sbox[256])
{
  for (size_t i = 0; i <= 0xFF; i++)
    {
      sbox[i] = multiply ((uint8_t)i, 0xab);
    }
}

uint32_t
mixColums (uint32_t a)
{
  uint16_t a1_vec = (a >> 16 & ~(uint32_t)0xFF) | ((uint16_t)(a >> 16));
  uint16_t a2_vec = ((uint16_t)(a & ~(uint32_t)0xFF)) | ((uint8_t)a);
  // printf ("a1_vec: %x, a2_vec: %x\n", a1_vec, a2_vec);
  uint16_t r1 = mixColums_vec (a1_vec);
  uint16_t r2 = mixColums_vec (a2_vec);
  // printf ("r1: %x, r2: %x\n", r1, r2);
  uint32_t result = (uint32_t)r1 << 16 | r2;
  return result;
}

uint16_t
mixColums_vec (uint16_t a)
{
  uint16_t result = 0;
  uint8_t M[4] = { 0x59, 0x4c, 0x4f, 0x4f };
  result = (uint16_t)((multiply (M[0], a >> 8) ^ multiply (M[1], (uint8_t)a))
                      << 8);
  result |= (multiply (M[2], a >> 8) ^ multiply (M[3], (uint8_t)a));
  return result;
}

#include "main.h"

int
main (void)
{
  test_all ();

  uint8_t sbox[256] = { 0 };
  gen_s_box (sbox);
  printf ("sbox[123] = %d\n", sbox[123]); // 193
  for (size_t i = 0; i <= 0xFF; i++)
    {
      if (sbox[i] == 123)
        printf ("sbox[%ld] = 123\n --> sbox^-1[123] = %ld\n", i, i);
      // printf ("%d\n", sbox[i]);
    }

  uint32_t B = 0xa3caab05;
  uint32_t res = mixColums (B);
  printf ("%x\n", res);

  return 0;
}

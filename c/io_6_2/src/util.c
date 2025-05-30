#include "util.h"

uint16_t
multiply_raw (uint8_t a, uint8_t b)
{
  uint16_t solution = 0;
  for (uint8_t i = 0; i < 8; i++)
    {
      if ((a >> i) & 1)
        {
          for (uint8_t j = 0; j < 8; j++)
            {
              if ((b >> j) & 1)
                {
                  solution ^= 1 << (i + j);
                }
            }
        }
    }
  return solution;
}

uint8_t
reduce_x8 (uint16_t a)
{
  uint8_t b = a >> 8; // x^8 * b  = a & ~0xFF
  uint8_t x8 = 0xc3;  // x^8 = x^7 + x^6 + x + 1
                      // printf ("x8^b = x^8 *( %s )\n", polToStr (b));
  // printf ("res = ( %s ) ^ ( %s )\n", polToStr (multiply_raw (x8, b)),
  // polToStr (a & 0xff));
  uint16_t res = multiply_raw (x8, b) ^ (a & 0xff);
  if (res & ~0xff)
    {
      // printf ("res = %s\n", polToStr (res));
      return reduce_x8 (res);
    }
  else
    {
      // printf ("Final: %s\n", polToStr (res));
      return (uint8_t)res;
    }
}

uint8_t
multiply (uint8_t a, uint8_t b)
{
  return reduce_x8 (multiply_raw (a, b));
}

char *
polToStr (uint16_t a)
{
  if (a == 0)
    return "0";
  char *buf = malloc (80);
  if (!buf)
    return NULL;
  buf[0] = '\0';

  uint8_t i = 16;
  int first = 1;
  while (i-- > 0)
    {
      if ((a >> i) & 1)
        {
          if (!first)
            strcat (buf, " + ");
          first = 0;
          if (i == 0)
            strcat (buf, "1");
          else if (i == 1)
            strcat (buf, "x");
          else
            {
              char term[8];
              // sprintf (term, "x^%d", i);
              strcat (buf, term);
            }
        }
    }
  return buf;
}

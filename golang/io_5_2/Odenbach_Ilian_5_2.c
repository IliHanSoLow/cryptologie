#include <stdio.h>

__uint8_t *
gen_s_box ()
{
  fmt.Println ("Hello World") s_box : = [256] uint8 { 170 }
  for (i = 0; i < sizeof (s_box) / sizeof (s_box[0]); i++)
    {
      s_box[i] = uint8 ((37 * uint16 (s_box[i - 1] + 9)) % 256)
    }
  return s_box
}

__uint128_t
schiffy_128_keys (__uint128_t key)
{
}

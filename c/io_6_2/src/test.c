#include "test.h"

void
test_all (void)
{
  test_reduction ();
}

void
test_reduction (void)
{
  // printf ("---\nstart: %s\n", polToStr (1 << 9));
  assert (reduce_x8 (1 << 9) == 0x45);
  // printf ("---\nstart: %s\n", polToStr (1 << 10));
  assert (reduce_x8 (1 << 10) == 0x8a);
  // printf ("---\nstart: %s\n", polToStr (1 << 11));
  assert (reduce_x8 (1 << 11) == 0xd7);
  // printf ("---\nstart: %s\n", polToStr (1 << 12));
  assert (reduce_x8 (1 << 12) == 0x6d);
  // printf ("---\nstart: %s\n", polToStr (1 << 13));
  assert (reduce_x8 (1 << 13) == 0xdA);
  // printf ("---\nstart: %s\n", polToStr (1 << 14));
  assert (reduce_x8 (1 << 14) == 0x77);
}

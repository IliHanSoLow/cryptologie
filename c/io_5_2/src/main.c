#include "main.h"
#include "util.h"

int
// main (int argc, char *argv[])
main (void)
{
  __uint128_t x = SET_UINT128 (0x0123456789ABCDEF, 0xFEDCBA9876543210);
  print_uint128 (x);
  print_uint128 (htobe128 (x));
  printf ("%lx, %lx\n", 0x0123456789ABCDEF, htobe64 (0x0123456789ABCDEF));

  test_all ();

  char *message
      = "While, therefore, I heartily recognize his lofty appreciation of "
        "_Faust_,-while I honor him for the patient and conscientious labor "
        "he has bestowed upon his translation,-I cannot but feel that he has "
        "himself illustrated the unsoundness of his argument. Nevertheless, "
        "the circumstance that his prose translation of _Faust_ has received "
        "so much acceptance proves those qualities of the original work which "
        "cannot be destroyed by a test so violent.";

  encrypt_msg_to_file (message,
                       SET_UINT128 (0x0815000000000000, 0x0000000000004711),
                       "ciphertext.bin");

  return 0;
}

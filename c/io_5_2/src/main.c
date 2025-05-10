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

  char *message =
"It is twenty years since I first determined to attempt the translation of _Faust_, in the original metres. At that time, although more than a score of English translations of the First Part, and three or four of the Second Part, were in existence, the experiment had not yet been made. The prose version of Hayward seemed to have been accepted as the standard, in default of anything more satisfactory: the English critics, generally sustaining the translator in his views concerning the secondary importance of form in Poetry, practically discouraged any further attempt; and no one, familiar with rhythmical expression through the needs of his own nature, had devoted the necessary love and patience to an adequate reproduction of the great work of Goethe's life.";


  encrypt_msg_to_file (message,
                       SET_UINT128 (0x0815000000000000, 0x0000000000004711),
                       "encrypted.bin");

  return 0;
}

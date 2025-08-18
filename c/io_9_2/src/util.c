#include "util.h"
// Ecdsa-Sig-Value  ::=  SEQUENCE  {
//      r     INTEGER,
//      s     INTEGER  }
void
ecdsa_asn1 (int r, int s, uint8_t output, size_t output_size)
{
  size_t size = sizeof (r) + sizeof (s);
  // if ( output_size <
}

#include <stdio.h>
#include <unistd.h>

void
test_rsa ()
{
  char *generate_rsa[] = { "openssl",
                           "pkeyutl",
                           "-decrypt",
                           "-inkey",
                           "privkey.pem",
                           "-pkeyopt",
                           "rsa_padding_mode:oaep",
                           "-pkeyopt",
                           "rsa_mgf1_md:sha256",
                           "-in",
                           "ciphertext.bin" };

  execl ("sh", "sh", "-c", generate_rsa, NULL);
}

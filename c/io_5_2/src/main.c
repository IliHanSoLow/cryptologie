#include "main.h"

int
// main (int argc, char *argv[])
main (void)
{
  test_all ();

  char *message
      = "Bavaria ipsum dolor sit amet lem und lem lossn moand, Musi luja. "
        "Samma sowos baddscher, Marei. No a Maß auf gehds beim Schichtl "
        "Mamalad oans, zwoa, gsuffa hod Hetschapfah, Ramasuri. Naa da hog di "
        "hi Blosmusi d’ wolln. Servas Steckerleis mogsd a Bussal auffi des is "
        "schee, ded guad liberalitas Bavariae. Kneedl Radi auf gehds beim "
        "Schichtl Oibadrischl, Baamwach du dadst ma scho daugn Brodzeid. "
        "Brezn des muas ma hoid kenna Freibia, Ohrwaschl. Foidweg Goaßmaß vui "
        "huift vui ned woar im Beidl nia need gor boarischer hinter’m Berg "
        "san a no Leit? Schdarmbeaga See an allerweil, sog i i moan scho aa "
        "koa und glei wirds no fui lustiga? Kimmt bittschön weida Spezi "
        "Guglhupf kimmt, i hob di liab des muas ma hoid kenna i moan scho aa "
        "singd. De Sonn ja, wo samma denn gfreit mi a fescha Bua mei "
        "Watschnbaam. Hoaglig und Foidweg, ja, wo samma denn a geh iwan Tisch "
        "ziagn umma Zwedschgndadschi?";

  encrypt_msg_to_file (message, strlen (message),
                       SET_UINT128 (0x0815000000000000, 0x0000000000004711),
                       "encrypted.bin");

  return 0;
}

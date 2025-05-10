#include "test.h"

extern uint8_t s_box[256];

void
test_all (void)
{
  test_s_box ();
  test_round_keys ();
  test_feistel ();
  test_schiffi ();
}

void
test_s_box (void)
{
  assert (s_box[0] == 170);
  assert (s_box[1] == 155);
  assert (s_box[2] == 112);
  assert (s_box[123] == 33);
  assert (s_box[255] == 205);
}

void
test_round_keys (void)
{
  __uint128_t keys[32];
  __uint128_t key = SET_UINT128 (0xdeadbeef00000000, 0x0000000badc0ffee);
  init_keys (key, keys);
  assert (keys[0] == SET_UINT128 (0xdeadbeef00000000, 0x00000000bad6b3201));
  assert (keys[1] == SET_UINT128 (0x56df778000000000, 0x0000005d6b532cd00));
  assert (keys[2] == SET_UINT128 (0xdde0000000000000, 0x00175ad4cb3ebd858));
  assert (keys[31] == SET_UINT128 (0x770feb4b3180dc3b, 0xc09870bd38e2cb5f));
}

void
test_feistel (void)
{
  __uint128_t keys[32];
  __uint128_t key = SET_UINT128 (0xdeadbeef00000000, 0x0000000badc0ffee);
  init_keys (key, keys);

  assert (feistel (0, keys[0]) == 0x94dfb49607c198ab);
  assert (feistel (0x94dfb49607c198ab, keys[1]) == 0xb0aa7cca50e95fb1);
  assert (feistel (0xb0aa7cca50e95fb1, keys[2]) == 0x1e9d6324e9783573);
  assert (feistel (0x8a42d7b2eeb9add8, keys[3]) == 0x01a6283b0f33c8f0);
  assert (feistel (0xc8ef99ba72f8a579, keys[29]) == 0xf7ffea032144154a);
  assert (feistel (0x81f3d4d01743d570, keys[30]) == 0x7fac6b4146d4f4c6);
  assert (feistel (0xb743f2fb342c51bf, keys[31]) == 0x2a66d3471f7cb499);
}

void
test_schiffi (void)
{
  assert (schiffi (0, SET_UINT128 (0xdeadbeef00000000, 0x0000000badc0ffee))
          == SET_UINT128 (0xb743f2fb342c51bf, 0xab950797083f61e9));
  assert (schiffi (SET_UINT128 (0xdeadbeef00000000, 0x0000000badc0ffee),
                   SET_UINT128 (0xdeadbeef00000000, 0x0000000badc0ffee))
          == SET_UINT128 (0xe1a6741fd1ec4e31, 0xb5704950783f4999));
}

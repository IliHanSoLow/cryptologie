#include "./crypt.h"

extern uint8_t s_box[256];

void
gen_s_box (uint8_t s_box_array[256])
{
  for (int i = 1; i < 256; i++)
    s_box_array[i] = (37 * s_box_array[i - 1] + 9) % 256;
}

void
init_keys (__uint128_t key, __uint128_t keys[32])
{
  for (int i = 0; i < 32; i++)
    {
      __uint128_t kx;
      if (i == 0)
        kx = key;
      else
        kx = keys[i - 1];
      keys[i] = rotl128 (kx, (uint32_t)(7 * i)) ^ 0xabcdef;
      // print_uint128 (keys[i]);
    }
}

uint64_t
feistel (uint64_t input, __uint128_t key)
{
  uint64_t output = 0;
  input ^= (uint64_t)(key >> 64);
  for (int i = 0; i < 8; i++)
    {
      uint8_t index = (uint8_t)(input >> 8 * i);
      output |= (uint64_t)(s_box[index]) << 8 * i;
    }
  output ^= (uint64_t)key;
  return output;
}

__uint128_t
f_rounds (__uint128_t input, __uint128_t keys[])
{
  uint64_t l = (uint64_t)(input >> 64);
  uint64_t r = (uint64_t)input;
  for (int i = 0; i < 32; i++)
    {
      uint64_t tmp = l ^ feistel (r, keys[i]);
      l = r;
      r = tmp;
    }
  return (((__uint128_t)l << 64) | r);
}

__uint128_t
schiffi (__uint128_t input, __uint128_t master_key)
{
  __uint128_t keys[32] = { 0 };
  init_keys (master_key, keys);
  return f_rounds (input, keys);
}

cyphertext_T
encrypt_msg (char *input, size_t input_len, __uint128_t master_key)
{
  __uint128_t keys[32] = { 0 };
  init_keys (master_key, keys);

  size_t i = 0;
  __uint128_t message = 0;
  uint8_t *output = (uint8_t *)(malloc (
      16 + input_len + ((input_len % 16 != 0) ? (16 - input_len % 16) : 0)));
  __uint128_t iv = SET_UINT128 (0x3029cd08ae64012c, 0x88698d9d6ccd7daa);
  // srand (time (NULL));
  // __uint128_t iv = ((__uint128_t)rand () << 96) | ((__uint128_t)rand () <<
  // 64)
  //                  | ((uint64_t)rand () << 32) | (uint)rand ();
  for (size_t j = 0; j < 16; j++)
    {
      output[j] = (uint8_t)(iv >> j * 8);
      // printf ("j: %ld,\t", j);
    }

  while (input[i] != '\0')
    {
      message = message << (8 * (i % 16)) | (uint8_t)input[i];
      if (i % 16 == 0 && i != 0)
        {
          __uint128_t tmp = message ^ iv;
          __uint128_t out = f_rounds (tmp, keys);
          iv = out;
          for (size_t j = 0; j < 16; j++)
            {
              output[i + j] = (uint8_t)(out >> j * 8);
              // printf ("hi i+j: %ld,\t", i + j);
            }
        }
      i++;
    }
  if (i % 16 != 0)
    {
      // fill up with 0
      // printf ("I:%ld\n", i);
      message = message << (16 - i % 16);
      __uint128_t tmp = message ^ iv;
      __uint128_t out = f_rounds (tmp, keys);
      iv = out;
      i = i - i % 16;
      for (size_t j = 0; j < 16; j++)
        {
          output[i + j + 16] = (uint8_t)(out >> j * 8);
          // printf ("i+j: %ld,\t", i + j + 16);
        }
    }
  return (cyphertext_T){ output, input_len };
}

void
encrypt_msg_to_file (char *input, size_t input_len, __uint128_t master_key,
                     char *file_path)
{
  if (access (file_path, F_OK) == 0)
    {
      remove (file_path);
    }

  FILE *file = fopen (file_path, "ab");
  if (file == NULL)
    {
      perror ("could not open file");
      exit (-1);
    }
  cyphertext_T data = encrypt_msg (input, input_len, master_key);
  fwrite (data.bytes, sizeof (uint8_t), data.len, file);
  free (data.bytes);
}

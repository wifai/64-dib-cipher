#include "dib-cipher.hpp"

Block DIBCipher::encrypt(Block plain) {
  Block cipher = plain ^ key;
  Block reverse = 0;
  for (int i = 0; i < N; i++)
    reverse |= ((cipher >> i) & 1) << (N-i-1);
  cipher = (reverse >> (N/2)) | (reverse << (N/2));
  return cipher;
}
Block DIBCipher::decrypt(Block cipher) {
  Block plain = cipher;
  plain = (plain >> (N/2)) | (plain << (N/2));
  Block reverse = 0;
  for (int i = 0; i < N; i++)
    reverse |= ((plain >> i) & 1) << (N-i-1);
  plain = reverse ^ key;
  return plain;
}
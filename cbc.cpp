#include "cbc.hpp"

Block * CBC::encrypt(int n, Block * plain) {
  Block * cipher = new Block[n + 2];
  Block2 cur;
  cur[0] = iv[0]; cur[1] = iv[1];
  for (int i = 0; i < n; i += 2) {
    cur[0] ^= plain[i];
    cur[1] ^= plain[i+1];
    f->encrypt(cur);
    cipher[i] = cur[0];
    cipher[i+1] = cur[1];
  }
  return cipher;
}
Block * CBC::decrypt(int n, Block * cipher) {
  Block * plain = new Block[n + 2];
  for (int i = 0; i < n; i += 2) {
    Block2 cur;
    cur[0] = cipher[i];
    cur[1] = cipher[i+1];
    f->decrypt(cur);
    plain[i] = cur[0] ^ (i >= 2 ? cipher[i-2] : iv[0]);
    plain[i+1] = cur[1] ^ (i >= 2 ? cipher[i-1] : iv[1]);
  }
  return plain;
}
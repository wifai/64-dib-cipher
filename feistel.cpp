#include "feistel.hpp"

Feistel::Feistel(int n, Block key1) : n(n) {
  f = new DIBCipher[n];
  for (int i = 0; i < n; i++) {
    f[i].set(key1);
    key1 = generateKey(key1);
  }
}
Block Feistel::generateKey(Block prev) {
  return prev * prime;
}
void Feistel::encrypt(Block2 & cipher) {
  for (int i = 0; i < n; i++) {
    cipher[0] ^= f[i].encrypt(cipher[1]);
    Block tmp = cipher[0];
    cipher[0] = cipher[1];
    cipher[1] = tmp;
  }
}
void Feistel::decrypt(Block2 & plain) {
  for (int i = n-1; i >= 0; i--) {
    Block tmp = plain[0];
    plain[0] = plain[1];
    plain[1] = tmp;
    plain[0] ^= f[i].encrypt(plain[1]);
  }
}
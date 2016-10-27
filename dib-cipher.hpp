#ifndef DIB_CIPHER_HPP
#define DIB_CIPHER_HPP

#include <cstdio>

#define N 64
typedef unsigned long long Block;

class DIBCipher {
private:
  Block key;
public:
  DIBCipher() : key(0) {}
  DIBCipher(Block key) : key(key) {
  };
  ~DIBCipher() {}
  Block encrypt(Block plain);
  Block decrypt(Block cipher);
  void set(Block key) {
    this->key = key;
  }
};

#endif
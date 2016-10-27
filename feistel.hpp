#ifndef FEISTEL_HPP
#define FEISTEL_HPP

#include "dib-cipher.hpp"

#define prime 101ULL
typedef Block Block2[2];

class Feistel {
private:
  int n;
  DIBCipher * f;
public:
  Feistel(int n, Block key1);
  ~Feistel() {
    delete [] f;
  }
  Block generateKey(Block seed);
  void encrypt(Block2 & plain);
  void decrypt(Block2 & cipher);
};

#endif
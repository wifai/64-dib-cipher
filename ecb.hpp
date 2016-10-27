#ifndef ECB_HPP
#define ECB_HPP

#include "feistel.hpp"

class ECB {
private:
  Feistel * f;
public:
  ECB(int n, Block key1) {
    f = new Feistel(n, key1);
  }
  ~ECB() {
    delete [] f;
  }
  Block * encrypt(int n, Block * plain);
  Block * decrypt(int n, Block * cipher);
};

#endif
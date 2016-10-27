#ifndef CBC_HPP
#define CBC_HPP

#include "feistel.hpp"

#define prime_cbc 137

class CBC {
private:
  Feistel * f;
  Block2 iv;
public:
  CBC(int n, Block key1) {
    f = new Feistel(n, key1);
    iv[0] = key1 * prime_cbc;
    iv[1] = iv[0] * prime_cbc;
  }
  ~CBC() {
    delete [] f;
  }
  Block * encrypt(int n, Block * plain);
  Block * decrypt(int n, Block * cipher);
};

#endif
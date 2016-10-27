#include <iostream>
#include <cstdio>
#include "dib-cipher.hpp"
#include "feistel.hpp"
#include "ecb.hpp"
#include "cbc.hpp"

using namespace std;

Block * toBlock(int n, char s[]) {
  int m = (n+7)/8;
  Block * ret = new Block[m+1];
  for (int i = 0; i < n;) {
    unsigned long long cur = 0;
    for (int j = 0; j < 8; j++, i++) {
      cur <<= 8;
      if (i < n)
        cur |= s[i];
    }
    ret[i/8] = cur;
  }
  return ret;
}
char * toString(int n, Block * block) {
  char * s = new char [n * 8 + 8];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 8; j++) {
      s[i * 8 + j] = (block[i] >> ((7-i) * 8)) & 0xFF;
    }
  }
  s[n * 8] = '\0';
  return s;
}

int main(int argc, char** argv) {
  printf("**** Difusing Invers Block Cipher ****\n");
  printf("Option:\n");
  printf("(1) Encrypt\n");
  printf("(2) Decrypt\n");
  printf("Your Choice (1/2): ");
  int enOrDe;
  scanf("%d", &enOrDe);
  if (enOrDe != 1 && enOrDe != 2) {
    puts("Your choice is wrong :(");
    return 0;
  }
  printf("Key in hex (8 byte / 64 bit): ");
  Block key;
  scanf("%U", &key);
  printf("Mode Option:\n");
  printf("(1) Electronic Code Book\n");
  printf("(2) Cipher Block Chaining\n");
  printf("(3) Cipher Feedback (CFB) 8-bit\n");
  int mode;
  printf("Your choice (1/2/3) : ");
  scanf("%d", &mode);
  if (mode != 1 && mode != 2 && mode != 3) {
    puts("Your choice is wrong :(");
    return 0;
  }
  switch (mode) {
    case 1: {
      ECB ecb(16, key);

      break;
    }
    case 2: {
      printf("case 2\n");
      break;
    }
    case 3: {
      printf("case 3\n");

      break;
    }
  }
  return 0;
}
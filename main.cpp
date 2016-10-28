#include <iostream>
#include <cstdio>
#include "dib-cipher.hpp"
#include "feistel.hpp"
#include "ecb.hpp"
#include "cbc.hpp"
#include <cstdlib>

using namespace std;

#define BUFFER_SIZE 100005

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

Block buffer[BUFFER_SIZE];

void readBlock(int &n, char * namefile) {
  FILE * file = fopen(namefile, "r");
  n = 0;
  bool ok = true;
  while (ok) {
    Block cur = 0;
    for (int i = 0; i < 8; i++) {
      cur <<= 8;
      int c;
      if (ok) {
        c = fgetc(file);
        ok &= (c != EOF);
        if (ok)
          cur |= c; 
      }
    }
    buffer[n++] = cur;
  }
  fclose(file);
  if (n & 1)
    buffer[n++] = 0;
}
void writeBlock(int n, Block * block, char * namefile) {
  FILE * file = fopen(namefile, "w");
  for (int i = 0; i < n; i++) {
    Block cur = block[i];
    for (int j = 0; j < 8; j++) {
      int c = (cur >> ((7-j) * 8)) & 0xFF;
      if (c != -1)
        fputc(c, file);
    }
  }
  fclose(file);
}

int main(int argc, char** argv) {
  // Feistel feis(16, 2131239);
  // Block2 result;
  // result[0] = 12345;
  // result[1] = 987;
  // feis.encrypt(result);
  // cerr << result[0] << " " << result[1] << endl;
  // feis.decrypt(result);
  // cerr << result[0] << " " << result[1] << endl;
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
  printf("Key in integer 64 bit: ");
  Block key;
  scanf("%llu", &key);
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
  printf("File input : ");
  char input[10000];
  scanf("%s", input);
  char output[100000];
  printf("File output : ");
  scanf("%s", output);
  int n;
  readBlock(n, input);
  cerr << "reading success " << n << endl;
  switch (mode) {
    case 1: {
      ECB ecb(16, key);
      Block * result = NULL;

      if (enOrDe == 1) {
        result = ecb.encrypt(n, buffer);
        puts("encrypting success");
      }
      else {
        result = ecb.decrypt(n, buffer);
        puts("decrypting success");
      }
      writeBlock(n, result, output);
    }
    break;
    case 2: {
      CBC cbc(16, key);
      Block * result = NULL;
      
      if (enOrDe == 1) {
        result = cbc.encrypt(n, buffer);
        puts("encrypting success");
      }
      else {
        result = cbc.decrypt(n, buffer);
        puts("decrypting success");
      }
      writeBlock(n, result, output); 
      break;
    }
    case 3: {

      break;
    }
  }
  return 0;
}
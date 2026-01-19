#include "bit_manip/bit_manip.hpp"

string binary(uint64_t n) {
  string bin = "";
  while (n > 0) {
    bin += (n % 2) + 48;
    n = n / 2;
  }
  return bin;
}

int count_1bit(uint64_t n) {
  int c1 = 0;
  while (n > 0) {
    c1 += n % 2;
    n = n >> 1;
  }
  return c1;
}

int degree(uint64_t n) {
  int deg=-1;
  while(n > 0) {
    deg++;
    n>>=1;
  }
  return deg;
}

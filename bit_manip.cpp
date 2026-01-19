#include "bit_manip/bit_manip.hpp"

string binary(int n) {
  string bin = "";
  while (n > 0) {
    bin += (n % 2) + 48;
    n = n / 2;
  }
  return bin;
}

int count_1bit(int n) {
  int c1 = 0;
  while (n > 0) {
    c1 += n % 2;
    n = n >> 1;
  }
  return c1;
}

int degree(int n) {
  int deg;
  for (deg = 0; n > 0; (n /= 2) && deg++)
    ;
  return deg;
}

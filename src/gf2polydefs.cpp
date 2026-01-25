#include "headers/gf2poly.h"
#include <cstdint>
#include <string>

/**
@ trim unecessary blocks
*/
void trim(gf2poly &_P) {
  while (_P.blocks.size() > 1 && _P.blocks.back() == 0)
    _P.blocks.pop_back();
}

/**
@ binary string representation
*/
string bin64(uint64_t n) {
  string bin = "";
  size_t cnt = 0;
  while (cnt++ < 64) {
    bin = "01"[n % 2] + bin;
    n >>= 1;
  }
  return bin;
}

string gf2_bin(gf2poly _Poly) {
  string _bin = "";
  for (auto block : _Poly.blocks)
    _bin = bin64(block) + _bin;
  return _bin;
}

/**
@ degree of the GF2 polynom
*/
size_t degree(gf2poly _Poly) {
  size_t deg = 0, bit_idx = 0;
  for (uint64_t block : _Poly.blocks)
    for (size_t _shi = 0; _shi < 64; _shi++) {
      deg = (block >> _shi) & 1 ? bit_idx : deg;
      bit_idx++;
    }

  return deg;
}

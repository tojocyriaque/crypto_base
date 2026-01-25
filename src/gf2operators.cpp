#include "headers/gf2poly.h"
#include <algorithm>
#include <cmath>
#include <cstdint>

/*
Operator overloading in GF2 polynoms
*/

gf2poly operator<<(gf2poly _Poly, uint64_t _shift) {
  size_t nblock = ceil((degree(_Poly) + _shift + 1) / 64.0);
  _Poly.blocks.resize(nblock);

  for (size_t _sfi = 0; _sfi < _shift; _sfi++) {
    uint64_t _idx_f_bit = _Poly.blocks[0] >> 63;
    _Poly.blocks[0] = _Poly.blocks[0] << 1;

    for (size_t _blk_i = 1; _blk_i < nblock; _blk_i++) {
      // the first bit of the current block
      uint64_t _idx_f_bit_t = _Poly.blocks[_blk_i] >> 63;
      _Poly.blocks[_blk_i] = (_Poly.blocks[_blk_i] << 1) ^ _idx_f_bit;
      _idx_f_bit = _idx_f_bit_t;
    }
  }
  return _Poly;
}

gf2poly operator>>(gf2poly _Poly, uint64_t _shift) {
  size_t nblock = _Poly.blocks.size();
  for (size_t _sfi = 0; _sfi < _shift; _sfi++) {
    // the last bit of the current block
    uint64_t _idx_l_bit = _Poly.blocks[nblock - 1] & 1;
    _Poly.blocks[nblock - 1] = _Poly.blocks[nblock - 1] >> 1;

    for (int _blk_i = nblock - 2; _blk_i >= 0; _blk_i--) {
      if (_blk_i < 0)
        break;

      uint64_t _idx_l_bit_t = _Poly.blocks[_blk_i] & 1;
      _Poly.blocks[_blk_i] = (_Poly.blocks[_blk_i] >> 1) ^ (_idx_l_bit << 63);
      _idx_l_bit = _idx_l_bit_t;
    }
  }
  trim(_Poly);

  return _Poly;
}

gf2poly operator^(gf2poly L, gf2poly R) {
  size_t nblock = max(L.blocks.size(), R.blocks.size());
  L.blocks.resize(nblock);
  R.blocks.resize(nblock);
  gf2poly _Poly;
  for (size_t _idx = 0; _idx < nblock; _idx++) {
    uint64_t res = L.blocks[_idx] ^ R.blocks[_idx];
    _Poly.blocks.push_back(res);
  }
  trim(_Poly);
  return _Poly;
}

gf2poly operator&(gf2poly L, gf2poly R) {
  size_t nblock = max(L.blocks.size(), R.blocks.size());
  L.blocks.resize(nblock);
  R.blocks.resize(nblock);
  gf2poly _Poly;

  for (size_t _idx = 0; _idx < nblock; _idx++) {
    uint64_t res = L.blocks[_idx] & R.blocks[_idx];
    _Poly.blocks.push_back(res);
  }
  trim(_Poly);

  return _Poly;
}

bool operator==(gf2poly L, gf2poly R) {
  size_t nblock = max(L.blocks.size(), R.blocks.size());
  L.blocks.resize(nblock);
  R.blocks.resize(nblock);
  bool eq = true;
  for (size_t _idx = 0; _idx < nblock; _idx++)
    eq &= (L.blocks[_idx] == R.blocks[_idx]);
  return eq;
}

/**
Clean coding arithmetic operations
*/
gf2poly operator*(gf2poly L, gf2poly R) { return gf2poly_mul(L, R); }
gf2poly operator%(gf2poly L, gf2poly R) { return gf2poly_mod(L, R); }
gf2poly operator%=(gf2poly L, gf2poly R) { return gf2poly_gcd(L, R); }
gf2poly operator/(gf2poly L, gf2poly R) { return gf2poly_div(L, R); }
#include "gf2_poly_256/gf2_poly_256.h"
#include <string>

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

string bin(gf2_poly_256_t _Poly) {
  string _bin = "";
  for (auto block : _Poly.blocks)
    _bin += bin64(block);
  return _bin;
}

/*
Operator overloading for GF2 polynomial
*/

/*
@ gf2_poly_256 bit shifting
*/

gf2_poly_256_t operator<<(gf2_poly_256_t _Poly, uint8_t _shift) {
  for (size_t _sfi = 0; _sfi < _shift; _sfi++) {
    uint8_t _idx_f_bit = _Poly.blocks[0] >> 63;
    _Poly.blocks[0] = _sfi < 64 ? (_Poly.blocks[0] << 1) : 0;

    for (size_t _blk_i : {1, 2, 3}) {
      uint8_t _idx_f_bit_t = _Poly.blocks[_blk_i] >> 63;
      _Poly.blocks[_blk_i] = _sfi < 64 * (_blk_i + 1)
                                 ? (_Poly.blocks[_blk_i] << 1) ^ _idx_f_bit
                                 : 0;
      _idx_f_bit = _idx_f_bit_t;
    }
  }
  return _Poly;
}

gf2_poly_256_t operator>>(gf2_poly_256_t _Poly, uint8_t _shift) {
  for (size_t _sfi = 0; _sfi < _shift; _sfi++) {
    uint64_t _idx_l_bit = _Poly.blocks[3] & 1;
    _Poly.blocks[3] = _sfi < 64 ? (_Poly.blocks[0] >> 1) : 0;

    for (size_t _blk_i : {2, 1, 0}) {
      uint64_t _idx_l_bit_t = _Poly.blocks[_blk_i] & 1;
      _Poly.blocks[_blk_i] =
          _sfi < 64 * (4 - _blk_i)
              ? (_Poly.blocks[_blk_i] >> 1) ^ (_idx_l_bit << 63)
              : 0;
      _idx_l_bit = _idx_l_bit_t;
    }
  }
  return _Poly;
}
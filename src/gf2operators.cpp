#include "headers/gf2poly.h"
#include <algorithm>
#include <cstdint>

/*
Operator overloading in GF2 polynoms
*/

gf2poly operator<<(gf2poly _Poly, uint64_t _shift) {
  size_t nblock = 1 + (degree(_Poly) + _shift) / 64;
  _Poly.blocks.resize(nblock);

  for (size_t _sfi = 0; _sfi < _shift; _sfi++) {
    uint64_t _idx_f_bit = _Poly.blocks[0] >> 63;
    _Poly.blocks[0] = _sfi < 64 ? (_Poly.blocks[0] << 1) : 0;

    for (size_t _blk_i = 1; _blk_i < nblock; _blk_i++) {
      // the first bit of the current block
      uint64_t _idx_f_bit_t = _Poly.blocks[_blk_i] >> 63;
      _Poly.blocks[_blk_i] = _sfi < 64 * (_blk_i + 1)
                                 ? (_Poly.blocks[_blk_i] << 1) ^ _idx_f_bit
                                 : 0;
      _idx_f_bit = _idx_f_bit_t;
    }
  }
  return _Poly;
}

// gf2poly operator<<(gf2poly p, uint64_t _shift) {
//   size_t nblock = 1 + (degree(p) + _shift) / 64;
//   p.blocks.resize(nblock, 0);

//   int block_shift = _shift / 64;
//   int bits_shift = _shift % 64;

//   // block shifting
//   for (int bi = nblock - 1; bi >= 0; bi--)
//     if (bi >= block_shift)
//       p.blocks[bi] = p.blocks[bi - block_shift];
//     else if (bi >= 0)
//       p.blocks[bi] = 0;

//   if (bits_shift == 0)
//     return p;

//   // bits shifting
//   uint64_t fb = 0, fb_t = 0;
//   for (size_t bi = 0; bi < nblock; bi++) {
//     fb_t = p.blocks[bi] >> (64 - bits_shift);
//     p.blocks[bi] = (p.blocks[bi] << bits_shift) ^ fb;
//     fb = fb_t;
//   }
//   return p;
// }

gf2poly operator>>(gf2poly _Poly, uint64_t _shift) {
  size_t nblock = _Poly.blocks.size();
  for (size_t _sfi = 0; _sfi < _shift; _sfi++) {
    // the last bit of the current block
    uint64_t _idx_l_bit = _Poly.blocks[nblock - 1] & 1;
    _Poly.blocks[nblock - 1] = _sfi < 64 ? (_Poly.blocks[nblock - 1] >> 1) :
    0;

    if (nblock < 2)
      continue;

    for (size_t _blk_i = nblock - 2; _blk_i > 0; _blk_i--) {
      // cout << "size: " << nblock << " => index: " << _blk_i << endl;
      uint64_t _idx_l_bit_t = _Poly.blocks[_blk_i] & 1;
      _Poly.blocks[_blk_i] =
          _sfi < 64 * (nblock - _blk_i)
              ? (_Poly.blocks[_blk_i] >> 1) ^ (_idx_l_bit << 63)
              : 0;
      _idx_l_bit = _idx_l_bit_t;
    }
  }
  return _Poly;
}


// gf2poly operator>>(gf2poly p, uint64_t shift) {
//   size_t deg = degree(p);
//   if (deg <= shift)
//     return 0;

//   int pblock = p.blocks.size();
//   int nblock = 1 + (deg - shift) / 64;

//   int block_shift = shift / 64;
//   int bits_shift = shift % 64;

//   // block shifting
//   for (int bi = 0; bi < pblock; bi++)
//     if (bi + block_shift < pblock)
//       p.blocks[bi] = p.blocks[bi + block_shift];
//     else
//       p.blocks[bi] = 0;

//   if (bits_shift == 0) {
//     p.blocks.resize(nblock);
//     return p;
//   }

//   // bits shifting
//   for (int bi = 0; bi < pblock; bi++) {
//     p.blocks[bi] = p.blocks[bi] >> bits_shift;
//     if (bi + 1 < pblock)
//       p.blocks[bi] = p.blocks[bi] ^ (p.blocks[bi + 1] << (64 - bits_shift));
//     else
//       p.blocks[bi] = p.blocks[bi] ^ 0;
//   }
//   p.blocks.resize(nblock);
//   return p;
// }

gf2poly operator^(gf2poly L, gf2poly R) {
  size_t nblock = max(L.blocks.size(), R.blocks.size());
  L.blocks.resize(nblock, 0);
  R.blocks.resize(nblock, 0);
  gf2poly p;
  for (size_t _idx = 0; _idx < nblock; _idx++)
    p.blocks.push_back(L.blocks[_idx] ^ R.blocks[_idx]);

  trim(p);
  return p;
}

gf2poly operator&(gf2poly L, gf2poly R) {
  size_t nblock = max(L.blocks.size(), R.blocks.size());
  L.blocks.resize(nblock);
  R.blocks.resize(nblock);
  gf2poly p;

  for (size_t _idx = 0; _idx < nblock; _idx++)
    p.blocks.push_back(L.blocks[_idx] & R.blocks[_idx]);

  trim(p);
  return p;
}

bool operator==(gf2poly L, gf2poly R) { return L.blocks == R.blocks; }
bool operator!=(gf2poly L, gf2poly R) { return L.blocks != R.blocks; }

/**
Clean coding arithmetic operations
*/
gf2poly operator*(gf2poly L, gf2poly R) { return gf2poly_mul(L, R); }
gf2poly operator%(gf2poly L, gf2poly R) { return gf2poly_mod(L, R); }
gf2poly operator%=(gf2poly L, gf2poly R) { return gf2poly_gcd(L, R); }
gf2poly operator/(gf2poly L, gf2poly R) { return gf2poly_div(L, R); }
#include "headers/gf2poly.h"
#include <algorithm>
#include <cstdint>

/*
Operator overloading in GF2 polynoms
*/

gf2poly operator<<(gf2poly p, uint64_t _shift) {
  size_t nblock = 1 + (degree(p) + _shift) / 64;
  p.blocks.resize(nblock, 0);

  int block_shift = _shift / 64;
  int bits_shift = _shift % 64;

  // block shifting
  for (int bi = nblock - 1; bi >= 0; bi--)
    if (bi >= block_shift)
      p.blocks[bi] = p.blocks[bi - block_shift];
    else if (bi >= 0)
      p.blocks[bi] = 0;

  if (bits_shift == 0)
    return p;

  // bits shifting
  for (int bi = nblock - 1; bi >= 1; bi--)
    p.blocks[bi] =
        (p.blocks[bi] << bits_shift) ^ (p.blocks[bi - 1] >> (64 - bits_shift));
  p.blocks[0] = p.blocks[0] << bits_shift;
  return p;
}

gf2poly operator>>(gf2poly p, uint64_t shift) {
  // cout << "dp: " << degree(p) << " , " << shift << endl;
  uint64_t dp = degree(p);
  if (dp < shift)
    return 0;

  int nblock = 1 + (dp - shift) / 64;
  int pblock = p.blocks.size();

  int block_shift = shift / 64;
  int bits_shift = shift % 64;

  // block shifting
  for (int bi = 0; bi < pblock; bi++)
    if (bi + block_shift < pblock)
      p.blocks[bi] = p.blocks[bi + block_shift];
    else
      p.blocks[bi] = 0;

  if (bits_shift == 0) {
    p.blocks.resize(nblock);
    return p;
  }

  for (int bi = 0; bi < pblock - 1; bi++)
    p.blocks[bi] =
        (p.blocks[bi] >> bits_shift) ^ (p.blocks[bi + 1] << (64 - bits_shift));
  p.blocks[pblock - 1] = p.blocks[pblock - 1] >> bits_shift;
  p.blocks.resize(nblock);
  return p;
}

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
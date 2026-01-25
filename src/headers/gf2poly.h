#ifndef __GF2POLY__
#define __GF2POLY__

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
using namespace std;

/*
dynamic number of bits GF2 polynome composed of 64bits blocks
*/
struct gf2poly {
  // uint64_t blocks[4];
  vector<uint64_t> blocks;

  gf2poly() : blocks{} {}

  gf2poly(uint64_t r) : blocks{r} {}

  gf2poly(vector<uint64_t> arr) : blocks(arr) {}
};

/*
Operator overloading for GF2 polynomial
*/
gf2poly operator<<(gf2poly, uint64_t);
gf2poly operator>>(gf2poly, uint64_t);

gf2poly operator^(gf2poly, gf2poly);
gf2poly operator&(gf2poly, gf2poly);
bool operator==(gf2poly, gf2poly);

void trim(gf2poly&);
/* Binary representation */
string bin64(uint64_t n);
string gf2_bin(gf2poly);

/* Degree of the integer uint256_t */
size_t degree(gf2poly);

/**
Arithmetic operations
*/
gf2poly gf2poly_mul(gf2poly, gf2poly);
gf2poly gf2poly_mod(gf2poly, gf2poly);
gf2poly gf2poly_gcd(gf2poly, gf2poly);
gf2poly gf2poly_div(gf2poly, gf2poly);
gf2poly gf2poly_pow_mod(gf2poly a, gf2poly n, gf2poly m);

/**
Clean coding arithmetic operations
*/
gf2poly operator*(gf2poly, gf2poly);
gf2poly operator%(gf2poly, gf2poly);
gf2poly operator%=(gf2poly, gf2poly); // GCD
gf2poly operator/(gf2poly, gf2poly);

#endif

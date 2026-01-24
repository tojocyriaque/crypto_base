#ifndef __POLY256__
#define __POLY256__

#include <cstdint>
#include <string>
using namespace std;

/*
256-bits GF2 polynome composed of 4 64bits blocks
*/
struct gf2_poly_256_t {
  uint64_t blocks[4];

  gf2_poly_256_t() : blocks{0, 0, 0, 0} {}

  gf2_poly_256_t(uint64_t r) : blocks{r, 0, 0, 0} {}

  gf2_poly_256_t(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
      : blocks{a, b, c, d} {}
};

/*
Operator overloading for GF2 polynomial
*/

gf2_poly_256_t operator^(gf2_poly_256_t, gf2_poly_256_t);
gf2_poly_256_t operator&(gf2_poly_256_t);
bool operator==(gf2_poly_256_t, gf2_poly_256_t);
gf2_poly_256_t operator<<(gf2_poly_256_t, uint8_t);
gf2_poly_256_t operator>>(gf2_poly_256_t, uint8_t);

/* Binary representation */
string bin64(uint64_t n);
string bin(gf2_poly_256_t);

/* Degree of the integer uint256_t */
int degree(gf2_poly_256_t);

#endif

#ifndef ARITHMETIC
#define ARITHMETIC

#include <cstdint>

uint64_t poly_mul_naive(uint32_t P, uint32_t Q);
uint64_t poly_mul(uint32_t P, uint32_t Q);
uint64_t poly_mod(uint64_t P, uint64_t Q);
uint64_t poly_gcd(uint64_t P, uint64_t Q);

#endif // !ARITHMETIC

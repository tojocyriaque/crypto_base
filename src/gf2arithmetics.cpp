#include "headers/gf2poly.h"

/**
Arithmetic operations
*/
gf2poly gf2poly_mul(gf2poly P, gf2poly Q) {
  size_t dp = degree(P);
  gf2poly _Pol = 0;
  for (size_t k = 0; k <= dp; k++) {
    if (((P >> k) & 1) != 0)
      _Pol = _Pol ^ (Q << k);
  }
  trim(_Pol);
  return _Pol;
}

gf2poly gf2poly_mod(gf2poly P, gf2poly Q) {
  size_t dp, dq = degree(Q);
  while ((dp = degree(P)) >= dq)
    P = P ^ (Q << (dp - dq));

  trim(P);
  return P;
}

gf2poly gf2poly_gcd(gf2poly P, gf2poly Q) {
  gf2poly R = 0;
  while (Q != 0) {
    R = gf2poly_mod(P, Q);
    P = Q;
    Q = R;
  }
  trim(P);
  return P;
}

gf2poly gf2poly_div(gf2poly P, gf2poly Q) {
  size_t dp = degree(P), dq = degree(Q);
  gf2poly quotient = 0;
  while ((dp = degree(P)) >= dq) {
    size_t shift = dp - dq;
    P = P ^ (Q << shift);
    quotient = quotient ^ (gf2poly(1) << shift);
  }
  trim(quotient);
  return quotient;
}

gf2poly gf2poly_pow_mod(gf2poly a, gf2poly n, gf2poly m) {
  gf2poly res = 1, base = a % m;
  while (n != 0) {
    if ((n & 1) == 1)
      res = (res * base) % m;

    base = (base * base) % m;
    n = n >> 1;
  }
  trim(res);
  return res;
}
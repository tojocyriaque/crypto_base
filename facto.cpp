#include "64bits/arithmetic.hpp"

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

string polynomial(uint64_t P);
int main() {
  cout << "Décomposition en facteur irréductibles de P(x) = x⁵ + x⁴ + 1"
       << endl;

  uint64_t P = 49;
  for (uint64_t Q = 1; Q < P; Q++) {
    uint64_t R = poly_mod(P, Q);
    if (R == 0) {
      uint64_t G = poly_div(P, Q);
      cout << "(" << polynomial(P) << ")" << " = (" << polynomial(G) << ")"
           << " * (" << polynomial(Q) << ")" << endl;
    }
  }
  return 0;
}

string polynomial(uint64_t P) {
  string pol = "";
  int p = 0;
  while (P > 0) {
    if (P % 2 == 1) {
      pol = (p == 0 ? "1" : p == 1 ? "x" : "x" + to_string(p)) + pol;
    } else {
      p++;
      P >>= 1;
      continue;
    }
    p++;
    P >>= 1;
    if (P != 0)
      pol = " + " + pol;
  }
  return pol;
}


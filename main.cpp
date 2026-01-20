
#include "64bits/facto.hpp"
#include <iostream>
using namespace std;

int main() {
  cout << "Décomposition en facteur irréductibles de P(x) = x⁵ + x⁴ + 1"
       << endl;

  uint64_t P = 49;
  find_factorisation(P);
  return 0;
}


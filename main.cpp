#include <iostream>
#include <cstdint>

using namespace std;

string polynomial_exp(uint64_t P);
void find_factorisation(uint64_t P);
int main() {
  cout << "Décomposition en facteur irréductibles de P(x) = x⁵ + x⁴ + 1"
       << endl;

  uint64_t P = 49;
  find_factorisation(P);
  return 0;
}


#include "arithmetic/arithmetic.hpp"
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  uint32_t P = 3, Q = 3;
  uint64_t R = poly_mul(P, Q);

  cout << "poly_mul: " << P << " X " << Q << " = " << R << endl;
  return 0;
}

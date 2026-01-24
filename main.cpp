#include "gf2_poly_256/gf2_poly_256.h"
#include <iostream>

void show_gf2_poly(gf2_poly_256_t poly);

using namespace std;
int main() {
  gf2_poly_256_t poly;
  poly.blocks[0] = 0;
  poly.blocks[1] = 0;
  poly.blocks[2] = 0;
  poly.blocks[3] = 1;

  return 0;
}

void show_gf2_poly(gf2_poly_256_t poly) {
  for (auto block : poly.blocks)
    cout << block << " ";
}
#include "gf2_poly_256/gf2_poly_256.h"
#include <iostream>


void show_gf2_poly(gf2_poly_256_t poly);

using namespace std;
int main() {
  gf2_poly_256_t poly(0,1,0,1);

  show_gf2_poly(poly);
  cout << "=> ";
  show_gf2_poly(poly >> 64);

  return 0;
}

void show_gf2_poly(gf2_poly_256_t poly) {
  for (auto block : poly.blocks)
    cout << block << " ";
}
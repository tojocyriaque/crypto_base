#include "headers/gf2poly.h"
#include <iostream>

using namespace std;

void test_regression() {
  gf2poly A(49); // x^5 + x^4 + 1
  gf2poly B(7);  // x^2 + x + 1

  gf2poly Q = A / B;
  gf2poly R = A % B;

  // On sait d'après tes tests précédents que :
  // A / B doit être 11 (x^3 + x + 1)
  // A % B doit être 0
  if (Q == gf2poly(11) && R == gf2poly(0)) {
    cout << "Test de régression réussi !" << endl;
  } else {
    cout << "ÉCHEC : Vérifie tes opérateurs / et %" << endl;
  }
}

void test_boundary() {
  gf2poly A = 1ULL << 63; // Un bit tout à gauche du premier wagon
  gf2poly B = A << 1;

  if (B.blocks.size() >= 2 && B.blocks[1] == 1 && B.blocks[0] == 0) {
    cout << "Test de frontière réussi (Shift OK) !" << endl;
  } else {
    cout << "ÉCHEC : Ton shift ne gère pas le passage entre wagons." << endl;
  }
}

void test_pow_mod() {
  gf2poly x(2);  // x
  gf2poly M(11); // x^3 + x + 1
  gf2poly result = gf2poly_pow_mod(x, 4, M);

  if (result == gf2poly(6)) { // 6 = 110 en binaire (x^2 + x)
    cout << "SUCCESS: Square and Multiply est correct !" << endl;
  } else {
    cout << "ERROR: Attendu 6, obtenu " << gf2_bin(result) << endl;
  }
}

int main() {
  test_regression();
  test_boundary();
  test_pow_mod();
  return 0;
}

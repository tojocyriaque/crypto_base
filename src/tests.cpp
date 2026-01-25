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

void test_frobenius_large() {
  gf2poly A;
  A.blocks = {1ULL, 1ULL}; // x^64 + 1

  gf2poly res = A * A; // Doit donner x^128 + 1

  if (degree(res) == 128 && res.blocks[0] == 1ULL && res.blocks[2] == 1ULL) {
    cout << "Test de Frobenius (128 bits) : RÉUSSI" << endl;
  } else {
    cout << "ÉCHEC : Problème de multiplication ou de stockage large." << endl;
  }
}

void test_large_modulo() {
  gf2poly M;
  M.blocks = {1ULL, 0, 0, 1ULL << 63}; // x^255 + 1

  gf2poly A;
  A.blocks = {0, 0, 0, 1ULL << 63}; // x^255

  gf2poly R = A % M;

  if (degree(R) == 0 && R.blocks[0] == 1ULL) {
    cout << "Test Grand Modulo (255 bits) : RÉUSSI" << endl;
  } else {
    cout << "ÉCHEC : Ta division ne réduit pas correctement les hauts degrés."
         << endl;
  }
}

void test_crypto_grade() {
  // x^128 + x^7 + x^2 + x + 1
  gf2poly P;
  P.blocks = {135ULL, 0,
              1ULL}; // 135 = 10000111 (x7+x2+x+1) et 1ULL au bloc 2 (x128)

  gf2poly x(2);
  // On calcule x^(2^128) mod P
  // Attention: 2^128 est un énorme exposant, pow_mod doit le gérer (en uint64_t
  // c'est dur, utilise une boucle de 128 carrés successifs)

  gf2poly res = x;
  for (int i = 0; i < 128; i++) {
    res = (res * res) % P;
  }

  if (degree(res) == 1 && res.blocks[0] == 2ULL) {
    cout << "Test Crypto-Grade (128 bits) : RÉUSSI. Tu es prêt pour Alpha "
            "Centauri."
         << endl;
  } else {
    cout << "ÉCHEC : L'exponentiation modulaire accumule des erreurs." << endl;
  }
}

int main() {
  test_regression();
  test_boundary();
  test_pow_mod();
  test_frobenius_large();
  test_large_modulo();
  test_crypto_grade();
  return 0;
}

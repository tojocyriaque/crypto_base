#include "headers/gf2poly.h"
#include <iostream>

using namespace std;
int main() {
  gf2poly _Poly_ = gf2poly(1) << 64;
  cout << "bin: " << gf2_bin(_Poly_) << " => deg: " << degree(_Poly_) << endl;
  cout << "----------" << endl;
  _Poly_ = _Poly_ & gf2poly(1);
  cout << "bin: " << gf2_bin(_Poly_) << " => deg: " << degree(_Poly_) << endl;
  return 0;
}

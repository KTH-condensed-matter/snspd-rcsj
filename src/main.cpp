#include <iostream>
#include "math/TridiagonalMatrix.h"
#include "Parameters.h"

int main() {
  std::cout << "Hello, World!" << '\n';

  using namespace snspd::math;

  auto matrix = TridiagonalMatrix<double>(3);
  matrix.fill_diagonal(TridiagonalMatrix<double>::DIAG, 1);
  matrix.fill_diagonal(TridiagonalMatrix<double>::UPPER, 0);
  matrix.fill_diagonal(TridiagonalMatrix<double>::LOWER, 0);

  std::cout << matrix.get_diagonal(TridiagonalMatrix<double>::DIAG).at(0) << '\n';

  auto matrix2 = 2 * matrix;

  return 0;
}

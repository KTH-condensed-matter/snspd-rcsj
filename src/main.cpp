#include <iostream>
#include "math/TridiagonalMatrix.h"
#include "Parameters.h"
#include "Model.h"

int main() {

  std::size_t size{10};

  snspd::Parameters params {
      size,
      0.01,
      1.0,
      1,
      0.0,
      0.0,
      0.5,
      std::vector<double>(size, 1.0),
      std::vector<double>(size, 0.0),
      std::vector<double>(size, 0.0),
      std::vector<double>(size, 0.0)
  };

  std::size_t multiplier = params.size;
  double arcsin_bias_current_ratio = asin(fmin(params.ib, 1.0));
  for (auto &value: params.x) {
    value = static_cast<double>(multiplier--) * arcsin_bias_current_ratio;
  }

  snspd::Model model(params);


  for (std::size_t i = 0; i < 1000000; ++i) {
    model.run();
  }

  std::cout << params << '\n';

  return 0;
}

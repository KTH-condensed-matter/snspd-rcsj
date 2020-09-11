#include <iostream>
#include <spdlog/spdlog.h>
#include "math/TridiagonalMatrix.h"
#include "Parameters.h"
#include "Model.h"
#include "io/ConfigParser.h"
#include "io/exception/FileNotFound.h"

int main() {

  using namespace snspd;

  std::size_t size{10};

  Parameters params {
    0,
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

  Model model(params);

  std::size_t steps{1000};

  for (std::size_t i = 0; i < steps; ++i) {
    model.run();
  }

  std::cout << params << '\n';

  // TODO implement ConfigParser
  try {
    io::ConfigParser config("settings.json");
  } catch (const io::FileNotFound &e) {
    spdlog::critical(e.what());
    return 1;
  } catch (const nlohmann::detail::parse_error &e) {
    spdlog::critical(e.what());
    return 1;
  }

  return 0;
}

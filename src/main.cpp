#include <iostream>
#include <docopt/docopt.h>
#include <spdlog/spdlog.h>
#include "math/TridiagonalMatrix.h"
#include "Parameters.h"
#include "Model.h"
#include "io/ConfigParser.h"
#include "io/exception/FileNotFound.h"

static constexpr auto USAGE = R"(
SNSPD simulation using the non-linear resistive and capacitive shunted junction model

Usage:
  snspd [options]

Options:
  -h, --help              Show the help screen.
  -V, --version           Display the version.
  -v, --verbose           Run program in verbose mode.
  -c, --config=<CONFIG>   Path to the JSON config file [default: settings.json].
  -o, --output=<OUTPUT>   HDF5 file to store output data.
)";

int main(int argc, char *argv[]) {

  using namespace snspd;

  auto args = docopt::docopt(USAGE,{ std::next(argv), std::next(argv, argc) },true,"v1.0.0");

  // Check if verbose logging should be enabled
  if (args.at("--verbose").asBool()) {
    spdlog::set_level(spdlog::level::debug);
    spdlog::debug("Verbose mode enabled.");
  }

  // Get the config parser;
  io::ConfigParser config(args);

  std::cout << config.get_config(0) << '\n';

  std::size_t size{10};

  Parameters params {
    0,
    1000,
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

  return 0;
}

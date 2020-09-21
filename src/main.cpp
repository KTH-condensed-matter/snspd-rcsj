#include <iostream>
#include <docopt/docopt.h>
#include <spdlog/spdlog.h>
#include <h5pp/h5pp.h>
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

  Model model(config.get_config());

  for (std::size_t i = 0; i < config.get_config().max_steps; ++i) {
    config.update_params(i);
    model.run();
  }

  std::cout << config.get_config() << '\n';

  h5pp::File file("test.h5");
  file.writeDataset(config.get_config().x, "phase");

  return 0;
}

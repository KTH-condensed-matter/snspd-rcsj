#include <fstream>
#include <filesystem>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <random>
#include "ConfigParser.h"
#include "exception/FileNotFound.h"
#include "../exception/NotImplemented.h"

nlohmann::json snspd::io::ConfigParser::get_config(const std::string &path) {

  spdlog::debug("Reading config from {}", path);

  // Make sure that the file exists
  if (!std::filesystem::exists(path)) {
    throw FileNotFound(fmt::format("JSON config file {} does not exist.", path));
  }

  std::ifstream json_file(path);
  nlohmann::json out;
  json_file >> out;
  return out;
}

nlohmann::json snspd::io::ConfigParser::get_config(const std::map<std::string, docopt::value> &args) {

  // Path to the config file
  std::string path = args.at("--config").asString();

  // Get the config
  auto out = get_config(path);

  if (args.at("--output")) {
    out["output"] = args.at("--output").asString();
  }

  return out;
}

snspd::Parameters snspd::io::ConfigParser::init_params(const nlohmann::json &config) {

  // Get the initial config values
  auto init_config = config["initial"];

  // Get the system size
  std::size_t size{init_config["size"].get<std::size_t>()};

  Parameters params {
      0,
      init_config["maxSteps"].get<unsigned long>(),
      size,
      init_config["dt"],
      init_config["q"],
      init_config["c0"],
      init_config["vg"],
      init_config["nl"],
      init_config["ib"],
      get_param_vector(init_config["ic"], config),
      get_param_vector(init_config["x"], config),
      get_param_vector(init_config["v"], config),
      get_param_vector(init_config["rqp"], config)
  };

  return params;
}

std::vector<double> snspd::io::ConfigParser::get_param_vector(const nlohmann::json &vec, const nlohmann::json &config) {

  // Get the system size
  std::size_t size{config["initial"]["size"].get<std::size_t>()};

  // Create the object to be returned
  std::vector<double> out(size);

  // Fill the vector with a number if a scalar is given
  if (vec.is_number()) {
    std::fill(out.begin(), out.end(), vec.get<double>());
  }

  // Fill the vector with the array values if an array is given
  else if (vec.is_array()) {
    out = config.get<std::vector<double>>();
  }

  // If it has stationaryPhase set to true than fill with vector that makes the phases stationary
  else if (vec.is_object() && vec.contains("stationaryPhase")) {
    std::size_t multiplier{size};
    double arcsin_ratio{std::asin(std::min(config["initial"]["ib"].get<double>(), 1.0))};

    std::generate(out.begin(), out.end(), [&]() {
      return static_cast<double>(multiplier--) * arcsin_ratio;
    });
  }

  // If it has random set to true then fill with random values between min and max
  else if (vec.is_object() && vec.contains("random")) {
    std::random_device uniform_rnd_dev;
    std::mt19937 uniform_rnd_gen(uniform_rnd_dev());
    std::uniform_real_distribution<double> uniform_dist(vec["min"].get<double>(), vec["max"].get<double>());

    std::generate(out.begin(), out.end(), [&](){
      return uniform_dist(uniform_rnd_gen);
    });
  }

  // No method found
  else {
    throw NotImplemented("The selected method for filling the vector is not implemented.");
  }

  return out;
}

snspd::Parameters &snspd::io::ConfigParser::get_config([[maybe_unused]] std::size_t step) {

  // TODO implement this
  return m_param;
}

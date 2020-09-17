#include <fstream>
#include <filesystem>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include "ConfigParser.h"
#include "exception/FileNotFound.h"

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

  auto init_config = config["initial"];

  Parameters params {
      0,
      init_config["maxSteps"],
      init_config["size"],
      init_config["dt"],
      init_config["q"],
      init_config["c0"],
      init_config["vg"],
      init_config["nl"],
      init_config["ib"],
      std::vector<double>(init_config["size"], 1.0),
      std::vector<double>(init_config["size"], 0.0),
      std::vector<double>(init_config["size"], 0.0),
      std::vector<double>(init_config["size"], 0.0)
  };

  return params;
}

snspd::Parameters &snspd::io::ConfigParser::get_config([[maybe_unused]] std::size_t step) {

  // TODO implement this
  return m_param;
}

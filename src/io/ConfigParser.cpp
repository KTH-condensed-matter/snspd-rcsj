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

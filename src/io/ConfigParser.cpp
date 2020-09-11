#include <fstream>
#include <filesystem>
#include <fmt/format.h>
#include "ConfigParser.h"
#include "exception/FileNotFound.h"

nlohmann::json snspd::io::ConfigParser::get_config(const std::string &path) {

  // Make sure that the file exists
  if (!std::filesystem::exists(path)) {
    throw FileNotFound(fmt::format("JSON config file {} does not exist.", path));
  }

  std::ifstream json_file(path);
  nlohmann::json out;
  json_file >> out;
  return out;
}

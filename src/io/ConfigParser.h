#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <docopt/docopt.h>

namespace snspd::io {
  class ConfigParser {
    nlohmann::json m_config;

    [[nodiscard]] nlohmann::json static get_config(const std::string &path);
    [[nodiscard]] nlohmann::json static get_config(const std::map<std::string, docopt::value> &args);

  public:
    explicit ConfigParser(const std::string &path):
      m_config(get_config(path)) {

    }

    explicit ConfigParser(const std::map<std::string, docopt::value> &args):
      m_config(get_config(args)) {
      std::cout << m_config << '\n';
    }

  };
}

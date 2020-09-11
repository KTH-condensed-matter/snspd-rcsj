#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>

namespace snspd::io {
  class ConfigParser {
    nlohmann::json m_config;

    [[nodiscard]] nlohmann::json static get_config(const std::string &path);

  public:
    explicit ConfigParser(const std::string &path):
      m_config(get_config(path)) {
     std::cout << m_config << '\n';
    }

  };
}

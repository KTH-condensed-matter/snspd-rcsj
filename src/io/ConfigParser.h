#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <docopt/docopt.h>
#include "../Parameters.h"

namespace snspd::io {
  class ConfigParser {
    nlohmann::json m_config;
    Parameters m_param;

    [[nodiscard]] static nlohmann::json get_config(const std::string &path);
    [[nodiscard]] static nlohmann::json get_config(const std::map<std::string, docopt::value> &args);
    [[nodiscard]] static Parameters init_params(const nlohmann::json &config);

  public:
    explicit ConfigParser(const std::string &path):
      m_config(get_config(path)),
      m_param(init_params(m_config)) {

    }

    explicit ConfigParser(const std::map<std::string, docopt::value> &args):
      m_config(get_config(args)),
      m_param(init_params(m_config)) {

    }

    [[nodiscard]] Parameters& get_config(std::size_t step);
  };
}

#pragma once

#include <h5pp/h5pp.h>
#include "ConfigParser.h"

namespace snspd::io {
  class Exporter {
    ConfigParser &m_config;

    std::vector<double>
        m_v,
        m_ib,
        m_t;

    h5pp::File m_file;

  public:

    explicit Exporter(ConfigParser &config):
        m_config(config),
        m_v(config.get_params().max_steps, 0.0),
        m_ib(config.get_params().max_steps, 0.0),
        m_t(config.get_params().max_steps, 0.0),
        m_file(config.get_settings().output) {

      save(config.get_params());
    }

    void save(const Parameters &param);
    void flush();
  };
}



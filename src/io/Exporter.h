#pragma once

#include <h5pp/h5pp.h>
#include "../Settings.h"
#include "../Parameters.h"

namespace snspd::io {
  class Exporter {
    const Settings &m_settings;

    std::vector<double> m_v;

    h5pp::File m_file;

  public:

    Exporter(const Settings &settings, const Parameters &params):
      m_settings(settings),
      m_v(params.max_steps + 1),
      m_file(settings.output) {
      save(params);
    }

    void save(const Parameters &param);
    void flush();
  };
}



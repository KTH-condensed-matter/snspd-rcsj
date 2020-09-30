#pragma once

#include "BoundaryCondition.h"

namespace snspd::bc {
  class VoltageBiasBoundaryCondition : public BoundaryCondition {
  public:

    explicit VoltageBiasBoundaryCondition(Parameters &param):
        BoundaryCondition(param) {

    }

    // Update the bias current with the bias voltage
    void run() override {

      // The voltage drop across the resistor is given by vb - v0.
      m_param.ib = (m_param.vb - + m_param.v.at(0)) / m_param.rt;
    }
  };
}

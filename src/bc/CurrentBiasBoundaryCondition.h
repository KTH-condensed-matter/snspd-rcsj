#pragma once

#include "BoundaryCondition.h"

namespace snspd::bc {
  class CurrentBiasBoundaryCondition : public BoundaryCondition {
  public:

    explicit CurrentBiasBoundaryCondition(Parameters &param):
        BoundaryCondition(param) {

    }

    // The bias current is used as input
    void run() override {}
  };
}

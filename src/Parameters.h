#pragma once

#include <vector>
#include "math/TridiagonalMatrix.h"

namespace snspd {
  struct Parameters {

    // The number of segments.
    // Cannot be changed when the simulation has started.
    const std::size_t size;

    // Measured in units of L_K/R.
    // Cannot be changed when the simulation has started.
    const double dt;

    double

        // Quality factor R \sqrt(C / L).
        q,

        // Capacitance to ground in terms of the capacitance C.
        c0,

        // Cut-off voltage in terms of R I_c.
        // Below this voltage the resistance is given by rqp.
        // Above this voltage the resistance is given by 1 (= R / R).
        vg,

        // Noise level given by \sqrt(2 k_B T / (R I_c^2))
        nl,

        // Bias current in terms of the critical current.
        ib;

    std::vector<double>

        // Critical current that can vary across the nanowire.
        // Measured in terms of I_c, i.e. 1 corresponds to normal critical current and values less than 1 corresponds to
        // a reduces critical current.
        ic,

        // The phase at each site.
        x,

        // The voltage at each site.
        v,

        // Quasiparticle resistance in terms of the resistance R.
        // The resistance can take different values for each site.
        rqp;
  };
}

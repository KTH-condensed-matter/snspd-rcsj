#include <catch2/catch.hpp>
#include "../src/math/VectorOperations.h"
#include "../src/math/TridiagonalMatrix.h"
#include "../src/Parameters.h"
#include "../src/Model.h"

TEST_CASE("Comparison with analytical calculation", "[rcsj]") {
  using namespace snspd;
  using namespace snspd::math;
  using mat = TridiagonalMatrix<double>;
  using vec = std::vector<double>;

  SECTION("2 sites case") {
    double
        dt{1.5},
        vg{2.0},
        rqp{3.0},
        c0{4.0},
        ib{0.7},
        q{1.1};

    vec
        x{0.0, 0.0},
        v{2 * vg, 0.0};

    // Compute x at dt / 2
    x += v * (dt / 2.0);

    // Force plus dampening
    vec force_damp = dt * (vec{ib, 0.0} + sin(vg * dt) * vec{-1.0, 1.0} - 2 * vg * vec{1.0, -1.0});

    spdlog::info("{}", force_damp);

    // Mass dampening matrix
    mat mass_dampening(2);
    mass_dampening.set(mat::DIAG, 0, (1.0 + c0) * q * q + dt / 2.0);
    mass_dampening.set(mat::UPPER, 0, - (q * q + dt / 2.0));
    mass_dampening.set(mat::LOWER, 0, - (q * q + dt / 2.0 ));
    mass_dampening.set(mat::DIAG, 1, (2.0 + c0) * q * q + dt / 2.0 * (1.0 + 1.0 / rqp));

    // Compute v at dt
    v += mass_dampening.lu_factorize().solve(force_damp);

    // Compute x at dt
    x += v * (dt / 2.0);

    // Solve using standard algorithm
    Parameters parameters{
        0,
        1,
        1,
        0,
        2,
        dt,
        q,
        c0,
        1.0,
        vg,
        0.0,
        ib,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        vec(2, 1.0),
        vec(2, 0.0),
        vec{2 * vg, 0.0},
        vec(2, rqp)
    };

    Settings settings{
      "",
      true,
      false
    };

    event::EventStorage storage(settings);

    Model model(parameters, storage);

    model.run();

    REQUIRE(norm(x - parameters.x) < 1e-7);
    REQUIRE(norm(v - parameters.v) < 1e-7);
  }
}

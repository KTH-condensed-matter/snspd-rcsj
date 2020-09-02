#pragma once

#include <random>
#include "Parameters.h"

namespace snspd {
  class Model {
    Parameters &m_param;

    const math::TridiagonalMatrix<double> m_mass;

    std::random_device m_rnd_dev;
    std::mt19937 m_rnd_gen;
    std::normal_distribution<double> m_rnd_dist;

    // Generate random vector with a specified length and amplitude.
    // The random numbers have zero mean and standard deviation amplitude
    std::vector<double> generate_rnd_vector(double amplitude, std::size_t length);

    // Generate the mass matrix M
    [[nodiscard]] static math::TridiagonalMatrix<double> generate_mass_matrix(const Parameters &param);

    // Generate the matrix A
    [[nodiscard]] static math::TridiagonalMatrix<double> generate_alpha_matrix(const Parameters &param);

    // Get the resistance
    [[nodiscard]] static double get_resistance(const Parameters &param, std::size_t site);

    // Get the voltage
    [[nodiscard]] static double get_voltage(const Parameters &param, std::size_t site);

    // Get the force
    [[nodiscard]] std::vector<double> get_force_damping(const Parameters &param,
                                                        const math::TridiagonalMatrix<double> &alpha);

  public:
    explicit Model(Parameters &param):
      m_param(param),
      m_mass(generate_mass_matrix(param)),
      m_rnd_gen(m_rnd_dev()),
      m_rnd_dist(0.0, 1.0) {

    }

    // Take one time step
    void run();
  };
}



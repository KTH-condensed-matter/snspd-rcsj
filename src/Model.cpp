#include <algorithm>
#include <cmath>
#include "Model.h"
#include "math/TridiagonalLuMatrix.h"
#include "math/VectorOperations.h"

void snspd::Model::run() {
  math::TridiagonalMatrix<double> alpha = generate_alpha_matrix(m_param);

  math::TridiagonalLuMatrix<double> mass_alpha = ((m_param.dt / 2) * alpha + m_mass).lu_factorize();

}

std::vector<double> snspd::Model::generate_rnd_vector(double amplitude, std::size_t length) {
  std::vector<double> rnd_vec(length);

  std::generate(rnd_vec.begin(), rnd_vec.end(), [&] {
    return amplitude * m_rnd_dist(m_rnd_gen);
  });

  return rnd_vec;
}

snspd::math::TridiagonalMatrix<double> snspd::Model::generate_mass_matrix(const Parameters &param) {
  using mat = math::TridiagonalMatrix<double>;

  mat mass(param.size);

  // Fill the diagonal with {(1 + c0)q^2, (2 + c0)q^2, (2 + c0)q^2, ...}.
  mass.fill_diagonal(mat::DIAG, (2 + param.c0) * param.q * param.q);
  mass.set(mat::DIAG, 0, (1 + param.c0) * param.q * param.q);

  // Fill the upper diagonal with {-q^2, -q^2, ...}.
  mass.fill_diagonal(mat::UPPER, -1.0 * param.q * param.q);

  // Fill the lower diagonal with {-q^2, -q^2, ...}.
  mass.fill_diagonal(mat::LOWER, -1.0 * param.q * param.q);

  return mass;
}

snspd::math::TridiagonalMatrix<double> snspd::Model::generate_alpha_matrix(const snspd::Parameters &param) {
  using mat = math::TridiagonalMatrix<double>;

  mat alpha(param.size);

  double forward_res{get_resistance(param, 0)};
  double backward_res;

  // Update first row
  alpha.set(mat::DIAG, 0, forward_res);
  alpha.set(mat::UPPER, 0, -forward_res);

  // Update row i
  for (std::size_t i = 1; i < param.size - 1; ++i) {
    backward_res = forward_res;
    forward_res = get_resistance(param, i);

    alpha.set(mat::DIAG, i, backward_res + forward_res);
    alpha.set(mat::UPPER, i, -forward_res);
    alpha.set(mat::LOWER, i - 1, -backward_res);
  }

  // Update last row
  backward_res = forward_res;
  forward_res = get_resistance(param, param.size - 1);

  alpha.set(mat::DIAG, param.size - 1, forward_res + backward_res);
  alpha.set(mat::LOWER, param.size - 2, -backward_res);

  return alpha;
}

double snspd::Model::get_resistance(const snspd::Parameters &param, std::size_t site) {

  // Return the normal resistance when the voltage is larger than vg
  if (std::abs(get_voltage(param, site)) >= param.vg) {
    return 1.0;
  }

  return param.rqp.at(site);
}

double snspd::Model::get_voltage(const snspd::Parameters &param, std::size_t site) {

  // Last site has voltage equal to itself
  if (site == param.size - 1) {
    return param.v.at(site);
  }

  return param.v.at(site) - param.v.at(site + 1);
}

std::vector<double> snspd::Model::get_force_damping(const snspd::Parameters &param,
                                            const snspd::math::TridiagonalMatrix<double> &alpha) {

  // The resulting force
  std::vector<double> force(param.size);

  // Damping
  std::vector<double> alpha_y = alpha * param.v;

  // TODO fix force

  return std::vector<double>();
}
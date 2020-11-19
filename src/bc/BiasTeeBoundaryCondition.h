#pragma once

#include <random>
#include "BoundaryCondition.h"

namespace snspd::bc {
  class BiasTeeBoundaryCondition : public BoundaryCondition {

    bool m_is_init{false};

    double
      m_old_t{},
      m_old_vb{},
      m_old_v0{},
      m_ib_init{},
      m_ir_init{},
      m_v0_init{},
      m_ib_int{0.0},
      m_ir_int{0.0},
      m_rt_random_int{0.0},
      m_rs_random_int{0.0};

    std::random_device m_rnd_dev;
    std::mt19937 m_rnd_gen;
    std::normal_distribution<double> m_rnd_dist;

  public:

    explicit BiasTeeBoundaryCondition(Parameters &param):
        BoundaryCondition(param),
        m_rnd_gen(m_rnd_dev()),
        m_rnd_dist(0.0, 1.0) {

    }

    void run() override {

      if (!m_is_init) {
        m_is_init = true;
        m_ib_init = m_param.ib;
        m_ir_init = m_param.ir;
        m_v0_init = m_param.v.at(0);
      }

      double t = m_param.dt * static_cast<double>(m_param.time_step);

      // Update the rt random integral
      m_rt_random_int += m_param.rt * std::sqrt(2 * m_param.nl * m_param.dt / m_param.rt) * m_rnd_dist(m_rnd_gen)
          * std::exp(m_param.rt * t / m_param.lb);

      // Update integral for ib
      m_ib_int += 0.5 * m_param.dt * ((m_old_vb - m_old_v0) * std::exp(m_param.rt * m_old_t / m_param.lb)
          + (m_param.vb - m_param.v.at(0)) * std::exp(m_param.rt * t / m_param.lb));

      // Compute ib
      m_param.ib = (m_ib_init + (m_ib_int - m_rt_random_int)  / m_param.lb)
          * std::exp(- m_param.rt * t / m_param.lb);

      // Update the rs random integral
      m_rs_random_int += m_param.rs * std::sqrt(2 * m_param.nl * m_param.dt / m_param.rs) * m_rnd_dist(m_rnd_gen)
                         * std::exp(t / (m_param.cb * m_param.rs));

      // Update integral for ir
      m_ir_int += 0.5 * m_param.dt * (m_old_v0 * std::exp(m_old_t / (m_param.rs * m_param.cb))
                                      + m_param.v.at(0) * std::exp(t / (m_param.rs * m_param.cb)));

      // Compute ir
      m_param.ir = m_param.v.at(0) / m_param.rs + (m_ir_init - m_v0_init / m_param.rs
          - (m_ir_int + m_rs_random_int) / (m_param.rs * m_param.rs * m_param.cb))
              * std::exp(-t / (m_param.cb * m_param.rs));

      m_param.i = m_param.ib - m_param.ir;

      // Update old params
      m_old_t = t;
      m_old_vb = m_param.vb;
      m_old_v0 = m_param.v.at(0);
    }
  };
}

#include "Exporter.h"

void snspd::io::Exporter::save(const snspd::Parameters &param) {
  auto average = static_cast<double>(param.average);
  m_v.at(param.step) += param.v.at(0) / average;
  m_i.at(param.step) += param.i / average;
  m_ib.at(param.step) += param.ib / average;
  m_ir.at(param.step) += param.ir / average;
  m_t.at(param.step) += static_cast<double>(param.time_step) * param.dt / average;
}

void snspd::io::Exporter::flush() {
  m_file.writeDataset(m_v, "voltage");
  m_file.writeDataset(m_i, "current");
  m_file.writeDataset(m_ib, "bias_current");
  m_file.writeDataset(m_ir, "readout_current");
  m_file.writeDataset(m_t, "time");
  m_file.writeDataset(m_config.get_json_config().dump(), "json_config");

  m_storage.flush_phase_slips(m_file);
}

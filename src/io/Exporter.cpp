#include "Exporter.h"

void snspd::io::Exporter::save(const snspd::Parameters &param) {
  auto average = static_cast<double>(param.average);
  m_v.at(param.step) += param.v.at(0) / average;
  m_ib.at(param.step) += param.i / average;
  m_t.at(param.step) += static_cast<double>(param.time_step) * param.dt / average;
}

void snspd::io::Exporter::flush() {
  m_file.writeDataset(m_v, "voltage");
  m_file.writeDataset(m_ib, "bias_current");
  m_file.writeDataset(m_t, "time");
  m_file.writeDataset(m_config.get_json_config().dump(), "json_config");

  h5pp::hid::h5t H5_PHASE_SLIP = H5Tcreate(H5T_COMPOUND, sizeof(event::PhaseSlipEvent));
  H5Tinsert(H5_PHASE_SLIP, "t", HOFFSET(event::PhaseSlipEvent, time_step), H5T_NATIVE_INT);
  H5Tinsert(H5_PHASE_SLIP, "x", HOFFSET(event::PhaseSlipEvent, location), H5T_NATIVE_INT);
  H5Tinsert(H5_PHASE_SLIP, "branch", HOFFSET(event::PhaseSlipEvent, branch), H5T_NATIVE_INT);

  // Store events
  m_file.writeDataset(m_storage.get_phase_slips(), "phase_slips", H5_PHASE_SLIP);
}

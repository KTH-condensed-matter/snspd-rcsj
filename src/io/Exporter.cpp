#include "Exporter.h"

void snspd::io::Exporter::save(const snspd::Parameters &param) {
  m_v.at(param.step) = param.v.at(0);
}

void snspd::io::Exporter::flush() {
  m_file.writeDataset(m_v, "voltage");
}

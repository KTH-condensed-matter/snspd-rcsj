#pragma once

#include <vector>
#include <climits>
#include "PhaseSlipEvent.h"

namespace snspd::event {
  class EventStorage {
    std::vector<PhaseSlipEvent> m_phase_slips{};

  public:
    void save_phase_slip(unsigned int time_step, std::size_t location, long int branch) {
      m_phase_slips.push_back(PhaseSlipEvent{
        time_step,
        location,
        branch
      });
    }

    [[nodiscard]] const std::vector<PhaseSlipEvent>& get_phase_slips() const {
      return m_phase_slips;
    }
  };
}

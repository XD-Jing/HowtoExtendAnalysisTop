#include "HowtoExtendAnalysisTop/EvenEventNumberSelector.h"

namespace top{
    //If the event number divided by two has no remainder then return true.
  bool EvenEventNumberSelector::apply(const top::Event& event) const {
      return event.m_info->eventNumber() % 2 == 0;
  }

  //For the cutflow and terminal output
  std::string EvenEventNumberSelector::name() const {
      return "EVEN";
  }
}

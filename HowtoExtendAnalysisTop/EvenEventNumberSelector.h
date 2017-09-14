#ifndef HOWTOEXTENDANALYSISTOP_EVENEVENTNUMBERSELECTOR_H
#define HOWTOEXTENDANALYSISTOP_EVENEVENTNUMBERSELECTOR_H

#include "TopEventSelectionTools/EventSelectorBase.h"
#include "TopEvent/Event.h"

namespace top{
  
  /**
  * This is a tool that selects only even numbered events.  But you could do something even cooler.
  */
  class EvenEventNumberSelector : public top::EventSelectorBase {
    public:
      //This function sees every event.  If you return true then the event passes this "cut"
      bool apply(const top::Event& event) const override;

      //For humans, something short and catchy
      std::string name() const override;
  };  
  
}

#endif

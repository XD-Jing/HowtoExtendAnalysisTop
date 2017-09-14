#ifndef HOWTOEXTENDANALYSISTOP_CUSTOMEVENTSAVER_H
#define HOWTOEXTENDANALYSISTOP_CUSTOMEVENTSAVER_H

#include "TopAnalysis/EventSaverFlatNtuple.h"

/**
 * This class shows you how to extend the flat ntuple to include your own variables
 * 
 * It inherits from top::EventSaverFlatNtuple, which will be doing all the hard work 
 * 
 */

namespace top{
  class CustomEventSaver : public top::EventSaverFlatNtuple {
    public:
      ///-- Default constrcutor with no arguments - needed for ROOT --///
      CustomEventSaver();
      ///-- Destructor does nothing --///
      virtual ~CustomEventSaver(){}
      
      ///-- initialize function for top::EventSaverFlatNtuple --///
      ///-- We will be setting up out custom variables here --///
      virtual void initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches) override;
      
      ///-- Keep the asg::AsgTool happy --///
      virtual StatusCode initialize(){return StatusCode::SUCCESS;}      
      
      ///-- saveEvent function for top::EventSaverFlatNtuple --///
      ///-- We will be setting our custom variables on a per-event basis --///
      virtual void saveEvent(const top::Event& event) override;
      
    private:
      ///-- Some additional custom variables for the output --///
      float m_randomNumber;
      float m_someOtherVariable;
      
      ///-- Tell RootCore to build a dictionary (we need this) --///
      ClassDef(top::CustomEventSaver, 0);
  };
}

#endif

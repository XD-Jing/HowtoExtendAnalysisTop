#include "HowtoExtendAnalysisTop/CustomEventSaver.h"
#include "TopEvent/Event.h"
#include "TopEventSelectionTools/TreeManager.h"

#include <TRandom3.h>


namespace top{
  ///-- Constrcutor --///
  CustomEventSaver::CustomEventSaver() :
    m_randomNumber(0.),
    m_someOtherVariable(0.)
  {
  }
  
  ///-- initialize - done once at the start of a job before the loop over events --///
  void CustomEventSaver::initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches)
  {
    ///-- Let the base class do all the hard work --///
    ///-- It will setup TTrees for each systematic with a standard set of variables --///
    top::EventSaverFlatNtuple::initialize(config, file, extraBranches);
    
    ///-- Loop over the systematic TTrees and add the custom variables --///
    for (auto systematicTree : treeManagers()) {
      systematicTree->makeOutputVariable(m_randomNumber, "randomNumber");
      systematicTree->makeOutputVariable(m_someOtherVariable,"someOtherVariable");
    }
  }
  
  ///-- saveEvent - run for every systematic and every event --///
  void CustomEventSaver::saveEvent(const top::Event& event) 
  {
    ///-- set our variables to zero --///
    m_randomNumber = 0.;
    m_someOtherVariable = 0.;
    
    ///-- Fill them - you should probably do something more complicated --///
    TRandom3 random( event.m_info->eventNumber() );
    m_randomNumber = random.Rndm();    
    m_someOtherVariable = 42;
    
    ///-- Let the base class do all the hard work --///
    top::EventSaverFlatNtuple::saveEvent(event);
  }
  
}

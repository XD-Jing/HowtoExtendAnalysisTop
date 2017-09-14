#include "HowtoExtendAnalysisTop/CustomMuon.h"

#include "TopEvent/EventTools.h"

namespace top{
  
  CustomMuon::CustomMuon(const double ptcut, IsolationBase* isolation) :
    m_ptcut(ptcut),
    m_muonSelectionTool("CP::MuonSelectionTool"),
    m_muonSelectionToolLoose("CP::MuonSelectionToolLoose"),
    m_isolation(isolation)
  {
    top::check( m_muonSelectionTool.retrieve() , "Failed to retrieve muonSelectionTool" );
    top::check( m_muonSelectionToolLoose.retrieve() , "Failed to retrieve muonSelectionToolLoose" );
  }
  
  bool CustomMuon::passSelection(const xAOD::Muon& mu) const 
  {
    if (mu.pt() < m_ptcut)
        return false; 
    
    ///-- https://twiki.cern.ch/twiki/bin/view/AtlasProtected/MCPAnalysisGuidelinesMC15 --///
    if (!m_muonSelectionTool->accept(mu))
        return false;
    
    ///-- require positive eta muons for this demonstration --///
    if (mu.eta() < 0.)
        return false;
    
    //isolation, if m_isolation != nullptr
    if (m_isolation && !m_isolation->passSelection(mu))
        return false;

    return true;
  }

  bool CustomMuon::passSelectionLoose(const xAOD::Muon& mu) const
  {
    if (mu.pt() < m_ptcut)
        return false; 
    
    ///-- https://twiki.cern.ch/twiki/bin/view/AtlasProtected/MCPAnalysisGuidelinesMC15 --///
    if (!m_muonSelectionToolLoose->accept(mu))
        return false;
    
    //isolation, if m_isolation != nullptr
    if (m_isolation && !m_isolation->passSelectionLoose(mu))
        return false;    
    
    return true;
  }

  void CustomMuon::print(std::ostream& os) const {
      os << "CustomMuon\n"
        << "    * pT > " << m_ptcut << "\n"
        << "    * Everything else from muon tool - fill this in?\n";

      if (!m_isolation)
        os << "    * No isolation requirement\n";
      else
        m_isolation->print(os);
  }
}

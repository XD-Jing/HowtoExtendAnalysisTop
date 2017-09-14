#include "HowtoExtendAnalysisTop/CustomJet.h"
#include <cmath>

namespace top{
  CustomJet::CustomJet(const double ptMin,const double ptMax,const double etamax, const double jvtmin) :
    m_ptMin(ptMin),
    m_ptMax(ptMax),
    m_etamax(etamax),
    m_applyJVTCut(true),
    m_jvtmin(jvtmin) 
  {
  }  
  
  bool CustomJet::passSelection(const xAOD::Jet& jet)
  {
    ///-- Jet is not below lower pT cut --///
    if (jet.pt() < m_ptMin)
        return false;
    
    ///-- Jet is not above upper pT cut --///
    ///-- This is a demonstration of how to extend AnalysisTop --///
    if (jet.pt() > m_ptMax)
        return false;   
    
    
    if (std::fabs(jet.eta()) > m_etamax)
        return false;
    
    ///-- TopSystematicObjectMaker/JetObjectCollectionMaker re-calculates the JVT for each jet --///
    ///-- This takes into account calibration and uncertainties --///
    ///-- Out-of-the-box JVT is only for uncalibrated jets, and we're not using them --///
    
    if (m_applyJVTCut) {
      float jvt(0.);
      if (jet.isAvailable<float>("AnalysisTop_JVT")) {
        jvt = jet.auxdataConst<float>("AnalysisTop_JVT");
      }
      
      if ((jet.pt() < 50e3) && std::fabs(jet.eta()) < 2.4 && jvt < m_jvtmin)                                                                                
          return false;                                                                                                                                                  
    }
    
    jet.auxdecor<char>("good")          = 1;
    jet.auxdecor<char>("closeToLepton") = 0;
    
    return true;
  }
  
  void CustomJet::print(std::ostream& os) const {
    os << "CustomJet\n"
       << "    * pT > " << m_ptMin << " && pT < "<<m_ptMax<< "\n"
       << "    * |eta| < " << m_etamax << "\n";
    
    if (m_jvtmin > 0.)
      os << "    * JVT > " << m_jvtmin << " for pT < 50 GeV and |eta| < 2.4\n";
    else
      os << "    * No JVT cut applied\n";
  }  
}

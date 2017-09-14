#ifndef HOWTOEXTENDANALYSISTOP_CUSTOMJET_H
#define HOWTOEXTENDANALYSISTOP_CUSTOMJET_H

#include "TopObjectSelectionTools/JetSelectionBase.h"

namespace top{
  /**
   * @brief Select jet with a pt min and a pt max
   *        No physics reason, demonstration of a plug-in
   */
  class CustomJet : public JetSelectionBase {
    public:
      CustomJet(const double ptMin,const double ptMax,const double etamax, const double jvtmin);
      virtual ~CustomJet(){}
      
      virtual bool passSelection(const xAOD::Jet& jet) ;

      ///Print the cuts to the ostream.
      virtual void print(std::ostream& os) const ;

    protected: 
      ///The lower pT cut threshold to apply to the object.
      double m_ptMin;
      ///The upper pT cut threshold to apply to the object.
      double m_ptMax;      

      ///The upper eta cut.
      double m_etamax;

      ///The minimum JVT cut for jets with pT < 50 GeV and |eta| < 2.4.
      bool m_applyJVTCut;
      double m_jvtmin;      
  };
}
#endif

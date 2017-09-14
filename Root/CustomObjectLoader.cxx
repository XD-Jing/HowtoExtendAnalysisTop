
#include "TopEvent/EventTools.h"
#include "TopConfiguration/TopConfig.h"

#include "TopObjectSelectionTools/TopObjectSelection.h"
#include "TopObjectSelectionTools/ElectronLikelihoodMC15.h"
#include "TopObjectSelectionTools/ElectronCutBasedMC15.h"
#include "TopObjectSelectionTools/IsolationTools.h"
#include "TopObjectSelectionTools/MuonMC15.h"
#include "TopObjectSelectionTools/TauMC15.h"
#include "TopObjectSelectionTools/JetMC15.h"
#include "TopObjectSelectionTools/OverlapRemovalASG.h"

///-- The custom object selections we have defined in this package --///
#include "HowtoExtendAnalysisTop/CustomObjectLoader.h"
#include "HowtoExtendAnalysisTop/CustomMuon.h"
#include "HowtoExtendAnalysisTop/CustomJet.h"

///-- We largely follow the standard, but replacing muon and jet selections with --///
///-- Those we have defined ourselves --///

namespace top {

  top::TopObjectSelection* CustomObjectLoader::init(std::shared_ptr<top::TopConfig> topConfig) 
  {
    top::TopObjectSelection* objectSelection = new top::TopObjectSelection(topConfig->objectSelectionName());
    top::check(objectSelection->setProperty( "config" , topConfig ) , "Failed to setProperty for top::TopObjectSelection" );
    top::check(objectSelection->initialize() , "Failed to initialize top::TopObjectSelection" );
    
    ///-- Electrons --///
    if (topConfig->useElectrons()) {
      if (topConfig->electronID().find("LH") == std::string::npos && topConfig->electronIDLoose().find("LH") == std::string::npos) {
          //both the tight and loose user settings do not contain LH -> cut based
        objectSelection->electronSelection(new top::ElectronCutBasedMC15(topConfig->electronPtcut(), 
									 topConfig->electronVetoLArCrack(), 
									 topConfig->electronID(), 
									 topConfig->electronIDLoose(), 
									 new top::StandardIsolation()));
        
      } else if (topConfig->electronID().find("LH") != std::string::npos && topConfig->electronIDLoose().find("LH") != std::string::npos) {
          //user wants likelihood electrons
	objectSelection->electronSelection(new top::ElectronLikelihoodMC15(topConfig->isPrimaryxAOD(),
									   topConfig->electronPtcut(), 
									   topConfig->electronVetoLArCrack(), 
									   topConfig->electronID(), 
									   topConfig->electronIDLoose(), 
									   new top::StandardIsolation()));
          
      } else {
          std::cout << "\nHo hum\n";
          std::cout << "Not sure it makes sense to use a mix of LH and cut-based electrons for the tight/loose definitions\n";
          std::cout << "Tight electron definition is " << topConfig->electronID() << "\n";
          std::cout << "Loose electron definition is " << topConfig->electronIDLoose() << "\n";
          std::cout << "If it does make sense, feel free to fix this\n";
          exit(1);
      }
    }
    
    ///-- Muons --///
    if (topConfig->useMuons()) {
      objectSelection -> muonSelection(new top::CustomMuon(topConfig->muonPtcut(), new top::StandardIsolation())); 
    }
    
    ///-- Taus --///
    if (topConfig->useTaus()) {
      objectSelection->tauSelection(new top::TauMC15());
    }

// jing: comment since topConfig has no jetEtacut()
//    ///-- Jets --///
//    if (topConfig->useJets()) {
//      double ptMax(100000.);
//      objectSelection -> jetSelection(new top::CustomJet(topConfig->jetPtcut(), ptMax ,topConfig->jetEtacut(), topConfig->jetJVTcut())); 
//    }
//    
//    ///-- Large R Jets --///
//    if (topConfig->useLargeRJets()) {
//      objectSelection -> largeJetSelection(new top::JetMC15(topConfig->jetPtcut(), topConfig->jetEtacut())); 
//    }

    ///-- Overlap removal --///
    objectSelection->overlapRemovalPostSelection(new top::OverlapRemovalASG());

    return objectSelection;
  }

}

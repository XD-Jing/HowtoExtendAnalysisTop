#include "HowtoExtendAnalysisTop/CustomEventSaver.h"
#include "TopEvent/Event.h"
#include "TopEventSelectionTools/TreeManager.h"
#include "TopConfiguration/TopConfig.h"

#include <TLorentzVector.h>
#include <TRandom3.h>


namespace top{
    ///-- Constrcutor --///
    CustomEventSaver::CustomEventSaver()// :
        //m_randomNumber(0.),
        //m_someOtherVariable(0.),
        //m_diel_mass(0.),
        //m_diel_eta(0.),
        //m_diel_pt(0.),
        //m_diel_phi(0.),
        //m_diel_energy(0.),
        //m_dimu_mass( 0.),
        //m_dimu_eta(0.),
        //m_dimu_pt(0.),
        //m_dimu_phi(0.),
        //m_dimu_energy(0.)
    {
    }

    ///-- initialize - done once at the start of a job before the loop over events --///
    void CustomEventSaver::initialize(std::shared_ptr<top::TopConfig> config, TFile* file, const std::vector<std::string>& extraBranches)
    {
        ///-- Let the base class do all the hard work --///
        ///-- It will setup TTrees for each systematic with a standard set of variables --///
        top::EventSaverFlatNtuple::initialize(config, file, extraBranches);

        customConfig = config;

        ///-- Loop over the systematic TTrees and add the custom variables --///
        for (auto systematicTree : treeManagers()) {
            //systematicTree->makeOutputVariable(m_randomNumber, "randomNumber");
            //systematicTree->makeOutputVariable(m_someOtherVariable,"someOtherVariable");
            if (customConfig->useElectrons()) {
                systematicTree->makeOutputVariable(m_diel_mass, "diel_mass");
                systematicTree->makeOutputVariable(m_diel_eta, "diel_eta");
                systematicTree->makeOutputVariable(m_diel_pt, "diel_pt");
                systematicTree->makeOutputVariable(m_diel_phi, "diel_phi");
                systematicTree->makeOutputVariable(m_diel_energy, "diel_energy");
                systematicTree->makeOutputVariable(m_el_mass, "el_mass");
                systematicTree->makeOutputVariable(m_el_pz, "el_pz");
            }
            if (customConfig->useMuons()) {
                systematicTree->makeOutputVariable(m_dimu_mass, "dimu_mass");
                systematicTree->makeOutputVariable(m_dimu_eta, "dimu_eta");
                systematicTree->makeOutputVariable(m_dimu_pt, "dimu_pt");
                systematicTree->makeOutputVariable(m_dimu_phi, "dimu_phi");
                systematicTree->makeOutputVariable(m_dimu_energy, "dimu_energy");
                systematicTree->makeOutputVariable(m_mu_mass, "mu_mass");
                systematicTree->makeOutputVariable(m_mu_pz, "mu_pz");
            }
        }
    }

    ///-- saveEvent - run for every systematic and every event --///
    void CustomEventSaver::saveEvent(const top::Event& event) 
    {
        ///-- set our variables to zero --///
        //m_randomNumber = 0.;
        //m_someOtherVariable = 0.;
        m_diel_mass = 0.;
        m_diel_eta = 0.;
        m_diel_pt = 0.;
        m_diel_phi = 0.;
        m_diel_energy = 0.;
        m_dimu_mass = 0.;
        m_dimu_eta = 0.;
        m_dimu_pt = 0.;
        m_dimu_phi = 0.;
        m_dimu_energy = 0.;

        ///-- Fill them - you should probably do something more complicated --///
        //TRandom3 random( event.m_info->eventNumber() );
        //m_randomNumber = random.Rndm();
        //m_someOtherVariable = 42;

        TLorentzVector tmp;
        unsigned int i(0);
        TLorentzVector v1(0.,0.,0.,0.);
        if (customConfig->useElectrons()){
            unsigned int n_electrons = event.m_electrons.size();
            m_el_mass.resize(n_electrons);
            m_el_pz.resize(n_electrons);
            i=0;
            for (const auto* const elPtr : event.m_electrons){
                m_el_mass[i] = elPtr->m();
                tmp.SetPtEtaPhiE ( elPtr->pt(), elPtr->eta(), elPtr->phi(), elPtr->e());
                m_el_pz[i] = tmp.Pz();
                if (n_electrons == 2) v1 = v1 + tmp;
                ++i;
            }

            m_diel_mass = v1.M();
            m_diel_eta = v1.Eta();
            m_diel_phi = v1.Phi();
            m_diel_pt = v1.Pt();
            m_diel_energy = v1.Energy();
        }

        TLorentzVector v2(0.,0.,0.,0.);
        if (customConfig->useMuons()){
            unsigned int n_muons = event.m_muons.size();
            m_mu_mass.resize(n_muons);
            m_mu_pz.resize(n_muons);
            i=0;
            for (const auto* const muPtr : event.m_muons){
                m_mu_mass[i] = muPtr->m();
                tmp.SetPtEtaPhiE ( muPtr->pt(), muPtr->eta(), muPtr->phi(), muPtr->e());
                m_mu_pz[i] = tmp.Pz();
                if (n_muons == 2) v2 = v2 + tmp;
                ++i;
            }
            m_dimu_mass = v2.M();
            m_dimu_eta = v2.Eta();
            m_dimu_phi = v2.Phi();
            m_dimu_pt = v2.Pt();
            m_dimu_energy = v2.Energy();

        }
        ///-- Let the base class do all the hard work --///
        top::EventSaverFlatNtuple::saveEvent(event);
    }
}

# include <iostream>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TTree.h>

# include "Common.h"
# include "CustomInfo_data.h"
# include "CustomInfo_common.h"


namespace CustomInfo_data
{
    Info::Info( \
        const char *fileName, \
        const char *treeName_reco, \
        std::vector <const char*> v_object_reco, \
        const char *mode)
    {
        if(!strcmp(mode, "read"))
        {
            file = TFile::Open(fileName, "READ");
            
            T_reco = (TTree*) file->Get(treeName_reco);
        }
        
        else if(!strcmp(mode, "write"))
        {
            file = TFile::Open(fileName, "RECREATE");
            
            T_reco = new TTree(treeName_reco, treeName_reco);
        }
        
        // El
        v_el_E_reco = 0; v_el_px_reco = 0; v_el_py_reco = 0; v_el_pz_reco = 0;
        
        v_el_dxy_reco = 0; v_el_dz_reco = 0;
        v_el_SIP3D_reco = 0;
        
        v_el_missingInnerHits_reco = 0;
        v_el_passConversionVeto_reco = 0;
        
        v_el_mvaEleIDSpring16GeneralPurposeV1wp80_reco = 0;
        v_el_mvaEleIDSpring16GeneralPurposeV1wp90_reco = 0;
        
        v_el_mvaEleIDFall17noIsoV2wp90_reco = 0;
        v_el_mvaEleIDFall17noIsoV2wp80_reco = 0;
        
        v_el_mvaEleIDFall17isoV2wp90_reco = 0;
        v_el_mvaEleIDFall17isoV2wp80_reco = 0;
        
        v_el_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR03_reco = 0;
        v_el_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR03_reco = 0;
        v_el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco = 0;
        v_el_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco = 0;
        
        // Mu
        v_mu_E_reco = 0; v_mu_px_reco = 0; v_mu_py_reco = 0; v_mu_pz_reco = 0;
        
        v_mu_dxy_reco = 0; v_mu_dz_reco = 0;
        v_mu_SIP3D_reco = 0;
        
        v_mu_isGlobalMuon_reco = 0;
        v_mu_isTrackerMuon_reco = 0;
        
        v_mu_isLooseMuon_reco = 0;
        v_mu_isMediumMuon_reco = 0;
        v_mu_isTightMuon_reco = 0;
        
        v_mu_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR04_reco = 0;
        v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco = 0;
        v_mu_byTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco = 0;
        v_mu_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco = 0;
        
        // Tau
        v_tau_E_reco = 0; v_tau_px_reco = 0; v_tau_py_reco = 0; v_tau_pz_reco = 0;
        
        v_tau_dxy_reco = 0; v_tau_dz_reco = 0;
        
        v_tau_byDecayModeFinding_reco = 0;
        v_tau_byDecayModeFindingNewDMs_reco = 0;
        v_tau_isTriggerMatched_reco = 0;
        
        // 2016
        v_tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_reco = 0;
        v_tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_reco = 0;
        v_tau_byTightCombinedIsolationDeltaBetaCorr3Hits_reco = 0;
        
        v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco = 0;
        v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco = 0;
        v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco = 0;
        
        v_tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco = 0;
        v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco = 0;
        v_tau_byMediumIsolationMVArun2v1DBoldDMwLT_reco = 0;
        v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco = 0;
        v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco = 0;
        
        v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco = 0;
        v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco = 0;
        v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco = 0;
        v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco = 0;
        v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco = 0;
        
        v_tau_againstElectronVLooseMVA6_reco = 0;
        v_tau_againstElectronLooseMVA6_reco = 0;
        v_tau_againstElectronMediumMVA6_reco = 0;
        v_tau_againstElectronTightMVA6_reco = 0;
        v_tau_againstElectronVTightMVA6_reco = 0;
        
        v_tau_againstMuonLoose3_reco = 0;
        v_tau_againstMuonTight3_reco = 0;
        
        // 2017
        v_tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco = 0;
        v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco = 0;
        v_tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_reco = 0;
        v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco = 0;
        v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco = 0;
        
        v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco = 0;
        v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco = 0;
        v_tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco = 0;
        v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco = 0;
        v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco = 0;
        
        //Deep Tau Id
        v_tau_byVVVLooseDeepTau2017v2p1VSjet_reco = 0;
        v_tau_byVVLooseDeepTau2017v2p1VSjet_reco = 0;
        v_tau_byVLooseDeepTau2017v2p1VSjet_reco = 0;
        v_tau_byLooseDeepTau2017v2p1VSjet_reco = 0;
        v_tau_byMediumDeepTau2017v2p1VSjet_reco = 0;
        v_tau_byTightDeepTau2017v2p1VSjet_reco = 0;
        v_tau_byVTightDeepTau2017v2p1VSjet_reco = 0;
        v_tau_byVVTightDeepTau2017v2p1VSjet_reco = 0;
        
        v_tau_byVVVLooseDeepTau2017v2p1VSe_reco = 0;
        v_tau_byVVLooseDeepTau2017v2p1VSe_reco = 0;
        v_tau_byVLooseDeepTau2017v2p1VSe_reco = 0;
        v_tau_byLooseDeepTau2017v2p1VSe_reco = 0;
        v_tau_byMediumDeepTau2017v2p1VSe_reco = 0;
        v_tau_byTightDeepTau2017v2p1VSe_reco = 0;
        v_tau_byVTightDeepTau2017v2p1VSe_reco = 0;
        v_tau_byVVTightDeepTau2017v2p1VSe_reco = 0;
        
        v_tau_byVLooseDeepTau2017v2p1VSmu_reco = 0;
        v_tau_byLooseDeepTau2017v2p1VSmu_reco = 0;
        v_tau_byMediumDeepTau2017v2p1VSmu_reco = 0;
        v_tau_byTightDeepTau2017v2p1VSmu_reco = 0;
        
        v_tau_decayMode_reco = 0;
        
        v_tau_chHad1_E_reco = 0;
        v_tau_chHad1_px_reco = 0;
        v_tau_chHad1_py_reco = 0;
        v_tau_chHad1_pz_reco = 0;
        
        // Jet
        v_jet_E_reco = 0; v_jet_px_reco = 0; v_jet_py_reco = 0; v_jet_pz_reco = 0;
        
        v_jet_partonFlavour_reco = 0;
        v_jet_hadronFlavour_reco = 0;
        
        v_jet_JECcorr_reco = 0;
        v_jet_JECcorrUp_reco = 0;
        v_jet_JECcorrDown_reco = 0;
        
        v_jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco = 0;
        v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco = 0;
        v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco = 0;
        v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco = 0;
        
        v_jet_pfDeepCSVJetTags_reco = 0;
        v_jet_byLoosePfDeepCSVJetTags_reco = 0;
        v_jet_byMediumPfDeepCSVJetTags_reco = 0;
        v_jet_byTightPfDeepCSVJetTags_reco = 0;
        
        v_jet_pfDeepFlavourJetTags_reco = 0;
        v_jet_byLoosePfDeepFlavourJetTags_reco = 0;
        v_jet_byMediumPfDeepFlavourJetTags_reco = 0;
        v_jet_byTightPfDeepFlavourJetTags_reco = 0;
        
        
        // Set object options
        bool_vertex_reco = false;
        
        bool_el_reco = false;
        bool_mu_reco = false;
        bool_tau_reco = false;
        
        bool_jet_reco = false;
        
        bool_MET_reco = false;
        
        bool_trigger = false;
        
        for(int iObject = 0; iObject < v_object_reco.size(); iObject++)
        {
            if(!strcmp(v_object_reco[iObject], "vertex"))
            {
                bool_vertex_reco = true;
            }
            
            if(!strcmp(v_object_reco[iObject], "el"))
            {
                bool_el_reco = true;
            }
            
            else if(!strcmp(v_object_reco[iObject], "mu"))
            {
                bool_mu_reco = true;
            }
            
            else if(!strcmp(v_object_reco[iObject], "tau"))
            {
                bool_tau_reco = true;
            }
            
            else if(!strcmp(v_object_reco[iObject], "jet"))
            {
                bool_jet_reco = true;
            }
            
            else if(!strcmp(v_object_reco[iObject], "MET"))
            {
                bool_MET_reco = true;
            }
            
            else if(!strcmp(v_object_reco[iObject], "trigger"))
            {
                bool_trigger = true;
            }
        }
        
        // Link branches
        linkBranch_reco(mode);
        
        // Create object collections
        // El
        v_el_reco.push_back(v_el_E_reco);
        v_el_reco.push_back(v_el_px_reco);
        v_el_reco.push_back(v_el_py_reco);
        v_el_reco.push_back(v_el_pz_reco);
        
        v_el_reco.push_back(v_el_dxy_reco);
        v_el_reco.push_back(v_el_dz_reco);
        v_el_reco.push_back(v_el_SIP3D_reco);
        
        v_el_reco.push_back(v_el_missingInnerHits_reco);
        v_el_reco.push_back(v_el_passConversionVeto_reco);
        
        v_el_reco.push_back(v_el_mvaEleIDSpring16GeneralPurposeV1wp80_reco);
        v_el_reco.push_back(v_el_mvaEleIDSpring16GeneralPurposeV1wp90_reco);
        
        v_el_reco.push_back(v_el_mvaEleIDFall17noIsoV2wp90_reco);
        v_el_reco.push_back(v_el_mvaEleIDFall17noIsoV2wp80_reco);
        
        v_el_reco.push_back(v_el_mvaEleIDFall17isoV2wp90_reco);
        v_el_reco.push_back(v_el_mvaEleIDFall17isoV2wp80_reco);
        
        v_el_reco.push_back(v_el_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
        v_el_reco.push_back(v_el_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
        v_el_reco.push_back(v_el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
        v_el_reco.push_back(v_el_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
        
        // Mu
        v_mu_reco.push_back(v_mu_E_reco);
        v_mu_reco.push_back(v_mu_px_reco);
        v_mu_reco.push_back(v_mu_py_reco);
        v_mu_reco.push_back(v_mu_pz_reco);
        
        v_mu_reco.push_back(v_mu_dxy_reco);
        v_mu_reco.push_back(v_mu_dz_reco);
        v_mu_reco.push_back(v_mu_SIP3D_reco);
        
        v_mu_reco.push_back(v_mu_isGlobalMuon_reco);
        v_mu_reco.push_back(v_mu_isTrackerMuon_reco);
        
        v_mu_reco.push_back(v_mu_isLooseMuon_reco);
        v_mu_reco.push_back(v_mu_isMediumMuon_reco);
        v_mu_reco.push_back(v_mu_isTightMuon_reco);
        
        v_mu_reco.push_back(v_mu_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
        v_mu_reco.push_back(v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
        v_mu_reco.push_back(v_mu_byTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
        v_mu_reco.push_back(v_mu_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
        
        // Tau
        v_tau_reco.push_back(v_tau_E_reco);
        v_tau_reco.push_back(v_tau_px_reco);
        v_tau_reco.push_back(v_tau_py_reco);
        v_tau_reco.push_back(v_tau_pz_reco);
        
        v_tau_reco.push_back(v_tau_dxy_reco);
        v_tau_reco.push_back(v_tau_dz_reco);
        
        v_tau_reco.push_back(v_tau_byDecayModeFinding_reco);
        //v_tau_reco.push_back(v_tau_byDecayModeFindingNewDMs_reco);
        v_tau_reco.push_back(v_tau_isTriggerMatched_reco);
        
        // 2016
        v_tau_reco.push_back(v_tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_reco);
        v_tau_reco.push_back(v_tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_reco);
        v_tau_reco.push_back(v_tau_byTightCombinedIsolationDeltaBetaCorr3Hits_reco);
        
        v_tau_reco.push_back(v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
        v_tau_reco.push_back(v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
        v_tau_reco.push_back(v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
        
        v_tau_reco.push_back(v_tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byMediumIsolationMVArun2v1DBoldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco);
        
        v_tau_reco.push_back(v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco);
        v_tau_reco.push_back(v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco);
        
        v_tau_reco.push_back(v_tau_againstElectronVLooseMVA6_reco);
        v_tau_reco.push_back(v_tau_againstElectronLooseMVA6_reco);
        v_tau_reco.push_back(v_tau_againstElectronMediumMVA6_reco);
        v_tau_reco.push_back(v_tau_againstElectronTightMVA6_reco);
        v_tau_reco.push_back(v_tau_againstElectronVTightMVA6_reco);
        
        v_tau_reco.push_back(v_tau_againstMuonLoose3_reco);
        v_tau_reco.push_back(v_tau_againstMuonTight3_reco);
        
        // 2017
        v_tau_reco.push_back(v_tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco);
        v_tau_reco.push_back(v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco);
        v_tau_reco.push_back(v_tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_reco);
        v_tau_reco.push_back(v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco);
        v_tau_reco.push_back(v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco);
        
        v_tau_reco.push_back(v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
        v_tau_reco.push_back(v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
        v_tau_reco.push_back(v_tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
        v_tau_reco.push_back(v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
        v_tau_reco.push_back(v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
        
        //Deep Tau Id
        v_tau_reco.push_back(v_tau_byVVVLooseDeepTau2017v2p1VSjet_reco);
        v_tau_reco.push_back(v_tau_byVVLooseDeepTau2017v2p1VSjet_reco);
        v_tau_reco.push_back(v_tau_byVLooseDeepTau2017v2p1VSjet_reco);
        v_tau_reco.push_back(v_tau_byLooseDeepTau2017v2p1VSjet_reco);
        v_tau_reco.push_back(v_tau_byMediumDeepTau2017v2p1VSjet_reco);
        v_tau_reco.push_back(v_tau_byTightDeepTau2017v2p1VSjet_reco);
        v_tau_reco.push_back(v_tau_byVTightDeepTau2017v2p1VSjet_reco);
        v_tau_reco.push_back(v_tau_byVVTightDeepTau2017v2p1VSjet_reco);
        
        v_tau_reco.push_back(v_tau_byVVVLooseDeepTau2017v2p1VSe_reco);
        v_tau_reco.push_back(v_tau_byVVLooseDeepTau2017v2p1VSe_reco);
        v_tau_reco.push_back(v_tau_byVLooseDeepTau2017v2p1VSe_reco);
        v_tau_reco.push_back(v_tau_byLooseDeepTau2017v2p1VSe_reco);
        v_tau_reco.push_back(v_tau_byMediumDeepTau2017v2p1VSe_reco);
        v_tau_reco.push_back(v_tau_byTightDeepTau2017v2p1VSe_reco);
        v_tau_reco.push_back(v_tau_byVTightDeepTau2017v2p1VSe_reco);
        v_tau_reco.push_back(v_tau_byVVTightDeepTau2017v2p1VSe_reco);
        
        v_tau_reco.push_back(v_tau_byVLooseDeepTau2017v2p1VSmu_reco);
        v_tau_reco.push_back(v_tau_byLooseDeepTau2017v2p1VSmu_reco);
        v_tau_reco.push_back(v_tau_byMediumDeepTau2017v2p1VSmu_reco);
        v_tau_reco.push_back(v_tau_byTightDeepTau2017v2p1VSmu_reco);
        
        v_tau_reco.push_back(v_tau_decayMode_reco);
        
        v_tau_reco.push_back(v_tau_chHad1_E_reco);
        v_tau_reco.push_back(v_tau_chHad1_px_reco);
        v_tau_reco.push_back(v_tau_chHad1_py_reco);
        v_tau_reco.push_back(v_tau_chHad1_pz_reco);
        
        // Jet
        v_jet_reco.push_back(v_jet_E_reco);
        v_jet_reco.push_back(v_jet_px_reco);
        v_jet_reco.push_back(v_jet_py_reco);
        v_jet_reco.push_back(v_jet_pz_reco);
        
        v_jet_reco.push_back(v_jet_partonFlavour_reco);
        v_jet_reco.push_back(v_jet_hadronFlavour_reco);
        
        v_jet_reco.push_back(v_jet_JECcorr_reco);
        v_jet_reco.push_back(v_jet_JECcorrUp_reco);
        v_jet_reco.push_back(v_jet_JECcorrDown_reco);
        
        v_jet_reco.push_back(v_jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
        v_jet_reco.push_back(v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
        v_jet_reco.push_back(v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
        v_jet_reco.push_back(v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
        
        v_jet_reco.push_back(v_jet_pfDeepCSVJetTags_reco);
        v_jet_reco.push_back(v_jet_byLoosePfDeepCSVJetTags_reco);
        v_jet_reco.push_back(v_jet_byMediumPfDeepCSVJetTags_reco);
        v_jet_reco.push_back(v_jet_byTightPfDeepCSVJetTags_reco);
        
        v_jet_reco.push_back(v_jet_pfDeepFlavourJetTags_reco);
        v_jet_reco.push_back(v_jet_byLoosePfDeepFlavourJetTags_reco);
        v_jet_reco.push_back(v_jet_byMediumPfDeepFlavourJetTags_reco);
        v_jet_reco.push_back(v_jet_byTightPfDeepFlavourJetTags_reco);
        
        
        m_JECcorr = {
            {Common::SYST_CENTRAL, v_jet_JECcorr_reco},
            {Common::SYST_UP, v_jet_JECcorrUp_reco},
            {Common::SYST_DOWN, v_jet_JECcorrDown_reco}
        };
        
        // MET 2016
        m_MET_reco_2016["JEC"] = {
            {
                Common::SYST_CENTRAL,
                {
                    {"E", &MET_E_reco},
                    {"phi", &MET_phi_reco}
                }
            },
            
            {
                Common::SYST_UP,
                {
                    {"E", &MET_JetEnUp_E_reco},
                    {"phi", &MET_JetEnUp_phi_reco}
                }
            },
            
            {
                Common::SYST_DOWN,
                {
                    {"E", &MET_JetEnDown_E_reco},
                    {"phi", &MET_JetEnDown_phi_reco}
                }
            }
        };
        
        m_MET_reco_2016["JER"] = {
            {
                Common::SYST_CENTRAL,
                {
                    {"E", &MET_E_reco},
                    {"phi", &MET_phi_reco}
                }
            },
            
            {
                Common::SYST_UP,
                {
                    {"E", &MET_JetResUp_E_reco},
                    {"phi", &MET_JetResUp_phi_reco}
                }
            },
            
            {
                Common::SYST_DOWN,
                {
                    {"E", &MET_JetResDown_E_reco},
                    {"phi", &MET_JetResDown_phi_reco}
                }
            }
        };
        
        m_MET_reco_2016["unclusteredEnergy"] = { 
            {
                Common::SYST_CENTRAL,
                {
                    {"E", &MET_E_reco},
                    {"phi", &MET_phi_reco}
                }
            },
            
            {
                Common::SYST_UP,
                {
                    {"E", &MET_UnclusteredEnUp_E_reco},
                    {"phi", &MET_UnclusteredEnUp_phi_reco}
                }
            },
            
            {
                Common::SYST_DOWN,
                {
                    {"E", &MET_UnclusteredEnDown_E_reco},
                    {"phi", &MET_UnclusteredEnDown_phi_reco}
                }
            }
        };
        
        
        // MET 2017
        m_MET_reco_2017["JEC"] = {
            {
                Common::SYST_CENTRAL,
                {
                    {"E", &METFixEE2017_E_reco},
                    {"phi", &METFixEE2017_phi_reco}
                }
            },
            
            {
                Common::SYST_UP,
                {
                    {"E", &METFixEE2017_JetEnUp_E_reco},
                    {"phi", &METFixEE2017_JetEnUp_phi_reco}
                }
            },
            
            {
                Common::SYST_DOWN,
                {
                    {"E", &METFixEE2017_JetEnDown_E_reco},
                    {"phi", &METFixEE2017_JetEnDown_phi_reco}
                }
            },
        };
        
        m_MET_reco_2017["JER"] = {
            {
                Common::SYST_CENTRAL,
                {
                    {"E", &METFixEE2017_E_reco},
                    {"phi", &METFixEE2017_phi_reco}
                }
            },
            
            {
                Common::SYST_UP,
                {
                    {"E", &METFixEE2017_JetResUp_E_reco},
                    {"phi", &METFixEE2017_JetResUp_phi_reco}
                }
            },
            
            {
                Common::SYST_DOWN,
                {
                    {"E", &METFixEE2017_JetResDown_E_reco},
                    {"phi", &METFixEE2017_JetResDown_phi_reco}
                }
            },
        };
        
        m_MET_reco_2017["unclusteredEnergy"] = {
            {
                Common::SYST_CENTRAL,
                {
                    {"E", &METFixEE2017_E_reco},
                    {"phi", &METFixEE2017_phi_reco}
                }
            },
            
            {
                Common::SYST_UP,
                {
                    {"E", &METFixEE2017_UnclusteredEnUp_E_reco},
                    {"phi", &METFixEE2017_UnclusteredEnUp_phi_reco}
                }
                
            },
            
            {
                Common::SYST_DOWN,
                {
                    {"E", &METFixEE2017_UnclusteredEnDown_E_reco},
                    {"phi", &METFixEE2017_UnclusteredEnDown_phi_reco}
                }
            }
        };
        
        m_MET_reco = {
            {"2016", m_MET_reco_2016},
            {"2017", m_MET_reco_2017}
        };
    }
    
    
    void Info::clear()
    {
        runNumber = 0;
        eventNumber = 0;
        luminosityNumber = 0;
        bunchCrossingNumber = 0;
        
        //isTriggerPassed_reco = 0;
        
        if(bool_vertex_reco)
        {
            vertex_n_reco = 0;
        }
        
        if(bool_el_reco)
        {
            el_n_reco = 0;
            
            for(int i = 0; i < v_el_reco.size(); i++)
            {
                v_el_reco[i]->clear();
            }
        }
        
        if(bool_mu_reco)
        {
            mu_n_reco = 0;
            
            for(int i = 0; i < v_mu_reco.size(); i++)
            {
                v_mu_reco[i]->clear();
            }
        }
        
        if(bool_tau_reco)
        {
            tau_n_reco = 0;
            
            for(int i = 0; i < v_tau_reco.size(); i++)
            {
                v_tau_reco[i]->clear();
            }
        }
        
        if(bool_jet_reco)
        {
            jet_n_reco = 0;
            
            for(int i = 0; i < v_jet_reco.size(); i++)
            {
                v_jet_reco[i]->clear();
            }
        }
        
        if(bool_MET_reco)
        {
            MET_E_reco = 0; MET_phi_reco = 0;
            MET_JetResUp_E_reco = 0; MET_JetResUp_phi_reco = 0;
            MET_JetResDown_E_reco = 0; MET_JetResDown_phi_reco = 0;
            MET_JetEnUp_E_reco = 0; MET_JetEnUp_phi_reco = 0;
            MET_JetEnDown_E_reco = 0; MET_JetEnDown_phi_reco = 0;
            MET_UnclusteredEnUp_E_reco = 0; MET_UnclusteredEnUp_phi_reco = 0;
            MET_UnclusteredEnDown_E_reco = 0; MET_UnclusteredEnDown_phi_reco = 0;
            
            METFixEE2017_E_reco = 0; METFixEE2017_phi_reco = 0;
            METFixEE2017_JetResUp_E_reco = 0; METFixEE2017_JetResUp_phi_reco = 0;
            METFixEE2017_JetResDown_E_reco = 0; METFixEE2017_JetResDown_phi_reco = 0;
            METFixEE2017_JetEnUp_E_reco = 0; METFixEE2017_JetEnUp_phi_reco = 0;
            METFixEE2017_JetEnDown_E_reco = 0; METFixEE2017_JetEnDown_phi_reco = 0;
            METFixEE2017_UnclusteredEnUp_E_reco = 0; METFixEE2017_UnclusteredEnUp_phi_reco = 0;
            METFixEE2017_UnclusteredEnDown_E_reco = 0; METFixEE2017_UnclusteredEnDown_phi_reco = 0;
        }
        
        if(bool_trigger)
        {
            // El-Mu trigger
            isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v = 0;
            isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v = 0;
            isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v = 0;
            isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v = 0;
            
            
            // Mu trigger
            isTriggerPassed_HLT_IsoMu24_v = 0;
            isTriggerPassed_HLT_IsoTkMu24_v = 0;
            isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v = 0;
            isTriggerPassed_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v = 0;
            isTriggerPassed_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v = 0;
            
            isTriggerPassed_HLT_IsoMu27_v = 0;
            isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v = 0;
            isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v = 0;
            
            
            // Tau trigger
            isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v = 0;
            isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v = 0;
            
            isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v = 0;
            isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v = 0;
            isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v = 0;
        }
    }
    
    
    void Info::freeMemory()
    {
        delete T_reco;
        
        delete file;
    }
    
    
    void Info::linkBranch_reco(const char *option)
    {
        if(!strcmp(option, "read"))
        {
            T_reco->SetBranchAddress("runNumber", &runNumber);
            T_reco->SetBranchAddress("eventNumber", &eventNumber);
            T_reco->SetBranchAddress("luminosityNumber", &luminosityNumber);
            T_reco->SetBranchAddress("bunchCrossingNumber", &bunchCrossingNumber);
            
            //T_reco->SetBranchAddress("isTriggerPassed_reco", &isTriggerPassed_reco);
            
            if(bool_vertex_reco)
            {
                T_reco->SetBranchAddress("vertex_n_reco", &vertex_n_reco);
            }
            
            if(bool_el_reco)
            {
                T_reco->SetBranchAddress("el_n_reco", &el_n_reco);
                T_reco->SetBranchAddress("el_E_reco", &v_el_E_reco);
                T_reco->SetBranchAddress("el_px_reco", &v_el_px_reco);
                T_reco->SetBranchAddress("el_py_reco", &v_el_py_reco);
                T_reco->SetBranchAddress("el_pz_reco", &v_el_pz_reco);
                
                T_reco->SetBranchAddress("el_dxy_reco", &v_el_dxy_reco);
                T_reco->SetBranchAddress("el_dz_reco", &v_el_dz_reco);
                T_reco->SetBranchAddress("el_SIP3D_reco", &v_el_SIP3D_reco);
                
                T_reco->SetBranchAddress("el_missingInnerHits_reco", &v_el_missingInnerHits_reco);
                T_reco->SetBranchAddress("el_passConversionVeto_reco", &v_el_passConversionVeto_reco);
                
                T_reco->SetBranchAddress("el_mvaEleIDSpring16GeneralPurposeV1wp80_reco", &v_el_mvaEleIDSpring16GeneralPurposeV1wp80_reco);
                T_reco->SetBranchAddress("el_mvaEleIDSpring16GeneralPurposeV1wp90_reco", &v_el_mvaEleIDSpring16GeneralPurposeV1wp90_reco);
                
                T_reco->SetBranchAddress("el_mvaEleIDFall17noIsoV2wp90_reco", &v_el_mvaEleIDFall17noIsoV2wp90_reco);
                T_reco->SetBranchAddress("el_mvaEleIDFall17noIsoV2wp80_reco", &v_el_mvaEleIDFall17noIsoV2wp80_reco);
                
                T_reco->SetBranchAddress("el_mvaEleIDFall17isoV2wp90_reco", &v_el_mvaEleIDFall17isoV2wp90_reco);
                T_reco->SetBranchAddress("el_mvaEleIDFall17isoV2wp80_reco", &v_el_mvaEleIDFall17isoV2wp80_reco);
                
                T_reco->SetBranchAddress("el_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
                T_reco->SetBranchAddress("el_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
                T_reco->SetBranchAddress("el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
                T_reco->SetBranchAddress("el_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
            }
            
            if(bool_mu_reco)
            {
                T_reco->SetBranchAddress("mu_n_reco", &mu_n_reco);
                T_reco->SetBranchAddress("mu_E_reco", &v_mu_E_reco);
                T_reco->SetBranchAddress("mu_px_reco", &v_mu_px_reco);
                T_reco->SetBranchAddress("mu_py_reco", &v_mu_py_reco);
                T_reco->SetBranchAddress("mu_pz_reco", &v_mu_pz_reco);
                
                T_reco->SetBranchAddress("mu_dxy_reco", &v_mu_dxy_reco);
                T_reco->SetBranchAddress("mu_dz_reco", &v_mu_dz_reco);
                T_reco->SetBranchAddress("mu_SIP3D_reco", &v_mu_SIP3D_reco);
                
                T_reco->SetBranchAddress("mu_isGlobalMuon_reco", &v_mu_isGlobalMuon_reco);
                T_reco->SetBranchAddress("mu_isTrackerMuon_reco", &v_mu_isTrackerMuon_reco);
                
                T_reco->SetBranchAddress("mu_isLooseMuon_reco", &v_mu_isLooseMuon_reco);
                T_reco->SetBranchAddress("mu_isMediumMuon_reco", &v_mu_isMediumMuon_reco);
                T_reco->SetBranchAddress("mu_isTightMuon_reco", &v_mu_isTightMuon_reco);
                
                T_reco->SetBranchAddress("mu_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
                T_reco->SetBranchAddress("mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
                T_reco->SetBranchAddress("mu_byTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
                T_reco->SetBranchAddress("mu_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
            }
            
            if(bool_tau_reco)
            {
                T_reco->SetBranchAddress("tau_n_reco", &tau_n_reco);
                T_reco->SetBranchAddress("tau_E_reco", &v_tau_E_reco);
                T_reco->SetBranchAddress("tau_px_reco", &v_tau_px_reco);
                T_reco->SetBranchAddress("tau_py_reco", &v_tau_py_reco);
                T_reco->SetBranchAddress("tau_pz_reco", &v_tau_pz_reco);
                
                T_reco->SetBranchAddress("tau_dxy_reco", &v_tau_dxy_reco);
                T_reco->SetBranchAddress("tau_dz_reco", &v_tau_dz_reco);
                
                T_reco->SetBranchAddress("tau_byDecayModeFinding_reco", &v_tau_byDecayModeFinding_reco);
                //T_reco->SetBranchAddress("tau_byDecayModeFindingNewDMs_reco", &v_tau_byDecayModeFindingNewDMs_reco);
                T_reco->SetBranchAddress("tau_isTriggerMatched_reco", &v_tau_isTriggerMatched_reco);
                
                // 2016
                T_reco->SetBranchAddress("tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_reco", &v_tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_reco);
                T_reco->SetBranchAddress("tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_reco", &v_tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_reco);
                T_reco->SetBranchAddress("tau_byTightCombinedIsolationDeltaBetaCorr3Hits_reco", &v_tau_byTightCombinedIsolationDeltaBetaCorr3Hits_reco);
                
                T_reco->SetBranchAddress("tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco", &v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
                T_reco->SetBranchAddress("tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco", &v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
                T_reco->SetBranchAddress("tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco", &v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
                
                T_reco->SetBranchAddress("tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byMediumIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byMediumIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byTightIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco);
                
                T_reco->SetBranchAddress("tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->SetBranchAddress("tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco);
                
                T_reco->SetBranchAddress("tau_againstElectronVLooseMVA6_reco", &v_tau_againstElectronVLooseMVA6_reco);
                T_reco->SetBranchAddress("tau_againstElectronLooseMVA6_reco", &v_tau_againstElectronLooseMVA6_reco);
                T_reco->SetBranchAddress("tau_againstElectronMediumMVA6_reco", &v_tau_againstElectronMediumMVA6_reco);
                T_reco->SetBranchAddress("tau_againstElectronTightMVA6_reco", &v_tau_againstElectronTightMVA6_reco);
                T_reco->SetBranchAddress("tau_againstElectronVTightMVA6_reco", &v_tau_againstElectronVTightMVA6_reco);
                
                T_reco->SetBranchAddress("tau_againstMuonLoose3_reco", &v_tau_againstMuonLoose3_reco);
                T_reco->SetBranchAddress("tau_againstMuonTight3_reco", &v_tau_againstMuonTight3_reco);
                
                // 2017
                T_reco->SetBranchAddress("tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->SetBranchAddress("tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->SetBranchAddress("tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->SetBranchAddress("tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->SetBranchAddress("tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco);
                
                T_reco->SetBranchAddress("tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->SetBranchAddress("tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->SetBranchAddress("tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->SetBranchAddress("tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->SetBranchAddress("tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                
                //Deep Tau Id branches
                T_reco->SetBranchAddress("tau_byVVVLooseDeepTau2017v2p1VSjet_reco", &v_tau_byVVVLooseDeepTau2017v2p1VSjet_reco);
                T_reco->SetBranchAddress("tau_byVVLooseDeepTau2017v2p1VSjet_reco", &v_tau_byVVLooseDeepTau2017v2p1VSjet_reco);
                T_reco->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSjet_reco", &v_tau_byVLooseDeepTau2017v2p1VSjet_reco);
                T_reco->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSjet_reco", &v_tau_byLooseDeepTau2017v2p1VSjet_reco);
                T_reco->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSjet_reco", &v_tau_byMediumDeepTau2017v2p1VSjet_reco);
                T_reco->SetBranchAddress("tau_byTightDeepTau2017v2p1VSjet_reco", &v_tau_byTightDeepTau2017v2p1VSjet_reco);
                T_reco->SetBranchAddress("tau_byVTightDeepTau2017v2p1VSjet_reco", &v_tau_byVTightDeepTau2017v2p1VSjet_reco);
                T_reco->SetBranchAddress("tau_byVVTightDeepTau2017v2p1VSjet_reco", &v_tau_byVVTightDeepTau2017v2p1VSjet_reco);
                
                T_reco->SetBranchAddress("tau_VVVLooseDeepTau2017v2p1VSe_reco", &v_tau_byVVVLooseDeepTau2017v2p1VSe_reco);
                T_reco->SetBranchAddress("tau_VVLooseDeepTau2017v2p1VSe_reco", &v_tau_byVVLooseDeepTau2017v2p1VSe_reco);
                T_reco->SetBranchAddress("tau_VLooseDeepTau2017v2p1VSe_reco", &v_tau_byVLooseDeepTau2017v2p1VSe_reco);
                T_reco->SetBranchAddress("tau_LooseDeepTau2017v2p1VSe_reco", &v_tau_byLooseDeepTau2017v2p1VSe_reco);
                T_reco->SetBranchAddress("tau_MediumDeepTau2017v2p1VSe_reco", &v_tau_byMediumDeepTau2017v2p1VSe_reco);
                T_reco->SetBranchAddress("tau_TightDeepTau2017v2p1VSe_reco", &v_tau_byTightDeepTau2017v2p1VSe_reco);
                T_reco->SetBranchAddress("tau_VTightDeepTau2017v2p1VSe_reco", &v_tau_byVTightDeepTau2017v2p1VSe_reco);
                T_reco->SetBranchAddress("tau_VVTightDeepTau2017v2p1VSe_reco", &v_tau_byVVTightDeepTau2017v2p1VSe_reco);
                
                T_reco->SetBranchAddress("tau_byVLooseDeepTau2017v2p1VSmu_reco", &v_tau_byVLooseDeepTau2017v2p1VSmu_reco);
                T_reco->SetBranchAddress("tau_byLooseDeepTau2017v2p1VSmu_reco", &v_tau_byLooseDeepTau2017v2p1VSmu_reco);
                T_reco->SetBranchAddress("tau_byMediumDeepTau2017v2p1VSmu_reco", &v_tau_byMediumDeepTau2017v2p1VSmu_reco);
                T_reco->SetBranchAddress("tau_byTightDeepTau2017v2p1VSmu_reco", &v_tau_byTightDeepTau2017v2p1VSmu_reco);
                
                T_reco->SetBranchAddress("tau_decayMode_reco", &v_tau_decayMode_reco);
                
                T_reco->SetBranchAddress("tau_chHad1_E_reco", &v_tau_chHad1_E_reco);
                T_reco->SetBranchAddress("tau_chHad1_px_reco", &v_tau_chHad1_px_reco);
                T_reco->SetBranchAddress("tau_chHad1_py_reco", &v_tau_chHad1_py_reco);
                T_reco->SetBranchAddress("tau_chHad1_pz_reco", &v_tau_chHad1_pz_reco);
            }
            
            if(bool_jet_reco)
            {
                T_reco->SetBranchAddress("jet_n_reco", &jet_n_reco);
                T_reco->SetBranchAddress("jet_E_reco", &v_jet_E_reco);
                T_reco->SetBranchAddress("jet_px_reco", &v_jet_px_reco);
                T_reco->SetBranchAddress("jet_py_reco", &v_jet_py_reco);
                T_reco->SetBranchAddress("jet_pz_reco", &v_jet_pz_reco);
                
                T_reco->SetBranchAddress("jet_partonFlavour_reco", &v_jet_partonFlavour_reco);
                T_reco->SetBranchAddress("jet_hadronFlavour_reco", &v_jet_hadronFlavour_reco);
                
                T_reco->SetBranchAddress("jet_JECcorr_reco", &v_jet_JECcorr_reco);
                T_reco->SetBranchAddress("jet_JECcorrUp_reco", &v_jet_JECcorrUp_reco);
                T_reco->SetBranchAddress("jet_JECcorrDown_reco", &v_jet_JECcorrDown_reco);
                
                T_reco->SetBranchAddress("jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
                T_reco->SetBranchAddress("jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
                T_reco->SetBranchAddress("jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
                T_reco->SetBranchAddress("jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
                
                T_reco->SetBranchAddress("jet_pfDeepCSVJetTags_reco", &v_jet_pfDeepCSVJetTags_reco);
                T_reco->SetBranchAddress("jet_byLoosePfDeepCSVJetTags_reco", &v_jet_byLoosePfDeepCSVJetTags_reco);
                T_reco->SetBranchAddress("jet_byMediumPfDeepCSVJetTags_reco", &v_jet_byMediumPfDeepCSVJetTags_reco);
                T_reco->SetBranchAddress("jet_byTightPfDeepCSVJetTags_reco", &v_jet_byTightPfDeepCSVJetTags_reco);
                
                T_reco->SetBranchAddress("jet_pfDeepFlavourJetTags_reco", &v_jet_pfDeepFlavourJetTags_reco);
                T_reco->SetBranchAddress("jet_byLoosePfDeepFlavourJetTags_reco", &v_jet_byLoosePfDeepFlavourJetTags_reco);
                T_reco->SetBranchAddress("jet_byMediumPfDeepFlavourJetTags_reco", &v_jet_byMediumPfDeepFlavourJetTags_reco);
                T_reco->SetBranchAddress("jet_byTightPfDeepFlavourJetTags_reco", &v_jet_byTightPfDeepFlavourJetTags_reco);
            }
            
            if(bool_MET_reco)
            {
                T_reco->SetBranchAddress("MET_E_reco", &MET_E_reco);
                T_reco->SetBranchAddress("MET_phi_reco", &MET_phi_reco);
                
                T_reco->SetBranchAddress("MET_JetResUp_E_reco", &MET_JetResUp_E_reco);
                T_reco->SetBranchAddress("MET_JetResUp_phi_reco", &MET_JetResUp_phi_reco);
                
                T_reco->SetBranchAddress("MET_JetResDown_E_reco", &MET_JetResDown_E_reco);
                T_reco->SetBranchAddress("MET_JetResDown_phi_reco", &MET_JetResDown_phi_reco);
                
                T_reco->SetBranchAddress("MET_JetEnUp_E_reco", &MET_JetEnUp_E_reco);
                T_reco->SetBranchAddress("MET_JetEnUp_phi_reco", &MET_JetEnUp_phi_reco);
                
                T_reco->SetBranchAddress("MET_JetEnDown_E_reco", &MET_JetEnDown_E_reco);
                T_reco->SetBranchAddress("MET_JetEnDown_phi_reco", &MET_JetEnDown_phi_reco);
                
                T_reco->SetBranchAddress("MET_UnclusteredEnUp_E_reco", &MET_UnclusteredEnUp_E_reco);
                T_reco->SetBranchAddress("MET_UnclusteredEnUp_phi_reco", &MET_UnclusteredEnUp_phi_reco);
                
                T_reco->SetBranchAddress("MET_UnclusteredEnDown_E_reco", &MET_UnclusteredEnDown_E_reco);
                T_reco->SetBranchAddress("MET_UnclusteredEnDown_phi_reco", &MET_UnclusteredEnDown_phi_reco);
                
                
                T_reco->SetBranchAddress("METFixEE2017_E_reco", &METFixEE2017_E_reco);
                T_reco->SetBranchAddress("METFixEE2017_phi_reco", &METFixEE2017_phi_reco);
                
                T_reco->SetBranchAddress("METFixEE2017_JetResUp_E_reco", &METFixEE2017_JetResUp_E_reco);
                T_reco->SetBranchAddress("METFixEE2017_JetResUp_phi_reco", &METFixEE2017_JetResUp_phi_reco);
                
                T_reco->SetBranchAddress("METFixEE2017_JetResDown_E_reco", &METFixEE2017_JetResDown_E_reco);
                T_reco->SetBranchAddress("METFixEE2017_JetResDown_phi_reco", &METFixEE2017_JetResDown_phi_reco);
                
                T_reco->SetBranchAddress("METFixEE2017_JetEnUp_E_reco", &METFixEE2017_JetEnUp_E_reco);
                T_reco->SetBranchAddress("METFixEE2017_JetEnUp_phi_reco", &METFixEE2017_JetEnUp_phi_reco);
                
                T_reco->SetBranchAddress("METFixEE2017_JetEnDown_E_reco", &METFixEE2017_JetEnDown_E_reco);
                T_reco->SetBranchAddress("METFixEE2017_JetEnDown_phi_reco", &METFixEE2017_JetEnDown_phi_reco);
                
                T_reco->SetBranchAddress("METFixEE2017_UnclusteredEnUp_E_reco", &METFixEE2017_UnclusteredEnUp_E_reco);
                T_reco->SetBranchAddress("METFixEE2017_UnclusteredEnUp_phi_reco", &METFixEE2017_UnclusteredEnUp_phi_reco);
                
                T_reco->SetBranchAddress("METFixEE2017_UnclusteredEnDown_E_reco", &METFixEE2017_UnclusteredEnDown_E_reco);
                T_reco->SetBranchAddress("METFixEE2017_UnclusteredEnDown_phi_reco", &METFixEE2017_UnclusteredEnDown_phi_reco);
            }
            
            if(bool_trigger)
            {
                // El-Mu trigger
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v", &isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", &isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", &isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", &isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v);
                
                // Mu trigger
                T_reco->SetBranchAddress("isTriggerPassed_HLT_IsoMu24_v", &isTriggerPassed_HLT_IsoMu24_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_IsoTkMu24_v", &isTriggerPassed_HLT_IsoTkMu24_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", &isTriggerPassed_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v);
                
                T_reco->SetBranchAddress("isTriggerPassed_HLT_IsoMu27_v", &isTriggerPassed_HLT_IsoMu27_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v);
                
                // Tau trigger
                T_reco->SetBranchAddress("isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v);
                
                T_reco->SetBranchAddress("isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v);
                T_reco->SetBranchAddress("isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v);
            }
        }
        
        else if(!strcmp(option, "write"))
        {
            T_reco->Branch("runNumber", &runNumber);
            T_reco->Branch("eventNumber", &eventNumber);
            T_reco->Branch("luminosityNumber", &luminosityNumber);
            T_reco->Branch("bunchCrossingNumber", &bunchCrossingNumber);
            
            //T_reco->Branch("isTriggerPassed_reco", &isTriggerPassed_reco);
            
            if(bool_vertex_reco)
            {
                T_reco->Branch("vertex_n_reco", &vertex_n_reco);
            }
            
            if(bool_el_reco)
            {
                T_reco->Branch("el_n_reco", &el_n_reco);
                T_reco->Branch("el_E_reco", &v_el_E_reco);
                T_reco->Branch("el_px_reco", &v_el_px_reco);
                T_reco->Branch("el_py_reco", &v_el_py_reco);
                T_reco->Branch("el_pz_reco", &v_el_pz_reco);
                
                T_reco->Branch("el_dxy_reco", &v_el_dxy_reco);
                T_reco->Branch("el_dz_reco", &v_el_dz_reco);
                T_reco->Branch("el_SIP3D_reco", &v_el_SIP3D_reco);
                
                T_reco->Branch("el_missingInnerHits_reco", &v_el_missingInnerHits_reco);
                T_reco->Branch("el_passConversionVeto_reco", &v_el_passConversionVeto_reco);
                
                T_reco->Branch("el_mvaEleIDSpring16GeneralPurposeV1wp80_reco", &v_el_mvaEleIDSpring16GeneralPurposeV1wp80_reco);
                T_reco->Branch("el_mvaEleIDSpring16GeneralPurposeV1wp90_reco", &v_el_mvaEleIDSpring16GeneralPurposeV1wp90_reco);
                
                T_reco->Branch("el_mvaEleIDFall17noIsoV2wp90_reco", &v_el_mvaEleIDFall17noIsoV2wp90_reco);
                T_reco->Branch("el_mvaEleIDFall17noIsoV2wp80_reco", &v_el_mvaEleIDFall17noIsoV2wp80_reco);
                
                T_reco->Branch("el_mvaEleIDFall17isoV2wp90_reco", &v_el_mvaEleIDFall17isoV2wp90_reco);
                T_reco->Branch("el_mvaEleIDFall17isoV2wp80_reco", &v_el_mvaEleIDFall17isoV2wp80_reco);
                
                T_reco->Branch("el_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
                T_reco->Branch("el_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
                T_reco->Branch("el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
                T_reco->Branch("el_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco", &v_el_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco);
            }
            
            if(bool_mu_reco)
            {
                T_reco->Branch("mu_n_reco", &mu_n_reco);
                T_reco->Branch("mu_E_reco", &v_mu_E_reco);
                T_reco->Branch("mu_px_reco", &v_mu_px_reco);
                T_reco->Branch("mu_py_reco", &v_mu_py_reco);
                T_reco->Branch("mu_pz_reco", &v_mu_pz_reco);
                
                T_reco->Branch("mu_dxy_reco", &v_mu_dxy_reco);
                T_reco->Branch("mu_dz_reco", &v_mu_dz_reco);
                T_reco->Branch("mu_SIP3D_reco", &v_mu_SIP3D_reco);
                
                T_reco->Branch("mu_isGlobalMuon_reco", &v_mu_isGlobalMuon_reco);
                T_reco->Branch("mu_isTrackerMuon_reco", &v_mu_isTrackerMuon_reco);
                
                T_reco->Branch("mu_isLooseMuon_reco", &v_mu_isLooseMuon_reco);
                T_reco->Branch("mu_isMediumMuon_reco", &v_mu_isMediumMuon_reco);
                T_reco->Branch("mu_isTightMuon_reco", &v_mu_isTightMuon_reco);
                
                T_reco->Branch("mu_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
                T_reco->Branch("mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
                T_reco->Branch("mu_byTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
                T_reco->Branch("mu_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco", &v_mu_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco);
            }
            
            if(bool_tau_reco)
            {
                T_reco->Branch("tau_n_reco", &tau_n_reco);
                T_reco->Branch("tau_E_reco", &v_tau_E_reco);
                T_reco->Branch("tau_px_reco", &v_tau_px_reco);
                T_reco->Branch("tau_py_reco", &v_tau_py_reco);
                T_reco->Branch("tau_pz_reco", &v_tau_pz_reco);
                
                T_reco->Branch("tau_dxy_reco", &v_tau_dxy_reco);
                T_reco->Branch("tau_dz_reco", &v_tau_dz_reco);
                
                T_reco->Branch("tau_byDecayModeFinding_reco", &v_tau_byDecayModeFinding_reco);
                T_reco->Branch("tau_isTriggerMatched_reco", &v_tau_isTriggerMatched_reco);
                
                // 2016
                T_reco->Branch("tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_reco", &v_tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_reco);
                T_reco->Branch("tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_reco", &v_tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_reco);
                T_reco->Branch("tau_byTightCombinedIsolationDeltaBetaCorr3Hits_reco", &v_tau_byTightCombinedIsolationDeltaBetaCorr3Hits_reco);
                
                T_reco->Branch("tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco", &v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
                T_reco->Branch("tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco", &v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
                T_reco->Branch("tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco", &v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco);
                
                T_reco->Branch("tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->Branch("tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->Branch("tau_byMediumIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byMediumIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->Branch("tau_byTightIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco);
                T_reco->Branch("tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco", &v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco);
                
                T_reco->Branch("tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->Branch("tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->Branch("tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->Branch("tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco);
                T_reco->Branch("tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco", &v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco);
                
                T_reco->Branch("tau_againstElectronVLooseMVA6_reco", &v_tau_againstElectronVLooseMVA6_reco);
                T_reco->Branch("tau_againstElectronLooseMVA6_reco", &v_tau_againstElectronLooseMVA6_reco);
                T_reco->Branch("tau_againstElectronMediumMVA6_reco", &v_tau_againstElectronMediumMVA6_reco);
                T_reco->Branch("tau_againstElectronTightMVA6_reco", &v_tau_againstElectronTightMVA6_reco);
                T_reco->Branch("tau_againstElectronVTightMVA6_reco", &v_tau_againstElectronVTightMVA6_reco);
                
                T_reco->Branch("tau_againstMuonLoose3_reco", &v_tau_againstMuonLoose3_reco);
                T_reco->Branch("tau_againstMuonTight3_reco", &v_tau_againstMuonTight3_reco);
                
                // 2017
                T_reco->Branch("tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->Branch("tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->Branch("tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->Branch("tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco);
                T_reco->Branch("tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco", &v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco);
                
                T_reco->Branch("tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->Branch("tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->Branch("tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->Branch("tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                T_reco->Branch("tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco", &v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco);
                
                T_reco->Branch("tau_decayMode_reco", &v_tau_decayMode_reco);
                
                T_reco->Branch("tau_chHad1_E_reco", &v_tau_chHad1_E_reco);
                T_reco->Branch("tau_chHad1_px_reco", &v_tau_chHad1_px_reco);
                T_reco->Branch("tau_chHad1_py_reco", &v_tau_chHad1_py_reco);
                T_reco->Branch("tau_chHad1_pz_reco", &v_tau_chHad1_pz_reco);
            }
            
            if(bool_jet_reco)
            {
                T_reco->Branch("jet_n_reco", &jet_n_reco);
                T_reco->Branch("jet_E_reco", &v_jet_E_reco);
                T_reco->Branch("jet_px_reco", &v_jet_px_reco);
                T_reco->Branch("jet_py_reco", &v_jet_py_reco);
                T_reco->Branch("jet_pz_reco", &v_jet_pz_reco);
                
                T_reco->Branch("jet_partonFlavour_reco", &v_jet_partonFlavour_reco);
                T_reco->Branch("jet_hadronFlavour_reco", &v_jet_hadronFlavour_reco);
                
                T_reco->Branch("jet_JECcorr_reco", &v_jet_JECcorr_reco);
                T_reco->Branch("jet_JECcorrUp_reco", &v_jet_JECcorrUp_reco);
                T_reco->Branch("jet_JECcorrDown_reco", &v_jet_JECcorrDown_reco);
                
                T_reco->Branch("jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
                T_reco->Branch("jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
                T_reco->Branch("jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
                T_reco->Branch("jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco", &v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco);
            }
            
            if(bool_MET_reco)
            {
                T_reco->Branch("MET_E_reco", &MET_E_reco);
                T_reco->Branch("MET_phi_reco", &MET_phi_reco);
                
                T_reco->Branch("MET_JetResUp_E_reco", &MET_JetResUp_E_reco);
                T_reco->Branch("MET_JetResUp_phi_reco", &MET_JetResUp_phi_reco);
                
                T_reco->Branch("MET_JetResDown_E_reco", &MET_JetResDown_E_reco);
                T_reco->Branch("MET_JetResDown_phi_reco", &MET_JetResDown_phi_reco);
                
                T_reco->Branch("MET_JetEnUp_E_reco", &MET_JetEnUp_E_reco);
                T_reco->Branch("MET_JetEnUp_phi_reco", &MET_JetEnUp_phi_reco);
                
                T_reco->Branch("MET_JetEnDown_E_reco", &MET_JetEnDown_E_reco);
                T_reco->Branch("MET_JetEnDown_phi_reco", &MET_JetEnDown_phi_reco);
                
                T_reco->Branch("MET_UnclusteredEnUp_E_reco", &MET_UnclusteredEnUp_E_reco);
                T_reco->Branch("MET_UnclusteredEnUp_phi_reco", &MET_UnclusteredEnUp_phi_reco);
                
                T_reco->Branch("MET_UnclusteredEnDown_E_reco", &MET_UnclusteredEnDown_E_reco);
                T_reco->Branch("MET_UnclusteredEnDown_phi_reco", &MET_UnclusteredEnDown_phi_reco);
                
                
                T_reco->Branch("METFixEE2017_E_reco", &METFixEE2017_E_reco);
                T_reco->Branch("METFixEE2017_phi_reco", &METFixEE2017_phi_reco);
                
                T_reco->Branch("METFixEE2017_JetResUp_E_reco", &METFixEE2017_JetResUp_E_reco);
                T_reco->Branch("METFixEE2017_JetResUp_phi_reco", &METFixEE2017_JetResUp_phi_reco);
                
                T_reco->Branch("METFixEE2017_JetResDown_E_reco", &METFixEE2017_JetResDown_E_reco);
                T_reco->Branch("METFixEE2017_JetResDown_phi_reco", &METFixEE2017_JetResDown_phi_reco);
                
                T_reco->Branch("METFixEE2017_JetEnUp_E_reco", &METFixEE2017_JetEnUp_E_reco);
                T_reco->Branch("METFixEE2017_JetEnUp_phi_reco", &METFixEE2017_JetEnUp_phi_reco);
                
                T_reco->Branch("METFixEE2017_JetEnDown_E_reco", &METFixEE2017_JetEnDown_E_reco);
                T_reco->Branch("METFixEE2017_JetEnDown_phi_reco", &METFixEE2017_JetEnDown_phi_reco);
                
                T_reco->Branch("METFixEE2017_UnclusteredEnUp_E_reco", &METFixEE2017_UnclusteredEnUp_E_reco);
                T_reco->Branch("METFixEE2017_UnclusteredEnUp_phi_reco", &METFixEE2017_UnclusteredEnUp_phi_reco);
                
                T_reco->Branch("METFixEE2017_UnclusteredEnDown_E_reco", &METFixEE2017_UnclusteredEnDown_E_reco);
                T_reco->Branch("METFixEE2017_UnclusteredEnDown_phi_reco", &METFixEE2017_UnclusteredEnDown_phi_reco);
            }
            
            if(bool_trigger)
            {
                // El-Mu trigger
                T_reco->Branch("isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v", &isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v);
                T_reco->Branch("isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v", &isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v);
                T_reco->Branch("isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v", &isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v);
                T_reco->Branch("isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v", &isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v);
                
                // Mu trigger
                T_reco->Branch("isTriggerPassed_HLT_IsoMu24_v", &isTriggerPassed_HLT_IsoMu24_v);
                T_reco->Branch("isTriggerPassed_HLT_IsoTkMu24_v", &isTriggerPassed_HLT_IsoTkMu24_v);
                T_reco->Branch("isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v);
                T_reco->Branch("isTriggerPassed_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v);
                T_reco->Branch("isTriggerPassed_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v", &isTriggerPassed_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v);
                
                T_reco->Branch("isTriggerPassed_HLT_IsoMu27_v", &isTriggerPassed_HLT_IsoMu27_v);
                T_reco->Branch("isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v);
                T_reco->Branch("isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v", &isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v);
                
                // Tau trigger
                T_reco->Branch("isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v);
                T_reco->Branch("isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v);
                
                T_reco->Branch("isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v);
                T_reco->Branch("isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v);
                T_reco->Branch("isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v", &isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v);
            }
        }
    }
    
    
    void Info::writeData()
    {
        file->cd();
        
        T_reco->Write();
    }
}

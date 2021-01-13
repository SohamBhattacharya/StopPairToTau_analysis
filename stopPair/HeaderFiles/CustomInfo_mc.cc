# include <iostream>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TTree.h>

# include "Common.h"
# include "CustomInfo_mc.h"
# include "CustomInfo_common.h"


namespace CustomInfo_mc
{
    Info::Info(
        const char *fileName,
        const char *treeName_gen,
        std::vector <const char*> v_object_gen,
        const char *treeName_reco,
        std::vector <const char*> v_object_reco,
        const char *mode,
        const char *fileName_pileUp_mc, const char *histName_pileUp_mc,
        const char *fileName_pileUp_data, const char *histName_pileUp_data,
        const char *fileName_pileUp_data_systUp, const char *histName_pileUp_data_systUp,
        const char *fileName_pileUp_data_systDown, const char *histName_pileUp_data_systDown
    )
    {
        if(!strcmp(mode, "read"))
        {
            file = TFile::Open(fileName, "READ");
            
            if(treeName_gen)
            {
                T_gen = (TTree*) file->Get(treeName_gen);
            }
            
            if(treeName_reco)
            {
                T_reco = (TTree*) file->Get(treeName_reco);
            }
        }
        
        else if(!strcmp(mode, "write"))
        {
            file = TFile::Open(fileName, "RECREATE");
            
            if(treeName_gen)
            {
                T_gen = new TTree(treeName_gen, treeName_gen);
            }
            
            if(treeName_reco)
            {
                T_reco = new TTree(treeName_reco, treeName_reco);
            }
        }
        
        // GEN ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        v_el_E_gen = 0; v_el_px_gen = 0; v_el_py_gen = 0; v_el_pz_gen = 0;
        v_el_isPrompt_gen = 0;
        
        v_mu_E_gen = 0; v_mu_px_gen = 0; v_mu_py_gen = 0; v_mu_pz_gen = 0;
        v_mu_isPrompt_gen = 0;
        
        v_tau_E_gen = 0; v_tau_px_gen = 0; v_tau_py_gen = 0; v_tau_pz_gen = 0;
        v_tau_vis_E_gen = 0; v_tau_vis_px_gen = 0; v_tau_vis_py_gen = 0; v_tau_vis_pz_gen = 0;
        
        v_t_E_gen = 0; v_t_px_gen = 0; v_t_py_gen = 0; v_t_pz_gen = 0;
        v_b_E_gen = 0; v_b_px_gen = 0; v_b_py_gen = 0; v_b_pz_gen = 0;
        
        v_W_E_gen = 0; v_W_px_gen = 0; v_W_py_gen = 0; v_W_pz_gen = 0;
        v_Z_E_gen = 0; v_Z_px_gen = 0; v_Z_py_gen = 0; v_Z_pz_gen = 0;
        
        v_stau1_E_gen = 0; v_stau1_px_gen = 0; v_stau1_py_gen = 0; v_stau1_pz_gen = 0;
        v_stop1_E_gen = 0; v_stop1_px_gen = 0; v_stop1_py_gen = 0; v_stop1_pz_gen = 0;
        v_chargino1_E_gen = 0; v_chargino1_px_gen = 0; v_chargino1_py_gen = 0; v_chargino1_pz_gen = 0;
        
        v_jet_E_gen = 0; v_jet_px_gen = 0; v_jet_py_gen = 0; v_jet_pz_gen = 0;
        
        // Set object options
        bool_genParam = false;
        
        bool_el_gen = false;
        bool_mu_gen = false;
        bool_tau_vis_gen = false;
        
        bool_t_gen = false;
        bool_b_gen = false;
        
        bool_W_gen = false;
        bool_Z_gen = false;
        
        bool_stau1_gen = false;
        bool_stop1_gen = false;
        bool_chargino1_gen = false;
        
        bool_jet_gen = false;
        
        bool_MET_gen = false;
        
        for(int iObject = 0; iObject < v_object_gen.size(); iObject++)
        {
            if(!strcmp(v_object_gen[iObject], "genParam"))
            {
                bool_genParam = true;
            }
            
            if(!strcmp(v_object_gen[iObject], "el"))
            {
                bool_el_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "mu"))
            {
                bool_mu_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "tau_vis"))
            {
                bool_tau_vis_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "t"))
            {
                bool_t_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "b"))
            {
                bool_b_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "W"))
            {
                bool_W_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "Z"))
            {
                bool_Z_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "stau1"))
            {
                bool_stau1_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "stop1"))
            {
                bool_stop1_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "chargino1"))
            {
                bool_chargino1_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "jet"))
            {
                bool_jet_gen = true;
            }
            
            else if(!strcmp(v_object_gen[iObject], "MET"))
            {
                bool_MET_gen = true;
            }
        }
        
        
        nScaleVariation = 9;
        v_scaleWeight.resize(nScaleVariation, 1.0);
        
        
        // Link branches
        linkBranch_gen(mode);
        
        // Create object collections
        // El
        v_el_gen.push_back(v_el_E_gen);
        v_el_gen.push_back(v_el_px_gen);
        v_el_gen.push_back(v_el_py_gen);
        v_el_gen.push_back(v_el_pz_gen);
        v_el_gen.push_back(v_el_isPrompt_gen);
        
        // Mu
        v_mu_gen.push_back(v_mu_E_gen);
        v_mu_gen.push_back(v_mu_px_gen);
        v_mu_gen.push_back(v_mu_py_gen);
        v_mu_gen.push_back(v_mu_pz_gen);
        v_mu_gen.push_back(v_mu_isPrompt_gen);
        
        // Tau-vis
        v_tau_vis_gen.push_back(v_tau_vis_E_gen);
        v_tau_vis_gen.push_back(v_tau_vis_px_gen);
        v_tau_vis_gen.push_back(v_tau_vis_py_gen);
        v_tau_vis_gen.push_back(v_tau_vis_pz_gen);
        v_tau_vis_gen.push_back(v_tau_E_gen);
        v_tau_vis_gen.push_back(v_tau_px_gen);
        v_tau_vis_gen.push_back(v_tau_py_gen);
        v_tau_vis_gen.push_back(v_tau_pz_gen);
        
        // t
        v_t_gen.push_back(v_t_E_gen);
        v_t_gen.push_back(v_t_px_gen);
        v_t_gen.push_back(v_t_py_gen);
        v_t_gen.push_back(v_t_pz_gen);
        
        // b
        v_b_gen.push_back(v_b_E_gen);
        v_b_gen.push_back(v_b_px_gen);
        v_b_gen.push_back(v_b_py_gen);
        v_b_gen.push_back(v_b_pz_gen);
        
        // W
        v_W_gen.push_back(v_W_E_gen);
        v_W_gen.push_back(v_W_px_gen);
        v_W_gen.push_back(v_W_py_gen);
        v_W_gen.push_back(v_W_pz_gen);
        
        // Z
        v_Z_gen.push_back(v_Z_E_gen);
        v_Z_gen.push_back(v_Z_px_gen);
        v_Z_gen.push_back(v_Z_py_gen);
        v_Z_gen.push_back(v_Z_pz_gen);
        
        // stau1
        v_stau1_gen.push_back(v_stau1_E_gen);
        v_stau1_gen.push_back(v_stau1_px_gen);
        v_stau1_gen.push_back(v_stau1_py_gen);
        v_stau1_gen.push_back(v_stau1_pz_gen);
        
        // stop1
        v_stop1_gen.push_back(v_stop1_E_gen);
        v_stop1_gen.push_back(v_stop1_px_gen);
        v_stop1_gen.push_back(v_stop1_py_gen);
        v_stop1_gen.push_back(v_stop1_pz_gen);
        
        // chargino1
        v_chargino1_gen.push_back(v_chargino1_E_gen);
        v_chargino1_gen.push_back(v_chargino1_px_gen);
        v_chargino1_gen.push_back(v_chargino1_py_gen);
        v_chargino1_gen.push_back(v_chargino1_pz_gen);
        
        // Jet
        v_jet_gen.push_back(v_jet_E_gen);
        v_jet_gen.push_back(v_jet_px_gen);
        v_jet_gen.push_back(v_jet_py_gen);
        v_jet_gen.push_back(v_jet_pz_gen);
        
        
        // RECO ////////////////////////////////////////////////////////////////////////////////////////////////////
        
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
        
        v_jet_isISR_reco = 0;
        
        v_jet_partonFlavour_reco = 0;
        v_jet_hadronFlavour_reco = 0;
        
        v_jet_JECcorr_reco = 0;
        v_jet_JECcorrUp_reco = 0;
        v_jet_JECcorrDown_reco = 0;
        
        v_jet_JERcorr_reco = 0;
        v_jet_JERcorrUp_reco = 0;
        v_jet_JERcorrDown_reco = 0;
        
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
        bool_pileUp_reco = false;
        bool_vertex_reco = false;
        bool_el_reco = false;
        bool_mu_reco = false;
        bool_tau_reco = false;
        
        bool_jet_reco = false;
        
        bool_MET_reco = false;
        
        bool_trigger = false;
        
        for(int iObject = 0; iObject < v_object_reco.size(); iObject++)
        {
            if(!strcmp(v_object_reco[iObject], "PU"))
            {
                bool_pileUp_reco = true;
            }
            
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
        
        v_jet_reco.push_back(v_jet_isISR_reco);
        
        v_jet_reco.push_back(v_jet_partonFlavour_reco);
        v_jet_reco.push_back(v_jet_hadronFlavour_reco);
        
        v_jet_reco.push_back(v_jet_JECcorr_reco);
        v_jet_reco.push_back(v_jet_JECcorrUp_reco);
        v_jet_reco.push_back(v_jet_JECcorrDown_reco);
        
        v_jet_reco.push_back(v_jet_JERcorr_reco);
        v_jet_reco.push_back(v_jet_JERcorrUp_reco);
        v_jet_reco.push_back(v_jet_JERcorrDown_reco);
        
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
        
        m_JERcorr = {
            {Common::SYST_CENTRAL, v_jet_JERcorr_reco},
            {Common::SYST_UP, v_jet_JERcorrUp_reco},
            {Common::SYST_DOWN, v_jet_JERcorrDown_reco}
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
        
        
        h1_pileUp_mc = 0;
        h1_pileUp_data = 0;
        h1_pileUp_data_systUp = 0;
        h1_pileUp_data_systDown = 0;
        
        // Get pile-up
        if(bool_pileUp_reco && fileName_pileUp_mc && histName_pileUp_mc)
        {
            h1_pileUp_mc = getPileUp(fileName_pileUp_mc, histName_pileUp_mc);
        }
        
        if(bool_pileUp_reco)
        {
            if(fileName_pileUp_data && histName_pileUp_data)
            {
                h1_pileUp_data = getPileUp(fileName_pileUp_data, histName_pileUp_data);
            }
            
            if(fileName_pileUp_data_systUp && histName_pileUp_data_systUp)
            {
                h1_pileUp_data_systUp = getPileUp(fileName_pileUp_data_systUp, histName_pileUp_data_systUp);
            }
            
            if(fileName_pileUp_data_systDown && histName_pileUp_data_systDown)
            {
                h1_pileUp_data_systDown = getPileUp(fileName_pileUp_data_systDown, histName_pileUp_data_systDown);
            }
        }
    }
    
    
    void Info::clear()
    {
        // GEN ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        if(bool_el_gen)
        {
            el_n_gen = 0;
            
            for(int i = 0; i < v_el_gen.size(); i++)
            {
                v_el_gen[i]->clear();
            }
        }
        
        if(bool_mu_gen)
        {
            mu_n_gen = 0;
            
            for(int i = 0; i < v_mu_gen.size(); i++)
            {
                v_mu_gen[i]->clear();
            }
        }
        
        if(bool_tau_vis_gen)
        {
            tau_vis_n_gen = 0;
            
            for(int i = 0; i < v_tau_vis_gen.size(); i++)
            {
                v_tau_vis_gen[i]->clear();
            }
        }
        
        if(bool_t_gen)
        {
            t_n_gen = 0;
            
            for(int i = 0; i < v_t_gen.size(); i++)
            {
                v_t_gen[i]->clear();
            }
        }
        
        if(bool_b_gen)
        {
            b_n_gen = 0;
            
            for(int i = 0; i < v_b_gen.size(); i++)
            {
                v_b_gen[i]->clear();
            }
        }
        
        if(bool_W_gen)
        {
            W_n_gen = 0;
            
            for(int i = 0; i < v_W_gen.size(); i++)
            {
                v_W_gen[i]->clear();
            }
        }
        
        if(bool_Z_gen)
        {
            Z_n_gen = 0;
            
            for(int i = 0; i < v_Z_gen.size(); i++)
            {
                v_Z_gen[i]->clear();
            }
        }
        
        if(bool_stau1_gen)
        {
            stau1_n_gen = 0;
            
            for(int i = 0; i < v_stau1_gen.size(); i++)
            {
                v_stau1_gen[i]->clear();
            }
        }
        
        if(bool_stop1_gen)
        {
            stop1_n_gen = 0;
            
            for(int i = 0; i < v_stop1_gen.size(); i++)
            {
                v_stop1_gen[i]->clear();
            }
        }
        
        if(bool_chargino1_gen)
        {
            chargino1_n_gen = 0;
            
            for(int i = 0; i < v_chargino1_gen.size(); i++)
            {
                v_chargino1_gen[i]->clear();
            }
        }
        
        if(bool_jet_gen)
        {
            jet_n_gen = 0;
            
            for(int i = 0; i < v_jet_gen.size(); i++)
            {
                v_jet_gen[i]->clear();
            }
        }
        
        if(bool_MET_gen)
        {
            MET_E_gen = 0;
            MET_phi_gen = 0;
        }
        
        
        // RECO ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        if(bool_pileUp_reco)
        {
            pileUp_n_reco = 0;
        }
        
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
        if(h1_pileUp_mc)
        {
            delete h1_pileUp_mc;
        }
        
        if(h1_pileUp_data)
        {
            delete h1_pileUp_data;
        }
        
        if(h1_pileUp_data_systUp)
        {
            delete h1_pileUp_data_systUp;
        }
        
        if(h1_pileUp_data_systDown)
        {
            delete h1_pileUp_data_systDown;
        }
        
        delete T_gen;
        delete T_reco;
        
        delete file;
    }
    
    
    TH1F* Info::getPileUp(const char *fileName_pileUp, \
        const char *histName_pileUp)
    {
        TFile *file_pileUp = TFile::Open(fileName_pileUp, "READ");
        
        TH1F *hist = (TH1F*) file_pileUp->Get(histName_pileUp)->Clone();
        
        printf("Pileup histogram: %s \n", histName_pileUp);
        printf("Pileup file: %s \n", fileName_pileUp);
        fflush(stdout);
        
        // Detach object from TFile. Otherwise, the object is deleted once the TFile is closed/deleted.
        hist->SetDirectory(0);
        
        hist->Sumw2();
        hist->Scale(1.0 / hist->Integral());
        
        file_pileUp->Close();
        delete file_pileUp;
        
        return hist;
    }
    
    
    TH1F* Info::choosePileUpHist_data(Common::SYST_TYPE syst)
    {
        TH1F *h1_pileUp;
        
        switch(syst)
        {
            case Common::SYST_CENTRAL: 
                h1_pileUp = h1_pileUp_data;
                break;
            
            case Common::SYST_UP:
                h1_pileUp = h1_pileUp_data_systUp;
                break;
            
            case Common::SYST_DOWN:
                h1_pileUp = h1_pileUp_data_systDown;
                break;
            
            default:
                printf("Error in CustomInfo_mc::choosePileUpHist_data(...): Invalid systematic type provided.");
                exit(EXIT_FAILURE);
        }
        
        return h1_pileUp;
    }
    
    
    void Info::linkBranch_gen(const char *mode)
    {
        if(!strcmp(mode, "read"))
        {
            if(bool_genParam)
            {
                T_gen->SetBranchAddress("stop1_m_genParam", &stop1_m_genParam);
                T_gen->SetBranchAddress("neutralino1_m_genParam", &neutralino1_m_genParam);
                
                T_gen->SetBranchAddress("outgoingParton_n_gen", &outgoingParton_n_gen);
                
                for(int iScale = 0; iScale < v_scaleWeight.size(); iScale++)
                {
                    char branchName[Common::str_len];
                    sprintf(branchName, "scaleWeight_%d", iScale+1);
                    
                    T_gen->SetBranchAddress(branchName, &v_scaleWeight.at(iScale));
                }
            }
            
            if(bool_el_gen)
            {
                T_gen->SetBranchAddress("el_n_gen", &el_n_gen);
                T_gen->SetBranchAddress("el_E_gen", &v_el_E_gen);
                T_gen->SetBranchAddress("el_px_gen", &v_el_px_gen);
                T_gen->SetBranchAddress("el_py_gen", &v_el_py_gen);
                T_gen->SetBranchAddress("el_pz_gen", &v_el_pz_gen);
                T_gen->SetBranchAddress("el_isPrompt_gen", &v_el_isPrompt_gen);
            }
            
            if(bool_mu_gen)
            {
                T_gen->SetBranchAddress("mu_n_gen", &mu_n_gen);
                T_gen->SetBranchAddress("mu_E_gen", &v_mu_E_gen);
                T_gen->SetBranchAddress("mu_px_gen", &v_mu_px_gen);
                T_gen->SetBranchAddress("mu_py_gen", &v_mu_py_gen);
                T_gen->SetBranchAddress("mu_pz_gen", &v_mu_pz_gen);
                T_gen->SetBranchAddress("mu_isPrompt_gen", &v_mu_isPrompt_gen);
            }
            
            if(bool_tau_vis_gen)
            {
                T_gen->SetBranchAddress("tau_vis_n_gen", &tau_vis_n_gen);
                
                T_gen->SetBranchAddress("tau_E_gen", &v_tau_E_gen);
                T_gen->SetBranchAddress("tau_px_gen", &v_tau_px_gen);
                T_gen->SetBranchAddress("tau_py_gen", &v_tau_py_gen);
                T_gen->SetBranchAddress("tau_pz_gen", &v_tau_pz_gen);
                
                T_gen->SetBranchAddress("tau_vis_E_gen", &v_tau_vis_E_gen);
                T_gen->SetBranchAddress("tau_vis_px_gen", &v_tau_vis_px_gen);
                T_gen->SetBranchAddress("tau_vis_py_gen", &v_tau_vis_py_gen);
                T_gen->SetBranchAddress("tau_vis_pz_gen", &v_tau_vis_pz_gen);
            }
            
            if(bool_t_gen)
            { 
                T_gen->SetBranchAddress("t_n_gen", &t_n_gen);
                T_gen->SetBranchAddress("t_E_gen", &v_t_E_gen);
                T_gen->SetBranchAddress("t_px_gen", &v_t_px_gen);
                T_gen->SetBranchAddress("t_py_gen", &v_t_py_gen);
                T_gen->SetBranchAddress("t_pz_gen", &v_t_pz_gen);
            }
            
            if(bool_b_gen)
            { 
                T_gen->SetBranchAddress("b_n_gen", &b_n_gen);
                T_gen->SetBranchAddress("b_E_gen", &v_b_E_gen);
                T_gen->SetBranchAddress("b_px_gen", &v_b_px_gen);
                T_gen->SetBranchAddress("b_py_gen", &v_b_py_gen);
                T_gen->SetBranchAddress("b_pz_gen", &v_b_pz_gen);
            }
            
            if(bool_W_gen)
            {
                T_gen->SetBranchAddress("W_n_gen", &W_n_gen);
                T_gen->SetBranchAddress("W_E_gen", &v_W_E_gen);
                T_gen->SetBranchAddress("W_px_gen", &v_W_px_gen);
                T_gen->SetBranchAddress("W_py_gen", &v_W_py_gen);
                T_gen->SetBranchAddress("W_pz_gen", &v_W_pz_gen);
            }
            
            if(bool_Z_gen)
            {
                T_gen->SetBranchAddress("Z_n_gen", &Z_n_gen);
                T_gen->SetBranchAddress("Z_E_gen", &v_Z_E_gen);
                T_gen->SetBranchAddress("Z_px_gen", &v_Z_px_gen);
                T_gen->SetBranchAddress("Z_py_gen", &v_Z_py_gen);
                T_gen->SetBranchAddress("Z_pz_gen", &v_Z_pz_gen);
            }
            
            if(bool_stau1_gen)
            {
                T_gen->SetBranchAddress("stau1_n_gen", &stau1_n_gen);
                T_gen->SetBranchAddress("stau1_E_gen", &v_stau1_E_gen);
                T_gen->SetBranchAddress("stau1_px_gen", &v_stau1_px_gen);
                T_gen->SetBranchAddress("stau1_py_gen", &v_stau1_py_gen);
                T_gen->SetBranchAddress("stau1_pz_gen", &v_stau1_pz_gen);
            }
            
            if(bool_stop1_gen)
            {
                T_gen->SetBranchAddress("stop1_n_gen", &stop1_n_gen);
                T_gen->SetBranchAddress("stop1_E_gen", &v_stop1_E_gen);
                T_gen->SetBranchAddress("stop1_px_gen", &v_stop1_px_gen);
                T_gen->SetBranchAddress("stop1_py_gen", &v_stop1_py_gen);
                T_gen->SetBranchAddress("stop1_pz_gen", &v_stop1_pz_gen);
            }
            
            if(bool_chargino1_gen)
            {
                T_gen->SetBranchAddress("chargino1_n_gen", &chargino1_n_gen);
                T_gen->SetBranchAddress("chargino1_E_gen", &v_chargino1_E_gen);
                T_gen->SetBranchAddress("chargino1_px_gen", &v_chargino1_px_gen);
                T_gen->SetBranchAddress("chargino1_py_gen", &v_chargino1_py_gen);
                T_gen->SetBranchAddress("chargino1_pz_gen", &v_chargino1_pz_gen);
            }
            
            if(bool_jet_gen)
            {
                T_gen->SetBranchAddress("jet_n_gen", &jet_n_gen);
                T_gen->SetBranchAddress("jet_E_gen", &v_jet_E_gen);
                T_gen->SetBranchAddress("jet_px_gen", &v_jet_px_gen);
                T_gen->SetBranchAddress("jet_py_gen", &v_jet_py_gen);
                T_gen->SetBranchAddress("jet_pz_gen", &v_jet_pz_gen);
            }
            
            if(bool_MET_gen)
            {
                T_gen->SetBranchAddress("MET_E_gen", &MET_E_gen);
                T_gen->SetBranchAddress("MET_phi_gen", &MET_phi_gen);
            }
        }
        
        
        else if(!strcmp(mode, "write"))
        {
            if(bool_genParam)
            {
                T_gen->Branch("stop1_m_genParam", &stop1_m_genParam);
                T_gen->Branch("neutralino1_m_genParam", &neutralino1_m_genParam);
                
                T_gen->Branch("outgoingParton_n_gen", &outgoingParton_n_gen);
                
                for(int iScale = 0; iScale < v_scaleWeight.size(); iScale++)
                {
                    char branchName[Common::str_len];
                    sprintf(branchName, "scaleWeight_%d", iScale+1);
                    
                    T_gen->Branch(branchName, &v_scaleWeight.at(iScale));
                }
            }
            
            if(bool_el_gen)
            {
                T_gen->Branch("el_n_gen", &el_n_gen);
                T_gen->Branch("el_E_gen", &v_el_E_gen);
                T_gen->Branch("el_px_gen", &v_el_px_gen);
                T_gen->Branch("el_py_gen", &v_el_py_gen);
                T_gen->Branch("el_pz_gen", &v_el_pz_gen);
                T_gen->Branch("el_isPrompt_gen", &v_el_isPrompt_gen);
            }
            
            if(bool_mu_gen)
            {
                T_gen->Branch("mu_n_gen", &mu_n_gen);
                T_gen->Branch("mu_E_gen", &v_mu_E_gen);
                T_gen->Branch("mu_px_gen", &v_mu_px_gen);
                T_gen->Branch("mu_py_gen", &v_mu_py_gen);
                T_gen->Branch("mu_pz_gen", &v_mu_pz_gen);
                T_gen->Branch("mu_isPrompt_gen", &v_mu_isPrompt_gen);
            }
            
            if(bool_tau_vis_gen)
            {
                T_gen->Branch("tau_vis_n_gen", &tau_vis_n_gen);
                
                T_gen->Branch("tau_E_gen", &v_tau_E_gen);
                T_gen->Branch("tau_px_gen", &v_tau_px_gen);
                T_gen->Branch("tau_py_gen", &v_tau_py_gen);
                T_gen->Branch("tau_pz_gen", &v_tau_pz_gen);
                
                T_gen->Branch("tau_vis_E_gen", &v_tau_vis_E_gen);
                T_gen->Branch("tau_vis_px_gen", &v_tau_vis_px_gen);
                T_gen->Branch("tau_vis_py_gen", &v_tau_vis_py_gen);
                T_gen->Branch("tau_vis_pz_gen", &v_tau_vis_pz_gen);
            }
            
            if(bool_t_gen)
            { 
                T_gen->Branch("t_n_gen", &t_n_gen);
                T_gen->Branch("t_E_gen", &v_t_E_gen);
                T_gen->Branch("t_px_gen", &v_t_px_gen);
                T_gen->Branch("t_py_gen", &v_t_py_gen);
                T_gen->Branch("t_pz_gen", &v_t_pz_gen);
            }
            
            if(bool_b_gen)
            { 
                T_gen->Branch("b_n_gen", &b_n_gen);
                T_gen->Branch("b_E_gen", &v_b_E_gen);
                T_gen->Branch("b_px_gen", &v_b_px_gen);
                T_gen->Branch("b_py_gen", &v_b_py_gen);
                T_gen->Branch("b_pz_gen", &v_b_pz_gen);
            }
            
            if(bool_W_gen)
            {
                T_gen->Branch("W_n_gen", &W_n_gen);
                T_gen->Branch("W_E_gen", &v_W_E_gen);
                T_gen->Branch("W_px_gen", &v_W_px_gen);
                T_gen->Branch("W_py_gen", &v_W_py_gen);
                T_gen->Branch("W_pz_gen", &v_W_pz_gen);
            }
            
            if(bool_Z_gen)
            {
                T_gen->Branch("Z_n_gen", &Z_n_gen);
                T_gen->Branch("Z_E_gen", &v_Z_E_gen);
                T_gen->Branch("Z_px_gen", &v_Z_px_gen);
                T_gen->Branch("Z_py_gen", &v_Z_py_gen);
                T_gen->Branch("Z_pz_gen", &v_Z_pz_gen);
            }
            
            if(bool_stau1_gen)
            {
                T_gen->Branch("stau1_n_gen", &stau1_n_gen);
                T_gen->Branch("stau1_E_gen", &v_stau1_E_gen);
                T_gen->Branch("stau1_px_gen", &v_stau1_px_gen);
                T_gen->Branch("stau1_py_gen", &v_stau1_py_gen);
                T_gen->Branch("stau1_pz_gen", &v_stau1_pz_gen);
            }
            
            if(bool_stop1_gen)
            {
                T_gen->Branch("stop1_n_gen", &stop1_n_gen);
                T_gen->Branch("stop1_E_gen", &v_stop1_E_gen);
                T_gen->Branch("stop1_px_gen", &v_stop1_px_gen);
                T_gen->Branch("stop1_py_gen", &v_stop1_py_gen);
                T_gen->Branch("stop1_pz_gen", &v_stop1_pz_gen);
            }
            
            if(bool_chargino1_gen)
            {
                T_gen->Branch("chargino1_n_gen", &chargino1_n_gen);
                T_gen->Branch("chargino1_E_gen", &v_chargino1_E_gen);
                T_gen->Branch("chargino1_px_gen", &v_chargino1_px_gen);
                T_gen->Branch("chargino1_py_gen", &v_chargino1_py_gen);
                T_gen->Branch("chargino1_pz_gen", &v_chargino1_pz_gen);
            }
            
            if(bool_jet_gen)
            {
                T_gen->Branch("jet_n_gen", &jet_n_gen);
                T_gen->Branch("jet_E_gen", &v_jet_E_gen);
                T_gen->Branch("jet_px_gen", &v_jet_px_gen);
                T_gen->Branch("jet_py_gen", &v_jet_py_gen);
                T_gen->Branch("jet_pz_gen", &v_jet_pz_gen);
            }
            
            if(bool_MET_gen)
            {
                T_gen->Branch("MET_E_gen", &MET_E_gen);
                T_gen->Branch("MET_phi_gen", &MET_phi_gen);
            }
        }
    }
    
    
    void Info::linkBranch_reco(const char *option)
    {
        if(!strcmp(option, "read"))
        {
            if(bool_pileUp_reco)
            {
                T_reco->SetBranchAddress("pileUp_n_reco", &pileUp_n_reco);
            }
            
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
                
                T_reco->SetBranchAddress("jet_isISR_reco", &v_jet_isISR_reco);
                
                T_reco->SetBranchAddress("jet_partonFlavour_reco", &v_jet_partonFlavour_reco);
                T_reco->SetBranchAddress("jet_hadronFlavour_reco", &v_jet_hadronFlavour_reco);
                
                T_reco->SetBranchAddress("jet_JECcorr_reco", &v_jet_JECcorr_reco);
                T_reco->SetBranchAddress("jet_JECcorrUp_reco", &v_jet_JECcorrUp_reco);
                T_reco->SetBranchAddress("jet_JECcorrDown_reco", &v_jet_JECcorrDown_reco);
                
                T_reco->SetBranchAddress("jet_JERcorr_reco", &v_jet_JERcorr_reco);
                T_reco->SetBranchAddress("jet_JERcorrUp_reco", &v_jet_JERcorrUp_reco);
                T_reco->SetBranchAddress("jet_JERcorrDown_reco", &v_jet_JERcorrDown_reco);
                
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
            if(bool_pileUp_reco)
            {
                T_reco->Branch("pileUp_n_reco", &pileUp_n_reco);
            }
            
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
                
                T_reco->Branch("jet_isISR_reco", &v_jet_isISR_reco);
                
                T_reco->Branch("jet_partonFlavour_reco", &v_jet_partonFlavour_reco);
                T_reco->Branch("jet_hadronFlavour_reco", &v_jet_hadronFlavour_reco);
                
                T_reco->Branch("jet_JECcorr_reco", &v_jet_JECcorr_reco);
                T_reco->Branch("jet_JECcorrUp_reco", &v_jet_JECcorrUp_reco);
                T_reco->Branch("jet_JECcorrDown_reco", &v_jet_JECcorrDown_reco);
                
                T_reco->Branch("jet_JERcorr_reco", &v_jet_JERcorr_reco);
                T_reco->Branch("jet_JERcorrUp_reco", &v_jet_JERcorrUp_reco);
                T_reco->Branch("jet_JERcorrDown_reco", &v_jet_JERcorrDown_reco);
                
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
        
        T_gen->Write();
        T_reco->Write();
    }
    
    
    void Info::sort_pT(const char *opt)
    {
        std::vector <std::vector <double> *> *obj;
        
        // GEN object
        if(!strcmp(opt, "el"))
        {
            obj = &v_el_gen;
        }
        
        else if(!strcmp(opt, "mu"))
        {
            obj = &v_mu_gen;
        }
        
        else if(!strcmp(opt, "tau_vis"))
        {
            obj = &v_tau_vis_gen;
        }
        
        else if(!strcmp(opt, "t"))
        {
            obj = &v_t_gen;
        }
        
        else if(!strcmp(opt, "b"))
        {
            obj = &v_b_gen;
        }
        
        else if(!strcmp(opt, "W"))
        {
            obj = &v_W_gen;
        }
        
        else if(!strcmp(opt, "Z"))
        {
            obj = &v_Z_gen;
        }
        
        else if(!strcmp(opt, "stau1"))
        {
            obj = &v_stau1_gen;
        }
        
        else if(!strcmp(opt, "stop1"))
        {
            obj = &v_stop1_gen;
        }
        
        else if(!strcmp(opt, "chargino1"))
        {
            obj = &v_chargino1_gen;
        }
        
        else if(!strcmp(opt, "jet"))
        {
            obj = &v_jet_gen;
        }
        
        // Sort
        for(int iObj = 0; iObj < obj->at(0)->size(); iObj++)
        {
            CLHEP::HepLorentzVector iObj_4mom;
            
            iObj_4mom.setT(fabs(obj->at(0)->at(iObj)));
            iObj_4mom.setX(obj->at(1)->at(iObj));
            iObj_4mom.setY(obj->at(2)->at(iObj));
            iObj_4mom.setZ(obj->at(3)->at(iObj));
            
            for(int jObj = iObj+1; jObj < obj->at(0)->size(); jObj++)
            {
                CLHEP::HepLorentzVector jObj_4mom;
                
                jObj_4mom.setT(fabs(obj->at(0)->at(jObj)));
                jObj_4mom.setX(obj->at(1)->at(jObj));
                jObj_4mom.setY(obj->at(2)->at(jObj));
                jObj_4mom.setZ(obj->at(3)->at(jObj));
                
                // if iObj_pT < jObj_pT, then interchange
                if(iObj_4mom.perp() < jObj_4mom.perp())
                {
                    for(int iContent = 0; iContent < obj->size(); iContent++)
                    {
                        double temp = obj->at(iContent)->at(iObj);
                        obj->at(iContent)->at(iObj) = obj->at(iContent)->at(jObj);
                        obj->at(iContent)->at(jObj) = temp;
                    }
                }
            }
        }
    }
    
    
    void Info::checkSeparation(const char *opt1, const char *opt2, double dRcut, const char *del_opt)
    {
        std::vector <std::vector <double> *> *obj1, *obj2;
        
        // Object 1
        if(!strcmp(opt1, "el"))
        {
            obj1 = &v_el_reco;
        }
        
        else if(!strcmp(opt1, "mu"))
        {
            obj1 = &v_mu_reco;
        }
        
        else if(!strcmp(opt1, "tau"))
        {
            obj1 = &v_tau_reco;
        }
        
        else if(!strcmp(opt1, "jet"))
        {
            obj1 = &v_jet_reco;
        }
        
        // Object 2
        if(!strcmp(opt2, "el"))
        {
            obj2 = &v_el_gen;
        }
        
        else if(!strcmp(opt2, "mu"))
        {
            obj2 = &v_mu_gen;
        }
        
        else if(!strcmp(opt2, "tau_vis"))
        {
            obj2 = &v_tau_vis_gen;
        }
        
        else if(!strcmp(opt2, "jet"))
        {
            obj2 = &v_jet_gen;
        }
        
        
        // Check separation between obj1 and obj2
        for(int iObj1 = 0; iObj1 < obj1->at(0)->size(); iObj1++)
        {
            CLHEP::HepLorentzVector obj1_4mom;
            
            obj1_4mom.setT(fabs(obj1->at(0)->at(iObj1)));
            obj1_4mom.setX(obj1->at(1)->at(iObj1));
            obj1_4mom.setY(obj1->at(2)->at(iObj1));
            obj1_4mom.setZ(obj1->at(3)->at(iObj1));
            
            for(int iObj2 = 0; iObj2 < obj2->at(0)->size(); iObj2++)
            {
                CLHEP::HepLorentzVector obj2_4mom;
                
                obj2_4mom.setT(fabs(obj2->at(0)->at(iObj2)));
                obj2_4mom.setX(obj2->at(1)->at(iObj2));
                obj2_4mom.setY(obj2->at(2)->at(iObj2));
                obj2_4mom.setZ(obj2->at(3)->at(iObj2));
                
                double dR = obj1_4mom.deltaR(obj2_4mom);
                
                if(dR < dRcut)
                {
                    if(!strcmp(del_opt, "first"))
                    {
                        Common::deleteElement(obj1, iObj1);
                        
                        iObj1--;
                    }
                    
                    else if(!strcmp(del_opt, "second"))
                    {
                        Common::deleteElement(obj2, iObj2);
                    }
                    
                    else if(!strcmp(del_opt, "both"))
                    {
                        Common::deleteElement(obj1, iObj1);
                        Common::deleteElement(obj2, iObj2);
                        
                        iObj1--;
                    }
                    
                    break;
                }
            }
        }
    }
    
    
    bool Info::isGenMatched(CLHEP::HepLorentzVector object_4mom, const char *object, \
        double dR, double object_pTcut, double object_etaCut)
    {
        if(!strcmp(object, "tau_vis"))
        {
            for(int iTau = 0; iTau < tau_vis_n_gen; iTau++)
            {
                CLHEP::HepLorentzVector tau_4mom_gen;
                
                tau_4mom_gen.setT(fabs(v_tau_vis_E_gen->at(iTau)));
                tau_4mom_gen.setX(v_tau_vis_px_gen->at(iTau));
                tau_4mom_gen.setY(v_tau_vis_py_gen->at(iTau));
                tau_4mom_gen.setZ(v_tau_vis_pz_gen->at(iTau));
                
                if(object_pTcut > 0 && tau_4mom_gen.perp() < object_pTcut)
                {
                    continue;
                }
                
                if(object_etaCut < 999 && fabs(tau_4mom_gen.eta()) > object_etaCut)
                {
                    continue;
                }
                
                if(object_4mom.deltaR(tau_4mom_gen) < dR)
                {
                    return true;
                }
            }
            
            return false;
        }
        
        else if(!strcmp(object, "b"))
        {
            for(int ib = 0; ib < b_n_gen; ib++)
            {
                CLHEP::HepLorentzVector b_4mom_gen;
                
                b_4mom_gen.setT(fabs(v_b_E_gen->at(ib)));
                b_4mom_gen.setX(v_b_px_gen->at(ib));
                b_4mom_gen.setY(v_b_py_gen->at(ib));
                b_4mom_gen.setZ(v_b_pz_gen->at(ib));
                
                if(object_pTcut > 0 && b_4mom_gen.perp() < object_pTcut)
                {
                    continue;
                }
                
                if(object_etaCut < 999 && fabs(b_4mom_gen.eta()) > object_etaCut)
                {
                    continue;
                }
                
                if(object_4mom.deltaR(b_4mom_gen) < dR)
                {
                    return true;
                }
            }
            
            return false;
        }
    }
}

# ifndef CustomInfo_common_H
# define CustomInfo_common_H


# include <iostream>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTree.h>

# include "Common.h"


namespace CustomInfo_common
{
    class Info
    {
        public:
        
        
        TFile *file;
        
        // GEN ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        TTree *T_gen;
        
        bool
            bool_genParam,
            
            bool_el_gen,
            bool_mu_gen,
            bool_tau_vis_gen,
            
            bool_t_gen,
            bool_b_gen,
            
            bool_W_gen,
            bool_Z_gen,
            
            bool_stau1_gen,
            bool_stop1_gen,
            bool_chargino1_gen,
            
            bool_jet_gen,
            
            bool_MET_gen;
        
        int
            el_n_gen,
            mu_n_gen,
            tau_vis_n_gen,
            
            t_n_gen,
            b_n_gen,
            
            W_n_gen,
            Z_n_gen,
            
            stau1_n_gen,
            stop1_n_gen,
            chargino1_n_gen,
            
            jet_n_gen;
        
        double MET_E_gen, MET_phi_gen;
        
        double stop1_m_genParam;
        double neutralino1_m_genParam;
        
        int nScaleVariation;
        std::vector <double> v_scaleWeight;
        
        int outgoingParton_n_gen;
        
        std::vector <double> 
            *v_el_E_gen, *v_el_px_gen, *v_el_py_gen, *v_el_pz_gen,
            *v_el_isPrompt_gen,
            
            *v_mu_E_gen, *v_mu_px_gen, *v_mu_py_gen, *v_mu_pz_gen,
            *v_mu_isPrompt_gen,
            
            *v_tau_E_gen, *v_tau_px_gen, *v_tau_py_gen, *v_tau_pz_gen,
            *v_tau_vis_E_gen, *v_tau_vis_px_gen, *v_tau_vis_py_gen, *v_tau_vis_pz_gen,
            
            *v_t_E_gen, *v_t_px_gen, *v_t_py_gen, *v_t_pz_gen,
            *v_b_E_gen, *v_b_px_gen, *v_b_py_gen, *v_b_pz_gen,
            
            *v_W_E_gen, *v_W_px_gen, *v_W_py_gen, *v_W_pz_gen,
            *v_Z_E_gen, *v_Z_px_gen, *v_Z_py_gen, *v_Z_pz_gen,
            
            *v_stau1_E_gen, *v_stau1_px_gen, *v_stau1_py_gen, *v_stau1_pz_gen,
            *v_stop1_E_gen, *v_stop1_px_gen, *v_stop1_py_gen, *v_stop1_pz_gen,
            *v_chargino1_E_gen, *v_chargino1_px_gen, *v_chargino1_py_gen, *v_chargino1_pz_gen,
            
            *v_jet_E_gen, *v_jet_px_gen, *v_jet_py_gen, *v_jet_pz_gen;
        
        std::vector <std::vector <double> *>
            v_el_gen,
            v_mu_gen,
            v_tau_vis_gen,
            
            v_t_gen,
            v_b_gen,
            
            v_W_gen,
            v_Z_gen,
            
            v_stau1_gen,
            v_stop1_gen,
            v_chargino1_gen,
            
            v_jet_gen;
        
        
        // RECO ////////////////////////////////////////////////////////////////////////////////////////////////////
        
        TTree *T_reco;
        
        bool
            bool_pileUp_reco,
            bool_vertex_reco,
            
            bool_el_reco,
            bool_mu_reco,
            bool_tau_reco,
            
            bool_jet_reco,
            
            bool_MET_reco,
            
            bool_trigger;
        
        ULong64_t
            runNumber,
            eventNumber,
            luminosityNumber,
            bunchCrossingNumber;
        
        int
            pileUp_n_reco,
            vertex_n_reco,
            el_n_reco,
            mu_n_reco,
            tau_n_reco,
            jet_n_reco;
        
        double MET_E_reco, MET_phi_reco;
        double MET_JetResUp_E_reco, MET_JetResUp_phi_reco;
        double MET_JetResDown_E_reco, MET_JetResDown_phi_reco;
        double MET_JetEnUp_E_reco, MET_JetEnUp_phi_reco;
        double MET_JetEnDown_E_reco, MET_JetEnDown_phi_reco;
        double MET_UnclusteredEnUp_E_reco, MET_UnclusteredEnUp_phi_reco;
        double MET_UnclusteredEnDown_E_reco, MET_UnclusteredEnDown_phi_reco;
        
        double METFixEE2017_E_reco, METFixEE2017_phi_reco;
        double METFixEE2017_JetResUp_E_reco, METFixEE2017_JetResUp_phi_reco;
        double METFixEE2017_JetResDown_E_reco, METFixEE2017_JetResDown_phi_reco;
        double METFixEE2017_JetEnUp_E_reco, METFixEE2017_JetEnUp_phi_reco;
        double METFixEE2017_JetEnDown_E_reco, METFixEE2017_JetEnDown_phi_reco;
        double METFixEE2017_UnclusteredEnUp_E_reco, METFixEE2017_UnclusteredEnUp_phi_reco;
        double METFixEE2017_UnclusteredEnDown_E_reco, METFixEE2017_UnclusteredEnDown_phi_reco;
        
        std::map <std::string, std::map <Common::SYST_TYPE, std::map <std::string, double*> > > m_MET_reco_2016;
        std::map <std::string, std::map <Common::SYST_TYPE, std::map <std::string, double*> > > m_MET_reco_2017;
        std::map <std::string, std::map <std::string, std::map <Common::SYST_TYPE, std::map <std::string, double*> > > > m_MET_reco;
        
        //double isTriggerPassed_reco;
        
        
        // El-Mu trigger
        double isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v;
        double isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v;
        double isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v;
        double isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v;
        
        
        // Mu trigger
        double isTriggerPassed_HLT_IsoMu24_v;
        double isTriggerPassed_HLT_IsoTkMu24_v;
        double isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v;
        double isTriggerPassed_HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v;
        double isTriggerPassed_HLT_TkMu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v;
        
        double isTriggerPassed_HLT_IsoMu27_v;
        double isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v;
        double isTriggerPassed_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v;
        
        
        // Tau trigger
        double isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v;
        double isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v;
        
        double isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v;
        double isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v;
        double isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v;
        
        std::vector <double>
            *v_el_E_reco, *v_el_px_reco, *v_el_py_reco, *v_el_pz_reco,
           
            *v_el_dxy_reco, *v_el_dz_reco,
            *v_el_SIP3D_reco,
           
            *v_el_missingInnerHits_reco,
            *v_el_passConversionVeto_reco,
           
            *v_el_mvaEleIDSpring16GeneralPurposeV1wp80_reco,
            *v_el_mvaEleIDSpring16GeneralPurposeV1wp90_reco,
            
            *v_el_mvaEleIDFall17noIsoV2wp90_reco,
            *v_el_mvaEleIDFall17noIsoV2wp80_reco,
            
            *v_el_mvaEleIDFall17isoV2wp90_reco,
            *v_el_mvaEleIDFall17isoV2wp80_reco,
            
            *v_el_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR03_reco,
            *v_el_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR03_reco,
            *v_el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco,
            *v_el_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco;
            
        std::vector <double>
            *v_mu_E_reco, *v_mu_px_reco, *v_mu_py_reco, *v_mu_pz_reco,
            *v_mu_dxy_reco, *v_mu_dz_reco,
            *v_mu_SIP3D_reco,
           
            *v_mu_isGlobalMuon_reco,
            *v_mu_isTrackerMuon_reco,
           
            *v_mu_isLooseMuon_reco,
            *v_mu_isMediumMuon_reco,
            *v_mu_isTightMuon_reco,
           
            *v_mu_byLoosePFbasedCombinedRelativeDeltaBetaCorrdR04_reco,
            *v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco,
            *v_mu_byTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco,
            *v_mu_byVTightPFbasedCombinedRelativeDeltaBetaCorrdR04_reco;
            
        std::vector <double>
            *v_tau_E_reco, *v_tau_px_reco, *v_tau_py_reco, *v_tau_pz_reco,
            *v_tau_dxy_reco, *v_tau_dz_reco,
            
            *v_tau_byDecayModeFinding_reco,
            *v_tau_byDecayModeFindingNewDMs_reco,
            *v_tau_isTriggerMatched_reco,
            
            // 2016
            *v_tau_byLooseCombinedIsolationDeltaBetaCorr3Hits_reco,
            *v_tau_byMediumCombinedIsolationDeltaBetaCorr3Hits_reco,
            *v_tau_byTightCombinedIsolationDeltaBetaCorr3Hits_reco,
            
            *v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco,
            *v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco,
            *v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco,
            
            *v_tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco,
            *v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco,
            *v_tau_byMediumIsolationMVArun2v1DBoldDMwLT_reco,
            *v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco,
            *v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco,
            
            *v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco,
            *v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco,
            *v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco,
            *v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco,
            *v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco,
            
            *v_tau_againstElectronVLooseMVA6_reco,
            *v_tau_againstElectronLooseMVA6_reco,
            *v_tau_againstElectronMediumMVA6_reco,
            *v_tau_againstElectronTightMVA6_reco,
            *v_tau_againstElectronVTightMVA6_reco,
            
            *v_tau_againstMuonLoose3_reco,
            *v_tau_againstMuonTight3_reco,
            
            // 2017
            *v_tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco,
            *v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco,
            *v_tau_byMediumIsolationMVArun2017v2DBoldDMwLT2017_reco,
            *v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco,
            *v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco,
            
            *v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco,
            *v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco,
            *v_tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco,
            *v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco,
            *v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco,
            
            //Deep Tau Id
            *v_tau_byVVVLooseDeepTau2017v2p1VSjet_reco,
            *v_tau_byVVLooseDeepTau2017v2p1VSjet_reco,
            *v_tau_byVLooseDeepTau2017v2p1VSjet_reco,
            *v_tau_byLooseDeepTau2017v2p1VSjet_reco,
            *v_tau_byMediumDeepTau2017v2p1VSjet_reco,
            *v_tau_byTightDeepTau2017v2p1VSjet_reco,
            *v_tau_byVTightDeepTau2017v2p1VSjet_reco,
            *v_tau_byVVTightDeepTau2017v2p1VSjet_reco,
            
            *v_tau_byVVVLooseDeepTau2017v2p1VSe_reco,
            *v_tau_byVVLooseDeepTau2017v2p1VSe_reco,
            *v_tau_byVLooseDeepTau2017v2p1VSe_reco,
            *v_tau_byLooseDeepTau2017v2p1VSe_reco,
            *v_tau_byMediumDeepTau2017v2p1VSe_reco,
            *v_tau_byTightDeepTau2017v2p1VSe_reco,
            *v_tau_byVTightDeepTau2017v2p1VSe_reco,
            *v_tau_byVVTightDeepTau2017v2p1VSe_reco,
            
            *v_tau_byVLooseDeepTau2017v2p1VSmu_reco,
            *v_tau_byLooseDeepTau2017v2p1VSmu_reco,
            *v_tau_byMediumDeepTau2017v2p1VSmu_reco,
            *v_tau_byTightDeepTau2017v2p1VSmu_reco,
            
            *v_tau_decayMode_reco,
            
            *v_tau_chHad1_E_reco,
            *v_tau_chHad1_px_reco,
            *v_tau_chHad1_py_reco,
            *v_tau_chHad1_pz_reco;
            
        std::vector <double>
            *v_jet_E_reco, *v_jet_px_reco, *v_jet_py_reco, *v_jet_pz_reco,
            
            *v_jet_isISR_reco,
            
            *v_jet_partonFlavour_reco,
            *v_jet_hadronFlavour_reco,
            
            *v_jet_JECcorr_reco,
            *v_jet_JECcorrUp_reco,
            *v_jet_JECcorrDown_reco,
            
            *v_jet_JERcorr_reco,
            *v_jet_JERcorrUp_reco,
            *v_jet_JERcorrDown_reco,
            
            *v_jet_pfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
            *v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
            *v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
            *v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
            
            *v_jet_pfDeepCSVJetTags_reco,
            *v_jet_byLoosePfDeepCSVJetTags_reco,
            *v_jet_byMediumPfDeepCSVJetTags_reco,
            *v_jet_byTightPfDeepCSVJetTags_reco,
            
            *v_jet_pfDeepFlavourJetTags_reco,
            *v_jet_byLoosePfDeepFlavourJetTags_reco,
            *v_jet_byMediumPfDeepFlavourJetTags_reco,
            *v_jet_byTightPfDeepFlavourJetTags_reco;
        
        std::map <Common::SYST_TYPE, std::vector <double>*>
            m_JECcorr,
            m_JERcorr;
        
        std::vector <std::vector <double> *>
            v_el_reco,
            v_mu_reco,
            v_tau_reco,
            v_jet_reco;
        
        TH1F *h1_pileUp_mc,
            *h1_pileUp_data,
            *h1_pileUp_data_systUp,
            *h1_pileUp_data_systDown;
        
        TH1F *h1_vertex_n_mc,
            *h1_vertex_n_data;
        
        virtual void clear(){}
        
        virtual TH1F* getPileUp(const char *fileName_pileUp,
            const char *histName_pileUp){}
        
        virtual TH1F* choosePileUpHist_data(Common::SYST_TYPE syst){}
        
        virtual void linkBranch_gen(const char *mode){}
        
        virtual void linkBranch_reco(const char *mode){}
        
        virtual void freeMemory(){}
        
        virtual void writeData(){}
        
        virtual void sort_pT(const char *opt){}
        
        virtual void checkSeparation(const char *opt1, const char *opt2, double dRcut, const char *del_opt){}
        
        virtual bool isGenMatched(CLHEP::HepLorentzVector object_4mom, const char *object,
            double dR, double object_pTcut = 0, double object_etaCut = 999){}
    };
}


# endif

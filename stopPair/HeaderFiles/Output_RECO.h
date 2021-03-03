# ifndef Output_RECO_H
# define Output_RECO_H

# include "TH2F.h"

# include "Common.h"


namespace Output_RECO
{
    class Output
    {
        public:
        
        
        char
            *details,
            *nameAddon,
            *titleAddon;
        
        bool
            output_pileUp,
            output_el,
            output_mu,
            output_elMu,
            output_muMu,
            output_tau,
            output_tauTau,
            output_muTau,
            output_jet,
            output_b,
            output_MET;
        
        // Number of events
        TH1F *h1_nEvent;
        
        TH1F *h1_nEvent_2tau;
        TH1F *h1_nEvent_1tau1lep;
        TH1F *h1_nEvent_1tau1jet;
        TH1F *h1_nEvent_2lep;
        TH1F *h1_nEvent_1lep1jet;
        TH1F *h1_nEvent_2jet;
        
        // Pile-up
        TH1F *h1_pileUpReweightFactor;
        
        // Top pT reweighting
        TH1F *h1_topPtReweightFactor;
        TH2F *h2_top1PtReweightFactor_vs_pT;
        TH2F *h2_top2PtReweightFactor_vs_pT;
        
        // Z pT reweighting
        TH1F *h1_ZpTreweightFactor;
        TH2F *h2_ZpTreweightFactor_vs_m;
        TH2F *h2_ZpTreweightFactor_vs_pT;
        
        TH1F *h1_ZpTreweightFactor_afterBaseline;
        TH2F *h2_ZpTreweightFactor_vs_m_afterBaseline;
        TH2F *h2_ZpTreweightFactor_vs_pT_afterBaseline;
        
        // ISR reweighting
        TH1F *h1_ISRreweightFactor;
        
        // el
        TH1F
            *h1_el_n,
            *h1_lep1_el_pT,
            *h1_lep1_el_eta,
            *h1_lep1_el_phi,
            
            *h1_el_IdIsoSF;
        
        // mu
        TH1F
            *h1_mu_n,
            *h1_lep1_mu_pT,
            *h1_lep1_mu_eta,
            *h1_lep1_mu_phi,
            
            *h1_mu_IdIsoSF;
        
        std::vector <TH1F*>
            v_h1_mu_pT,
            v_h1_mu_eta,
            v_h1_mu_phi;
        
        // el-mu pair
        TH1F
            *h1_elMu_el_pT,
            *h1_elMu_el_eta,
            *h1_elMu_mu_pT,
            *h1_elMu_mu_eta,
            *h1_elMu_deltaPhi,
            *h1_elMu_m,
            *h1_elMu_MET_mT2,
            *h1_elMu_MET_Dzeta,
            *h1_elMu_jet_HT,
            
            *h1_elMuTrig_elSF,
            *h1_elMuTrig_muSF,
            *h1_elMuTrigSF;
        
        // mu-mu pair
        TH1F
            *h1_muMu_mu1_pT,
            *h1_muMu_mu1_eta,
            *h1_muMu_mu1_phi,
            
            *h1_muMu_mu2_pT,
            *h1_muMu_mu2_eta,
            *h1_muMu_mu2_phi,
            
            *h1_muMu_mu1_idIsoEff,
            *h1_muMu_mu2_idIsoEff,
            *h1_muMu_idIsoEff,
            
            *h1_muMu_deltaPhi,
            *h1_muMu_deltaEta,
            *h1_muMu_m,
            *h1_muMu_MET_mT2_lsp0,
            *h1_muMu_MET_Dzeta,
            
            *h1_muMu_jet_HT,
            
            *h1_muTriggerSF;
        
        TH2F
            *h2_ZpTreweightFactor_vs_muMu_pT,
            *h2_ZpTreweightFactor_vs_muMu_m;
        
        // tau
        TH1F
            *h1_tauIDefficiencyEventWeight,
            
            *h1_tau_n,
            
            *h1_tau_n_looseIso, *h1_tau_n_mediumIso, *h1_tau_n_tightIso,
            *h1_tau_pT_looseIso, *h1_tau_pT_mediumIso, *h1_tau_pT_tightIso,
            *h1_tau_eta_looseIso, *h1_tau_eta_mediumIso, *h1_tau_eta_tightIso;
        
        TH1F *h1_tau_pT;
        
        TH2F *h2_tau_pT_vs_DM;
        TH2F *h2_tau_eta_vs_DM;
        TH2F *h2_MET_vs_DM;
        TH2F *h2_tauTau_MET_mT2_vs_DM;
        TH2F *h2_tauTau_jet_HT_vs_DM;
        TH2F *h2_b_n_vs_DM;
        TH2F *h2_tau_nPV_vs_DM;
        
        TH3F *h3_tau_pT_eta_DM;
        
        std::vector <TH1F*>
            v_h1_tau_pT_gen,
            v_h1_tau_eta_gen,
            v_h1_tau_phi_gen,
            
            v_h1_tau_pT,
            v_h1_tau_eta,
            v_h1_tau_phi,
            v_h1_tau_m,
            
            v_h1_tau_MET_deltaPhi_gen,
            v_h1_tau_MET_mT_gen,
            
            v_h1_tau_MET_deltaPhi,
            v_h1_tau_MET_mT,
            
            v_h1_tau_chHad1_pT_by_tau_pT;
        
        TH1F *h1_MET_pZeta;
        
        // tau-tau pair
        TH1F
            *h1_tauTau_MET_mT2_gen,
            *h1_tauTau_jet_HT_gen,
            *h1_tauTau_jet_MHT_gen,
            
            *h1_tauTau_genMatched_n,
            
            *h1_tauTau_deltaPhi,
            *h1_tauTau_deltaEta,
            *h1_tauTau_deltaR,
            *h1_tauTau_m,
            *h1_tauTau_pT,
            *h1_tauTau_MET_mT2,
            *h1_tauTau_MET_mT2_lsp0,
            *h1_tauTau_MET_mT2_lsp0_unsmearedMET,
            *h1_tauTau_MET_mT2_lsp0_unsmearedMETphi,
            *h1_tauBtauB_MET_mT2_lsp0,
            
            *h1_tauTau_pZeta,
            *h1_tauTau_MET_pZeta,
            *h1_tauTau_MET_Dzeta,
            
            *h1_tauTau_b_HT,
            *h1_tauTau_b_MHT,
            *h1_tauTau_jet_HT,
            *h1_tauTau_jet_MHT,
            *h1_tauTau_b_HT_by_tauTau_jet_HT,
            *h1_tauTau_b_MHT_by_tauTau_jet_MHT,
            
            *h1_b_tauOverlap_n_by_b_n,
            *h1_nonBjet_tauOverlap_n_by_nonBjet_n,
            
            *h1_tauTau_promptFakeEventWeight,
            
            *h1_tauTauTrig_tau1SF,
            *h1_tauTauTrig_tau2SF,
            *h1_tauTauTrigSF;
        
        TH2F
            *h2_tauTau_MET_mT2_vs_MET_E,
            *h2_tauTau_MET_Dzeta_vs_MET_E,
            
            *h2_MET_vs_tau1_MET_deltaPhi,
            *h2_MET_vs_tau2_MET_deltaPhi,
            *h2_MET_vs_tauTau_deltaPhi,
            
            *h2_tauTau_MET_Dzeta_vs_tau1_MET_deltaPhi,
            *h2_tauTau_MET_Dzeta_vs_tau2_MET_deltaPhi,
            *h2_tauTau_MET_Dzeta_vs_tauTau_deltaPhi,
            
            *h2_tauTau_MET_mT2_vs_tau1_MET_deltaPhi,
            *h2_tauTau_MET_mT2_vs_tau2_MET_deltaPhi,
            *h2_tauTau_MET_mT2_vs_tauTau_deltaPhi,
            
            *h2_ZpTreweightFactor_vs_tauTau_pT,
            *h2_ZpTreweightFactor_vs_tauTau_m;
        
        // mu-tau pair
        TH1F
            *h1_muTau_mu_pT,
            *h1_muTau_mu_eta,
            *h1_muTau_mu_phi,
            *h1_muTau_tau_pT,
            *h1_muTau_tau_eta,
            *h1_muTau_tau_phi,
            *h1_muTau_tau_m,
            
            *h1_muTau_deltaPhi,
            *h1_muTau_deltaR,
            *h1_muTau_m,
            *h1_muTau_pT,
            *h1_muTau_MET_mT2,
            *h1_muTau_MET_mT2_lsp0,
            *h1_muBtauB_MET_mT2_lsp0,
            
            *h1_muTau_pZeta,
            *h1_muTau_MET_pZeta,
            *h1_muTau_MET_Dzeta,
            
            *h1_muTau_b_HT,
            *h1_muTau_b_MHT,
            *h1_muTau_jet_HT,
            *h1_muTau_jet_MHT,
            *h1_muTau_b_HT_by_muTau_jet_HT,
            *h1_muTau_b_MHT_by_muTau_jet_MHT;
        
        TH2F
            *h2_muTau_MET_mT2_vs_MET_E,
            *h2_muTau_MET_Dzeta_vs_MET_E,
            
            *h2_ZpTreweightFactor_vs_muTau_pT,
            *h2_ZpTreweightFactor_vs_muTau_m;
        
        // jet
        TH1F
            
            *h1_jet_n_gen,
            *h1_jet_HT_gen,
            *h1_jet_MHT_gen,
            
            *h1_jet_n,
            *h1_jet_HT,
            *h1_jet_MHT,
            *h1_jet_Meff,
            
            *h1_jet_tauOverlap_n,
            
            *h1_jet1_jet2_mT,
            *h1_nonBjet1_pT_by_jet_HT,
            
            *h1_jet_MET_deltaPhi_min,
            
            *h1_jet_MET_deltaPhi_jetEta0to2p4,
            *h1_jet_MET_deltaPhi_jetEta2p4to3p139,
            *h1_jet_MET_deltaPhi_jetEta0to5,
            *h1_jet_MET_deltaPhi_jetEta2p65to3p139,
            *h1_jet_MET_deltaPhi_jetEta0to2p65and3p139to5,
            
            *h1_jet_MET_deltaPhiMin_jetEta0to2p4,
            *h1_jet_MET_deltaPhiMin_jetEta2p4to3p139,
            *h1_jet_MET_deltaPhiMin_jetEta0to5,
            *h1_jet_MET_deltaPhiMin_jetEta2p65to3p139,
            *h1_jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5,
            
            *h1_jet_pT_eta2p1to2p4,
            *h1_jet_HT_eta2p1to2p4_by_jet_HT,
            
            *h1_jet_pT_eta2p1to3,
            *h1_jet_HT_eta2p1to3_by_jet_HT;
        
        TH2F *h2_jet_n_eta2p1to2p4_vs_jet_n;
        TH2F *h2_jet_n_eta2p1to3_vs_jet_n;
        
        std::vector <TH1F*>
            v_h1_jet_pT_gen,
            v_h1_jet_eta_gen,
            v_h1_jet_phi_gen,
            
            v_h1_jet_MET_deltaPhi_gen,
            
            
            v_h1_jet_pT,
            v_h1_jet_eta,
            v_h1_jet_phi,
            
            v_h1_jet_MET_deltaPhi;
        
        std::vector <TH1F*>
            v_h1_nonBjet_pT,
            v_h1_nonBjet_eta,
            v_h1_nonBjet_phi;
        
        // b
        TH1F
            *h1_bTaggingEventWeight_loose,
            *h1_bTaggingEventWeight_medium,
            *h1_bTaggingEventWeight_tight,
            
            *h1_b_n_loose, *h1_b_n_medium, *h1_b_n_tight,
            *h1_b_pT_loose, *h1_b_pT_medium, *h1_b_pT_tight,
            *h1_b_eta_loose, *h1_b_eta_medium, *h1_b_eta_tight,
            *h1_bb_MET_mT2_lsp0,
            
            *h1_b_n_by_jet_n,
            *h1_b1_pT_by_jet_HT,
            *h1_nonBjet1_pT_by_b1_pT;
        
        TH2F
            *h2_b_n_vs_jet_n_pT20,
            *h2_b_n_vs_jet_n_pT40,
            *h2_b_n_vs_jet_n_pT60,
            
            *h2_b_n_eta2p1to2p4_vs_b_n,
            *h2_b_n_eta2p1to3_vs_b_n;
        
        std::vector <TH1F*>
            v_h1_b_pT,
            v_h1_b_eta,
            v_h1_b_phi;
        
        // MET
        TH1F
            *h1_MET_E,
            *h1_MET_phi,
            
            *h1_MET_E_unsmeared,
            *h1_MET_phi_unsmeared,
            
            *h1_MET_E_gen,
            *h1_MET_phi_gen;
        
        // Cut-flow
        std::vector <std::string> v_cutFlow_name;
        std::vector <std::vector <double> > v_cutFlow;
        std::vector <TH1F*> v_h1_cutFlow;
        
        
        Output(std::vector <const char*> &v_option, const char *details = "");
        
        void addMuHist(int n);
        
        void addTauHist(int n);
        
        void addbHist(int n);
        
        void addJetHist(int n);
        
        void addNonBjetHist(int n);
        
        void addCutFlow(int n, std::string cutFlow_name);
        //std::vector <double>* getCutFlow(std::string cutFlow_name);
        TH1F* getCutFlow(std::string cutFlow_name);
        void incrementCutFlow(std::string cutFlow_name, int startIndex, std::vector <bool> v_selection);
        void incrementCutFlow(std::string cutFlow_name, int startIndex, std::vector <bool> v_selection, double eventWeight);
        void incrementCutFlow(std::string cutFlow_name, int startIndex, std::vector <bool> v_selection, std::vector <double> v_eventWeight);
        //void writeCutFlow(std::string cutFlow_name, const char *cutFlow_fileName);
        
        void updateBins(
            std::string cutFlowNameBase,
            std::vector <std:: vector <double> > vv_cut,
            std::vector <double> v_selectionVar,
            std::vector <double> v_eventWeight,
            int cutFlow_startIndex
        );
        
        void writeCutFlow(std::string cutFlow_name);
        
        void writeData();
        
        void freeMemory();
    };
}


# endif

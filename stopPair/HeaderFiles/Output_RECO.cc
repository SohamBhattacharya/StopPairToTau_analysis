# include <string>
# include <stdio.h>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TH1F.h>
# include <TH2F.h>

# include "Common.h"
# include "Output_RECO.h"


namespace Output_RECO
{
    Output::Output(std::vector <const char*> &v_option, const char *details)
    {
        this->details = (char*) malloc(Common::str_len * sizeof(char));
        nameAddon = (char*) malloc(Common::str_len * sizeof(char));
        titleAddon = (char*) malloc(Common::str_len * sizeof(char));
        
        sprintf(this->details, "%s", details);
        sprintf(nameAddon, "%s", "");
        sprintf(titleAddon, "%s", "");
        
        if(strcmp(details, ""))
        {
            sprintf(nameAddon, "_%s", details);
            sprintf(titleAddon, " [%s]", details);
        }
        
        
        output_pileUp = false;
        output_el = false;
        output_mu = false;
        output_elMu = false;
        output_muMu = false;
        output_tau = false;
        output_tauTau = false;
        output_muTau = false;
        output_jet = false;
        output_b = false;
        output_MET = false;
        
        
        for(int iOption = 0; iOption < v_option.size(); iOption++)
        {
            if(!strcmp(v_option[iOption], "PU"))
            {
                output_pileUp = true;
            }
            
            if(!strcmp(v_option[iOption], "el"))
            {
                output_el = true;
            }
            
            else if(!strcmp(v_option[iOption], "mu"))
            {
                output_mu = true;
            }
            
            else if(!strcmp(v_option[iOption], "elMu"))
            {
                output_elMu = true;
            }
            
            else if(!strcmp(v_option[iOption], "muMu"))
            {
                output_muMu = true;
            }
            
            else if(!strcmp(v_option[iOption], "tau"))
            {
                output_tau = true;
            }
            
            else if(!strcmp(v_option[iOption], "tauTau"))
            {
                output_tauTau = true;
            }
            
            else if(!strcmp(v_option[iOption], "muTau"))
            {
                output_muTau = true;
            }
            
            else if(!strcmp(v_option[iOption], "jet"))
            {
                output_jet = true;
            }
            
            else if(!strcmp(v_option[iOption], "b"))
            {
                output_b = true;
            }
            
            else if(!strcmp(v_option[iOption], "MET"))
            {
                output_MET = true;
            }
        }
        
        
        h1_nEvent = new TH1F(("nEvent" + std::string(nameAddon)).c_str(), ("nEvent" + std::string(titleAddon)).c_str(), 1, 0, 1);
        
        h1_nEvent_2tau     = new TH1F(("nEvent_2tau" + std::string(nameAddon)).c_str(), ("nEvent_2tau" + std::string(titleAddon)).c_str(), 1, 0, 1);
        h1_nEvent_1tau1lep = new TH1F(("nEvent_1tau1lep" + std::string(nameAddon)).c_str(), ("nEvent_1tau1lep" + std::string(titleAddon)).c_str(), 1, 0, 1);
        h1_nEvent_1tau1jet = new TH1F(("nEvent_1tau1jet" + std::string(nameAddon)).c_str(), ("nEvent_1tau1jet" + std::string(titleAddon)).c_str(), 1, 0, 1);
        h1_nEvent_2lep     = new TH1F(("nEvent_2lep" + std::string(nameAddon)).c_str(), ("nEvent_2lep" + std::string(titleAddon)).c_str(), 1, 0, 1);
        h1_nEvent_1lep1jet = new TH1F(("nEvent_1lep1jet" + std::string(nameAddon)).c_str(), ("nEvent_1lep1jet" + std::string(titleAddon)).c_str(), 1, 0, 1);
        h1_nEvent_2jet     = new TH1F(("nEvent_2jet" + std::string(nameAddon)).c_str(), ("nEvent_2jet" + std::string(titleAddon)).c_str(), 1, 0, 1);
        
        h1_topPtReweightFactor = new TH1F(("topPtReweightFactor" + std::string(nameAddon)).c_str(), ("Top p_{T} reweight factor" + std::string(titleAddon)).c_str(), 500, 0, 5);
        h2_top1PtReweightFactor_vs_pT = new TH2F(("top1PtReweightFactor_vs_pT" + std::string(nameAddon)).c_str(), ("Top1 p_{T} reweight factor vs p_{T}" + std::string(titleAddon)).c_str(), 200, 0.0, 2000.0, 500, 0.0, 5.0);;
        h2_top2PtReweightFactor_vs_pT = new TH2F(("top2PtReweightFactor_vs_pT" + std::string(nameAddon)).c_str(), ("Top2 p_{T} reweight factor vs p_{T}" + std::string(titleAddon)).c_str(), 200, 0.0, 2000.0, 500, 0.0, 5.0);;
        
        h1_ZpTreweightFactor = new TH1F(("ZpTreweightFactor" + std::string(nameAddon)).c_str(), ("Z p_{T} reweight factor" + std::string(titleAddon)).c_str(), 500, 0, 5);
        h2_ZpTreweightFactor_vs_m = new TH2F(("ZpTreweightFactor_vs_m" + std::string(nameAddon)).c_str(), ("Z p_{T} reweight factor vs m" + std::string(titleAddon)).c_str(), 50, 0.0, 500.0, 500, 0.0, 5.0);
        h2_ZpTreweightFactor_vs_pT = new TH2F(("ZpTreweightFactor_vs_pT" + std::string(nameAddon)).c_str(), ("Z p_{T} reweight factor vs p_{T}" + std::string(titleAddon)).c_str(), 200, 0.0, 2000.0, 500, 0.0, 5.0);
        
        h1_ZpTreweightFactor_afterBaseline = new TH1F(("ZpTreweightFactor_afterBaseline" + std::string(nameAddon)).c_str(), ("Z p_{T} reweight factor (after baseline sel.)" + std::string(titleAddon)).c_str(), 500, 0, 5);
        h2_ZpTreweightFactor_vs_m_afterBaseline = new TH2F(("ZpTreweightFactor_vs_m_afterBaseline" + std::string(nameAddon)).c_str(), ("Z p_{T} reweight factor vs m (after baseline sel.)" + std::string(titleAddon)).c_str(), 50, 0.0, 500.0, 500, 0.0, 5.0);
        h2_ZpTreweightFactor_vs_pT_afterBaseline = new TH2F(("ZpTreweightFactor_vs_pT_afterBaseline" + std::string(nameAddon)).c_str(), ("Z p_{T} reweight factor vs p_{T} (after baseline sel.)" + std::string(titleAddon)).c_str(), 200, 0.0, 2000.0, 500, 0.0, 5.0);
        
        h1_ISRreweightFactor = new TH1F(("ISRreweightFactor" + std::string(nameAddon)).c_str(), ("ISRreweightFactor " + std::string(titleAddon)).c_str(), 500, 0.0, 5.0);
        
        if(output_pileUp)
        {
            h1_pileUpReweightFactor = new TH1F(("pileUpReweightFactor_reco" + std::string(nameAddon)).c_str(), ("Pile-up re-weight factor RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
        }
        
        if(output_el)
        {
            h1_el_n = new TH1F(("el_n_reco" + std::string(nameAddon)).c_str(), ("n_{e} RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_lep1_el_pT = new TH1F(("lep1_el_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, lep1-e} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_lep1_el_eta = new TH1F(("lep1_el_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{lep1-e} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_lep1_el_phi = new TH1F(("lep1_el_phi_reco" + std::string(nameAddon)).c_str(), ("#phi_{lep1-e} RECO" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            
            h1_el_IdIsoSF = new TH1F(("el_IdIsoSF_reco" + std::string(nameAddon)).c_str(), ("e ID-Iso SF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
        }
        
        if(output_mu)
        {
            h1_mu_n = new TH1F(("mu_n_reco" + std::string(nameAddon)).c_str(), ("n_{#mu} RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_lep1_mu_pT = new TH1F(("lep1_mu_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, lep1-#mu} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_lep1_mu_eta = new TH1F(("lep1_mu_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{lep1-#mu} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_lep1_mu_phi = new TH1F(("lep1_mu_phi_reco" + std::string(nameAddon)).c_str(), ("#phi_{lep1-#mu} RECO" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            
            h1_mu_IdIsoSF = new TH1F(("mu_IdIsoSF_reco" + std::string(nameAddon)).c_str(), ("#mu ID-Iso SF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
        }
        
        if(output_elMu)
        {
            h1_elMu_el_pT = new TH1F(("elMu_el_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, e} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_elMu_el_eta = new TH1F(("elMu_el_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{e} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_elMu_mu_pT = new TH1F(("elMu_mu_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, #mu} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_elMu_mu_eta = new TH1F(("elMu_mu_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{#mu} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_elMu_deltaPhi = new TH1F(("elMu_deltaPhi_reco" + std::string(nameAddon)).c_str(), ("#Delta#phi_{e#mu} RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_elMu_m = new TH1F(("elMu_m_reco" + std::string(nameAddon)).c_str(), ("m_{e#mu} RECO" + std::string(titleAddon)).c_str(), 50, 0, 500);
            h1_elMu_MET_mT2 = new TH1F(("elMu_MET_mT2_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (e#mu-MET)} RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_elMu_MET_Dzeta = new TH1F(("elMu_MET_Dzeta_reco" + std::string(nameAddon)).c_str(), ("D_{#zeta (e#mu-MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            
            h1_elMu_jet_HT = new TH1F(("elMu_jet_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, e#mu-jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            h1_elMuTrig_elSF = new TH1F(("elMuTrig_elSF_reco" + std::string(nameAddon)).c_str(), ("elMuTrig_elSF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_elMuTrig_muSF = new TH1F(("elMuTrig_muSF_reco" + std::string(nameAddon)).c_str(), ("elMuTrig_muSF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_elMuTrigSF = new TH1F(("elMuTrigSF_reco" + std::string(nameAddon)).c_str(), ("elMuTrigSF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
        }
        
        if(output_muMu)
        {
            h1_muMu_mu1_pT = new TH1F(("muMu_mu1_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, #mu1} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muMu_mu1_eta = new TH1F(("muMu_mu1_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{#mu1} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_muMu_mu1_phi = new TH1F(("muMu_mu1_phi_reco" + std::string(nameAddon)).c_str(), ("#phi_{#mu1} RECO" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            
            h1_muMu_mu2_pT = new TH1F(("muMu_mu2_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, #mu2} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muMu_mu2_eta = new TH1F(("muMu_mu2_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{#mu2} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_muMu_mu2_phi = new TH1F(("muMu_mu2_phi_reco" + std::string(nameAddon)).c_str(), ("#phi_{#mu2} RECO" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            
            h1_muMu_mu1_idIsoEff = new TH1F(("muMu_mu1_idIsoEff" + std::string(nameAddon)).c_str(), ("#epsilon_{#mu1} RECO" + std::string(titleAddon)).c_str(), 1000, 0, 10);
            h1_muMu_mu2_idIsoEff = new TH1F(("muMu_mu2_idIsoEff" + std::string(nameAddon)).c_str(), ("#epsilon_{#mu2} RECO" + std::string(titleAddon)).c_str(), 1000, 0, 10);
            h1_muMu_idIsoEff = new TH1F(("muMu_idIsoEff" + std::string(nameAddon)).c_str(), ("#epsilon_{#mu1}#epsilon_{#mu2} RECO" + std::string(titleAddon)).c_str(), 1000, 0, 10);
            
            h1_muMu_deltaPhi = new TH1F(("muMu_deltaPhi_reco" + std::string(nameAddon)).c_str(), ("#Delta#phi_{#mu#mu} RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_muMu_deltaEta = new TH1F(("muMu_deltaEta_reco" + std::string(nameAddon)).c_str(), ("#Delta#eta_{#mu#mu} RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_muMu_m = new TH1F(("muMu_m_reco" + std::string(nameAddon)).c_str(), ("m_{#mu#mu} RECO" + std::string(titleAddon)).c_str(), 50, 0, 500);
            h1_muMu_MET_mT2_lsp0 = new TH1F(("muMu_MET_mT2_lsp0_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#mu#mu-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_muMu_MET_Dzeta = new TH1F(("muMu_MET_Dzeta_reco" + std::string(nameAddon)).c_str(), ("D_{#zeta (#mu#mu-MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            
            h1_muMu_jet_HT = new TH1F(("muMu_jet_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, #mu#mu-jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            h1_muTriggerSF = new TH1F(("muTriggerSF_reco" + std::string(nameAddon)).c_str(), ("muTriggerSF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            
            h2_ZpTreweightFactor_vs_muMu_pT = new TH2F(("ZpTreweightFactor_vs_muMu_pT_reco" + std::string(nameAddon)).c_str(), ("ZpTreweightFactor_vs_muMu_pT_reco" + std::string(titleAddon)).c_str(), 200, 0.0, 2000.0, 500, 0.0, 5.0);
            h2_ZpTreweightFactor_vs_muMu_m = new TH2F(("ZpTreweightFactor_vs_muMu_m_reco" + std::string(nameAddon)).c_str(), ("ZpTreweightFactor_vs_muMu_m_reco" + std::string(titleAddon)).c_str(), 50, 0.0, 500.0, 500, 0.0, 5.0);
        }
        
        if(output_tau)
        {
            h1_tauIDefficiencyEventWeight = new TH1F(("tauIDeventWeight_reco" + std::string(nameAddon)).c_str(), ("#tau ID efficiency event-weight RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            
            h1_tau_n = new TH1F(("tau_n_reco" + std::string(nameAddon)).c_str(), ("n_{#tau} RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            
            h1_tau_n_looseIso = new TH1F(("tau_n_looseIso_reco" + std::string(nameAddon)).c_str(), ("n_{#tau} looseIso RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_tau_n_mediumIso = new TH1F(("tau_n_mediumIso_reco" + std::string(nameAddon)).c_str(), ("n_{#tau} mediumIso RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_tau_n_tightIso = new TH1F(("tau_n_tightIso_reco" + std::string(nameAddon)).c_str(), ("n_{#tau} tightIso RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            
            h1_tau_pT_looseIso = new TH1F(("tau_pT_looseIso_reco" + std::string(nameAddon)).c_str(), ("p_{T, #tau} looseIso RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tau_pT_mediumIso = new TH1F(("tau_pT_mediumIso_reco" + std::string(nameAddon)).c_str(), ("p_{T, #tau} mediumIso RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tau_pT_tightIso = new TH1F(("tau_pT_tightIso_reco" + std::string(nameAddon)).c_str(), ("p_{T, #tau} tightIso RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            h1_tau_eta_looseIso = new TH1F(("tau_eta_looseIso_reco" + std::string(nameAddon)).c_str(), ("#eta_{#tau} looseIso RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_tau_eta_mediumIso = new TH1F(("tau_eta_mediumIso_reco" + std::string(nameAddon)).c_str(), ("#eta_{#tau} mediumIso RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_tau_eta_tightIso = new TH1F(("tau_eta_tightIso_reco" + std::string(nameAddon)).c_str(), ("#eta_{#tau} tightIso RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            
            h1_tau_pT = new TH1F(("tau_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, #tau} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            h2_tau_pT_vs_DM = new TH2F(("tau_pT_vs_DM_reco" + std::string(nameAddon)).c_str(), ("p_{T, #tau} vs. DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 200, 0.0, 2000.0);
            h2_tau_eta_vs_DM = new TH2F(("tau_eta_vs_DM_reco" + std::string(nameAddon)).c_str(), ("#eta_{#tau} vs. DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 120, -3.0, 3.0);
            h2_MET_vs_DM = new TH2F(("MET_vs_DM_reco" + std::string(nameAddon)).c_str(), ("MET_vs_DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 200, 0.0, 2000.0);
            h2_tauTau_MET_mT2_vs_DM = new TH2F(("tauTau_MET_mT2_vs_DM_reco" + std::string(nameAddon)).c_str(), ("tauTau_MET_mT2_vs_DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 100, 0, 1000);
            h2_tauTau_jet_HT_vs_DM = new TH2F(("tauTau_jet_HT_vs_DM_reco" + std::string(nameAddon)).c_str(), ("tauTau_jet_HT_vs_DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 200, 0.0, 2000.0);
            h2_b_n_vs_DM = new TH2F(("b_n_vs_DM_reco" + std::string(nameAddon)).c_str(), ("b_n_vs_DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 30, 0.0, 30.0);
            h2_tau_nPV_vs_DM = new TH2F(("tau_nPV_vs_DM_reco" + std::string(nameAddon)).c_str(), ("PU vs. DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 100, 0.0, 100.0);
            
            h3_tau_pT_eta_DM = new TH3F(("tau_pT_eta_DM" + std::string(nameAddon)).c_str(), ("p_{T, #tau} vs. #eta_{#tau} vs. DM RECO" + std::string(titleAddon)).c_str(), 30, 0.0, 30.0, 120, -3.0, 3.0, 200, 0, 2000);
        }
        
        if(output_tauTau)
        {
            h1_tauTau_MET_mT2_gen = new TH1F(("tauTau_MET_mT2_gen" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} GEN" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_tauTau_jet_HT_gen = new TH1F(("tauTau_jet_HT_gen" + std::string(nameAddon)).c_str(), ("H_{T, #tau#tau-jet} GEN" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tauTau_jet_MHT_gen = new TH1F(("tauTau_jet_MHT_gen" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, #tau#tau-jet} GEN" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            
            h1_tauTau_genMatched_n = new TH1F(("tauTau_genMatched_n_reco" + std::string(nameAddon)).c_str(), ("h1_tauTau_genMatched_n RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            
            h1_tauTau_m = new TH1F(("tauTau_m_reco" + std::string(nameAddon)).c_str(), ("m_{#tau#tau} RECO" + std::string(titleAddon)).c_str(), 50, 0, 500);
            h1_tauTau_pT = new TH1F(("tauTau_pT_reco" + std::string(nameAddon)).c_str(), ("p^{#tau#tau}_{T} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tauTau_deltaPhi = new TH1F(("tauTau_deltaPhi_reco" + std::string(nameAddon)).c_str(), ("#Delta#phi_{#tau#tau} RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_tauTau_deltaEta = new TH1F(("tauTau_deltaEta_reco" + std::string(nameAddon)).c_str(), ("#Delta#eta_{#tau#tau} RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_tauTau_deltaR = new TH1F(("tauTau_deltaR_reco" + std::string(nameAddon)).c_str(), ("#DeltaR_{#tau#tau} RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_tauTau_MET_mT2 = new TH1F(("tauTau_MET_mT2_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_tauTau_MET_mT2_lsp0 = new TH1F(("tauTau_MET_mT2_lsp0_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_tauTau_MET_mT2_lsp0_unsmearedMET = new TH1F(("tauTau_MET_mT2_lsp0_unsmearedMET" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_tauTau_MET_mT2_lsp0_unsmearedMETphi = new TH1F(("tauTau_MET_mT2_lsp0_unsmearedMETphi" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_tauBtauB_MET_mT2_lsp0 = new TH1F(("tauBtauB_MET_mT2_lsp0_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#taub-#taub-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            
            h1_MET_pZeta = new TH1F(("MET_pZeta_reco" + std::string(nameAddon)).c_str(), ("p_{#zeta (MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            h1_tauTau_pZeta = new TH1F(("tauTau_pZeta_reco" + std::string(nameAddon)).c_str(), ("p_{#zeta (#tau#tau)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            h1_tauTau_MET_pZeta = new TH1F(("tauTau_MET_pZeta_reco" + std::string(nameAddon)).c_str(), ("p_{#zeta (#tau#tau-MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            h1_tauTau_MET_Dzeta = new TH1F(("tauTau_MET_Dzeta_reco" + std::string(nameAddon)).c_str(), ("D_{#zeta (#tau#tau-MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            
            h2_tauTau_MET_mT2_vs_MET_E = new TH2F(("tauTau_MET_mT2_vs_MET_E_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} vs. MET_{E} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000, 100, 0, 1000);
            h2_tauTau_MET_Dzeta_vs_MET_E = new TH2F(("tauTau_MET_Dzeta_vs_MET_E_reco" + std::string(nameAddon)).c_str(), ("D_{#zeta (#tau#tau-MET)} vs. MET_{E} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000, 50, -500, 500);
            
            h2_MET_vs_tau1_MET_deltaPhi = new TH2F(("MET_vs_tau1_MET_deltaPhi" + std::string(nameAddon)).c_str(), ("MET vs. #Delta#phi(#tau1, MET) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 200, 0, 2000);
            h2_MET_vs_tau2_MET_deltaPhi = new TH2F(("MET_vs_tau2_MET_deltaPhi" + std::string(nameAddon)).c_str(), ("MET vs. #Delta#phi(#tau2, MET) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 200, 0, 2000);
            h2_MET_vs_tauTau_deltaPhi = new TH2F(("MET_vs_tauTau_deltaPhi" + std::string(nameAddon)).c_str(), ("MET vs. #Delta#phi(#tau1, #tau2) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 200, 0, 2000);
            
            h2_tauTau_MET_Dzeta_vs_tau1_MET_deltaPhi = new TH2F(("tauTau_MET_Dzeta_vs_tau1_MET_deltaPhi" + std::string(nameAddon)).c_str(), ("D_{#zeta (#tau#tau-MET)} vs. #Delta#phi(#tau1, MET) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 50, -500, 500);
            h2_tauTau_MET_Dzeta_vs_tau2_MET_deltaPhi = new TH2F(("tauTau_MET_Dzeta_vs_tau2_MET_deltaPhi" + std::string(nameAddon)).c_str(), ("D_{#zeta (#tau#tau-MET)} vs. #Delta#phi(#tau2, MET) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 50, -500, 500);
            h2_tauTau_MET_Dzeta_vs_tauTau_deltaPhi = new TH2F(("tauTau_MET_Dzeta_vs_tauTau_deltaPhi" + std::string(nameAddon)).c_str(), ("D_{#zeta (#tau#tau-MET)} vs. #Delta#phi(#tau1, #tau2) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 50, -500, 500);
            
            h2_tauTau_MET_mT2_vs_tau1_MET_deltaPhi = new TH2F(("tauTau_MET_mT2_vs_tau1_MET_deltaPhi" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} vs. #Delta#phi(#tau1, MET) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 100, 0, 1000);
            h2_tauTau_MET_mT2_vs_tau2_MET_deltaPhi = new TH2F(("tauTau_MET_mT2_vs_tau2_MET_deltaPhi" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} vs. #Delta#phi(#tau2, MET) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 100, 0, 1000);
            h2_tauTau_MET_mT2_vs_tauTau_deltaPhi = new TH2F(("tauTau_MET_mT2_vs_tauTau_deltaPhi" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau#tau-MET)} vs. #Delta#phi(#tau1, #tau2) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI, 100, 0, 1000);
            
            h2_ZpTreweightFactor_vs_tauTau_pT = new TH2F(("ZpTreweightFactor_vs_tauTau_pT_reco" + std::string(nameAddon)).c_str(), ("ZpTreweightFactor_vs_tauTau_pT_reco" + std::string(titleAddon)).c_str(), 200, 0.0, 2000.0, 500, 0.0, 5.0);
            h2_ZpTreweightFactor_vs_tauTau_m = new TH2F(("ZpTreweightFactor_vs_tauTau_m_reco" + std::string(nameAddon)).c_str(), ("ZpTreweightFactor_vs_tauTau_m_reco" + std::string(titleAddon)).c_str(), 50, 0.0, 500.0, 500, 0.0, 5.0);
            
            h1_tauTau_b_HT = new TH1F(("tauTau_b_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, #tau#tau-b} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tauTau_b_MHT = new TH1F(("tauTau_b_MHT_reco" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, #tau#tau-b} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tauTau_jet_HT = new TH1F(("tauTau_jet_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, #tau#tau-jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tauTau_jet_MHT = new TH1F(("tauTau_jet_MHT_reco" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, #tau#tau-jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_tauTau_b_HT_by_tauTau_jet_HT = new TH1F(("tauTau_b_HT_by_tauTau_jet_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, #tau#tau-b} / H_{T, #tau#tau-jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            h1_tauTau_b_MHT_by_tauTau_jet_MHT = new TH1F(("tauTau_b_MHT_by_tauTau_jet_MHT_reco" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, #tau#tau-b} / #slash{H}_{T, #tau#tau-jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            
            h1_tauTau_promptFakeEventWeight = new TH1F(("tauTau_promptFakeEventWeight_reco" + std::string(nameAddon)).c_str(), ("tauTau_promptFakeEventWeight RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            
            h1_tauTauTrig_tau1SF = new TH1F(("tauTauTrig_tau1SF" + std::string(nameAddon)).c_str(), ("tauTauTrig_tau1SF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_tauTauTrig_tau2SF = new TH1F(("tauTauTrig_tau2SF" + std::string(nameAddon)).c_str(), ("tauTauTrig_tau2SF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_tauTauTrigSF = new TH1F(("tauTauTrigSF" + std::string(nameAddon)).c_str(), ("tauTauTrigSF RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
        }
        
        if(output_muTau)
        {
            h1_muTau_mu_pT = new TH1F(("muTau_mu_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, #mu} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muTau_mu_eta = new TH1F(("muTau_mu_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{#mu} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_muTau_mu_phi = new TH1F(("muTau_mu_phi_reco" + std::string(nameAddon)).c_str(), ("#phi_{#mu} RECO" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            h1_muTau_tau_pT = new TH1F(("muTau_tau_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, #tau} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muTau_tau_eta = new TH1F(("muTau_tau_eta_reco" + std::string(nameAddon)).c_str(), ("#eta_{#tau} RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_muTau_tau_phi = new TH1F(("muTau_tau_phi_reco" + std::string(nameAddon)).c_str(), ("#phi_{#tau} RECO" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            h1_muTau_tau_m = new TH1F(("muTau_tau_m_reco" + std::string(nameAddon)).c_str(), ("m_{#tau} RECO" + std::string(titleAddon)).c_str(), 25, 0, 5);
            
            h1_muTau_m = new TH1F(("muTau_m_reco" + std::string(nameAddon)).c_str(), ("m_{#mu#tau} RECO" + std::string(titleAddon)).c_str(), 50, 0, 500);
            h1_muTau_pT = new TH1F(("muTau_pT_reco" + std::string(nameAddon)).c_str(), ("p^{#mu#tau}_{T} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muTau_deltaPhi = new TH1F(("muTau_deltaPhi_reco" + std::string(nameAddon)).c_str(), ("#Delta#phi_{#mu#tau} RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_muTau_deltaR = new TH1F(("muTau_deltaR_reco" + std::string(nameAddon)).c_str(), ("#DeltaR_{#mu#tau} RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_muTau_MET_mT2 = new TH1F(("muTau_MET_mT2_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#mu#tau-MET)} RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_muTau_MET_mT2_lsp0 = new TH1F(("muTau_MET_mT2_lsp0_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#mu#tau-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            h1_muBtauB_MET_mT2_lsp0 = new TH1F(("muBtauB_MET_mT2_lsp0_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#mub-#taub-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            
            h1_MET_pZeta = new TH1F(("MET_pZeta_reco" + std::string(nameAddon)).c_str(), ("p_{#zeta (MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            h1_muTau_pZeta = new TH1F(("muTau_pZeta_reco" + std::string(nameAddon)).c_str(), ("p_{#zeta (#mu#tau)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            h1_muTau_MET_pZeta = new TH1F(("muTau_MET_pZeta_reco" + std::string(nameAddon)).c_str(), ("p_{#zeta (#mu#tau-MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            h1_muTau_MET_Dzeta = new TH1F(("muTau_MET_Dzeta_reco" + std::string(nameAddon)).c_str(), ("D_{#zeta (#mu#tau-MET)} RECO" + std::string(titleAddon)).c_str(), 50, -500, 500);
            
            h2_muTau_MET_mT2_vs_MET_E = new TH2F(("muTau_MET_mT2_vs_MET_E_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (#mu#tau-MET)} vs. MET_{E} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000, 100, 0, 1000);
            h2_muTau_MET_Dzeta_vs_MET_E = new TH2F(("muTau_MET_Dzeta_vs_MET_E_reco" + std::string(nameAddon)).c_str(), ("D_{#zeta (#mu#tau-MET)} vs. MET_{E} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000, 50, -500, 500);
            
            h2_ZpTreweightFactor_vs_muTau_pT = new TH2F(("ZpTreweightFactor_vs_muTau_pT_reco" + std::string(nameAddon)).c_str(), ("ZpTreweightFactor_vs_muTau_pT_reco" + std::string(titleAddon)).c_str(), 200, 0.0, 2000.0, 500, 0.0, 5.0);
            h2_ZpTreweightFactor_vs_muTau_m = new TH2F(("ZpTreweightFactor_vs_muTau_m_reco" + std::string(nameAddon)).c_str(), ("ZpTreweightFactor_vs_muTau_m_reco" + std::string(titleAddon)).c_str(), 50, 0.0, 500.0, 500, 0.0, 5.0);
            
            h1_muTau_b_HT = new TH1F(("muTau_b_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, #mu#tau-b} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muTau_b_MHT = new TH1F(("muTau_b_MHT_reco" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, #mu#tau-b} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muTau_jet_HT = new TH1F(("muTau_jet_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, #mu#tau-jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muTau_jet_MHT = new TH1F(("muTau_jet_MHT_reco" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, #mu#tau-jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_muTau_b_HT_by_muTau_jet_HT = new TH1F(("muTau_b_HT_by_muTau_jet_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, #mu#tau-b} / H_{T, #mu#tau-jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            h1_muTau_b_MHT_by_muTau_jet_MHT = new TH1F(("muTau_b_MHT_by_muTau_jet_MHT_reco" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, #mu#tau-b} / #slash{H}_{T, #mu#tau-jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
        }
        
        if(output_jet)
        {
            h1_jet_n_gen = new TH1F(("jet_n_gen" + std::string(nameAddon)).c_str(), ("n_{jet} GEN" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_jet_HT_gen = new TH1F(("jet_HT_gen" + std::string(nameAddon)).c_str(), ("H_{T, jet} GEN" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_jet_MHT_gen = new TH1F(("jet_MHT_gen" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, jet} GEN" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            
            h1_jet_n = new TH1F(("jet_n_reco" + std::string(nameAddon)).c_str(), ("n_{jet} RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_jet_HT = new TH1F(("jet_HT_reco" + std::string(nameAddon)).c_str(), ("H_{T, jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_jet_MHT = new TH1F(("jet_MHT_reco" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_jet_Meff = new TH1F(("jet_Meff_reco" + std::string(nameAddon)).c_str(), ("M_{eff, jet} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            h1_jet_tauOverlap_n = new TH1F(("jet_tauOverlap_n_reco" + std::string(nameAddon)).c_str(), ("n^{#tau-overlap}_{jet} RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            
            h1_jet1_jet2_mT = new TH1F(("jet1_jet2_mT_reco" + std::string(nameAddon)).c_str(), ("m_{T, j1j2} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_nonBjet1_pT_by_jet_HT = new TH1F(("nonBjet1_pT_by_jet_HT_reco" + std::string(nameAddon)).c_str(), ("p_{T, non-b j1} / H_{T, jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            
            h1_nonBjet_tauOverlap_n_by_nonBjet_n = new TH1F(("nonBjet_tauOverlap_n_by_nonBjet_n_reco" + std::string(nameAddon)).c_str(), ("n^{#tau overlap}_{non-b jet} / n_{non-b jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            
            h1_jet_MET_deltaPhi_min = new TH1F(("jet_MET_deltaPhi_min_reco" + std::string(nameAddon)).c_str(), ("min(#Delta#phi_{jet-MET}) RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            
            h1_jet_MET_deltaPhi_jetEta0to2p4 = new TH1F(("jet_MET_deltaPhi_jetEta0to2p4_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhi_jetEta0to2p4 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhi_jetEta2p4to3p139 = new TH1F(("jet_MET_deltaPhi_jetEta2p4to3p139_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhi_jetEta2p4to3p139 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhi_jetEta0to5 = new TH1F(("jet_MET_deltaPhi_jetEta0to5_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhi_jetEta0to5 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhi_jetEta2p65to3p139 = new TH1F(("jet_MET_deltaPhi_jetEta2p65to3p139_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhi_jetEta2p65to3p139 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhi_jetEta0to2p65and3p139to5 = new TH1F(("jet_MET_deltaPhi_jetEta0to2p65and3p139to5_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhi_jetEta0to2p65and3p139to5 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            
            h1_jet_MET_deltaPhiMin_jetEta0to2p4 = new TH1F(("jet_MET_deltaPhiMin_jetEta0to2p4_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhiMin_jetEta0to2p4 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhiMin_jetEta2p4to3p139 = new TH1F(("jet_MET_deltaPhiMin_jetEta2p4to3p139_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhiMin_jetEta2p4to3p139 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhiMin_jetEta0to5 = new TH1F(("jet_MET_deltaPhiMin_jetEta0to5_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhiMin_jetEta0to5 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhiMin_jetEta2p65to3p139 = new TH1F(("jet_MET_deltaPhiMin_jetEta2p65to3p139_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhiMin_jetEta2p65to3p139 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            h1_jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5 = new TH1F(("jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5_reco" + std::string(nameAddon)).c_str(), ("jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5 RECO" + std::string(titleAddon)).c_str(), 100, -2*M_PI, 2*M_PI);
            
            
            h1_jet_pT_eta2p1to2p4 = new TH1F(("jet_pT_eta2p1to2p4_reco" + std::string(nameAddon)).c_str(), ("jet_pT_eta2p1to2p4 RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_jet_HT_eta2p1to2p4_by_jet_HT = new TH1F(("jet_HT_eta2p1to2p4_by_jet_HT_reco" + std::string(nameAddon)).c_str(), ("jet_HT_eta2p1to2p4_by_jet_HT RECO" + std::string(titleAddon)).c_str(), 100, 0, 1);
            
            h1_jet_pT_eta2p1to3 = new TH1F(("jet_pT_eta2p1to3_reco" + std::string(nameAddon)).c_str(), ("jet_pT_eta2p1to3 RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_jet_HT_eta2p1to3_by_jet_HT = new TH1F(("jet_HT_eta2p1to3_by_jet_HT_reco" + std::string(nameAddon)).c_str(), ("jet_HT_eta2p1to3_by_jet_HT RECO" + std::string(titleAddon)).c_str(), 100, 0, 1);
            
            h2_jet_n_eta2p1to2p4_vs_jet_n = new TH2F(("jet_n_eta2p1to2p4_vs_jet_n_reco" + std::string(nameAddon)).c_str(), ("jet_n_eta2p1to2p4_vs_jet_n RECO" + std::string(titleAddon)).c_str(), 10, 0, 10, 10, 0, 10);
            h2_jet_n_eta2p1to3_vs_jet_n = new TH2F(("jet_n_eta2p1to3_vs_jet_n_reco" + std::string(nameAddon)).c_str(), ("jet_n_eta2p1to3_vs_jet_n RECO" + std::string(titleAddon)).c_str(), 10, 0, 10, 10, 0, 10);
        }
        
        if(output_b)
        {
            h1_bTaggingEventWeight_loose = new TH1F(("bTaggingEventWeight_loose_reco" + std::string(nameAddon)).c_str(), ("b-tagging event-weight loose RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_bTaggingEventWeight_medium = new TH1F(("bTaggingEventWeight_medium_reco" + std::string(nameAddon)).c_str(), ("b-tagging event-weight medium RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_bTaggingEventWeight_tight = new TH1F(("bTaggingEventWeight_tight_reco" + std::string(nameAddon)).c_str(), ("b-tagging event-weight tight RECO" + std::string(titleAddon)).c_str(), 100, 0, 10);
            
            h1_b_n_loose = new TH1F(("b_n_loose_reco" + std::string(nameAddon)).c_str(), ("n_{b jet} loose RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_b_n_medium = new TH1F(("b_n_medium_reco" + std::string(nameAddon)).c_str(), ("n_{b jet} medium RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            h1_b_n_tight = new TH1F(("b_n_tight_reco" + std::string(nameAddon)).c_str(), ("n_{b jet} tight RECO" + std::string(titleAddon)).c_str(), 10, 0, 10);
            
            h1_b_pT_loose = new TH1F(("b_pT_loose_reco" + std::string(nameAddon)).c_str(), ("p_{T, b} loose RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_b_pT_medium = new TH1F(("b_pT_medium_reco" + std::string(nameAddon)).c_str(), ("p_{T, b} medium RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_b_pT_tight = new TH1F(("b_pT_tight_reco" + std::string(nameAddon)).c_str(), ("p_{T, b} tight RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            
            h1_b_eta_loose = new TH1F(("b_eta_loose_reco" + std::string(nameAddon)).c_str(), ("eta_{b} loose RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_b_eta_medium = new TH1F(("b_eta_medium_reco" + std::string(nameAddon)).c_str(), ("eta_{b} medium RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            h1_b_eta_tight = new TH1F(("b_eta_tight_reco" + std::string(nameAddon)).c_str(), ("eta_{b} tight RECO" + std::string(titleAddon)).c_str(), 60, -3, 3);
            
            h1_bb_MET_mT2_lsp0 = new TH1F(("bb_MET_mT2_lsp0_reco" + std::string(nameAddon)).c_str(), ("m_{T2 (bb-MET)} (lsp0) RECO" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            
            h1_b_tauOverlap_n_by_b_n = new TH1F(("b_tauOverlap_n_by_b_n_reco" + std::string(nameAddon)).c_str(), ("n^{#tau overlap}_{b} / n_{b} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            
            h1_b1_pT_by_jet_HT = new TH1F(("b1_pT_by_jet_HT_reco" + std::string(nameAddon)).c_str(), ("p_{T, b1} / H_{T, jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            h1_nonBjet1_pT_by_b1_pT = new TH1F(("nonBjet1_pT_by_b1_pT_reco" + std::string(nameAddon)).c_str(), ("p_{T, non-b jet1} / p_{T, b1} RECO" + std::string(titleAddon)).c_str(), 500, 0, 10);
            
            h1_b_n_by_jet_n = new TH1F(("b_n_by_jet_n_reco" + std::string(nameAddon)).c_str(), ("n_{b} / n_{jet} RECO" + std::string(titleAddon)).c_str(), 100, 0, 2);
            
            h2_b_n_vs_jet_n_pT20 = new TH2F(("b_n_vs_jet_n_pT20_reco" + std::string(nameAddon)).c_str(), ("n_{b} vs. n_{jet} (p_{T} > 20 GeV) RECO" + std::string(titleAddon)).c_str(), 10, 0, 10, 10, 0, 10);
            h2_b_n_vs_jet_n_pT40 = new TH2F(("b_n_vs_jet_n_pT40_reco" + std::string(nameAddon)).c_str(), ("n_{b} vs. n_{jet} (p_{T} > 40 GeV) RECO" + std::string(titleAddon)).c_str(), 10, 0, 10, 10, 0, 10);
            h2_b_n_vs_jet_n_pT60 = new TH2F(("b_n_vs_jet_n_pT60_reco" + std::string(nameAddon)).c_str(), ("n_{b} vs. n_{jet} (p_{T} > 60 GeV) RECO" + std::string(titleAddon)).c_str(), 10, 0, 10, 10, 0, 10);
            
            h2_b_n_eta2p1to2p4_vs_b_n = new TH2F(("b_n_eta2p1to2p4_vs_b_n_reco" + std::string(nameAddon)).c_str(), ("b_n_eta2p1to2p4_vs_b_n RECO" + std::string(titleAddon)).c_str(), 10, 0, 10, 10, 0, 10);
            h2_b_n_eta2p1to3_vs_b_n = new TH2F(("b_n_eta2p1to3_vs_b_n_reco" + std::string(nameAddon)).c_str(), ("b_n_eta2p1to3_vs_b_n RECO" + std::string(titleAddon)).c_str(), 10, 0, 10, 10, 0, 10);
        }
        
        if(output_MET)
        {
            h1_MET_E = new TH1F(("MET_E_reco" + std::string(nameAddon)).c_str(), ("MET_{E} RECO" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_MET_phi = new TH1F(("MET_phi_reco" + std::string(nameAddon)).c_str(), ("MET_{#phi} RECO" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            
            h1_MET_E_unsmeared = new TH1F(("MET_E_reco_unsmeared" + std::string(nameAddon)).c_str(), ("MET_{E} RECO unsmeared" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_MET_phi_unsmeared = new TH1F(("MET_phi_reco_unsmeared" + std::string(nameAddon)).c_str(), ("MET_{#phi} RECO unsmeared" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            
            h1_MET_E_gen = new TH1F(("MET_E_gen" + std::string(nameAddon)).c_str(), ("MET_{E} GEN" + std::string(titleAddon)).c_str(), 200, 0, 2000);
            h1_MET_phi_gen = new TH1F(("MET_phi_gen" + std::string(nameAddon)).c_str(), ("MET_{#phi} GEN" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
        }
    }
    
    
    void Output::addMuHist(int n)
    {
        for(int i = v_h1_mu_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "mu%d_pT_reco%s", i+1, nameAddon);
            sprintf(title, "p_{T, mu%d} RECO%s", i+1, titleAddon);
            v_h1_mu_pT.push_back(new TH1F(name, title, 200, 0, 2000));
            
            sprintf(name, "mu%d_eta_reco%s", i+1, nameAddon);
            sprintf(title, "#eta_{mu%d} RECO%s", i+1, titleAddon);
            v_h1_mu_eta.push_back(new TH1F(name, title, 60, -3, 3));
            
            sprintf(name, "mu%d_phi_reco%s", i+1, nameAddon);
            sprintf(title, "#phi_{mu%d} RECO%s", i+1, titleAddon);
            v_h1_mu_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
        }
    }
    
    
    void Output::addTauHist(int n)
    {
        for(int i = v_h1_tau_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "tau%d_pT_gen%s", i+1, nameAddon);
            sprintf(title, "p_{T, #tau%d} GEN%s", i+1, titleAddon);
            v_h1_tau_pT_gen.push_back(new TH1F(name, title, 200, 0, 2000));
            
            sprintf(name, "tau%d_eta_gen%s", i+1, nameAddon);
            sprintf(title, "#eta_{#tau%d} GEN%s", i+1, titleAddon);
            v_h1_tau_eta_gen.push_back(new TH1F(name, title, 60, -3, 3));
            
            sprintf(name, "tau%d_phi_gen%s", i+1, nameAddon);
            sprintf(title, "#phi_{#tau%d} GEN%s", i+1, titleAddon);
            v_h1_tau_phi_gen.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
            
            sprintf(name, "tau%d_MET_deltaPhi_gen%s", i+1, nameAddon);
            sprintf(title, "#Delta#phi_{#tau%d-MET} GEN%s", i+1, titleAddon);
            v_h1_tau_MET_deltaPhi_gen.push_back(new TH1F(name, title, 100, -2*M_PI, 2*M_PI));
            
            sprintf(name, "tau%d_MET_mT_gen%s", i+1, nameAddon);
            sprintf(title, "m^{#tau%d-MET}_{T} GEN%s", i+1, titleAddon);
            v_h1_tau_MET_mT_gen.push_back(new TH1F(name, title, 100, 0, 1000));
            
            
            sprintf(name, "tau%d_pT_reco%s", i+1, nameAddon);
            sprintf(title, "p_{T, #tau%d} RECO%s", i+1, titleAddon);
            v_h1_tau_pT.push_back(new TH1F(name, title, 200, 0, 2000));
            
            sprintf(name, "tau%d_eta_reco%s", i+1, nameAddon);
            sprintf(title, "#eta_{#tau%d} RECO%s", i+1, titleAddon);
            v_h1_tau_eta.push_back(new TH1F(name, title, 60, -3, 3));
            
            sprintf(name, "tau%d_phi_reco%s", i+1, nameAddon);
            sprintf(title, "#phi_{#tau%d} RECO%s", i+1, titleAddon);
            v_h1_tau_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
            
            sprintf(name, "tau%d_m_reco%s", i+1, nameAddon);
            sprintf(title, "m_{#tau%d} RECO%s", i+1, titleAddon);
            v_h1_tau_m.push_back(new TH1F(name, title, 25, 0, 5));
            
            sprintf(name, "tau%d_MET_deltaPhi_reco%s", i+1, nameAddon);
            sprintf(title, "#Delta#phi_{#tau%d-MET} RECO%s", i+1, titleAddon);
            v_h1_tau_MET_deltaPhi.push_back(new TH1F(name, title, 100, -2*M_PI, 2*M_PI));
            
            sprintf(name, "tau%d_MET_mT_reco%s", i+1, nameAddon);
            sprintf(title, "m^{#tau%d-MET}_{T} RECO%s", i+1, titleAddon);
            v_h1_tau_MET_mT.push_back(new TH1F(name, title, 100, 0, 1000));
            
            sprintf(name, "tau%d_chHad1_pT_by_tau%d_pT_reco%s", i+1, i+1, nameAddon);
            sprintf(title, "p_{T, #tau%d-chHad1} / p_{T, #tau%d} RECO%s", i+1, i+1, titleAddon);
            v_h1_tau_chHad1_pT_by_tau_pT.push_back(new TH1F(name, title, 40, 0, 2));
        }
    }
    
    
    void Output::addbHist(int n)
    {
        for(int i = v_h1_b_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "b%d_pT_reco%s", i+1, nameAddon);
            sprintf(title, "p_{T, b%d} RECO%s", i+1, titleAddon);
            v_h1_b_pT.push_back(new TH1F(name, title, 200, 0, 2000));
            
            sprintf(name, "b%d_eta_reco%s", i+1, nameAddon);
            sprintf(title, "#eta_{b%d} RECO%s", i+1, titleAddon);
            v_h1_b_eta.push_back(new TH1F(name, title, 60, -3, 3));
            
            sprintf(name, "b%d_phi_reco%s", i+1, nameAddon);
            sprintf(title, "#phi_{b%d} RECO%s", i+1, titleAddon);
            v_h1_b_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
        }
    }
    
    
    void Output::addNonBjetHist(int n)
    {
        for(int i = v_h1_nonBjet_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "nonBjet%d_pT_reco%s", i+1, nameAddon);
            sprintf(title, "p_{T, nonBjet%d} RECO%s", i+1, titleAddon);
            v_h1_nonBjet_pT.push_back(new TH1F(name, title, 200, 0, 2000));
            
            sprintf(name, "nonBjet%d_eta_reco%s", i+1, nameAddon);
            sprintf(title, "#eta_{nonBjet%d} RECO%s", i+1, titleAddon);
            v_h1_nonBjet_eta.push_back(new TH1F(name, title, 60, -3, 3));
            
            sprintf(name, "nonBjet%d_phi_reco%s", i+1, nameAddon);
            sprintf(title, "#phi_{nonBjet%d} RECO%s", i+1, titleAddon);
            v_h1_nonBjet_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
        }
    }
    
    
    void Output::addJetHist(int n)
    {
        for(int i = v_h1_jet_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            //
            sprintf(name, "jet%d_pT_gen%s", i+1, nameAddon);
            sprintf(title, "p_{T, #j%d} GEN%s", i+1, titleAddon);
            v_h1_jet_pT_gen.push_back(new TH1F(name, title, 200, 0, 2000));
            
            sprintf(name, "jet%d_eta_gen%s", i+1, nameAddon);
            sprintf(title, "#eta_{#j%d} GEN%s", i+1, titleAddon);
            v_h1_jet_eta_gen.push_back(new TH1F(name, title, 60, -3, 3));
            
            sprintf(name, "jet%d_phi_gen%s", i+1, nameAddon);
            sprintf(title, "#phi_{#j%d} GEN%s", i+1, titleAddon);
            v_h1_jet_phi_gen.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
            
            sprintf(name, "jet%d_MET_deltaPhi_gen%s", i+1, nameAddon);
            sprintf(title, "jet%d_MET_deltaPhi_gen%s", i+1, titleAddon);
            v_h1_jet_MET_deltaPhi_gen.push_back(new TH1F(name, title, 100, -2*M_PI, 2*M_PI));
            
            
            //
            sprintf(name, "jet%d_pT_reco%s", i+1, nameAddon);
            sprintf(title, "p_{T, #j%d} RECO%s", i+1, titleAddon);
            v_h1_jet_pT.push_back(new TH1F(name, title, 200, 0, 2000));
            
            sprintf(name, "jet%d_eta_reco%s", i+1, nameAddon);
            sprintf(title, "#eta_{#j%d} RECO%s", i+1, titleAddon);
            v_h1_jet_eta.push_back(new TH1F(name, title, 60, -3, 3));
            
            sprintf(name, "jet%d_phi_reco%s", i+1, nameAddon);
            sprintf(title, "#phi_{#j%d} RECO%s", i+1, titleAddon);
            v_h1_jet_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
            
            sprintf(name, "jet%d_MET_deltaPhi_reco%s", i+1, nameAddon);
            sprintf(title, "jet%d_MET_deltaPhi_reco%s", i+1, titleAddon);
            v_h1_jet_MET_deltaPhi.push_back(new TH1F(name, title, 100, -2*M_PI, 2*M_PI));
        }
    }
    
    
    void Output::addCutFlow(int n, std::string cutFlow_name)
    {
        for(int iCutFlow = 0; iCutFlow < v_cutFlow_name.size(); iCutFlow++)
        {
            //printf("%d, %s, %s \n", v_cutFlow_name.size(), v_cutFlow_name[iCutFlow].c_str(), cutFlow_name.c_str());
            if(!v_cutFlow_name[iCutFlow].compare(cutFlow_name))
            {
                printf("Cut-flow already exists: %s \n", cutFlow_name.c_str());
                exit(EXIT_FAILURE);
            }
        }
        
        std::vector <double> cutFlow(n, 0);
        
        v_cutFlow.push_back(cutFlow);
        v_cutFlow_name.push_back(std::string(cutFlow_name).c_str());
        
        //
        char name[Common::str_len];
        char title[Common::str_len];
        sprintf(name, "%s%s", cutFlow_name.c_str(), nameAddon);
        sprintf(title, "%s%s", cutFlow_name.c_str(), titleAddon);
        
        v_h1_cutFlow.push_back(new TH1F(name, title, n, 0, n));
        v_h1_cutFlow.at(v_h1_cutFlow.size()-1)->Sumw2();
    }
    
    
    //std::vector <double>* Output::getCutFlow(std::string cutFlow_name)
    //{
    //    for(int iCutFlow = 0; iCutFlow < v_cutFlow_name.size(); iCutFlow++)
    //    {
    //        if(!v_cutFlow_name[iCutFlow].compare(cutFlow_name))
    //        {
    //            return &v_cutFlow.at(iCutFlow);
    //        }
    //    }
    //    
    //    printf("Cut-flow not found: %s \n", cutFlow_name.c_str());
    //    exit(EXIT_FAILURE);
    //    
    //    return 0;
    //}
    
    
    TH1F* Output::getCutFlow(std::string cutFlow_name)
    {
        for(int iCutFlow = 0; iCutFlow < v_cutFlow_name.size(); iCutFlow++)
        {
            if(!v_cutFlow_name[iCutFlow].compare(cutFlow_name))
            {
                return v_h1_cutFlow.at(iCutFlow);
            }
        }
        
        printf("Error in Output::getCutFlow(...): Cut-flow %s not found. \n", cutFlow_name.c_str());
        exit(EXIT_FAILURE);
        
        return 0;
    }
    
    
    void Output::incrementCutFlow(std::string cutFlow_name, int startIndex, std::vector <bool> v_selection)
    {
        incrementCutFlow(cutFlow_name, startIndex, v_selection, 1);
    }
    
    
    void Output::incrementCutFlow(std::string cutFlow_name, int startIndex, std::vector <bool> v_selection, double eventWeight)
    {
        //std::vector <double> *cutFlow = getCutFlow(cutFlow_name);
        TH1F *h1_cutFlow = getCutFlow(cutFlow_name);
        
        if(startIndex+v_selection.size() > h1_cutFlow->GetNbinsX())
        {
            printf("Size mismatch in incrementCutFlow: %s \n", cutFlow_name.c_str());
            exit(EXIT_FAILURE);
        }
        
        for(int iSelection = 0; iSelection < v_selection.size(); iSelection++)
        {
            if(!v_selection.at(iSelection))
            {
                break;
            }
            
            //cutFlow->at(startIndex+iSelection) += eventWeight;
            
            //
            h1_cutFlow->Fill(startIndex+iSelection, eventWeight);
        }
    }
    
    
    void Output::incrementCutFlow(std::string cutFlow_name, int startIndex, std::vector <bool> v_selection, std::vector <double> v_eventWeight)
    {
        //std::vector <double> *cutFlow = getCutFlow(cutFlow_name);
        TH1F *h1_cutFlow = getCutFlow(cutFlow_name);
        
        if(startIndex+v_selection.size() > h1_cutFlow->GetNbinsX())
        {
            printf("Size mismatch in incrementCutFlow: %s \n", cutFlow_name.c_str());
            exit(EXIT_FAILURE);
        }
        
        if(v_selection.size() != v_eventWeight.size())
        {
            printf("Sizes of [v_selection] and [v_eventWeight] must be equal in incrementCutFlow: %s \n", cutFlow_name.c_str());
            exit(EXIT_FAILURE);
        }
        
        for(int iSelection = 0; iSelection < v_selection.size(); iSelection++)
        {
            if(!v_selection.at(iSelection))
            {
                break;
            }
            
            //cutFlow->at(startIndex+iSelection) += v_eventWeight.at(iSelection);
            
            h1_cutFlow->Fill(startIndex+iSelection, v_eventWeight.at(iSelection));
        }
    }
    
    
    void Output::updateBins(
        std::string cutFlowNameBase,
        std::vector <std:: vector <double> > vv_cut,
        std::vector <double> v_selectionVar,
        std::vector <double> v_eventWeight,
        int cutFlow_startIndex
    )
    {
        int nSR = Common::get_nSR(vv_cut);
        int nSel = vv_cut.size();
        
        for(int iSR = 0; iSR < nSR; iSR++)
        {
            std::vector <bool> v_selection(nSel, false);
            
            std::vector <int> v_SRpos = Common::get_SRpos(iSR+1, vv_cut);
            
            for(int iSel = 0; iSel < vv_cut.size(); iSel++)
            {
                std::vector <double> v_cut = vv_cut.at(iSel);
                
                if(v_SRpos.at(iSel) < v_cut.size()-1)
                {
                    if(v_selectionVar.at(iSel) >= v_cut.at(v_SRpos.at(iSel)) && v_selectionVar.at(iSel) < v_cut.at(v_SRpos.at(iSel)+1))
                    {
                        v_selection.at(iSel) = true;
                    }
                }
                
                else
                {
                    if(v_selectionVar.at(iSel) >= v_cut.at(v_SRpos.at(iSel)))
                    {
                        v_selection.at(iSel) = true;
                    }
                }
            }
            
            std::string cutFlowName = cutFlowNameBase + std::to_string(iSR+1);
            
            incrementCutFlow(
                cutFlowName,
                cutFlow_startIndex,
                v_selection,
                v_eventWeight
            );
        }
    }
    
    
    void Output::writeCutFlow(std::string cutFlow_name/*, const char *cutFlow_fileName*/)
    {
        //std::vector <double> *cutFlow = getCutFlow(cutFlow_name);
        //
        //printf("Writing cut-flow: %s --> %s \n", cutFlow_name.c_str(), cutFlow_fileName);
        //
        //FILE *cutFlow_file = fopen(cutFlow_fileName, "w");
        //
        //for(int iCut = 0; iCut < cutFlow->size(); iCut++)
        //{
        //    fprintf(cutFlow_file, "%f \n", cutFlow->at(iCut));
        //}
        //
        //fclose(cutFlow_file);
        
        //
        printf("Writing cut-flow: %s \n", cutFlow_name.c_str());
        
        getCutFlow(cutFlow_name)->Write();
    }
    
    
    void Output::writeData()
    {
        h1_nEvent->Write();
        
        h1_nEvent_2tau->Write();
        h1_nEvent_1tau1lep->Write();
        h1_nEvent_1tau1jet->Write();
        h1_nEvent_2lep->Write();
        h1_nEvent_1lep1jet->Write();
        h1_nEvent_2jet->Write();
        
        h1_topPtReweightFactor->Write();
        h2_top1PtReweightFactor_vs_pT->Write();
        h2_top2PtReweightFactor_vs_pT->Write();
        
        h1_ZpTreweightFactor->Write();
        h2_ZpTreweightFactor_vs_m->Write();
        h2_ZpTreweightFactor_vs_pT->Write();
        
        h1_ZpTreweightFactor_afterBaseline->Write();
        h2_ZpTreweightFactor_vs_m_afterBaseline->Write();
        h2_ZpTreweightFactor_vs_pT_afterBaseline->Write();
        
        h1_ISRreweightFactor->Write();
        
        if(output_pileUp)
        {
            h1_pileUpReweightFactor->Write();
        }
        
        if(output_el)
        {
            h1_el_n->Write();
            h1_lep1_el_pT->Write();
            h1_lep1_el_eta->Write();
            h1_lep1_el_phi->Write();
            
            h1_el_IdIsoSF->Write();
        }
        
        if(output_mu)
        {
            h1_mu_n->Write();
            h1_lep1_mu_pT->Write();
            h1_lep1_mu_eta->Write();
            h1_lep1_mu_phi->Write();
            
            h1_mu_IdIsoSF->Write();
            
            for(int i = 0; i < v_h1_mu_pT.size(); i++)
            {
                v_h1_mu_pT[i]->Write();
                v_h1_mu_eta[i]->Write();
                v_h1_mu_phi[i]->Write();
            }
        }
        
        if(output_elMu)
        {
            h1_elMu_el_pT->Write();
            h1_elMu_el_eta->Write();
            h1_elMu_mu_pT->Write();
            h1_elMu_mu_eta->Write();
            h1_elMu_deltaPhi->Write();
            h1_elMu_m->Write();
            h1_elMu_MET_mT2->Write();
            h1_elMu_MET_Dzeta->Write();
            h1_elMu_jet_HT->Write();
            
            h1_elMuTrig_elSF->Write();
            h1_elMuTrig_muSF->Write();
            h1_elMuTrigSF->Write();
        }
        
        if(output_muMu)
        {
            h1_muMu_mu1_pT->Write();
            h1_muMu_mu1_eta->Write();
            h1_muMu_mu1_phi->Write();
            
            h1_muMu_mu2_pT->Write();
            h1_muMu_mu2_eta->Write();
            h1_muMu_mu2_phi->Write();
            
            h1_muMu_mu1_idIsoEff->Write();
            h1_muMu_mu2_idIsoEff->Write();
            h1_muMu_idIsoEff->Write();
            
            h1_muMu_deltaPhi->Write();
            h1_muMu_deltaEta->Write();
            h1_muMu_m->Write();
            h1_muMu_MET_mT2_lsp0->Write();
            h1_muMu_MET_Dzeta->Write();
            
            h1_muMu_jet_HT->Write();
            
            h1_muTriggerSF->Write();
            
            h2_ZpTreweightFactor_vs_muMu_pT->Write();
            h2_ZpTreweightFactor_vs_muMu_m->Write();
        }
        
        if(output_tau)
        {
            h1_tauIDefficiencyEventWeight->Write();
            
            h1_tau_n->Write();
            
            h1_tau_n_looseIso->Write();
            h1_tau_n_mediumIso->Write();
            h1_tau_n_tightIso->Write();
            
            h1_tau_pT_looseIso->Write();
            h1_tau_pT_mediumIso->Write();
            h1_tau_pT_tightIso->Write();
            
            h1_tau_eta_looseIso->Write();
            h1_tau_eta_mediumIso->Write();
            h1_tau_eta_tightIso->Write();
            
            h1_tau_pT->Write();
            
            h2_tau_pT_vs_DM->Write();
            h2_tau_eta_vs_DM->Write();
            h2_MET_vs_DM->Write();
            h2_tauTau_MET_mT2_vs_DM->Write();
            h2_tauTau_jet_HT_vs_DM->Write();
            h2_b_n_vs_DM->Write();
            h2_tau_nPV_vs_DM->Write();
            
            h3_tau_pT_eta_DM->Write();
            
            for(int i = 0; i < v_h1_tau_pT.size(); i++)
            {
                v_h1_tau_pT_gen[i]->Write();
                v_h1_tau_eta_gen[i]->Write();
                v_h1_tau_phi_gen[i]->Write();
                
                v_h1_tau_MET_deltaPhi_gen[i]->Write();
                v_h1_tau_MET_mT_gen[i]->Write();
                
                
                v_h1_tau_pT[i]->Write();
                v_h1_tau_eta[i]->Write();
                v_h1_tau_phi[i]->Write();
                
                v_h1_tau_m[i]->Write();
                v_h1_tau_MET_deltaPhi[i]->Write();
                v_h1_tau_MET_mT[i]->Write();
                v_h1_tau_chHad1_pT_by_tau_pT[i]->Write();
            }
        }
        
        if(output_tauTau)
        {
            h1_tauTau_MET_mT2_gen->Write();
            h1_tauTau_jet_HT_gen->Write();
            h1_tauTau_jet_MHT_gen->Write();
            
            
            h1_tauTau_genMatched_n->Write();
            
            h1_tauTau_m->Write();
            h1_tauTau_pT->Write();
            h1_tauTau_deltaPhi->Write();
            h1_tauTau_deltaEta->Write();
            h1_tauTau_deltaR->Write();
            h1_tauTau_MET_mT2->Write();
            h1_tauTau_MET_mT2_lsp0->Write();
            h1_tauTau_MET_mT2_lsp0_unsmearedMET->Write();
            h1_tauTau_MET_mT2_lsp0_unsmearedMETphi->Write();
            h1_tauBtauB_MET_mT2_lsp0->Write();
            
            h1_MET_pZeta->Write();
            h1_tauTau_pZeta->Write();
            h1_tauTau_MET_pZeta->Write();
            h1_tauTau_MET_Dzeta->Write();
            
            h2_tauTau_MET_mT2_vs_MET_E->Write();
            h2_tauTau_MET_Dzeta_vs_MET_E->Write();
            
            h2_MET_vs_tau1_MET_deltaPhi->Write();
            h2_MET_vs_tau2_MET_deltaPhi->Write();
            h2_MET_vs_tauTau_deltaPhi->Write();
            
            h2_tauTau_MET_Dzeta_vs_tau1_MET_deltaPhi->Write();
            h2_tauTau_MET_Dzeta_vs_tau2_MET_deltaPhi->Write();
            h2_tauTau_MET_Dzeta_vs_tauTau_deltaPhi->Write();
            
            h2_tauTau_MET_mT2_vs_tau1_MET_deltaPhi->Write();
            h2_tauTau_MET_mT2_vs_tau2_MET_deltaPhi->Write();
            h2_tauTau_MET_mT2_vs_tauTau_deltaPhi->Write();
            
            h2_ZpTreweightFactor_vs_tauTau_pT->Write();
            h2_ZpTreweightFactor_vs_tauTau_m->Write();
            
            h1_tauTau_b_HT->Write();
            h1_tauTau_b_MHT->Write();
            h1_tauTau_jet_HT->Write();
            h1_tauTau_jet_MHT->Write();
            h1_tauTau_b_HT_by_tauTau_jet_HT->Write();
            h1_tauTau_b_MHT_by_tauTau_jet_MHT->Write();
            
            h1_tauTau_promptFakeEventWeight->Write();
            
            h1_tauTauTrig_tau1SF->Write();
            h1_tauTauTrig_tau2SF->Write();
            h1_tauTauTrigSF->Write();
        }
        
        if(output_muTau)
        {
            h1_muTau_mu_pT->Write();
            h1_muTau_mu_eta->Write();
            h1_muTau_mu_phi->Write();
            h1_muTau_tau_pT->Write();
            h1_muTau_tau_eta->Write();
            h1_muTau_tau_phi->Write();
            h1_muTau_tau_m->Write();
            
            h1_muTau_m->Write();
            h1_muTau_pT->Write();
            h1_muTau_deltaPhi->Write();
            h1_muTau_deltaR->Write();
            h1_muTau_MET_mT2->Write();
            h1_muTau_MET_mT2_lsp0->Write();
            h1_muBtauB_MET_mT2_lsp0->Write();
            
            h1_MET_pZeta->Write();
            h1_muTau_pZeta->Write();
            h1_muTau_MET_pZeta->Write();
            h1_muTau_MET_Dzeta->Write();
            
            h2_muTau_MET_mT2_vs_MET_E->Write();
            h2_muTau_MET_Dzeta_vs_MET_E->Write();
            
            h2_ZpTreweightFactor_vs_muTau_pT->Write();
            h2_ZpTreweightFactor_vs_muTau_m->Write();
            
            h1_muTau_b_HT->Write();
            h1_muTau_b_MHT->Write();
            h1_muTau_jet_HT->Write();
            h1_muTau_jet_MHT->Write();
            h1_muTau_b_HT_by_muTau_jet_HT->Write();
            h1_muTau_b_MHT_by_muTau_jet_MHT->Write();
        }
        
        if(output_jet)
        {
            h1_jet_n_gen->Write();
            h1_jet_HT_gen->Write();
            h1_jet_MHT_gen->Write();
            
            
            h1_jet_n->Write();
            h1_jet_HT->Write();
            h1_jet_MHT->Write();
            h1_jet_Meff->Write();
            
            h1_jet_tauOverlap_n->Write();
            
            h1_jet1_jet2_mT->Write();
            h1_nonBjet1_pT_by_jet_HT->Write();
            
            h1_nonBjet_tauOverlap_n_by_nonBjet_n->Write();
            
            h1_jet_MET_deltaPhi_min->Write();
            
            h1_jet_MET_deltaPhi_jetEta0to2p4->Write();
            h1_jet_MET_deltaPhi_jetEta2p4to3p139->Write();
            h1_jet_MET_deltaPhi_jetEta0to5->Write();
            h1_jet_MET_deltaPhi_jetEta2p65to3p139->Write();
            h1_jet_MET_deltaPhi_jetEta0to2p65and3p139to5->Write();
            
            h1_jet_MET_deltaPhiMin_jetEta0to2p4->Write();
            h1_jet_MET_deltaPhiMin_jetEta2p4to3p139->Write();
            h1_jet_MET_deltaPhiMin_jetEta0to5->Write();
            h1_jet_MET_deltaPhiMin_jetEta2p65to3p139->Write();
            h1_jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5->Write();
            
            h1_jet_pT_eta2p1to2p4->Write();
            h1_jet_HT_eta2p1to2p4_by_jet_HT->Write();
            
            h1_jet_pT_eta2p1to3->Write();
            h1_jet_HT_eta2p1to3_by_jet_HT->Write();
            
            h2_jet_n_eta2p1to2p4_vs_jet_n->Write();
            h2_jet_n_eta2p1to3_vs_jet_n->Write();
            
            for(int i = 0; i < v_h1_jet_pT.size(); i++)
            {
                v_h1_jet_pT_gen[i]->Write();
                v_h1_jet_eta_gen[i]->Write();
                v_h1_jet_phi_gen[i]->Write();
                
                v_h1_jet_MET_deltaPhi_gen[i]->Write();
                
                
                v_h1_jet_pT[i]->Write();
                v_h1_jet_eta[i]->Write();
                v_h1_jet_phi[i]->Write();
                
                v_h1_jet_MET_deltaPhi[i]->Write();
            }
            
            for(int i = 0; i < v_h1_nonBjet_pT.size(); i++)
            {
                v_h1_nonBjet_pT[i]->Write();
                v_h1_nonBjet_eta[i]->Write();
                v_h1_nonBjet_phi[i]->Write();
            }
        }
        
        if(output_b)
        {
            h1_bTaggingEventWeight_loose->Write();
            h1_bTaggingEventWeight_medium->Write();
            h1_bTaggingEventWeight_tight->Write();
            
            h1_b_n_loose->Write();
            h1_b_n_medium->Write();
            h1_b_n_tight->Write();
            
            h1_b_pT_loose->Write();
            h1_b_pT_medium->Write();
            h1_b_pT_tight->Write();
            
            h1_b_eta_loose->Write();
            h1_b_eta_medium->Write();
            h1_b_eta_tight->Write();
            
            h1_bb_MET_mT2_lsp0->Write();
            
            h1_b_tauOverlap_n_by_b_n->Write();
            
            h1_b1_pT_by_jet_HT->Write();
            h1_nonBjet1_pT_by_b1_pT->Write();
            
            h1_b_n_by_jet_n->Write();
            
            for(int i = 0; i < v_h1_b_pT.size(); i++)
            {
                v_h1_b_pT[i]->Write();
                v_h1_b_eta[i]->Write();
                v_h1_b_phi[i]->Write();
            }
            
            h2_b_n_vs_jet_n_pT20->Write();
            h2_b_n_vs_jet_n_pT40->Write();
            h2_b_n_vs_jet_n_pT60->Write();
            
            h2_b_n_eta2p1to2p4_vs_b_n->Write();
            h2_b_n_eta2p1to3_vs_b_n->Write();
        }
        
        if(output_MET)
        {
            h1_MET_E->Write();
            h1_MET_phi->Write();
            
            h1_MET_E_unsmeared->Write();
            h1_MET_phi_unsmeared->Write();
            
            h1_MET_E_gen->Write();
            h1_MET_phi_gen->Write();
        }
        
        for(int iCutFlow = 0; iCutFlow < v_h1_cutFlow.size(); iCutFlow++)
        {
            v_h1_cutFlow.at(iCutFlow)->Write();
        }
    }
    
    
    void Output::freeMemory()
    {
        delete h1_nEvent;
        
        delete h1_nEvent_2tau;
        delete h1_nEvent_1tau1lep;
        delete h1_nEvent_1tau1jet;
        delete h1_nEvent_2lep;
        delete h1_nEvent_1lep1jet;
        delete h1_nEvent_2jet;
        
        delete h1_topPtReweightFactor;
        delete h2_top1PtReweightFactor_vs_pT;
        delete h2_top2PtReweightFactor_vs_pT;
        
        delete h1_ZpTreweightFactor;
        delete h2_ZpTreweightFactor_vs_m;
        delete h2_ZpTreweightFactor_vs_pT;
        
        delete h1_ZpTreweightFactor_afterBaseline;
        delete h2_ZpTreweightFactor_vs_m_afterBaseline;
        delete h2_ZpTreweightFactor_vs_pT_afterBaseline;
        
        delete h1_ISRreweightFactor;
        
        if(output_pileUp)
        {
            delete h1_pileUpReweightFactor;
        }
        
        if(output_el)
        {
            delete h1_el_n;
            delete h1_lep1_el_pT;
            delete h1_lep1_el_eta;
            delete h1_lep1_el_phi;
            
            delete h1_el_IdIsoSF;
        }
        
        if(output_mu)
        {
            delete h1_mu_n;
            delete h1_lep1_mu_pT;
            delete h1_lep1_mu_eta;
            delete h1_lep1_mu_phi;
            
            delete h1_mu_IdIsoSF;
            
            for(int i = 0; i < v_h1_mu_pT.size(); i++)
            {
                delete v_h1_mu_pT[i];
                delete v_h1_mu_eta[i];
                delete v_h1_mu_phi[i];
            }
        }
        
        if(output_elMu)
        {
            delete h1_elMu_el_pT;
            delete h1_elMu_el_eta;
            delete h1_elMu_mu_pT;
            delete h1_elMu_mu_eta;
            delete h1_elMu_deltaPhi;
            delete h1_elMu_m;
            delete h1_elMu_MET_mT2;
            delete h1_elMu_MET_Dzeta;
            delete h1_elMu_jet_HT;
            
            delete h1_elMuTrig_elSF;
            delete h1_elMuTrig_muSF;
            delete h1_elMuTrigSF;
        }
        
        if(output_muMu)
        {
            delete h1_muMu_mu1_pT;
            delete h1_muMu_mu1_eta;
            delete h1_muMu_mu1_phi;
            
            delete h1_muMu_mu2_pT;
            delete h1_muMu_mu2_eta;
            delete h1_muMu_mu2_phi;
            
            delete h1_muMu_mu1_idIsoEff;
            delete h1_muMu_mu2_idIsoEff;
            delete h1_muMu_idIsoEff;
            
            delete h1_muMu_deltaPhi;
            delete h1_muMu_deltaEta;
            delete h1_muMu_m;
            delete h1_muMu_MET_mT2_lsp0;
            delete h1_muMu_MET_Dzeta;
            
            delete h1_muMu_jet_HT;
            
            delete h1_muTriggerSF;
            
            delete h2_ZpTreweightFactor_vs_muMu_pT;
            delete h2_ZpTreweightFactor_vs_muMu_m;
        }
        
        if(output_tau)
        {
            delete h1_tauIDefficiencyEventWeight;
            
            delete h1_tau_n;
            
            delete h1_tau_n_looseIso;
            delete h1_tau_n_mediumIso;
            delete h1_tau_n_tightIso;
            
            delete h1_tau_pT_looseIso;
            delete h1_tau_pT_mediumIso;
            delete h1_tau_pT_tightIso;
            
            delete h1_tau_eta_looseIso;
            delete h1_tau_eta_mediumIso;
            delete h1_tau_eta_tightIso;
            
            delete h1_tau_pT;
            
            delete h2_tau_pT_vs_DM;
            delete h2_tau_eta_vs_DM;
            delete h2_MET_vs_DM;
            delete h2_tauTau_MET_mT2_vs_DM;
            delete h2_tauTau_jet_HT_vs_DM;
            delete h2_b_n_vs_DM;
            delete h2_tau_nPV_vs_DM;
            
            delete h3_tau_pT_eta_DM;
            
            for(int i = 0; i < v_h1_tau_pT.size(); i++)
            {
                delete v_h1_tau_pT_gen[i];
                delete v_h1_tau_eta_gen[i];
                delete v_h1_tau_phi_gen[i];
                
                delete v_h1_tau_MET_deltaPhi_gen[i];
                delete v_h1_tau_MET_mT_gen[i];
                
                
                delete v_h1_tau_pT[i];
                delete v_h1_tau_eta[i];
                delete v_h1_tau_phi[i];
                
                delete v_h1_tau_m[i];
                delete v_h1_tau_MET_deltaPhi[i];
                delete v_h1_tau_MET_mT[i];
                delete v_h1_tau_chHad1_pT_by_tau_pT[i];
            }
        }
        
        if(output_tauTau)
        {
            delete h1_tauTau_MET_mT2_gen;
            delete h1_tauTau_jet_HT_gen;
            delete h1_tauTau_jet_MHT_gen;
            
            
            delete h1_tauTau_genMatched_n;
            
            delete h1_tauTau_m;
            delete h1_tauTau_pT;
            delete h1_tauTau_deltaPhi;
            delete h1_tauTau_deltaEta;
            delete h1_tauTau_deltaR;
            delete h1_tauTau_MET_mT2;
            delete h1_tauTau_MET_mT2_lsp0;
            delete h1_tauTau_MET_mT2_lsp0_unsmearedMET;
            delete h1_tauTau_MET_mT2_lsp0_unsmearedMETphi;
            delete h1_tauBtauB_MET_mT2_lsp0;
            
            delete h1_MET_pZeta;
            delete h1_tauTau_pZeta;
            delete h1_tauTau_MET_pZeta;
            delete h1_tauTau_MET_Dzeta;
            
            delete h2_tauTau_MET_mT2_vs_MET_E;
            delete h2_tauTau_MET_Dzeta_vs_MET_E;
            
            delete h2_MET_vs_tau1_MET_deltaPhi;
            delete h2_MET_vs_tau2_MET_deltaPhi;
            delete h2_MET_vs_tauTau_deltaPhi;
            
            delete h2_tauTau_MET_Dzeta_vs_tau1_MET_deltaPhi;
            delete h2_tauTau_MET_Dzeta_vs_tau2_MET_deltaPhi;
            delete h2_tauTau_MET_Dzeta_vs_tauTau_deltaPhi;
            
            delete h2_tauTau_MET_mT2_vs_tau1_MET_deltaPhi;
            delete h2_tauTau_MET_mT2_vs_tau2_MET_deltaPhi;
            delete h2_tauTau_MET_mT2_vs_tauTau_deltaPhi;
            
            delete h2_ZpTreweightFactor_vs_tauTau_pT;
            delete h2_ZpTreweightFactor_vs_tauTau_m;
            
            delete h1_tauTau_b_HT;
            delete h1_tauTau_b_MHT;
            delete h1_tauTau_jet_HT;
            delete h1_tauTau_jet_MHT;
            delete h1_tauTau_b_HT_by_tauTau_jet_HT;
            delete h1_tauTau_b_MHT_by_tauTau_jet_MHT;
            
            delete h1_tauTau_promptFakeEventWeight;
            
            delete h1_tauTauTrig_tau1SF;
            delete h1_tauTauTrig_tau2SF;
            delete h1_tauTauTrigSF;
        }
        
        if(output_muTau)
        {
            delete h1_muTau_mu_pT;
            delete h1_muTau_mu_eta;
            delete h1_muTau_mu_phi;
            delete h1_muTau_tau_pT;
            delete h1_muTau_tau_eta;
            delete h1_muTau_tau_phi;
            delete h1_muTau_tau_m;
            
            delete h1_muTau_m;
            delete h1_muTau_pT;
            delete h1_muTau_deltaPhi;
            delete h1_muTau_deltaR;
            delete h1_muTau_MET_mT2;
            delete h1_muTau_MET_mT2_lsp0;
            delete h1_muBtauB_MET_mT2_lsp0;
            
            delete h1_MET_pZeta;
            delete h1_muTau_pZeta;
            delete h1_muTau_MET_pZeta;
            delete h1_muTau_MET_Dzeta;
            
            delete h2_muTau_MET_mT2_vs_MET_E;
            delete h2_muTau_MET_Dzeta_vs_MET_E;
            
            delete h2_ZpTreweightFactor_vs_muTau_pT;
            delete h2_ZpTreweightFactor_vs_muTau_m;
            
            delete h1_muTau_b_HT;
            delete h1_muTau_b_MHT;
            delete h1_muTau_jet_HT;
            delete h1_muTau_jet_MHT;
            delete h1_muTau_b_HT_by_muTau_jet_HT;
            delete h1_muTau_b_MHT_by_muTau_jet_MHT;
        }
        
        if(output_jet)
        {
            delete h1_jet_n_gen;
            delete h1_jet_HT_gen;
            delete h1_jet_MHT_gen;
            
            
            delete h1_jet_n;
            delete h1_jet_HT;
            delete h1_jet_MHT;
            delete h1_jet_Meff;
            
            delete h1_jet_tauOverlap_n;
            
            delete h1_jet1_jet2_mT;
            delete h1_nonBjet1_pT_by_jet_HT;
            
            delete h1_nonBjet_tauOverlap_n_by_nonBjet_n;
            
            delete h1_jet_MET_deltaPhi_min;
            
            delete h1_jet_MET_deltaPhi_jetEta0to2p4;
            delete h1_jet_MET_deltaPhi_jetEta2p4to3p139;
            delete h1_jet_MET_deltaPhi_jetEta0to5;
            delete h1_jet_MET_deltaPhi_jetEta2p65to3p139;
            delete h1_jet_MET_deltaPhi_jetEta0to2p65and3p139to5;
            
            delete h1_jet_MET_deltaPhiMin_jetEta0to2p4;
            delete h1_jet_MET_deltaPhiMin_jetEta2p4to3p139;
            delete h1_jet_MET_deltaPhiMin_jetEta0to5;
            delete h1_jet_MET_deltaPhiMin_jetEta2p65to3p139;
            delete h1_jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5;
            
            delete h1_jet_pT_eta2p1to2p4;
            delete h1_jet_HT_eta2p1to2p4_by_jet_HT;
            
            delete h1_jet_pT_eta2p1to3;
            delete h1_jet_HT_eta2p1to3_by_jet_HT;
            
            delete h2_jet_n_eta2p1to2p4_vs_jet_n;
            delete h2_jet_n_eta2p1to3_vs_jet_n;
            
            for(int i = 0; i < v_h1_jet_pT.size(); i++)
            {
                delete v_h1_jet_pT_gen[i];
                delete v_h1_jet_eta_gen[i];
                delete v_h1_jet_phi_gen[i];
                
                delete v_h1_jet_MET_deltaPhi_gen[i];
                
                delete v_h1_jet_pT[i];
                delete v_h1_jet_eta[i];
                delete v_h1_jet_phi[i];
                
                delete v_h1_jet_MET_deltaPhi[i];
            }
            
            for(int i = 0; i < v_h1_nonBjet_pT.size(); i++)
            {
                delete v_h1_nonBjet_pT[i];
                delete v_h1_nonBjet_eta[i];
                delete v_h1_nonBjet_phi[i];
            }
        }
        
        if(output_b)
        {
            delete h1_bTaggingEventWeight_loose;
            delete h1_bTaggingEventWeight_medium;
            delete h1_bTaggingEventWeight_tight;
            
            delete h1_b_n_loose;
            delete h1_b_n_medium;
            delete h1_b_n_tight;
            
            delete h1_b_pT_loose;
            delete h1_b_pT_medium;
            delete h1_b_pT_tight;
            
            delete h1_b_eta_loose;
            delete h1_b_eta_medium;
            delete h1_b_eta_tight;
            
            delete h1_bb_MET_mT2_lsp0;
            
            delete h1_b_tauOverlap_n_by_b_n;
            
            delete h1_b1_pT_by_jet_HT;
            delete h1_nonBjet1_pT_by_b1_pT;
            
            delete h1_b_n_by_jet_n;
            
            for(int i = 0; i < v_h1_b_pT.size(); i++)
            {
                delete v_h1_b_pT[i];
                delete v_h1_b_eta[i];
                delete v_h1_b_phi[i];
            }
            
            delete h2_b_n_vs_jet_n_pT20;
            delete h2_b_n_vs_jet_n_pT40;
            delete h2_b_n_vs_jet_n_pT60;
            
            delete h2_b_n_eta2p1to2p4_vs_b_n;
            delete h2_b_n_eta2p1to3_vs_b_n;
        }
        
        if(output_MET)
        {
            delete h1_MET_E;
            delete h1_MET_phi;
            
            delete h1_MET_E_unsmeared;
            delete h1_MET_phi_unsmeared;
            
            delete h1_MET_E_gen;
            delete h1_MET_phi_gen;
        }
        
        for(int iCutFlow = 0; iCutFlow < v_h1_cutFlow.size(); iCutFlow++)
        {
            delete v_h1_cutFlow.at(iCutFlow);
        }
    }
}

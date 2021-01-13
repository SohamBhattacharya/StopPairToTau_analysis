# ifndef Miscellaneous_H
# define Miscellaneous_H

# include "BTagCalibrationStandalone.h"
# include "ElMuScaleFactor.h"
# include "lester_mt2_bisect_mod.h"

# include "Common.h"
# include "CustomInfo_data.h"
# include "CustomInfo_mc.h"
# include "TauEfficiencyAndSF.h"
//# include "TemplateSmearing.h"


namespace Miscellaneous
{
    class Output
    {
        public :
        
        
        TH1F *h1_mu1_pT_gen;
        TH1F *h1_mu1_eta_gen;
        TH1F *h1_mu1_phi_gen;
        
        TH1F *h1_tau1_pT_gen;
        TH1F *h1_tau1_eta_gen;
        TH1F *h1_tau1_phi_gen;
        
        TH1F *h1_mu1_pT_reco;
        TH1F *h1_mu1_eta_reco;
        TH1F *h1_mu1_phi_reco;
        
        TH1F *h1_mu1_genMatched_pT_reco;
        TH1F *h1_mu1_genMatched_eta_reco;
        TH1F *h1_mu1_genMatched_phi_reco;
        
        TH1F *h1_mu1_resolution_pT;
        
        TH1F *h1_tauTau_isGenMatched;
        
        TH1F *h1_tau_isGenMatched;
        
        TH2F *h2_tau_n_gen_vs_reco;
        
        Output();
        
        void writeData();
        
        void freeMemory();
    };
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName
    );
    
    
    template <typename T1> void analyze(
        T1 *input,
        Output *output,
        std::string tauID_WPname
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if((iEvent+2) % 1000 == 0)
            {
                printf("Processed event no. %d / %d \n", iEvent+2, nEvent);
                fflush(stdout);
            }
            
            input->T_gen->GetEntry(iEvent);
            input->T_reco->GetEntry(iEvent);
            
            
            // GEN mu
            std::vector <bool> v_mu_isSelected_gen(input->mu_n_gen, false);
            std::vector <bool> v_mu_isUsed_gen(input->mu_n_gen, false);
            
            CLHEP::HepLorentzVector mu1_4mom_gen(0, 0, 0, 0);
            
            int mu_isSelected_n_gen = 0;
            
            for(int iMu = 0; iMu < input->mu_n_gen; iMu++)
            {
                CLHEP::HepLorentzVector mu_4mom_gen;
                
                mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu)));
                mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu));
                mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu));
                mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu));
                
                if(mu_4mom_gen.perp() < 20 || fabs(mu_4mom_gen.eta()) > 2.1)
                {
                    continue;
                }
                
                mu_isSelected_n_gen++;
                
                v_mu_isSelected_gen.at(iMu) = true;
                
                if(mu_4mom_gen.perp() > mu1_4mom_gen.perp())
                {
                    mu1_4mom_gen = mu_4mom_gen;
                }
            }
            
            if(mu_isSelected_n_gen)
            {
                output->h1_mu1_pT_gen->Fill(mu1_4mom_gen.perp());
                output->h1_mu1_eta_gen->Fill(mu1_4mom_gen.eta());
                output->h1_mu1_phi_gen->Fill(mu1_4mom_gen.phi());
            }
            
            
            // RECO mu
            std::vector <bool> v_mu_isSelected_reco(input->mu_n_reco, false);
            std::vector <bool> v_mu_isUsed_reco(input->mu_n_reco, false);
            
            CLHEP::HepLorentzVector mu1_4mom_reco(0, 0, 0, 0);
            
            int mu_isSelected_n_reco = 0;
            
            for(int iMu = 0; iMu < input->mu_n_reco; iMu++)
            {
                CLHEP::HepLorentzVector mu_4mom_reco;
                
                mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(iMu)));
                mu_4mom_reco.setX(input->v_mu_px_reco->at(iMu));
                mu_4mom_reco.setY(input->v_mu_py_reco->at(iMu));
                mu_4mom_reco.setZ(input->v_mu_pz_reco->at(iMu));
                
                if(mu_4mom_reco.perp() < 20 || fabs(mu_4mom_reco.eta()) > 2.1)
                {
                    continue;
                }
                
                if(!input->v_mu_isMediumMuon_reco->at(iMu))
                {
                    continue;
                }
                
                if(!input->v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco->at(iMu))
                {
                    continue;
                }
                
                if(fabs(input->v_mu_dxy_reco->at(iMu)) > Common::mu_dxyCut_reco || fabs(input->v_mu_dz_reco->at(iMu)) > Common::mu_dzCut_reco)
                {
                    continue;
                }
                
                mu_isSelected_n_reco++;
                
                v_mu_isSelected_reco.at(iMu) = true;
                
                if(mu_4mom_reco.perp() > mu1_4mom_reco.perp())
                {
                    mu1_4mom_reco = mu_4mom_reco;
                }
            }
            
            if(mu_isSelected_n_reco)
            {
                output->h1_mu1_pT_reco->Fill(mu1_4mom_reco.perp());
                output->h1_mu1_eta_reco->Fill(mu1_4mom_reco.eta());
                output->h1_mu1_phi_reco->Fill(mu1_4mom_reco.phi());
            }
            
            
            // GEN tau
            std::vector <bool> v_tau_isSelected_gen(input->tau_vis_n_gen, false);
            std::vector <bool> v_tau_isUsed_gen(input->tau_vis_n_gen, false);
            
            CLHEP::HepLorentzVector tau1_4mom_gen(0, 0, 0, 0);
            CLHEP::HepLorentzVector tau2_4mom_gen(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector tauh1_4mom_gen(0, 0, 0, 0);
            CLHEP::HepLorentzVector tauh2_4mom_gen(0, 0, 0, 0);
            
            int tau_isSelected_n_gen = 0;
            
            for(int iTau = 0; iTau < input->tau_vis_n_gen; iTau++)
            {
                CLHEP::HepLorentzVector tau_4mom_gen;
                
                tau_4mom_gen.setT(fabs(input->v_tau_E_gen->at(iTau)));
                tau_4mom_gen.setX(input->v_tau_px_gen->at(iTau));
                tau_4mom_gen.setY(input->v_tau_py_gen->at(iTau));
                tau_4mom_gen.setZ(input->v_tau_pz_gen->at(iTau));
                
                CLHEP::HepLorentzVector tauh_4mom_gen;
                
                tauh_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(iTau)));
                tauh_4mom_gen.setX(input->v_tau_vis_px_gen->at(iTau));
                tauh_4mom_gen.setY(input->v_tau_vis_py_gen->at(iTau));
                tauh_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(iTau));
                
                //if(tau_4mom_gen.perp() < 20 || fabs(tau_4mom_gen.eta()) > 2.1)
                //{
                //    continue;
                //}
                
                if(tauh_4mom_gen.perp() < 20 || fabs(tauh_4mom_gen.eta()) > 2.1)
                {
                    continue;
                }
                
                //if(input->MET_E_reco < 80)
                //{
                //    continue;
                //}
                
                tau_isSelected_n_gen++;
                
                v_tau_isSelected_gen.at(iTau) = true;
                
                if(tau_4mom_gen.perp() > tau1_4mom_gen.perp())
                {
                    tau1_4mom_gen = tau_4mom_gen;
                }
                
                else if(tau_4mom_gen.perp() > tau2_4mom_gen.perp())
                {
                    tau2_4mom_gen = tau_4mom_gen;
                }
                
                if(tauh_4mom_gen.perp() > tauh1_4mom_gen.perp())
                {
                    tauh1_4mom_gen = tauh_4mom_gen;
                }
                
                else if(tauh_4mom_gen.perp() > tauh2_4mom_gen.perp())
                {
                    tauh2_4mom_gen = tauh_4mom_gen;
                }
            }
            
            if(tau_isSelected_n_gen)
            {
                output->h1_tau1_pT_gen->Fill(tau1_4mom_gen.perp());
                output->h1_tau1_eta_gen->Fill(tau1_4mom_gen.eta());
                output->h1_tau1_phi_gen->Fill(tau1_4mom_gen.phi());
            }
            
            
            // Select tau pair
            std::vector <double> v_tau_pTetaCut(input->tau_n_reco, 0);
            std::vector <double> v_tau_IPcut(input->tau_n_reco, 0);
            
            for(int iTau = 0; iTau < input->tau_n_reco; iTau++)
            {
                CLHEP::HepLorentzVector tau_4mom_reco;
                
                tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau)));
                tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau));
                tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau));
                tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau));
                
                if(tau_4mom_reco.perp() > Common::tau_pTcut_tauTau_reco && fabs(tau_4mom_reco.eta()) < Common::tau_etaCut_tauTau_reco)
                {
                    v_tau_pTetaCut.at(iTau) = 1;
                }
                
                if(fabs(input->v_tau_dz_reco->at(iTau)) < Common::tau_dzCut_reco)
                {
                    v_tau_IPcut.at(iTau) = 1;
                }
            }
            
            std::vector <double> *v_tau_iso_reco;
            
            v_tau_iso_reco = input->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
            //tauID_WPname = "TightIsolationMVArun2v1DBdR03oldDMwLT";
            
            
            std::vector <std::vector <double> *> vv_tauSelection = {
                input->v_tau_byDecayModeFinding_reco,
                &v_tau_IPcut,
                input->v_tau_againstElectronLooseMVA6_reco,
                input->v_tau_againstMuonLoose3_reco,
                v_tau_iso_reco,
                &v_tau_pTetaCut
            };
            
            std::vector <int> tauPair_pos = Common::getObjPair(
                &(input->v_tau_reco),
                &(input->v_tau_reco),
                true,
                vv_tauSelection,
                vv_tauSelection,
                Common::tauTau_deltaRcut_reco,
                "OS"
            );
            
            
            int tauTau_genMatched_n = 0;
            
            if(tauPair_pos.size())
            {
                // Reco taus
                CLHEP::HepLorentzVector tau1_4mom_reco(0, 0, 0, 0);
                CLHEP::HepLorentzVector tau2_4mom_reco(0, 0, 0, 0);
                
                bool foundTauPair_reco = false;
                
                std::vector <bool> v_tau_isSelected_reco(input->tau_n_reco, false);
                std::vector <bool> v_tau_isGenMatched_reco(input->tau_n_reco, false);
                
                int tauTau_pos1 = tauPair_pos.at(0);
                int tauTau_pos2 = tauPair_pos.at(1);
                
                for(int iTau_reco = 0; iTau_reco < input->tau_n_reco; iTau_reco++)
                {
                    CLHEP::HepLorentzVector tau_4mom_reco;
                    
                    tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau_reco)));
                    tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau_reco));
                    tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau_reco));
                    tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau_reco));
                    
                    // Select the taus belonging to the pair only
                    if(iTau_reco != tauTau_pos1 && iTau_reco != tauTau_pos2)
                    {
                        continue;
                    }
                    
                    v_tau_isSelected_reco.at(iTau_reco) = true;
                    
                    int tau_genMatchedIndex = -1;
                    int tau_nearestGenIndex = -1;
                    double deltaR_min = 9999;
                    
                    CLHEP::HepLorentzVector tau_nearestGenh_4mom;
                    CLHEP::HepLorentzVector tau_nearestGen_4mom;
                    
                    for(int iTau_gen = 0; iTau_gen < input->tau_vis_n_gen; iTau_gen++)
                    {
                        CLHEP::HepLorentzVector tauh_4mom_gen;
                        
                        tauh_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(iTau_gen)));
                        tauh_4mom_gen.setX(input->v_tau_vis_px_gen->at(iTau_gen));
                        tauh_4mom_gen.setY(input->v_tau_vis_py_gen->at(iTau_gen));
                        tauh_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(iTau_gen));
                        
                        CLHEP::HepLorentzVector tau_4mom_gen;
                        
                        tau_4mom_gen.setT(fabs(input->v_tau_E_gen->at(iTau_gen)));
                        tau_4mom_gen.setX(input->v_tau_px_gen->at(iTau_gen));
                        tau_4mom_gen.setY(input->v_tau_py_gen->at(iTau_gen));
                        tau_4mom_gen.setZ(input->v_tau_pz_gen->at(iTau_gen));
                        
                        // Choose the the selected gen taus
                        if(!v_tau_isSelected_gen.at(iTau_gen))
                        {
                            continue;
                        }
                        
                        // Reject if already used for matching
                        if(v_tau_isUsed_gen.at(iTau_gen))
                        {
                            continue;
                        }
                        
                        double deltaR = tau_4mom_reco.deltaR(tauh_4mom_gen);
                        
                        if(deltaR < deltaR_min)
                        {
                            deltaR_min = deltaR;
                            
                            tau_nearestGenIndex = iTau_gen;
                            
                            tau_nearestGenh_4mom = tauh_4mom_gen;
                            tau_nearestGen_4mom = tau_4mom_gen;
                        }
                    }
                    
                    if(tau_nearestGenIndex >= 0)
                    {
                        //output->h1_tau_nearestGen_deltaR->Fill(deltaR_min);
                        
                        if(deltaR_min < 0.3)
                        {
                            v_tau_isGenMatched_reco.at(iTau_reco) = true;
                            
                            tau_genMatchedIndex = tau_nearestGenIndex;
                            
                            v_tau_isUsed_gen.at(tau_genMatchedIndex) = true;
                        }
                    }
                }
                
                if(v_tau_isGenMatched_reco.at(tauTau_pos1) && v_tau_isGenMatched_reco.at(tauTau_pos2))
                {
                    output->h1_tauTau_isGenMatched->Fill(1);
                    
                    tauTau_genMatched_n = 2;
                }
                
                else if(v_tau_isGenMatched_reco.at(tauTau_pos1) || v_tau_isGenMatched_reco.at(tauTau_pos2))
                {
                    output->h1_tauTau_isGenMatched->Fill(0.5);
                    
                    tauTau_genMatched_n = 1;
                }
                
                else
                {
                    output->h1_tauTau_isGenMatched->Fill(0);
                }
            }
            
            //else
            //{
            //    output->h1_tauTau_isGenMatched->Fill(-1);
            //}
            
            if(tau_isSelected_n_gen >= 2)
            {
                output->h1_tauTau_isGenMatched->Fill(-1);
            }
            
            
            int temp = v_tau_isUsed_gen.size();
            v_tau_isUsed_gen.resize(0);
            v_tau_isUsed_gen.resize(temp, false);
            
            
            
            // Select single tau
            int tau_selected_n = 0;
            int tau_selected_index = -1;
            
            CLHEP::HepLorentzVector tau1_4mom_reco;
            
            for(int iTau = 0; iTau < input->tau_n_reco; iTau++)
            {
                CLHEP::HepLorentzVector tau_4mom_reco;
                
                tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau)));
                tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau));
                tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau));
                tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau));
                
                bool isSelected = true;
                
                if(tau_4mom_reco.perp() < Common::tau_pTcut_tauTau_reco || fabs(tau_4mom_reco.eta()) > Common::tau_etaCut_tauTau_reco)
                {
                    isSelected = false;
                }
                
                if(!input->v_tau_byDecayModeFinding_reco->at(iTau))
                {
                    isSelected = false;
                }
                
                if(fabs(input->v_tau_dz_reco->at(iTau)) > Common::tau_dzCut_reco)
                {
                    isSelected = false;
                }
                
                if(!v_tau_iso_reco->at(iTau))
                {
                    isSelected = false;
                }
                
                if(!input->v_tau_againstElectronLooseMVA6_reco->at(iTau))
                {
                    isSelected = false;
                }
                
                if(!input->v_tau_againstMuonLoose3_reco->at(iTau))
                {
                    isSelected = false;
                }
                
                if(!isSelected)
                {
                    continue;
                }
                
                tau_selected_n++;
                
                if(tau_selected_n > 1)
                {
                    continue;
                }
                
                tau_selected_index = iTau;
                tau1_4mom_reco = tau_4mom_reco;
            }
            
            // Exactly 1 tau
            int tau_genMatched_n = 0;
            
            if(tau_selected_n == 1)
            {
                int tau_genMatchedIndex = -1;
                int tau_nearestGenIndex = -1;
                double deltaR_min = 9999;
                
                CLHEP::HepLorentzVector tau_nearestGenh_4mom;
                CLHEP::HepLorentzVector tau_nearestGen_4mom;
                
                for(int iTau_gen = 0; iTau_gen < input->tau_vis_n_gen; iTau_gen++)
                {
                    CLHEP::HepLorentzVector tauh_4mom_gen;
                    
                    tauh_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(iTau_gen)));
                    tauh_4mom_gen.setX(input->v_tau_vis_px_gen->at(iTau_gen));
                    tauh_4mom_gen.setY(input->v_tau_vis_py_gen->at(iTau_gen));
                    tauh_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(iTau_gen));
                    
                    CLHEP::HepLorentzVector tau_4mom_gen;
                    
                    tau_4mom_gen.setT(fabs(input->v_tau_E_gen->at(iTau_gen)));
                    tau_4mom_gen.setX(input->v_tau_px_gen->at(iTau_gen));
                    tau_4mom_gen.setY(input->v_tau_py_gen->at(iTau_gen));
                    tau_4mom_gen.setZ(input->v_tau_pz_gen->at(iTau_gen));
                    
                    // Choose the the selected gen taus
                    if(!v_tau_isSelected_gen.at(iTau_gen))
                    {
                        continue;
                    }
                    
                    // Reject if already used for matching
                    if(v_tau_isUsed_gen.at(iTau_gen))
                    {
                        continue;
                    }
                    
                    double deltaR = tau1_4mom_reco.deltaR(tauh_4mom_gen);
                    
                    if(deltaR < deltaR_min)
                    {
                        deltaR_min = deltaR;
                        
                        tau_nearestGenIndex = iTau_gen;
                        
                        tau_nearestGenh_4mom = tauh_4mom_gen;
                        tau_nearestGen_4mom = tau_4mom_gen;
                    }
                }
                
                //output->h1_tau_nearestGen_deltaR->Fill(deltaR_min);
                
                if(deltaR_min < 0.3)
                {
                    tau_genMatchedIndex = tau_nearestGenIndex;
                    
                    v_tau_isUsed_gen.at(tau_genMatchedIndex) = true;
                    
                    output->h1_tau_isGenMatched->Fill(1);
                    
                    tau_genMatched_n = 1;
                }
                
                else
                {
                    output->h1_tau_isGenMatched->Fill(0);
                }
                
                output->h1_tau_isGenMatched->Fill(-1);
            }
            
            
            if(tau_selected_n == 1)
            {
                output->h2_tau_n_gen_vs_reco->Fill(1, tau_isSelected_n_gen);
                
                output->h2_tau_n_gen_vs_reco->Fill(1.5 + (tau_genMatched_n / 2.0)*0.5, tau_isSelected_n_gen);
            }
            
            else if(tauPair_pos.size())
            {
                output->h2_tau_n_gen_vs_reco->Fill(2, tau_isSelected_n_gen);
                
                output->h2_tau_n_gen_vs_reco->Fill(2.5 + (tauTau_genMatched_n / 3.0)*0.5, tau_isSelected_n_gen);
            }
            
            else if(tau_selected_n == 0)
            {
                output->h2_tau_n_gen_vs_reco->Fill(tau_selected_n, tau_isSelected_n_gen);
            }
            
            
            // Match RECO-mu to GEN-mu
            std::vector <bool> v_mu_isGenMatched_reco(input->mu_n_reco, false);
            
            CLHEP::HepLorentzVector mu1_genMatched_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector mu1_nearestGenMu_4mom(0, 0, 0, 0);
            
            int mu_isGenMatched_n_reco = 0;
            
            for(int iMu_reco = 0; iMu_reco < input->mu_n_reco; iMu_reco++)
            {
                CLHEP::HepLorentzVector mu_4mom_reco;
                
                mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(iMu_reco)));
                mu_4mom_reco.setX(input->v_mu_px_reco->at(iMu_reco));
                mu_4mom_reco.setY(input->v_mu_py_reco->at(iMu_reco));
                mu_4mom_reco.setZ(input->v_mu_pz_reco->at(iMu_reco));
                
                if(!v_mu_isSelected_reco.at(iMu_reco))
                {
                    continue;
                }
                
                bool mu_isGenMatched = false;
                
                int nearestGenMu_index = -1;
                double deltaR_min = 9999;
                
                CLHEP::HepLorentzVector mu_nearestGenMu_4mom(0, 0, 0, 0);
                
                for(int iMu_gen = 0; iMu_gen < input->mu_n_gen; iMu_gen++)
                {
                    CLHEP::HepLorentzVector mu_4mom_gen;
                    
                    mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu_gen)));
                    mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu_gen));
                    mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu_gen));
                    mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu_gen));
                    
                    if(!v_mu_isSelected_gen.at(iMu_gen))
                    {
                        continue;
                    }
                    
                    if(v_mu_isUsed_gen.at(iMu_gen))
                    {
                        continue;
                    }
                    
                    double deltaR = mu_4mom_gen.deltaR(mu_4mom_reco);
                    
                    if(deltaR < deltaR_min)
                    {
                        nearestGenMu_index = iMu_gen;
                        deltaR_min = deltaR;
                        
                        mu_nearestGenMu_4mom = mu_4mom_gen;
                    }
                }
                
                if(deltaR_min < 0.3)
                {
                    mu_isGenMatched = true;
                    v_mu_isGenMatched_reco.at(iMu_reco) = true;
                    v_mu_isUsed_gen.at(nearestGenMu_index) = true;
                    
                    mu_isGenMatched_n_reco++;
                }
                
                if(!mu_isGenMatched)
                {
                    continue;
                }
                
                if(mu_4mom_reco.perp() > mu1_genMatched_4mom_reco.perp())
                {
                    mu1_genMatched_4mom_reco = mu_4mom_reco;
                    mu1_nearestGenMu_4mom = mu_nearestGenMu_4mom;
                }
            }
            
            if(mu_isGenMatched_n_reco)
            {
                output->h1_mu1_genMatched_pT_reco->Fill(mu1_genMatched_4mom_reco.perp());
                output->h1_mu1_genMatched_eta_reco->Fill(mu1_genMatched_4mom_reco.eta());
                output->h1_mu1_genMatched_phi_reco->Fill(mu1_genMatched_4mom_reco.phi());
                
                output->h1_mu1_resolution_pT->Fill(mu1_genMatched_4mom_reco.perp()/mu1_nearestGenMu_4mom.perp());
            }
        }
    }
}


# endif

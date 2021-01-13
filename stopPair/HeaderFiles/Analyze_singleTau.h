# ifndef Analyze_singleTau_H
# define Analyze_singleTau_H


# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <utility>
# include <vector>

# include "lester_mt2_bisect_mod.h"

# include "BTagCalibrationStandalone.h"
# include "CustomInfo_data.h"
# include "CustomInfo_mc.h"
# include "Output_GEN.h"
# include "Output_RECO.h"
# include "TauEfficiencyAndSF.h"


namespace Analyze_singleTau
{
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY,
        std::vector <double> v_eventWeight_nJetBin
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::vector <double> v_eventWeight_nJetBin
    );
    
    
    template <typename T1> void analyze_reco(T1 *input, \
        Output_RECO::Output *output_reco, \
        const char *tau_isoOption, \
        const char *tauPair_signOption, \
        std::map <std::string, bool> m_eventSelection, \
        bool isMC, \
        bool isSUSY, \
        std::pair <int, int> massPoint_stop1_neutralino1, \
        std::vector <double> v_eventWeight_nJetBin, \
        BTagCalibration *bTagCalib, \
        std::string fileName_bTaggingEfficiency)
    {
        int nEvent = input->T_reco->GetEntries();
        
        output_reco->addTauHist(1);
        output_reco->addbHist(2);
        output_reco->addJetHist(2);
        output_reco->addNonBjetHist(2);
        
        for(int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if((iEvent+2) % 1000 == 0)
            {
                printf("[%s] Processed event no. %d / %d \n", output_reco->nameAddon, iEvent+2, nEvent);
                fflush(stdout);
            }
            
            input->T_reco->GetEntry(iEvent);
            
            double eventWeight_common = 1;
            
            if(isMC)
            {
                input->T_gen->GetEntry(iEvent);
                
                // n-jet bin stitching event weight
                if(v_eventWeight_nJetBin.size())
                {
                    double eventWeight_nJetBin = Common::getEventWeight_nJetBin(v_eventWeight_nJetBin, input->outgoingParton_n_gen);
                    //printf("eventWeight_nJetBin: %d %f \n", input->outgoingParton_n_gen, eventWeight_nJetBin);
                    
                    eventWeight_common *= eventWeight_nJetBin;
                }
            }
            
            // Select mass point
            if(isSUSY)
            {
                //printf("stop1_m_genParam %f, neutralino1_m_genParam %f \n", input->stop1_m_genParam, input->neutralino1_m_genParam);
                
                if((massPoint_stop1_neutralino1.first >= 0 && input->stop1_m_genParam != massPoint_stop1_neutralino1.first) || \
                    (massPoint_stop1_neutralino1.second >= 0 && input->neutralino1_m_genParam != massPoint_stop1_neutralino1.second))
                {
                    continue;
                }
            }
            
            
            // Select muon
            int mu_selected_n = 0;
            int mu1_index = -1;
            
            CLHEP::HepLorentzVector mu1_4mom_reco;
            
            for(int iMu = 0; iMu < input->mu_n_reco; iMu++)
            {
                CLHEP::HepLorentzVector mu_4mom_reco;
                
                mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(iMu)));
                mu_4mom_reco.setX(input->v_mu_px_reco->at(iMu));
                mu_4mom_reco.setY(input->v_mu_py_reco->at(iMu));
                mu_4mom_reco.setZ(input->v_mu_pz_reco->at(iMu));
                
                bool isSelected = true;
                
                if(mu_4mom_reco.perp() < Common::mu_pTcut_muMu_reco || fabs(mu_4mom_reco.eta()) > Common::tau_etaCut_tauTau_reco)//Common::mu_etaCut_muMu_reco)
                {
                    isSelected = false;
                }
                
                if(fabs(input->v_mu_dxy_reco->at(iMu)) > Common::mu_dxyCut_reco || fabs(input->v_mu_dz_reco->at(iMu)) > Common::mu_dzCut_reco)
                {
                    isSelected = false;
                }
                
                if(!input->v_mu_isMediumMuon_reco->at(iMu))
                {
                    isSelected = false;
                }
                
                if(!input->v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco->at(iMu))
                {
                    isSelected = false;
                }
                
                if(!isSelected)
                {
                    continue;
                }
                
                mu_selected_n++;
                
                if(mu_selected_n > 1)
                {
                    break;
                }
                
                mu1_index = iMu;
                
                mu1_4mom_reco = mu_4mom_reco;
            }
            
            // Exactly 0 muon
            if(mu_selected_n > 0)
            {
                continue;
            }
            
            
            std::string tauID_WPname = "";
            std::vector <double> *v_tau_iso_reco;
            
            if(!strcmp(tau_isoOption, "loose"))
            {
                //v_tau_iso_reco = input->v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco;
                v_tau_iso_reco = input->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                tauID_WPname = "LooseIsolationMVArun2v1DBdR03oldDMwLT";
            }
            
            else if(!strcmp(tau_isoOption, "medium"))
            {
                //v_tau_iso_reco = input->v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco;
                v_tau_iso_reco = input->v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco;
                tauID_WPname = "MediumIsolationMVArun2v1DBdR03oldDMwLT";
            }
            
            else if(!strcmp(tau_isoOption, "tight"))
            {
                //v_tau_iso_reco = input->v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco;
                v_tau_iso_reco = input->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                tauID_WPname = "TightIsolationMVArun2v1DBdR03oldDMwLT";
            }
            
            else
            {
                printf("Wrong tau isolation option");
                exit(EXIT_FAILURE);
            }
            
            
            // Select tau
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
                    break;
                }
                
                tau_selected_index = iTau;
                tau1_4mom_reco = tau_4mom_reco;
            }
            
            // Exactly 1 tau
            if(tau_selected_n != 1)
            {
                continue;
            }
            
            
            double bTaggingEventWeight = 1;
            
            //if(isMC)
            //{
            //    BTagCalibrationReader bTagCalibReader_CSVv2M( \
            //        BTagEntry::OP_MEDIUM,
            //        "central",
            //        {"up", "down"}
            //    );
            //    
            //    
            //    bTagCalibReader_CSVv2M.load(*bTagCalib,
            //        BTagEntry::FLAV_B,
            //        "comb");
            //    
            //    bTagCalibReader_CSVv2M.load(*bTagCalib,
            //        BTagEntry::FLAV_C,
            //        "comb");
            //    
            //    bTagCalibReader_CSVv2M.load(*bTagCalib,
            //        BTagEntry::FLAV_UDSG,
            //        "incl");
            //    
            //    bTaggingEventWeight = Common::getBTaggingEventWeight(&input->v_jet_reco,
            //        Common::b_pTcut_reco, Common::b_etaCut_reco,
            //        input->v_jet_partonFlavour_reco,
            //        input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
            //        &bTagCalibReader_CSVv2M,
            //        "central",
            //        fileName_bTaggingEfficiency,
            //        "bTaggingEff_eff_b_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
            //        "bTaggingEff_eff_c_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
            //        "bTaggingEff_eff_udsg_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
            //        {std::make_pair(tau1_4mom_reco, 0.3)}
            //    );
            //    
            //    //printf("bTaggingEventWeight %f \n", bTaggingEventWeight);
            //    output_reco->h1_bTaggingEventWeight_medium->Fill(bTaggingEventWeight);
            //    //eventWeight_common *= bTaggingEventWeight;
            //}
            
            
            output_reco->v_h1_tau_pT.at(0)->Fill(tau1_4mom_reco.perp(), eventWeight_common);
            output_reco->v_h1_tau_eta.at(0)->Fill(tau1_4mom_reco.eta(), eventWeight_common);
            output_reco->v_h1_tau_phi.at(0)->Fill(tau1_4mom_reco.phi(), eventWeight_common);
            
            output_reco->h1_MET_E->Fill(input->MET_E_reco);
            output_reco->h1_MET_phi->Fill(input->MET_phi_reco);
            
        }
    }
}


# endif

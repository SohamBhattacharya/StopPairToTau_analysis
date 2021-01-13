# ifndef FakeRate_tauTau_H
# define FakeRate_tauTau_H

# include "BTagCalibrationStandalone.h"
# include "ElMuScaleFactor.h"
# include "lester_mt2_bisect_mod.h"

# include "Common.h"
# include "CustomInfo_data.h"
# include "CustomInfo_mc.h"
# include "Output_GEN.h"
# include "Output_RECO.h"
# include "TauEfficiencyAndSF.h"
//# include "TemplateSmearing.h"


namespace FakeRate_tauTau
{
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::vector <double> v_eventWeight_nJetBin
    );
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era
    );
    
    
    template <typename T1> void analyze_reco(
        T1 *input,
        Output_RECO::Output *output_reco,
        const char *tauTau_signOption,
        std::string tau1_isoOption, std::vector <double> *v_tau1_isolation,
        std::string tau2_isoOption, std::vector <double> *v_tau2_isolation,
        std::string eventSelectionStr,
        bool isMC,
        std::string era,
        BTagCalibration *bTagCalib,
        std::string fileName_bTaggingEfficiency,
        TauEfficiencyAndSF::TauEfficiencyAndSF *tauEfficiencyObject,
        std::vector <double> v_eventWeight_nJetBin
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        output_reco->addTauHist(2);
        output_reco->addbHist(2);
        output_reco->addJetHist(2);
        output_reco->addNonBjetHist(2);
        
        // If no event selection provided
        if(!eventSelectionStr.length())
        {
            printf("Error in FakeRate_tauTau:analyze_reco: \"eventSelectionStr\" cannot be empty. \n");
            fflush(stdout);
            
            exit(EXIT_FAILURE);
        }
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if(iEvent == 0 || (iEvent+1) % 1000 == 0 || iEvent == nEvent-1)
            {
                printf("[%s] Processing event no. %d / %d \n", output_reco->nameAddon, iEvent+1, nEvent);
                fflush(stdout);
            }
            
            input->T_reco->GetEntry(iEvent);
            
            // Trigger
            if(!(
                // 2016
                input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v ||
                input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v ||
                
                //2017
                input->isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v ||
                input->isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v ||
                input->isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v
            ))
            {
                continue;
            }
            
            double eventWeight_common = 1;
            
            // Select MET
            double MET_E_reco = -9999;
            double MET_phi_reco = -9999;
            
            if(!era.compare("2016"))
            {
                MET_E_reco = input->MET_E_reco;
                MET_phi_reco = input->MET_phi_reco;
            }
            
            else if(!era.compare("2017"))
            {
                MET_E_reco = input->METFixEE2017_E_reco;
                MET_phi_reco = input->METFixEE2017_phi_reco;
            }
            
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
                
                
                // Get pile-up reweight factor
                //double pileUpReweightFactor = Common::getPileUpReweightFactor( \
                //    input->h1_pileUp_mc, input->h1_pileUp_data, \
                //    input->pileUp_n_reco);
                //
                ////printf("pileUp %d, pileUpReweightFactor %f \n", input->pileUp_n_reco, pileUpReweightFactor);
                //output_reco->h1_pileUpReweightFactor->Fill(pileUpReweightFactor);
                //
                //eventWeight_common *= pileUpReweightFactor;
            }
            
            
            // Select tau pair
            std::vector <double> v_tau_pTetaCut(input->tau_n_reco, 0);
            std::vector <double> v_tau_IPcut(input->tau_n_reco, 0);
            
            std::vector <double> v_tau_DM(input->tau_n_reco, 0);
            
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
                
                //v_tau_DM.at(iTau) = Common::isTauNewDM(
                //    input->v_tau_byDecayModeFindingNewDMs_reco->at(iTau),
                //    input->v_tau_decayMode_reco->at(iTau)
                //);
                
                v_tau_DM.at(iTau) = Common::isTauNewDM(
                    input->v_tau_decayMode_reco->at(iTau)
                );
            }
            
            
            //std::vector <std::vector <double> *> vv_tau1_selection = {
            //    input->v_tau_isTriggerMatched_reco,
            //    input->v_tau_byDecayModeFinding_reco,
            //    &v_tau_IPcut,
            //    input->v_tau_againstElectronLooseMVA6_reco,
            //    input->v_tau_againstMuonLoose3_reco,
            //    v_tau1_isolation,
            //    &v_tau_pTetaCut
            //};
            //
            //std::vector <std::vector <double> *> vv_tau2_selection = {
            //    input->v_tau_isTriggerMatched_reco,
            //    input->v_tau_byDecayModeFinding_reco,
            //    &v_tau_IPcut,
            //    input->v_tau_againstElectronLooseMVA6_reco,
            //    input->v_tau_againstMuonLoose3_reco,
            //    v_tau2_isolation,
            //    &v_tau_pTetaCut
            //};
            
            
            std::vector <std::vector <double> *> vv_tau1_selection = {
                input->v_tau_isTriggerMatched_reco,
                &v_tau_DM,
                &v_tau_IPcut,
                input->v_tau_byLooseDeepTau2017v2p1VSe_reco,
                input->v_tau_byTightDeepTau2017v2p1VSmu_reco,
                v_tau1_isolation,
                &v_tau_pTetaCut
            };
            
            std::vector <std::vector <double> *> vv_tau2_selection = {
                input->v_tau_isTriggerMatched_reco,
                &v_tau_DM,
                &v_tau_IPcut,
                input->v_tau_byLooseDeepTau2017v2p1VSe_reco,
                input->v_tau_byTightDeepTau2017v2p1VSmu_reco,
                v_tau2_isolation,
                &v_tau_pTetaCut
            };
            
            //printf("tauTau_signOption %s \n", tauTau_signOption);
            
            std::vector <int> tauPair_pos = Common::getObjPair(
                &(input->v_tau_reco),
                &(input->v_tau_reco),
                true,
                vv_tau1_selection,
                vv_tau2_selection,
                Common::tauTau_deltaRcut_reco,
                tauTau_signOption,
                true
            );
            
            
            // Tau-pair must exist
            if(!tauPair_pos.size())
            {
                continue;
            }
            
            CLHEP::HepLorentzVector tauTau_tau1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector tauTau_tau2_4mom_reco(0, 0, 0, 0);
            
            int tauTau_pos1 = tauPair_pos.at(0);
            int tauTau_pos2 = tauPair_pos.at(1);
            
            tauTau_tau1_4mom_reco.setT(fabs(input->v_tau_E_reco->at(tauTau_pos1)));
            tauTau_tau1_4mom_reco.setX(input->v_tau_px_reco->at(tauTau_pos1));
            tauTau_tau1_4mom_reco.setY(input->v_tau_py_reco->at(tauTau_pos1));
            tauTau_tau1_4mom_reco.setZ(input->v_tau_pz_reco->at(tauTau_pos1));
            
            tauTau_tau2_4mom_reco.setT(fabs(input->v_tau_E_reco->at(tauTau_pos2)));
            tauTau_tau2_4mom_reco.setX(input->v_tau_px_reco->at(tauTau_pos2));
            tauTau_tau2_4mom_reco.setY(input->v_tau_py_reco->at(tauTau_pos2));
            tauTau_tau2_4mom_reco.setZ(input->v_tau_pz_reco->at(tauTau_pos2));
            
            std::vector <std::pair <std::vector <CLHEP::HepLorentzVector>, double> > vp_obj4mom_deltaR_min = {
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {tauTau_tau1_4mom_reco}, 
                    0.4
                ),
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {tauTau_tau2_4mom_reco}, 
                    0.4
                )
            };
            
            // b-tagging SF
            //double bTaggingEventWeight = 1;
            //
            //if(isMC)
            //{
            //    BTagCalibrationReader bTagCalibReader_CSVv2M(
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
            //        vp_obj4mom_deltaR_min
            //    );
            //    
            //    output_reco->h1_bTaggingEventWeight_medium->Fill(bTaggingEventWeight);
            //}
            //
            //eventWeight_common *= bTaggingEventWeight;
            
            
            bool areTausLeptonMatched = false;
            bool tau1_isGenElMatched = false;
            bool tau2_isGenElMatched = false;
            bool tau1_isGenMuMatched = false;
            bool tau2_isGenMuMatched = false;
            
            //if(isMC)
            //{
            //    // Gen electron matching
            //    for(int iEl_gen = 0; iEl_gen < input->el_n_gen; iEl_gen++)
            //    {
            //        CLHEP::HepLorentzVector el_4mom_gen;
            //        
            //        el_4mom_gen.setT(fabs(input->v_el_E_gen->at(iEl_gen)));
            //        el_4mom_gen.setX(input->v_el_px_gen->at(iEl_gen));
            //        el_4mom_gen.setY(input->v_el_py_gen->at(iEl_gen));
            //        el_4mom_gen.setZ(input->v_el_pz_gen->at(iEl_gen));
            //        
            //        if(el_4mom_gen.perp() < Common::el_pTcut_elMu_reco || fabs(el_4mom_gen.eta()) > Common::tau_etaCut_tauTau_reco)
            //        {
            //            continue;
            //        }
            //        
            //        //if(!input->v_el_isPrompt_gen->at(iEl_gen))
            //        //{
            //        //    continue;
            //        //}
            //        
            //        if(el_4mom_gen.deltaR(tauTau_tau1_4mom_reco) < 0.3)
            //        {
            //            tau1_isGenElMatched = true;
            //            //break;
            //        }
            //        
            //        else if(el_4mom_gen.deltaR(tauTau_tau2_4mom_reco) < 0.3)
            //        {
            //            tau2_isGenElMatched = true;
            //            //break;
            //        }
            //    }
            //    
            //    
            //    // Gen muon matching
            //    for(int iMu_gen = 0; iMu_gen < input->mu_n_gen; iMu_gen++)
            //    {
            //        CLHEP::HepLorentzVector mu_4mom_gen;
            //        
            //        mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu_gen)));
            //        mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu_gen));
            //        mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu_gen));
            //        mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu_gen));
            //        
            //        if(mu_4mom_gen.perp() < Common::mu_pTcut_elMu_reco || fabs(mu_4mom_gen.eta()) > Common::tau_etaCut_tauTau_reco)
            //        {
            //            continue;
            //        }
            //        
            //        //if(!input->v_mu_isPrompt_gen->at(iMu_gen))
            //        //{
            //        //    continue;
            //        //}
            //        
            //        if(mu_4mom_gen.deltaR(tauTau_tau1_4mom_reco) < 0.3)
            //        {
            //            tau1_isGenMuMatched = true;
            //            //break;
            //        }
            //        
            //        else if(mu_4mom_gen.deltaR(tauTau_tau2_4mom_reco) < 0.3)
            //        {
            //            tau2_isGenMuMatched = true;
            //            //break;
            //        }
            //    }
            //    
            //    //printf("%d %d, %d %d \n", tau1_isGenElMatched, tau1_isGenMuMatched, tau2_isGenElMatched, tau2_isGenMuMatched);
            //    
            //    areTausLeptonMatched = (tau1_isGenElMatched || tau1_isGenMuMatched) && (tau2_isGenElMatched || tau2_isGenMuMatched);
            //}
            
            
            double tauTau_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2(
                tauTau_tau1_4mom_reco.m(), tauTau_tau1_4mom_reco.px(), tauTau_tau1_4mom_reco.py(),
                tauTau_tau2_4mom_reco.m(), tauTau_tau2_4mom_reco.px(), tauTau_tau2_4mom_reco.py(),
                MET_E_reco*cos(input->MET_phi_reco), MET_E_reco*sin(input->MET_phi_reco),
                0, 0
            );
            
            
            //if(tauTau_MET_mT2_lsp0 > 40)
            //{
            //    continue;
            //}
            
            //if(MET_E_reco > 50)
            //{
            //    continue;
            //}
            
            std::vector <std::pair <std::string, double> > vp_symbolVal = {
                std::make_pair("MET_E_reco", MET_E_reco),
            };
            
            if(isMC)
            {
                vp_symbolVal.push_back(std::make_pair("areTausLeptonMatched", areTausLeptonMatched));
                vp_symbolVal.push_back(std::make_pair("tau_vis_n_gen", input->tau_vis_n_gen));
            }
            
            // Event selection
            bool isEventSelected = Common::evaluateExpression(
                eventSelectionStr,
                vp_symbolVal//,
                //true
            );
            
            if(!isEventSelected)
            {
                continue;
            }
            
            if(isMC)
            {
                printf("input->tau_vis_n_gen %d \n", (int) input->tau_vis_n_gen);
                printf("input->el_n_gen %d \n", (int) input->el_n_gen);
                printf("input->mu_n_gen %d \n", (int) input->mu_n_gen);
                printf("%d %d, %d %d \n", tau1_isGenElMatched, tau1_isGenMuMatched, tau2_isGenElMatched, tau2_isGenMuMatched);
            }
            
            output_reco->v_h1_tau_pT.at(0)->Fill(tauTau_tau1_4mom_reco.perp(), eventWeight_common);
            output_reco->v_h1_tau_eta.at(0)->Fill(tauTau_tau1_4mom_reco.eta(), eventWeight_common);
            output_reco->v_h1_tau_phi.at(0)->Fill(tauTau_tau1_4mom_reco.phi(), eventWeight_common);
            output_reco->v_h1_tau_m.at(0)->Fill(tauTau_tau1_4mom_reco.m(), eventWeight_common);
            
            output_reco->v_h1_tau_pT.at(1)->Fill(tauTau_tau2_4mom_reco.perp(), eventWeight_common);
            output_reco->v_h1_tau_eta.at(1)->Fill(tauTau_tau2_4mom_reco.eta(), eventWeight_common);
            output_reco->v_h1_tau_phi.at(1)->Fill(tauTau_tau2_4mom_reco.phi(), eventWeight_common);
            output_reco->v_h1_tau_m.at(1)->Fill(tauTau_tau2_4mom_reco.m(), eventWeight_common);
            
            output_reco->h1_tau_pT->Fill(tauTau_tau1_4mom_reco.perp(), eventWeight_common);
            output_reco->h1_tau_pT->Fill(tauTau_tau2_4mom_reco.perp(), eventWeight_common);
            
            output_reco->h2_tau_pT_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos1), tauTau_tau1_4mom_reco.perp(), eventWeight_common);
            output_reco->h2_tau_pT_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos2), tauTau_tau2_4mom_reco.perp(), eventWeight_common);
            
            output_reco->h2_tau_nPV_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos1), input->vertex_n_reco, eventWeight_common);
            output_reco->h2_tau_nPV_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos2), input->vertex_n_reco, eventWeight_common);
            
            
            double jet_HT_reco = 0;
            
            int b_n_medium = 0;
            
            for(int iJet = 0; iJet < input->jet_n_reco; iJet++)
            {
                CLHEP::HepLorentzVector jet_4mom_reco;
                
                jet_4mom_reco.setT(fabs(input->v_jet_E_reco->at(iJet)));
                jet_4mom_reco.setX(input->v_jet_px_reco->at(iJet));
                jet_4mom_reco.setY(input->v_jet_py_reco->at(iJet));
                jet_4mom_reco.setZ(input->v_jet_pz_reco->at(iJet));
                
                if(jet_4mom_reco.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::jet_etaCut_reco)
                {
                    continue;
                }
                
                
                bool hasTauOverlap = !Common::isSeparated(jet_4mom_reco, &input->v_tau_reco, 0.3, tauPair_pos);
                
                if(hasTauOverlap)
                {
                    continue;
                }
                
                jet_HT_reco += jet_4mom_reco.perp();
                
                // RECO b
                if(jet_4mom_reco.perp() < Common::b_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::b_etaCut_reco)
                {
                    continue;
                }
                
                if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    b_n_medium++;
                }
            }
            
            double tauTau_jet_HT_reco = tauTau_tau1_4mom_reco.perp() + tauTau_tau2_4mom_reco.perp() + jet_HT_reco;
            
            
            output_reco->h2_MET_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos1), MET_E_reco, eventWeight_common);
            output_reco->h2_MET_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos2), MET_E_reco, eventWeight_common);
            
            output_reco->h2_tauTau_MET_mT2_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos1), tauTau_MET_mT2_lsp0, eventWeight_common);
            output_reco->h2_tauTau_MET_mT2_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos2), tauTau_MET_mT2_lsp0, eventWeight_common);
            
            output_reco->h2_tauTau_jet_HT_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos1), tauTau_jet_HT_reco, eventWeight_common);
            output_reco->h2_tauTau_jet_HT_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos2), tauTau_jet_HT_reco, eventWeight_common);
            
            output_reco->h2_b_n_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos1), b_n_medium, eventWeight_common);
            output_reco->h2_b_n_vs_DM->Fill(input->v_tau_decayMode_reco->at(tauTau_pos2), b_n_medium, eventWeight_common);
        }
    }
}


# endif

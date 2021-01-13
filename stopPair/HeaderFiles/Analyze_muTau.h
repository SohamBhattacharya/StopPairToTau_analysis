# ifndef Analyze_muTau_H
# define Analyze_muTau_H


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
# include "ElMuScaleFactor.h"
# include "Output_GEN.h"
# include "Output_RECO.h"
# include "TauEfficiencyAndSF.h"
# include "TauTriggerSFs2017.h"


namespace Analyze_muTau
{
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::vector <double> v_eventWeight_nJetBin,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::vector <double> v_eventWeight_nJetBin,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    );
    
    
    void analyze_gen(CustomInfo_mc::Info *input,
        Output_GEN::Output *output_gen,
        const char *muTau_signOption,
        std::map <std::string, bool> m_eventSelection,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1
    );
    
    
    template <typename T1> void analyze_reco(
        T1 *input,
        Output_RECO::Output *output_reco,
        std::map <std::pair <int, int>, Output_RECO::Output*> *m_output_reco,
        const char *tau_isoOption,
        const char *muTau_signOption,
        //std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::vector <double> v_eventWeight_nJetBin,
        ElMuScaleFactor::ScaleFactor *muIdIsoSFobject,
        std::map <std::string, ElMuScaleFactor::ScaleFactor*> *m_muTriggerSFobject,
        TauEfficiencyAndSF::TauFastFullSF *tauFastFullSimSFinfo,
        nlohmann::json diTauTrigger2016json,
        std::map <std::string, TauTriggerSFs2017*> m_diTauTrigger2017,
        RooWorkspace *htt_scaleFactorWS,
        BTagCalibration *bTagCalib,
        std::string fileName_bTaggingEfficiency,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex,
        bool tauGenMatching = false,
        double tauGenMatching_deltaRcut = 9999
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        if(isSUSY)
        {
            std::map <std::pair <int, int>, Output_RECO::Output*>::iterator iter;
            
            for(iter = m_output_reco->begin(); iter != m_output_reco->end(); iter++)
            {
                iter->second->addMuHist(1);
                iter->second->addTauHist(1);
                iter->second->addbHist(2);
                iter->second->addJetHist(2);
                iter->second->addNonBjetHist(2);
            }
        }
        
        else
        {
            output_reco->addMuHist(1);
            output_reco->addTauHist(1);
            output_reco->addbHist(2);
            output_reco->addJetHist(2);
            output_reco->addNonBjetHist(2);
        }
        
        // If no event selection provided, selection is always true
        if(!eventSelectionStr.length())
        {
            eventSelectionStr = "1";
        }
        
        for(int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            input->T_reco->GetEntry(iEvent);
            
            if(isMC)
            {
                input->T_gen->GetEntry(iEvent);
            }
            
            // Select mass point
            if(isSUSY)
            {
                //printf("stop1_m_genParam %f, neutralino1_m_genParam %f \n", input->stop1_m_genParam, input->neutralino1_m_genParam);
                
                //if((massPoint_stop1_neutralino1.first >= 0 && input->stop1_m_genParam != massPoint_stop1_neutralino1.first) || \
                //    (massPoint_stop1_neutralino1.second >= 0 && input->neutralino1_m_genParam != massPoint_stop1_neutralino1.second))
                //{
                //    continue;
                //}
                
                std::pair <int, int> p_temp(
                    (int) input->stop1_m_genParam,
                    (int) input->neutralino1_m_genParam
                );
                
                //printf("Event mass-point [%d, %d]. \n", p_temp.first, p_temp.second);
                
                if(m_output_reco->find(p_temp) == m_output_reco->end())
                {
                    continue;
                }
                
                output_reco = m_output_reco->at(p_temp);
            }
            
            
            if(iEvent == 0 || (iEvent+1) % 1000 == 0 || iEvent == nEvent-1)
            {
                printf("[%s] Processing event no. %d / %d \n", output_reco->nameAddon, iEvent+1, nEvent);
                fflush(stdout);
            }
            
            if(tauGenMatching && !isMC)
            {
                printf("Error in Analyze_muTau::analyze_reco(...): \"tauGenMatching\" cannot be true if \"isMC\" is false. \n");
                exit(EXIT_FAILURE);
            }
            
            if(tauGenMatching && tauGenMatching_deltaRcut == 9999)
            {
                printf("Error in Analyze_muTau::analyze_reco(...): Provide a valid \"tauGenMatching_deltaRcut\". \n");
                exit(EXIT_FAILURE);
            }
            
            
            double eventWeight_common = 1;
            
            double ZpTreweightFactor = 1;
            
            CLHEP::HepLorentzVector Z_gen_4mom;
            
            // Theory (generator) event weights here
            if(isMC)
            {
                if(scaleVariationIndex >= input->v_scaleWeight.size())
                {
                    printf("Error in Analyze_muTau::analyze_reco(...): \"scaleVariationIndex\" (= %d) must be LESS than %d. \n", scaleVariationIndex, (int) input->v_scaleWeight.size());
                    exit(EXIT_FAILURE);
                }
                
                
                double scaleWeight = input->v_scaleWeight.at(scaleVariationIndex);
                //printf("[%d] scale-weight %0.4f \n", iEvent+1, scaleWeight);
                
                eventWeight_common *= scaleWeight;
            }
            
            
            //////////////////////////////////////////////////
            output_reco->h1_nEvent->Fill(0.0, eventWeight_common);
            //////////////////////////////////////////////////
            
            
            //if(input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v || input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v)
            //{
            //    printf("[%s] Event %d: Trigger passed (%0.1f, %0.1f). \n",
            //        output_reco->nameAddon, iEvent+1,
            //        input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v,
            //        input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v
            //    );
            //}
            
            if(isMC)
            {
                // n-jet bin stitching event weight
                if(v_eventWeight_nJetBin.size())
                {
                    double eventWeight_nJetBin = Common::getEventWeight_nJetBin(v_eventWeight_nJetBin, input->outgoingParton_n_gen);
                    //printf("eventWeight_nJetBin: %d %f \n", input->outgoingParton_n_gen, eventWeight_nJetBin);
                    
                    eventWeight_common *= eventWeight_nJetBin;
                }
                
                // Z-pT reweighting
                if(m_correction.at(Common::ZptReweighting_str) && input->Z_n_gen > 0)
                {
                    Z_gen_4mom.setT(fabs(input->v_Z_gen.at(0)->at(0)));
                    Z_gen_4mom.setX(input->v_Z_gen.at(1)->at(0));
                    Z_gen_4mom.setY(input->v_Z_gen.at(2)->at(0));
                    Z_gen_4mom.setZ(input->v_Z_gen.at(3)->at(0));
                    
                    
                    if(!strcmp(era, "2016"))
                    {
                        htt_scaleFactorWS->var("z_gen_mass")->setVal(Z_gen_4mom.m());
                    }
                    
                    htt_scaleFactorWS->var("z_gen_pt")->setVal(Z_gen_4mom.perp());
                    
                    //ZpTreweightFactor = htt_scaleFactorWS->function("zpt_weight_nom")->getVal();
                    ZpTreweightFactor = Common::getZpTreweightFactor(
                        Z_gen_4mom,
                        htt_scaleFactorWS,
                        std::string(era),
                        chooseSystType(syst_name, "ZpTreweight", syst_type)
                    ).first;
                    
                    //printf(
                    //    "[%d] Z: m %0.2f, pT %0.2f, SF %0.4f \n",
                    //    iEvent+1, 
                    //    Z_gen_4mom.m(),
                    //    Z_gen_4mom.perp(),
                    //    ZpTreweightFactor
                    //);
                    
                    output_reco->h1_ZpTreweightFactor->Fill(ZpTreweightFactor);
                    output_reco->h2_ZpTreweightFactor_vs_pT->Fill(Z_gen_4mom.perp(), ZpTreweightFactor);
                    output_reco->h2_ZpTreweightFactor_vs_m->Fill(Z_gen_4mom.m(), ZpTreweightFactor);
                    
                    eventWeight_common *= ZpTreweightFactor;
                }
            }
            
            //output_reco->getCutFlow("tau_n = 0")->at(0)++;
            //output_reco->getCutFlow("tau_n = 1")->at(0)++;
            //output_reco->getCutFlow("tau_n >= 2")->at(0)++;
            //output_reco->getCutFlow("cutFlow1")->at(0) += eventWeight_common;
            
            for(int iSRA = 0; iSRA < 6; iSRA++)
            {
                output_reco->getCutFlow(("SRA"+std::to_string(iSRA+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            for(int iSRB = 0; iSRB < 18; iSRB++)
            {
                output_reco->getCutFlow(("SRB"+std::to_string(iSRB+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            for(int iSRC = 0; iSRC < 18; iSRC++)
            {
                output_reco->getCutFlow(("SRC"+std::to_string(iSRC+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            for(int iSRD = 0; iSRD < 18; iSRD++)
            {
                output_reco->getCutFlow(("SRD"+std::to_string(iSRD+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            
            // Trigger
            //if(!(
            //    // 2016
            //    input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v ||
            //    input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v ||
            //    
            //    //2017
            //    input->isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v ||
            //    input->isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v ||
            //    input->isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v ||
            //    
            //    isSUSY /*||
            //    
            //    !strcmp(era, "2017") ***** TEST TEST TEST ***** */
            //))
            //{
            //    continue;
            //}
            
            // Trigger
            if(!(
                // 2016
                input->isTriggerPassed_HLT_IsoMu24_v ||
                input->isTriggerPassed_HLT_IsoTkMu24_v ||
                
                //2017
                input->isTriggerPassed_HLT_IsoMu27_v
            ))
            {
                continue;
            }
            
            //printf("Passed trigger selection. \n");
            
            
            // Select MET
            double MET_E_reco = -9999;
            double MET_phi_reco = -9999;
            
            if(!syst_name.compare("JEC"))
            {
                MET_E_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JEC", syst_type)).at("E"));
                MET_phi_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JEC", syst_type)).at("phi"));
            }
            
            if(!syst_name.compare("JER"))
            {
                MET_E_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JER", syst_type)).at("E"));
                MET_phi_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JER", syst_type)).at("phi"));
            }
            
            if(!syst_name.compare("unclusteredEnergy"))
            {
                MET_E_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "unclusteredEnergy", syst_type)).at("E"));
                MET_phi_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "unclusteredEnergy", syst_type)).at("phi"));
            }
            
            else
            {
                if(!strcmp(era, "2016"))
                {
                    MET_E_reco = input->MET_E_reco;
                    MET_phi_reco = input->MET_phi_reco;
                }
                
                else if(!strcmp(era, "2017"))
                {
                    MET_E_reco = input->METFixEE2017_E_reco;
                    MET_phi_reco = input->METFixEE2017_phi_reco;
                }
            }
            
            //printf("MET: E %0.2f, phi %0.2f \n", MET_E_reco, MET_phi_reco);
            //printf("MET JEC: E %0.2f, phi %0.2f \n", *(input->m_MET_reco.at(std::string(era)).at("JEC").at(chooseSystType(syst_name, "JEC", syst_type)).at("E")), *(input->m_MET_reco.at(std::string(era)).at("JEC").at(chooseSystType(syst_name, "JEC", syst_type)).at("phi")));
            //printf("MET JER: E %0.2f, phi %0.2f \n", *(input->m_MET_reco.at(std::string(era)).at("JER").at(chooseSystType(syst_name, "JER", syst_type)).at("E")), *(input->m_MET_reco.at(std::string(era)).at("JER").at(chooseSystType(syst_name, "JER", syst_type)).at("phi")));
            //printf("MET unclusteredEnergy: E %0.2f, phi %0.2f \n", *(input->m_MET_reco.at(std::string(era)).at("unclusteredEnergy").at(chooseSystType(syst_name, "unclusteredEnergy", syst_type)).at("E")), *(input->m_MET_reco.at(std::string(era)).at("unclusteredEnergy").at(chooseSystType(syst_name, "unclusteredEnergy", syst_type)).at("phi")));
            //fflush(stdout);
            
            
            std::vector <int> muTau_pos;
            std::vector <int> v_nTau;
            
            // Select mu
            std::vector <double> v_mu_pTetacut(input->mu_n_reco, 0);
            std::vector <double> v_mu_IPcut(input->mu_n_reco, 0);
            
            for(int iMu = 0; iMu < input->mu_n_reco; iMu++)
            {
                CLHEP::HepLorentzVector mu_4mom_reco;
                
                mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(iMu)));
                mu_4mom_reco.setX(input->v_mu_px_reco->at(iMu));
                mu_4mom_reco.setY(input->v_mu_py_reco->at(iMu));
                mu_4mom_reco.setZ(input->v_mu_pz_reco->at(iMu));
                
                if(mu_4mom_reco.perp() > Common::mu_pTcut_muMu_reco && fabs(mu_4mom_reco.eta()) < Common::mu_etaCut_muMu_reco)
                {
                    v_mu_pTetacut.at(iMu) = 1;
                }
                
                if(fabs(input->v_mu_dxy_reco->at(iMu)) < Common::mu_dxyCut_reco && fabs(input->v_mu_dz_reco->at(iMu)) < Common::mu_dzCut_reco)
                {
                    v_mu_IPcut.at(iMu) = 1;
                }
            }
            
            std::vector <std::vector <double> *> vv_muSelection = {
                input->v_mu_isMediumMuon_reco,
                &v_mu_IPcut,
                input->v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco,
                &v_mu_pTetacut
            };
            
            // Select tau
            std::vector <double> v_tau_pTetaCut(input->tau_n_reco, 0);
            std::vector <double> v_tau_IPcut(input->tau_n_reco, 0);
            std::vector <double> v_tau_ES(input->tau_n_reco, 1.0);
            
            for(int iTau = 0; iTau < input->tau_n_reco; iTau++)
            {
                if(isMC)
                {
                    v_tau_ES.at(iTau) = TauEfficiencyAndSF::getTauES(
                        (int) input->v_tau_decayMode_reco->at(iTau),
                        std::string(era),
                        chooseSystType(syst_name, "tauES", syst_type)
                    ).first;
                }
            }
            
            // Tau ES
            if(isMC)
            {
                Common::scaleObject4mom(
                    &(input->v_tau_reco),
                    &v_tau_ES
                );
            }
            
            
            for(int iTau = 0; iTau < input->tau_n_reco; iTau++)
            {
                CLHEP::HepLorentzVector tau_4mom_reco;
                
                tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau)));
                tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau));
                tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau));
                tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau));
                
                if(tau_4mom_reco.perp() > Common::tau_pTcut_muTau_reco && fabs(tau_4mom_reco.eta()) < Common::tau_etaCut_muTau_reco)
                {
                    v_tau_pTetaCut.at(iTau) = 1;
                }
                
                if(fabs(input->v_tau_dz_reco->at(iTau)) < Common::tau_dzCut_reco)
                {
                    v_tau_IPcut.at(iTau) = 1;
                }
                
                //if(!strcmp(tau_isoOption, "tight") && input->tau_n_reco >= 2)
                //{
                //    printf("[%s] Event %d: tau %d/%d: %d (%d, %d) \n",
                //        output_reco->nameAddon, iEvent+1,
                //        iTau+1, input->tau_n_reco,
                //        (int) input->v_tau_isTriggerMatched_reco->at(iTau),
                //        (int) input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v,
                //        (int) input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v
                //    );
                //}
                
                //if(iEvent >= 1 && iEvent <= 10)
                //{
                //    printf(
                //        "event %d, tau %d/%d: pT %0.5f, eta %0.5f, phi %0.5f, E %0.5f, ES %0.5f\n",
                //        iEvent+1, iTau+1, input->tau_n_reco,
                //        tau_4mom_reco.perp(), tau_4mom_reco.eta(), tau_4mom_reco.phi(), tau_4mom_reco.e(), v_tau_ES.at(iTau)
                //    );
                //}
                
                //if(isSUSY/* || !strcmp(era, "2017") ***** TEST TEST TEST ***** */)
                //{
                //    input->v_tau_isTriggerMatched_reco->at(iTau) = 1;
                //}
            }
            
            
            std::string tauID_WPname = "";
            std::string tauID_WPname_2016 = "";
            std::string tauID_WPname_2017 = "";
            
            std::string tauTrigger2016WPname = "";
            std::string tauTrigger2017WPname = "";
            
            std::vector <double> *v_tau_iso_reco;
            std::vector <double> *v_tau_iso_reco_2016;
            std::vector <double> *v_tau_iso_reco_2017;
            
            if(!strcmp(tau_isoOption, "loose"))
            {
                v_tau_iso_reco_2016 = input->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                tauID_WPname_2016 = "LooseIsolationMVArun2v1DBdR03oldDMwLT";
                
                v_tau_iso_reco_2017 = input->v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                tauID_WPname_2017 = "LooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                
                tauTrigger2016WPname = "LooseIso";
                tauTrigger2017WPname = "loose";
            }
            
            else if(!strcmp(tau_isoOption, "medium"))
            {
                v_tau_iso_reco_2016 = input->v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco;
                tauID_WPname_2016 = "MediumIsolationMVArun2v1DBdR03oldDMwLT";
                
                v_tau_iso_reco_2017 = input->v_tau_byMediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                tauID_WPname_2017 = "MediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                
                tauTrigger2016WPname = "MediumIso";
                tauTrigger2017WPname = "medium";
            }
            
            else if(!strcmp(tau_isoOption, "tight"))
            {
                v_tau_iso_reco_2016 = input->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                tauID_WPname_2016 = "TightIsolationMVArun2v1DBdR03oldDMwLT";
                
                v_tau_iso_reco_2017 = input->v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                //v_tau_iso_reco_2017 = input->v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco;
                tauID_WPname_2017 = "TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                
                tauTrigger2016WPname = "TightIso";
                tauTrigger2017WPname = "tight";
            }
            
            else
            {
                printf("Wrong tau isolation option. \n");
                exit(EXIT_FAILURE);
            }
            
            if(!strcmp(era, "2016"))
            {
                v_tau_iso_reco = v_tau_iso_reco_2016;
                tauID_WPname = tauID_WPname_2016;
            }
            
            else if(!strcmp(era, "2017"))
            {
                v_tau_iso_reco = v_tau_iso_reco_2017;
                tauID_WPname = tauID_WPname_2017;
            }
            
            
            std::vector <std::vector <double> *> vv_tauSelection = {
                //input->v_tau_isTriggerMatched_reco,
                input->v_tau_byDecayModeFinding_reco,
                &v_tau_IPcut,
                input->v_tau_againstElectronLooseMVA6_reco,
                input->v_tau_againstMuonLoose3_reco,
                v_tau_iso_reco,
                &v_tau_pTetaCut
            };
            
            muTau_pos = Common::getObjPair(
                &(input->v_mu_reco),
                &(input->v_tau_reco),
                false,
                vv_muSelection,
                vv_tauSelection,
                Common::muTau_deltaRcut_reco,
                muTau_signOption
            );
            
            //if(muTau_pos.size()) printf("iEvent %d; getObjPair: %d %d \n", iEvent, muTau_pos.at(0), muTau_pos.at(1));
            
            // Get tau pair
            //std::vector <std::vector <int> > muTau_info = Common::getTauPair(
            //    &(input->v_tau_reco),
            //    {},
            //    vv_tauSelection,
            //    Common::muTau_deltaRcut_reco,
            //    muTau_signOption);
            //
            //
            //muTau_pos = muTau_info[0];
            //v_nTau = muTau_info[1];
            //
            //if(muTau_pos.size()) printf("iEvent %d; getTauPair: %d %d \n", iEvent, muTau_pos.at(0), muTau_pos.at(1));
            
            // v_nTau.size()-<No. of tau-pair selection criteria>
            //for(int iCut = 0; iCut < v_nTau.size()-1; iCut++)
            //{
            //    if(v_nTau[iCut] == 0)
            //    {
            //        output_reco->getCutFlow("tau_n = 0")->at(iCut+1)++;
            //    }
            //}
            //
            //for(int iCut = 0; iCut < v_nTau.size()-1; iCut++)
            //{
            //    if(v_nTau[iCut] == 1)
            //    {
            //        output_reco->getCutFlow("tau_n = 1")->at(iCut+1)++;
            //    }
            //}
            //
            //for(int iCut = 0; iCut < v_nTau.size(); iCut++)
            //{
            //    if(v_nTau[iCut] >= 2)
            //    {
            //        output_reco->getCutFlow("tau_n >= 2")->at(iCut+1)++;
            //    }
            //}
            
            
            // At least 2 taus
            if(!muTau_pos.size())
            {
                continue;
            }
            
            //printf("[%s] Event %d: Found tau-pair. \n", output_reco->nameAddon, iEvent+1);
            
            // Gen-matching
            //if(tauGenMatching)
            //{
            //    std::vector <bool> v_tau_isGenMatched_reco(input->tau_n_reco, false);
            //    std::vector <bool> v_tau_isUsed_gen(input->tau_vis_n_gen, false);
            //    
            //    for(int iTau_reco = 0; iTau_reco < input->tau_n_reco; iTau_reco++)
            //    {
            //        // Check matching only for the selected pair
            //        // No need to check for all the taus
            //        if(iTau_reco != muTau_pos[0] && iTau_reco != muTau_pos[1])
            //        {
            //            continue;
            //        }
            //        
            //        CLHEP::HepLorentzVector tau_4mom_reco;
            //        
            //        tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau_reco)));
            //        tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau_reco));
            //        tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau_reco));
            //        tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau_reco));
            //        
            //        int tau_genMatchedIndex = -1;
            //        int tau_nearestGenIndex = -1;
            //        double deltaR_min = 9999;
            //        
            //        CLHEP::HepLorentzVector tau_nearestGenh_4mom;
            //        CLHEP::HepLorentzVector tau_nearestGen_4mom;
            //        
            //        for(int iTau_gen = 0; iTau_gen < input->tau_vis_n_gen; iTau_gen++)
            //        {
            //            CLHEP::HepLorentzVector tauh_4mom_gen;
            //            
            //            tauh_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(iTau_gen)));
            //            tauh_4mom_gen.setX(input->v_tau_vis_px_gen->at(iTau_gen));
            //            tauh_4mom_gen.setY(input->v_tau_vis_py_gen->at(iTau_gen));
            //            tauh_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(iTau_gen));
            //            
            //            if(tauh_4mom_gen.perp() < Common::tau_pTcut_muTau_reco || fabs(tauh_4mom_gen.eta()) > Common::tau_etaCut_muTau_reco)
            //            {
            //                continue;
            //            }
            //            
            //            // Reject if already used for matching
            //            if(v_tau_isUsed_gen.at(iTau_gen))
            //            {
            //                continue;
            //            }
            //            
            //            double deltaR = tau_4mom_reco.deltaR(tauh_4mom_gen);
            //            
            //            if(deltaR < deltaR_min)
            //            {
            //                deltaR_min = deltaR;
            //                
            //                tau_nearestGenIndex = iTau_gen;
            //                tau_nearestGenh_4mom = tauh_4mom_gen;
            //            }
            //        }
            //        
            //        if(tau_nearestGenIndex >= 0)
            //        {
            //            if(deltaR_min < tauGenMatching_deltaRcut)
            //            {
            //                v_tau_isGenMatched_reco.at(iTau_reco) = true;
            //                
            //                tau_genMatchedIndex = tau_nearestGenIndex;
            //                
            //                v_tau_isUsed_gen.at(tau_genMatchedIndex) = true;
            //            }
            //        }
            //    }
            //    
            //    // Both the taus must be gen-matched
            //    if(!v_tau_isGenMatched_reco.at(muTau_pos[0]) || !v_tau_isGenMatched_reco.at(muTau_pos[1]))
            //    {
            //        continue;
            //    }
            //}
            
            CLHEP::HepLorentzVector muTau_mu_4mom_reco, muTau_tau_4mom_reco;
            
            muTau_mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(muTau_pos[0])));
            muTau_mu_4mom_reco.setX(input->v_mu_px_reco->at(muTau_pos[0]));
            muTau_mu_4mom_reco.setY(input->v_mu_py_reco->at(muTau_pos[0]));
            muTau_mu_4mom_reco.setZ(input->v_mu_pz_reco->at(muTau_pos[0]));
            
            muTau_tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(muTau_pos[1])));
            muTau_tau_4mom_reco.setX(input->v_tau_px_reco->at(muTau_pos[1]));
            muTau_tau_4mom_reco.setY(input->v_tau_py_reco->at(muTau_pos[1]));
            muTau_tau_4mom_reco.setZ(input->v_tau_pz_reco->at(muTau_pos[1]));
            
            //printf("muTau_signOption: %s, iEvent %d, muTau_m %f \n", muTau_signOption, iEvent, (muTau_mu_4mom_reco+muTau_tau_4mom_reco).m());
            
            //printf("tau pos: (%d, %d); E1*E2 < 0: %d (%s) \n", muTau_pos[0], muTau_pos[1], (input->v_tau_E_reco->at(muTau_pos[0])*input->v_tau_E_reco->at(muTau_pos[1]) < 0), muTau_signOption);
            
            std::vector <std::pair <std::vector <CLHEP::HepLorentzVector>, double> > vp_obj4mom_deltaR_min = {
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {muTau_mu_4mom_reco}, 
                    0.4
                ),
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {muTau_tau_4mom_reco}, 
                    0.3
                )
            };
            
            double bTaggingEventWeight = 1;
            
            if(isMC)
            {
                //if(!strcmp(era, "2016"))
                {
                    // Get pile-up reweight factor
                    double pileUpReweightFactor = Common::getPileUpReweightFactor(
                        input->h1_pileUp_mc, input->choosePileUpHist_data(chooseSystType(syst_name, "pileupReweight", syst_type)),
                        input->pileUp_n_reco
                    );
                    
                    //printf("pileUp %d, pileUpReweightFactor %f \n", input->pileUp_n_reco, pileUpReweightFactor);
                    output_reco->h1_pileUpReweightFactor->Fill(pileUpReweightFactor);
                    eventWeight_common *= pileUpReweightFactor;
                }
                
                // Top pT reweighting
                double eventWeight_topPt = 1.0;
                
                if(m_correction.at(Common::topPtReweighting_str))
                {
                    
                    std::pair <std::pair <double, double>, std::pair <double, double> > topPtReweightFactor_info = Common::getTopPtReweightFactor(
                        &input->v_t_gen,
                        chooseSystType(syst_name, "topPtReweight", syst_type)
                    );
                    
                    eventWeight_topPt = topPtReweightFactor_info.first.first;
                    
                    output_reco->h1_topPtReweightFactor->Fill(eventWeight_topPt);
                    output_reco->h2_top1PtReweightFactor_vs_pT->Fill(topPtReweightFactor_info.second.first, eventWeight_topPt);
                    output_reco->h2_top2PtReweightFactor_vs_pT->Fill(topPtReweightFactor_info.second.second, eventWeight_topPt);
                }
                
                eventWeight_common *= eventWeight_topPt;
                
                
                //########## 1. 2017 PU
                //########## 2. 2017 b-tag SF
                //########## 3. Apply b-tag SF before filling histograms
                
                
                // Mu1 Id-iso SF
                double muTau_mu_muIdIsoSF = muIdIsoSFobject->get_ScaleFactor(muTau_mu_4mom_reco.perp(), muTau_mu_4mom_reco.eta());
                eventWeight_common *= muTau_mu_muIdIsoSF;
                
                output_reco->h1_mu_IdIsoSF->Fill(muTau_mu_muIdIsoSF);
                
                
                // Tau ID efficiency SF
                std::pair <double, double> muTau_tau_IDefficiencySF = TauEfficiencyAndSF::getTauSF(
                    muTau_tau_4mom_reco.perp(), muTau_tau_4mom_reco.eta(), tauID_WPname, std::string(era),
                    chooseSystType(syst_name, "tauIDisoSF", syst_type)
                );
                
                double tauIDefficiencyEventWeight = muTau_tau_IDefficiencySF.first;
                
                output_reco->h1_tauIDefficiencyEventWeight->Fill(tauIDefficiencyEventWeight);
                eventWeight_common *= tauIDefficiencyEventWeight;
                
                
                // Tau Fast-FullSim SF
                double muTau_mu_fastFullSimSF = 1.0;
                double muTau_tau_fastFullSimSF = 1.0;
                
                if(isSUSY)
                {
                    std::pair <double, double> muTau_mu_fastFullSimSFinfo = tauFastFullSimSFinfo->getSF(
                        muTau_mu_4mom_reco.perp(), muTau_mu_4mom_reco.eta(),
                        chooseSystType(syst_name, "tauFastFullSimSF", syst_type)
                    );
                    
                    std::pair <double, double> muTau_tau_fastFullSimSFinfo = tauFastFullSimSFinfo->getSF(
                        muTau_tau_4mom_reco.perp(), muTau_tau_4mom_reco.eta(),
                        chooseSystType(syst_name, "tauFastFullSimSF", syst_type)
                    );
                    
                    muTau_mu_fastFullSimSF = muTau_mu_fastFullSimSFinfo.first;
                    muTau_tau_fastFullSimSF = muTau_tau_fastFullSimSFinfo.first;
                    
                    //printf("[Event %d] muTau_mu: pT %0.2f, eta %0.2f, fastFullSimSF %0.2f, SFerr %0.2f \n", iEvent+1, muTau_mu_4mom_reco.perp(), muTau_mu_4mom_reco.eta(), muTau_mu_fastFullSimSF, muTau_mu_fastFullSimSFinfo.second);
                    //printf("[Event %d] muTau_tau: pT %0.2f, eta %0.2f, fastFullSimSF %0.2f, SFerr %0.2f \n", iEvent+1, muTau_tau_4mom_reco.perp(), muTau_tau_4mom_reco.eta(), muTau_tau_fastFullSimSF, muTau_tau_fastFullSimSFinfo.second);
                }
                
                double tau_fastFullSimSF = muTau_mu_fastFullSimSF * muTau_tau_fastFullSimSF;
                
                eventWeight_common *= tau_fastFullSimSF;
                
                
                //printf(
                //    "muTau_mu: pT %0.2f, eta %0.2f, phi %0.2f, DM %d, eff SF %0.4f, ES %0.5f \n"
                //    "muTau_tau: pT %0.2f, eta %0.2f, phi %0.2f, DM %d, eff SF %0.4f, ES %0.5f \n"
                //    "\n",
                //    muTau_mu_4mom_reco.perp(), muTau_mu_4mom_reco.eta(), muTau_mu_4mom_reco.phi(), (int) input->v_tau_decayMode_reco->at(muTau_pos[0]),
                //    muTau_mu_IDefficiencySF.first, muTau_mu_ES.first,
                //    muTau_tau_4mom_reco.perp(), muTau_tau_4mom_reco.eta(), muTau_tau_4mom_reco.phi(), (int) input->v_tau_decayMode_reco->at(muTau_pos[1]),
                //    muTau_tau_IDefficiencySF.first, muTau_tau_ES.first
                //);
                
                
                
                // Mu trigger SF
                double muTrigSF = 1.0;
                
                if(!strcmp(era, "2016"))
                {
                    muTrigSF = m_muTriggerSFobject->at("IsoMu24_OR_TkIsoMu24")->get_ScaleFactor(muTau_mu_4mom_reco.perp(), muTau_mu_4mom_reco.eta());
                }
                
                if(!strcmp(era, "2017"))
                {
                    muTrigSF = m_muTriggerSFobject->at("IsoMu24_OR_IsoMu27")->get_ScaleFactor(muTau_mu_4mom_reco.perp(), muTau_mu_4mom_reco.eta());
                }
                
                eventWeight_common *= muTrigSF;
                
                output_reco->h1_muTriggerSF->Fill(muTrigSF);
                
                
                // Get b-tagging SF event weight
                // To do: produce bTagging data for the signal
                //if(!isSUSY)
                {
                    // APPLY TO 2017 LATER ///////////////////////////////////////////////////////////////////////////////////////////////
                    //if(!strcmp(era, "2016"))
                    {
                        BTagCalibrationReader bTagCalibReader_CSVv2M( \
                            BTagEntry::OP_MEDIUM,
                            "central",
                            {"up", "down"}
                        );
                        
                        if(isSUSY)
                        {
                            bTagCalibReader_CSVv2M.load(*bTagCalib,
                                BTagEntry::FLAV_B,
                                "fastsim");
                            
                            bTagCalibReader_CSVv2M.load(*bTagCalib,
                                BTagEntry::FLAV_C,
                                "fastsim");
                            
                            bTagCalibReader_CSVv2M.load(*bTagCalib,
                                BTagEntry::FLAV_UDSG,
                                "fastsim");
                        }
                        
                        else
                        {
                            bTagCalibReader_CSVv2M.load(*bTagCalib,
                                BTagEntry::FLAV_B,
                                "comb");
                            
                            bTagCalibReader_CSVv2M.load(*bTagCalib,
                                BTagEntry::FLAV_C,
                                "comb");
                            
                            bTagCalibReader_CSVv2M.load(*bTagCalib,
                                BTagEntry::FLAV_UDSG,
                                "incl");
                        }
                        
                        bTaggingEventWeight = Common::getBTaggingEventWeight(
                            &input->v_jet_reco,
                            Common::b_pTcut_reco, Common::b_etaCut_reco,
                            input->v_jet_partonFlavour_reco,
                            input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
                            &bTagCalibReader_CSVv2M,
                            Common::chooseBTaggingSFsystType(syst_name, "bTaggingSF", syst_type),
                            fileName_bTaggingEfficiency,
                            "bTaggingEff_eff_b_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
                            "bTaggingEff_eff_c_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
                            "bTaggingEff_eff_udsg_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
                            vp_obj4mom_deltaR_min
                        );
                        
                        //printf("bTaggingEventWeight %f \n", bTaggingEventWeight);
                        output_reco->h1_bTaggingEventWeight_medium->Fill(bTaggingEventWeight);
                        //eventWeight_common *= bTaggingEventWeight;
                    }
                }
            }
            
            
            // RECO jet
            //output_reco->h1_jet_n->Fill(input->jet_n_reco, eventWeight_common);
            
            // JEC
            //printf("Starting JEC. \n");
            //fflush(stdout);
            
            Common::scaleObject4mom(
                &(input->v_jet_reco),
                input->m_JECcorr.at(chooseSystType(syst_name, "JEC", syst_type))
            );
            
            //printf("Finished JEC. \n");
            //fflush(stdout);
            
            // JER
            if(isMC)
            {
                //printf("Starting JER. \n");
                //fflush(stdout);
                
                Common::scaleObject4mom(
                    &(input->v_jet_reco),
                    input->m_JERcorr.at(chooseSystType(syst_name, "JER", syst_type))
                );
                
                //printf("Finished JER. \n");
                //fflush(stdout);
            }
            
            int b_n_medium = 0;
            
            double jet_HT_reco = 0;
            
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
                
                
                // Remember to use dR of isolation variable
                bool hasMuOverlap = jet_4mom_reco.deltaR(muTau_mu_4mom_reco) < 0.4;
                bool hasTauOverlap = jet_4mom_reco.deltaR(muTau_tau_4mom_reco) < 0.3;
                
                if(hasMuOverlap || hasTauOverlap)
                {
                    //printf("Event %d: excluding jet %d. \n", iEvent, iJet);
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
            
            double muTau_jet_HT_reco = muTau_mu_4mom_reco.perp() + muTau_tau_4mom_reco.perp() + jet_HT_reco;
            
            
            // Event selection
            bool isEventSelected = Common::evaluateExpression(
                eventSelectionStr,
                {
                    std::make_pair("muTau_m_reco", (muTau_mu_4mom_reco+muTau_tau_4mom_reco).m()),
                    std::make_pair("MET_E_reco", MET_E_reco),
                    std::make_pair("muTau_jet_HT_reco", muTau_jet_HT_reco),
                    std::make_pair("b_n_reco", b_n_medium),
                }//,
                //true
            );
            
            //// Use the SRB selections for now
            //bool isEventSelected = true;
            //
            //isEventSelected = isEventSelected && Common::isEventSelected(
            //    m_eventSelection,
            //    "MET_E_reco >= 50",
            //    MET_E_reco >= 50
            //);
            //
            //isEventSelected = isEventSelected && Common::isEventSelected(
            //    m_eventSelection,
            //    "muTau_jet_HT_reco >= 100",
            //    muTau_jet_HT_reco >= 100
            //);
            //
            //isEventSelected = isEventSelected && Common::isEventSelected(
            //    m_eventSelection,
            //    "b_n_reco == 0",
            //    b_n_medium == 0
            //);
            //
            //isEventSelected = isEventSelected && Common::isEventSelected(
            //    m_eventSelection,
            //    "b_n_reco >= 1",
            //    b_n_medium >= 1
            //);
            
            
            if(!isEventSelected)
            {
                continue;
            }
            
            
            // Apply b-tagging SF if there is any selection on b-jets
            // REMEMBER TO REMOVE IT BEFORE CUTFLOW
            bool isbTaggingEventWeightApplied = false;
            
            if(isMC && eventSelectionStr.find("b_n_reco") != std::string::npos)
            {
                isbTaggingEventWeightApplied = true;
                eventWeight_common *= bTaggingEventWeight;
                //printf("Event %d: isbTaggingEventWeightApplied = True \n", iEvent+1);
            }
            
            
            // MET
            output_reco->h1_MET_E->Fill(MET_E_reco, eventWeight_common);
            output_reco->h1_MET_phi->Fill(MET_phi_reco, eventWeight_common);
            
            // RECO tau
            //output_reco->h1_tau_n->Fill(input->tau_n_reco, eventWeight_common);
            
            int tau_n_reco = 0;
            
            int tau_n_looseIso = 0, \
                tau_n_mediumIso = 0, \
                tau_n_tightIso = 0;
            
            double muTau_MET_mT2 = 0;
            double muTau_MET_mT2_lsp0 = 0;
            
            double MET_pZeta = 0;
            double muTau_pZeta = 0;
            double muTau_MET_pZeta = 0;
            double muTau_MET_Dzeta = 0;
            
            for(int iTau = 0; iTau < input->tau_n_reco; iTau++)
            {
                CLHEP::HepLorentzVector tau_4mom_reco;
                
                tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau)));
                tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau));
                tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau));
                tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau));
                
                if(tau_4mom_reco.perp() < Common::tau_pTcut_muTau_reco \
                    || fabs(tau_4mom_reco.eta()) > Common::tau_etaCut_muTau_reco)
                {
                    continue;
                }
                
                tau_n_reco++;
                
                if(isMC && !input->isGenMatched(tau_4mom_reco, "tau_vis", \
                    0.3, Common::tau_vis_pTcut_gen, Common::tau_vis_etaCut_gen))
                {
                    continue;
                }
                
                if(!input->v_tau_againstElectronLooseMVA6_reco->at(iTau))
                {
                    continue;
                }
                
                if(!input->v_tau_againstMuonLoose3_reco->at(iTau))
                {
                    continue;
                }
                
                //if(input->v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco->at(iTau))
                if(input->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco->at(iTau))
                {
                    output_reco->h1_tau_pT_looseIso->Fill(tau_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_tau_eta_looseIso->Fill(tau_4mom_reco.eta(), eventWeight_common);
                    tau_n_looseIso++;
                }
                
                //if(input->v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco->at(iTau))
                if(input->v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco->at(iTau))
                {
                    output_reco->h1_tau_pT_mediumIso->Fill(tau_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_tau_eta_mediumIso->Fill(tau_4mom_reco.eta(), eventWeight_common);
                    tau_n_mediumIso++;
                }
                
                //if(input->v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco->at(iTau))
                if(input->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco->at(iTau))
                {
                    output_reco->h1_tau_pT_tightIso->Fill(tau_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_tau_eta_tightIso->Fill(tau_4mom_reco.eta(), eventWeight_common);
                    tau_n_tightIso++;
                }
            }
            
            output_reco->h1_tau_n->Fill(tau_n_reco, eventWeight_common);
            
            output_reco->h1_tau_n_looseIso->Fill(tau_n_looseIso, eventWeight_common);
            output_reco->h1_tau_n_mediumIso->Fill(tau_n_mediumIso, eventWeight_common);
            output_reco->h1_tau_n_tightIso->Fill(tau_n_tightIso, eventWeight_common);
            
            //CLHEP::HepLorentzVector muTau_mu_4mom_reco, muTau_tau_4mom_reco;
            
            /*muTau_mu_4mom_reco.setT(fabs(input->v_tau_E_reco->at(muTau_pos[0])));
            muTau_mu_4mom_reco.setX(input->v_tau_px_reco->at(muTau_pos[0]));
            muTau_mu_4mom_reco.setY(input->v_tau_py_reco->at(muTau_pos[0]));
            muTau_mu_4mom_reco.setZ(input->v_tau_pz_reco->at(muTau_pos[0]));
            
            muTau_tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(muTau_pos[1])));
            muTau_tau_4mom_reco.setX(input->v_tau_px_reco->at(muTau_pos[1]));
            muTau_tau_4mom_reco.setY(input->v_tau_py_reco->at(muTau_pos[1]));
            muTau_tau_4mom_reco.setZ(input->v_tau_pz_reco->at(muTau_pos[1]));*/
            
            double muTau_mu_MET_deltaPhi_reco = Common::getDeltaPhi(muTau_mu_4mom_reco.phi(), MET_phi_reco);
            double muTau_tau_MET_deltaPhi_reco = Common::getDeltaPhi(muTau_tau_4mom_reco.phi(), MET_phi_reco);
            double muTau_deltaPhi_reco = Common::getDeltaPhi(muTau_mu_4mom_reco.phi(), muTau_tau_4mom_reco.phi());
            
            CLHEP::Hep3Vector MET_3mom_reco(MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco), 0.0);
            double muTau_mu_MET_mT_reco = Common::getMT_massless(muTau_mu_4mom_reco.v(), MET_3mom_reco);
            double muTau_tau_MET_mT_reco = Common::getMT_massless(muTau_tau_4mom_reco.v(), MET_3mom_reco);
            
            output_reco->h1_muTau_mu_pT->Fill(muTau_mu_4mom_reco.perp(), eventWeight_common);
            output_reco->h1_muTau_mu_eta->Fill(muTau_mu_4mom_reco.eta(), eventWeight_common);
            output_reco->h1_muTau_mu_phi->Fill(muTau_mu_4mom_reco.phi(), eventWeight_common);
            
            output_reco->h1_muTau_tau_pT->Fill(muTau_tau_4mom_reco.perp(), eventWeight_common);
            output_reco->h1_muTau_tau_eta->Fill(muTau_tau_4mom_reco.eta(), eventWeight_common);
            output_reco->h1_muTau_tau_phi->Fill(muTau_tau_4mom_reco.phi(), eventWeight_common);
            
            double lsp_m = 0;
            
            if(isSUSY)
            {
                lsp_m = input->neutralino1_m_genParam;
            }
            
            muTau_MET_mT2 = asymm_mt2_lester_bisect::get_mT2( \
                muTau_mu_4mom_reco.m(), muTau_mu_4mom_reco.px(), muTau_mu_4mom_reco.py(), \
                muTau_tau_4mom_reco.m(), muTau_tau_4mom_reco.px(), muTau_tau_4mom_reco.py(), \
                MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco), \
                lsp_m, lsp_m);
            
            muTau_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2( \
                muTau_mu_4mom_reco.m(), muTau_mu_4mom_reco.px(), muTau_mu_4mom_reco.py(), \
                muTau_tau_4mom_reco.m(), muTau_tau_4mom_reco.px(), muTau_tau_4mom_reco.py(), \
                MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco), \
                0, 0);
            
            output_reco->h1_muTau_m->Fill((muTau_mu_4mom_reco+muTau_tau_4mom_reco).m(), eventWeight_common);
            output_reco->h1_muTau_pT->Fill((muTau_mu_4mom_reco+muTau_tau_4mom_reco).perp(), eventWeight_common);
            output_reco->h1_muTau_deltaPhi->Fill(muTau_deltaPhi_reco, eventWeight_common);
            output_reco->h1_muTau_deltaR->Fill(muTau_mu_4mom_reco.deltaR(muTau_tau_4mom_reco), eventWeight_common);
            output_reco->h1_muTau_MET_mT2->Fill(muTau_MET_mT2, eventWeight_common);
            output_reco->h1_muTau_MET_mT2_lsp0->Fill(muTau_MET_mT2_lsp0, eventWeight_common);
            
            if(m_correction.at(Common::ZptReweighting_str) && input->Z_n_gen > 0)
            {
                output_reco->h1_ZpTreweightFactor_afterBaseline->Fill(ZpTreweightFactor);
                output_reco->h2_ZpTreweightFactor_vs_m_afterBaseline->Fill(Z_gen_4mom.m(), ZpTreweightFactor);
                output_reco->h2_ZpTreweightFactor_vs_pT_afterBaseline->Fill(Z_gen_4mom.perp(), ZpTreweightFactor);
                
                output_reco->h2_ZpTreweightFactor_vs_muTau_m->Fill((muTau_mu_4mom_reco+muTau_tau_4mom_reco).m(), ZpTreweightFactor, eventWeight_common);
                output_reco->h2_ZpTreweightFactor_vs_muTau_pT->Fill((muTau_mu_4mom_reco+muTau_tau_4mom_reco).perp(), ZpTreweightFactor, eventWeight_common);
            }
            
            output_reco->h2_muTau_MET_mT2_vs_MET_E->Fill(MET_E_reco, muTau_MET_mT2_lsp0, eventWeight_common);
            
            //output_reco->h2_MET_vs_muTau_mu_MET_deltaPhi->Fill(muTau_mu_MET_deltaPhi_reco, MET_E_reco, eventWeight_common);
            //output_reco->h2_MET_vs_muTau_tau_MET_deltaPhi->Fill(muTau_tau_MET_deltaPhi_reco, MET_E_reco, eventWeight_common);
            //output_reco->h2_MET_vs_muTau_deltaPhi->Fill(muTau_deltaPhi_reco, MET_E_reco, eventWeight_common);
            //
            //output_reco->h2_muTau_MET_mT2_vs_muTau_mu_MET_deltaPhi->Fill(muTau_mu_MET_deltaPhi_reco, muTau_MET_mT2_lsp0, eventWeight_common);
            //output_reco->h2_muTau_MET_mT2_vs_muTau_tau_MET_deltaPhi->Fill(muTau_tau_MET_deltaPhi_reco, muTau_MET_mT2_lsp0, eventWeight_common);
            //output_reco->h2_muTau_MET_mT2_vs_muTau_deltaPhi->Fill(muTau_deltaPhi_reco, muTau_MET_mT2_lsp0, eventWeight_common);
            
            MET_pZeta = Common::getPzeta(
                {{MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco)}},
                
                {muTau_mu_4mom_reco.px(), muTau_mu_4mom_reco.py()},
                {muTau_tau_4mom_reco.px(), muTau_tau_4mom_reco.py()}
            );
            
            muTau_pZeta = Common::getPzeta(
                {{muTau_mu_4mom_reco.px(), muTau_mu_4mom_reco.py()},
                    {muTau_tau_4mom_reco.px(), muTau_tau_4mom_reco.py()}
                },
                
                {muTau_mu_4mom_reco.px(), muTau_mu_4mom_reco.py()},
                {muTau_tau_4mom_reco.px(), muTau_tau_4mom_reco.py()}
            );
            
            muTau_MET_pZeta = Common::getPzeta(
                {{muTau_mu_4mom_reco.px(), muTau_mu_4mom_reco.py()},
                    {muTau_tau_4mom_reco.px(), muTau_tau_4mom_reco.py()},
                    {MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco)}
                },
                
                {muTau_mu_4mom_reco.px(), muTau_mu_4mom_reco.py()},
                {muTau_tau_4mom_reco.px(), muTau_tau_4mom_reco.py()}
            );
            
            muTau_MET_Dzeta = muTau_MET_pZeta - 1.85*muTau_pZeta;
            
            output_reco->h1_MET_pZeta->Fill(MET_pZeta, eventWeight_common);
            output_reco->h1_muTau_pZeta->Fill(muTau_pZeta, eventWeight_common);
            output_reco->h1_muTau_MET_pZeta->Fill(muTau_MET_pZeta, eventWeight_common);
            output_reco->h1_muTau_MET_Dzeta->Fill(muTau_MET_Dzeta, eventWeight_common);
            
            output_reco->h2_muTau_MET_Dzeta_vs_MET_E->Fill(MET_E_reco, muTau_MET_Dzeta, eventWeight_common);
            
            // Tau constituents
            //CLHEP::HepLorentzVector muTau_mu_chHad1_4mom_reco, muTau_tau_chHad1_4mom_reco;
            //
            //// One-pronged
            //if(input->v_tau_decayMode_reco->at(muTau_pos[0]) <= 2)
            //{
            //    muTau_mu_chHad1_4mom_reco.setT(fabs(input->v_tau_chHad1_E_reco->at(muTau_pos[0])));
            //    muTau_mu_chHad1_4mom_reco.setX(input->v_tau_chHad1_px_reco->at(muTau_pos[0]));
            //    muTau_mu_chHad1_4mom_reco.setY(input->v_tau_chHad1_py_reco->at(muTau_pos[0]));
            //    muTau_mu_chHad1_4mom_reco.setZ(input->v_tau_chHad1_pz_reco->at(muTau_pos[0]));
            //    
            //    output_reco->v_h1_tau_chHad1_pT_by_tau_pT[0]->Fill( \
            //        muTau_mu_chHad1_4mom_reco.perp() / muTau_mu_4mom_reco.perp(), eventWeight_common);
            //}
            //
            //// One-pronged
            //if(input->v_tau_decayMode_reco->at(muTau_pos[1]) <= 2)
            //{
            //    muTau_tau_chHad1_4mom_reco.setT(fabs(input->v_tau_chHad1_E_reco->at(muTau_pos[1])));
            //    muTau_tau_chHad1_4mom_reco.setX(input->v_tau_chHad1_px_reco->at(muTau_pos[1]));
            //    muTau_tau_chHad1_4mom_reco.setY(input->v_tau_chHad1_py_reco->at(muTau_pos[1]));
            //    muTau_tau_chHad1_4mom_reco.setZ(input->v_tau_chHad1_pz_reco->at(muTau_pos[1]));
            //    
            //    output_reco->v_h1_tau_chHad1_pT_by_tau_pT[1]->Fill( \
            //        muTau_tau_chHad1_4mom_reco.perp() / muTau_tau_4mom_reco.perp(), eventWeight_common);
            //}
            
            
            // RECO jet
            //output_reco->h1_jet_n->Fill(input->jet_n_reco, eventWeight_common);
            
            int jet_n_reco = 0;
            int jet_n_eta2p1to2p4_reco = 0;
            
            int jet_tauOverlap_n = 0;
            
            int jet_n_pT20 = 0;
            int jet_n_pT40 = 0;
            int jet_n_pT60 = 0;
            
            int b_n_pT20 = 0;
            int b_n_pT40 = 0;
            int b_n_pT60 = 0;
            
            int b_n_loose = 0;
            b_n_medium = 0;
            int b_n_medium_eta2p1to2p4 = 0;
            int b_n_tight = 0;
            
            double jet_pxSum_reco = 0;
            double jet_pySum_reco = 0;
            
            jet_HT_reco = 0;
            double jet_HT_eta2p1to2p4_reco = 0;
            double jet_MHT_reco = 0;
            
            double muTau_b_pxSum_reco = 0;
            double muTau_b_pySum_reco = 0;
            
            double muTau_b_HT_reco = 0;
            double muTau_b_MHT_reco = 0;
            
            int b_tauOverlap_n = 0;
            int nonBjet_tauOverlap_n = 0;
            
            double nonBjet1_pT = 0;
            
            int nonBjet_n_reco = 0;
            int nonBjet_n_noOverlapCheck = 0;
            
            CLHEP::HepLorentzVector jet1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector jet2_4mom_reco(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector b1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector b2_4mom_reco(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector nonBjet1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector nonBjet2_4mom_reco(0, 0, 0, 0);
            
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
                
                
                //if(!input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                //{
                //    nonBjet_n_noOverlapCheck++;
                //}
                
                // Remember to use dR of isolation variable
                bool hasMuOverlap = jet_4mom_reco.deltaR(muTau_mu_4mom_reco) < 0.4;
                bool hasTauOverlap = jet_4mom_reco.deltaR(muTau_tau_4mom_reco) < 0.3;
                
                if(hasMuOverlap || hasTauOverlap)
                {
                    //printf("Event %d: excluding jet %d. \n", iEvent, iJet);
                    continue;
                }
                
                jet_n_reco++;
                
                if(fabs(jet_4mom_reco.eta()) > 2.1 && fabs(jet_4mom_reco.eta()) < 2.4)
                {
                    output_reco->h1_jet_pT_eta2p1to2p4->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    
                    jet_n_eta2p1to2p4_reco++;
                    jet_HT_eta2p1to2p4_reco += jet_4mom_reco.perp();
                }
                
                if(jet_4mom_reco.perp() > 20)
                {
                    jet_n_pT20++;
                }
                
                if(jet_4mom_reco.perp() > 40)
                {
                    jet_n_pT40++;
                }
                
                if(jet_4mom_reco.perp() > 60)
                {
                    jet_n_pT60++;
                }
                
                jet_pxSum_reco += input->v_jet_px_reco->at(iJet);
                jet_pySum_reco += input->v_jet_py_reco->at(iJet);
                
                jet_HT_reco += jet_4mom_reco.perp();
                
                // Leading jet
                //if(jet_n_reco == 1)
                //{
                //    output_reco->h1_jet1_MET_deltaPhi->Fill(Common::getDeltaPhi(jet_4mom_reco.phi(), MET_phi_reco), eventWeight_common);
                //}
                
                if(jet_4mom_reco.perp() > jet1_4mom_reco.perp())
                {
                    jet1_4mom_reco = jet_4mom_reco;
                }
                
                else if(jet_4mom_reco.perp() > jet2_4mom_reco.perp())
                {
                    jet2_4mom_reco = jet_4mom_reco;
                }
                
                
                // RECO b
                if(jet_4mom_reco.perp() < Common::b_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::b_etaCut_reco)
                {
                    continue;
                }
                
                /*if(isMC && !input->isGenMatched(jet_4mom_reco, "b", 0.3))
                {
                    continue;
                }*/
                
                if(input->v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    output_reco->h1_b_pT_loose->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_b_eta_loose->Fill(jet_4mom_reco.eta(), eventWeight_common);
                    
                    b_n_loose++;
                }
                
                if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    output_reco->h1_b_pT_medium->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_b_eta_medium->Fill(jet_4mom_reco.eta(), eventWeight_common);
                    
                    b_n_medium++;
                    
                    if(fabs(jet_4mom_reco.eta()) > 2.1 && fabs(jet_4mom_reco.eta()) < 2.4)
                    {
                        b_n_medium_eta2p1to2p4++;
                    }
                    
                    if(jet_4mom_reco.perp() > b1_4mom_reco.perp())
                    {
                        b1_4mom_reco = jet_4mom_reco;
                    }
                    
                    else if(jet_4mom_reco.perp() > b2_4mom_reco.perp())
                    {
                        b2_4mom_reco = jet_4mom_reco;
                    }
                    
                    if(jet_4mom_reco.perp() > 20)
                    {
                        b_n_pT20++;
                    }
                    
                    if(jet_4mom_reco.perp() > 40)
                    {
                        b_n_pT40++;
                    }
                    
                    if(jet_4mom_reco.perp() > 60)
                    {
                        b_n_pT60++;
                    }
                    
                    muTau_b_pxSum_reco += jet_4mom_reco.px();
                    muTau_b_pySum_reco += jet_4mom_reco.py();
                    muTau_b_HT_reco += jet_4mom_reco.perp();
                }
                
                else
                {
                    nonBjet_n_reco++;
                    
                    if(nonBjet_n_reco && nonBjet_n_reco <= 2)
                    {
                        output_reco->v_h1_nonBjet_pT[nonBjet_n_reco-1]->Fill(jet_4mom_reco.perp(), eventWeight_common);
                        output_reco->v_h1_nonBjet_eta[nonBjet_n_reco-1]->Fill(jet_4mom_reco.eta(), eventWeight_common);
                        output_reco->v_h1_nonBjet_phi[nonBjet_n_reco-1]->Fill(jet_4mom_reco.phi(), eventWeight_common);
                    }
                    
                    if(jet_4mom_reco.perp() > nonBjet1_4mom_reco.perp())
                    {
                        nonBjet1_4mom_reco = jet_4mom_reco;
                    }
                    
                    else if(jet_4mom_reco.perp() > nonBjet2_4mom_reco.perp())
                    {
                        nonBjet2_4mom_reco = jet_4mom_reco;
                    }
                }
                
                if(input->v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    output_reco->h1_b_pT_tight->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_b_eta_tight->Fill(jet_4mom_reco.eta(), eventWeight_common);
                    
                    b_n_tight++;
                }
            }
            
            if(jet_n_reco >= 1)
            {
                output_reco->v_h1_jet_pT[0]->Fill(jet1_4mom_reco.perp(), eventWeight_common);
                output_reco->v_h1_jet_eta[0]->Fill(jet1_4mom_reco.eta(), eventWeight_common);
                output_reco->v_h1_jet_phi[0]->Fill(jet1_4mom_reco.phi(), eventWeight_common);
            }
            
            if(jet_n_reco >= 2)
            {
                output_reco->v_h1_jet_pT[1]->Fill(jet2_4mom_reco.perp(), eventWeight_common);
                output_reco->v_h1_jet_eta[1]->Fill(jet2_4mom_reco.eta(), eventWeight_common);
                output_reco->v_h1_jet_phi[1]->Fill(jet2_4mom_reco.phi(), eventWeight_common);
            }
            
            output_reco->h1_jet_n->Fill(jet_n_reco, eventWeight_common);
            output_reco->h1_jet_tauOverlap_n->Fill(jet_tauOverlap_n, eventWeight_common);
            
            output_reco->h2_jet_n_eta2p1to2p4_vs_jet_n->Fill(jet_n_reco, jet_n_eta2p1to2p4_reco, eventWeight_common);
            
            output_reco->h1_jet_HT_eta2p1to2p4_by_jet_HT->Fill(jet_HT_eta2p1to2p4_reco/jet_HT_reco, eventWeight_common);
            
            output_reco->h2_b_n_vs_jet_n_pT20->Fill(jet_n_pT20, b_n_pT20, eventWeight_common);
            output_reco->h2_b_n_vs_jet_n_pT40->Fill(jet_n_pT40, b_n_pT40, eventWeight_common);
            output_reco->h2_b_n_vs_jet_n_pT60->Fill(jet_n_pT60, b_n_pT60, eventWeight_common);
            
            if(jet_n_reco)
            {
                jet_MHT_reco = sqrt(jet_pxSum_reco*jet_pxSum_reco + jet_pySum_reco*jet_pySum_reco);
                
                output_reco->h1_jet_HT->Fill(jet_HT_reco, eventWeight_common);
                output_reco->h1_jet_MHT->Fill(jet_MHT_reco, eventWeight_common);
                output_reco->h1_jet_Meff->Fill(jet_HT_reco + jet_MHT_reco, eventWeight_common);
                
                output_reco->h1_b_n_by_jet_n->Fill((double) b_n_medium/jet_n_reco, eventWeight_common);
            }
            
            if(jet_n_reco >= 2)
            {
                output_reco->h1_jet1_jet2_mT->Fill(Common::getMT(jet1_4mom_reco, jet2_4mom_reco), eventWeight_common);
            }
            
            if(nonBjet_n_reco && jet_n_reco)
            {
                output_reco->h1_nonBjet1_pT_by_jet_HT->Fill(nonBjet1_4mom_reco.perp()/jet_HT_reco, eventWeight_common);
            }
            
            /*if(nonBjet_n_noOverlapCheck)
            {
                output_reco->h1_nonBjet_tauOverlap_n_by_nonBjet_n->Fill((double) nonBjet_tauOverlap_n/nonBjet_n_noOverlapCheck, eventWeight_common);
            }*/
            
            if(b_n_medium && jet_n_reco)
            {
                output_reco->h1_b1_pT_by_jet_HT->Fill(b1_4mom_reco.perp()/jet_HT_reco, eventWeight_common);
            }
            
            if(nonBjet_n_reco && b_n_medium)
            {
                output_reco->h1_nonBjet1_pT_by_b1_pT->Fill(nonBjet1_4mom_reco.perp() / b1_4mom_reco.perp(), eventWeight_common);
            }
            
            /*if(b_tauOverlap_n+b_n_medium)
            {
                output_reco->h1_b_tauOverlap_n_by_b_n->Fill((double) b_tauOverlap_n/(b_tauOverlap_n+b_n_medium), eventWeight_common);
            }*/
            
            // RECO b jet hist
            output_reco->h1_b_n_loose->Fill(b_n_loose, eventWeight_common);
            output_reco->h1_b_n_medium->Fill(b_n_medium, eventWeight_common);
            output_reco->h1_b_n_tight->Fill(b_n_tight, eventWeight_common);
            
            output_reco->h2_b_n_eta2p1to2p4_vs_b_n->Fill(b_n_medium, b_n_medium_eta2p1to2p4, eventWeight_common);
            
            if(b_n_medium >= 1)
            {
                output_reco->v_h1_b_pT[0]->Fill(b1_4mom_reco.perp(), eventWeight_common);
                output_reco->v_h1_b_eta[0]->Fill(b1_4mom_reco.eta(), eventWeight_common);
                output_reco->v_h1_b_phi[0]->Fill(b1_4mom_reco.phi(), eventWeight_common);
            }
            
            if(b_n_medium >= 2)
            {
                output_reco->v_h1_b_pT[1]->Fill(b2_4mom_reco.perp(), eventWeight_common);
                output_reco->v_h1_b_eta[1]->Fill(b2_4mom_reco.eta(), eventWeight_common);
                output_reco->v_h1_b_phi[1]->Fill(b2_4mom_reco.phi(), eventWeight_common);
            }
            
            
            double muTau_jet_pxSum_reco = 0;
            double muTau_jet_pySum_reco = 0;
            double muTau_jet_MHT_reco = 0;
            
            muTau_b_pxSum_reco += muTau_mu_4mom_reco.px();
            muTau_b_pxSum_reco += muTau_tau_4mom_reco.px();
            
            muTau_b_pySum_reco += muTau_mu_4mom_reco.py();
            muTau_b_pySum_reco += muTau_tau_4mom_reco.py();
            
            muTau_b_HT_reco += muTau_mu_4mom_reco.perp();
            muTau_b_HT_reco += muTau_tau_4mom_reco.perp();
            
            muTau_b_MHT_reco = sqrt(muTau_b_pxSum_reco*muTau_b_pxSum_reco + muTau_b_pySum_reco*muTau_b_pySum_reco);
            
            muTau_jet_pxSum_reco = muTau_mu_4mom_reco.px() + muTau_tau_4mom_reco.px() + jet_pxSum_reco;
            muTau_jet_pySum_reco = muTau_mu_4mom_reco.py() + muTau_tau_4mom_reco.py() + jet_pySum_reco;
            muTau_jet_MHT_reco = sqrt(muTau_jet_pxSum_reco*muTau_jet_pxSum_reco + muTau_jet_pySum_reco*muTau_jet_pySum_reco);
            
            output_reco->h1_muTau_b_HT->Fill(muTau_b_HT_reco, eventWeight_common);
            output_reco->h1_muTau_b_MHT->Fill(muTau_b_MHT_reco, eventWeight_common);
            
            output_reco->h1_muTau_jet_HT->Fill(muTau_jet_HT_reco, eventWeight_common);
            output_reco->h1_muTau_jet_MHT->Fill(muTau_jet_MHT_reco, eventWeight_common);
            
            if(muTau_jet_HT_reco > 0)
            {
                output_reco->h1_muTau_b_HT_by_muTau_jet_HT->Fill(muTau_b_HT_reco/muTau_jet_HT_reco, eventWeight_common);
            }
            
            else
            {
                output_reco->h1_muTau_b_HT_by_muTau_jet_HT->Fill(-1, eventWeight_common);
            }
            
            if(muTau_jet_MHT_reco > 0)
            {
                output_reco->h1_muTau_b_MHT_by_muTau_jet_MHT->Fill(muTau_b_MHT_reco/muTau_jet_MHT_reco, eventWeight_common);
            }
            
            else
            {
                output_reco->h1_muTau_b_MHT_by_muTau_jet_MHT->Fill(-1, eventWeight_common);
            }
            
            
            // lblb mT2
            double muBtauB_MET_mT2_lsp0 = 0;
            
            if(muTau_pos.size())
            {
                if(b_n_medium >= 2)
                {
                    muBtauB_MET_mT2_lsp0 = Common::get_lepBlepB_mT2(
                        muTau_mu_4mom_reco,
                        b1_4mom_reco,
                        muTau_tau_4mom_reco,
                        b2_4mom_reco,
                        MET_E_reco*cos(MET_phi_reco),
                        MET_E_reco*sin(MET_phi_reco)
                    );
                }
                
                // Use nonBjet1 as b2 if there is only 1 b jet
                else if(b_n_medium == 1 && jet_n_reco >= 2)
                {
                    muBtauB_MET_mT2_lsp0 = Common::get_lepBlepB_mT2(
                        muTau_mu_4mom_reco,
                        b1_4mom_reco,
                        muTau_tau_4mom_reco,
                        nonBjet1_4mom_reco,
                        MET_E_reco*cos(MET_phi_reco),
                        MET_E_reco*sin(MET_phi_reco)
                    );
                }
            }
            
            output_reco->h1_muBtauB_MET_mT2_lsp0->Fill(muBtauB_MET_mT2_lsp0, eventWeight_common);
            
            
            // cutFlows
            std::vector <double> v_eventWeight;
            std::vector <double> v_selectionVar;
            
            // REMOVE b-tagging weight for cut-flows as it is to be applied to last stage only
            if(isbTaggingEventWeightApplied)
            {
                eventWeight_common /= bTaggingEventWeight;
                //printf("Event %d: Removing  bTaggingEventWeight before filling cut-flows. \n", iEvent+1);
            }
            
            // SRA
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("SRA1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight;
            
            v_selectionVar = {
                (double) muTau_pos.size(),
                muTau_MET_mT2_lsp0,
                MET_E_reco,
                //(double) jet_n_reco,
                (double) b_n_medium
            };
            
            output_reco->updateBins(
                "SRA",
                Common::vv_cut_SRA,
                v_selectionVar,
                v_eventWeight,
                1
            );
            
            
            // SRB
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("SRB1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight;
            
            v_selectionVar = {
                (double) muTau_pos.size(),
                muTau_MET_mT2_lsp0,
                MET_E_reco,
                muTau_jet_HT_reco,
                //(double) jet_n_reco,
                (double) b_n_medium
            };
            
            output_reco->updateBins(
                "SRB",
                Common::vv_cut_SRB,
                v_selectionVar,
                v_eventWeight,
                1
            );
            
            
            // SRC
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("SRC1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight;
            
                v_selectionVar = {
                (double) muTau_pos.size(),
                muBtauB_MET_mT2_lsp0,
                MET_E_reco,
                muTau_jet_HT_reco,
                //(double) jet_n_reco,
                (double) b_n_medium
            };
            
            
            output_reco->updateBins(
                "SRC",
                Common::vv_cut_SRC,
                v_selectionVar,
                v_eventWeight,
                1
            );
            
            
            // SRD
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("SRD1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight;
            
                v_selectionVar = {
                (double) muTau_pos.size(),
                muTau_MET_mT2_lsp0,
                MET_E_reco,
                muBtauB_MET_mT2_lsp0,
                //(double) jet_n_reco,
                (double) b_n_medium
            };
            
            
            output_reco->updateBins(
                "SRD",
                Common::vv_cut_SRD,
                v_selectionVar,
                v_eventWeight,
                1
            );
        }
    }
}


# endif

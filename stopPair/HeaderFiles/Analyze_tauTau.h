# ifndef Analyze_tauTau_H
# define Analyze_tauTau_H


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
//# include "TauTriggerSFs2017.h"
# include "TauTriggerSFProvider.h"
# include "TauIDSFTool.h"



namespace Analyze_tauTau
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
        const char *tauPair_signOption,
        std::map <std::string, bool> m_eventSelection,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1
    );
    
    
    template <typename T1> void analyze_reco(
        T1 *input,
        Output_RECO::Output *output_reco,
        std::map <std::pair <int, int>, Output_RECO::Output*> *m_output_reco,
        const char *tau_isoOption,
        const char *tauPair_signOption,
        //std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::vector <double> v_eventWeight_nJetBin,
        std::vector <std::vector <double> > vv_ISRinfo,
        TauEfficiencyAndSF::TauFastFullSF *tauFastFullSimSFinfo,
        tau_trigger::SFProvider *tauTriggerSFobj,
        TauIDSFTool *tauIDSFobj,
        RooWorkspace *htt_scaleFactorWS,
        BTagCalibration *bTagCalib,
        std::string fileName_bTaggingEfficiency,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex,
        std::vector <nlohmann::json> v_runJson,
        bool tauGenMatching = false,
        double tauGenMatching_deltaRcut = 0.3
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        if(isSUSY)
        {
            std::map <std::pair <int, int>, Output_RECO::Output*>::iterator iter;
            
            for(iter = m_output_reco->begin(); iter != m_output_reco->end(); iter++)
            {
                iter->second->addTauHist(2);
                iter->second->addbHist(2);
                iter->second->addJetHist(3);
                iter->second->addNonBjetHist(2);
            }
        }
        
        else
        {
            output_reco->addTauHist(2);
            output_reco->addbHist(2);
            output_reco->addJetHist(3);
            output_reco->addNonBjetHist(2);
        }
        
        // If no event selection provided, selection is always true
        if(!eventSelectionStr.length())
        {
            eventSelectionStr = "1";
        }
        
        int nEventSkipped = 0;
        
        for(int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            int eventReadResult = input->T_reco->GetEntry(iEvent);
            
            //printf("[%d] eventReadResult %d \n", iEvent+1, eventReadResult);
            
            if(eventReadResult == -1)
            {
                printf("[%s] Problem reading event %d from tree. Skipping this event. \n", output_reco->nameAddon, iEvent+1);
                
                nEventSkipped++;
                
                continue;
            }
            
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
                printf("Error in Analyze_tauTau::analyze_reco(...): \"tauGenMatching\" cannot be true if \"isMC\" is false. \n");
                exit(EXIT_FAILURE);
            }
            
            if(tauGenMatching && tauGenMatching_deltaRcut == 9999)
            {
                printf("Error in Analyze_tauTau::analyze_reco(...): Provide a valid \"tauGenMatching_deltaRcut\". \n");
                exit(EXIT_FAILURE);
            }
            
            
            // Use run JSON (if not empty)
            if(!isMC && v_runJson.size())
            {
                bool isInJson = false;
                
                for(int iJson = 0; iJson < v_runJson.size(); iJson++)
                {
                    //printf("Run JSON %d: \n", iJson);
                    
                    isInJson = Common::isInRunJson(
                        v_runJson.at(iJson),
                        input->runNumber,
                        input->luminosityNumber,
                        //true
                        false
                    );
                    
                    if(isInJson)
                    {
                        break;
                    }
                }
                
                if(!isInJson)
                {
                    //printf("Event not in run JSON. Continuing. \n");
                    
                    continue;
                }
            }
            
            
            double eventWeight_common = 1;
            
            double ZpTreweightFactor = 1;
            
            CLHEP::HepLorentzVector Z_gen_4mom;
            
            // Theory (generator) event weights here
            if(isMC)
            {
                if(scaleVariationIndex >= input->v_scaleWeight.size())
                {
                    printf("Error in Analyze_tauTau::analyze_reco(...): \"scaleVariationIndex\" (= %d) must be LESS than %d. \n", scaleVariationIndex, (int) input->v_scaleWeight.size());
                    exit(EXIT_FAILURE);
                }
                
                
                double scaleWeight = input->v_scaleWeight.at(scaleVariationIndex);
                //printf("[%d] scale-weight %0.4f \n", iEvent+1, scaleWeight);
                
                eventWeight_common *= scaleWeight;
            }
            
            
            // ISR reweighting
            /*if(isSUSY)
            {
                int jet_nISR_reco = 0;
                
                for(int iJet = 0; iJet < input->jet_n_reco; iJet++)
                {
                    if(!input->v_jet_isISR_reco->at(iJet))
                    {
                        continue;
                    }
                    
                    CLHEP::HepLorentzVector jet_4mom_reco;
                    
                    jet_4mom_reco.setT(fabs(input->v_jet_E_reco->at(iJet)));
                    jet_4mom_reco.setX(input->v_jet_px_reco->at(iJet));
                    jet_4mom_reco.setY(input->v_jet_py_reco->at(iJet));
                    jet_4mom_reco.setZ(input->v_jet_pz_reco->at(iJet));
                    
                    if(jet_4mom_reco.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::jet_etaCut_reco)
                    {
                        continue;
                    }
                    
                    jet_nISR_reco++;
                }
                
                double ISRweight = 1;
                
                if(jet_nISR_reco < Common::v_ISRweight.size())
                {
                    ISRweight = Common::v_ISRweight.at(jet_nISR_reco);
                }
                
                else
                {
                    ISRweight = Common::v_ISRweight.at(Common::v_ISRweight.size()-1);
                }
                
                for(int iMass = 0; iMass < vv_ISRinfo.size(); iMass++)
                {
                    if(vv_ISRinfo.at(iMass).at(0) == input->stop1_m_genParam && vv_ISRinfo.at(iMass).at(1) == input->neutralino1_m_genParam)
                    {
                        //printf("[%s] nISR %d, weight %0.2f, normFactor %0.2f \n", output_reco->nameAddon, ISRweight, vv_ISRinfo.at(iMass).at(2));
                        
                        // Multiply by normalization factor
                        ISRweight *= vv_ISRinfo.at(iMass).at(2);
                        
                        break;
                    }
                }
                
                eventWeight_common *= ISRweight;
                output_reco->h1_ISRreweightFactor->Fill(ISRweight);
            }*/
            
            
            //////////////////////////////////////////////////
            output_reco->h1_nEvent->Fill(0.0, eventWeight_common);
            //////////////////////////////////////////////////
            
            
            
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
                    
                    
                    // TEST TEST TEST //
                    // Comment out for DYCR //
                    eventWeight_common *= ZpTreweightFactor;
                }
            }
            
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
            
            //for(int iDYCR = 0; iDYCR < 18; iDYCR++)
            //{
            //    output_reco->getCutFlow(("DYCR"+std::to_string(iDYCR+1)).c_str())->Fill(0.0, eventWeight_common);
            //}
            
            // Trigger
            if(!(
                // 2016
                input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v ||
                input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v ||
                
                //2017
                input->isTriggerPassed_HLT_DoubleTightChargedIsoPFTau35_Trk1_TightID_eta2p1_Reg_v ||
                input->isTriggerPassed_HLT_DoubleMediumChargedIsoPFTau40_Trk1_TightID_eta2p1_Reg_v ||
                input->isTriggerPassed_HLT_DoubleTightChargedIsoPFTau40_Trk1_eta2p1_Reg_v ||
                
                isSUSY /*||
                
                !strcmp(era, "2017") ***** TEST TEST TEST ***** */
            ))
            {
                continue;
            }
            
            //printf("Passed trigger selection. \n");
            
            
            // GEN MET
            double MET_E_gen = -9999;
            double MET_phi_gen = -9999;
            
            if(isMC)
            {
                MET_E_gen = input->MET_E_gen;
                MET_phi_gen = input->MET_phi_gen;
                
                if(!strcmp(era, "2017"))
                {
                    double MET_px = MET_E_gen * cos(MET_phi_gen);
                    double MET_py = MET_E_gen * sin(MET_phi_gen);
                    
                    // MET correction due to EE noise in 2017
                    // Must be done at GEN level also for consistency
                    for(int iJet = 0; iJet < input->jet_n_gen; iJet++)
                    {
                        CLHEP::HepLorentzVector jet_4mom_gen;
                        
                        jet_4mom_gen.setT(fabs(input->v_jet_E_gen->at(iJet)));
                        jet_4mom_gen.setX(input->v_jet_px_gen->at(iJet));
                        jet_4mom_gen.setY(input->v_jet_py_gen->at(iJet));
                        jet_4mom_gen.setZ(input->v_jet_pz_gen->at(iJet));
                        
                        if(
                            jet_4mom_gen.perp() > 50 ||
                            !(fabs(jet_4mom_gen.eta()) > 2.65 && fabs(jet_4mom_gen.eta()) < 3.139)
                        )
                        {
                            continue;
                        }
                        
                        MET_px += jet_4mom_gen.px();
                        MET_py += jet_4mom_gen.py();
                    }
                    
                    MET_E_gen = sqrt(MET_px*MET_px + MET_py*MET_py);
                    MET_phi_gen = atan2(MET_py, MET_px);
                    
                    //printf(
                    //    "GEN E %0.2f, GEN phi %0.2f, "
                    //    "GEN uncorr E %0.2f, GEN uncorr phi %0.2f, "
                    //    "RECO E %0.2f, RECO phi %0.2f \n",
                    //    MET_E_reco, MET_phi_reco,
                    //    input->MET_E_gen, input->MET_phi_gen,
                    //    input->METFixEE2017_E_reco, input->METFixEE2017_phi_reco
                    //);
                }
            }
            
            
            // Select MET
            double MET_E_reco = -9999;
            double MET_phi_reco = -9999;
            
            if(!syst_name.compare("JEC"))
            {
                MET_E_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JEC", syst_type)).at("E"));
                MET_phi_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JEC", syst_type)).at("phi"));
            }
            
            else if(!syst_name.compare("JER"))
            {
                MET_E_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JER", syst_type)).at("E"));
                MET_phi_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JER", syst_type)).at("phi"));
            }
            
            else if(!syst_name.compare("unclusteredEnergy"))
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
                    
                    if(isSUSY && !syst_name.compare("withGenMET"))
                    {
                        //printf("Using GEN MET. \n");
                        
                        MET_E_reco = MET_E_gen;
                        MET_phi_reco = MET_phi_gen;
                    }
                }
                
                else if(!strcmp(era, "2017"))
                {
                    MET_E_reco = input->METFixEE2017_E_reco;
                    MET_phi_reco = input->METFixEE2017_phi_reco;
                    
                    if(isSUSY && !syst_name.compare("withGenMET"))
                    {
                        MET_E_reco = MET_E_gen;
                        MET_phi_reco = MET_phi_gen;
                    }
                }
            }
            
            std::vector <int> tauPair_pos;
            std::vector <int> v_nTau;
            
            
            // Select tau pair
            std::vector <double> v_tau_pTetaCut(input->tau_n_reco, 0);
            std::vector <double> v_tau_isNewDM(input->tau_n_reco, 0);
            std::vector <double> v_tau_IPcut(input->tau_n_reco, 0);
            std::vector <double> v_tau_ES(input->tau_n_reco, 1.0);
            
            //for(int iTau = 0; iTau < input->tau_n_reco; iTau++)
            //{
            //    if(isMC)
            //    {
            //        v_tau_ES.at(iTau) = TauEfficiencyAndSF::getTauES(
            //            (int) input->v_tau_decayMode_reco->at(iTau),
            //            std::string(era),
            //            chooseSystType(syst_name, "tauES", syst_type)
            //        ).first;
            //    }
            //}
            //
            //// Tau ES
            //if(isMC)
            //{
            //    Common::scaleObject4mom(
            //        &(input->v_tau_reco),
            //        &v_tau_ES
            //    );
            //}
            
            
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
                
                if(isSUSY)
                {
                    input->v_tau_isTriggerMatched_reco->at(iTau) = 1;
                }
                
                v_tau_isNewDM.at(iTau) = Common::isTauNewDM((int) input->v_tau_decayMode_reco->at(iTau));
            }
            
            
            std::vector <std::vector <double> *> vv_tauSelection = {
                input->v_tau_isTriggerMatched_reco,
                &v_tau_isNewDM,
                &v_tau_IPcut,
                input->v_tau_byLooseDeepTau2017v2p1VSe_reco,
                input->v_tau_byTightDeepTau2017v2p1VSmu_reco,
                input->v_tau_byTightDeepTau2017v2p1VSjet_reco,
                &v_tau_pTetaCut
            };
            
            tauPair_pos = Common::getObjPair(
                &(input->v_tau_reco),
                &(input->v_tau_reco),
                true,
                vv_tauSelection,
                vv_tauSelection,
                Common::tauTau_deltaRcut_reco,
                tauPair_signOption
            );
            
            // At least 2 taus
            if(!tauPair_pos.size())
            {
                continue;
            }
            
            bool tau1_isGenMatched = false;
            bool tau2_isGenMatched = false;
            
            int tau_genMatched_n = 0;
            int tau_genLepMatched_n = 0;
            int tau_genUnmatched_n = 0;
            
            CLHEP::HepLorentzVector tau1_4mom_reco, tau2_4mom_reco;
            
            tau1_4mom_reco.setT(fabs(input->v_tau_E_reco->at(tauPair_pos[0])));
            tau1_4mom_reco.setX(input->v_tau_px_reco->at(tauPair_pos[0]));
            tau1_4mom_reco.setY(input->v_tau_py_reco->at(tauPair_pos[0]));
            tau1_4mom_reco.setZ(input->v_tau_pz_reco->at(tauPair_pos[0]));
            
            tau2_4mom_reco.setT(fabs(input->v_tau_E_reco->at(tauPair_pos[1])));
            tau2_4mom_reco.setX(input->v_tau_px_reco->at(tauPair_pos[1]));
            tau2_4mom_reco.setY(input->v_tau_py_reco->at(tauPair_pos[1]));
            tau2_4mom_reco.setZ(input->v_tau_pz_reco->at(tauPair_pos[1]));
            
            //printf("[%s] Event %d: Found tau-pair. \n", output_reco->nameAddon, iEvent+1);
            
            CLHEP::HepLorentzVector tauh1_4mom_gen;
            CLHEP::HepLorentzVector tauh2_4mom_gen;
            
            // Gen-matching
            if(isMC)
            {
                std::vector <bool> v_tau_isGenMatched_reco(input->tau_n_reco, false);
                std::vector <bool> v_tau_isUsed_gen(input->tau_vis_n_gen, false);
                
                for(int iTau_reco = 0; iTau_reco < input->tau_n_reco; iTau_reco++)
                {
                    // Check matching only for the selected pair
                    // No need to check for all the taus
                    if(iTau_reco != tauPair_pos[0] && iTau_reco != tauPair_pos[1])
                    {
                        continue;
                    }
                    
                    CLHEP::HepLorentzVector tau_4mom_reco;
                    
                    tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau_reco)));
                    tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau_reco));
                    tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau_reco));
                    tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau_reco));
                    
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
                        
                        if(tauh_4mom_gen.perp() < Common::tau_pTcut_tauTau_reco || fabs(tauh_4mom_gen.eta()) > Common::tau_etaCut_tauTau_reco)
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
                        }
                    }
                    
                    if(tau_nearestGenIndex >= 0)
                    {
                        if(deltaR_min < tauGenMatching_deltaRcut)
                        {
                            v_tau_isGenMatched_reco.at(iTau_reco) = true;
                            
                            tau_genMatchedIndex = tau_nearestGenIndex;
                            
                            v_tau_isUsed_gen.at(tau_genMatchedIndex) = true;
                            
                            if(iTau_reco == tauPair_pos[0])
                            {
                                tauh1_4mom_gen = tau_nearestGenh_4mom;
                            }
                            
                            else if(iTau_reco == tauPair_pos[1])
                            {
                                tauh2_4mom_gen = tau_nearestGenh_4mom;
                            }
                        }
                    }
                }
                
                tau1_isGenMatched = v_tau_isGenMatched_reco.at(tauPair_pos[0]);
                tau2_isGenMatched = v_tau_isGenMatched_reco.at(tauPair_pos[1]);
                
                int tauTau_genMatched_n = v_tau_isGenMatched_reco.at(tauPair_pos[0]) + v_tau_isGenMatched_reco.at(tauPair_pos[1]);
                
                output_reco->h1_tauTau_genMatched_n->Fill(tauTau_genMatched_n);
                
                
                // Both the taus must be gen-matched
                if(tauGenMatching)
                {
                    if(!v_tau_isGenMatched_reco.at(tauPair_pos[0]) || !v_tau_isGenMatched_reco.at(tauPair_pos[1]))
                    {
                        continue;
                    }
                }
                
                // ********** TEST!!! ********** //
                // At least one not gen-matched
                //if(v_tau_isGenMatched_reco.at(tauPair_pos[0]) && v_tau_isGenMatched_reco.at(tauPair_pos[1]))
                //{
                //    continue;
                //}
            }
            
            
            
            //printf("tauPair_signOption: %s, iEvent %d, tauTau_m %f \n", tauPair_signOption, iEvent, (tau1_4mom_reco+tau2_4mom_reco).m());
            
            //printf("tau pos: (%d, %d); E1*E2 < 0: %d (%s) \n", tauPair_pos[0], tauPair_pos[1], (input->v_tau_E_reco->at(tauPair_pos[0])*input->v_tau_E_reco->at(tauPair_pos[1]) < 0), tauPair_signOption);
            
            std::vector <std::pair <std::vector <CLHEP::HepLorentzVector>, double> > vp_obj4mom_deltaR_min = {
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {tau1_4mom_reco, tau2_4mom_reco}, 
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
                    
                    //printf("Event %d: pileUp %d, pileUpReweightFactor %f \n", iEvent+1, input->pileUp_n_reco, pileUpReweightFactor);
                    output_reco->h1_pileUpReweightFactor->Fill(pileUpReweightFactor);
                    eventWeight_common *= pileUpReweightFactor;
                }
                
                // Top pT reweighting
                double eventWeight_topPt = 1.0;
                
                //if(m_correction.at(Common::topPtReweighting_str))
                //{
                //    
                //    std::pair <std::pair <double, double>, std::pair <double, double> > topPtReweightFactor_info = Common::getTopPtReweightFactor(
                //        &input->v_t_gen,
                //        chooseSystType(syst_name, "topPtReweight", syst_type)
                //    );
                //    
                //    eventWeight_topPt = topPtReweightFactor_info.first.first;
                //    
                //    output_reco->h1_topPtReweightFactor->Fill(eventWeight_topPt);
                //    output_reco->h2_top1PtReweightFactor_vs_pT->Fill(topPtReweightFactor_info.second.first, eventWeight_topPt);
                //    output_reco->h2_top2PtReweightFactor_vs_pT->Fill(topPtReweightFactor_info.second.second, eventWeight_topPt);
                //}
                //
                //eventWeight_common *= eventWeight_topPt;
                
                
                //########## 1. 2017 PU
                //########## 2. 2017 b-tag SF
                //########## 3. Apply b-tag SF before filling histograms
                
                
                // Tau ID efficiency SF
                double tau1_IDefficiencySF = tauIDSFobj->getSFvsPT(
                    tau1_4mom_reco.perp(),
                    5,
                    chooseTauIDsystType(syst_name, "tauIDisoSF", syst_type)
                );
                
                double tau2_IDefficiencySF = tauIDSFobj->getSFvsPT(
                    tau2_4mom_reco.perp(),
                    5,
                    chooseTauIDsystType(syst_name, "tauIDisoSF", syst_type)
                );
                
                double tauIDefficiencyEventWeight = tau1_IDefficiencySF * tau2_IDefficiencySF;
                
                output_reco->h1_tauIDefficiencyEventWeight->Fill(tauIDefficiencyEventWeight);
                eventWeight_common *= tauIDefficiencyEventWeight;
                
                
                // Tau Fast-FullSim SF
                double tau1_fastFullSimSF = 1.0;
                double tau2_fastFullSimSF = 1.0;
                
                if(isSUSY)
                {
                    std::pair <double, double> tau1_fastFullSimSFinfo = tauFastFullSimSFinfo->getSF(
                        tau1_4mom_reco.perp(), tau1_4mom_reco.eta(),
                        chooseSystType(syst_name, "tauFastFullSimSF", syst_type)
                    );
                    
                    std::pair <double, double> tau2_fastFullSimSFinfo = tauFastFullSimSFinfo->getSF(
                        tau2_4mom_reco.perp(), tau2_4mom_reco.eta(),
                        chooseSystType(syst_name, "tauFastFullSimSF", syst_type)
                    );
                    
                    tau1_fastFullSimSF = tau1_fastFullSimSFinfo.first;
                    tau2_fastFullSimSF = tau2_fastFullSimSFinfo.first;
                    
                    //printf("[Event %d] tau1: pT %0.2f, eta %0.2f, fastFullSimSF %0.2f, SFerr %0.2f \n", iEvent+1, tau1_4mom_reco.perp(), tau1_4mom_reco.eta(), tau1_fastFullSimSF, tau1_fastFullSimSFinfo.second);
                    //printf("[Event %d] tau2: pT %0.2f, eta %0.2f, fastFullSimSF %0.2f, SFerr %0.2f \n", iEvent+1, tau2_4mom_reco.perp(), tau2_4mom_reco.eta(), tau2_fastFullSimSF, tau2_fastFullSimSFinfo.second);
                }
                
                double tau_fastFullSimSF = tau1_fastFullSimSF * tau2_fastFullSimSF;
                
                eventWeight_common *= tau_fastFullSimSF;
                
                
                //printf(
                //    "tau1: pT %0.2f, eta %0.2f, phi %0.2f, DM %d, eff SF %0.4f, ES %0.5f \n"
                //    "tau2: pT %0.2f, eta %0.2f, phi %0.2f, DM %d, eff SF %0.4f, ES %0.5f \n"
                //    "\n",
                //    tau1_4mom_reco.perp(), tau1_4mom_reco.eta(), tau1_4mom_reco.phi(), (int) input->v_tau_decayMode_reco->at(tauPair_pos[0]),
                //    tau1_IDefficiencySF.first, tau1_ES.first,
                //    tau2_4mom_reco.perp(), tau2_4mom_reco.eta(), tau2_4mom_reco.phi(), (int) input->v_tau_decayMode_reco->at(tauPair_pos[1]),
                //    tau2_IDefficiencySF.first, tau2_ES.first
                //);
                
                
                // Tau Trigger SF
                if(isSUSY)
                {
                    double tau1_triggerEff = tauTriggerSFobj->getEfficiencyData(
                        tau1_4mom_reco.perp(),
                        input->v_tau_decayMode_reco->at(tauPair_pos[0]),
                        Common::chooseSystType(syst_name, "triggerSF", syst_type)
                    );
                    
                    double tau2_triggerEff = tauTriggerSFobj->getEfficiencyData(
                        tau2_4mom_reco.perp(),
                        input->v_tau_decayMode_reco->at(tauPair_pos[1]),
                        Common::chooseSystType(syst_name, "triggerSF", syst_type)
                    );
                    
                    double tauTriggerEff = tau1_triggerEff * tau2_triggerEff;
                    
                    eventWeight_common *= tauTriggerEff;
                }
                
                else
                {
                    double tau1_triggerSF = tauTriggerSFobj->getSF(
                        tau1_4mom_reco.perp(),
                        input->v_tau_decayMode_reco->at(tauPair_pos[0]),
                        syst_type
                    );
                    
                    double tau2_triggerSF = tauTriggerSFobj->getSF(
                        tau2_4mom_reco.perp(),
                        input->v_tau_decayMode_reco->at(tauPair_pos[1]),
                        syst_type
                    );
                    
                    double tauTriggerSF = tau1_triggerSF * tau2_triggerSF;
                    
                    eventWeight_common *= tauTriggerSF;
                    
                    output_reco->h1_tauTauTrig_tau1SF->Fill(tau1_triggerSF);
                    output_reco->h1_tauTauTrig_tau2SF->Fill(tau2_triggerSF);
                    output_reco->h1_tauTauTrigSF->Fill(tauTriggerSF);
                }
                
                
                // Get b-tagging SF event weight
                // To do: produce bTagging data for the signal
                //if(!isSUSY)
                {
                    // APPLY TO 2017 LATER ///////////////////////////////////////////////////////////////////////////////////////////////
                    //if(!strcmp(era, "2016"))
                    {
                        BTagCalibrationReader bTagCalibReader( \
                            BTagEntry::OP_MEDIUM,
                            "central",
                            {"up", "down"}
                        );
                        
                        // No separate SFs for 2017 FastSim
                        if(isSUSY)
                        {
                            bTagCalibReader.load(*bTagCalib,
                                BTagEntry::FLAV_B,
                                "fastsim");
                            
                            bTagCalibReader.load(*bTagCalib,
                                BTagEntry::FLAV_C,
                                "fastsim");
                            
                            bTagCalibReader.load(*bTagCalib,
                                BTagEntry::FLAV_UDSG,
                                "fastsim");
                        }
                        
                        else
                        {
                            bTagCalibReader.load(*bTagCalib,
                                BTagEntry::FLAV_B,
                                "comb");
                            
                            bTagCalibReader.load(*bTagCalib,
                                BTagEntry::FLAV_C,
                                "comb");
                            
                            bTagCalibReader.load(*bTagCalib,
                                BTagEntry::FLAV_UDSG,
                                "incl");
                        }
                        
                        bTaggingEventWeight = Common::getBTaggingEventWeight(
                            &input->v_jet_reco,
                            Common::b_pTcut_reco, Common::b_etaCut_reco,
                            input->v_jet_partonFlavour_reco,
                            input->v_jet_byMediumPfDeepFlavourJetTags_reco,
                            &bTagCalibReader,
                            Common::chooseBTaggingSFsystType(syst_name, "bTaggingSF", syst_type),
                            fileName_bTaggingEfficiency,
                            "bTaggingEff_eff_b_pfDeepFlavourJetTags_DeepJetM",
                            "bTaggingEff_eff_c_pfDeepFlavourJetTags_DeepJetM",
                            "bTaggingEff_eff_udsg_pfDeepFlavourJetTags_DeepJetM",
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
            
            int jet_n_reco = 0;
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
                
                
                bool hasTauOverlap = !Common::isSeparated(jet_4mom_reco, &input->v_tau_reco, 0.3, tauPair_pos);
                
                if(hasTauOverlap)
                {
                    continue;
                }
                
                jet_n_reco++;
                
                jet_HT_reco += jet_4mom_reco.perp();
                
                // RECO b
                if(jet_4mom_reco.perp() < Common::b_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::b_etaCut_reco)
                {
                    continue;
                }
                
                if(input->v_jet_byMediumPfDeepFlavourJetTags_reco->at(iJet))
                {
                    b_n_medium++;
                }
            }
            
            double tauTau_jet_HT_reco = tau1_4mom_reco.perp() + tau2_4mom_reco.perp() + jet_HT_reco;
            
            
            double tauTau_MET_mT2_gen = 0;
            
            if(isMC)
            {
                tauTau_MET_mT2_gen = asymm_mt2_lester_bisect::get_mT2(
                    tauh1_4mom_gen.m(), tauh1_4mom_gen.px(), tauh1_4mom_gen.py(),
                    tauh2_4mom_gen.m(), tauh2_4mom_gen.px(), tauh2_4mom_gen.py(),
                    MET_E_gen*cos(MET_phi_gen), MET_E_gen*sin(MET_phi_gen),
                    0, 0
                );
            }
            
            double tauTau_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2(
                tau1_4mom_reco.m(), tau1_4mom_reco.px(), tau1_4mom_reco.py(),
                tau2_4mom_reco.m(), tau2_4mom_reco.px(), tau2_4mom_reco.py(),
                MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco),
                0, 0
            );
            
            
            double tauTau_m_reco = (tau1_4mom_reco + tau2_4mom_reco).m();
            
            // Event selection
            bool isEventSelected = Common::evaluateExpression(
                eventSelectionStr,
                {
                    std::make_pair("MET_E_reco", MET_E_reco),
                    std::make_pair("tauTau_MET_mT2", tauTau_MET_mT2_lsp0),
                    std::make_pair("tauTau_jet_HT_reco", tauTau_jet_HT_reco),
                    std::make_pair("tauTau_m_reco", tauTau_m_reco),
                    std::make_pair("b_n_reco", b_n_medium),
                    std::make_pair("jet_n_reco", jet_n_reco),
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
            //    "tauTau_jet_HT_reco >= 100",
            //    tauTau_jet_HT_reco >= 100
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
            
            
            if(isMC)
            {
                // Gen electron matching
                bool tau1_isGenElMatched = false;
                bool tau2_isGenElMatched = false;
                
                
                for(int iEl_gen = 0; iEl_gen < input->el_n_gen; iEl_gen++)
                {
                    CLHEP::HepLorentzVector el_4mom_gen;
                    
                    el_4mom_gen.setT(fabs(input->v_el_E_gen->at(iEl_gen)));
                    el_4mom_gen.setX(input->v_el_px_gen->at(iEl_gen));
                    el_4mom_gen.setY(input->v_el_py_gen->at(iEl_gen));
                    el_4mom_gen.setZ(input->v_el_pz_gen->at(iEl_gen));
                    
                    if(el_4mom_gen.perp() < Common::tau_pTcut_tauTau_reco || fabs(el_4mom_gen.eta()) > Common::tau_etaCut_tauTau_reco)
                    {
                        continue;
                    }
                    
                    //if(!input->v_el_isPrompt_gen->at(iEl_gen))
                    //{
                    //    continue;
                    //}
                    
                    if(!tau1_isGenMatched && el_4mom_gen.deltaR(tau1_4mom_reco) < 0.3)
                    {
                        tau1_isGenElMatched = true;
                        //break;
                    }
                    
                    else if(!tau2_isGenMatched && el_4mom_gen.deltaR(tau2_4mom_reco) < 0.3)
                    {
                        tau2_isGenElMatched = true;
                        //break;
                    }
                }
                
                
                // Gen muon matching
                bool tau1_isGenMuMatched = false;
                bool tau2_isGenMuMatched = false;
                
                for(int iMu_gen = 0; iMu_gen < input->mu_n_gen; iMu_gen++)
                {
                    CLHEP::HepLorentzVector mu_4mom_gen;
                    
                    mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu_gen)));
                    mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu_gen));
                    mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu_gen));
                    mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu_gen));
                    
                    if(mu_4mom_gen.perp() < Common::tau_pTcut_tauTau_reco || fabs(mu_4mom_gen.eta()) > Common::tau_etaCut_tauTau_reco)
                    {
                        continue;
                    }
                    
                    //if(!input->v_mu_isPrompt_gen->at(iMu_gen))
                    //{
                    //    continue;
                    //}
                    
                    if(!tau1_isGenMatched && mu_4mom_gen.deltaR(tau1_4mom_reco) < 0.3)
                    {
                        tau1_isGenMuMatched = true;
                        //break;
                    }
                    
                    else if(!tau2_isGenMatched && mu_4mom_gen.deltaR(tau2_4mom_reco) < 0.3)
                    {
                        tau2_isGenMuMatched = true;
                        //break;
                    }
                }
                
                
                tau_genMatched_n = tau1_isGenMatched + tau2_isGenMatched;
                tau_genLepMatched_n = (tau1_isGenElMatched || tau1_isGenMuMatched) + (tau2_isGenElMatched || tau2_isGenMuMatched);
                tau_genUnmatched_n = std::max(0, 2 - tau_genMatched_n - tau_genLepMatched_n);
                
                
                if(tau_genMatched_n == 2)
                {
                    output_reco->h1_nEvent_2tau->Fill(0.0, eventWeight_common);
                }
                
                else if(tau_genMatched_n == 1 && tau_genLepMatched_n == 1)
                {
                    output_reco->h1_nEvent_1tau1lep->Fill(0.0, eventWeight_common);
                }
                
                else if(tau_genMatched_n == 1 && tau_genUnmatched_n == 1)
                {
                    output_reco->h1_nEvent_1tau1jet->Fill(0.0, eventWeight_common);
                }
                
                else if(tau_genLepMatched_n == 2)
                {
                    output_reco->h1_nEvent_2lep->Fill(0.0, eventWeight_common);
                }
                
                else if(tau_genLepMatched_n == 1 && tau_genUnmatched_n == 1)
                {
                    output_reco->h1_nEvent_1lep1jet->Fill(0.0, eventWeight_common);
                }
                
                else if(tau_genUnmatched_n == 2)
                {
                    output_reco->h1_nEvent_2jet->Fill(0.0, eventWeight_common);
                }
            }
            
            
            // MET
            output_reco->h1_MET_E->Fill(MET_E_reco, eventWeight_common);
            output_reco->h1_MET_phi->Fill(MET_phi_reco, eventWeight_common);
            
            if(isMC)
            {
                output_reco->h1_MET_E_gen->Fill(MET_E_gen, eventWeight_common);
                output_reco->h1_MET_phi_gen->Fill(MET_phi_gen, eventWeight_common);
            }
            
            
            double tauTau_MET_mT2 = 0;
            
            double MET_pZeta = 0;
            double tauTau_pZeta = 0;
            double tauTau_MET_pZeta = 0;
            double tauTau_MET_Dzeta = 0;
            
            
            if(isMC)
            {
                double tau1_MET_deltaPhi_gen = Common::getDeltaPhi(tauh1_4mom_gen.phi(), MET_phi_gen);
                double tau2_MET_deltaPhi_gen = Common::getDeltaPhi(tauh2_4mom_gen.phi(), MET_phi_gen);
                
                CLHEP::Hep3Vector MET_3mom_gen(MET_E_gen*cos(MET_phi_gen), MET_E_gen*sin(MET_phi_gen), 0.0);
                double tau1_MET_mT_gen = Common::getMT_massless(tauh1_4mom_gen.v(), MET_3mom_gen);
                double tau2_MET_mT_gen = Common::getMT_massless(tauh2_4mom_gen.v(), MET_3mom_gen);
                
                output_reco->v_h1_tau_pT_gen[0]->Fill(tauh1_4mom_gen.perp(), eventWeight_common);
                output_reco->v_h1_tau_eta_gen[0]->Fill(tauh1_4mom_gen.eta(), eventWeight_common);
                output_reco->v_h1_tau_phi_gen[0]->Fill(tauh1_4mom_gen.phi(), eventWeight_common);
                output_reco->v_h1_tau_MET_mT_gen[0]->Fill(tau1_MET_mT_gen, eventWeight_common);
                output_reco->v_h1_tau_MET_deltaPhi_gen[0]->Fill(tau1_MET_deltaPhi_gen, eventWeight_common);
                
                output_reco->v_h1_tau_pT_gen[1]->Fill(tauh2_4mom_gen.perp(), eventWeight_common);
                output_reco->v_h1_tau_eta_gen[1]->Fill(tauh2_4mom_gen.eta(), eventWeight_common);
                output_reco->v_h1_tau_phi_gen[1]->Fill(tauh2_4mom_gen.phi(), eventWeight_common);
                output_reco->v_h1_tau_MET_mT_gen[1]->Fill(tau2_MET_mT_gen, eventWeight_common);
                output_reco->v_h1_tau_MET_deltaPhi_gen[1]->Fill(tau2_MET_deltaPhi_gen, eventWeight_common);
                
                output_reco->h1_tauTau_MET_mT2_gen->Fill(tauTau_MET_mT2_gen, eventWeight_common);
            }
            
            
            //
            double tau1_MET_deltaPhi_reco = Common::getDeltaPhi(tau1_4mom_reco.phi(), MET_phi_reco);
            double tau2_MET_deltaPhi_reco = Common::getDeltaPhi(tau2_4mom_reco.phi(), MET_phi_reco);
            double tauTau_deltaPhi_reco = Common::getDeltaPhi(tau1_4mom_reco.phi(), tau2_4mom_reco.phi());
            
            CLHEP::Hep3Vector MET_3mom_reco(MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco), 0.0);
            double tau1_MET_mT_reco = Common::getMT_massless(tau1_4mom_reco.v(), MET_3mom_reco);
            double tau2_MET_mT_reco = Common::getMT_massless(tau2_4mom_reco.v(), MET_3mom_reco);
            
            output_reco->v_h1_tau_pT[0]->Fill(tau1_4mom_reco.perp(), eventWeight_common);
            output_reco->v_h1_tau_eta[0]->Fill(tau1_4mom_reco.eta(), eventWeight_common);
            output_reco->v_h1_tau_phi[0]->Fill(tau1_4mom_reco.phi(), eventWeight_common);
            output_reco->v_h1_tau_m[0]->Fill(tau1_4mom_reco.m(), eventWeight_common);
            output_reco->v_h1_tau_MET_deltaPhi[0]->Fill(tau1_MET_deltaPhi_reco, eventWeight_common);
            output_reco->v_h1_tau_MET_mT[0]->Fill(tau1_MET_mT_reco, eventWeight_common);
            
            output_reco->v_h1_tau_pT[1]->Fill(tau2_4mom_reco.perp(), eventWeight_common);
            output_reco->v_h1_tau_eta[1]->Fill(tau2_4mom_reco.eta(), eventWeight_common);
            output_reco->v_h1_tau_phi[1]->Fill(tau2_4mom_reco.phi(), eventWeight_common);
            output_reco->v_h1_tau_m[1]->Fill(tau2_4mom_reco.m(), eventWeight_common);
            output_reco->v_h1_tau_MET_deltaPhi[1]->Fill(tau2_MET_deltaPhi_reco, eventWeight_common);
            output_reco->v_h1_tau_MET_mT[1]->Fill(tau2_MET_mT_reco, eventWeight_common);
            
            double lsp_m = 0;
            
            if(isSUSY)
            {
                lsp_m = input->neutralino1_m_genParam;
            }
            
            tauTau_MET_mT2 = asymm_mt2_lester_bisect::get_mT2( \
                tau1_4mom_reco.m(), tau1_4mom_reco.px(), tau1_4mom_reco.py(), \
                tau2_4mom_reco.m(), tau2_4mom_reco.px(), tau2_4mom_reco.py(), \
                MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco), \
                lsp_m, lsp_m);
            
            output_reco->h1_tauTau_m->Fill((tau1_4mom_reco+tau2_4mom_reco).m(), eventWeight_common);
            output_reco->h1_tauTau_pT->Fill((tau1_4mom_reco+tau2_4mom_reco).perp(), eventWeight_common);
            output_reco->h1_tauTau_deltaPhi->Fill(tauTau_deltaPhi_reco, eventWeight_common);
            output_reco->h1_tauTau_deltaR->Fill(tau1_4mom_reco.deltaR(tau2_4mom_reco), eventWeight_common);
            output_reco->h1_tauTau_MET_mT2->Fill(tauTau_MET_mT2, eventWeight_common);
            output_reco->h1_tauTau_MET_mT2_lsp0->Fill(tauTau_MET_mT2_lsp0, eventWeight_common);
            
            //int bin = output_reco->h1_tauTau_MET_mT2_lsp0->FindBin(tauTau_MET_mT2_lsp0);
            //printf("eventWeight_common %0.6e \n", eventWeight_common);
            //printf("h1_tauTau_MET_mT2_lsp0: bin %d, val %0.2e, err %0.2e \n\n", bin, output_reco->h1_tauTau_MET_mT2_lsp0->GetBinContent(bin), output_reco->h1_tauTau_MET_mT2_lsp0->GetBinError(bin));
            
            if(m_correction.at(Common::ZptReweighting_str) && input->Z_n_gen > 0)
            {
                output_reco->h1_ZpTreweightFactor_afterBaseline->Fill(ZpTreweightFactor);
                output_reco->h2_ZpTreweightFactor_vs_m_afterBaseline->Fill(Z_gen_4mom.m(), ZpTreweightFactor);
                output_reco->h2_ZpTreweightFactor_vs_pT_afterBaseline->Fill(Z_gen_4mom.perp(), ZpTreweightFactor);
                
                output_reco->h2_ZpTreweightFactor_vs_tauTau_m->Fill((tau1_4mom_reco+tau2_4mom_reco).m(), ZpTreweightFactor, eventWeight_common);
                output_reco->h2_ZpTreweightFactor_vs_tauTau_pT->Fill((tau1_4mom_reco+tau2_4mom_reco).perp(), ZpTreweightFactor, eventWeight_common);
            }
            
            output_reco->h2_tauTau_MET_mT2_vs_MET_E->Fill(MET_E_reco, tauTau_MET_mT2_lsp0, eventWeight_common);
            
            output_reco->h2_MET_vs_tau1_MET_deltaPhi->Fill(tau1_MET_deltaPhi_reco, MET_E_reco, eventWeight_common);
            output_reco->h2_MET_vs_tau2_MET_deltaPhi->Fill(tau2_MET_deltaPhi_reco, MET_E_reco, eventWeight_common);
            output_reco->h2_MET_vs_tauTau_deltaPhi->Fill(tauTau_deltaPhi_reco, MET_E_reco, eventWeight_common);
            
            output_reco->h2_tauTau_MET_mT2_vs_tau1_MET_deltaPhi->Fill(tau1_MET_deltaPhi_reco, tauTau_MET_mT2_lsp0, eventWeight_common);
            output_reco->h2_tauTau_MET_mT2_vs_tau2_MET_deltaPhi->Fill(tau2_MET_deltaPhi_reco, tauTau_MET_mT2_lsp0, eventWeight_common);
            output_reco->h2_tauTau_MET_mT2_vs_tauTau_deltaPhi->Fill(tauTau_deltaPhi_reco, tauTau_MET_mT2_lsp0, eventWeight_common);
            
            MET_pZeta = Common::getPzeta(
                {{MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco)}},
                
                {tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                {tau2_4mom_reco.px(), tau2_4mom_reco.py()}
            );
            
            tauTau_pZeta = Common::getPzeta(
                {{tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                    {tau2_4mom_reco.px(), tau2_4mom_reco.py()}
                },
                
                {tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                {tau2_4mom_reco.px(), tau2_4mom_reco.py()}
            );
            
            tauTau_MET_pZeta = Common::getPzeta(
                {{tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                    {tau2_4mom_reco.px(), tau2_4mom_reco.py()},
                    {MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco)}
                },
                
                {tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                {tau2_4mom_reco.px(), tau2_4mom_reco.py()}
            );
            
            tauTau_MET_Dzeta = tauTau_MET_pZeta - 1.85*tauTau_pZeta;
            
            output_reco->h1_MET_pZeta->Fill(MET_pZeta, eventWeight_common);
            output_reco->h1_tauTau_pZeta->Fill(tauTau_pZeta, eventWeight_common);
            output_reco->h1_tauTau_MET_pZeta->Fill(tauTau_MET_pZeta, eventWeight_common);
            output_reco->h1_tauTau_MET_Dzeta->Fill(tauTau_MET_Dzeta, eventWeight_common);
            
            output_reco->h2_tauTau_MET_Dzeta_vs_MET_E->Fill(MET_E_reco, tauTau_MET_Dzeta, eventWeight_common);
            
            // Tau constituents
            CLHEP::HepLorentzVector tau1_chHad1_4mom_reco, tau2_chHad1_4mom_reco;
            
            // One-pronged
            if(input->v_tau_decayMode_reco->at(tauPair_pos[0]) <= 2)
            {
                tau1_chHad1_4mom_reco.setT(fabs(input->v_tau_chHad1_E_reco->at(tauPair_pos[0])));
                tau1_chHad1_4mom_reco.setX(input->v_tau_chHad1_px_reco->at(tauPair_pos[0]));
                tau1_chHad1_4mom_reco.setY(input->v_tau_chHad1_py_reco->at(tauPair_pos[0]));
                tau1_chHad1_4mom_reco.setZ(input->v_tau_chHad1_pz_reco->at(tauPair_pos[0]));
                
                output_reco->v_h1_tau_chHad1_pT_by_tau_pT[0]->Fill( \
                    tau1_chHad1_4mom_reco.perp() / tau1_4mom_reco.perp(), eventWeight_common);
            }
            
            // One-pronged
            if(input->v_tau_decayMode_reco->at(tauPair_pos[1]) <= 2)
            {
                tau2_chHad1_4mom_reco.setT(fabs(input->v_tau_chHad1_E_reco->at(tauPair_pos[1])));
                tau2_chHad1_4mom_reco.setX(input->v_tau_chHad1_px_reco->at(tauPair_pos[1]));
                tau2_chHad1_4mom_reco.setY(input->v_tau_chHad1_py_reco->at(tauPair_pos[1]));
                tau2_chHad1_4mom_reco.setZ(input->v_tau_chHad1_pz_reco->at(tauPair_pos[1]));
                
                output_reco->v_h1_tau_chHad1_pT_by_tau_pT[1]->Fill( \
                    tau2_chHad1_4mom_reco.perp() / tau2_4mom_reco.perp(), eventWeight_common);
            }
            
            
            // GEN jet
            if(isMC)
            {
                int jet_n_gen = 0;
                
                double jet_pxSum_gen = 0;
                double jet_pySum_gen = 0;
                
                double jet_HT_gen = 0;
                double jet_MHT_gen = 0;
                
                double tauTau_jet_pxSum_gen = 0;
                double tauTau_jet_pySum_gen = 0;
                
                double tauTau_jet_HT_gen = 0;
                double tauTau_jet_MHT_gen = 0;
                
                for(int iJet = 0; iJet < input->jet_n_gen; iJet++)
                {
                    CLHEP::HepLorentzVector jet_4mom_gen;
                    
                    jet_4mom_gen.setT(fabs(input->v_jet_E_gen->at(iJet)));
                    jet_4mom_gen.setX(input->v_jet_px_gen->at(iJet));
                    jet_4mom_gen.setY(input->v_jet_py_gen->at(iJet));
                    jet_4mom_gen.setZ(input->v_jet_pz_gen->at(iJet));
                    
                    if(jet_4mom_gen.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_gen.eta()) > Common::jet_etaCut_reco)
                    {
                        continue;
                    }
                    
                    bool isTauSeparated = jet_4mom_gen.deltaR(tauh1_4mom_gen) > 0.3 && jet_4mom_gen.deltaR(tauh2_4mom_gen) > 0.3;
                    
                    if(!isTauSeparated)
                    {
                        continue;
                    }
                    
                    double jet_MET_deltaPhi = Common::getDeltaPhi(jet_4mom_gen.phi(), input->MET_phi_gen);
                    
                    if(jet_n_gen < output_reco->v_h1_jet_pT_gen.size())
                    {
                        output_reco->v_h1_jet_pT_gen.at(jet_n_gen)->Fill(jet_4mom_gen.perp(), eventWeight_common);
                        output_reco->v_h1_jet_eta_gen.at(jet_n_gen)->Fill(jet_4mom_gen.eta(), eventWeight_common);
                        output_reco->v_h1_jet_phi_gen.at(jet_n_gen)->Fill(jet_4mom_gen.phi(), eventWeight_common);
                        
                        output_reco->v_h1_jet_MET_deltaPhi_gen.at(jet_n_gen)->Fill(jet_MET_deltaPhi, eventWeight_common);
                    }
                    
                    jet_n_gen++;
                    
                    jet_pxSum_gen += input->v_jet_px_gen->at(iJet);
                    jet_pySum_gen += input->v_jet_py_gen->at(iJet);
                    
                    jet_HT_gen += jet_4mom_gen.perp();
                }
                
                output_reco->h1_jet_n_gen->Fill(jet_n_gen, eventWeight_common);
                
                jet_MHT_gen = sqrt(jet_pxSum_gen*jet_pxSum_gen + jet_pySum_gen*jet_pySum_gen);
                
                tauTau_jet_pxSum_gen = jet_pxSum_gen + tauh1_4mom_gen.px() + tauh2_4mom_gen.px();
                tauTau_jet_pySum_gen = jet_pySum_gen + tauh1_4mom_gen.py() + tauh2_4mom_gen.py();
                
                tauTau_jet_HT_gen = jet_HT_gen + tauh1_4mom_gen.perp() + tauh2_4mom_gen.perp();
                tauTau_jet_MHT_gen = sqrt(tauTau_jet_pxSum_gen*tauTau_jet_pxSum_gen + tauTau_jet_pySum_gen*tauTau_jet_pySum_gen);
                
                if(jet_n_gen)
                {
                    output_reco->h1_jet_HT_gen->Fill(jet_HT_gen, eventWeight_common);
                    output_reco->h1_jet_MHT_gen->Fill(jet_MHT_gen, eventWeight_common);
                }
                
                output_reco->h1_tauTau_jet_HT_gen->Fill(tauTau_jet_HT_gen, eventWeight_common);
                output_reco->h1_tauTau_jet_MHT_gen->Fill(tauTau_jet_MHT_gen, eventWeight_common);
            }
            
            
            
            // RECO jet
            //output_reco->h1_jet_n->Fill(input->jet_n_reco, eventWeight_common);
            
            jet_n_reco = 0;
            int jet_n_eta2p1to2p4_reco = 0;
            int jet_n_eta2p1to3_reco = 0;
            
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
            int b_n_medium_eta2p1to3 = 0;
            int b_n_tight = 0;
            
            double jet_pxSum_reco = 0;
            double jet_pySum_reco = 0;
            
            jet_HT_reco = 0;
            double jet_HT_eta2p1to2p4_reco = 0;
            double jet_HT_eta2p1to3_reco = 0;
            double jet_MHT_reco = 0;
            
            double tauTau_b_pxSum_reco = 0;
            double tauTau_b_pySum_reco = 0;
            
            double tauTau_b_HT_reco = 0;
            double tauTau_b_MHT_reco = 0;
            
            int b_tauOverlap_n = 0;
            int nonBjet_tauOverlap_n = 0;
            
            double nonBjet1_pT = 0;
            
            int nonBjet_n_reco = 0;
            int nonBjet_n_noOverlapCheck = 0;
            
            CLHEP::HepLorentzVector jet1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector jet2_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector jet3_4mom_reco(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector b1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector b2_4mom_reco(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector nonBjet1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector nonBjet2_4mom_reco(0, 0, 0, 0);
            
            double jet_MET_deltaPhi_min = 9999;
            
            double jet_MET_deltaPhiMin_jetEta0to2p4 = 9999;
            double jet_MET_deltaPhiMin_jetEta2p4to3p139 = 9999;
            double jet_MET_deltaPhiMin_jetEta0to5 = 9999;
            double jet_MET_deltaPhiMin_jetEta2p65to3p139 = 9999;
            double jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5 = 9999;
            
            for(int iJet = 0; iJet < input->jet_n_reco; iJet++)
            {
                CLHEP::HepLorentzVector jet_4mom_reco;
                
                jet_4mom_reco.setT(fabs(input->v_jet_E_reco->at(iJet)));
                jet_4mom_reco.setX(input->v_jet_px_reco->at(iJet));
                jet_4mom_reco.setY(input->v_jet_py_reco->at(iJet));
                jet_4mom_reco.setZ(input->v_jet_pz_reco->at(iJet));
                
                double jet_MET_deltaPhi = Common::getDeltaPhi(jet_4mom_reco.phi(), MET_phi_reco);
                
                bool isTauSeparated = Common::isSeparated(jet_4mom_reco, &input->v_tau_reco, 0.3, tauPair_pos);
                
                // 0 < eta < 2.4
                if(
                    jet_4mom_reco.perp() >= Common::jet_pTcut_reco &&
                    fabs(jet_4mom_reco.eta()) < 2.4 &&
                    isTauSeparated
                )
                {
                    output_reco->h1_jet_MET_deltaPhi_jetEta0to2p4->Fill(jet_MET_deltaPhi, eventWeight_common);
                    
                    if(fabs(jet_MET_deltaPhi) < fabs(jet_MET_deltaPhiMin_jetEta0to2p4))
                    {
                        jet_MET_deltaPhiMin_jetEta0to2p4 = jet_MET_deltaPhi;
                    }
                }
                
                // 2.4 < eta < 3.139
                if(
                    jet_4mom_reco.perp() >= Common::jet_pTcut_reco &&
                    (2.4 < fabs(jet_4mom_reco.eta()) && fabs(jet_4mom_reco.eta()) < 3.139) &&
                    isTauSeparated
                )
                {
                    output_reco->h1_jet_MET_deltaPhi_jetEta2p4to3p139->Fill(jet_MET_deltaPhi, eventWeight_common);
                    
                    if(fabs(jet_MET_deltaPhi) < fabs(jet_MET_deltaPhiMin_jetEta2p4to3p139))
                    {
                        jet_MET_deltaPhiMin_jetEta2p4to3p139 = jet_MET_deltaPhi;
                    }
                }
                
                // 0 < eta < 5
                if(
                    jet_4mom_reco.perp() >= Common::jet_pTcut_reco &&
                    fabs(jet_4mom_reco.eta()) < 5 &&
                    isTauSeparated
                )
                {
                    output_reco->h1_jet_MET_deltaPhi_jetEta0to5->Fill(jet_MET_deltaPhi, eventWeight_common);
                    
                    if(fabs(jet_MET_deltaPhi) < fabs(jet_MET_deltaPhiMin_jetEta0to5))
                    {
                        jet_MET_deltaPhiMin_jetEta0to5 = jet_MET_deltaPhi;
                    }
                }
                
                // 2.65 < eta < 3.139
                if(
                    jet_4mom_reco.perp() >= Common::jet_pTcut_reco &&
                    (2.65 < fabs(jet_4mom_reco.eta()) && fabs(jet_4mom_reco.eta()) < 3.139) &&
                    isTauSeparated
                )
                {
                    output_reco->h1_jet_MET_deltaPhi_jetEta2p65to3p139->Fill(jet_MET_deltaPhi, eventWeight_common);
                    
                    if(fabs(jet_MET_deltaPhi) < fabs(jet_MET_deltaPhiMin_jetEta2p65to3p139))
                    {
                        jet_MET_deltaPhiMin_jetEta2p65to3p139 = jet_MET_deltaPhi;
                    }
                }
                
                // 0 < eta < 2.65, 3.139 < eta < 5
                if(
                    jet_4mom_reco.perp() >= Common::jet_pTcut_reco &&
                    (fabs(jet_4mom_reco.eta()) < 2.65 || (3.139 < fabs(jet_4mom_reco.eta()) && fabs(jet_4mom_reco.eta()) < 5)) &&
                    isTauSeparated
                )
                {
                    output_reco->h1_jet_MET_deltaPhi_jetEta0to2p65and3p139to5->Fill(jet_MET_deltaPhi, eventWeight_common);
                    
                    if(fabs(jet_MET_deltaPhi) < fabs(jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5))
                    {
                        jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5 = jet_MET_deltaPhi;
                    }
                }
                
                
                if(jet_4mom_reco.perp() >= Common::jet_pTcut_reco && fabs(jet_4mom_reco.eta()) > 2.1 && fabs(jet_4mom_reco.eta()) < 3)
                {
                    output_reco->h1_jet_pT_eta2p1to3->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    
                    jet_n_eta2p1to3_reco++;
                    jet_HT_eta2p1to3_reco += jet_4mom_reco.perp();
                    
                    if(input->v_jet_byMediumPfDeepFlavourJetTags_reco->at(iJet))
                    {
                        b_n_medium_eta2p1to3++;
                    }
                }
                
                
                if(jet_4mom_reco.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::jet_etaCut_reco)
                {
                    continue;
                }
                
                
                //if(!input->v_jet_byMediumPfDeepFlavourJetTags_reco->at(iJet))
                //{
                //    nonBjet_n_noOverlapCheck++;
                //}
                
                bool hasTauOverlap = !Common::isSeparated(jet_4mom_reco, &input->v_tau_reco, 0.3, tauPair_pos);
                
                if(hasTauOverlap)
                {
                    /*if(input->v_jet_byMediumPfDeepFlavourJetTags_reco->at(iJet))
                    {
                        b_tauOverlap_n++;
                    }
                    
                    else
                    {
                        nonBjet_tauOverlap_n++;
                    }*/
                    
                    jet_tauOverlap_n++;
                    
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
                
                else if(jet_4mom_reco.perp() > jet3_4mom_reco.perp())
                {
                    jet3_4mom_reco = jet_4mom_reco;
                }
                
                if(jet_n_reco >= 1 && jet_n_reco <= 4)
                {
                    if(fabs(jet_MET_deltaPhi) < fabs(jet_MET_deltaPhi_min))
                    {
                        jet_MET_deltaPhi_min = jet_MET_deltaPhi;
                    }
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
                
                if(input->v_jet_byLoosePfDeepFlavourJetTags_reco->at(iJet))
                {
                    output_reco->h1_b_pT_loose->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_b_eta_loose->Fill(jet_4mom_reco.eta(), eventWeight_common);
                    
                    b_n_loose++;
                }
                
                if(input->v_jet_byMediumPfDeepFlavourJetTags_reco->at(iJet))
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
                    
                    tauTau_b_pxSum_reco += jet_4mom_reco.px();
                    tauTau_b_pySum_reco += jet_4mom_reco.py();
                    tauTau_b_HT_reco += jet_4mom_reco.perp();
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
                
                if(input->v_jet_byTightPfDeepFlavourJetTags_reco->at(iJet))
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
                
                output_reco->v_h1_jet_MET_deltaPhi[0]->Fill(Common::getDeltaPhi(jet1_4mom_reco.phi(), MET_phi_reco), eventWeight_common);
            }
            
            if(jet_n_reco >= 2)
            {
                output_reco->v_h1_jet_pT[1]->Fill(jet2_4mom_reco.perp(), eventWeight_common);
                output_reco->v_h1_jet_eta[1]->Fill(jet2_4mom_reco.eta(), eventWeight_common);
                output_reco->v_h1_jet_phi[1]->Fill(jet2_4mom_reco.phi(), eventWeight_common);
                
                output_reco->v_h1_jet_MET_deltaPhi[1]->Fill(Common::getDeltaPhi(jet2_4mom_reco.phi(), MET_phi_reco), eventWeight_common);
            }
            
            if(jet_n_reco >= 3)
            {
                output_reco->v_h1_jet_pT[2]->Fill(jet3_4mom_reco.perp(), eventWeight_common);
                output_reco->v_h1_jet_eta[2]->Fill(jet3_4mom_reco.eta(), eventWeight_common);
                output_reco->v_h1_jet_phi[2]->Fill(jet3_4mom_reco.phi(), eventWeight_common);
                
                output_reco->v_h1_jet_MET_deltaPhi[2]->Fill(Common::getDeltaPhi(jet3_4mom_reco.phi(), MET_phi_reco), eventWeight_common);
            }
            
            if(jet_n_reco >= 1 && jet_n_reco <= 4)
            {
                output_reco->h1_jet_MET_deltaPhi_min->Fill(jet_MET_deltaPhi_min, eventWeight_common);
            }
            
            
            if(fabs(jet_MET_deltaPhiMin_jetEta0to2p4) < 9999)
            {
                output_reco->h1_jet_MET_deltaPhiMin_jetEta0to2p4->Fill(jet_MET_deltaPhiMin_jetEta0to2p4, eventWeight_common);
            }
            
            if(fabs(jet_MET_deltaPhiMin_jetEta2p4to3p139) < 9999)
            {
                output_reco->h1_jet_MET_deltaPhiMin_jetEta2p4to3p139->Fill(jet_MET_deltaPhiMin_jetEta2p4to3p139, eventWeight_common);
            }
            
            if(fabs(jet_MET_deltaPhiMin_jetEta0to5) < 9999)
            {
                output_reco->h1_jet_MET_deltaPhiMin_jetEta0to5->Fill(jet_MET_deltaPhiMin_jetEta0to5, eventWeight_common);
            }
            
            if(fabs(jet_MET_deltaPhiMin_jetEta2p65to3p139) < 9999)
            {
                output_reco->h1_jet_MET_deltaPhiMin_jetEta2p65to3p139->Fill(jet_MET_deltaPhiMin_jetEta2p65to3p139, eventWeight_common);
            }
            
            if(fabs(jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5) < 9999)
            {
                output_reco->h1_jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5->Fill(jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5, eventWeight_common);
            }
            
            output_reco->h1_jet_n->Fill(jet_n_reco, eventWeight_common);
            output_reco->h1_jet_tauOverlap_n->Fill(jet_tauOverlap_n, eventWeight_common);
            
            output_reco->h2_jet_n_eta2p1to2p4_vs_jet_n->Fill(jet_n_reco, jet_n_eta2p1to2p4_reco, eventWeight_common);
            output_reco->h2_jet_n_eta2p1to3_vs_jet_n->Fill(jet_n_reco, jet_n_eta2p1to3_reco, eventWeight_common);
            
            output_reco->h1_jet_HT_eta2p1to2p4_by_jet_HT->Fill(jet_HT_eta2p1to2p4_reco/jet_HT_reco, eventWeight_common);
            output_reco->h1_jet_HT_eta2p1to3_by_jet_HT->Fill(jet_HT_eta2p1to3_reco/jet_HT_reco, eventWeight_common);
            
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
            output_reco->h2_b_n_eta2p1to3_vs_b_n->Fill(b_n_medium, b_n_medium_eta2p1to3, eventWeight_common);
            
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
            
            
            double tauTau_jet_pxSum_reco = 0;
            double tauTau_jet_pySum_reco = 0;
            double tauTau_jet_MHT_reco = 0;
            
            tauTau_b_pxSum_reco += tau1_4mom_reco.px();
            tauTau_b_pxSum_reco += tau2_4mom_reco.px();
            
            tauTau_b_pySum_reco += tau1_4mom_reco.py();
            tauTau_b_pySum_reco += tau2_4mom_reco.py();
            
            tauTau_b_HT_reco += tau1_4mom_reco.perp();
            tauTau_b_HT_reco += tau2_4mom_reco.perp();
            
            tauTau_b_MHT_reco = sqrt(tauTau_b_pxSum_reco*tauTau_b_pxSum_reco + tauTau_b_pySum_reco*tauTau_b_pySum_reco);
            
            tauTau_jet_pxSum_reco = tau1_4mom_reco.px() + tau2_4mom_reco.px() + jet_pxSum_reco;
            tauTau_jet_pySum_reco = tau1_4mom_reco.py() + tau2_4mom_reco.py() + jet_pySum_reco;
            tauTau_jet_MHT_reco = sqrt(tauTau_jet_pxSum_reco*tauTau_jet_pxSum_reco + tauTau_jet_pySum_reco*tauTau_jet_pySum_reco);
            
            output_reco->h1_tauTau_b_HT->Fill(tauTau_b_HT_reco, eventWeight_common);
            output_reco->h1_tauTau_b_MHT->Fill(tauTau_b_MHT_reco, eventWeight_common);
            
            output_reco->h1_tauTau_jet_HT->Fill(tauTau_jet_HT_reco, eventWeight_common);
            output_reco->h1_tauTau_jet_MHT->Fill(tauTau_jet_MHT_reco, eventWeight_common);
            
            if(tauTau_jet_HT_reco > 0)
            {
                output_reco->h1_tauTau_b_HT_by_tauTau_jet_HT->Fill(tauTau_b_HT_reco/tauTau_jet_HT_reco, eventWeight_common);
            }
            
            else
            {
                output_reco->h1_tauTau_b_HT_by_tauTau_jet_HT->Fill(-1, eventWeight_common);
            }
            
            if(tauTau_jet_MHT_reco > 0)
            {
                output_reco->h1_tauTau_b_MHT_by_tauTau_jet_MHT->Fill(tauTau_b_MHT_reco/tauTau_jet_MHT_reco, eventWeight_common);
            }
            
            else
            {
                output_reco->h1_tauTau_b_MHT_by_tauTau_jet_MHT->Fill(-1, eventWeight_common);
            }
            
            
            // lblb mT2
            double tauBtauB_MET_mT2_lsp0 = 0;
            
            if(tauPair_pos.size())
            {
                if(b_n_medium >= 2)
                {
                    tauBtauB_MET_mT2_lsp0 = Common::get_lepBlepB_mT2(
                        tau1_4mom_reco,
                        b1_4mom_reco,
                        tau2_4mom_reco,
                        b2_4mom_reco,
                        MET_E_reco*cos(MET_phi_reco),
                        MET_E_reco*sin(MET_phi_reco)
                    );
                }
                
                // Use nonBjet1 as b2 if there is only 1 b jet
                else if(b_n_medium == 1 && jet_n_reco >= 2)
                {
                    tauBtauB_MET_mT2_lsp0 = Common::get_lepBlepB_mT2(
                        tau1_4mom_reco,
                        b1_4mom_reco,
                        tau2_4mom_reco,
                        nonBjet1_4mom_reco,
                        MET_E_reco*cos(MET_phi_reco),
                        MET_E_reco*sin(MET_phi_reco)
                    );
                }
            }
            
            output_reco->h1_tauBtauB_MET_mT2_lsp0->Fill(tauBtauB_MET_mT2_lsp0, eventWeight_common);
            
            
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
                (double) tauPair_pos.size(),
                tauTau_MET_mT2_lsp0,
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
                (double) tauPair_pos.size(),
                tauTau_MET_mT2_lsp0,
                MET_E_reco,
                tauTau_jet_HT_reco,
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
                (double) tauPair_pos.size(),
                tauBtauB_MET_mT2_lsp0,
                MET_E_reco,
                tauTau_jet_HT_reco,
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
                (double) tauPair_pos.size(),
                tauTau_MET_mT2_lsp0,
                MET_E_reco,
                tauBtauB_MET_mT2_lsp0,
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
            
            
            // DYCR
            //v_eventWeight.resize(0);
            //v_eventWeight.resize(output_reco->getCutFlow("DYCR1")->GetNbinsX()-1, eventWeight_common);
            //v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight;
            //
            //v_selectionVar = {
            //    (double) tauPair_pos.size(),
            //    tauTau_MET_mT2_lsp0,
            //    MET_E_reco,
            //    tauTau_jet_HT_reco,
            //    (double) b_n_medium
            //};
            //
            //output_reco->updateBins(
            //    "DYCR",
            //    Common::vv_cut_DYCR,
            //    v_selectionVar,
            //    v_eventWeight,
            //    1
            //);
        }
        
        
        printf("\n\n");
        printf("[%s] Number of evenst skipped: %d \n\n", output_reco->nameAddon, nEventSkipped);
    }
}


# endif

# ifndef Analyze_elMu_H
# define Analyze_elMu_H

# include <map>
//# include <typeinfo>

# include "RooWorkspace.h"
# include "RooRealVar.h"

# include "BTagCalibrationStandalone.h"
# include "ElMuScaleFactor.h"
# include "lester_mt2_bisect_mod.h"

# include "CustomInfo_data.h"
# include "CustomInfo_mc.h"
# include "Output_GEN.h"
# include "Output_RECO.h"


namespace Analyze_elMu
{
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        const char *era,
        bool isMC,
        bool isSUSY,
        std::map <std::string, bool> m_correction
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        const char *era,
        bool isMC,
        bool isSUSY,
        std::vector <double> v_eventWeight_nJetBin,
        std::map <std::string, bool> m_correction
    );
    
    
    template <typename T1> void analyze_reco(T1 *input,
        Output_RECO::Output *output_reco,
        std::map <std::pair <int, int>, Output_RECO::Output*> *m_output_reco,
        const char *elMu_signOption,
        std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::vector <double> v_eventWeight_nJetBin,
        BTagCalibration *bTagCalib,
        std::string fileName_bTaggingEfficiency,
        ElMuScaleFactor::ScaleFactor *elIdIsoSFobject,
        ElMuScaleFactor::ScaleFactor *muIdIsoSFobject,
        std::map <std::string, ElMuScaleFactor::ScaleFactor*> *m_elMuTriggerSFobject,
        RooWorkspace *htt_scaleFactorWS,
        std::map <std::string, bool> m_correction,
        bool elGenMatching = false,
        double elGenMatching_deltaRcut = 9999,
        bool muGenMatching = false,
        double muGenMatching_deltaRcut = 9999
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
                iter->second->addJetHist(2);
                iter->second->addNonBjetHist(2);
            }
        }
        
        else
        {
            output_reco->addbHist(2);
        }
        
        // If no event selection provided, selection is always true
        if(!eventSelectionStr.length())
        {
            eventSelectionStr = "1";
        }
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            input->T_reco->GetEntry(iEvent);
            
            
            if(isMC)
            {
                input->T_gen->GetEntry(iEvent);
            }
            
            // Select mass point
            if(isSUSY)
            {
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
            
            
            double eventWeight_common = 1;
            output_reco->h1_nEvent->Fill(0.0, eventWeight_common);
            
            
            if(isMC)
            {
                // n-jet bin stitching event weight
                if(v_eventWeight_nJetBin.size())
                {
                    double eventWeight_nJetBin = Common::getEventWeight_nJetBin(v_eventWeight_nJetBin, input->outgoingParton_n_gen);
                    //printf("eventWeight_nJetBin: %d %f \n", input->outgoingParton_n_gen, eventWeight_nJetBin);
                    
                    eventWeight_common *= eventWeight_nJetBin;
                }
            }
            
            
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->at(0) += eventWeight_common;
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->Fill(0.0, eventWeight_common);
            
            for(int iCRA = 0; iCRA < 6; iCRA++)
            {
                //output_reco->getCutFlow(("CRA"+std::to_string(iCRA+1)).c_str())->at(0) += eventWeight_common;
                
                output_reco->getCutFlow(("CRA"+std::to_string(iCRA+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            for(int iCRB = 0; iCRB < 18; iCRB++)
            {
                //output_reco->getCutFlow(("CRB"+std::to_string(iCRB+1)).c_str())->at(0) += eventWeight_common;
                
                output_reco->getCutFlow(("CRB"+std::to_string(iCRB+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            
            // Trigger
            if(!(
                // 2016 and 2017
                input->isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v ||
                input->isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v ||
                input->isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v ||
                input->isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v ||
                
                isSUSY
            ))
            {
                continue;
            }
            
            
            // Select MET
            double MET_E_reco = -9999;
            double MET_phi_reco = -9999;
            
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
            
            //std::string eventSelectionStr;
            
            std::vector <double> v_el_pTetacut(input->el_n_reco, 0);
            std::vector <double> v_el_IPcut(input->el_n_reco, 0);
            std::vector <double> v_el_missingInnerHitsCut(input->el_n_reco, 0);
            
            for(int iEl = 0; iEl < input->el_n_reco; iEl++)
            {
                CLHEP::HepLorentzVector el_4mom_reco;
                
                el_4mom_reco.setT(fabs(input->v_el_E_reco->at(iEl)));
                el_4mom_reco.setX(input->v_el_px_reco->at(iEl));
                el_4mom_reco.setY(input->v_el_py_reco->at(iEl));
                el_4mom_reco.setZ(input->v_el_pz_reco->at(iEl));
                
                if(el_4mom_reco.perp() > Common::el_pTcut_elMu_reco && fabs(el_4mom_reco.eta()) < Common::el_etaCut_elMu_reco)
                {
                    v_el_pTetacut.at(iEl) = 1;
                }
                
                if(fabs(input->v_el_dxy_reco->at(iEl)) < Common::el_dxyCut_reco && fabs(input->v_el_dz_reco->at(iEl)) < Common::el_dzCut_reco)
                {
                    v_el_IPcut.at(iEl) = 1;
                }
                
                if(input->v_el_missingInnerHits_reco->at(iEl) <= Common::el_missingInnerHitsCut_reco)
                {
                    v_el_missingInnerHitsCut.at(iEl) = 1;
                }
            }
            
            std::vector <double> v_mu_pTetacut(input->mu_n_reco, 0);
            std::vector <double> v_mu_IPcut(input->mu_n_reco, 0);
            
            for(int iMu = 0; iMu < input->mu_n_reco; iMu++)
            {
                CLHEP::HepLorentzVector mu_4mom_reco;
                
                mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(iMu)));
                mu_4mom_reco.setX(input->v_mu_px_reco->at(iMu));
                mu_4mom_reco.setY(input->v_mu_py_reco->at(iMu));
                mu_4mom_reco.setZ(input->v_mu_pz_reco->at(iMu));
                
                if(mu_4mom_reco.perp() > Common::mu_pTcut_elMu_reco && fabs(mu_4mom_reco.eta()) < Common::mu_etaCut_elMu_reco)
                {
                    v_mu_pTetacut.at(iMu) = 1;
                }
                
                if(fabs(input->v_mu_dxy_reco->at(iMu)) < Common::mu_dxyCut_reco && fabs(input->v_mu_dz_reco->at(iMu)) < Common::mu_dzCut_reco)
                {
                    v_mu_IPcut.at(iMu) = 1;
                }
            }
            
            
            std::vector <double> *v_el_ID;
            
            if(!strcmp(era, "2016"))
            {
                //printf("Using 2016 electron ID. \n");
                v_el_ID = input->v_el_mvaEleIDSpring16GeneralPurposeV1wp80_reco;
            }
            
            else if(!strcmp(era, "2017"))
            {
                //printf("Using 2017 electron ID. \n");
                v_el_ID = input->v_el_mvaEleIDFall17noIsoV2wp80_reco;
            }
            
            std::vector <std::vector <double>* > vv_elSelection = {
                v_el_ID,
                input->v_el_passConversionVeto_reco,
                &v_el_missingInnerHitsCut,
                &v_el_IPcut,
                input->v_el_byTightPFbasedCombinedRelativeDeltaBetaCorrdR03_reco,
                &v_el_pTetacut
            };
            
            std::vector <std::vector <double>* > vv_muSelection = {
                input->v_mu_isMediumMuon_reco,
                &v_mu_IPcut,
                input->v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco,
                &v_mu_pTetacut
            };
            
            //printf("Searching for el-mu pair. \n");
            //fflush(stdout);
            
            std::vector <int> elMu_pos = Common::getObjPair(
                &(input->v_el_reco),
                &(input->v_mu_reco),
                false,
                vv_elSelection,
                vv_muSelection,
                Common::elMu_deltaRcut_reco,
                elMu_signOption
            );
            
            // At least one El-Mu pair
            if(!elMu_pos.size())
            {
                continue;
            }
            
            //printf("Found el-mu pair. \n");
            //fflush(stdout);
            
            CLHEP::HepLorentzVector elMu_el_4mom_reco;
            elMu_el_4mom_reco.setT(fabs(input->v_el_E_reco->at(elMu_pos.at(0))));
            elMu_el_4mom_reco.setX(input->v_el_px_reco->at(elMu_pos.at(0)));
            elMu_el_4mom_reco.setY(input->v_el_py_reco->at(elMu_pos.at(0)));
            elMu_el_4mom_reco.setZ(input->v_el_pz_reco->at(elMu_pos.at(0)));
            
            CLHEP::HepLorentzVector elMu_mu_4mom_reco;
            elMu_mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(elMu_pos.at(1))));
            elMu_mu_4mom_reco.setX(input->v_mu_px_reco->at(elMu_pos.at(1)));
            elMu_mu_4mom_reco.setY(input->v_mu_py_reco->at(elMu_pos.at(1)));
            elMu_mu_4mom_reco.setZ(input->v_mu_pz_reco->at(elMu_pos.at(1)));
            
            std::vector <std::pair <std::vector <CLHEP::HepLorentzVector>, double> > vp_obj4mom_deltaR_min = {
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {elMu_el_4mom_reco}, 
                    0.3
                ),
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {elMu_mu_4mom_reco}, 
                    0.4
                )
            };
            
            
            // Gen-matching
            bool isElGenMatched = false;
            bool isMuGenMatched = false;
            
            if(isMC)
            {
                // Electron gen-matching
                if(elGenMatching)
                {
                    std::vector <bool> v_el_isUsed_gen(input->el_n_gen, false);
                    
                    for(int iEl_gen = 0; iEl_gen < input->el_n_gen; iEl_gen++)
                    {
                        CLHEP::HepLorentzVector el_4mom_gen;
                        
                        el_4mom_gen.setT(fabs(input->v_el_E_gen->at(iEl_gen)));
                        el_4mom_gen.setX(input->v_el_px_gen->at(iEl_gen));
                        el_4mom_gen.setY(input->v_el_py_gen->at(iEl_gen));
                        el_4mom_gen.setZ(input->v_el_pz_gen->at(iEl_gen));
                        
                        if(el_4mom_gen.perp() < Common::el_pTcut_elMu_reco || fabs(el_4mom_gen.eta()) > Common::el_etaCut_elMu_reco)
                        {
                            continue;
                        }
                        
                        double deltaR = el_4mom_gen.deltaR(elMu_el_4mom_reco);
                        
                        if(deltaR < elGenMatching_deltaRcut)
                        {
                            isElGenMatched = true;
                            
                            break;
                        }
                    }
                    
                    if(!isElGenMatched)
                    {
                        continue;
                    }
                }
                
                // Muon gen-matching
                if(muGenMatching)
                {
                    std::vector <bool> v_mu_isUsed_gen(input->mu_n_gen, false);
                    
                    for(int iMu_gen = 0; iMu_gen < input->mu_n_gen; iMu_gen++)
                    {
                        CLHEP::HepLorentzVector mu_4mom_gen;
                        
                        mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu_gen)));
                        mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu_gen));
                        mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu_gen));
                        mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu_gen));
                        
                        if(mu_4mom_gen.perp() < Common::mu_pTcut_elMu_reco || fabs(mu_4mom_gen.eta()) > Common::mu_etaCut_elMu_reco)
                        {
                            continue;
                        }
                        
                        double deltaR = mu_4mom_gen.deltaR(elMu_mu_4mom_reco);
                        
                        if(deltaR < muGenMatching_deltaRcut)
                        {
                            isMuGenMatched = true;
                            
                            break;
                        }
                    }
                    
                    if(!isMuGenMatched)
                    {
                        continue;
                    }
                }
            }
            
            double pileUpReweightFactor = 1;
            double bTaggingEventWeight_medium = 1;
            double bTaggingEventWeight_tight = 1;
            
            
            if(isMC)
            {
                // Get pile-up reweight factor
                if(!strcmp(era, "2016"))
                {
                    pileUpReweightFactor = Common::getPileUpReweightFactor( \
                        input->h1_pileUp_mc, input->h1_pileUp_data,
                        input->pileUp_n_reco);
                    
                    //printf("pileUp %d, pileUpReweightFactor %f \n", input->pileUp_n_reco, pileUpReweightFactor);
                    output_reco->h1_pileUpReweightFactor->Fill(pileUpReweightFactor);
                    
                    eventWeight_common *= pileUpReweightFactor;
                }
                
                double elIdIsoSF = 1;
                double muIdIsoSF = 1;
                
                if(!strcmp(era, "2016"))
                {
                    // El Id-iso SF
                    elIdIsoSF = elIdIsoSFobject->get_ScaleFactor(elMu_el_4mom_reco.perp(), elMu_el_4mom_reco.eta());
                    
                    // Mu Id-iso SF
                    muIdIsoSF = muIdIsoSFobject->get_ScaleFactor(elMu_mu_4mom_reco.perp(), elMu_mu_4mom_reco.eta());
                    
                }
                
                else if(!strcmp(era, "2017"))
                {
                    htt_scaleFactorWS->var("e_pt")->setVal(elMu_el_4mom_reco.perp());
                    htt_scaleFactorWS->var("e_eta")->setVal(elMu_el_4mom_reco.eta());
                    
                    htt_scaleFactorWS->var("m_pt")->setVal(elMu_mu_4mom_reco.perp());
                    htt_scaleFactorWS->var("m_eta")->setVal(elMu_mu_4mom_reco.eta());
                    
                    elIdIsoSF = htt_scaleFactorWS->function("e_id_ratio")->getVal()*htt_scaleFactorWS->function("e_iso_ratio")->getVal();
                    
                    muIdIsoSF = htt_scaleFactorWS->function("m_id_ratio")->getVal()*htt_scaleFactorWS->function("m_iso_ratio")->getVal();
                }
                
                output_reco->h1_el_IdIsoSF->Fill(elIdIsoSF);
                eventWeight_common *= elIdIsoSF;
                
                output_reco->h1_mu_IdIsoSF->Fill(muIdIsoSF);
                eventWeight_common *= muIdIsoSF;
                
                // El-Mu trigger SF
                double elTrigSF = 1.0;
                double muTrigSF = 1.0;
                
                if(input->isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v || input->isTriggerPassed_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v)
                {
                    if(!strcmp(era, "2016"))
                    {
                        if(isSUSY)
                        {
                            elTrigSF = m_elMuTriggerSFobject->at("Mu8leg")->get_EfficiencyMC(elMu_mu_4mom_reco.perp(), elMu_mu_4mom_reco.eta());
                            muTrigSF = m_elMuTriggerSFobject->at("Ele23leg")->get_EfficiencyMC(elMu_el_4mom_reco.perp(), elMu_el_4mom_reco.eta());
                        }
                        
                        else
                        {
                            elTrigSF = m_elMuTriggerSFobject->at("Mu8leg")->get_ScaleFactor(elMu_mu_4mom_reco.perp(), elMu_mu_4mom_reco.eta());
                            muTrigSF = m_elMuTriggerSFobject->at("Ele23leg")->get_ScaleFactor(elMu_el_4mom_reco.perp(), elMu_el_4mom_reco.eta());
                        }
                    }
                    
                    else if(!strcmp(era, "2017"))
                    {
                        htt_scaleFactorWS->var("e_pt")->setVal(elMu_el_4mom_reco.perp());
                        htt_scaleFactorWS->var("e_eta")->setVal(elMu_el_4mom_reco.eta());
                        
                        htt_scaleFactorWS->var("m_pt")->setVal(elMu_mu_4mom_reco.perp());
                        htt_scaleFactorWS->var("m_eta")->setVal(elMu_mu_4mom_reco.eta());
                        
                        elTrigSF = htt_scaleFactorWS->function("e_trg_23_ratio")->getVal();
                        muTrigSF = htt_scaleFactorWS->function("m_trg_8_ratio")->getVal();
                    }
                }
                
                if(input->isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v || input->isTriggerPassed_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v)
                {
                    if(!strcmp(era, "2016"))
                    {
                        if(isSUSY)
                        {
                            elTrigSF = m_elMuTriggerSFobject->at("Mu23leg")->get_EfficiencyMC(elMu_el_4mom_reco.perp(), elMu_el_4mom_reco.eta());
                            muTrigSF = m_elMuTriggerSFobject->at("Ele12leg")->get_EfficiencyMC(elMu_mu_4mom_reco.perp(), elMu_mu_4mom_reco.eta());
                        }
                        
                        else
                        {
                            elTrigSF = m_elMuTriggerSFobject->at("Mu23leg")->get_ScaleFactor(elMu_el_4mom_reco.perp(), elMu_el_4mom_reco.eta());
                            muTrigSF = m_elMuTriggerSFobject->at("Ele12leg")->get_ScaleFactor(elMu_mu_4mom_reco.perp(), elMu_mu_4mom_reco.eta());
                        }
                    }
                    
                    else if(!strcmp(era, "2017"))
                    {
                        htt_scaleFactorWS->var("e_pt")->setVal(elMu_el_4mom_reco.perp());
                        htt_scaleFactorWS->var("e_eta")->setVal(elMu_el_4mom_reco.eta());
                        
                        htt_scaleFactorWS->var("m_pt")->setVal(elMu_mu_4mom_reco.perp());
                        htt_scaleFactorWS->var("m_eta")->setVal(elMu_mu_4mom_reco.eta());
                        
                        elTrigSF = htt_scaleFactorWS->function("e_trg_12_ratio")->getVal();
                        muTrigSF = htt_scaleFactorWS->function("m_trg_23_ratio")->getVal();
                    }
                }
                
                //htt_scaleFactorWS->var("e_pt")->setVal(elMu_el_4mom_reco.perp());
                //htt_scaleFactorWS->var("e_eta")->setVal(elMu_el_4mom_reco.eta());
                //
                //htt_scaleFactorWS->var("m_pt")->setVal(elMu_mu_4mom_reco.perp());
                //htt_scaleFactorWS->var("m_eta")->setVal(elMu_mu_4mom_reco.eta());
                //
                //printf(
                //    "[%d] el: pT %0.2f, eta %0.2f, "
                //    "IdSF %0.2f, "
                //    "isoSF %0.2f, "
                //    "IdIsoSF %0.2f (%0.2f), "
                //    "trigSF %0.2f \n",
                //    
                //    iEvent+1, elMu_el_4mom_reco.perp(), elMu_el_4mom_reco.eta(),
                //    htt_scaleFactorWS->function("e_id_ratio")->getVal(),
                //    htt_scaleFactorWS->function("e_iso_ratio")->getVal(),
                //    htt_scaleFactorWS->function("e_id_ratio")->getVal()*htt_scaleFactorWS->function("e_iso_ratio")->getVal(), elIdIsoSF,
                //    elTrigSF
                //);
                //
                //printf(
                //    "[%d] mu: pT %0.2f, eta %0.2f, "
                //    "IdSF %0.2f, "
                //    "isoSF %0.2f, "
                //    "IdIsoSF %0.2f (%0.2f), "
                //    "trigSF %0.2f \n",
                //    
                //    iEvent+1, elMu_mu_4mom_reco.perp(), elMu_mu_4mom_reco.eta(),
                //    htt_scaleFactorWS->function("m_id_ratio")->getVal(),
                //    htt_scaleFactorWS->function("m_iso_ratio")->getVal(),
                //    htt_scaleFactorWS->function("m_id_ratio")->getVal()*htt_scaleFactorWS->function("m_iso_ratio")->getVal(), muIdIsoSF,
                //    muTrigSF
                //);
                
                eventWeight_common *= elTrigSF;
                eventWeight_common *= muTrigSF;
                
                output_reco->h1_elMuTrig_elSF->Fill(elTrigSF);
                output_reco->h1_elMuTrig_muSF->Fill(muTrigSF);
                output_reco->h1_elMuTrigSF->Fill(elTrigSF*muTrigSF);
                
                
                // Get b-tagging SF event weight
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
                            "comb"
                        );
                        
                        bTagCalibReader_CSVv2M.load(*bTagCalib,
                            BTagEntry::FLAV_C,
                            "comb"
                        );
                        
                        bTagCalibReader_CSVv2M.load(*bTagCalib,
                            BTagEntry::FLAV_UDSG,
                            "incl"
                        );
                    }
                
                    bTaggingEventWeight_medium = Common::getBTaggingEventWeight(&input->v_jet_reco,
                        Common::b_pTcut_reco, Common::b_etaCut_reco,
                        input->v_jet_partonFlavour_reco,
                        input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
                        &bTagCalibReader_CSVv2M,
                        "central",
                        fileName_bTaggingEfficiency,
                        "bTaggingEff_eff_b_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
                        "bTaggingEff_eff_c_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
                        "bTaggingEff_eff_udsg_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2M",
                        vp_obj4mom_deltaR_min
                    );
                }
                
                //printf("bTaggingEventWeight %f \n", bTaggingEventWeight);
                //output_reco->h1_bTaggingEventWeight_medium->Fill(bTaggingEventWeight_medium);
                
                
                /*BTagCalibrationReader bTagCalibReader_CSVv2T( \
                    BTagEntry::OP_TIGHT,
                    "central",
                    {"up", "down"}
                );
                
                
                bTagCalibReader_CSVv2T.load(*bTagCalib,
                    BTagEntry::FLAV_B,
                    "comb");
                
                bTagCalibReader_CSVv2T.load(*bTagCalib,
                    BTagEntry::FLAV_C,
                    "comb");
                
                bTagCalibReader_CSVv2T.load(*bTagCalib,
                    BTagEntry::FLAV_UDSG,
                    "incl");
            
                bTaggingEventWeight_tight = Common::getBTaggingEventWeight(&input->v_jet_reco,
                    Common::b_pTcut_reco, Common::b_etaCut_reco,
                    input->v_jet_partonFlavour_reco,
                    input->v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco,
                    &bTagCalibReader_CSVv2T,
                    "central",
                    fileName_bTaggingEfficiency,
                    "bTaggingEff_eff_b_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2T",
                    "bTaggingEff_eff_c_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2T",
                    "bTaggingEff_eff_udsg_pfCombinedInclusiveSecondaryVertexV2BJetTags_CSVv2T",
                    vp_obj4mom_deltaR_min
                );
                
                output_reco->h1_bTaggingEventWeight_tight->Fill(bTaggingEventWeight_tight);*/
                
                
                // Top pT reweighting
                double eventWeight_topPt = 1.0;
                
                if(m_correction.at(Common::topPtReweighting_str))
                {
                    
                    std::pair <std::pair <double, double>, std::pair <double, double> > topPtReweightFactor_info = Common::getTopPtReweightFactor(
                        &input->v_t_gen,
                        Common::SYST_CENTRAL
                    );
                    
                    eventWeight_topPt = topPtReweightFactor_info.first.first;
                    
                    output_reco->h1_topPtReweightFactor->Fill(eventWeight_topPt);
                    output_reco->h2_top1PtReweightFactor_vs_pT->Fill(topPtReweightFactor_info.second.first, eventWeight_topPt);
                    output_reco->h2_top2PtReweightFactor_vs_pT->Fill(topPtReweightFactor_info.second.second, eventWeight_topPt);
                }
                
                eventWeight_common *= eventWeight_topPt;
            }
            
            
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->at(1) += eventWeight_common;
            
            //double MET_pZeta = Common::getPzeta(
            //    {{MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco)}},
            //    
            //    {elMu_el_4mom_reco.px(), elMu_el_4mom_reco.py()},
            //    {elMu_mu_4mom_reco.px(), elMu_mu_4mom_reco.py()});
            
            double elMu_pZeta = Common::getPzeta(
                {{elMu_el_4mom_reco.px(), elMu_el_4mom_reco.py()},
                {elMu_mu_4mom_reco.px(), elMu_mu_4mom_reco.py()}},
                
                {elMu_el_4mom_reco.px(), elMu_el_4mom_reco.py()},
                {elMu_mu_4mom_reco.px(), elMu_mu_4mom_reco.py()});
            
            double elMu_MET_pZeta = Common::getPzeta(
                {{elMu_el_4mom_reco.px(), elMu_el_4mom_reco.py()},
                {elMu_mu_4mom_reco.px(), elMu_mu_4mom_reco.py()},
                {MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco)}},
                
                {elMu_el_4mom_reco.px(), elMu_el_4mom_reco.py()},
                {elMu_mu_4mom_reco.px(), elMu_mu_4mom_reco.py()});
            
            double elMu_MET_Dzeta = elMu_MET_pZeta - 1.85*elMu_pZeta;
            
            
            // Dzeta cut
            //eventSelectionStr = "elMu_Dzeta < -35";
            //
            //if(m_eventSelection.find(eventSelectionStr) == m_eventSelection.end())
            //{
            //    printf("Error: Event selection string \"%s\" not found. \n", eventSelectionStr.c_str());
            //    exit(EXIT_FAILURE);
            //}
            //
            //if(m_eventSelection[eventSelectionStr] && elMu_MET_Dzeta >= -35)
            //{
            //    continue;
            //}
            //
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->at(2) += eventWeight_common;
            
            
            // MET cut
            //eventSelectionStr = "MET > 80";
            //
            //if(m_eventSelection.find(eventSelectionStr) == m_eventSelection.end())
            //{
            //    printf("Error: Event selection string \"%s\" not found. \n", eventSelectionStr.c_str());
            //    exit(EXIT_FAILURE);
            //}
            //
            //if(m_eventSelection[eventSelectionStr] && MET_E_reco <= 50)
            //{
            //    continue;
            //}
            //
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->at(3) += eventWeight_common;
            
            
            double elMu_m = (elMu_el_4mom_reco + elMu_mu_4mom_reco).m();
            
            // el-mu inv. mass cut
            //eventSelectionStr = "elMu_m > 90";
            //
            //if(m_eventSelection.find(eventSelectionStr) == m_eventSelection.end())
            //{
            //    printf("Error: Event selection string \"%s\" not found. \n", eventSelectionStr.c_str());
            //    exit(EXIT_FAILURE);
            //}
            //
            //if(m_eventSelection[eventSelectionStr] && elMu_m <= 90)
            //{
            //    continue;
            //}
            //
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->at(4) += eventWeight_common;
            
            
            asymm_mt2_lester_bisect::disableCopyrightMessage();
            
            double elMu_MET_mT2 = asymm_mt2_lester_bisect::get_mT2( \
                elMu_el_4mom_reco.m(), elMu_el_4mom_reco.px(), elMu_el_4mom_reco.py(),
                elMu_mu_4mom_reco.m(), elMu_mu_4mom_reco.px(), elMu_mu_4mom_reco.py(),
                MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco),
                0, 0);
            
            
            
            // RECO jet
            int jet_n_reco = 0;
            
            int b_n_loose = 0,
                b_n_medium = 0,
                b_n_tight = 0;
            
            double jet_HT_reco = 0;
            
            CLHEP::HepLorentzVector b1_4mom_reco(0.0, 0.0, 0.0, 0.0);
            CLHEP::HepLorentzVector b2_4mom_reco(0.0, 0.0, 0.0, 0.0);
            
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
                bool hasElOverlap = jet_4mom_reco.deltaR(elMu_el_4mom_reco) < 0.3;
                bool hasMuOverlap = jet_4mom_reco.deltaR(elMu_mu_4mom_reco) < 0.4;
                
                if(hasElOverlap || hasMuOverlap)
                {
                    //printf("Event %d: excluding jet %d. \n", iEvent, iJet);
                    continue;
                }
                
                jet_n_reco++;
                
                jet_HT_reco += jet_4mom_reco.perp();
                
                // RECO b
                if(jet_4mom_reco.perp() < Common::b_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::b_etaCut_reco)
                {
                    continue;
                }
                
                if(input->v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    //output_reco->h1_b_pT_loose->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    //output_reco->h1_b_eta_loose->Fill(jet_4mom_reco.eta(), eventWeight_common);
                    
                    b_n_loose++;
                }
                
                if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    //output_reco->h1_b_pT_medium->Fill(jet_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight_medium);
                    //output_reco->h1_b_eta_medium->Fill(jet_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight_medium);
                    
                    b_n_medium++;
                    
                    if(jet_4mom_reco.perp() > b1_4mom_reco.perp())
                    {
                        b1_4mom_reco = jet_4mom_reco;
                    }
                    
                    else if(jet_4mom_reco.perp() > b2_4mom_reco.perp())
                    {
                        b2_4mom_reco = jet_4mom_reco;
                    }
                    
                    //if(b_n_medium && b_n_medium <= 2)
                    //{
                    //    output_reco->v_h1_b_pT[b_n_medium-1]->Fill(jet_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight_medium);
                    //    output_reco->v_h1_b_eta[b_n_medium-1]->Fill(jet_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight_medium);
                    //    output_reco->v_h1_b_phi[b_n_medium-1]->Fill(jet_4mom_reco.phi(), eventWeight_common*bTaggingEventWeight_medium);
                    //}
                }
                
                if(input->v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    //output_reco->h1_b_pT_tight->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    //output_reco->h1_b_eta_tight->Fill(jet_4mom_reco.eta(), eventWeight_common);
                    
                    b_n_tight++;
                }
            }
            
            double elMu_jet_HT_reco = elMu_el_4mom_reco.perp() + elMu_mu_4mom_reco.perp() + jet_HT_reco;
            
            // Event selection
            bool isEventSelected = Common::evaluateExpression(
                eventSelectionStr,
                {
                    std::make_pair("elMu_m", elMu_m),
                    std::make_pair("MET_E_reco", MET_E_reco),
                    std::make_pair("elMu_jet_HT_reco", elMu_jet_HT_reco),
                    std::make_pair("b_n_reco", b_n_medium),
                }//,
                //true
            );
            
            if(!isEventSelected)
            {
                continue;
            }
            
            if(b_n_medium >= 1)
            {
                output_reco->v_h1_b_pT[0]->Fill(b1_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight_medium);
                output_reco->v_h1_b_eta[0]->Fill(b1_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight_medium);
                output_reco->v_h1_b_phi[0]->Fill(b1_4mom_reco.phi(), eventWeight_common*bTaggingEventWeight_medium);
            }
            
            if(b_n_medium >= 2)
            {
                output_reco->v_h1_b_pT[1]->Fill(b2_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight_medium);
                output_reco->v_h1_b_eta[1]->Fill(b2_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight_medium);
                output_reco->v_h1_b_phi[1]->Fill(b2_4mom_reco.phi(), eventWeight_common*bTaggingEventWeight_medium);
            }
            
            // At least 1 b jet
            //eventSelectionStr = "b_n >= 1";
            //
            //if(m_eventSelection.find(eventSelectionStr) == m_eventSelection.end())
            //{
            //    printf("Error: Event selection string \"%s\" not found. \n", eventSelectionStr.c_str());
            //    exit(EXIT_FAILURE);
            //}
            //
            //if(m_eventSelection[eventSelectionStr])
            //{
            //    // Multiply b-tagging event-weight after b-selection
            //    eventWeight_common *= bTaggingEventWeight_medium;
            //    
            //    if(b_n_medium < 1)
            //    {
            //        continue;
            //    }
            //}
            //
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->at(5) += eventWeight_common;
            
            output_reco->h1_bTaggingEventWeight_medium->Fill(bTaggingEventWeight_medium);
            //output_reco->h1_bTaggingEventWeight_tight->Fill(bTaggingEventWeight_tight);
            
            // At least 2 b jets
            //eventSelectionStr = "b_n >= 2";
            //
            //if(m_eventSelection.find(eventSelectionStr) == m_eventSelection.end())
            //{
            //    printf("Error: Event selection string \"%s\" not found. \n", eventSelectionStr.c_str());
            //    exit(EXIT_FAILURE);
            //}
            //
            //if(m_eventSelection[eventSelectionStr] && b_n_medium < 2)
            //{
            //    continue;
            //}
            //
            //output_reco->getCutFlow("cutFlow_ttbar_elMu_CR")->at(6) += eventWeight_common;
            
            // RECO b jet number
            output_reco->h1_b_n_loose->Fill(b_n_loose, eventWeight_common);
            output_reco->h1_b_n_medium->Fill(b_n_medium, eventWeight_common*bTaggingEventWeight_medium);
            output_reco->h1_b_n_tight->Fill(b_n_tight, eventWeight_common);
            
            //if(elMu_el_4mom_reco.perp() <= Common::el_pTcut_reco) 
            //    printf("elMu_el_4mom_reco.perp() %f \n", elMu_el_4mom_reco.perp());
            //if(elMu_mu_4mom_reco.perp() <= Common::mu_pTcut_reco) 
            //    printf("elMu_mu_4mom_reco.perp() %f \n", elMu_mu_4mom_reco.perp());
            
            // el-mu variables
            output_reco->h1_elMu_el_pT->Fill(elMu_el_4mom_reco.perp(), eventWeight_common);
            output_reco->h1_elMu_el_eta->Fill(elMu_el_4mom_reco.eta(), eventWeight_common);
            
            output_reco->h1_elMu_mu_pT->Fill(elMu_mu_4mom_reco.perp(), eventWeight_common);
            output_reco->h1_elMu_mu_eta->Fill(elMu_mu_4mom_reco.eta(), eventWeight_common);
            
            output_reco->h1_elMu_deltaPhi->Fill(Common::getDeltaPhi(elMu_el_4mom_reco.phi(), elMu_mu_4mom_reco.phi()));
            
            output_reco->h1_elMu_m->Fill(elMu_m, eventWeight_common);
            output_reco->h1_elMu_MET_Dzeta->Fill(elMu_MET_Dzeta, eventWeight_common);
            output_reco->h1_elMu_MET_mT2->Fill(elMu_MET_mT2, eventWeight_common);
            
            output_reco->h1_jet_n->Fill(jet_n_reco, eventWeight_common);
            
            output_reco->h1_jet_HT->Fill(jet_HT_reco, eventWeight_common);
            output_reco->h1_elMu_jet_HT->Fill(elMu_jet_HT_reco, eventWeight_common);
            
            // MET
            output_reco->h1_MET_E->Fill(MET_E_reco, eventWeight_common);
            output_reco->h1_MET_phi->Fill(MET_phi_reco, eventWeight_common);
            
            
            std::vector <double> v_eventWeight;
            
            
            // CRA
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("CRA1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight_medium;
            
            output_reco->incrementCutFlow(
                "CRA1", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA2", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA3", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA4", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA5", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA6", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            
            //output_reco->incrementCutFlow(
            //    "cutFlow_ttbar_elMu_CR", 1,
            //    {(bool) elMu_pos.size(),
            //        elMu_m < 60 || elMu_m > 120,
            //        MET_E_reco >= 50,
            //        elMu_MET_mT2 >= 40,
            //        b_n_medium >= 1},
            //    v_eventWeight
            //);
            
            
            // CRB
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("CRB1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight_medium;
            
            output_reco->incrementCutFlow(
                "CRB1", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    elMu_jet_HT_reco >= 100 && elMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB2", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    elMu_jet_HT_reco >= 300 && elMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB3", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    elMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB4", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    elMu_jet_HT_reco >= 100 && elMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB5", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    elMu_jet_HT_reco >= 300 && elMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB6", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 0 && elMu_MET_mT2 < 40,
                    elMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB7", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    elMu_jet_HT_reco >= 100 && elMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB8", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    elMu_jet_HT_reco >= 300 && elMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB9", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    elMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB10", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    elMu_jet_HT_reco >= 100 && elMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB11", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    elMu_jet_HT_reco >= 300 && elMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB12", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 40 && elMu_MET_mT2 < 80,
                    elMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB13", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 80,
                    elMu_jet_HT_reco >= 100 && elMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB14", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 80,
                    elMu_jet_HT_reco >= 300 && elMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB15", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    elMu_MET_mT2 >= 80,
                    elMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB16", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 80,
                    elMu_jet_HT_reco >= 100 && elMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB17", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 80,
                    elMu_jet_HT_reco >= 300 && elMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB18", 1,
                {(bool) elMu_pos.size(),
                    elMu_m < 60 || elMu_m > 120,
                    MET_E_reco >= 200,
                    elMu_MET_mT2 >= 80,
                    elMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
        }
    }
}


# endif

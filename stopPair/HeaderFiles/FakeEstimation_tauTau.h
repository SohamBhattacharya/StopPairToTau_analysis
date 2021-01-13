# ifndef FakeEstimation_tauTau_H
# define FakeEstimation_tauTau_H

# include "BTagCalibrationStandalone.h"
# include "ElMuScaleFactor.h"
# include "lester_mt2_bisect_mod.h"

# include "Common.h"
# include "CustomInfo_data.h"
# include "CustomInfo_mc.h"
# include "Output_GEN.h"
# include "Output_RECO.h"
# include "TauEfficiencyAndSF.h"
# include "TauPromptAndFakeRate.h"
//# include "TemplateSmearing.h"


namespace FakeEstimation_tauTau
{
    class RunInfo
    {
        public:
        
        std::string term;
        std::string expression;
        std::string details;
        
        std::vector <double> *v_tau1_isolation;
        std::vector <double> *v_tau1_antiIsolation;
        
        std::vector <double> *v_tau2_isolation;
        std::vector <double> *v_tau2_antiIsolation;
        
        //std::map <std::string, bool> m_eventSelection;
        
        std::string eventSelectionStr;
        
        Output_RECO::Output *output_reco;
        
        
        RunInfo(
            std::string term,
            std::string expression,
            std::vector <double> *v_tau1_isolation, std::vector <double> *v_tau1_antiIsolation,
            std::vector <double> *v_tau2_isolation, std::vector <double> *v_tau2_antiIsolation,
            //std::map <std::string, bool> m_eventSelection,
            std::string eventSelectionStr,
            std::vector <const char*> v_outputOption_reco
        );
        
        
        void freeMemory();
    };
    
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::vector <double> v_eventWeight_nJetBin,
        std::string syst_name,
        Common::SYST_TYPE syst_type
    );
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::string syst_name,
        Common::SYST_TYPE syst_type
    );
    
    
    template <typename T1> void analyze_reco(
        T1 *input,
        Output_RECO::Output *output_reco,
        const char *tauTau_signOption,
        std::vector <double> *v_tau1_isolation, std::vector <double> *v_tau1_antiIsolation,
        std::vector <double> *v_tau2_isolation, std::vector <double> *v_tau2_antiIsolation,
        std::string promptFakeWeightExpression,
        bool isMC,
        std::string era,
        //std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        BTagCalibration *bTagCalib,
        std::string fileName_bTaggingEfficiency,
        TauEfficiencyAndSF::TauEfficiencyAndSF *tauEfficiencyObject,
        TauPromptAndFakeRate::TauPromptAndFakeRate *tauPandFobject,
        std::vector <double> v_eventWeight_nJetBin,
        std::string syst_name,
        Common::SYST_TYPE syst_type
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        output_reco->addTauHist(2);
        output_reco->addbHist(2);
        output_reco->addJetHist(2);
        output_reco->addNonBjetHist(2);
        
        // If no event selection provided, selection is always true
        if(!eventSelectionStr.length())
        {
            eventSelectionStr = "1";
        }
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if(iEvent == 0 || (iEvent+1) % 1000 == 0 || iEvent == nEvent-1)
            {
                printf("[%s] Processing event no. %d / %d \n", output_reco->nameAddon, iEvent+1, nEvent);
                fflush(stdout);
            }
            
            input->T_reco->GetEntry(iEvent);
            
            double eventWeight_common = 1;
            
            output_reco->h1_nEvent->Fill(0.0, eventWeight_common);
            
            for(int iSRB = 0; iSRB < 18; iSRB++)
            {
                output_reco->getCutFlow(("SRB"+std::to_string(iSRB+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            for(int iDYCR = 0; iDYCR < 18; iDYCR++)
            {
                output_reco->getCutFlow(("DYCR"+std::to_string(iDYCR+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            // Select MET
            double MET_E_reco = -9999;
            double MET_phi_reco = -9999;
            
            if(!syst_name.compare("JEC"))
            {
                MET_E_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JEC", syst_type)).at("E"));
                MET_phi_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "JEC", syst_type)).at("phi"));
            }
            
            if(!syst_name.compare("unclusteredEnergy"))
            {
                MET_E_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "unclusteredEnergy", syst_type)).at("E"));
                MET_phi_reco = *(input->m_MET_reco.at(std::string(era)).at(syst_name).at(chooseSystType(syst_name, "unclusteredEnergy", syst_type)).at("phi"));
            }
            
            else
            {
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
            }
            
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
            
            //if(input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v || input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v)
            //{
            //    //printf("[%s] Event %d: Trigger passed (%0.1f, %0.1f). \n",
            //    //    output_reco->nameAddon, iEvent+1,
            //    //    input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v,
            //    //    input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v
            //    //);
            //}
            
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
            
            std::vector <double> v_tau_ES(input->tau_n_reco, 1.0);
            
            std::vector <double> v_tau1_antiIsolationCut(input->tau_n_reco, 1);
            std::vector <double> v_tau2_antiIsolationCut(input->tau_n_reco, 1);
            
            //std::vector <double> v_tau1_antiIsolation_temp(input->tau_n_reco, 0);
            //std::vector <double> v_tau2_antiIsolation_temp(input->tau_n_reco, 0);
            
            //if(!v_tau1_antiIsolation)
            //{
            //    v_tau1_antiIsolation = &v_tau1_antiIsolation_temp;
            //    //printf("[%s] !v_tau1_antiIsolation \n", output_reco->nameAddon);
            //}
            //
            //if(!v_tau2_antiIsolation)
            //{
            //    v_tau2_antiIsolation = &v_tau2_antiIsolation_temp;
            //    //printf("[%s] !v_tau2_antiIsolation \n", output_reco->nameAddon);
            //}
            
            //if(v_tau1_antiIsolation)
            //{
            //    printf("Tau1 anti-isolation provided. \n");
            //}
            //
            //if(v_tau2_antiIsolation)
            //{
            //    printf("Tau2 anti-isolation provided. \n");
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
                
                if(v_tau1_antiIsolation && v_tau1_antiIsolation->at(iTau))
                {
                    v_tau1_antiIsolationCut.at(iTau) = 0;
                }
                
                if(v_tau2_antiIsolation && v_tau2_antiIsolation->at(iTau))
                {
                    v_tau2_antiIsolationCut.at(iTau) = 0;
                }
                
                ////if(v_tau1_isolation->at(iTau) && v_tau2_isolation->at(iTau))
                //{
                //    printf("[%s] Event %d: tau %d: %d %d, %d %d \n",
                //        output_reco->nameAddon, iEvent+1, iTau,
                //        (int) v_tau1_isolation->at(iTau), (int) v_tau1_antiIsolation->at(iTau),
                //        (int) v_tau2_isolation->at(iTau), (int) v_tau2_antiIsolation->at(iTau)
                //    );
                //}
                
                //if(!v_tau1_antiIsolation && !v_tau2_antiIsolation && input->tau_n_reco >= 2)
                //{
                //    printf("[%s] Event %d: tau %d/%d: %d (%d, %d) \n",
                //        output_reco->nameAddon, iEvent+1,
                //        iTau+1, input->tau_n_reco,
                //        (int) input->v_tau_isTriggerMatched_reco->at(iTau),
                //        (int) input->isTriggerPassed_HLT_DoubleMediumIsoPFTau35_Trk1_eta2p1_Reg_v,
                //        (int) input->isTriggerPassed_HLT_DoubleMediumCombinedIsoPFTau35_Trk1_eta2p1_Reg_v
                //    );
                //}
            }
            
            std::vector <std::vector <double> *> vv_tau1_selection = {
                input->v_tau_isTriggerMatched_reco,
                input->v_tau_byDecayModeFinding_reco,
                &v_tau_IPcut,
                input->v_tau_againstElectronLooseMVA6_reco,
                input->v_tau_againstMuonLoose3_reco,
                v_tau1_isolation,
                &v_tau1_antiIsolationCut,
                &v_tau_pTetaCut
            };
            
            std::vector <std::vector <double> *> vv_tau2_selection = {
                input->v_tau_isTriggerMatched_reco,
                input->v_tau_byDecayModeFinding_reco,
                &v_tau_IPcut,
                input->v_tau_againstElectronLooseMVA6_reco,
                input->v_tau_againstMuonLoose3_reco,
                v_tau2_isolation,
                &v_tau2_antiIsolationCut,
                &v_tau_pTetaCut
            };
            
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
            
            //printf("[%s] Event %d: Found tau-pair. \n", output_reco->nameAddon, iEvent+1);
            
            //printf("[%s] Event %d: Tau-pair (%d, %d; %d) found; %d %d (%d), %d %d (%d) \n", 
            //    output_reco->nameAddon, iEvent+1,
            //    tauPair_pos.at(0), tauPair_pos.at(1), input->tau_n_reco,
            //    (int) v_tau1_isolation->at(tauPair_pos.at(0)), (int) v_tau1_antiIsolation->at(tauPair_pos.at(0)), (int) v_tau1_antiIsolationCut.at(tauPair_pos.at(0)),
            //    (int) v_tau2_isolation->at(tauPair_pos.at(1)), (int) v_tau2_antiIsolation->at(tauPair_pos.at(1)), (int) v_tau2_antiIsolationCut.at(tauPair_pos.at(1))
            //);
            
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
            
            
            // Prompt-Fake event weight
            double tauTau_tau1_DM = input->v_tau_decayMode_reco->at(tauTau_pos1);
            double tauTau_tau2_DM = input->v_tau_decayMode_reco->at(tauTau_pos2);
            
            double p1 = tauPandFobject->getPromptRate(tauTau_tau1_4mom_reco.perp(), tauTau_tau1_DM).first;
            double f1 = tauPandFobject->getFakeRate(
                tauTau_tau1_4mom_reco.perp(),
                tauTau_tau1_DM,
                syst_name,
                syst_type
            ).first;
            
            double p2 = tauPandFobject->getPromptRate(tauTau_tau2_4mom_reco.perp(), tauTau_tau2_DM).first;
            double f2 = tauPandFobject->getFakeRate(
                tauTau_tau2_4mom_reco.perp(),
                tauTau_tau2_DM,
                syst_name,
                syst_type
            ).first;
            
            double promptFakeWeight = Common::evaluateExpression(
                promptFakeWeightExpression,
                {
                    std::make_pair("p1", p1),
                    std::make_pair("f1", f1),
                    std::make_pair("p2", p2),
                    std::make_pair("f2", f2),
                }
            );
            
            eventWeight_common *= promptFakeWeight;
            
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
            double bTaggingEventWeight = 1;
            
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
            
            //eventWeight_common *= bTaggingEventWeight;
            
            
            // JEC
            //printf("Starting JEC. \n");
            //fflush(stdout);
            
            Common::scaleObject4mom(
                &(input->v_jet_reco),
                input->m_JECcorr.at(chooseSystType(syst_name, "JEC", syst_type))
            );
            
            //printf("Finished JEC. \n");
            //fflush(stdout);
            
            
            // RECO jet
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
                
                if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    b_n_medium++;
                }
            }
            
            double tauTau_jet_HT_reco = tauTau_tau1_4mom_reco.perp() + tauTau_tau2_4mom_reco.perp() + jet_HT_reco;
            
            
            double tauTau_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2(
                tauTau_tau1_4mom_reco.m(), tauTau_tau1_4mom_reco.px(), tauTau_tau1_4mom_reco.py(),
                tauTau_tau2_4mom_reco.m(), tauTau_tau2_4mom_reco.px(), tauTau_tau2_4mom_reco.py(),
                MET_E_reco*cos(input->MET_phi_reco), MET_E_reco*sin(input->MET_phi_reco),
                0, 0
            );
            
            double tauTau_m_reco = (tauTau_tau1_4mom_reco + tauTau_tau2_4mom_reco).m();
            
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
            
            //// Baseline selections
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
            //    "b_n_reco >= 1",
            //    b_n_medium >= 1
            //);
            
            if(!isEventSelected)
            {
                continue;
            }
            
            output_reco->h1_tauTau_promptFakeEventWeight->Fill(promptFakeWeight);
            
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
            
            output_reco->h1_tauTau_MET_mT2_lsp0->Fill(tauTau_MET_mT2_lsp0, eventWeight_common);
            
            output_reco->h1_tauTau_m->Fill((tauTau_tau1_4mom_reco+tauTau_tau2_4mom_reco).m(), eventWeight_common);
            output_reco->h1_tauTau_pT->Fill((tauTau_tau1_4mom_reco+tauTau_tau2_4mom_reco).perp(), eventWeight_common);
            
            output_reco->h1_MET_E->Fill(MET_E_reco, eventWeight_common);
            output_reco->h1_MET_phi->Fill(input->MET_phi_reco, eventWeight_common);
            
            
            // RECO jet
            
            jet_n_reco = 0;
            int jet_tauOverlap_n = 0;
            
            b_n_medium = 0;
            
            double jet_pxSum_reco = 0;
            double jet_pySum_reco = 0;
            
            jet_HT_reco = 0;
            double jet_MHT_reco = 0;
            
            CLHEP::HepLorentzVector jet1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector jet2_4mom_reco(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector b1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector b2_4mom_reco(0, 0, 0, 0);
            
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
                
                if(jet_4mom_reco.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::jet_etaCut_reco)
                {
                    continue;
                }
                
                bool hasTauOverlap = !Common::isSeparated(jet_4mom_reco, &input->v_tau_reco, 0.3, tauPair_pos);
                
                if(hasTauOverlap)
                {
                    jet_tauOverlap_n++;
                    
                    continue;
                }
                
                jet_n_reco++;
                
                jet_pxSum_reco += input->v_jet_px_reco->at(iJet);
                jet_pySum_reco += input->v_jet_py_reco->at(iJet);
                
                jet_HT_reco += jet_4mom_reco.perp();
                
                
                if(jet_4mom_reco.perp() > jet1_4mom_reco.perp())
                {
                    jet1_4mom_reco = jet_4mom_reco;
                }
                
                else if(jet_4mom_reco.perp() > jet2_4mom_reco.perp())
                {
                    jet2_4mom_reco = jet_4mom_reco;
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
                
                if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    output_reco->h1_b_pT_medium->Fill(jet_4mom_reco.perp(), eventWeight_common);
                    output_reco->h1_b_eta_medium->Fill(jet_4mom_reco.eta(), eventWeight_common);
                    
                    b_n_medium++;
                    
                    if(jet_4mom_reco.perp() > b1_4mom_reco.perp())
                    {
                        b1_4mom_reco = jet_4mom_reco;
                    }
                    
                    else if(jet_4mom_reco.perp() > b2_4mom_reco.perp())
                    {
                        b2_4mom_reco = jet_4mom_reco;
                    }
                }
            }
            
            output_reco->h1_jet_n->Fill(jet_n_reco, eventWeight_common);
            output_reco->h1_jet_tauOverlap_n->Fill(jet_tauOverlap_n, eventWeight_common);
            
            if(jet_n_reco)
            {
                jet_MHT_reco = sqrt(jet_pxSum_reco*jet_pxSum_reco + jet_pySum_reco*jet_pySum_reco);
                
                output_reco->h1_jet_HT->Fill(jet_HT_reco, eventWeight_common);
                output_reco->h1_jet_MHT->Fill(jet_MHT_reco, eventWeight_common);
                output_reco->h1_jet_Meff->Fill(jet_HT_reco + jet_MHT_reco, eventWeight_common);
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
            
            // RECO b jet hist
            output_reco->h1_b_n_medium->Fill(b_n_medium, eventWeight_common*bTaggingEventWeight);
            
            if(b_n_medium >= 1)
            {
                output_reco->v_h1_b_pT[0]->Fill(b1_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight);
                output_reco->v_h1_b_eta[0]->Fill(b1_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight);
                output_reco->v_h1_b_phi[0]->Fill(b1_4mom_reco.phi(), eventWeight_common*bTaggingEventWeight);
            }
            
            if(b_n_medium >= 2)
            {
                output_reco->v_h1_b_pT[1]->Fill(b2_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight);
                output_reco->v_h1_b_eta[1]->Fill(b2_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight);
                output_reco->v_h1_b_phi[1]->Fill(b2_4mom_reco.phi(), eventWeight_common*bTaggingEventWeight);
            }
            
            double tauTau_jet_pxSum_reco = 0;
            double tauTau_jet_pySum_reco = 0;
            double tauTau_jet_MHT_reco = 0;
            
            tauTau_jet_pxSum_reco = tauTau_tau1_4mom_reco.px() + tauTau_tau2_4mom_reco.px() + jet_pxSum_reco;
            tauTau_jet_pySum_reco = tauTau_tau1_4mom_reco.py() + tauTau_tau2_4mom_reco.py() + jet_pySum_reco;
            tauTau_jet_MHT_reco = sqrt(tauTau_jet_pxSum_reco*tauTau_jet_pxSum_reco + tauTau_jet_pySum_reco*tauTau_jet_pySum_reco);
            
            output_reco->h1_tauTau_jet_HT->Fill(tauTau_jet_HT_reco, eventWeight_common);
            output_reco->h1_tauTau_jet_MHT->Fill(tauTau_jet_MHT_reco, eventWeight_common);
            
            
            // cutFlows
            std::vector <double> v_eventWeight;
            std::vector <double> v_selectionVar;
            
            
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
            
            
            // DYCR
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("DYCR1")->GetNbinsX()-1, eventWeight_common);
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
                "DYCR",
                Common::vv_cut_DYCR,
                v_selectionVar,
                v_eventWeight,
                1
            );
        }
    }
}


# endif

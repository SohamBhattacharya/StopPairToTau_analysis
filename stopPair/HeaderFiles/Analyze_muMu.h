# ifndef Analyze_muMu_H
# define Analyze_muMu_H

# include <map>
//# include <typeinfo>

# include "BTagCalibrationStandalone.h"
# include "ElMuScaleFactor.h"
# include "lester_mt2_bisect_mod.h"

# include "CustomInfo_data.h"
# include "CustomInfo_mc.h"
# include "Output_GEN.h"
# include "Output_RECO.h"


namespace Analyze_muMu
{
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        const char *era,
        bool isMC,
        std::map <std::string, bool> m_correction
    );
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        const char *era,
        bool isMC,
        std::vector <double> v_eventWeight_nJetBin,
        std::map <std::string, bool> m_correction
    );
    
    
    template <typename T1> void analyze_reco(T1 *input,
        Output_RECO::Output *output_reco,
        const char *muMu_signOption,
        std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        bool isMC,
        const char *era,
        std::vector <double> v_eventWeight_nJetBin,
        BTagCalibration *bTagCalib,
        std::string fileName_bTaggingEfficiency,
        ElMuScaleFactor::ScaleFactor *muIdIsoSFobject,
        std::map <std::string, ElMuScaleFactor::ScaleFactor*> *m_muTriggerSFobject,
        std::map <std::string, bool> m_correction,
        RooWorkspace *htt_scaleFactorWS
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        output_reco->addbHist(2);
        
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
            
            input->T_gen->GetEntry(iEvent);
            input->T_reco->GetEntry(iEvent);
            
            double eventWeight_common = 1;
            
            output_reco->h1_nEvent->Fill(0.0, eventWeight_common);
            
            double ZpTreweightFactor = 1;
            CLHEP::HepLorentzVector Z_gen_4mom;
            
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
                        Common::SYST_CENTRAL
                    ).first;
                    
                    eventWeight_common *= ZpTreweightFactor;
                    
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
                }
            }
            
            //output_reco->getCutFlow("cutFlow_ttbar_muMu_CR")->at(0) += eventWeight_common;
            //output_reco->getCutFlow("cutFlow_ttbar_muMu_CR")->Fill(0.0, eventWeight_common);
            
            for(int iCRA = 0; iCRA < 6; iCRA++)
            {
                output_reco->getCutFlow(("CRA"+std::to_string(iCRA+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            for(int iCRB = 0; iCRB < 18; iCRB++)
            {
               output_reco->getCutFlow(("CRB"+std::to_string(iCRB+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
            for(int iDYCR = 0; iDYCR < 18; iDYCR++)
            {
               output_reco->getCutFlow(("DYCR"+std::to_string(iDYCR+1)).c_str())->Fill(0.0, eventWeight_common);
            }
            
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
            
            std::vector <int> muMu_pos = Common::getObjPair( 
                &(input->v_mu_reco),
                &(input->v_mu_reco),
                true,
                vv_muSelection,
                vv_muSelection,
                Common::muMu_deltaRcut_reco,
                muMu_signOption);
            
            // At least one mu-mu pair
            if(!muMu_pos.size())
            {
                continue;
            }
            
            CLHEP::HepLorentzVector muMu_mu1_4mom_reco;
            muMu_mu1_4mom_reco.setT(fabs(input->v_mu_E_reco->at(muMu_pos.at(0))));
            muMu_mu1_4mom_reco.setX(input->v_mu_px_reco->at(muMu_pos.at(0)));
            muMu_mu1_4mom_reco.setY(input->v_mu_py_reco->at(muMu_pos.at(0)));
            muMu_mu1_4mom_reco.setZ(input->v_mu_pz_reco->at(muMu_pos.at(0)));
            
            CLHEP::HepLorentzVector muMu_mu2_4mom_reco;
            muMu_mu2_4mom_reco.setT(fabs(input->v_mu_E_reco->at(muMu_pos.at(1))));
            muMu_mu2_4mom_reco.setX(input->v_mu_px_reco->at(muMu_pos.at(1)));
            muMu_mu2_4mom_reco.setY(input->v_mu_py_reco->at(muMu_pos.at(1)));
            muMu_mu2_4mom_reco.setZ(input->v_mu_pz_reco->at(muMu_pos.at(1)));
            
            std::vector <std::pair <std::vector <CLHEP::HepLorentzVector>, double> > vp_obj4mom_deltaR_min = {
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {muMu_mu1_4mom_reco}, 
                    0.3
                ),
                std::make_pair(
                    (std::vector <CLHEP::HepLorentzVector>) {muMu_mu2_4mom_reco}, 
                    0.4
                )
            };
            
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
                
                
                // Mu1 Id-iso SF
                double mu1IdIsoSF = muIdIsoSFobject->get_ScaleFactor(muMu_mu1_4mom_reco.perp(), muMu_mu1_4mom_reco.eta());
                eventWeight_common *= mu1IdIsoSF;
                
                // Mu2 Id-iso SF
                double mu2IdIsoSF = muIdIsoSFobject->get_ScaleFactor(muMu_mu2_4mom_reco.perp(), muMu_mu2_4mom_reco.eta());
                eventWeight_common *= mu2IdIsoSF;
                
                output_reco->h1_mu_IdIsoSF->Fill(mu1IdIsoSF*mu2IdIsoSF);
                
                
                // Mu trigger SF
                double muTrigSF = 1.0;
                
                if(!strcmp(era, "2016"))
                {
                    muTrigSF = m_muTriggerSFobject->at("IsoMu24_OR_TkIsoMu24")->get_ScaleFactor(muMu_mu1_4mom_reco.perp(), muMu_mu1_4mom_reco.eta());
                }
                
                if(!strcmp(era, "2017"))
                {
                    muTrigSF = m_muTriggerSFobject->at("IsoMu24_OR_IsoMu27")->get_ScaleFactor(muMu_mu1_4mom_reco.perp(), muMu_mu1_4mom_reco.eta());
                }
                
                eventWeight_common *= muTrigSF;
                
                output_reco->h1_muTriggerSF->Fill(muTrigSF);
                
                
                // Get b-tagging SF event weight
                // APPLY TO 2017 LATER ///////////////////////////////////////////////////////////////////////////////////////////////
                //if(!strcmp(era, "2016"))
                {
                    BTagCalibrationReader bTagCalibReader_CSVv2M( \
                        BTagEntry::OP_MEDIUM,
                        "central",
                        {"up", "down"}
                    );
                    
                    bTagCalibReader_CSVv2M.load(*bTagCalib,
                        BTagEntry::FLAV_B,
                        "comb");
                    
                    bTagCalibReader_CSVv2M.load(*bTagCalib,
                        BTagEntry::FLAV_C,
                        "comb");
                    
                    bTagCalibReader_CSVv2M.load(*bTagCalib,
                        BTagEntry::FLAV_UDSG,
                        "incl");
                
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
            
            
            // RECO jet
            int jet_n_reco = 0;
            
            int b_n_loose = 0;
            int b_n_medium = 0;
            int b_n_tight = 0;
            
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
                bool hasMu1Overlap = jet_4mom_reco.deltaR(muMu_mu1_4mom_reco) < 0.4;
                bool hasMu2Overlap = jet_4mom_reco.deltaR(muMu_mu2_4mom_reco) < 0.4;
                
                if(hasMu1Overlap || hasMu2Overlap)
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
                    b_n_loose++;
                }
                
                if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
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
                
                if(input->v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    b_n_tight++;
                }
            }
            
            double muMu_jet_HT_reco = muMu_mu1_4mom_reco.perp() + muMu_mu2_4mom_reco.perp() + jet_HT_reco;
            
            
            //// Use the SRB selections for now
            //bool isEventSelected = true;
            //
            //isEventSelected = isEventSelected && Common::isEventSelected(
            //    m_eventSelection,
            //    "MET_E_reco >= 80",
            //    MET_E_reco >= 80
            //);
            //
            //isEventSelected = isEventSelected && Common::isEventSelected(
            //    m_eventSelection,
            //    "muMu_jet_HT_reco >= 100",
            //    muMu_jet_HT_reco >= 100
            //);
            //
            //isEventSelected = isEventSelected && Common::isEventSelected(
            //    m_eventSelection,
            //    "b_n_reco >= 1",
            //    b_n_medium >= 1
            //);
            //
            //
            //if(!isEventSelected)
            //{
            //    continue;
            //}
            
            
            double muMu_pZeta = Common::getPzeta(
                {{muMu_mu1_4mom_reco.px(), muMu_mu1_4mom_reco.py()},
                {muMu_mu2_4mom_reco.px(), muMu_mu2_4mom_reco.py()}},
                
                {muMu_mu1_4mom_reco.px(), muMu_mu1_4mom_reco.py()},
                {muMu_mu2_4mom_reco.px(), muMu_mu2_4mom_reco.py()}
            );
            
            double muMu_MET_pZeta = Common::getPzeta(
                {{muMu_mu1_4mom_reco.px(), muMu_mu1_4mom_reco.py()},
                {muMu_mu2_4mom_reco.px(), muMu_mu2_4mom_reco.py()},
                {MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco)}},
                
                {muMu_mu1_4mom_reco.px(), muMu_mu1_4mom_reco.py()},
                {muMu_mu2_4mom_reco.px(), muMu_mu2_4mom_reco.py()}
            );
            
            double muMu_MET_Dzeta = muMu_MET_pZeta - 1.85*muMu_pZeta;
            
            double muMu_m = (muMu_mu1_4mom_reco + muMu_mu2_4mom_reco).m();
            
            asymm_mt2_lester_bisect::disableCopyrightMessage();
            
            double muMu_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2( \
                muMu_mu1_4mom_reco.m(), muMu_mu1_4mom_reco.px(), muMu_mu1_4mom_reco.py(),
                muMu_mu2_4mom_reco.m(), muMu_mu2_4mom_reco.px(), muMu_mu2_4mom_reco.py(),
                MET_E_reco*cos(MET_phi_reco), MET_E_reco*sin(MET_phi_reco),
                0, 0);
            
            
            // Event selection
            bool isEventSelected = Common::evaluateExpression(
                eventSelectionStr,
                {
                    std::make_pair("muMu_m", muMu_m),
                    std::make_pair("MET_E_reco", MET_E_reco),
                    std::make_pair("muMu_jet_HT_reco", muMu_jet_HT_reco),
                    std::make_pair("b_n_reco", b_n_medium),
                }//,
                //true
            );
            
            if(!isEventSelected)
            {
                continue;
            }
            
            if(m_correction.at(Common::ZptReweighting_str) && input->Z_n_gen > 0)
            {
                output_reco->h1_ZpTreweightFactor_afterBaseline->Fill(ZpTreweightFactor);
                output_reco->h2_ZpTreweightFactor_vs_m_afterBaseline->Fill(Z_gen_4mom.m(), ZpTreweightFactor);
                output_reco->h2_ZpTreweightFactor_vs_pT_afterBaseline->Fill(Z_gen_4mom.perp(), ZpTreweightFactor);
                
                output_reco->h2_ZpTreweightFactor_vs_muMu_m->Fill((muMu_mu1_4mom_reco+muMu_mu2_4mom_reco).m(), ZpTreweightFactor, eventWeight_common);
                output_reco->h2_ZpTreweightFactor_vs_muMu_pT->Fill((muMu_mu1_4mom_reco+muMu_mu2_4mom_reco).perp(), ZpTreweightFactor, eventWeight_common);
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
            
            output_reco->h1_bTaggingEventWeight_medium->Fill(bTaggingEventWeight_medium);
            
            //// RECO jet
            //b_n_loose = 0;
            //b_n_medium = 0;
            //b_n_tight = 0;
            //
            //for(int iJet = 0; iJet < input->jet_n_reco; iJet++)
            //{
            //    CLHEP::HepLorentzVector jet_4mom_reco;
            //    jet_4mom_reco.setT(fabs(input->v_jet_E_reco->at(iJet)));
            //    jet_4mom_reco.setX(input->v_jet_px_reco->at(iJet));
            //    jet_4mom_reco.setY(input->v_jet_py_reco->at(iJet));
            //    jet_4mom_reco.setZ(input->v_jet_pz_reco->at(iJet));
            //    
            //    if(jet_4mom_reco.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::jet_etaCut_reco)
            //    {
            //        continue;
            //    }
            //    
            //    // Remember to use dR of isolation variable
            //    bool hasMu1Overlap = jet_4mom_reco.deltaR(muMu_mu1_4mom_reco) < 0.4;
            //    bool hasMu2Overlap = jet_4mom_reco.deltaR(muMu_mu2_4mom_reco) < 0.4;
            //    
            //    if(hasMu1Overlap || hasMu2Overlap)
            //    {
            //        //printf("Event %d: excluding jet %d. \n", iEvent, iJet);
            //        continue;
            //    }
            //    
            //    // RECO b
            //    if(jet_4mom_reco.perp() < Common::b_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::b_etaCut_reco)
            //    {
            //        continue;
            //    }
            //    
            //    if(input->v_jet_byLoosePfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
            //    {
            //        output_reco->h1_b_pT_loose->Fill(jet_4mom_reco.perp(), eventWeight_common);
            //        output_reco->h1_b_eta_loose->Fill(jet_4mom_reco.eta(), eventWeight_common);
            //    }
            //    
            //    if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
            //    {
            //        output_reco->h1_b_pT_medium->Fill(jet_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight_medium);
            //        output_reco->h1_b_eta_medium->Fill(jet_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight_medium);
            //        
            //        b_n_medium++;
            //        
            //        if(b_n_medium && b_n_medium <= 2)
            //        {
            //            output_reco->v_h1_b_pT[b_n_medium-1]->Fill(jet_4mom_reco.perp(), eventWeight_common*bTaggingEventWeight_medium);
            //            output_reco->v_h1_b_eta[b_n_medium-1]->Fill(jet_4mom_reco.eta(), eventWeight_common*bTaggingEventWeight_medium);
            //            output_reco->v_h1_b_phi[b_n_medium-1]->Fill(jet_4mom_reco.phi(), eventWeight_common*bTaggingEventWeight_medium);
            //        }
            //    }
            //    
            //    if(input->v_jet_byTightPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
            //    {
            //        output_reco->h1_b_pT_tight->Fill(jet_4mom_reco.perp(), eventWeight_common);
            //        output_reco->h1_b_eta_tight->Fill(jet_4mom_reco.eta(), eventWeight_common);
            //        
            //        b_n_tight++;
            //    }
            //}
            
            // RECO b jet number
            output_reco->h1_b_n_loose->Fill(b_n_loose, eventWeight_common);
            output_reco->h1_b_n_medium->Fill(b_n_medium, eventWeight_common*bTaggingEventWeight_medium);
            output_reco->h1_b_n_tight->Fill(b_n_tight, eventWeight_common);
            
            // mu-mu variables
            output_reco->h1_muMu_mu1_pT->Fill(muMu_mu1_4mom_reco.perp(), eventWeight_common);
            output_reco->h1_muMu_mu1_eta->Fill(muMu_mu1_4mom_reco.eta(), eventWeight_common);
            
            output_reco->h1_muMu_mu2_pT->Fill(muMu_mu2_4mom_reco.perp(), eventWeight_common);
            output_reco->h1_muMu_mu2_eta->Fill(muMu_mu2_4mom_reco.eta(), eventWeight_common);
            
            output_reco->h1_muMu_deltaPhi->Fill(Common::getDeltaPhi(muMu_mu1_4mom_reco.phi(), muMu_mu2_4mom_reco.phi()));
            
            output_reco->h1_muMu_m->Fill(muMu_m, eventWeight_common);
            output_reco->h1_muMu_MET_Dzeta->Fill(muMu_MET_Dzeta, eventWeight_common);
            output_reco->h1_muMu_MET_mT2_lsp0->Fill(muMu_MET_mT2_lsp0, eventWeight_common);
            
            output_reco->h1_jet_n->Fill(jet_n_reco, eventWeight_common);
            
            output_reco->h1_jet_HT->Fill(jet_HT_reco, eventWeight_common);
            output_reco->h1_muMu_jet_HT->Fill(muMu_jet_HT_reco, eventWeight_common);
            
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
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA2", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA3", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA4", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA5", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRA6", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            
            //output_reco->incrementCutFlow(
            //    "cutFlow_ttbar_muMu_CR", 1,
            //    {(bool) muMu_pos.size(),
            //        muMu_m < 60 || muMu_m > 120,
            //        MET_E_reco >= 50,
            //        muMu_MET_mT2_lsp0 >= 40,
            //        b_n_medium >= 1},
            //    v_eventWeight
            //);
            
            
            // CRB
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("CRB1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight_medium;
            
            output_reco->incrementCutFlow(
                "CRB1", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB2", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB3", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB4", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB5", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB6", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB7", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB8", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB9", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB10", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB11", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB12", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB13", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB14", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB15", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 50 && MET_E_reco < 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "CRB16", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB17", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "CRB18", 1,
                {(bool) muMu_pos.size(),
                    muMu_m < 60 || muMu_m > 120,
                    MET_E_reco >= 200,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium >= 1},
                v_eventWeight
            );
            
            
            // DYCR
            v_eventWeight.resize(0);
            v_eventWeight.resize(output_reco->getCutFlow("DYCR1")->GetNbinsX()-1, eventWeight_common);
            v_eventWeight.at(v_eventWeight.size()-1) *= bTaggingEventWeight_medium;
            
            output_reco->incrementCutFlow(
                "DYCR1", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR2", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR3", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "DYCR4", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR5", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR6", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 0 && muMu_MET_mT2_lsp0 < 40,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "DYCR7", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR8", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR9", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "DYCR10", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR11", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR12", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 40 && muMu_MET_mT2_lsp0 < 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "DYCR13", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR14", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR15", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 30 && MET_E_reco < 100,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            //
            output_reco->incrementCutFlow(
                "DYCR16", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 100 && muMu_jet_HT_reco < 300,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR17", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 300 && muMu_jet_HT_reco < 700,
                    b_n_medium == 0},
                v_eventWeight
            );
            
            output_reco->incrementCutFlow(
                "DYCR18", 1,
                {(bool) muMu_pos.size(),
                    muMu_m > 80 and muMu_m < 100,
                    MET_E_reco >= 100,
                    muMu_MET_mT2_lsp0 >= 80,
                    muMu_jet_HT_reco >= 700,
                    b_n_medium == 0},
                v_eventWeight
            );
        }
    }
}


# endif

# include "lester_mt2_bisect_mod.h"

# include "TMVA_treeMaker_tauTau.h"


namespace TMVA_treeMaker_tauTau
{
    void initialize(const char *process, const char *dir,
        bool isSUSY
    )
    {
        TMVA_treeMaker_tauTau::initialize(
            process, dir,
            isSUSY,
            std::make_pair(-1, -1),
            ""
        );
    }
    
    
    void initialize(const char *process, const char *dir,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::string sourceFile
    )
    {
        asymm_mt2_lester_bisect::disableCopyrightMessage();
        
        char sourceFileName[Common::str_len];
        
        if(sourceFile.length())
        {
            sprintf(sourceFileName, "%s", sourceFile.c_str());
        }
        
        else
        {
            sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process, process);
        }
        
        printf("Source file: %s \n", sourceFileName);
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName);
        
        std::string inFile;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        sprintf(outDir, "output_TMVAtree/%s", dir);
        
        sprintf(command, "mkdir -p %s", outDir);
        system(command);
        
        
        char treePath_gen[Common::str_len];
        char treePath_reco[Common::str_len];
        
        sprintf(treePath_gen, "miniaodsim2custom/gen");
        sprintf(treePath_reco, "miniaodsim2custom/reco");
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {
            //n++; if(n > 200) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFile.substr(inFile.rfind("/")+1, inFile.rfind(".root")-inFile.rfind("/")-1)).c_str());
            
            char outFile[Common::str_len];
            sprintf(outFile, "%s/%s_TMVAtree.root", outDir, fileNameStripped);
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("Output: %s \n", outFile);
            printf("\n");
            
            std::vector <const char*> v_object_mc_gen = {
                "genParam"};
            
            std::vector <const char*> v_object_reco = {
                "el", "mu", "tau", "jet", "MET"};
            
            CustomInfo_mc::Info *input = new CustomInfo_mc::Info(
                inFile.c_str(),
                treePath_gen, v_object_mc_gen,
                treePath_reco, v_object_reco,
                "read",
                0, 0,
                0, 0);
            
            TMVA_treeContent_tauTau::Info *output = new TMVA_treeContent_tauTau::Info(
                outFile, "tree"
            );
            
            
            TMVA_treeMaker_tauTau::makeTree(input,
                output,
                "tight",
                "OS",
                isSUSY,
                massPoint_stop1_neutralino1
            );
            
            output->writeData();
            
            output->freeMemory();
            delete output;
            
            input->freeMemory();
            delete input;
            
            printf("\n");
        }
    }
    
    
    void makeTree(CustomInfo_mc::Info *input,
        TMVA_treeContent_tauTau::Info *output,
        const char *tau_isoOption,
        const char *tauPair_signOption,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        for(int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if((iEvent+2) % 1000 == 0)
            {
                printf("Processed event no. %d / %d \n", iEvent+2, nEvent);
                fflush(stdout);
            }
            
            input->T_gen->GetEntry(iEvent);
            input->T_reco->GetEntry(iEvent);
            
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
            
            
            std::vector <int> tauPair_pos;
            std::vector <int> v_nTau;
            
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
            
            if(!strcmp(tau_isoOption, "loose"))
            {
                //v_tau_iso_reco = input->v_tau_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03_reco;
                v_tau_iso_reco = input->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
            }
            
            else if(!strcmp(tau_isoOption, "medium"))
            {
                //v_tau_iso_reco = input->v_tau_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03_reco;
                v_tau_iso_reco = input->v_tau_byMediumIsolationMVArun2v1DBdR03oldDMwLT_reco;
            }
            
            else if(!strcmp(tau_isoOption, "tight"))
            {
                //v_tau_iso_reco = input->v_tau_byTightCombinedIsolationDeltaBetaCorr3HitsdR03_reco;
                v_tau_iso_reco = input->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
            }
            
            else
            {
                printf("Wrong tau isolation option");
                exit(EXIT_FAILURE);
            }
            
            
            // Get tau pair
            std::vector <std::vector <int> > tauPair_info = Common::getTauPair( \
                &(input->v_tau_reco), \
                {}, \
                {input->v_tau_byDecayModeFinding_reco, \
                    &v_tau_IPcut, \
                    input->v_tau_againstElectronLooseMVA6_reco, \
                    input->v_tau_againstMuonLoose3_reco, \
                    v_tau_iso_reco, \
                    &v_tau_pTetaCut}, \
                Common::tauTau_deltaRcut_reco, \
                tauPair_signOption);
            
            
            tauPair_pos = tauPair_info[0];
            v_nTau = tauPair_info[1];
            
            // At least one tau-pair
            if(!tauPair_pos.size())
            {
                continue;
            }
            
            // MET cut
            if(input->MET_E_reco <= 50)
            {
                continue;
            }
            
            
            CLHEP::HepLorentzVector tau1_4mom_reco, tau2_4mom_reco;
            
            tau1_4mom_reco.setT(fabs(input->v_tau_E_reco->at(tauPair_pos[0])));
            tau1_4mom_reco.setX(input->v_tau_px_reco->at(tauPair_pos[0]));
            tau1_4mom_reco.setY(input->v_tau_py_reco->at(tauPair_pos[0]));
            tau1_4mom_reco.setZ(input->v_tau_pz_reco->at(tauPair_pos[0]));
            
            tau2_4mom_reco.setT(fabs(input->v_tau_E_reco->at(tauPair_pos[1])));
            tau2_4mom_reco.setX(input->v_tau_px_reco->at(tauPair_pos[1]));
            tau2_4mom_reco.setY(input->v_tau_py_reco->at(tauPair_pos[1]));
            tau2_4mom_reco.setZ(input->v_tau_pz_reco->at(tauPair_pos[1]));
            
            double tauTau_m_reco = (tau1_4mom_reco+tau2_4mom_reco).m();
            
            double jet_pxSum_reco = 0;
            double jet_pySum_reco = 0;
            
            double jet_HT_reco = 0;
            double jet_MHT_reco = 0;
            
            double tauTau_jet_pxSum_reco = tau1_4mom_reco.px() + tau2_4mom_reco.px();
            double tauTau_jet_pySum_reco = tau1_4mom_reco.py() + tau2_4mom_reco.py();
            
            double tauTau_jet_HT_reco = tau1_4mom_reco.perp() + tau2_4mom_reco.perp();
            double tauTau_jet_MHT_reco = 0;
            
            int jet_n_reco = 0;
            int b_n_medium = 0;
            int nonBjet_n = 0;
            
            CLHEP::HepLorentzVector b1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector b2_4mom_reco(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector nonBjet1_4mom_reco(0, 0, 0, 0);
            
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
                jet_pxSum_reco += jet_4mom_reco.px();
                jet_pySum_reco += jet_4mom_reco.py();
                
                tauTau_jet_HT_reco += jet_4mom_reco.perp();
                tauTau_jet_pxSum_reco += jet_4mom_reco.px();
                tauTau_jet_pySum_reco += jet_4mom_reco.py();
                
                if(input->v_jet_byMediumPfCombinedInclusiveSecondaryVertexV2BJetTags_reco->at(iJet))
                {
                    b_n_medium++;
                    
                    //b1_4mom_reco.setT(fabs(input->v_jet_E_reco->at(iJet)));
                    //b1_4mom_reco.setX(input->v_jet_px_reco->at(iJet));
                    //b1_4mom_reco.setY(input->v_jet_py_reco->at(iJet));
                    //b1_4mom_reco.setZ(input->v_jet_pz_reco->at(iJet));
                    
                    if(jet_4mom_reco.perp() > b1_4mom_reco.perp())
                    {
                        b1_4mom_reco = jet_4mom_reco;
                    }
                    
                    else if(jet_4mom_reco.perp() > b2_4mom_reco.perp())
                    {
                        b2_4mom_reco = jet_4mom_reco;
                    }
                }
                
                else
                {
                    nonBjet_n++;
                    
                    if(jet_4mom_reco.perp() > nonBjet1_4mom_reco.perp())
                    {
                        nonBjet1_4mom_reco = jet_4mom_reco;
                    }
                }
            }
            
            // At least one b
            if(b_n_medium < 1)
            {
                continue;
            }
            
            
            jet_MHT_reco = sqrt(jet_pxSum_reco*jet_pxSum_reco + jet_pySum_reco*jet_pySum_reco);
            tauTau_jet_MHT_reco = sqrt(tauTau_jet_pxSum_reco*tauTau_jet_pxSum_reco + tauTau_jet_pySum_reco*tauTau_jet_pySum_reco);
            
            
            double tauTau_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2(
                tau1_4mom_reco.m(), tau1_4mom_reco.px(), tau1_4mom_reco.py(),
                tau2_4mom_reco.m(), tau2_4mom_reco.px(), tau2_4mom_reco.py(),
                input->MET_E_reco*cos(input->MET_phi_reco), input->MET_E_reco*sin(input->MET_phi_reco),
                0, 0);
            
            
            double tauTau_pZeta = Common::getPzeta(
                {{tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                    {tau2_4mom_reco.px(), tau2_4mom_reco.py()}},
                
                {tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                {tau2_4mom_reco.px(), tau2_4mom_reco.py()});
            
            double tauTau_MET_pZeta = Common::getPzeta(
                {{tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                    {tau2_4mom_reco.px(), tau2_4mom_reco.py()},
                    {input->MET_E_reco*cos(input->MET_phi_reco), input->MET_E_reco*sin(input->MET_phi_reco)}},
                
                {tau1_4mom_reco.px(), tau1_4mom_reco.py()},
                {tau2_4mom_reco.px(), tau2_4mom_reco.py()});
            
            double tauTau_MET_Dzeta = tauTau_MET_pZeta - 1.85*tauTau_pZeta;
            
            double tau1_b1_deltaPhi = Common::getDeltaPhi(tau1_4mom_reco.phi(), b1_4mom_reco.phi());
            
            
            output->tau1_pT = tau1_4mom_reco.perp();
            output->tau1_eta = tau1_4mom_reco.eta();
            
            output->tau2_pT = tau2_4mom_reco.perp();
            output->tau2_eta = tau2_4mom_reco.eta();
            
            output->tauTau_m = tauTau_m_reco;
            
            output->MET_E = input->MET_E_reco;
            output->MET_phi = input->MET_phi_reco;
            
            output->tauTau_MET_mT2_lsp0 = tauTau_MET_mT2_lsp0;
            output->tauTau_MET_Dzeta = tauTau_MET_Dzeta;
            
            output->tauTau_jet_HT = tauTau_jet_HT_reco;
            output->tauTau_jet_MHT = tauTau_jet_MHT_reco;
            
            output->nonBjet_n = nonBjet_n;
            
            output->b_n = b_n_medium;
            
            output->b1_pT = b1_4mom_reco.perp();
            output->b1_eta = b1_4mom_reco.eta();
            
            output->tau1_b1_deltaPhi = tau1_b1_deltaPhi;
            
            
            // tauBtauB mT2
            if(tauPair_pos.size() && jet_n_reco >= 2 && b_n_medium >= 1)
            {
                CLHEP::HepLorentzVector tau_b_4mom1_comb1;
                CLHEP::HepLorentzVector tau_b_4mom2_comb1;
                
                CLHEP::HepLorentzVector tau_b_4mom1_comb2;
                CLHEP::HepLorentzVector tau_b_4mom2_comb2;
                
                CLHEP::HepLorentzVector tau_b_4mom1;
                CLHEP::HepLorentzVector tau_b_4mom2;
                
                double bb_MET_mT2_lsp0 = 0;
                
                // Create the two possible combinations:
                // [(lep1+b1), (lep2+b2)], and [(lep1+b2), (lep2+b1)]
                if(b_n_medium >= 2)
                {
                    tau_b_4mom1_comb1 = tau1_4mom_reco + b1_4mom_reco;
                    tau_b_4mom1_comb1 = tau2_4mom_reco + b2_4mom_reco;
                    
                    tau_b_4mom1_comb2 = tau1_4mom_reco + b2_4mom_reco;
                    tau_b_4mom1_comb2 = tau2_4mom_reco + b1_4mom_reco;
                    
                    bb_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2( \
                        b1_4mom_reco.m(), b1_4mom_reco.px(), b1_4mom_reco.py(), \
                        b2_4mom_reco.m(), b2_4mom_reco.px(), b2_4mom_reco.py(), \
                        input->MET_E_reco*cos(input->MET_phi_reco), input->MET_E_reco*sin(input->MET_phi_reco), \
                        0, 0);
                }
                
                // Use nonBjet1 as b2 if there is only 1 b jet
                else
                {
                    tau_b_4mom1_comb1 = tau1_4mom_reco + b1_4mom_reco;
                    tau_b_4mom1_comb1 = tau2_4mom_reco + nonBjet1_4mom_reco;
                    
                    tau_b_4mom1_comb2 = tau1_4mom_reco + nonBjet1_4mom_reco;
                    tau_b_4mom1_comb2 = tau2_4mom_reco + b1_4mom_reco;
                    
                    bb_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2( \
                        b1_4mom_reco.m(), b1_4mom_reco.px(), b1_4mom_reco.py(), \
                        nonBjet1_4mom_reco.m(), nonBjet1_4mom_reco.px(), nonBjet1_4mom_reco.py(), \
                        input->MET_E_reco*cos(input->MET_phi_reco), input->MET_E_reco*sin(input->MET_phi_reco), \
                        0, 0);
                }
                
                output->bb_MET_mT2_lsp0 = bb_MET_mT2_lsp0;
                
                // Select the combination whose max. invariant mass is lower
                double comb1_m_max = std::max(tau_b_4mom1_comb1.m(), tau_b_4mom2_comb1.m());
                double comb2_m_max = std::max(tau_b_4mom1_comb2.m(), tau_b_4mom2_comb2.m());
                
                if(comb1_m_max < comb2_m_max)
                {
                    tau_b_4mom1 = tau_b_4mom1_comb1;
                    tau_b_4mom2 = tau_b_4mom2_comb1;
                }
                
                else
                {
                    tau_b_4mom1 = tau_b_4mom1_comb2;
                    tau_b_4mom2 = tau_b_4mom2_comb2;
                }
                
                
                double tauBtauB_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2( \
                    tau_b_4mom1.m(), tau_b_4mom1.px(), tau_b_4mom1.py(), \
                    tau_b_4mom2.m(), tau_b_4mom2.px(), tau_b_4mom2.py(), \
                    input->MET_E_reco*cos(input->MET_phi_reco), input->MET_E_reco*sin(input->MET_phi_reco), \
                    0, 0);
                
                output->tauBtauB_MET_mT2_lsp0 = tauBtauB_MET_mT2_lsp0;
                
                
                double tauBtauB_MET_mT2_lsp0_comb1 = asymm_mt2_lester_bisect::get_mT2( \
                    tau_b_4mom1_comb1.m(), tau_b_4mom1_comb1.px(), tau_b_4mom1_comb1.py(), \
                    tau_b_4mom2_comb1.m(), tau_b_4mom2_comb1.px(), tau_b_4mom2_comb1.py(), \
                    input->MET_E_reco*cos(input->MET_phi_reco), input->MET_E_reco*sin(input->MET_phi_reco), \
                    0, 0);
                
                double tauBtauB_MET_mT2_lsp0_comb2 = asymm_mt2_lester_bisect::get_mT2( \
                    tau_b_4mom1_comb2.m(), tau_b_4mom1_comb2.px(), tau_b_4mom1_comb2.py(), \
                    tau_b_4mom2_comb2.m(), tau_b_4mom2_comb2.px(), tau_b_4mom2_comb2.py(), \
                    input->MET_E_reco*cos(input->MET_phi_reco), input->MET_E_reco*sin(input->MET_phi_reco), \
                    0, 0);
                
                if(tauBtauB_MET_mT2_lsp0_comb1 < tauBtauB_MET_mT2_lsp0_comb2)
                {
                    output->tauBtauB_MET_mT2_lsp0_mod1 = tauBtauB_MET_mT2_lsp0_comb1;
                }
                
                else
                {
                    output->tauBtauB_MET_mT2_lsp0_mod1 = tauBtauB_MET_mT2_lsp0_comb2;
                }
            }
            
            else
            {
                output->tauBtauB_MET_mT2_lsp0 = 0;
                output->tauBtauB_MET_mT2_lsp0_mod1 = 0;
                
                output->bb_MET_mT2_lsp0 = 0;
            }
            
            
            // Fill output tree
            output->fillTree();
        }
    }
}

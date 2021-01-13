# include "MuIdIsoEfficiency_mc.h"

namespace MuIdIsoEfficiency_mc
{
    Output::Output()
    {
        v_bin_pT = {
            0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
            120, 150, 300, 2000
        };
        
        v_bin_eta = {
            -3.0, -2.1, -1.2, -0.9,
            0.0,
            0.9, 1.2, 2.1, 3.0
        };
        
        
        char name[Common::str_len];
        char title[Common::str_len];
        
        // GEN
        sprintf(name, "mu_pT_gen");
        sprintf(title, "mu_pT_gen");
        h1_mu_pT_gen = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "mu_eta_gen");
        sprintf(title, "mu_eta_gen");
        h1_mu_eta_gen = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "mu_pT_vs_eta_gen");
        sprintf(title, "mu_pT_vs_eta_gen");
        h2_mu_pT_vs_eta_gen = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "muMu_m_gen");
        sprintf(title, "muMu_m_gen");
        h1_muMu_m_gen = new TH1F(name, title, 50, 0, 500);
        
        
        
        // RECO
        sprintf(name, "mu_genMatched_pT_reco");
        sprintf(title, "mu_genMatched_pT_reco");
        h1_mu_genMatched_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "mu_genMatched_eta_reco");
        sprintf(title, "mu_genMatched_eta_reco");
        h1_mu_genMatched_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "mu_genMatched_pT_vs_eta_reco");
        sprintf(title, "mu_genMatched_pT_vs_eta_reco");
        h2_mu_genMatched_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "mu_nearestGen_deltaR");
        sprintf(title, "mu_nearestGen_deltaR");
        h1_mu_nearestGen_deltaR = new TH1F(name, title, 500, 0, 10);
        
        sprintf(name, "muMu_m_reco");
        sprintf(title, "muMu_m_reco");
        h1_muMu_m_reco = new TH1F(name, title, 50, 0, 500);
    }
    
    
    void Output::writeData()
    {
        // GEN
        h1_mu_pT_gen->Write();
        h1_mu_eta_gen->Write();
        h2_mu_pT_vs_eta_gen->Write();
        
        h1_muMu_m_gen->Write();
        
        // RECO
        h1_mu_genMatched_pT_reco->Write();
        h1_mu_genMatched_eta_reco->Write();
        h2_mu_genMatched_pT_vs_eta_reco->Write();
        
        h1_mu_nearestGen_deltaR->Write();
        
        h1_muMu_m_reco->Write();
    }
    
    
    void Output::freeMemory()
    {
        // GEN
        delete h1_mu_pT_gen;
        delete h1_mu_eta_gen;
        delete h2_mu_pT_vs_eta_gen;
        
        delete h1_muMu_m_gen;
        
        // RECO
        delete h1_mu_genMatched_pT_reco;
        delete h1_mu_genMatched_eta_reco;
        delete h2_mu_genMatched_pT_vs_eta_reco;
        
        delete h1_mu_nearestGen_deltaR;
        
        delete h1_muMu_m_reco;
    }
    
    
    void run(
        std::string process,
        std::string dir,
        std::string sourceFileName
    )
    {
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process.c_str(), process.c_str());
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName);
        
        std::string inFileName;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        //sprintf(outDir, "output_muIdIsoEfficiency/%s", dir.c_str());
        sprintf(outDir, "%s", dir.c_str());
        
        sprintf(command, "mkdir -p %s", outDir);
        system(command);
        
        
        char treePath_gen[Common::str_len];
        char treePath_reco[Common::str_len];
        
        sprintf(treePath_gen, "miniaodsim2custom/gen");
        sprintf(treePath_reco, "miniaodsim2custom/reco");
        
        int n = 0;
        
        while(std::getline(sourceFileList, inFileName))
        {
            n++; if(n > 1) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFileName.substr(inFileName.rfind("/")+1, inFileName.rfind(".root")-inFileName.rfind("/")-1)).c_str());
            
            // Outfile
            char outFileName[Common::str_len];
            sprintf(outFileName, "%s/%s_muIdIsoEfficiency.root", outDir, fileNameStripped);
            TFile *outFile = TFile::Open(outFileName, "RECREATE");
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFileName.c_str());
            printf("Output: %s \n", outFileName);
            printf("\n");
            
            // Input
            std::vector <const char*> v_object_mc_gen = {
                "mu"
            };
            
            std::vector <const char*> v_object_reco = {
                "mu", "jet"
            };
            
            CustomInfo_mc::Info *input = new CustomInfo_mc::Info(
                inFileName.c_str(),
                treePath_gen, v_object_mc_gen,
                treePath_reco, v_object_reco,
                "read",
                0, 0,
                0, 0);
            
            std::string mu_WPoption;
            std::string mu_isoOption;
            
            char outFile_internalDir[Common::str_len];
            
            Output *output;
            
            mu_WPoption = "Medium";
            mu_isoOption = "MediumPFbasedCombinedRelativeDeltaBetaCorrdR04";
            
            output = new Output();
            
            analyze(
                input,
                output,
                20, 2.4,
                20, 2.4,
                Common::mu_dxyCut_reco, input->v_mu_dxy_reco,
                Common::mu_dzCut_reco, input->v_mu_dz_reco,
                mu_WPoption, input->v_mu_isMediumMuon_reco,
                mu_isoOption, input->v_mu_byMediumPFbasedCombinedRelativeDeltaBetaCorrdR04_reco,
                0.3
            );
            
            sprintf(outFile_internalDir, "%s_%s", mu_WPoption.c_str(), mu_isoOption.c_str());
            outFile->mkdir(outFile_internalDir);
            outFile->cd(outFile_internalDir);
            output->writeData();
            
            output->freeMemory();
            delete output;
            
            
            //
            delete outFile;
            
            input->freeMemory();
            delete input;
        }
    }
    
    
    void analyze(
        CustomInfo_mc::Info *input,
        Output *output,
        double mu_pTcut_gen, double mu_etaCut_gen,
        double mu_pTcut_reco, double mu_etaCut_reco,
        double mu_dxyCut_reco, std::vector <double> *v_mu_dxy_reco,
        double mu_dzCut_reco, std::vector <double> *v_mu_dz_reco,
        std::string mu_WPoption, std::vector <double> *v_mu_WP,
        std::string mu_isoOption, std::vector <double> *v_mu_isolation,
        double deltaRcut
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
            
            
            // Gen mu
            std::vector <bool> v_mu_isSelected_gen(input->mu_n_gen, false);
            std::vector <bool> v_mu_isUsed_gen(input->mu_n_gen, false);
            
            CLHEP::HepLorentzVector mu1_4mom_gen(0, 0, 0, 0);
            CLHEP::HepLorentzVector mu2_4mom_gen(0, 0, 0, 0);
            
            bool foundMuPair_gen = false;
            
            for(int iMu = 0; iMu < input->mu_n_gen; iMu++)
            {
                CLHEP::HepLorentzVector mu_4mom_gen;
                
                mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu)));
                mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu));
                mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu));
                mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu));
                
                if(mu_4mom_gen.perp() < mu_pTcut_gen || fabs(mu_4mom_gen.eta()) > mu_etaCut_gen)
                {
                    continue;
                }
                
                v_mu_isSelected_gen.at(iMu) = true;
                
                output->h1_mu_pT_gen->Fill(mu_4mom_gen.perp());
                output->h1_mu_eta_gen->Fill(mu_4mom_gen.eta());
                output->h2_mu_pT_vs_eta_gen->Fill(mu_4mom_gen.eta(), mu_4mom_gen.perp());
                
                
                // Store the two leading mus
                if(mu_4mom_gen.perp() > mu1_4mom_gen.perp())
                {
                    mu1_4mom_gen = mu_4mom_gen;
                    mu1_4mom_gen = mu_4mom_gen;
                }
                
                else if(mu_4mom_gen.perp() > mu2_4mom_gen.perp())
                {
                    mu2_4mom_gen = mu_4mom_gen;
                    mu2_4mom_gen = mu_4mom_gen;
                    
                    foundMuPair_gen = true;
                }
            }
            
            
            if(foundMuPair_gen)
            {
                output->h1_muMu_m_gen->Fill((mu1_4mom_gen + mu2_4mom_gen).m());
            }
            
            
            // Reco mus
            CLHEP::HepLorentzVector mu1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector mu2_4mom_reco(0, 0, 0, 0);
            
            bool foundMuPair_reco = false;
            
            std::vector <bool> v_mu_isSelected_reco(input->mu_n_reco, false);
            std::vector <bool> v_mu_isGenMatched_reco(input->mu_n_reco, false);
            
            for(int iMu_reco = 0; iMu_reco < input->mu_n_reco; iMu_reco++)
            {
                CLHEP::HepLorentzVector mu_4mom_reco;
                
                mu_4mom_reco.setT(fabs(input->v_mu_E_reco->at(iMu_reco)));
                mu_4mom_reco.setX(input->v_mu_px_reco->at(iMu_reco));
                mu_4mom_reco.setY(input->v_mu_py_reco->at(iMu_reco));
                mu_4mom_reco.setZ(input->v_mu_pz_reco->at(iMu_reco));
                
                // Isolation
                if(!v_mu_isolation->at(iMu_reco))
                {
                    continue;
                }
                
                // IP
                if(fabs(v_mu_dxy_reco->at(iMu_reco)) >= mu_dxyCut_reco)
                {
                    continue;
                }
                
                if(fabs(v_mu_dz_reco->at(iMu_reco)) >= mu_dzCut_reco)
                {
                    continue;
                }
                
                // pT, eta
                if(mu_4mom_reco.perp() < mu_pTcut_reco || fabs(mu_4mom_reco.eta()) > mu_etaCut_reco)
                {
                    continue;
                }
                
                v_mu_isSelected_reco.at(iMu_reco) = true;
                
                int mu_genMatchedIndex = -1;
                int mu_nearestGenIndex = -1;
                double deltaR_min = 9999;
                
                CLHEP::HepLorentzVector mu_nearestGen_4mom;
                
                for(int iMu_gen = 0; iMu_gen < input->mu_n_gen; iMu_gen++)
                {
                    CLHEP::HepLorentzVector mu_4mom_gen;
                    
                    mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu_gen)));
                    mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu_gen));
                    mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu_gen));
                    mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu_gen));
                    
                    // Choose the the selected gen mus
                    if(!v_mu_isSelected_gen.at(iMu_gen))
                    {
                        continue;
                    }
                    
                    // Reject if already used for matching
                    if(v_mu_isUsed_gen.at(iMu_gen))
                    {
                        continue;
                    }
                    
                    double deltaR = mu_4mom_reco.deltaR(mu_4mom_gen);
                    
                    if(deltaR < deltaR_min)
                    {
                        deltaR_min = deltaR;
                        
                        mu_nearestGenIndex = iMu_gen;
                        
                        mu_nearestGen_4mom = mu_4mom_gen;
                    }
                }
                
                if(mu_nearestGenIndex >= 0)
                {
                    output->h1_mu_nearestGen_deltaR->Fill(deltaR_min);
                    
                    if(deltaR_min < deltaRcut)
                    {
                        v_mu_isGenMatched_reco.at(iMu_reco) = true;
                        
                        mu_genMatchedIndex = mu_nearestGenIndex;
                        
                        v_mu_isUsed_gen.at(mu_genMatchedIndex) = true;
                        
                        output->h1_mu_genMatched_pT_reco->Fill(mu_nearestGen_4mom.perp());
                        output->h1_mu_genMatched_eta_reco->Fill(mu_nearestGen_4mom.eta());
                        output->h2_mu_genMatched_pT_vs_eta_reco->Fill(mu_nearestGen_4mom.eta(), mu_nearestGen_4mom.perp());
                        
                        
                        // Store the two leading mus
                        if(mu_4mom_reco.perp() > mu1_4mom_reco.perp())
                        {
                            mu1_4mom_reco = mu_4mom_reco;
                        }
                        
                        else if(mu_4mom_reco.perp() > mu2_4mom_reco.perp())
                        {
                            mu2_4mom_reco = mu_4mom_reco;
                            
                            foundMuPair_reco = true;
                        }
                    }
                }
            }
            
            
            if(foundMuPair_reco)
            {
                output->h1_muMu_m_reco->Fill((mu1_4mom_reco + mu2_4mom_reco).m());
            }
        }
    }
}

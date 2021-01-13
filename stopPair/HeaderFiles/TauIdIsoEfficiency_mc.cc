# include "TauIdIsoEfficiency_mc.h"

namespace TauIdIsoEfficiency_mc
{
    Output::Output()
    {
        v_bin_pT = {
            0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
            120, 150, 300, 2000
        };
        
        v_bin_eta = {
            -3.0, -2.4, -2.1, -1.8, -1.5, -1.2, -0.9, -0.6, -0.3,
            0.0,
            0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4, 2.7, 3.0
        };
        
        v_template_pTbin = {
            20, 30, 50, 100
        };
        
        v_template_pxyBin = {
            0, 20, 40, 70
        };
        
        v_template_responseBin = {
            -3.0, -2.0, -1.5, -1.0, -0.5
        };
        
        for(int binLwrEdge = 0; binLwrEdge < 16; binLwrEdge++)
        {
            v_template_responseBin.push_back((float) binLwrEdge / 10.0);
        }
        
        v_template_responseBin.push_back(2.0);
        v_template_responseBin.push_back(3.0);
        
        
        char name[Common::str_len];
        char title[Common::str_len];
        
        // GEN
        sprintf(name, "tau_vis_pT_gen");
        sprintf(title, "tau_vis_pT_gen");
        h1_tau_vis_pT_gen = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_vis_eta_gen");
        sprintf(title, "tau_vis_eta_gen");
        h1_tau_vis_eta_gen = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_vis_pT_vs_eta_gen");
        sprintf(title, "tau_vis_pT_vs_eta_gen");
        h2_tau_vis_pT_vs_eta_gen = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tauTau_m_gen");
        sprintf(title, "tauTau_m_gen");
        h1_tauTau_m_gen = new TH1F(name, title, 50, 0, 500);
        
        sprintf(name, "tauhTauh_m_gen");
        sprintf(title, "tauhTauh_m_gen");
        h1_tauhTauh_m_gen = new TH1F(name, title, 50, 0, 500);
        
        
        
        // RECO
        sprintf(name, "tau_all_pT_reco");
        sprintf(title, "tau_all_pT_reco");
        h1_tau_all_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_all_eta_reco");
        sprintf(title, "tau_all_eta_reco");
        h1_tau_all_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_all_pT_vs_eta_reco");
        sprintf(title, "tau_all_pT_vs_eta_reco");
        h2_tau_all_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_all_pT_vs_DM_reco");
        sprintf(title, "tau_all_pT_vs_DM_reco");
        h2_tau_all_pT_vs_DM_reco = new TH2F(name, title, 30, 0.0, 30.0, 200, 0.0, 2000.0);
        
        //
        sprintf(name, "tau_pT_reco");
        sprintf(title, "tau_pT_reco");
        h1_tau_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_eta_reco");
        sprintf(title, "tau_eta_reco");
        h1_tau_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_pT_vs_eta_reco");
        sprintf(title, "tau_pT_vs_eta_reco");
        h2_tau_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_pT_vs_DM_reco");
        sprintf(title, "tau_pT_vs_DM_reco");
        h2_tau_pT_vs_DM_reco = new TH2F(name, title, 30, 0.0, 30.0, 200, 0.0, 2000.0);
        
        //
        sprintf(name, "tau_genMatched_pT_reco");
        sprintf(title, "tau_genMatched_pT_reco");
        h1_tau_genMatched_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_genMatched_eta_reco");
        sprintf(title, "tau_genMatched_eta_reco");
        h1_tau_genMatched_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_genMatched_pT_vs_eta_reco");
        sprintf(title, "tau_genMatched_pT_vs_eta_reco");
        h2_tau_genMatched_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        //
        sprintf(name, "tau_genNotMatched_n_reco");
        sprintf(title, "tau_genNotMatched_n_reco");
        h1_tau_genNotMatched_n_reco = new TH1F(name, title, 10, 0, 10);
        
        sprintf(name, "tau_genNotMatched_pT_reco");
        sprintf(title, "tau_genNotMatched_pT_reco");
        h1_tau_genNotMatched_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_genNotMatched_eta_reco");
        sprintf(title, "tau_genNotMatched_eta_reco");
        h1_tau_genNotMatched_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_genNotMatched_pT_vs_eta_reco");
        sprintf(title, "tau_genNotMatched_pT_vs_eta_reco");
        h2_tau_genNotMatched_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        //
        sprintf(name, "tau_genNotMatched_genElMatched_n_reco");
        sprintf(title, "tau_genNotMatched_genElMatched_n_reco");
        h1_tau_genNotMatched_genElMatched_n_reco = new TH1F(name, title, 10, 0, 10);
        
        sprintf(name, "tau_genNotMatched_genElMatched_pT_reco");
        sprintf(title, "tau_genNotMatched_genElMatched_pT_reco");
        h1_tau_genNotMatched_genElMatched_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_genNotMatched_genElMatched_eta_reco");
        sprintf(title, "tau_genNotMatched_genElMatched_eta_reco");
        h1_tau_genNotMatched_genElMatched_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_genNotMatched_genElMatched_pT_vs_eta_reco");
        sprintf(title, "tau_genNotMatched_genElMatched_pT_vs_eta_reco");
        h2_tau_genNotMatched_genElMatched_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        //
        sprintf(name, "tau_genNotMatched_genMuMatched_n_reco");
        sprintf(title, "tau_genNotMatched_genMuMatched_n_reco");
        h1_tau_genNotMatched_genMuMatched_n_reco = new TH1F(name, title, 10, 0, 10);
        
        sprintf(name, "tau_genNotMatched_genMuMatched_pT_reco");
        sprintf(title, "tau_genNotMatched_genMuMatched_pT_reco");
        h1_tau_genNotMatched_genMuMatched_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_genNotMatched_genMuMatched_eta_reco");
        sprintf(title, "tau_genNotMatched_genMuMatched_eta_reco");
        h1_tau_genNotMatched_genMuMatched_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_genNotMatched_genMuMatched_pT_vs_eta_reco");
        sprintf(title, "tau_genNotMatched_genMuMatched_pT_vs_eta_reco");
        h2_tau_genNotMatched_genMuMatched_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        //
        sprintf(name, "tau_genNotMatched_genBmatched_n_reco");
        sprintf(title, "tau_genNotMatched_genBmatched_n_reco");
        h1_tau_genNotMatched_genBmatched_n_reco = new TH1F(name, title, 10, 0, 10);
        
        sprintf(name, "tau_genNotMatched_genBmatched_pT_reco");
        sprintf(title, "tau_genNotMatched_genBmatched_pT_reco");
        h1_tau_genNotMatched_genBmatched_pT_reco = new TH1F(name, title, v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        sprintf(name, "tau_genNotMatched_genBmatched_eta_reco");
        sprintf(title, "tau_genNotMatched_genBmatched_eta_reco");
        h1_tau_genNotMatched_genBmatched_eta_reco = new TH1F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0));
        
        sprintf(name, "tau_genNotMatched_genBmatched_pT_vs_eta_reco");
        sprintf(title, "tau_genNotMatched_genBmatched_pT_vs_eta_reco");
        h2_tau_genNotMatched_genBmatched_pT_vs_eta_reco = new TH2F(name, title, v_bin_eta.size()-1, &v_bin_eta.at(0), v_bin_pT.size()-1, &v_bin_pT.at(0));
        
        
        //
        sprintf(name, "tau_nearestGen_deltaR");
        sprintf(title, "tau_nearestGen_deltaR");
        h1_tau_nearestGen_deltaR = new TH1F(name, title, 500, 0, 10);
        
        sprintf(name, "tauTau_m_reco");
        sprintf(title, "tauTau_m_reco");
        h1_tauTau_m_reco = new TH1F(name, title, 50, 0, 500);
        
        sprintf(name, "jet_nearestGen_deltaR");
        sprintf(title, "jet_nearestGen_deltaR");
        h1_jet_nearestGen_deltaR = new TH1F(name, title, 500, 0, 10);
        
        for(int iBin = 0; iBin < v_template_pTbin.size(); iBin++)
        {
            char pTbinStr[Common::str_len];
            
            char posPxBinStr[Common::str_len];
            char negPxBinStr[Common::str_len];
            
            char posPyBinStr[Common::str_len];
            char negPyBinStr[Common::str_len];
            
            if(iBin < v_template_pTbin.size()-1)
            {
                sprintf(pTbinStr, "pT: %dto%d", v_template_pTbin.at(iBin), v_template_pTbin.at(iBin+1));
                
                sprintf(posPxBinStr, "px: %dto%d", v_template_pxyBin.at(iBin), v_template_pxyBin.at(iBin+1));
                sprintf(negPxBinStr, "px: -%dto-%d", v_template_pxyBin.at(iBin), v_template_pxyBin.at(iBin+1));
                
                sprintf(posPyBinStr, "py: %dto%d", v_template_pxyBin.at(iBin), v_template_pxyBin.at(iBin+1));
                sprintf(negPyBinStr, "py: -%dto-%d", v_template_pxyBin.at(iBin), v_template_pxyBin.at(iBin+1));
            }
            
            else
            {
                sprintf(pTbinStr, "pT: %d", v_template_pTbin.at(iBin));
                
                sprintf(posPxBinStr, "px: %d", v_template_pxyBin.at(iBin));
                sprintf(negPxBinStr, "px: -%d", v_template_pxyBin.at(iBin));
                
                sprintf(posPyBinStr, "py: %d", v_template_pxyBin.at(iBin));
                sprintf(negPyBinStr, "py: -%d", v_template_pxyBin.at(iBin));
            }
            
            sprintf(name, "tauh_pTfraction_gen_%s", pTbinStr);
            sprintf(title, "tauh_pTfraction_gen_%s", pTbinStr);
            v_h1_tauh_pTfraction_gen_pTbin.push_back(new TH1F(name, title, 50, 0, 2.5));
            
            sprintf(name, "tauh_Efraction_gen_%s", pTbinStr);
            sprintf(title, "tauh_Efraction_gen_%s", pTbinStr);
            v_h1_tauh_Efraction_gen_pTbin.push_back(new TH1F(name, title, 50, 0, 2.5));
            
            sprintf(name, "tauh_resolution_%s", pTbinStr);
            sprintf(title, "tauh_resolution_%s", pTbinStr);
            v_h1_tauh_resolution_pTbin.push_back(new TH1F(name, title, 50, 0, 2.5));
            
            
            //
            sprintf(name, "tauh_response_%s", pTbinStr);
            sprintf(title, "tauh_response_%s", pTbinStr);
            v_h1_tauh_response_pTbin.push_back(new TH1F(name, title, 50, 0, 2.5));
            
            sprintf(name, "tauh_response_%s", posPxBinStr);
            sprintf(title, "tauh_response_%s", posPxBinStr);
            //v_h1_tauh_response_posPxBin.push_back(new TH1F(name, title, 100, -2.5, 2.5));
            v_h1_tauh_response_posPxBin.push_back(new TH1F(name, title, v_template_responseBin.size()-1, &v_template_responseBin.at(0)));
            
            sprintf(name, "tauh_response_%s", negPxBinStr);
            sprintf(title, "tauh_response_%s", negPxBinStr);
            //v_h1_tauh_response_negPxBin.push_back(new TH1F(name, title, 100, -2.5, 2.5));
            v_h1_tauh_response_negPxBin.push_back(new TH1F(name, title, v_template_responseBin.size()-1, &v_template_responseBin.at(0)));
            
            sprintf(name, "tauh_response_%s", posPyBinStr);
            sprintf(title, "tauh_response_%s", posPyBinStr);
            //v_h1_tauh_response_posPyBin.push_back(new TH1F(name, title, 100, -2.5, 2.5));
            v_h1_tauh_response_posPyBin.push_back(new TH1F(name, title, v_template_responseBin.size()-1, &v_template_responseBin.at(0)));
            
            sprintf(name, "tauh_response_%s", negPyBinStr);
            sprintf(title, "tauh_response_%s", negPyBinStr);
            //v_h1_tauh_response_negPyBin.push_back(new TH1F(name, title, 100, -2.5, 2.5));
            v_h1_tauh_response_negPyBin.push_back(new TH1F(name, title, v_template_responseBin.size()-1, &v_template_responseBin.at(0)));
            
            
            sprintf(name, "tauh_jetResponse_%s", pTbinStr);
            sprintf(title, "tauh_jetResponse_%s", pTbinStr);
            v_h1_tauh_jetResponse_pTbin.push_back(new TH1F(name, title, 50, 0, 2.5));
            
            sprintf(name, "tauh_jetResolution_%s", pTbinStr);
            sprintf(title, "tauh_jetResolution_%s", pTbinStr);
            v_h1_tauh_jetResolution_pTbin.push_back(new TH1F(name, title, 50, 0, 2.5));
        }
    }
    
    
    void Output::writeData()
    {
        // GEN
        h1_tau_vis_pT_gen->Write();
        h1_tau_vis_eta_gen->Write();
        h2_tau_vis_pT_vs_eta_gen->Write();
        
        h1_tauTau_m_gen->Write();
        h1_tauhTauh_m_gen->Write();
        
        // RECO
        h1_tau_all_pT_reco->Write();
        h1_tau_all_eta_reco->Write();
        h2_tau_all_pT_vs_eta_reco->Write();
        
        h2_tau_all_pT_vs_DM_reco->Write();
        
        h1_tau_pT_reco->Write();
        h1_tau_eta_reco->Write();
        h2_tau_pT_vs_eta_reco->Write();
        
        h2_tau_pT_vs_DM_reco->Write();
        
        h1_tau_genMatched_pT_reco->Write();
        h1_tau_genMatched_eta_reco->Write();
        h2_tau_genMatched_pT_vs_eta_reco->Write();
        
        h1_tau_genNotMatched_n_reco->Write();
        h1_tau_genNotMatched_pT_reco->Write();
        h1_tau_genNotMatched_eta_reco->Write();
        h2_tau_genNotMatched_pT_vs_eta_reco->Write();
        
        h1_tau_genNotMatched_genElMatched_n_reco->Write();
        h1_tau_genNotMatched_genElMatched_pT_reco->Write();
        h1_tau_genNotMatched_genElMatched_eta_reco->Write();
        h2_tau_genNotMatched_genElMatched_pT_vs_eta_reco->Write();
        
        h1_tau_genNotMatched_genMuMatched_n_reco->Write();
        h1_tau_genNotMatched_genMuMatched_pT_reco->Write();
        h1_tau_genNotMatched_genMuMatched_eta_reco->Write();
        h2_tau_genNotMatched_genMuMatched_pT_vs_eta_reco->Write();
        
        h1_tau_genNotMatched_genBmatched_n_reco->Write();
        h1_tau_genNotMatched_genBmatched_pT_reco->Write();
        h1_tau_genNotMatched_genBmatched_eta_reco->Write();
        h2_tau_genNotMatched_genBmatched_pT_vs_eta_reco->Write();
        
        h1_tau_nearestGen_deltaR->Write();
        
        h1_tauTau_m_reco->Write();
        
        h1_jet_nearestGen_deltaR->Write();
        
        for(int iBin = 0; iBin < v_template_pTbin.size(); iBin++)
        {
            v_h1_tauh_pTfraction_gen_pTbin.at(iBin)->Write();
            v_h1_tauh_Efraction_gen_pTbin.at(iBin)->Write();
            
            v_h1_tauh_resolution_pTbin.at(iBin)->Write();
            
            v_h1_tauh_response_pTbin.at(iBin)->Write();
            
            v_h1_tauh_response_posPxBin.at(iBin)->Write();
            v_h1_tauh_response_negPxBin.at(iBin)->Write();
            
            v_h1_tauh_response_posPyBin.at(iBin)->Write();
            v_h1_tauh_response_negPyBin.at(iBin)->Write();
            
            v_h1_tauh_jetResponse_pTbin.at(iBin)->Write();
            v_h1_tauh_jetResolution_pTbin.at(iBin)->Write();
        }
    }
    
    
    void Output::freeMemory()
    {
        // GEN
        delete h1_tau_vis_pT_gen;
        delete h1_tau_vis_eta_gen;
        delete h2_tau_vis_pT_vs_eta_gen;
        
        delete h1_tauTau_m_gen;
        delete h1_tauhTauh_m_gen;
        
        // RECO
        delete h1_tau_all_pT_reco;
        delete h1_tau_all_eta_reco;
        delete h2_tau_all_pT_vs_eta_reco;
        
        delete h2_tau_all_pT_vs_DM_reco;
        
        delete h1_tau_pT_reco;
        delete h1_tau_eta_reco;
        delete h2_tau_pT_vs_eta_reco;
        
        delete h2_tau_pT_vs_DM_reco;
        
        delete h1_tau_genMatched_pT_reco;
        delete h1_tau_genMatched_eta_reco;
        delete h2_tau_genMatched_pT_vs_eta_reco;
        
        delete h1_tau_genNotMatched_n_reco;
        delete h1_tau_genNotMatched_pT_reco;
        delete h1_tau_genNotMatched_eta_reco;
        delete h2_tau_genNotMatched_pT_vs_eta_reco;
        
        delete h1_tau_genNotMatched_genElMatched_n_reco;
        delete h1_tau_genNotMatched_genElMatched_pT_reco;
        delete h1_tau_genNotMatched_genElMatched_eta_reco;
        delete h2_tau_genNotMatched_genElMatched_pT_vs_eta_reco;
        
        delete h1_tau_genNotMatched_genMuMatched_n_reco;
        delete h1_tau_genNotMatched_genMuMatched_pT_reco;
        delete h1_tau_genNotMatched_genMuMatched_eta_reco;
        delete h2_tau_genNotMatched_genMuMatched_pT_vs_eta_reco;
        
        delete h1_tau_genNotMatched_genBmatched_n_reco;
        delete h1_tau_genNotMatched_genBmatched_pT_reco;
        delete h1_tau_genNotMatched_genBmatched_eta_reco;
        delete h2_tau_genNotMatched_genBmatched_pT_vs_eta_reco;
        
        delete h1_tau_nearestGen_deltaR;
        
        delete h1_tauTau_m_reco;
        
        delete h1_jet_nearestGen_deltaR;
        
        for(int iBin = 0; iBin < v_template_pTbin.size(); iBin++)
        {
            delete v_h1_tauh_pTfraction_gen_pTbin.at(iBin);
            delete v_h1_tauh_Efraction_gen_pTbin.at(iBin);
            
            delete v_h1_tauh_resolution_pTbin.at(iBin);
            
            delete v_h1_tauh_response_pTbin.at(iBin);
            
            delete v_h1_tauh_response_posPxBin.at(iBin);
            delete v_h1_tauh_response_negPxBin.at(iBin);

            delete v_h1_tauh_response_posPyBin.at(iBin);
            delete v_h1_tauh_response_negPyBin.at(iBin);
            
            delete v_h1_tauh_jetResponse_pTbin.at(iBin);
            delete v_h1_tauh_jetResolution_pTbin.at(iBin);
        }
    }
    
    
    void run(
        std::string process,
        std::string dir,
        std::string sourceFileName,
        std::string era
    )
    {
        printf("\n");
        printf("********** Era: %s ********** \n", era.c_str());
        printf("\n");
        
        
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process.c_str(), process.c_str());
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName);
        
        std::string inFileName;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        //sprintf(outDir, "output_tauIdIsoEfficiency/%s", dir.c_str());
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
            //n++; if(n > 1) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFileName.substr(inFileName.rfind("/")+1, inFileName.rfind(".root")-inFileName.rfind("/")-1)).c_str());
            
            // Outfile
            char outFileName[Common::str_len];
            sprintf(outFileName, "%s/%s_tauIdIsoEfficiency.root", outDir, fileNameStripped);
            TFile *outFile = TFile::Open(outFileName, "RECREATE");
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFileName.c_str());
            printf("Output: %s \n", outFileName);
            printf("\n");
            
            // Input
            std::vector <const char*> v_object_mc_gen = {
                "tau_vis", "el", "mu", "b"
            };
            
            std::vector <const char*> v_object_reco = {
                "tau", "jet", "MET"
            };
            
            CustomInfo_mc::Info *input = new CustomInfo_mc::Info(
                inFileName.c_str(),
                treePath_gen, v_object_mc_gen,
                treePath_reco, v_object_reco,
                "read",
                0, 0,
                0, 0);
            
            std::string tau_isoOption;
            std::string tau_antiElOption;
            std::string tau_antiMuOption;
            
            char outFile_internalDir[Common::str_len];
            
            
            Output *output_temp;
            Output *output_VLooseIso;
            Output *output_looseIso;
            Output *output_mediumIso;
            Output *output_tightIso;
            Output *output_VTightIso;
            
            
            std::string tau_isoOption_vlooseIsolation_dR03;
            std::string tau_isoOption_looseIsolation_dR03;
            std::string tau_isoOption_mediumIsolation_dR03;
            std::string tau_isoOption_tightIsolation_dR03;
            std::string tau_isoOption_vtightIsolation_dR03;
            
            std::string tau_isoOption_vlooseIsolation_dR05;
            std::string tau_isoOption_looseIsolation_dR05;
            std::string tau_isoOption_mediumIsolation_dR05;
            std::string tau_isoOption_tightIsolation_dR05;
            std::string tau_isoOption_vtightIsolation_dR05;
            
            std::vector <double> *v_tau_vlooseIsolation_dR03;
            std::vector <double> *v_tau_looseIsolation_dR03;
            std::vector <double> *v_tau_mediumIsolation_dR03;
            std::vector <double> *v_tau_tightIsolation_dR03;
            std::vector <double> *v_tau_vtightIsolation_dR03;
            
            std::vector <double> *v_tau_vlooseIsolation_dR05;
            std::vector <double> *v_tau_looseIsolation_dR05;
            std::vector <double> *v_tau_mediumIsolation_dR05;
            std::vector <double> *v_tau_tightIsolation_dR05;
            std::vector <double> *v_tau_vtightIsolation_dR05;
            
            // Era
            if(!era.compare("2016"))
            {
                tau_isoOption_vlooseIsolation_dR03 = "VLooseIsolationMVArun2v1DBdR03oldDMwLT";
                tau_isoOption_looseIsolation_dR03 = "LooseIsolationMVArun2v1DBdR03oldDMwLT";
                tau_isoOption_mediumIsolation_dR03 = "MediumIsolationMVArun2v1DBdR03oldDMwLT";
                tau_isoOption_tightIsolation_dR03 = "TightIsolationMVArun2v1DBdR03oldDMwLT";
                tau_isoOption_vtightIsolation_dR03 = "VTightIsolationMVArun2v1DBdR03oldDMwLT";
                
                v_tau_vlooseIsolation_dR03 = input->v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                v_tau_looseIsolation_dR03 = input->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                v_tau_mediumIsolation_dR03 = input->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                v_tau_tightIsolation_dR03 = input->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                v_tau_vtightIsolation_dR03 = input->v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                
                
                tau_isoOption_vlooseIsolation_dR05 = "VLooseIsolationMVArun2v1DBoldDMwLT";
                tau_isoOption_looseIsolation_dR05 = "LooseIsolationMVArun2v1DBoldDMwLT";
                tau_isoOption_mediumIsolation_dR05 = "MediumIsolationMVArun2v1DBoldDMwLT";
                tau_isoOption_tightIsolation_dR05 = "TightIsolationMVArun2v1DBoldDMwLT";
                tau_isoOption_vtightIsolation_dR05 = "VTightIsolationMVArun2v1DBoldDMwLT";
                
                v_tau_vlooseIsolation_dR05 = input->v_tau_byVLooseIsolationMVArun2v1DBoldDMwLT_reco;
                v_tau_looseIsolation_dR05 = input->v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco;
                v_tau_mediumIsolation_dR05 = input->v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco;
                v_tau_tightIsolation_dR05 = input->v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco;
                v_tau_vtightIsolation_dR05 = input->v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco;
            }
            
            else if(!era.compare("2017"))
            {
                tau_isoOption_vlooseIsolation_dR03 = "VLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                tau_isoOption_looseIsolation_dR03 = "LooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                tau_isoOption_mediumIsolation_dR03 = "MediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                tau_isoOption_tightIsolation_dR03 = "TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                tau_isoOption_vtightIsolation_dR03 = "VTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017";
                
                v_tau_vlooseIsolation_dR03 = input->v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                v_tau_looseIsolation_dR03 = input->v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                v_tau_mediumIsolation_dR03 = input->v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                v_tau_tightIsolation_dR03 = input->v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                v_tau_vtightIsolation_dR03 = input->v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                
                
                tau_isoOption_vlooseIsolation_dR05 = "VLooseIsolationMVArun2017v2DBoldDMwLT2017";
                tau_isoOption_looseIsolation_dR05 = "LooseIsolationMVArun2017v2DBoldDMwLT2017";
                tau_isoOption_mediumIsolation_dR05 = "MediumIsolationMVArun2017v2DBoldDMwLT2017";
                tau_isoOption_tightIsolation_dR05 = "TightIsolationMVArun2017v2DBoldDMwLT2017";
                tau_isoOption_vtightIsolation_dR05 = "VTightIsolationMVArun2017v2DBoldDMwLT2017";
                
                v_tau_vlooseIsolation_dR05 = input->v_tau_byVLooseIsolationMVArun2017v2DBoldDMwLT2017_reco;
                v_tau_looseIsolation_dR05 = input->v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco;
                v_tau_mediumIsolation_dR05 = input->v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco;
                v_tau_tightIsolation_dR05 = input->v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco;
                v_tau_vtightIsolation_dR05 = input->v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco;
            }
            
            else
            {
                printf("Error in TauIdIsoEfficiency_mc::run(...): Provide a valid era (2016/2017). Provided era: %s", era);
                exit(EXIT_FAILURE);
            }
            
            
            
            // LooseDeepTau2017v2p1VSjet
            tau_isoOption = "LooseDeepTau2017v2p1VSjet";
            tau_antiElOption = "LooseDeepTau2017v2p1VSe";
            tau_antiMuOption = "TightDeepTau2017v2p1VSmu";
            
            output_temp = new Output();
            
            analyze(
                input,
                output_temp,
                20, 2.1,
                20, 2.1,
                Common::tau_dzCut_reco, input->v_tau_dz_reco,
                tau_isoOption, input->v_tau_byLooseDeepTau2017v2p1VSjet_reco,
                tau_antiElOption, input->v_tau_byLooseDeepTau2017v2p1VSe_reco,
                tau_antiMuOption, input->v_tau_byTightDeepTau2017v2p1VSmu_reco,
                0.3,
                true
            );
            
            sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            outFile->mkdir(outFile_internalDir);
            outFile->cd(outFile_internalDir);
            output_temp->writeData();
            
            output_temp->freeMemory();
            delete output_temp;
            
            printf("\n");
            
            
            
            // TightDeepTau2017v2p1VSjet
            tau_isoOption = "TightDeepTau2017v2p1VSjet";
            tau_antiElOption = "LooseDeepTau2017v2p1VSe";
            tau_antiMuOption = "TightDeepTau2017v2p1VSmu";
            
            output_temp = new Output();
            
            analyze(
                input,
                output_temp,
                20, 2.1,
                20, 2.1,
                Common::tau_dzCut_reco, input->v_tau_dz_reco,
                tau_isoOption, input->v_tau_byTightDeepTau2017v2p1VSjet_reco,
                tau_antiElOption, input->v_tau_byLooseDeepTau2017v2p1VSe_reco,
                tau_antiMuOption, input->v_tau_byTightDeepTau2017v2p1VSmu_reco,
                0.3,
                true
            );
            
            sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            outFile->mkdir(outFile_internalDir);
            outFile->cd(outFile_internalDir);
            output_temp->writeData();
            
            output_temp->freeMemory();
            delete output_temp;
            
            printf("\n");
            
            
            
            // VLooseIsolationMVArun2v1DBdR03oldDMwLT
            //tau_isoOption = tau_isoOption_vlooseIsolation_dR03;
            //tau_antiElOption = "againstElectronLooseMVA6";
            //tau_antiMuOption = "againstMuonLoose3";
            //
            //output_VLooseIso = new Output();
            //
            //analyze(
            //    input,
            //    output_VLooseIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_vlooseIsolation_dR03,
            //    tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_VLooseIso->writeData();
            //
            //output_VLooseIso->freeMemory();
            //delete output_VLooseIso;
            //
            //printf("\n");
            //
            //
            //// VLooseIsolationMVArun2v1DBoldDMwLT
            //tau_isoOption = tau_isoOption_vlooseIsolation_dR05;
            //tau_antiElOption = "againstElectronLooseMVA6";
            //tau_antiMuOption = "againstMuonLoose3";
            //
            //output_VLooseIso = new Output();
            //
            //analyze(
            //    input,
            //    output_VLooseIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_vlooseIsolation_dR05,
            //    tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_VLooseIso->writeData();
            //
            //output_VLooseIso->freeMemory();
            //delete output_VLooseIso;
            //
            //printf("\n");
            
            
            // LooseIsolationMVArun2v1DBdR03oldDMwLT
            tau_isoOption = tau_isoOption_looseIsolation_dR03;
            tau_antiElOption = "againstElectronLooseMVA6";
            tau_antiMuOption = "againstMuonLoose3";
            
            output_looseIso = new Output();
            
            analyze(
                input,
                output_looseIso,
                20, 2.1,
                20, 2.1,
                Common::tau_dzCut_reco, input->v_tau_dz_reco,
                tau_isoOption, v_tau_looseIsolation_dR03,
                tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
                tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
                0.3,
                false
            );
            
            sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            outFile->mkdir(outFile_internalDir);
            outFile->cd(outFile_internalDir);
            output_looseIso->writeData();
            
            output_looseIso->freeMemory();
            delete output_looseIso;
            
            printf("\n");
            
            
            // LooseIsolationMVArun2v1DBoldDMwLT
            //tau_isoOption = tau_isoOption_looseIsolation_dR05;
            //tau_antiElOption = "againstElectronLooseMVA6";
            //tau_antiMuOption = "againstMuonLoose3";
            //
            //output_looseIso = new Output();
            //
            //analyze(
            //    input,
            //    output_looseIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_looseIsolation_dR05,
            //    tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_looseIso->writeData();
            //
            //output_looseIso->freeMemory();
            //delete output_looseIso;
            //
            //printf("\n");*/
            
            
            // MediumIsolationMVArun2v1DBdR03oldDMwLT
            //tau_isoOption = tau_isoOption_mediumIsolation_dR03;
            //tau_antiElOption = "againstElectronLooseMVA6";
            //tau_antiMuOption = "againstMuonLoose3";
            //
            //output_mediumIso = new Output();
            //
            //analyze(
            //    input,
            //    output_mediumIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_mediumIsolation_dR03,
            //    tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_mediumIso->writeData();
            //
            //output_mediumIso->freeMemory();
            //delete output_mediumIso;
            //
            //printf("\n");
            
            
            // MediumIsolationMVArun2v1DBoldDMwLT
            //tau_isoOption = tau_isoOption_mediumIsolation_dR05;
            //tau_antiElOption = "againstElectronLooseMVA6";
            //tau_antiMuOption = "againstMuonLoose3";
            //
            //output_mediumIso = new Output();
            //
            //analyze(
            //    input,
            //    output_mediumIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_mediumIsolation_dR05,
            //    tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_mediumIso->writeData();
            //
            //output_mediumIso->freeMemory();
            //delete output_mediumIso;
            //
            //printf("\n");
            
            
            // TightIsolationMVArun2v1DBdR03oldDMwLT
            tau_isoOption = tau_isoOption_tightIsolation_dR03;
            tau_antiElOption = "againstElectronLooseMVA6";
            tau_antiMuOption = "againstMuonLoose3";
            
            output_tightIso = new Output();
            
            analyze(
                input,
                output_tightIso,
                20, 2.1,
                20, 2.1,
                Common::tau_dzCut_reco, input->v_tau_dz_reco,
                tau_isoOption, v_tau_tightIsolation_dR03,
                tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
                tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
                0.3,
                false
            );
            
            sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            outFile->mkdir(outFile_internalDir);
            outFile->cd(outFile_internalDir);
            output_tightIso->writeData();
            
            output_tightIso->freeMemory();
            delete output_tightIso;
            
            printf("\n");
            
            
            // TightIsolationMVArun2v1DBdR03oldDMwLT
            //tau_isoOption = tau_isoOption_tightIsolation_dR03;
            //tau_antiElOption = "againstElectronTightMVA6";
            //tau_antiMuOption = "againstMuonTight3";
            //
            //output_tightIso = new Output();
            //
            //analyze(
            //    input,
            //    output_tightIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_tightIsolation_dR03,
            //    tau_antiElOption, input->v_tau_againstElectronTightMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonTight3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_tightIso->writeData();
            //
            //output_tightIso->freeMemory();
            //delete output_tightIso;
            //
            //printf("\n");
            
            /*
            // TightIsolationMVArun2v1DBoldDMwLT
            tau_isoOption = tau_isoOption_tightIsolation_dR05;
            tau_antiElOption = "againstElectronLooseMVA6";
            tau_antiMuOption = "againstMuonLoose3";
            
            output_tightIso = new Output();
            
            analyze(
                input,
                output_tightIso,
                20, 2.1,
                20, 2.1,
                Common::tau_dzCut_reco, input->v_tau_dz_reco,
                tau_isoOption, v_tau_tightIsolation_dR05,
                tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
                tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
                0.3
            );
            
            sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            outFile->mkdir(outFile_internalDir);
            outFile->cd(outFile_internalDir);
            output_tightIso->writeData();
            
            output_tightIso->freeMemory();
            delete output_tightIso;
            
            printf("\n");*/
            
            
            // VTightIsolationMVArun2v1DBdR03oldDMwLT
            //tau_isoOption = tau_isoOption_vtightIsolation_dR03;
            //tau_antiElOption = "againstElectronLooseMVA6";
            //tau_antiMuOption = "againstMuonLoose3";
            //
            //output_VTightIso = new Output();
            //
            //analyze(
            //    input,
            //    output_VTightIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_vtightIsolation_dR03,
            //    tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_VTightIso->writeData();
            //
            //output_VTightIso->freeMemory();
            //delete output_VTightIso;
            //
            //printf("\n");
            
            
            // VTightIsolationMVArun2v1DBoldDMwLT
            //tau_isoOption = tau_isoOption_vtightIsolation_dR05;
            //tau_antiElOption = "againstElectronLooseMVA6";
            //tau_antiMuOption = "againstMuonLoose3";
            //
            //output_VTightIso = new Output();
            //
            //analyze(
            //    input,
            //    output_VTightIso,
            //    20, 2.1,
            //    20, 2.1,
            //    Common::tau_dzCut_reco, input->v_tau_dz_reco,
            //    tau_isoOption, v_tau_vtightIsolation_dR05,
            //    tau_antiElOption, input->v_tau_againstElectronLooseMVA6_reco,
            //    tau_antiMuOption, input->v_tau_againstMuonLoose3_reco,
            //    0.3
            //);
            //
            //sprintf(outFile_internalDir, "%s_%s_%s", tau_isoOption.c_str(), tau_antiElOption.c_str(), tau_antiMuOption.c_str());
            //outFile->mkdir(outFile_internalDir);
            //outFile->cd(outFile_internalDir);
            //output_VTightIso->writeData();
            //
            //output_VTightIso->freeMemory();
            //delete output_VTightIso;
            //
            //printf("\n");
            
            
            //
            delete outFile;
            
            input->freeMemory();
            delete input;
        }
    }
    
    
    void analyze(
        CustomInfo_mc::Info *input,
        Output *output,
        double tau_pTcut_gen, double tau_etaCut_gen,
        double tau_pTcut_reco, double tau_etaCut_reco,
        double tau_dzCut_reco, std::vector <double> *v_tau_dz_reco,
        std::string tau_isoOption, std::vector <double> *v_tau_isolation,
        std::string tau_antiElOption, std::vector <double> *v_tau_antiElectron,
        std::string tau_antiMuOption, std::vector <double> *v_tau_antiMuon,
        double deltaRcut,
        bool isDeepTau
    )
    {
        int nEvent = input->T_reco->GetEntries();
        
        for(int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if(iEvent == 0 || (iEvent+1) % 1000 == 0 || iEvent == nEvent-1)
            {
                printf(
                    "[%s, %s, %s] Processing event no. %d / %d \n",
                    tau_isoOption.c_str(),
                    tau_antiElOption.c_str(),
                    tau_antiMuOption.c_str(),
                    iEvent+1,
                    nEvent
                );
                
                fflush(stdout);
            }
            
            input->T_gen->GetEntry(iEvent);
            input->T_reco->GetEntry(iEvent);
            
            
            // Gen taus
            std::vector <bool> v_tau_isSelected_gen(input->tau_vis_n_gen, false);
            std::vector <bool> v_tau_isUsed_gen(input->tau_vis_n_gen, false);
            
            CLHEP::HepLorentzVector tau1_4mom_gen(0, 0, 0, 0);
            CLHEP::HepLorentzVector tau2_4mom_gen(0, 0, 0, 0);
            
            CLHEP::HepLorentzVector tauh1_4mom_gen(0, 0, 0, 0);
            CLHEP::HepLorentzVector tauh2_4mom_gen(0, 0, 0, 0);
            
            bool foundTauPair_gen = false;
            
            for(int iTau = 0; iTau < input->tau_vis_n_gen; iTau++)
            {
                CLHEP::HepLorentzVector tauh_4mom_gen;
                
                tauh_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(iTau)));
                tauh_4mom_gen.setX(input->v_tau_vis_px_gen->at(iTau));
                tauh_4mom_gen.setY(input->v_tau_vis_py_gen->at(iTau));
                tauh_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(iTau));
                
                CLHEP::HepLorentzVector tau_4mom_gen;
                
                tau_4mom_gen.setT(fabs(input->v_tau_E_gen->at(iTau)));
                tau_4mom_gen.setX(input->v_tau_px_gen->at(iTau));
                tau_4mom_gen.setY(input->v_tau_py_gen->at(iTau));
                tau_4mom_gen.setZ(input->v_tau_pz_gen->at(iTau));
                
                if(/*tauh_4mom_gen.perp() < tau_pTcut_gen || */fabs(tauh_4mom_gen.eta()) > tau_etaCut_gen)
                {
                    continue;
                }
                
                v_tau_isSelected_gen.at(iTau) = true;
                
                output->h1_tau_vis_pT_gen->Fill(tauh_4mom_gen.perp());
                output->h1_tau_vis_eta_gen->Fill(tauh_4mom_gen.eta());
                output->h2_tau_vis_pT_vs_eta_gen->Fill(tauh_4mom_gen.eta(), tauh_4mom_gen.perp());
                
                double tauh_pTfraction_gen = tauh_4mom_gen.perp() / tau_4mom_gen.perp();
                double tauh_Efraction_gen = tauh_4mom_gen.e() / tau_4mom_gen.e();
                
                int pTbin_tau = -1;
                
                for(int iBin = 0; iBin < output->v_template_pTbin.size(); iBin++)
                {
                    if(tau_4mom_gen.perp() >= output->v_template_pTbin.at(iBin))
                    {
                        pTbin_tau = iBin;
                    }
                }
                
                if(pTbin_tau >= 0)
                {
                    output->v_h1_tauh_pTfraction_gen_pTbin.at(pTbin_tau)->Fill(tauh_pTfraction_gen);
                    output->v_h1_tauh_Efraction_gen_pTbin.at(pTbin_tau)->Fill(tauh_Efraction_gen);
                }
                
                // Store the two leading taus
                if(tauh_4mom_gen.perp() > tauh1_4mom_gen.perp())
                {
                    tau1_4mom_gen = tau_4mom_gen;
                    tauh1_4mom_gen = tauh_4mom_gen;
                }
                
                else if(tauh_4mom_gen.perp() > tauh2_4mom_gen.perp())
                {
                    tau2_4mom_gen = tau_4mom_gen;
                    tauh2_4mom_gen = tauh_4mom_gen;
                    
                    foundTauPair_gen = true;
                }
            }
            
            
            if(foundTauPair_gen)
            {
                output->h1_tauTau_m_gen->Fill((tau1_4mom_gen + tau2_4mom_gen).m());
                output->h1_tauhTauh_m_gen->Fill((tauh1_4mom_gen + tauh2_4mom_gen).m());
            }
            
            
            // Reco taus
            CLHEP::HepLorentzVector tau1_4mom_reco(0, 0, 0, 0);
            CLHEP::HepLorentzVector tau2_4mom_reco(0, 0, 0, 0);
            
            bool foundTauPair_reco = false;
            
            std::vector <bool> v_tau_isSelected_reco(input->tau_n_reco, false);
            std::vector <bool> v_tau_isGenMatched_reco(input->tau_n_reco, false);
            
            for(int iTau_reco = 0; iTau_reco < input->tau_n_reco; iTau_reco++)
            {
                CLHEP::HepLorentzVector tau_4mom_reco;
                
                tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau_reco)));
                tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau_reco));
                tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau_reco));
                tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau_reco));
                
                // pT, eta
                if(tau_4mom_reco.perp() < tau_pTcut_reco || fabs(tau_4mom_reco.eta()) > tau_etaCut_reco)
                {
                    continue;
                }
                
                output->h1_tau_all_pT_reco->Fill(tau_4mom_reco.perp());
                output->h1_tau_all_eta_reco->Fill(tau_4mom_reco.eta());
                output->h2_tau_all_pT_vs_eta_reco->Fill(tau_4mom_reco.eta(), tau_4mom_reco.perp());
                
                output->h2_tau_all_pT_vs_DM_reco->Fill(input->v_tau_decayMode_reco->at(iTau_reco), tau_4mom_reco.perp());
                
                // Decay mode
                if(isDeepTau)
                {
                    if(!Common::isTauNewDM(input->v_tau_decayMode_reco->at(iTau_reco)))
                    {
                        continue;
                    }
                }
                
                else
                {
                    if(!input->v_tau_byDecayModeFinding_reco->at(iTau_reco))
                    {
                        continue;
                    }
                }
                
                // Isolation
                if(!v_tau_isolation->at(iTau_reco))
                {
                    continue;
                }
                
                // Anti-electron/muon
                if(!v_tau_antiElectron->at(iTau_reco) || !v_tau_antiMuon->at(iTau_reco))
                {
                    continue;
                }
                
                // IP
                if(fabs(v_tau_dz_reco->at(iTau_reco)) >= tau_dzCut_reco)
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
                    output->h1_tau_nearestGen_deltaR->Fill(deltaR_min);
                    
                    if(deltaR_min < deltaRcut)
                    {
                        v_tau_isGenMatched_reco.at(iTau_reco) = true;
                        
                        tau_genMatchedIndex = tau_nearestGenIndex;
                        
                        v_tau_isUsed_gen.at(tau_genMatchedIndex) = true;
                        
                        output->h1_tau_pT_reco->Fill(tau_4mom_reco.perp());
                        output->h1_tau_eta_reco->Fill(tau_4mom_reco.eta());
                        output->h2_tau_pT_vs_eta_reco->Fill(tau_4mom_reco.eta(), tau_4mom_reco.perp());
                        
                        output->h2_tau_pT_vs_DM_reco->Fill(input->v_tau_decayMode_reco->at(iTau_reco), tau_4mom_reco.perp());
                        
                        output->h1_tau_genMatched_pT_reco->Fill(tau_nearestGenh_4mom.perp());
                        output->h1_tau_genMatched_eta_reco->Fill(tau_nearestGenh_4mom.eta());
                        output->h2_tau_genMatched_pT_vs_eta_reco->Fill(tau_nearestGenh_4mom.eta(), tau_nearestGenh_4mom.perp());
                        
                        
                        // Tau response and resolution
                        double tau_pTresolution = tau_4mom_reco.perp() / tau_nearestGenh_4mom.perp();
                        
                        double tau_pTresponse = tau_4mom_reco.perp() / tau_nearestGen_4mom.perp();
                        double tau_pxResponse = tau_4mom_reco.px() / tau_nearestGen_4mom.px();
                        double tau_pyResponse = tau_4mom_reco.py() / tau_nearestGen_4mom.py();
                        
                        int pTbin_tauh = -1;
                        
                        int pTbin_tau = -1;
                        int pxBin_tau = -1;
                        int pyBin_tau = -1;
                        
                        for(int iBin = 0; iBin < output->v_template_pTbin.size(); iBin++)
                        {
                            if(tau_nearestGenh_4mom.perp() >= output->v_template_pTbin.at(iBin))
                            {
                                pTbin_tauh = iBin;
                            }
                            
                            if(tau_nearestGen_4mom.perp() >= output->v_template_pTbin.at(iBin))
                            {
                                pTbin_tau = iBin;
                            }
                            
                            if(fabs(tau_nearestGen_4mom.px()) >= output->v_template_pxyBin.at(iBin))
                            {
                                pxBin_tau = iBin;
                            }
                            
                            if(fabs(tau_nearestGen_4mom.py()) >= output->v_template_pxyBin.at(iBin))
                            {
                                pyBin_tau = iBin;
                            }
                        }
                        
                        if(pTbin_tauh >= 0)
                        {
                            output->v_h1_tauh_resolution_pTbin.at(pTbin_tauh)->Fill(tau_pTresolution);
                        }
                        
                        if(pTbin_tau >= 0)
                        {
                            output->v_h1_tauh_response_pTbin.at(pTbin_tau)->Fill(tau_pTresponse);
                        }
                        
                        if(pxBin_tau >= 0)
                        {
                            if(tau_nearestGen_4mom.px() > 0)
                            {
                                output->v_h1_tauh_response_posPxBin.at(pxBin_tau)->Fill(tau_pxResponse);
                            }
                            
                            else
                            {
                                output->v_h1_tauh_response_negPxBin.at(pxBin_tau)->Fill(tau_pxResponse);
                            }
                        }
                        
                        if(pyBin_tau >= 0)
                        {
                            if(tau_nearestGen_4mom.py() > 0)
                            {
                                output->v_h1_tauh_response_posPyBin.at(pyBin_tau)->Fill(tau_pyResponse);
                            }
                            
                            else
                            {
                                output->v_h1_tauh_response_negPyBin.at(pyBin_tau)->Fill(tau_pyResponse);
                            }
                        }
                        
                        
                        // Store the two leading taus
                        if(tau_4mom_reco.perp() > tau1_4mom_reco.perp())
                        {
                            tau1_4mom_reco = tau_4mom_reco;
                        }
                        
                        else if(tau_4mom_reco.perp() > tau2_4mom_reco.perp())
                        {
                            tau2_4mom_reco = tau_4mom_reco;
                            
                            foundTauPair_reco = true;
                        }
                    }
                }
            }
            
            std::vector <double> vd_tau_isSelected_reco(v_tau_isSelected_reco.begin(), v_tau_isSelected_reco.end());
            
            std::vector <std::vector <double> *> vv_tauSelection_reco = {
                &vd_tau_isSelected_reco
            };
            
            std::vector <int> tauPair_pos = Common::getObjPair(
                &(input->v_tau_reco),
                &(input->v_tau_reco),
                true,
                vv_tauSelection_reco,
                vv_tauSelection_reco,
                Common::tauTau_deltaRcut_reco,
                "OS"
            );
            
            if(tauPair_pos.size() && input->MET_E_reco > 50)
            //if(input->MET_E_reco > 50)
            {
                int tau_genNotMatched_n = 0;
                int tau_genNotMatched_genElMatched_n = 0;
                int tau_genNotMatched_genMuMatched_n = 0;
                int tau_genNotMatched_genBmatched_n = 0;
                
                for(int iTau_reco = 0; iTau_reco < input->tau_n_reco; iTau_reco++)
                {
                    // Only the fake tau reco
                    if(v_tau_isGenMatched_reco.at(iTau_reco))
                    {
                        continue;
                    }
                    
                    if(!v_tau_isSelected_reco.at(iTau_reco))
                    {
                        continue;
                    }
                    
                    // Must be one of the tau-pair
                    if(!(iTau_reco == tauPair_pos.at(0) || iTau_reco == tauPair_pos.at(1)))
                    {
                        continue;
                    }
                    
                    
                    tau_genNotMatched_n++;
                    
                    CLHEP::HepLorentzVector tau_4mom_reco;
                    
                    tau_4mom_reco.setT(fabs(input->v_tau_E_reco->at(iTau_reco)));
                    tau_4mom_reco.setX(input->v_tau_px_reco->at(iTau_reco));
                    tau_4mom_reco.setY(input->v_tau_py_reco->at(iTau_reco));
                    tau_4mom_reco.setZ(input->v_tau_pz_reco->at(iTau_reco));
                    
                    //printf("[%d] Tau %d: isSelected %d, pT %0.2f, eta %0.2f \n",
                    //    iEvent, iTau_reco,
                    //    (int) v_tau_isSelected_reco.at(iTau_reco),
                    //    tau_4mom_reco.perp(),
                    //    tau_4mom_reco.eta()
                    //);
                    
                    output->h1_tau_genNotMatched_pT_reco->Fill(tau_4mom_reco.perp());
                    output->h1_tau_genNotMatched_eta_reco->Fill(tau_4mom_reco.eta());
                    output->h2_tau_genNotMatched_pT_vs_eta_reco->Fill(tau_4mom_reco.eta(), tau_4mom_reco.perp());
                    
                    
                    // Gen electron matching
                    bool isGenElMatched = false;
                    
                    for(int iEl_gen = 0; iEl_gen < input->el_n_gen; iEl_gen++)
                    {
                        CLHEP::HepLorentzVector el_4mom_gen;
                        
                        el_4mom_gen.setT(fabs(input->v_el_E_gen->at(iEl_gen)));
                        el_4mom_gen.setX(input->v_el_px_gen->at(iEl_gen));
                        el_4mom_gen.setY(input->v_el_py_gen->at(iEl_gen));
                        el_4mom_gen.setZ(input->v_el_pz_gen->at(iEl_gen));
                        
                        if(el_4mom_gen.perp() < tau_pTcut_reco || fabs(el_4mom_gen.eta()) > tau_etaCut_reco)
                        {
                            continue;
                        }
                        
                        if(!input->v_el_isPrompt_gen->at(iEl_gen))
                        {
                            continue;
                        }
                        
                        if(el_4mom_gen.deltaR(tau_4mom_reco) < 0.3)
                        {
                            isGenElMatched = true;
                            break;
                        }
                    }
                    
                    
                    // Gen muon matching
                    bool isGenMuMatched = false;
                    
                    for(int iMu_gen = 0; iMu_gen < input->mu_n_gen; iMu_gen++)
                    {
                        CLHEP::HepLorentzVector mu_4mom_gen;
                        
                        mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(iMu_gen)));
                        mu_4mom_gen.setX(input->v_mu_px_gen->at(iMu_gen));
                        mu_4mom_gen.setY(input->v_mu_py_gen->at(iMu_gen));
                        mu_4mom_gen.setZ(input->v_mu_pz_gen->at(iMu_gen));
                        
                        if(mu_4mom_gen.perp() < tau_pTcut_reco || fabs(mu_4mom_gen.eta()) > tau_etaCut_reco)
                        {
                            continue;
                        }
                        
                        if(!input->v_mu_isPrompt_gen->at(iMu_gen))
                        {
                            continue;
                        }
                        
                        if(mu_4mom_gen.deltaR(tau_4mom_reco) < 0.3)
                        {
                            isGenMuMatched = true;
                            break;
                        }
                    }
                    
                    
                    // Gen b matching
                    bool isGenBmatched = false;
                    
                    for(int iB_gen = 0; iB_gen < input->b_n_gen; iB_gen++)
                    {
                        CLHEP::HepLorentzVector b_4mom_gen;
                        
                        b_4mom_gen.setT(fabs(input->v_b_E_gen->at(iB_gen)));
                        b_4mom_gen.setX(input->v_b_px_gen->at(iB_gen));
                        b_4mom_gen.setY(input->v_b_py_gen->at(iB_gen));
                        b_4mom_gen.setZ(input->v_b_pz_gen->at(iB_gen));
                        
                        if(b_4mom_gen.perp() < tau_pTcut_reco || fabs(b_4mom_gen.eta()) > tau_etaCut_reco)
                        {
                            continue;
                        }
                        
                        if(b_4mom_gen.deltaR(tau_4mom_reco) < 0.3)
                        {
                            isGenBmatched = true;
                            break;
                        }
                    }
                    
                    
                    if(isGenElMatched && !isGenMuMatched && !isGenBmatched)
                    {
                        tau_genNotMatched_genElMatched_n++;
                        
                        output->h1_tau_genNotMatched_genElMatched_pT_reco->Fill(tau_4mom_reco.perp());
                        output->h1_tau_genNotMatched_genElMatched_eta_reco->Fill(tau_4mom_reco.eta());
                        output->h2_tau_genNotMatched_genElMatched_pT_vs_eta_reco->Fill(tau_4mom_reco.eta(), tau_4mom_reco.perp());
                    }
                    
                    if(isGenMuMatched && !isGenElMatched && !isGenBmatched)
                    {
                        tau_genNotMatched_genMuMatched_n++;
                        
                        output->h1_tau_genNotMatched_genMuMatched_pT_reco->Fill(tau_4mom_reco.perp());
                        output->h1_tau_genNotMatched_genMuMatched_eta_reco->Fill(tau_4mom_reco.eta());
                        output->h2_tau_genNotMatched_genMuMatched_pT_vs_eta_reco->Fill(tau_4mom_reco.eta(), tau_4mom_reco.perp());
                    }
                    
                    if(isGenBmatched)
                    {
                        tau_genNotMatched_genBmatched_n++;
                        
                        output->h1_tau_genNotMatched_genBmatched_pT_reco->Fill(tau_4mom_reco.perp());
                        output->h1_tau_genNotMatched_genBmatched_eta_reco->Fill(tau_4mom_reco.eta());
                        output->h2_tau_genNotMatched_genBmatched_pT_vs_eta_reco->Fill(tau_4mom_reco.eta(), tau_4mom_reco.perp());
                    }
                }
                
                output->h1_tau_genNotMatched_n_reco->Fill(tau_genNotMatched_n);
                output->h1_tau_genNotMatched_genElMatched_n_reco->Fill(tau_genNotMatched_genElMatched_n);
                output->h1_tau_genNotMatched_genMuMatched_n_reco->Fill(tau_genNotMatched_genMuMatched_n);
                output->h1_tau_genNotMatched_genBmatched_n_reco->Fill(tau_genNotMatched_genBmatched_n);
            }
            
            
            // Fill the underflow bin for the gen taus that were not matched
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
                
                int pTbin_tau = -1;
                
                for(int iBin = 0; iBin < output->v_template_pTbin.size(); iBin++)
                {
                    if(tau_4mom_gen.perp() >= output->v_template_pTbin.at(iBin))
                    {
                        pTbin_tau = iBin;
                    }
                }
                
                if(pTbin_tau >= 0)
                {
                    output->v_h1_tauh_response_pTbin.at(pTbin_tau)->Fill(-1);
                }
            }
            
            
            if(foundTauPair_reco)
            //if(foundTauPair_reco && tau1_4mom_reco.perp() > 40 && tau2_4mom_reco.perp() > 40)
            {
                output->h1_tauTau_m_reco->Fill((tau1_4mom_reco + tau2_4mom_reco).m());
            }
            
            
            // Do the same with AK4 jets
            v_tau_isUsed_gen.resize(0);
            v_tau_isUsed_gen.resize(input->tau_vis_n_gen, false);
            
            for(int iJet_reco = 0; iJet_reco < input->jet_n_reco; iJet_reco++)
            {
                CLHEP::HepLorentzVector jet_4mom_reco;
                
                jet_4mom_reco.setT(fabs(input->v_jet_E_reco->at(iJet_reco)));
                jet_4mom_reco.setX(input->v_jet_px_reco->at(iJet_reco));
                jet_4mom_reco.setY(input->v_jet_py_reco->at(iJet_reco));
                jet_4mom_reco.setZ(input->v_jet_pz_reco->at(iJet_reco));
                
                // pT, eta
                if(/*jet_4mom_reco.perp() < jet_pTcut_reco || */fabs(jet_4mom_reco.eta()) > 2.1)
                {
                    continue;
                }
                
                int jet_genMatchedIndex = -1;
                int jet_nearestGenIndex = -1;
                double deltaR_min = 9999;
                
                CLHEP::HepLorentzVector jet_nearestGenh_4mom;
                CLHEP::HepLorentzVector jet_nearestGen_4mom;
                
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
                    
                    double deltaR = jet_4mom_reco.deltaR(tauh_4mom_gen);
                    
                    if(deltaR < deltaR_min)
                    {
                        deltaR_min = deltaR;
                        
                        jet_nearestGenIndex = iTau_gen;
                        
                        jet_nearestGenh_4mom = tauh_4mom_gen;
                        jet_nearestGen_4mom = tau_4mom_gen;
                    }
                }
                
                if(jet_nearestGenIndex >= 0)
                {
                    output->h1_jet_nearestGen_deltaR->Fill(deltaR_min);
                    
                    if(deltaR_min < deltaRcut)
                    {
                        jet_genMatchedIndex = jet_nearestGenIndex;
                        
                        v_tau_isUsed_gen.at(jet_genMatchedIndex) = true;
                        
                        // Jet response and resolution
                        double jet_pTresolution = jet_4mom_reco.perp() / jet_nearestGenh_4mom.perp();
                        double jet_pTresponse = jet_4mom_reco.perp() / jet_nearestGen_4mom.perp();
                        
                        int pTbin_tauh = -1;
                        int pTbin_tau = -1;
                        
                        for(int iBin = 0; iBin < output->v_template_pTbin.size(); iBin++)
                        {
                            if(jet_nearestGenh_4mom.perp() >= output->v_template_pTbin.at(iBin))
                            {
                                pTbin_tauh = iBin;
                            }
                            
                            if(jet_nearestGen_4mom.perp() >= output->v_template_pTbin.at(iBin))
                            {
                                pTbin_tau = iBin;
                            }
                        }
                        
                        if(pTbin_tauh >= 0)
                        {
                            output->v_h1_tauh_jetResolution_pTbin.at(pTbin_tauh)->Fill(jet_pTresolution);
                        }
                        
                        if(pTbin_tau >= 0)
                        {
                            output->v_h1_tauh_jetResponse_pTbin.at(pTbin_tau)->Fill(jet_pTresponse);
                        }
                    }
                }
            }
        }
    }
}

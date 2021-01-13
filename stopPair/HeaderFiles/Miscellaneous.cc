# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <typeinfo>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTable.h>
# include <TTree.h>

# include "lester_mt2_bisect_mod.h"

# include "Common.h"
# include "CustomInfo_mc.h"
# include "CustomInfo_data.h"
# include "Miscellaneous.h"


namespace Miscellaneous
{
    Output::Output()
    {
        h1_mu1_pT_gen = new TH1F("mu1_pT_gen", "mu1_pT_gen", 100, 0, 2000);
        h1_mu1_eta_gen = new TH1F("mu1_eta_gen", "mu1_eta_gen", 24, -3, 3);
        h1_mu1_phi_gen = new TH1F("mu1_phi_gen", "mu1_phi_gen", 25, -M_PI, M_PI);
        
        h1_tau1_pT_gen = new TH1F("tau1_pT_gen", "tau1_pT_gen", 100, 0, 2000);
        h1_tau1_eta_gen = new TH1F("tau1_eta_gen", "tau1_eta_gen", 24, -3, 3);
        h1_tau1_phi_gen = new TH1F("tau1_phi_gen", "tau1_phi_gen", 25, -M_PI, M_PI);
        
        h1_mu1_pT_reco = new TH1F("mu1_pT_reco", "mu1_pT_reco", 100, 0, 2000);
        h1_mu1_eta_reco = new TH1F("mu1_eta_reco", "mu1_eta_reco", 24, -3, 3);
        h1_mu1_phi_reco = new TH1F("mu1_phi_reco", "mu1_phi_reco", 25, -M_PI, M_PI);
        
        h1_mu1_genMatched_pT_reco = new TH1F("mu1_genMatched_pT_reco", "mu1_genMatched_pT_reco", 100, 0, 2000);
        h1_mu1_genMatched_eta_reco = new TH1F("mu1_genMatched_eta_reco", "mu1_genMatched_eta_reco", 24, -3, 3);
        h1_mu1_genMatched_phi_reco = new TH1F("mu1_genMatched_phi_reco", "mu1_genMatched_phi_reco", 25, -M_PI, M_PI);
        
        h1_mu1_resolution_pT = new TH1F("mu1_resolution_pT", "mu1_resolution_pT", 100, 0, 2.5);
        
        h1_tauTau_isGenMatched = new TH1F("tauTau_isGenMatched", "tauTau_isGenMatched", 6, -1, 2);
        
        h1_tau_isGenMatched = new TH1F("tau_isGenMatched", "tau_isGenMatched", 6, -1, 2);
        
        h2_tau_n_gen_vs_reco = new TH2F("tau_n_gen_vs_reco", "tau_n_gen_vs_reco", 50, 0, 5, 5, 0, 5);
    }
    
    
    void Output::writeData()
    {
        h1_mu1_pT_gen->Write();
        h1_mu1_eta_gen->Write();
        h1_mu1_phi_gen->Write();
        
        h1_tau1_pT_gen->Write();
        h1_tau1_eta_gen->Write();
        h1_tau1_phi_gen->Write();
        
        h1_mu1_pT_reco->Write();
        h1_mu1_eta_reco->Write();
        h1_mu1_phi_reco->Write();
        
        h1_mu1_genMatched_pT_reco->Write();
        h1_mu1_genMatched_eta_reco->Write();
        h1_mu1_genMatched_phi_reco->Write();
        
        h1_mu1_resolution_pT->Write();
        
        h1_tauTau_isGenMatched->Write();
        
        h1_tau_isGenMatched->Write();
        
        h2_tau_n_gen_vs_reco->Write();
    }
    
    
    void Output::freeMemory()
    {
        delete h1_mu1_pT_gen;
        delete h1_mu1_eta_gen;
        delete h1_mu1_phi_gen;
        
        delete h1_tau1_pT_gen;
        delete h1_tau1_eta_gen;
        delete h1_tau1_phi_gen;
        
        delete h1_mu1_pT_reco;
        delete h1_mu1_eta_reco;
        delete h1_mu1_phi_reco;
        
        delete h1_mu1_genMatched_pT_reco;
        delete h1_mu1_genMatched_eta_reco;
        delete h1_mu1_genMatched_phi_reco;
        
        delete h1_mu1_resolution_pT;
        
        delete h1_tauTau_isGenMatched;
        
        delete h1_tau_isGenMatched;
        
        delete h2_tau_n_gen_vs_reco;
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName
    )
    {
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName);
        
        std::string inFile;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        sprintf(outDir, "%s", dir);
        
        sprintf(command, "mkdir -p %s", outDir);
        system(command);
        
        
        char treePath_gen[Common::str_len];
        char treePath_reco[Common::str_len];
        
        sprintf(treePath_gen, "miniaodsim2custom/gen");
        sprintf(treePath_reco, "miniaodsim2custom/reco");
        
        asymm_mt2_lester_bisect::disableCopyrightMessage();
        
        std::string tauID_WPname = "TightIsolationMVArun2v1DBdR03oldDMwLT";
        
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {
            //n++; if(n > 100) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFile.substr(inFile.rfind("/")+1, inFile.rfind(".root")-inFile.rfind("/")-1)).c_str());
            
            char outFile[Common::str_len];
            sprintf(outFile, "%s/%s_miscellaneous.root", outDir, fileNameStripped);
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("Output: %s \n", outFile);
            printf("\n");
            
            std::vector <const char*> v_object_mc_gen = {
                "genParam", "el", "mu", "tau_vis", "b", "jet", "MET"
            };
            
            std::vector <const char*> v_object_reco;
            
            v_object_reco = {
                "PU", "el", "mu", "tau", "jet", "MET"
            };
            
            CustomInfo_mc::Info *input_mc;
            
            input_mc = new CustomInfo_mc::Info(
                inFile.c_str(),
                treePath_gen, v_object_mc_gen,
                treePath_reco, v_object_reco,
                "read",
                0, 0,
                0, 0
            );
            
            // RECO histograms
            std::vector <const char*> v_outputOption_reco;
            
            v_outputOption_reco = {
                "mu", "muMu", "tau", "tauTau", "jet", "b", "MET"
            };
            
            
            Output *output = new Output();
            
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            // Analyze
            analyze(
                input_mc,
                output,
                tauID_WPname
            );
            
            printf("\n\n");
            
            
            // Write output
            //output_analyzed->mkdir("reco");
            //output_analyzed->cd("reco");
            
            output->writeData();
            
            
            // Release memory
            output->freeMemory();
            
            delete output;
            
            delete output_analyzed;
            
            input_mc->freeMemory();
            delete input_mc;
        }
    }
}

# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTable.h>
# include <TTree.h>
# include <TVector.h>

# include "lester_mt2_bisect_mod.h"

# include "Common.h"
# include "CustomInfo_mc.h"
# include "Output_GEN.h"
# include "Output_RECO.h"
# include "Analyze_singleTau.h"


namespace Analyze_singleTau
{
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY
    )
    {
        Analyze_singleTau::initialize(
            process,
            dir,
            otherInfoDir,
            isMC,
            isSUSY,
            std::make_pair(-1, -1),
            {}
        );
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1
    )
    {
        Analyze_singleTau::initialize(
            process,
            dir,
            otherInfoDir,
            isMC,
            isSUSY,
            massPoint_stop1_neutralino1,
            {}
        );
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY,
        std::vector <double> v_eventWeight_nJetBin
    )
    {
        Analyze_singleTau::initialize(
            process,
            dir,
            otherInfoDir,
            isMC,
            isSUSY,
            std::make_pair(-1, -1),
            v_eventWeight_nJetBin
        );
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        bool isMC,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::vector <double> v_eventWeight_nJetBin
    )
    {
        asymm_mt2_lester_bisect::disableCopyrightMessage();
        
        char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process, process);
        sprintf(sourceFileName, "sourceFiles/%s/%s_custom.txt", process, process);
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName);
        
        std::string inFile;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        sprintf(outDir, "%s/output_analyzed/%s", otherInfoDir, dir);
        
        sprintf(command, "mkdir -p %s", outDir);
        system(command);
        
        
        char treePath_gen[Common::str_len];
        char treePath_reco[Common::str_len];
        
        sprintf(treePath_gen, "miniaodsim2custom/gen");
        
        if(isMC)
        {
            sprintf(treePath_reco, "miniaodsim2custom/reco");
        }
        else
        {
            sprintf(treePath_reco, "miniaod2custom/reco");
        }
        
        char fileName_pileUp_mc[Common::str_len];
        sprintf(fileName_pileUp_mc, "%s/output_pileUp/%s/custom_all_pileUp.root", otherInfoDir, process);
        char histName_pileUp_mc[Common::str_len];
        sprintf(histName_pileUp_mc, "pileup");
        
        char fileName_pileUp_data[Common::str_len];
        //sprintf(fileName_pileUp_data, "../tauTau_data/output_pileUp/Tau/pileUpDistribution_2016H.root");
        sprintf(fileName_pileUp_data, "tauTau_data/output_pileUp/Tau/pileUpDistribution_2016H.root");
        char histName_pileUp_data[Common::str_len];
        sprintf(histName_pileUp_data, "pileup");
        
        char fileName_bTaggingEfficiency[Common::str_len];
        sprintf(fileName_bTaggingEfficiency, "output_bTaggingEfficiency/%s/bTaggingEfficiency.root", process);
        //BTagCalibration bTagCalib("CSVv2_Moriond17_B_H", "../resources/bTagging/CSVv2_Moriond17_B_H.csv");
        BTagCalibration bTagCalib("CSVv2_Moriond17_B_H", "resources/bTagging/CSVv2_Moriond17_B_H.csv");
        
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {
            //n++; if(n > 1) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFile.substr(inFile.rfind("/")+1, inFile.rfind(".root")-inFile.rfind("/")-1)).c_str());
            
            char outFile[Common::str_len];
            sprintf(outFile, "%s/%s_analyzed.root", outDir, fileNameStripped);
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("Output: %s \n", outFile);
            printf("\n");
            
            // Input root file
            std::vector <const char*> v_object_mc_gen = {
                "genParam", "el", "mu", "tau_vis", "b", "jet", "MET"};
            
            std::vector <const char*> v_object_reco;
            
            if(isMC)
            {
                v_object_reco = {
                    "PU", "el", "mu", "tau", "jet", "MET"};
            }
            
            else
            {
                v_object_reco = {
                    "el", "mu", "tau", "jet", "MET"};
            }
            
            
            CustomInfo_mc::Info *input_mc;
            CustomInfo_data::Info *input_data;
            
            if(isMC)
            {
                input_mc = new CustomInfo_mc::Info(
                    inFile.c_str(),
                    treePath_gen, v_object_mc_gen,
                    treePath_reco, v_object_reco,
                    "read",
                    fileName_pileUp_mc, histName_pileUp_mc,
                    fileName_pileUp_data, histName_pileUp_data);
            }
            
            else
            {
                input_data = new CustomInfo_data::Info(
                    inFile.c_str(),
                    treePath_reco, v_object_reco,
                    "read");
            }
            
            // RECO histograms
            std::vector <const char*> v_outputOption_reco;
            
            if(isMC)
            {
                v_outputOption_reco = {
                    "PU", "el", "mu", "tau", "tauTau", "jet", "b", "MET"};
            }
            
            else
            {
                v_outputOption_reco = {
                    "el", "mu", "tau", "tauTau", "jet", "b", "MET"};
            }
            
            
            Output_RECO::Output *output_reco = new Output_RECO::Output(v_outputOption_reco, "");
            
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            
            std::map <std::string, bool> m_eventSelection;
            
            //m_eventSelection["tau_n >= 2"] = false;
            m_eventSelection["MET_E_reco >= 80"] = false;
            m_eventSelection["tauTau_jet_HT_reco >= 100"] = false;
            m_eventSelection["b_n_reco >= 1"] = false;
            
            // Analyze
            if(isMC)
            {
                Analyze_singleTau::analyze_reco(
                    input_mc,
                    output_reco,
                    "tight", "OS",
                    m_eventSelection,
                    isMC, isSUSY,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    &bTagCalib,
                    fileName_bTaggingEfficiency
                );
            }
            
            else
            {
                Analyze_singleTau::analyze_reco(
                    input_data,
                    output_reco,
                    "loose", "SS",
                    m_eventSelection,
                    isMC, isSUSY,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    0,
                    ""
                );
            }
            
            printf("\n\n");
            
            output_analyzed->mkdir("reco");
            output_analyzed->cd("reco");
            
            output_reco->writeData();
            
            // Release memory
            output_reco->freeMemory();
            
            delete output_reco;
            
            delete output_analyzed;
            
            if(isMC)
            {
                input_mc->freeMemory();
                delete input_mc;
            }
            
            else
            {
                input_data->freeMemory();
                delete input_data;
            }
        }
    }
}

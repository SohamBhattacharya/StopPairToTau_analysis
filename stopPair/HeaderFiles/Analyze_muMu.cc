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

# include "Analyze_muMu.h"
# include "Common.h"
# include "CustomInfo_mc.h"
# include "CustomInfo_data.h"
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
    )
    {
        Analyze_muMu::initialize(
            process,
            dir,
            otherInfoDir,
            sourceFileName,
            era,
            isMC,
            {},
            m_correction
        );
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        const char *era,
        bool isMC,
        std::vector <double> v_eventWeight_nJetBin,
        std::map <std::string, bool> m_correction
        
    )
    {
        printf("\n");
        printf("********** Era: %s ********** \n", era);
        printf("\n");
        
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process, process);
        
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
        
        if(isMC)
        {
            sprintf(treePath_reco, "miniaodsim2custom/reco");
        }
        else
        {
            sprintf(treePath_reco, "miniaod2custom/reco");
        }
        
        
        char fileName_pileUp_data[Common::str_len];
        //sprintf(fileName_pileUp_data, "../tauTau_data/output_pileUp/Tau/pileUpDistribution_2016H.root");
        
        char histName_pileUp_data[Common::str_len];
        sprintf(histName_pileUp_data, "pileup");
        
        char fileName_muIdIsoSF[Common::str_len];
        
        std::map <std::string, ElMuScaleFactor::ScaleFactor*> m_muTriggerSFobject;
        
        char fileName_bTagCalib[Common::str_len];
        
        char fileName_htt_scaleFactor[Common::str_len];
        
        // Era
        if(!strcmp(era, "2016"))
        {
            //sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.root");
            
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.root");
            
            sprintf(fileName_muIdIsoSF, "resources/muonSF/2016/Muon_IdIso_IsoLt0p2_2016BtoH_eff_update1407.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2016/CSVv2_Moriond17_B_H.csv");
            
            sprintf(fileName_htt_scaleFactor, "resources/htt_scalefactors_v16_5_2.root");
            
            m_muTriggerSFobject = {
                {"IsoMu24_OR_TkIsoMu24", new ElMuScaleFactor::ScaleFactor()}
            };
            
            m_muTriggerSFobject.at("IsoMu24_OR_TkIsoMu24")->init_ScaleFactor("resources/muonSF/2016/Muon_IsoMu24_OR_TkIsoMu24_2016BtoH_eff.root");
        }
        
        else if(!strcmp(era, "2017"))
        {
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.root");
            
            sprintf(fileName_muIdIsoSF, "resources/muonSF/2017/Muon_IdIso_IsoLt0.2_eff.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2017/CSVv2_94XSF_V2_B_F.csv");
            
            sprintf(fileName_htt_scaleFactor, "resources/htt_scalefactors_2017_v2.root");
            
            m_muTriggerSFobject = {
                {"IsoMu24_OR_IsoMu27", new ElMuScaleFactor::ScaleFactor()}
            };
            
            m_muTriggerSFobject.at("IsoMu24_OR_IsoMu27")->init_ScaleFactor("resources/muonSF/2017/Muon_IsoMu24orIsoMu27.root");
        }
        
        else
        {
            printf("Error in Analyze_muMu::initialize(...): Provide a valid era (2016/2017). Provided era: %s", era);
            exit(EXIT_FAILURE);
        }
        
        // Remember to delete
        ElMuScaleFactor::ScaleFactor *muIdIsoSFobject = new ElMuScaleFactor::ScaleFactor();
        muIdIsoSFobject->init_ScaleFactor(fileName_muIdIsoSF);
        
        
        char fileName_pileUp_mc[Common::str_len];
        sprintf(fileName_pileUp_mc, "%s/output_pileUp/%s/custom_all_pileUp.root", otherInfoDir, process);
        char histName_pileUp_mc[Common::str_len];
        sprintf(histName_pileUp_mc, "pileup");
        
        char fileName_bTaggingEfficiency[Common::str_len];
        sprintf(fileName_bTaggingEfficiency, "%s/output_bTaggingEfficiency/%s_bTaggingEfficiency/bTaggingEfficiency.root", otherInfoDir, process);
        BTagCalibration bTagCalib;
        
        if(!strcmp(era, "2016"))
        {
            bTagCalib = BTagCalibration("CSVv2", fileName_bTagCalib);
        }
        
        else if(!strcmp(era, "2017"))
        {
            bTagCalib = BTagCalibration("CSVv2", fileName_bTagCalib);
        }
        
        
        TFile *htt_scaleFactorFile = TFile::Open(fileName_htt_scaleFactor);
        RooWorkspace *htt_scaleFactorWS = (RooWorkspace*) htt_scaleFactorFile->Get("w");
        htt_scaleFactorFile->Close();
        
        
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
            
            std::vector <const char*> v_object_mc_gen = { \
                "genParam", "t", "Z", "el", "mu", "tau_vis", "b", "jet", "MET"};
            
            std::vector <const char*> v_object_reco;
            
            if(isMC)
            {
                v_object_reco = { \
                    "PU", "el", "mu", "tau", "jet", "MET", "trigger"};
            }
            
            else
            {
                v_object_reco = { \
                    "el", "mu", "tau", "jet", "MET", "trigger"};
            }
            
            CustomInfo_mc::Info *input_mc;
            CustomInfo_data::Info *input_data;
            
            if(isMC)
            {
                //if(!strcmp(era, "2017"))
                //{
                //    input_mc = new CustomInfo_mc::Info(
                //        inFile.c_str(),
                //        treePath_gen, v_object_mc_gen,
                //        treePath_reco, v_object_reco,
                //        "read",
                //        0, 0,
                //        0, 0
                //    );
                //}
                //
                //else
                {
                    input_mc = new CustomInfo_mc::Info(
                        inFile.c_str(),
                        treePath_gen, v_object_mc_gen,
                        treePath_reco, v_object_reco,
                        "read",
                        fileName_pileUp_mc, histName_pileUp_mc,
                        fileName_pileUp_data, histName_pileUp_data
                    );
                }
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
                v_outputOption_reco = { \
                    "PU", "el", "mu", "muMu", "jet", "b", "MET"};
            }
            
            else
            {
                v_outputOption_reco = { \
                    "el", "mu", "muMu", "jet", "b", "MET"};
            }
            
            std::string eventSelectionStr_baselineCRB = 
                "(muMu_m < 60 or muMu_m > 120) and "
                "MET_E_reco >= 50 and "
                "muMu_jet_HT_reco >= 100 and "
                "b_n_reco >= 1";
            
            std::string eventSelectionStr_baselineDYCR = 
                "(muMu_m > 80 and muMu_m < 100) and "
                "MET_E_reco >= 30 and "
                "muMu_jet_HT_reco >= 100 and "
                "b_n_reco == 0";
            
            
            Output_RECO::Output *output_reco_OS = new Output_RECO::Output(v_outputOption_reco, "OS");
            //Output_RECO::Output *output_reco_OS_DzetaCut = new Output_RECO::Output(v_outputOption_reco, "OS_muMu_DzetaCut");
            //Output_RECO::Output *output_reco_OS_METcut = new Output_RECO::Output(v_outputOption_reco, "OS_METcut");
            //Output_RECO::Output *output_reco_OS_muMu_mCut = new Output_RECO::Output(v_outputOption_reco, "OS_muMu_mCut");
            
            Output_RECO::Output *output_reco_OS_baselineTTCRB = new Output_RECO::Output(v_outputOption_reco, "OS_baselineTTCRB");
            Output_RECO::Output *output_reco_OS_baselineDYCR = new Output_RECO::Output(v_outputOption_reco, "OS_baselineDYCR");
            
            //Output_RECO::Output *output_reco_OS_CSVv2Mcut2 = new Output_RECO::Output(v_outputOption_reco, "OS_CSVv2Mcut2");
            
            //Output_RECO::Output *output_reco_mediumMedium_OS = new Output_RECO::Output(v_outputOption_reco, "mediumMedium_OS");
            //Output_RECO::Output *output_reco_mediumMedium_OS_baselineSRB = new Output_RECO::Output(v_outputOption_reco, "mediumMedium_OS_baselineSRB");
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            std::map <std::string, bool> m_eventSelection;
            
            //m_eventSelection["muMu_Dzeta < -35"] = false;
            //m_eventSelection["MET > 80"] = false;
            //m_eventSelection["muMu_m > 90"] = false;
            //m_eventSelection["b_n >= 1"] = false;
            //m_eventSelection["b_n >= 2"] = false;
            
            m_eventSelection["MET_E_reco >= 80"] = false;
            m_eventSelection["muMu_jet_HT_reco >= 100"] = false;
            m_eventSelection["b_n_reco >= 1"] = false;
            
            
            //output_reco_mediumMedium_OS->addCutFlow(6, "cutFlow_ttbar_muMu_CR");
            
            for(int iCRA = 0; iCRA < 6; iCRA++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "CRA%d", iCRA+1);
                
                output_reco_OS->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
                output_reco_OS_baselineTTCRB->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
                output_reco_OS_baselineDYCR->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
                
                //output_reco_mediumMedium_OS->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
                //output_reco_mediumMedium_OS_baselineSRB->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
            }
            
            for(int iCRB = 0; iCRB < 18; iCRB++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "CRB%d", iCRB+1);
                
                output_reco_OS->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
                output_reco_OS_baselineTTCRB->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
                output_reco_OS_baselineDYCR->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
                
                //output_reco_mediumMedium_OS->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
                //output_reco_mediumMedium_OS_baselineSRB->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
            }
            
            for(int iDYCR = 0; iDYCR < 18; iDYCR++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "DYCR%d", iDYCR+1);
                
                output_reco_OS->addCutFlow(7, "DYCR"+std::to_string(iDYCR+1));
                output_reco_OS_baselineTTCRB->addCutFlow(7, "DYCR"+std::to_string(iDYCR+1));
                output_reco_OS_baselineDYCR->addCutFlow(7, "DYCR"+std::to_string(iDYCR+1));
                
                //output_reco_mediumMedium_OS->addCutFlow(7, "DYCR"+std::to_string(iDYCR+1));
                //output_reco_mediumMedium_OS_baselineSRB->addCutFlow(7, "DYCR"+std::to_string(iDYCR+1));
            }
            
            
            // Analyze
            if(isMC)
            {
                /////Analyze_muMu::analyze_reco(
                /////    input_mc,
                /////    output_reco_OS,
                /////    "OS",
                /////    m_eventSelection,
                /////    "",
                /////    isMC,
                /////    era,
                /////    v_eventWeight_nJetBin,
                /////    &bTagCalib,
                /////    fileName_bTaggingEfficiency,
                /////    muIdIsoSFobject,
                /////    &m_muTriggerSFobject,
                /////    m_correction,
                /////    htt_scaleFactorWS
                /////);
                /////
                /////Analyze_muMu::analyze_reco(
                /////    input_mc,
                /////    output_reco_OS_baselineTTCRB,
                /////    "OS",
                /////    m_eventSelection,
                /////    eventSelectionStr_baselineCRB,
                /////    isMC,
                /////    era,
                /////    v_eventWeight_nJetBin,
                /////    &bTagCalib,
                /////    fileName_bTaggingEfficiency,
                /////    muIdIsoSFobject,
                /////    &m_muTriggerSFobject,
                /////    m_correction,
                /////    htt_scaleFactorWS
                /////);
                
                Analyze_muMu::analyze_reco(
                    input_mc,
                    output_reco_OS_baselineDYCR,
                    "OS",
                    m_eventSelection,
                    eventSelectionStr_baselineDYCR,
                    isMC,
                    era,
                    v_eventWeight_nJetBin,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    m_correction,
                    htt_scaleFactorWS
                );
                
                //Analyze_muMu::analyze_reco(
                //    input_mc,
                //    output_reco_mediumMedium_OS,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    muIdIsoSFobject
                //);
                //
                //
                //m_eventSelection["MET_E_reco >= 80"] = true;
                //m_eventSelection["muMu_jet_HT_reco >= 100"] = true;
                //m_eventSelection["b_n_reco >= 1"] = true;
                //
                //Analyze_muMu::analyze_reco(
                //    input_mc,
                //    output_reco_mediumMedium_OS_baselineSRB,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    muIdIsoSFobject
                //);
            }
            
            else
            {
                /////Analyze_muMu::analyze_reco(
                /////    input_data,
                /////    output_reco_OS,
                /////    "OS",
                /////    m_eventSelection,
                /////    "",
                /////    isMC,
                /////    era,
                /////    v_eventWeight_nJetBin,
                /////    &bTagCalib,
                /////    fileName_bTaggingEfficiency,
                /////    muIdIsoSFobject,
                /////    &m_muTriggerSFobject,
                /////    m_correction,
                /////    htt_scaleFactorWS
                /////);
                /////
                /////Analyze_muMu::analyze_reco(
                /////    input_data,
                /////    output_reco_OS_baselineTTCRB,
                /////    "OS",
                /////    m_eventSelection,
                /////    eventSelectionStr_baselineCRB,
                /////    isMC,
                /////    era,
                /////    v_eventWeight_nJetBin,
                /////    &bTagCalib,
                /////    fileName_bTaggingEfficiency,
                /////    muIdIsoSFobject,
                /////    &m_muTriggerSFobject,
                /////    m_correction,
                /////    htt_scaleFactorWS
                /////);
                
                Analyze_muMu::analyze_reco(
                    input_data,
                    output_reco_OS_baselineDYCR,
                    "OS",
                    m_eventSelection,
                    eventSelectionStr_baselineDYCR,
                    isMC,
                    era,
                    v_eventWeight_nJetBin,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    m_correction,
                    htt_scaleFactorWS
                );
                
                //Analyze_muMu::analyze_reco(
                //    input_data,
                //    output_reco_mediumMedium_OS,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    muIdIsoSFobject
                //);
                //
                //
                //m_eventSelection["MET_E_reco >= 80"] = true;
                //m_eventSelection["muMu_jet_HT_reco >= 100"] = true;
                //m_eventSelection["b_n_reco >= 1"] = true;
                //
                //Analyze_muMu::analyze_reco(
                //    input_data,
                //    output_reco_mediumMedium_OS_baselineSRB,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    muIdIsoSFobject
                //);
            }
            
            printf("\n\n");
            
            
            // Write output
            output_analyzed->mkdir("reco");
            //output_analyzed->cd("reco");
            
            char dirName[Common::str_len];
            
            sprintf(dirName, "reco/%s", output_reco_OS->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            output_reco_OS->writeData();
            
            sprintf(dirName, "reco/%s", output_reco_OS_baselineTTCRB->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            output_reco_OS_baselineTTCRB->writeData();
            
            sprintf(dirName, "reco/%s", output_reco_OS_baselineDYCR->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            output_reco_OS_baselineDYCR->writeData();
            
            //output_reco_mediumMedium_OS->writeData();
            //output_reco_mediumMedium_OS_baselineSRB->writeData();
            
            
            // Release memory
            output_reco_OS->freeMemory();
            output_reco_OS_baselineTTCRB->freeMemory();
            
            output_reco_OS_baselineDYCR->freeMemory();
            
            //output_reco_mediumMedium_OS->freeMemory();
            //output_reco_mediumMedium_OS_baselineSRB->freeMemory();
            
            delete output_reco_OS;
            delete output_reco_OS_baselineTTCRB;
            
            delete output_reco_OS_baselineDYCR;
            
            //delete output_reco_mediumMedium_OS;
            //delete output_reco_mediumMedium_OS_baselineSRB;
            
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
        
        delete muIdIsoSFobject;
        
        for(auto iter = m_muTriggerSFobject.begin(); iter != m_muTriggerSFobject.end(); iter++)
        {
            delete iter->second;
        }
    }
}

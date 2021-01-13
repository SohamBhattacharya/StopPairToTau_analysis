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

# include "Analyze_elMu.h"
# include "Common.h"
# include "CustomInfo_mc.h"
# include "CustomInfo_data.h"
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
    )
    {
        Analyze_elMu::initialize(
            process,
            dir,
            otherInfoDir,
            sourceFileName,
            era,
            isMC,
            isSUSY,
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
        bool isSUSY,
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
        
        
        char fileName_massPointInfo[Common::str_len];
        std::vector <std::vector <double> > vv_massPointInfo;
        
        if(isSUSY)
        {
            sprintf(fileName_massPointInfo, "%s/output_genParam/%s/massPointInfo.txt", otherInfoDir, process);
            printf("Mass-point info file: %s \n", fileName_massPointInfo);
            fflush(stdout);
            
            Common::parseCSVto2Dvector(std::string(fileName_massPointInfo), &vv_massPointInfo);
            
            printf("# mass-point: %d \n", vv_massPointInfo.size());
            fflush(stdout);
        }
        
        
        char fileName_pileUp_data[Common::str_len];
        //sprintf(fileName_pileUp_data, "../tauTau_data/output_pileUp/Tau/pileUpDistribution_2016H.root");
        
        char histName_pileUp_data[Common::str_len];
        sprintf(histName_pileUp_data, "pileup");
        
        char fileName_elIdIsoSF[Common::str_len];
        char fileName_muIdIsoSF[Common::str_len];
        
        std::map <std::string, ElMuScaleFactor::ScaleFactor*> m_elMuTriggerSFobject;
        
        char fileName_bTagCalib[Common::str_len];
        
        TFile *htt_scaleFactorFile = TFile::Open("resources/htt_scalefactors_2017_v2.root");
        RooWorkspace *htt_scaleFactorWS = (RooWorkspace*) htt_scaleFactorFile->Get("w");
        htt_scaleFactorFile->Close();
        
        // Era
        if(!strcmp(era, "2016"))
        {
            //sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.root");
            
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.root");
            
            sprintf(fileName_elIdIsoSF, "resources/electronSF/2016/Electron_IdIso_IsoLt0p15_eff.root");
            sprintf(fileName_muIdIsoSF, "resources/muonSF/2016/Muon_IdIso_IsoLt0p2_2016BtoH_eff_update1407.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2016/CSVv2_Moriond17_B_H.csv");
            
            m_elMuTriggerSFobject = {
                {"Ele12leg", new ElMuScaleFactor::ScaleFactor()},
                {"Ele23leg", new ElMuScaleFactor::ScaleFactor()},
                {"Mu8leg", new ElMuScaleFactor::ScaleFactor()},
                {"Mu23leg", new ElMuScaleFactor::ScaleFactor()},
            };
            
            m_elMuTriggerSFobject.at("Ele12leg")->init_ScaleFactor("resources/electronSF/2016/Electron_Ele12leg_eff.root");
            m_elMuTriggerSFobject.at("Ele23leg")->init_ScaleFactor("resources/electronSF/2016/Electron_Ele23leg_eff.root");
            m_elMuTriggerSFobject.at("Mu8leg")->init_ScaleFactor("resources/muonSF/2016/Muon_Mu8leg_2016BtoH_eff.root");
            m_elMuTriggerSFobject.at("Mu23leg")->init_ScaleFactor("resources/muonSF/2016/Muon_Mu23leg_2016BtoH_eff.root");
            
            if(isSUSY)
            {
                sprintf(fileName_bTagCalib, "resources/bTagging/2016/fastsim_csvv2_ttbar_26_1_2017.csv");
            }
        }
        
        else if(!strcmp(era, "2017"))
        {
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.root");
            
            //sprintf(fileName_elIdIsoSF, "resources/electronSF/2017/Electron_IdIso_IsoLt0.15_IsoID_eff.root");
            sprintf(fileName_elIdIsoSF, "resources/electronSF/2017/Electron_IdIso_IsoLt0.15_noIsoID_eff.root");
            sprintf(fileName_muIdIsoSF, "resources/muonSF/2017/Muon_IdIso_IsoLt0.2_eff.root");
            
            //sprintf(fileName_bTagCalib, "resources/bTagging/2016/CSVv2_Moriond17_B_H.csv");
            sprintf(fileName_bTagCalib, "resources/bTagging/2017/CSVv2_94XSF_V2_B_F.csv");
            
            //m_elMuTriggerSFobject = {
            //    {"Ele12leg", new ElMuScaleFactor::ScaleFactor()},
            //    {"Ele23leg", new ElMuScaleFactor::ScaleFactor()},
            //    {"Mu8leg", new ElMuScaleFactor::ScaleFactor()},
            //    {"Mu23leg", new ElMuScaleFactor::ScaleFactor()},
            //};
            //
            //m_elMuTriggerSFobject.at("Ele12leg")->init_ScaleFactor("resources/electronSF/2017/Electron_Ele12_eff_2017.root");
            //m_elMuTriggerSFobject.at("Ele23leg")->init_ScaleFactor("resources/electronSF/2017/Electron_Ele23_eff_2017.root");
            //m_elMuTriggerSFobject.at("Mu8leg")->init_ScaleFactor("resources/muonSF/2017/Muon_Mu8_eff_2017.root");
            //m_elMuTriggerSFobject.at("Mu23leg")->init_ScaleFactor("resources/muonSF/2017/Muon_Mu23_eff_2017.root");
            
            
        }
        
        else
        {
            printf("Error in Analyze_elMu::initialize(...): Provide a valid era (2016/2017). Provided era: %s", era);
            exit(EXIT_FAILURE);
        }
        
        // Remember to delete
        ElMuScaleFactor::ScaleFactor *elIdIsoSFobject = new ElMuScaleFactor::ScaleFactor();
        elIdIsoSFobject->init_ScaleFactor(fileName_elIdIsoSF);
        
        ElMuScaleFactor::ScaleFactor *muIdIsoSFobject = new ElMuScaleFactor::ScaleFactor();
        muIdIsoSFobject->init_ScaleFactor(fileName_muIdIsoSF);
        
        
        char fileName_pileUp_mc[Common::str_len];
        sprintf(fileName_pileUp_mc, "%s/output_pileUp/%s/custom_all_pileUp.root", otherInfoDir, process);
        ////////// CHANGE NAMING OF 2016 LATER //////////
        if(!strcmp(era, "2017"))
        {
            sprintf(fileName_pileUp_mc, "%s/output_pileUp/%s_pileUp/custom_all_pileUp.root", otherInfoDir, process);
        }
        /////////////////////////////////////////////////
        
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
        
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {
            //n++; if(n > 10) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFile.substr(inFile.rfind("/")+1, inFile.rfind(".root")-inFile.rfind("/")-1)).c_str());
            
            char outFile[Common::str_len];
            sprintf(outFile, "%s/%s_analyzed.root", outDir, fileNameStripped);
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("Output: %s \n", outFile);
            printf("\n");
            
            std::vector <const char*> v_object_mc_gen = { \
                "genParam", "t", "el", "mu", "tau_vis", "b", "jet", "MET"};
            
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
                    "PU", "el", "mu", "elMu", "jet", "b", "MET"};
            }
            
            else
            {
                v_outputOption_reco = { \
                    "el", "mu", "elMu", "jet", "b", "MET"};
            }
            
            std::string eventSelectionStr_baselineCRB = 
                "(elMu_m < 60 or elMu_m > 120) and "
                "MET_E_reco >= 50 and "
                "elMu_jet_HT_reco >= 100 and "
                "b_n_reco >= 1";
            
            
            Output_RECO::Output *output_reco_OS = new Output_RECO::Output(v_outputOption_reco, "OS");
            //Output_RECO::Output *output_reco_OS_DzetaCut = new Output_RECO::Output(v_outputOption_reco, "OS_elMu_DzetaCut");
            //Output_RECO::Output *output_reco_OS_METcut = new Output_RECO::Output(v_outputOption_reco, "OS_METcut");
            //Output_RECO::Output *output_reco_OS_elMu_mCut = new Output_RECO::Output(v_outputOption_reco, "OS_elMu_mCut");
            
            Output_RECO::Output *output_reco_OS_baselineTTCRB = new Output_RECO::Output(v_outputOption_reco, "OS_baselineTTCRB");
            
            //Output_RECO::Output *output_reco_OS_CSVv2Mcut2 = new Output_RECO::Output(v_outputOption_reco, "OS_CSVv2Mcut2");
            
            
            std::map <std::pair <int, int>, Output_RECO::Output*> m_output_reco_stopPair_OS_genMatched_baselineTTCRB;
            
            if(isSUSY)
            {
                for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                {
                    std::pair <int, int> p_temp(
                        (int) vv_massPointInfo.at(iMassPoint).at(0),
                        (int) vv_massPointInfo.at(iMassPoint).at(1)
                    );
                    
                    //printf("Initializing mass-point [%d, %d]. \n", p_temp.first, p_temp.second);
                    
                    char details_temp[Common::str_len];
                    
                    sprintf(details_temp, "%s_%d_%d", "OS_genMatched_baselineTTCRB", p_temp.first, p_temp.second);
                    m_output_reco_stopPair_OS_genMatched_baselineTTCRB[p_temp] = new Output_RECO::Output(v_outputOption_reco, details_temp);
                }
            }
            
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            std::map <std::string, bool> m_eventSelection;
            
            m_eventSelection["elMu_Dzeta < -35"] = false;
            m_eventSelection["MET > 80"] = false;
            m_eventSelection["elMu_m > 90"] = false;
            m_eventSelection["b_n >= 1"] = false;
            //m_eventSelection["b_n >= 2"] = false;
            
            
            output_reco_OS->addCutFlow(6, "cutFlow_ttbar_elMu_CR");
            //output_reco_OS_DzetaCut->addCutFlow(6, "cutFlow_ttbar_elMu_CR");
            //output_reco_OS_METcut->addCutFlow(6, "cutFlow_ttbar_elMu_CR");
            //output_reco_OS_elMu_mCut->addCutFlow(6, "cutFlow_ttbar_elMu_CR");
            output_reco_OS_baselineTTCRB->addCutFlow(6, "cutFlow_ttbar_elMu_CR");
            //output_reco_OS_CSVv2Mcut2->addCutFlow(7, "cutFlow_ttbar_elMu_CR");
            
            for(int iCRA = 0; iCRA < 6; iCRA++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "CRA%d", iCRA+1);
                
                output_reco_OS->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
                output_reco_OS_baselineTTCRB->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
                
                if(isSUSY)
                {
                    for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                    {
                        std::pair <int, int> p_temp(
                            (int) vv_massPointInfo.at(iMassPoint).at(0),
                            (int) vv_massPointInfo.at(iMassPoint).at(1)
                        );
                        
                        m_output_reco_stopPair_OS_genMatched_baselineTTCRB.at(p_temp)->addCutFlow(6, "CRA"+std::to_string(iCRA+1));
                    }
                }
            }
            
            for(int iCRB = 0; iCRB < 18; iCRB++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "CRB%d", iCRB+1);
                
                output_reco_OS->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
                output_reco_OS_baselineTTCRB->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
                
                if(isSUSY)
                {
                    for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                    {
                        std::pair <int, int> p_temp(
                            (int) vv_massPointInfo.at(iMassPoint).at(0),
                            (int) vv_massPointInfo.at(iMassPoint).at(1)
                        );
                        
                        m_output_reco_stopPair_OS_genMatched_baselineTTCRB.at(p_temp)->addCutFlow(7, "CRB"+std::to_string(iCRB+1));
                    }
                }
            }
            
            
            // Analyze
            if(isMC)
            {
                if(!isSUSY)
                {
                    Analyze_elMu::analyze_reco(
                        input_mc,
                        output_reco_OS,
                        0,
                        "OS",
                        m_eventSelection,
                        "",
                        isMC,
                        isSUSY,
                        era,
                        v_eventWeight_nJetBin,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        elIdIsoSFobject,
                        muIdIsoSFobject,
                        &m_elMuTriggerSFobject,
                        htt_scaleFactorWS,
                        m_correction
                    );
                    
                    //m_eventSelection.find("elMu_Dzeta < -35")->second = true;
                    
                    //Analyze_elMu::analyze_reco(
                    //    input_mc,
                    //    output_reco_OS_DzetaCut,
                    //    "OS", m_eventSelection, isMC,
                    //    v_eventWeight_nJetBin,
                    //    &bTagCalib,
                    //    fileName_bTaggingEfficiency,
                    //    elIdIsoSFobject,
                    //    muIdIsoSFobject
                    //);
                    
                    //m_eventSelection.find("MET > 80")->second = true;
                    
                    //Analyze_elMu::analyze_reco(
                    //    input_mc,
                    //    output_reco_OS_METcut,
                    //    "OS", m_eventSelection, isMC,
                    //    v_eventWeight_nJetBin,
                    //    &bTagCalib,
                    //    fileName_bTaggingEfficiency,
                    //    elIdIsoSFobject,
                    //    muIdIsoSFobject
                    //);
                    
                    //m_eventSelection.find("elMu_m > 90")->second = true;
                    
                    //Analyze_elMu::analyze_reco(
                    //    input_mc,
                    //    output_reco_OS_elMu_mCut,
                    //    "OS", m_eventSelection, isMC,
                    //    v_eventWeight_nJetBin,
                    //    &bTagCalib,
                    //    fileName_bTaggingEfficiency,
                    //    elIdIsoSFobject,
                    //    muIdIsoSFobject
                    //);
                    
                    //m_eventSelection.find("b_n >= 1")->second = true;
                    
                    Analyze_elMu::analyze_reco(
                        input_mc,
                        output_reco_OS_baselineTTCRB,
                        0,
                        "OS",
                        m_eventSelection,
                        eventSelectionStr_baselineCRB,
                        isMC,
                        isSUSY,
                        era,
                        v_eventWeight_nJetBin,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        elIdIsoSFobject,
                        muIdIsoSFobject,
                        &m_elMuTriggerSFobject,
                        htt_scaleFactorWS,
                        m_correction
                    );
                    
                    //m_eventSelection.find("b_n >= 2")->second = true;
                    //
                    //Analyze_elMu::analyze_reco(
                    //    input_mc,
                    //    output_reco_OS_CSVv2Mcut2,
                    //    "OS", m_eventSelection, isMC,
                    //    v_eventWeight_nJetBin,
                    //    &bTagCalib,
                    //    fileName_bTaggingEfficiency,
                    //    elIdIsoSFobject,
                    //    muIdIsoSFobject
                    //);
                }
                
                if(isSUSY)
                {
                    Analyze_elMu::analyze_reco(
                        input_mc,
                        0,
                        &m_output_reco_stopPair_OS_genMatched_baselineTTCRB,
                        "OS",
                        m_eventSelection,
                        eventSelectionStr_baselineCRB,
                        isMC,
                        isSUSY,
                        era,
                        v_eventWeight_nJetBin,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        elIdIsoSFobject,
                        muIdIsoSFobject,
                        &m_elMuTriggerSFobject,
                        htt_scaleFactorWS,
                        m_correction,
                        true, 0.4,
                        true, 0.4
                    );
                }
            }
            
            else
            {
                Analyze_elMu::analyze_reco(
                    input_data,
                    output_reco_OS,
                    0,
                    "OS",
                    m_eventSelection,
                    "",
                    isMC,
                    isSUSY,
                    era,
                    v_eventWeight_nJetBin,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    elIdIsoSFobject,
                    muIdIsoSFobject,
                    &m_elMuTriggerSFobject,
                    htt_scaleFactorWS,
                    m_correction
                );
                
                //m_eventSelection["elMu_Dzeta < -35"] = true;
                
                //Analyze_elMu::analyze_reco(
                //    input_data,
                //    output_reco_OS_DzetaCut,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    elIdIsoSFobject,
                //    muIdIsoSFobject
                //);
                
                //m_eventSelection["MET > 80"] = true;
                
                //Analyze_elMu::analyze_reco(
                //    input_data,
                //    output_reco_OS_METcut,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    elIdIsoSFobject,
                //    muIdIsoSFobject
                //);
                
                //m_eventSelection["elMu_m > 90"] = true;
                
                //Analyze_elMu::analyze_reco(
                //    input_data,
                //    output_reco_OS_elMu_mCut,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    elIdIsoSFobject,
                //    muIdIsoSFobject
                //);
                
                //m_eventSelection["b_n >= 1"] = true;
                
                Analyze_elMu::analyze_reco(
                    input_data,
                    output_reco_OS_baselineTTCRB,
                    0,
                    "OS",
                    m_eventSelection,
                    eventSelectionStr_baselineCRB,
                    isMC,
                    isSUSY,
                    era,
                    v_eventWeight_nJetBin,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    elIdIsoSFobject,
                    muIdIsoSFobject,
                    &m_elMuTriggerSFobject,
                    htt_scaleFactorWS,
                    m_correction
                );
                
                //m_eventSelection["b_n >= 2"] = true;
                //
                //Analyze_elMu::analyze_reco(
                //    input_data,
                //    output_reco_OS_CSVv2Mcut2,
                //    "OS", m_eventSelection, isMC,
                //    v_eventWeight_nJetBin,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    elIdIsoSFobject,
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
            
            //output_reco_OS_DzetaCut->writeData();
            //output_reco_OS_METcut->writeData();
            //output_reco_OS_elMu_mCut->writeData();
            
            sprintf(dirName, "reco/%s", output_reco_OS_baselineTTCRB->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            output_reco_OS_baselineTTCRB->writeData();
            
            //output_reco_OS_CSVv2Mcut2->writeData();
            
            if(isSUSY)
            {
                for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                {
                    std::pair <int, int> p_temp(
                        (int) vv_massPointInfo.at(iMassPoint).at(0),
                        (int) vv_massPointInfo.at(iMassPoint).at(1)
                    );
                    
                    sprintf(dirName, "reco/%s", m_output_reco_stopPair_OS_genMatched_baselineTTCRB.at(p_temp)->details);
                    output_analyzed->mkdir(dirName);
                    output_analyzed->cd(dirName);
                    m_output_reco_stopPair_OS_genMatched_baselineTTCRB.at(p_temp)->writeData();
                }
            }
            
            
            // Write cut-flows
            //char cutFlow_outDir[Common::str_len];
            //char cutFlow_outFile[Common::str_len];
            //
            //sprintf(cutFlow_outDir, "%s/cutFlow_ttbar_elMu_CR", outDir);
            //sprintf(cutFlow_outFile, "%s/%s_cutFlow.txt", cutFlow_outDir, fileNameStripped);
            //system(("mkdir -p " + std::string(cutFlow_outDir)).c_str());
            ////output_reco_OS_CSVv2Mcut2->writeCutFlow("cutFlow_ttbar_elMu_CR", cutFlow_outFile);
            //output_reco_OS_baselineTTCRB->writeCutFlow("cutFlow_ttbar_elMu_CR", cutFlow_outFile);
            //
            //for(int iCRA = 0; iCRA < 6; iCRA++)
            //{
            //    std::string tempStr = "CRA"+std::to_string(iCRA+1);
            //    
            //    sprintf(cutFlow_outDir, "%s/cutFlow_CRA%d", outDir, iCRA+1);
            //    sprintf(cutFlow_outFile, "%s/%s_cutFlow.txt", cutFlow_outDir, fileNameStripped);
            //    system(("mkdir -p " + std::string(cutFlow_outDir)).c_str());
            //    output_reco_OS_baselineTTCRB->writeCutFlow(tempStr, cutFlow_outFile);
            //}
            //
            //for(int iCRB = 0; iCRB < 18; iCRB++)
            //{
            //    std::string tempStr = "CRB"+std::to_string(iCRB+1);
            //    
            //    sprintf(cutFlow_outDir, "%s/cutFlow_CRB%d", outDir, iCRB+1);
            //    sprintf(cutFlow_outFile, "%s/%s_cutFlow.txt", cutFlow_outDir, fileNameStripped);
            //    system(("mkdir -p " + std::string(cutFlow_outDir)).c_str());
            //    output_reco_OS_baselineTTCRB->writeCutFlow(tempStr, cutFlow_outFile);
            //}
            
            
            // Release memory
            output_reco_OS->freeMemory();
            //output_reco_OS_DzetaCut->freeMemory();
            //output_reco_OS_METcut->freeMemory();
            //output_reco_OS_elMu_mCut->freeMemory();
            output_reco_OS_baselineTTCRB->freeMemory();
            //output_reco_OS_CSVv2Mcut2->freeMemory();
            
            if(isSUSY)
            {
                for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                {
                    std::pair <int, int> p_temp(
                        (int) vv_massPointInfo.at(iMassPoint).at(0),
                        (int) vv_massPointInfo.at(iMassPoint).at(1)
                    );
                    
                    m_output_reco_stopPair_OS_genMatched_baselineTTCRB.at(p_temp)->freeMemory();
                }
            }
            
            
            delete output_reco_OS;
            //delete output_reco_OS_DzetaCut;
            //delete output_reco_OS_METcut;
            //delete output_reco_OS_elMu_mCut;
            delete output_reco_OS_baselineTTCRB;
            //delete output_reco_OS_CSVv2Mcut2;
            
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
            
            if(isSUSY)
            {
                for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                {
                    std::pair <int, int> p_temp(
                        (int) vv_massPointInfo.at(iMassPoint).at(0),
                        (int) vv_massPointInfo.at(iMassPoint).at(1)
                    );
                    
                    delete m_output_reco_stopPair_OS_genMatched_baselineTTCRB.at(p_temp);
                }
            }
        }
        
        delete elIdIsoSFobject;
        delete muIdIsoSFobject;
        
        for(auto iter = m_elMuTriggerSFobject.begin(); iter != m_elMuTriggerSFobject.end(); iter++)
        {
            delete iter->second;
        }
    }

}

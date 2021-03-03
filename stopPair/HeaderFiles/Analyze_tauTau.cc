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

# include "Analyze_tauTau.h"
# include "Common.h"
# include "CustomInfo_mc.h"
# include "json.h"
# include "Output_GEN.h"
# include "Output_RECO.h"


namespace Analyze_tauTau
{
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    )
    {
        Analyze_tauTau::initialize(
            process,
            dir,
            otherInfoDir,
            sourceFileName,
            isMC,
            isSUSY,
            era,
            std::make_pair(-1, -1),
            {},
            m_correction,
            syst_name,
            syst_type,
            scaleVariationIndex
        );
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    )
    {
        Analyze_tauTau::initialize(
            process,
            dir,
            otherInfoDir,
            sourceFileName,
            isMC,
            isSUSY,
            era,
            massPoint_stop1_neutralino1,
            {},
            m_correction,
            syst_name,
            syst_type,
            scaleVariationIndex
        );
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::vector <double> v_eventWeight_nJetBin,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    )
    {
        Analyze_tauTau::initialize(
            process,
            dir,
            otherInfoDir,
            sourceFileName,
            isMC,
            isSUSY,
            era,
            std::make_pair(-1, -1),
            v_eventWeight_nJetBin,
            m_correction,
            syst_name,
            syst_type,
            scaleVariationIndex
        );
    }
    
    
    void initialize(
        const char *process,
        const char *dir,
        const char *otherInfoDir,
        const char *sourceFileName,
        bool isMC,
        bool isSUSY,
        const char *era,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::vector <double> v_eventWeight_nJetBin,
        std::map <std::string, bool> m_correction,
        std::string syst_name,
        Common::SYST_TYPE syst_type,
        int scaleVariationIndex
    )
    {
        printf("\n");
        printf("********** Era: %s ********** \n", era);
        printf("\n");
        
        asymm_mt2_lester_bisect::disableCopyrightMessage();
        
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "sourceFiles/%s/%s_custom.txt", process, process);
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName);
        
        std::string inFile;
        
        char command[Common::str_len];
        
        char massPointStr[Common::str_len];
        
        //if(isSUSY)
        //{
        //    sprintf(massPointStr, "_%d_%d", massPoint_stop1_neutralino1.first, massPoint_stop1_neutralino1.second);
        //}
        //
        //else
        {
            sprintf(massPointStr, "");
        }
        
        char outDir[Common::str_len];
        sprintf(
            outDir,
            "%s%s%s%s",
            dir, massPointStr,
            Common::getSystSuffix(syst_name, syst_type).c_str(),
            Common::getScaleVariationSuffix(scaleVariationIndex).c_str()
        );
        
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
        
        char fileName_ISRinfo[Common::str_len];
        std::vector <std::vector <double> > vv_ISRinfo;
        
        if(isSUSY)
        {
            sprintf(fileName_massPointInfo, "%s/output_genParam/%s/XSweightInfo.txt", otherInfoDir, process);
            printf("Mass-point info file: %s \n", fileName_massPointInfo);
            fflush(stdout);
            
            Common::parseCSVto2Dvector(std::string(fileName_massPointInfo), &vv_massPointInfo);
            
            //for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
            //{
            //    if(vv_massPointInfo.at(iMassPoint).at(0) > 1500 || vv_massPointInfo.at(iMassPoint).at(1) > 650)
            //    {
            //        vv_massPointInfo.erase(vv_massPointInfo.begin()+iMassPoint);
            //    }
            //}
            
            printf("# mass-point: %d \n", vv_massPointInfo.size());
            fflush(stdout);
            
            
            sprintf(fileName_ISRinfo, "%s/output_ISRinfo/%s/ISRinfo.txt", otherInfoDir, process);
            printf("ISR info file: %s \n", fileName_ISRinfo);
            fflush(stdout);
            
            Common::parseCSVto2Dvector(std::string(fileName_ISRinfo), &vv_ISRinfo);
        }
        
        char fileName_pileUp_mc[Common::str_len];
        sprintf(fileName_pileUp_mc, "%s/output_pileUp/%s_pileUp/custom_all_pileUp.root", otherInfoDir, process);

        char histName_pileUp_mc[Common::str_len];
        sprintf(histName_pileUp_mc, "pileup");
        
        char fileName_pileUp_data[Common::str_len];
        char histName_pileUp_data[Common::str_len];
        sprintf(histName_pileUp_data, "pileup");
        
        char fileName_pileUp_data_systUp[Common::str_len];
        char histName_pileUp_data_systUp[Common::str_len];
        sprintf(histName_pileUp_data_systUp, "pileup");
        
        char fileName_pileUp_data_systDown[Common::str_len];
        char histName_pileUp_data_systDown[Common::str_len];
        sprintf(histName_pileUp_data_systDown, "pileup");
        
        char fileName_bTaggingEfficiency[Common::str_len];
        sprintf(fileName_bTaggingEfficiency, "%s/output_bTaggingEfficiency/%s_bTaggingEfficiency/bTaggingEfficiency.root", otherInfoDir, process);
        
        char fileName_bTagCalib[Common::str_len];
        BTagCalibration bTagCalib;
        
        
        char fileName_htt_scaleFactor[Common::str_len];
        
        
        // Era
        if(!strcmp(era, "2016"))
        {
            //sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.root");
            
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.root");
            sprintf(fileName_pileUp_data_systUp, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_systUp.root");
            sprintf(fileName_pileUp_data_systDown, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_systDown.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2016/DeepJet_2016LegacySF_WP_V1.csv");
            
            sprintf(fileName_htt_scaleFactor, "resources/htt_scalefactors_v16_5_2.root");
            
            if(isSUSY)
            {
                sprintf(fileName_bTagCalib, "resources/bTagging/2016/DeepFlav_13TEV_16SL_18_3_2019.csv");
            }
        }
        
        else if(!strcmp(era, "2017"))
        {
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.root");
            sprintf(fileName_pileUp_data_systUp, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_systUp.root");
            sprintf(fileName_pileUp_data_systDown, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_systDown.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2017/DeepFlavour_94XSF_WP_V3_B_F.csv");
            
            sprintf(fileName_htt_scaleFactor, "resources/htt_scalefactors_2017_v2.root");
            
            if(isSUSY)
            {
                sprintf(fileName_bTagCalib, "resources/bTagging/2017/DeepFlav_13TEV_17SL_18_3_2019.csv");
            }
        }
        
        else
        {
            printf("Error in Analyze_tauTau::initialize(...): Provide a valid era (2016/2017). Provided era: %s", era);
            exit(EXIT_FAILURE);
        }
        
        bTagCalib = BTagCalibration("DeepFlav", fileName_bTagCalib);
        
        
        TFile *htt_scaleFactorFile = TFile::Open(fileName_htt_scaleFactor);
        RooWorkspace *htt_scaleFactorWS = (RooWorkspace*) htt_scaleFactorFile->Get("w");
        htt_scaleFactorFile->Close();
        
        
        // Tau trigger
        std::map <std::string, std::string> m_tauTriggerSFfile;
        m_tauTriggerSFfile["2016"] = "resources/tauTrigger/2016/2016_tauTriggerEff_DeepTau2017v2p1.root";
        m_tauTriggerSFfile["2017"] = "resources/tauTrigger/2017/2017_tauTriggerEff_DeepTau2017v2p1.root";
        m_tauTriggerSFfile["2018"] = "resources/tauTrigger/2018/2018_tauTriggerEff_DeepTau2017v2p1.root";
        
        tau_trigger::SFProvider tauTriggerSFobj(
            m_tauTriggerSFfile.at(era),
            "ditau",
            "Tight"
        );
        
        
        // Tau ID
        std::map <std::string, std::string> m_tauIDyear;
        m_tauIDyear["2016"] = "2016Legacy";
        m_tauIDyear["2017"] = "2017ReReco";
        m_tauIDyear["2018"] = "2018ReReco";
        
        TauIDSFTool tauIDSFobj(
            m_tauIDyear.at(era),
            "DeepTau2017v2p1VSjet",
            "Tight",
            false,
            false
        );
        
        
        //
        std::string tauInputFileName_fast;
        std::string tauInputFileName_full;
        
        std::string tauHistName_num_fast;
        std::string tauHistName_den_fast;
        
        std::string tauHistName_num_full;
        std::string tauHistName_den_full;
        
        if(!strcmp(era, "2016"))
        {
            tauInputFileName_fast = "ttbar_mc/output_tauIdIsoEfficiency/TTJets_13TeV-madgraphMLM_FastSim_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root";
            tauInputFileName_full = "ttbar_mc/output_tauIdIsoEfficiency/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root";
            
            tauHistName_num_fast = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_eta_reco";
            tauHistName_den_fast = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_all_pT_vs_eta_reco";
            
            tauHistName_num_full = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_eta_reco";
            tauHistName_den_full = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_all_pT_vs_eta_reco";
        }
        
        else if(!strcmp(era, "2017"))
        {
            tauInputFileName_fast = "ttbar_mc/output_tauIdIsoEfficiency/TTJets_DiLept_TuneCP2_13TeV-madgraphMLM-pythia8_FastSim_Fall17_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root";
            tauInputFileName_full = "ttbar_mc/output_tauIdIsoEfficiency/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root";
            
            tauHistName_num_fast = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_eta_reco";
            tauHistName_den_fast = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_all_pT_vs_eta_reco";
            
            tauHistName_num_full = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_eta_reco";
            tauHistName_den_full = "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_all_pT_vs_eta_reco";
        }
        
        TauEfficiencyAndSF::TauFastFullSF *tauFastFullSimSFinfo = new TauEfficiencyAndSF::TauFastFullSF(
            tauInputFileName_fast,
            tauHistName_num_fast,
            tauHistName_den_fast,
            tauInputFileName_full,
            tauHistName_num_full,
            tauHistName_den_full,
            Common::v_eta_bin_tauFastFullSF,
            Common::v_pT_bin_tauFastFullSF,
            true
        );
        
        
        // Run JSON
        std::map <std::string, std::vector <std::string> > m_runJsonName = {
            {"2016", {}},
            
            {"2017", {
                "resources/unblindingJson/2017/unblindingJson_2017BCDE.json",
                "resources/unblindingJson/2017/unblindingJson_2017F.json",
            }}
        };
        
        std::vector <nlohmann::json> v_runJson;
        
        //if(!isMC)
        //{
        //    for(int iJson = 0; iJson < m_runJsonName.at(era).size(); iJson++)
        //    {
        //        std::ifstream jsonFileStream(m_runJsonName.at(era).at(iJson));
        //        nlohmann::json jsonContent;
        //        jsonFileStream >> jsonContent;
        //        jsonFileStream.close();
        //        
        //        v_runJson.push_back(jsonContent);
        //    }
        //    
        //    // Check is run JSONs are read correctly
        //    printf("\n");
        //    
        //    for(int iJson = 0; iJson < m_runJsonName.at(era).size(); iJson++)
        //    {
        //        printf("Using run JSON: %s \n", m_runJsonName.at(era).at(iJson).c_str());
        //        std::cout << v_runJson.at(iJson) << "\n\n";
        //    }
        //}
        
        
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
                "genParam", "t", "Z", "el", "mu", "tau_vis", "b", "jet", "MET"};
            
            std::vector <const char*> v_object_reco;
            
            if(isMC)
            {
                v_object_reco = {
                    "PU", "el", "mu", "tau", "jet", "MET", "trigger"};
            }
            
            else
            {
                v_object_reco = {
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
                        fileName_pileUp_data, histName_pileUp_data,
                        fileName_pileUp_data_systUp, histName_pileUp_data_systUp,
                        fileName_pileUp_data_systDown, histName_pileUp_data_systDown
                    );
                }
            }
            
            else
            {
                input_data = new CustomInfo_data::Info(
                    inFile.c_str(),
                    treePath_reco, v_object_reco,
                    "read"
                );
            }
            
            // GEN histograms
            std::vector <const char*> v_outputOption_gen = {
                "el", "mu", "tau", "tau_vis", "b", "jet", "MET"};
            
            //Output_GEN::Output *output_gen_noTauPairSelection = new Output_GEN::Output(v_outputOption_gen, "noTauPairSelection");
            //Output_GEN::Output *output_gen_OS = new Output_GEN::Output(v_outputOption_gen, "OS");
            
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
            
            Output_RECO::Output *output_reco_tightTight_OS_baselineSRB = new Output_RECO::Output(v_outputOption_reco, "tightTight_OS_baselineSRB");
            Output_RECO::Output *output_reco_tightTight_SS_baselineSRB_nbAny = new Output_RECO::Output(v_outputOption_reco, "tightTight_SS_baselineSRB_nbAny");
            Output_RECO::Output *output_reco_tightTight_OS_baselineSRB_nb0 = new Output_RECO::Output(v_outputOption_reco, "tightTight_OS_baselineSRB_nb0");
            
            Output_RECO::Output *output_reco_tightTight_OS_genMatched;
            Output_RECO::Output *output_reco_tightTight_OS_genMatched_baselineSRB;
            Output_RECO::Output *output_reco_tightTight_SS_genMatched_baselineSRB_nbAny;
            Output_RECO::Output *output_reco_tightTight_OS_genMatched_baselineSRB_nb0;
            
            
            if(isMC)
            {
                output_reco_tightTight_OS_genMatched = new Output_RECO::Output(v_outputOption_reco, "tightTight_OS_genMatched");
                
                output_reco_tightTight_OS_genMatched_baselineSRB = new Output_RECO::Output(v_outputOption_reco, "tightTight_OS_genMatched_baselineSRB");
                output_reco_tightTight_SS_genMatched_baselineSRB_nbAny = new Output_RECO::Output(v_outputOption_reco, "tightTight_SS_genMatched_baselineSRB_nbAny");
                output_reco_tightTight_OS_genMatched_baselineSRB_nb0 = new Output_RECO::Output(v_outputOption_reco, "tightTight_OS_genMatched_baselineSRB_nb0");
            }
            
            
            std::map <std::pair <int, int>, Output_RECO::Output*> m_output_reco_stopPair_OS_genMatched;
            std::map <std::pair <int, int>, Output_RECO::Output*> m_output_reco_stopPair_OS_genMatched_baselineSRB;
            std::map <std::pair <int, int>, Output_RECO::Output*> m_output_reco_stopPair_OS_genMatched_baselineSRB_nb0;
            
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
                    
                    sprintf(details_temp, "%s_%d_%d", "tightTight_OS_genMatched", p_temp.first, p_temp.second);
                    m_output_reco_stopPair_OS_genMatched[p_temp] = new Output_RECO::Output(v_outputOption_reco, details_temp);
                    
                    sprintf(details_temp, "%s_%d_%d", "tightTight_OS_genMatched_baselineSRB", p_temp.first, p_temp.second);
                    m_output_reco_stopPair_OS_genMatched_baselineSRB[p_temp] = new Output_RECO::Output(v_outputOption_reco, details_temp);
                }
            }
            
            
            for(int iSRA = 0; iSRA < 6; iSRA++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRA%d", iSRA+1);
                
                output_reco_tightTight_OS_baselineSRB->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                output_reco_tightTight_SS_baselineSRB_nbAny->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                output_reco_tightTight_OS_baselineSRB_nb0->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                
                if(isMC)
                {
                    output_reco_tightTight_OS_genMatched->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                    
                    output_reco_tightTight_OS_genMatched_baselineSRB->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                    output_reco_tightTight_SS_genMatched_baselineSRB_nbAny->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                    output_reco_tightTight_OS_genMatched_baselineSRB_nb0->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                }
                
                if(isSUSY)
                {
                    for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                    {
                        std::pair <int, int> p_temp(
                            (int) vv_massPointInfo.at(iMassPoint).at(0),
                            (int) vv_massPointInfo.at(iMassPoint).at(1)
                        );
                        
                        m_output_reco_stopPair_OS_genMatched.at(p_temp)->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                        m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp)->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                    }
                }
            }
            
            for(int iSRB = 0; iSRB < 18; iSRB++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRB%d", iSRB+1);
                
                output_reco_tightTight_OS_baselineSRB->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                output_reco_tightTight_SS_baselineSRB_nbAny->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                output_reco_tightTight_OS_baselineSRB_nb0->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                
                if(isMC)
                {
                    output_reco_tightTight_OS_genMatched->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                    
                    output_reco_tightTight_OS_genMatched_baselineSRB->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                    output_reco_tightTight_SS_genMatched_baselineSRB_nbAny->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                    output_reco_tightTight_OS_genMatched_baselineSRB_nb0->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                }
                
                if(isSUSY)
                {
                    for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                    {
                        std::pair <int, int> p_temp(
                            (int) vv_massPointInfo.at(iMassPoint).at(0),
                            (int) vv_massPointInfo.at(iMassPoint).at(1)
                        );
                        
                        m_output_reco_stopPair_OS_genMatched.at(p_temp)->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                        m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp)->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                    }
                }
            }
            
            for(int iSRC = 0; iSRC < 18; iSRC++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRC%d", iSRC+1);
                
                output_reco_tightTight_OS_baselineSRB->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                output_reco_tightTight_SS_baselineSRB_nbAny->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                output_reco_tightTight_OS_baselineSRB_nb0->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                
                if(isMC)
                {
                    output_reco_tightTight_OS_genMatched->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                    
                    output_reco_tightTight_OS_genMatched_baselineSRB->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                    output_reco_tightTight_SS_genMatched_baselineSRB_nbAny->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                    output_reco_tightTight_OS_genMatched_baselineSRB_nb0->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                }
                
                if(isSUSY)
                {
                    for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                    {
                        std::pair <int, int> p_temp(
                            (int) vv_massPointInfo.at(iMassPoint).at(0),
                            (int) vv_massPointInfo.at(iMassPoint).at(1)
                        );
                        
                        m_output_reco_stopPair_OS_genMatched.at(p_temp)->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                        m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp)->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                    }
                }
            }
            
            for(int iSRD = 0; iSRD < 18; iSRD++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRD%d", iSRD+1);
                
                output_reco_tightTight_OS_baselineSRB->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                output_reco_tightTight_SS_baselineSRB_nbAny->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                output_reco_tightTight_OS_baselineSRB_nb0->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                
                if(isMC)
                {
                    output_reco_tightTight_OS_genMatched->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                    
                    output_reco_tightTight_OS_genMatched_baselineSRB->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                    output_reco_tightTight_SS_genMatched_baselineSRB_nbAny->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                    output_reco_tightTight_OS_genMatched_baselineSRB_nb0->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                }
                
                if(isSUSY)
                {
                    for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                    {
                        std::pair <int, int> p_temp(
                            (int) vv_massPointInfo.at(iMassPoint).at(0),
                            (int) vv_massPointInfo.at(iMassPoint).at(1)
                        );
                        
                        m_output_reco_stopPair_OS_genMatched.at(p_temp)->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                        m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp)->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                    }
                }
            }
            
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            
            std::map <std::string, bool> m_eventSelection;
            
            m_eventSelection["MET_E_reco >= 50"] = false;
            m_eventSelection["tauTau_jet_HT_reco >= 100"] = false;
            m_eventSelection["b_n_reco >= 1"] = false;
            
            std::string eventSelectionStr_blank = "1";
            std::string eventSelectionStr_baselineSRB = "MET_E_reco >= 50 and tauTau_jet_HT_reco >= 100 and b_n_reco >= 1";
            std::string eventSelectionStr_baselineSRB_nbAny = "MET_E_reco >= 50 and tauTau_jet_HT_reco >= 100";
            std::string eventSelectionStr_baselineSRB_nb0 = "MET_E_reco >= 50 and tauTau_jet_HT_reco >= 100 and b_n_reco == 0";
            
            
            // Analyze
            if(isMC)
            {
                if(!isSUSY)
                {
                    Analyze_tauTau::analyze_reco(
                        input_mc,
                        output_reco_tightTight_OS_genMatched,
                        0,
                        "tight", "OS",
                        eventSelectionStr_blank,
                        isMC,
                        isSUSY,
                        era,
                        massPoint_stop1_neutralino1,
                        v_eventWeight_nJetBin,
                        vv_ISRinfo,
                        tauFastFullSimSFinfo,
                        &tauTriggerSFobj,
                        &tauIDSFobj,
                        htt_scaleFactorWS,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        m_correction,
                        syst_name,
                        syst_type,
                        scaleVariationIndex,
                        v_runJson,
                        true,
                        0.3
                    );
                    
                    printf("\n");
                    
                    
                    //
                    Analyze_tauTau::analyze_reco(
                        input_mc,
                        output_reco_tightTight_OS_genMatched_baselineSRB,
                        0,
                        "tight", "OS",
                        eventSelectionStr_baselineSRB,
                        isMC,
                        isSUSY,
                        era,
                        massPoint_stop1_neutralino1,
                        v_eventWeight_nJetBin,
                        vv_ISRinfo,
                        tauFastFullSimSFinfo,
                        &tauTriggerSFobj,
                        &tauIDSFobj,
                        htt_scaleFactorWS,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        m_correction,
                        syst_name,
                        syst_type,
                        scaleVariationIndex,
                        v_runJson,
                        true,
                        0.3
                    );
                    
                    printf("\n");
                    
                    
                    //
                    Analyze_tauTau::analyze_reco(
                        input_mc,
                        output_reco_tightTight_SS_genMatched_baselineSRB_nbAny,
                        0,
                        "tight", "SS",
                        eventSelectionStr_baselineSRB_nbAny,
                        isMC,
                        isSUSY,
                        era,
                        massPoint_stop1_neutralino1,
                        v_eventWeight_nJetBin,
                        vv_ISRinfo,
                        tauFastFullSimSFinfo,
                        &tauTriggerSFobj,
                        &tauIDSFobj,
                        htt_scaleFactorWS,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        m_correction,
                        syst_name,
                        syst_type,
                        scaleVariationIndex,
                        v_runJson,
                        true,
                        0.3
                    );
                    
                    printf("\n");
                    
                    
                    //
                    Analyze_tauTau::analyze_reco(
                        input_mc,
                        output_reco_tightTight_OS_genMatched_baselineSRB_nb0,
                        0,
                        "tight", "OS",
                        eventSelectionStr_baselineSRB_nb0,
                        isMC,
                        isSUSY,
                        era,
                        massPoint_stop1_neutralino1,
                        v_eventWeight_nJetBin,
                        vv_ISRinfo,
                        tauFastFullSimSFinfo,
                        &tauTriggerSFobj,
                        &tauIDSFobj,
                        htt_scaleFactorWS,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        m_correction,
                        syst_name,
                        syst_type,
                        scaleVariationIndex,
                        v_runJson,
                        true,
                        0.3
                    );
                    
                    printf("\n");
                }
                
                if(isSUSY)
                {
                    //
                    Analyze_tauTau::analyze_reco(
                        input_mc,
                        0,
                        &m_output_reco_stopPair_OS_genMatched,
                        "tight", "OS",
                        eventSelectionStr_blank,
                        isMC,
                        isSUSY,
                        era,
                        massPoint_stop1_neutralino1,
                        v_eventWeight_nJetBin,
                        vv_ISRinfo,
                        tauFastFullSimSFinfo,
                        &tauTriggerSFobj,
                        &tauIDSFobj,
                        htt_scaleFactorWS,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        m_correction,
                        syst_name,
                        syst_type,
                        scaleVariationIndex,
                        v_runJson,
                        true,
                        0.3
                    );
                    
                    printf("\n");
                    
                    
                    //
                    Analyze_tauTau::analyze_reco(
                        input_mc,
                        0,
                        &m_output_reco_stopPair_OS_genMatched_baselineSRB,
                        "tight", "OS",
                        eventSelectionStr_baselineSRB,
                        isMC,
                        isSUSY,
                        era,
                        massPoint_stop1_neutralino1,
                        v_eventWeight_nJetBin,
                        vv_ISRinfo,
                        tauFastFullSimSFinfo,
                        &tauTriggerSFobj,
                        &tauIDSFobj,
                        htt_scaleFactorWS,
                        &bTagCalib,
                        fileName_bTaggingEfficiency,
                        m_correction,
                        syst_name,
                        syst_type,
                        scaleVariationIndex,
                        v_runJson,
                        true,
                        0.3
                    );
                    
                    printf("\n");
                }
            }
            
            else
            {
                //
                Analyze_tauTau::analyze_reco(
                    input_data,
                    output_reco_tightTight_OS_baselineSRB,
                    0,
                    "tight", "OS",
                    eventSelectionStr_baselineSRB,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    vv_ISRinfo,
                    tauFastFullSimSFinfo,
                    &tauTriggerSFobj,
                    &tauIDSFobj,
                    htt_scaleFactorWS,
                    0,
                    "",
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex,
                    v_runJson
                );
                
                printf("\n");
                
                
                //
                Analyze_tauTau::analyze_reco(
                    input_data,
                    output_reco_tightTight_SS_baselineSRB_nbAny,
                    0,
                    "tight", "SS",
                    eventSelectionStr_baselineSRB_nbAny,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    vv_ISRinfo,
                    tauFastFullSimSFinfo,
                    &tauTriggerSFobj,
                    &tauIDSFobj,
                    htt_scaleFactorWS,
                    0,
                    "",
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex,
                    v_runJson
                );
                
                printf("\n");
                
                
                //
                Analyze_tauTau::analyze_reco(
                    input_data,
                    output_reco_tightTight_OS_baselineSRB_nb0,
                    0,
                    "tight", "OS",
                    eventSelectionStr_baselineSRB_nb0,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    vv_ISRinfo,
                    tauFastFullSimSFinfo,
                    &tauTriggerSFobj,
                    &tauIDSFobj,
                    htt_scaleFactorWS,
                    0,
                    "",
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex,
                    v_runJson
                );
                
                printf("\n");
            }
            
            printf("\n\n");
            
            
            output_analyzed->mkdir("gen");
            output_analyzed->cd("gen");
            //output_gen_OS->writeData();
            
            
            output_analyzed->cd("../");
            
            
            output_analyzed->mkdir("reco");
            //output_analyzed->cd("reco");
            
            char dirName[Common::str_len];
            
            
            if(isMC)
            {
                if(!isSUSY)
                {
                    sprintf(dirName, "reco/%s", output_reco_tightTight_OS_genMatched->details);
                    output_analyzed->mkdir(dirName);
                    output_analyzed->cd(dirName);
                    output_reco_tightTight_OS_genMatched->writeData();
                    
                    sprintf(dirName, "reco/%s", output_reco_tightTight_OS_genMatched_baselineSRB->details);
                    output_analyzed->mkdir(dirName);
                    output_analyzed->cd(dirName);
                    output_reco_tightTight_OS_genMatched_baselineSRB->writeData();
                    
                    sprintf(dirName, "reco/%s", output_reco_tightTight_SS_genMatched_baselineSRB_nbAny->details);
                    output_analyzed->mkdir(dirName);
                    output_analyzed->cd(dirName);
                    output_reco_tightTight_SS_genMatched_baselineSRB_nbAny->writeData();
                    
                    sprintf(dirName, "reco/%s", output_reco_tightTight_OS_genMatched_baselineSRB_nb0->details);
                    output_analyzed->mkdir(dirName);
                    output_analyzed->cd(dirName);
                    output_reco_tightTight_OS_genMatched_baselineSRB_nb0->writeData();
                }
                
                if(isSUSY)
                {
                    for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                    {
                        std::pair <int, int> p_temp(
                            (int) vv_massPointInfo.at(iMassPoint).at(0),
                            (int) vv_massPointInfo.at(iMassPoint).at(1)
                        );
                        
                        sprintf(dirName, "reco/%s", m_output_reco_stopPair_OS_genMatched.at(p_temp)->details);
                        output_analyzed->mkdir(dirName);
                        output_analyzed->cd(dirName);
                        m_output_reco_stopPair_OS_genMatched.at(p_temp)->writeData();
                        
                        sprintf(dirName, "reco/%s", m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp)->details);
                        output_analyzed->mkdir(dirName);
                        output_analyzed->cd(dirName);
                        m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp)->writeData();
                    }
                }
            }
            
            else
            {
                sprintf(dirName, "reco/%s", output_reco_tightTight_OS_baselineSRB->details);
                output_analyzed->mkdir(dirName);
                output_analyzed->cd(dirName);
                output_reco_tightTight_OS_baselineSRB->writeData();
                
                sprintf(dirName, "reco/%s", output_reco_tightTight_SS_baselineSRB_nbAny->details);
                output_analyzed->mkdir(dirName);
                output_analyzed->cd(dirName);
                output_reco_tightTight_SS_baselineSRB_nbAny->writeData();
                
                sprintf(dirName, "reco/%s", output_reco_tightTight_OS_baselineSRB_nb0->details);
                output_analyzed->mkdir(dirName);
                output_analyzed->cd(dirName);
                output_reco_tightTight_OS_baselineSRB_nb0->writeData();
            }
            
            
            // Release memory
            output_reco_tightTight_OS_baselineSRB->freeMemory();
            output_reco_tightTight_SS_baselineSRB_nbAny->freeMemory();
            output_reco_tightTight_OS_baselineSRB_nb0->freeMemory();
            
            if(isMC)
            {
                output_reco_tightTight_OS_genMatched->freeMemory();
                output_reco_tightTight_OS_genMatched_baselineSRB->freeMemory();
                output_reco_tightTight_SS_genMatched_baselineSRB_nbAny->freeMemory();
                output_reco_tightTight_OS_genMatched_baselineSRB_nb0->freeMemory();
            }
            
            if(isSUSY)
            {
                for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                {
                    std::pair <int, int> p_temp(
                        (int) vv_massPointInfo.at(iMassPoint).at(0),
                        (int) vv_massPointInfo.at(iMassPoint).at(1)
                    );
                    
                    m_output_reco_stopPair_OS_genMatched.at(p_temp)->freeMemory();
                    m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp)->freeMemory();
                }
            }
            
            
            delete output_reco_tightTight_OS_baselineSRB;
            delete output_reco_tightTight_SS_baselineSRB_nbAny;
            delete output_reco_tightTight_OS_baselineSRB_nb0;
            
            if(isMC)
            {
                delete output_reco_tightTight_OS_genMatched;
                delete output_reco_tightTight_OS_genMatched_baselineSRB;
                delete output_reco_tightTight_SS_genMatched_baselineSRB_nbAny;
                delete output_reco_tightTight_OS_genMatched_baselineSRB_nb0;
            }
            
            if(isSUSY)
            {
                for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
                {
                    std::pair <int, int> p_temp(
                        (int) vv_massPointInfo.at(iMassPoint).at(0),
                        (int) vv_massPointInfo.at(iMassPoint).at(1)
                    );
                    
                    delete m_output_reco_stopPair_OS_genMatched.at(p_temp);
                    delete m_output_reco_stopPair_OS_genMatched_baselineSRB.at(p_temp);
                }
            }
            
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
    
    
    void analyze_gen(CustomInfo_mc::Info *input,
        Output_GEN::Output *output_gen,
        const char *tauPair_signOption,
        std::map <std::string, bool> m_eventSelection,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1)
    {
        int nEvent = input->T_gen->GetEntries();
        
        //output_gen->addTauHist(2);
        output_gen->addTauVisHist(2);
        output_gen->addbHist(2);
        output_gen->addJetHist(2);
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if((iEvent+2) % 1000 == 0)
            {
                printf("Processed event no. %d / %d \n", iEvent+2, nEvent);
                fflush(stdout);
            }
            
            input->T_gen->GetEntry(iEvent);
            
            // Select mass point
            if(isSUSY)
            {
                if((massPoint_stop1_neutralino1.first >= 0 && input->stop1_m_genParam != massPoint_stop1_neutralino1.first) ||
                    (massPoint_stop1_neutralino1.second >= 0 && input->neutralino1_m_genParam != massPoint_stop1_neutralino1.second))
                {
                    continue;
                }
            }
            
            std::vector <int> tau_visPair_pos;
            std::vector <int> v_nTau_vis;
            
            if(m_eventSelection["tau_n >= 2"])
            {
                std::vector <double> v_tau_pTetaCut(input->tau_vis_n_gen, 0);
                
                for(int iTau = 0; iTau < input->tau_vis_n_gen; iTau++)
                {
                    CLHEP::HepLorentzVector tau_vis_4mom_gen;
                    
                    tau_vis_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(iTau)));
                    tau_vis_4mom_gen.setX(input->v_tau_vis_px_gen->at(iTau));
                    tau_vis_4mom_gen.setY(input->v_tau_vis_py_gen->at(iTau));
                    tau_vis_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(iTau));
                    
                    if(tau_vis_4mom_gen.perp() < Common::tau_vis_pTcut_gen || fabs(tau_vis_4mom_gen.eta()) > Common::tau_vis_etaCut_gen)
                    {
                        continue;
                    }
                    
                    v_tau_pTetaCut[iTau] = 1;
                }
                
                // Get tau-vis pair
                std::vector <std::vector <int> > tau_visPair_info = Common::getTauPair(
                    &(input->v_tau_vis_gen),
                    {},
                    {&v_tau_pTetaCut},
                    Common::tauTau_deltaRcut_reco,
                    tauPair_signOption);
                
                
                tau_visPair_pos = tau_visPair_info[0];
                v_nTau_vis = tau_visPair_info[1];
                
                
                // At least 2 tau-vis
                if(!tau_visPair_pos.size())
                {
                    continue;
                }
            }
            
            // MET
            output_gen->h1_MET_E->Fill(input->MET_E_gen);
            output_gen->h1_MET_phi->Fill(input->MET_phi_gen);
            
            // GEN electron number
            /*output_gen->h1_el_n->Fill(input->el_n_gen);
            
            // GEN muon number
            output_gen->h1_mu_n->Fill(input->mu_n_gen);
            
            CLHEP::HepLorentzVector el_4mom_gen, mu_4mom_gen;
            
            if(input->el_n_gen > 0)
            {
                el_4mom_gen.setT(fabs(input->v_el_E_gen->at(0)));
                el_4mom_gen.setX(input->v_el_px_gen->at(0));
                el_4mom_gen.setY(input->v_el_py_gen->at(0));
                el_4mom_gen.setZ(input->v_el_pz_gen->at(0));
            }
            
            if(input->mu_n_gen > 0)
            {
                mu_4mom_gen.setT(fabs(input->v_mu_E_gen->at(0)));
                mu_4mom_gen.setX(input->v_mu_px_gen->at(0));
                mu_4mom_gen.setY(input->v_mu_py_gen->at(0));
                mu_4mom_gen.setZ(input->v_mu_pz_gen->at(0));
            }
            
            // GEN leading lepton (electron)
            if(el_4mom_gen.perp() > mu_4mom_gen.perp())
            {
                output_gen->h1_lep1_el_pT->Fill(el_4mom_gen.perp());
                output_gen->h1_lep1_el_eta->Fill(el_4mom_gen.eta());
                output_gen->h1_lep1_el_phi->Fill(el_4mom_gen.phi());
            }
            
            // GEN leading lepton (muon)
            else if(mu_4mom_gen.perp() > el_4mom_gen.perp())
            {
                output_gen->h1_lep1_mu_pT->Fill(mu_4mom_gen.perp());
                output_gen->h1_lep1_mu_eta->Fill(mu_4mom_gen.eta());
                output_gen->h1_lep1_mu_phi->Fill(mu_4mom_gen.phi());
            }*/
            
            // GEN tau
            int tau_vis_n_gen = 0;
            
            double tau_vis1_tau_vis2_MET_mT2 = 0;
            
            double MET_pZeta = 0;
            double tau_vis1_tau_vis2_pZeta = 0;
            double tau_vis1_tau_vis2_MET_pZeta = 0;
            
            for(int iTau = 0; iTau < input->tau_vis_n_gen; iTau++)
            {
                // Tau lepton
                //CLHEP::HepLorentzVector tau_4mom_gen;
                //
                //tau_4mom_gen.setT(fabs(input->v_tau_E_gen->at(iTau)));
                //tau_4mom_gen.setX(input->v_tau_px_gen->at(iTau));
                //tau_4mom_gen.setY(input->v_tau_py_gen->at(iTau));
                //tau_4mom_gen.setZ(input->v_tau_pz_gen->at(iTau));
                //
                //output_gen->h1_tau_pT->Fill(tau_4mom_gen.perp());
                //output_gen->h1_tau_eta->Fill(tau_4mom_gen.eta());
                //output_gen->h1_tau_phi->Fill(tau_4mom_gen.phi());
                //
                //if(iTau < 2)
                //{
                //    output_gen->v_h1_tau_pT[iTau]->Fill(tau_4mom_gen.perp());
                //    output_gen->v_h1_tau_eta[iTau]->Fill(tau_4mom_gen.eta());
                //    output_gen->v_h1_tau_phi[iTau]->Fill(tau_4mom_gen.phi());
                //}
                
                // Visible part of tau
                CLHEP::HepLorentzVector tau_vis_4mom_gen;
                
                tau_vis_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(iTau)));
                tau_vis_4mom_gen.setX(input->v_tau_vis_px_gen->at(iTau));
                tau_vis_4mom_gen.setY(input->v_tau_vis_py_gen->at(iTau));
                tau_vis_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(iTau));
                
                if(tau_vis_4mom_gen.perp() < Common::tau_pTcut_tauTau_reco || fabs(tau_vis_4mom_gen.eta()) > Common::tau_etaCut_tauTau_reco)
                {
                    continue;
                }
                
                tau_vis_n_gen++;
                
                output_gen->h1_tau_vis_pT->Fill(tau_vis_4mom_gen.perp());
                output_gen->h1_tau_vis_eta->Fill(tau_vis_4mom_gen.eta());
                output_gen->h1_tau_vis_phi->Fill(tau_vis_4mom_gen.phi());
            }
            
            output_gen->h1_tau_vis_n->Fill(tau_vis_n_gen);
            
            
            if(tau_visPair_pos.size() && m_eventSelection["tau_n >= 2"])
            {
                CLHEP::HepLorentzVector tau_vis1_4mom_gen, tau_vis2_4mom_gen;
                
                tau_vis1_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(tau_visPair_pos[0])));
                tau_vis1_4mom_gen.setX(input->v_tau_vis_px_gen->at(tau_visPair_pos[0]));
                tau_vis1_4mom_gen.setY(input->v_tau_vis_py_gen->at(tau_visPair_pos[0]));
                tau_vis1_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(tau_visPair_pos[0]));
                
                tau_vis2_4mom_gen.setT(fabs(input->v_tau_vis_E_gen->at(tau_visPair_pos[1])));
                tau_vis2_4mom_gen.setX(input->v_tau_vis_px_gen->at(tau_visPair_pos[1]));
                tau_vis2_4mom_gen.setY(input->v_tau_vis_py_gen->at(tau_visPair_pos[1]));
                tau_vis2_4mom_gen.setZ(input->v_tau_vis_pz_gen->at(tau_visPair_pos[1]));
                
                
                output_gen->v_h1_tau_vis_pT[0]->Fill(tau_vis1_4mom_gen.perp());
                output_gen->v_h1_tau_vis_eta[0]->Fill(tau_vis1_4mom_gen.eta());
                output_gen->v_h1_tau_vis_phi[0]->Fill(tau_vis1_4mom_gen.phi());
                output_gen->v_h1_tau_vis_m[0]->Fill(tau_vis1_4mom_gen.m());
                output_gen->v_h1_tau_vis_MET_deltaPhi[0]->Fill(Common::getDeltaPhi(tau_vis1_4mom_gen.phi(), input->MET_phi_gen));
                
                output_gen->v_h1_tau_vis_pT[1]->Fill(tau_vis2_4mom_gen.perp());
                output_gen->v_h1_tau_vis_eta[1]->Fill(tau_vis2_4mom_gen.eta());
                output_gen->v_h1_tau_vis_phi[1]->Fill(tau_vis2_4mom_gen.phi());
                output_gen->v_h1_tau_vis_m[1]->Fill(tau_vis2_4mom_gen.m());
                output_gen->v_h1_tau_vis_MET_deltaPhi[1]->Fill(Common::getDeltaPhi(tau_vis2_4mom_gen.phi(), input->MET_phi_gen));
                
                asymm_mt2_lester_bisect::disableCopyrightMessage();
                
                tau_vis1_tau_vis2_MET_mT2 = asymm_mt2_lester_bisect::get_mT2(
                    tau_vis1_4mom_gen.m(), tau_vis1_4mom_gen.px(), tau_vis1_4mom_gen.py(),
                    tau_vis2_4mom_gen.m(), tau_vis2_4mom_gen.px(), tau_vis2_4mom_gen.py(),
                    input->MET_E_gen*cos(input->MET_phi_gen), input->MET_E_gen*sin(input->MET_phi_gen),
                    0, 0);
                
                output_gen->h1_tau_vis1_tau_vis2_m->Fill((tau_vis1_4mom_gen+tau_vis2_4mom_gen).m());
                output_gen->h1_tau_vis1_tau_vis2_deltaPhi->Fill(Common::getDeltaPhi(tau_vis1_4mom_gen.phi(), tau_vis2_4mom_gen.phi()));
                output_gen->h1_tau_vis1_tau_vis2_deltaR->Fill(tau_vis1_4mom_gen.deltaR(tau_vis2_4mom_gen));
                output_gen->h1_tau_vis1_tau_vis2_MET_mT2->Fill(tau_vis1_tau_vis2_MET_mT2);
                
                MET_pZeta = Common::getPzeta(
                    {{input->MET_E_gen*cos(input->MET_phi_gen), input->MET_E_gen*sin(input->MET_phi_gen)}},
                   
                    {input->v_tau_vis_px_gen->at(tau_visPair_pos[0]), input->v_tau_vis_py_gen->at(tau_visPair_pos[0])},
                    {input->v_tau_vis_px_gen->at(tau_visPair_pos[1]), input->v_tau_vis_py_gen->at(tau_visPair_pos[1])});
                
                tau_vis1_tau_vis2_pZeta = Common::getPzeta(
                    {{input->v_tau_vis_px_gen->at(tau_visPair_pos[0]), input->v_tau_vis_py_gen->at(tau_visPair_pos[0])},
                     {input->v_tau_vis_px_gen->at(tau_visPair_pos[1]), input->v_tau_vis_py_gen->at(tau_visPair_pos[1])}},
                   
                    {input->v_tau_vis_px_gen->at(tau_visPair_pos[0]), input->v_tau_vis_py_gen->at(tau_visPair_pos[0])},
                    {input->v_tau_vis_px_gen->at(tau_visPair_pos[1]), input->v_tau_vis_py_gen->at(tau_visPair_pos[1])});
                
                tau_vis1_tau_vis2_MET_pZeta = Common::getPzeta(
                    {{input->v_tau_vis_px_gen->at(tau_visPair_pos[0]), input->v_tau_vis_py_gen->at(tau_visPair_pos[0])},
                     {input->v_tau_vis_px_gen->at(tau_visPair_pos[1]), input->v_tau_vis_py_gen->at(tau_visPair_pos[1])},
                     {input->MET_E_gen*cos(input->MET_phi_gen), input->MET_E_gen*sin(input->MET_phi_gen)}},
                   
                    {input->v_tau_vis_px_gen->at(tau_visPair_pos[0]), input->v_tau_vis_py_gen->at(tau_visPair_pos[0])},
                    {input->v_tau_vis_px_gen->at(tau_visPair_pos[1]), input->v_tau_vis_py_gen->at(tau_visPair_pos[1])});
                
                output_gen->h1_MET_pZeta->Fill(MET_pZeta);
                output_gen->h1_tau_vis1_tau_vis2_pZeta->Fill(tau_vis1_tau_vis2_pZeta);
                output_gen->h1_tau_vis1_tau_vis2_MET_pZeta->Fill(tau_vis1_tau_vis2_MET_pZeta);
                output_gen->h1_tau_vis1_tau_vis2_MET_Dzeta->Fill(tau_vis1_tau_vis2_MET_pZeta - 1.85*tau_vis1_tau_vis2_pZeta);
            }
            
            
            // GEN b
            input->sort_pT("b");
            
            int b_n_gen = 0;
            
            for(int ib = 0; ib < input->b_n_gen; ib++)
            {
                CLHEP::HepLorentzVector b_4mom_gen;
                
                b_4mom_gen.setT(fabs(input->v_b_E_gen->at(ib)));
                b_4mom_gen.setX(input->v_b_px_gen->at(ib));
                b_4mom_gen.setY(input->v_b_py_gen->at(ib));
                b_4mom_gen.setZ(input->v_b_pz_gen->at(ib));
                
                if(b_4mom_gen.perp() < Common::b_pTcut_reco || fabs(b_4mom_gen.eta()) > Common::b_etaCut_reco)
                {
                    continue;
                }
                
                b_n_gen++;
                
                output_gen->h1_b_pT->Fill(b_4mom_gen.perp());
                output_gen->h1_b_eta->Fill(b_4mom_gen.eta());
                output_gen->h1_b_phi->Fill(b_4mom_gen.phi());
                
                if(b_n_gen && b_n_gen <= 2)
                {
                    output_gen->v_h1_b_pT[b_n_gen-1]->Fill(b_4mom_gen.perp());
                    output_gen->v_h1_b_eta[b_n_gen-1]->Fill(b_4mom_gen.eta());
                    output_gen->v_h1_b_phi[b_n_gen-1]->Fill(b_4mom_gen.phi());
                }
            }
            
            output_gen->h1_b_n->Fill(b_n_gen);
            
            
            // GEN jet
            int jet_n_gen = 0;
            
            double jet_pxSum_gen = 0;
            double jet_pySum_gen = 0;
            
            double jet_HT_gen = 0;
            double jet_MHT_gen = 0;
            
            for(int iJet = 0; iJet < input->jet_n_gen; iJet++)
            {
                CLHEP::HepLorentzVector jet_4mom_gen;
                
                jet_4mom_gen.setT(fabs(input->v_jet_E_gen->at(iJet)));
                jet_4mom_gen.setX(input->v_jet_px_gen->at(iJet));
                jet_4mom_gen.setY(input->v_jet_py_gen->at(iJet));
                jet_4mom_gen.setZ(input->v_jet_pz_gen->at(iJet));
                
                if(jet_4mom_gen.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_gen.eta()) > Common::jet_etaCut_reco)
                {
                    continue;
                }
                
                jet_n_gen++;
                
                jet_pxSum_gen += input->v_jet_px_gen->at(iJet);
                jet_pySum_gen += input->v_jet_py_gen->at(iJet);
                
                jet_HT_gen += jet_4mom_gen.perp();
                
                if(jet_n_gen && jet_n_gen <= 2)
                {
                    output_gen->v_h1_jet_pT[jet_n_gen-1]->Fill(jet_4mom_gen.perp());
                    output_gen->v_h1_jet_eta[jet_n_gen-1]->Fill(jet_4mom_gen.eta());
                    output_gen->v_h1_jet_phi[jet_n_gen-1]->Fill(jet_4mom_gen.phi());
                }
            }
            
            output_gen->h1_jet_n->Fill(jet_n_gen);
            
            if(jet_n_gen)
            {
                jet_MHT_gen = sqrt(jet_pxSum_gen*jet_pxSum_gen + jet_pySum_gen*jet_pySum_gen);
                
                output_gen->h1_jet_HT->Fill(jet_HT_gen);
                output_gen->h1_jet_MHT->Fill(jet_MHT_gen);
                output_gen->h1_jet_Meff->Fill(jet_HT_gen + jet_MHT_gen);
            }
        }
    }
}

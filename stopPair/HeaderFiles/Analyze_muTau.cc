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

# include "Analyze_muTau.h"
# include "Common.h"
# include "CustomInfo_mc.h"
# include "json.h"
# include "Output_GEN.h"
# include "Output_RECO.h"


namespace Analyze_muTau
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
        Analyze_muTau::initialize(
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
        Analyze_muTau::initialize(
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
        Analyze_muTau::initialize(
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
        
        if(isSUSY)
        {
            sprintf(fileName_massPointInfo, "%s/output_genParam/%s/massPointInfo.txt", otherInfoDir, process);
            printf("Mass-point info file: %s \n", fileName_massPointInfo);
            fflush(stdout);
            
            Common::parseCSVto2Dvector(std::string(fileName_massPointInfo), &vv_massPointInfo);
            
            printf("# mass-point: %d \n", vv_massPointInfo.size());
            fflush(stdout);
        }
        
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
        
        char fileName_muIdIsoSF[Common::str_len];
        std::map <std::string, ElMuScaleFactor::ScaleFactor*> m_muTriggerSFobject;
        
        
        // Era
        if(!strcmp(era, "2016"))
        {
            //sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.root");
            
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.root");
            sprintf(fileName_pileUp_data_systUp, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_systUp.root");
            sprintf(fileName_pileUp_data_systDown, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON_systDown.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2016/CSVv2_Moriond17_B_H.csv");
            
            sprintf(fileName_htt_scaleFactor, "resources/htt_scalefactors_v16_5_2.root");
            
            sprintf(fileName_muIdIsoSF, "resources/muonSF/2016/Muon_IdIso_IsoLt0p2_2016BtoH_eff_update1407.root");
            
            m_muTriggerSFobject = {
                {"IsoMu24_OR_TkIsoMu24", new ElMuScaleFactor::ScaleFactor()}
            };
            
            m_muTriggerSFobject.at("IsoMu24_OR_TkIsoMu24")->init_ScaleFactor("resources/muonSF/2016/Muon_IsoMu24_OR_TkIsoMu24_2016BtoH_eff.root");
            
            if(isSUSY)
            {
                sprintf(fileName_bTagCalib, "resources/bTagging/2016/fastsim_csvv2_ttbar_26_1_2017.csv");
            }
        }
        
        else if(!strcmp(era, "2017"))
        {
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.root");
            sprintf(fileName_pileUp_data_systUp, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_systUp.root");
            sprintf(fileName_pileUp_data_systDown, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_systDown.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2017/CSVv2_94XSF_V2_B_F.csv");
            
            sprintf(fileName_muIdIsoSF, "resources/muonSF/2017/Muon_IdIso_IsoLt0.2_eff.root");
            
            m_muTriggerSFobject = {
                {"IsoMu24_OR_IsoMu27", new ElMuScaleFactor::ScaleFactor()}
            };
            
            m_muTriggerSFobject.at("IsoMu24_OR_IsoMu27")->init_ScaleFactor("resources/muonSF/2017/Muon_IsoMu24orIsoMu27.root");
            
            sprintf(fileName_htt_scaleFactor, "resources/htt_scalefactors_2017_v2.root");
        }
        
        else
        {
            printf("Error in Analyze_elMu::initialize(...): Provide a valid era (2016/2017). Provided era: %s", era);
            exit(EXIT_FAILURE);
        }
        
        bTagCalib = BTagCalibration("CSVv2", fileName_bTagCalib);
        
        
        TFile *htt_scaleFactorFile = TFile::Open(fileName_htt_scaleFactor);
        RooWorkspace *htt_scaleFactorWS = (RooWorkspace*) htt_scaleFactorFile->Get("w");
        htt_scaleFactorFile->Close();
        
        
        std::ifstream jsonFileStream("resources/tauTrigger/2016/fitresults_tt_moriond2017.json");
        nlohmann::json diTauTrigger2016json;
        jsonFileStream >> diTauTrigger2016json;
        jsonFileStream.close();
        
        // Remember to delete
        ElMuScaleFactor::ScaleFactor *muIdIsoSFobject = new ElMuScaleFactor::ScaleFactor();
        muIdIsoSFobject->init_ScaleFactor(fileName_muIdIsoSF);
        
        
        //
        TauTriggerSFs2017 diTauTrigger2017_loose(
            "resources/tauTrigger/2017/tauTriggerEfficiencies2017_New.root",
            "resources/tauTrigger/2017/tauTriggerEfficiencies2017.root",
            "loose",
            "dR0p3"
        );
        
        TauTriggerSFs2017 diTauTrigger2017_medium(
            "resources/tauTrigger/2017/tauTriggerEfficiencies2017_New.root",
            "resources/tauTrigger/2017/tauTriggerEfficiencies2017.root",
            "medium",
            "dR0p3"
        );
        
        TauTriggerSFs2017 diTauTrigger2017_tight(
            "resources/tauTrigger/2017/tauTriggerEfficiencies2017_New.root",
            "resources/tauTrigger/2017/tauTriggerEfficiencies2017.root",
            "tight",
            "dR0p3"
            //"MVA"
        );
        
        std::map <std::string, TauTriggerSFs2017*> m_diTauTrigger2017 = {
            {"loose", &diTauTrigger2017_loose},
            {"medium", &diTauTrigger2017_medium},
            {"tight", &diTauTrigger2017_tight}
        };
        
        
        //
        std::string tauInputFileName_fast = "ttbar_mc/output_tauIdIsoEfficiency/TTJets_13TeV-madgraphMLM_FastSim_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root";
        std::string tauInputFileName_full = "ttbar_mc/output_tauIdIsoEfficiency/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root";
        
        std::string tauHistName_num_fast = "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_eta_reco";
        std::string tauHistName_den_fast = "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_all_pT_vs_eta_reco";
        
        std::string tauHistName_num_full = "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_eta_reco";
        std::string tauHistName_den_full = "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_all_pT_vs_eta_reco";
        
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
            
            // RECO histograms
            std::vector <const char*> v_outputOption_reco;
            
            if(isMC)
            {
                v_outputOption_reco = {
                    "PU", "el", "mu", "tau", "muTau", "muMu", "jet", "b", "MET"};
            }
            
            else
            {
                v_outputOption_reco = {
                    "el", "mu", "tau", "muTau", "jet", "muMu", "b", "MET"};
            }
            
            //Output_RECO::Output *output_reco_noTauPairSelection = new Output_RECO::Output(v_outputOption_reco, "noTauPairSelection");
            
            Output_RECO::Output *output_reco_mediumTight_OS = new Output_RECO::Output(v_outputOption_reco, "mediumTight_OS");
            Output_RECO::Output *output_reco_mediumTight_OS_baselineSRB = new Output_RECO::Output(v_outputOption_reco, "mediumTight_OS_baselineSRB");
            Output_RECO::Output *output_reco_mediumTight_OS_baselineSRB_nb0 = new Output_RECO::Output(v_outputOption_reco, "mediumTight_OS_baselineSRB_nb0");
            
            std::map <std::pair <int, int>, Output_RECO::Output*> m_output_reco_stopPair_OS_genMatched_baselineSRB;
            
            for(int iSRA = 0; iSRA < 6; iSRA++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRA%d", iSRA+1);
                
                output_reco_mediumTight_OS->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                output_reco_mediumTight_OS_baselineSRB->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
                output_reco_mediumTight_OS_baselineSRB_nb0->addCutFlow(5, "SRA"+std::to_string(iSRA+1));
            }
            
            for(int iSRB = 0; iSRB < 18; iSRB++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRB%d", iSRB+1);
                
                output_reco_mediumTight_OS->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                output_reco_mediumTight_OS_baselineSRB->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                output_reco_mediumTight_OS_baselineSRB_nb0->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
            }
            
            for(int iSRC = 0; iSRC < 18; iSRC++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRC%d", iSRC+1);
                
                output_reco_mediumTight_OS->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                output_reco_mediumTight_OS_baselineSRB->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
                output_reco_mediumTight_OS_baselineSRB_nb0->addCutFlow(6, "SRC"+std::to_string(iSRC+1));
            }
            
            for(int iSRD = 0; iSRD < 18; iSRD++)
            {
                char tempStr[Common::str_len];
                sprintf(tempStr, "SRD%d", iSRD+1);
                
                output_reco_mediumTight_OS->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                output_reco_mediumTight_OS_baselineSRB->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
                output_reco_mediumTight_OS_baselineSRB_nb0->addCutFlow(6, "SRD"+std::to_string(iSRD+1));
            }
            
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            
            std::string eventSelectionStr = "muTau_m_reco > 40 and muTau_m_reco < 120";
            std::string eventSelectionStr_baselineSRB = "(muTau_m_reco > 40 and muTau_m_reco < 120) and MET_E_reco >= 50 and muTau_jet_HT_reco >= 100 and b_n_reco >= 1";
            std::string eventSelectionStr_baselineSRB_nb0 = "(muTau_m_reco > 40 and muTau_m_reco < 120) and MET_E_reco >= 50 and muTau_jet_HT_reco >= 100 and b_n_reco == 0";
            
            // Analyze
            if(isMC)
            {
                //
                Analyze_muTau::analyze_reco(
                    input_mc,
                    output_reco_mediumTight_OS,
                    0,
                    "tight", "OS",
                    eventSelectionStr,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    tauFastFullSimSFinfo,
                    diTauTrigger2016json,
                    m_diTauTrigger2017,
                    htt_scaleFactorWS,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex
                );
                
                printf("\n");
                
                
                //
                Analyze_muTau::analyze_reco(
                    input_mc,
                    output_reco_mediumTight_OS_baselineSRB,
                    0,
                    "tight", "OS",
                    eventSelectionStr_baselineSRB,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    tauFastFullSimSFinfo,
                    diTauTrigger2016json,
                    m_diTauTrigger2017,
                    htt_scaleFactorWS,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex
                );
                
                printf("\n");
                
                
                //
                Analyze_muTau::analyze_reco(
                    input_mc,
                    output_reco_mediumTight_OS_baselineSRB_nb0,
                    0,
                    "tight", "OS",
                    eventSelectionStr_baselineSRB_nb0,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    tauFastFullSimSFinfo,
                    diTauTrigger2016json,
                    m_diTauTrigger2017,
                    htt_scaleFactorWS,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex
                );
                
                printf("\n");
            }
            
            else
            {
                //
                Analyze_muTau::analyze_reco(
                    input_data,
                    output_reco_mediumTight_OS,
                    0,
                    "tight", "OS",
                    eventSelectionStr,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    tauFastFullSimSFinfo,
                    diTauTrigger2016json,
                    m_diTauTrigger2017,
                    htt_scaleFactorWS,
                    0,
                    "",
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex
                );
                
                printf("\n");
                
                
                //
                Analyze_muTau::analyze_reco(
                    input_data,
                    output_reco_mediumTight_OS_baselineSRB,
                    0,
                    "tight", "OS",
                    eventSelectionStr_baselineSRB,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    tauFastFullSimSFinfo,
                    diTauTrigger2016json,
                    m_diTauTrigger2017,
                    htt_scaleFactorWS,
                    0,
                    "",
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex
                );
                
                printf("\n");
                
                
                //
                Analyze_muTau::analyze_reco(
                    input_data,
                    output_reco_mediumTight_OS_baselineSRB_nb0,
                    0,
                    "tight", "OS",
                    eventSelectionStr_baselineSRB_nb0,
                    isMC,
                    isSUSY,
                    era,
                    massPoint_stop1_neutralino1,
                    v_eventWeight_nJetBin,
                    muIdIsoSFobject,
                    &m_muTriggerSFobject,
                    tauFastFullSimSFinfo,
                    diTauTrigger2016json,
                    m_diTauTrigger2017,
                    htt_scaleFactorWS,
                    0,
                    "",
                    m_correction,
                    syst_name,
                    syst_type,
                    scaleVariationIndex
                );
                
                printf("\n");
            }
            
            printf("\n\n");
            
            
            // Write
            output_analyzed->mkdir("reco");
            //output_analyzed->cd("reco");
            
            char dirName[Common::str_len];
            
            sprintf(dirName, "reco/%s", output_reco_mediumTight_OS->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            output_reco_mediumTight_OS->writeData();
            
            sprintf(dirName, "reco/%s", output_reco_mediumTight_OS_baselineSRB->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            output_reco_mediumTight_OS_baselineSRB->writeData();
            
            sprintf(dirName, "reco/%s", output_reco_mediumTight_OS_baselineSRB_nb0->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            output_reco_mediumTight_OS_baselineSRB_nb0->writeData();
            
            
            // Release memory
            output_reco_mediumTight_OS->freeMemory();
            output_reco_mediumTight_OS_baselineSRB->freeMemory();
            output_reco_mediumTight_OS_baselineSRB_nb0->freeMemory();
            
            delete output_reco_mediumTight_OS;
            delete output_reco_mediumTight_OS_baselineSRB;
            delete output_reco_mediumTight_OS_baselineSRB_nb0;
            
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

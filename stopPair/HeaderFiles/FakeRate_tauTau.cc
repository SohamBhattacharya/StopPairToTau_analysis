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
# include "Output_RECO.h"
# include "FakeRate_tauTau.h"


namespace FakeRate_tauTau
{
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era
    )
    {
        initialize(
            process,
            dir,
            otherInfoDir,
            sourceFileName,
            isMC,
            era,
            {}
        );
    }
    
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::vector <double> v_eventWeight_nJetBin
    )
    {
        printf("\n");
        printf("********** Era: %s ********** \n", era.c_str());
        printf("\n");
        
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process.c_str(), process.c_str());
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName.c_str());
        
        std::string inFile;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        //sprintf(outDir, "output_tauFakeRate_tauTau/%s", dir.c_str());
        sprintf(outDir, "%s", dir.c_str());
        
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
        
        asymm_mt2_lester_bisect::disableCopyrightMessage();
        
        char fileName_pileUp_mc[Common::str_len];
        sprintf(fileName_pileUp_mc, "%s/output_pileUp/%s/custom_all_pileUp.root", otherInfoDir.c_str(), process.c_str());
        char histName_pileUp_mc[Common::str_len];
        sprintf(histName_pileUp_mc, "pileup");
        
        char fileName_pileUp_data[Common::str_len];
        //sprintf(fileName_pileUp_data, "../tauTau_data/output_pileUp/Tau/pileUpDistribution_2016H.root");
        //sprintf(fileName_pileUp_data, "../resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.root");
        sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.root");
        char histName_pileUp_data[Common::str_len];
        sprintf(histName_pileUp_data, "pileup");
        
        char fileName_bTaggingEfficiency[Common::str_len];
        sprintf(fileName_bTaggingEfficiency, "%s/output_bTaggingEfficiency/%s/bTaggingEfficiency.root", otherInfoDir.c_str(), process.c_str());
        //BTagCalibration bTagCalib("CSVv2_Moriond17_B_H", "../resources/bTagging/CSVv2_Moriond17_B_H.csv");
        //BTagCalibration bTagCalib("CSVv2_Moriond17_B_H", "resources/bTagging/CSVv2_Moriond17_B_H.csv");
        BTagCalibration bTagCalib;
        
        // Remember to delete
        TauEfficiencyAndSF::TauEfficiencyAndSF *tauEffSFobject = 0;/*new TauEfficiencyAndSF::TauEfficiencyAndSF(
            //"../DYJetsToLL_mc/output_tauIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
            //"DYJetsToLL_mc/output_tauIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
            "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
            "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_vs_eta_reco",
            "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_vis_pT_vs_eta_gen"
        );*/
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {
            //n++; if(n > 50) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFile.substr(inFile.rfind("/")+1, inFile.rfind(".root")-inFile.rfind("/")-1)).c_str());
            
            char outFile[Common::str_len];
            sprintf(outFile, "%s/%s_fakeRate_tauTau.root", outDir, fileNameStripped);
            fflush(stdout);
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("Output: %s \n", outFile);
            printf("\n");
            
            std::vector <const char*> v_object_mc_gen = {
                "genParam", "el", "mu", "tau_vis", "b", "jet", "MET"
            };
            
            std::vector <const char*> v_object_reco;
            
            if(isMC)
            {
                v_object_reco = { \
                    "PU", "el", "mu", "tau", "jet", "MET", "trigger"};
            }
            
            else
            {
                v_object_reco = { \
                    "vertex", "el", "mu", "tau", "jet", "MET", "trigger"};
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
                    fileName_pileUp_data, histName_pileUp_data
                );
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
                v_outputOption_reco = { \
                    "PU", "tau", "tauTau", "jet", "b", "MET"};
            }
            
            else
            {
                v_outputOption_reco = { \
                    "tau", "tauTau", "jet", "b", "MET"};
            }
            
            
            Output_RECO::Output *output_reco_vlooseVLoose_dR03_SS = new Output_RECO::Output(v_outputOption_reco, "vlooseVLoose_dR03_SS");
            Output_RECO::Output *output_reco_looseLoose_dR03_SS = new Output_RECO::Output(v_outputOption_reco, "looseLoose_dR03_SS");
            
            Output_RECO::Output *output_reco_tightVLoose_dR03_SS = new Output_RECO::Output(v_outputOption_reco, "tightVLoose_dR03_SS");
            Output_RECO::Output *output_reco_tightLoose_dR03_SS = new Output_RECO::Output(v_outputOption_reco, "tightLoose_dR03_SS");
            
            Output_RECO::Output *output_reco_tightTight_dR03_SS = new Output_RECO::Output(v_outputOption_reco, "tightTight_dR03_SS");
            
            //Output_RECO::Output *output_reco_vtightLoose_dR03_SS = new Output_RECO::Output(v_outputOption_reco, "vtightLoose_dR03_SS");
            //Output_RECO::Output *output_reco_vtightVTight_dR03_SS = new Output_RECO::Output(v_outputOption_reco, "vtightVTight_dR03_SS");
            
            Output_RECO::Output *output_reco_looseLoose_dR03_OS_lepToTau = new Output_RECO::Output(v_outputOption_reco, "looseLoose_dR03_OS_lepToTau");
            Output_RECO::Output *output_reco_tightLoose_dR03_OS_lepToTau = new Output_RECO::Output(v_outputOption_reco, "tightLoose_dR03_OS_lepToTau");
            Output_RECO::Output *output_reco_tightTight_dR03_OS_lepToTau = new Output_RECO::Output(v_outputOption_reco, "tightTight_dR03_OS_lepToTau");
            
            
            Output_RECO::Output *output_reco_looseLoose_SS = new Output_RECO::Output(v_outputOption_reco, "looseLoose_SS");
            Output_RECO::Output *output_reco_tightLoose_SS = new Output_RECO::Output(v_outputOption_reco, "tightLoose_SS");
            Output_RECO::Output *output_reco_tightTight_SS = new Output_RECO::Output(v_outputOption_reco, "tightTight_SS");
            
            
            std::vector <double> *v_tau_vlooseIsolation_dR03;
            std::vector <double> *v_tau_looseIsolation_dR03;
            std::vector <double> *v_tau_tightIsolation_dR03;
            std::vector <double> *v_tau_vtightIsolation_dR03;
            
            std::vector <double> *v_tau_looseIsolation;
            std::vector <double> *v_tau_tightIsolation;
            std::vector <double> *v_tau_vtightIsolation;
            
            std::vector <double> *v_tau_vLooseDeepTau2017v2p1VSjet;
            std::vector <double> *v_tau_looseDeepTau2017v2p1VSjet;
            std::vector <double> *v_tau_tightDeepTau2017v2p1VSjet;
            
            // Era
            if(!era.compare("2016"))
            {
                if(isMC)
                {
                    v_tau_vlooseIsolation_dR03 = input_mc->v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    v_tau_looseIsolation_dR03 = input_mc->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    v_tau_tightIsolation_dR03 = input_mc->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    v_tau_vtightIsolation_dR03 = input_mc->v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    
                    v_tau_looseIsolation = input_mc->v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco;
                    v_tau_tightIsolation = input_mc->v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco;
                    v_tau_vtightIsolation = input_mc->v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco;
                    
                    v_tau_vLooseDeepTau2017v2p1VSjet = input_mc->v_tau_byVLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_looseDeepTau2017v2p1VSjet = input_mc->v_tau_byLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_tightDeepTau2017v2p1VSjet = input_mc->v_tau_byTightDeepTau2017v2p1VSjet_reco;
                }
                
                else
                {
                    v_tau_vlooseIsolation_dR03 = input_data->v_tau_byVLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    v_tau_looseIsolation_dR03 = input_data->v_tau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    v_tau_tightIsolation_dR03 = input_data->v_tau_byTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    v_tau_vtightIsolation_dR03 = input_data->v_tau_byVTightIsolationMVArun2v1DBdR03oldDMwLT_reco;
                    
                    v_tau_looseIsolation = input_data->v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco;
                    v_tau_tightIsolation = input_data->v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco;
                    v_tau_vtightIsolation = input_data->v_tau_byVTightIsolationMVArun2v1DBoldDMwLT_reco;
                    
                    v_tau_vLooseDeepTau2017v2p1VSjet = input_data->v_tau_byVLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_looseDeepTau2017v2p1VSjet = input_data->v_tau_byLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_tightDeepTau2017v2p1VSjet = input_data->v_tau_byTightDeepTau2017v2p1VSjet_reco;
                }
            }
            
            else if(!era.compare("2017"))
            {
                if(isMC)
                {
                    v_tau_vlooseIsolation_dR03 = input_mc->v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    v_tau_looseIsolation_dR03 = input_mc->v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    v_tau_tightIsolation_dR03 = input_mc->v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    v_tau_vtightIsolation_dR03 = input_mc->v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    
                    v_tau_looseIsolation = input_mc->v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco;
                    v_tau_tightIsolation = input_mc->v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco;
                    v_tau_vtightIsolation = input_mc->v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco;
                    
                    v_tau_vLooseDeepTau2017v2p1VSjet = input_mc->v_tau_byVLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_looseDeepTau2017v2p1VSjet = input_mc->v_tau_byLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_tightDeepTau2017v2p1VSjet = input_mc->v_tau_byTightDeepTau2017v2p1VSjet_reco;
                }
                
                else
                {
                    v_tau_vlooseIsolation_dR03 = input_data->v_tau_byVLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    v_tau_looseIsolation_dR03 = input_data->v_tau_byLooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    v_tau_tightIsolation_dR03 = input_data->v_tau_byTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    v_tau_vtightIsolation_dR03 = input_data->v_tau_byVTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_reco;
                    
                    v_tau_looseIsolation = input_data->v_tau_byLooseIsolationMVArun2017v2DBoldDMwLT2017_reco;
                    v_tau_tightIsolation = input_data->v_tau_byTightIsolationMVArun2017v2DBoldDMwLT2017_reco;
                    v_tau_vtightIsolation = input_data->v_tau_byVTightIsolationMVArun2017v2DBoldDMwLT2017_reco;
                    
                    v_tau_vLooseDeepTau2017v2p1VSjet = input_data->v_tau_byVLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_looseDeepTau2017v2p1VSjet = input_data->v_tau_byLooseDeepTau2017v2p1VSjet_reco;
                    v_tau_tightDeepTau2017v2p1VSjet = input_data->v_tau_byTightDeepTau2017v2p1VSjet_reco;
                }
            }
            
            else
            {
                printf("Error in FakeRate_tauTau::initialize(...): Provide a valid era (2016/2017). Provided era: %s", era);
                exit(EXIT_FAILURE);
            }
            
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            std::string eventSelectionStr = "MET_E_reco < 50";
            //std::string eventSelectionStr = "MET_E_reco < 20";
            
            std::string eventSelectionStr_lepToTau = "tau_vis_n_gen == 0 and areTausLeptonMatched";
            //std::string eventSelectionStr_lepToTau = "1";
           
            // Analyze
            if(isMC)
            {
                // Deep tau
                FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_looseLoose_dR03_OS_lepToTau,
                    "OS",
                    "loose", v_tau_looseDeepTau2017v2p1VSjet,
                    "loose", v_tau_looseDeepTau2017v2p1VSjet,
                    eventSelectionStr_lepToTau,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_tightLoose_dR03_OS_lepToTau,
                    "OS",
                    "tight", v_tau_tightDeepTau2017v2p1VSjet,
                    "loose", v_tau_looseDeepTau2017v2p1VSjet,
                    eventSelectionStr_lepToTau,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_tightTight_dR03_OS_lepToTau,
                    "OS",
                    "tight", v_tau_tightDeepTau2017v2p1VSjet,
                    "tight", v_tau_tightDeepTau2017v2p1VSjet,
                    eventSelectionStr_lepToTau,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                
                //FakeRate_tauTau::analyze_reco(
                //    input_mc,
                //    output_reco_looseLoose_dR03_OS_lepToTau,
                //    "OS",
                //    "loose", v_tau_looseIsolation_dR03,
                //    "loose", v_tau_looseIsolation_dR03,
                //    eventSelectionStr_lepToTau,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_mc,
                //    output_reco_tightLoose_dR03_OS_lepToTau,
                //    "OS",
                //    "tight", v_tau_tightIsolation_dR03,
                //    "loose", v_tau_looseIsolation_dR03,
                //    eventSelectionStr_lepToTau,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_mc,
                //    output_reco_tightTight_dR03_OS_lepToTau,
                //    "OS",
                //    "tight", v_tau_tightIsolation_dR03,
                //    "tight", v_tau_tightIsolation_dR03,
                //    eventSelectionStr_lepToTau,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                
                
                // dR03
                /*FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_looseLoose_dR03_SS,
                    "SS",
                    "loose", v_tau_looseIsolation_dR03,
                    "loose", v_tau_looseIsolation_dR03,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_tightLoose_dR03_SS,
                    "SS",
                    "tight", v_tau_tightIsolation_dR03,
                    "loose", v_tau_looseIsolation_dR03,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_tightTight_dR03_SS,
                    "SS",
                    "tight", v_tau_tightIsolation_dR03,
                    "tight", v_tau_tightIsolation_dR03,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_vtightLoose_dR03_SS,
                    "SS",
                    "vtight", v_tau_vtightIsolation_dR03,
                    "loose", v_tau_looseIsolation_dR03,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_mc,
                    output_reco_vtightVTight_dR03_SS,
                    "SS",
                    "vtight", v_tau_vtightIsolation_dR03,
                    "vtight", v_tau_vtightIsolation_dR03,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                
                // dR05
                //FakeRate_tauTau::analyze_reco(
                //    input_mc,
                //    output_reco_tightLoose_SS,
                //    "SS",
                //    "tight", input_mc->v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco,
                //    "loose", input_mc->v_tau_byLooseIsolationMVArun2v1DBoldDMwLT_reco,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_mc,
                //    output_reco_tightTight_SS,
                //    "SS",
                //    "tight", input_mc->v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco,
                //    "tight", input_mc->v_tau_byTightIsolationMVArun2v1DBoldDMwLT_reco,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);*/
            }
            
            else
            {
                FakeRate_tauTau::analyze_reco(
                    input_data,
                    output_reco_vlooseVLoose_dR03_SS,
                    "SS",
                    "vloose", v_tau_vLooseDeepTau2017v2p1VSjet,
                    "vloose", v_tau_vLooseDeepTau2017v2p1VSjet,
                    eventSelectionStr,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_data,
                    output_reco_looseLoose_dR03_SS,
                    "SS",
                    "loose", v_tau_looseDeepTau2017v2p1VSjet,
                    "loose", v_tau_looseDeepTau2017v2p1VSjet,
                    eventSelectionStr,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_data,
                    output_reco_tightVLoose_dR03_SS,
                    "SS",
                    "tight", v_tau_tightDeepTau2017v2p1VSjet,
                    "vloose", v_tau_vLooseDeepTau2017v2p1VSjet,
                    eventSelectionStr,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_data,
                    output_reco_tightLoose_dR03_SS,
                    "SS",
                    "tight", v_tau_tightDeepTau2017v2p1VSjet,
                    "loose", v_tau_looseDeepTau2017v2p1VSjet,
                    eventSelectionStr,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                FakeRate_tauTau::analyze_reco(
                    input_data,
                    output_reco_tightTight_dR03_SS,
                    "SS",
                    "tight", v_tau_tightDeepTau2017v2p1VSjet,
                    "tight", v_tau_tightDeepTau2017v2p1VSjet,
                    eventSelectionStr,
                    isMC,
                    era,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    v_eventWeight_nJetBin
                );
                
                printf("\n");
                
                
                // dR03
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_vlooseVLoose_dR03_SS,
                //    "SS",
                //    "vloose", v_tau_vlooseIsolation_dR03,
                //    "vloose", v_tau_vlooseIsolation_dR03,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_looseLoose_dR03_SS,
                //    "SS",
                //    "loose", v_tau_looseIsolation_dR03,
                //    "loose", v_tau_looseIsolation_dR03,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_tightVLoose_dR03_SS,
                //    "SS",
                //    "tight", v_tau_tightIsolation_dR03,
                //    "vloose", v_tau_vlooseIsolation_dR03,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_tightLoose_dR03_SS,
                //    "SS",
                //    "tight", v_tau_tightIsolation_dR03,
                //    "loose", v_tau_looseIsolation_dR03,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_tightTight_dR03_SS,
                //    "SS",
                //    "tight", v_tau_tightIsolation_dR03,
                //    "tight", v_tau_tightIsolation_dR03,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_vtightLoose_dR03_SS,
                //    "SS",
                //    "vtight", v_tau_vtightIsolation_dR03,
                //    "loose", v_tau_looseIsolation_dR03,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_vtightVTight_dR03_SS,
                //    "SS",
                //    "vtight", v_tau_vtightIsolation_dR03,
                //    "vtight", v_tau_vtightIsolation_dR03,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                
                
                // dR05
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_looseLoose_SS,
                //    "SS",
                //    "loose", v_tau_looseIsolation,
                //    "loose", v_tau_looseIsolation,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_tightLoose_SS,
                //    "SS",
                //    "tight", v_tau_tightIsolation,
                //    "loose", v_tau_looseIsolation,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
                //
                //printf("\n");
                //
                //FakeRate_tauTau::analyze_reco(
                //    input_data,
                //    output_reco_tightTight_SS,
                //    "SS",
                //    "tight", v_tau_tightIsolation,
                //    "tight", v_tau_tightIsolation,
                //    eventSelectionStr,
                //    isMC,
                //    era,
                //    &bTagCalib,
                //    fileName_bTaggingEfficiency,
                //    tauEffSFobject,
                //    v_eventWeight_nJetBin
                //);
            }
            
            printf("\n\n");
            
            
            // Write output
            std::string dirName;
            
            // dR03
            dirName = "vlooseVLoose_dR03_SS";
            output_analyzed->mkdir(dirName.c_str());
            output_analyzed->cd(dirName.c_str());
            output_reco_vlooseVLoose_dR03_SS->writeData();
            
            dirName = "looseLoose_dR03_SS";
            output_analyzed->mkdir(dirName.c_str());
            output_analyzed->cd(dirName.c_str());
            output_reco_looseLoose_dR03_SS->writeData();
            
            dirName = "tightVLoose_dR03_SS";
            output_analyzed->mkdir(dirName.c_str());
            output_analyzed->cd(dirName.c_str());
            output_reco_tightVLoose_dR03_SS->writeData();
            
            dirName = "tightLoose_dR03_SS";
            output_analyzed->mkdir(dirName.c_str());
            output_analyzed->cd(dirName.c_str());
            output_reco_tightLoose_dR03_SS->writeData();
            
            dirName = "tightTight_dR03_SS";
            output_analyzed->mkdir(dirName.c_str());
            output_analyzed->cd(dirName.c_str());
            output_reco_tightTight_dR03_SS->writeData();
            
            //dirName = "vtightLoose_dR03_SS";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_vtightLoose_dR03_SS->writeData();
            //
            //dirName = "vtightVTight_dR03_SS";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_vtightVTight_dR03_SS->writeData();
            
            
            //dirName = "looseLoose_dR03_OS_lepToTau";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_looseLoose_dR03_OS_lepToTau->writeData();
            //
            //dirName = "tightLoose_dR03_OS_lepToTau";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_tightLoose_dR03_OS_lepToTau->writeData();
            //
            //dirName = "tightTight_dR03_OS_lepToTau";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_tightTight_dR03_OS_lepToTau->writeData();
            
            
            
            // dR05
            //dirName = "looseLoose_SS";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_looseLoose_SS->writeData();
            //
            //dirName = "tightLoose_SS";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_tightLoose_SS->writeData();
            //
            //dirName = "tightTight_SS";
            //output_analyzed->mkdir(dirName.c_str());
            //output_analyzed->cd(dirName.c_str());
            //output_reco_tightTight_SS->writeData();
            
            // Release memory
            output_reco_vlooseVLoose_dR03_SS->freeMemory();
            output_reco_looseLoose_dR03_SS->freeMemory();
            output_reco_tightVLoose_dR03_SS->freeMemory();
            output_reco_tightLoose_dR03_SS->freeMemory();
            output_reco_tightTight_dR03_SS->freeMemory();
            //output_reco_vtightLoose_dR03_SS->freeMemory();
            //output_reco_vtightVTight_dR03_SS->freeMemory();
            
            output_reco_looseLoose_dR03_OS_lepToTau->freeMemory();
            output_reco_tightLoose_dR03_OS_lepToTau->freeMemory();
            output_reco_tightTight_dR03_OS_lepToTau->freeMemory();
            
            output_reco_looseLoose_SS->freeMemory();
            output_reco_tightLoose_SS->freeMemory();
            output_reco_tightTight_SS->freeMemory();
            
            delete output_reco_vlooseVLoose_dR03_SS;
            delete output_reco_looseLoose_dR03_SS;
            delete output_reco_tightVLoose_dR03_SS;
            delete output_reco_tightLoose_dR03_SS;
            delete output_reco_tightTight_dR03_SS;
            //delete output_reco_vtightLoose_dR03_SS;
            //delete output_reco_vtightVTight_dR03_SS;
            
            delete output_reco_looseLoose_dR03_OS_lepToTau;
            delete output_reco_tightLoose_dR03_OS_lepToTau;
            delete output_reco_tightTight_dR03_OS_lepToTau;
            
            delete output_reco_looseLoose_SS;
            delete output_reco_tightLoose_SS;
            delete output_reco_tightTight_SS;
            
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
        
        delete tauEffSFobject;
    }

}

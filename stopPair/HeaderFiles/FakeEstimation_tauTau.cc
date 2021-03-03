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
# include "FakeEstimation_tauTau.h"


namespace FakeEstimation_tauTau
{
    RunInfo::RunInfo(
        std::string term,
        std::string expression,
        std::vector <double> *v_tau1_isolation, std::vector <double> *v_tau1_antiIsolation,
        std::vector <double> *v_tau2_isolation, std::vector <double> *v_tau2_antiIsolation,
        //std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        std::vector <const char*> v_outputOption_reco
    )
    {
        this->expression = expression;
        this->term = term;
        
        //if(expression.length() && term.length())
        //{
        //    details = term + ": " + expression;
        //}
        //
        //else if(expression.length())
        //{
        //    details = expression;
        //}
        //
        //else if(term.length())
        //{
        //    details = term;
        //}
        //
        //else
        //{
        //    printf("Error in FakeEstimation_tauTau::RunInfo::RunInfo(...): Both \"expression\" and \"term\" cannot be empty. \n");
        //    
        //    exit(EXIT_FAILURE);
        //}
        
        details = term;
        
        this->v_tau1_isolation = v_tau1_isolation;
        this->v_tau2_isolation = v_tau2_isolation;
        
        this->v_tau1_antiIsolation = v_tau1_antiIsolation;
        this->v_tau2_antiIsolation = v_tau2_antiIsolation;
        
        //this->m_eventSelection = m_eventSelection;
        this->eventSelectionStr = eventSelectionStr;
        
        output_reco = new Output_RECO::Output(v_outputOption_reco, details.c_str());
    }
    
    
    void RunInfo::freeMemory()
    {
        delete output_reco;
    }
    
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::string syst_name,
        Common::SYST_TYPE syst_type
    )
    {
        initialize(
            process,
            dir,
            otherInfoDir,
            sourceFileName,
            isMC,
            era,
            {},
            syst_name,
            syst_type
        );
    }
    
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::vector <double> v_eventWeight_nJetBin,
        std::string syst_name,
        Common::SYST_TYPE syst_type
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
        //sprintf(outDir, "output_tauFakeEstimation_tauTau/%s", dir.c_str());
        //sprintf(outDir, "%s", dir.c_str());
        sprintf(outDir, "%s%s", dir.c_str(), Common::getSystSuffix(syst_name, syst_type).c_str());
        
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
        char histName_pileUp_data[Common::str_len];
        sprintf(histName_pileUp_data, "pileup");
        
        char fileName_bTaggingEfficiency[Common::str_len];
        sprintf(fileName_bTaggingEfficiency, "%s/output_bTaggingEfficiency/%s/bTaggingEfficiency.root", otherInfoDir.c_str(), process.c_str());
        
        char fileName_bTagCalib[Common::str_len];
        BTagCalibration bTagCalib;
        
        std::vector <std::string> v_tauPromptRateFile;
        std::vector <std::string> v_tauFakeRateFile;
        
        // Era
        if(!era.compare("2016"))
        {
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.root");
            //sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2016/DeepJet_2016LegacySF_WP_V1.csv");
            
            v_tauPromptRateFile = {
                "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root"
            };
            
            v_tauFakeRateFile = {
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-17Jul2018_ver2-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
            };
        }
        
        else if(!era.compare("2017"))
        {
            sprintf(fileName_pileUp_data, "resources/pileup/pileUpDistribution_Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.root");
            
            sprintf(fileName_bTagCalib, "resources/bTagging/2017/DeepFlavour_94XSF_WP_V3_B_F.csv");
            
            v_tauPromptRateFile = {
                "ttbar_mc/output_tauIdIsoEfficiency/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root"
            };
            
            v_tauFakeRateFile = {
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2017B-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2017C-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2017D-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2017E-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
                "tauTau_data/output_tauTau_fakeRate/Tau_Run2017F-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root"
            };
        }
        
        else
        {
            printf("Error in Analyze_elMu::initialize(...): Provide a valid era (2016/2017). Provided era: %s", era);
            exit(EXIT_FAILURE);
        }
        
        bTagCalib = BTagCalibration("DeepFlav", fileName_bTagCalib);
        
        // Remember to delete
        TauEfficiencyAndSF::TauEfficiencyAndSF *tauEffSFobject = 0;/*new TauEfficiencyAndSF::TauEfficiencyAndSF(
            //"../DYJetsToLL_mc/output_tauIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
            //"DYJetsToLL_mc/output_tauIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
            "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
            "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_vs_eta_reco",
            "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_vis_pT_vs_eta_gen"
        );*/
        
        
        
        TauPromptAndFakeRate::TauPromptAndFakeRate *tauPandFobject = new TauPromptAndFakeRate::TauPromptAndFakeRate(
            v_tauPromptRateFile,
            "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_DM_reco",
            "LooseDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_DM_reco",
            
            v_tauFakeRateFile,
            "tightLoose_dR03_SS/tau_pT_vs_DM_reco_tightLoose_dR03_SS",
            "looseLoose_dR03_SS/tau_pT_vs_DM_reco_looseLoose_dR03_SS",
            "tightTight_dR03_SS/tau_pT_vs_DM_reco_tightTight_dR03_SS",
            "tightLoose_dR03_SS/tau_pT_vs_DM_reco_tightLoose_dR03_SS",
            
            Common::v_tau_promptFake_pTbin
        );
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {
            //n++; if(n > 10) break;
            
            char fileNameStripped[Common::str_len];
            sprintf(fileNameStripped, "%s", (inFile.substr(inFile.rfind("/")+1, inFile.rfind(".root")-inFile.rfind("/")-1)).c_str());
            
            char outFile[Common::str_len];
            sprintf(outFile, "%s/%s_fakeEstimation_tauTau.root", outDir, fileNameStripped);
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
                    "el", "mu", "tau", "jet", "MET", "trigger"};
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
                    0, 0,//fileName_pileUp_mc, histName_pileUp_mc,
                    0, 0//fileName_pileUp_data, histName_pileUp_data
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
            
            
            std::vector <double> *v_tau_looseIsolation_dR03;
            std::vector <double> *v_tau_tightIsolation_dR03;
            std::vector <double> *v_tau_vtightIsolation_dR03;
            
            // Era
            if(!era.compare("2016"))
            {
                v_tau_looseIsolation_dR03 = input_data->v_tau_byLooseDeepTau2017v2p1VSjet_reco;
                v_tau_tightIsolation_dR03 = input_data->v_tau_byTightDeepTau2017v2p1VSjet_reco;
                v_tau_vtightIsolation_dR03 = input_data->v_tau_byVTightDeepTau2017v2p1VSjet_reco;
            }
            
            else if(!era.compare("2017"))
            {
                v_tau_looseIsolation_dR03 = input_data->v_tau_byLooseDeepTau2017v2p1VSjet_reco;
                v_tau_tightIsolation_dR03 = input_data->v_tau_byTightDeepTau2017v2p1VSjet_reco;
                v_tau_vtightIsolation_dR03 = input_data->v_tau_byVTightDeepTau2017v2p1VSjet_reco;
            }
            
            
            std::string expression_common_Nff = " * (f1*f2) / ((p1-f1)*(p2-f2))";
            std::string expression_common_Nfp = " / ((p1-f1)*(p2-f2))";
            
            
            ////////////////////////////////////////////////////////////
            //////////////////// SS_baselineSRB_nbAny ////////////////////
            ////////////////////////////////////////////////////////////
            
            std::vector <RunInfo*> v_runInfo_SS_baselineSRB_nbAny;
            
            std::map <std::string, bool> m_eventSelection_SS_baselineSRB_nbAny;
            
            m_eventSelection_SS_baselineSRB_nbAny["MET_E_reco >= 50"] = true;
            m_eventSelection_SS_baselineSRB_nbAny["tauTau_jet_HT_reco >= 100"] = true;
            m_eventSelection_SS_baselineSRB_nbAny["b_n_reco >= 1"] = true;
            
            std::string eventSelectionStr_SS_baselineSRB_nbAny = "MET_E_reco >= 50 and tauTau_jet_HT_reco >= 100";
            
            // N_ff
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nff_Nll_SS_baselineSRB_nbAny",
                "p1*p2" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nff_Nlt_SS_baselineSRB_nbAny",
                "p1*(1-p2)" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nff_Ntl_SS_baselineSRB_nbAny",
                "p2*(1-p1)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nff_Ntt_SS_baselineSRB_nbAny",
                "(1-p1)*(1-p2)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            
            // N_f/p
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nfp_Nll_SS_baselineSRB_nbAny",
                "2*f1*f2*p1*p2" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nfp_Nlt_SS_baselineSRB_nbAny",
                "(f1*f2*p1*(1-p2) + p1*p2*f1*(1-f2))" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nfp_Ntl_SS_baselineSRB_nbAny",
                "(p1*p2*f2*(1-f1) + f1*f2*p2*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            v_runInfo_SS_baselineSRB_nbAny.push_back(new RunInfo(
                "Nfp_Ntt_SS_baselineSRB_nbAny",
                "(f2*p1*(1-f1)*(1-p2) + f1*p2*(1-f2)*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_SS_baselineSRB_nbAny,
                eventSelectionStr_SS_baselineSRB_nbAny,
                v_outputOption_reco
            ));
            
            
            ////////////////////////////////////////////////////////////
            //////////////////// OS_baselineSRB_nb0 ////////////////////
            ////////////////////////////////////////////////////////////
            
            std::vector <RunInfo*> v_runInfo_OS_baselineSRB_nb0;
            
            std::map <std::string, bool> m_eventSelection_OS_baselineSRB_nb0;
            
            m_eventSelection_OS_baselineSRB_nb0["MET_E_reco >= 50"] = true;
            m_eventSelection_OS_baselineSRB_nb0["tauTau_jet_HT_reco >= 100"] = true;
            m_eventSelection_OS_baselineSRB_nb0["b_n_reco == 0"] = true;
            
            std::string eventSelectionStr_OS_baselineSRB_nb0 = "MET_E_reco >= 50 and tauTau_jet_HT_reco >= 100 and b_n_reco == 0";
            
            // N_ff
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nff_Nll_OS_baselineSRB_nb0",
                "p1*p2" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nff_Nlt_OS_baselineSRB_nb0",
                "p1*(1-p2)" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nff_Ntl_OS_baselineSRB_nb0",
                "p2*(1-p1)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nff_Ntt_OS_baselineSRB_nb0",
                "(1-p1)*(1-p2)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            
            // N_f/p
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nfp_Nll_OS_baselineSRB_nb0",
                "2*f1*f2*p1*p2" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nfp_Nlt_OS_baselineSRB_nb0",
                "(f1*f2*p1*(1-p2) + p1*p2*f1*(1-f2))" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nfp_Ntl_OS_baselineSRB_nb0",
                "(p1*p2*f2*(1-f1) + f1*f2*p2*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB_nb0.push_back(new RunInfo(
                "Nfp_Ntt_OS_baselineSRB_nb0",
                "(f2*p1*(1-f1)*(1-p2) + f1*p2*(1-f2)*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB_nb0,
                eventSelectionStr_OS_baselineSRB_nb0,
                v_outputOption_reco
            ));
            
            
            ////////////////////////////////////////////////////////////
            //////////////////// OS_baselineSRB ////////////////////
            ////////////////////////////////////////////////////////////
            
            std::vector <RunInfo*> v_runInfo_OS_baselineSRB;
            
            std::map <std::string, bool> m_eventSelection_OS_baselineSRB;
            
            m_eventSelection_OS_baselineSRB["MET_E_reco >= 50"] = true;
            m_eventSelection_OS_baselineSRB["tauTau_jet_HT_reco >= 100"] = true;
            m_eventSelection_OS_baselineSRB["b_n_reco >= 1"] = true;
            
            std::string eventSelectionStr_OS_baselineSRB = "MET_E_reco >= 50 and tauTau_jet_HT_reco >= 100 and b_n_reco >= 1";
            
            // N_ff
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nff_Nll_OS_baselineSRB",
                "p1*p2" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nff_Nlt_OS_baselineSRB",
                "p1*(1-p2)" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nff_Ntl_OS_baselineSRB",
                "p2*(1-p1)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nff_Ntt_OS_baselineSRB",
                "(1-p1)*(1-p2)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            
            // N_f/p
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nfp_Nll_OS_baselineSRB",
                "2*f1*f2*p1*p2" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nfp_Nlt_OS_baselineSRB",
                "(f1*f2*p1*(1-p2) + p1*p2*f1*(1-f2))" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nfp_Ntl_OS_baselineSRB",
                "(p1*p2*f2*(1-f1) + f1*f2*p2*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineSRB.push_back(new RunInfo(
                "Nfp_Ntt_OS_baselineSRB",
                "(f2*p1*(1-f1)*(1-p2) + f1*p2*(1-f2)*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineSRB,
                eventSelectionStr_OS_baselineSRB,
                v_outputOption_reco
            ));
            
            
            ////////////////////////////////////////////////////////////
            //////////////////// OS_baselineDYCR ////////////////////
            ////////////////////////////////////////////////////////////
            
            std::vector <RunInfo*> v_runInfo_OS_baselineDYCR;
            
            std::map <std::string, bool> m_eventSelection_OS_baselineDYCR;
            
            m_eventSelection_OS_baselineDYCR["MET_E_reco >= 30"] = true;
            m_eventSelection_OS_baselineDYCR["tauTau_jet_HT_reco >= 100"] = true;
            m_eventSelection_OS_baselineDYCR["b_n_reco == 0"] = true;
            
            std::string eventSelectionStr_OS_baselineDYCR = "MET_E_reco >= 30 and tauTau_jet_HT_reco >= 100 and b_n_reco = 0 and tauTau_m_reco < 100";
            
            // N_ff
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nff_Nll_OS_baselineDYCR",
                "p1*p2" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nff_Nlt_OS_baselineDYCR",
                "p1*(1-p2)" + expression_common_Nff,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nff_Ntl_OS_baselineDYCR",
                "p2*(1-p1)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nff_Ntt_OS_baselineDYCR",
                "(1-p1)*(1-p2)" + expression_common_Nff,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            
            // N_f/p
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nfp_Nll_OS_baselineDYCR",
                "2*f1*f2*p1*p2" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nfp_Nlt_OS_baselineDYCR",
                "(f1*f2*p1*(1-p2) + p1*p2*f1*(1-f2))" + expression_common_Nfp,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nfp_Ntl_OS_baselineDYCR",
                "(p1*p2*f2*(1-f1) + f1*f2*p2*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_looseIsolation_dR03, v_tau_tightIsolation_dR03,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            v_runInfo_OS_baselineDYCR.push_back(new RunInfo(
                "Nfp_Ntt_OS_baselineDYCR",
                "(f2*p1*(1-f1)*(1-p2) + f1*p2*(1-f2)*(1-p1))" + expression_common_Nfp,
                v_tau_tightIsolation_dR03, 0,
                v_tau_tightIsolation_dR03, 0,
                //m_eventSelection_OS_baselineDYCR,
                eventSelectionStr_OS_baselineDYCR,
                v_outputOption_reco
            ));
            
            
            // Output root file
            TFile *output_analyzed;
            output_analyzed = TFile::Open(outFile, "RECREATE");
            
            
            
            for(int iRun = 0; iRun < v_runInfo_SS_baselineSRB_nbAny.size(); iRun++)
            {
                for(int iSRB = 0; iSRB < 18; iSRB++)
                {
                    char tempStr[Common::str_len];
                    sprintf(tempStr, "SRB%d", iSRB+1);
                    
                    v_runInfo_SS_baselineSRB_nbAny.at(iRun)->output_reco->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                    
                    v_runInfo_OS_baselineSRB_nb0.at(iRun)->output_reco->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                    
                    v_runInfo_OS_baselineSRB.at(iRun)->output_reco->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                    
                    v_runInfo_OS_baselineDYCR.at(iRun)->output_reco->addCutFlow(6, "SRB"+std::to_string(iSRB+1));
                }
                
                for(int iDYCR = 0; iDYCR < 18; iDYCR++)
                {
                    char tempStr[Common::str_len];
                    sprintf(tempStr, "DYCR%d", iDYCR+1);
                    
                    v_runInfo_SS_baselineSRB_nbAny.at(iRun)->output_reco->addCutFlow(6, "DYCR"+std::to_string(iDYCR+1));
                    
                    v_runInfo_OS_baselineSRB_nb0.at(iRun)->output_reco->addCutFlow(6, "DYCR"+std::to_string(iDYCR+1));
                    
                    v_runInfo_OS_baselineSRB.at(iRun)->output_reco->addCutFlow(6, "DYCR"+std::to_string(iDYCR+1));
                    
                    v_runInfo_OS_baselineDYCR.at(iRun)->output_reco->addCutFlow(6, "DYCR"+std::to_string(iDYCR+1));
                }
                
                
                //
                FakeEstimation_tauTau::analyze_reco(
                    input_data,
                    v_runInfo_SS_baselineSRB_nbAny.at(iRun)->output_reco,
                    "SS",
                    v_runInfo_SS_baselineSRB_nbAny.at(iRun)->v_tau1_isolation, v_runInfo_SS_baselineSRB_nbAny.at(iRun)->v_tau1_antiIsolation,
                    v_runInfo_SS_baselineSRB_nbAny.at(iRun)->v_tau2_isolation, v_runInfo_SS_baselineSRB_nbAny.at(iRun)->v_tau2_antiIsolation,
                    v_runInfo_SS_baselineSRB_nbAny.at(iRun)->expression,
                    isMC,
                    era,
                    //v_runInfo_SS_baselineSRB_nbAny.at(iRun)->m_eventSelection,
                    v_runInfo_SS_baselineSRB_nbAny.at(iRun)->eventSelectionStr,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    tauPandFobject,
                    v_eventWeight_nJetBin,
                    syst_name,
                    syst_type
                );
                
                printf("\n");
                
                
                //
                FakeEstimation_tauTau::analyze_reco(
                    input_data,
                    v_runInfo_OS_baselineSRB_nb0.at(iRun)->output_reco,
                    "OS",
                    v_runInfo_OS_baselineSRB_nb0.at(iRun)->v_tau1_isolation, v_runInfo_OS_baselineSRB_nb0.at(iRun)->v_tau1_antiIsolation,
                    v_runInfo_OS_baselineSRB_nb0.at(iRun)->v_tau2_isolation, v_runInfo_OS_baselineSRB_nb0.at(iRun)->v_tau2_antiIsolation,
                    v_runInfo_OS_baselineSRB_nb0.at(iRun)->expression,
                    isMC,
                    era,
                    //v_runInfo_OS_baselineSRB_nb0.at(iRun)->m_eventSelection,
                    v_runInfo_OS_baselineSRB_nb0.at(iRun)->eventSelectionStr,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    tauPandFobject,
                    v_eventWeight_nJetBin,
                    syst_name,
                    syst_type
                );
                
                printf("\n");
                
                
                //
                FakeEstimation_tauTau::analyze_reco(
                    input_data,
                    v_runInfo_OS_baselineSRB.at(iRun)->output_reco,
                    "OS",
                    v_runInfo_OS_baselineSRB.at(iRun)->v_tau1_isolation, v_runInfo_OS_baselineSRB.at(iRun)->v_tau1_antiIsolation,
                    v_runInfo_OS_baselineSRB.at(iRun)->v_tau2_isolation, v_runInfo_OS_baselineSRB.at(iRun)->v_tau2_antiIsolation,
                    v_runInfo_OS_baselineSRB.at(iRun)->expression,
                    isMC,
                    era,
                    //v_runInfo_OS_baselineSRB.at(iRun)->m_eventSelection,
                    v_runInfo_OS_baselineSRB.at(iRun)->eventSelectionStr,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    tauPandFobject,
                    v_eventWeight_nJetBin,
                    syst_name,
                    syst_type
                );
                
                printf("\n");
                
                
                //
                FakeEstimation_tauTau::analyze_reco(
                    input_data,
                    v_runInfo_OS_baselineDYCR.at(iRun)->output_reco,
                    "OS",
                    v_runInfo_OS_baselineDYCR.at(iRun)->v_tau1_isolation, v_runInfo_OS_baselineDYCR.at(iRun)->v_tau1_antiIsolation,
                    v_runInfo_OS_baselineDYCR.at(iRun)->v_tau2_isolation, v_runInfo_OS_baselineDYCR.at(iRun)->v_tau2_antiIsolation,
                    v_runInfo_OS_baselineDYCR.at(iRun)->expression,
                    isMC,
                    era,
                    //v_runInfo_OS_baselineDYCR.at(iRun)->m_eventSelection,
                    v_runInfo_OS_baselineDYCR.at(iRun)->eventSelectionStr,
                    &bTagCalib,
                    fileName_bTaggingEfficiency,
                    tauEffSFobject,
                    tauPandFobject,
                    v_eventWeight_nJetBin,
                    syst_name,
                    syst_type
                );
                
                printf("\n");
            }
            
            printf("\n\n");
            
            
            
            for(int iRun = 0; iRun < v_runInfo_SS_baselineSRB_nbAny.size(); iRun++)
            {
                // Write output
                std::string dirName;
                
                dirName = v_runInfo_SS_baselineSRB_nbAny.at(iRun)->term;
                output_analyzed->mkdir(dirName.c_str());
                output_analyzed->cd(dirName.c_str());
                v_runInfo_SS_baselineSRB_nbAny.at(iRun)->output_reco->writeData();
                
                
                dirName = v_runInfo_OS_baselineSRB_nb0.at(iRun)->term;
                output_analyzed->mkdir(dirName.c_str());
                output_analyzed->cd(dirName.c_str());
                v_runInfo_OS_baselineSRB_nb0.at(iRun)->output_reco->writeData();
                
                
                dirName = v_runInfo_OS_baselineSRB.at(iRun)->term;
                output_analyzed->mkdir(dirName.c_str());
                output_analyzed->cd(dirName.c_str());
                v_runInfo_OS_baselineSRB.at(iRun)->output_reco->writeData();
                
                
                dirName = v_runInfo_OS_baselineDYCR.at(iRun)->term;
                output_analyzed->mkdir(dirName.c_str());
                output_analyzed->cd(dirName.c_str());
                v_runInfo_OS_baselineDYCR.at(iRun)->output_reco->writeData();
                
                
                // Release memory
                v_runInfo_SS_baselineSRB_nbAny.at(iRun)->output_reco->freeMemory();
                v_runInfo_SS_baselineSRB_nbAny.at(iRun)->freeMemory();
                delete v_runInfo_SS_baselineSRB_nbAny.at(iRun);
                
                
                v_runInfo_OS_baselineSRB_nb0.at(iRun)->output_reco->freeMemory();
                v_runInfo_OS_baselineSRB_nb0.at(iRun)->freeMemory();
                delete v_runInfo_OS_baselineSRB_nb0.at(iRun);
                
                
                v_runInfo_OS_baselineSRB.at(iRun)->output_reco->freeMemory();
                v_runInfo_OS_baselineSRB.at(iRun)->freeMemory();
                delete v_runInfo_OS_baselineSRB.at(iRun);
                
                
                v_runInfo_OS_baselineDYCR.at(iRun)->output_reco->freeMemory();
                v_runInfo_OS_baselineDYCR.at(iRun)->freeMemory();
                delete v_runInfo_OS_baselineDYCR.at(iRun);
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
        
        delete tauEffSFobject;
        delete tauPandFobject;
    }

}

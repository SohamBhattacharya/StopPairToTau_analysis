import numpy
import os


condorConfig = "condor_config.sub"
condorScript = "condor_script.sh"

condorConfig_name = condorConfig[0: condorConfig.rfind(".")]
condorConfig_ext = condorConfig[condorConfig.rfind("."):]

condorScript_name = condorScript[0: condorScript.rfind(".")]
condorScript_ext = condorScript[condorScript.rfind("."):]


# Files to process per job
nUnitPerJob = 5

# Set to -1 for all files
nInputFileMax = -1


dictionary = {}


d_systType = {
    "up": ["Common::SYST_UP", "systUp"],
    "down": ["Common::SYST_DOWN", "systDown"],
    "singleSided": ["Common::SYST_ONESIDED", ""],
}

d_systName_elMu_analysis = {
    "nominal": "",
}

d_systName_muMu_analysis = {
    "nominal": "",
}

d_systName_bTaggingEfficiency = {
    "nominal": "",
}

d_systName_tauIdIsoEfficiency = {
    "nominal": "",
}

d_systName_pileUp = {
    "nominal": "",
}


l_scaleVarIndex = [
    0, 1, 2, 3, 4, 6, 8
]

d_systName_tauTau_analysis = {
    "nominal": "",
    "tauES": "tauES",
    "pileupReweight": "pileupReweight",
    "topPtReweight": "topPtReweight",
    "ZpTreweight": "ZpTreweight",
    "tauIDisoSF": "tauIDisoSF",
    #"triggerSF": "triggerSF",
    "tauFastFullSimSF": "tauFastFullSimSF",
    "bTaggingSF": "bTaggingSF",
    "JEC": "JEC",
    "JER": "JER",
    "unclusteredEnergy": "unclusteredEnergy",
    "withGenMET": "withGenMET",
}

d_systName_tauTau_analysis_data = {
    "nominal": "",
}

d_systName_muTau_analysis = {
    "nominal": "",
}

d_systName_muTau_analysis_data = {
    "nominal": "",
}

d_systName_tauTau_fakeRate = {
    "nominal": "",
}

d_systName_tauTau_fakeEstimation = {
    "nominal": "",
    "tauFakeRateRegion": "tauFakeRateRegion",
    "tauFakeRateJetPartonFlav": "tauFakeRateJetPartonFlav",
}

d_systName_genParamInfo = {
    "nominal": "",
}

d_systName_ISRinfo = {
    "nominal": "",
}


############################## Data ##############################

dictionary["tauTau_data"] = {
    "l_process": {
        "2016": [
            #"Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD",
            #"Tau_Run2016C-18Apr2017-v1_MINIAOD",
            #"Tau_Run2016D-18Apr2017-v1_MINIAOD",
            #"Tau_Run2016E-18Apr2017-v1_MINIAOD",
            #"Tau_Run2016F-18Apr2017-v1_MINIAOD",
            #"Tau_Run2016G-18Apr2017-v1_MINIAOD",
            #"Tau_Run2016H-18Apr2017-v1_MINIAOD",
            
            #"Tau_Run2016B-07Aug17_ver2-v1_MINIAOD",
            #"Tau_Run2016C-07Aug17-v1_MINIAOD",
            #"Tau_Run2016D-07Aug17-v1_MINIAOD",
            #"Tau_Run2016E-07Aug17-v1_MINIAOD",
            #"Tau_Run2016F-07Aug17-v1_MINIAOD",
            #"Tau_Run2016G-07Aug17-v1_MINIAOD",
            #"Tau_Run2016H-07Aug17-v1_MINIAOD",
            
            "Tau_Run2016B-17Jul2018_ver2-v1_MINIAOD",
            "Tau_Run2016C-17Jul2018-v1_MINIAOD",
            "Tau_Run2016D-17Jul2018-v1_MINIAOD",
            "Tau_Run2016E-17Jul2018-v1_MINIAOD",
            "Tau_Run2016F-17Jul2018-v1_MINIAOD",
            "Tau_Run2016G-17Jul2018-v1_MINIAOD",
            "Tau_Run2016H-17Jul2018-v1_MINIAOD",
        ],
        
        "2017": [
            "Tau_Run2017B-31Mar2018-v1_MINIAOD",
            "Tau_Run2017C-31Mar2018-v1_MINIAOD",
            "Tau_Run2017D-31Mar2018-v1_MINIAOD",
            "Tau_Run2017E-31Mar2018-v1_MINIAOD",
            "Tau_Run2017F-31Mar2018-v1_MINIAOD",
        ]
    },
    
    "directory": "tauTau_data",
    
    "run": {
        "fakeRate": {
            "outDir": "tauTau_data/output_tauTau_fakeRate",
            "otherInfoDir": "tauTau_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "tauTau_data/tauTau_data_fakeRate.cc",
            "suffix": "_tauTau_fakeRate",
            #"suffix": "_tauTau_fakeRate_METleq20",
            "syst_names": d_systName_tauTau_fakeRate,
            "splitByFiles": True
        },
        
        "fakeEstimation": {
            "outDir": "tauTau_data/output_tauTau_fakeEstimation",
            "otherInfoDir": "tauTau_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "tauTau_data/tauTau_data_fakeEstimation.cc",
            "suffix": "_tauTau_fakeEstimation",
            #"suffix": "_tauTau_fakeEstimation_nJetGeq1",
            "syst_names": d_systName_tauTau_fakeEstimation,
            "splitByFiles": True
        },
        
        "tauTau_analysis": {
            "outDir": "tauTau_data/output_analyzed",
            "otherInfoDir": "tauTau_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "tauTau_data/tauTau_data_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis_data,
            "splitByFiles": True
        },
        
        "pileUp": {
            "outDir": "tauTau_data/output_pileUp",
            "otherInfoDir": "tauTau_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "tauTau_data/tauTau_data_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["elMu_data"] = {
    "l_process": {
        "2016": [
            #"MuonEG_Run2016B-18Apr2017_ver2-v1_MINIAOD",
            #"MuonEG_Run2016C-18Apr2017-v1_MINIAOD",
            #"MuonEG_Run2016D-18Apr2017-v1_MINIAOD",
            #"MuonEG_Run2016E-18Apr2017-v1_MINIAOD",
            #"MuonEG_Run2016F-18Apr2017-v1_MINIAOD",
            #"MuonEG_Run2016G-18Apr2017-v1_MINIAOD",
            #"MuonEG_Run2016H-18Apr2017-v1_MINIAOD",
            
            "MuonEG_Run2016B-07Aug17_ver2-v1_MINIAOD",
            "MuonEG_Run2016C-07Aug17-v1_MINIAOD",
            "MuonEG_Run2016D-07Aug17-v1_MINIAOD",
            "MuonEG_Run2016E-07Aug17-v1_MINIAOD",
            "MuonEG_Run2016F-07Aug17-v1_MINIAOD",
            "MuonEG_Run2016G-07Aug17-v1_MINIAOD",
            "MuonEG_Run2016H-07Aug17-v1_MINIAOD",
        ],
        
        "2017": [
            "MuonEG_Run2017B-31Mar2018-v1_MINIAOD",
            "MuonEG_Run2017C-31Mar2018-v1_MINIAOD",
            "MuonEG_Run2017D-31Mar2018-v1_MINIAOD",
            "MuonEG_Run2017E-31Mar2018-v1_MINIAOD",
            "MuonEG_Run2017F-31Mar2018-v1_MINIAOD",
        ]
    },
    
    "directory": "elMu_data",
    
    "run": {
        "elMu_analysis": {
            "outDir": "elMu_data/output_analyzed",
            "otherInfoDir": "elMu_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "elMu_data/elMu_data_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
    }
}


dictionary["muMu_data"] = {
    "l_process": {
        "2016": [
            #"SingleMuon_Run2016B-18Apr2017_ver2-v1_MINIAOD",
            #"SingleMuon_Run2016C-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016D-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016E-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016F-18Apr2017-v2_MINIAOD",
            #"SingleMuon_Run2016G-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016H-18Apr2017-v1_MINIAOD",
            
            "SingleMuon_Run2016B-07Aug17_ver2-v1_MINIAOD",
            "SingleMuon_Run2016C-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016D-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016E-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016F-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016G-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016H-07Aug17-v1_MINIAOD",
        ],
        
        "2017": [
            "SingleMuon_Run2017B-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017C-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017D-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017E-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017F-31Mar2018-v1_MINIAOD",
        ]
    },
    
    "directory": "muMu_data",
    
    "run": {
        "muMu_analysis": {
            "outDir": "muMu_data/output_analyzed",
            "otherInfoDir": "muMu_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "muMu_data/muMu_data_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
    }
}


dictionary["muTau_data"] = {
    "l_process": {
        "2016": [
            #"SingleMuon_Run2016B-18Apr2017_ver2-v1_MINIAOD",
            #"SingleMuon_Run2016C-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016D-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016E-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016F-18Apr2017-v2_MINIAOD",
            #"SingleMuon_Run2016G-18Apr2017-v1_MINIAOD",
            #"SingleMuon_Run2016H-18Apr2017-v1_MINIAOD",
            
            "SingleMuon_Run2016B-07Aug17_ver2-v1_MINIAOD",
            "SingleMuon_Run2016C-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016D-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016E-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016F-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016G-07Aug17-v1_MINIAOD",
            "SingleMuon_Run2016H-07Aug17-v1_MINIAOD",
        ],
        
        "2017": [
            "SingleMuon_Run2017B-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017C-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017D-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017E-31Mar2018-v1_MINIAOD",
            "SingleMuon_Run2017F-31Mar2018-v1_MINIAOD",
        ]
    },
    
    "directory": "muTau_data",
    
    "run": {
        "muTau_analysis": {
            "outDir": "muTau_data/output_analyzed",
            "otherInfoDir": "muTau_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "muTau_data/muTau_data_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis_data,
            "splitByFiles": True
        },
    }
}


############################## stop-pair ##############################

dictionary["stopPair_mc"] = {
    "l_process": {
        "2016": [
            #"SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            #"SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            #"SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            
            "SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
        ],
        
        "2017": [
            "SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
            "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
            "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
        ]
    },
    
    "directory": "stopPair_mc",
    
    "run": {
        "tauTau_analysis": {
            "outDir": "stopPair_mc/output_analyzed",
            "otherInfoDir": "stopPair_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "stopPair_mc/stopPair_tauTau_mc_analysis.cc",
            "massPointFile": "stopPair_mc/output_genParam/%s/XSweightInfo.txt",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByMass": False,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "stopPair_mc/output_analyzed",
            "otherInfoDir": "stopPair_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "stopPair_mc/stopPair_elMu_mc_analysis.cc",
            "massPointFile": "stopPair_mc/output_genParam/%s/XSweightInfo.txt",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "runScaleVariation": True,
            "splitByMass": False,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "stopPair_mc/output_bTaggingEfficiency",
            "otherInfoDir": "stopPair_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "stopPair_mc/stopPair_mc_bTaggingEfficiency.cc",
            "massPointFile": "stopPair_mc/output_genParam/%s/XSweightInfo.txt",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByMass": False,
            "splitByFiles": False,
        },
        
        "pileUp": {
            "outDir": "stopPair_mc/output_pileUp",
            "otherInfoDir": "stopPair_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "stopPair_mc/stopPair_mc_pileUp.cc",
            "massPointFile": "stopPair_mc/output_genParam/%s/XSweightInfo.txt",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByMass": False,
            "splitByFiles": True,
        },
        
        "genParamInfo": {
            "outDir": "stopPair_mc/output_genParam",
            "otherInfoDir": "stopPair_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "stopPair_mc/stopPair_mc_genParamInfo.cc",
            "suffix": "",
            "syst_names": d_systName_genParamInfo,
            "splitByMass": False,
            "splitByFiles": False,
        },
        
        "ISRinfo": {
            "outDir": "stopPair_mc/output_ISRinfo",
            "otherInfoDir": "stopPair_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "stopPair_mc/stopPair_mc_ISRinfo.cc",
            "suffix": "",
            "syst_names": d_systName_genParamInfo,
            "splitByMass": False,
            "splitByFiles": False,
        },
    }
}


############################## MC ##############################

dictionary["DYJets_mc"] = {
    "l_process": {
        "2016": [
            "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
        ],
        
        "2017": [
            "DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
        ]
    },
    
    "directory": "DYJetsToLL_mc",
    
    "run": {
        "fakeRate": {
            "outDir": "DYJetsToLL_mc/output_tauTau_fakeRate",
            "otherInfoDir": "tauTau_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_tauTau_mc_fakeRate",
            "suffix": "_tauTau_fakeRate",
            "syst_names": d_systName_tauTau_fakeRate,
            "splitByFiles": True
        },
        
        "tauIdIsoEfficiency": {
            "outDir": "DYJetsToLL_mc/output_tauIdIsoEfficiency",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_tauIdIsoEfficiency.cc",
            "suffix": "_tauIdIsoEfficiency",
            "syst_names": d_systName_tauIdIsoEfficiency,
            "splitByFiles": True
        },
        
        "tauTemplateMethod": {
            "outDir": "DYJetsToLL_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauTau_analysis": {
            "outDir": "DYJetsToLL_mc/output_analyzed",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "DYJetsToLL_mc/output_analyzed",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "DYJetsToLL_mc/output_analyzed",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "DYJetsToLL_mc/output_analyzed",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "DYJetsToLL_mc/output_bTaggingEfficiency",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "DYJetsToLL_mc/output_pileUp",
            "otherInfoDir": "DYJetsToLL_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "DYJetsToLL_mc/DYJetsToLL_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["WJets_mc"] = {
    "l_process": {
        "2016": [
            "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
            "W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
        ],
        
        "2017": [
            "WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            "W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
        ]
    },
    
    "directory": "WJetsToLNu_mc",
    
    "run": {
        "tauTemplateMethod": {
            "outDir": "WJetsToLNu_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "WJetsToLNu_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WJetsToLNu_mc/WJetsToLNu_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauTau_analysis": {
            "outDir": "WJetsToLNu_mc/output_analyzed",
            "otherInfoDir": "WJetsToLNu_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WJetsToLNu_mc/WJetsToLNu_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "WJetsToLNu_mc/output_analyzed",
            "otherInfoDir": "WJetsToLNu_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WJetsToLNu_mc/WJetsToLNu_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "WJetsToLNu_mc/output_analyzed",
            "otherInfoDir": "WJetsToLNu_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WJetsToLNu_mc/WJetsToLNu_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "WJetsToLNu_mc/output_analyzed",
            "otherInfoDir": "WJetsToLNu_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WJetsToLNu_mc/WJetsToLNu_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "WJetsToLNu_mc/output_bTaggingEfficiency",
            "otherInfoDir": "WJetsToLNu_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "WJetsToLNu_mc/WJetsToLNu_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "WJetsToLNu_mc/output_pileUp",
            "otherInfoDir": "WJetsToLNu_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "WJetsToLNu_mc/WJetsToLNu_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["VH_mc"] = {
    "l_process": {
        "2016": [
            "ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
            "WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
        ],
        
        "2017": [
            "ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Fall17",
            "WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17",
            "WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17",
        ]
    },
    
    "directory": "VH_mc",
    
    "run": {
        "tauTemplateMethod": {
            "outDir": "VH_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "VH_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VH_mc/VH_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauTau_analysis": {
            "outDir": "VH_mc/output_analyzed",
            "otherInfoDir": "VH_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VH_mc/VH_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "VH_mc/output_analyzed",
            "otherInfoDir": "VH_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VH_mc/VH_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "VH_mc/output_analyzed",
            "otherInfoDir": "VH_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VH_mc/VH_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "VH_mc/output_analyzed",
            "otherInfoDir": "VH_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VH_mc/VH_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "VH_mc/output_bTaggingEfficiency",
            "otherInfoDir": "VH_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "VH_mc/VH_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "VH_mc/output_pileUp",
            "otherInfoDir": "VH_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "VH_mc/VH_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["VV_mc"] = {
    "l_process": {
        "2016": [
            "VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
            "WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
            "ZZTo4L_13TeV-amcatnloFXFX-pythia8_Summer16",
            "ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
            "WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_Summer16",
            "WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
            "WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
            "WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
        ],
        
        "2017": [
            "VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
            "WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
            "WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
            "WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_Fall17",
            "WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
            "ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
            "ZZTo4L_13TeV_powheg_pythia8_Fall17",
        ]
    },
    
    "directory": "VV_mc",
    
    "run": {
        "tauTemplateMethod": {
            "outDir": "VV_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "VV_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VV_mc/VV_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauTau_analysis": {
            "outDir": "VV_mc/output_analyzed",
            "otherInfoDir": "VV_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VV_mc/VV_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "VV_mc/output_analyzed",
            "otherInfoDir": "VV_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VV_mc/VV_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "VV_mc/output_analyzed",
            "otherInfoDir": "VV_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VV_mc/VV_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "VV_mc/output_analyzed",
            "otherInfoDir": "VV_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "VV_mc/VV_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "VV_mc/output_bTaggingEfficiency",
            "otherInfoDir": "VV_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "VV_mc/VV_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "VV_mc/output_pileUp",
            "otherInfoDir": "VV_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "VV_mc/VV_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["WG_mc"] = {
    "l_process": {
        "2016": [
            "WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Summer16",
            "WGstarToLNuMuMu_012Jets_13TeV-madgraph_Summer16",
            "WGstarToLNuEE_012Jets_13TeV-madgraph_Summer16",
        ],
        
        "2017": [
            "WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
        ],
    },
    
    "directory": "WG_mc",
    
    "run": {
        "tauTemplateMethod": {
            "outDir": "WG_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "WG_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WG_mc/WG_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauTau_analysis": {
            "outDir": "WG_mc/output_analyzed",
            "otherInfoDir": "WG_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WG_mc/WG_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "WG_mc/output_analyzed",
            "otherInfoDir": "WG_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WG_mc/WG_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "WG_mc/output_analyzed",
            "otherInfoDir": "WG_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WG_mc/WG_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "WG_mc/output_analyzed",
            "otherInfoDir": "WG_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "WG_mc/WG_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "WG_mc/output_bTaggingEfficiency",
            "otherInfoDir": "WG_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "WG_mc/WG_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "WG_mc/output_pileUp",
            "otherInfoDir": "WG_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "WG_mc/WG_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["ttbar_mc"] = {
    "l_process": {
        "2016": [
            "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16",
            
            "TTJets_13TeV-madgraphMLM_FastSim_Summer16",
            "TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
        ],
        
        "2017": [
            "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17",
            "TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17",
            "TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_Fall17",
            
            #"TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
            #"TTJets_DiLept_TuneCP2_13TeV-madgraphMLM-pythia8_FastSim_Fall17",
        ],
    },
    
    "directory": "ttbar_mc",
    
    "run": {
        "fakeRate": {
            "outDir": "ttbar_mc/output_tauTau_fakeRate",
            "otherInfoDir": "tauTau_data",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "ttbar_mc/ttbar_tauTau_mc_fakeRate",
            "suffix": "_tauTau_fakeRate",
            "syst_names": d_systName_tauTau_fakeRate,
            "splitByFiles": True
        },
        
        "tauTemplateMethod": {
            "outDir": "ttbar_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "ttbar_mc/ttbar_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauIdIsoEfficiency": {
            "outDir": "ttbar_mc/output_tauIdIsoEfficiency",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "ttbar_mc/ttbar_tauIdIsoEfficiency.cc",
            "suffix": "_tauIdIsoEfficiency",
            "syst_names": d_systName_tauIdIsoEfficiency,
            "splitByFiles": True
        },
        
        "tauTau_analysis": {
            "outDir": "ttbar_mc/output_analyzed",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "ttbar_mc/ttbar_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "ttbar_mc/output_analyzed",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "ttbar_mc/ttbar_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "ttbar_mc/output_analyzed",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "ttbar_mc/ttbar_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "ttbar_mc/output_analyzed",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "ttbar_mc/ttbar_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "ttbar_mc/output_bTaggingEfficiency",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "ttbar_mc/ttbar_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "ttbar_mc/output_pileUp",
            "otherInfoDir": "ttbar_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "ttbar_mc/ttbar_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["singleTop_mc"] = {
    "l_process": {
        "2016": [
            "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16",
            "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16",
            "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16",
            "ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16",
        ],
        
        "2017": [
            "ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17",
            "ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17",
            "ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17",
            "ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17",
        ]
    },
    
    "directory": "singleTop_mc",
    
    "run": {
        "tauTemplateMethod": {
            "outDir": "singleTop_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "singleTop_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "singleTop_mc/singleTop_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauTau_analysis": {
            "outDir": "singleTop_mc/output_analyzed",
            "otherInfoDir": "singleTop_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "singleTop_mc/singleTop_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "singleTop_mc/output_analyzed",
            "otherInfoDir": "singleTop_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "singleTop_mc/singleTop_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "singleTop_mc/output_analyzed",
            "otherInfoDir": "singleTop_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "singleTop_mc/singleTop_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "singleTop_mc/output_analyzed",
            "otherInfoDir": "singleTop_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "singleTop_mc/singleTop_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "singleTop_mc/output_bTaggingEfficiency",
            "otherInfoDir": "singleTop_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "singleTop_mc/singleTop_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "singleTop_mc/output_pileUp",
            "otherInfoDir": "singleTop_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "singleTop_mc/singleTop_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}


dictionary["TTX_mc"] = {
    "l_process": {
        "2016": [
            "TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16",
            "TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16",
            "TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16",
            "TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16",
        ],
        
        "2017": [
            "TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8_Fall17",
            "TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_Fall17",
            "TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17",
            "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17",
        ]
    },
    
    "directory": "TTX_mc",
    
    "run": {
        "tauTemplateMethod": {
            "outDir": "TTX_mc/output_tauTemplateMethodEstimation",
            "otherInfoDir": "TTX_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "TTX_mc/TTX_tauTau_mc_tauTemplateMethodEstimation.cc",
            "suffix": "_tauTau_tauTemplateMethodEstimation"
        },
        
        "tauTau_analysis": {
            "outDir": "TTX_mc/output_analyzed",
            "otherInfoDir": "TTX_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "TTX_mc/TTX_tauTau_mc_analysis.cc",
            "suffix": "_tauTau_analysis",
            "syst_names": d_systName_tauTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "muTau_analysis": {
            "outDir": "TTX_mc/output_analyzed",
            "otherInfoDir": "TTX_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "TTX_mc/TTX_muTau_mc_analysis.cc",
            "suffix": "_muTau_analysis",
            "syst_names": d_systName_muTau_analysis,
            "runScaleVariation": True,
            "splitByFiles": True
        },
        
        "elMu_analysis": {
            "outDir": "TTX_mc/output_analyzed",
            "otherInfoDir": "TTX_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "TTX_mc/TTX_elMu_mc_analysis.cc",
            "suffix": "_elMu_analysis",
            "syst_names": d_systName_elMu_analysis,
            "splitByFiles": True
        },
        
        "muMu_analysis": {
            "outDir": "TTX_mc/output_analyzed",
            "otherInfoDir": "TTX_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "codeFile": "TTX_mc/TTX_muMu_mc_analysis.cc",
            "suffix": "_muMu_analysis",
            "syst_names": d_systName_muMu_analysis,
            "splitByFiles": True
        },
        
        "bTaggingEfficiency": {
            "outDir": "TTX_mc/output_bTaggingEfficiency",
            "otherInfoDir": "TTX_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_bTaggingEfficiency",
            "codeFile": "TTX_mc/TTX_mc_bTaggingEfficiency.cc",
            "suffix": "_bTaggingEfficiency",
            "syst_names": d_systName_bTaggingEfficiency,
            "splitByFiles": False
        },
        
        "pileUp": {
            "outDir": "TTX_mc/output_pileUp",
            "otherInfoDir": "TTX_mc",
            "inputFileList_template": "sourceFiles/%s/%s_custom.txt",
            "suffix": "_pileUp",
            "codeFile": "TTX_mc/TTX_mc_pileUp.cc",
            "suffix": "_pileUp",
            "syst_names": d_systName_pileUp,
            "splitByFiles": True
        },
    }
}



if (__name__ == "__main__") :
    
    ########## Choose process ##########
    print "Choose process:"
    
    for key in dictionary :
        
        print "\t", key
    
    processOptionList = str(raw_input("Choice: ")).strip()
    processOptionList = processOptionList.split()
    
    # Check input
    for processOption in processOptionList :
        
        if (processOption not in dictionary) :
            
            print("Enter a valid option.")
            exit(1)
    
    print processOptionList
    print ""
    
    
    ########### Choose what to run ##########
    print "Choose run option:"
    
    for key in dictionary[processOptionList[0]]["run"] :
        
        print "\t", key
    
    runOption = str(raw_input("Choice: ")).strip()
    
    # Check input
    if (runOption not in dictionary[processOptionList[0]]["run"]) :
        
        print("Enter a valid option.")
        exit(1)
    
    print ""
    
    
    ########## Choose mass points for stop-pair ##########
    if (len(processOptionList) == 1 and processOptionList[0] == "stopPair_mc" and dictionary["stopPair_mc"]["run"][runOption]["splitByMass"]) :
        
        print "Choose stop-pair mass points:"
        print "Format:"
        print "\t stop1_m neutralino1_m, stop1_m neutralino1_m, ..."
        print "\t OR enter 0 for all mass points"
        stopPair_massPointOptionList = str(raw_input("Choice: ")).strip()
        
        if (stopPair_massPointOptionList != "0" and len(stopPair_massPointOptionList)) :
            
            # Remove trailing comma
            stopPair_massPointOptionList = stopPair_massPointOptionList[0: -1] if (stopPair_massPointOptionList[-1] == ",") else stopPair_massPointOptionList
            stopPair_massPointOptionList = stopPair_massPointOptionList.split(",")
            stopPair_massPointOptionList = [ele.split() for ele in stopPair_massPointOptionList]
            stopPair_massPointOptionList = [[int(ele[0]), int(ele[1])] for ele in stopPair_massPointOptionList]
            
            # Check input (dimension)
            if (len(numpy.array(stopPair_massPointOptionList).shape) != 2) :
                
                print "Enter mass points in the correct format."
                exit(1)
        
        else :
            
            stopPair_massPointOptionList = []
        
        print stopPair_massPointOptionList
        print ""
    
    
    ########### Choose systematics ##########
    print "Choose systematics:"
    
    for key in dictionary[processOption]["run"][runOption]["syst_names"] :
        
        print "\t", key
    
    systNameList = str(raw_input("Choice: ")).strip()
    systNameList = systNameList.split()
    
    # Check input
    for systName in systNameList :
        
        if (systName not in dictionary[processOption]["run"][runOption]["syst_names"]) :
            
            print("Enter a valid option.")
            exit(1)
    
    print systNameList
    print ""
    
    
    ########## Choose systematic type ##########
    if (not (len(systNameList) == 1 and systNameList[0] == "nominal")) :
        
        print "Choose systematic type:"
        
        for key in d_systType :
            
            print "\t", key
        
        systType = str(raw_input("Choice: ")).strip()
        
        # Check input
        if (systType not in d_systType) :
            
            print("Enter a valid option.")
            exit(1)
        
        print ""
    
    
    ########## Choose scale variation ##########
    l_scaleVarOption = [0]
    
    if (len(systNameList) == 1 and systNameList[0] == "nominal" and \
        "runScaleVariation" in dictionary[processOption]["run"][runOption] and \
        dictionary[processOption]["run"][runOption]["runScaleVariation"]
        ) :
        
        print "Enter scale variation options (space separated): ", l_scaleVarIndex
        print "If no entries are given, all will be used."
        
        l_scaleVarOption = str(raw_input("Choice: ")).strip()
        l_scaleVarOption = l_scaleVarOption.split()
        
        if (len(l_scaleVarOption)) :
            
            l_scaleVarOption = [int(ele) for ele in l_scaleVarOption]
        
        else :
            
            l_scaleVarOption = l_scaleVarIndex
        
        if (not all([ele in l_scaleVarIndex for ele in l_scaleVarOption])) :
            
            print("Enter a valid option.")
            exit(1)
        
        print "You've chosen:", l_scaleVarOption
        print ""
    
    
    ########## Choose era ##########
    print "Choose era:"
    
    for key in dictionary[processOption]["l_process"] :
        
        print "\t", key
    
    era = str(raw_input("Choice: ")).strip()
    
    # Check input
    if (era not in dictionary[processOption]["l_process"]) :
        
        print("Enter a valid option.")
        exit(1)
    
    print ""
    
    
    ########## Units per job ##########
    if (dictionary[processOptionList[0]]["run"][runOption]["splitByFiles"]) :
        
        print "Enter # units to process per job (enter 0 to use default value [%d]):" %(nUnitPerJob)
        
        nUnitPerJob_choice = int(raw_input("Choice: ").strip())
        
        # Check input
        if (nUnitPerJob_choice > 0) :
            
            nUnitPerJob = nUnitPerJob_choice
        
        if (nUnitPerJob_choice < 0) :
            
            print "Value cannot be negative."
            exit(1)
        
        print ""
    
    nJob_total = 0
    nUnit_total = 0
    
    
    ########## Choose to add to suffix ##########
    print "Enter addition to existing suffix (maybe with leading underscore?)."
    
    suffixChoice = str(raw_input("Additional suffix: ")).strip()
    suffixChoice = suffixChoice.strip()
    
    print "You've entered: %s" %(suffixChoice)
    print ""
    
    
    for processOption in processOptionList :
        
        l_process = dictionary[processOption]["l_process"][era]
        
        for iEntry in range(0, len(l_process)) :
            
            for iSyst in range(0, len(systNameList)):
                
                l_scaleVarOption_mod = l_scaleVarOption
                
                #if (systNameList[iSyst] != "nominal") :
                #    
                #    l_scaleVarOption_mod = [0]
                
                for iScaleVar in range(0, len(l_scaleVarOption_mod)) :
                    
                    scalVarIndex = l_scaleVarOption_mod[iScaleVar]
                    
                    outDir = dictionary[processOption]["run"][runOption]["outDir"]
                    otherInfoDir = dictionary[processOption]["run"][runOption]["otherInfoDir"]
                    inputFileList_template = dictionary[processOption]["run"][runOption]["inputFileList_template"]
                    codeFile = dictionary[processOption]["run"][runOption]["codeFile"]
                    suffix = dictionary[processOption]["run"][runOption]["suffix"]
                    systName = dictionary[processOption]["run"][runOption]["syst_names"][systNameList[iSyst]]
                    
                    if (len(suffixChoice)) :
                        
                        suffix += suffixChoice
                    
                    processName = l_process[iEntry]
                    inputFileList = inputFileList_template %(l_process[iEntry], l_process[iEntry])
                    
                    outDir = "%s/%s%s" %(outDir, processName, suffix)
                    
                    # Systematics suffix
                    systStr = ""
                    
                    if(systNameList[iSyst] != "nominal") :
                        
                        systStr = "_%s%s%s" %(systName, "-"*(len(d_systType[systType][1]) > 0), d_systType[systType][1])
                    
                    
                    # Scale variation suffix
                    scaleVarStr = ""
                    
                    if(systNameList[iSyst] == "nominal" and scalVarIndex != 0) :
                        
                        scaleVarStr = "_scale%d" %(scalVarIndex)
                    
                    
                    condorDirectory = "condorJobs/condor_%s%s%s%s" %(processName, suffix, systStr, scaleVarStr)
                    
                    inputFiles = numpy.loadtxt(inputFileList, dtype = str)
                    nInputFile = inputFiles.shape[0]
                    
                    if (nInputFileMax > 0 and nInputFile > nInputFileMax) :
                        
                        inputFiles = inputFiles[0: nInputFileMax]
                        nInputFile = inputFiles.shape[0]
                    
                    if (not dictionary[processOption]["run"][runOption]["splitByFiles"]) :
                        
                        nUnitPerJob = nInputFile
                    
                    massPointList = []
                    
                    nJob = 0
                    nJobPerMass = 1
                    
                    if (processOption == "stopPair_mc" and dictionary[processOption]["run"][runOption]["splitByMass"]) :
                        
                        massPointFile = dictionary[processOption]["run"][runOption]["massPointFile"] %(l_process[iEntry])
                        massPointList = numpy.loadtxt(massPointFile, dtype = int, delimiter = ",")#[0: 2]
                        
                        nJob = massPointList.shape[0]
                        
                        if (dictionary[processOption]["run"][runOption]["splitByFiles"]) :
                            
                            nJobPerMass = int(numpy.ceil(float(nInputFile)/nUnitPerJob))
                    
                    else :
                        
                        nJob = int(numpy.ceil(float(nInputFile)/nUnitPerJob))
                    
                    nJob_total += nJob*nJobPerMass
                    nUnit_total += inputFiles.shape[0]
                    
                    print "****************************************************************************************************"
                    print "****************************************************************************************************"
                    print "Process:", processName
                    print "Input file:", inputFileList
                    print "Code file:", codeFile
                    print "Condor directory:", condorDirectory
                    print "# jobs:", nJob
                    print "# units:", inputFiles.shape[0]
                    print "# units per job:", nUnitPerJob
                    print "****************************************************************************************************"
                    print "****************************************************************************************************"
                    print ""
                    
                    
                    inputFileList = inputFileList[inputFileList.rfind("/")+1:]
                    inputFileList_name = inputFileList[0: inputFileList.rfind(".")]
                    inputFileList_ext = inputFileList[inputFileList.rfind("."):]
                    
                    codeFile_name = codeFile[0: codeFile.rfind(".")]
                    codeFile_ext = codeFile[codeFile.rfind("."):]
                    
                    codeFile_content = ""
                    
                    with open(codeFile, "r") as f :
                        
                        codeFile_content = f.read()
                    
                    
                    condorConfig_content = ""
                    
                    with open(condorConfig, "r") as f :
                        
                        condorConfig_content = f.read()
                    
                    
                    condorScript_content = ""
                    
                    with open(condorScript, "r") as f :
                        
                        condorScript_content = f.read()
                    
                    
                    command = "mkdir -p " + condorDirectory
                    print "Command:", command
                    os.system(command)
                    
                    print "\n"
                    
                    
                    for iJob in range(0, nJob) :
                        
                        stop1_m = 0
                        neutralino1_m = 0
                        
                        if (processOption == "stopPair_mc" and dictionary[processOption]["run"][runOption]["splitByMass"]) :
                            
                            stop1_m = int(massPointList[iJob][0])
                            neutralino1_m = int(massPointList[iJob][1])
                            
                            if (len (stopPair_massPointOptionList) and not([stop1_m, neutralino1_m] in stopPair_massPointOptionList)) :
                                
                                continue
                        
                        for iJobPerMass in range(0, nJobPerMass) :
                            
                            codeFile_content_mod = codeFile_content
                            condorConfig_content_mod = condorConfig_content
                            condorScript_content_mod = condorScript_content
                            
                            inputFiles_mod = []
                            
                            jobNumberStr = ""
                            
                            if (processOption == "stopPair_mc" and dictionary[processOption]["run"][runOption]["splitByMass"]) :
                                
                                inputFiles_mod = inputFiles[:]
                                jobNumberStr = "%d_%d" %(stop1_m, neutralino1_m)
                                
                                if (dictionary[processOption]["run"][runOption]["splitByFiles"]) :
                                    
                                    inputFiles_mod = inputFiles[:]
                                    jobNumberStr = "%d_%d_%d" %(stop1_m, neutralino1_m, int(iJobPerMass+1))
                                    
                                    if iJobPerMass < nJobPerMass-1 :
                                        
                                        inputFiles_mod = inputFiles[iJobPerMass*nUnitPerJob: (iJobPerMass+1)*nUnitPerJob]
                                        
                                    else :
                                        
                                        inputFiles_mod = inputFiles[iJobPerMass*nUnitPerJob:]
                            
                            else :
                                
                                jobNumberStr = str(int(iJob+1))
                                
                                if iJob < nJob-1 :
                                    
                                    inputFiles_mod = inputFiles[iJob*nUnitPerJob: (iJob+1)*nUnitPerJob]
                                    
                                else :
                                    
                                    inputFiles_mod = inputFiles[iJob*nUnitPerJob:]
                                
                            condorConfig_mod = condorConfig_name + "_" + jobNumberStr + condorConfig_ext
                            condorScript_mod = condorScript_name + "_" + jobNumberStr + condorScript_ext
                            
                            inputFileList_mod = inputFileList_name + "_" + jobNumberStr + inputFileList_ext
                            codeFile_name_mod = codeFile_name[codeFile_name.rfind("/")+1:] + "_" + jobNumberStr
                            
                            
                            # Condor config
                            condorConfig_content_mod = condorConfig_content_mod.replace("@exe@", condorDirectory + "/" + condorScript_mod)
                            condorConfig_content_mod = condorConfig_content_mod.replace("@log@", condorDirectory + "/" + codeFile_name_mod + ".log")
                            condorConfig_content_mod = condorConfig_content_mod.replace("@out@", condorDirectory + "/" + codeFile_name_mod + ".out")
                            condorConfig_content_mod = condorConfig_content_mod.replace("@err@", condorDirectory + "/" + codeFile_name_mod + ".err")
                            
                            print "Writing:", (condorDirectory + "/" + condorConfig_mod)
                            
                            with open(condorDirectory + "/" + condorConfig_mod, "w") as f :
                                
                                f.write(condorConfig_content_mod)
                            
                            
                            # Condor script
                            condorScript_content_mod = condorScript_content_mod.replace("@infile@", condorDirectory + "/" + codeFile_name_mod+codeFile_ext)
                            condorScript_content_mod = condorScript_content_mod.replace("@exe@", condorDirectory + "/" + codeFile_name_mod)
                            
                            print "Writing:", (condorDirectory + "/" + condorScript_mod)
                            
                            with open(condorDirectory + "/" + condorScript_mod, "w") as f :
                                
                                f.write(condorScript_content_mod)
                            
                            command = "chmod +x " + condorDirectory + "/" + condorScript_mod
                            print "Command:", command
                            os.system(command)
                            
                            
                            # Code file
                            codeFile_content_mod = codeFile_content_mod.replace("@process@", processName)
                            codeFile_content_mod = codeFile_content_mod.replace("@dir@", outDir)
                            codeFile_content_mod = codeFile_content_mod.replace("@otherInfoDir@", otherInfoDir)
                            codeFile_content_mod = codeFile_content_mod.replace("@sourceFileName@", condorDirectory + "/" + inputFileList_mod)
                            codeFile_content_mod = codeFile_content_mod.replace("@era@", era)
                            codeFile_content_mod = codeFile_content_mod.replace("@syst_name@", systName)
                            codeFile_content_mod = codeFile_content_mod.replace("@scaleVariationIndex@", str(scalVarIndex))
                            
                            if (processOption == "stopPair_mc" and dictionary[processOption]["run"][runOption]["splitByMass"]) :
                                
                                codeFile_content_mod = codeFile_content_mod.replace("@stop1_m@", str(stop1_m))
                                codeFile_content_mod = codeFile_content_mod.replace("@neutralino1_m@", str(neutralino1_m))
                            
                            if (systNameList[iSyst] != "nominal") :
                                
                                codeFile_content_mod = codeFile_content_mod.replace("Common::SYST_CENTRAL", d_systType[systType][0])
                            
                            print "Writing:", (condorDirectory + "/" + codeFile_name_mod + codeFile_ext)
                            
                            with open(condorDirectory + "/" + codeFile_name_mod + codeFile_ext, "w") as f :
                                
                                f.write(codeFile_content_mod)
                            
                            
                            # Input file list
                            print "Writing:", (condorDirectory + "/" + inputFileList_mod)
                            
                            with open(condorDirectory + "/" + inputFileList_mod, "w") as f :
                                
                                f.write("\n".join(inputFiles_mod) + "\n")
                            
                            
                            command = "condor_submit " + condorDirectory + "/" + condorConfig_mod
                            print "Command:", command
                            
                            commandReturn = 1
                            
                            # Repeat until job is submission is successful (returns 0)
                            while (commandReturn) :
                                
                                commandReturn = os.system(command)
                            
                            
                            print "\n"
                        
    
    
    print "\n"
    print "****************************************************************************************************"
    print "****************************************************************************************************"
    print "Total # unit:", nUnit_total
    print "Total # job:", nJob_total
    print "****************************************************************************************************"
    print "****************************************************************************************************"
    print "\n"

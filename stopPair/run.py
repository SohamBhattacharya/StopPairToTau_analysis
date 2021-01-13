import os


dictionary = {}


dictionary["tauTau_data"] = {
    "process": [
        "Tau",
    ],
    
    "directory": "tauTau_data",
    
    "run": {
        "analysis:tauTau": ["tauTau_data_analysis", "@1@_tauTau_analysis", "_tauTau"]
    }
}


dictionary["muTau_data"] = {
    "process": [
        "SingleMuon",
    ],
    
    "directory": "muTau_data",
    
    "run": {
        "analysis:muTau": ["muTau_data_analysis", "@1@_muTau_analysis", "_muTau"]
    }
}


dictionary["elMu_data"] = {
    "process": [
        #"MuonEG_Run2016B-18Apr2017_ver2-v1_MINIAOD",
        #"MuonEG_Run2016C-18Apr2017-v1_MINIAOD",
        #"MuonEG_Run2016D-18Apr2017-v1_MINIAOD",
        #"MuonEG_Run2016E-18Apr2017-v1_MINIAOD",
        #"MuonEG_Run2016F-18Apr2017-v1_MINIAOD",
        #"MuonEG_Run2016G-18Apr2017-v1_MINIAOD",
        #"MuonEG_Run2016H-18Apr2017-v1_MINIAOD",
        
        "MuonEG_Run2017B-31Mar2018-v1_MINIAOD",
        "MuonEG_Run2017C-31Mar2018-v1_MINIAOD",
        "MuonEG_Run2017D-31Mar2018-v1_MINIAOD",
        "MuonEG_Run2017E-31Mar2018-v1_MINIAOD",
        "MuonEG_Run2017F-31Mar2018-v1_MINIAOD",
    ],
    
    "directory": "elMu_data",
    
    "run": {
        "analysis:elMu": ["elMu_data_analysis", "@1@_elMu_analysis", "_elMu"]
    }
}


dictionary["muMu_data"] = {
    "process": [
        #"SingleMuon_Run2016B-18Apr2017_ver2-v1_MINIAOD",
        #"SingleMuon_Run2016C-18Apr2017-v1_MINIAOD",
        #"SingleMuon_Run2016D-18Apr2017-v1_MINIAOD",
        #"SingleMuon_Run2016E-18Apr2017-v1_MINIAOD",
        #"SingleMuon_Run2016F-18Apr2017-v2_MINIAOD",
        #"SingleMuon_Run2016G-18Apr2017-v1_MINIAOD",
        #"SingleMuon_Run2016H-18Apr2017-v1_MINIAOD",
        
        "SingleMuon_Run2017B-31Mar2018-v1_MINIAOD",
        "SingleMuon_Run2017C-31Mar2018-v1_MINIAOD",
        "SingleMuon_Run2017D-31Mar2018-v1_MINIAOD",
        "SingleMuon_Run2017E-31Mar2018-v1_MINIAOD",
        "SingleMuon_Run2017F-31Mar2018-v1_MINIAOD",
    ],
    
    "directory": "muMu_data",
    
    "run": {
        "analysis:muMu": ["muMu_data_analysis", "@1@_muMu_analysis", "_muMu"]
    }
}


#dictionary["stopPair_mc"] = {
#    "process": [
#        "stopPair_mc_1",
#        "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#        "SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#        "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#    ],
#    
#    "directory": "stopPair_mc",
#    
#    "run": {
#        "pileUp": ["stopPair_mc_pileUp", "@1@_pileUp", ""],
#        
#        "analysis:elMu": ["stopPair_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
#        "analysis:tauTau": ["stopPair_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"]
#    }
#}


dictionary["DYJets_mc"] = {
    "process": [
        #"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    ],
    
    "directory": "DYJetsToLL_mc",
    
    "run": {
        "pileUp": ["DYJetsToLL_mc_pileUp", "@1@_pileUp", ""],
        
        "bTaggingEfficiency": ["DYJetsToLL_mc_bTaggingEfficiency", "@1@_bTaggingEfficiency", ""],
        
        "tauIdIsoEfficiency": ["DYJetsToLL_tauIdIsoEfficiency", "@1@_tauIdIsoEfficiency", ""],
        
        "analysis:elMu": ["DYJetsToLL_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
        "analysis:muMu": ["DYJetsToLL_muMu_mc_analysis", "@1@_muMu_analysis", "_muMu"],
        "analysis:tauTau": ["DYJetsToLL_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"],
        "analysis:muTau": ["DYJetsToLL_muTau_mc_analysis", "@1@_muTau_analysis", "_muTau"],
    }
}


dictionary["WJets_mc"] = {
    "process": [
        "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        "W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    ],
    
    "directory": "WJetsToLNu_mc",
    
    "run": {
        "pileUp": ["WJetsToLNu_mc_pileUp", "@1@_pileUp", ""],
        
        "bTaggingEfficiency": ["WJetsToLNu_mc_bTaggingEfficiency", "@1@_bTaggingEfficiency", ""],
        
        "analysis:elMu": ["WJetsToLNu_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
        "analysis:muMu": ["WJetsToLNu_muMu_mc_analysis", "@1@_muMu_analysis", "_muMu"],
        "analysis:tauTau": ["WJetsToLNu_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"],
        "analysis:muTau": ["WJetsToLNu_muTau_mc_analysis", "@1@_muTau_analysis", "_muTau"],
    }
}


dictionary["VH_mc"] = {
    "process": [
        "ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8",
        "WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8",
    ],
    
    "directory": "VH_mc",
    
    "run": {
        "pileUp": ["VH_mc_pileUp", "@1@_pileUp", ""],
        
        "bTaggingEfficiency": ["VH_mc_bTaggingEfficiency", "@1@_bTaggingEfficiency", ""],
        
        "analysis:elMu": ["VH_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
        "analysis:muMu": ["VH_muMu_mc_analysis", "@1@_muMu_analysis", "_muMu"],
        "analysis:tauTau": ["VH_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"],
        "analysis:muTau": ["VH_muTau_mc_analysis", "@1@_muTau_analysis", "_muTau"],
    }
}


dictionary["VV_mc"] = {
    "process": [
        "VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8",
        "WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
        "ZZTo4L_13TeV-amcatnloFXFX-pythia8",
        "ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
        "WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8",
        "WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
        "WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8",
        "WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    ],
    
    "directory": "VV_mc",
    
    "run": {
        "pileUp": ["VV_mc_pileUp", "@1@_pileUp", ""],
        
        "bTaggingEfficiency": ["VV_mc_bTaggingEfficiency", "@1@_bTaggingEfficiency", ""],
        
        "analysis:elMu": ["VV_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
        "analysis:muMu": ["VV_muMu_mc_analysis", "@1@_muMu_analysis", "_muMu"],
        "analysis:tauTau": ["VV_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"],
        "analysis:muTau": ["VV_muTau_mc_analysis", "@1@_muTau_analysis", "_muTau"],
    }
}


dictionary["WG_mc"] = {
    "process": [
        "WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
        "WGstarToLNuMuMu_012Jets_13TeV-madgraph",
        "WGstarToLNuEE_012Jets_13TeV-madgraph",
    ],
    
    "directory": "WG_mc",
    
    "run": {
        "pileUp": ["WG_mc_pileUp", "@1@_pileUp", ""],
        
        "bTaggingEfficiency": ["WG_mc_bTaggingEfficiency", "@1@_bTaggingEfficiency", ""],
        
        "analysis:elMu": ["WG_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
        "analysis:muMu": ["WG_muMu_mc_analysis", "@1@_muMu_analysis", "_muMu"],
        "analysis:tauTau": ["WG_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"],
        "analysis:muTau": ["WG_muTau_mc_analysis", "@1@_muTau_analysis", "_muTau"],
    }
}


dictionary["ttbar_mc"] = {
    "process": [
        "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
    ],
    
    "directory": "ttbar_mc",
    
    "run": {
        "pileUp": ["ttbar_mc_pileUp", "@1@_pileUp", ""],
        
        "bTaggingEfficiency": ["ttbar_mc_bTaggingEfficiency", "@1@_bTaggingEfficiency", ""],
        
        "tauIdIsoEfficiency": ["ttbar_tauIdIsoEfficiency", "@1@_tauIdIsoEfficiency", ""],
        
        "analysis:elMu": ["ttbar_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
        "analysis:muMu": ["ttbar_muMu_mc_analysis", "@1@_muMu_analysis", "_muMu"],
        "analysis:tauTau": ["ttbar_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"],
        "analysis:muTau": ["ttbar_muTau_mc_analysis", "@1@_muTau_analysis", "_muTau"],
    }
}


dictionary["singleTop_mc"] = {
    "process": [
        "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
        "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
        "ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
    ],
    
    "directory": "singleTop_mc",
    
    "run": {
        "pileUp": ["singleTop_mc_pileUp", "@1@_pileUp", ""],
        
        "bTaggingEfficiency": ["singleTop_mc_bTaggingEfficiency", "@1@_bTaggingEfficiency", ""],
        
        "analysis:elMu": ["singleTop_elMu_mc_analysis", "@1@_elMu_analysis", "_elMu"],
        "analysis:muMu": ["singleTop_muMu_mc_analysis", "@1@_muMu_analysis", "_muMu"],
        "analysis:tauTau": ["singleTop_tauTau_mc_analysis", "@1@_tauTau_analysis", "_tauTau"],
        "analysis:muTau": ["singleTop_muTau_mc_analysis", "@1@_muTau_analysis", "_muTau"],
    }
}


# Choose process
print "Choose process:"

for key in dictionary :
    
    print "\t", key

processOptionList = str(raw_input("Choice: "))
processOptionList = processOptionList.split(" ")

# Check input
for processOption in processOptionList :
    
    if(processOption not in dictionary) :
        
        print("Enter a valid option.")
        exit()

print processOptionList
print ""

# Choose what to run
print "Choose run option:"

for key in dictionary[processOption]["run"] :
    
    print "\t", key

runOption = str(raw_input("Choice: "))

# Check input
if(runOption not in dictionary[processOption]["run"]) :
    
    printf("Enter a valid option.")
    exit()

print ""


for processOption in processOptionList :
    
    #workingFileDir = dictionary[processOption]["directory"]
    #workingFile = "%s/%s" %(workingFileDir, dictionary[processOption]["run"][runOption][0])
    #workingFile_mod = "%s/%s" %(workingFileDir, dictionary[processOption]["run"][runOption][1])
    
    workingFile = "%s" %(dictionary[processOption]["run"][runOption][0])
    workingFile_mod = "%s" %(dictionary[processOption]["run"][runOption][1])
    
    suffix = dictionary[processOption]["run"][runOption][2]

    # Go to working directory
    os.chdir(dictionary[processOption]["directory"])
    
    for iEntry in range(0, len(dictionary[processOption]["process"])) :
        
        # Open file
        with open(workingFile + ".cc", "r") as f :
            
            workingFile_fileContent = f.read()
        
        process = dictionary[processOption]["process"][iEntry]
        
        workingFile_mod_temp = workingFile_mod.replace("@1@", process)
        
        # Edit file
        workingFile_fileContent = workingFile_fileContent.replace("@1@", process)
        #workingFile_fileContent = workingFile_fileContent.replace("@2@", process + suffix)
        workingFile_fileContent = workingFile_fileContent.replace("@2@", workingFile_mod_temp)
        
        # Write file
        with open(workingFile_mod_temp + ".cc", "w") as f :
            
            f.write(workingFile_fileContent)
        
        # Compile
        command = "g++mod ch " + workingFile_mod_temp
        print command
        commandReturn = os.system(command)
        
        if(not commandReturn) :
            
            os.system("mkdir -p logs")
            
            # Run
            command = "nohup ./" + workingFile_mod_temp + \
                " > " + "logs/" + workingFile_mod_temp + ".log &"
            
            print command
            os.system(command)
        
        else :
            
            print "Compilation not successful."
            
            exit()
        
        print "\n"
    
    
    # Go back to parent directory
    os.chdir("..")

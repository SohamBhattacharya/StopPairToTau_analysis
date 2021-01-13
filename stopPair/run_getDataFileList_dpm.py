import os
import subprocess


dictionary = {}




dictionary["2016"] = [
    ##["", "Tau", "Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD"],
    ##["", "Tau", "Tau_Run2016C-18Apr2017-v1_MINIAOD"],
    ##["", "Tau", "Tau_Run2016D-18Apr2017-v1_MINIAOD"],
    ##["", "Tau", "Tau_Run2016E-18Apr2017-v1_MINIAOD"],
    ##["", "Tau", "Tau_Run2016F-18Apr2017-v1_MINIAOD"],
    ##["", "Tau", "Tau_Run2016G-18Apr2017-v1_MINIAOD"],
    ##["", "Tau", "Tau_Run2016H-18Apr2017-v1_MINIAOD"],
    #
    #["", "Tau", "Tau_Run2016B-07Aug17_ver2-v1_MINIAOD"],
    #["", "Tau", "Tau_Run2016C-07Aug17-v1_MINIAOD"],
    #["", "Tau", "Tau_Run2016D-07Aug17-v1_MINIAOD"],
    #["", "Tau", "Tau_Run2016E-07Aug17-v1_MINIAOD"],
    #["", "Tau", "Tau_Run2016F-07Aug17-v1_MINIAOD"],
    #["", "Tau", "Tau_Run2016G-07Aug17-v1_MINIAOD"],
    #["", "Tau", "Tau_Run2016H-07Aug17-v1_MINIAOD"],
    #
    ##["", "MuonEG", "MuonEG_Run2016B-18Apr2017_ver2-v1_MINIAOD"],
    ##["", "MuonEG", "MuonEG_Run2016C-18Apr2017-v1_MINIAOD"],
    ##["", "MuonEG", "MuonEG_Run2016D-18Apr2017-v1_MINIAOD"],
    ##["", "MuonEG", "MuonEG_Run2016E-18Apr2017-v1_MINIAOD"],
    ##["", "MuonEG", "MuonEG_Run2016F-18Apr2017-v1_MINIAOD"],
    ##["", "MuonEG", "MuonEG_Run2016G-18Apr2017-v1_MINIAOD"],
    ##["", "MuonEG", "MuonEG_Run2016H-18Apr2017-v1_MINIAOD"],
    #
    #["", "MuonEG", "MuonEG_Run2016B-07Aug17_ver2-v1_MINIAOD"],
    #["", "MuonEG", "MuonEG_Run2016C-07Aug17-v1_MINIAOD"],
    #["", "MuonEG", "MuonEG_Run2016D-07Aug17-v1_MINIAOD"],
    #["", "MuonEG", "MuonEG_Run2016E-07Aug17-v1_MINIAOD"],
    #["", "MuonEG", "MuonEG_Run2016F-07Aug17-v1_MINIAOD"],
    #["", "MuonEG", "MuonEG_Run2016G-07Aug17-v1_MINIAOD"],
    #["", "MuonEG", "MuonEG_Run2016H-07Aug17-v1_MINIAOD"],
    
    ["", "SingleElectron", "SingleElectron_Run2016B-07Aug17_ver2-v2_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2016C-07Aug17-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2016D-07Aug17-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2016E-07Aug17-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2016F-07Aug17-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2016G-07Aug17-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2016H-07Aug17-v1_MINIAOD"],
    
    ##["", "SingleMuon", "SingleMuon_Run2016B-18Apr2017_ver2-v1_MINIAOD"],
    ##["", "SingleMuon", "SingleMuon_Run2016C-18Apr2017-v1_MINIAOD"],
    ##["", "SingleMuon", "SingleMuon_Run2016D-18Apr2017-v1_MINIAOD"],
    ##["", "SingleMuon", "SingleMuon_Run2016E-18Apr2017-v1_MINIAOD"],
    ##["", "SingleMuon", "SingleMuon_Run2016F-18Apr2017-v2_MINIAOD"],
    ##["", "SingleMuon", "SingleMuon_Run2016G-18Apr2017-v1_MINIAOD"],
    ##["", "SingleMuon", "SingleMuon_Run2016H-18Apr2017-v1_MINIAOD"],
    #
    #["", "SingleMuon", "SingleMuon_Run2016B-07Aug17_ver2-v1_MINIAOD"],
    #["", "SingleMuon", "SingleMuon_Run2016C-07Aug17-v1_MINIAOD"],
    #["", "SingleMuon", "SingleMuon_Run2016D-07Aug17-v1_MINIAOD"],
    #["", "SingleMuon", "SingleMuon_Run2016E-07Aug17-v1_MINIAOD"],
    #["", "SingleMuon", "SingleMuon_Run2016F-07Aug17-v1_MINIAOD"],
    #["", "SingleMuon", "SingleMuon_Run2016G-07Aug17-v1_MINIAOD"],
    #["", "SingleMuon", "SingleMuon_Run2016H-07Aug17-v1_MINIAOD"],
    
    
    #["", "", "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    
    ##["", "", "DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    
    ##["", "", "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_FastSim_Summer16"],
    
    #
    #["", "", "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #["", "", "W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    #
    ###["", "", "ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Summer16"],
    #["", "", "ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #["", "", "WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #
    #["", "", "VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #["", "", "WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #["", "", "WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_Summer16"],
    #["", "", "WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #["", "", "WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #["", "", "WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #["", "", "ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16"],
    #["", "", "ZZTo4L_13TeV-amcatnloFXFX-pythia8_Summer16"],
    #
    #["", "", "WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Summer16"],
    #["", "", "WGstarToLNuEE_012Jets_13TeV-madgraph_Summer16"],
    #["", "", "WGstarToLNuMuMu_012Jets_13TeV-madgraph_Summer16"],
    #
    ###["", "", "TT_TuneCUETP8M1_13TeV-powheg-pythia8_Summer16"],
    #["", "", "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16"],
    
    ##["", "", "TTJets_13TeV-madgraphMLM_FastSim_Summer16"],
    ##["", "", "TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"],
    
    #["", "", "ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16"],
    #["", "", "ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16"],
    #["", "", "ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16"],
    #["", "", "ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16"],
    
    #["", "", "TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16"],
    #["", "", "TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16"],
    #["", "", "TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16"],
    #["", "", "TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16"],
    
    
    
    ###["", "QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8"],
    ###["", "QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8"]
]


dictionary["2017"] = [
    ["", "Tau", "Tau_Run2017B-31Mar2018-v1_MINIAOD"],
    ["", "Tau", "Tau_Run2017C-31Mar2018-v1_MINIAOD"],
    ["", "Tau", "Tau_Run2017D-31Mar2018-v1_MINIAOD"],
    ["", "Tau", "Tau_Run2017E-31Mar2018-v1_MINIAOD"],
    ["", "Tau", "Tau_Run2017F-31Mar2018-v1_MINIAOD"],
    
    ["", "MuonEG", "MuonEG_Run2017B-31Mar2018-v1_MINIAOD"],
    ["", "MuonEG", "MuonEG_Run2017C-31Mar2018-v1_MINIAOD"],
    ["", "MuonEG", "MuonEG_Run2017D-31Mar2018-v1_MINIAOD"],
    ["", "MuonEG", "MuonEG_Run2017E-31Mar2018-v1_MINIAOD"],
    ["", "MuonEG", "MuonEG_Run2017F-31Mar2018-v1_MINIAOD"],
    
    ["", "SingleElectron", "SingleElectron_Run2017B-31Mar2018-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2017C-31Mar2018-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2017D-31Mar2018-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2017E-31Mar2018-v1_MINIAOD"],
    ["", "SingleElectron", "SingleElectron_Run2017F-31Mar2018-v1_MINIAOD"],
    
    ["", "SingleMuon", "SingleMuon_Run2017B-31Mar2018-v1_MINIAOD"],
    ["", "SingleMuon", "SingleMuon_Run2017C-31Mar2018-v1_MINIAOD"],
    ["", "SingleMuon", "SingleMuon_Run2017D-31Mar2018-v1_MINIAOD"],
    ["", "SingleMuon", "SingleMuon_Run2017E-31Mar2018-v1_MINIAOD"],
    ["", "SingleMuon", "SingleMuon_Run2017F-31Mar2018-v1_MINIAOD"],
    
    ["", "", "SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17"],
    
    ["", "", "DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    
    ["", "", "WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ["", "", "W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    
    ["", "", "WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17"],
    ["", "", "WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17"],
    ["", "", "ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Fall17"],
    
    ["", "", "VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Fall17"],
    ["", "", "WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17"],
    ["", "", "WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17"],
    ["", "", "WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_Fall17"],
    ["", "", "WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17"],
    ["", "", "ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17"],
    ["", "", "ZZTo4L_13TeV_powheg_pythia8_Fall17"],
    
    ["", "", "WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    
    ["", "", "ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17"],
    ["", "", "ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17"],
    ["", "", "ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17"],
    ["", "", "ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17"],
    
    ["", "", "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17"],
    ["", "", "TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17"],
    ["", "", "TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_Fall17"],
    
    ##["", "", "TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17"],
    ##["", "", "TTJets_DiLept_TuneCP2_13TeV-madgraphMLM-pythia8_FastSim_Fall17"],
    
    ["", "", "TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8_Fall17"],
    ["", "", "TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_Fall17"],
    ["", "", "TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17"],
    ["", "", "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17"],
]


scriptName = "getDataFileList_dpm.sh"
scriptName_mod = "getDataFileList_dpm_mod.sh"


print("Option:")
print("1 --> Number of events")
print("2 --> Data file list")
option = str(input("Choice: "))
print("")


print("Option:")
print("2016 --> 2016")
print("2017 --> 2017")
era = str(input("Choice: "))
print("")

dictionary = dictionary[era]

era_str = ""

if (era == "2016") :
    
    era_str = "_Summer16"

elif (era == "2017") :
    
    era_str = "_Fall17"

else :
    
    print("Error: Enter a valid era.")
    exit(1)


for iEntry in range(0, len(dictionary)) :
    
    if (not len(dictionary[iEntry][1])) :
        
        suffix = era_str
        
        if ("FastSim" in dictionary[iEntry][2]) :
            
            suffix = "_FastSim%s" %(suffix)
        
        dictionary[iEntry][1] = dictionary[iEntry][2][0: dictionary[iEntry][2].find(suffix)]
    
    #crabDir = "/home/sobhatta/t3store2/PhD/source2custom/CMSSW_9_4_10/src/crabJobs/crab_" + dictionary[iEntry][2]
    crabDir = "/home/sobhatta/t3store2/PhD/source2custom/CMSSW_10_6_5/src/crabJobs/crab_" + dictionary[iEntry][2]
    print("CRAB directory:", crabDir)
    
    if (option == "1") :
        
        print("Getting number of events:", dictionary[iEntry][2])
        
        crabReport = subprocess.Popen(["crab", "report", crabDir], stdout=subprocess.PIPE).communicate()[0].split("\n")
        
        nEvent = ""
        
        for line in crabReport :
            
            if ("Number of events read" in line) :
                
                nEvent = line
                break
        
        nEvent = nEvent[nEvent.find(":") + 1 :].strip()
        print("nEvent =", nEvent, "\n")
    
    elif (option == "2") :
        
        print("Getting file list:", dictionary[iEntry][2])
        
        # For python >= 2.7
        crabStatus = subprocess.check_output(["crab", "status", crabDir]).decode("utf-8").split("\n")
        
        # For python < 2.7
        #crabStatus = subprocess.Popen(["crab", "status", crabDir], stdout=subprocess.PIPE).communicate()[0].split("\n")
        
        jobID = ""
        
        for line in crabStatus :
            
            if ("Task name" in line) :
                
                jobID = line
                break
        
        jobID = jobID[jobID.find(":") + 1 : jobID.rfind(":")].strip()
        print("Task ID:", jobID)
        
        dictionary[iEntry][0] = jobID
        
        
        with open(scriptName, "r") as f :
            
            scriptName_fileContent = f.read()
        
        
        scriptName_fileContent = scriptName_fileContent.replace("@1@", dictionary[iEntry][0])
        scriptName_fileContent = scriptName_fileContent.replace("@2@", dictionary[iEntry][1])
        scriptName_fileContent = scriptName_fileContent.replace("@3@", dictionary[iEntry][2])
        
        
        with open(scriptName_mod, "w") as f :
            
            f.write(scriptName_fileContent)
        
        
        command = "chmod +x " + scriptName_mod
        os.system(command)
        
        command = "echo ./" + scriptName_mod + " | env -i bash -i"
        os.system(command)
    
    else :
        
        print("Enter a valid option.")
        exit()

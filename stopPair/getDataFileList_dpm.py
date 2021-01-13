import os


dictionary = [ \
    #"Tau", \
    #"MuonEG", \
    #\
    "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    "SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #\
    #"DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #"DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #"DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #"DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #\
    #"W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #"W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #"W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #"W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    #\
    #"TT_TuneCUETP8M1_13TeV-powheg-pythia8", \
    #\
    #"QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8", \
    #"QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8", \
]


scriptName = "getDataFileList_dpm.sh"
scriptName_mod = "getDataFileList_dpm_mod.sh"


for iEntry in range(0, len(dictionary)) :
    
    print "Getting file list:", dictionary[iEntry]
    
    crabDir = "/home/sobhatta/t3store2/PhD/source2custom/CMSSW_8_0_28_patch1/src/crabJobs/crab_" + dictionary[iEntry]
    
    outDir = "sourceFiles/" + dictionary[iEntry]
    outFile = "sourceFiles/" + dictionary[iEntry] + "/" + dictionary[iEntry] + "_custom.txt"
    
    command = "mkdir -p " + outDir
    print command
    os.system(command)
    
    command = "crab getoutput --xrootd " + crabDir + " | sort -V > " + outFile
    print command
    os.system(command)
    
    print "\n"

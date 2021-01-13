import glob
import numpy


directories = [
    #"elMu_data/output_analyzed/MuonEG",
    #"elMu_data/output_analyzed/MuonEG_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016C-18Apr2017-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016D-18Apr2017-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016E-18Apr2017-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016F-18Apr2017-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016G-18Apr2017-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016H-18Apr2017-v1_MINIAOD",
    
    "tauTau_data/output_analyzed/Tau",
    #"muTau_data/output_analyzed/SingleMuon",
    
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_200_100",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_300_150",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_500_325",
    #
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_200_100",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_300_150",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_500_325",
    
    ##"DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"DYJetsToLL_mc/output_analyzed/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"DYJetsToLL_mc/output_analyzed/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #
    #"WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"WJetsToLNu_mc/output_analyzed/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"WJetsToLNu_mc/output_analyzed/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"WJetsToLNu_mc/output_analyzed/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"WJetsToLNu_mc/output_analyzed/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #
    #"VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8",
    #"VH_mc/output_analyzed/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8",
    #
    #"VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8",
    #"VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    #"VV_mc/output_analyzed/ZZTo4L_13TeV-amcatnloFXFX-pythia8",
    #"VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    #"VV_mc/output_analyzed/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8",
    #"VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    #"VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8",
    #"VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    #
    #"WG_mc/output_analyzed/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
    #"WG_mc/output_analyzed/WGstarToLNuMuMu_012Jets_13TeV-madgraph",
    #"WG_mc/output_analyzed/WGstarToLNuEE_012Jets_13TeV-madgraph",
    #
    #"singleTop_mc/output_analyzed/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
    #"singleTop_mc/output_analyzed/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
    #"singleTop_mc/output_analyzed/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
    #"singleTop_mc/output_analyzed/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
    #
    #"ttbar_mc/output_analyzed/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
]


suffix = ""

print "Options:"
print "1a --> Analysis: elMu"
print "1b --> Analysis: tauTau"
print "1c --> Analysis: muTau"
option = str(raw_input("Choice: "))

if (option == "1a") :
    
    suffix = "_elMu_analysis"

elif (option == "1b") :
    
    suffix = "_tauTau_analysis"

elif (option == "1c") :
    
    suffix = "_muTau_analysis"

else :
    
    print "Enter a valid option."
    exit()


temp_str = "someNonExistantString"


for iDir in range(0, len(directories)) :
    
    # Get cut-flow directories
    dirContent = glob.glob(directories[iDir] + suffix + "/**")
    temp_str = directories[iDir] + suffix + "/cutFlow_"
    cutFlowDirs = [d for d in dirContent if (d.find(temp_str) == 0)]# and d.find("cutFlow1") < 0)]
    
    # Loop over cut-flow directories
    for iCutFlowDir in range(0, len(cutFlowDirs)) :
        
        print "Combining files in directory:", cutFlowDirs[iCutFlowDir]
        
        # Get cut-flow files
        cutFlowFiles = glob.glob(cutFlowDirs[iCutFlowDir] + "/**")
        cutFlowFiles = [f for f in cutFlowFiles if (f.find(".txt") != -1 and f.find("all") == -1)]
        
        print "Number of files:", len(cutFlowFiles)
        
        
        # Output file name
        cutFlow_fileName_sample = cutFlowFiles[0]
        cutFlow_combined_fileName = cutFlow_fileName_sample[0: cutFlow_fileName_sample.rfind("/")]
        cutFlow_fileName_sample = cutFlow_fileName_sample[cutFlow_fileName_sample.rfind("/")+1:]
        
        if(cutFlow_fileName_sample.find("custom_") == 0) :
            
            cutFlow_fileName_sample = "custom_all_cutFlow.txt"
        
        cutFlow_combined_fileName += "/" + cutFlow_fileName_sample
        print "Output file:", cutFlow_combined_fileName
        
        
        # Add files
        cutFlow_combined = numpy.zeros(0)
        
        for iFile in range(0, len(cutFlowFiles)) :
            
            cutFlow_temp = numpy.loadtxt(cutFlowFiles[iFile], ndmin = 1)
            
            if(not cutFlow_combined.shape[0]) :
                
                cutFlow_combined = numpy.zeros(cutFlow_temp.shape[0])
            
            cutFlow_combined += cutFlow_temp
        
        print cutFlow_combined
        
        
        # Write combined cut-flow to file
        with open(cutFlow_combined_fileName, "w") as outFile:
            
            for iLine in range(0, cutFlow_combined.shape[0]) :
                
                outFile.write(str(float(cutFlow_combined[iLine])) + "\n")
        
        
        print ""

import glob
import numpy
import os


process = "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
massPointFile = "output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/massPointInfo.txt"

suffix = "_tauTau"
temp_str = "someNonExistantString"


massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")#[0: 1]


for iMass in range(0, massPointInfo.shape[0]) :
    
    stop1_m = massPointInfo[iMass, 0]
    neutralino_m = massPointInfo[iMass, 1]
    
    #print stop1_m, neutralino_m
    
    # Skip points if needed
    if(stop1_m <= 1050 and neutralino_m <= 650) :
        
        continue
    
    #if(stop1_m < 700) :
    #    
    #    continue
    
    print stop1_m, neutralino_m
    
    directory = "output_analyzed/" + process + "_" + str(int(stop1_m)) + "_" + str(int(neutralino_m)) + suffix + "_analysis"
    
    # Get cut-flow directories
    dirContent = glob.glob(directory + "/**")
    temp_str = directory + "/cutFlow_"
    cutFlowDirs = [d for d in dirContent if (d.find(temp_str) == 0 and d.find("tightIso_OS") >= 0)]# and d.find("cutFlow1") < 0)]
    
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

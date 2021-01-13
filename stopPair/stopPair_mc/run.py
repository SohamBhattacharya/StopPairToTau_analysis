import numpy
import os


dictionary = [ \
    #"stopPair_mc_1",
    "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    #"SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
]


massPoint_stop1_neutralino1 = [
    #[-1, -1]
    #[400, 250],
    [200, 100],
    [300, 150],
    [500, 325],
    #[500, 50],
]

suffix_elMu = "_elMu"
suffix_tauTau = "_tauTau"
suffix_muTau = "_muTau"

suffix = ""


pileUpFile = "stopPair_mc_pileUp"
pileUpFile_mod = "@1@_mc_pileUp"


genParamFile = "stopPair_mc_genParamInfo"
genParamFile_mod = "@1@_mc_genParamInfo"


analysisFile_tauTau = "stopPair_tauTau_mc_analysis"
analysisFile_tauTau_mod = "@1@_mc_analysis"

analysisFile_muTau = "stopPair_muTau_mc_analysis"
analysisFile_muTau_mod = "@1@_mc_analysis"

analysisFile_bTaggingEfficiency = "stopPair_mc_bTaggingEfficiency"
analysisFile_bTaggingEfficiency_mod = "@1@_bTaggingEfficiency"


print "Options:"
print "1a --> Pile-up"
print "1b --> Gen-param info"
print "2a --> Analysis - tauTau"
print "2b --> Analysis - muTau"
print "3a --> bTaggingEfficiency"
option = str(raw_input("Choice: "))


workingFile = ""
workingFile_mod = ""


if (option == "1a") :
    
    workingFile = pileUpFile
    workingFile_mod = pileUpFile_mod

elif (option == "1b") :
    
    workingFile = genParamFile
    workingFile_mod = genParamFile_mod

elif (option == "2a") :
    
    workingFile = analysisFile_tauTau
    workingFile_mod = analysisFile_tauTau_mod
    suffix = suffix_tauTau

elif (option == "2b") :
    
    workingFile = analysisFile_muTau
    workingFile_mod = analysisFile_muTau_mod
    suffix = suffix_muTau

elif (option == "3a") :
    
    workingFile = analysisFile_bTaggingEfficiency
    workingFile_mod = analysisFile_bTaggingEfficiency_mod

else :
    
    print "Enter a valid option."
    exit()


for iEntry in range(0, len(dictionary)) :
    
    massPoint_infoFile = "output_genParam/" + dictionary[iEntry] + "/massPointInfo.txt"
    massPoint_stop1_neutralino1 = numpy.loadtxt(massPoint_infoFile, delimiter = ",", dtype = int)[:, [0, 1]].tolist()
    print massPoint_stop1_neutralino1, "\n"
    print len(massPoint_stop1_neutralino1), "\n"
    
    #if (option == "1a" or option == "1b") :
    #    
    #    with open(workingFile + ".cc", "r") as f :
    #        
    #        workingFile_fileContent = f.read()
    #    
    #    workingFile_fileContent = workingFile_fileContent.replace("@1@", dictionary[iEntry])
    #    
    #    workingFile_mod_temp = workingFile_mod.replace("@1@", dictionary[iEntry])
    #    
    #    
    #    with open(workingFile_mod_temp + ".cc", "w") as f :
    #        
    #        f.write(workingFile_fileContent)
    #    
    #    
    #    command = "g++mod ch " + workingFile_mod_temp
    #    print command
    #    commandReturn = os.system(command)
    #    
    #    if(not commandReturn) :
    #        
    #        command = "nohup ./" + workingFile_mod_temp + " > logs/" + workingFile_mod_temp + ".log &"
    #        print command
    #        os.system(command)
    #    
    #    else :
    #        
    #        print "Compilation not successful."
    #        
    #        exit()
    #    
    #    print "\n"
    #
    #elif (option == "2a" or option == "2b") :
    #    
    #    for iMassPoint in range(0, len(massPoint_stop1_neutralino1)) :
    #        
    #        with open(workingFile + ".cc", "r") as f :
    #            
    #            workingFile_fileContent = f.read()
    #        
    #        stop1_m = str(int(massPoint_stop1_neutralino1[iMassPoint][0]))
    #        neutralino1_m = str(int(massPoint_stop1_neutralino1[iMassPoint][1]))
    #        
    #        suffix_temp = suffix
    #        
    #        if (massPoint_stop1_neutralino1[iMassPoint][0] > 0 and massPoint_stop1_neutralino1[iMassPoint][1] > 0) :
    #            
    #            suffix_temp = "_" + stop1_m + "_" + neutralino1_m + suffix
    #        
    #        workingFile_fileContent = workingFile_fileContent.replace("@1@", dictionary[iEntry])
    #        workingFile_fileContent = workingFile_fileContent.replace("@2@", dictionary[iEntry] + suffix_temp)
    #        workingFile_fileContent = workingFile_fileContent.replace("@3@", stop1_m)
    #        workingFile_fileContent = workingFile_fileContent.replace("@4@", neutralino1_m)
    #        
    #        workingFile_mod_temp = workingFile_mod.replace("@1@", dictionary[iEntry] + suffix_temp)
    #        
    #        
    #        with open(workingFile_mod_temp + ".cc", "w") as f :
    #            
    #            f.write(workingFile_fileContent)
    #        
    #        
    #        command = "g++mod ch " + workingFile_mod_temp
    #        print command
    #        commandReturn = os.system(command)
    #        
    #        if(not commandReturn) :
    #            
    #            command = "nohup ./" + workingFile_mod_temp + " > logs/" + workingFile_mod_temp + ".log &"
    #            print command
    #            os.system(command)
    #        
    #        else :
    #            
    #            print "Compilation not successful."
    #            
    #            exit()
    #        
    #        print "\n"
    #
    #elif (option == "3a") :
    #    
    #    #for iMassPoint in range(0, len(massPoint_stop1_neutralino1)) :
    #        
    #        with open(workingFile + ".cc", "r") as f :
    #            
    #            workingFile_fileContent = f.read()
    #        
    #        #stop1_m = str(int(massPoint_stop1_neutralino1[iMassPoint][0]))
    #        #neutralino1_m = str(int(massPoint_stop1_neutralino1[iMassPoint][1]))
    #        
    #        suffix_temp = suffix
    #        
    #        #if (massPoint_stop1_neutralino1[iMassPoint][0] > 0 and massPoint_stop1_neutralino1[iMassPoint][1] > 0) :
    #        #    
    #        #    suffix_temp = "_" + stop1_m + "_" + neutralino1_m + suffix
    #        
    #        workingFile_fileContent = workingFile_fileContent.replace("@1@", dictionary[iEntry] + suffix_temp)
    #        
    #        workingFile_mod_temp = workingFile_mod.replace("@1@", dictionary[iEntry] + suffix_temp)
    #        
    #        
    #        with open(workingFile_mod_temp + ".cc", "w") as f :
    #            
    #            f.write(workingFile_fileContent)
    #        
    #        command = "g++mod ch " + workingFile_mod_temp
    #        print command
    #        commandReturn = os.system(command)
    #        
    #        if(not commandReturn) :
    #            
    #            command = "nohup ./" + workingFile_mod_temp + " > logs/" + workingFile_mod_temp + ".log &"
    #            print command
    #            os.system(command)
    #        
    #        else :
    #            
    #            print "Compilation not successful."
    #            
    #            exit()
    #        
    #        print "\n"
    

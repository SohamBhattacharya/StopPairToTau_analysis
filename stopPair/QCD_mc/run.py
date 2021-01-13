import os


dictionary = [ \
    "QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8", \
    "QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8" ]


preAnalysisFile="QCD_mc_preAnalysis"
preAnalysisFile_mod="@1@_mc_preAnalysis"


analysisFile="QCD_mc_analysis"
analysisFile_mod="@1@_mc_analysis"


print "Options:"
print "1 --> Pre-analysis"
print "2 --> Analysis"
option = str(raw_input("Choice: "))


workingFile = ""
workingFile_mod = ""


if (option == "1") :
    
    workingFile = preAnalysisFile
    workingFile_mod = preAnalysisFile_mod

elif (option == "2") :
    
    workingFile = analysisFile
    workingFile_mod = analysisFile_mod

else :
    
    print "Enter a valid option."
    exit()


for iEntry in range(0, len(dictionary)) :
    
    with open(workingFile + ".cc", "r") as f :
        
        workingFile_fileContent = f.read()
    
    
    workingFile_fileContent = workingFile_fileContent.replace("@1@", dictionary[iEntry])
    workingFile_mod_temp = workingFile_mod.replace("@1@", dictionary[iEntry])
    
    
    with open(workingFile_mod_temp + ".cc", "w") as f :
        
        f.write(workingFile_fileContent)
    
    
    command = "g++mod " + workingFile_mod_temp
    print command
    commandReturn = os.system(command)
    
    if(not commandReturn) :
        
        command = "nohup ./" + workingFile_mod_temp + " > logs/" + workingFile_mod_temp + ".log &"
        #command = "./" + workingFile_mod_temp
        print command
        os.system(command)
    
    else :
        
        print "Compilation not successful."
        
        break
    
    print "\n"

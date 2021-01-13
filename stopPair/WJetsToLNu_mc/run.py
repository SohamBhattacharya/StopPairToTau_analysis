import os


dictionary = [ \
    "W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    "W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    "W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8", \
    "W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"]

suffix_elMu = "_elMu"
suffix_tauTau = "_tauTau"

pileUpFile="WJetsToLNu_mc_pileUp"
pileUpFile_mod="W@1@JetsToLNu_mc_pileUp"


analysisFile_tauTau = "WJetsToLNu_tauTau_mc_analysis"
analysisFile_tauTau_mod = "W@1@JetsToLNu_tauTau_mc_analysis"

analysisFile_elMu = "WJetsToLNu_elMu_mc_analysis"
analysisFile_elMu_mod = "W@1@JetsToLNu_elMu_mc_analysis"


print "Options:"
print "1 --> Pile-up"
print "2 --> Analysis - tauTau"
print "3 --> Analysis - elMu"
option = str(input("Choice: "))


workingFile = ""
workingFile_mod = ""

suffix = ""

if (option == "1") :
    
    workingFile = pileUpFile
    workingFile_mod = pileUpFile_mod

elif (option == "2") :
    
    workingFile = analysisFile_tauTau
    workingFile_mod = analysisFile_tauTau_mod
    suffix = suffix_tauTau

elif (option == "3") :
    
    workingFile = analysisFile_elMu
    workingFile_mod = analysisFile_elMu_mod
    suffix = suffix_elMu

else :
    
    print "Enter a valid option."
    exit()


for iEntry in range(0, len(dictionary)) :
    
    with open(workingFile + ".cc", "r") as f :
        
        workingFile_fileContent = f.read()
    
    
    workingFile_fileContent = workingFile_fileContent.replace("@1@", dictionary[iEntry])
    workingFile_fileContent = workingFile_fileContent.replace("@2@", dictionary[iEntry] + suffix)
    
    workingFile_mod_temp = workingFile_mod.replace("@1@", str(int(iEntry+1)))
    
    
    with open(workingFile_mod_temp + ".cc", "w") as f :
        
        f.write(workingFile_fileContent)
    
    
    command = "g++mod ch " + workingFile_mod_temp
    print command
    commandReturn = os.system(command)
    
    if(not commandReturn) :
        
        command = "nohup ./" + workingFile_mod_temp + " > logs/" + workingFile_mod_temp + ".log &"
        print command
        os.system(command)
    
    else :
        
        print "Compilation not successful."
        
        break
    
    print "\n"

import numpy
import os

import condorDiagnose


condorConfig = "condor_config.sub"
condorScript = "condor_script.sh"

condorConfig_name = condorConfig[0: condorConfig.rfind(".")]
condorConfig_ext = condorConfig[condorConfig.rfind("."):]

condorScript_name = condorScript[0: condorScript.rfind(".")]
condorScript_ext = condorScript[condorScript.rfind("."):]


#suffix = "_tauTau_TMVAtree"
suffix = "_tauTau_analysis"


#codeFile = "stopPair_mc/stopPair_tauTau_mc_TMVAtree.cc"
codeFile = "stopPair_mc/stopPair_tauTau_mc_analysis.cc"


process = "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
#process = "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"


processName = process + "_@stop1_m@_@neutralino1_m@"
inputFileList = "sourceFiles/" + process + "/" + process + "_custom.txt"
massPointFile = "stopPair_mc/output_genParam/" + process + "/massPointInfo.txt"

#process = "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
#processName = "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_@stop1_m@_@neutralino1_m@"
#inputFileList = "../sourceFiles/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_custom.txt"
#massPointFile = "output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/massPointInfo.txt"


processName += suffix


#faultyMassIndexList = condorDiagnose.getFaultyMassIndexList(process, suffix)

massPointList = numpy.loadtxt(massPointFile, dtype = int, delimiter = ",")#[faultyMassIndexList]


inputFiles = numpy.loadtxt(inputFileList, dtype = str)
nInputFile = inputFiles.shape[0]

nJob = massPointList.shape[0]

#nUnitPerJob = int(nInputFile/nJob)


print "Process:", process
print "Input file:", inputFileList
print "Code file:", codeFile
print "# jobs:", nJob
#print "# units:", inputFiles.shape[0]
#print "# units per job:", nUnitPerJob
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


#command = "mkdir -p " + condorDirectory
#print "Command:", command
#os.system(command)

print "\n"


for iJob in range(0, nJob) :
    
    stop1_m = int(massPointList[iJob, 0])
    neutralino1_m = int(massPointList[iJob, 1])
    
    processName_mod = processName
    processName_mod = processName_mod.replace("@stop1_m@", str(stop1_m))
    processName_mod = processName_mod.replace("@neutralino1_m@", str(neutralino1_m))
    
    condorDirectory = "condorJobs/condor_" + processName_mod
    
    command = "mkdir -p " + condorDirectory
    print "Command:", command
    os.system(command)
    
    
    codeFile_content_mod = codeFile_content
    condorConfig_content_mod = condorConfig_content
    condorScript_content_mod = condorScript_content
    
    inputFiles_mod = inputFiles
    
    #if iJob < nJob-1 :
    #    
    #    inputFiles_mod = inputFiles[iJob*nUnitPerJob: (iJob+1)*nUnitPerJob]
    #    
    #else :
    #    
    #    inputFiles_mod = inputFiles[iJob*nUnitPerJob:]
    
    condorConfig_mod = condorConfig_name + "_" + str(stop1_m) + "_" + str(neutralino1_m) + condorConfig_ext
    condorScript_mod = condorScript_name + "_" + str(stop1_m) + "_" + str(neutralino1_m) + condorScript_ext
    
    inputFileList_mod = inputFileList_name + "_" + str(stop1_m) + "_" + str(neutralino1_m) + inputFileList_ext
    codeFile_name_mod = codeFile_name + "_" + str(stop1_m) + "_" + str(neutralino1_m)
    
    
    # Condor config
    condorConfig_content_mod = condorConfig_content_mod.replace("@exe@", condorDirectory + "/" + condorScript_mod)
    condorConfig_content_mod = condorConfig_content_mod.replace("@log@", condorDirectory + "/" + codeFile_name_mod + ".log")
    condorConfig_content_mod = condorConfig_content_mod.replace("@out@", condorDirectory + "/" + codeFile_name_mod + ".out")
    condorConfig_content_mod = condorConfig_content_mod.replace("@err@", condorDirectory + "/" + codeFile_name_mod + ".err")
    
    print "Writing:", (condorDirectory + "/" + condorConfig_mod)
    
    with open(condorDirectory + "/" + condorConfig_mod, "w") as f :
        
        f.write(condorConfig_content_mod)
    
    
    # Condor script
    condorScript_content_mod = condorScript_content_mod.replace("@exe@", condorDirectory + "/" + codeFile_name_mod)
    
    print "Writing:", (condorDirectory + "/" + condorScript_mod)
    
    with open(condorDirectory + "/" + condorScript_mod, "w") as f :
        
        f.write(condorScript_content_mod)
    
    command = "chmod +x " + condorDirectory + "/" + condorScript_mod
    print "Command:", command
    os.system(command)
    
    
    # Code file
    codeFile_content_mod = codeFile_content_mod.replace("@process@", process)
    codeFile_content_mod = codeFile_content_mod.replace("@dir@", processName_mod)
    codeFile_content_mod = codeFile_content_mod.replace("@stop1_m@", str(stop1_m))
    codeFile_content_mod = codeFile_content_mod.replace("@neutralino1_m@", str(neutralino1_m))
    codeFile_content_mod = codeFile_content_mod.replace("@sourceFile@", condorDirectory + "/" + inputFileList_mod)
    
    print "Writing:", (condorDirectory + "/" + codeFile_name_mod + codeFile_ext)
    
    with open(condorDirectory + "/" + codeFile_name_mod + codeFile_ext, "w") as f :
        
        f.write(codeFile_content_mod)
    
    
    # Input file list
    print "Writing:", (condorDirectory + "/" + inputFileList_mod)
    
    with open(condorDirectory + "/" + inputFileList_mod, "w") as f :
        
        f.write("\n".join(inputFiles_mod) + "\n")
    
    
    commandReturn = 1
    
    # Repeat until job is submission is successful (returns 0)
    while (commandReturn) :
        
        commandReturn = os.system(command)
    
    
    print "\n"
    
    
    print "\n"
    

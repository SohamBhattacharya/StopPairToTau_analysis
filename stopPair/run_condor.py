import numpy
import os


condorConfig = "condor_config.sub"
condorScript = "condor_script.sh"

condorConfig_name = condorConfig[0: condorConfig.rfind(".")]
condorConfig_ext = condorConfig[condorConfig.rfind("."):]

condorScript_name = condorScript[0: condorScript.rfind(".")]
condorScript_ext = condorScript[condorScript.rfind("."):]


# Files to process per job
nUnitPerJob = 3

# Set to -1 for all files
nInputFileMax = -1


#l_process = [
#    "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
#]
#
#processName = ""
#outDir = "ttbar_mc/output_tauIdIsoEfficiency"
#otherInfoDir = "ttbar_mc"
#inputFileList_template = "sourceFiles/%s/%s_custom.txt"
#codeFile = "ttbar_mc/ttbar_tauIdIsoEfficiency.cc"
#suffix = "_tauIdIsoEfficiency"


#l_process = [
#    "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#]
#
#processName = ""
#outDir = "DYJetsToLL_mc/output_tauIdIsoEfficiency"
#otherInfoDir = "DYJetsToLL_mc"
#inputFileList_template = "sourceFiles/%s/%s_custom.txt"
#codeFile = "DYJetsToLL_mc/DYJetsToLL_tauIdIsoEfficiency.cc"
#suffix = "_tauIdIsoEfficiency"


l_process = [
    "SingleMuon_Run2016H-18Apr2017-v1_MINIAOD",
]

processName = ""
outDir = "muMu_data/output_tauTemplateMethodEstimation"
otherInfoDir = "muMu_data"
inputFileList_template = "sourceFiles/%s/%s_custom.txt"
codeFile = "muMu_data/muMu_data_tauTemplateMethodEstimation.cc"
suffix = "_muMu_tauTemplateMethodEstimation"


#l_process = [
#    "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#    "DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#    "DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#    "DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#    "DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
#]
#
#processName = ""
#outDir = "DYJetsToLL_mc/output_tauTemplateMethodEstimation"
#otherInfoDir = "DYJetsToLL_mc"
#inputFileList_template = "sourceFiles/%s/%s_custom.txt"
#codeFile = "DYJetsToLL_mc/DYJetsToLL_tauTau_mc_tauTemplateMethodEstimation.cc"
#suffix = "_tauTau_tauTemplateMethodEstimation"


#l_process = [
#    "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
#]
#
#processName = ""
#outDir = "ttbar_mc/output_tauTemplateMethodEstimation"
#otherInfoDir = "ttbar_mc"
#inputFileList_template = "sourceFiles/%s/%s_custom.txt"
#codeFile = "ttbar_mc/ttbar_tauTau_mc_tauTemplateMethodEstimation.cc"
#suffix = "_tauTau_tauTemplateMethodEstimation"


for iEntry in range(0, len(l_process)) :
    
    processName = l_process[iEntry]
    inputFileList = inputFileList_template %(l_process[iEntry], l_process[iEntry])
    
    
    outDir = "%s/%s%s" %(outDir, processName, suffix)
    
    condorDirectory = "condorJobs/condor_" + processName + suffix
    
    inputFiles = numpy.loadtxt(inputFileList, dtype = str)
    nInputFile = inputFiles.shape[0]
    
    if nInputFileMax > 0 and nInputFile > nInputFileMax :
        
        inputFiles = inputFiles[0: nInputFileMax]
        nInputFile = inputFiles.shape[0]
    
    nJob = int(numpy.ceil(float(nInputFile)/nUnitPerJob))
    
    print "Process:", processName
    print "Input file:", inputFileList
    print "Code file:", codeFile
    print "# jobs:", nJob
    print "# units:", inputFiles.shape[0]
    print "# units per job:", nUnitPerJob
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
        
        codeFile_content_mod = codeFile_content
        condorConfig_content_mod = condorConfig_content
        condorScript_content_mod = condorScript_content
        
        inputFiles_mod = []
        
        if iJob < nJob-1 :
            
            inputFiles_mod = inputFiles[iJob*nUnitPerJob: (iJob+1)*nUnitPerJob]
            
        else :
            
            inputFiles_mod = inputFiles[iJob*nUnitPerJob:]
        
        condorConfig_mod = condorConfig_name + "_" + str(int(iJob+1)) + condorConfig_ext
        condorScript_mod = condorScript_name + "_" + str(int(iJob+1)) + condorScript_ext
        
        inputFileList_mod = inputFileList_name + "_" + str(int(iJob+1)) + inputFileList_ext
        codeFile_name_mod = codeFile_name[codeFile_name.rfind("/")+1:] + "_" + str(int(iJob+1))
        
        
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
        codeFile_content_mod = codeFile_content_mod.replace("@process@", processName)
        codeFile_content_mod = codeFile_content_mod.replace("@dir@", outDir)
        codeFile_content_mod = codeFile_content_mod.replace("@otherInfoDir@", otherInfoDir)
        codeFile_content_mod = codeFile_content_mod.replace("@sourceFileName@", condorDirectory + "/" + inputFileList_mod)
        
        print "Writing:", (condorDirectory + "/" + codeFile_name_mod + codeFile_ext)
        
        with open(condorDirectory + "/" + codeFile_name_mod + codeFile_ext, "w") as f :
            
            f.write(codeFile_content_mod)
        
        
        # Input file list
        print "Writing:", (condorDirectory + "/" + inputFileList_mod)
        
        with open(condorDirectory + "/" + inputFileList_mod, "w") as f :
            
            f.write("\n".join(inputFiles_mod) + "\n")
        
        
        command = "condor_submit " + condorDirectory + "/" + condorConfig_mod
        print "Command:", command
        os.system(command)
        
        
        print "\n"
        

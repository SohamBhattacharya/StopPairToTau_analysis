import getpass
import glob
import multiprocessing
import numpy
import os
import subprocess
import time


##################################################
# Safety
##################################################
username = getpass.getuser()

if (username != "sobhatta") :
    
    print "WARNING!!! Probably running where you're NOT supposed to."
    print "Exiting."
    exit(1)

##################################################
##################################################


haddLogDir = "logs_hadd"
os.system("mkdir -p %s" %(haddLogDir))


##################################################
outputDir_analyzed = {}

l_syst_tauTau_analysis = [
    #"",
    
    #"tauES-systUp",
    #"tauES-systDown",
    #
    #"pileupReweight-systUp",
    #"pileupReweight-systDown",
    #
    #"tauIDisoSF-systUp",
    #"tauIDisoSF-systDown",
    #
    ###"triggerSF-systUp",
    ###"triggerSF-systDown",
    #
    #"tauFastFullSimSF-systUp",
    #"tauFastFullSimSF-systDown",
    #
    #"bTaggingSF-systUp",
    #"bTaggingSF-systDown",
    #
    #"JEC-systUp",
    #"JEC-systDown",
    #
    #"JER-systUp",
    #"JER-systDown",
    #
    #"unclusteredEnergy-systUp",
    #"unclusteredEnergy-systDown",
    
    "withGenMET",
]


l_tauTau_scaleVarIndex = [
    0,
    #1, 2, 3, 4, 6, 8
]


outputDir_analyzed["2016"] = [
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
]


outputDir_analyzed["2017"] = [
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
]


print "Era:"
print "2016 --> 2016"
print "2017 --> 2017"
era = str(raw_input("Choice: "))
print "\n"


outputDir = outputDir_analyzed[era]
outputFileName  = "custom_all_analyzed.root"
suffix = "_tauTau_analysis"
l_syst = l_syst_tauTau_analysis
l_scaleVarIndex = l_tauTau_scaleVarIndex


def work (command) :
    
    process = subprocess.Popen(command, shell = True)
    #os.system(command)
    
    return process


def doNothing() :
    
    return 1


l_command = []
l_process = []
l_runProcess = []
nWorkerMax = 10


for iDir in range(0, len(outputDir)) :
    
    #massPointFile = "stopPair_mc/output_genParam/%s/massPointInfo.txt" %(outputDir[iDir][outputDir[iDir].rfind("/"):])
    #
    #massPointFile_info = numpy.loadtxt(massPointFile, delimiter = ",")#[20: 21]
    #
    #for iMass in range(massPointFile_info.shape[0]) :
    
    #stop1_m = int(massPointFile_info[iMass][0])
    #neutralino1_m = int(massPointFile_info[iMass][1])
    
    for iSyst in range(0, len(l_syst)) :
        
        l_scaleVarIndex_mod = l_scaleVarIndex
        
        # If not nominal, do not run over scale variations
        if (len(l_syst[iSyst])) :
            
            l_scaleVarIndex_mod = [0]
        
        for iScaleVar in range(0, len(l_scaleVarIndex_mod)) :
            
            scaleVarIndex = l_scaleVarIndex_mod[iScaleVar]
            
            #suffix_mod = "%s_%d_%d" %(suffix, stop1_m, neutralino1_m)
            suffix_mod = suffix
            
            if (len(l_syst[iSyst])) :
                
                suffix_mod = "%s_%s" %(suffix_mod, l_syst[iSyst])
            
            if (scaleVarIndex != 0) :
                
                suffix_mod = "%s_scale%d" %(suffix_mod, scaleVarIndex)
            
            outputFile = outputDir[iDir] + suffix_mod + "/" + outputFileName
            
            command = "rm " + outputFile
            print command
            os.system(command)
            
            #command = "hadd " + outputFile + " `find " + outputDir[iDir] + suffix_mod + " | grep .root$ | grep -v %s | sort -V`" %(outputFileName)
            
            haddLogFile = "%s/hadd_%s%s.log" %(haddLogDir, outputDir[iDir][outputDir[iDir].rfind("/")+1:],suffix_mod)
            
            command = "hadd -n 50 -f0 %s `find %s%s | grep .root$ | grep -v %s | sort -V` &> %s" %(outputFile, outputDir[iDir], suffix_mod, outputFileName, haddLogFile)
            
            l_command.append(command)
            
            
            # Run
            while (sum([(runProc.poll() == None) for runProc in l_runProcess]) == nWorkerMax) :
                
                #time.sleep(30)
                doNothing()
            
            if (sum([(runProc.poll() == None) for runProc in l_runProcess]) < nWorkerMax) :
                
                print "Submitting:", command
                
                l_runProcess.append(
                    subprocess.Popen(command, shell = True)
                )
            
            
            print "\n\n"


# Wait for processes to complete
while (sum([(runProc.poll() == None) for runProc in l_runProcess])) :
    
    #time.sleep(30)
    doNothing()


#l_runProcess = []
#
#for iProc in range(0, len(l_process)) :
#    
#    proc = l_process[iProc]
#    
#    while (sum([runProc.is_alive() for runProc in l_runProcess]) == nWorkerMax) :
#        
#        time.sleep(30)
#    
#    if (sum([runProc.is_alive() for runProc in l_runProcess]) < nWorkerMax) :
#        
#        print "Submitting: %s" %(l_command[iProc])
#        
#        l_runProcess.append(proc)
#        proc.start()
#        
#        print "PID:", proc.pid
#        
#        print "\n"
#    
#    


#jobPool = multiprocessing.Pool(3)
#jobPool.map(work, l_command)

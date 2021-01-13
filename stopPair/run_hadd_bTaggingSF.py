import glob
import os

import run_condor_mod


########## Choose process ##########
print "Choose process:"

for key in run_condor_mod.dictionary :
    
    if ("data" in key) :
        
        continue
    
    print "\t", key

processOptionList = str(raw_input("Choice: ")).strip()
processOptionList = processOptionList.split()

# Check input
for processOption in processOptionList :
    
    if (processOption not in run_condor_mod.dictionary) :
        
        print("Enter a valid option.")
        exit(1)

print processOptionList
print ""


########## Choose era ##########
print "Choose era:"

for key in run_condor_mod.dictionary[processOption]["l_process"] :
    
    print "\t", key

era = str(raw_input("Choice: ")).strip()

# Check input
if (era not in run_condor_mod.dictionary[processOption]["l_process"]) :
    
    print("Enter a valid option.")
    exit(1)

print ""


for processOption in processOptionList :
    
    l_process = run_condor_mod.dictionary[processOption]["l_process"][era]
    
    sourceFileName_template = run_condor_mod.dictionary[processOption]["run"]["bTaggingEfficiency"]["inputFileList_template"]
    outDir_base = run_condor_mod.dictionary[processOption]["run"]["bTaggingEfficiency"]["outDir"]
    suffix = run_condor_mod.dictionary[processOption]["run"]["bTaggingEfficiency"]["suffix"]
    
    for iProcess in range(0, len(l_process)) :
        
        process = l_process[iProcess]
        sourceFileName = sourceFileName_template %(process, process)
        outDir = "%s/%s%s" %(outDir_base, process, suffix)
        outFileName = "%s/bTaggingEfficiency.root" %(outDir)
        
        print "\n\n"
        print "*"*50
        print "Source file:", sourceFileName
        print "Output directory:", outDir
        print "Output file:", outFileName
        print "*"*50
        print ""
        
        os.system("mkdir -p %s" %(outDir))
        os.system("rm %s" %(outFileName))
        
        command = "hadd -T %s `cat %s`" %(outFileName, sourceFileName)
        print command
        
        commandReturn = os.system(command)
        
        if(commandReturn) :
            
            print "Error."
            exit(1)

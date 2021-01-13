import argparse
import glob
import os
import re
import subprocess


# Argument parser
parser = argparse.ArgumentParser()

# List of directories
parser.add_argument(
    "-d",
    "--directories",
    help = "List of directories",
    nargs = "*",
    type = str,
    required = True
)

parser.add_argument(
    "-s",
    "--submit",
    help = "Sumbit the failed jobs",
    action = "store_true"
)

# Parse arguments
args = parser.parse_args()


l_directory = args.directories

print "You have entered:"
print "\n".join(l_directory)
print ""

if (args.submit) :
    
    print "Will SUBMIT the failed jobs."

else :
    
    print "Will NOT submit the failed jobs."

print ""
print "Enter YES to proceed, or anything else to cancel."
choice = raw_input("Input: ")

if (choice != "YES") :
    
    print "Exiting."
    exit()


extension_code = ".cc"
extension_out = ".out"
extension_err = ".err"

sourceFileStr = "custom"
sourceFileStr_mod= "mod"
extension_sourceFile = ".txt"

# Case insentitive
l_errorStr = ["error", "segmentation"]
l_errorStrSkip = ["unknown branch"]

condorConfig_nameTemplate = "condor_config_%s.sub"
command_template = "condor_submit %s"


nJobTotal = 0


underscoreIndex = -3


def getStrOccurrenceIndex(mainStr, subStr, occurrenceIndex) :
    
    l_pos = [pos.start() for pos in re.finditer(subStr, mainStr)]
    
    if (not len(l_pos)) :
        
        return -1
    
    return l_pos[occurrenceIndex]


for iDir in range(0, len(l_directory)) :
    
    directory = l_directory[iDir]
    
    print "\n"
    print "**************************************************"
    print "Directory:", directory
    print "**************************************************"
    
    if (not os.path.isdir(directory)) :
        
        print "Directory does not exist."
        exit(1)
    
    l_fileName = glob.glob(directory + "/**")
    
    l_fileName_sourceFile = [f for f in l_fileName if (sourceFileStr in f and sourceFileStr_mod not in f)]
    l_fileName_sourceFile.sort(key = lambda l: l[getStrOccurrenceIndex(l, "_", underscoreIndex)+1:])
    
    l_fileName_code = [f for f in l_fileName if extension_code in f]
    l_fileName_code.sort(key = lambda l: l[getStrOccurrenceIndex(l, "_", underscoreIndex)+1:])
    
    l_fileName_out = [f for f in l_fileName if extension_out in f]
    l_fileName_out.sort(key = lambda l: l[getStrOccurrenceIndex(l, "_", underscoreIndex)+1:])
    
    l_fileName_err = [f for f in l_fileName if extension_err in f]
    l_fileName_err.sort(key = lambda l: l[getStrOccurrenceIndex(l, "_", underscoreIndex)+1:])
    
    count = 0
    
    for iFile in range(0, len(l_fileName_err)) :
        
        fileName_code = l_fileName_code[iFile]
        fileName_out = l_fileName_out[iFile]
        fileName_err = l_fileName_err[iFile]
        fileName_sourceFile = l_fileName_sourceFile[iFile]
        
        fileName_sourceFile_mod = "%s_%s%s" %(fileName_sourceFile[: fileName_sourceFile.rfind(extension_sourceFile)], sourceFileStr_mod, extension_sourceFile)
        
        #####
        fileContent_err = []
        
        with open(fileName_err) as f :
            
            fileContent_err = f.readlines()
        
        #####
        fileContent_sourceFile = []
        
        with open(fileName_sourceFile) as f :
            
            fileContent_sourceFile = f.readlines()
        
        
        # Case insensitive search
        #if (not any([errorStr.lower() in line.lower() for line in fileContent_err])) :
        #if (not any([(errorStr.lower() in line.lower() and errorStrSkip.lower() not in line.lower()) for line in fileContent_err])) :
        #    
        #    continue
        
        hasError = False
        
        for errorStr in l_errorStr :
            
            for errorStrSkip in l_errorStrSkip :
                
                if (any([(errorStr.lower() in line.lower() and errorStrSkip.lower() not in line.lower()) for line in fileContent])) :
                    
                    hasError = True
                    
                    break
            
            if (hasError) :
                
                break
        
        if (not hasError) :
            
            continue
        
        count += 1
        nJobTotal += 1
        
        # Faster than reading and scanning the file
        nInputDone = int(subprocess.Popen(["grep -i input %s | wc -l" %(fileName_out)], stdout = subprocess.PIPE, shell = True).communicate()[0].strip().split("\n")[0])
        nInputDone -= 1
        
        number = fileName_err[getStrOccurrenceIndex(fileName_err, "_", underscoreIndex)+1: fileName_err.rfind(extension_err)]
        
        condorConfig_name = condorConfig_nameTemplate %(number)
        condorConfig_name = "%s/%s" %(directory, condorConfig_name)
        command = command_template %(condorConfig_name)
        
        
        #with open(fileName_sourceFile_mod, "w") as f :
        #    
        #    f.write("".join(fileContent_sourceFile[nInputDone:]))
        #
        #fileContent_code = []
        #
        #with open(fileName_code) as f :
        #    
        #    fileContent_code = f.readlines()
        #
        #fileContent_code = "".join(fileContent_code)
        #fileContent_code = fileContent_code.replace(fileName_sourceFile, fileName_sourceFile_mod)
        #
        #with open(fileName_code, "w") as f :
        #    
        #    f.write(fileContent_code)
        
        
        print "Count:", count
        print "Total count:", nJobTotal
        print "Code file:", fileName_code
        print "Out file:", fileName_out
        #print "Error file:", fileName_err
        #print "Source file:", fileName_sourceFile
        #print "Source file (mod):", fileName_sourceFile_mod
        print "Condor config:", condorConfig_name
        print "Files done: %s/%s" %(nInputDone, len(fileContent_sourceFile))
        
        if (args.submit) :
            
            print "Command:", command
            os.system(command)
        
        print ""

print "\n"
print "Total number of failed jobs:", nJobTotal
print "\n"

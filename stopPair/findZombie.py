import argparse
import glob
import os
import sys

import ROOT


# Argument parser
parser = argparse.ArgumentParser()

# List of directories
parser.add_argument(
    "-d",
    "--directories",
    help = "Directory",
    nargs = "*",
    type = str,
    required = True
)

# Parse arguments
args = parser.parse_args()

l_directory = args.directories


for iDir in range(0, len(l_directory)) :
    
    directory = l_directory[iDir]
    
    print ""
    print "*" * 50
    print "Directory:", directory
    print "*" * 50
    print ""
    
    l_fileName = glob.glob(directory + "/**")
    
    l_fileName = [ele for ele in l_fileName if ".root" in ele]
    
    l_zombie = []
    
    for iFile in range(0, len(l_fileName)) :
        
        fileName = l_fileName[iFile]
        
        # Note the trailing comma: prevents a newline
        # Note the carriage return (\r): takes the caret to the beginning of the line
        # Note the tabs (\t): clears the line if the previous print was longer
        print "Checking file %d/%d ... \t\t\t\t \r" %(iFile+1, len(l_fileName)),
        sys.stdout.flush()
        
        inputFile = ROOT.TFile(fileName)
        
        isZombie = inputFile.IsZombie()
        
        if (isZombie) :
            
            l_zombie.append(fileName)
        
        inputFile.Close()
    
    
    print ""
    
    #print "\n\n"
    print "Zombies:"
    
    print "\n".join(l_zombie)
    
    print "\n"

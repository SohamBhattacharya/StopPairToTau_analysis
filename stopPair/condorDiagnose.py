import glob
import numpy
import os
import subprocess


someNonExistantString = "someNonExistantString"


def getFaultyMassIndexList(process, suffix) :
    
    massPointFile = "output_genParam/" + process + "/massPointInfo.txt"
    massPointList = numpy.loadtxt(massPointFile, delimiter = ",")
    nMass = massPointList.shape[0]
    
    sourceFile = "../sourceFiles/" + process + "/" + process + "_custom.txt"
    nSourceFile = numpy.loadtxt(sourceFile, delimiter = someNonExistantString, dtype = str).shape[0]
    
    faultyMassIndexList = []
    
    for iMass in range(0, nMass) :
    
        stop1_m = int(massPointList[iMass][0])
        neutralino1_m = int(massPointList[iMass][1])
    
        dir = "output_analyzed/" + process + "_" + str(stop1_m) + "_" + str(neutralino1_m)  + suffix
        #print dir
    
        isFaulty = False
    
        fileList = glob.glob(dir + "/**")
        fileList = [f for f in fileList if (".root" in f and "all" not in f)]
    
        if len(fileList) < nSourceFile :
    
            print "Not all files analyzed (" + str(len(fileList)) + "/" + str(nSourceFile) + "):", massPointList[iMass]
            isFaulty = True
    
        if isFaulty :
    
            faultyMassIndexList.append(iMass)
    
    print "Faulty mass-point indices:", faultyMassIndexList
    print "Number of faulty mass-points:", len(faultyMassIndexList)    
    
    return faultyMassIndexList
    

def main() :
    
    process = "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
    suffix = "_tauTau_analysis"
    
    getFaultyMassIndexList(process, suffix)

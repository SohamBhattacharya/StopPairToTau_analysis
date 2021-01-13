import numpy
import os


process = "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
#process = "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"

massPointFile = "output_genParam/" + process + "/massPointInfo.txt"

suffix = "_tauTau_analysis"
outputFileName = "custom_all_analyzed.root"

#suffix = "_tauTau_TMVAtree"
#outputFileName = "custom_all_TMVAtree.root"

massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")#[378:]


for iMass in range(0, massPointInfo.shape[0]) :

    stop1_m = massPointInfo[iMass, 0]
    neutralino1_m = massPointInfo[iMass, 1]

    #outputDir = "output_TMVAtree/" + process + "_" + str(int(stop1_m)) + "_" + str(int(neutralino1_m)) + suffix
    outputDir = "output_analyzed/" + process + "_" + str(int(stop1_m)) + "_" + str(int(neutralino1_m)) + suffix

    outputFile = outputDir+ "/" + outputFileName

    command = "rm " + outputFile
    print command
    os.system(command)

    command = "hadd " + outputFile + " `find " + outputDir + " | grep .root$`"
    print command
    commandReturn = os.system(command)

    if(commandReturn) :

        print "Error."
        exit()

    print "\n\n"


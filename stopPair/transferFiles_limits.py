import numpy
import os

pwd = "Indiacms*1964"

l_file = [
    #"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
    ###"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
    #"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
    "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_combined_tauTau_analysis/limitInfo_SRB.txt",
    
    #"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
    ###"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
    #"stopPair_mc/output_combine/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
    "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_combined_tauTau_analysis/limitInfo_SRB.txt",
    
    #"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
    ###"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
    #"stopPair_mc/output_combine/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
    "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_combined_tauTau_analysis/limitInfo_SRB.txt",
]


path = "/home/sobhatta/t3store2/PhD/analysis/CMSSW_8_0_20/src/stopPair"

for iFile in range(0, len(l_file)) :
    
    fileName = l_file[iFile]
    
    sourcePath = "%s/%s" %(path, fileName)
    destPath = fileName[: fileName.rfind("/")+1]
    
    command = "rsync -asP sobhatta@ui.indiacms.res.in:%s %s" %(sourcePath, destPath)
    
    print "*"*50
    print command
    
    command = "sshpass -p %s %s" %(pwd, command)
    
    os.system(command)
    
    print "\n"

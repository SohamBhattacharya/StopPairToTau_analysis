import argparse
import glob
import os


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


#directory = "condorJobs/condor_SingleMuon_Run2016H-18Apr2017-v1_MINIAOD_muMu_tauTemplateMethodEstimation"
#directory = "condorJobs/condor_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauTau_tauTemplateMethodEstimation"
#directory = "condorJobs/condor_Tau_Run2016H-18Apr2017-v1_MINIAOD_tauTau_fakeEstimation"

#l_directory = [
#    #"condorJobs/condor_Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2016C-18Apr2017-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2016D-18Apr2017-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2016E-18Apr2017-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2016F-18Apr2017-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2016G-18Apr2017-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2016H-18Apr2017-v1_MINIAOD_tauTau_analysis",
#    
#    #"condorJobs/condor_Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2016C-18Apr2017-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2016D-18Apr2017-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2016E-18Apr2017-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2016F-18Apr2017-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2016G-18Apr2017-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2016H-18Apr2017-v1_MINIAOD_tauTau_fakeEstimation",
#    
#    #"condorJobs/condor_DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    
#    "condorJobs/condor_TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauTau_analysis",
#    
#    #"condorJobs/condor_W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    #"condorJobs/condor_WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis",
#    
#    #"condorJobs/condor_VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis",
#    #"condorJobs/condor_WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis",
#    #"condorJobs/condor_WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_tauTau_analysis",
#    #"condorJobs/condor_WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis",
#    #"condorJobs/condor_WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis",
#    #"condorJobs/condor_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis",
#    #"condorJobs/condor_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis",
#    #"condorJobs/condor_ZZTo4L_13TeV-amcatnloFXFX-pythia8_tauTau_analysis",
#    
#    
#    
#    #"condorJobs/condor_MuonEG_Run2017B-31Mar2018-v1_MINIAOD_elMu_analysis",
#    #"condorJobs/condor_MuonEG_Run2017C-31Mar2018-v1_MINIAOD_elMu_analysis",
#    #"condorJobs/condor_MuonEG_Run2017D-31Mar2018-v1_MINIAOD_elMu_analysis",
#    #"condorJobs/condor_MuonEG_Run2017E-31Mar2018-v1_MINIAOD_elMu_analysis",
#    #"condorJobs/condor_MuonEG_Run2017F-31Mar2018-v1_MINIAOD_elMu_analysis",
#    #
#    #"condorJobs/condor_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #
#    #"condorJobs/condor_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #
#    #"condorJobs/condor_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17_elMu_analysis",
#    #
#    #"condorJobs/condor_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_Fall17_elMu_analysis",
#    #
#    #"condorJobs/condor_VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_Fall17_elMu_analysis",
#    #"condorJobs/condor_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_ZZTo4L_13TeV_powheg_pythia8_Fall17_elMu_analysis",
#    #
#    #"condorJobs/condor_WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_elMu_analysis",
#    #
#    #"condorJobs/condor_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17_elMu_analysis",
#    #"condorJobs/condor_WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17_elMu_analysis",
#    
#    
#    
#    #"condorJobs/condor_SingleMuon_Run2017B-31Mar2018-v1_MINIAOD_muMu_analysis",
#    #"condorJobs/condor_SingleMuon_Run2017C-31Mar2018-v1_MINIAOD_muMu_analysis",
#    #"condorJobs/condor_SingleMuon_Run2017D-31Mar2018-v1_MINIAOD_muMu_analysis",
#    #"condorJobs/condor_SingleMuon_Run2017E-31Mar2018-v1_MINIAOD_muMu_analysis",
#    #"condorJobs/condor_SingleMuon_Run2017F-31Mar2018-v1_MINIAOD_muMu_analysis",
#    #
#    #"condorJobs/condor_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #
#    #"condorJobs/condor_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #
#    #"condorJobs/condor_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17_muMu_analysis",
#    #
#    #"condorJobs/condor_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_Fall17_muMu_analysis",
#    #
#    #"condorJobs/condor_VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_Fall17_muMu_analysis",
#    #"condorJobs/condor_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_ZZTo4L_13TeV_powheg_pythia8_Fall17_muMu_analysis",
#    #
#    #"condorJobs/condor_WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muMu_analysis",
#    #
#    #"condorJobs/condor_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17_muMu_analysis",
#    #"condorJobs/condor_WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17_muMu_analysis",
#    
#    
#    
#    #"condorJobs/condor_Tau_Run2017B-31Mar2018-v1_MINIAOD_tauTau_fakeRate",
#    #"condorJobs/condor_Tau_Run2017C-31Mar2018-v1_MINIAOD_tauTau_fakeRate",
#    #"condorJobs/condor_Tau_Run2017D-31Mar2018-v1_MINIAOD_tauTau_fakeRate",
#    #"condorJobs/condor_Tau_Run2017E-31Mar2018-v1_MINIAOD_tauTau_fakeRate",
#    #"condorJobs/condor_Tau_Run2017F-31Mar2018-v1_MINIAOD_tauTau_fakeRate",
#    #
#    #
#    #"condorJobs/condor_Tau_Run2017B-31Mar2018-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2017C-31Mar2018-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2017D-31Mar2018-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2017E-31Mar2018-v1_MINIAOD_tauTau_fakeEstimation",
#    #"condorJobs/condor_Tau_Run2017F-31Mar2018-v1_MINIAOD_tauTau_fakeEstimation",
#    #
#    #
#    #"condorJobs/condor_Tau_Run2017B-31Mar2018-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2017C-31Mar2018-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2017D-31Mar2018-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2017E-31Mar2018-v1_MINIAOD_tauTau_analysis",
#    #"condorJobs/condor_Tau_Run2017F-31Mar2018-v1_MINIAOD_tauTau_analysis",
#    #
#    #"condorJobs/condor_DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #
#    #"condorJobs/condor_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #
#    #"condorJobs/condor_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17_tauTau_analysis",
#    #
#    #"condorJobs/condor_TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_Fall17_tauTau_analysis",
#    #
#    #"condorJobs/condor_VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_Fall17_tauTau_analysis",
#    #"condorJobs/condor_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_ZZTo4L_13TeV_powheg_pythia8_Fall17_tauTau_analysis",
#    #
#    #"condorJobs/condor_WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis",
#    #
#    #"condorJobs/condor_ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17_tauTau_analysis",
#    #"condorJobs/condor_WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17_tauTau_analysis",
#]

extension = ".err"

# Case insentitive
l_errorStr = ["error", "segmentation", "killed", "SCRAM fatal"]
l_errorStrSkip = ["unknown branch"]

condorConfig_nameTemplate = "condor_config_%s.sub"
command_template = "condor_submit %s"


l_syst = [
    "",
    
    #"tauIDisoSF-systUp",
    #"tauIDisoSF-systDown",
    #
    #"topPtReweight-systUp",
    #"topPtReweight-systDown",
]


nJobTotal = 0


for iDir in range(0, len(l_directory)) :
    
    for iSyst in range(0, len(l_syst)) :
        
        directory = l_directory[iDir]
        
        if (len(l_syst[iSyst])) :
            
            directory = "%s_%s" %(directory, l_syst[iSyst])
        
        print "\n"
        print "**************************************************"
        print "Directory:", directory
        print "**************************************************"
        
        if (not os.path.isdir(directory)) :
            
            print "Directory does not exist."
            exit(1)
        
        l_fileName = glob.glob(directory + "/**")
        l_fileName = [f for f in l_fileName if extension in f]
        l_fileName.sort(key = lambda l: int(l[l.rfind("_")+1: l.rfind(extension)]))
        
        count = 0
        
        for iFile in range(0, len(l_fileName)) :
            
            fileName = l_fileName[iFile]
            
            fileContent = []
            
            with open(fileName) as f :
                
                fileContent = f.readlines()
            
            # Case insensitive search
            #if (not any([errorStr.lower() in line.lower() for line in fileContent])) :
            #if (not any([(errorStr.lower() in line.lower() and errorStrSkip.lower() not in line.lower()) for line in fileContent])) :
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
            
            number = fileName[fileName.rfind("_")+1: fileName.rfind(extension)]
            
            condorConfig_name = condorConfig_nameTemplate %(number)
            condorConfig_name = "%s/%s" %(directory, condorConfig_name)
            command = command_template %(condorConfig_name)
            
            print "Count:", count
            print "Total count:", nJobTotal
            print "File:", fileName
            print "Condor config:", condorConfig_name
            
            if (args.submit) :
                
                os.system("rm %s" %(fileName))
                
                print "Command:", command
                os.system(command)
            
            print ""

print "\n"
print "Total number of failed jobs:", nJobTotal
print "\n"

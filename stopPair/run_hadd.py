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


#abspath = "/home/sobhatta/t3store2/PhD/analysis/CMSSW_8_0_20/src/stopPair"
abspath = os.getcwd()


haddLogDir = "logs_hadd"
os.system("mkdir -p %s" %(haddLogDir))


##################################################
outputDir_analyzed = {}

l_syst_tauTau_analysis = [
    "",
    
    #"tauES-systUp",
    #"tauES-systDown",
    #
    #"pileupReweight-systUp",
    #"pileupReweight-systDown",
    #
    #"topPtReweight-systUp",
    #"topPtReweight-systDown",
    #
    #"ZpTreweight-systUp",
    #"ZpTreweight-systDown",
    #
    #"tauIDisoSF-systUp",
    #"tauIDisoSF-systDown",
    #
    ####"triggerSF-systUp",
    ####"triggerSF-systDown",
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
]


l_systName_tauTau_fakeEstimation = [
    "",
    
    #"tauFakeRateRegion-systUp",
    #"tauFakeRateRegion-systDown",
    #
    #"tauFakeRateJetPartonFlav-systUp",
    #"tauFakeRateJetPartonFlav-systDown",
]


l_tauTau_scaleVarIndex = [
    0,
    #1, 2, 3, 4, 6, 8
]


outputDir_analyzed["2016"] = [
    ##"elMu_data/output_analyzed/MuonEG_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    ##"elMu_data/output_analyzed/MuonEG_Run2016C-18Apr2017-v1_MINIAOD",
    ##"elMu_data/output_analyzed/MuonEG_Run2016D-18Apr2017-v1_MINIAOD",
    ##"elMu_data/output_analyzed/MuonEG_Run2016E-18Apr2017-v1_MINIAOD",
    ##"elMu_data/output_analyzed/MuonEG_Run2016F-18Apr2017-v1_MINIAOD",
    ##"elMu_data/output_analyzed/MuonEG_Run2016G-18Apr2017-v1_MINIAOD",
    ##"elMu_data/output_analyzed/MuonEG_Run2016H-18Apr2017-v1_MINIAOD",
    
    #"elMu_data/output_analyzed/MuonEG_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016C-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016D-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016E-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016F-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016G-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016H-07Aug17-v1_MINIAOD",
    
    
    ##"muMu_data/output_analyzed/SingleMuon_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    ##"muMu_data/output_analyzed/SingleMuon_Run2016D-18Apr2017-v1_MINIAOD",
    ##"muMu_data/output_analyzed/SingleMuon_Run2016E-18Apr2017-v1_MINIAOD",
    ##"muMu_data/output_analyzed/SingleMuon_Run2016F-18Apr2017-v2_MINIAOD",
    ##"muMu_data/output_analyzed/SingleMuon_Run2016G-18Apr2017-v1_MINIAOD",
    ##"muMu_data/output_analyzed/SingleMuon_Run2016H-18Apr2017-v1_MINIAOD",
    ##"muMu_data/output_analyzed/SingleMuon_Run2016C-18Apr2017-v1_MINIAOD",
    
    #"muMu_data/output_analyzed/SingleMuon_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2016C-07Aug17-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2016D-07Aug17-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2016E-07Aug17-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2016F-07Aug17-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2016G-07Aug17-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2016H-07Aug17-v1_MINIAOD",
    
    
    #"muTau_data/output_analyzed/SingleMuon_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2016C-07Aug17-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2016D-07Aug17-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2016E-07Aug17-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2016F-07Aug17-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2016G-07Aug17-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2016H-07Aug17-v1_MINIAOD",
    
    
    ##"tauTau_data/output_analyzed/Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    ##"tauTau_data/output_analyzed/Tau_Run2016C-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_analyzed/Tau_Run2016D-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_analyzed/Tau_Run2016E-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_analyzed/Tau_Run2016F-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_analyzed/Tau_Run2016G-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_analyzed/Tau_Run2016H-18Apr2017-v1_MINIAOD",
    
    #"tauTau_data/output_analyzed/Tau_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016C-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016D-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016E-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016F-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016G-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016H-07Aug17-v1_MINIAOD",
    
    
    #"muTau_data/output_analyzed/SingleMuon",
    
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    
    #"DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"DYJetsToLL_mc/output_analyzed/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"DYJetsToLL_mc/output_analyzed/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #
    #"WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"WJetsToLNu_mc/output_analyzed/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"WJetsToLNu_mc/output_analyzed/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"WJetsToLNu_mc/output_analyzed/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #"WJetsToLNu_mc/output_analyzed/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    #
    #"VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VH_mc/output_analyzed/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #
    #"VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/ZZTo4L_13TeV-amcatnloFXFX-pythia8_Summer16",
    #"VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_Summer16",
    #"VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #
    #"WG_mc/output_analyzed/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Summer16",
    #"WG_mc/output_analyzed/WGstarToLNuMuMu_012Jets_13TeV-madgraph_Summer16",
    #"WG_mc/output_analyzed/WGstarToLNuEE_012Jets_13TeV-madgraph_Summer16",
    #
    #"singleTop_mc/output_analyzed/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16",
    #"singleTop_mc/output_analyzed/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16",
    #"singleTop_mc/output_analyzed/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16",
    #"singleTop_mc/output_analyzed/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16",
    #
    #"ttbar_mc/output_analyzed/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16",
    #
    #"TTX_mc/output_analyzed/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16",
    #"TTX_mc/output_analyzed/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16",
    #"TTX_mc/output_analyzed/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16",
    #"TTX_mc/output_analyzed/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16",
    
    #"QCD_mc/output_analyzed/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8",
    #"QCD_mc/output_analyzed/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8",
]


outputDir_analyzed["2017"] = [
    #"tauTau_data/output_analyzed/Tau_Run2017B-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2017C-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2017D-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2017E-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2017F-31Mar2018-v1_MINIAOD",
    
    #"elMu_data/output_analyzed/MuonEG_Run2017B-31Mar2018-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2017C-31Mar2018-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2017D-31Mar2018-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2017E-31Mar2018-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2017F-31Mar2018-v1_MINIAOD",
    
    #"muMu_data/output_analyzed/SingleMuon_Run2017B-31Mar2018-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2017C-31Mar2018-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2017D-31Mar2018-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2017E-31Mar2018-v1_MINIAOD",
    #"muMu_data/output_analyzed/SingleMuon_Run2017F-31Mar2018-v1_MINIAOD",
    
    #"muTau_data/output_analyzed/SingleMuon_Run2017B-31Mar2018-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2017C-31Mar2018-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2017D-31Mar2018-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2017E-31Mar2018-v1_MINIAOD",
    #"muTau_data/output_analyzed/SingleMuon_Run2017F-31Mar2018-v1_MINIAOD",
    
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    #"stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    
    "DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    
    "WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "WJetsToLNu_mc/output_analyzed/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "WJetsToLNu_mc/output_analyzed/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "WJetsToLNu_mc/output_analyzed/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "WJetsToLNu_mc/output_analyzed/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    
    "VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Fall17",
    "VH_mc/output_analyzed/WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17",
    "VH_mc/output_analyzed/WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17",
    
    "VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    "VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    "VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    "VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_Fall17",
    "VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    "VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    "VV_mc/output_analyzed/ZZTo4L_13TeV_powheg_pythia8_Fall17",
    
    "WG_mc/output_analyzed/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    
    "ttbar_mc/output_analyzed/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17",
    "ttbar_mc/output_analyzed/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17",
    "ttbar_mc/output_analyzed/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_Fall17",
    
    "singleTop_mc/output_analyzed/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17",
    "singleTop_mc/output_analyzed/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17",
    "singleTop_mc/output_analyzed/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17",
    "singleTop_mc/output_analyzed/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17",
    
    "TTX_mc/output_analyzed/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8_Fall17",
    "TTX_mc/output_analyzed/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_Fall17",
    "TTX_mc/output_analyzed/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17",
    "TTX_mc/output_analyzed/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17",
]


##################################################
outputDir_tauFakeRate = {}

outputDir_tauFakeRate["2016"] = [
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-18Apr2017-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-18Apr2017-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-18Apr2017-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-18Apr2017-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-18Apr2017-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-18Apr2017-v1_MINIAOD",
    
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-07Aug17-v1_MINIAOD",
    
    
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-17Jul2018_ver2-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-17Jul2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-17Jul2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-17Jul2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-17Jul2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-17Jul2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-17Jul2018-v1_MINIAOD",
]

outputDir_tauFakeRate["2017"] = [
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017B-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017C-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017D-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017E-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017F-31Mar2018-v1_MINIAOD",
]


##################################################
outputDir_tauFakeEstimation = {}

outputDir_tauFakeEstimation["2016"] = [
    ##"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    ##"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016C-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016D-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016E-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016F-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016G-18Apr2017-v1_MINIAOD",
    ##"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016H-18Apr2017-v1_MINIAOD",
    
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016B-07Aug17_ver2-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016C-07Aug17-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016D-07Aug17-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016E-07Aug17-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016F-07Aug17-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016G-07Aug17-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016H-07Aug17-v1_MINIAOD",
]

outputDir_tauFakeEstimation["2017"] = [
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017B-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017C-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017D-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017E-31Mar2018-v1_MINIAOD",
    "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017F-31Mar2018-v1_MINIAOD",
]


outputDir_tauTemplateMethod = [
    #"muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    #"muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016C-18Apr2017-v1_MINIAOD",
    #"muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016D-18Apr2017-v1_MINIAOD",
    #"muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016E-18Apr2017-v1_MINIAOD",
    #"muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016F-18Apr2017-v2_MINIAOD",
    #"muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016G-18Apr2017-v1_MINIAOD",
    #"muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016H-18Apr2017-v1_MINIAOD",
    
    "DYJetsToLL_mc/output_tauTemplateMethodEstimation/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_tauTemplateMethodEstimation/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_tauTemplateMethodEstimation/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_tauTemplateMethodEstimation/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_tauTemplateMethodEstimation/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    
    "WJetsToLNu_mc/output_tauTemplateMethodEstimation/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_tauTemplateMethodEstimation/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_tauTemplateMethodEstimation/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_tauTemplateMethodEstimation/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_tauTemplateMethodEstimation/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    
    "VH_mc/output_tauTemplateMethodEstimation/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8",
    "VH_mc/output_tauTemplateMethodEstimation/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8",
    
    "VV_mc/output_tauTemplateMethodEstimation/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_tauTemplateMethodEstimation/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_tauTemplateMethodEstimation/ZZTo4L_13TeV-amcatnloFXFX-pythia8",
    "VV_mc/output_tauTemplateMethodEstimation/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_tauTemplateMethodEstimation/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8",
    "VV_mc/output_tauTemplateMethodEstimation/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_tauTemplateMethodEstimation/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_tauTemplateMethodEstimation/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    
    "WG_mc/output_tauTemplateMethodEstimation/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
    "WG_mc/output_tauTemplateMethodEstimation/WGstarToLNuMuMu_012Jets_13TeV-madgraph",
    "WG_mc/output_tauTemplateMethodEstimation/WGstarToLNuEE_012Jets_13TeV-madgraph",
    
    "singleTop_mc/output_tauTemplateMethodEstimation/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
    "singleTop_mc/output_tauTemplateMethodEstimation/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
    "singleTop_mc/output_tauTemplateMethodEstimation/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
    "singleTop_mc/output_tauTemplateMethodEstimation/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
    
    "ttbar_mc/output_tauTemplateMethodEstimation/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
]


##################################################
outputDir_pileUp = {}

outputDir_pileUp["2016"] = [
    "stopPair_mc/output_pileUp/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "stopPair_mc/output_pileUp/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "stopPair_mc/output_pileUp/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    
    "DYJetsToLL_mc/output_pileUp/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "DYJetsToLL_mc/output_pileUp/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "DYJetsToLL_mc/output_pileUp/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "DYJetsToLL_mc/output_pileUp/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "DYJetsToLL_mc/output_pileUp/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    
    "WJetsToLNu_mc/output_pileUp/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "WJetsToLNu_mc/output_pileUp/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "WJetsToLNu_mc/output_pileUp/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "WJetsToLNu_mc/output_pileUp/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "WJetsToLNu_mc/output_pileUp/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    
    "VH_mc/output_pileUp/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    "VH_mc/output_pileUp/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    
    "VV_mc/output_pileUp/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    "VV_mc/output_pileUp/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    "VV_mc/output_pileUp/ZZTo4L_13TeV-amcatnloFXFX-pythia8_Summer16",
    "VV_mc/output_pileUp/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    "VV_mc/output_pileUp/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_Summer16",
    "VV_mc/output_pileUp/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    "VV_mc/output_pileUp/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    "VV_mc/output_pileUp/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    
    "WG_mc/output_pileUp/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Summer16",
    "WG_mc/output_pileUp/WGstarToLNuMuMu_012Jets_13TeV-madgraph_Summer16",
    "WG_mc/output_pileUp/WGstarToLNuEE_012Jets_13TeV-madgraph_Summer16",
    
    "singleTop_mc/output_pileUp/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16",
    "singleTop_mc/output_pileUp/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_Summer16",
    "singleTop_mc/output_pileUp/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16",
    "singleTop_mc/output_pileUp/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_Summer16",
    
    "ttbar_mc/output_pileUp/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16",
    
    "TTX_mc/output_pileUp/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16",
    "TTX_mc/output_pileUp/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8_Summer16",
    "TTX_mc/output_pileUp/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16",
    "TTX_mc/output_pileUp/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8_Summer16",
]

outputDir_pileUp["2017"] = [
    
    "stopPair_mc/output_pileUp/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    "stopPair_mc/output_pileUp/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    "stopPair_mc/output_pileUp/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    
    #"DYJetsToLL_mc/output_pileUp/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"DYJetsToLL_mc/output_pileUp/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"DYJetsToLL_mc/output_pileUp/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"DYJetsToLL_mc/output_pileUp/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"DYJetsToLL_mc/output_pileUp/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #
    #"WJetsToLNu_mc/output_pileUp/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"WJetsToLNu_mc/output_pileUp/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"WJetsToLNu_mc/output_pileUp/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"WJetsToLNu_mc/output_pileUp/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #"WJetsToLNu_mc/output_pileUp/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #
    #"VH_mc/output_pileUp/ZH_HToBB_ZToLL_M125_13TeV_powheg_pythia8_Fall17",
    #"VH_mc/output_pileUp/WminusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17",
    #"VH_mc/output_pileUp/WplusH_HToBB_WToLNu_M125_13TeV_powheg_pythia8_Fall17",
    #
    #"VV_mc/output_pileUp/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    #"VV_mc/output_pileUp/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    #"VV_mc/output_pileUp/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    #"VV_mc/output_pileUp/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_Fall17",
    #"VV_mc/output_pileUp/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    #"VV_mc/output_pileUp/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Fall17",
    #"VV_mc/output_pileUp/ZZTo4L_13TeV_powheg_pythia8_Fall17",
    #
    #"WG_mc/output_pileUp/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    #
    #"ttbar_mc/output_pileUp/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17",
    #"ttbar_mc/output_pileUp/TTToHadronic_TuneCP5_13TeV-powheg-pythia8_Fall17",
    #"ttbar_mc/output_pileUp/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_Fall17",
    #
    #"singleTop_mc/output_pileUp/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17",
    #"singleTop_mc/output_pileUp/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8_Fall17",
    #"singleTop_mc/output_pileUp/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17",
    #"singleTop_mc/output_pileUp/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_Fall17",
    
    #"TTX_mc/output_pileUp/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8_Fall17",
    #"TTX_mc/output_pileUp/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_Fall17",
    #"TTX_mc/output_pileUp/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17",
    #"TTX_mc/output_pileUp/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_Fall17",
]




print "Options:"
print "1 --> Pile-up"
print "2a --> Analysis: elMu"
print "2b --> Analysis: tauTau"
print "2c --> Analysis: muTau"
print "2d --> Analysis: muMu"
print "3a --> TauTemplateMethod: tauTau"
print "4a --> TauFakeRate: tauTau"
print "5a --> TauFakeEstimation: tauTau"
option = str(raw_input("Choice: "))
print "\n"


print "Era:"
print "2016 --> 2016"
print "2017 --> 2017"
era = str(raw_input("Choice: "))
print "\n"


outputDir = []
outputFileName = ""
suffix = ""
l_syst = [""]
l_scaleVarIndex = [0]


if (option == "1") :
    
    outputDir = outputDir_pileUp[era]
    outputFileName  = "custom_all_pileUp.root"
    suffix = "_pileUp"

elif (option == "2a") :
    
    outputDir = outputDir_analyzed[era]
    outputFileName  = "custom_all_analyzed.root"
    suffix = "_elMu_analysis"

elif (option == "2b") :
    
    outputDir = outputDir_analyzed[era]
    outputFileName  = "custom_all_analyzed.root"
    suffix = "_tauTau_analysis"
    #suffix = "_tauTau_analysis_noBaseline"
    #suffix = "_tauTau_analysis_nJetGeq1"
    #suffix = "_tauTau_analysis_gtr1sigmaBins2016"
    #suffix = "_tauTau_analysis_partialUnblinding2017"
    #suffix = "_tauTau_analysis_nFakeTauGeq1"
    #suffix = "_tauTau_analysis_baselineSRB_METleq50"
    #suffix = "_tauTau_analysis_baselineSRB_METleq50_nFakeTauGeq1"
    #suffix = "_tauTau_analysis_DYCR"
    #suffix = "_tauTau_analysis_DYCR_withZpTreweighting"
    l_syst = l_syst_tauTau_analysis
    l_scaleVarIndex = l_tauTau_scaleVarIndex

elif (option == "2c") :
    
    outputDir = outputDir_analyzed[era]
    outputFileName  = "custom_all_analyzed.root"
    suffix = "_muTau_analysis"

elif (option == "2d") :
    
    outputDir = outputDir_analyzed[era]
    outputFileName  = "custom_all_analyzed.root"
    #suffix = "_muMu_analysis"
    #suffix = "_muMu_analysis_DYCR"
    suffix = "_muMu_analysis_DYCR_withZpTreweighting"

elif (option == "3a") :
    
    outputDir = outputDir_tauTemplateMethod
    outputFileName  = "custom_all_tauTemplateMethodEstimation.root"
    suffix = "_tauTau_tauTemplateMethodEstimation"
    
elif (option == "4a") :
    
    outputDir = outputDir_tauFakeRate[era]
    outputFileName  = "custom_all_fakeRate_tauTau.root"
    suffix = "_tauTau_fakeRate"
    #suffix = "_tauTau_fakeRate_METleq20"

elif (option == "5a") :
    
    outputDir = outputDir_tauFakeEstimation[era]
    outputFileName  = "custom_all_fakeEstimation_tauTau.root"
    suffix = "_tauTau_fakeEstimation"
    #suffix = "_tauTau_fakeEstimation_noBaseline"
    #suffix = "_tauTau_fakeEstimation_nJetGeq1"
    #suffix = "_tauTau_fakeEstimation_gtr1sigmaBins2016"
    #suffix = "_tauTau_fakeEstimation_baselineSRB_METleq50"
    #suffix = "_tauTau_fakeEstimation_DYCR"
    l_syst = l_systName_tauTau_fakeEstimation

else :
    
    print "Enter a valid option."
    exit()


def work (command) :
    
    process = subprocess.Popen(command, shell = True)
    #os.system(command)
    
    return process


def doNothing() :
    
    return 1


l_command = []
l_process = []
l_runProcess = []
nWorkerMax = 20


for iDir in range(0, len(outputDir)) :
    
    for iSyst in range(0, len(l_syst)) :
        
        l_scaleVarIndex_mod = l_scaleVarIndex
        
        # If not nominal, do not run over scale variations
        if (len(l_syst[iSyst])) :
            
            l_scaleVarIndex_mod = [0]
        
        for iScaleVar in range(0, len(l_scaleVarIndex_mod)) :
            
            scaleVarIndex = l_scaleVarIndex_mod[iScaleVar]
            
            suffix_mod = suffix
            
            if (len(l_syst[iSyst])) :
                
                suffix_mod = "%s_%s" %(suffix_mod, l_syst[iSyst])
            
            
            if (scaleVarIndex != 0) :
                
                suffix_mod = "%s_scale%d" %(suffix_mod, scaleVarIndex)
            
            
            outputFile = "%s/%s%s/%s" %(abspath, outputDir[iDir], suffix_mod, outputFileName)
            
            command = "rm " + outputFile
            print command
            os.system(command)
            
            #haddCompressionStr = ""
            haddCompressionStr = "-f0"
            
            #if ("data" in outputDir[iDir]) :
            #    
            #    haddCompressionStr = "-f0"
            
            haddLogFile = "%s/hadd_%s%s.log" %(haddLogDir, outputDir[iDir][outputDir[iDir].rfind("/")+1:],suffix_mod)
            
            #command = "hadd -f0 " + outputFile + " `find " + outputDir[iDir] + suffix_mod + " | grep .root$ | grep -v %s | sort -V`" %(outputFileName)
            command = "hadd %s %s `find %s/%s%s | grep .root$ | grep -v %s | sort -V` &> %s" %(
                haddCompressionStr,
                outputFile,
                abspath, outputDir[iDir], suffix_mod,
                outputFileName,
                haddLogFile
            )
            
            #print command
            
            #haddCompression = ""
            #
            #if ("data" in outputDir[iDir]) :
            #    
            #    haddCompression = "-f0"
            #
            #haddLogFile = "%s/hadd_%s%s.log" %(haddLogDir, outputDir[iDir][outputDir[iDir].rfind("/")+1:],suffix_mod)
            
            ##command = "nohup hadd %s %s `find %s%s | grep .root$ | grep -v %s | sort -V` > %s &" %(haddCompression, outputFile, outputDir[iDir], suffix_mod, outputFileName, haddLogFile)
            ##print command
            
            #commandReturn = os.system(command)
            #
            #if(commandReturn) :
            #    
            #    print "Error."
            #    exit()
            
            
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

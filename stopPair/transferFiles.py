import os


source_template = "sobhatta@ui3.indiacms.res.in:/home/sobhatta/t3store3/stopPairToTau/analysis/CMSSW_10_5_0/src/stopPair/%s"
destination_template = "%s/"


l_location = {}


l_location["2016"] = [
    ##"tauTau_data/output_analyzed",
    
    ##"tauTau_data/output_tauTau_fakeRate",
    ##"tauTau_data/output_tauTau_fakeEstimation",
    
    #"elMu_data/output_analyzed/MuonEG_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016C-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016D-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016E-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016F-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016G-07Aug17-v1_MINIAOD",
    #"elMu_data/output_analyzed/MuonEG_Run2016H-07Aug17-v1_MINIAOD",
    
    
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
    
    
    #"tauTau_data/output_analyzed/Tau_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016C-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016D-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016E-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016F-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016G-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_analyzed/Tau_Run2016H-07Aug17-v1_MINIAOD",
    
    
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-17Jul2018_ver2-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-17Jul2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-17Jul2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-17Jul2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-17Jul2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-17Jul2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-17Jul2018-v1_MINIAOD",
    
    
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016B-07Aug17_ver2-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016C-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016D-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016E-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016F-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016G-07Aug17-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2016H-07Aug17-v1_MINIAOD",
    
    
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
    #"VH_mc/output_analyzed/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #
    #"VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_Summer16",
    #"VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_Summer16",
    #"VV_mc/output_analyzed/ZZTo4L_13TeV-amcatnloFXFX-pythia8_Summer16",
    #
    #"WG_mc/output_analyzed/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_Summer16",
    #"WG_mc/output_analyzed/WGstarToLNuEE_012Jets_13TeV-madgraph_Summer16",
    #"WG_mc/output_analyzed/WGstarToLNuMuMu_012Jets_13TeV-madgraph_Summer16",
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
]


l_location["2017"] = [
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2017B-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2017C-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2017D-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2017E-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2017F-31Mar2018-v1_MINIAOD",
    
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017B-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017C-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017D-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017E-31Mar2018-v1_MINIAOD",
    #"tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017F-31Mar2018-v1_MINIAOD",
    
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


l_syst_tauTau_analysis = [
    "",
    
    #"tauES-systUp",
    #"tauES-systDown",
    #
    #"pileupReweight-systUp",
    #"pileupReweight-systDown",
    #
    ##"topPtReweight-systUp",
    ##"topPtReweight-systDown",
    #
    ##"ZpTreweight-systUp",
    ##"ZpTreweight-systDown",
    #
    #"tauIDisoSF-systUp",
    #"tauIDisoSF-systDown",
    #
    ##"triggerSF-systUp",
    ##"triggerSF-systDown",
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
    #
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


#fileNamePattern = "*custom_all_analyzed.root"
#suffix = "_elMu_analysis"
#l_syst = [""]
#l_scaleVarIndex = [0]


#fileNamePattern = "*custom_all_analyzed.root"
##suffix = "_muMu_analysis"
##suffix = "_muMu_analysis_DYCR"
#suffix = "_muMu_analysis_DYCR_withZpTreweighting"
#l_syst = [""]
#l_scaleVarIndex = [0]


#fileNamePattern = "*custom_all_analyzed.root"
#suffix = "_muTau_analysis"
#l_syst = [""]
#l_scaleVarIndex = [0]


#fileNamePattern = "*custom_all_analyzed.root"
#suffix = "_tauTau_analysis"
##suffix = "_tauTau_analysis_noBaseline"
##suffix = "_tauTau_analysis_nJetGeq1"
##suffix = "_tauTau_analysis_gtr1sigmaBins2016"
##suffix = "_tauTau_analysis_partialUnblinding2017"
##suffix = "_tauTau_analysis_nFakeTauGeq1"
##suffix = "_tauTau_analysis_baselineSRB_METleq50"
##suffix = "_tauTau_analysis_baselineSRB_METleq50_nFakeTauGeq1"
##suffix = "_tauTau_analysis_DYCR_withZpTreweighting"
#l_syst = l_syst_tauTau_analysis
#l_scaleVarIndex = l_tauTau_scaleVarIndex


fileNamePattern = "*custom_all_fakeRate_tauTau.root"
suffix = "_tauTau_fakeRate"
#suffix = "_tauTau_fakeRate_METleq20"
l_syst = [""]
l_scaleVarIndex = [0]


#fileNamePattern = "*custom_all_fakeEstimation_tauTau.root"
##suffix = "_tauTau_fakeEstimation"
##suffix = "_tauTau_fakeEstimation_noBaseline"
##suffix = "_tauTau_fakeEstimation_nJetGeq1"
##suffix = "_tauTau_fakeEstimation_gtr1sigmaBins2016"
#suffix = "_tauTau_fakeEstimation_baselineSRB_METleq50"
##suffix = "_tauTau_fakeEstimation_DYCR"
#l_syst = l_systName_tauTau_fakeEstimation
#l_scaleVarIndex = [0]


pwd = "Indiacms*1964"


print "Era:"
print "2016 --> 2016"
print "2017 --> 2017"
era = str(raw_input("Choice: "))
print "\n"


for iLocation in range(0, len(l_location[era])) :
    
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
            
            location = l_location[era][iLocation] + suffix_mod
            
            source = source_template %(location)
            destination = destination_template %(location[0:location.rfind("/")])
            
            #os.system("mkdir -p %s" %(destination))
            
            command = "rsync -asP --include \"%s\" --include \"*/\" --exclude \"*\" %s %s" %(fileNamePattern, source, destination)
            
            print ""
            print "**********"
            print "Source: %s" %(source)
            print "Destination: %s" %(destination)
            print "Command: %s" %(command)
            print ""
            
            command = "sshpass -p %s %s" %(pwd, command)
            
            os.system(command)

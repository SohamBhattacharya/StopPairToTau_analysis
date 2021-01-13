import os


source_template = "sobhatta@ui.indiacms.res.in:/home/sobhatta/t3store2/PhD/analysis/CMSSW_8_0_20/src/stopPair/%s"
destination_template = "%s/"


l_location = {}


l_location["2016"] = [
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
]


l_location["2017"] = [
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
]


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
    #0,
    #1, 2, 3, 4, 6, 8
]


fileNamePattern = "*custom_all_analyzed.root"
suffix = "_tauTau_analysis"
l_syst = l_syst_tauTau_analysis
l_scaleVarIndex = l_tauTau_scaleVarIndex



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
            
            #print "#####", location
            #print "#####", suffix_mod
            
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

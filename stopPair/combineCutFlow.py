import glob
import numpy

import Array2LatexTable

#numpy.seterr(divide="ignore", invalid = "ignore")


# Data
cutFlowDir_tauTau_data = [
    "tauTau_data/output_analyzed/Tau"
]

label_tauTau_data = [
    "$ Data: \\tau \\tau $"
]

cutFlowDir_muTau_data = [
    "muTau_data/output_analyzed/SingleMuon"
]

label_muTau_data = [
    "$ Data: \\mu \\tau $"
]

cutFlowDir_elMu_data = [
    #"elMu_data/output_analyzed/MuonEG"
    
    "elMu_data/output_analyzed/MuonEG_Run2016B-18Apr2017_ver2-v1_MINIAOD",
    "elMu_data/output_analyzed/MuonEG_Run2016C-18Apr2017-v1_MINIAOD",
    "elMu_data/output_analyzed/MuonEG_Run2016D-18Apr2017-v1_MINIAOD",
    "elMu_data/output_analyzed/MuonEG_Run2016E-18Apr2017-v1_MINIAOD",
    "elMu_data/output_analyzed/MuonEG_Run2016F-18Apr2017-v1_MINIAOD",
    "elMu_data/output_analyzed/MuonEG_Run2016G-18Apr2017-v1_MINIAOD",
    "elMu_data/output_analyzed/MuonEG_Run2016H-18Apr2017-v1_MINIAOD",
]

label_elMu_data = [
    "$ Data: e \\mu $"
]

#luminosity_data = 3.102 * 10**3
luminosity_data = 8.347 * 10**3
#luminosity_data = 35.9 * 10**3


# stopPair
cutFlowDir_stopPair = [
    #"stopPair_mc/output_analyzed/stopPair_mc_1",
    
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_200_100",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_300_150",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_500_325",
    
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_200_100",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_300_150",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_500_325",
]

crossSection_stopPair = [
    #1.443,
    
    64.5085,
    8.51615,
    0.51848,
    
    64.5085,
    8.51615,
    0.51848,
]

label_stopPair = [
    #"$ stopPair $",
    
    "$ 0.25, [200, 100] $",
    "$ 0.25, [300, 150] $",
    "$ 0.25, [500, 325] $",
    
    "$ 0.75, [200, 100] $",
    "$ 0.75, [300, 150] $",
    "$ 0.75, [500, 325] $",
]


# WJetsToLNu
cutFlowDir_WJetsToLNu = [
    "WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_analyzed/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_analyzed/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_analyzed/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "WJetsToLNu_mc/output_analyzed/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
]

crossSection_WJetsToLNu = [
    #1.21*9644.5,
    #1.21*3144.5,
    #1.21*954.8,
    #1.21*485.6,
    1.0/10**3,
    1.0/10**3,
    1.0/10**3,
    1.0/10**3,
    1.0/10**3,
]

label_WJetsToLNu = [
    "$ WJets $"
]


# DYJetsToLL
cutFlowDir_DYJetsToLL = [
    "DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_analyzed/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_analyzed/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
    "DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
]

crossSection_DYJetsToLL = [
    #1.16*1012.5,
    #1.16*332.8,
    #1.16*101.8,
    #1.16*54.8,
    1.0/10**3,
    1.0/10**3,
    1.0/10**3,
    1.0/10**3,
    1.0/10**3,
]

label_DYJetsToLL = [
    "$ DYJets $"
]


# VH
cutFlowDir_VH = [
    "VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8",
    "VH_mc/output_analyzed/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8",
]

crossSection_VH = [
    0.0515,
    0.2580,
]

label_VH = [
    "$ VH $"
]


# VV
cutFlowDir_VV = [
    "VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_analyzed/ZZTo4L_13TeV-amcatnloFXFX-pythia8",
    "VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_analyzed/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8",
    "VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8",
    "VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8",
]

crossSection_VV = [
    11.95,
    49.997,
    1.212,
    3.22,
    4.708,
    5.595,
    3.05,
    10.71,
]

label_VV = [
    "$ VV $"
]


# WG
cutFlowDir_WG = [
    "WG_mc/output_analyzed/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8",
    "WG_mc/output_analyzed/WGstarToLNuMuMu_012Jets_13TeV-madgraph",
    "WG_mc/output_analyzed/WGstarToLNuEE_012Jets_13TeV-madgraph",
]

crossSection_WG = [
    489.0,
    2.793,
    3.526,
]

label_WG = [
    "$ WG $"
]


# singleTop
cutFlowDir_singleTop = [
    "singleTop_mc/output_analyzed/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
    "singleTop_mc/output_analyzed/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1",
    "singleTop_mc/output_analyzed/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
    "singleTop_mc/output_analyzed/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1",
]

crossSection_singleTop = [
    35.6,
    35.6,
    80.95,
    136.02,
]

label_singleTop = [
    "$ ST $"
]


# ttbar
cutFlowDir_ttbar = [
    "ttbar_mc/output_analyzed/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8",
]

crossSection_ttbar = [
    831.76
]

label_ttbar = [
    "$ TT $"
]


#cutFlowDir_QCD = [
#    "QCD_mc/logs/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log",
#    "QCD_mc/logs/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8_mc_preAnalysis.log"]
#
#crossSection_QCD = [
#    1837410000.0,
#    140932000.0,
#    19204300.0,
#    2762530.0,
#    471100.0,
#    117276.0,
#    7823.0,
#    648.2,
#    186.9,
#    32.293,
#    9.4183,
#    0.84265,
#    0.114943,
#    0.00682981,
#    0.000165445]

label_QCD = [
    "$ QCD $"
]


suffix = ""

print "Options:"
print "1a --> Analysis: elMu"
print "1b --> Analysis: tauTau"
print "1c --> Analysis: muTau"
option = str(raw_input("Choice: "))

if (option == "1a") :
    
    suffix = "_elMu"

elif (option == "1b") :
    
    suffix = "_tauTau"

elif (option == "1c") :
    
    suffix = "_muTau"

else :
    
    print "Enter a valid option."
    exit()


temp_str = "someNonExistantString"


def getStringArray(array) :
    
    stringArray = []
    
    for iEntry in range(0, len(array)) :
        
        if (type(array[iEntry]) == str) :
            
            stringArray += [array[iEntry]]
            
        else :
            
            # Replace non-positive values with a "-"
            if (array[iEntry] <= 0) :
                
                stringArray += ["$ - $"]
            
            # Format conversion: X^Y --> XeY
            else :
                
                stringArray += ["$ " + ("%0.2e" % array[iEntry]).replace("+0", "").replace("-0", "-").replace("+", "") + " $"]
                #stringArray += ["$ " + ("%0.2e" % array[iEntry]) + " $"]
    
    return stringArray



def printLatexTable(table, rowLabel, tableCaption = "") :
    
    table = [[rowLabel[iRow]] + getStringArray(table[iRow]) for iRow in range(0, len(table))]
    
    print Array2LatexTable.array2LatexTable(table, isColumnTitled = True, table_caption = tableCaption)


def getCombinedCutFlow_QCD(
    cutFlowName,
    details_sig, details_shape,
    details_scaleNum, details_scaleDen,
    cutFlowDir_data, lumi_data,
    cutFlowDirs_mc, crossSections_mc,
    debug) :
    
    # Get Data
    cutFlow_sig = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_sig, debug).astype(float)
    cutFlow_shape = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_shape, debug).astype(float)
    cutFlow_scaleNum = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_scaleNum, debug).astype(float)
    cutFlow_scaleDen = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_scaleDen, debug).astype(float)
    
    # Subtract non-QCD MC from Data
    for iBg in range(0, len(cutFlowDirs_mc)) :
        
        if (debug) :
            
            print cutFlow_sig
            print cutFlow_shape
            print cutFlow_scaleNum
            print cutFlow_scaleDen
        
        cutFlow_sig -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_sig, debug, crossSections_mc[iBg], lumi_data, "MC")
        cutFlow_shape -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_shape, debug, crossSections_mc[iBg], lumi_data, "MC")
        cutFlow_scaleNum -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_scaleNum, debug, crossSections_mc[iBg], lumi_data, "MC")
        cutFlow_scaleDen -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_scaleDen, debug, crossSections_mc[iBg], lumi_data, "MC")
    
    cutFlow_sig[numpy.where(cutFlow_sig < 0)] = 0
    cutFlow_shape[numpy.where(cutFlow_shape < 0)] = 0
    cutFlow_scaleNum[numpy.where(cutFlow_scaleNum < 0)] = 0
    cutFlow_scaleDen[numpy.where(cutFlow_scaleDen < 0)] = 0
    
    # Subtract signal region
    cutFlow_shape -= cutFlow_sig
    cutFlow_shape[numpy.where(cutFlow_shape < 0)] = 0
    
    # Subtract signal region
    cutFlow_scaleDen -= cutFlow_scaleNum
    cutFlow_scaleDen[numpy.where(cutFlow_scaleDen < 0)] = 0
    
    with numpy.errstate(divide = "ignore", invalid = "ignore") :
        
        cutFlow_QCD = cutFlow_shape * cutFlow_scaleNum/cutFlow_scaleDen
        cutFlow_QCD[numpy.where(cutFlow_QCD < 0)] = 0
        
        cutFlow_QCD[numpy.where(numpy.isnan(cutFlow_QCD))[0]] = 0
        cutFlow_QCD[numpy.where(numpy.isinf(cutFlow_QCD))[0]] = 0
    
    return cutFlow_QCD


def getCombinedCutFlow(cutFlowDirs, cutFlowName, details, debug, \
    crossSections = [], lumi_data = 1, option = "") :
    
    if(details != "") :
        
        cutFlowName += "_" + details
    
    cutFlow_combined = numpy.empty(0)
    
    for iDir in range(0, len(cutFlowDirs)) :
        
        cutFlowDir = cutFlowDirs[iDir] + suffix + "/" + cutFlowName
        
        if(debug) :
            
            print "Directory:", cutFlowDir
        
        # Get cut-flow file names in directory
        cutFlowFiles = glob.glob(cutFlowDir + "/**")
        cutFlowFiles = [f for f in cutFlowFiles if ".txt" in f]
        
        # Get cut-flows in directory
        cutFlows = [numpy.loadtxt(f, ndmin = 1) for f in cutFlowFiles]
        
        cutFlow_len = cutFlows[0].shape[0]
        
        cutFlow_sum = numpy.zeros(cutFlow_len)
        
        # Add cut-flows in directory
        for iFile in range (0, len(cutFlows)) :
            
            cutFlow_sum += cutFlows[iFile]
        
        # Get nEvent
        nEvent = cutFlow_sum[0]
        
        if(("DYJets" in cutFlowDir) or ("WJets" in cutFlowDir)) :
            
            nEvent = 1
        
        if(debug) :
            
            print "nEvent =", int(nEvent)
        
        # Scale cut-flow
        if(option == "MC") :
            
            cutFlow_sum = cutFlow_sum / float(nEvent) * crossSections[iDir] * lumi_data
        
        # If empty, initialize combined cut-flow
        if(not cutFlow_combined.shape[0]) :
            
            cutFlow_combined = numpy.zeros(cutFlow_len)
        
        # Add to combined cut-flow
        cutFlow_combined += cutFlow_sum
        
        if(debug) :
            
            print cutFlow_sum
    
    # Return combined cut-flow
    return cutFlow_combined



def printCutFlow(debug, cutFlowDetail) :
    
    #cutFlow_data = getCombinedCutFlow(cutFlowDir_elMu_data, cutFlowName, cutFlowDetail, debug)
    cutFlow_data = getCombinedCutFlow(cutFlowDir_tauTau_data, cutFlowName, cutFlowDetail, debug)
    #cutFlow_data = getCombinedCutFlow(cutFlowDir_muTau_data, cutFlowName, cutFlowDetail, debug)
    
    if(debug) :
        
        print cutFlowDetail
        print cutFlow_data
        
        print "\n"
    
    
    cutFlow_stopPair = []
    
    for iSig in range(0, len(cutFlowDir_stopPair)) :
        
        cutFlow_stopPair.append(getCombinedCutFlow([cutFlowDir_stopPair[iSig]], cutFlowName, cutFlowDetail, debug, [crossSection_stopPair[iSig]], luminosity_data, "MC"))
        
        if(debug) :
            
            print cutFlow_stopPair
            print "\n"
    
    
    cutFlow_WJetsToLNu = getCombinedCutFlow(cutFlowDir_WJetsToLNu, cutFlowName, cutFlowDetail, debug, crossSection_WJetsToLNu, luminosity_data, "MC")
    
    if(debug) :
        
        print cutFlow_WJetsToLNu
        print "\n"
    
    
    cutFlow_DYJetsToLL = getCombinedCutFlow(cutFlowDir_DYJetsToLL, cutFlowName, cutFlowDetail, debug, crossSection_DYJetsToLL, luminosity_data, "MC")
    
    if(debug) :
        
        print cutFlow_DYJetsToLL
        print "\n"
    
    
    cutFlow_VH = getCombinedCutFlow(cutFlowDir_VH, cutFlowName, cutFlowDetail, debug, crossSection_VH, luminosity_data, "MC")
    
    if(debug) :
        
        print cutFlow_VH
        print "\n"
    
    
    cutFlow_VV = getCombinedCutFlow(cutFlowDir_VV, cutFlowName, cutFlowDetail, debug, crossSection_VV, luminosity_data, "MC")
    
    if(debug) :
        
        print cutFlow_VV
        print "\n"
    
    
    cutFlow_WG = getCombinedCutFlow(cutFlowDir_WG, cutFlowName, cutFlowDetail, debug, crossSection_WG, luminosity_data, "MC")
    
    if(debug) :
        
        print cutFlow_WG
        print "\n"
    
    
    cutFlow_ttbar = getCombinedCutFlow(cutFlowDir_ttbar, cutFlowName, cutFlowDetail, debug, crossSection_ttbar, luminosity_data, "MC")
    
    if(debug) :
        
        print cutFlow_ttbar
        print "\n"
    
    
    cutFlow_singleTop = getCombinedCutFlow(cutFlowDir_singleTop, cutFlowName, cutFlowDetail, debug, crossSection_singleTop, luminosity_data, "MC")
    
    if(debug) :
        
        print cutFlow_singleTop
        print "\n"
    
    
    cutFlow_QCD = getCombinedCutFlow_QCD(
        cutFlowName,
        "tightIso_OS", "looseIso_OS",
        "tightIso_SS", "looseIso_SS",
        cutFlowDir_tauTau_data, luminosity_data,
        [cutFlowDir_WJetsToLNu,
            cutFlowDir_DYJetsToLL,
            cutFlowDir_VH,
            cutFlowDir_VV,
            cutFlowDir_WG,
            cutFlowDir_ttbar,
            cutFlowDir_singleTop,
        ],
        
        [crossSection_WJetsToLNu,
            crossSection_DYJetsToLL,
            crossSection_VH,
            crossSection_VV,
            crossSection_WG,
            crossSection_ttbar,
            crossSection_singleTop,
        ],
        
        debug
    )
    
    #cutFlow_QCD = getCombinedCutFlow_QCD(
    #    cutFlowName,
    #    "tightTightIso_OS", "looseMediumIso_OS",
    #    "tightTightIso_SS", "looseMediumIso_SS",
    #    cutFlowDir_muTau_data, luminosity_data,
    #    [cutFlowDir_WJetsToLNu,
    #        cutFlowDir_DYJetsToLL,
    #        cutFlowDir_VH,
    #        cutFlowDir_VV,
    #        cutFlowDir_WG,
    #        cutFlowDir_ttbar,
    #        cutFlowDir_singleTop,
    #    ],
    #    
    #    [crossSection_WJetsToLNu,
    #        crossSection_DYJetsToLL,
    #        crossSection_VH,
    #        crossSection_VV,
    #        crossSection_WG,
    #        crossSection_ttbar,
    #        crossSection_singleTop,
    #    ],
    #    
    #    debug
    #)
    
    
    #with numpy.errstate(invalid = "ignore") :
    #    
    #    cutFlow_QCD[numpy.where(numpy.isnan(cutFlow_QCD))[0]] = 0
    #    cutFlow_QCD[numpy.where(numpy.isinf(cutFlow_QCD))[0]] = 0
    #
    #if(debug) :
    #    
    #    print cutFlow_QCD
    #    print "\n"
    
    
    row_label = []
    
    if("cutFlow_tau_n-" in cutFlowName) :
        
        #cutFlow_QCD[0: -1] = -1
        
        row_label = [
            "",
            "$ N_{ev} $",
            "$ n_{\\tau} \geq 2 $",
            "$ p_{T,\tau} > 40 \\ \\text{GeV},\ |\\eta_{\\tau}| < 2.1 $",
            "DM finding",
            "$ e $ fake check",
            "$ \\mu $ fake check",
            "Isolation",
            "OS"
        ]
    
    elif(cutFlowName == "cutFlow_cutFlow1") :
        
        #cutFlow_QCD[numpy.where(numpy.isnan(cutFlow_QCD))[0]] = 0
        #cutFlow_QCD[-2:] = 0
        
        row_label = [
            "",
            "$ N_{ev} $",
            "$ n_{\\tau} \geq 2 $",
            "$ \\slashed{E}_{T} > 80 \\ \\text{GeV} $",
            "$ m_{T2} > 80 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
            "$ \\slashed{E}_{T} > 100 \\ \\text{GeV} $",
            "$ \\slashed{E}_{T} > 120 \\ \\text{GeV} $",
            "$ m_{T2} > 100 \\ \\text{GeV} $",
        ]
    
    elif(cutFlowName == "cutFlow_SR1") :
        
        row_label = [
            "",
            "$ N_{ev} $",
            "Pair selection",
            #"$ m_{e\\mu} > 90 \\ \\text{GeV} $",
            "$ 50 \\leq \\slashed{E}_{T} < 200 \\ \\text{GeV} $",
            "$ 0 \\leq m_{T2} < 40 \\ \\text{GeV} $",
            #"$ D_{\\zeta} < -35 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
        ]
    
    elif(cutFlowName == "cutFlow_SR2") :
        
        row_label = [
            "",
            "$ N_{ev} $",
            "Pair selection",
            #"$ m_{e\\mu} > 90 \\ \\text{GeV} $",
            "$ \\slashed{E}_{T} \\geq 200 \\ \\text{GeV} $",
            "$ 0 \\leq m_{T2} < 40 \\ \\text{GeV} $",
            #"$ D_{\\zeta} < -35 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
        ]
    
    elif(cutFlowName == "cutFlow_SR3") :
        
        row_label = [
            "",
            "$ N_{ev} $",
            "Pair selection",
            #"$ m_{e\\mu} > 90 \\ \\text{GeV} $",
            "$ 50 \\leq \\slashed{E}_{T} < 200 \\ \\text{GeV} $",
            "$ 40 \\leq m_{T2} < 80 \\ \\text{GeV} $",
            #"$ D_{\\zeta} < -35 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
        ]
    
    elif(cutFlowName == "cutFlow_SR4") :
        
        row_label = [
            "",
            "$ N_{ev} $",
            "Pair selection",
            #"$ m_{e\\mu} > 90 \\ \\text{GeV} $",
            "$ \\slashed{E}_{T} \\geq 200 \\ \\text{GeV} $",
            "$ 40 \\leq m_{T2} < 80 \\ \\text{GeV} $",
            #"$ D_{\\zeta} < -35 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
        ]
    
    elif(cutFlowName == "cutFlow_SR5") :
        
        row_label = [
            "",
            "$ N_{ev} $",
            "Pair selection",
            #"$ m_{e\\mu} > 90 \\ \\text{GeV} $",
            "$ 50 \\leq \\slashed{E}_{T} < 200 \\ \\text{GeV} $",
            "$ m_{T2} \\geq 80 \\ \\text{GeV} $",
            #"$ D_{\\zeta} < -35 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
        ]
    
    elif(cutFlowName == "cutFlow_SR6") :
        
        row_label = [
            "",
            "$ N_{ev} $",
            "Pair selection",
            #"$ m_{e\\mu} > 90 \\ \\text{GeV} $",
            "$ \\slashed{E}_{T} \\geq 200 \\ \\text{GeV} $",
            "$ m_{T2} \\geq 80 \\ \\text{GeV} $",
            #"$ D_{\\zeta} < -35 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
        ]
    
    elif(cutFlowName == "cutFlow_ttbar_elMu_CR") :
        
        row_label = [
            "",
            "$ N_{ev} $",
            "$ OS \\ e \\mu $",
            "$ D_{\\zeta} < -35 \\ \\text{GeV} $",
            "$ \\slashed{E}_{T} > 80 \\ \\text{GeV} $",
            "$ m_{e \\mu} > 90 \\ \\text{GeV} $",
            "$ n_{b} \\geq 1 $",
            #"$ n_{b} \\geq 2 $",
        ]
    
    
    column_label = []
    
    column_label += label_tauTau_data
    #column_label += label_muTau_data
    
    column_label += label_DYJetsToLL
    column_label += label_WJetsToLNu
    #column_label += label_VH
    column_label += label_VV
    #column_label += label_WG
    column_label += label_QCD
    column_label += label_ttbar
    column_label += label_singleTop
    column_label += ["$ \\text{all} \\ MC $ "]
    column_label += ["$ TT / \\text{all} \\ MC $ "]
    column_label += ["$ Data / \\text{all} \\ MC $ "]
    
    for iSig in range(0, len(cutFlowDir_stopPair)) :
        
        column_label += [label_stopPair[iSig]]
        column_label += ["$ \\frac{S" + str(iSig+1) + "}{S" + str(iSig+1) + "+B} $ "]
    
    
    #column_label += label_elMu_data
    #column_label += label_DYJetsToLL
    #column_label += label_WJetsToLNu
    #column_label += label_VH
    #column_label += label_VV
    #column_label += label_WG
    #column_label += label_ttbar
    #column_label += label_singleTop
    #column_label += ["all $ MC $"]
    #column_label += ["$ TT / \\text{all} \\ MC $"]
    #column_label += [" $ Data / MC $ "]
    
    
    cutFlow_combined = []
    
    
    cutFlow_combined.append(cutFlow_data.tolist())
    
    
    cutFlow_combined.append(cutFlow_DYJetsToLL.tolist())
    cutFlow_combined.append(cutFlow_WJetsToLNu.tolist())
    #cutFlow_combined.append(cutFlow_VH.tolist())
    cutFlow_combined.append(cutFlow_VV.tolist())
    #cutFlow_combined.append(cutFlow_WG.tolist())
    cutFlow_combined.append(cutFlow_QCD.tolist())
    cutFlow_combined.append(cutFlow_ttbar.tolist())
    cutFlow_combined.append(cutFlow_singleTop.tolist())
    allMC = cutFlow_DYJetsToLL+cutFlow_WJetsToLNu+cutFlow_VH+cutFlow_VV+cutFlow_WG+cutFlow_QCD+cutFlow_ttbar+cutFlow_singleTop
    cutFlow_combined.append(allMC.tolist())
    cutFlow_combined.append((cutFlow_ttbar / allMC).tolist())
    cutFlow_combined.append((cutFlow_data / allMC).tolist())
    
    for iSig in range(0, len(cutFlowDir_stopPair)) :
        
        cutFlow_combined.append(cutFlow_stopPair[iSig].tolist())
        cutFlow_combined.append((cutFlow_stopPair[iSig] / (cutFlow_stopPair[iSig]+allMC)).tolist())
    
    
    
    #cutFlow_combined.append(cutFlow_DYJetsToLL.tolist())
    #cutFlow_combined.append(cutFlow_WJetsToLNu.tolist())
    #cutFlow_combined.append(cutFlow_VH.tolist())
    #cutFlow_combined.append(cutFlow_VV.tolist())
    #cutFlow_combined.append(cutFlow_WG.tolist())
    #cutFlow_combined.append(cutFlow_ttbar.tolist())
    #cutFlow_combined.append(cutFlow_singleTop.tolist())
    #allMC = cutFlow_DYJetsToLL+cutFlow_WJetsToLNu+cutFlow_VH+cutFlow_VV+cutFlow_WG+cutFlow_ttbar+cutFlow_singleTop
    #cutFlow_combined.append(allMC.tolist())
    #cutFlow_combined.append((cutFlow_ttbar / allMC).tolist())
    #cutFlow_combined.append((cutFlow_data / allMC).tolist())
    
    
    #print cutFlow_combined
    cutFlow_combined = numpy.transpose(cutFlow_combined).tolist()
    cutFlow_combined.insert(0, column_label)
    
    if(debug) :
        
        print cutFlow_combined
    
    #print len(cutFlow_combined)
    printLatexTable(cutFlow_combined, row_label)
    
    return [cutFlow_combined, row_label, column_label]


cutFlowNames = [
    "cutFlow_tau_n-0",
    "cutFlow_tau_n-1",
    "cutFlow_tau_n-2",
    "cutFlow_cutFlow1",
    "cutFlow_SR1",
    "cutFlow_SR2",
    "cutFlow_SR3",
    "cutFlow_SR4",
    "cutFlow_SR5",
    "cutFlow_SR6",
    "cutFlow_ttbar_elMu_CR",
]


#cutFlowIndex = -1
#cutFlowName = cutFlowNames[cutFlowIndex]
#printCutFlow(False, "")


cutFlow_finalYield = []
row_label = [""]
column_label = []

count_temp = 0

for iSR in range(4, 10) :
    
    count_temp += 1
    
    cutFlowIndex = iSR
    cutFlowName = cutFlowNames[cutFlowIndex]
    
    print "~\\\\"
    print "\\textbf{SR" + str(count_temp) + "}"
    print ""
    
    #temp = printCutFlow(False, "")
    temp = printCutFlow(False, "tightIso_OS")
    #temp = printCutFlow(False, "tightTightIso_OS")
    cutFlow_temp = temp[0]
    column_label = temp[2]
    cutFlow_finalYield.append(cutFlow_temp[-1][:])
    
    row_label.append("SR" + str(count_temp))

cutFlow_finalYield.insert(0, column_label)

#print cutFlow_finalYield

print "~\\\\"
print "\\textbf{Final Yield: all SR}"
print ""

printLatexTable(cutFlow_finalYield, row_label)

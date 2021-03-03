import argparse
import collections
import copy
#import hepdata_lib
import numpy
import os
import pprint
import sys
import tabulate

import ROOT
ROOT.gROOT.SetBatch(1)


import Array2LatexTable


# Argument parser
parser = argparse.ArgumentParser()

# List of directories
parser.add_argument(
    "--eras",
    help = "Eras",
    nargs = "*",
    type = str,
    choices = ["2016", "2017"],
    required = True,
)

parser.add_argument(
    "--xVal",
    help = "Value of x",
    #nargs = "*",
    type = str,
    choices = ["25", "5", "75"],
    required = True,
)

parser.add_argument(
    "--noPrelim",
    help = "Remove \"Preliminary\" from plots",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--noSigGenMET",
    help = "Do not use signal FastSim MET correction",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--noTTbarSF",
    help = "Do not use ttbar SF",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--noSig",
    help = "Do not evaluate signal",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--lumiScale",
    help = "Scale the luminosity by this factor",
    #nargs = "*",
    type = float,
    required = False,
    default = 1.0,
)

parser.add_argument(
    "--card",
    help = "Make combine cards",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--cardSuffix",
    help = "Card filename suffix",
    type = str,
    default = "",
)

parser.add_argument(
    "--pseudodataSB",
    help = "Generate pseudodata (obs=S+B)",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--pseudodataB",
    help = "Generate pseudodata (obs=B)",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--cardPerBin",
    help = "Make combine cards for each bin",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--syst",
    help = "Print total systematics",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--SRyield",
    help = "Draw SR yield histogram and print the table (without the significance)",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--SRyieldWithSignificance",
    help = "Draw SR yield histogram and print the table (with the significance)",
    default = False,
    action = "store_true",
)

parser.add_argument(
    "--debug",
    help = "Debug",
    default = False,
    action = "store_true",
)



#parser.add_argument(
#    "--HEPData",
#    help = "Create HEPData yaml files",
#    default = False,
#    action = "store_true",
#)

# Parse arguments
args = parser.parse_args()

if (args.pseudodataSB and args.pseudodataB) :
    
    print "Error: Only ONE of --pseudodataSB and --pseudodataB can be given at a time."
    exit(1)

print args.card
print args.syst
print args.eras

if (len(args.eras) > 1 and (not args.SRyield and not args.syst)) :
    
    print "Error: Eras can be combined for yield and systematics outputs only."
    exit(1)

#workingDir = "../../../analysis/CMSSW_8_0_20/src/stopPair/"

# Add the analysis directory to the system path
#sys.path.append(workingDir)

# import from the analysis directory
import Common
import Details

# Go to analysis directory
#os.chdir(workingDir)

#era = args.era
l_era = args.eras


d_lumi_data = copy.deepcopy(Details.luminosity_data)
d_lumi_data_TTCR = copy.deepcopy(Details.luminosity_data)

for era in d_lumi_data :
    
    d_lumi_data[era] *= args.lumiScale


fakeScale = args.lumiScale

#if (era == "2017") :
#    
#    lumi_data = 10.0e3
#    fakeScale = lumi_data / Details.luminosity_data[era]


# Number of search bins
#nSR = 6
#cutFlowNameBase = "SRA"

#nSR = 18
cutFlowNameBase = "SRB"

#nSR = 18
#cutFlowNameBase = "SRC"

#nSR = 18
#cutFlowNameBase = "SRD"

# Number of backgrounds
nBG = 4 # ttbar, DY, other SM, fake

# nBG + 1 (for signal)
nProcess = nBG+1

# Scale variations
l_scaleVarIndex = [
    #0,
    1, 2, 3, 4, 6, 8
]



# Card block dictionaries
d_block_data_template = {
    "bin": ["bin"],
    "observation": ["observation"],
}

d_block_mc_template = {
    "bin": ["bin"],
    "processName": ["process"],
    "processIndex": ["process"],
    "rate": ["rate"],
}

d_block_statErr_template = {
    #"stat": ["stat%s" %(era), "lnN"],
    #"flat_syst lnN",
}

d_block_err_template = {
    #"stat": ["stat%s" %(era), "lnN"],
    #"flat_syst lnN",
}


l_corrSyst = [
    
]

l_uncorrSyst = [
]


label_sig = "sig"
label_DYJetsToLL = "DY" #Details.label_DYJetsToLL[0]
label_ttbar = Details.label_ttbar[0]
label_otherSM = "otherSM"
label_fake = "fake"


# Systematics dictionaries
d_syst_sig = {
    "tauFastFullSimSF": {
        "latexTitle": r"$ \tauh $ \textsc{FastSim}/{\GEANTfour}",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_sig: {},
    },
}

l_syst_sig_toExclude = ["normalization"]


d_syst_commonMC = {
    "tauES": {
        "latexTitle": r"$ \tauh $ energy scale",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "pileupReweight": {
        "latexTitle": r"Pileup",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "tauIDisoSF": {
        "latexTitle": r"$ \tauh $ ID-iso",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    ##"triggerSF": {
    ##    "type": "lnN",
    ##    "added": False,
    ##},
    
    "bTaggingSF": {
        "latexTitle": r"\PQb tagging",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "JEC": {
        "latexTitle": r"JES",
        "type": "lnN",
        "added": False,
        "correlated": True,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "JER": {
        "latexTitle": r"JER",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "unclusteredEnergy": {
        "latexTitle": r"\ptmiss unclustered energy",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "scale": {
        "latexTitle": r"$ \mu_{\text{R}} $ and $ \mu_{\text{F}} $ scales",
        "type": "lnN",
        "added": False,
        "correlated": True,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "luminosity": {
        "latexTitle": r"Luminosity",
        "type": "lnN",
        "added": True,
        "correlated": False,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    },
    
    "normalization": {
        "latexTitle": r"Background normalization",
        "type": "lnN",
        "added": True,
        "correlated": True,
        label_sig: {},
        label_ttbar: {},
        label_DYJetsToLL: {},
        label_otherSM: {},
    }
}

d_syst_ttbar = {
    "ttbarSF": {
        "latexTitle": r"$ \ttbar $ SF",
        "type": "lnN",
        "added": True,
        "correlated": False,
        label_ttbar: {},
    }
}

l_syst_ttbar_toInclude = [
    "tauES",
    "tauIDisoSF",
]

d_syst_DY = {
    "ZpTreweight": {
        "latexTitle": r"\PZ $ \pt $ reweighting",
        "type": "lnN",
        "added": False,
        "correlated": False,
        label_DYJetsToLL: {},
    },
}

d_syst_fake = {
    "tauFakeRateRegion": {
        #"latexTitle": r"$ \tauh $ fake-rate (region)",
        "latexTitle": r"\vtop{\hbox{\strut $ \tauh $ misid. rate}\hbox{\strut ($ \text{LL} \to \text{TL} $ vs. $ \text{TL} \to \text{TT} $)}}",
        "type": "lnN",
        "added": False,
        "correlated": True,
        label_fake: {},
    },
    
    "tauFakeRateJetPartonFlav": {
        "latexTitle": r"$ \tauh $ misid. rate (parton flavour)",
        "type": "lnN",
        "added": False,
        "correlated": True,
        label_fake: {},
    },
}




# Number of independent uncertainties
# Plus 1 for stat
#nSystematics = len(d_syst_commonMC) + len(d_syst_ttbar) + len(d_syst_fake) + 1

flatSystVal = 0.15

#zeroReplacement = 1e-4
zeroReplacement = 0

#process_sig = "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"
#process_sig = "SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"
process_sig = "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"

d_process_sig = {
    "2016": {
        "25": "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
        "5":  "SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
        "75": "SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16",
    },
    
    "2017": {
        #"25": "SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
        #"5":  "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
        #"75": "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
        
        "25": "SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
        "5":  "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
        "75": "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17",
    }
}

#process_sig = d_process_sig[era][args.xVal]
#massPointFile = "stopPair_mc/output_genParam/" + process_sig + "/XSweightInfo.txt"
#massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")

d_massPointInfo = {}

for iEra in range(0, len(l_era)):
    
    era = l_era[iEra]
    
    massPointFile = "stopPair_mc/output_genParam/" + d_process_sig[era][args.xVal] + "/XSweightInfo.txt"
    d_massPointInfo[era] = numpy.loadtxt(massPointFile, delimiter = ",")


############################################################
#################### Select mass points ####################
############################################################

l_selectMassPoint = []
l_selectMassPoint = [
    #[700, 150],
    #[700, 1],
    #[900, 400],
    #[1000, 1], [600, 425], [300, 150],
    #[300, 100], [800, 300], [1000, 1],
    #[800, 300],
]


sig_x_str = ""
sig_x_str_fileName = ""

if (args.xVal == "25") :
    
    sig_x_str = "0.25"
    sig_x_str_fileName = "x0p25"

elif (args.xVal == "5") :
    
    sig_x_str = "0.5"
    sig_x_str_fileName = "x0p5"

elif (args.xVal == "75") :
    
    sig_x_str = "0.75"
    sig_x_str_fileName = "x0p75"

l_massPointYieldHist = []
#l_massPointYieldHist = [[300, 100], [500, 350], [800, 300]]

l_massPointYieldHist_yieldTableExtra = []#[[300, 100]]


#for ele in d_massPointInfo[l_era[0]] :
#    
#    massPoint = [ele[0], ele[1]]
#    
#    if (massPoint not in l_massPointYieldHist) :
#        
#        l_massPointYieldHist_yieldTableExtra.append(massPoint)


if (args.SRyield and len(l_massPointYieldHist)) :
    
    l_massPointYieldHist = l_massPointYieldHist_yieldTableExtra + l_massPointYieldHist

l_massPointYieldHist = sorted(l_massPointYieldHist, key = lambda x: (x[0], x[1]))

d_massPointYieldHist = {}

d_massPointSystTable = {}


for ele in l_massPointYieldHist :
    
    if (ele not in l_selectMassPoint) :
        
        l_selectMassPoint.append(ele)
    
    sigKey = (ele[0], ele[1])
    
    d_massPointYieldHist[sigKey] = {}


for iEra in range(0, len(l_era)) :
    
    era = l_era[iEra]
    #d_massPointSystTable[era] = {}
    
    for ele in l_massPointYieldHist :
        
        sigKey = (ele[0], ele[1])
        d_massPointSystTable[sigKey] = {}
    
    
    if len(l_selectMassPoint) :
        
        d_massPointInfo[era] = numpy.array([ele for ele in d_massPointInfo[era] if [int(ele[0]), int(ele[1])] in l_selectMassPoint])


#####
suffix_data = "_tauTau_analysis"
suffix_mc = "_tauTau_analysis"
suffix_fakeEstimation = "_tauTau_fakeEstimation"
suffix_ttbarCR_elMu = "_elMu_analysis"
suffix_ttbarCR_muMu = "_muMu_analysis"

#####
rootFileName_data = "custom_all_analyzed.root"
rootFileName_mc = "custom_all_analyzed.root"
rootFileName_fakeEstimation = "custom_all_fakeEstimation_tauTau.root"
rootFileName_ttbarCR = "custom_all_analyzed.root"

#####
detailStr_data = "tightTight_OS_baselineSRB"
detailStr_mc = "tightTight_OS_genMatched_baselineSRB"
detailStr_fakeEstimation = "OS_baselineSRB"
detailStr_ttbarCR = "OS_baselineTTCRB"


#if (era == "2017") :
#    
#    suffix_data = "_tauTau_analysis_partialUnblinding2017"
#

nSR = 18
finalYieldBin = 6

# ttbar, DY, other SM, fake
nBackground = 4

histName_base = "SRB"
histName_base_ttbarCR = "CRB"

ll_regionNumber_SR = [
    [1], [2], [3],
    [4, 5], [6],
    [7], [8], [9],
    [10, 11], [12],
    [13], [14], [15],
    [16, 17], [18],
]

#ll_regionNumber_SR = [[ele+1] for ele in range(0, nSR)]

nSR_merged = len(ll_regionNumber_SR)


ll_regionNumber_ttbarCR = [
    [1], [2], [3],
    #[4, 5, 6],
    [4, 5], [6],
    [7], [8], [9],
    #[10, 11, 12],
    [10, 11], [12],
    [13], [14], [15],
    [16, 17, 18],
]


inputFiles_sig = []


d_details_otherSM = {}
d_xs_otherSM = {}

for iEra in range(0, len(l_era)):
    
    era = l_era[iEra]
    
    details_otherSM = \
        Details.cutFlowDir_WJetsToLNu[era] + \
        Details.cutFlowDir_VH[era] + \
        Details.cutFlowDir_VV[era] + \
        Details.cutFlowDir_WG[era] + \
        Details.cutFlowDir_singleTop[era] + \
        Details.cutFlowDir_TTX[era]
    
    
    l_xs_otherSM = \
        Details.crossSection_WJetsToLNu[era] + \
        Details.crossSection_VH[era] + \
        Details.crossSection_VV[era] + \
        Details.crossSection_WG[era] + \
        Details.crossSection_singleTop[era] + \
        Details.crossSection_TTX[era]
    
    
    d_details_otherSM[era] = details_otherSM
    d_xs_otherSM[era] = l_xs_otherSM

#details_otherSM = Details.cutFlowDir_singleTop[era]
#
#l_xs_otherSM = Details.crossSection_singleTop[era]


#l_label_otherSM = [
#    Details.label_WJetsToLNu,
#    Details.label_VH,
#    Details.label_VV,
#    Details.label_WG,
#    Details.label_singleTop,
#]


d_inputFiles_data = {}

d_inputFiles_DYJetsToLL = {}
d_inputFiles_ttbar = {}
d_inputFiles_otherSM = {}
d_inputFiles_fake = {}


for iEra in range(0, len(l_era)):
    
    era = l_era[iEra]
    
    inputFiles_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data[era], suffix_data, rootFileName_data)
    
    inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix_mc, rootFileName_mc)
    inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix_mc, rootFileName_mc)
    inputFiles_otherSM = Common.getRootFiles(d_details_otherSM[era], suffix_mc, rootFileName_mc)
    inputFiles_fake = Common.getRootFiles(Details.cutFlowDir_tauTau_fakeEstimation[era], suffix_fakeEstimation, rootFileName_fakeEstimation)
    
    
    d_inputFiles_data[era] = inputFiles_data
    
    d_inputFiles_DYJetsToLL[era] = inputFiles_DYJetsToLL
    d_inputFiles_ttbar[era] = inputFiles_ttbar
    d_inputFiles_otherSM[era] = inputFiles_otherSM
    d_inputFiles_fake[era] = inputFiles_fake


prettyPrinter = pprint.PrettyPrinter(indent = 4)


#def getRootFiles_ttbarCR(era, suffix, rootFileName) :
#    
#    inputFiles_WJetsToLNu_ttbarCR = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
#    inputFiles_DYJetsToLL_ttbarCR = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)
#    inputFiles_VH_ttbarCR = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
#    inputFiles_VV_ttbarCR = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
#    inputFiles_WG_ttbarCR = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
#    inputFiles_ttbar_ttbarCR = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix, rootFileName)
#    inputFiles_singleTop_ttbarCR = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)
#    
#    inputFiles_ttbarCR = [
#        inputFiles_WJetsToLNu_ttbarCR,
#        inputFiles_DYJetsToLL_ttbarCR,
#        inputFiles_VH_ttbarCR,
#        inputFiles_VV_ttbarCR,
#        inputFiles_WG_ttbarCR,
#        inputFiles_ttbar_ttbarCR,
#        inputFiles_singleTop_ttbarCR,
#    ]
#    
#    labels_ttbarCR = [
#        Details.label_WJetsToLNu[0],
#        Details.label_DYJetsToLL[0],
#        Details.label_VH[0],
#        Details.label_VV[0],
#        Details.label_WG[0],
#        Details.label_ttbar[0],
#        Details.label_singleTop[0],
#    ]
#    
#    crossSections_ttbarCR = [
#        Details.crossSection_WJetsToLNu[era],
#        Details.crossSection_DYJetsToLL[era],
#        Details.crossSection_VH[era],
#        Details.crossSection_VV[era],
#        Details.crossSection_WG[era],
#        Details.crossSection_ttbar[era],
#        Details.crossSection_singleTop[era],
#    ]
#    
#    d_info_ttbarCR = {
#        "files": inputFiles_ttbarCR,
#        "labels": labels_ttbarCR,
#        "xs": crossSections_ttbarCR,
#    }
#    
#    return d_info_ttbarCR
#
#
#d_inputFiles_data_ttbarCR_elMu = {}
#d_inputFiles_data_ttbarCR_muMu = {}
#
#d_info_mc_ttbarCR_elMu = {}
#d_info_mc_ttbarCR_muMu = {}
#
#
#for iEra in range(0, len(l_era)):
#    
#    era = l_era[iEra]
#    
#    d_inputFiles_data_ttbarCR_elMu[era] = Common.getRootFiles(Details.cutFlowDir_elMu_data[era], suffix_ttbarCR_elMu, rootFileName_ttbarCR)
#    d_info_mc_ttbarCR_elMu[era] = getRootFiles_ttbarCR(era = era, suffix = suffix_ttbarCR_elMu, rootFileName = rootFileName_ttbarCR)
#    
#    d_inputFiles_data_ttbarCR_muMu[era] = Common.getRootFiles(Details.cutFlowDir_muMu_data[era], suffix_ttbarCR_muMu, rootFileName_ttbarCR)
#    d_info_mc_ttbarCR_muMu[era] = getRootFiles_ttbarCR(era = era, suffix = suffix_ttbarCR_muMu, rootFileName = rootFileName_ttbarCR)


##################################################
# Getting the info for data and background
##################################################


d_yieldResult_data = {}

d_yieldResult_nominal_ttbar = {}
d_yieldResult_nominal_DYJetsToLL = {}
d_yieldResult_nominal_otherSM = {}
d_yieldResult_nominal_fake = {}


d_systCombined = {
    label_ttbar: {
        "stat": [[] for ele in range(0, nSR_merged)],
        "syst": [[] for ele in range(0, nSR_merged)], #[systName, errUp, errDown]
    },
    
    label_DYJetsToLL: {
        "stat": [[] for ele in range(0, nSR_merged)],
        "syst": [[] for ele in range(0, nSR_merged)],
    },
    
    label_otherSM: {
        "stat": [[] for ele in range(0, nSR_merged)],
        "syst": [[] for ele in range(0, nSR_merged)],
    },
    
    label_fake: {
        "stat": [[] for ele in range(0, nSR_merged)],
        "syst": [[] for ele in range(0, nSR_merged)],
    },
}


#d_systCombined = {}
d_systCombined_sig = {}


for iEra in range(0, len(l_era)):
    
    era = l_era[iEra]
    eraStr = "_%s" %(era)
    
    
    # Data
    d_yieldResult_data[era] = Common.getYields(
        l_rootFile = d_inputFiles_data[era],
        l_xs = [],
        suffix = suffix_data,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr_data,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        #scale = lumi_data,
        negToZero = True,
        debug = args.debug,
    )
    
    
    # Nominal
    d_yieldResult_nominal_ttbar[era] = Common.getYields(
        l_rootFile = d_inputFiles_ttbar[era],
        l_xs = Details.crossSection_ttbar[era],
        suffix = suffix_mc,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr_mc,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        scale = d_lumi_data[era],
        negToZero = True,
        era = era,
        debug = args.debug,
    )
    
    d_yieldResult_nominal_DYJetsToLL[era] = Common.getYields(
        l_rootFile = d_inputFiles_DYJetsToLL[era],
        l_xs = Details.crossSection_DYJetsToLL[era],
        suffix = suffix_mc,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr_mc,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        scale = d_lumi_data[era],
        negToZero = True,
        era = era,
        debug = args.debug,
    )
    
    d_yieldResult_nominal_otherSM[era] = Common.getYields(
        l_rootFile = d_inputFiles_otherSM[era],
        l_xs = d_xs_otherSM[era],
        suffix = suffix_mc,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr_mc,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        scale = d_lumi_data[era],
        negToZero = True,
        era = era,
        debug = args.debug,
    )
    
    d_yieldResult_nominal_fake[era] = Common.getYields(
        l_rootFile = d_inputFiles_fake[era],
        l_xs = [],
        suffix = suffix_mc,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr_fakeEstimation,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        scale = fakeScale,
        negToZero = True,
        debug = args.debug,
    )
    
    
    ## ttbar SF
    #ttbarSFinfo_elMu = Common.getTTbarSF_multibin(
    #    cutFlowNameBase = histName_base_ttbarCR,
    #    inputFiles_data = d_inputFiles_data_ttbarCR_elMu[era],
    #    lumi_data = d_lumi_data_TTCR[era],
    #    label_data = "data",
    #    details_data = detailStr_ttbarCR,
    #    inputFiles_mc = d_info_mc_ttbarCR_elMu[era]["files"],
    #    crossSections_mc = d_info_mc_ttbarCR_elMu[era]["xs"],
    #    labels_mc = d_info_mc_ttbarCR_elMu[era]["labels"],
    #    details_mc = detailStr_ttbarCR,
    #    ll_regionNumber = ll_regionNumber_ttbarCR,
    #    debug = args.debug,
    #)
    #
    #ttbarSFinfo_muMu = Common.getTTbarSF_multibin(
    #    cutFlowNameBase = histName_base_ttbarCR,
    #    inputFiles_data = d_inputFiles_data_ttbarCR_muMu[era],
    #    lumi_data = d_lumi_data_TTCR[era],
    #    label_data = "data",
    #    details_data = detailStr_ttbarCR,
    #    inputFiles_mc = d_info_mc_ttbarCR_muMu[era]["files"],
    #    crossSections_mc = d_info_mc_ttbarCR_muMu[era]["xs"],
    #    labels_mc = d_info_mc_ttbarCR_muMu[era]["labels"],
    #    details_mc = detailStr_ttbarCR,
    #    ll_regionNumber = ll_regionNumber_ttbarCR,
    #    debug = args.debug,
    #)
    #
    #l_ttbarSF_elMu = ttbarSFinfo_elMu["SF"]
    #l_ttbarSF_muMu = ttbarSFinfo_muMu["SF"]
    #
    #l_ttbarSF_err_elMu = ttbarSFinfo_elMu["SFerr"]
    #l_ttbarSF_err_muMu = ttbarSFinfo_muMu["SFerr"]
    #
    #l_ttbarSF = [(l_ttbarSF_elMu[iEle] + l_ttbarSF_muMu[iEle]) / 2.0 for iEle in range(0, len(l_ttbarSF_elMu))]
    #
    ## Difference between elMu and muMu
    #l_ttbarSF_err = [abs(l_ttbarSF_elMu[iEle]-l_ttbarSF[iEle]) for iEle in range(0, len(l_ttbarSF_elMu))]
    #
    ## Add the stat error in quadrature
    #l_ttbarSF_err = [numpy.sqrt(l_ttbarSF_err[iEle]**2 + (l_ttbarSF_err_elMu[iEle]**2 + l_ttbarSF_err_muMu[iEle]**2)/4.0) for iEle in range(0, len(l_ttbarSF_elMu))]
    #
    ## To percentage
    #l_ttbarSF_err = [(l_ttbarSF_err[iEle] / l_ttbarSF[iEle] * 100.0) for iEle in range(0, len(l_ttbarSF))]
    #
    ## Apply ttbar SF
    #l_ttbarSF_temp = []
    #l_ttbarSF_err_temp = []
    #
    #for iRegionGroup in range (0, nSR_merged) :
    #    
    #    ttbarSF_temp = 0
    #    ttbarSF_err_temp = 0
    #    
    #    for iRegion in range(0, len(ll_regionNumber_SR[iRegionGroup])) :
    #        
    #        regionNumber = ll_regionNumber_SR[iRegionGroup][iRegion]
    #        
    #        ttbarSF_temp += l_ttbarSF[regionNumber-1]
    #        ttbarSF_err_temp += l_ttbarSF_err[regionNumber-1]
    #    
    #    ttbarSF_temp /= len(ll_regionNumber_SR[iRegionGroup])
    #    ttbarSF_err_temp /= len(ll_regionNumber_SR[iRegionGroup])
    #    
    #    l_ttbarSF_temp.append(ttbarSF_temp)
    #    l_ttbarSF_err_temp.append(ttbarSF_err_temp)
    #    
    #    d_yieldResult_nominal_ttbar[era]["yield"][iRegionGroup] *= ttbarSF_temp
    #    d_yieldResult_nominal_ttbar[era]["error"][iRegionGroup] *= ttbarSF_temp
    #
    #d_yieldResult_nominal_ttbar[era]["integral"] = sum(d_yieldResult_nominal_ttbar[era]["yield"])
    #
    #l_ttbarSF = l_ttbarSF_temp
    #l_ttbarSF_err = l_ttbarSF_err_temp
    #
    ## Weighted average
    #ttbarF_err_mean = numpy.average(l_ttbarSF_err, weights = d_yieldResult_nominal_ttbar[era]["yield"])
    
    
    for iSR in range(0, nSR_merged) :
        
        binLabel = cutFlowNameBase + str(int(iSR+1))
        #binLabels.append(binLabel)
        
        processIndex = -1
        
        
        # ttbar
        processIndex += 1
        statPos = d_yieldResult_nominal_ttbar[era]["error"][iSR]
        statNeg = -d_yieldResult_nominal_ttbar[era]["error"][iSR] * (d_yieldResult_nominal_ttbar[era]["yield"][iSR] > 0)
        d_systCombined[label_ttbar]["stat"][iSR].append(["stat"+era, statPos, statNeg])
        
        
        # DY
        processIndex += 1
        statPos = d_yieldResult_nominal_DYJetsToLL[era]["error"][iSR]
        statNeg = -d_yieldResult_nominal_DYJetsToLL[era]["error"][iSR] * (d_yieldResult_nominal_DYJetsToLL[era]["yield"][iSR] > 0)
        d_systCombined[label_DYJetsToLL]["stat"][iSR].append(["stat"+era, statPos, statNeg])
        
        
        # Other SM
        processIndex += 1
        statPos = d_yieldResult_nominal_otherSM[era]["error"][iSR]
        statNeg = -d_yieldResult_nominal_otherSM[era]["error"][iSR] * (d_yieldResult_nominal_otherSM[era]["yield"][iSR] > 0)
        d_systCombined[label_otherSM]["stat"][iSR].append(["stat"+era, statPos, statNeg])
        
        
        # Fake
        processIndex += 1
        statPos = d_yieldResult_nominal_fake[era]["error"][iSR]
        statNeg = -d_yieldResult_nominal_fake[era]["error"][iSR] * (d_yieldResult_nominal_fake[era]["yield"][iSR] > 0)
        d_systCombined[label_fake]["stat"][iSR].append(["stat"+era, statPos, statNeg])



def getYieldHist(yieldResult) :
    
    nBin = len(yieldResult["yield"])
    
    hist = ROOT.TH1F("hist", "hist", nBin, 0, nBin)
    
    for iBin in range(0, nBin) :
        
        binVal = yieldResult["yield"][iBin]
        binErr = yieldResult["error"][iBin]
        
        hist.SetBinContent(iBin+1, binVal)
        hist.SetBinError(iBin+1, binErr)
        hist.GetXaxis().SetBinLabel(iBin+1, str(iBin+1))
    
    return hist


if (args.SRyield) :
    
    yieldResult_data = Common.getEraCombinedYields([d_yieldResult_data[era] for era in l_era])
    
    yieldResult_nominal_ttbar = Common.getEraCombinedYields([d_yieldResult_nominal_ttbar[era] for era in l_era])
    yieldResult_nominal_DYJetsToLL = Common.getEraCombinedYields([d_yieldResult_nominal_DYJetsToLL[era] for era in l_era])
    yieldResult_nominal_otherSM = Common.getEraCombinedYields([d_yieldResult_nominal_otherSM[era] for era in l_era])
    yieldResult_nominal_fake = Common.getEraCombinedYields([d_yieldResult_nominal_fake[era] for era in l_era])
    
    ##### Yield table #####
    
    l_yieldTable = []
    l_header = []
    
    l_yieldTable_sig = []
    l_header_sig = []
    
    l_significance = []
    
    totalBkg_yield = 0
    totalBkg_statErr = 0
    totalBkg_statErrPos = 0
    totalBkg_statErrNeg = 0
    totalBkg_systErrPos = 0
    totalBkg_systErrNeg = 0
    
    totalData_yield = 0
    totalData_statErr = 0
    
    l_sig_yield = [0 for i in range(0, len(l_massPointYieldHist))]
    l_sig_statErr = [0 for i in range(0, len(l_massPointYieldHist))]
    l_sig_statErrPos = [0 for i in range(0, len(l_massPointYieldHist))]
    l_sig_statErrNeg = [0 for i in range(0, len(l_massPointYieldHist))]
    l_sig_systErrPos = [0 for i in range(0, len(l_massPointYieldHist))]
    l_sig_systErrNeg = [0 for i in range(0, len(l_massPointYieldHist))]
    
    # ttbar, DY, other SM, fake
    l_bkg_yield = [0 for i in range(0, nBackground)]
    l_bkg_statErr = [0 for i in range(0, nBackground)]
    l_bkg_statErrPos = [0 for i in range(0, nBackground)]
    l_bkg_statErrNeg = [0 for i in range(0, nBackground)]
    l_bkg_systErrPos = [0 for i in range(0, nBackground)]
    l_bkg_systErrNeg = [0 for i in range(0, nBackground)]
    
    l_totalBkg_yield = [0 for i in range(0, nSR_merged)]
    l_totalBkg_statErr = [0 for i in range(0, nSR_merged)]
    l_totalBkg_statErrPos = [0 for i in range(0, nSR_merged)]
    l_totalBkg_statErrNeg = [0 for i in range(0, nSR_merged)]
    l_totalBkg_systErrPos = [0 for i in range(0, nSR_merged)]
    l_totalBkg_systErrNeg = [0 for i in range(0, nSR_merged)]
    
    l_bkg_label = []
    
    
    for iSR in range(0, nSR_merged) :
        
        #l_err_temp = []
        #
        #for iEra in range(0, len(l_era)) :
        #    
        #    era = l_era[iEra]
        #    eraStr = "_%s" %(era)
        #    
        #    l_err_temp.append(
        #        d_systCombined[label_ttbar][era]["stat"][iSR]
        #    )
        #
        #d_systCombined[label_ttbar]["stat"][iSR] = Common.getCombinedError(l_err_temp)#, sign = +1)
        
        #Common.getEraCombinedError(l_systInfo = d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = xxx)
        
        
        l_row = []
        l_header = []
        
        l_row_sig = []
        l_header_sig = []
        
        l_header.append("SR")
        l_row.append("%d" %(iSR+1))
        
        l_header_sig.append("SR bin")
        l_row_sig.append("%d" %(iSR+1))
        
        
        # Prediction
        allSM = 0
        allSM_statPos = 0
        allSM_statNeg = 0
        
        #allSM = (
        #    yieldResult_nominal_ttbar["yield"][iSR] +
        #    yieldResult_nominal_DYJetsToLL["yield"][iSR] +
        #    yieldResult_nominal_otherSM["yield"][iSR] +
        #    yieldResult_nominal_fake["yield"][iSR]
        #)
        
        
        # ttbar
        if (iSR == 0) :
            
            l_bkg_label.append(label_ttbar)
        
        statSign = "+" if (yieldResult_nominal_ttbar["yield"][iSR] == 0) else "\pm"
        
        l_header.append(r"$ \ttbar $")
        
        yieldStr = ""
        
        l_eraYield_ttbar = [d_yieldResult_nominal_ttbar[era]["yield"][iSR] for era in l_era]
        
        statPos_ttbar = 0
        
        if (yieldResult_nominal_ttbar["yield"][iSR] == 0) :
            
            statPos_ttbar = Common.getEraCombinedError(d_systCombined[label_ttbar]["stat"][iSR], sign = +1, l_yield = l_eraYield_ttbar)
            
            yieldStr = r"$ 0.0 ^{+%0.1f +0.0} _{-0.0 -0.0} $" %(
                statPos_ttbar
            )
        
        else :
            
            statPos_ttbar = Common.getEraCombinedError(d_systCombined[label_ttbar]["stat"][iSR], sign = +1)
            
            minPreci = Common.getMinPrecision(["%0.2g" %(float("%0.1f" %(yieldResult_nominal_ttbar["yield"][iSR])))], zeroRemovalThresh = 2)
            
            yieldStr = r"$ %0.*f ^{+%0.*f +%0.*f} _{-%0.*f -%0.*f} $" %(
                minPreci, yieldResult_nominal_ttbar["yield"][iSR],
                #statSign,
                minPreci, statPos_ttbar,
                minPreci, Common.getEraCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = +1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_ttbar]["stat"][iSR], sign = -1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = -1),
                #round(yieldResult_nominal_ttbar["yield"][iSR] / allSM * 100.0)
            )
        
        l_row.append(yieldStr)
        
        statNeg_ttbar = Common.getEraCombinedError(d_systCombined[label_ttbar]["stat"][iSR], sign = -1)
        systPos_ttbar = Common.getEraCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = +1)
        systNeg_ttbar = Common.getEraCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = -1)
        
        l_bkg_yield[0] += float("%0.*f" %(minPreci, yieldResult_nominal_ttbar["yield"][iSR]))
        l_bkg_statErr[0] += Common.getEraCombinedError(d_systCombined[label_ttbar]["stat"][iSR], sign = +1)**2
        l_bkg_statErrPos[0] += statPos_ttbar**2
        l_bkg_statErrNeg[0] += statNeg_ttbar**2
        l_bkg_systErrPos[0] += systPos_ttbar**2
        l_bkg_systErrNeg[0] += systNeg_ttbar**2
        
        allSM += float("%0.*f" %(minPreci, yieldResult_nominal_ttbar["yield"][iSR]))
        
        allSM_statPos += statPos_ttbar**2
        
        
        # DY
        if (iSR == 0) :
            
            l_bkg_label.append(label_DYJetsToLL)
        
        statSign = "+" if (yieldResult_nominal_DYJetsToLL["yield"][iSR] == 0) else "\pm"
        
        l_header.append(r"DY+jets")
        
        yieldStr = ""
        
        l_eraYield_DYJetsToLL = [d_yieldResult_nominal_DYJetsToLL[era]["yield"][iSR] for era in l_era]
        
        statPos_DYJetsToLL = 0
        
        if (yieldResult_nominal_DYJetsToLL["yield"][iSR] == 0) :
            
            statPos_DYJetsToLL = Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["stat"][iSR], sign = +1, l_yield = l_eraYield_DYJetsToLL)
            
            yieldStr = r"$ 0.0 ^{+%0.1f +0.0} _{-0.0 -0.0} $" %(
                statPos_DYJetsToLL
            )
        
        else :
            
            statPos_DYJetsToLL = Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["stat"][iSR], sign = +1)
            
            minPreci = Common.getMinPrecision(["%0.2g" %(float("%0.1f" %(yieldResult_nominal_DYJetsToLL["yield"][iSR])))], zeroRemovalThresh = 2)
            
            yieldStr = r"$ %0.*f ^{+%0.*f +%0.*f} _{-%0.*f -%0.*f} $" %(
                minPreci, yieldResult_nominal_DYJetsToLL["yield"][iSR],
                #statSign,
                minPreci, statPos_DYJetsToLL,
                minPreci, Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = +1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["stat"][iSR], sign = -1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = -1),
                #round(yieldResult_nominal_DYJetsToLL["yield"][iSR] / allSM * 100.0)
            )
        
        l_row.append(yieldStr)
        
        statNeg_DYJetsToLL = Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["stat"][iSR], sign = -1)
        systPos_DYJetsToLL = Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = +1)
        systNeg_DYJetsToLL = Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = -1)
        
        l_bkg_yield[1] += float("%0.*f" %(minPreci, yieldResult_nominal_DYJetsToLL["yield"][iSR]))
        l_bkg_statErr[1] += Common.getEraCombinedError(d_systCombined[label_DYJetsToLL]["stat"][iSR])**2
        l_bkg_statErrPos[1] += statPos_DYJetsToLL**2
        l_bkg_statErrNeg[1] += statNeg_DYJetsToLL**2
        l_bkg_systErrPos[1] += systPos_DYJetsToLL**2
        l_bkg_systErrNeg[1] += systNeg_DYJetsToLL**2
        
        allSM += float("%0.*f" %(minPreci, yieldResult_nominal_DYJetsToLL["yield"][iSR]))
        
        allSM_statPos += statPos_DYJetsToLL**2
        
        # Other SM
        if (iSR == 0) :
            
            l_bkg_label.append(label_otherSM)
        
        statSign = "+" if (yieldResult_nominal_otherSM["yield"][iSR] == 0) else "\pm"
        
        l_header.append(r"Other SM")
        
        yieldStr = ""
        
        l_eraYield_otherSM = [d_yieldResult_nominal_otherSM[era]["yield"][iSR] for era in l_era]
        
        statPos_otherSM = 0
        
        if (yieldResult_nominal_otherSM["yield"][iSR] == 0) :
            
            statPos_otherSM = Common.getEraCombinedError(d_systCombined[label_otherSM]["stat"][iSR], sign = +1, l_yield = l_eraYield_otherSM)
            
            yieldStr = r"$ 0.0 ^{+%0.1f +0.0} _{-0.0 -0.0} $" %(
                statPos_otherSM
            )
        
        else :
            
            statPos_otherSM = Common.getEraCombinedError(d_systCombined[label_otherSM]["stat"][iSR], sign = +1)
            
            minPreci = Common.getMinPrecision(["%0.2g" %(float("%0.1f" %(yieldResult_nominal_otherSM["yield"][iSR])))], zeroRemovalThresh = 2)
            
            yieldStr = r"$ %0.*f ^{+%0.*f +%0.*f} _{-%0.*f -%0.*f} $" %(
                minPreci, yieldResult_nominal_otherSM["yield"][iSR],
                #statSign,
                minPreci, statPos_otherSM,
                minPreci, Common.getEraCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = +1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_otherSM]["stat"][iSR], sign = -1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = -1),
                #round(yieldResult_nominal_otherSM["yield"][iSR] / allSM * 100.0)
            )
        
        l_row.append(yieldStr)
        
        statNeg_otherSM = Common.getEraCombinedError(d_systCombined[label_otherSM]["stat"][iSR], sign = -1)
        systPos_otherSM = Common.getEraCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = +1)
        systNeg_otherSM = Common.getEraCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = -1)
        
        l_bkg_yield[2] += float("%0.*f" %(minPreci, yieldResult_nominal_otherSM["yield"][iSR]))
        l_bkg_statErr[2] += Common.getEraCombinedError(d_systCombined[label_otherSM]["stat"][iSR])**2
        l_bkg_statErrPos[2] += statPos_otherSM**2
        l_bkg_statErrNeg[2] += statNeg_otherSM**2
        l_bkg_systErrPos[2] += systPos_otherSM**2
        l_bkg_systErrNeg[2] += systNeg_otherSM**2
        
        allSM += float("%0.*f" %(minPreci, yieldResult_nominal_otherSM["yield"][iSR]))
        
        allSM_statPos += statPos_otherSM**2
        
        
        # Fake
        if (iSR == 0) :
            
            l_bkg_label.append(label_fake)
        
        l_header.append(r"Misid. \tauh")
        
        yieldStr = ""
        
        l_eraYield_fake = [d_yieldResult_nominal_fake[era]["yield"][iSR] for era in l_era]
        
        statPos_fake = 0
        
        if (yieldResult_nominal_fake["yield"][iSR] == 0) :
            
            statPos_fake = Common.getEraCombinedError(d_systCombined[label_fake]["stat"][iSR], sign = +1, l_yield = l_eraYield_fake)
            
            yieldStr = r"$ 0.0 ^{+%0.1f +0.0} _{-0.0 -0.0} $" %(
                statPos_fake
            )
        
        else :
            
            statPos_fake = Common.getEraCombinedError(d_systCombined[label_fake]["stat"][iSR], sign = +1)
            
            minPreci = Common.getMinPrecision(["%0.2g" %(float("%0.1f" %(yieldResult_nominal_fake["yield"][iSR])))], zeroRemovalThresh = 2)
            
            yieldStr = r"$ %0.*f ^{+%0.*f +%0.*f} _{-%0.*f -%0.*f} $" %(
                minPreci, yieldResult_nominal_fake["yield"][iSR],
                minPreci, statPos_fake,
                minPreci, Common.getEraCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = +1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_fake]["stat"][iSR], sign = -1),
                minPreci, Common.getEraCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = -1),
            )
        
        l_row.append(yieldStr)
        
        statNeg_fake = Common.getEraCombinedError(d_systCombined[label_fake]["stat"][iSR], sign = -1)
        systPos_fake = Common.getEraCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = +1)
        systNeg_fake = Common.getEraCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = -1)
        
        l_bkg_yield[3] += float("%0.*f" %(minPreci, yieldResult_nominal_fake["yield"][iSR]))
        l_bkg_statErr[3] += Common.getEraCombinedError(d_systCombined[label_fake]["stat"][iSR])**2
        l_bkg_statErrPos[3] += statPos_fake**2
        l_bkg_statErrNeg[3] += statNeg_fake**2
        l_bkg_systErrPos[3] += systPos_fake**2
        l_bkg_systErrNeg[3] += systNeg_fake**2
        
        allSM += float("%0.*f" %(minPreci, yieldResult_nominal_fake["yield"][iSR]))
        
        allSM_statPos += statPos_fake**2
        
        
        #####
        allSM_stat = Common.getEraCombinedError(
            d_systCombined[label_ttbar]["stat"][iSR] +
            d_systCombined[label_DYJetsToLL]["stat"][iSR] +
            d_systCombined[label_otherSM]["stat"][iSR] +
            d_systCombined[label_fake]["stat"][iSR],
            treatCorrelated = False
        )
        
        
        l_eraYield_allSM = l_eraYield_ttbar + l_eraYield_DYJetsToLL + l_eraYield_otherSM + l_eraYield_fake
        
        allSM_statPos = numpy.sqrt(allSM_statPos)
        
        
        # Do not add the one sided stat errors for the zero bins to the negative error
        allSM_statNeg = Common.getEraCombinedError(
            d_systCombined[label_ttbar]["stat"][iSR] +
            d_systCombined[label_DYJetsToLL]["stat"][iSR] +
            d_systCombined[label_otherSM]["stat"][iSR] +
            d_systCombined[label_fake]["stat"][iSR],
            sign = -1,
            treatCorrelated = False,
        )
        
        allSM_systPos = Common.getEraCombinedError(
            d_systCombined[label_ttbar]["syst"][iSR] +
            d_systCombined[label_DYJetsToLL]["syst"][iSR] +
            d_systCombined[label_otherSM]["syst"][iSR] +
            d_systCombined[label_fake]["syst"][iSR],
            sign = +1,
            #treatCorrelated = False
        )
        
        allSM_systNeg = Common.getEraCombinedError(
            d_systCombined[label_ttbar]["syst"][iSR] +
            d_systCombined[label_DYJetsToLL]["syst"][iSR] +
            d_systCombined[label_otherSM]["syst"][iSR] +
            d_systCombined[label_fake]["syst"][iSR],
            sign = -1,
            #treatCorrelated = False
        )
        
        
        # Total background
        l_header.append(r"Total bkg.")
        
        #if (allSM_statPos == allSM_statNeg) :
        #    
        #    l_row.append(r"$ %0.1f \pm %0.1f ^{+%0.1f} _{-%0.1f} $" %(
        #        allSM,
        #        allSM_statPos,
        #        allSM_systPos,
        #        allSM_systNeg
        #    ))
        #
        #else :
        
        minPreci = Common.getMinPrecision(["%0.2g" %(float("%0.1f" %(allSM)))], zeroRemovalThresh = 2)
        
        l_row.append(r"$ %0.*f ^{+%0.*f +%0.*f} _{-%0.*f -%0.*f} $" %(
            minPreci, allSM,
            #allSM_stat,
            minPreci, allSM_statPos,
            minPreci, allSM_systPos,
            minPreci, allSM_statNeg,
            minPreci, allSM_systNeg
        ))
        
        
        totalBkg_yield += allSM
        totalBkg_statErr += allSM_stat**2
        totalBkg_statErrPos += allSM_statPos**2
        totalBkg_statErrNeg += allSM_statNeg**2
        totalBkg_systErrPos += allSM_systPos**2
        totalBkg_systErrNeg += allSM_systNeg**2
        
        
        # Data
        l_header.append(r"Data")
        l_row.append("$ %d $" %(
            yieldResult_data["yield"][iSR],
        ))
        
        totalData_yield += yieldResult_data["yield"][iSR]
        totalData_statErr += yieldResult_data["yield"][iSR]
        
        
        # Significance
        if (args.SRyieldWithSignificance) :
            
            significance = (yieldResult_data["yield"][iSR] - allSM) / numpy.sqrt( \
                allSM_stat**2 + \
                ((abs(allSM_systPos)+abs(allSM_systNeg))/2.0)**2 + \
                yieldResult_data["yield"][iSR]
            )
            
            l_header.append(r"Significance")
            l_row.append("$ %0.1f $" %(
                significance,
            ))
        
        l_yieldTable.append(l_row)
        
        
        l_totalBkg_yield[iSR] = allSM
        l_totalBkg_statErr[iSR] = allSM_stat
        l_totalBkg_statErrPos[iSR] = allSM_statPos
        l_totalBkg_statErrNeg[iSR] = allSM_statNeg
        l_totalBkg_systErrPos[iSR] = allSM_systPos
        l_totalBkg_systErrNeg[iSR] = allSM_systNeg
        
        
        # Signal
        for iSig in range(0, len(l_massPointYieldHist)) :
            
            key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
            
            yieldResult = Common.getEraCombinedYields([d_massPointYieldHist[key][era] for era in l_era])
            #yieldResult = d_massPointYieldHist[key]
            
            statSign = "+" if (yieldResult["yield"][iSR] == 0) else "\pm"
            
            l_header_sig.append(r"$ x = %s, [%d, %d] $" %(sig_x_str, key[0], key[1]))
            
            yieldStr = ""
            
            SbySB = 0
            SbySB_str = ""
            
            if (allSM) :
                
                #SbySB = yieldResult["yield"][iSR] / (yieldResult["yield"][iSR] + allSM)
                
                #SbySB = yieldResult["yield"][iSR] / (
                #    (
                #        (l_totalBkg_statErrPos[iSR]**2 + l_totalBkg_systErrPos[iSR]**2)**0.5 +
                #        (l_totalBkg_statErrNeg[iSR]**2 + l_totalBkg_systErrNeg[iSR]**2)**0.5
                #    ) / 2.0
                #)
                
                # Ref: https://www.pp.rhul.ac.uk/~cowan/stat/medsig/medsigNote.pdf
                SbySB = (2 * (
                    (yieldResult["yield"][iSR]+allSM) *
                    numpy.log(1 + yieldResult["yield"][iSR]/allSM) -
                    yieldResult["yield"][iSR])
                )**0.5
            
            
            #if (SbySB > 0.5) :
            if (SbySB > 1) :
                
                SbySB_str = r"\boldmath{$ (%0.1f) $}" %(SbySB)
            
            else :
                
                SbySB_str = r"$ (%0.1f) $" %(SbySB)
            
            
            l_eraYield_sig = [d_massPointYieldHist[key][era]["yield"][iSR] for era in l_era]
            
            statPos_sig = 0
            
            if (yieldResult["yield"][iSR] == 0) :
                
                statPos_sig = Common.getEraCombinedError(d_systCombined_sig[key]["stat"][iSR], sign = +1, l_yield = l_eraYield_sig)
                
                #yieldStr = r"\begin{tabular}[t]{c} $ < %0.1f $ \\ %s \end{tabular}" %(
                #yieldStr = r"$ < %0.1f $" %(
                yieldStr = r"$ 0.0 ^{+%0.1f +0.0} _{-0.0 -0.0} $" %(
                    statPos_sig
                )
            
            else :
                
                statPos_sig = Common.getEraCombinedError(d_systCombined_sig[key]["stat"][iSR], sign = +1)
                
                yieldStr = r"$ %0.1f ^{+%0.1f +%0.1f} _{-%0.1f -%0.1f} $" %(
                    yieldResult["yield"][iSR],
                    statPos_sig,
                    Common.getEraCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = +1),
                    Common.getEraCombinedError(d_systCombined_sig[key]["stat"][iSR], sign = -1),
                    Common.getEraCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = -1),
                )
                
                #yieldStr = r"\begin{tabular}[t]{c} $ %0.1f ^{+%0.1f +%0.1f} _{-%0.1f -%0.1f} $ \\ %s \end{tabular}" %(
                #    yieldResult["yield"][iSR],
                #    statPos_sig,
                #    Common.getEraCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = +1),
                #    Common.getEraCombinedError(d_systCombined_sig[key]["stat"][iSR], sign = -1),
                #    Common.getEraCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = -1),
                #    SbySB_str
                #)
            
            l_row_sig.append(yieldStr)
            
            l_sig_yield[iSig] += yieldResult["yield"][iSR]
            l_sig_statErr[iSig] += Common.getEraCombinedError(d_systCombined_sig[key]["stat"][iSR])**2
            l_sig_statErrPos[iSig] += statPos_sig**2
            l_sig_statErrNeg[iSig] += Common.getEraCombinedError(d_systCombined_sig[key]["stat"][iSR], sign = -1)**2
            l_sig_systErrPos[iSig] += Common.getEraCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = +1)**2
            l_sig_systErrNeg[iSig] += Common.getEraCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = -1)**2
        
        l_yieldTable_sig.append(l_row_sig)
    
    # Add the totals
    totalBkg_statErr = numpy.sqrt(totalBkg_statErr)
    totalBkg_statErrPos = numpy.sqrt(totalBkg_statErrPos)
    totalBkg_statErrNeg = numpy.sqrt(totalBkg_statErrNeg)
    totalBkg_systErrPos = numpy.sqrt(totalBkg_systErrPos)
    totalBkg_systErrNeg = numpy.sqrt(totalBkg_systErrNeg)
    
    totalData_statErr = numpy.sqrt(totalData_statErr)
    
    l_sig_statErr = [numpy.sqrt(ele) for ele in l_sig_statErr]
    l_sig_statErrPos = [numpy.sqrt(ele) for ele in l_sig_statErrPos]
    l_sig_statErrNeg = [numpy.sqrt(ele) for ele in l_sig_statErrNeg]
    l_sig_systErrPos = [numpy.sqrt(ele) for ele in l_sig_systErrPos]
    l_sig_systErrNeg = [numpy.sqrt(ele) for ele in l_sig_systErrNeg]
    
    l_bkg_statErr = [numpy.sqrt(ele) for ele in l_bkg_statErr]
    l_bkg_statErrPos = [numpy.sqrt(ele) for ele in l_bkg_statErrPos]
    l_bkg_statErrNeg = [numpy.sqrt(ele) for ele in l_bkg_statErrNeg]
    l_bkg_systErrPos = [numpy.sqrt(ele) for ele in l_bkg_systErrPos]
    l_bkg_systErrNeg = [numpy.sqrt(ele) for ele in l_bkg_systErrNeg]
    
    l_row = [r"Total"]
    l_row_sig = [r"Total"]
    
    for iSig in range(0, len(l_massPointYieldHist)) :
        
        key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
        
        l_temp = []
        
        for iSR in range(0, nSR_merged) :
            
            l_temp.extend(d_systCombined_sig[key]["syst"][iSR])
        
        systErrPos = Common.getEraCombinedError(l_temp, sign = +1)
        systErrNeg = Common.getEraCombinedError(l_temp, sign = -1)
        
        #if (l_sig_statErrPos[iSig] == l_sig_statErrNeg[iSig]) :
        #    
        #    l_row_sig.append(r"\boldmath{$ %0.1f \pm %0.1f ^{+%0.1f} _{-%0.1f} $}" %(
        #        l_sig_yield[iSig],
        #        l_sig_statErrPos[iSig],
        #        l_sig_systErrPos[iSig],
        #        l_sig_systErrNeg[iSig]
        #    ))
        #
        #else :
        
        l_row_sig.append(r"$ %0.1f ^{+%0.1f +%0.1f} _{-%0.1f -%0.1f} $" %(
            l_sig_yield[iSig],
            l_sig_statErrPos[iSig],
            #l_sig_systErrPos[iSig],
            systErrPos,
            l_sig_statErrNeg[iSig],
            #l_sig_systErrNeg[iSig],
            systErrNeg,
        ))
    
    l_yieldTable_sig.append(l_row_sig)
    
    
    totalBkg_systErrPos = 0
    totalBkg_systErrNeg = 0
    
    l_bkg_systErrPos_comb = []
    
    for iBkg in range(0, len(l_bkg_yield)) :
        
        bkg_label = l_bkg_label[iBkg]
        
        l_temp = []
        
        for iSR in range(0, nSR_merged) :
            
            l_temp.extend(d_systCombined[bkg_label]["syst"][iSR])
        
        systErrPos = Common.getEraCombinedError(l_temp, sign = +1)
        systErrNeg = Common.getEraCombinedError(l_temp, sign = -1)
        
        totalBkg_systErrPos += systErrPos**2
        totalBkg_systErrNeg += systErrNeg**2
        
        #if (l_bkg_statErrPos[iBkg] == l_bkg_statErrNeg[iBkg]) :
        #    
        #    l_row.append(r"\boldmath{$ %0.1f \pm %0.1f ^{+%0.1f} _{-%0.1f} $}" %(
        #        l_bkg_yield[iBkg],
        #        l_bkg_statErrPos[iBkg],
        #        l_bkg_systErrPos[iBkg],
        #        l_bkg_systErrNeg[iBkg]
        #    ))
        #
        #else :
        
        #l_row.append(r"\boldmath{$ %0.1f ^{+%0.1f +%0.1f} _{-%0.1f -%0.1f} $}" %(
        l_row.append(r"$ %0.0f ^{+%0.0f +%0.0f} _{-%0.0f -%0.0f} $" %(
            l_bkg_yield[iBkg],
            l_bkg_statErrPos[iBkg],
            #l_bkg_systErrPos[iBkg],
            systErrPos,
            l_bkg_statErrNeg[iBkg],
            #l_bkg_systErrNeg[iBkg],
            systErrNeg,
        ))
        
        
    
    totalBkg_systErrPos = numpy.sqrt(totalBkg_systErrPos)
    totalBkg_systErrNeg = numpy.sqrt(totalBkg_systErrNeg)
    
    #if (totalBkg_statErrPos == totalBkg_statErrNeg) :
    #    
    #    l_row.append(r"\boldmath{$ %0.1f \pm %0.1f ^{+%0.1f} _{-%0.1f} $}" %(
    #        totalBkg_yield,
    #        totalBkg_statErrPos,
    #        totalBkg_systErrPos,
    #        totalBkg_systErrNeg
    #    ))
    #
    #else :
    
    #l_row.append(r"\boldmath{$ %0.1f ^{+%0.1f +%0.1f} _{-%0.1f -%0.1f} $}" %(
    l_row.append(r"$ %0.0f ^{+%0.0f +%0.0f} _{-%0.0f -%0.0f} $" %(
        totalBkg_yield,
        #totalBkg_statErr,
        totalBkg_statErrPos,
        totalBkg_systErrPos,
        totalBkg_statErrNeg,
        totalBkg_systErrNeg
    ))
    
    l_row.append(r"$ %d $" %(
        totalData_yield
    ))
    
    if (args.SRyieldWithSignificance) :
        
        significance = (totalData_yield - totalBkg_yield) / numpy.sqrt( \
            totalBkg_statErr**2 + \
            ((abs(totalBkg_systErrPos)+abs(totalBkg_systErrNeg))/2.0)**2 + \
            totalData_yield
        )
        
        l_row.append(r"$ %0.1f $" %(
            significance,
        ))
    
    l_yieldTable.append(l_row)
    
    
    #####
    l_yieldTable_temp = copy.deepcopy(l_yieldTable)
    
    for iRow in range(len(l_yieldTable_temp)) :
        
        for iCol in range(0, len(l_yieldTable_temp[iRow])) :
            
            l_yieldTable_temp[iRow][iCol] = l_yieldTable_temp[iRow][iCol].replace(r"\boldmath", "")
            l_yieldTable_temp[iRow][iCol] = l_yieldTable_temp[iRow][iCol].replace(r"\textbf", "")
    
    yieldTableStr = tabulate.tabulate(
        l_yieldTable_temp,
        headers = l_header
    )
    
    print yieldTableStr
    
    
    # Background table
    yieldTableLatex = Array2LatexTable.array2LatexTable(
        [l_header] + l_yieldTable,
        isColumnTitled = True,
        centerTable = True,
        table_caption = "Signal region yields for %s." %(era),
        table_label = "",
        table_width = 1,
        headerVspace = False,
        vLine = False,
        vSpace = False,
        vSpace_str = r"\\[\cmsTabSkip]",
        vSpaceAfterLine_str = r"\\[\cmsTabSkipSmall]",
        columnColorDict = {},
        columnHorOrientDict = {0: "l"},
        rowGap = True,
        line_break = r"\\[\cmsTabSkip]",
        d_line_break = {"vtop": r"\\[\cmsTabSkipLarge]", "tabular": r"\\[\cmsTabSkipLarge]"},
        adjustBox = False,
    )
    
    systTableDir = "cutFlowTables/%s" %("+".join(l_era))
    os.system("mkdir -p %s" %(systTableDir))
    
    yieldTableFile = "%s/yieldTable%s_tex.txt" %(systTableDir, "_withSignificance" * args.SRyieldWithSignificance)
    
    print "\n"
    print "Writing: %s" %(yieldTableFile)
    print "\n"
    
    with open(yieldTableFile, "w") as f :
        
        f.write(yieldTableLatex)
    
    
    ## Signal table
    #yieldTableLatex_sig = Array2LatexTable.array2LatexTable(
    #    [l_header_sig] + l_yieldTable_sig,
    #    isColumnTitled = True,
    #    centerTable = True,
    #    table_caption = "Signal region yields for %s." %(era),
    #    table_label = "",
    #    table_width = 1,
    #    headerVspace = False,
    #    vLine = False,
    #    vSpace = False,
    #    vSpace_str = r"\\[\cmsTabSkip]",
    #    vSpaceAfterLine_str = r"\\[\cmsTabSkipSmall]",
    #    columnColorDict = {},
    #    columnHorOrientDict = {0: "l"},
    #    rowGap = True,
    #    line_break = r"\\[\cmsTabSkip]",
    #    d_line_break = {"vtop": r"\\[\cmsTabSkipLarge]", "tabular": r"\\[\cmsTabSkipLarge]"},
    #    adjustBox = False,
    #)
    #
    #systTableDir = "cutFlowTables/%s" %("+".join(l_era))
    #os.system("mkdir -p %s" %(systTableDir))
    #
    #yieldTableFile_sig = "%s/yieldTable_sig_%s_tex.txt" %(systTableDir, sig_x_str_fileName)
    #
    #print "\n"
    #print "Writing: %s" %(yieldTableFile_sig)
    #print "\n"
    #
    #with open(yieldTableFile_sig, "w") as f :
    #    
    #    f.write(yieldTableLatex_sig)
    
    
    ##### Yield plot #####
    
    l_histDetail_data = []
    l_histDetail = []
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_data)
    histDetail_temp.histLabel = "Data"
    histDetail_temp.color = 1
    l_histDetail_data.append(histDetail_temp)
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_nominal_ttbar)
    histDetail_temp.histLabel = Details.latex_ttbar
    histDetail_temp.color = Details.color_ttbar
    l_histDetail.append(histDetail_temp)
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_nominal_DYJetsToLL)
    histDetail_temp.histLabel = Details.latex_DYJetsToLL
    histDetail_temp.color = Details.color_DYJetsToLL
    l_histDetail.append(histDetail_temp)
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_nominal_otherSM)
    histDetail_temp.histLabel = Details.latex_otherSM
    histDetail_temp.color = Details.color_otherSM
    l_histDetail.append(histDetail_temp)
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_nominal_fake)
    histDetail_temp.histLabel = "Misid. #tau_{h}"
    histDetail_temp.color = Details.color_QCD
    l_histDetail.append(histDetail_temp)
    
    
    #
    histDetail_mc_statErrPos = Common.HistogramDetails()
    histDetail_mc_statErrPos.hist = getYieldHist(yieldResult_data).Clone()
    histDetail_mc_statErrPos.hist.Reset()
    
    #
    histDetail_mc_statErrNeg = Common.HistogramDetails()
    histDetail_mc_statErrNeg.hist = getYieldHist(yieldResult_data).Clone()
    histDetail_mc_statErrNeg.hist.Reset()
    
    #
    histDetail_mc_systErrPos = Common.HistogramDetails()
    histDetail_mc_systErrPos.hist = getYieldHist(yieldResult_data).Clone()
    histDetail_mc_systErrPos.hist.Reset()
    
    #
    histDetail_mc_systErrNeg = Common.HistogramDetails()
    histDetail_mc_systErrNeg.hist = getYieldHist(yieldResult_data).Clone()
    histDetail_mc_systErrNeg.hist.Reset()
    
    for iSR in range(0, nSR_merged) :
        
        histDetail_mc_statErrPos.hist.SetBinContent(iSR+1, l_totalBkg_statErrPos[iSR])
        histDetail_mc_statErrNeg.hist.SetBinContent(iSR+1, l_totalBkg_statErrNeg[iSR])
        
        histDetail_mc_systErrPos.hist.SetBinContent(iSR+1, l_totalBkg_systErrPos[iSR])
        histDetail_mc_systErrNeg.hist.SetBinContent(iSR+1, l_totalBkg_systErrNeg[iSR])
    
    
    #
    l_histDetail_sig = []
    
    for iSig in range(0, len(l_massPointYieldHist)) :
        
        if (l_massPointYieldHist[iSig] in l_massPointYieldHist_yieldTableExtra) :
            
            continue
        
        key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
        
        yieldResult = Common.getEraCombinedYields([d_massPointYieldHist[key][era] for era in l_era])
        
        histDetail_temp = Common.HistogramDetails()
        histDetail_temp.hist = getYieldHist(yieldResult)
        histDetail_temp.histLabel = "x = %s, [%d, %d]" %(sig_x_str, key[0], key[1])
        #histDetail_temp.color = ROOT.kMagenta + 2*(iSig+1)
        #histDetail_temp.color = ROOT.kMagenta + 2*(len(l_histDetail_sig)+1)
        histDetail_temp.color = Details.l_color_sig[len(l_histDetail_sig)]
        histDetail_temp.lineStyle = Details.l_lineStyle_sig[len(l_histDetail_sig)]
        histDetail_temp.lineWidth = 5
        l_histDetail_sig.append(histDetail_temp)
    
    
    # Rearrange:
    # Reverse the order of prompt backgrounds (ttbar last)
    # Fake at last
    l_histDetail = l_histDetail[0:-1][::-1] + [l_histDetail[-1]]
    
    
    noPrelimStr = "_noPrelim"*(args.noPrelim)
    outDir = "plots/SR_yields/%s%s" %("+".join(l_era), noPrelimStr)
    os.system("mkdir -p %s" %(outDir))
    
    outFileName = "%s/SRyield_%s_%s" %(outDir, cutFlowNameBase, sig_x_str_fileName)
    
    Common.plot1D(
        l_histDetail_data = [],#l_histDetail_data,
        l_histDetail_mc = l_histDetail,
        histDetail_mc_statErrPos = histDetail_mc_statErrPos,
        histDetail_mc_statErrNeg = histDetail_mc_statErrNeg,
        histDetail_mc_systErrPos = histDetail_mc_systErrPos,
        histDetail_mc_systErrNeg = histDetail_mc_systErrNeg,
        l_histDetail_sig = [],#l_histDetail_sig,
        stackDrawOption = "",
        drawMCerr = True,
        ratioPlot = False,
        ratioLegendTextSizeScale = 2,
        ratioStatErr = True,
        ratioTotalErr = True,
        drawRatioStatErr = False,
        drawRatioTotalErr = True,
        title = "SR yields (%s)" %(era),
        xTitle = "SR bin number", yTitle = "Events",
        ratioYtitle = "Data / Pred.",
        d_colorRatioGridY = {1: {"color": 2}},
        #xMin = plotQuantity.xMin, xMax = plotQuantity.xMax,
        yMin = 1e-1,
        yMax = 1e5,
        logY = True,
        ratioHist_ymax = 2,
        gridX = False,
        gridY = False,
        centerLabelsX = True,
        #nDivisionsX = [nSR, 1, 1],
        drawLegend = True,
        legendBorder = 0,
        legendTextSize = 0.05,
        legendPos = "UR",
        legendNcolumn = 2,
        dataLegendFirst = True,
        drawRatioLegend = False,
        fixAlphanumericBinLabels = True,
        CMSextraText = Common.getCMSextraText(isPrelim = (not args.noPrelim)),
        lumiText = Common.getLumitext("+".join(l_era)),
        outFileName = outFileName,
        #outFileName_suffix = "",
    )

import argparse
import collections
import copy
import numpy
import os
import pprint
import sys
import tabulate

import ROOT


import Array2LatexTable


# Argument parser
parser = argparse.ArgumentParser()

# List of directories
parser.add_argument(
    "--era",
    help = "Era",
    #nargs = "*",
    type = str,
    choices = ["2016", "2017", "2016+2017"],
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
    "--card",
    help = "Make combine cards",
    default = False,
    action = "store_true",
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

# Parse arguments
args = parser.parse_args()

if (args.pseudodataSB and args.pseudodataB) :
    
    print "Error: Only ONE of --pseudodataSB and --pseudodataB can be given at a time."
    exit(1)

print args.card
print args.syst

if (args.era == "2016+2017" and (not args.SRyield and not args.syst)) :
    
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

era = args.era


lumi_data = Details.luminosity_data[era]
lumi_data_TTCR = Details.luminosity_data[era]

fakeScale = 1.0

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

def getCorrStr(systName, era, isCorr) :
    
    if (isCorr) :
        
        corrStr = "%s" %(systName)
    
    else :
        
        corrStr = "syst%s_%s" %(era, systName)
    
    #corrStr = ""
    #
    #if (systName in l_corrSyst) :
    #    
    #    corrStr = ""
    #
    #elif (systName in l_uncorrSyst) :
    #    
    #    corrStr = "syst%s_" %(era)
    #
    #else :
    #    
    #    print "Error in getCorrStr(...): Invalid systematic name (%s) provided." %(systName)
    
    return corrStr


# Systematics dictionaries
d_syst_sig = {
    "tauFastFullSimSF": {
        "latexTitle": r"$ \tauh $ FastSim/FullSim",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
}

l_syst_sig_toExclude = ["normalization"]


d_syst_commonMC = {
    "tauES": {
        "latexTitle": r"$ \tauh $ energy scale",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
    
    "pileupReweight": {
        "latexTitle": r"Pileup",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
    
    "tauIDisoSF": {
        "latexTitle": r"$ \tauh $ ID-iso",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
    
    ##"triggerSF": {
    ##    "type": "lnN",
    ##    "added": False,
    ##},
    
    "bTaggingSF": {
        "latexTitle": r"b-tagging",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
    
    "JEC": {
        "latexTitle": r"JEC",
        "type": "lnN",
        "added": False,
        "correlated": True,
    },
    
    "JER": {
        "latexTitle": r"JER",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
    
    "unclusteredEnergy": {
        "latexTitle": r"\ptmiss unclustered energy",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
    
    "scale": {
        "latexTitle": r"QCD scale",
        "type": "lnN",
        "added": False,
        "correlated": True,
    },
}

d_syst_ttbar = {
    #"topPtReweight": {
    #    "latexTitle": r"Top $ \pt $ reweighting",
    #    "type": "lnN",
    #    "added": False,
    #},
}

l_syst_ttbar_toInclude = [
    "tauES",
    "tauIDisoSF",
]

d_syst_DY = {
    "ZpTreweight": {
        "latexTitle": r"Z $ \pt $ reweighting",
        "type": "lnN",
        "added": False,
        "correlated": False,
    },
}

d_syst_fake = {
    "tauFakeRateRegion": {
        #"latexTitle": r"$ \tauh $ fake-rate (region)",
        "latexTitle": r"\vtop{\hbox{\strut $ \tauh $ fake-rate}\hbox{\strut ($ LL \to TL $ vs. $ TL \to TT $)}}",
        "type": "lnN",
        "added": False,
        "correlated": True,
    },
    
    "tauFakeRateJetPartonFlav": {
        "latexTitle": r"$ \tauh $ fake-rate (parton flavour)",
        "type": "lnN",
        "added": False,
        "correlated": True,
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

process_sig = d_process_sig[era][args.xVal]

massPointFile = "stopPair_mc/output_genParam/" + process_sig + "/XSweightInfo.txt"

massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")


############################################################
#################### Select mass points ####################
############################################################

l_selectMassPoint = []
l_selectMassPoint = [
    #[700, 150],
    #[700, 1],
    #[900, 400],
    #[1000, 1], [600, 425], [300, 150],
]


sig_x_str = ""
sig_x_str_fileName = ""

if ("XStau0p25" in process_sig) :
    
    sig_x_str = "0.25"
    sig_x_str_fileName = "x0p25"

elif ("XStau0p5" in process_sig) :
    
    sig_x_str = "0.5"
    sig_x_str_fileName = "x0p5"

elif ("XStau0p75" in process_sig) :
    
    sig_x_str = "0.75"
    sig_x_str_fileName = "x0p75"

l_massPointYieldHist = []
l_massPointYieldHist = [[300, 100], [500, 350], [800, 300]]

l_massPointYieldHist_yieldTableExtra = []#[[300, 100]]

if (args.SRyield and len(l_massPointYieldHist)) :
    
    l_massPointYieldHist = l_massPointYieldHist_yieldTableExtra + l_massPointYieldHist

d_massPointYieldHist = {}

d_massPointSystTable = {}

for ele in l_massPointYieldHist :
    
    d_massPointSystTable[(ele[0], ele[1])] = {}


for ele in l_massPointYieldHist :
    
    if (ele not in l_selectMassPoint) :
        
        l_selectMassPoint.append(ele)


if len(l_selectMassPoint) :
    
    massPointInfo = numpy.array([ele for ele in massPointInfo if [int(ele[0]), int(ele[1])] in l_selectMassPoint])

############################################################


combineDatacard_template_name = "combineDatacard_template.txt"
combineDatacard_name = "combineDatacard_" + cutFlowNameBase + "_@stop1_m@_@neutralino1_m@.txt"

combineOutput_name = "combineOutput_@stop1_m@_@neutralino1_m@.txt"

combineDatacard_content = ""

with open(combineDatacard_template_name, "r") as f :
    
    combineDatacard_content = f.read()


#suffix = "_tauTau_analysis"
debug = False

#rootFileName = "custom_all_analyzed.root"

#inputFiles_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data[era], suffix, rootFileName)

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

#details_otherSM = Details.cutFlowDir_singleTop[era]
#
#l_xs_otherSM = Details.crossSection_singleTop[era]


label_sig = "sig"
label_DYJetsToLL = "DY" #Details.label_DYJetsToLL[0]
label_ttbar = Details.label_ttbar[0]
label_otherSM = "otherSM"
label_fake = "fake"

#l_label_otherSM = [
#    Details.label_WJetsToLNu,
#    Details.label_VH,
#    Details.label_VV,
#    Details.label_WG,
#    Details.label_singleTop,
#]


inputFiles_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data[era], suffix_data, rootFileName_data)

inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix_mc, rootFileName_mc)
inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix_mc, rootFileName_mc)
inputFiles_otherSM = Common.getRootFiles(details_otherSM, suffix_mc, rootFileName_mc)
inputFiles_fake = Common.getRootFiles(Details.cutFlowDir_tauTau_fakeEstimation[era], suffix_fakeEstimation, rootFileName_fakeEstimation)


prettyPrinter = pprint.PrettyPrinter(indent = 4)


def getRootFiles_ttbarCR(era, suffix, rootFileName) :
    
    inputFiles_WJetsToLNu_ttbarCR = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
    inputFiles_DYJetsToLL_ttbarCR = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)
    inputFiles_VH_ttbarCR = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
    inputFiles_VV_ttbarCR = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
    inputFiles_WG_ttbarCR = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
    inputFiles_ttbar_ttbarCR = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix, rootFileName)
    inputFiles_singleTop_ttbarCR = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)
    
    inputFiles_ttbarCR = [
        inputFiles_WJetsToLNu_ttbarCR,
        inputFiles_DYJetsToLL_ttbarCR,
        inputFiles_VH_ttbarCR,
        inputFiles_VV_ttbarCR,
        inputFiles_WG_ttbarCR,
        inputFiles_ttbar_ttbarCR,
        inputFiles_singleTop_ttbarCR,
    ]
    
    labels_ttbarCR = [
        Details.label_WJetsToLNu[0],
        Details.label_DYJetsToLL[0],
        Details.label_VH[0],
        Details.label_VV[0],
        Details.label_WG[0],
        Details.label_ttbar[0],
        Details.label_singleTop[0],
    ]
    
    crossSections_ttbarCR = [
        Details.crossSection_WJetsToLNu[era],
        Details.crossSection_DYJetsToLL[era],
        Details.crossSection_VH[era],
        Details.crossSection_VV[era],
        Details.crossSection_WG[era],
        Details.crossSection_ttbar[era],
        Details.crossSection_singleTop[era],
    ]
    
    d_info_ttbarCR = {
        "files": inputFiles_ttbarCR,
        "labels": labels_ttbarCR,
        "xs": crossSections_ttbarCR,
    }
    
    return d_info_ttbarCR


inputFiles_data_ttbarCR_elMu = Common.getRootFiles(Details.cutFlowDir_elMu_data[era], suffix_ttbarCR_elMu, rootFileName_ttbarCR)
d_info_mc_ttbarCR_elMu = getRootFiles_ttbarCR(era = era, suffix = suffix_ttbarCR_elMu, rootFileName = rootFileName_ttbarCR)

inputFiles_data_ttbarCR_muMu = Common.getRootFiles(Details.cutFlowDir_muMu_data[era], suffix_ttbarCR_muMu, rootFileName_ttbarCR)
d_info_mc_ttbarCR_muMu = getRootFiles_ttbarCR(era = era, suffix = suffix_ttbarCR_muMu, rootFileName = rootFileName_ttbarCR)


##################################################
# Getting the info for the background
##################################################

for systKey in d_syst_commonMC :
    
    if (d_syst_commonMC[systKey]["added"]) :
        
        continue
    
    
    if (systKey == "scale") :
        
        systResult_ttbar = Common.getScaleUncertainty(
            l_rootFileDir = Details.cutFlowDir_ttbar[era],
            rootFileName = rootFileName_mc,
            l_xs = Details.crossSection_ttbar[era],
            l_scaleVarIndex = l_scaleVarIndex,
            suffix = suffix_mc,
            histName_base = histName_base,
            detailStr = detailStr_mc,
            nRegion = nSR,
            yieldBinNumber = finalYieldBin,
            ll_regionNumber = ll_regionNumber_SR,
            debug = debug,
        )
        
        
        systResult_DYJetsToLL = Common.getScaleUncertainty(
            l_rootFileDir = Details.cutFlowDir_DYJetsToLL[era],
            rootFileName = rootFileName_mc,
            l_xs = Details.crossSection_DYJetsToLL[era],
            l_scaleVarIndex = l_scaleVarIndex,
            suffix = suffix_mc,
            histName_base = histName_base,
            detailStr = detailStr_mc,
            nRegion = nSR,
            yieldBinNumber = finalYieldBin,
            ll_regionNumber = ll_regionNumber_SR,
            debug = debug,
        )
        
        
        systResult_otherSM = Common.getScaleUncertainty(
            l_rootFileDir = details_otherSM,
            rootFileName = rootFileName_mc,
            l_xs = l_xs_otherSM,
            l_scaleVarIndex = l_scaleVarIndex,
            suffix = suffix_mc,
            histName_base = histName_base,
            detailStr = detailStr_mc,
            nRegion = nSR,
            yieldBinNumber = finalYieldBin,
            ll_regionNumber = ll_regionNumber_SR,
            debug = debug,
        )
    
    else :
        
        systResult_ttbar = Common.getSystematics(
            l_rootFileDir = Details.cutFlowDir_ttbar[era],
            rootFileName = rootFileName_mc,
            l_xs = Details.crossSection_ttbar[era],
            suffix = suffix_mc,
            systStr = systKey,
            histName_base = histName_base,
            detailStr = detailStr_mc,
            nRegion = nSR,
            yieldBinNumber = finalYieldBin,
            ll_regionNumber = ll_regionNumber_SR,
            debug = debug,
        )
        
        
        systResult_DYJetsToLL = Common.getSystematics(
            l_rootFileDir = Details.cutFlowDir_DYJetsToLL[era],
            rootFileName = rootFileName_mc,
            l_xs = Details.crossSection_DYJetsToLL[era],
            suffix = suffix_mc,
            systStr = systKey,
            histName_base = histName_base,
            detailStr = detailStr_mc,
            nRegion = nSR,
            yieldBinNumber = finalYieldBin,
            ll_regionNumber = ll_regionNumber_SR,
            debug = debug,
        )
        
        
        systResult_otherSM = Common.getSystematics(
            l_rootFileDir = details_otherSM,
            rootFileName = rootFileName_mc,
            l_xs = l_xs_otherSM,
            suffix = suffix_mc,
            systStr = systKey,
            histName_base = histName_base,
            detailStr = detailStr_mc,
            nRegion = nSR,
            yieldBinNumber = finalYieldBin,
            ll_regionNumber = ll_regionNumber_SR,
            debug = debug,
        )
    
    
    d_syst_commonMC[systKey][label_DYJetsToLL] = systResult_DYJetsToLL
    
    if (systKey in l_syst_ttbar_toInclude) :
        
        d_syst_commonMC[systKey][label_ttbar] = systResult_ttbar
    
    d_syst_commonMC[systKey][label_otherSM] = systResult_otherSM


for systKey in d_syst_ttbar :
    
    systResult_ttbar = Common.getSystematics(
        l_rootFileDir = Details.cutFlowDir_ttbar[era],
        rootFileName = rootFileName_mc,
        l_xs = Details.crossSection_ttbar[era],
        suffix = suffix_mc,
        systStr = systKey,
        histName_base = histName_base,
        detailStr = detailStr_mc,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        debug = debug,
    )
    
    d_syst_ttbar[systKey][label_ttbar] = systResult_ttbar


for systKey in d_syst_DY :
    
    systResult_DY = Common.getSystematics(
        l_rootFileDir = Details.cutFlowDir_DYJetsToLL[era],
        rootFileName = rootFileName_mc,
        l_xs = Details.crossSection_DYJetsToLL[era],
        suffix = suffix_mc,
        systStr = systKey,
        histName_base = histName_base,
        detailStr = detailStr_mc,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        debug = debug,
    )
    
    d_syst_DY[systKey][label_DYJetsToLL] = systResult_DY


for systKey in d_syst_fake :
    
    systResult_fake = Common.getSystematics(
        l_rootFileDir = Details.cutFlowDir_tauTau_fakeEstimation[era],
        rootFileName = rootFileName_fakeEstimation,
        l_xs = [],
        suffix = suffix_fakeEstimation,
        systStr = systKey,
        histName_base = histName_base,
        detailStr = detailStr_fakeEstimation,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        debug = debug,
    )
    
    d_syst_fake[systKey][label_fake] = systResult_fake


# Data
yieldResult_data = Common.getYields(
    l_rootFile = inputFiles_data,
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
    debug = debug,
)


# Nominal
yieldResult_nominal_ttbar = Common.getYields(
    l_rootFile = inputFiles_ttbar,
    l_xs = Details.crossSection_ttbar[era],
    suffix = suffix_mc,
    systStr = "",
    histName_base = histName_base,
    detailStr = detailStr_mc,
    nRegion = nSR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_SR,
    scale = lumi_data,
    negToZero = True,
    era = era,
    debug = debug,
)

yieldResult_nominal_DYJetsToLL = Common.getYields(
    l_rootFile = inputFiles_DYJetsToLL,
    l_xs = Details.crossSection_DYJetsToLL[era],
    suffix = suffix_mc,
    systStr = "",
    histName_base = histName_base,
    detailStr = detailStr_mc,
    nRegion = nSR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_SR,
    scale = lumi_data,
    negToZero = True,
    era = era,
    debug = debug,
)

yieldResult_nominal_otherSM = Common.getYields(
    l_rootFile = inputFiles_otherSM,
    l_xs = l_xs_otherSM,
    suffix = suffix_mc,
    systStr = "",
    histName_base = histName_base,
    detailStr = detailStr_mc,
    nRegion = nSR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_SR,
    scale = lumi_data,
    negToZero = True,
    era = era,
    debug = debug,
)

yieldResult_nominal_fake = Common.getYields(
    l_rootFile = inputFiles_fake,
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
    debug = debug,
)


# ttbar SF
ttbarSFinfo_elMu = Common.getTTbarSF_multibin(
    cutFlowNameBase = histName_base_ttbarCR,
    inputFiles_data = inputFiles_data_ttbarCR_elMu,
    lumi_data = lumi_data_TTCR,
    label_data = "data",
    details_data = detailStr_ttbarCR,
    inputFiles_mc = d_info_mc_ttbarCR_elMu["files"],
    crossSections_mc = d_info_mc_ttbarCR_elMu["xs"],
    labels_mc = d_info_mc_ttbarCR_elMu["labels"],
    details_mc = detailStr_ttbarCR,
    ll_regionNumber = ll_regionNumber_ttbarCR,
    debug = debug,
)

ttbarSFinfo_muMu = Common.getTTbarSF_multibin(
    cutFlowNameBase = histName_base_ttbarCR,
    inputFiles_data = inputFiles_data_ttbarCR_muMu,
    lumi_data = lumi_data_TTCR,
    label_data = "data",
    details_data = detailStr_ttbarCR,
    inputFiles_mc = d_info_mc_ttbarCR_muMu["files"],
    crossSections_mc = d_info_mc_ttbarCR_muMu["xs"],
    labels_mc = d_info_mc_ttbarCR_muMu["labels"],
    details_mc = detailStr_ttbarCR,
    ll_regionNumber = ll_regionNumber_ttbarCR,
    debug = debug,
)

l_ttbarSF_elMu = ttbarSFinfo_elMu["SF"]
l_ttbarSF_muMu = ttbarSFinfo_muMu["SF"]

l_ttbarSF_err_elMu = ttbarSFinfo_elMu["SFerr"]
l_ttbarSF_err_muMu = ttbarSFinfo_muMu["SFerr"]

l_ttbarSF = [(l_ttbarSF_elMu[iEle] + l_ttbarSF_muMu[iEle]) / 2.0 for iEle in range(0, len(l_ttbarSF_elMu))]

# Difference between elMu and muMu
l_ttbarSF_err = [abs(l_ttbarSF_elMu[iEle]-l_ttbarSF[iEle]) for iEle in range(0, len(l_ttbarSF_elMu))]

#print "XXXXX", l_ttbarSF_err_elMu
#print "YYYYY", l_ttbarSF_err_muMu
#print "ZZZZZ", l_ttbarSF_err

# Add the stat error in quadrature
l_ttbarSF_err = [numpy.sqrt(l_ttbarSF_err[iEle]**2 + (l_ttbarSF_err_elMu[iEle]**2 + l_ttbarSF_err_muMu[iEle]**2)/4.0) for iEle in range(0, len(l_ttbarSF_elMu))]

#print "FFFFF", l_ttbarSF_err

# To percentage
l_ttbarSF_err = [(l_ttbarSF_err[iEle] / l_ttbarSF[iEle] * 100.0) for iEle in range(0, len(l_ttbarSF))]

#print "PPPPP", l_ttbarSF_err

# Apply ttbar SF
l_ttbarSF_temp = []
l_ttbarSF_err_temp = []

for iRegionGroup in range (0, nSR_merged) :
    
    ttbarSF_temp = 0
    ttbarSF_err_temp = 0
    
    for iRegion in range(0, len(ll_regionNumber_SR[iRegionGroup])) :
        
        regionNumber = ll_regionNumber_SR[iRegionGroup][iRegion]
        
        ttbarSF_temp += l_ttbarSF[regionNumber-1]
        ttbarSF_err_temp += l_ttbarSF_err[regionNumber-1]
    
    ttbarSF_temp /= len(ll_regionNumber_SR[iRegionGroup])
    ttbarSF_err_temp /= len(ll_regionNumber_SR[iRegionGroup])
    
    l_ttbarSF_temp.append(ttbarSF_temp)
    l_ttbarSF_err_temp.append(ttbarSF_err_temp)
    
    yieldResult_nominal_ttbar["yield"][iRegionGroup] *= ttbarSF_temp

l_ttbarSF = l_ttbarSF_temp
l_ttbarSF_err = l_ttbarSF_err_temp

# Weighted average
ttbarF_err_mean = numpy.average(l_ttbarSF_err, weights = yieldResult_nominal_ttbar["yield"])

d_syst_ttbar["ttbarSF"] = {
    "latexTitle": r"$ \ttbar $ SF",
    "type": "lnN",
    "correlated": False,
    
    label_ttbar: {
        "syst": l_ttbarSF_err,
        "syst_mean": ttbarF_err_mean,
        "integral_syst": ttbarF_err_mean,
    }
}


# Luminosity
lumi_err = Details.luminosity_unc_data[era]
l_lumi_err = [lumi_err]*nSR_merged


d_syst_commonMC["luminosity"] = {
    "latexTitle": r"Luminosity",
    "type": "lnN",
    "added": True,
    "correlated": False,
    
    label_sig: {
        "syst": l_lumi_err,
        "syst_mean": lumi_err,
        "integral_syst": lumi_err,
    },
    
    #label_ttbar: {
    #    "syst": l_lumi_err,
    #    "syst_mean": lumi_err,
    #    "integral_syst": lumi_err,
    #},
    
    label_DYJetsToLL: {
        "syst": l_lumi_err,
        "syst_mean": lumi_err,
        "integral_syst": lumi_err,
    },
    
    label_otherSM: {
        "syst": l_lumi_err,
        "syst_mean": lumi_err,
        "integral_syst": lumi_err,
    },
}


# TEST!!!
# Flat normalization uncertainty
norm_err = 15.0
l_norm_err = [norm_err]*nSR_merged

d_syst_commonMC["normalization"] = {
    "latexTitle": r"Background normalization",
    "type": "lnN",
    "added": True,
    "correlated": True,
    
    #label_sig: {
    #    "syst": [0.0]*nSR_merged,
    #    "syst_mean": 0.0,
    #    "integral_syst": 0.0,
    #},
    
    #label_ttbar: {
    #    "syst": l_norm_err,
    #    "syst_mean": norm_err,
    #    "integral_syst": norm_err,
    #},
    
    label_DYJetsToLL: {
        "syst": l_norm_err,
        "syst_mean": norm_err,
        "integral_syst": norm_err,
    },
    
    label_otherSM: {
        "syst": l_norm_err,
        "syst_mean": norm_err,
        "integral_syst": norm_err,
    },
}


#print "\n\n%s\n" %("*"*50)
#print prettyPrinter.pprint(d_syst_commonMC)
#print "\n\n%s\n" %("*"*50)
#print prettyPrinter.pprint(d_syst_fake)
#print "\n\n%s\n" %("*"*50)
#print prettyPrinter.pprint(d_syst_ttbar)
#
#print "\n\n%s\n" %("*"*50)
#print l_ttbarSF


##################################################
# Got info for the background
##################################################


d_systCombined = {
    label_ttbar: {
        "stat": [0]*nSR_merged,
        "syst": [[] for ele in range(0, nSR_merged)],
    },
    
    label_DYJetsToLL: {
        "stat": [0]*nSR_merged,
        "syst": [[] for ele in range(0, nSR_merged)],
    },
    
    label_otherSM: {
        "stat": [0]*nSR_merged,
        "syst": [[] for ele in range(0, nSR_merged)],
    },
    
    label_fake: {
        "stat": [0]*nSR_merged,
        "syst": [[] for ele in range(0, nSR_merged)],
    },
}


d_systCombined_sig = {}


def writeCard(
    combineDatacard_content,
    era,
    outFileName,
    d_block_data = {},
    d_block_mc = {},
    d_block_err = {},
    d_block_statErr = {},
    ) :
    
    
    combineDatacard_content_mod = combineDatacard_content
    
    # Edit datacard
    
    combineDatacard_content_mod = combineDatacard_content_mod.replace(
        "@nChannel@",
        str(nSR_merged)
    )
    
    combineDatacard_content_mod = combineDatacard_content_mod.replace(
        "@nBG@",
        "*"
    )
    
    combineDatacard_content_mod = combineDatacard_content_mod.replace(
        "@nSystematics@",
        "*"
    )
    
    #combineDatacard_content_mod = combineDatacard_content_mod.replace(
    #    "@binLabels@",
    #    " ".join(["%s%d" %(histName_base, iSR+1) for iSR in range(0, nSR_merged)])
    #)
    
    combineDatacard_content_mod = combineDatacard_content_mod.replace(
        "#@yieldBlock_data@",
        
        tabulate.tabulate(
            [
                d_block_data["bin"],
                d_block_data["observation"],
            ],
            
            tablefmt = "plain",
        )
    )
    
    combineDatacard_content_mod = combineDatacard_content_mod.replace(
        "#@yieldBlock_mc@",
        
        tabulate.tabulate(
            [
                #d_block_mc["bin"].split(),
                #d_block_mc["processName"].split(),
                #d_block_mc["processIndex"].split(),
                #d_block_mc["rate"].split(),
                d_block_mc["bin"],
                d_block_mc["processName"],
                d_block_mc["processIndex"],
                d_block_mc["rate"],
            ],
            
            tablefmt = "plain",
        )
    )
    
    
    l_key_sorted = Common.getSortedList(d_block_err)
    
    combineDatacard_content_mod = combineDatacard_content_mod.replace(
        "#@systematicsBlock@",
        
        tabulate.tabulate(
            #[
            #    ["#"] + ["#"] + d_block_mc["bin"].split()[1:],
            #    ["#"] + ["#"] + d_block_mc["processName"].split()[1:],
            #    ["#"] + ["#"] + d_block_mc["processIndex"].split()[1:],
            #] + \
            #[d_block_err[systKey].split() for systKey in d_block_err],
            [
                ["#"] + ["#"] + d_block_mc["bin"][1:],
                ["#"] + ["#"] + d_block_mc["processName"][1:],
                ["#"] + ["#"] + d_block_mc["processIndex"][1:],
            ] + \
            [d_block_err[systKey] for systKey in l_key_sorted],
            
            tablefmt = "plain",
        )
    )
    
    
    l_key_sorted = Common.getSortedList(d_block_statErr)
    
    combineDatacard_content_mod = combineDatacard_content_mod.replace(
        "#@statBlock@",
        
        tabulate.tabulate(
            [
                ["#"] + ["#"] + d_block_mc["bin"][1:],
                ["#"] + ["#"] + d_block_mc["processName"][1:],
                ["#"] + ["#"] + d_block_mc["processIndex"][1:],
            ] + \
            [d_block_statErr[systKey] for systKey in l_key_sorted],
            
            tablefmt = "plain",
        )
    )
    
    # Group stat
    #l_statGroup = ["group_stat%s group = " %(era)]
    #
    #for systKey in l_key_sorted :
    #    
    #    l_statGroup.append(systKey)
    #
    #combineDatacard_content_mod = combineDatacard_content_mod.replace(
    #    "#@statGroupBlock@",
    #    
    #    tabulate.tabulate(
    #        [l_statGroup],
    #        tablefmt = "plain",
    #    )
    #)
    
    
    # Uncorrelate stat uncertainty
    #nuisanceOptionStr = "nuisance~edit~rename~@process@~@channel@~@oldname@~@newname@"
    #
    #l_nuisanceOption = []
    #
    #nuisanceName = "stat%s" %(era)
    #
    #l_processName = d_block_mc["processName"][1:]
    #l_binName = d_block_mc["bin"][1:]
    #
    ## Remove duplicates (preserve order)
    ##l_processName = list(set(l_processName))
    ##l_binName = list(set(l_binName))
    #l_processName = list(collections.OrderedDict.fromkeys(l_processName))
    #l_binName = list(collections.OrderedDict.fromkeys(l_binName))
    #
    #
    #for iProcess in range(0, len(l_processName)) :
    #    
    #    for iBin in range(0, len(l_binName)) :
    #        
    #        nuisanceName_mod = "%s_%s_%s" %(nuisanceName, l_processName[iProcess], l_binName[iBin])
    #        
    #        nuisanceOptionStr_mod = nuisanceOptionStr
    #        
    #        nuisanceOptionStr_mod = nuisanceOptionStr_mod.replace("@process@", l_processName[iProcess])
    #        nuisanceOptionStr_mod = nuisanceOptionStr_mod.replace("@channel@", l_binName[iBin])
    #        nuisanceOptionStr_mod = nuisanceOptionStr_mod.replace("@oldname@", nuisanceName)
    #        nuisanceOptionStr_mod = nuisanceOptionStr_mod.replace("@newname@", nuisanceName_mod)
    #        
    #        l_nuisanceOption.append(nuisanceOptionStr_mod)
    #
    #combineDatacard_content_mod = combineDatacard_content_mod.replace(
    #    "#@nuisanceOptionsBlock@",
    #    
    #    #"\n".join(l_nuisanceOption)
    #    
    #    tabulate.tabulate(
    #        [ele.split("~") for ele in l_nuisanceOption],
    #        tablefmt = "plain",
    #    )
    #)
    
    
    # Write datacard
    print "Writing: %s" %(outFileName)
    
    with open("%s" %(outFileName), "w") as f :
        
        f.write(combineDatacard_content_mod)


def fillStatError(
    d_info,
    d_out,
    processLabel,
    binLabel,
    nProcess,
    iProcess,
    nBin,
    iBin,
    era,
    isFake = False,
    ) :
    
    nBefore = iBin*nProcess + iProcess
    nAfter = nBin*nProcess - nBefore - 1
    
    if (d_info["yield"][iBin] == 0 and not isFake) :
        
        #statName = "zerostat%s_%s_%s%d" %(era, processLabel, binLabel, iBin+1)
        statName = "stat%s_%s_%s%d" %(era, processLabel, binLabel, iBin+1)
        d_out[statName] = [statName, "gmN 0"]
        
        d_out[statName].extend(["-"] * nBefore)
        d_out[statName].append("%0.4e" %(d_info["scale"]))
        d_out[statName].extend(["-"] * nAfter)
    
    else :
        
        statName = "stat%s_%s_%s%d" %(era, processLabel, binLabel, iBin+1)
        d_out[statName] = [statName, "lnN"]
        
        d_out[statName].extend(["-"] * nBefore)
        d_out[statName].append("%0.4e" %(1+Common.getRelativeError(val = d_info["yield"][iBin], err = d_info["error"][iBin])))
        d_out[statName].extend(["-"] * nAfter)
        
        #d_block_err["stat"].append("%0.4e" %(1+Common.getRelativeError(val = yieldResult_nominal_ttbar["yield"][iSR], err = yieldResult_nominal_ttbar["error"][iSR])))


for iMass in range(0, massPointInfo.shape[0]) :
    
    d_block_data = copy.deepcopy(d_block_data_template)
    d_block_mc = copy.deepcopy(d_block_mc_template)
    d_block_statErr = copy.deepcopy(d_block_statErr_template)
    d_block_err = copy.deepcopy(d_block_err_template)
    
    
    stop1_m = massPointInfo[iMass, 0]
    neutralino1_m = massPointInfo[iMass, 1]
    xs_sig = massPointInfo[iMass, 3]
    xsUnc_sig = massPointInfo[iMass, 4]
    
    suffix_sig = suffix_mc
    cutFlowDir_sig = "stopPair_mc/output_analyzed/" + process_sig
    inputFiles_sig = Common.getRootFiles([cutFlowDir_sig], suffix_sig, rootFileName_mc)
    
    suffix_sig_genMET = suffix_mc + "_withGenMET"
    cutFlowDir_sig_genMET = "stopPair_mc/output_analyzed/" + process_sig
    inputFiles_sig_genMET = Common.getRootFiles([cutFlowDir_sig_genMET], suffix_sig_genMET, rootFileName_mc)
    
    # Using 2016 signal, but need to create separate directory for 2017
    process_sig_mod = process_sig
    
    if (era == "2017") :
        
        process_sig_mod = process_sig.replace("Summer16", "Fall17")
    
    combineOutputDir = "stopPair_mc/output_combine/" + process_sig_mod + suffix_mc
    command = "mkdir -p " + combineOutputDir
    os.system(command)
    
    detailStr_sig = "%s_%d_%d" %(detailStr_mc, int(stop1_m), int(neutralino1_m))
    
    
    ##### Signal systematics #####
    
    # Signal xs uncertainty
    # Only for systematics table
    if (args.syst) :
        
        d_syst_sig["sigXS"] = {
            "latexTitle": r"Signal cross-section",
            "type": "lnN",
            "added": True,
            "correlated": True,
            
            label_sig: {
                "syst": [xsUnc_sig]*nSR_merged,
                "syst_mean": xsUnc_sig,
                "integral_syst": xsUnc_sig,
            },
        }
    
    # Common systematics
    for systKey in d_syst_commonMC :
        
        if (systKey in l_syst_sig_toExclude) :
            
            continue
        
        if (d_syst_commonMC[systKey]["added"]) :
            
            if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
                
                d_massPointSystTable[(int(stop1_m), int(neutralino1_m))][systKey] = d_syst_commonMC[systKey][label_sig]
            
            continue
        
        if (systKey == "scale") :
            
            systResult_sig = Common.getScaleUncertainty(
                l_rootFileDir = [cutFlowDir_sig],
                rootFileName = rootFileName_mc,
                l_xs = [xs_sig],
                l_scaleVarIndex = l_scaleVarIndex,
                suffix = suffix_sig,
                histName_base = histName_base,
                detailStr = detailStr_sig,
                nRegion = nSR,
                yieldBinNumber = finalYieldBin,
                ll_regionNumber = ll_regionNumber_SR,
                debug = debug,
            )
        
        else :
            
            systResult_sig = Common.getSystematics(
                l_rootFileDir = [cutFlowDir_sig],
                rootFileName = rootFileName_mc,
                l_xs = [xs_sig],
                suffix = suffix_sig,
                systStr = systKey,
                histName_base = histName_base,
                detailStr = detailStr_sig,
                nRegion = nSR,
                yieldBinNumber = finalYieldBin,
                ll_regionNumber = ll_regionNumber_SR,
                debug = debug,
            )
        
        d_syst_commonMC[systKey][label_sig] = systResult_sig
        
        if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
            
            d_massPointSystTable[(int(stop1_m), int(neutralino1_m))][systKey] = systResult_sig
    
    
    # Signal specific systematics
    for systKey in d_syst_sig :
        
        if (d_syst_sig[systKey]["added"]) :
            
            if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
                
                d_massPointSystTable[(int(stop1_m), int(neutralino1_m))][systKey] = d_syst_sig[systKey][label_sig]
            
            continue
        
        systResult_sig = Common.getSystematics(
            l_rootFileDir = [cutFlowDir_sig],
            rootFileName = rootFileName_mc,
            l_xs = [xs_sig],
            suffix = suffix_sig,
            systStr = systKey,
            histName_base = histName_base,
            detailStr = detailStr_sig,
            nRegion = nSR,
            yieldBinNumber = finalYieldBin,
            ll_regionNumber = ll_regionNumber_SR,
            debug = debug,
        )
        
        d_syst_sig[systKey][label_sig] = systResult_sig
        
        if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
            
            d_massPointSystTable[(int(stop1_m), int(neutralino1_m))][systKey] = systResult_sig
    
    
    
    # Signal nominal
    yieldResult_nominal_sig = Common.getYields(
        l_rootFile = inputFiles_sig,
        l_xs = [xs_sig],
        suffix = suffix_sig,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr_sig,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        l_rootFile_sig_genMET = inputFiles_sig_genMET,
        ll_regionNumber = ll_regionNumber_SR,
        scale = lumi_data,
        debug = debug,
    )
    
    # Signal yields with GEN-MET
    yieldResult_nominal_sig_genMET= Common.getYields(
        l_rootFile = inputFiles_sig_genMET,
        l_xs = [xs_sig],
        suffix = suffix_sig_genMET,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr_sig,
        nRegion = nSR,
        yieldBinNumber = finalYieldBin,
        ll_regionNumber = ll_regionNumber_SR,
        scale = lumi_data,
        debug = debug,
    )
    
    l_syst_temp = []
    syst_mean_temp = 0
    integral_temp = 0
    
    for iSR in range(0, nSR_merged) :
        
        #yield_temp = (yieldResult_nominal_sig["yield"][iSR] + yieldResult_nominal_sig_genMET["yield"][iSR]) / 2.0
        yield_temp = yieldResult_nominal_sig["yield"][iSR]
        
        syst_temp = abs(yield_temp - yieldResult_nominal_sig_genMET["yield"][iSR])
        
        systPercent_temp = 0
        
        if (yield_temp) :
            
            systPercent_temp = syst_temp / yield_temp * 100.0
        
        if (systPercent_temp == -100) :
            
            systPercent_temp = (1e-4 - 1) * 100
        
        integral_temp += yield_temp
        syst_mean_temp += systPercent_temp * yield_temp
        
        l_syst_temp.append(systPercent_temp)
    
    if (integral_temp) :
        
        syst_mean_temp /= integral_temp
    
    
    d_syst_sig["sigMET"] = {
        "latexTitle": r"FastSim $ \ptmiss $ resolution",
        "type": "lnN",
        "added": True,
        "correlated": True,
        
        label_sig: {
            "syst": l_syst_temp,
            "syst_mean": syst_mean_temp,
            "integral_syst": syst_mean_temp,
        },
    }
    
    
    sigKey = (int(stop1_m), int(neutralino1_m))
    
    if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
        
        # Key must be immutable
        # Use tuple
        d_massPointYieldHist[(int(stop1_m), int(neutralino1_m))] = yieldResult_nominal_sig
        d_massPointSystTable[(int(stop1_m), int(neutralino1_m))]["sigMET"] = d_syst_sig["sigMET"][label_sig]
        
        
        if (label_sig not in d_systCombined_sig) :
            
            d_systCombined_sig[sigKey] = {
                "stat": [0]*nSR_merged,
                "syst": [[] for ele in range(0, nSR_merged)],
            }
    
    
    # Datacard name
    combineDatacard_name_mod = combineDatacard_name
    combineDatacard_name_mod = combineDatacard_name_mod.replace("@stop1_m@", str(int(stop1_m)))
    combineDatacard_name_mod = combineDatacard_name_mod.replace("@neutralino1_m@", str(int(neutralino1_m)))
    
    if (args.pseudodataSB) :
        
        combineDatacard_name_mod = combineDatacard_name_mod.replace(".txt", "_pseudodataSB.txt")
    
    elif (args.pseudodataB) :
        
        combineDatacard_name_mod = combineDatacard_name_mod.replace(".txt", "_pseudodataB.txt")
    
    # Output file name
    combineOutput_name_mod = combineOutput_name
    combineOutput_name_mod = combineOutput_name_mod.replace("@stop1_m@", str(int(stop1_m)))
    combineOutput_name_mod = combineOutput_name_mod.replace("@neutralino1_m@", str(int(neutralino1_m)))
    
    # Datacard content
    combineDatacard_content_mod = combineDatacard_content
    
    binLabels = []
    
    for iSR in range(0, nSR_merged) :
        
        if (args.cardPerBin) :
            
            d_block_data = copy.deepcopy(d_block_data_template)
            d_block_mc = copy.deepcopy(d_block_mc_template)
            d_block_statErr = copy.deepcopy(d_block_statErr_template)
            d_block_err = copy.deepcopy(d_block_err_template)
        
        binLabel = cutFlowNameBase + str(int(iSR+1))
        binLabels.append(binLabel)
        
        processIndex = -1
        
        
        d_block_data["bin"].append(binLabel)
        
        if (args.pseudodataSB) :
            
            pseudodata_val = (
                Common.replaceZero(yieldResult_nominal_sig["yield"][iSR], zeroReplacement) +
                Common.replaceZero(yieldResult_nominal_ttbar["yield"][iSR], zeroReplacement) +
                Common.replaceZero(yieldResult_nominal_DYJetsToLL["yield"][iSR], zeroReplacement) +
                Common.replaceZero(yieldResult_nominal_otherSM["yield"][iSR], zeroReplacement) +
                Common.replaceZero(yieldResult_nominal_fake["yield"][iSR], zeroReplacement)
            )
            
            d_block_data["observation"].append("%0.4e" %(pseudodata_val))
        
        elif (args.pseudodataB) :
            
            pseudodata_val = (
                Common.replaceZero(yieldResult_nominal_ttbar["yield"][iSR], zeroReplacement) +
                Common.replaceZero(yieldResult_nominal_DYJetsToLL["yield"][iSR], zeroReplacement) +
                Common.replaceZero(yieldResult_nominal_otherSM["yield"][iSR], zeroReplacement) +
                Common.replaceZero(yieldResult_nominal_fake["yield"][iSR], zeroReplacement)
            )
            
            d_block_data["observation"].append("%0.4e" %(pseudodata_val))
        
        else :
            
            d_block_data["observation"].append("%d" %(yieldResult_data["yield"][iSR]))
        
        
        # Signal
        processIndex += 1
        #d_block_mc["bin"] = "%s %s" %(d_block_mc["bin"], binLabel)
        #d_block_mc["processName"] = "%s %s" %(d_block_mc["processName"], label_sig)
        #d_block_mc["processIndex"] = "%s %s" %(d_block_mc["processIndex"], str(int(processIndex)))
        #d_block_mc["rate"] = "%s %0.4e" %(d_block_mc["rate"], Common.replaceZero(yieldResult_nominal_sig["yield"][iSR], zeroReplacement))
        #d_block_err["stat"] = "%s %0.4e" %(d_block_err["stat"], 1+Common.getRelativeError(val = yieldResult_nominal_sig["yield"][iSR], err = yieldResult_nominal_sig["error"][iSR]))
        d_block_mc["bin"].append(binLabel)
        d_block_mc["processName"].append(label_sig)
        d_block_mc["processIndex"].append(str(int(processIndex)))
        d_block_mc["rate"].append("%0.4e" %(Common.replaceZero(yieldResult_nominal_sig["yield"][iSR], zeroReplacement)))
        #d_block_err["stat"].append("%0.4e" %(1+Common.getRelativeError(val = yieldResult_nominal_sig["yield"][iSR], err = yieldResult_nominal_sig["error"][iSR])))
        
        if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
            
            d_systCombined_sig[sigKey]["stat"][iSR] = yieldResult_nominal_sig["error"][iSR]
        
        fillStatError(
            d_info = yieldResult_nominal_sig,
            d_out = d_block_statErr,
            processLabel = label_sig,
            binLabel = cutFlowNameBase,
            nProcess = nProcess,
            iProcess = processIndex,
            nBin = nSR_merged,
            iBin = iSR,
            era = era,
        )
        
        
        # ttbar
        processIndex += 1
        #d_block_mc["bin"] = "%s %s" %(d_block_mc["bin"], binLabel)
        #d_block_mc["processName"] = "%s %s" %(d_block_mc["processName"], label_ttbar)
        #d_block_mc["processIndex"] = "%s %s" %(d_block_mc["processIndex"], str(int(processIndex)))
        #d_block_mc["rate"] = "%s %0.4e" %(d_block_mc["rate"], Common.replaceZero(yieldResult_nominal_ttbar["yield"][iSR], zeroReplacement))
        #d_block_err["stat"] = "%s %0.4e" %(d_block_err["stat"], 1+Common.getRelativeError(val = yieldResult_nominal_ttbar["yield"][iSR], err = yieldResult_nominal_ttbar["error"][iSR]))
        #d_systCombined[label_ttbar]["stat"][iSR] = yieldResult_nominal_ttbar["error"][iSR]
        d_block_mc["bin"].append(binLabel)
        d_block_mc["processName"].append(label_ttbar)
        d_block_mc["processIndex"].append(str(int(processIndex)))
        d_block_mc["rate"].append("%0.4e" %(Common.replaceZero(yieldResult_nominal_ttbar["yield"][iSR], zeroReplacement)))
        #d_block_err["stat"].append("%0.4e" %(1+Common.getRelativeError(val = yieldResult_nominal_ttbar["yield"][iSR], err = yieldResult_nominal_ttbar["error"][iSR])))
        d_systCombined[label_ttbar]["stat"][iSR] = yieldResult_nominal_ttbar["error"][iSR]
        
        fillStatError(
            d_info = yieldResult_nominal_ttbar,
            d_out = d_block_statErr,
            processLabel = label_ttbar,
            binLabel = cutFlowNameBase,
            nProcess = nProcess,
            iProcess = processIndex,
            nBin = nSR_merged,
            iBin = iSR,
            era = era,
        )
        
        #if (yieldResult_nominal_ttbar["yield"][iSR] == 0) :
        #    
        #    statName = "zerostat%s_%s_%s%d" %(era, label_ttbar, cutFlowNameBase, iSR+1)
        #    d_block_err[statName] = [statName, "gmN 0"]
        #    
        #    nBefore = iSR*nProcess + processIndex
        #    nAfter = nSR_merged*nProcess - nBefore - 1
        #    
        #    d_block_err[statName].extend(["-"] * nBefore)
        #    d_block_err[statName].append("%0.4e" %(yieldResult_nominal_ttbar["scale"]))
        #    d_block_err[statName].extend(["-"] * nAfter)
        
        
        # DY
        processIndex += 1
        #d_block_mc["bin"] = "%s %s" %(d_block_mc["bin"], binLabel)
        #d_block_mc["processName"] = "%s %s" %(d_block_mc["processName"], label_DYJetsToLL)
        #d_block_mc["processIndex"] = "%s %s" %(d_block_mc["processIndex"], str(int(processIndex)))
        #d_block_mc["rate"] = "%s %0.4e" %(d_block_mc["rate"], Common.replaceZero(yieldResult_nominal_DYJetsToLL["yield"][iSR], zeroReplacement))
        #d_block_err["stat"] = "%s %0.4e" %(d_block_err["stat"], 1+Common.getRelativeError(val = yieldResult_nominal_DYJetsToLL["yield"][iSR], err = yieldResult_nominal_DYJetsToLL["error"][iSR]))
        #d_systCombined[label_DYJetsToLL]["stat"][iSR] = yieldResult_nominal_DYJetsToLL["error"][iSR]
        d_block_mc["bin"].append(binLabel)
        d_block_mc["processName"].append(label_DYJetsToLL)
        d_block_mc["processIndex"].append(str(int(processIndex)))
        d_block_mc["rate"].append("%0.4e" %(Common.replaceZero(yieldResult_nominal_DYJetsToLL["yield"][iSR], zeroReplacement)))
        #d_block_err["stat"].append("%0.4e" %(1+Common.getRelativeError(val = yieldResult_nominal_DYJetsToLL["yield"][iSR], err = yieldResult_nominal_DYJetsToLL["error"][iSR])))
        d_systCombined[label_DYJetsToLL]["stat"][iSR] = yieldResult_nominal_DYJetsToLL["error"][iSR]
        
        fillStatError(
            d_info = yieldResult_nominal_DYJetsToLL,
            d_out = d_block_statErr,
            processLabel = label_DYJetsToLL,
            binLabel = cutFlowNameBase,
            nProcess = nProcess,
            iProcess = processIndex,
            nBin = nSR_merged,
            iBin = iSR,
            era = era,
        )
        
        
        # Other SM
        processIndex += 1
        #d_block_mc["bin"] = "%s %s" %(d_block_mc["bin"], binLabel)
        #d_block_mc["processName"] = "%s %s" %(d_block_mc["processName"], label_otherSM)
        #d_block_mc["processIndex"] = "%s %s" %(d_block_mc["processIndex"], str(int(processIndex)))
        #d_block_mc["rate"] = "%s %0.4e" %(d_block_mc["rate"], Common.replaceZero(yieldResult_nominal_otherSM["yield"][iSR], zeroReplacement))
        #d_block_err["stat"] = "%s %0.4e" %(d_block_err["stat"], 1+Common.getRelativeError(val = yieldResult_nominal_otherSM["yield"][iSR], err = yieldResult_nominal_otherSM["error"][iSR]))
        #d_systCombined[label_otherSM]["stat"][iSR] = yieldResult_nominal_otherSM["error"][iSR]
        d_block_mc["bin"].append(binLabel)
        d_block_mc["processName"].append(label_otherSM)
        d_block_mc["processIndex"].append(str(int(processIndex)))
        d_block_mc["rate"].append("%0.4e" %(Common.replaceZero(yieldResult_nominal_otherSM["yield"][iSR], zeroReplacement)))
        #d_block_err["stat"].append("%0.4e" %(1+Common.getRelativeError(val = yieldResult_nominal_otherSM["yield"][iSR], err = yieldResult_nominal_otherSM["error"][iSR])))
        d_systCombined[label_otherSM]["stat"][iSR] = yieldResult_nominal_otherSM["error"][iSR]
        
        fillStatError(
            d_info = yieldResult_nominal_otherSM,
            d_out = d_block_statErr,
            processLabel = label_otherSM,
            binLabel = cutFlowNameBase,
            nProcess = nProcess,
            iProcess = processIndex,
            nBin = nSR_merged,
            iBin = iSR,
            era = era,
        )
        
        
        # Fake
        processIndex += 1
        #d_block_mc["bin"] = "%s %s" %(d_block_mc["bin"], binLabel)
        #d_block_mc["processName"] = "%s %s" %(d_block_mc["processName"], label_fake)
        #d_block_mc["processIndex"] = "%s %s" %(d_block_mc["processIndex"], str(int(processIndex)))
        #d_block_mc["rate"] = "%s %0.4e" %(d_block_mc["rate"], Common.replaceZero(yieldResult_nominal_fake["yield"][iSR], zeroReplacement))
        #d_block_err["stat"] = "%s %0.4e" %(d_block_err["stat"], 1+Common.getRelativeError(val = yieldResult_nominal_fake["yield"][iSR], err = yieldResult_nominal_fake["error"][iSR]))
        #d_systCombined[label_fake]["stat"][iSR] = yieldResult_nominal_fake["error"][iSR]
        d_block_mc["bin"].append(binLabel)
        d_block_mc["processName"].append(label_fake)
        d_block_mc["processIndex"].append(str(int(processIndex)))
        d_block_mc["rate"].append("%0.4e" %(Common.replaceZero(yieldResult_nominal_fake["yield"][iSR], zeroReplacement)))
        #d_block_err["stat"].append("%0.4e" %(1+Common.getRelativeError(val = yieldResult_nominal_fake["yield"][iSR], err = yieldResult_nominal_fake["error"][iSR])))
        d_systCombined[label_fake]["stat"][iSR] = yieldResult_nominal_fake["error"][iSR]
        
        fillStatError(
            d_info = yieldResult_nominal_fake,
            d_out = d_block_statErr,
            processLabel = label_fake,
            binLabel = cutFlowNameBase,
            nProcess = nProcess,
            iProcess = processIndex,
            nBin = nSR_merged,
            iBin = iSR,
            era = era,
            isFake = True,
        )
        
        
        for systKey in d_syst_sig :
            
            systName = getCorrStr(systKey, era, d_syst_sig[systKey]["correlated"])
            
            if (systKey not in d_block_err) :
                
                #d_block_err[systKey] = "%s %s" %(systKey, d_syst_sig[systKey]["type"])
                d_block_err[systKey] = [systName, d_syst_sig[systKey]["type"]]
                
            
            # Symmetric
            if ("syst" in d_syst_sig[systKey][label_sig]) :
                
                # Signal
                #d_block_err[systKey] = "%s %0.4e" %(d_block_err[systKey], 1+d_syst_sig[systKey][label_sig]["syst"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e" %(1+d_syst_sig[systKey][label_sig]["syst"][iSR]/100.0))
                
                if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
                    
                    err = yieldResult_nominal_sig["yield"][iSR]*d_syst_sig[systKey][label_sig]["syst"][iSR]/100.0
                    
                    d_systCombined_sig[sigKey]["syst"][iSR].append(err)
                    d_systCombined_sig[sigKey]["syst"][iSR].append(-err)
            
            # Asymmetric
            else :
                
                #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_sig[systKey][label_sig]["systDown"][iSR]/100.0, 1+d_syst_sig[systKey][label_sig]["systUp"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_sig[systKey][label_sig]["systDown"][iSR]/100.0, 1+d_syst_sig[systKey][label_sig]["systUp"][iSR]/100.0))
                
                if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
                    
                    errUp = yieldResult_nominal_sig["yield"][iSR]*d_syst_sig[systKey][label_sig]["systUp"][iSR]/100.0
                    errDown = yieldResult_nominal_sig["yield"][iSR]*d_syst_sig[systKey][label_sig]["systDown"][iSR]/100.0
                    
                    d_systCombined_sig[sigKey]["syst"][iSR].append(errUp)
                    d_systCombined_sig[sigKey]["syst"][iSR].append(errDown)
            
            # ttbar
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # DY
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # Other SM
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # Fake
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
        
        
        for systKey in d_syst_commonMC :
            
            systName = getCorrStr(systKey, era, d_syst_commonMC[systKey]["correlated"])
            
            if (systKey not in d_block_err) :
                
                #d_block_err[systKey] = "%s %s" %(systKey, d_syst_commonMC[systKey]["type"])
                d_block_err[systKey] = [systName, d_syst_commonMC[systKey]["type"]]
            
            # Symmetric
            if ("syst" in d_syst_commonMC[systKey][label_DYJetsToLL]) :
                
                # Signal
                if (systKey not in l_syst_sig_toExclude) :
                    
                    #d_block_err[systKey] = "%s %0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_sig]["syst"][iSR]/100.0)
                    d_block_err[systKey].append("%0.4e" %(1+d_syst_commonMC[systKey][label_sig]["syst"][iSR]/100.0))
                    
                    if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
                        
                        err = yieldResult_nominal_sig["yield"][iSR]*d_syst_commonMC[systKey][label_sig]["syst"][iSR]/100.0
                        
                        d_systCombined_sig[sigKey]["syst"][iSR].append(err)
                        d_systCombined_sig[sigKey]["syst"][iSR].append(-err)
                
                else :
                    
                    d_block_err[systKey].append("-")
                
                # ttbar
                if (systKey in l_syst_ttbar_toInclude) :
                    
                    #d_block_err[systKey] = "%s %0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_ttbar]["syst"][iSR]/100.0)
                    d_block_err[systKey].append("%0.4e" %(1+d_syst_commonMC[systKey][label_ttbar]["syst"][iSR]/100.0))
                    
                    if (iMass == 0) :
                        
                        err = yieldResult_nominal_ttbar["yield"][iSR]*d_syst_commonMC[systKey][label_ttbar]["syst"][iSR]/100.0
                        
                        d_systCombined[label_ttbar]["syst"][iSR].append(err)
                        d_systCombined[label_ttbar]["syst"][iSR].append(-err)
                
                else :
                    
                    #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
                    d_block_err[systKey].append("-")
                
                # DY
                #d_block_err[systKey] = "%s %0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_DYJetsToLL]["syst"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e" %(1+d_syst_commonMC[systKey][label_DYJetsToLL]["syst"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    err = yieldResult_nominal_DYJetsToLL["yield"][iSR]*d_syst_commonMC[systKey][label_DYJetsToLL]["syst"][iSR]/100.0
                    
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(err)
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(-err)
                
                # Other SM
                #d_block_err[systKey] = "%s %0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_otherSM]["syst"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e" %(1+d_syst_commonMC[systKey][label_otherSM]["syst"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    err = yieldResult_nominal_otherSM["yield"][iSR]*d_syst_commonMC[systKey][label_otherSM]["syst"][iSR]/100.0
                    
                    d_systCombined[label_otherSM]["syst"][iSR].append(err)
                    d_systCombined[label_otherSM]["syst"][iSR].append(-err)
            
            # Asymmetric
            else :
                
                # Signal
                #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_sig]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_sig]["systUp"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_commonMC[systKey][label_sig]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_sig]["systUp"][iSR]/100.0))
                
                if (systKey not in l_syst_sig_toExclude) :
                    
                    if ([int(stop1_m), int(neutralino1_m)] in l_massPointYieldHist) :
                        
                        errUp = yieldResult_nominal_sig["yield"][iSR]*d_syst_commonMC[systKey][label_sig]["systUp"][iSR]/100.0
                        errDown = yieldResult_nominal_sig["yield"][iSR]*d_syst_commonMC[systKey][label_sig]["systDown"][iSR]/100.0
                        
                        d_systCombined_sig[sigKey]["syst"][iSR].append(errUp)
                        d_systCombined_sig[sigKey]["syst"][iSR].append(errDown)
                
                else :
                    
                    d_block_err[systKey].append("-")
                
                # ttbar
                if (systKey in l_syst_ttbar_toInclude) :
                    
                    #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_ttbar]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_ttbar]["systUp"][iSR]/100.0)
                    d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_commonMC[systKey][label_ttbar]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_ttbar]["systUp"][iSR]/100.0))
                    
                    if (iMass == 0) :
                        
                        errUp = yieldResult_nominal_ttbar["yield"][iSR]*d_syst_commonMC[systKey][label_ttbar]["systUp"][iSR]/100.0
                        errDown = yieldResult_nominal_ttbar["yield"][iSR]*d_syst_commonMC[systKey][label_ttbar]["systDown"][iSR]/100.0
                        
                        d_systCombined[label_ttbar]["syst"][iSR].append(errUp)
                        d_systCombined[label_ttbar]["syst"][iSR].append(errDown)
                
                else :
                    
                    #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
                    d_block_err[systKey].append("-")
                
                # DY
                #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_DYJetsToLL]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_DYJetsToLL]["systUp"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_commonMC[systKey][label_DYJetsToLL]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_DYJetsToLL]["systUp"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    errUp = yieldResult_nominal_DYJetsToLL["yield"][iSR]*d_syst_commonMC[systKey][label_DYJetsToLL]["systUp"][iSR]/100.0
                    errDown = yieldResult_nominal_DYJetsToLL["yield"][iSR]*d_syst_commonMC[systKey][label_DYJetsToLL]["systDown"][iSR]/100.0
                    
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(errUp)
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(errDown)
                
                # Other SM
                #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_commonMC[systKey][label_otherSM]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_otherSM]["systUp"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_commonMC[systKey][label_otherSM]["systDown"][iSR]/100.0, 1+d_syst_commonMC[systKey][label_otherSM]["systUp"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    errUp = yieldResult_nominal_otherSM["yield"][iSR]*d_syst_commonMC[systKey][label_otherSM]["systUp"][iSR]/100.0
                    errDown = yieldResult_nominal_otherSM["yield"][iSR]*d_syst_commonMC[systKey][label_otherSM]["systDown"][iSR]/100.0
                    
                    d_systCombined[label_otherSM]["syst"][iSR].append(errUp)
                    d_systCombined[label_otherSM]["syst"][iSR].append(errDown)
            
            # Fake
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
        
        
        for systKey in d_syst_ttbar :
            
            systName = getCorrStr(systKey, era, d_syst_ttbar[systKey]["correlated"])
            
            if (systKey not in d_block_err) :
                
                #print d_syst_ttbar
                #print d_syst_ttbar[systKey]["type"]
                
                #d_block_err[systKey] = "%s %s" %(systKey, d_syst_ttbar[systKey]["type"])
                d_block_err[systKey] = [systName, d_syst_ttbar[systKey]["type"]]
            
            # Signal
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # ttbar
            if ("syst" in d_syst_ttbar[systKey][label_ttbar]) :
                
                #d_block_err[systKey] = "%s %0.4e" %(d_block_err[systKey], 1+d_syst_ttbar[systKey][label_ttbar]["syst"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e" %(1+d_syst_ttbar[systKey][label_ttbar]["syst"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    err = yieldResult_nominal_ttbar["yield"][iSR]*d_syst_ttbar[systKey][label_ttbar]["syst"][iSR]/100.0
                    
                    d_systCombined[label_ttbar]["syst"][iSR].append(err)
                    d_systCombined[label_ttbar]["syst"][iSR].append(-err)
            
            else :
                
                #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_ttbar[systKey][label_ttbar]["systDown"][iSR]/100.0, 1+d_syst_ttbar[systKey][label_ttbar]["systUp"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_ttbar[systKey][label_ttbar]["systDown"][iSR]/100.0, 1+d_syst_ttbar[systKey][label_ttbar]["systUp"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    errUp = yieldResult_nominal_ttbar["yield"][iSR]*d_syst_ttbar[systKey][label_ttbar]["systUp"][iSR]/100.0
                    errDown = yieldResult_nominal_ttbar["yield"][iSR]*d_syst_ttbar[systKey][label_ttbar]["systDown"][iSR]/100.0
                    
                    d_systCombined[label_ttbar]["syst"][iSR].append(errUp)
                    d_systCombined[label_ttbar]["syst"][iSR].append(errDown)
            
            # DY
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # Other SM
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # Fake
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
        
        
        for systKey in d_syst_DY :
            
            systName = getCorrStr(systKey, era, d_syst_DY[systKey]["correlated"])
            
            if (systKey not in d_block_err) :
                
                #print d_syst_DY
                #print d_syst_DY[systKey]["type"]
                
                #d_block_err[systKey] = "%s %s" %(systKey, d_syst_DY[systKey]["type"])
                d_block_err[systKey] = [systName, d_syst_DY[systKey]["type"]]
            
            # Signal
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # ttbar
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # DY
            if ("syst" in d_syst_DY[systKey][label_DYJetsToLL]) :
                
                #d_block_err[systKey] = "%s %0.4e" %(d_block_err[systKey], 1+d_syst_DY[systKey][label_DYJetsToLL]["syst"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e" %(1+d_syst_DY[systKey][label_DYJetsToLL]["syst"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    err = yieldResult_nominal_DYJetsToLL["yield"][iSR]*d_syst_DY[systKey][label_DYJetsToLL]["syst"][iSR]/100.0
                    
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(err)
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(-err)
            
            else :
                
                #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_DY[systKey][label_DYJetsToLL]["systDown"][iSR]/100.0, 1+d_syst_DY[systKey][label_DYJetsToLL]["systUp"][iSR]/100.0)
                d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_DY[systKey][label_DYJetsToLL]["systDown"][iSR]/100.0, 1+d_syst_DY[systKey][label_DYJetsToLL]["systUp"][iSR]/100.0))
                
                if (iMass == 0) :
                    
                    errUp = yieldResult_nominal_DYJetsToLL["yield"][iSR]*d_syst_DY[systKey][label_DYJetsToLL]["systUp"][iSR]/100.0
                    errDown = yieldResult_nominal_DYJetsToLL["yield"][iSR]*d_syst_DY[systKey][label_DYJetsToLL]["systDown"][iSR]/100.0
                    
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(errUp)
                    d_systCombined[label_DYJetsToLL]["syst"][iSR].append(errDown)
            
            
            # Other SM
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # Fake
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
        
        
        for systKey in d_syst_fake :
            
            systName = getCorrStr(systKey, era, d_syst_fake[systKey]["correlated"])
            
            if (systKey not in d_block_err) :
                
                #d_block_err[systKey] = "%s %s" %(systKey, d_syst_fake[systKey]["type"])
                d_block_err[systKey] = [systName, d_syst_fake[systKey]["type"]]
            
            # Signal
            #d_block_err[systKey] = "%s %s" %(d_block_err[systKey], "-")
            d_block_err[systKey].append("-")
            
            # ttbar
            d_block_err[systKey].append("-")
            
            # DY
            d_block_err[systKey].append("-")
            
            # Other SM
            d_block_err[systKey].append("-")
            
            # Fake
            #d_block_err[systKey] = "%s %0.4e/%0.4e" %(d_block_err[systKey], 1+d_syst_fake[systKey][label_fake]["systDown"][iSR]/100.0, 1+d_syst_fake[systKey][label_fake]["systUp"][iSR]/100.0)
            d_block_err[systKey].append("%0.4e/%0.4e" %(1+d_syst_fake[systKey][label_fake]["systDown"][iSR]/100.0, 1+d_syst_fake[systKey][label_fake]["systUp"][iSR]/100.0))
            
            if (iMass == 0) :
                
                errUp = yieldResult_nominal_fake["yield"][iSR]*d_syst_fake[systKey][label_fake]["systUp"][iSR]/100.0
                errDown = yieldResult_nominal_fake["yield"][iSR]*d_syst_fake[systKey][label_fake]["systDown"][iSR]/100.0
                
                d_systCombined[label_fake]["syst"][iSR].append(errUp)
                d_systCombined[label_fake]["syst"][iSR].append(errDown)
        
        
        # Card per bin
        #if (args.cardPerBin) :
        #    
        #    xxx
    
    outFileName = "%s/%s" %(combineOutputDir, combineDatacard_name_mod)
    
    if (args.card) :
        
        writeCard(
            combineDatacard_content = combineDatacard_content_mod,
            era = era,
            outFileName = outFileName,
            d_block_data = d_block_data,
            d_block_mc = d_block_mc,
            d_block_err = d_block_err,
            d_block_statErr = d_block_statErr,
        )


if (args.syst) :
    
    l_systTable = []
    l_systTable_range = []
    
    
    # Signal specific
    for systKey in d_syst_sig :
        
        l_systRow = []
        l_systRow_range = []
        
        l_systRow.append(d_syst_sig[systKey]["latexTitle"])
        l_systRow_range.append(d_syst_sig[systKey]["latexTitle"])
        
        # Symmetric
        if ("syst_mean" in d_syst_sig[systKey][label_sig]) :
            
            for iSig in range(0, len(l_massPointYieldHist)) :
                
                key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
                
                print systKey, label_sig, d_massPointSystTable[key][systKey]["syst_mean"]
                l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_massPointSystTable[key][systKey]["syst_mean"]))
                
                l_syst_temp = copy.deepcopy(d_massPointSystTable[key][systKey]["syst"])
                l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
                
                if (min(l_syst_temp) == max(l_syst_temp)) :
                    
                    l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
                
                else :
                    
                    l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
        
        # Asymmetric
        else :
            
            for iSig in range(0, len(l_massPointYieldHist)) :
                
                key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
                
                print systKey, label_sig, d_massPointSystTable[key][systKey]["systUp_mean"], d_massPointSystTable[key][systKey]["systDown_mean"]
                #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_massPointSystTable[key][systKey]["systUp_mean"], d_massPointSystTable[key][systKey]["systDown_mean"]))
                l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_massPointSystTable[key][systKey]["systUp_mean"], d_massPointSystTable[key][systKey]["systDown_mean"]))
                
                l_syst_temp = copy.deepcopy(d_massPointSystTable[key][systKey]["systUp"] + d_massPointSystTable[key][systKey]["systDown"])
                l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
                
                if (min(l_syst_temp) == max(l_syst_temp)) :
                    
                    l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
                
                else :
                    
                    l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
        
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        
        print "\n"
        
        
        l_systTable.append(l_systRow)
        l_systTable_range.append(l_systRow_range)
    
    
    # Common
    for systKey in d_syst_commonMC :
        
        l_systRow = []
        l_systRow_range = []
        
        l_systRow.append(d_syst_commonMC[systKey]["latexTitle"])
        l_systRow_range.append(d_syst_commonMC[systKey]["latexTitle"])
        
        # Symmetric
        if ("syst_mean" in d_syst_commonMC[systKey][label_DYJetsToLL]) :
            
            # Signal
            for iSig in range(0, len(l_massPointYieldHist)) :
                
                key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
                
                if (systKey not in l_syst_sig_toExclude) :
                    
                    print systKey, label_ttbar, d_massPointSystTable[key][systKey]["syst_mean"]
                    l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_massPointSystTable[key][systKey]["syst_mean"]))
                    
                    l_syst_temp = copy.deepcopy(d_massPointSystTable[key][systKey]["syst"])
                    l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
                    
                    if (min(l_syst_temp) == max(l_syst_temp)) :
                        
                        l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
                    
                    else :
                        
                        l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
                
                else :
                    
                    l_systRow.append(r"\NA")
                    l_systRow_range.append(r"\NA")
            
            
            # ttbar
            if (systKey in l_syst_ttbar_toInclude) :
                
                print systKey, label_ttbar, d_syst_commonMC[systKey][label_ttbar]["syst_mean"]
                l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_syst_commonMC[systKey][label_ttbar]["syst_mean"]))
                
                l_syst_temp = copy.deepcopy(d_syst_commonMC[systKey][label_ttbar]["syst"])
                l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
                
                if (min(l_syst_temp) == max(l_syst_temp)) :
                    
                    l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
                
                else :
                    
                    l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
            else :
                
                l_systRow.append(r"\NA")
                l_systRow_range.append(r"\NA")
            
            
            # DY
            print systKey, label_DYJetsToLL, d_syst_commonMC[systKey][label_DYJetsToLL]["syst_mean"]
            l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_syst_commonMC[systKey][label_DYJetsToLL]["syst_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_commonMC[systKey][label_DYJetsToLL]["syst"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
            
            # Other SM
            print systKey, label_otherSM, d_syst_commonMC[systKey][label_otherSM]["syst_mean"]
            l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_syst_commonMC[systKey][label_otherSM]["syst_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_commonMC[systKey][label_otherSM]["syst"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
        
        # Asymmetric
        else :
            
            # Signal
            for iSig in range(0, len(l_massPointYieldHist)) :
                
                key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
                
                if (systKey not in l_syst_sig_toExclude) :
                    
                    print systKey, label_sig, d_massPointSystTable[key][systKey]["systUp_mean"], d_massPointSystTable[key][systKey]["systDown_mean"]
                    #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_massPointSystTable[key][systKey]["systUp_mean"], d_massPointSystTable[key][systKey]["systDown_mean"]))
                    l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_massPointSystTable[key][systKey]["systUp_mean"], d_massPointSystTable[key][systKey]["systDown_mean"]))
                    
                    l_syst_temp = copy.deepcopy(d_massPointSystTable[key][systKey]["systUp"] + d_massPointSystTable[key][systKey]["systDown"])
                    l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
                    
                    if (min(l_syst_temp) == max(l_syst_temp)) :
                        
                        l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
                    
                    else :
                        
                        l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
                
                else :
                    
                    l_systRow.append(r"\NA")
                    l_systRow_range.append(r"\NA")
            
            
            # ttbar
            if (systKey in l_syst_ttbar_toInclude) :
                
                print systKey, label_ttbar, d_syst_commonMC[systKey][label_ttbar]["systUp_mean"], d_syst_commonMC[systKey][label_ttbar]["systDown_mean"]
                #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_syst_commonMC[systKey][label_ttbar]["systUp_mean"], d_syst_commonMC[systKey][label_ttbar]["systDown_mean"]))
                l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_syst_commonMC[systKey][label_ttbar]["systUp_mean"], d_syst_commonMC[systKey][label_ttbar]["systDown_mean"]))
                
                l_syst_temp = copy.deepcopy(d_syst_commonMC[systKey][label_ttbar]["systUp"] + d_syst_commonMC[systKey][label_ttbar]["systDown"])
                l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
                
                if (min(l_syst_temp) == max(l_syst_temp)) :
                    
                    l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
                
                else :
                    
                    l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
            else :
                
                l_systRow.append(r"\NA")
                l_systRow_range.append(r"\NA")
            
            
            # DY
            print systKey, label_DYJetsToLL, d_syst_commonMC[systKey][label_DYJetsToLL]["systUp_mean"], d_syst_commonMC[systKey][label_DYJetsToLL]["systDown_mean"]
            #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_syst_commonMC[systKey][label_DYJetsToLL]["systUp_mean"], d_syst_commonMC[systKey][label_DYJetsToLL]["systDown_mean"]))
            l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_syst_commonMC[systKey][label_DYJetsToLL]["systUp_mean"], d_syst_commonMC[systKey][label_DYJetsToLL]["systDown_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_commonMC[systKey][label_DYJetsToLL]["systUp"] + d_syst_commonMC[systKey][label_DYJetsToLL]["systDown"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
            
            # Other SM
            print systKey, label_otherSM, d_syst_commonMC[systKey][label_otherSM]["systUp_mean"], d_syst_commonMC[systKey][label_otherSM]["systDown_mean"]
            #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_syst_commonMC[systKey][label_otherSM]["systUp_mean"], d_syst_commonMC[systKey][label_otherSM]["systDown_mean"]))
            l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_syst_commonMC[systKey][label_otherSM]["systUp_mean"], d_syst_commonMC[systKey][label_otherSM]["systDown_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_commonMC[systKey][label_otherSM]["systUp"] + d_syst_commonMC[systKey][label_otherSM]["systDown"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
            
        
        # Fake
        l_systRow.append(r"\NA")
        l_systRow_range.append(r"\NA")
        
        print "\n"
        
        
        l_systTable.append(l_systRow)
        l_systTable_range.append(l_systRow_range)
    
    
    # ttbar
    for systKey in d_syst_ttbar :
        
        l_systRow = []
        l_systRow_range = []
        
        l_systRow.append(d_syst_ttbar[systKey]["latexTitle"])
        l_systRow_range.append(d_syst_ttbar[systKey]["latexTitle"])
        
        for iSig in range(0, len(l_massPointYieldHist)) :
            
            l_systRow.append(r"\NA")
            l_systRow_range.append(r"\NA")
        
        # Symmetric
        if ("syst_mean" in d_syst_ttbar[systKey][label_ttbar]) :
            
            print systKey, label_ttbar, d_syst_ttbar[systKey][label_ttbar]["syst_mean"]
            l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_syst_ttbar[systKey][label_ttbar]["syst_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_ttbar[systKey][label_ttbar]["syst"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
        
        # Asymmetric
        else :
            
            print systKey, label_ttbar, d_syst_ttbar[systKey][label_ttbar]["systUp_mean"], d_syst_ttbar[systKey][label_ttbar]["systDown_mean"]
            #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_syst_ttbar[systKey][label_ttbar]["systUp_mean"], d_syst_ttbar[systKey][label_ttbar]["systDown_mean"]))
            l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_syst_ttbar[systKey][label_ttbar]["systUp_mean"], d_syst_ttbar[systKey][label_ttbar]["systDown_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_ttbar[systKey][label_ttbar]["systUp"] + d_syst_ttbar[systKey][label_ttbar]["systDown"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
        
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        
        print "\n"
        
        
        l_systTable.append(l_systRow)
        l_systTable_range.append(l_systRow_range)
    
    
    # DY
    for systKey in d_syst_DY :
        
        l_systRow = []
        l_systRow_range = []
        
        l_systRow.append(d_syst_DY[systKey]["latexTitle"])
        l_systRow_range.append(d_syst_DY[systKey]["latexTitle"])
        
        for iSig in range(0, len(l_massPointYieldHist)) :
            
            l_systRow.append(r"\NA")
            l_systRow_range.append(r"\NA")
        
        l_systRow.append(r"\NA")
        l_systRow_range.append(r"\NA")
        
        # Symmetric
        if ("syst_mean" in d_syst_DY[systKey][label_DYJetsToLL]) :
            
            print systKey, label_DYJetsToLL, d_syst_DY[systKey][label_DYJetsToLL]["syst_mean"]
            l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_syst_DY[systKey][label_DYJetsToLL]["syst_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_DY[systKey][label_DYJetsToLL]["syst"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
        
        # Asymmetric
        else :
            
            print systKey, label_DYJetsToLL, d_syst_DY[systKey][label_DYJetsToLL]["systUp_mean"], d_syst_DY[systKey][label_DYJetsToLL]["systDown_mean"]
            #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_syst_DY[systKey][label_DYJetsToLL]["systUp_mean"], d_syst_DY[systKey][label_DYJetsToLL]["systDown_mean"]))
            l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_syst_DY[systKey][label_DYJetsToLL]["systUp_mean"], d_syst_DY[systKey][label_DYJetsToLL]["systDown_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_DY[systKey][label_DYJetsToLL]["systUp"] + d_syst_DY[systKey][label_DYJetsToLL]["systDown"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
        
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        
        print "\n"
        
        
        l_systTable.append(l_systRow)
        l_systTable_range.append(l_systRow_range)
    
    
    # Fake
    for systKey in d_syst_fake :
        
        l_systRow = []
        l_systRow_range = []
        
        l_systRow.append(d_syst_fake[systKey]["latexTitle"])
        l_systRow_range.append(d_syst_fake[systKey]["latexTitle"])
        
        for iSig in range(0, len(l_massPointYieldHist)) :
            
            l_systRow.append(r"\NA")
            l_systRow_range.append(r"\NA")
        
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        l_systRow.append(r"\NA")
        
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        l_systRow_range.append(r"\NA")
        
        # Symmetric
        if ("syst_mean" in d_syst_fake[systKey][label_fake]) :
            
            print systKey, label_fake, d_syst_fake[systKey][label_fake]["syst_mean"]
            l_systRow.append(r"$ \pm %0.2f \ \%% $" %(d_syst_fake[systKey][label_fake]["syst_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_fake[systKey][label_fake]["syst"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
        
        # Asymmetric
        else :
            
            print systKey, label_fake, d_syst_fake[systKey][label_fake]["systUp_mean"], d_syst_fake[systKey][label_fake]["systDown_mean"]
            #l_systRow.append(r"$ %0.2f, \ %0.2f \ \%% $" %(d_syst_fake[systKey][label_fake]["systUp_mean"], d_syst_fake[systKey][label_fake]["systDown_mean"]))
            l_systRow.append(r"\vtop{\hbox{\strut $ %+0.2f \ \%% $}\hbox{\strut $ %+0.2f \ \%% $}}" %(d_syst_fake[systKey][label_fake]["systUp_mean"], d_syst_fake[systKey][label_fake]["systDown_mean"]))
            
            l_syst_temp = copy.deepcopy(d_syst_fake[systKey][label_fake]["systUp"] + d_syst_fake[systKey][label_fake]["systDown"])
            l_syst_temp = [abs(ele) for ele in l_syst_temp if (abs(ele) > 0)]
            
            if (min(l_syst_temp) == max(l_syst_temp)) :
                
                l_systRow_range.append(r"$ %0.2f \ \%% $" %(min(l_syst_temp)))
            
            else :
                
                l_systRow_range.append(r"$ %0.2f \ \text{-} \ %0.2f \ \%% $" %(min(l_syst_temp), max(l_syst_temp)))
        
        print "\n"
        
        
        l_systTable.append(l_systRow)
        l_systTable_range.append(l_systRow_range)
    
    
    l_header = ["Uncertainty source"]
    #l_header += [r"$ x=%s, [%d, %d] $" %(sig_x_str, key[0], key[1]) for key in l_massPointYieldHist]
    l_header += [r"\vtop{\hbox{\strut $ x=%s $}\hbox{\strut $ [%d, %d] $}}" %(sig_x_str, key[0], key[1]) for key in l_massPointYieldHist]
    l_header += [r"$ t \overline{t} $", "DY+jets", "Other SM", "Fake"]
    
    systTableStr = tabulate.tabulate(
        l_systTable,
        headers = l_header
    )
    
    print systTableStr
    
    
    # Average (weighted) uncertainty table
    systTableLatex = Array2LatexTable.array2LatexTable(
        [l_header] + l_systTable,
        isColumnTitled = True,
        centerTable = True,
        table_caption = "Average uncertainties for %s." %(era),
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
        d_line_break = {"vtop": r"\\[\cmsTabSkipLarge]"},
        adjustBox = False,
    )
    
    systTableDir = "systematicsTables/%s" %(era)
    os.system("mkdir -p %s" %(systTableDir))
    
    systTableFile = "%s/systTable_%s_tex.txt" %(systTableDir, sig_x_str_fileName)
    
    print "\n"
    print "Writing: %s" %(systTableFile)
    print "\n"
    
    with open(systTableFile, "w") as f :
        
        f.write(systTableLatex)
    
    
    # Uncertainty range table
    systTableLatex_range = Array2LatexTable.array2LatexTable(
        [l_header] + l_systTable_range,
        isColumnTitled = True,
        centerTable = True,
        table_caption = "Uncertainty ranges for %s." %(era),
        table_label = "",
        table_width = 1,
        columnColorDict = {},
        columnHorOrientDict = {0: "l"}
    )
    
    systTableDir = "systematicsTables/%s" %(era)
    os.system("mkdir -p %s" %(systTableDir))
    
    systTableFile_range = "%s/systTable_range_%s_tex.txt" %(systTableDir, sig_x_str_fileName)
    
    print "\n"
    print "Writing: %s" %(systTableFile_range)
    print "\n"
    
    with open(systTableFile_range, "w") as f :
        
        f.write(systTableLatex_range)


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
    
    for iSR in range(0, nSR_merged) :
        
        l_row = []
        l_header = []
        
        l_row_sig = []
        l_header_sig = []
        
        l_header.append("SR bin")
        l_row.append("%d" %(iSR+1))
        
        l_header_sig.append("SR bin")
        l_row_sig.append("%d" %(iSR+1))
        
        
        # Prediction
        allSM = yieldResult_nominal_ttbar["yield"][iSR] + yieldResult_nominal_DYJetsToLL["yield"][iSR] + yieldResult_nominal_otherSM["yield"][iSR] + yieldResult_nominal_fake["yield"][iSR]
        
        
        # ttbar
        statSign = "+" if (yieldResult_nominal_ttbar["yield"][iSR] == 0) else "\pm"
        
        l_header.append(r"$ \ttbar $")
        
        yieldStr = ""
        
        if (yieldResult_nominal_ttbar["yield"][iSR] == 0) :
            
            #yieldStr = r"$ < %0.2f \ (0 \ \%%) $" %(
            yieldStr = r"\begin{tabular}[t]{c} $ < %0.2f $ \\ ($ 0 \ \%% $) \end{tabular}" %(
                d_systCombined[label_ttbar]["stat"][iSR]
            )
        
        else :
            
            #yieldStr = r"$ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} \ (%d \ \%%) $" %(
            #yieldStr = r"\vtop{\hbox{\strut $ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} $}\hbox{\strut ($ %d \ \%% $)}}" %(
            yieldStr = r"\begin{tabular}[t]{c} $ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} $ \\ ($ %d \ \%% $) \end{tabular}" %(
                yieldResult_nominal_ttbar["yield"][iSR],
                statSign,
                d_systCombined[label_ttbar]["stat"][iSR],
                Common.getCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = +1),
                Common.getCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = -1),
                round(yieldResult_nominal_ttbar["yield"][iSR] / allSM * 100.0)
            )
        
        l_row.append(yieldStr)
        
        l_bkg_yield[0] += yieldResult_nominal_ttbar["yield"][iSR]
        l_bkg_statErr[0] += d_systCombined[label_ttbar]["stat"][iSR]**2
        l_bkg_statErrPos[0] += d_systCombined[label_ttbar]["stat"][iSR]**2
        l_bkg_statErrNeg[0] += d_systCombined[label_ttbar]["stat"][iSR]**2 * (abs(yieldResult_nominal_ttbar["yield"][iSR]) > 0)
        l_bkg_systErrPos[0] += Common.getCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = +1)**2
        l_bkg_systErrNeg[0] += Common.getCombinedError(d_systCombined[label_ttbar]["syst"][iSR], sign = -1)**2
        
        
        # DY
        statSign = "+" if (yieldResult_nominal_DYJetsToLL["yield"][iSR] == 0) else "\pm"
        
        l_header.append(r"DY+jets")
        
        yieldStr = ""
        
        if (yieldResult_nominal_DYJetsToLL["yield"][iSR] == 0) :
            
            #yieldStr = r"$ < %0.2f \ (0 \ \%%) $" %(
            yieldStr = r"\begin{tabular}[t]{c} $ < %0.2f $ \\ ($ 0 \ \%% $) \end{tabular}" %(
                d_systCombined[label_DYJetsToLL]["stat"][iSR]
            )
        
        else :
            
            #yieldStr = r"$ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} \ (%d \ \%%) $" %(
            #yieldStr = r"\vtop{\hbox{\strut $ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} $}\hbox{\strut ($ %d \ \%% $)}}" %(
            yieldStr = r"\begin{tabular}[t]{c} $ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} $ \\ ($ %d \ \%% $) \end{tabular}" %(
                yieldResult_nominal_DYJetsToLL["yield"][iSR],
                statSign,
                d_systCombined[label_DYJetsToLL]["stat"][iSR],
                Common.getCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = +1),
                Common.getCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = -1),
                round(yieldResult_nominal_DYJetsToLL["yield"][iSR] / allSM * 100.0)
            )
        
        l_row.append(yieldStr)
        
        l_bkg_yield[1] += yieldResult_nominal_DYJetsToLL["yield"][iSR]
        l_bkg_statErr[1] += d_systCombined[label_DYJetsToLL]["stat"][iSR]**2
        l_bkg_statErrPos[1] += d_systCombined[label_DYJetsToLL]["stat"][iSR]**2
        l_bkg_statErrNeg[1] += d_systCombined[label_DYJetsToLL]["stat"][iSR]**2 * (abs(yieldResult_nominal_DYJetsToLL["yield"][iSR]) > 0)
        l_bkg_systErrPos[1] += Common.getCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = +1)**2
        l_bkg_systErrNeg[1] += Common.getCombinedError(d_systCombined[label_DYJetsToLL]["syst"][iSR], sign = -1)**2
        
        
        # Other SM
        statSign = "+" if (yieldResult_nominal_otherSM["yield"][iSR] == 0) else "\pm"
        
        l_header.append(r"Other SM")
        
        yieldStr = ""
        
        if (yieldResult_nominal_otherSM["yield"][iSR]  == 0) :
            
            #yieldStr = r"$ < %0.2f \ (0 \ \%%) $" %(
            yieldStr = r"\begin{tabular}[t]{c} $ < %0.2f $ \\ ($ 0 \ \%% $) \end{tabular}" %(
                d_systCombined[label_otherSM]["stat"][iSR]
            )
        
        else :
            
            #yieldStr = r"$ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} \ (%d \ \%%) $" %(
            #yieldStr = r"\vtop{\hbox{\strut $ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} $}\hbox{\strut ($ %d \ \%% $)}}" %(
            yieldStr = r"\begin{tabular}[t]{c} $ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} $ \\ ($ %d \ \%% $) \end{tabular}" %(
                yieldResult_nominal_otherSM["yield"][iSR],
                statSign,
                d_systCombined[label_otherSM]["stat"][iSR],
                Common.getCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = +1),
                Common.getCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = -1),
                round(yieldResult_nominal_otherSM["yield"][iSR] / allSM * 100.0)
            )
        
        l_row.append(yieldStr)
        
        l_bkg_yield[2] += yieldResult_nominal_otherSM["yield"][iSR]
        l_bkg_statErr[2] += d_systCombined[label_otherSM]["stat"][iSR]**2
        l_bkg_statErrPos[2] += d_systCombined[label_otherSM]["stat"][iSR]**2
        l_bkg_statErrNeg[2] += d_systCombined[label_otherSM]["stat"][iSR]**2 * (abs(yieldResult_nominal_otherSM["yield"][iSR]) > 0)
        l_bkg_systErrPos[2] += Common.getCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = +1)**2
        l_bkg_systErrNeg[2] += Common.getCombinedError(d_systCombined[label_otherSM]["syst"][iSR], sign = -1)**2
        
        
        # Fake
        l_header.append(r"Fake")
        
        yieldStr = ""
        
        if (yieldResult_nominal_fake["yield"][iSR] == 0) :
            
            yieldStr = r"\begin{tabular}[t]{c} $ %0.2f $ \\ ($ 0 \ \%% $) \end{tabular}" %(d_systCombined[label_fake]["stat"][iSR])
        
        else :
            
            #yieldStr = r"$ %0.2f \pm %0.2f ^{+%0.2f} _{-%0.2f} \ (%d \ \%%) $" %(
            #yieldStr = r"\vtop{\hbox{\strut $ %0.2f \pm %0.2f ^{+%0.2f} _{-%0.2f} $}\hbox{\strut ($ %d \ \%% $)}}" %(
            yieldStr = r"\begin{tabular}[t]{c} $ %0.2f \pm %0.2f ^{+%0.2f} _{-%0.2f} $ \\ ($ %d \ \%% $) \end{tabular}" %(
                yieldResult_nominal_fake["yield"][iSR],
                d_systCombined[label_fake]["stat"][iSR],
                Common.getCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = +1),
                Common.getCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = -1),
                round(yieldResult_nominal_fake["yield"][iSR] / allSM * 100.0)
            )
        
        l_row.append(yieldStr)
        
        l_bkg_yield[3] += yieldResult_nominal_fake["yield"][iSR]
        l_bkg_statErr[3] += d_systCombined[label_fake]["stat"][iSR]**2
        l_bkg_statErrPos[3] += d_systCombined[label_fake]["stat"][iSR]**2
        l_bkg_statErrNeg[3] += d_systCombined[label_fake]["stat"][iSR]**2 * (abs(yieldResult_nominal_fake["yield"][iSR]) > 0)
        l_bkg_systErrPos[3] += Common.getCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = +1)**2
        l_bkg_systErrNeg[3] += Common.getCombinedError(d_systCombined[label_fake]["syst"][iSR], sign = -1)**2
        
        
        #####
        allSM_stat = Common.getCombinedError([
            d_systCombined[label_ttbar]["stat"][iSR],
            d_systCombined[label_DYJetsToLL]["stat"][iSR],
            d_systCombined[label_otherSM]["stat"][iSR],
            d_systCombined[label_fake]["stat"][iSR],
        ])
        
        allSM_statPos = Common.getCombinedError([
            d_systCombined[label_ttbar]["stat"][iSR],
            d_systCombined[label_DYJetsToLL]["stat"][iSR],
            d_systCombined[label_otherSM]["stat"][iSR],
            d_systCombined[label_fake]["stat"][iSR],
        ])
        
        # Do not add the one sided stat errors for the zero bins to the negative error
        allSM_statNeg = Common.getCombinedError([
            d_systCombined[label_ttbar]["stat"][iSR] * (abs(yieldResult_nominal_ttbar["yield"][iSR]) > 0),
            d_systCombined[label_DYJetsToLL]["stat"][iSR] * (abs(yieldResult_nominal_DYJetsToLL["yield"][iSR]) > 0),
            d_systCombined[label_otherSM]["stat"][iSR] * (abs(yieldResult_nominal_otherSM["yield"][iSR]) > 0),
            d_systCombined[label_fake]["stat"][iSR] * (abs(yieldResult_nominal_fake["yield"][iSR]) > 0),
        ])
        
        allSM_systPos = Common.getCombinedError(
            d_systCombined[label_ttbar]["syst"][iSR] +
            d_systCombined[label_DYJetsToLL]["syst"][iSR] +
            d_systCombined[label_otherSM]["syst"][iSR] +
            d_systCombined[label_fake]["syst"][iSR],
            sign = +1
        )
        
        allSM_systNeg = Common.getCombinedError(
            d_systCombined[label_ttbar]["syst"][iSR] +
            d_systCombined[label_DYJetsToLL]["syst"][iSR] +
            d_systCombined[label_otherSM]["syst"][iSR] +
            d_systCombined[label_fake]["syst"][iSR],
            sign = -1
        )
        
        l_header.append(r"Total bkg.")
        
        if (allSM_statPos == allSM_statNeg) :
            
            l_row.append(r"$ %0.2f \pm %0.2f ^{+%0.2f} _{-%0.2f} $" %(
                allSM,
                allSM_statPos,
                allSM_systPos,
                allSM_systNeg
            ))
        
        else :
            
            l_row.append(r"$ %0.2f ^{+%0.2f +%0.2f} _{-%0.2f -%0.2f} $" %(
                allSM,
                #allSM_stat,
                allSM_statPos,
                allSM_systPos,
                allSM_statNeg,
                allSM_systNeg
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
        
        
        #for iSig in range(0, len(l_massPointYieldHist)) :
        #    
        #    key = (l_massPointYieldHist[iSig][0], l_massPointYieldHist[iSig][1])
        #    
        #    yieldResult = d_massPointYieldHist[key]
        #    
        #    #l_header.append(r"$ x=%s, [%d, %d] \ (\frac{S}{S+B}) $" %(sig_x_str, key[0], key[1]))
        #    l_header.append(r"$ x=%s, [%d, %d] $" %(sig_x_str, key[0], key[1]))
        #    l_row.append("%0.2f \ (%0.2f)" %(yieldResult["yield"][iSR], yieldResult["yield"][iSR] / (yieldResult["yield"][iSR]+allSM)))
        #    
        #    #l_header.append(r"\frac{S}{S+B}")
        #    #l_row.append("%0.2f" %(yieldResult["yield"][iSR] / (yieldResult["yield"][iSR]+allSM)))
        
        
        # Significance
        if (args.SRyieldWithSignificance) :
            
            significance = (yieldResult_data["yield"][iSR] - allSM) / numpy.sqrt( \
                allSM_stat**2 + \
                ((abs(allSM_systPos)+abs(allSM_systNeg))/2.0)**2 + \
                yieldResult_data["yield"][iSR]
            )
            
            l_header.append(r"Significance")
            l_row.append("$ %0.2f $" %(
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
            
            yieldResult = d_massPointYieldHist[key]
            
            statSign = "+" if (yieldResult["yield"][iSR] == 0) else "\pm"
            
            l_header_sig.append(r"$ x=%s, [%d, %d] $" %(sig_x_str, key[0], key[1]))
            
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
                
                SbySB_str = r"\boldmath{$ (%0.2f) $}" %(SbySB)
            
            else :
                
                SbySB_str = r"$ (%0.2f) $" %(SbySB)
            
            
            if (yieldResult["yield"][iSR] == 0) :
                
                #yieldStr = r"\begin{tabular}[t]{c} $ < %0.2f $ \\ %s \end{tabular}" %(
                yieldStr = r"$ < %0.2f $" %(
                    d_systCombined_sig[key]["stat"][iSR]
                )
            
            else :
                
                yieldStr = r"\begin{tabular}[t]{c} $ %0.2f %s %0.2f ^{+%0.2f} _{-%0.2f} $ \\ %s \end{tabular}" %(
                    yieldResult["yield"][iSR],
                    statSign,
                    d_systCombined_sig[key]["stat"][iSR],
                    Common.getCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = +1),
                    Common.getCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = -1),
                    SbySB_str
                )
            
            l_row_sig.append(yieldStr)
            
            l_sig_yield[iSig] += yieldResult["yield"][iSR]
            l_sig_statErr[iSig] += d_systCombined_sig[key]["stat"][iSR]**2
            l_sig_statErrPos[iSig] += d_systCombined_sig[key]["stat"][iSR]**2
            l_sig_statErrNeg[iSig] += d_systCombined_sig[key]["stat"][iSR]**2 * (abs(yieldResult["yield"][iSR]) > 0)
            l_sig_systErrPos[iSig] += Common.getCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = +1)**2
            l_sig_systErrNeg[iSig] += Common.getCombinedError(d_systCombined_sig[key]["syst"][iSR], sign = -1)**2
        
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
    
    l_row = [r"\textbf{Total}"]
    l_row_sig = [r"\textbf{Total}"]
    
    for iSig in range(0, len(l_massPointYieldHist)) :
        
        if (l_sig_statErrPos[iSig] == l_sig_statErrNeg[iSig]) :
            
            l_row_sig.append(r"\boldmath{$ %0.2f \pm %0.2f ^{+%0.2f} _{-%0.2f} $}" %(
                l_sig_yield[iSig],
                l_sig_statErrPos[iSig],
                l_sig_systErrPos[iSig],
                l_sig_systErrNeg[iSig]
            ))
        
        else :
            
            l_row_sig.append(r"\boldmath{$ %0.2f ^{+%0.2f +%0.2f} _{-%0.2f -%0.2f} $}" %(
                l_sig_yield[iSig],
                #l_sig_statErr[iSig],
                l_sig_statErrPos[iSig],
                l_sig_systErrPos[iSig],
                l_sig_statErrNeg[iSig],
                l_sig_systErrNeg[iSig]
            ))
    
    l_yieldTable_sig.append(l_row_sig)
    
    
    for iBkg in range(0, len(l_bkg_yield)) :
        
        if (l_bkg_statErrPos[iBkg] == l_bkg_statErrNeg[iBkg]) :
            
            l_row.append(r"\boldmath{$ %0.2f \pm %0.2f ^{+%0.2f} _{-%0.2f} $}" %(
                l_bkg_yield[iBkg],
                l_bkg_statErrPos[iBkg],
                l_bkg_systErrPos[iBkg],
                l_bkg_systErrNeg[iBkg]
            ))
        
        else :
            
            l_row.append(r"\boldmath{$ %0.2f ^{+%0.2f +%0.2f} _{-%0.2f -%0.2f} $}" %(
                l_bkg_yield[iBkg],
                #l_bkg_statErr[iBkg],
                l_bkg_statErrPos[iBkg],
                l_bkg_systErrPos[iBkg],
                l_bkg_statErrNeg[iBkg],
                l_bkg_systErrNeg[iBkg]
            ))
    
    if (totalBkg_statErrPos == totalBkg_statErrNeg) :
        
        l_row.append(r"\boldmath{$ %0.2f \pm %0.2f ^{+%0.2f} _{-%0.2f} $}" %(
            totalBkg_yield,
            totalBkg_statErrPos,
            totalBkg_systErrPos,
            totalBkg_systErrNeg
        ))
    
    else :
        
        l_row.append(r"\boldmath{$ %0.2f ^{+%0.2f +%0.2f} _{-%0.2f -%0.2f} $}" %(
            totalBkg_yield,
            #totalBkg_statErr,
            totalBkg_statErrPos,
            totalBkg_systErrPos,
            totalBkg_statErrNeg,
            totalBkg_systErrNeg
        ))
    
    l_row.append(r"\boldmath{$ %d $}" %(
        totalData_yield
    ))
    
    if (args.SRyieldWithSignificance) :
        
        significance = (totalData_yield - totalBkg_yield) / numpy.sqrt( \
            totalBkg_statErr**2 + \
            ((abs(totalBkg_systErrPos)+abs(totalBkg_systErrNeg))/2.0)**2 + \
            totalData_yield
        )
        
        l_row.append(r"\boldmath{$ %0.2f $}" %(
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
    
    systTableDir = "cutFlowTables/%s" %(era)
    os.system("mkdir -p %s" %(systTableDir))
    
    yieldTableFile = "%s/yieldTable%s_tex.txt" %(systTableDir, "_withSignificance" * args.SRyieldWithSignificance)
    
    print "\n"
    print "Writing: %s" %(yieldTableFile)
    print "\n"
    
    with open(yieldTableFile, "w") as f :
        
        f.write(yieldTableLatex)
    
    
    # Signal table
    yieldTableLatex_sig = Array2LatexTable.array2LatexTable(
        [l_header_sig] + l_yieldTable_sig,
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
    
    systTableDir = "cutFlowTables/%s" %(era)
    os.system("mkdir -p %s" %(systTableDir))
    
    yieldTableFile_sig = "%s/yieldTable_sig_%s_tex.txt" %(systTableDir, sig_x_str_fileName)
    
    print "\n"
    print "Writing: %s" %(yieldTableFile_sig)
    print "\n"
    
    with open(yieldTableFile_sig, "w") as f :
        
        f.write(yieldTableLatex_sig)
    
    
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
    histDetail_temp.histLabel = "\ttbar"
    histDetail_temp.color = Details.color_ttbar
    l_histDetail.append(histDetail_temp)
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_nominal_DYJetsToLL)
    histDetail_temp.histLabel = "DY+jets"
    histDetail_temp.color = Details.color_DYJetsToLL
    l_histDetail.append(histDetail_temp)
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_nominal_otherSM)
    histDetail_temp.histLabel = "Other SM"
    histDetail_temp.color = Details.color_otherSM
    l_histDetail.append(histDetail_temp)
    
    #
    histDetail_temp = Common.HistogramDetails()
    histDetail_temp.hist = getYieldHist(yieldResult_nominal_fake)
    histDetail_temp.histLabel = "Fake"
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
        
        yieldResult = d_massPointYieldHist[key]
        
        histDetail_temp = Common.HistogramDetails()
        histDetail_temp.hist = getYieldHist(yieldResult)
        histDetail_temp.histLabel = "x=%s, [%d, %d]" %(sig_x_str, key[0], key[1])
        #histDetail_temp.color = ROOT.kMagenta + 2*(iSig+1)
        #histDetail_temp.color = ROOT.kMagenta + 2*(len(l_histDetail_sig)+1)
        histDetail_temp.color = Details.l_color_sig[len(l_histDetail_sig)]
        histDetail_temp.lineStyle = 2
        histDetail_temp.lineWidth = 4
        l_histDetail_sig.append(histDetail_temp)
    
    
    outDir = "plots/SR_yields/%s" %(era)
    os.system("mkdir -p %s" %(outDir))
    
    outFileName = "%s/SRyield_%s_%s" %(outDir, cutFlowNameBase, sig_x_str_fileName)
    
    Common.plot1D(
        l_histDetail_data = l_histDetail_data,
        l_histDetail_mc = l_histDetail,
        histDetail_mc_statErrPos = histDetail_mc_statErrPos,
        histDetail_mc_statErrNeg = histDetail_mc_statErrNeg,
        histDetail_mc_systErrPos = histDetail_mc_systErrPos,
        histDetail_mc_systErrNeg = histDetail_mc_systErrNeg,
        l_histDetail_sig = l_histDetail_sig,
        stackDrawOption = "",
        drawMCerr = True,
        ratioPlot = True,
        ratioLegendTextSizeScale = 2,
        ratioStatErr = True,
        ratioTotalErr = True,
        drawRatioStatErr = False,
        drawRatioTotalErr = True,
        title = "SR yields (%s)" %(era),
        xTitle = "Bin number", yTitle = "Events",
        ratioYtitle = "Data / Prediction",
        d_colorRatioGridY = {1: {"color": 2}},
        #xMin = plotQuantity.xMin, xMax = plotQuantity.xMax,
        yMin = 1e-3,
        yMax = 1e6,
        logY = True,
        ratioHist_ymax = 3,
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
        CMSextraText = Common.getCMSextraText(),
        lumiText = Common.getLumitext(era),
        outFileName = outFileName,
        #outFileName_suffix = "",
    )

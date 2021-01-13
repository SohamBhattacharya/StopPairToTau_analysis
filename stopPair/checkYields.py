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
import Common
import Details


era = "2016"


lumi_data = Details.luminosity_data[era]


debug = False


#nSR = 18
cutFlowNameBase = "SRB"

#####
suffix_data = "_tauTau_analysis"
#suffix_mc = "_tauTau_analysis"
suffix_mc = "_tauTau_analysis_nFakeTauGeq1"
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


nSR_merged = len(ll_regionNumber_SR)


inputFiles_sig = []


details_otherSM = (
    #Details.cutFlowDir_WJetsToLNu[era] +
    Details.cutFlowDir_VH[era] +
    Details.cutFlowDir_VV[era] +
    #Details.cutFlowDir_WG[era] +
    Details.cutFlowDir_singleTop[era] +
    Details.cutFlowDir_TTX[era]
)


l_xs_otherSM = (
    #Details.crossSection_WJetsToLNu[era] +
    Details.crossSection_VH[era] +
    Details.crossSection_VV[era] +
    #Details.crossSection_WG[era] +
    Details.crossSection_singleTop[era] +
    Details.crossSection_TTX[era]
)


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


inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix_mc, rootFileName_mc)
inputFiles_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix_mc, rootFileName_mc)
inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix_mc, rootFileName_mc)
inputFiles_otherSM = Common.getRootFiles(details_otherSM, suffix_mc, rootFileName_mc)
inputFiles_fake = Common.getRootFiles(Details.cutFlowDir_tauTau_fakeEstimation[era], suffix_fakeEstimation, rootFileName_fakeEstimation)


prettyPrinter = pprint.PrettyPrinter(indent = 4)


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

yieldResult_nominal_WJetsToLNu = Common.getYields(
    l_rootFile = inputFiles_WJetsToLNu,
    l_xs = Details.crossSection_WJetsToLNu[era],
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


l_allSM = numpy.sum(
    [
        yieldResult_nominal_ttbar["yield"],
        yieldResult_nominal_DYJetsToLL["yield"],
        yieldResult_nominal_WJetsToLNu["yield"],
        yieldResult_nominal_otherSM["yield"],
    ],
    
    axis = 0,
).tolist()

l_ttbarFraction = ["%d %%" %(yieldResult_nominal_ttbar["yield"][iSR]/l_allSM[iSR]*100.0 if (l_allSM[iSR]) else 0) for iSR in range(0, nSR_merged)]
l_DYJetsToLLfraction = ["%d %%" %(yieldResult_nominal_DYJetsToLL["yield"][iSR]/l_allSM[iSR]*100.0 if (l_allSM[iSR]) else 0) for iSR in range(0, nSR_merged)]
l_WJetsToLNuFraction = ["%d %%" %(yieldResult_nominal_WJetsToLNu["yield"][iSR]/l_allSM[iSR]*100.0 if (l_allSM[iSR]) else 0) for iSR in range(0, nSR_merged)]
l_otherSMfraction = ["%d %%" %(yieldResult_nominal_otherSM["yield"][iSR]/l_allSM[iSR]*100.0 if (l_allSM[iSR]) else 0) for iSR in range(0, nSR_merged)]

print yieldResult_nominal_ttbar["yield"]
print yieldResult_nominal_DYJetsToLL["yield"]
print yieldResult_nominal_WJetsToLNu["yield"]
print yieldResult_nominal_otherSM["yield"]

l_print = [
    #["ttbar"] + yieldResult_nominal_ttbar["yield"],
    #["DY+jets"] + yieldResult_nominal_DYJetsToLL["yield"],
    #["W+jets"] + yieldResult_nominal_WJetsToLNu["yield"],
    #["Other SM"] + yieldResult_nominal_otherSM["yield"],
    #
    #[None]*(nSR_merged+1),
    #["Total"] + l_allSM,
    #[None]*(nSR_merged+1),
    
    ["ttbar"] + l_ttbarFraction,
    ["DY+jets"] + l_DYJetsToLLfraction,
    ["W+jets"] + l_WJetsToLNuFraction,
    ["Other SM"] + l_otherSMfraction,
]




l_header = ["process"] + ["SR%d" %(iSR+1) for iSR in range(0, nSR_merged)]

outTableStr = tabulate.tabulate(
    l_print,
    headers = l_header,
    #tablefmt = "simple",
    tablefmt = "latex",
    numalign = "left",
    floatfmt = ".2f",
)


outFileName = "checkYields_nFakeTauGeq1.txt"

print "Writing: %s" %(outFileName)

with open(outFileName, "w") as f:
    
    f.write(outTableStr)
    f.write("\n")

print "\n"
print outTableStr

import numpy
import os
import sys
import tabulate

import ROOT
from ROOT import TAxis
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import THStack
from ROOT import TLegend
from ROOT import TStyle

import Common
import Details


era = "2016"


d_systName_tauTau_analysis = {
    ##"nominal": "",
    "tauES": "tauES",
    "pileupReweight": "pileupReweight",
    "topPtReweight": "topPtReweight",
    "tauIDisoSF": "tauIDisoSF",
    ##"triggerSF": "triggerSF",
    "bTaggingSF": "bTaggingSF",
    "JEC": "JEC",
    "JER": "JER",
    "unclusteredEnergy": "unclusteredEnergy",
}


d_systName_tauTau_fakeEstimation = {
    ##"nominal": "",
    "tauFakeRateRegion": "tauFakeRateRegion",
    "tauFakeRateJetPartonFlav": "tauFakeRateJetPartonFlav",
}


#####

l_rootFileDir_mc = Details.cutFlowDir_ttbar[era]
l_xs = Details.crossSection_ttbar[era]

#l_rootFileDir_mc = Details.cutFlowDir_DYJetsToLL[era]
#l_xs = Details.crossSection_DYJetsToLL[era]

#l_rootFileDir_mc = Details.cutFlowDir_WJetsToLNu[era]
#l_xs = Details.crossSection_WJetsToLNu[era]

l_rootFileDir_fakeEstimation = Details.cutFlowDir_tauTau_fakeEstimation[era]

#####
suffix_mc = "_tauTau_analysis"
suffix_fakeEstimation = "_tauTau_fakeEstimation"

#####
rootFileName_mc = "custom_all_analyzed.root"
rootFileName_fakeEstimation = "custom_all_fakeEstimation_tauTau.root"

#####
detailStr_mc = "tightTight_OS_genMatched_baselineSRB"
detailStr_fakeEstimation = "OS_baselineSRB"


#lumi_data = 8.347e3
#lumi_data = 35.9e3
lumi_data = Details.luminosity_data[era]

debug = True


nSR = 18
finalYieldBin = 6
histName_base = "SRB"

isFakeEstimation = False


d_systName = d_systName_tauTau_analysis
l_rootFileDir = l_rootFileDir_mc
suffix = suffix_mc
rootFileName = rootFileName_mc
detailStr = detailStr_mc


#d_systName = d_systName_tauTau_fakeEstimation
#l_rootFileDir = l_rootFileDir_fakeEstimation
#suffix = suffix_fakeEstimation
#rootFileName = rootFileName_fakeEstimation
#detailStr = detailStr_fakeEstimation
#isFakeEstimation = True


##################################################
l_rootFile_nominal = Common.getRootFiles(l_rootFileDir, suffix, rootFileName, debug)


d_nominal = {}


d_systUpResult = {}
d_systDownResult = {}


d_systUpNegFake = {}
d_systDownNegFake = {}


for systKey in d_systName :
    
    suffix_mod = "%s_%s-systUp" %(suffix, systKey)
    l_rootFile_systUp = Common.getRootFiles(l_rootFileDir, suffix_mod, rootFileName, debug)
    
    suffix_mod = "%s_%s-systDown" %(suffix, systKey)
    l_rootFile_systDown = Common.getRootFiles(l_rootFileDir, suffix_mod, rootFileName, debug)
    
    l_nominal = []
    
    l_systUpResult = []
    l_systDownResult = []
    
    l_systUpNegFake = []
    l_systDownNegFake = []
    
    for iSR in range(0, nSR) :
        
        systUpPercent = 0
        systDownPercent = 0
        
        if ("fakeEstimation" in l_rootFile_nominal[0].GetName()) :
            
            histName = "%s%d" %(histName_base, iSR+1)
            
            # Nominal
            h1_nominal = Common.HistogramDetails(l_rootFile = l_rootFile_nominal, histName = histName)
            h1_nominal.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "total"
            )
            
            h1_nominal_pos = Common.HistogramDetails(l_rootFile = l_rootFile_nominal, histName = histName)
            h1_nominal_pos.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "pos"
            )
            
            h1_nominal_neg = Common.HistogramDetails(l_rootFile = l_rootFile_nominal, histName = histName)
            h1_nominal_neg.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "neg"
            )
            
            
            # Up
            h1_systUp = Common.HistogramDetails(l_rootFile = l_rootFile_systUp, histName = histName)
            h1_systUp.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "total"
            )
            
            h1_systUp_pos = Common.HistogramDetails(l_rootFile = l_rootFile_systUp, histName = histName)
            h1_systUp_pos.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "pos"
            )
            
            h1_systUp_neg = Common.HistogramDetails(l_rootFile = l_rootFile_systUp, histName = histName)
            h1_systUp_neg.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "neg"
            )
            
            
            # Down
            h1_systDown = Common.HistogramDetails(l_rootFile = l_rootFile_systDown, histName = histName)
            h1_systDown.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "total"
            )
            
            h1_systDown_pos = Common.HistogramDetails(l_rootFile = l_rootFile_systDown, histName = histName)
            h1_systDown_pos.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "pos"
            )
            
            h1_systDown_neg = Common.HistogramDetails(l_rootFile = l_rootFile_systDown, histName = histName)
            h1_systDown_neg.getFakeEstimationHistogram(
                suffix = detailStr,
                debug = debug,
                component = "neg"
            )
            
            
            binVal_nominal = h1_nominal.hist.GetBinContent(finalYieldBin)
            binVal_nominal_pos = h1_nominal_pos.hist.GetBinContent(finalYieldBin)
            binVal_nominal_neg = h1_nominal_neg.hist.GetBinContent(finalYieldBin)
            
            binVal_systUp = h1_systUp.hist.GetBinContent(finalYieldBin)
            binVal_systUp_pos = h1_systUp_pos.hist.GetBinContent(finalYieldBin)
            binVal_systUp_neg = h1_systUp_neg.hist.GetBinContent(finalYieldBin)
            
            binVal_systDown = h1_systDown.hist.GetBinContent(finalYieldBin)
            binVal_systDown_pos = h1_systDown_pos.hist.GetBinContent(finalYieldBin)
            binVal_systDown_neg = h1_systDown_neg.hist.GetBinContent(finalYieldBin)
            
            
            l_systUpNegFake.append(False)
            l_systDownNegFake.append(False)
            
            #if (binVal_nominal >= 0) :
            
            l_nominal.append(binVal_nominal)
            
            # Up syst
            if (binVal_nominal > 0 and binVal_systUp >= 0) :
                
                systUpPercent = (binVal_systUp - binVal_nominal) / binVal_nominal * 100.0
            
            elif (binVal_nominal < 0 or binVal_systUp < 0) :
                
                systUp_pos = (binVal_systUp_pos-binVal_nominal_pos)/binVal_nominal_pos if (abs(binVal_nominal_pos) > 0) else 0
                systUp_neg = (binVal_systUp_neg-binVal_nominal_neg)/binVal_nominal_neg if (abs(binVal_nominal_neg) > 0) else 0
                
                systUpPercent = 100.0 * numpy.sqrt(
                    pow(systUp_pos, 2) +
                    pow(systUp_neg, 2)
                )
                
                l_systUpNegFake[-1] = True
                
                print \
                    "%s SR%d: nom (pos, neg) %0.2f (%0.2f, %0.2f), up (pos, neg) %0.2f (%0.2f, %0.2f)" \
                    %(systKey, iSR+1, binVal_nominal, binVal_nominal_pos, binVal_nominal_neg, binVal_systUp, binVal_systUp_pos, binVal_systUp_neg)
            
            # Down syst
            if (binVal_nominal > 0 and binVal_systDown >= 0) :
                
                systDownPercent = (binVal_systDown - binVal_nominal) / binVal_nominal * 100.0
            
            elif (binVal_nominal < 0 or binVal_systDown < 0) :
                
                systDown_pos = (binVal_systDown_pos-binVal_nominal_pos)/binVal_nominal_pos if (abs(binVal_nominal_pos) > 0) else 0
                systDown_neg = (binVal_systDown_neg-binVal_nominal_neg)/binVal_nominal_neg if (abs(binVal_nominal_neg) > 0) else 0
                
                systDownPercent = 100.0 * numpy.sqrt(
                    pow(systDown_pos, 2) +
                    pow(systDown_neg, 2)
                )
                
                l_systDownNegFake[-1] = True
                
                print \
                    "%s SR%d: nom (pos, neg) %0.2f (%0.2f, %0.2f), down (pos, neg) %0.2f (%0.2f, %0.2f)" \
                    %(systKey, iSR+1, binVal_nominal, binVal_nominal_pos, binVal_nominal_neg, binVal_systDown, binVal_systDown_pos, binVal_systDown_neg)
        
        else :
            
            histName = "reco/%s/%s%d_%s" %(detailStr, histName_base, iSR+1, detailStr)
            nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
            
            if ("WJets" in l_rootFile_nominal[0].GetName() or "DYJets" in l_rootFile_nominal[0].GetName()) :
                
                nEventHistName = ""
            
            
            # Nominal
            h1_nominal = Common.HistogramDetails(l_rootFile = l_rootFile_nominal, l_xs = l_xs, histName = histName)
            h1_nominal.getHist(
                xsNormalize = True,
                nEventHistName = nEventHistName,
            )
            h1_nominal.hist.Scale(lumi_data)
            
            
            # Up
            h1_systUp = Common.HistogramDetails(l_rootFile = l_rootFile_systUp, l_xs = l_xs, histName = histName)
            h1_systUp.getHist(
                xsNormalize = True,
                nEventHistName = nEventHistName,
            )
            h1_systUp.hist.Scale(lumi_data)
            
            
            # Down
            h1_systDown = Common.HistogramDetails(l_rootFile = l_rootFile_systDown, l_xs = l_xs, histName = histName)
            h1_systDown.getHist(
                xsNormalize = True,
                nEventHistName = nEventHistName,
            )
            h1_systDown.hist.Scale(lumi_data)
            
            
            binVal_nominal = h1_nominal.hist.GetBinContent(finalYieldBin)
            binVal_systUp = h1_systUp.hist.GetBinContent(finalYieldBin)
            binVal_systDown = h1_systDown.hist.GetBinContent(finalYieldBin)
            
            l_nominal.append(binVal_nominal)
            
            systUp = binVal_systUp - binVal_nominal
            systDown = binVal_systDown - binVal_nominal
            
            if (abs(binVal_nominal) > 0) :
                
                systUpPercent = systUp / binVal_nominal * 100.0
                systDownPercent = systDown / binVal_nominal * 100.0
            
            else :
                
                if (abs(binVal_systUp) > 0) :
                    
                    systUpPercent = 100
                
                if (abs(binVal_systDown) > 0) :
                    
                    systDownPercent = 100
        
        
        l_systUpResult.append(systUpPercent)
        l_systDownResult.append(systDownPercent)
        
        print "%s SR%d: nom %0.2f, up %0.2f, down %0.2f" %(systKey, iSR+1, binVal_nominal, binVal_systUp, binVal_systDown)
        print "%s SR%d: up %0.2f%%, down %0.2f%%" %(systKey, iSR+1, systUpPercent, systDownPercent)
    
    d_nominal[systKey] = l_nominal
    
    d_systUpResult[systKey] = l_systUpResult
    d_systDownResult[systKey] = l_systDownResult
    
    d_systUpNegFake[systKey] = l_systUpNegFake
    d_systDownNegFake[systKey] = l_systDownNegFake
    


temp_str = ""

lenMax = max([len(systKey) for systKey in d_systUpResult])

l_print = []

nominal_str = "Nominal yield"
l_temp = []
l_temp.append(nominal_str)

for iSR in range(0, nSR) :
    
    nominal_str = "%0.2f" %(d_nominal[d_systUpResult.keys()[0]][iSR])
    
    l_temp.append(nominal_str)

l_print.append(l_temp)


for systKey in d_systUpResult :
    
    l_temp = []
    
    temp_str = "%s [up%%/down%%]" %(systKey)
    l_temp.append(temp_str)
    
    for iSR in range(0, nSR) :
        
        if (isFakeEstimation) :
            
            temp_str = "%0.1f%s/%0.1f%s" %(d_systUpResult[systKey][iSR], "[*]"*d_systUpNegFake[systKey][iSR], d_systDownResult[systKey][iSR], "[*]"*d_systDownNegFake[systKey][iSR])
        
        else :
            
            temp_str = "%0.1f/%0.1f" %(d_systUpResult[systKey][iSR], d_systDownResult[systKey][iSR])
        
        l_temp.append(temp_str)
    
    l_print.append(l_temp)


outTableStr = tabulate.tabulate(
    l_print,
    headers = ["Systematic name"] + ["SR%d" %(iSR+1) for iSR in range(0, nSR)]
)

print "\n"
print outTableStr
print "\n"


with open("printSytematics_output.txt", "w") as f :
    
    f.write(outTableStr)

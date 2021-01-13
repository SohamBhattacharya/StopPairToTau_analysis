import array
import glob
import numpy
import operator
import os
import pprint
import re
import time

import ROOT
from ROOT import TAxis
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TGraphAsymmErrors
from ROOT import TH1F
from ROOT import TH2F
from ROOT import THStack
from ROOT import TLegend
from ROOT import TStyle

import Details

import CMS_lumi
import tdrstyle


initVal = -9999


# Scale variations
l_QCDscaleVarIndex = [
    #0,
    1, 2, 3, 4, 6, 8
]


def getOperatorFromStr(optr):
    
    return {
        '+' : operator.add,
        '-' : operator.sub,
        '*' : operator.mul,
        '/' : operator.div,
        '%' : operator.mod,
        '^' : operator.xor,
        }[optr]


# Can do alphanumeric sort properly
def getSortedList(l) :
    
    # From https://stackoverflow.com/questions/2669059/how-to-sort-alpha-numeric-set-in-python
    convert = lambda text: int(text) if text.isdigit() else text
    
    alphanum_key = lambda key: [convert(c) for c in re.split("([0-9]+)", key)]
    
    #print convert
    #print alphanum_key
    
    return sorted(l, key = alphanum_key)


def getRootFiles(directories, suffix, fileName, debug = False) :
    
    inputFiles = []
    
    for iDir in range(0, len(directories)) :
        
        fileName_full = directories[iDir] + suffix + "/" + fileName
        
        if(os.path.isfile(fileName_full)) :
            
            if (debug) :
                
                print "Input file:", fileName_full
            
            inputFiles.append(TFile.Open(fileName_full))
        
        else :
            
            print "File not found:", fileName_full
            exit(1)
    
    return inputFiles


def getCombinedCutFlow(inputFiles, cutFlowName, details, debug,
    crossSections = [], lumi_data = 1, option = "", nEventHistName = "") :
    
    if (not len(nEventHistName)) :
        
        nEventHistName = "nEvent"
    
    if(details != "") :
        
        cutFlowName += "_" + details
        
        #nEventHistName = "%s/%s_%s" %(details, nEventHistName, details)
    
    h1_cutFlow_combined = 0
    
    for iFile in range(0, len(inputFiles)) :
        
        if(debug) :
            
            print "File:", inputFiles[iFile].GetName()
            print "Cutflow:", cutFlowName
        
        #if(not inputFiles[iFile].GetListOfKeys().Contains(cutFlowName)) :
        #    
        #    print "Cannot find", cutFlowName, "in file", inputFiles[iFile].GetName()
        #    exit(1)
        
        h1_cutFlow = inputFiles[iFile].Get(cutFlowName).Clone()
        h1_cutFlow.Sumw2()
        
        # Get nEvent
        nEvent = h1_cutFlow.GetBinContent(1)
        
        #if ("MC" in option) :
        #    
        #    print crossSections[iFile], nEvent
        
        if (not nEvent) :
            
            print "nEventHistName: %s" %(nEventHistName)
            h1_nEvent = inputFiles[iFile].Get(nEventHistName).Clone()
            nEvent = h1_nEvent.Integral()
        
        # DYJets and WJets are already reweighted
        if(("DYJetsToLL_mc" in inputFiles[iFile].GetName()) or ("WJetsToLNu_mc" in inputFiles[iFile].GetName())) :
            
            nEvent = 1
        
        if(debug) :
            
            print "nEventHistName: %s" %(nEventHistName)
            print "nEvent =", int(nEvent)
        
        eventWeight = 1.0
        
        kFactorCorr = 1.0
        
        if (
            "Summer16" in inputFiles[iFile].GetName() and
            "DYJetsToLL_mc" in inputFiles[iFile].GetName()
            ) :
            
            kFactorCorr = 6225.0 / 5765.0
            
            eventWeight *= kFactorCorr
            
            #print "Correctiion factor for 2016 DY x-sec (new NNLO / old NNLO): %f" %(kFactorCorr    ) 
            #scale *= kFactorCorr
        
        # Scale cut-flow
        if("MC" in option) :
            
            eventWeight = 1.0 / float(nEvent) * crossSections[iFile] * lumi_data * kFactorCorr
        
        h1_cutFlow.Scale(eventWeight)
        
        # If empty, initialize combined cut-flow
        if(not h1_cutFlow_combined) :
            
            h1_cutFlow_combined = h1_cutFlow.Clone()
        
        # Add to combined cut-flow
        else :
            
            h1_cutFlow_combined.Add(h1_cutFlow);
    
    # Return combined cut-flow
    return h1_cutFlow_combined
    

#def getCombinedCutFlow(cutFlowDirs, cutFlowName, details, suffix, debug,
#    crossSections = [], lumi_data = 1, option = "") :
#    
#    if(details != "") :
#        
#        cutFlowName += "_" + details
#    
#    cutFlow_combined = numpy.empty(0)
#    
#    statError_combined = numpy.empty(0)
#    
#    for iDir in range(0, len(cutFlowDirs)) :
#        
#        cutFlowDir = cutFlowDirs[iDir] + suffix + "/" + cutFlowName
#        
#        if(debug) :
#            
#            print "Directory:", cutFlowDir
#        
#        # Get cut-flow file names in directory
#        cutFlowFiles = glob.glob(cutFlowDir + "/**")
#        cutFlowFiles = [f for f in cutFlowFiles if ".txt" in f]
#        
#        # Get cut-flows in directory
#        cutFlows = [numpy.loadtxt(f, ndmin = 1) for f in cutFlowFiles]
#        
#        cutFlow_len = cutFlows[0].shape[0]
#        
#        cutFlow_sum = numpy.zeros(cutFlow_len)
#        statError = numpy.zeros(cutFlow_len)
#        
#        # Add cut-flows in directory
#        for iFile in range (0, len(cutFlows)) :
#            
#            cutFlow_sum += cutFlows[iFile]
#        
#        # Get nEvent
#        nEvent = cutFlow_sum[0]
#        
#        if(("DYJets" in cutFlowDir) or ("WJets" in cutFlowDir)) :
#            
#            nEvent = 1
#        
#        if(debug) :
#            
#            print "nEvent =", int(nEvent)
#        
#        eventWeight = 1.0
#        
#        # Scale cut-flow
#        if(option == "MC") :
#            
#            eventWeight = 1.0 / float(nEvent) * crossSections[iDir] * lumi_data
#        
#        statError = statError + (eventWeight**2 * cutFlow_sum)
#        
#        cutFlow_sum = eventWeight * cutFlow_sum
#        
#        # If empty, initialize combined cut-flow
#        if(not cutFlow_combined.shape[0]) :
#            
#            cutFlow_combined = numpy.zeros(cutFlow_len)
#            statError_combined = numpy.ones(cutFlow_len)
#        
#        # Add to combined cut-flow
#        cutFlow_combined += cutFlow_sum
#        
#        if(debug) :
#            
#            print cutFlow_sum
#    
#    # Return combined cut-flow
#    return cutFlow_combined


def getCombinedCutFlow_QCD(
    cutFlowName,
    details_sig, details_shape,
    details_scaleNum, details_scaleDen,
    inputFiles_data, lumi_data,
    inputFiles_mc, crossSections_mc,
    debug) :
    
    # Get histograms
    h1_cutFlow_sig = getCombinedCutFlow(inputFiles_data, cutFlowName, details_sig, debug)
    h1_cutFlow_shape = getCombinedCutFlow(inputFiles_data, cutFlowName, details_shape, debug)
    h1_cutFlow_scaleNum = getCombinedCutFlow(inputFiles_data, cutFlowName, details_scaleNum, debug)
    h1_cutFlow_scaleDen = getCombinedCutFlow(inputFiles_data, cutFlowName, details_scaleDen, debug)
    
    # Subtract non-QCD MC from Data
    for iBg in range(0, len(inputFiles_mc)) :
        
        if (debug) :
            
            print "h1_cutFlow_sig", histToArray(h1_cutFlow_sig, "binContent")[0]
            print "h1_cutFlow_shape", histToArray(h1_cutFlow_shape, "binContent")[0]
            print "h1_cutFlow_scaleNum", histToArray(h1_cutFlow_scaleNum, "binContent")[0]
            print "h1_cutFlow_scaleDen", histToArray(h1_cutFlow_scaleDen, "binContent")[0]
        
        h1_cutFlow_sig.Add(getCombinedCutFlow(inputFiles_mc[iBg], cutFlowName, details_sig, debug, crossSections_mc[iBg], lumi_data, "MC"), -1)
        h1_cutFlow_shape.Add(getCombinedCutFlow(inputFiles_mc[iBg], cutFlowName, details_shape, debug, crossSections_mc[iBg], lumi_data, "MC"), -1)
        h1_cutFlow_scaleNum.Add(getCombinedCutFlow(inputFiles_mc[iBg], cutFlowName, details_scaleNum, debug, crossSections_mc[iBg], lumi_data, "MC"), -1)
        h1_cutFlow_scaleDen.Add(getCombinedCutFlow(inputFiles_mc[iBg], cutFlowName, details_scaleDen, debug, crossSections_mc[iBg], lumi_data, "MC"), -1)
    
    # Set -ve bins to zero
    setBinLwrThreshold(h1_cutFlow_sig, 0, 0, False)
    setBinLwrThreshold(h1_cutFlow_shape, 0, 0, False)
    setBinLwrThreshold(h1_cutFlow_scaleNum, 0, 0, False)
    setBinLwrThreshold(h1_cutFlow_scaleDen, 0, 0, False)
    
    # Subtract signal region
    h1_cutFlow_shape.Add(h1_cutFlow_sig, -1)
    h1_cutFlow_scaleDen.Add(h1_cutFlow_scaleNum, -1)
    
    # Set -ve bins to zero
    setBinLwrThreshold(h1_cutFlow_shape, 0, 0, False)
    setBinLwrThreshold(h1_cutFlow_scaleDen, 0, 0, False)
    
    # Calculate QCD
    h1_cutFlow_QCD = h1_cutFlow_shape.Clone()
    h1_cutFlow_QCD.Sumw2()
    h1_cutFlow_QCD.Multiply(h1_cutFlow_scaleNum);
    h1_cutFlow_QCD.Divide(h1_cutFlow_scaleDen);
    
    return h1_cutFlow_QCD


def getTTbarSF(
    cutFlowName,
    inputFiles_data,
    lumi_data,
    label_data,
    details_data,
    inputFiles_mc,
    crossSections_mc,
    labels_mc,
    details_mc,
    nEventHistName = "",
    getYieldOnly = False,
    debug = False,
    ) :
    
    h1_cutFlow_data = getCombinedCutFlow(inputFiles_data, cutFlowName, details_data, nEventHistName = nEventHistName, debug = debug)
    h1_cutFlow_mc = 0
    
    hist_info = {}
    
    # Add Data histogram to dictionary with the supplied label
    hist_info[label_data] = h1_cutFlow_data
    
    for iBg in range(0, len(inputFiles_mc)) :
        
        if (debug) :
            
            print h1_cutFlow_data
        
        h1_temp = getCombinedCutFlow(inputFiles_mc[iBg], cutFlowName, details_mc, debug, crossSections_mc[iBg], lumi_data, "MC", nEventHistName = nEventHistName)
        
        # Add MC histogram to dictionary with the supplied label
        hist_info[labels_mc[iBg]] = h1_temp.Clone()
        
        # Initialize if empty; otherwise add
        if (h1_cutFlow_mc) :
            
            h1_cutFlow_mc.Add(h1_temp)
        
        else :
            
            h1_cutFlow_mc = h1_temp.Clone()
    
    nBin = h1_cutFlow_data.GetNbinsX()
    
    binVal_data = h1_cutFlow_data.GetBinContent(nBin)
    binErr_data = h1_cutFlow_data.GetBinError(nBin)
    
    binVal_ttbar = hist_info[Details.label_ttbar[0]].GetBinContent(nBin)
    binErr_ttbar = hist_info[Details.label_ttbar[0]].GetBinError(nBin)
    
    binVal_mc = h1_cutFlow_mc.GetBinContent(nBin)
    binErr_mc = h1_cutFlow_mc.GetBinError(nBin)
    
    # Obtain the ratio
    h1_ratio = h1_cutFlow_data.Clone()
    h1_ratio.Divide(h1_cutFlow_mc)
    
    # Get the SF and error
    SF = h1_ratio.GetBinContent(nBin)
    SF_error = h1_ratio.GetBinError(nBin)
    SF_info = [SF, SF_error]
    
    # Get ttbar purity
    h1_ttbar_purity = hist_info[Details.label_ttbar[0]].Clone()
    h1_ttbar_purity.Divide(h1_cutFlow_mc)
    
    purity = h1_ttbar_purity.GetBinContent(nBin)
    purity_error = h1_ttbar_purity.GetBinError(nBin)
    purity_info = [purity, purity_error]
    
    info_mc = {}
    
    for iBg in range(0, len(inputFiles_mc)) :
        
        info_mc[labels_mc[iBg]] = {}
        info_mc[labels_mc[iBg]]["yield"] = hist_info[labels_mc[iBg]].GetBinContent(nBin)
        info_mc[labels_mc[iBg]]["error"] = hist_info[labels_mc[iBg]].GetBinError(nBin)
    
    if (getYieldOnly) :
        
        info = {
            "data": binVal_data,
            "mc": binVal_mc,
            "SFerr": SF_error,
        }
        
        return info
    
    info = {
        "data": {
            "yield": binVal_data,
            "error": binErr_data,
        },
        
        "mc": {
            "yield": binVal_mc,
            "error": binErr_mc,
        },
        
        "ttbar": {
            "yield": binVal_ttbar,
            "error": binErr_ttbar,
        },
        
        "purity": {
            "value": purity,
            "error": purity_error,
        },
        
        "SF": {
            "value": SF,
            "error": SF_error,
        },
    }
    
    info.update(info_mc)
    
    #info = [SF_info, purity_info, hist_info]
    
    return info


def getTTbarSF_multibin(
    cutFlowNameBase,
    inputFiles_data,
    lumi_data,
    label_data,
    details_data,
    inputFiles_mc,
    crossSections_mc,
    labels_mc,
    details_mc,
    ll_regionNumber,
    nEventHistName = "",
    expand = True,
    debug = False,
    ) :
    
    # ll_regionNumber is a list of lists of the form [[1], [2, 3], [4, 5, 6]]
    # Make sure there is no overlap
    # If expand is True: Will return a list whose length is same as the flattened ll_regionNumber (i.e. 6 for the above example)
    # If expand is False: Will return a list whose length is same as ll_regionNumber (i.e. 3 for the above example)
    
    l_binYield_data = []
    l_binError_data = []
    
    l_binYield_mc = []
    l_binError_mc = []
    
    l_binYield_ttbar = []
    l_binError_ttbar = []
    
    l_SF = []
    l_SFerr = []
    
    l_purity = []
    l_purityErr = []
    
    d_l_binYield_mc = {}
    d_l_binError_mc = {}
    
    nEventHistName = "reco/%s/%s_%s" %(details_data, nEventHistName, details_data)
    #print "nEventHistName %s" %(nEventHistName)
    
    for iMC in range(0, len(labels_mc)) :
        
        d_l_binYield_mc[labels_mc[iMC]] = []
        d_l_binError_mc[labels_mc[iMC]] = []
    
    for iRegionGroup in range(0, len(ll_regionNumber)) :
        
        l_regionNumber = ll_regionNumber[iRegionGroup]
        
        binYield_data = 0
        binError_data = 0
        
        binYield_mc = 0
        binError_mc = 0
        
        binYield_ttbar = 0
        binError_ttbar = 0
        
        d_binYield_mc = {}
        d_binError_mc = {}
        
        for iMC in range(0, len(labels_mc)) :
            
            d_binYield_mc[labels_mc[iMC]] = 0
            d_binError_mc[labels_mc[iMC]] = 0
        
        purity = 0
        purityErr = 0
        
        SF = 0
        SFerr = 0
        
        for iRegion in range(0, len(l_regionNumber)) :
            
            regionNumber = l_regionNumber[iRegion]
            
            cutFlowName = "reco/%s/%s%d_%s" %(details_data, cutFlowNameBase, int(regionNumber), details_data)
            
            ttbar_SF_info = getTTbarSF(
                cutFlowName = cutFlowName,
                inputFiles_data = inputFiles_data,
                lumi_data = lumi_data,
                label_data = label_data,
                details_data = "",
                inputFiles_mc = inputFiles_mc,
                crossSections_mc = crossSections_mc,
                labels_mc = labels_mc,
                details_mc = "",
                #getYieldOnly = True,
                nEventHistName = nEventHistName,
                debug = debug
            )
            
            binYield_data += ttbar_SF_info["data"]["yield"]
            binError_data += ttbar_SF_info["data"]["error"]**2
            
            binYield_mc += ttbar_SF_info["mc"]["yield"]
            binError_mc += ttbar_SF_info["mc"]["error"]**2
            
            binYield_ttbar += ttbar_SF_info["ttbar"]["yield"]
            binError_ttbar += ttbar_SF_info["ttbar"]["error"]**2
            
            #SFerr += ttbar_SF_info["SF"]["error"]**2
            
            #purityErr += ttbar_SF_info["purity"]["error"]**2
            
            for iMC in range(0, len(labels_mc)) :
                
                d_binYield_mc[labels_mc[iMC]] += ttbar_SF_info[labels_mc[iMC]]["yield"]
                d_binError_mc[labels_mc[iMC]] += ttbar_SF_info[labels_mc[iMC]]["error"]
        
        binError_data = numpy.sqrt(binError_data)
        
        binError_mc = numpy.sqrt(binError_mc)
        
        binError_ttbar = numpy.sqrt(binError_ttbar)
        
        purity = binYield_ttbar/binYield_mc
        #purityErr = numpy.sqrt(purityErr)
        purityErr = purity * numpy.sqrt((binError_ttbar/binYield_ttbar)**2 + (binError_mc/binYield_mc)**2)
        
        SF = binYield_data/binYield_mc
        #SFerr = numpy.sqrt(SFerr)
        SFerr = SF * numpy.sqrt((binError_mc/binYield_mc)**2 + (binError_data/binYield_data)**2)
        
        for iMC in range(0, len(labels_mc)) :
            
            d_binError_mc[labels_mc[iMC]] += numpy.sqrt(d_binError_mc[labels_mc[iMC]])
        
        expandNumber = 1
        
        if (expand) :
            
            expandNumber = len(l_regionNumber)
            
        l_binYield_data += [binYield_data] * expandNumber
        l_binError_data += [binError_data] * expandNumber
        
        l_binYield_mc += [binYield_mc] * expandNumber
        l_binError_mc += [binError_mc] * expandNumber
        
        l_binYield_ttbar += [binYield_ttbar] * expandNumber
        l_binError_ttbar += [binError_ttbar] * expandNumber
        
        l_SF += [SF] * expandNumber
        l_SFerr += [SFerr] * expandNumber
        
        l_purity += [purity] * expandNumber
        l_purityErr += [purityErr] * expandNumber
        
        for iMC in range(0, len(labels_mc)) :
            
            d_l_binYield_mc[labels_mc[iMC]] += [d_binYield_mc[labels_mc[iMC]]] * expandNumber
            d_l_binError_mc[labels_mc[iMC]] += [d_binError_mc[labels_mc[iMC]]] * expandNumber
    
    
    info = {
        "dataYield": l_binYield_data,
        "dataError": l_binError_data,
        
        "mcYield": l_binYield_mc,
        "mcError": l_binError_mc,
        
        #"ttbarYield": l_binYield_ttbar,
        #"ttbarError": l_binError_ttbar,
        
        "mc": {
            "yield": d_l_binYield_mc,
            "error": d_l_binError_mc,
        },
        
        "SF": l_SF,
        "SFerr": l_SFerr,
        
        "purity": l_purity,
        "purityErr": l_purityErr,
    }
    
    print "*"*50
    print ["%d (%0.2f/%0.2f)" %(iEle+1, l_binYield_ttbar[iEle], l_binYield_mc[iEle]) for iEle in range(0, len(l_binYield_ttbar))]
    print sum(l_binYield_ttbar), sum(l_binYield_mc)
    print "*"*50
    
    return info


def computeError(val1, err1, val2, err2, optr) :
    
    #val_final = getOperatorFromStr(optr)(val1, val2)
    err_final = 0
    
    if (optr == "*" or optr == "/") :
        
        err_final = (err1*val2)**2 + (val1*err2)**2
        err_final = numpy.sqrt(err_final)
    
    return err_final


def histToArray(hist, opt) :
    
    # Returns a 2D list: [[y0], [y1], ...]
    
    histContent = []
    
    for iBinY in range(0, hist.GetNbinsY()) :
        
        row = []
        
        for iBinX in range(0, hist.GetNbinsX()) :
            
            if(opt == "binContent") :
                
                row.append(hist.GetBinContent(iBinX+1, iBinY+1))
            
            elif(opt == "binError") :
                
                row.append(hist.GetBinError(iBinX+1, iBinY+1))
            
            else :
                
                print "Wrong option to function Common::histToArray(...)."
                exit(1)
        
        histContent.append(row)
    
    return numpy.array(histContent)


def getHistSumFromHistDetailList(l_histDetail) :
    
    h_sum = l_histDetail[0].hist.Clone()
    h_sum.Sumw2()
    
    for iHist in range(1, len(l_histDetail)) :
        
        h_sum.Add(l_histDetail[iHist].hist)
    
    return h_sum


def setBinLwrThreshold(
    hist,
    thr_lwr,
    newBinVal,
    evalError = False,
    considerIntegral = False,
) :
    
    # if considerIntegral is True, then all the bins are set to newBinVal if integral < thr_lwr
    
    for iBinX in range(0, hist.GetNbinsX()) :
        
        for iBinY in range(0, hist.GetNbinsY()) :
            
            binContent = hist.GetBinContent(iBinX+1, iBinY+1)
            
            if(binContent < thr_lwr or considerIntegral) :
                
                hist.SetBinContent(iBinX+1, iBinY+1, float(newBinVal))
                
                if(evalError) :
                    
                    hist.SetBinError(iBinX+1, iBinY+1, numpy.sqrt(newBinVal))


#def getCombinedCutFlow_QCD(
#    cutFlowName,
#    suffix,
#    details_sig, details_shape,
#    details_scaleNum, details_scaleDen,
#    cutFlowDir_data, lumi_data,
#    cutFlowDirs_mc, crossSections_mc,
#    debug) :
#    
#    # Get Data
#    cutFlow_sig = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_sig, suffix, debug).astype(float)
#    cutFlow_shape = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_shape, suffix, debug).astype(float)
#    cutFlow_scaleNum = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_scaleNum, suffix, debug).astype(float)
#    cutFlow_scaleDen = getCombinedCutFlow(cutFlowDir_data, cutFlowName, details_scaleDen, suffix, debug).astype(float)
#    
#    # Subtract non-QCD MC from Data
#    for iBg in range(0, len(cutFlowDirs_mc)) :
#        
#        if (debug) :
#            
#            print cutFlow_sig
#            print cutFlow_shape
#            print cutFlow_scaleNum
#            print cutFlow_scaleDen
#        
#        cutFlow_sig -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_sig, suffix, debug, crossSections_mc[iBg], lumi_data, "MC")
#        cutFlow_shape -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_shape, suffix, debug, crossSections_mc[iBg], lumi_data, "MC")
#        cutFlow_scaleNum -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_scaleNum, suffix, debug, crossSections_mc[iBg], lumi_data, "MC")
#        cutFlow_scaleDen -= getCombinedCutFlow(cutFlowDirs_mc[iBg], cutFlowName, details_scaleDen, suffix, debug, crossSections_mc[iBg], lumi_data, "MC")
#    
#    cutFlow_sig[numpy.where(cutFlow_sig < 0)] = 0
#    cutFlow_shape[numpy.where(cutFlow_shape < 0)] = 0
#    cutFlow_scaleNum[numpy.where(cutFlow_scaleNum < 0)] = 0
#    cutFlow_scaleDen[numpy.where(cutFlow_scaleDen < 0)] = 0
#    
#    # Subtract signal region
#    cutFlow_shape -= cutFlow_sig
#    cutFlow_shape[numpy.where(cutFlow_shape < 0)] = 0
#    
#    # Subtract signal region
#    cutFlow_scaleDen -= cutFlow_scaleNum
#    cutFlow_scaleDen[numpy.where(cutFlow_scaleDen < 0)] = 0
#    
#    with numpy.errstate(divide = "ignore", invalid = "ignore") :
#        
#        cutFlow_QCD = cutFlow_shape * cutFlow_scaleNum/cutFlow_scaleDen
#        cutFlow_QCD[numpy.where(cutFlow_QCD < 0)] = 0
#        
#        cutFlow_QCD[numpy.where(numpy.isnan(cutFlow_QCD))[0]] = 0
#        cutFlow_QCD[numpy.where(numpy.isinf(cutFlow_QCD))[0]] = 0
#    
#    return cutFlow_QCD


def createCombineCardMCyieldBlock(details_sig, details_bg, binLabel, nRow, debug) :
    
    # Format:
    # details_sig/bg = [["label", value], ...]
    
    #block = [
    #    ["bin"],
    #    ["process"],
    #    ["process"],
    #    ["rate"],
    #]
    
    block = [[] for iRow in range(0, nRow)]
    
    for iSig in range(0, len(details_sig)) :
        
        details_iSig = details_sig[iSig]
        
        # Must be of the form [label, value]
        if(len(details_iSig) != 2) :
            
            print "Invalid format of details_sig. Look at createCombineCardBinBlock(...)."
            
            exit(1)
        
        block[0].append(binLabel)
        block[1].append(details_iSig[0])
        block[2].append(str(int(-1*iSig)))
        block[3].append(str(details_iSig[1]))
    
    
    for iBg in range(0, len(details_bg)) :
        
        details_iBg = details_bg[iBg]
        
        # Must be of the form [label, value]
        if(len(details_iBg) != 2) :
            
            print "Invalid format of details_bg. Look at createCombineCardBinBlock(...)."
            
            exit(1)
        
        block[0].append(binLabel)
        block[1].append(details_iBg[0])
        block[2].append(str(int(iBg+1)))
        block[3].append(str(details_iBg[1]))
    
    
    if(debug) :
        
        print details_sig
        print details_bg
        print block
    
    return block


#def stringify1DArray(array) :
#    
#    stringArray = []
#    
#    for iEntry in range(0, len(array)) :
#        
#        if (type(array[iEntry]) == str) :
#            
#            stringArray += [array[iEntry]]
#            
#        else :
#            
#            # Replace non-positive values with a "-"
#            if (array[iEntry] <= 0) :
#                
#                stringArray += ["$ - $"]
#            
#            # Format conversion: X^Y --> XeY
#            else :
#                
#                stringArray += ["$ " + ("%0.2e" % array[iEntry]).replace("+0", "").replace("-0", "-").replace("+", "") + " $"]
#                #stringArray += ["$ " + ("%0.2e" % array[iEntry]) + " $"]
#    
#    return stringArray


def stringify1DArray(array, doFormatting = False, latexify = False) :
    
    stringArray = []
    
    template_str = ""
    
    if (latexify) :
        
        template_str = "$ - $"
    
    else :
        
        template_str = "-"
    
    for iEntry in range(0, len(array)) :
        
        temp_str = template_str
        
        if (doFormatting) :
            
            if (array[iEntry] == 0) :
                
                stringArray += [temp_str]
            
            elif (array[iEntry] > 0 and array[iEntry] <= 1000) :
                
                temp_str = temp_str.replace("-", ("%0.2f" % array[iEntry]))
                stringArray += [temp_str]
            
            else :
                
                temp_str = temp_str.replace("-", "%0.2e" % array[iEntry])
                temp_str = temp_str.replace("+0", "").replace("-0", "-").replace("+", "")
                stringArray += [temp_str]
        
        else :
            
            temp_str = temp_str.replace("-", str(array[iEntry]))
            stringArray += [temp_str]
    
    return stringArray


def stringify2DArray(array, doFormatting = False, latexify = False) :
    
    stringArray = [stringify1DArray(entry, doFormatting, latexify) for entry in array]
    
    return stringArray


def printNegativeBins(hist, newBinVal = 0, setBinVal = False, debug = False) :
    
    for iBin in range(1, hist.GetNbinsX()+1) :
        
        if (hist.GetBinContent(iBin) < 0) :
            
            if (debug) :
                
                print "Negative bin content: Bin %d, content %0.2f" %(iBin, hist.GetBinContent(iBin))
            
            if (setBinVal) :
                
                hist.SetBinContent(iBin, newBinVal)


class HistogramDetails :
    
    era = ""
    
    #rootFileName = ""
    #rootFile = 0
    
    l_rootFileName = []
    l_rootFile = []
    
    l_xs = []
    l_weight = []
    
    weightSum = 0
    
    histName = ""
    histTitle = ""
    histLabel = ""
    
    lineStyle = 1
    lineWidth = 3
    
    #markerStyle = 20
    markerStyle = -1
    
    color = 4
    
    hist = 0
    
    xTitle = ""
    yTitle = ""
    
    xMin = initVal
    xMax = initVal
    
    yMin = initVal
    yMax = initVal
    
    zMin = initVal
    zMax = initVal
    
    rebinX = 1
    rebinY = 1
    
    logX = False
    logY = False
    logZ = False
    
    gridX = False
    gridY = False
    
    nDivisionsX = [0, 0, 0]
    nDivisionsY = [0, 0, 0]
    
    centerLabelsX = False
    centerLabelsY = False
    
    drawOption = "hist"
    
    outFileName = ""
    outFileName_suffix = ""
    
    
    def __init__(
        self,
        #rootFileName = "",
        l_rootFileName = [],
        l_rootFile = [],
        l_xs = [],
        l_weight = [],
        histName = "",
        hist = 0,
        era = "",
        ) :
        
        #if (len(rootFileName)) :
        #    
        #    self.rootFileName = rootFileName
        
        if (len(l_rootFileName)) :
            
            self.l_rootFileName = l_rootFileName
        
        if (len(l_rootFile)) :
            
            self.l_rootFile = l_rootFile
        
        if (len(l_xs)) :
            
            self.l_xs = l_xs
        
        if (len(l_weight)) :
            
            self.l_weight = l_weight
        
        if (len(histName)) :
            
            self.histName = histName
        
        if (hist) :
            
            self.hist = hist
        
        self.era = era
        
        self.weightSum = 0
        
        
        #if (len(rootFileName) and len(l_rootFileName)) :
        #    
        #    print "Error in Common.HistogramDetails.__init__(...): Provide either \"rootFileName\" OR \"l_rootFileName\"."
        #    exit(1)
    
    
    def getHist(
        self,
        projection = "",
        startBin = 0,
        endBin = -1,
        findStartBin = False,
        findEndBin = False,
        nRebin = 1,
        l_rebin = [],
        suffix = "",
        xsNormalize = False,
        negToZero = True,
        nEventHistName = "",
        debug = False,
        ) :
        
        nEventHistName_orig = nEventHistName
        
        #if (xsNormalize and len(self.l_rootFileName) != len(l_xs)) :
        #    
        #    print "Error in Common.HistogramDetails.__init__(...): \"l_rootFileName\" and \"l_xs\" must have the same length."
        #    exit(1)
        
        if (xsNormalize and not len(nEventHistName)) :
            
            print "WARNING in Common.HistogramDetails.__init__(...): \"xsNormalize\" provided; \"nEventHistName\" not provided. Will use nEvent = 1."
            #exit(1)
        
        if (nRebin > 1 and len(l_rebin)) :
            
            print "Error in Common.HistogramDetails.__init__(...): Provide either \"nRebin\" OR \"l_rebin\"."
            exit(1)
        
        
        print "Histogram name:", self.histName
        
        
        nEventTotal = 0
        
        #for iFile in range(0, len(self.l_rootFileName)) :
        for iFile in range(0, len(self.l_rootFile)) :
            
            #rootFile = TFile.Open(rootFileName)
            rootFile = self.l_rootFile[iFile]
            
            #rootFileName = self.l_rootFileName[iFile]
            rootFileName = rootFile.GetName()
            
            print "File:", rootFileName
            
            #if ("WJets" in rootFileName or "DYJets" in rootFileName) :
            #    
            #    nEventHistName = ""
            #
            #else :
            #    
            #    nEventHistName = nEventHistName_orig
            
            axis = 0
            
            if (projection == "X") :
                
                hist_temp = rootFile.Get(self.histName).Clone()
                axis = hist_temp.GetYaxis()
            
            elif (projection == "Y") :
                
                hist_temp = rootFile.Get(self.histName).Clone()
                axis = hist_temp.GetXaxis()
            
            if (projection != "" and findStartBin) :
                
                startBin = axis.FindBin(startBin)
            
            if (projection != "" and findEndBin) :
                
                endBin = axis.FindBin(endBin)
            
            # Get histogram
            if (projection == "") :
                
                hist_temp = rootFile.Get(self.histName).Clone()
            
            elif (projection == "X") :
                
                print "Projection X"
                hist_temp = rootFile.Get(self.histName).Clone().ProjectionX(self.histName + "_px", startBin, endBin)
            
            elif (projection == "Y") :
                
                print "Projection Y"
                hist_temp = rootFile.Get(self.histName).Clone().ProjectionY(self.histName + "_py", startBin, endBin)
            
            else :
                
                print "Wrong projection option to HistogramDetails.getHist(...)"
                exit(1)
            
            
            hist_temp.Sumw2()
            
            if (nRebin > 1) :
                
                hist_temp = hist_temp.Rebin(nRebin)
            
            elif (len(l_rebin)) :
                
                hist_temp = hist_temp.Rebin(len(l_rebin)-1, "", array.array("d", l_rebin))
            
            
            # Negative bin content
            if (negToZero) :
                
                printNegativeBins(hist_temp, newBinVal = 0, setBinVal = True, debug = debug)
            
            xs = 1.0
            nEvent = 1.0
            
            if (xsNormalize) :
                
                xs = self.l_xs[iFile]
                
                if (len(nEventHistName)) :
                    
                    nEvent_hist = rootFile.Get(nEventHistName).Clone()
                    nEvent = nEvent_hist.Integral()
                    
                    nEventTotal += nEvent
            
            scale = xs / nEvent
            eventWeight = scale
            
            if ("WJetsToLNu_mc" in rootFileName or "DYJetsToLL_mc" in rootFileName) :
                
                print "WJets/DYJets:", nEvent, nEvent_hist.GetEntries(), nEvent / nEvent_hist.GetEntries()
                #scale *= nEvent_hist.GetEntries()
                scale *= nEvent
                
                if ("WJetsToLNu_mc" in rootFileName and len(self.era)) :
                    
                    # Convert to pb
                    eventWeight = Details.nJetWeight_WJetsToLNu[self.era][iFile] / 1000.0
                    #print "WJetsToLNu nJetWeight", eventWeight
                
                elif ("DYJetsToLL_mc" in rootFileName and len(self.era)) :
                    
                    # Convert to pb
                    eventWeight = Details.nJetWeight_DYJetsToLL[self.era][iFile] / 1000.0
                    #print "DYJetsToLL nJetWeight", eventWeight
            
            
            ##################################################
            # Correct for 2017 tau ID SF
            ##################################################
            
            corr_tauID = 1.0
            
            if ("Fall17" in rootFileName) :
                
                if ("tauTau_analysis" in rootFileName) :
                    
                    corr_tauID = (1.00/0.89)**2
                
                if ("tauTau_analysis" in rootFileName and "tauIDisoSF-systUp" in rootFileName) :
                    
                    corr_tauID = (1.10/0.92)**2
                
                if ("tauTau_analysis" in rootFileName and "tauIDisoSF-systDown" in rootFileName) :
                    
                    corr_tauID = (0.90/0.86)**2
            
            scale *= corr_tauID
            
            ##################################################
            ##################################################
            
            
            ##################################################
            # Correct for 2016 DY x-sec (new NNLO / old NNLO)
            ##################################################
            
            kFactorCorr = 1.0
            
            if (
                "Summer16" in rootFileName and
                "DYJetsToLL_mc" in rootFileName
                ) :
                
                kFactorCorr = 6225.0 / 5765.0
                
                eventWeight *= kFactorCorr
                
                #print "Correctiion factor for 2016 DY x-sec (new NNLO / old NNLO): %f" %(kFactorCorr    ) 
                scale *= kFactorCorr
            
            ##################################################
            ##################################################
            
            if (not self.hist) :
                
                self.hist = hist_temp.Clone()
                self.hist.SetDirectory(0)
                
                self.hist.Sumw2()
                
                self.hist.Scale(scale)
            
            else :
                
                self.hist.Add(hist_temp, scale)
            
            # Earlier: For example: Sum (in inverse quadrature) of (xs/nEvent) for the processes
            # Now: (Total x-sec) / (Total events)
            # Skip for data
            if (len(self.l_xs)) :
                
                #self.weightSum += eventWeight**(-2)
                self.weightSum += xs
            
            print "File %d: integral %e" %(iFile+1, hist_temp.Integral()*scale)
            
            #rootFile.Close()
        
        integralOption = ""
        
        
        # Skip for Data
        if (len(self.l_xs)) :
            
            #self.weightSum = 1.0 / numpy.sqrt(self.weightSum)
            self.weightSum /= float(nEventTotal)
        
        if ("DYJetsToLL_mc" in self.l_rootFile[0].GetName()) :
            
            self.weightSum = Details.inclusiveCrossSection_DYJetsToLL / float(nEventTotal)
            
        
        if (len(l_rebin)) :
            
            self.hist.Scale(1.0, "width")
            integralOption = "width"
        
        print "Total integral: %e" %(self.hist.Integral(integralOption))
    
    
    def getFakeEstimationHistogram(
        self,
        suffix = "",
        nRebin = 1,
        l_rebin = [],
        scale = 1,
        debug = False,
        component = "total",
        fakeWeightHistName = "tauTau_promptFakeEventWeight_reco",
        ) :
        
        if (nRebin > 1 and len(l_rebin)) :
            
            print "Error in Common.HistogramDetails.getFakeEstimationHistogram(...): Provide either \"nRebin\" OR \"l_rebin\"."
            exit(1)
        
        hist = 0
        
        d_detail = {
            "total": [
                ["Nfp_Nll", -1.0],
                ["Nfp_Nlt", +1.0],
                ["Nfp_Ntl", +1.0],
                ["Nfp_Ntt", -1.0],
                
                ["Nff_Nll", +1.0],
                ["Nff_Nlt", -1.0],
                ["Nff_Ntl", -1.0],
                ["Nff_Ntt", +1.0],
            ],
            
            "pos": [
                ["Nfp_Nlt", +1.0],
                ["Nfp_Ntl", +1.0],
                
                ["Nff_Nll", +1.0],
                ["Nff_Ntt", +1.0],
            ],
            
            # Because this is the -ve component only, no need to scale by -1
            "neg": [
                ["Nfp_Nll", +1.0],
                ["Nfp_Ntt", +1.0],
                
                ["Nff_Nlt", +1.0],
                ["Nff_Ntl", +1.0],
            ],
        }
        
        l_detail = d_detail[component]
        
        
        nComponent_fp = 2
        nComponent_lt = len(l_detail) / nComponent_fp
        
        
        l_nEntry = [0 for ele in range(0, len(l_detail))]
        l_fakeWeight = [0 for ele in range(0, len(l_detail))]
        l_binVal = [[] for ele in range(0, len(l_detail))]
        l_binCount = [[] for ele in range(0, len(l_detail))]
        
        #debug = True
        
        for iFile in range(0, len(self.l_rootFile)) :
        #for iFile in range(len(self.l_rootFile)-1, len(self.l_rootFile)) :
            
            #rootFile = TFile(self.rootFileName[iFile])
            rootFile = self.l_rootFile[iFile]
            
            iFile_hist = 0
            
            if (debug) :
                
                print "\n"
                print "********************"
                print "getFakeEstimationHistogram(...): File: %s" %(rootFile.GetName())
                print "********************"
            
            intermediateHist = 0
            
            for iDetail in range(0, len(l_detail)) :
                
                detailStr = "%s_%s" %(l_detail[iDetail][0], suffix)
                sign = l_detail[iDetail][1]
                
                self.histName_mod = "%s/%s_%s" %(detailStr, self.histName, detailStr)
                
                if (debug) :
                    
                    print ""
                    print "getFakeEstimationHistogram(...): Getting histogram %s" %(self.histName_mod)
                
                h_temp = rootFile.Get(self.histName_mod).Clone()
                
                if (nRebin > 1) :
                    
                    h_temp = h_temp.Rebin(nRebin)
                
                elif (len(l_rebin)) :
                    
                    h_temp = h_temp.Rebin(len(l_rebin)-1, "", array.array("d", l_rebin))
                
                if (debug) :
                    
                    print "getFakeEstimationHistogram(...): Sign %d, Integral %0.2f" %(int(sign), h_temp.Integral())
                
                h_temp.Sumw2()
                h_temp.Scale(sign)
                
                # Scale
                h_temp.Scale(scale)
                
                
                ####################################################################################################
                #################### TEST TEST TEST ################################################################
                ####################################################################################################
                
                #if ("jet_n_reco" in self.histName) :
                #    
                #    dBin = 0
                #    
                #    if ("Nlt" in detailStr or "Ntl" in detailStr) :
                #        
                #        dBin = 1
                #    
                #    elif ("Nll" in detailStr) :
                #        
                #        dBin = 2
                #    
                #    if (dBin) :
                #        
                #        for iBin in range(h_temp.GetNbinsX()+1, 0, -1) :
                #            
                #            h_temp.SetBinContent(iBin, h_temp.GetBinContent(iBin-dBin))
                #            h_temp.SetBinError(iBin, h_temp.GetBinError(iBin-dBin))
                #            
                #            h_temp.SetBinContent(iBin-dBin, 0)
                #            h_temp.SetBinError(iBin-dBin, 0)
                #            
                #        #h_temp.Draw("hist")
                #        #time.sleep(5000)
                
                ####################################################################################################
                ####################################################################################################
                
                
                #if (debug) :
                #    
                #    print "Fake %s %0.4f, %0.4f \n" %(detailStr, h_temp.GetBinContent(2), h_temp.GetBinError(2))
                
                if (not iFile_hist) :
                    
                    iFile_hist = h_temp.Clone()
                    
                    #####if (component == "total") :
                    #####    
                    #####    iFile_hist.Reset()
                    
                    iFile_hist.SetDirectory(0)
                    iFile_hist.Sumw2()
                
                else :
                    
                    iFile_hist.Add(h_temp)
                
                
                #####if (iDetail == 0 or iDetail == 4) :
                #####    
                #####    intermediateHist = h_temp.Clone()
                #####    intermediateHist.SetDirectory(0)
                #####
                #####else :
                #####    
                #####    intermediateHist.Add(h_temp)
                
                #if (iDetail == 3 or iDetail == 7) :
                #    
                #    print "iDetail = %s" %(iDetail)
                #    printNegativeBins(iFile_hist)
                
                #####if (component == "total" and (iDetail == 3 or iDetail == 7)) :
                #####    
                #####    print "Intermediate (iDetail = %s)" %(iDetail)
                #####    printNegativeBins(intermediateHist, newBinVal = 0, setBinVal = True)
                #####    
                #####    iFile_hist.Add(intermediateHist)
                #####    
                #####    #print "iDetail = %s" %(iDetail)
                #####    #print "Integral: %f" %(tempSum)
                #####    printNegativeBins(iFile_hist, newBinVal = 0, setBinVal = True) 
                
                # Error calculation
                if (not len(l_binVal[iDetail])) :
                    
                    l_binVal[iDetail] = [0 for iBin in range(0, h_temp.GetNbinsX())]
                    l_binCount[iDetail] = [0 for iBin in range(0, h_temp.GetNbinsX())]
                
                fakeWeightHistName_mod = "%s/%s_%s" %(detailStr, fakeWeightHistName, detailStr)
                h_fakeWeight = rootFile.Get(fakeWeightHistName_mod).Clone()
                h_fakeWeight.SetDirectory(0)
                
                fakeWeight = h_fakeWeight.GetMean()
                nEntry = h_fakeWeight.GetEntries()
                # Weighted
                l_fakeWeight[iDetail] += fakeWeight * nEntry
                #l_fakeWeight[iDetail] += fakeWeight
                l_nEntry[iDetail] += nEntry
                #print "iFile %d, detailStr %s, fakeWeight %f, nEntry %f" %(iFile, detailStr, fakeWeight, nEntry)
                
                for iBin in range(0, h_temp.GetNbinsX()) :
                    
                    binWidth = h_temp.GetBinWidth(iBin+1) if (len(l_rebin) > 0) else 1
                    
                    # Already multiplied by the sign before
                    # So remove that by dividing
                    binVal = float(h_temp.GetBinContent(iBin+1)) / sign / binWidth
                    
                    l_binVal[iDetail][iBin] += binVal
                    #print "iFile %d, detailStr %s, iBin %d, binVal %f" %(iFile, detailStr, iBin+1, binVal)
                    
                    # The bin entry already contains the fake-weight
                    # So divide by the fake-weight to get the count
                    l_binCount[iDetail][iBin] += binVal / fakeWeight / binWidth
            
            
            
            #print "Fake %0.4f, %0.4f \n" %(iFile_hist.GetBinContent(2), iFile_hist.GetBinError(2))
            
            ##### Used for results
            printNegativeBins(iFile_hist, newBinVal = 0, setBinVal = True, debug = debug)
            
            if (not hist) :
                
                hist = iFile_hist.Clone()
                hist.SetDirectory(0)
                hist.Sumw2()
            
            else :
                
                hist.Add(iFile_hist)
                
            #printNegativeBins(iFile_hist) 
            
            #rootFile.Close()
            
            if (debug) :
                
                print "getFakeEstimationHistogram(...): File %d integral: %0.2f" %(iFile+1, iFile_hist.Integral())
        
        integralOption = ""
        
        if (len(l_rebin)) :
            
            hist.Scale(1.0, "width")
            integralOption = "width"
        
        if (debug) :
            
            print "getFakeEstimationHistogram(...): Final integral %0.2f" %(hist.Integral(integralOption))
            print "\n"
        
        self.hist = hist
        
        ##### Not used for results
        #####printNegativeBins(hist, newBinVal = 0, setBinVal = True, debug = debug)
        
        #debug = True
        
        # Error calculation
        for iBin in range(0, self.hist.GetNbinsX()) :
        #for iBin in range(self.hist.GetNbinsX()-1, self.hist.GetNbinsX()) :
            
            mtx_D = numpy.matrix(numpy.ones((nComponent_fp, 1)))
            mtx_M = numpy.matrix(numpy.zeros((nComponent_lt, nComponent_lt)))
            mtx_T = numpy.matrix(numpy.zeros((nComponent_fp, nComponent_lt)))
            
            # Divide by nComponent_fp because [N_ll, N_lt, N_tl, N_tt] is repeated nComponent_fp times
            l_binVal_componentSum = numpy.sum(l_binVal, axis = 0) / nComponent_fp
            l_binCount_componentSum = numpy.sum(l_binCount, axis = 0) / nComponent_fp
            
            prettyPrinter = pprint.PrettyPrinter(indent = 2, depth = 2, width = 500)
            
            ##debug = True
            
            if (debug) :
                
                print "l_binVal:"
                prettyPrinter.pprint(l_binVal)
                prettyPrinter.pprint(l_binVal_componentSum)
                
                print ""
                
                print "l_binCount:"
                prettyPrinter.pprint(l_binCount)
                prettyPrinter.pprint(l_binCount_componentSum)
            
            for iComponent_lt in range(0, nComponent_lt) :
                
                prob = 0
                
                if (l_binCount_componentSum[iBin] > 0) :
                    
                    prob = l_binCount[iComponent_lt][iBin] / l_binCount_componentSum[iBin]
                
                # Only a problem in the low stat bins where only one of [N_ll, N_lt, N_tl, N_tt] may be non-zero
                if (prob > 1) :
                    
                    prob = 1
                    #print "*"*50, iBin, iComponent_lt, l_binCount[iComponent_lt][iBin], l_binCount_componentSum[iBin]
                
                
                # Binomial error
                #print mtx_M
                #print l_binCount
                #print iBin, iComponent_lt, l_binVal[iComponent_lt][iBin], l_binCount[iComponent_lt][iBin], numpy.sum() prob
                mtx_M[iComponent_lt, iComponent_lt] = l_binCount_componentSum[iBin] * prob * (1-prob)
                #mtx_M[iComponent_lt, iComponent_lt] = l_binCount[iComponent_lt][iBin]
                
                for iComponent_fp in range(0, nComponent_fp) :
                    
                    index = iComponent_fp*nComponent_lt + iComponent_lt
                    
                    # Weighted average
                    # Take the sign too
                    mtx_T[iComponent_fp, iComponent_lt] = l_detail[index][1] * l_fakeWeight[index] / l_nEntry[index]
                    #mtx_T[iComponent_fp, iComponent_lt] = l_detail[index][1] * l_fakeWeight[index] / len(self.l_rootFile)
            
            errSq = (mtx_D.T * (mtx_T * mtx_M * mtx_T.T) * mtx_D)[0, 0]
            err = numpy.sqrt(errSq)
            
            if (debug) :
                
                print "mtx_D: \n", mtx_D
                print "mtx_M: \n", mtx_M
                print "mtx_T: \n", mtx_T
                
                print "*" * 30
                print "Bin: %d" %(iBin+1)
                print "Error sq.", errSq
                print "Error", err
                print "Error (old)", self.hist.GetBinError(iBin+1)
                print "Bin val:", self.hist.GetBinContent(iBin+1)
                print "Error / Bin val:", err / self.hist.GetBinContent(iBin+1)
                print ""
            
            self.hist.SetBinError(iBin+1, err)
        
        if (debug) :
            
            print "*" * 30
            print "\n\n"
    
    
    def normalize(self, byBinWidth = False) :
        
        integral = self.hist.Integral()
        
        if (abs(integral) == 0) :
            
            return
        
        self.hist.Scale(1.0 / integral)
        
        if (byBinWidth) :
            
            for iBin in range(0, self.hist.GetNbinsX()) :
                
                binWidth = self.hist.GetXaxis().GetBinWidth(iBin+1)
                binContent = self.hist.GetBinContent(iBin+1)
                binError = self.hist.GetBinError(iBin+1)
                
                #print binWidth, binContent
                
                scale = 1.0 / binWidth
                
                self.hist.SetBinContent(iBin+1, binContent*scale)
                self.hist.SetBinError(iBin+1, binError*scale)


def getFormulaStr(
    func,
    formulaStr = "",
    precision_val = 4,
    precision_err = 4,
    withError = False,
    relativeError = False
    ) :
    
    if (formulaStr == "") :
        
        formulaStr = str(func.GetExpFormula())
    
    print formulaStr
    
    nPar = func.GetNpar()
    
    for iPar in range(0, nPar) :
        
        parName = func.GetParName(iPar)
        parValue = func.GetParameter(iPar)
        parError = func.GetParError(iPar)
        
        relErrorStr = ""
        
        if (relativeError) :
            
            parError = abs(parError / parValue * 100.0)
            
            relErrorStr = "%"
        
        # Note: %+d prints the sign explicitly
        
        # If there is a plus sign, consider that
        strToReplace = "+[%s]" %(parName)
        
        if (withError) :
            
            newStr = "%+0.*f [%0.*f%s]" %(precision_val, parValue, precision_err, parError, relErrorStr)
        
        else :
            
            newStr = "%+0.*f" %(precision_val, parValue)
        
        formulaStr = formulaStr.replace(strToReplace, newStr)
        
        
        # If there is a minus sign, consider that
        strToReplace = "-[%s]" %(parName)
        
        if (withError) :
            
            newStr = "%+0.*f [%0.*f%s]" %(precision_val, parValue, precision_err, parError, relErrorStr)
        
        else :
            
            newStr = "%+0.*f" %(precision_val, parValue)
        
        formulaStr = formulaStr.replace(strToReplace, newStr)
        
        
        # If there is no sign before the parameter
        strToReplace = "[%s]" %(parName)
        
        if (withError) :
            
            newStr = "%0.*f [%0.*f%s]" %(precision_val, parValue, precision_err, parError, relErrorStr)
        
        else :
            
            newStr = "%0.*f" %(precision_val, parValue)
        
        formulaStr = formulaStr.replace(strToReplace, newStr)
    
    return formulaStr


def plot1D(
    l_histDetail_data = [],
    l_histDetail_mc = [],
    histDetail_mc_statErrPos = 0,
    histDetail_mc_statErrNeg = 0,
    histDetail_mc_systErrPos = 0,
    histDetail_mc_systErrNeg = 0,
    l_histDetail_sig = [],
    stackDrawOption = "nostack",
    drawMCerr = False,
    useDataHistDrawOption = False,
    ratioPlot = False,
    ratioLegendTextSizeScale = 1,
    ratioStatErr = False,
    ratioTotalErr = False,
    drawRatioStatErr = True,
    drawRatioTotalErr = True,
    ratioStatErrLabel = "Stat.",
    ratioTotalErrLabel = "Syst.+Stat.",
    ratioHistDrawOption = "E1",
    ratioHist_ymin = 0,
    ratioHist_ymax = 2,
    fitRatio = "",
    fitRatioLineColor = 1,
    plotFitResult = False,
    title = "",
    xTitle = "", yTitle = "",
    ratioYtitle = "",
    d_colorRatioGridY = {},
    rebinX = 1,
    xMin = initVal, xMax = initVal,
    yMin = initVal, yMax = initVal,
    logX = False, logY = False,
    gridX = False, gridY = False,
    nDivisionsX = [0, 0, 0], nDivisionsY = [0, 0, 0],
    centerLabelsX = False, centerLabelsY = False,
    drawLegend = True,
    legendTitle = "",
    legendBorder = 1,
    legendTextSize = -1,
    legendPos = "UR",
    legendNcolumn = 1,
    dataLegendFirst = False,
    drawRatioLegend = True,
    fixAlphanumericBinLabels = False,
    CMSextraText = "",
    lumiText = "",
    outFileName = "outFile",
    outFileName_suffix = "",
    ) :
    
    ROOT.gStyle.SetOptStat(0)
    
    tdrstyle.setTDRStyle()
    
    ROOT.gStyle.SetHatchesSpacing(7*ROOT.gStyle.GetHatchesSpacing())
    ROOT.gStyle.SetHatchesLineWidth(1)
    
    canvas = TCanvas("canvas", "canvas")
    #canvas.SetCanvasSize(800, 600)
    
    if (ratioPlot and not len(l_histDetail_data)) :
        
        print "Error in plot1D: l_histDetail_data cannot be empty if ratioPlot is True."
        exit(1)
    
    if (ratioPlot) :
        
        canvas.Divide(1, 2);
        
        canvas.cd(1).SetPad(0, 0.32, 1, 0.975);
        canvas.cd(1).SetBottomMargin(0)
        
        canvas.cd(2).SetPad(0, 0.0, 1, 0.315);
        canvas.cd(2).SetTopMargin(0.05)
        canvas.cd(2).SetBottomMargin(0.285)
    
    
    canvas.SetLeftMargin(0.125)
    canvas.SetRightMargin(0.05)
    
    if (ratioPlot) :
        
        canvas.cd(1).SetLeftMargin(0.125)
        canvas.cd(1).SetRightMargin(0.05)
        
        canvas.cd(2).SetLeftMargin(0.125)
        canvas.cd(2).SetRightMargin(0.05)
    
    canvas.cd(1)
    
    legend = 0
    
    if (ratioPlot) :
        
        if(legendPos == "UR") :
            
            legend = TLegend(0.6, 0.6, 0.945, 0.94)
            
            if (legendNcolumn > 1) :
                
                legend = TLegend(0.3, 0.6, 0.945, 0.94)
        
        elif(legendPos == "LR") :
            
            legend = TLegend(0.6, 0.025, 0.945, 0.365)
            
            if (legendNcolumn > 1) :
                
                legend = TLegend(0.3, 0.025, 0.945, 0.365)
            
        elif(legendPos == "LL") :
            
            legend = TLegend(0.15, 0.025, 0.495, 0.365)
            
            if (legendNcolumn > 1) :
                
                legend = TLegend(0.15, 0.025, 0.795, 0.365)
        
        else :
            
            print "Wrong legend position option:", legendPos
            exit(1)
    
    else :
        
        if(legendPos == "UR") :
            
            legend = TLegend(0.55, 0.65, 0.925, 0.925)
            
            if (legendNcolumn > 1) :
                
                legend = TLegend(0.3, 0.65, 0.925, 0.925)
        
        elif(legendPos == "LR") :
            
            legend = TLegend(0.55, 0.05, 0.925, 0.3)
            
        elif(legendPos == "LL") :
            
            legend = TLegend(0.15, 0.15, 0.525, 0.425)
        
        else :
            
            print "Wrong legend position option:", legendPos
            exit(1)
    
    if (legendTextSize > 0) :
        
        legend.SetTextSize(legendTextSize)
    
    else :
        
        legend.SetTextSize(0.06)
    
    if (legendNcolumn > 1) :
        
        legend.SetNColumns(legendNcolumn)
    
    #legend.SetFillStyle(0)
    legend.SetBorderSize(legendBorder)
    
    # VERY important
    # Otherwise, seg-faults when accessing GetListOfPrimitives(), etc.
    ROOT.SetOwnership(legend, 0)
    
    # stack_mc
    stack_mc = THStack()
    
    if (fixAlphanumericBinLabels) :
        
        h1_temp = TH1F("temp", "temp", l_histDetail_mc[0].hist.GetXaxis().GetNbins(), l_histDetail_mc[0].hist.GetXaxis().GetXmin(), l_histDetail_mc[0].hist.GetXaxis().GetXmax())
        stack_mc.Add(h1_temp)
    
    for iHist in range(0, len(l_histDetail_mc)) :
        
        if (rebinX > 1) :
            
            l_histDetail_mc[iHist].hist.Rebin(rebinX)
        
        print "MC (%s) bin %d, %0.4f, %0.4f" %(l_histDetail_mc[iHist].histLabel, 1, l_histDetail_mc[iHist].hist.GetBinContent(1), l_histDetail_mc[iHist].hist.GetBinError(1))
        print "MC (%s) bin %d, %0.4f, %0.4f" %(l_histDetail_mc[iHist].histLabel, 4, l_histDetail_mc[iHist].hist.GetBinContent(4), l_histDetail_mc[iHist].hist.GetBinError(4))
        print "MC (%s) bin %d, %0.4f, %0.4f" %(l_histDetail_mc[iHist].histLabel, 5, l_histDetail_mc[iHist].hist.GetBinContent(5), l_histDetail_mc[iHist].hist.GetBinError(5))
        print ""
        
        #####if (l_histDetail_mc[iHist].histLabel == "DY+jets") :
        #####    
        #####    l_histDetail_mc[iHist].hist.SetBinError(4, 0.0)
        
        l_histDetail_mc[iHist].hist.SetLineColor(l_histDetail_mc[iHist].color)
        l_histDetail_mc[iHist].hist.SetLineStyle(l_histDetail_mc[iHist].lineStyle)
        l_histDetail_mc[iHist].hist.SetLineWidth(l_histDetail_mc[iHist].lineWidth)
        
        if (l_histDetail_mc[iHist].markerStyle >= 0) :
            
            l_histDetail_mc[iHist].hist.SetMarkerStyle(l_histDetail_mc[iHist].markerStyle)
        
        l_histDetail_mc[iHist].hist.SetMarkerColor(l_histDetail_mc[iHist].color)
        
        if (stackDrawOption != "nostack") :
            
            l_histDetail_mc[iHist].hist.SetLineWidth(0)
            l_histDetail_mc[iHist].hist.SetFillColor(l_histDetail_mc[iHist].color)
        
        stack_mc.Add(l_histDetail_mc[iHist].hist, l_histDetail_mc[iHist].drawOption)
        legend.AddEntry(l_histDetail_mc[iHist].hist, l_histDetail_mc[iHist].histLabel)
    
    # Draw stack_mc
    stack_mc.Draw("%s" %(stackDrawOption))
    
    if (fixAlphanumericBinLabels) :
        
        stack_mc.GetXaxis().SetLabelSize(0.1)
        stack_mc.GetXaxis().LabelsOption("v")
        
        for iBin in range(0, stack_mc.GetXaxis().GetNbins()) :
            
            stack_mc.GetXaxis().SetBinLabel(iBin+1, l_histDetail_mc[0].hist.GetXaxis().GetBinLabel(iBin+1))
    
    stack_mc.GetXaxis().SetTitle(xTitle)
    stack_mc.GetYaxis().SetTitle(yTitle)
    
    if (ratioPlot) :
        
        stack_mc.GetXaxis().SetTitleOffset(1.2)
        stack_mc.GetYaxis().SetTitleOffset(1)
    
    else :
        
        stack_mc.GetXaxis().SetLabelSize(0.045)
        stack_mc.GetXaxis().SetTitleSize(0.0475)
        stack_mc.GetXaxis().SetTitleOffset(1.02)
        
        stack_mc.GetYaxis().SetLabelSize(0.035)
        stack_mc.GetYaxis().SetTitleSize(0.045)
        stack_mc.GetYaxis().SetTitleOffset(1.3)
    
    stack_mc.SetTitle(title)
    
    # X range
    if (xMin != initVal and xMax != initVal) :
        
        stack_mc.GetXaxis().SetRangeUser(
            xMin,
            xMax
        )
    
    elif (xMin != initVal) :
        
        stack_mc.GetXaxis().SetRangeUser(
            xMin,
            stack_mc.GetXaxis().GetXmax()
        )
    
    elif (xMax != initVal) :
        
        stack_mc.GetXaxis().SetRangeUser(
            stack_mc.GetXaxis().GetXmin(),
            xMax
        )
    
    # Y range
    if (yMin != initVal) :
        
        stack_mc.SetMinimum(yMin)
    
    if (yMax != initVal) :
        
        stack_mc.SetMaximum(yMax)
    
    stack_mc.GetXaxis().CenterTitle(True)
    stack_mc.GetYaxis().CenterTitle(True)
    
    #ROOT.TGaxis.SetMaxDigits(3)
    #stack_mc.GetXaxis().SetMaxDigits(3)
    
    # Axis divisions
    if (abs(sum(nDivisionsX)) > 0) :
        
        stack_mc.GetXaxis().SetNdivisions(nDivisionsX[0], nDivisionsX[1], nDivisionsX[2])
    
    if (abs(sum(nDivisionsY)) > 0) :
        
        stack_mc.GetYaxis().SetNdivisions(nDivisionsY[0], nDivisionsY[1], nDivisionsY[2])
    
    # Bin label position
    if (centerLabelsX) :
        
        stack_mc.GetXaxis().CenterLabels()
    
    if (centerLabelsY) :
        
        stack_mc.GetYaxis().CenterLabels()
    
    if (ratioPlot) :
        
        stack_mc.GetXaxis().SetLabelSize(0)
    
    
    if (drawMCerr) :
        
        h1_den = stack_mc.GetStack().Last().Clone()
        h1_den.Sumw2()
        
        gr_mc_totalErr = TGraphAsymmErrors(h1_den.GetNbinsX())
        
        for iBin in range(0, h1_den.GetNbinsX()) :
            
            binErrorDen = h1_den.GetBinError(iBin+1)
            
            binErrorPosDen = 0
            binErrorNegDen = 0
            
            if (ratioStatErr and histDetail_mc_statErrPos and histDetail_mc_statErrNeg) :
                
                binErrorPosDen = numpy.sqrt(
                    histDetail_mc_statErrPos.hist.GetBinContent(iBin+1)**2 +
                    histDetail_mc_systErrPos.hist.GetBinContent(iBin+1)**2
                )
                
                binErrorNegDen = numpy.sqrt(
                    histDetail_mc_statErrNeg.hist.GetBinContent(iBin+1)**2 +
                    histDetail_mc_systErrNeg.hist.GetBinContent(iBin+1)**2
                )
            
            else :
                
                binErrorPosDen = numpy.sqrt(
                    binErrorDen**2 +
                    histDetail_mc_systErrPos.hist.GetBinContent(iBin+1)**2
                )
                
                binErrorNegDen = numpy.sqrt(
                    binErrorDen**2 +
                    histDetail_mc_systErrNeg.hist.GetBinContent(iBin+1)**2
                )
            
            gr_mc_totalErr.SetPoint(iBin, h1_den.GetBinCenter(iBin+1), h1_den.GetBinContent(iBin+1))
            
            gr_mc_totalErr.SetPointEXhigh(iBin, h1_den.GetBinWidth(iBin+1) / 2.0)
            gr_mc_totalErr.SetPointEXlow(iBin, h1_den.GetBinWidth(iBin+1) / 2.0)
            
            gr_mc_totalErr.SetPointEYhigh(iBin, binErrorPosDen)
            gr_mc_totalErr.SetPointEYlow(iBin, binErrorNegDen)
            
        
        #gr_mc_totalErr.SetFillStyle(3005)
        gr_mc_totalErr.SetFillStyle(3354)
        #gr_mc_totalErr.SetFillColorAlpha(16, 0.5)
        gr_mc_totalErr.SetMarkerSize(0)
        gr_mc_totalErr.SetLineWidth(0)
        gr_mc_totalErr.Draw("E2")
        
        legend.AddEntry(gr_mc_totalErr, "Bkg. uncertainty")
    
    
    # Signal histograms
    for iHist in range(0, len(l_histDetail_sig)) :
        
        if (rebinX > 1) :
            
            l_histDetail_sig[iHist].hist.Rebin(rebinX)
        
        print "Sig %0.4f, %0.4f \n" %(l_histDetail_sig[iHist].hist.GetBinContent(2), l_histDetail_sig[iHist].hist.GetBinError(2))
        
        l_histDetail_sig[iHist].hist.SetLineColor(l_histDetail_sig[iHist].color)
        l_histDetail_sig[iHist].hist.SetLineStyle(l_histDetail_sig[iHist].lineStyle)
        l_histDetail_sig[iHist].hist.SetLineWidth(l_histDetail_sig[iHist].lineWidth)
        l_histDetail_sig[iHist].hist.SetFillStyle(0)
        
        legend.AddEntry(l_histDetail_sig[iHist].hist, l_histDetail_sig[iHist].histLabel, "l")
        
        l_histDetail_sig[iHist].hist.Draw("same " + l_histDetail_sig[iHist].drawOption)
        #l_histDetail_sig[iHist].hist.Draw("same ALP")
    
    
    if (dataLegendFirst) :
        
        legend_temp = legend.Clone()
        legend.Clear()
    
    
    # Data histograms
    for iHist in range(0, len(l_histDetail_data)) :
        
        if (rebinX > 1) :
            
            l_histDetail_data[iHist].hist.Rebin(rebinX)
        
        #print "Data %0.4f, %0.4f \n" %(l_histDetail_data[iHist].hist.GetBinContent(2), l_histDetail_data[iHist].hist.GetBinError(2))
        print "Total data: %0.4f \n" %(l_histDetail_data[iHist].hist.Integral())
        
        l_histDetail_data[iHist].hist.SetLineColor(l_histDetail_data[iHist].color)
        l_histDetail_data[iHist].hist.SetLineStyle(l_histDetail_data[iHist].lineStyle)
        l_histDetail_data[iHist].hist.SetLineWidth(l_histDetail_data[iHist].lineWidth)
        
        if (l_histDetail_data[iHist].markerStyle >= 0) :
            
            l_histDetail_data[iHist].hist.SetMarkerStyle(l_histDetail_data[iHist].markerStyle)
        
        else :
            
            l_histDetail_data[iHist].hist.SetMarkerStyle(20)
        
        l_histDetail_data[iHist].hist.SetMarkerColor(l_histDetail_data[iHist].color)
        
        
        if (useDataHistDrawOption) :
            
            dataHistDrawOption = l_histDetail_data[iHist].drawOption
        
        else :
            
            dataHistDrawOption = "E1"
        
        
        l_histDetail_data[iHist].hist.Draw("same %s" %(dataHistDrawOption))
        
        legend.AddEntry(l_histDetail_data[iHist].hist, l_histDetail_data[iHist].histLabel, "LPE")
        
        #legendEntries = legend.GetListOfPrimitives()
        #legendEntries.AddAt(legendEntries.Last(), 0)
        #legendEntries.AddFirst(legendEntries.Last())
        #legendEntries.Remove(legendEntries.Last())
        
        if (ratioPlot) :
            
            l_histDetail_data[iHist].hist.GetXaxis().SetLabelSize(0)
    
    
    if (dataLegendFirst) :
        
        legendEntries = legend_temp.GetListOfPrimitives()
        
        for iLegendEntry in range(0, legendEntries.GetSize()) :
            
            legend.AddEntry(
                legendEntries.At(iLegendEntry).GetObject(),
                legendEntries.At(iLegendEntry).GetLabel(),
                legendEntries.At(iLegendEntry).GetOption(),
            )
    
    
    canvas.cd(1).SetLogx(logX)
    canvas.cd(1).SetLogy(logY)
    
    canvas.cd(1).SetGridx(gridX)
    canvas.cd(1).SetGridy(gridY)
    
    # VERY important
    # Otherwise, seg-faults when accessing GetListOfPrimitives(), etc.
    #ROOT.SetOwnership(legend, 0)
    
    if (len(legendTitle)) :
        
        legend.SetHeader(legendTitle);
        legendHeader = legend.GetListOfPrimitives().First()
        legendHeader.SetTextAlign(22)
    
    
    if (drawLegend) :
        
        legend.Draw()
    
    
    legendFitResult = TLegend(0.15, 0.79, 0.475, 0.925)
    legendFitResult.SetBorderSize(legendBorder)
    
    # Ratio plot
    if (ratioPlot) :
        
        canvas.cd(2)
        #print stack_mc.GetStack().Last().Integral
        
        stack_ratio = THStack()
        
        gr_ratio_statErr = TGraphAsymmErrors(l_histDetail_data[0].hist.GetNbinsX())
        gr_ratio_totalErr = TGraphAsymmErrors(l_histDetail_data[0].hist.GetNbinsX())
        
        for iHist in range(0, len(l_histDetail_data)) :
            
            #l_histDetail_data[iHist].hist.SetLineColor(l_histDetail_data[iHist].color)
            #l_histDetail_data[iHist].hist.SetLineStyle(l_histDetail_data[iHist].lineStyle)
            #l_histDetail_data[iHist].hist.SetLineWidth(l_histDetail_data[iHist].lineWidth)
            #
            #l_histDetail_data[iHist].hist.SetMarkerStyle(20)
            #l_histDetail_data[iHist].hist.SetMarkerColor(l_histDetail_data[iHist].color)
            #
            #legend.AddEntry(l_histDetail_data[iHist].hist, l_histDetail_data[iHist].histLabel)
            
            h1_ratio = l_histDetail_data[iHist].hist.Clone()
            h1_ratio.Sumw2()
            
            if (len(l_histDetail_data) == 1) :
                
                h1_ratio.SetLineStyle(1)
                h1_ratio.SetLineColor(1)
                h1_ratio.SetMarkerColor(1)
            
            h1_den = stack_mc.GetStack().Last().Clone()
            h1_den.Sumw2()
            
            print "Total MC: %0.4f \n" %(h1_den.Integral())
            
            #print h1_ratio.GetBinContent(8), h1_ratio.GetBinError(8)
            #sprint h1_den.GetBinContent(8), h1_den.GetBinError(8)
            
            h1_ratio.Divide(h1_den)
            
            for iBin in range(0, h1_ratio.GetNbinsX()) :
                
                binContentNum = l_histDetail_data[iHist].hist.GetBinContent(iBin+1)
                binErrorNum = l_histDetail_data[iHist].hist.GetBinError(iBin+1)
                
                binContentDen = h1_den.GetBinContent(iBin+1)
                binErrorDen = h1_den.GetBinError(iBin+1)
                
                binContentRatio = h1_ratio.GetBinContent(iBin+1)
                binErrorRatio = h1_ratio.GetBinError(iBin+1)
                
                binErrorRatioByHand = 0
                
                if (binContentNum > 0 and binContentDen > 0) :
                    
                    binErrorRatioByHand = binContentRatio * numpy.sqrt((float(binErrorNum)/binContentNum)**2 + (float(binErrorDen)/binContentDen)**2)
                
                #print ("XXXXX Bin %d: num %0.2e (err %0.2e), \t den %0.2e (err %.2e), \t ratio %0.2e (err %0.2e, errByHand %0.2e)" %(
                #    iBin+1,
                #    
                #    binContentNum,
                #    binErrorNum,
                #    
                #    binContentDen,
                #    binErrorDen,
                #    
                #    binContentRatio,
                #    binErrorRatio,
                #    binErrorRatioByHand
                #)).expandtabs(10)
                
                
                if (ratioStatErr) :
                    
                    if (binContentNum) :
                        
                        binErrorRatio = binContentRatio * binErrorNum/binContentNum
                        
                        h1_ratio.SetBinError(iBin+1, binErrorRatio)
                    
                    gr_ratio_statErr.SetPoint(iBin, h1_ratio.GetBinCenter(iBin+1), 1.0)
                    
                    #print "*****", iBin+1, histDetail_mc_statErrPos.hist.GetBinContent(iBin+1), histDetail_mc_statErrNeg.hist.GetBinContent(iBin+1)
                    #print "#####", iBin+1, h1_ratio.GetBinContent(iBin+1), h1_ratio_statErrNeg.GetBinContent(iBin+1), h1_ratio_statErrPos.GetBinContent(iBin+1)
                    
                    ratioErrPos = 0
                    ratioErrNeg = 0
                    
                    if (binContentNum and binContentDen) :
                        
                        binErrorPosDen = binErrorDen
                        binErrorNegDen = binErrorDen
                        
                        if (histDetail_mc_statErrPos and histDetail_mc_statErrNeg) :
                            
                            binErrorPosDen = histDetail_mc_statErrPos.hist.GetBinContent(iBin+1)
                            binErrorNegDen = histDetail_mc_statErrNeg.hist.GetBinContent(iBin+1)
                        
                        # Use relative error for the band
                        #####binContentRatio_mod = binContentRatio
                        binContentRatio_mod = 1
                        
                        # Uncertainty due to bkg. only
                        ratioErrPos = binContentRatio_mod * numpy.sqrt(
                            #(binErrorNum/binContentNum)**2 +
                            (binErrorPosDen/binContentDen)**2
                        )
                        
                        ratioErrNeg = binContentRatio_mod * numpy.sqrt(
                            #(binErrorNum/binContentNum)**2 +
                            (binErrorNegDen/binContentDen)**2
                        )
                    
                    gr_ratio_statErr.SetPointEXhigh(iBin, h1_ratio.GetBinWidth(iBin+1) / 2.0)
                    gr_ratio_statErr.SetPointEXlow(iBin, h1_ratio.GetBinWidth(iBin+1) / 2.0)
                    
                    #gr_ratio_statErr.SetPointEYhigh(iBin, abs(h1_ratio_statErrNeg.GetBinContent(iBin+1)))
                    #gr_ratio_statErr.SetPointEYlow(iBin, abs(h1_ratio_statErrPos.GetBinContent(iBin+1)))
                    
                    gr_ratio_statErr.SetPointEYhigh(iBin, ratioErrPos)
                    gr_ratio_statErr.SetPointEYlow(iBin, ratioErrNeg)
                
                if (ratioTotalErr) :
                    
                    gr_ratio_totalErr.SetPoint(iBin, h1_ratio.GetBinCenter(iBin+1), 1.0)
                    
                    #if (binContentNum and binContentDen) :
                    if (binContentDen) :
                        
                        binErrorPosDen = 0
                        binErrorNegDen = 0
                        
                        if (ratioStatErr and histDetail_mc_statErrPos and histDetail_mc_statErrNeg) :
                            
                            binErrorPosDen = numpy.sqrt(
                                histDetail_mc_statErrPos.hist.GetBinContent(iBin+1)**2 +
                                histDetail_mc_systErrPos.hist.GetBinContent(iBin+1)**2
                            )
                            
                            binErrorNegDen = numpy.sqrt(
                                histDetail_mc_statErrNeg.hist.GetBinContent(iBin+1)**2 +
                                histDetail_mc_systErrNeg.hist.GetBinContent(iBin+1)**2
                            )
                        
                        else :
                            
                            binErrorPosDen = numpy.sqrt(
                                binErrorDen**2 +
                                histDetail_mc_systErrPos.hist.GetBinContent(iBin+1)**2
                            )
                            
                            binErrorNegDen = numpy.sqrt(
                                binErrorDen**2 +
                                histDetail_mc_systErrNeg.hist.GetBinContent(iBin+1)**2
                            )
                        
                        # Use relative error for the band
                        #####binContentRatio_mod = binContentRatio
                        binContentRatio_mod = 1
                        
                        # Uncertainty due to bkg. only
                        ratioErrPos = binContentRatio_mod * numpy.sqrt(
                            #(binErrorNum/binContentNum)**2 +
                            (binErrorPosDen/binContentDen)**2
                        )
                        
                        ratioErrNeg = binContentRatio_mod * numpy.sqrt(
                            #(binErrorNum/binContentNum)**2 +
                            (binErrorNegDen/binContentDen)**2
                        )
                    
                    gr_ratio_totalErr.SetPointEXhigh(iBin, h1_ratio.GetBinWidth(iBin+1) / 2.0)
                    gr_ratio_totalErr.SetPointEXlow(iBin, h1_ratio.GetBinWidth(iBin+1) / 2.0)
                    
                    gr_ratio_totalErr.SetPointEYhigh(iBin, ratioErrPos)
                    gr_ratio_totalErr.SetPointEYlow(iBin, ratioErrNeg)
                
                #if (rationSystErr) :
                #    
                #    binErrorRatio_systPos = 0
                #    binErrorRatio_systNeg = 0
            
            print "Ratio %0.4f, %0.4f \n" %(h1_ratio.GetBinContent(2), h1_ratio.GetBinError(2))
            
            if (fitRatio != "") :
                
                h1_ratio.Fit(fitRatio)
                h1_ratio.GetFunction(fitRatio).SetLineColor(fitRatioLineColor)
                h1_ratio.GetFunction(fitRatio).SetLineWidth(2)
                h1_ratio.GetFunction(fitRatio).SetMarkerColor(fitRatioLineColor)
                h1_ratio.GetFunction(fitRatio).SetMarkerSize(0)
                
                fitResultStr =  getFormulaStr(
                    h1_ratio.GetFunction(fitRatio),
                    precision_val = 4,
                    precision_err = 4,
                )
                
                print fitResultStr
                
                legendFitResult.AddEntry(h1_ratio.GetFunction(fitRatio), fitResultStr)
            
            
            stack_ratio.Add(h1_ratio, ratioHistDrawOption)
        
        
        stack_ratio.Draw("nostack")
        
        stack_ratio.GetXaxis().SetLabelSize(0.1)
        stack_ratio.GetYaxis().SetLabelSize(0.1)
        
        stack_ratio.GetXaxis().SetTitle(xTitle)
        stack_ratio.GetXaxis().SetTitleSize(0.13)
        stack_ratio.GetXaxis().SetTitleOffset(0.91)
        
        if (fixAlphanumericBinLabels) :
            
            stack_ratio.GetXaxis().SetLabelSize(0.2)
            #stack_ratio.GetXaxis().LabelsOption("v")
        
        if (not len(ratioYtitle)) :
            
            stack_ratio.GetYaxis().SetTitle("Data / MC")
        
        else :
            
            stack_ratio.GetYaxis().SetTitle(ratioYtitle)
        
        stack_ratio.GetYaxis().SetTitleSize(0.126)
        stack_ratio.GetYaxis().SetTitleOffset(0.475)
        
        stack_ratio.SetMinimum(ratioHist_ymin)
        stack_ratio.SetMaximum(ratioHist_ymax)
        
        stack_ratio.GetYaxis().SetNdivisions(6, 5, 0)
        
        # X range
        if (xMin != initVal and xMax != initVal) :
            
            stack_ratio.GetXaxis().SetRangeUser(
                xMin,
                xMax
            )
        
        elif (xMin != initVal) :
            
            stack_ratio.GetXaxis().SetRangeUser(
                xMin,
                stack_ratio.GetXaxis().GetXmax()
            )
        
        elif (xMax != initVal) :
            
            stack_ratio.GetXaxis().SetRangeUser(
                stack_ratio.GetXaxis().GetXmin(),
                xMax
            )
        
        stack_ratio.GetXaxis().CenterTitle(True)
        stack_ratio.GetYaxis().CenterTitle(True)
        
        # Bin label position
        if (centerLabelsX) :
            
            stack_ratio.GetXaxis().CenterLabels()
        
        if (centerLabelsY) :
            
            stack_ratio.GetYaxis().CenterLabels()
        
        canvas.cd(2).SetGridx(gridX)
        canvas.cd(2).SetGridy(gridY)
        
        legendRatio = 0
        
        if (ratioTotalErr or ratioStatErr) :
            
            legendRatio = TLegend(0.15, 0.79, 0.475, 0.925)
            
            if (legendTextSize > 0) :
                
                legendRatio.SetTextSize(ratioLegendTextSizeScale*legendTextSize)
            
            else :
                
                legendRatio.SetTextSize(0.06)
            
            legendRatio.SetBorderSize(legendBorder)
            
            legendRatio.SetNColumns(2)
        
        # Draw the uncertainty band
        if (ratioTotalErr and drawRatioTotalErr) :
            
            gr_ratio_totalErr.SetFillColor(16)
            gr_ratio_totalErr.SetMarkerSize(0)
            gr_ratio_totalErr.SetLineWidth(0)
            
            if (not drawRatioStatErr) :
                
                gr_ratio_totalErr.SetFillColor(1)
                #gr_ratio_totalErr.SetFillStyle(3005)
                gr_ratio_totalErr.SetFillStyle(3354)
            
            gr_ratio_totalErr.Draw("E2")
            
            legendRatio.AddEntry(gr_ratio_totalErr, ratioTotalErrLabel, "f")
        
        if (ratioStatErr and drawRatioStatErr) :
            
            #gr_ratio_statErr.SetFillColor(0)
            #gr_ratio_statErr.SetFillStyle(3005)
            gr_ratio_statErr.SetFillStyle(3354)
            gr_ratio_statErr.SetMarkerSize(0)
            gr_ratio_statErr.SetLineWidth(0)
            gr_ratio_statErr.Draw("E2")
            
            legendRatio.AddEntry(gr_ratio_statErr, ratioStatErrLabel)
        
        
        # Draw coloured gridlines
        for lineKey in d_colorRatioGridY.keys() :
            
            tempLine = ROOT.TF1("line%f" %(lineKey), "%f" %(lineKey), stack_mc.GetXaxis().GetXmin(), stack_mc.GetXaxis().GetXmax())
            
            tempLine.SetLineWidth(2)
            tempLine.SetLineColor(d_colorRatioGridY[lineKey]["color"])
            
            tempLine.Draw("same")
        
        # Redraw to put the coloured grid lines below the ratio
        if (len(d_colorRatioGridY) or ratioStatErr or ratioTotalErr) :
            
            stack_ratio.Draw("nostack same")
        
        
        if (drawRatioLegend and (ratioTotalErr or ratioStatErr)) :
            
            legendRatio.Draw()
        
        
        if (plotFitResult) :
            
            legendFitResult.Draw()
        
        
    # CMS label
    CMS_lumi.CMS_lumi(pad = canvas, iPeriod = 0, iPosX = 0, CMSextraText = CMSextraText, lumiText = lumiText)
    
    outFileName = outFileName + ("_"*(outFileName_suffix != "")) + outFileName_suffix + ".pdf"
    print "Output:", outFileName
    
    canvas.SaveAs(outFileName)
    
    print "\n"


def plot2D(histDetails) :
    
    canvas = TCanvas("canvas", "canvas")
    canvas.SetCanvasSize(800, 600)
    
    histDetails.hist.SetStats(False)
    
    # X range
    if (histDetails.xMin != initVal and histDetails.xMax != initVal) :
        
        histDetails.hist.GetXaxis().SetRangeUser(
            histDetails.xMin,
            histDetails.xMax
        )
    
    elif (histDetails.xMin != initVal) :
        
        histDetails.hist.GetXaxis().SetRangeUser(
            histDetails.xMin,
            histDetails.hist.GetXaxis().GetXmax()
        )
    
    elif (histDetails.xMax != initVal) :
        
        histDetails.hist.GetXaxis().SetRangeUser(
            histDetails.hist.GetXaxis().GetXmin(),
            histDetails.xMax
        )
    
    # Y range
    if (histDetails.yMin != initVal and histDetails.yMax != initVal) :
        
        histDetails.hist.GetYaxis().SetRangeUser(
            histDetails.yMin,
            histDetails.yMax
        )
    
    elif (histDetails.yMin != initVal) :
        
        histDetails.hist.GetYaxis().SetRangeUser(
            histDetails.yMin,
            histDetails.hist.GetYaxis().GetXmax()
        )
    
    elif (histDetails.yMax != initVal) :
        
        histDetails.hist.GetYaxis().SetRangeUser(
            histDetails.hist.GetYaxis().GetXmin(),
            histDetails.yMax
        )
    
    # Z range
    if (histDetails.zMin != initVal) :
        
        histDetails.hist.SetMinimum(histDetails.zMin)
    
    if (histDetails.zMax != initVal) :
        
        histDetails.hist.SetMaximum(histDetails.zMax)
    
    # Axis divisions
    if (abs(sum(histDetails.nDivisionsX)) > 0) :
        
        histDetails.hist.GetXaxis().SetNdivisions(histDetails.nDivisionsX[0], histDetails.nDivisionsX[1], histDetails.nDivisionsX[2])
    
    if (abs(sum(histDetails.nDivisionsY)) > 0) :
        
        histDetails.hist.GetYaxis().SetNdivisions(histDetails.nDivisionsY[0], histDetails.nDivisionsY[1], histDetails.nDivisionsY[2])
    
    # Bin label position
    if (histDetails.centerLabelsX) :
        
        histDetails.hist.GetXaxis().CenterLabels()
    
    if (histDetails.centerLabelsY) :
        
        histDetails.hist.GetYaxis().CenterLabels()
    
    histDetails.hist.GetXaxis().SetTitle(histDetails.xTitle)
    histDetails.hist.GetXaxis().SetTitleSize(0.05)
    histDetails.hist.GetXaxis().SetTitleOffset(0.8)
    
    histDetails.hist.GetYaxis().SetTitle(histDetails.yTitle)
    histDetails.hist.GetYaxis().SetTitleSize(0.05)
    histDetails.hist.GetYaxis().SetTitleOffset(1.0)
    
    histDetails.hist.GetXaxis().CenterTitle(True)
    histDetails.hist.GetYaxis().CenterTitle(True)
    
    #histDetails.hist.SetStats(0)
    histDetails.hist.SetTitle(histDetails.histTitle)
    
    #ROOT.TGaxis.SetMaxDigits(3)
    
    canvas.SetLogx(histDetails.logX)
    canvas.SetLogy(histDetails.logY)
    canvas.SetLogz(histDetails.logZ)
    
    canvas.SetGridx(histDetails.gridX)
    canvas.SetGridy(histDetails.gridY)
    
    #canvas.SetRightMargin(0.13)
    #canvas.SetRightMargin(0.05)
    
    histDetails.hist.Draw(histDetails.drawOption)
    
    outFileName = histDetails.outFileName + ("_"*(histDetails.outFileName_suffix != "")) + histDetails.outFileName_suffix + ".pdf"
    print "Output:", outFileName
    
    canvas.SaveAs(outFileName)
    
    print "\n"


def getCorrStr(systName, era, isCorr) :
    
    corrStr = ""
    
    if (isCorr) :
        
        corrStr = "%s" %(systName)
    
    else :
        
        if (len(era)) :
            
            corrStr = "syst%s_%s" %(era, systName)
            
        else :
            
            corrStr = systName
    
    
    return corrStr


def getErrorHist(hist_nominal, l_hist_up = [], l_hist_down = [], errPercent = False) :
    
    if (len(l_hist_up) != len(l_hist_down)) :
        
        print "Error in Common.getErrorHist(...): List of up and down histograms must have the same length."
        exit(1)
    
    nVariation = len(l_hist_up)
    
    hist_errUp = hist_nominal.Clone()
    hist_errUp.SetName("%s_errUp" %(hist_errUp.GetName()))
    hist_errUp.SetTitle("%s [errUp]" %(hist_errUp.GetTitle()))
    hist_errUp.Reset()
    hist_errUp.SetDirectory(0)
    
    hist_errDown = hist_nominal.Clone()
    hist_errDown.SetName("%s_errDown" %(hist_errDown.GetName()))
    hist_errDown.SetTitle("%s [errDown]" %(hist_errDown.GetTitle()))
    hist_errDown.Reset()
    hist_errDown.SetDirectory(0)
    
    for iVariation in range(0, nVariation) :
        
        nBin = hist_nominal.GetNbinsX()
        
        # Include over/underflow bins
        for iBin in range(0, nBin+1) :
            
            binVal_nominal = hist_nominal.GetBinContent(iBin)
            
            binVal_errUp = l_hist_up[iVariation].GetBinContent(iBin)
            errUp = abs(binVal_nominal - binVal_errUp)
            errUp_current = hist_errUp.GetBinContent(iBin)
            errUp_mod = sqrt(errUp_current*errUp_current + errUp*errUp)
            hist_errUp.SetBinContent(iBin, binVal_nominal+errUp_mod)
            
            
            binVal_errDown = l_hist_down[iVariation].GetBinContent(iBin)
            errDown = abs(binVal_nominal - binVal_errDown)
            errDown_current = hist_errDown.GetBinContent(iBin)
            errDown_mod = sqrt(errDown_current*errDown_current + errDown*errDown)
            hist_errDown.SetBinContent(iBin, binVal_nominal-errDown_mod)
    
    
    return [hist_errUp, hist_errDown]


def getEraCombinedYields(l_yieldResult) :
    
    nEra = len(l_yieldResult)
    nBin = len(l_yieldResult[0]["yield"])
    
    l_yield = []
    l_error = []
    
    for iBin in range(0, nBin) :
        
        binYield_total = 0
        
        zeroBinError_total = 0
        nonZeroBinError_total = 0
        binError_total = 0
        
        for iEra in range(0, nEra) :
            
            binYield_total += l_yieldResult[iEra]["yield"][iBin]
            
            if (l_yieldResult[iEra]["yield"][iBin]) :
                
                nonZeroBinError_total += l_yieldResult[iEra]["error"][iBin]**2
            
            else :
                
                zeroBinError_total += l_yieldResult[iEra]["error"][iBin]**(-2)
        
        if (zeroBinError_total) :
            
            binError_total = numpy.sqrt(nonZeroBinError_total + 1.0/zeroBinError_total)
        
        else :
            
            binError_total = numpy.sqrt(nonZeroBinError_total)
        
        l_yield.append(binYield_total)
        l_error.append(binError_total)
    
    
    integral_total = 0
    scale_total = 0
    
    for iEra in range(0, nEra) :
        
        integral_total += l_yieldResult[iEra]["integral"]
        scale_total += l_yieldResult[iEra]["scale"] * l_yieldResult[iEra]["integral"]
    
    if (integral_total > 0) :
        
        scale_total /= integral_total
    
    
    d_yieldResult = {}
    
    d_yieldResult["yield"] = l_yield
    d_yieldResult["error"] = l_error
    
    d_yieldResult["integral"] = integral_total
    
    d_yieldResult["scale"] = scale_total
    
    
    return d_yieldResult


def getYields(
    l_rootFile,
    l_xs,
    suffix,
    systStr,
    histName_base,
    detailStr,
    nRegion,
    yieldBinNumber,
    l_rootFile_sig_genMET = [],
    era = "",
    scale = 1,
    fakeComponent = "total",
    fakeWeightHistName = "tauTau_promptFakeEventWeight_reco",
    ll_regionNumber = [],
    negToZero = False,
    debug = False,
    ) :
    
    #l_rootFile = Common.getRootFiles(l_rootFileDir, suffix, rootFileName, debug)
    
    l_yield = []
    l_error = []
    
    d_yieldResult = {}
    
    integral = 0
    integral_error = 0
    
    finalScale = 0
    
    for iRegion in range(0, nRegion) :
        
        if ("fakeEstimation" in l_rootFile[0].GetName()) :
            
            histName = "%s%d" %(histName_base, iRegion+1)
            
            # Nominal
            h1 = HistogramDetails(l_rootFile = l_rootFile, histName = histName)
            h1.getFakeEstimationHistogram(
                suffix = detailStr,
                scale = scale,
                debug = debug,
                component = fakeComponent
            )
            
            #h1_pos = Common.HistogramDetails(l_rootFile = l_rootFile, histName = histName)
            #h1_pos.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "pos"
            #)
            #
            #h1_neg = Common.HistogramDetails(l_rootFile = l_rootFile, histName = histName)
            #h1_neg.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "neg"
            #)
            
            
            binVal = h1.hist.GetBinContent(yieldBinNumber)
            #binVal_pos = h1_pos.hist.GetBinContent(yieldBinNumber)
            #binVal_neg = h1_neg.hist.GetBinContent(yieldBinNumber)
            
            binErr = h1.hist.GetBinError(yieldBinNumber)
            #binErr_pos = h1_pos.hist.GetBinError(yieldBinNumber)
            #binErr_neg = h1_neg.hist.GetBinError(yieldBinNumber)
            
            # Add before setting to zero because we're concerned with the TOTAL sum
            integral += binVal
            
            if (negToZero and binVal < 0) :
                
                binVal = 0
            
            l_yield.append(binVal)
            l_error.append(binErr)
        
        else :
            
            histName = "reco/%s/%s%d_%s" %(detailStr, histName_base, iRegion+1, detailStr)
            nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
            
            #if ("WJets" in l_rootFile[0].GetName() or "DYJets" in l_rootFile[0].GetName()) :
            #    
            #    nEventHistName = ""
            
            
            # Nominal
            h1 = HistogramDetails(l_rootFile = l_rootFile, l_xs = l_xs, histName = histName, era = era)
            h1.getHist(
                xsNormalize = (len(l_xs) > 0),
                nEventHistName = nEventHistName,
                negToZero = negToZero,
            )
            h1.hist.Scale(scale)
            
            finalScale = scale * h1.weightSum
            
            if (len(l_rootFile_sig_genMET)) :
                
                h1_sig_genMET = HistogramDetails(l_rootFile = l_rootFile_sig_genMET, l_xs = l_xs, histName = histName, era = era)
                h1_sig_genMET.getHist(
                    xsNormalize = (len(l_xs) > 0),
                    nEventHistName = nEventHistName,
                    negToZero = negToZero,
                )
                h1_sig_genMET.hist.Scale(scale)
                
                # Average
                h1.hist.Add(h1_sig_genMET.hist)
                h1.hist.Scale(0.5)
                
                finalScale = scale * (h1.weightSum + h1_sig_genMET.weightSum) / 2.0
            
            
            binVal = h1.hist.GetBinContent(yieldBinNumber)
            
            # Add before setting to zero because we're concerned with the TOTAL sum
            integral += binVal
            
            if (negToZero and binVal < 0) :
                
                binVal = 0
            
            
            binErr = h1.hist.GetBinError(yieldBinNumber)
            
            
            l_yield.append(binVal)
            l_error.append(binErr)
    
    
    if (negToZero and integral < 0) :
        
        integral = 0
    
    
    # Merge bins
    nRegion_merged = len(ll_regionNumber)
    
    if (nRegion_merged) :
        
        l_yield_merged = []
        l_error_merged = []
        
        for iRegionGroup in range(0, nRegion_merged) :
            
            yield_temp = 0
            error_temp = 0
            
            for iRegion in range(0, len(ll_regionNumber[iRegionGroup])) :
                
                regionNumber = ll_regionNumber[iRegionGroup][iRegion]
                
                yield_temp += l_yield[regionNumber-1]
                error_temp = numpy.sqrt(error_temp**2 + l_error[regionNumber-1]*l_error[regionNumber-1])
            
            #if (yield_temp == 0 and "fakeEstimation" not in l_rootFile[0].GetName()) :
            if (yield_temp == 0) : 
                
                if ("fakeEstimation" in l_rootFile[0].GetName()) :
                    
                    finalScale = 1.0
                    error_temp = -numpy.log((1-0.68)/2.0)
                
                else :
                    
                    # Upper limit at 68% CL
                    error_temp = finalScale * (-numpy.log((1-0.68)/2.0))
            
            l_yield_merged.append(yield_temp)
            l_error_merged.append(error_temp)
        
        l_yield = l_yield_merged
        l_error = l_error_merged
    
    
    d_yieldResult["yield"] = l_yield
    d_yieldResult["error"] = l_error
    
    d_yieldResult["integral"] = integral
    
    d_yieldResult["scale"] = finalScale
    
    
    return d_yieldResult


def getScaleUncertainty(
    l_rootFileDir,
    rootFileName,
    l_xs,
    l_scaleVarIndex,
    suffix,
    histName_base,
    detailStr,
    nRegion,
    yieldBinNumber,
    ll_regionNumber = [],
    debug = False,
    ) :
    
    
    l_rootFile_nominal = getRootFiles(l_rootFileDir, suffix, rootFileName, debug)
    
    yieldInfo_nominal = getYields(
        l_rootFile = l_rootFile_nominal,
        l_xs = l_xs,
        suffix = suffix,
        systStr = "",
        histName_base = histName_base,
        detailStr = detailStr,
        nRegion = nRegion,
        yieldBinNumber = yieldBinNumber,
        scale = 1,
        ll_regionNumber = ll_regionNumber,
        negToZero = True,
        debug = debug,
    )
    
    l_yieldInfo_scaleVar = []
    
    yieldInfo_scaleVar_max = 0
    yieldInfo_scaleVar_min = 0
    
    scaleVarIndex_max = 0
    scaleVarIndex_min = 0
    
    for iScaleVar in range(0, len(l_scaleVarIndex)) :
        
        scaleVarIndex = l_scaleVarIndex[iScaleVar]
        
        suffix_mod = "%s_scale%d" %(suffix, scaleVarIndex)
        l_rootFile_scaleVar = getRootFiles(l_rootFileDir, suffix_mod, rootFileName, debug)
        
        yieldInfo_scaleVar = getYields(
            l_rootFile = l_rootFile_scaleVar,
            l_xs = l_xs,
            suffix = suffix_mod,
            systStr = "",
            histName_base = histName_base,
            detailStr = detailStr,
            nRegion = nRegion,
            yieldBinNumber = yieldBinNumber,
            scale = 1,
            ll_regionNumber = ll_regionNumber,
            negToZero = True,
            debug = debug,
        )
        
        
        if (not yieldInfo_scaleVar_max) :
            
            yieldInfo_scaleVar_max = yieldInfo_scaleVar
        
        elif (yieldInfo_scaleVar["integral"] > yieldInfo_scaleVar_max["integral"]) :
            
            scaleVarIndex_max = scaleVarIndex
            yieldInfo_scaleVar_max = yieldInfo_scaleVar
        
        
        if (not yieldInfo_scaleVar_min) :
            
            yieldInfo_scaleVar_min = yieldInfo_scaleVar
        
        elif (yieldInfo_scaleVar["integral"] < yieldInfo_scaleVar_min["integral"]) :
            
            scaleVarIndex_min = scaleVarIndex
            yieldInfo_scaleVar_min = yieldInfo_scaleVar
        
        
        l_yieldInfo_scaleVar.append(yieldInfo_scaleVar)
        
        for iFile in range(0, len(l_rootFile_scaleVar)) :
            
            l_rootFile_scaleVar[iFile].Close()
    
    
    for iFile in range(0, len(l_rootFile_nominal)) :
        
        l_rootFile_nominal[iFile].Close()
    
    
    d_systResult = {}
    
    l_systUpResult = []
    l_systDownResult = []
    
    
    systUpPercent_mean = 0
    systDownPercent_mean = 0
    
    
    if (len(ll_regionNumber)) :
        
        nRegion = len(ll_regionNumber)
    
    for iRegion in range(0, nRegion) :
        
        binVal_nominal =  yieldInfo_nominal["yield"][iRegion]
        binVal_systUp =  yieldInfo_scaleVar_max["yield"][iRegion]
        binVal_systDown =  yieldInfo_scaleVar_min["yield"][iRegion]
        
        systUp = binVal_systUp - binVal_nominal
        systDown = binVal_systDown - binVal_nominal
        
        systUpPercent = 0
        systDownPercent = 0
        
        # Percent
        if (abs(binVal_nominal) > 0) :
            
            systUpPercent = systUp / binVal_nominal * 100.0
            systDownPercent = systDown / binVal_nominal * 100.0
            
            systUpPercent_mean += binVal_nominal * systUpPercent
            #systUpPercent_mean += binVal_nominal * systUp
            systDownPercent_mean += binVal_nominal * systDownPercent
            #systDownPercent_mean += binVal_nominal * systDown
        
        #else :
        #    
        #    systUpPercent = 100.0
        #    systDownPercent = 0.0
        
        
        # Set -100% error to a small value because 1-1 = 0 and combine complains because of that
        if (systUpPercent == -100) :
            
            systUpPercent = (1e-4 - 1) * 100
        
        if (systDownPercent == -100) :
            
            systDownPercent = (1e-4 - 1) * 100
        
        
        l_systUpResult.append(systUpPercent)
        l_systDownResult.append(systDownPercent)
        
        if (debug) :
            
            print "Scale-variation SR%d: nom %0.4e, up (scale %d) %0.4e, down (scale %d) %0.4e" %(iRegion+1, binVal_nominal, scaleVarIndex_max, binVal_systUp, scaleVarIndex_min, binVal_systDown)
            print "Scale-variation SR%d: up %0.2f%%, down %0.2f%%" %(iRegion+1, systUpPercent, systDownPercent)
    
    
    if (debug) :
        
        for iScaleVar in range(0, len(l_scaleVarIndex)) :
            
            scaleVarIndex = l_scaleVarIndex[iScaleVar]
            
            print "Scale-variation integral: nom %0.4e, scale %d %0.4e \n" %(yieldInfo_nominal["integral"], scaleVarIndex, l_yieldInfo_scaleVar[iScaleVar]["integral"])
    
    
    integral_systUp = yieldInfo_scaleVar_max["integral"] - yieldInfo_nominal["integral"]
    integral_systDown = yieldInfo_scaleVar_min["integral"] - yieldInfo_nominal["integral"]
    
    integral_systUpPercent = 0
    integral_systDownPercent = 0
    
    # Percent
    if (abs(yieldInfo_nominal["integral"]) > 0) :
        
        integral_systUpPercent = integral_systUp / yieldInfo_nominal["integral"] * 100.0
        integral_systDownPercent = integral_systDown / yieldInfo_nominal["integral"] * 100.0
        
        systUpPercent_mean = systUpPercent_mean / yieldInfo_nominal["integral"]
        systDownPercent_mean = systDownPercent_mean / yieldInfo_nominal["integral"]
    
    #else :
    #    
    #    integral_systUpPercent = 100.0
    #    integral_systDownPercent = 0.0
    
    
    # Set -100% error to a small value because 1-1 = 0 and combine complains because of that
    if (integral_systUpPercent == -100) :
        
        integral_systUpPercent = (1e-4 - 1) * 100
    
    if (integral_systDownPercent == -100) :
        
        integral_systDownPercent = (1e-4 - 1) * 100
    
    
    d_systResult["systUp"] = l_systUpResult
    d_systResult["systDown"] = l_systDownResult
    
    d_systResult["systUp_mean"] = systUpPercent_mean
    d_systResult["systDown_mean"] = systDownPercent_mean
    
    d_systResult["integral"] = yieldInfo_nominal["integral"]
    d_systResult["integral_systUp"] = integral_systUpPercent
    d_systResult["integral_systDown"] = integral_systDownPercent
    
    
    return d_systResult



def getSystematicsHist(
    l_rootFileDir,
    rootFileName,
    l_xs,
    suffix,
    l_systStr,
    l_systStr_isEraCorr,
    d_systStr_flat = {},
    #systStrSuffix = "",
    histName = "",
    detailStr = "",
    nRebin = 1,
    l_rebin = [],
    era = "",
    scale = 1,
    nEventHistName = "",
    negToZero = False,
    returnSystListOnly = False,
    debug = False,
    ) :
    
    h1_systPos = 0
    h1_systNeg = 0
    
    l_histSyst = []
    l_histSystInfo = []
    
    inputFiles_nominal = []
    
    if ("fakeEstimation" in l_rootFileDir[0]) :
        
        inputFiles_nominal = getRootFiles(l_rootFileDir, suffix, rootFileName)
        
        h1_nominal = HistogramDetails(l_rootFile = inputFiles_nominal, histName = histName)
        h1_nominal.getFakeEstimationHistogram(
            suffix = detailStr,
            nRebin = nRebin,
            l_rebin = l_rebin,
            scale = scale,
            debug = debug,
            #component = fakeComponent
        )
        
        for iSyst in range(0, len(l_systStr)) :
            
            #
            suffix_temp = "%s_%s-systUp" %(suffix, l_systStr[iSyst])
            inputFiles_systUp = getRootFiles(l_rootFileDir, suffix_temp, rootFileName)
            
            h1_systUp = HistogramDetails(l_rootFile = inputFiles_systUp, histName = histName)
            h1_systUp.getFakeEstimationHistogram(
                suffix = detailStr,
                nRebin = nRebin,
                l_rebin = l_rebin,
                scale = scale,
                debug = debug,
                #component = fakeComponent
            )
            
            h1_systUp.hist.Add(h1_nominal.hist, -1)
            
            
            #
            suffix_temp = "%s_%s-systDown" %(suffix, l_systStr[iSyst])
            inputFiles_systDown = getRootFiles(l_rootFileDir, suffix_temp, rootFileName)
            
            h1_systDown = HistogramDetails(l_rootFile = inputFiles_systDown, histName = histName)
            h1_systDown.getFakeEstimationHistogram(
                suffix = detailStr,
                nRebin = nRebin,
                l_rebin = l_rebin,
                scale = scale,
                debug = debug,
                #component = fakeComponent
            )
            
            h1_systDown.hist.Add(h1_nominal.hist, -1)
            
            
            l_histSyst.append(h1_systUp.hist)
            l_histSyst.append(h1_systDown.hist)
            
            systName = getCorrStr(l_systStr[iSyst], era, l_systStr_isEraCorr[iSyst])
            l_histSystInfo.append([systName, h1_systUp.hist, h1_systDown.hist])
            
            
            for iFile in range(0, len(inputFiles_nominal)) :
                
                inputFiles_systUp[iFile].Close()
                inputFiles_systDown[iFile].Close()
    
    else :
        
        inputFiles_nominal = getRootFiles(l_rootFileDir, suffix, rootFileName)
        
        h1_nominal = HistogramDetails(l_rootFile = inputFiles_nominal, l_xs = l_xs, histName = histName, era = era)
        h1_nominal.getHist(
            xsNormalize = (len(l_xs) > 0),
            suffix = detailStr,
            nEventHistName = nEventHistName,
            nRebin = nRebin,
            l_rebin = l_rebin,
            negToZero = negToZero,
            debug = debug,
            #component = fakeComponent
        )
        h1_nominal.hist.Scale(scale)
        
        for iSyst in range(0, len(l_systStr)) :
            
            if (l_systStr[iSyst] == "scale") :
                
                scaleVarIndex_min = -1
                
                h1_scaleVar_max = 0
                h1_scaleVar_min = 0
                
                for iScaleVar in range(0, len(l_QCDscaleVarIndex)) :
                    
                    scaleVarIndex = l_QCDscaleVarIndex[iScaleVar]
                    
                    suffix_mod = "%s_scale%d" %(suffix, scaleVarIndex)
                    l_rootFile_scaleVar = getRootFiles(l_rootFileDir, suffix_mod, rootFileName, debug)
                    
                    h1_scaleVar = HistogramDetails(l_rootFile = l_rootFile_scaleVar, l_xs = l_xs, histName = histName, era = era)
                    h1_scaleVar.getHist(
                        xsNormalize = (len(l_xs) > 0),
                        suffix = detailStr,
                        nEventHistName = nEventHistName,
                        nRebin = nRebin,
                        l_rebin = l_rebin,
                        negToZero = negToZero,
                        debug = debug,
                        #component = fakeComponent
                    )
                    h1_scaleVar.hist.Scale(scale)
                    
                    #print "@"*10
                    #print "@@@@@", scaleVarIndex, h1_scaleVar.hist.Integral(), h1_nominal.hist.Integral()
                    #print "@"*10
                    
                    if (not h1_scaleVar_max) :
                        
                        h1_scaleVar_max = h1_scaleVar
                    
                    elif (h1_scaleVar.hist.Integral() > h1_scaleVar_max.hist.Integral()) :
                        
                        scaleVarIndex_max = scaleVarIndex
                        h1_scaleVar_max = h1_scaleVar
                    
                    
                    if (not h1_scaleVar_min) :
                        
                        h1_scaleVar_min = h1_scaleVar
                    
                    elif (h1_scaleVar.hist.Integral() < h1_scaleVar_min.hist.Integral()) :
                        
                        scaleVarIndex_min = scaleVarIndex
                        h1_scaleVar_min = h1_scaleVar
                    
                    
                    for iFile in range(0, len(l_rootFile_scaleVar)) :
                        
                        l_rootFile_scaleVar[iFile].Close()
                
                
                h1_scaleVar_max.hist.Add(h1_nominal.hist, -1)
                h1_scaleVar_min.hist.Add(h1_nominal.hist, -1)
                
                
                l_histSyst.append(h1_scaleVar_max.hist)
                l_histSyst.append(h1_scaleVar_min.hist)
                
                systName = getCorrStr(l_systStr[iSyst], era, l_systStr_isEraCorr[iSyst])
                l_histSystInfo.append([systName, h1_scaleVar_max.hist, h1_scaleVar_min.hist])
                
                #print "#"*10
                #print "##### max", scaleVarIndex_max, h1_scaleVar_max.hist.Integral(), h1_nominal.hist.Integral()
                #print "##### min", scaleVarIndex_min, h1_scaleVar_min.hist.Integral(), h1_nominal.hist.Integral()
                #print "#"*10
            
            else :
                
                #
                suffix_temp = "%s_%s-systUp" %(suffix, l_systStr[iSyst])
                
                if (l_systStr[iSyst] in d_systStr_flat) :
                    
                    suffix_temp = suffix
                
                inputFiles_systUp = getRootFiles(l_rootFileDir, suffix_temp, rootFileName)
                
                h1_systUp = HistogramDetails(l_rootFile = inputFiles_systUp, l_xs = l_xs, histName = histName, era = era)
                h1_systUp.getHist(
                    xsNormalize = (len(l_xs) > 0),
                    suffix = "",
                    nEventHistName = nEventHistName,
                    nRebin = nRebin,
                    l_rebin = l_rebin,
                    negToZero = negToZero,
                    debug = debug,
                    #component = fakeComponent
                )
                
                # Flat uncertainty
                if (l_systStr[iSyst] in d_systStr_flat) :
                    
                    h1_systUp.hist.Scale(1 + d_systStr_flat[l_systStr[iSyst]]["up"]/100.0)
                
                h1_systUp.hist.Scale(scale)
                h1_systUp.hist.Add(h1_nominal.hist, -1)
                
                
                #
                suffix_temp = "%s_%s-systDown" %(suffix, l_systStr[iSyst])
                
                if (l_systStr[iSyst] in d_systStr_flat) :
                    
                    suffix_temp = suffix
                
                inputFiles_systDown = getRootFiles(l_rootFileDir, suffix_temp, rootFileName)
                
                h1_systDown = HistogramDetails(l_rootFile = inputFiles_systDown, l_xs = l_xs, histName = histName, era = era)
                h1_systDown.getHist(
                    xsNormalize = (len(l_xs) > 0),
                    suffix = "",
                    nEventHistName = nEventHistName,
                    nRebin = nRebin,
                    l_rebin = l_rebin,
                    negToZero = True,
                    debug = debug,
                    #component = fakeComponent
                )
                
                # Flat uncertainty
                if (l_systStr[iSyst] in d_systStr_flat) :
                    
                    h1_systDown.hist.Scale(1 - d_systStr_flat[l_systStr[iSyst]]["down"]/100.0)
                
                h1_systDown.hist.Scale(scale)
                h1_systDown.hist.Add(h1_nominal.hist, -1)
                
                
                l_histSyst.append(h1_systUp.hist)
                l_histSyst.append(h1_systDown.hist)
                
                systName = getCorrStr(l_systStr[iSyst], era, l_systStr_isEraCorr[iSyst])
                l_histSystInfo.append([systName, h1_systUp.hist, h1_systDown.hist])
            
            
            for iFile in range(0, len(inputFiles_nominal)) :
                
                inputFiles_systUp[iFile].Close()
                inputFiles_systDown[iFile].Close()
    
    
    #####
    if (returnSystListOnly) :
        
        return l_histSystInfo
    
    
    l_errPos = getCombinedErrorFromHist(l_histSyst, sign = +1)
    l_errNeg = getCombinedErrorFromHist(l_histSyst, sign = -1)
    
    h1_systPos = h1_nominal.hist.Clone()
    h1_systPos.Reset()
    h1_systPos.SetDirectory(0)
    
    h1_systNeg = h1_nominal.hist.Clone()
    h1_systNeg.Reset()
    h1_systNeg.SetDirectory(0)
    
    for iBin in range(0, h1_systPos.GetNbinsX()) :
        
        h1_systPos.SetBinContent(iBin+1, l_errPos[iBin])
        h1_systNeg.SetBinContent(iBin+1, l_errNeg[iBin])
    
    
    d_info = {
        "histPos": h1_systPos,
        "histNeg": h1_systNeg,
    }
    
    for iFile in range(0, len(inputFiles_nominal)) :
        
        inputFiles_nominal[iFile].Close()
    
    
    return d_info


#def combineEraSyst(l_systResult, isCorrelated) :
#    
#    d_systResult["systUp"] = l_systUpResult
#    d_systResult["systDown"] = l_systDownResult
#    
#    d_systResult["systUp_mean"] = systUpPercent_mean
#    d_systResult["systDown_mean"] = systDownPercent_mean
#    
#    d_systResult["integral"] = integral_nominal
#    d_systResult["integral_systUp"] = integral_systUpPercent
#    d_systResult["integral_systDown"] = integral_systDownPercent
#    
#    d_systResult["yield"] = yieldInfo_nominal["yield"]
#    
#    d_systResultCombined
#    
#    nBin = 0
#    
#    isSymmetric = "syst" in l_systResult[0]
#    
#    # Symmetric
#    if (isSymmetric) :
#        
#        nBin = len(l_systResult[0]["syst"]
#    
#    # Asymmetric
#    else :
#        
#        nBin = len(l_systResult[0]["systUp"]
#    
#    
#    for iBin in range(0, iBin) :
#        
#        syst_comb = 0
#        systUp_comb = 0
#        systDown_comb = 0
#        
#        syst_mean_comb = 0
#        systUp_mean_comb = 0
#        systDown_mean_comb = 0
#        
#        binYield_comb = 0
#        
#        for iEra in range(0, len(l_systResult)) :
#            
#            if (isSymmetric) :
#                
#                syst = abs(l_systResult[iEra]["syst"][iBin] / 100.0 * l_systResult[iEra]["yield"][iBin])
#                
#                binYield = 0
#                
#                syst += numpy.sqrt(
#                    
#                )


def getSystematics(
    #l_rootFile,
    l_rootFileDir,
    rootFileName,
    l_xs,
    suffix,
    systStr,
    histName_base,
    detailStr,
    nRegion,
    yieldBinNumber,
    scale = 1,
    fakeComponent = "total",
    ll_regionNumber = [],
    debug = False,
    ) :
    
    l_rootFile_nominal = getRootFiles(l_rootFileDir, suffix, rootFileName, debug)
    
    suffix_mod = "%s_%s-systUp" %(suffix, systStr)
    l_rootFile_systUp = getRootFiles(l_rootFileDir, suffix_mod, rootFileName, debug)
    
    suffix_mod = "%s_%s-systDown" %(suffix, systStr)
    l_rootFile_systDown = getRootFiles(l_rootFileDir, suffix_mod, rootFileName, debug)
    
    l_nominal = []
    
    l_systUpResult = []
    l_systDownResult = []
    
    l_systUpAbsVal = []
    l_systDownAbsVal = []
    
    l_systUpNegFake = []
    l_systDownNegFake = []
    
    d_systResult = {}
    
    
    integral_nominal = 0
    integral_systUp = 0
    integral_systDown = 0
    
    systUpPercent_mean = 0
    systDownPercent_mean = 0
    
    
    negToZero = True
    
    if ("fakeEstimation" in l_rootFile_nominal[0].GetName()) :
        
        negToZero = False
    
    
    yieldInfo_nominal = getYields(
        l_rootFile = l_rootFile_nominal,
        l_xs = l_xs,
        suffix = suffix,
        systStr = systStr,
        histName_base = histName_base,
        detailStr = detailStr,
        nRegion = nRegion,
        yieldBinNumber = yieldBinNumber,
        scale = scale,
        fakeComponent = fakeComponent,
        ll_regionNumber = ll_regionNumber,
        negToZero = negToZero,
        debug = debug,
    )
    
    yieldInfo_systUp = getYields(
        l_rootFile = l_rootFile_systUp,
        l_xs = l_xs,
        suffix = suffix,
        systStr = systStr,
        histName_base = histName_base,
        detailStr = detailStr,
        nRegion = nRegion,
        yieldBinNumber = yieldBinNumber,
        scale = scale,
        fakeComponent = fakeComponent,
        ll_regionNumber = ll_regionNumber,
        negToZero = negToZero,
        debug = debug,
    )
    
    yieldInfo_systDown = getYields(
        l_rootFile = l_rootFile_systDown,
        l_xs = l_xs,
        suffix = suffix,
        systStr = systStr,
        histName_base = histName_base,
        detailStr = detailStr,
        nRegion = nRegion,
        yieldBinNumber = yieldBinNumber,
        scale = scale,
        fakeComponent = fakeComponent,
        ll_regionNumber = ll_regionNumber,
        negToZero = negToZero,
        debug = debug,
    )
    
    
    yieldInfo_nominal_pos = {}
    yieldInfo_nominal_neg = {}
    
    yieldInfo_systUp_pos = {}
    yieldInfo_systUp_neg = {}
    
    yieldInfo_systDown_pos = {}
    yieldInfo_systDown_neg = {}
    
    
    if ("fakeEstimation" in l_rootFile_nominal[0].GetName()) :
        
        #
        yieldInfo_nominal_pos = getYields(
            l_rootFile = l_rootFile_nominal,
            l_xs = l_xs,
            suffix = suffix,
            systStr = systStr,
            histName_base = histName_base,
            detailStr = detailStr,
            nRegion = nRegion,
            yieldBinNumber = yieldBinNumber,
            scale = scale,
            fakeComponent = "pos",
            ll_regionNumber = ll_regionNumber,
            negToZero = negToZero,
            debug = debug,
        )
        
        yieldInfo_nominal_neg = getYields(
            l_rootFile = l_rootFile_nominal,
            l_xs = l_xs,
            suffix = suffix,
            systStr = systStr,
            histName_base = histName_base,
            detailStr = detailStr,
            nRegion = nRegion,
            yieldBinNumber = yieldBinNumber,
            scale = scale,
            fakeComponent = "neg",
            ll_regionNumber = ll_regionNumber,
            negToZero = negToZero,
            debug = debug,
        )
        
        #
        yieldInfo_systUp_pos = getYields(
            l_rootFile = l_rootFile_systUp,
            l_xs = l_xs,
            suffix = suffix,
            systStr = systStr,
            histName_base = histName_base,
            detailStr = detailStr,
            nRegion = nRegion,
            yieldBinNumber = yieldBinNumber,
            scale = scale,
            fakeComponent = "pos",
            ll_regionNumber = ll_regionNumber,
            negToZero = negToZero,
            debug = debug,
        )
        
        yieldInfo_systUp_neg = getYields(
            l_rootFile = l_rootFile_systUp,
            l_xs = l_xs,
            suffix = suffix,
            systStr = systStr,
            histName_base = histName_base,
            detailStr = detailStr,
            nRegion = nRegion,
            yieldBinNumber = yieldBinNumber,
            scale = scale,
            fakeComponent = "neg",
            ll_regionNumber = ll_regionNumber,
            negToZero = negToZero,
            debug = debug,
        )
        
        #
        yieldInfo_systDown_pos = getYields(
            l_rootFile = l_rootFile_systDown,
            l_xs = l_xs,
            suffix = suffix,
            systStr = systStr,
            histName_base = histName_base,
            detailStr = detailStr,
            nRegion = nRegion,
            yieldBinNumber = yieldBinNumber,
            scale = scale,
            fakeComponent = "pos",
            ll_regionNumber = ll_regionNumber,
            negToZero = negToZero,
            debug = debug,
        )
        
        yieldInfo_systDown_neg = getYields(
            l_rootFile = l_rootFile_systDown,
            l_xs = l_xs,
            suffix = suffix,
            systStr = systStr,
            histName_base = histName_base,
            detailStr = detailStr,
            nRegion = nRegion,
            yieldBinNumber = yieldBinNumber,
            scale = scale,
            fakeComponent = "neg",
            ll_regionNumber = ll_regionNumber,
            negToZero = negToZero,
            debug = debug,
        )
    
    
    if (len(ll_regionNumber)) :
        
        nRegion = len(ll_regionNumber)
    
    for iRegion in range(0, nRegion) :
        
        binVal_nominal = 0
        binVal_systUp = 0
        binVal_systDown = 0
        
        systUp = 0
        systDown = 0
        
        systUpPercent = 0
        systDownPercent = 0
        
        if ("fakeEstimation" in l_rootFile_nominal[0].GetName()) :
            
            #histName = "%s%d" %(histName_base, iRegion+1)
            #
            ## Nominal
            #h1_nominal = HistogramDetails(l_rootFile = l_rootFile_nominal, histName = histName)
            #h1_nominal.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "total"
            #)
            #
            #h1_nominal_pos = HistogramDetails(l_rootFile = l_rootFile_nominal, histName = histName)
            #h1_nominal_pos.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "pos"
            #)
            #
            #h1_nominal_neg = HistogramDetails(l_rootFile = l_rootFile_nominal, histName = histName)
            #h1_nominal_neg.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "neg"
            #)
            #
            #
            ## Up
            #h1_systUp = HistogramDetails(l_rootFile = l_rootFile_systUp, histName = histName)
            #h1_systUp.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "total"
            #)
            #
            #h1_systUp_pos = HistogramDetails(l_rootFile = l_rootFile_systUp, histName = histName)
            #h1_systUp_pos.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "pos"
            #)
            #
            #h1_systUp_neg = HistogramDetails(l_rootFile = l_rootFile_systUp, histName = histName)
            #h1_systUp_neg.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "neg"
            #)
            #
            #
            ## Down
            #h1_systDown = HistogramDetails(l_rootFile = l_rootFile_systDown, histName = histName)
            #h1_systDown.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "total"
            #)
            #
            #h1_systDown_pos = HistogramDetails(l_rootFile = l_rootFile_systDown, histName = histName)
            #h1_systDown_pos.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "pos"
            #)
            #
            #h1_systDown_neg = HistogramDetails(l_rootFile = l_rootFile_systDown, histName = histName)
            #h1_systDown_neg.getFakeEstimationHistogram(
            #    suffix = detailStr,
            #    debug = debug,
            #    component = "neg"
            #)
            
            
            #binVal_nominal = h1_nominal.hist.GetBinContent(yieldBinNumber)
            #binVal_nominal_pos = h1_nominal_pos.hist.GetBinContent(yieldBinNumber)
            #binVal_nominal_neg = h1_nominal_neg.hist.GetBinContent(yieldBinNumber)
            #
            #binVal_systUp = h1_systUp.hist.GetBinContent(yieldBinNumber)
            #binVal_systUp_pos = h1_systUp_pos.hist.GetBinContent(yieldBinNumber)
            #binVal_systUp_neg = h1_systUp_neg.hist.GetBinContent(yieldBinNumber)
            #
            #binVal_systDown = h1_systDown.hist.GetBinContent(yieldBinNumber)
            #binVal_systDown_pos = h1_systDown_pos.hist.GetBinContent(yieldBinNumber)
            #binVal_systDown_neg = h1_systDown_neg.hist.GetBinContent(yieldBinNumber)
            
            binVal_nominal = yieldInfo_nominal["yield"][iRegion]
            binVal_nominal_pos = yieldInfo_nominal_pos["yield"][iRegion]
            binVal_nominal_neg = yieldInfo_nominal_neg["yield"][iRegion]
            
            binVal_systUp = yieldInfo_systUp["yield"][iRegion]
            binVal_systUp_pos = yieldInfo_systUp_pos["yield"][iRegion]
            binVal_systUp_neg = yieldInfo_systUp_neg["yield"][iRegion]
            
            binVal_systDown = yieldInfo_systDown["yield"][iRegion]
            binVal_systDown_pos = yieldInfo_systDown_pos["yield"][iRegion]
            binVal_systDown_neg = yieldInfo_systDown_neg["yield"][iRegion]
            
            
            if (binVal_nominal > 0) : integral_nominal += binVal_nominal
            if (binVal_systUp > 0) : integral_systUp += binVal_systUp
            if (binVal_systDown > 0) : integral_systDown += binVal_systDown
            
            if (debug) :
            #if (1) :
                
                print iRegion+1, "Nom:", binVal_nominal, binVal_nominal_pos, binVal_nominal_neg, integral_nominal
                print iRegion+1, "Up:", binVal_systUp, binVal_systUp_pos, binVal_systUp_neg, integral_systUp
                print iRegion+1, "Down:", binVal_systDown, binVal_systDown_pos, binVal_systDown_neg, integral_systDown
            
            
            l_systUpNegFake.append(False)
            l_systDownNegFake.append(False)
            
            #if (binVal_nominal >= 0) :
            
            l_nominal.append(binVal_nominal)
            
            # Up syst
            if (binVal_nominal > 0 and binVal_systUp >= 0) :
                
                systUp = binVal_systUp - binVal_nominal
                systUpPercent = systUp / binVal_nominal * 100.0
                
                systUpPercent_mean += binVal_nominal * systUpPercent
                #systUpPercent_mean += binVal_nominal * (binVal_systUp - binVal_nominal)
            
            elif (binVal_nominal < 0 or binVal_systUp < 0) :
                
                systUp_pos = (binVal_systUp_pos-binVal_nominal_pos)/binVal_nominal_pos if (abs(binVal_nominal_pos) > 0) else 0
                systUp_neg = (binVal_systUp_neg-binVal_nominal_neg)/binVal_nominal_neg if (abs(binVal_nominal_neg) > 0) else 0
                
                systUpPercent = 100.0 * numpy.sqrt(
                    pow(systUp_pos, 2) +
                    pow(systUp_neg, 2)
                )
                
                l_systUpNegFake[-1] = True
                
                if (debug) :
                    
                    print \
                        "%s SR%d: nom (pos, neg) %0.2f (%0.2f, %0.2f), up (pos, neg) %0.2f (%0.2f, %0.2f)" \
                        %(systStr, iRegion+1, binVal_nominal, binVal_nominal_pos, binVal_nominal_neg, binVal_systUp, binVal_systUp_pos, binVal_systUp_neg)
            
            # Down syst
            if (binVal_nominal > 0 and binVal_systDown >= 0) :
                
                systDown = binVal_systDown - binVal_nominal
                systDownPercent = systDown / binVal_nominal * 100.0
                
                systDownPercent_mean += binVal_nominal * systDownPercent
                #systDownPercent_mean += binVal_nominal * (binVal_systDown - binVal_nominal)
            
            elif (binVal_nominal < 0 or binVal_systDown < 0) :
                
                systDown_pos = (binVal_systDown_pos-binVal_nominal_pos)/binVal_nominal_pos if (abs(binVal_nominal_pos) > 0) else 0
                systDown_neg = (binVal_systDown_neg-binVal_nominal_neg)/binVal_nominal_neg if (abs(binVal_nominal_neg) > 0) else 0
                
                systDownPercent = 100.0 * numpy.sqrt(
                    pow(systDown_pos, 2) +
                    pow(systDown_neg, 2)
                )
                
                l_systDownNegFake[-1] = True
                
                if (debug) :
                    
                    print \
                        "%s SR%d: nom (pos, neg) %0.2f (%0.2f, %0.2f), down (pos, neg) %0.2f (%0.2f, %0.2f)" \
                        %(systStr, iRegion+1, binVal_nominal, binVal_nominal_pos, binVal_nominal_neg, binVal_systDown, binVal_systDown_pos, binVal_systDown_neg)
        
        
        else :
            
            #histName = "reco/%s/%s%d_%s" %(detailStr, histName_base, iRegion+1, detailStr)
            #nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
            #
            ##if ("WJets" in l_rootFile_nominal[0].GetName() or "DYJets" in l_rootFile_nominal[0].GetName()) :
            ##    
            ##    nEventHistName = ""
            #
            #
            ## Nominal
            #h1_nominal = HistogramDetails(l_rootFile = l_rootFile_nominal, l_xs = l_xs, histName = histName)
            #h1_nominal.getHist(
            #    xsNormalize = True,
            #    nEventHistName = nEventHistName,
            #)
            ##h1_nominal.hist.Scale(lumi_data)
            #
            #
            ## Up
            #h1_systUp = HistogramDetails(l_rootFile = l_rootFile_systUp, l_xs = l_xs, histName = histName)
            #h1_systUp.getHist(
            #    xsNormalize = True,
            #    nEventHistName = nEventHistName,
            #)
            ##h1_systUp.hist.Scale(lumi_data)
            #
            #
            ## Down
            #h1_systDown = HistogramDetails(l_rootFile = l_rootFile_systDown, l_xs = l_xs, histName = histName)
            #h1_systDown.getHist(
            #    xsNormalize = True,
            #    nEventHistName = nEventHistName,
            #)
            ##h1_systDown.hist.Scale(lumi_data)
            
            
            #binVal_nominal = h1_nominal.hist.GetBinContent(yieldBinNumber)
            #binVal_systUp = h1_systUp.hist.GetBinContent(yieldBinNumber)
            #binVal_systDown = h1_systDown.hist.GetBinContent(yieldBinNumber)
            
            binVal_nominal = yieldInfo_nominal["yield"][iRegion]
            binVal_systUp = yieldInfo_systUp["yield"][iRegion]
            binVal_systDown = yieldInfo_systDown["yield"][iRegion]
            
            integral_nominal += binVal_nominal
            integral_systUp += binVal_systUp
            integral_systDown += binVal_systDown
            
            l_nominal.append(binVal_nominal)
            
            systUp = binVal_systUp - binVal_nominal
            systDown = binVal_systDown - binVal_nominal
            
            
            # Percent
            if (abs(binVal_nominal) > 0) :
                
                systUpPercent = systUp / binVal_nominal * 100.0
                systDownPercent = systDown / binVal_nominal * 100.0
                
                systUpPercent_mean += binVal_nominal * systUpPercent
                #systUpPercent_mean += binVal_nominal * systUp
                systDownPercent_mean += binVal_nominal * systDownPercent
                #systDownPercent_mean += binVal_nominal * systDown
                
                #print "[%s] binVal_nominal %e, systUp %e" %(suffix_mod, binVal_nominal, systUp)
            
            #else :
            #    
            #    systUpPercent = 100.0
            #    systDownPercent = 0.0
                
                #if (abs(binVal_systUp) > 0) :
                #    
                #    systUpPercent = 100
                #
                #if (abs(binVal_systDown) > 0) :
                #    
                #    systDownPercent = 100
            
            
        # Set -100% error to a small value because 1-1 = 0 and combine complains because of that
        if (systUpPercent == -100) :
            
            systUpPercent = (1e-4 - 1) * 100
        
        if (systDownPercent == -100) :
            
            systDownPercent = (1e-4 - 1) * 100
        
        
        l_systUpAbsVal.append(systUp)
        l_systDownAbsVal.append(systDown)
        
        l_systUpResult.append(systUpPercent)
        l_systDownResult.append(systDownPercent)
        
        if (debug) :
            
            print "%s SR%d: nom %0.4e, up %0.4e, down %0.4e" %(systStr, iRegion+1, binVal_nominal, binVal_systUp, binVal_systDown)
            print "%s SR%d: up %0.2f%%, down %0.2f%%" %(systStr, iRegion+1, systUpPercent, systDownPercent)
    
    #d_nominal[systStr] = l_nominal
    #
    #d_systUpResult[systStr] = l_systUpResult
    #d_systDownResult[systStr] = l_systDownResult
    #
    #d_systUpNegFake[systStr] = l_systUpNegFake
    #d_systDownNegFake[systStr] = l_systDownNegFake
    
    integral_systUp = integral_systUp - integral_nominal
    integral_systDown = integral_systDown - integral_nominal
    
    integral_systUpPercent = 0
    integral_systDownPercent = 0
    
    # Percent
    if (abs(integral_nominal) > 0) :
        
        integral_systUpPercent = integral_systUp / integral_nominal * 100.0
        integral_systDownPercent = integral_systDown / integral_nominal * 100.0
        
        #print "[%s] systUpPercent_mean %e, systDownPercent_mean %e, integral_nominal %e" %(suffix_mod, systUpPercent_mean, systDownPercent_mean, integral_nominal)
        systUpPercent_mean = systUpPercent_mean / integral_nominal
        systDownPercent_mean = systDownPercent_mean / integral_nominal
    
    #else :
    #    
    #    integral_systUpPercent = 100.0
    #    integral_systDownPercent = 0.0
    
    
    
    d_systResult["systUpAbsVal"] = l_systUpAbsVal
    d_systResult["systDownAbsVal"] = l_systDownAbsVal
    
    d_systResult["systUp"] = l_systUpResult
    d_systResult["systDown"] = l_systDownResult
    
    d_systResult["systUp_mean"] = systUpPercent_mean
    d_systResult["systDown_mean"] = systDownPercent_mean
    
    d_systResult["integral"] = integral_nominal
    d_systResult["integral_systUp"] = integral_systUpPercent
    d_systResult["integral_systDown"] = integral_systDownPercent
    
    d_systResult["yield"] = yieldInfo_nominal["yield"]
    
    # Close files
    for iFile in range(0, len(l_rootFile_nominal)) :
        
        l_rootFile_nominal[iFile].Close()
        l_rootFile_systUp[iFile].Close()
        l_rootFile_systDown[iFile].Close()
    
    
    return d_systResult


# Format of input:
# d_systInfo = {
#     systName1
#         corr = True/False,
#         info: {
#             era1: [errUp, errDown],
#             era2: [errUp, errDown],
#             ...
#         },
#     },
#     ...
# }


# Need yieldInfo for yield weighted average
# qtyStr is What to average: syst, syst_mean, systUp, systUp_mean, etc.
# So, it can be a scalar or a list. Handle that accordingly
def getEraCombinedSystMean(d_systInfo, d_yieldInfo, qtyStr) :
    
    l_era = d_systInfo.keys()
    
    if (isinstance(d_systInfo[l_era[0]][qtyStr], list)) :
        
        nBin = len(d_systInfo[l_era[0]][qtyStr])
        
        l_mean = [0] * nBin
        l_yield_sum = [0] * nBin
        
        for iBin in range(0, nBin) :
            
            for era in d_systInfo :
                
                l_mean[iBin] += d_systInfo[era][qtyStr][iBin] * d_yieldInfo[era]["yield"][iBin]
                l_yield_sum[iBin] += d_yieldInfo[era]["yield"][iBin]
            
            if (l_yield_sum[iBin]) :
                
                l_mean[iBin] /= l_yield_sum[iBin]
        
        return l_mean
    
    else :
        
        mean = 0
        integral_sum = 0
        
        for era in d_systInfo :
            
            mean += d_systInfo[era][qtyStr] * d_yieldInfo[era]["integral"]
            integral_sum += d_yieldInfo[era]["integral"]
        
        if (integral_sum) :
            
            mean /= integral_sum
        
        return mean


def getEraCombinedSystInfoMean(d_systInfo, d_yieldInfo) :
    
    d_combinedInfo = {}
    
    l_era = d_systInfo.keys()
    
    if (not len(l_era)) :
        
        return d_combinedInfo
    
    l_qtyStr = [
        "syst", "syst_mean",
        "systUp", "systUp_mean",
        "systDown", "systDown_mean"
    ]
    
    for iStr in range(0, len(l_qtyStr)) :
        
        qtyStr = l_qtyStr[iStr]
        
        # Combine only if the quantity exists
        
        if (qtyStr in d_systInfo[l_era[0]]) :
            
            d_combinedInfo[qtyStr] = getEraCombinedSystMean(d_systInfo = d_systInfo, d_yieldInfo = d_yieldInfo, qtyStr = qtyStr)
    
    return d_combinedInfo


def getCombinedError(l_err, sign = 0, returnSign = False, corr = False, l_yield = [], debug = False) :
    
    if (corr and len(l_yield)) :
        
        print("Error in Common.getCombinedError(...): Trying to use zero-yield info when corr = True. Check!!!")
        exit(1)
    
    
    errPow_zeroBin = 0
    errPow_nonZeroBin = 0
    errPow = 0
    
    power = 2.0
    power_zeroBin = 1.0
    
    if (corr) :
        
        power = 1.0
    
    n_zeroBin = 0
    
    for iErr in range(0, len(l_err)) :
        
        powSign = 1
        isZeroYield = False
        
        if (len(l_yield)) :
            
            if (not l_yield[iErr]) :
                
                #powSign = -1
                isZeroYield = True
        
        n_zeroBin += int(isZeroYield)
        
        
        if (sign == 0) :
            
            errPow += l_err[iErr]**power
            
            if (len(l_yield)) :
                
                errPow_zeroBin += isZeroYield * l_err[iErr]**(powSign*power_zeroBin)
                errPow_nonZeroBin += (not isZeroYield) * l_err[iErr]**(powSign*power)
        
        elif (sign == 1) :
            
            errPow += l_err[iErr]**power * (l_err[iErr] > 0)
            
            if (len(l_yield)) :
                
                errPow_zeroBin += isZeroYield * l_err[iErr]**(powSign*power_zeroBin) * (l_err[iErr] > 0)
                errPow_nonZeroBin += (not isZeroYield) * l_err[iErr]**(powSign*power) * (l_err[iErr] > 0)
        
        elif (sign == -1) :
            
            errPow += l_err[iErr]**power * (l_err[iErr] < 0)
            
            if (len(l_yield)) :
                
                errPow_zeroBin += isZeroYield * l_err[iErr]**(powSign*power_zeroBin) * (l_err[iErr] < 0)
                errPow_nonZeroBin += (not isZeroYield) * l_err[iErr]**(powSign*power) * (l_err[iErr] < 0)
    
    
    #err = numpy.sqrt(errSq)
    
    err = abs(errPow)**(1.0/power)
    
    if (len(l_yield)) :
        
        if (n_zeroBin) :
            
            errPow_zeroBin /= n_zeroBin
            errPow_zeroBin = errPow_zeroBin*errPow_zeroBin
            
            #err = (errPow_nonZeroBin + 1.0/errPow_zeroBin)**(1.0/power)
            err = (errPow_nonZeroBin + errPow_zeroBin)**(1.0/power)
    
    
    if (sign and returnSign) :
        
        err *= sign
    
    return err


def getEraCombinedError(l_systInfo, sign = 0, treatCorrelated = True, l_yield = [], debug = False) :
    
    if (debug) :
        
        print "Entering Common.getEraCombinedError(...)."
    
    #d_systCombined[label_fake]["syst"][iSR][systName] = [errUp, -errDown]
    
    d_systInfo_combined = {}
    
    for iSyst in range(0, len(l_systInfo)) :
        
        systKey = l_systInfo[iSyst][0]
        
        errUp = l_systInfo[iSyst][1]
        errDown = l_systInfo[iSyst][2]
        
        if (sign == 1) :
            
            errUp *= (errUp > 0)
            errDown *= (errDown > 0)
        
        elif (sign == -1) :
            
            errUp *= (errUp < 0)
            errDown *= (errDown < 0)
        
        
        # Group systematics with the same name (correlated)
        if (systKey in d_systInfo_combined) :
            
            d_systInfo_combined[systKey].append(errUp)
            d_systInfo_combined[systKey].append(errDown)
        
        else :
            
            d_systInfo_combined[systKey] = [errUp, errDown]
    
    if (debug) :
        
        print d_systInfo_combined
    
    l_combinedErr = []
    
    # Merge groups of correlated systematics
    for systKey in d_systInfo_combined :
        
        # Note: Get the sign correct
        l_combinedErr.append(getCombinedError(
            l_err = d_systInfo_combined[systKey],
            sign = sign,
            returnSign = True,
            corr = treatCorrelated,
        ))
    
    if (debug) :
        
        print l_combinedErr
    
    # Now all the systematics are uncorrelated
    combinedErr = getCombinedError(l_err = l_combinedErr, sign = sign, corr = False, l_yield = l_yield)
    
    if (debug) :
        
        print "Exiting Common.getEraCombinedError(...)."
    
    return combinedErr


def getCombinedErrorFromHist(l_hist, sign = 0) :
    
    l_err_binwise = [0]*l_hist[0].GetNbinsX()
    
    for iBin in range(0, l_hist[0].GetNbinsX()) :
        
        l_err = []
        
        for iHist in range(0, len(l_hist)) :
            
            l_err.append(l_hist[iHist].GetBinContent(iBin+1))
        
        err = getCombinedError(l_err = l_err, sign = sign)
        
        l_err_binwise[iBin] = err
    
    return l_err_binwise


def getEraCombinedErrorHist(l_histInfo, sign = 0, treatCorrelated = True, debug = False) :
    
    combinedHist = l_histInfo[0][1].Clone()
    combinedHist.Reset()
    combinedHist.SetDirectory(0)
    combinedHist.Sumw2()
    
    nHist = len(l_histInfo)
    nBin = combinedHist.GetNbinsX()
    
    for iBin in range(0, nBin) :
        
        l_errInfo = []
        
        for iHist in range(0, nHist) :
            
            systName = l_histInfo[iHist][0]
            histUp = l_histInfo[iHist][1]
            histDown = l_histInfo[iHist][2]
            
            l_errInfo.append([
                systName,
                histUp.GetBinContent(iBin+1),
                histDown.GetBinContent(iBin+1),
            ])
        
        combinedErr = getEraCombinedError(
            l_systInfo = l_errInfo,
            sign = sign,
            treatCorrelated = treatCorrelated,
            debug = debug
        )
        
        combinedHist.SetBinContent(iBin+1, combinedErr)
    
    return combinedHist


def getRelativeError(val, err) :
    
    val = float(val)
    err = float(err)
    
    if (abs(val) > 0) :
        
        return err/val
    
    else :
        
        return 0.0


def replaceZero(val, zeroReplacement) :
    
    if (abs(val) == 0) :
        
        return zeroReplacement
    
    else :
        
        return val


def getYieldHistFromYieldInfo(yieldResult) :
    
    nBin = len(yieldResult["yield"])
    
    hist = ROOT.TH1F("hist", "hist", nBin, 0, nBin)
    
    for iBin in range(0, nBin) :
        
        binVal = yieldResult["yield"][iBin]
        binErr = yieldResult["error"][iBin]
        
        hist.SetBinContent(iBin+1, binVal)
        hist.SetBinError(iBin+1, binErr)
        hist.GetXaxis().SetBinLabel(iBin+1, str(iBin+1))
    
    return hist


def rebin2Dhistogram(
    hist,
    rebinX,
    l_xBin_lwrEdge, 
    rebinY,
    l_yBin_lwrEdge,
    #replaceHist,
    debug = False
    ):
    
    xAxis = hist.GetXaxis()
    yAxis = hist.GetYaxis()
    
    if (not rebinX) :
        
        l_xBin_lwrEdge = [xAxis.GetBinLowEdge(iBin) for iBin in range(1, hist.GetNbinsX()+1)]
        #l_xBin_lwrEdge = ROOT.std.vector("double")()
        #xAxis.GetLowEdge(ROOT.AddressOf(l_xBin_lwrEdge))
    
    
    if (not rebinY) :
        
        l_yBin_lwrEdge = [yAxis.GetBinLowEdge(iBin) for iBin in range(1, hist.GetNbinsY()+1)]
        #l_yBin_lwrEdge = ROOT.std.vector("double")()
        #yAxis.GetLowEdge(ROOT.AddressOf(l_yBin_lwrEdge))
    
    
    if (debug) :
        
        print "x-binning: %d --> %d" %(hist.GetNbinsX(), len(l_xBin_lwrEdge))
        print "y-binning: %d --> %d" %(hist.GetNbinsY(), len(l_yBin_lwrEdge))
    
    
    histNew = ROOT.TH2F(
        hist.GetName(), hist.GetTitle(),
        len(l_xBin_lwrEdge)-1, array.array("d", l_xBin_lwrEdge),
        len(l_yBin_lwrEdge)-1, array.array("d", l_yBin_lwrEdge)
    )
    
    histNew.SetDirectory(0)
    histNew.Sumw2()
    
    # INCLUDING over/underflow bins
    for iBinX in range(0, hist.GetNbinsX()+2) :
        
        for iBinY in range(0, hist.GetNbinsY()+2) :
            
            binContent = hist.GetBinContent(iBinX, iBinY)
            binErr = hist.GetBinError(iBinX, iBinY)
            
            binLocationX = xAxis.GetBinCenter(iBinX)
            binLocationY = yAxis.GetBinCenter(iBinY)
            
            #print iBinX, binLocationX, iBinY, binLocationY, binContent
            
            binX_histNew = histNew.GetXaxis().FindBin(binLocationX)
            binY_histNew = histNew.GetYaxis().FindBin(binLocationY)
            
            binErr_histNew = histNew.GetBinError(binX_histNew, binY_histNew)
            
            histNew.Fill(binLocationX, binLocationY, binContent)
            histNew.SetBinError(binX_histNew, binY_histNew, numpy.sqrt(binErr*binErr+binErr_histNew*binErr_histNew))
    
    #print hist.Integral()
    #print histNew.Integral()
    
    #if (replaceHist)
    #    
    #    hist.SetDirectory(0)
    #    delete hist
    #    
    #    hist = histNew
    
    
    return histNew


def histAdd(hist1, hist2, option = "") :
    
    histSum = hist1.Clone()
    histSum.SetDirectory(0)
    
    if (option == "") :
        
        histSum.Add(hist2)
    
    elif (option == "quad") :
        
        for iBin in range(0, hist1.GetNbinsX()) :
            
            histSum.SetBinContent(iBin+1, numpy.sqrt(
                hist1.GetBinContent(iBin+1)**2 +
                hist2.GetBinContent(iBin+1)**2
            ))
    
    else :
        
        print "Error in Common.histAdd(...): Invalid option provided. \n"
        exit(0)
    
    
    return histSum


def getCMSextraText(
    isPrelim = True,
    isSimOnly = False
) :
    
    CMSextraText = ""
    
    if (isSimOnly) :
        
        CMSextraText += " Simulation"
    
    if (isPrelim) :
        
        CMSextraText += " Preliminary"
    
    return CMSextraText


def getLumitext(era, eraDetail = "", printYear = False, precision = 1) :
    
    lumiText = ""
    
    if (era == "2016" or era == "2017") :
        
        eraStr = ""
        
        if (printYear) :
            
            eraStr = ", %s%s" %(era, eraDetail)
        
        lumiText = "%0.*f fb^{-1} (13 TeV%s)" %(precision, Details.luminosity_data_fb[era], eraStr)
    
    elif (era in ["combined", "2016+2017"]) :
        
        eraStr = ""
        
        if (printYear) :
            
            eraStr = ", 2016+2017" %(era, eraDetail)
        
        #lumiText = "%0.1f+%0.1f fb^{-1} (13 TeV, 2016+2017)" %(Details.luminosity_data_fb["2016"], Details.luminosity_data_fb["2017"])
        #lumiText = "%0.1f fb^{-1} (13 TeV, 2016+2017)" %(Details.luminosity_data_fb["2016"] + Details.luminosity_data_fb["2017"])
        lumiText = "%0.*f fb^{-1} (13 TeV%s)" %(precision, Details.luminosity_data_fb["2016"] + Details.luminosity_data_fb["2017"], eraStr)
    
    else :
        
        print "Error in Common.getLumitext(...): Wrong era option."
        exit(1)
    
    return lumiText


def formatNumberMin(val, minVal, nDecimal, withSign = True, useSigFig = False) :
    
    val_abs = abs(val)
    
    precisionStr = "f"
    
    if (useSigFig) :
        
        precisionStr = "g"
    
    if (val_abs < minVal) :
        
        # Dynamic precision
        #formatStr = "< %%0.*%s" %(precisionStr)
        #return formatStr %(nDecimal, minVal)
        return "< %s" %(str(minVal))
    
    else :
        
        if (withSign) :
            
            formatStr = "%%+0.*%s" %(precisionStr)
            return formatStr %(nDecimal, val)
        
        else :
            
            formatStr = "%%0.*%s" %(precisionStr)
            return formatStr %(nDecimal, val)


def getMinPrecision(l_valStr, zeroRemovalThresh = -1) :
    
    minPreci = 99999
    
    for iValStr in range(0, len(l_valStr)) :
        
        valStr = l_valStr[iValStr]
        
        # Convert numbers like "1.7e2" to "170.0"
        valStr = str(float(valStr))
        
        # Convert numbers like "170.0" to "170"
        if (
            valStr[-2:] == ".0" and
            zeroRemovalThresh > 0 and
            len(valStr.replace(".", "")) > zeroRemovalThresh
        ) :
            
            valStr = valStr[:-2]
        
        preci = 0
        
        if (valStr.find(".") < 0) :
            
            preci = 0
        
        else :
            
            preci = len(valStr[valStr.find(".") + 1:])
        
        
        if (preci < minPreci) :
            
            minPreci = preci
    
    
    return minPreci

import numpy
import os
import sys
import time

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


initVal = -9999

numberFormat_int = ".0f"
numberFormat_float = ".2f"


ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)
ROOT.gStyle.SetTitleH(0.035)
ROOT.gStyle.SetTitleY(0.985)

outDir = "plots/tauTemplateMethodEstimation/muMu_data"
#outDir = "plots/tauTemplateMethodEstimation/muMu_data_2Dtemplate"
os.system("mkdir -p %s" %(outDir))

histSuffix = "tightTight_OS_baselineSRB"
histSuffix_templateMethod = "OS_baselineSRB"

suffix = "_tauTau_analysis"
suffix_templateMethod = "_muMu_tauTemplateMethodEstimation"

rootFileName = "custom_all_analyzed.root"
rootFileName_templateMethod = "custom_all_tauTemplateMethodEstimation.root"

l_inputFile_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data, suffix, rootFileName)
l_inputFile_templateMethod = Common.getRootFiles(Details.cutFlowDir_muMu_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)
#l_inputFile_templateMethod = Common.getRootFiles(Details.cutFlowDir_muMu_tauTemplateMethodEstimation, suffix_templateMethod, "custom_all_tauTemplateMethodEstimation_2Dtemplate.root")

l_inputFile_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu, suffix, rootFileName)
l_inputFile_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL, suffix, rootFileName)
l_inputFile_VH = Common.getRootFiles(Details.cutFlowDir_VH, suffix, rootFileName)
l_inputFile_VV = Common.getRootFiles(Details.cutFlowDir_VV, suffix, rootFileName)
l_inputFile_WG = Common.getRootFiles(Details.cutFlowDir_WG, suffix, rootFileName)
l_inputFile_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar, suffix, rootFileName)
l_inputFile_singleTop = Common.getRootFiles(Details.cutFlowDir_singleTop, suffix, rootFileName)


luminosity_QCDestimation = 8.347e3
luminosity_templateMethod = 8.347e3


print "\n\n"

def getHistogram(
    histName,
    histSuffix = "",
    isMC = False,
    l_rootFile = [],
    l_crossSection = [],
    l_nEvent = [],
    luminosity = 1.0
    ) :
    
    if (histSuffix != "") :
        
        histName = "%s_%s" %(histName, histSuffix)
    
    print "Getting histogram %s" %(histName)
    
    hist = l_rootFile[0].Get(histName).Clone()
    hist.Sumw2()
    
    for iFile in range(0, len(l_rootFile)) :
        
        print "Input file: %s" %(l_rootFile[iFile].GetName())
        
        temp = l_rootFile[iFile].Get(histName).Clone()
        
        f = 1.0
        
        if (isMC) :
            
            f = l_crossSection[iFile] / float(l_nEvent[iFile])
        
        if (iFile == 0) :
            
            hist.Scale(f)
        
        else :
            
            hist.Add(temp, f)
    
    hist.Scale(luminosity);
    
    print "Got histogram %s (Integral = %f)" %(histName, hist.Integral())
    print ""
    
    return hist


def getHistogram_QCD(
    histName,
    histSuffix_sig,
    histSuffix_shape,
    histSuffix_scaleNum,
    histSuffix_scaleDen,
    l_rootFile_data,
    luminosity,
    ll_rootFile_mc,
    ll_crossSection_mc,
    ll_nEvent_mc
    ) :
    
    print ""
    print "**********"
    print "********** QCD estimation start **********"
    print "**********"
    print ""
    
    h_sig = getHistogram(
        histName = histName,
        histSuffix = histSuffix_sig,
        l_rootFile = l_rootFile_data
    )
    
    h_shape = getHistogram(
        histName = histName,
        histSuffix = histSuffix_shape,
        l_rootFile = l_rootFile_data
    )
    
    h_scaleNum = getHistogram(
        histName = histName,
        histSuffix = histSuffix_scaleNum,
        l_rootFile = l_rootFile_data
    )
    
    h_scaleDen = getHistogram(
        histName = histName,
        histSuffix = histSuffix_scaleDen,
        l_rootFile = l_rootFile_data
    )
    
    # Subtract nonQCD from Data
    for iBg in range(0, len(ll_rootFile_mc)) :
        
        # shape region
        h_temp = getHistogram(
            histName = histName,
            histSuffix = histSuffix_shape,
            isMC = True,
            l_rootFile = ll_rootFile_mc[iBg],
            l_crossSection = ll_crossSection_mc[iBg],
            l_nEvent = ll_nEvent_mc[iBg],
            luminosity = luminosity
        )
        
        h_shape.Add(h_temp, -1)
        
        
        # signal region
        h_temp = getHistogram(
            histName = histName,
            histSuffix = histSuffix_sig,
            isMC = True,
            l_rootFile = ll_rootFile_mc[iBg],
            l_crossSection = ll_crossSection_mc[iBg],
            l_nEvent = ll_nEvent_mc[iBg],
            luminosity = luminosity
        )
        
        h_sig.Add(h_temp, -1)
        
        
        # ScaleNum
        h_temp = getHistogram(
            histName = histName,
            histSuffix = histSuffix_scaleNum,
            isMC = True,
            l_rootFile = ll_rootFile_mc[iBg],
            l_crossSection = ll_crossSection_mc[iBg],
            l_nEvent = ll_nEvent_mc[iBg],
            luminosity = luminosity
        )
        
        h_scaleNum.Add(h_temp, -1)
        
        
        # ScaleDen
        h_temp = getHistogram(
            histName = histName,
            histSuffix = histSuffix_scaleDen,
            isMC = True,
            l_rootFile = ll_rootFile_mc[iBg],
            l_crossSection = ll_crossSection_mc[iBg],
            l_nEvent = ll_nEvent_mc[iBg],
            luminosity = luminosity
        )
        
        h_scaleDen.Add(h_temp, -1)
    
    #if ("MET_E" in histName) :
    #    h_shape.Draw()
    #    time.sleep(100)
    #
    #print "h_shape ", h_shape.GetBinContent(3), h_shape.Integral()
    #print "h_sig ", h_sig.GetBinContent(3), h_sig.Integral()
    #print "h_scaleNum ", h_scaleNum.GetBinContent(3), h_scaleNum.Integral()
    #print "h_scaleDen ", h_scaleDen.GetBinContent(3), h_scaleDen.Integral()
    
    evalError = True
    considerIntegral = True
    
    # Take care of -ve values
    Common.setBinLwrThreshold(
        hist = h_shape,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    Common.setBinLwrThreshold(
        hist = h_sig,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    Common.setBinLwrThreshold(
        hist = h_scaleNum,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    Common.setBinLwrThreshold(
        hist = h_scaleDen,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    # Subtract signal region
    h_shape.Add(h_sig, -1)
    h_scaleDen.Add(h_scaleNum, -1)
    
    # Take care of -ve values
    Common.setBinLwrThreshold(
        hist = h_shape,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    Common.setBinLwrThreshold(
        hist = h_sig,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    Common.setBinLwrThreshold(
        hist = h_scaleNum,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    Common.setBinLwrThreshold(
        hist = h_scaleDen,
        thr_lwr = 0,
        newBinVal = 0,
        evalError = evalError,
        considerIntegral = considerIntegral,
    )
    
    # Get scale factor
    h_scaleNum.Divide(h_scaleDen)
    
    # Scale shape to signal region
    h_shape.Multiply(h_scaleNum)
    
    
    print "QCD: %s (Integral = %f)" %(histName, h_shape.Integral())
    
    print ""
    print "**********"
    print "********** QCD estimation end **********"
    print "**********"
    print ""
    
    return h_shape


##################################################
def getHistogramDetail_template(histName, histSuffix) :
    
    l_histDetail = []
    
    histDetail = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = False,
        l_rootFile = l_inputFile_templateMethod,
    ))
    
    histDetail.histLabel = "#tau-template method"
    histDetail.color = 1
    
    l_histDetail.append(histDetail)
    
    return l_histDetail


##################################################
def getHistogramDetail_mc(histName, histSuffix) :
    
    l_histDetail = []
    
    histDetail_WJetsToLNu = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = True,
        l_rootFile = l_inputFile_WJetsToLNu,
        l_crossSection = Details.crossSection_WJetsToLNu,
        l_nEvent = Details.nEvent_WJetsToLNu,
        luminosity = luminosity_templateMethod,
    ))
    
    histDetail_WJetsToLNu.histLabel = Details.label_WJetsToLNu[0]
    histDetail_WJetsToLNu.color = Details.color_WJetsToLNu
    
    l_histDetail.append(histDetail_WJetsToLNu)
    
    
    ##################################################
    histDetail_DYJetsToLL = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = True,
        l_rootFile = l_inputFile_DYJetsToLL,
        l_crossSection = Details.crossSection_DYJetsToLL,
        l_nEvent = Details.nEvent_DYJetsToLL,
        luminosity = luminosity_templateMethod,
    ))
    
    histDetail_DYJetsToLL.histLabel = Details.label_DYJetsToLL[0]
    histDetail_DYJetsToLL.color = Details.color_DYJetsToLL
    
    l_histDetail.append(histDetail_DYJetsToLL)
    
    
    ##################################################
    histDetail_VH = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = True,
        l_rootFile = l_inputFile_VH,
        l_crossSection = Details.crossSection_VH,
        l_nEvent = Details.nEvent_VH,
        luminosity = luminosity_templateMethod,
    ))
    
    histDetail_VH.histLabel = Details.label_VH[0]
    histDetail_VH.color = Details.color_VH
    
    l_histDetail.append(histDetail_VH)
    
    
    ##################################################
    histDetail_VV = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = True,
        l_rootFile = l_inputFile_VV,
        l_crossSection = Details.crossSection_VV,
        l_nEvent = Details.nEvent_VV,
        luminosity = luminosity_templateMethod,
    ))
    
    histDetail_VV.histLabel = Details.label_VV[0]
    histDetail_VV.color = Details.color_VV
    
    l_histDetail.append(histDetail_VV)
    
    
    ##################################################
    histDetail_WG = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = True,
        l_rootFile = l_inputFile_WG,
        l_crossSection = Details.crossSection_WG,
        l_nEvent = Details.nEvent_WG,
        luminosity = luminosity_templateMethod,
    ))
    
    histDetail_WG.histLabel = Details.label_WG[0]
    histDetail_WG.color = Details.color_WG
    
    l_histDetail.append(histDetail_WG)
    
    
    ##################################################
    histDetail_QCD = Common.HistogramDetails(hist = getHistogram_QCD(
        histName = histName,
        histSuffix_sig = "tightTight_OS_baselineSRB",
        histSuffix_shape = "looseLoose_OS_baselineSRB",
        histSuffix_scaleNum = "tightTight_SS_baselineSRB",
        histSuffix_scaleDen = "looseLoose_SS_baselineSRB",
        l_rootFile_data = l_inputFile_data,
        luminosity = luminosity_QCDestimation,
        
        ll_rootFile_mc = [
            l_inputFile_WJetsToLNu,
            l_inputFile_DYJetsToLL,
            l_inputFile_VH,
            l_inputFile_VV,
            l_inputFile_WG,
            l_inputFile_ttbar,
            l_inputFile_singleTop,
        ],
        
        ll_crossSection_mc = [
            Details.crossSection_WJetsToLNu,
            Details.crossSection_DYJetsToLL,
            Details.crossSection_VH,
            Details.crossSection_VV,
            Details.crossSection_WG,
            Details.crossSection_ttbar,
            Details.crossSection_singleTop,
        ],
        
        ll_nEvent_mc = [
            Details.nEvent_WJetsToLNu,
            Details.nEvent_DYJetsToLL,
            Details.nEvent_VH,
            Details.nEvent_VV,
            Details.nEvent_WG,
            Details.nEvent_ttbar,
            Details.nEvent_singleTop,
        ],
    ))
    
    histDetail_QCD.histLabel = Details.label_QCD[0]
    histDetail_QCD.color = Details.color_QCD
    
    l_histDetail.append(histDetail_QCD)
    
    
    ##################################################
    histDetail_ttbar = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = True,
        l_rootFile = l_inputFile_ttbar,
        l_crossSection = Details.crossSection_ttbar,
        l_nEvent = Details.nEvent_ttbar,
        luminosity = luminosity_templateMethod,
    ))
    
    histDetail_ttbar.histLabel = Details.label_ttbar[0]
    histDetail_ttbar.color = Details.color_ttbar
    
    l_histDetail.append(histDetail_ttbar)
    
    
    ##################################################
    histDetail_singleTop = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = True,
        l_rootFile = l_inputFile_singleTop,
        l_crossSection = Details.crossSection_singleTop,
        l_nEvent = Details.nEvent_singleTop,
        luminosity = luminosity_templateMethod,
    ))
    
    histDetail_singleTop.histLabel = Details.label_singleTop[0]
    histDetail_singleTop.color = Details.color_singleTop
    
    l_histDetail.append(histDetail_singleTop)
    
    
    return l_histDetail


##################################################
histDir = "reco"
histName = "tau1_pT_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "p_{T} of #tau^{reco}_{h1}",
    xTitle = "p_{T} [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    xMin = 0,
    xMax = 500,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "tau2_pT_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "p_{T} of #tau^{reco}_{h2}",
    xTitle = "p_{T} [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    xMin = 0,
    xMax = 500,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "tau1_MET_deltaPhi_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "#Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T})",
    xTitle = "#Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T})", yTitle = "# event",
    ratioYtitle = "Data / MC",
    rebinX = 2,
    legendPos = "LR",
    xMin = -4,
    xMax = 4,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "tau2_MET_deltaPhi_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "#Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T})",
    xTitle = "#Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T})", yTitle = "# event",
    ratioYtitle = "Data / MC",
    rebinX = 2,
    legendPos = "LR",
    xMin = -4,
    xMax = 4,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "tauTau_deltaPhi_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "#Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2})",
    xTitle = "#Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2})", yTitle = "# event",
    ratioYtitle = "Data / MC",
    rebinX = 2,
    legendPos = "LR",
    xMin = -4,
    xMax = 4,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "b1_pT_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "p_{T} of b_{1}",
    xTitle = "p_{T} [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    xMin = 0,
    xMax = 500,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "tauTau_jet_HT_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "H_{T}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, jets)",
    xTitle = "H_{T} [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    rebinX = 3,
    xMin = 0,
    xMax = 1000,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)

#
###################################################
#histDir = "reco"
#histName = "tau1_MET_mT_reco"
#histNameFull = "%s/%s" %(histDir, histName)
#outFile = "%s/%s" %(outDir, histName)
#
#l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
#l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
#
#Common.plot1D(
#    l_histDetail_data = l_histDetail_template,
#    l_histDetail_mc = l_histDetail_mc,
#    stackDrawOption = "",
#    ratioPlot = True,
#    title = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T})",
#    xTitle = "m_{T2} [GeV]", yTitle = "# event",
#    ratioYtitle = "Data / MC",
#    xMin = 0,
#    xMax = 200,
#    logY = True,
#    gridX = True,
#    gridY = True,
#    outFileName = outFile,
#)
#

##################################################
histDir = "reco"
histName = "tauTau_MET_mT2_lsp0_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T})",
    xTitle = "m_{T2} [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    xMin = 0,
    xMax = 200,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "tauTau_MET_Dzeta_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "D_{#zeta}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T})",
    xTitle = "D_{#zeta} [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    xMin = -300,
    xMax = 300,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "tauTau_m_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "m(#tau^{reco}_{h1}, #tau^{reco}_{h2})",
    xTitle = "m [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    xMin = 0,
    xMax = 500,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "MET_E_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
#l_histDetail_template = getHistogramDetail_template(histNameFull + "_unsmeared", histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "|#slash{E}_{T}|",
    xTitle = "|#slash{E}_{T}| [GeV]", yTitle = "# event",
    ratioYtitle = "Data / MC",
    xMin = 0,
    xMax = 800,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


##################################################
histDir = "reco"
histName = "MET_phi_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
#l_histDetail_template = getHistogramDetail_template(histNameFull + "_unsmeared", histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    title = "#slash{E}_{T} #phi",
    xTitle = "#phi", yTitle = "# event",
    ratioYtitle = "Data / MC",
    rebinX = 2,
    #xMin = 0,
    #xMax = 800,
    legendPos = "LR",
    #logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


############################################################
######################### 2D plots #########################
############################################################

"""
for iType in range(0, 2) :
    
    
    
    ##################################################
    histDir = "reco"
    histName = "tauTau_MET_mT2_vs_MET_E_reco"
    histNameFull = "%s/%s" %(histDir, histName)
    outFile = "%s/%s" %(outDir, histName)
    
    l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
    l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
    
    histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
    histDetail.hist.Divide(Common.getHistSumFromHistDetailList(l_histDetail_mc))
    
    histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #slash{E}_{T} [Data / MC]"
    
    histDetail.xTitle = "#slash{E}_{T} [GeV]"
    histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"
    
    histDetail.xMin = 0
    histDetail.xMax = 400
    
    histDetail.yMin = 0
    histDetail.yMax = 120
    
    histDetail.zMin = 0
    histDetail.zMax = 2
    
    histDetail.gridX = True
    histDetail.gridY = True
    
    histDetail.drawOption = "colz text45"
    
    histDetail.outFileName = outFile
    
    Common.plot2D(histDetail)
    
    
    ##################################################
    histDir = "reco"
    histName = "MET_vs_tau1_MET_deltaPhi"
    histNameFull = "%s/%s" %(histDir, histName)
    outFile = "%s/%s" %(outDir, histName)
    
    l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
    l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
    
    l_histDetail_template[0].hist.RebinX(2)
    h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
    h_temp.RebinX(2)
    
    histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
    histDetail.hist.Divide(h_temp)
    
    histDetail.histTitle = "#slash{E}_{T} vs. #Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T}) [Data / MC]"
    
    histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T})"
    histDetail.yTitle = "#slash{E}_{T} [GeV]"
    
    histDetail.xMin = -4
    histDetail.xMax = 4
    
    histDetail.yMin = 0
    histDetail.yMax = 400
    
    histDetail.zMin = 0
    histDetail.zMax = 2
    
    histDetail.gridX = True
    histDetail.gridY = True
    
    histDetail.drawOption = "colz text45"
    
    histDetail.outFileName = outFile
    
    Common.plot2D(histDetail)
    
    
    ##################################################
    histDir = "reco"
    histName = "MET_vs_tau2_MET_deltaPhi"
    histNameFull = "%s/%s" %(histDir, histName)
    outFile = "%s/%s" %(outDir, histName)
    
    l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
    l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
    
    l_histDetail_template[0].hist.RebinX(2)
    h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
    h_temp.RebinX(2)
    
    histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
    histDetail.hist.Divide(h_temp)
    
    histDetail.histTitle = "#slash{E}_{T} vs. #Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T}) [Data / MC]"
    
    histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T})"
    histDetail.yTitle = "#slash{E}_{T} [GeV]"
    
    histDetail.xMin = -4
    histDetail.xMax = 4
    
    histDetail.yMin = 0
    histDetail.yMax = 400
    
    histDetail.zMin = 0
    histDetail.zMax = 2
    
    histDetail.gridX = True
    histDetail.gridY = True
    
    histDetail.drawOption = "colz text45"
    
    histDetail.outFileName = outFile
    
    Common.plot2D(histDetail)
    
    
    ##################################################
    histDir = "reco"
    histName = "MET_vs_tauTau_deltaPhi"
    histNameFull = "%s/%s" %(histDir, histName)
    outFile = "%s/%s" %(outDir, histName)
    
    l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
    l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
    
    l_histDetail_template[0].hist.RebinX(2)
    h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
    h_temp.RebinX(2)
    
    histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
    histDetail.hist.Divide(h_temp)
    
    histDetail.histTitle = "#slash{E}_{T} vs. #Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2}) [Data / MC]"
    
    histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2})"
    histDetail.yTitle = "#slash{E}_{T} [GeV]"
    
    histDetail.xMin = -4
    histDetail.xMax = 4
    
    histDetail.yMin = 0
    histDetail.yMax = 400
    
    histDetail.zMin = 0
    histDetail.zMax = 2
    
    histDetail.gridX = True
    histDetail.gridY = True
    
    histDetail.drawOption = "colz text45"
    
    histDetail.outFileName = outFile
    
    Common.plot2D(histDetail)
    
    
    ##################################################
    histDir = "reco"
    histName = "tauTau_MET_mT2_vs_tau1_MET_deltaPhi"
    histNameFull = "%s/%s" %(histDir, histName)
    outFile = "%s/%s" %(outDir, histName)
    
    l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
    l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
    
    l_histDetail_template[0].hist.RebinX(2)
    h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
    h_temp.RebinX(2)
    
    histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
    histDetail.hist.Divide(h_temp)
    
    histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T}) [Data / MC]"
    
    histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T})"
    histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"
    
    histDetail.xMin = -4
    histDetail.xMax = 4
    
    histDetail.yMin = 0
    histDetail.yMax = 120
    
    histDetail.zMin = 0
    histDetail.zMax = 2
    
    histDetail.gridX = True
    histDetail.gridY = True
    
    histDetail.drawOption = "colz text45"
    
    histDetail.outFileName = outFile
    
    Common.plot2D(histDetail)
    
    
    ##################################################
    histDir = "reco"
    histName = "tauTau_MET_mT2_vs_tau2_MET_deltaPhi"
    histNameFull = "%s/%s" %(histDir, histName)
    outFile = "%s/%s" %(outDir, histName)
    
    l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
    l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
    
    l_histDetail_template[0].hist.RebinX(2)
    h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
    h_temp.RebinX(2)
    
    histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
    histDetail.hist.Divide(h_temp)
    
    histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T}) [Data / MC]"
    
    histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T})"
    histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"
    
    histDetail.xMin = -4
    histDetail.xMax = 4
    
    histDetail.yMin = 0
    histDetail.yMax = 120
    
    histDetail.zMin = 0
    histDetail.zMax = 2
    
    histDetail.gridX = True
    histDetail.gridY = True
    
    histDetail.drawOption = "colz text45"
    
    histDetail.outFileName = outFile
    
    Common.plot2D(histDetail)
    
    
    ##################################################
    histDir = "reco"
    histName = "tauTau_MET_mT2_vs_tauTau_deltaPhi"
    histNameFull = "%s/%s" %(histDir, histName)
    outFile = "%s/%s" %(outDir, histName)
    
    l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
    l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)
    
    l_histDetail_template[0].hist.RebinX(2)
    h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
    h_temp.RebinX(2)
    
    histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
    histDetail.hist.Divide(h_temp)
    
    histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2}) [Data / MC]"
    
    histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2})"
    histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"
    
    histDetail.xMin = -4
    histDetail.xMax = 4
    
    histDetail.yMin = 0
    histDetail.yMax = 120
    
    histDetail.zMin = 0
    histDetail.zMax = 2
    
    histDetail.gridX = True
    histDetail.gridY = True
    
    histDetail.drawOption = "colz text45"
    
    histDetail.outFileName = outFile
    
    Common.plot2D(histDetail)
"""

############################################################
######################### 2D ratio #########################
############################################################


##################################################
histDir = "reco"
histName = "tauTau_MET_mT2_vs_MET_E_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s_ratio" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
histDetail.hist.Divide(Common.getHistSumFromHistDetailList(l_histDetail_mc))

histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #slash{E}_{T} [Data / MC]"

histDetail.xTitle = "#slash{E}_{T} [GeV]"
histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"

histDetail.xMin = 0
histDetail.xMax = 400

histDetail.yMin = 0
histDetail.yMax = 120

histDetail.zMin = 0
histDetail.zMax = 2

histDetail.gridX = True
histDetail.gridY = True

histDetail.drawOption = "colz text45"

histDetail.outFileName = outFile

Common.plot2D(histDetail)


##################################################
histDir = "reco"
histName = "MET_vs_tau1_MET_deltaPhi"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s_ratio" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

l_histDetail_template[0].hist.RebinX(2)
h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
h_temp.RebinX(2)

histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
histDetail.hist.Divide(h_temp)

histDetail.histTitle = "#slash{E}_{T} vs. #Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T}) [Data / MC]"

histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T})"
histDetail.yTitle = "#slash{E}_{T} [GeV]"

histDetail.xMin = -4
histDetail.xMax = 4

histDetail.yMin = 0
histDetail.yMax = 400

histDetail.zMin = 0
histDetail.zMax = 2

histDetail.gridX = True
histDetail.gridY = True

histDetail.drawOption = "colz text45"

histDetail.outFileName = outFile

Common.plot2D(histDetail)


##################################################
histDir = "reco"
histName = "MET_vs_tau2_MET_deltaPhi"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s_ratio" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

l_histDetail_template[0].hist.RebinX(2)
h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
h_temp.RebinX(2)

histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
histDetail.hist.Divide(h_temp)

histDetail.histTitle = "#slash{E}_{T} vs. #Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T}) [Data / MC]"

histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T})"
histDetail.yTitle = "#slash{E}_{T} [GeV]"

histDetail.xMin = -4
histDetail.xMax = 4

histDetail.yMin = 0
histDetail.yMax = 400

histDetail.zMin = 0
histDetail.zMax = 2

histDetail.gridX = True
histDetail.gridY = True

histDetail.drawOption = "colz text45"

histDetail.outFileName = outFile

Common.plot2D(histDetail)


##################################################
histDir = "reco"
histName = "MET_vs_tauTau_deltaPhi"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s_ratio" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

print "XXXXXXXXXX"
print l_histDetail_template[0].hist.GetNbinsX(), \
    l_histDetail_template[0].hist.GetBinContent(l_histDetail_template[0].hist.FindBin(-1.0, 200.0)), \
    l_histDetail_template[0].hist.GetBinContent(l_histDetail_template[0].hist.FindBin(-0.5, 200.0)), \
    l_histDetail_template[0].hist.GetBinContent(l_histDetail_template[0].hist.FindBin(0.0, 200.0))
l_histDetail_template[0].hist.RebinX(2)
#l_histDetail_template[0].hist.RebinY(2)
print l_histDetail_template[0].hist.GetNbinsX(), \
    l_histDetail_template[0].hist.GetBinContent(l_histDetail_template[0].hist.FindBin(-1.0, 200.0)), \
    l_histDetail_template[0].hist.GetBinContent(l_histDetail_template[0].hist.FindBin(-0.5, 200.0)), \
    l_histDetail_template[0].hist.GetBinContent(l_histDetail_template[0].hist.FindBin(0.0, 200.0))

h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
print h_temp.GetNbinsX(), \
    h_temp.GetBinContent(h_temp.FindBin(-1.0, 200.0)), \
    h_temp.GetBinContent(h_temp.FindBin(-0.5, 200.0)), \
    h_temp.GetBinContent(h_temp.FindBin(0.0, 200.0))
h_temp.RebinX(2)
#h_temp.RebinY(2)
print h_temp.GetNbinsX(), \
    h_temp.GetBinContent(h_temp.FindBin(-1.0, 200.0)), \
    h_temp.GetBinContent(h_temp.FindBin(-0.5, 200.0)), \
    h_temp.GetBinContent(h_temp.FindBin(0.0, 200.0))

#histDetail = Common.HistogramDetails(hist = h_temp.Clone())
histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
histDetail.hist.Divide(h_temp)

histDetail.histTitle = "#slash{E}_{T} vs. #Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2}) [Data / MC]"

histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2})"
histDetail.yTitle = "#slash{E}_{T} [GeV]"

histDetail.xMin = -4
histDetail.xMax = 4

histDetail.yMin = 0
histDetail.yMax = 400

histDetail.zMin = 0
histDetail.zMax = 2

histDetail.gridX = True
histDetail.gridY = True

histDetail.drawOption = "colz text45"

histDetail.outFileName = outFile

Common.plot2D(histDetail)


##################################################
histDir = "reco"
histName = "tauTau_MET_mT2_vs_tau1_MET_deltaPhi"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s_ratio" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

l_histDetail_template[0].hist.RebinX(2)
h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
h_temp.RebinX(2)

histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
histDetail.hist.Divide(h_temp)

histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T}) [Data / MC]"

histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #slash{E}_{T})"
histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"

histDetail.xMin = -4
histDetail.xMax = 4

histDetail.yMin = 0
histDetail.yMax = 120

histDetail.zMin = 0
histDetail.zMax = 2

histDetail.gridX = True
histDetail.gridY = True

histDetail.drawOption = "colz text45"

histDetail.outFileName = outFile

Common.plot2D(histDetail)


##################################################
histDir = "reco"
histName = "tauTau_MET_mT2_vs_tau2_MET_deltaPhi"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s_ratio" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

l_histDetail_template[0].hist.RebinX(2)
h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
h_temp.RebinX(2)

histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
histDetail.hist.Divide(h_temp)

histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T}) [Data / MC]"

histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h2}, #slash{E}_{T})"
histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"

histDetail.xMin = -4
histDetail.xMax = 4

histDetail.yMin = 0
histDetail.yMax = 120

histDetail.zMin = 0
histDetail.zMax = 2

histDetail.gridX = True
histDetail.gridY = True

histDetail.drawOption = "colz text45"

histDetail.outFileName = outFile

Common.plot2D(histDetail)


##################################################
histDir = "reco"
histName = "tauTau_MET_mT2_vs_tauTau_deltaPhi"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s_ratio" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

l_histDetail_template[0].hist.RebinX(2)
h_temp = Common.getHistSumFromHistDetailList(l_histDetail_mc)
h_temp.RebinX(2)

histDetail = Common.HistogramDetails(hist = l_histDetail_template[0].hist.Clone())
histDetail.hist.Divide(h_temp)

histDetail.histTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) vs. #Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2}) [Data / MC]"

histDetail.xTitle = "#Delta#phi(#tau^{reco}_{h1}, #tau^{reco}_{h2})"
histDetail.yTitle = "m_{T2}(#tau^{reco}_{h1}, #tau^{reco}_{h2}, #slash{E}_{T}) [GeV]"

histDetail.xMin = -4
histDetail.xMax = 4

histDetail.yMin = 0
histDetail.yMax = 120

histDetail.zMin = 0
histDetail.zMax = 2

histDetail.gridX = True
histDetail.gridY = True

histDetail.drawOption = "colz text45"

histDetail.outFileName = outFile

Common.plot2D(histDetail)


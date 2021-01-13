import numpy
import os
import sys

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
numberFormat_float = ".3f"


ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPaintTextFormat(numberFormat_float)
ROOT.gStyle.SetTitleH(0.035)
ROOT.gStyle.SetTitleY(0.985)


outDir = "plots/tauTemplateMethodEstimation/singleTau/ttbar"
histSuffix = ""
histSuffix_templateMethod = ""

#outDir = "plots/tauTemplateMethodEstimation/ttbar_noBaseline"
#histSuffix = "tightTight_OS"
#histSuffix_templateMethod = "OS"


os.system("mkdir -p %s" %(outDir))

suffix = "_singleTau_analysis"
suffix_templateMethod = "_tauTemplateMethodEstimation_singleMuon"

rootFileName = "custom_all_analyzed.root"
rootFileName_templateMethod = "custom_all_tauTemplateMethodEstimation.root"

l_inputFile_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar, suffix, rootFileName)
l_inputFile_templateMethod = Common.getRootFiles(Details.cutFlowDir_ttbar_tauTemplateEstimationMethod, suffix_templateMethod, rootFileName_templateMethod)



luminosity_data = 35.9e3


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
    
    if (isMC) :
        
        hist.Scale(luminosity);
    
    print "Got histogram %s (Integral = %f)" %(histName, hist.Integral())
    print ""
    
    return hist


##################################################
def getHistogramDetail_template(histName, histSuffix) :
    
    l_histDetail = []
    
    histDetail = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = False,
        l_rootFile = l_inputFile_templateMethod,
    ))
    
    histDetail.hist.Scale(1.5)
    
    histDetail.histLabel = "#tau-template method"
    histDetail.color = 1
    
    l_histDetail.append(histDetail)
    
    return l_histDetail



##################################################
def getHistogramDetail_mc(histName, histSuffix) :
    
    l_histDetail = []
    
    
    ##################################################
    histDetail_ttbar = Common.HistogramDetails(hist = getHistogram(
        histName = histName,
        histSuffix = histSuffix,
        isMC = False,
        l_rootFile = l_inputFile_ttbar,
        #l_crossSection = Details.crossSection_ttbar,
        #l_nEvent = Details.nEvent_ttbar,
        #luminosity = luminosity_data,
    ))
    
    histDetail_ttbar.histLabel = Details.label_ttbar[0]
    histDetail_ttbar.color = Details.color_ttbar
    
    l_histDetail.append(histDetail_ttbar)
    
    
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
    fitRatio = "",
    title = "p_{T} of #tau^{reco}_{h1}",
    xTitle = "p_{T} [GeV]", yTitle = "# event",
    xMin = 0,
    xMax = 600,
    logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)


histDir = "reco"
histName = "tau1_phi_reco"
histNameFull = "%s/%s" %(histDir, histName)
outFile = "%s/%s" %(outDir, histName)

l_histDetail_template = getHistogramDetail_template(histNameFull, histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    fitRatio = "",
    title = "#phi of #tau^{reco}_{h1}",
    xTitle = "#phi", yTitle = "# event",
    #xMin = -numpy.pi,
    #xMax = numpy.pi,
    #logY = True,
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
#l_histDetail_template = getHistogramDetail_template("reco/MET_E_reco_unsmeared", histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    fitRatio = "",
    title = "|#slash{E}_{T}|",
    xTitle = "|#slash{E}_{T}| [GeV]", yTitle = "# event",
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
#l_histDetail_template = getHistogramDetail_template("reco/MET_phi_reco_unsmeared", histSuffix_templateMethod)
l_histDetail_mc = getHistogramDetail_mc(histNameFull, histSuffix)

Common.plot1D(
    l_histDetail_data = l_histDetail_template,
    l_histDetail_mc = l_histDetail_mc,
    stackDrawOption = "",
    ratioPlot = True,
    fitRatio = "",
    title = "#slash{E}_{#phi}",
    xTitle = "#slash{E}_{#phi}", yTitle = "# event",
    #xMin = 0,
    #xMax = 800,
    #logY = True,
    gridX = True,
    gridY = True,
    outFileName = outFile,
)

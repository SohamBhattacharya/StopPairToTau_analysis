import numpy
import os
import subprocess

import ROOT
from ROOT import TCanvas
from ROOT import TFile
from ROOT import THStack
from ROOT import TH1F
from ROOT import TLegend
from ROOT import TStyle

import Common
import Details


era = "2016"

CMSextraText = Common.getCMSextraText(isSimOnly = True)
lumiText = Common.getLumitext(era)

nSR = 18
cutFlowNameBase = "SRB"

details_data = "OS_baselineSRB"
details_mc = "OS_genMatched_baselineSRB"

debug = False

histStyle_data = "E"
histStyle_sig = "hist E"

lumi_data = Details.luminosity_data[era]

#plotDir = "plots/compareSigISRreweighting/%s" %(era)
plotDir = "plots/compareSigGenMET/%s" %(era)
os.system("mkdir -p %s" %(plotDir))

ll_regionNumber_SR = [
    [1], [2], [3],
    [4, 5], [6],
    [7], [8], [9],
    [10, 11], [12],
    [13], [14], [15],
    [16, 17], [18],
]

nSR_merged = len(ll_regionNumber_SR)


inputFile_sig_type1 = 0
inputFile_sig_type2 = 0

massPointFile = ""

if (era == "2016") :
    
    inputFile_sig_type1 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/custom_all_analyzed.root", "READ")
    #inputFile_sig_type2 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis_withISRreweighting/custom_all_analyzed.root", "READ")
    inputFile_sig_type2 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis_withGenMET/custom_all_analyzed.root", "READ")
    
    massPointFile = "stopPair_mc/output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"

elif (era == "2017") :
    
    inputFile_sig_type1 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/custom_all_analyzed.root", "READ")
    inputFile_sig_type2 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis_withGenMET/custom_all_analyzed.root", "READ")
    
    massPointFile = "stopPair_mc/output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/XSweightInfo.txt"

#labelExtra_type1 = "(no ISR corr.)"
#labelExtra_type2 = "(with ISR corr.)"

labelExtra_type1 = "(with #slash{E}^{reco}_{T})"
labelExtra_type2 = "(with #slash{E}^{gen}_{T})"


massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")

l_selectMassPoint = [
    ##[500, 1],
    
    #[300, 150],
    #[600, 300],
    #[900, 400],
    
    ##[1000, 1],
    
    [300, 100],
    [800, 300],
    [1000, 1],
    #[1000, 100],
    #[1000, 400],
]

l_yieldPlot_skipMassPoint = [
    #[1000, 1],
]

l_color = [
    2, 4, 6, 8, 46
]


l_METbin = [0, 50, 100, 150, 200, 300, 500, 700, 1000]


l_histDetail_sig = []


count = 0

for iMass in range(0, len(massPointInfo)) :
    
    stop1_m = massPointInfo[iMass, 0]
    neutralino1_m = massPointInfo[iMass, 1]
    xs_sig = massPointInfo[iMass, 3]
    xsUnc_sig = massPointInfo[iMass, 4]
    
    if ([int(stop1_m), int(neutralino1_m)] not in l_selectMassPoint) :
        
        continue
    
    detailStr_sig = "tightTight_OS_genMatched_baselineSRB_%d_%d" %(stop1_m, neutralino1_m)
    
    if ([stop1_m, neutralino1_m] not in l_yieldPlot_skipMassPoint) :
        
        # Type 1 yield histogram
        h1_temp = TH1F("%d_%d" %(stop1_m, neutralino1_m), "%d_%d" %(stop1_m, neutralino1_m), nSR_merged, 0, nSR_merged)
        
        yieldResult_sig_type1 = Common.getYields(
            l_rootFile = [inputFile_sig_type1],
            l_xs = [xs_sig],
            suffix = "_tauTau_analysis",
            systStr = "",
            histName_base = cutFlowNameBase,
            detailStr = detailStr_sig,
            nRegion = 18,
            yieldBinNumber = 6,
            ll_regionNumber = ll_regionNumber_SR,
            scale = lumi_data,
            debug = debug,
        )
        
        for iSR in range(0, nSR_merged) :
            
            h1_temp.SetBinContent(iSR+1, yieldResult_sig_type1["yield"][iSR])
            h1_temp.SetBinError(iSR+1, yieldResult_sig_type1["error"][iSR])
            h1_temp.GetXaxis().SetBinLabel(iSR+1, str(int(iSR+1)))
        
        histDetail_sig_type1 = Common.HistogramDetails()
        
        histDetail_sig_type1.hist = h1_temp.Clone()
        histDetail_sig_type1.histLabel = "x=0.5, [%d, %d] %s" %(stop1_m, neutralino1_m, labelExtra_type1)
        histDetail_sig_type1.color = l_color[count]
        histDetail_sig_type1.lineStyle = 1
        histDetail_sig_type1.markerStyle = 0
        histDetail_sig_type1.drawOption = histStyle_sig
        
        l_histDetail_sig.append(histDetail_sig_type1)
        
        
        # Type 2 yield histogram
        h1_temp = TH1F("%d_%d" %(stop1_m, neutralino1_m), "%d_%d" %(stop1_m, neutralino1_m), nSR_merged, 0, nSR_merged)
        
        yieldResult_sig_type2 = Common.getYields(
            l_rootFile = [inputFile_sig_type2],
            l_xs = [xs_sig],
            suffix = "_tauTau_analysis",
            systStr = "",
            histName_base = cutFlowNameBase,
            detailStr = detailStr_sig,
            nRegion = 18,
            yieldBinNumber = 6,
            ll_regionNumber = ll_regionNumber_SR,
            scale = lumi_data,
            debug = debug,
        )
        
        for iSR in range(0, nSR_merged) :
            
            h1_temp.SetBinContent(iSR+1, yieldResult_sig_type2["yield"][iSR])
            h1_temp.SetBinError(iSR+1, yieldResult_sig_type2["error"][iSR])
            h1_temp.GetXaxis().SetBinLabel(iSR+1, str(int(iSR+1)))
        
        histDetail_sig_type2 = Common.HistogramDetails()
        
        histDetail_sig_type2.hist = h1_temp
        histDetail_sig_type2.histLabel = "x=0.5, [%d, %d] %s" %(stop1_m, neutralino1_m, labelExtra_type2)
        histDetail_sig_type2.color = l_color[count]
        histDetail_sig_type2.lineStyle = 2
        histDetail_sig_type2.markerStyle = 0
        histDetail_sig_type2.drawOption = histStyle_sig
        
        l_histDetail_sig.append(histDetail_sig_type2)
        
        
        count += 1


outFileName = "%s/SRyield_%s" %(plotDir, cutFlowNameBase)

Common.plot1D(
    #l_histDetail_data = l_histDetail_data,
    l_histDetail_mc = l_histDetail_sig,
    #l_histDetail_sig = l_histDetail_sig,
    stackDrawOption = "nostack",
    ratioPlot = False,
    title = "SR yields (%s)" %(era),
    xTitle = "Bin number", yTitle = "Events",
    #ratioYtitle = "Data / Prediction",
    #d_colorRatioGridY = {1: {"color": 2}},
    #xMin = plotQuantity.xMin, xMax = plotQuantity.xMax,
    yMin = 1e-3,
    yMax = 1e5,
    logY = True,
    #ratioHist_ymax = 3,
    gridX = True, gridY = True,
    centerLabelsX = True,
    #nDivisionsX = [nSR, 1, 1],
    drawLegend = True,
    legendTextSize = 0.02,
    legendPos = "UR",
    fixAlphanumericBinLabels = True,
    CMSextraText = CMSextraText,
    lumiText = lumiText,
    outFileName = outFileName,
    #outFileName_suffix = "",
)

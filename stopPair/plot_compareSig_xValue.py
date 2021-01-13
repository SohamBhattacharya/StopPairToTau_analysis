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

withSig = True

CMSextraText = "#scale[0.8]{%s}" %(Common.getCMSextraText(isSimOnly = True))
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
plotDir = "plots/compareSigXval/%s" %(era)
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


inputFile_sig_x0p25 = 0
inputFile_sig_x0p5  = 0
inputFile_sig_x0p75 = 0

massPointFile = ""

if (era == "2016") :
    
    inputFile_sig_x0p25 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/custom_all_analyzed.root", "READ")
    inputFile_sig_x0p5  = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/custom_all_analyzed.root", "READ")
    inputFile_sig_x0p75 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/custom_all_analyzed.root", "READ")
    
    massPointFile = "stopPair_mc/output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"

elif (era == "2017") :
    
    inputFile_sig_type1 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/custom_all_analyzed.root", "READ")
    inputFile_sig_type2 = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis_withGenMET/custom_all_analyzed.root", "READ")
    
    massPointFile = "stopPair_mc/output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/XSweightInfo.txt"


labelExtra_x0p25 = "x=0.25"
labelExtra_x0p5  = "x=0.5"
labelExtra_x0p75 = "x=0.75"


d_xValinfo = {
    "25": {
        "inputFile": inputFile_sig_x0p25,
        "labelExtra": labelExtra_x0p25,
    },
    
    "5": {
        "inputFile": inputFile_sig_x0p5,
        "labelExtra": labelExtra_x0p5,
    },
    
    "75": {
        "inputFile": inputFile_sig_x0p75,
        "labelExtra": labelExtra_x0p75,
    },
}


massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")

l_selectMassPoint = [
    ##[500, 1],
    
    #[300, 150],
    #[600, 300],
    #[900, 400],
    
    ##[1000, 1],
    
    #[300, 100],
    [800, 300],
    [1000, 1],
    #[1000, 100],
    #[1000, 400],
]

l_color = [
    2, 4, 6, 8, 46
]


l_pTbin = [0, 40, 60, 80, 100, 120, 150, 200, 300, 500]
#l_pTbin = [0, 40, 500]

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))
l_phiBin = list(numpy.arange(-3.6, 4.2, 0.6))

l_pTbin_b = [0, 20, 80, 150, 300, 500]

l_mT2bin = [0, 40, 80, 120, 200, 300, 500] if withSig else [0, 40, 80, 120, 200, 300]
#l_mT2bin = [0, 40, 80, 100, 200, 300, 500]
#l_mT2bin = []

l_HTbin = [0, 100, 300, 700, 1100, 1500, 2000, 2500] if withSig else [0, 100, 300, 700, 1200, 1700]
#l_HTbin = [0, 100, 300, 500, 700, 1200, 1700]

#l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]
l_invMassBin = [0, 20, 40, 60, 100, 120, 150, 200, 300]

#l_METbin = [0, 10, 20, 30, 40, 50]
l_METbin = [0, 50, 100, 150, 200, 300, 500, 1000] if withSig else [0, 50, 100, 150, 200, 300, 500]


yMin = 1e-3 if withSig else 1e-2


class PlotQuantity :
    
    name = ""
    
    xtitle = ""
    ytitle = ""
    
    nRebin = 1
    l_rebin = []
    
    xMin = 0
    xMax = 0
    
    yMin = 0
    yMax = 1 #Common.initVal
    
    logY = False
    
    gridX = True
    gridY = True
    
    legendPos = "UR"


l_plotQuantity = []


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_pT_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_pT_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "b1_pT_reco"
plotQuantity_temp.xtitle = "b_{1} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_MET_mT2_lsp0_reco"
#plotQuantity_temp.xtitle = "m_{T2} (#tau^{1}_{h}, #tau^{2}_{h}, p^{miss}_{T}) [GeV]"
plotQuantity_temp.xtitle = "m_{T2} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_mT2bin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_mT2bin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_jet_HT_reco"
#plotQuantity_temp.xtitle = "H_{T} (#tau^{1}_{h}, #tau^{2}_{h}, jet) [GeV]"
plotQuantity_temp.xtitle = "H_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 1000
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "MET_E_reco"
plotQuantity_temp.xtitle = "p^{miss}_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_METbin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)



detailStr = "tightTight_OS_genMatched_baselineSRB"


for iQuantity in range(0, len(l_plotQuantity)) :
    
    plotQuantity = l_plotQuantity[iQuantity]
    
    l_histDetail_sig = []
    
    massCount = 0
    
    for iMass in range(0, len(massPointInfo)) :
        
        stop1_m = massPointInfo[iMass, 0]
        neutralino1_m = massPointInfo[iMass, 1]
        xs_sig = massPointInfo[iMass, 3]
        xsUnc_sig = massPointInfo[iMass, 4]
        
        if ([int(stop1_m), int(neutralino1_m)] not in l_selectMassPoint) :
            
            continue
        
        detailStr_sig = "%s_%d_%d" %(detailStr, stop1_m, neutralino1_m)
        
        histName = "reco/%s/%s_%s" %(detailStr_sig, plotQuantity.name, detailStr_sig)
        nEventHistName = "reco/%s/nEvent_%s" %(detailStr_sig, detailStr_sig)
        
        iXval = 0
        
        for xValKey in sorted(d_xValinfo.keys()) :
            
            h1_temp = Common.HistogramDetails(l_rootFile = [d_xValinfo[xValKey]["inputFile"]], l_xs = [xs_sig], histName = histName)
            h1_temp.getHist(
                xsNormalize = True,
                nEventHistName = nEventHistName,
                nRebin = plotQuantity.nRebin,
                l_rebin = plotQuantity.l_rebin
            )
            
            h1_temp.hist.Scale(Details.luminosity_data[era])
            h1_temp.histLabel = "[%d, %d], %s" %(stop1_m, neutralino1_m, d_xValinfo[xValKey]["labelExtra"])
            #h1_temp.color = ROOT.kCyan + 2*len(l_histDetail_sig)
            #h1_temp.color = ROOT.kMagenta + 2*(len(l_histDetail_sig)+1)
            h1_temp.color = Details.l_color_sig[massCount]
            h1_temp.drawOption = histStyle_sig
            h1_temp.lineStyle = iXval+1
            h1_temp.lineWidth = 5
            
            l_histDetail_sig.append(h1_temp)
            
            iXval += 1
        
        massCount += 1
    
    
    plotDir_mod = "%s/%s" %(plotDir, detailStr)
    os.system("mkdir -p %s" %(plotDir_mod))
    
    outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name)
    
    Common.plot1D(
            l_histDetail_data = [],
            l_histDetail_mc = l_histDetail_sig,
            l_histDetail_sig = [],
            stackDrawOption = "nostack",
            #drawMCerr = True,
            ratioPlot = False,
            #ratioLegendTextSizeScale = 2,
            #ratioStatErr = True,
            #ratioTotalErr = True,
            #drawRatioStatErr = False,
            #drawRatioTotalErr = True,
            ##ratioStatErrLabel = "Stat.",
            #ratioTotalErrLabel = "Bkg. uncertainty",
            title = era,
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            #ratioYtitle = "Data / Prediction",
            #ratioHist_ymax = 2,
            #d_colorRatioGridY = {1: {"color": 2}},
            xMin = plotQuantity.xMin,
            xMax = plotQuantity.xMax,
            yMin = plotQuantity.yMin,
            yMax = plotQuantity.yMax,
            logY = plotQuantity.logY,
            gridX = False, #plotQuantity.gridX,
            gridY = False, #plotQuantity.gridX,
            #centerLabelsX = False, centerLabelsY = False,
            drawLegend = True,
            legendBorder = 0,
            legendTextSize = 0.03,
            legendPos = plotQuantity.legendPos,
            #legendNcolumn = 2,
            dataLegendFirst = True,
            #drawRatioLegend = False,
            #fixAlphanumericBinLabels = False,
            CMSextraText = CMSextraText,
            lumiText = lumiText,
            outFileName = outFileName,
            #outFileName_suffix = "",
        )

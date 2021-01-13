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


l_era = ["2016", "2017"]

CMSextraText = Common.getCMSextraText(isSimOnly = True)
lumiText = ""#Common.getLumitext(era)

nSR = 18
cutFlowNameBase = "SRB"

details_data = "OS_baselineSRB"
details_mc = "OS_genMatched_baselineSRB"

debug = False

histStyle_data = "E"
histStyle_sig = "hist E"

#lumi_data = Details.luminosity_data[era]


#pathSuffix = {
#    "2016": "",
#    
#    "2017": "",
#    #"2017": "_noMETFixEE2017",
#}


#plotDir = "plots/compareSigISRreweighting/%s" %(era)
plotDir = "plots/compareSig_era/%s" %("-".join(l_era))
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


d_inputFile_sig = {
    "2016": ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/custom_all_analyzed.root", "READ"),
    
    "2017": ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/custom_all_analyzed.root", "READ"),
    #"2017": ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis_noMETFixEE2017/custom_all_analyzed.root", "READ"),
}

d_massPointInfo = {
    "2016": numpy.loadtxt("stopPair_mc/output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt", delimiter = ","),
    
    "2017": numpy.loadtxt("stopPair_mc/output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/XSweightInfo.txt", delimiter = ","),
}


l_selectMassPoint = [
    ##[500, 1],
    
    #[300, 150],
    #[600, 300],
    #[900, 400],
    
    ##[1000, 1],
    
    #[400, 100],
    #[800, 400],
    #[1000, 1],
    #[1000, 100],
    #[1000, 400],
    
    [500, 1],
    [500, 300],
    
    [600, 1],
    [600, 250],
    [600, 400],
    
    [800, 1],
]

l_yieldPlot_skipMassPoint = [
    [1000, 1],
]

l_color = [
    2, 4, 6, 8, 46
]


l_pTbin = [0, 40, 80, 150, 300, 500]

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))
l_phiBin = list(numpy.arange(-3.6, 4.2, 0.6))

l_pTbin_b = [0, 20, 80, 150, 300, 500]

l_mTbin = [0, 40, 80, 120, 200, 300, 500]

l_mT2bin = [0, 40, 80, 120, 200, 300, 500]

l_HTbin = [0, 100, 300, 700, 1100, 1500, 2000, 2500]

l_invMassBin = [0, 20, 40, 60, 100, 120, 150, 200, 300]

#l_METbin = [0, 10, 20, 30, 40, 50]
l_METbin = [0, 50, 100, 150, 200, 300, 400, 700]


class PlotQuantity :
    
    name = ""
    
    xtitle = ""
    ytitle = ""
    
    nRebin = 1
    l_rebin = []
    
    xMin = 0
    xMax = 0
    
    yMin = 0
    yMax = 0#1e4 #Common.initVal
    
    logY = False
    
    gridX = True
    gridY = True
    
    legendPos = "UR"


l_plotQuantity = []


for iTau in range(0, 2) :
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "tau%d_pT_reco" %(iTau+1)
    plotQuantity_temp.xtitle = "p^{#tau^{%d}_{h}}_{T} [GeV]" %(iTau+1)
    plotQuantity_temp.ytitle = "a.u."
    plotQuantity_temp.l_rebin = l_pTbin
    plotQuantity_temp.xMin = l_pTbin[1]
    plotQuantity_temp.xMax = l_pTbin[-1]
    #plotQuantity_temp.yMin = yMin
    #plotQuantity_temp.yMax = 500
    plotQuantity_temp.logY = True
    #plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)
    
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "tau%d_eta_reco" %(iTau+1)
    plotQuantity_temp.xtitle = "#eta^{#tau^{%d}_{h}}" %(iTau+1)
    plotQuantity_temp.ytitle = "a.u."
    plotQuantity_temp.l_rebin = l_etaBin
    plotQuantity_temp.xMin = l_etaBin[0]
    plotQuantity_temp.xMax = l_etaBin[-1]
    #plotQuantity_temp.yMin = yMin
    #plotQuantity_temp.yMax = 500
    plotQuantity_temp.logY = True
    plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)
    
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "tau%d_MET_mT_reco" %(iTau+1)
    plotQuantity_temp.xtitle = "m_{T} (#tau^{%d}_{h}, p^{miss}_{T}) [GeV]" %(iTau+1)
    plotQuantity_temp.ytitle = "a.u."
    plotQuantity_temp.l_rebin = l_mTbin
    plotQuantity_temp.xMin = l_mTbin[1]
    plotQuantity_temp.xMax = l_mTbin[-1]
    #plotQuantity_temp.yMin = yMin
    #plotQuantity_temp.yMax = 500
    plotQuantity_temp.logY = True
    #plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)
    
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "tau%d_MET_deltaPhi_reco" %(iTau+1)
    plotQuantity_temp.xtitle = "#Delta#phi(#tau^{%d}_{h}, p^{miss}_{T})" %(iTau+1)
    plotQuantity_temp.ytitle = "a.u."
    plotQuantity_temp.l_rebin = l_phiBin
    plotQuantity_temp.xMin = l_phiBin[0]
    plotQuantity_temp.xMax = l_phiBin[-1]
    #plotQuantity_temp.yMin = yMin
    #plotQuantity_temp.yMax = 500
    plotQuantity_temp.logY = True
    plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)



plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "MET_E_reco"
plotQuantity_temp.xtitle = "p^{miss}_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = l_METbin[1]
plotQuantity_temp.xMax = l_METbin[-1]
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_MET_mT2_lsp0_reco"
plotQuantity_temp.xtitle = "m_{T2} [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_mT2bin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_mT2bin[-1]
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_jet_HT"
plotQuantity_temp.name_gen = "tauTau_jet_HT_gen"
plotQuantity_temp.name = "tauTau_jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} (#tau^{1}_{h}, #tau^{2}_{h}, jet) [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = l_HTbin[1]
plotQuantity_temp.xMax = l_HTbin[-1]
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_jet_MHT_reco"
plotQuantity_temp.xtitle = "#slash{H}_{T} (#tau^{1}_{h}, #tau^{2}_{h}, jet) [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_METbin[-1]
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_n_reco"
plotQuantity_temp.xtitle = "n_{jet}"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_HT"
plotQuantity_temp.name_gen = "jet_HT_gen"
plotQuantity_temp.name = "jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} (jet) [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = l_HTbin[1]
plotQuantity_temp.xMax = l_HTbin[-1]
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_MHT_reco"
plotQuantity_temp.xtitle = "#slash{H}_{T} (jet) [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_METbin[-1]
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


for iJet in range(0, 3) :
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "jet%d_pT" %(iJet+1)
    plotQuantity_temp.name_gen = "jet%d_pT_gen" %(iJet+1)
    plotQuantity_temp.name = "jet%d_pT_reco" %(iJet+1)
    plotQuantity_temp.xtitle = "p^{jet_{%d}}_{T} [GeV]" %(iJet+1)
    plotQuantity_temp.ytitle = "a.u."
    plotQuantity_temp.l_rebin = l_pTbin
    plotQuantity_temp.xMin = l_pTbin[1]
    plotQuantity_temp.xMax = l_pTbin[-1]
    #plotQuantity_temp.yMin = yMin
    #plotQuantity_temp.yMax = 500
    plotQuantity_temp.logY = True
    #plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)
    
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "jet%d_eta_reco" %(iJet+1)
    plotQuantity_temp.xtitle = "#eta^{jet_{%d}}" %(iJet+1)
    plotQuantity_temp.ytitle = "a.u."
    plotQuantity_temp.l_rebin = l_etaBin
    plotQuantity_temp.xMin = l_etaBin[0]
    plotQuantity_temp.xMax = l_etaBin[-1]
    #plotQuantity_temp.yMin = yMin
    #plotQuantity_temp.yMax = 500
    plotQuantity_temp.logY = True
    plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)
    
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "jet%d_MET_deltaPhi_reco" %(iJet+1)
    plotQuantity_temp.xtitle = "#Delta#phi(jet_{%d}, p^{miss}_{T})" %(iJet+1)
    plotQuantity_temp.ytitle = "a.u."
    plotQuantity_temp.l_rebin = l_phiBin
    plotQuantity_temp.xMin = l_phiBin[0]
    plotQuantity_temp.xMax = l_phiBin[-1]
    #plotQuantity_temp.yMin = yMin
    #plotQuantity_temp.yMax = 500
    plotQuantity_temp.logY = True
    plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)


l_histDetail_sig = []


count = 0

for iMass in range(0, len(d_massPointInfo[l_era[0]])) :
    
    stop1_m = d_massPointInfo[l_era[0]][iMass, 0]
    neutralino1_m = d_massPointInfo[l_era[0]][iMass, 1]
    
    if ([int(stop1_m), int(neutralino1_m)] not in l_selectMassPoint) :
        
        continue
    
    detailStr_sig = "tightTight_OS_genMatched_baselineSRB_%d_%d" %(stop1_m, neutralino1_m)
    
    # Distributions
    for iQuantity in range(0, len(l_plotQuantity)) :
        
        plotQuantity = l_plotQuantity[iQuantity]
        
        histName = "reco/%s/%s_%s" %(detailStr_sig, plotQuantity.name, detailStr_sig)
        
        nEventHistName = "reco/%s/nEvent_%s" %(detailStr_sig, detailStr_sig)
        
        l_histDetail = []
        
        for iEra in range(0, len(l_era)) :
            
            era = l_era[iEra]
            
            xs_sig = d_massPointInfo[era][iMass, 3]
            xsUnc_sig = d_massPointInfo[era][iMass, 4]
            
            h1_temp = Common.HistogramDetails(l_rootFile = [d_inputFile_sig[era]], l_xs = [xs_sig], histName = histName)
            h1_temp.getHist(
                xsNormalize = True,
                nEventHistName = nEventHistName,
                nRebin = plotQuantity.nRebin,
                l_rebin = plotQuantity.l_rebin
            )
            #h1_temp.hist.Scale(lumi_data)
            #h1_temp.normalize(byBinWidth = True)
            h1_temp.hist.Scale(1.0 / h1_temp.hist.Integral("width"))
            h1_temp.lineStyle = 1
            h1_temp.color = ROOT.TColor.GetColorDark(iEra+2)
            h1_temp.markerStyle = 0
            h1_temp.drawOption = histStyle_sig
            h1_temp.histLabel = "%s FastSim" %(era)
            #h1_temp.histLabel = "#splitline{x=0.5, [%d, %d]}{FastSim (#mu=%0.0f GeV)}" %(stop1_m, neutralino1_m, h1_temp.hist.GetMean())
            
            l_histDetail.append(h1_temp)
        
        
        plotDir_mod = "%s/%d_%d" %(plotDir, stop1_m, neutralino1_m)
        os.system("mkdir -p %s" %(plotDir_mod))
        
        outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name)
        
        Common.plot1D(
            l_histDetail_data = l_histDetail[1:],
            l_histDetail_mc = [l_histDetail[0]],
            stackDrawOption = "nostack",
            useDataHistDrawOption = True,
            ratioPlot = True,
            ratioLegendTextSizeScale = 2,
            #ratioStatErr = True,
            #ratioTotalErr = True,
            #drawRatioStatErr = False,
            #drawRatioTotalErr = True,
            #ratioStatErrLabel = "Stat.",
            #ratioTotalErrLabel = "Bkg. uncertainty",
            title = era,
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            ratioYtitle = "2017 / 2016",
            ratioHist_ymax = 3,
            d_colorRatioGridY = {1: {"color": 2}},
            xMin = plotQuantity.xMin,
            xMax = plotQuantity.xMax,
            yMin = l_histDetail[0].hist.GetMinimum(0) / 2,
            yMax = l_histDetail[0].hist.GetMaximum() * 2, #plotQuantity.yMax,
            logY = plotQuantity.logY,
            gridX = False, #plotQuantity.gridX,
            gridY = False, #plotQuantity.gridX,
            #centerLabelsX = False, centerLabelsY = False,
            drawLegend = True,
            legendBorder = 0,
            legendTextSize = 0.05 if len(l_selectMassPoint) else 0.045,
            legendPos = plotQuantity.legendPos,
            #legendNcolumn = 2,
            dataLegendFirst = True,
            drawRatioLegend = False,
            #fixAlphanumericBinLabels = False,
            CMSextraText = CMSextraText,
            lumiText = lumiText,
            outFileName = outFileName,
            #outFileName_suffix = "",
        )

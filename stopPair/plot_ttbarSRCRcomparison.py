import array
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
import numpy

import Details


era = "2016"

CMSextraText = Common.getCMSextraText(isSimOnly = True)
lumiText = Common.getLumitext(era)


suffix_SR = "_tauTau_analysis"
suffix_CR_elMu = "_elMu_analysis"
suffix_CR_muMu = "_muMu_analysis"

rootFileName = "custom_all_analyzed.root"

inputFiles_ttbar_SR = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix_SR, rootFileName)
inputFiles_ttbar_CR_elMu = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix_CR_elMu, rootFileName)
inputFiles_ttbar_CR_muMu = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix_CR_muMu, rootFileName)


lumi_data = Details.luminosity_data[era]


plotDir = "plots/ttbar_SRCRcomparison/%s" %(era)
os.system("mkdir -p %s" %(plotDir))

debug = False

histStyle_data = "hist"
histStyle_mc = "E2"

#l_pTbin = [0, 40, 80, 150, 300, 500]
#l_pTbin = [0, 40, 500]
l_pTbin = range(0, 550, 50)

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))
l_phiBin = list(numpy.arange(-3.6, 4.2, 0.6))

#l_pTbin_b = [0, 20, 80, 150, 300, 500]
l_pTbin_b = range(0, 550, 50)

#l_mT2bin = [0, 40, 80, 120, 200, 300, 500]
l_mT2bin = range(0, 320, 20)

#l_HTbin = [0, 100, 300, 700, 1200, 1700]
#l_HTbin = [0, 100, 300, 500, 700, 1200, 1700]
l_HTbin = range(0, 1600, 100)

#l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]
l_invMassBin = [0, 20, 40, 60, 100, 120, 150, 200, 300]

#l_METbin = [0, 50, 100, 150, 200, 300, 500]
l_METbin = range(0, 550, 50)


crossSection_ttbar = Details.crossSection_ttbar[era]


class PlotQuantity :
    
    name_SR = ""
    name_CR_elMu = ""
    name_CR_muMu = ""
    
    xtitle = ""
    ytitle = ""
    
    nRebin = 1
    l_rebin = []
    
    xMin = 0
    xMax = 0
    
    yMin = 0
    yMax = 0
    
    logY = False
    
    gridX = True
    gridY = True
    
    legendPos = "UR"


l_plotQuantity = []



plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "tauTau_MET_mT2_lsp0_reco"
plotQuantity_temp.name_CR_elMu = "elMu_MET_mT2_reco"
plotQuantity_temp.name_CR_muMu = "muMu_MET_mT2_lsp0_reco"
plotQuantity_temp.xtitle = "m_{T2} (obj_{1}, obj_{2}, p^{miss}_{T}) [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_mT2bin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_mT2bin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "jet_HT_reco"
plotQuantity_temp.name_CR_elMu = "jet_HT_reco"
plotQuantity_temp.name_CR_muMu = "jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} (jet) [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "tauTau_jet_HT_reco"
plotQuantity_temp.name_CR_elMu = "elMu_jet_HT_reco"
plotQuantity_temp.name_CR_muMu = "muMu_jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} (obj_{1}, obj_{2}, jet) [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "tauTau_m_reco"
plotQuantity_temp.name_CR_elMu = "elMu_m_reco"
plotQuantity_temp.name_CR_muMu = "muMu_m_reco"
plotQuantity_temp.xtitle = "m [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_invMassBin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_invMassBin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "MET_E_reco"
plotQuantity_temp.name_CR_elMu = "MET_E_reco"
plotQuantity_temp.name_CR_muMu = "MET_E_reco"
plotQuantity_temp.xtitle = "p^{miss}_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_METbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "jet_n_reco"
plotQuantity_temp.name_CR_elMu = "jet_n_reco"
plotQuantity_temp.name_CR_muMu = "jet_n_reco"
plotQuantity_temp.xtitle = "n_{jet}"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LL"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "b_n_medium_reco"
plotQuantity_temp.name_CR_elMu = "b_n_medium_reco"
plotQuantity_temp.name_CR_muMu = "b_n_medium_reco"
plotQuantity_temp.xtitle = "n_{b}"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "UR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name_SR = "b1_pT_reco"
plotQuantity_temp.name_CR_elMu = "b1_pT_reco"
plotQuantity_temp.name_CR_muMu = "b1_pT_reco"
plotQuantity_temp.xtitle = "b_{1} p_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin_b[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 1
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


##################################################

l_details = []

l_details.append({
    "MC_SR": "tightTight_OS_genMatched_baselineSRB",
    "MC_CR": "OS_baselineTTCRB",
    "Dir": "elMu",
})

l_details.append({
    "MC_SR": "tightTight_OS_genMatched_baselineSRB",
    "MC_CR": "OS_baselineTTCRB",
    "Dir": "muMu",
})


for iDetail in range(0, len(l_details)) :
    
    for iQuantity in range(0, len(l_plotQuantity)) :
        
        plotQuantity = l_plotQuantity[iQuantity]
        
        
        # SR
        detailStr = l_details[iDetail]["MC_SR"]
        histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name_SR, detailStr)
        nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
        
        h1_SR = Common.HistogramDetails(l_rootFile = inputFiles_ttbar_SR, l_xs = crossSection_ttbar, histName = histName)
        h1_SR.getHist(
            xsNormalize = True,
            nEventHistName = nEventHistName,
            nRebin = plotQuantity.nRebin,
            l_rebin = plotQuantity.l_rebin,
            debug = debug,
        )
        h1_SR.normalize(byBinWidth = True)
        h1_SR.histLabel = "t#bar{t} #tau_{h}#tau_{h} SR"
        h1_SR.color = 2
        h1_SR.lineWidth = 4
        h1_SR.markerStyle = 20
        h1_SR.drawOption = histStyle_mc
        
        print ""
        
        
        # CR
        l_rootFile = []
        histName = ""
        histLabel = ""
        
        if ("elMu" in l_details[iDetail]["Dir"]) :
            
            l_rootFile = inputFiles_ttbar_CR_elMu
            histName = plotQuantity.name_CR_elMu
            histLabel = "t#bar{t} e#mu CR"
        
        elif ("muMu" in l_details[iDetail]["Dir"]) :
            
            l_rootFile = inputFiles_ttbar_CR_muMu
            histName = plotQuantity.name_CR_muMu
            histLabel = "t#bar{t} #mu#mu CR"
        
        detailStr = l_details[iDetail]["MC_CR"]
        histName = "reco/%s/%s_%s" %(detailStr, histName, detailStr)
        nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
        
        h1_CR = Common.HistogramDetails(l_rootFile = l_rootFile, l_xs = crossSection_ttbar, histName = histName)
        h1_CR.getHist(
            xsNormalize = True,
            nEventHistName = nEventHistName,
            nRebin = plotQuantity.nRebin,
            l_rebin = plotQuantity.l_rebin,
            debug = debug,
        )
        h1_CR.normalize(byBinWidth = True)
        h1_CR.histLabel = histLabel
        h1_CR.color = 4
        h1_CR.lineWidth = 4
        h1_CR.markerStyle = 20
        h1_CR.drawOption = histStyle_mc
        
        print ""
        
        
        plotDir_mod = "%s/%s" %(plotDir, l_details[iDetail]["Dir"])
        os.system("mkdir -p %s" %(plotDir_mod))
        
        outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name_SR)
        
        Common.plot1D(
            l_histDetail_data = [h1_SR],
            l_histDetail_mc = [h1_CR],
            stackDrawOption = "nostack",
            ratioPlot = True,
            title = era,
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            ratioYtitle = "SR / CR",
            xMin = plotQuantity.xMin,
            xMax = plotQuantity.xMax,
            yMin = plotQuantity.yMin,
            yMax = plotQuantity.yMax,
            logY = plotQuantity.logY,
            gridX = plotQuantity.gridX,
            gridY = plotQuantity.gridX,
            #centerLabelsX = False, centerLabelsY = False,
            drawLegend = True,
            legendTextSize = 0.075,
            legendPos = plotQuantity.legendPos,
            #fixAlphanumericBinLabels = False,
            CMSextraText = CMSextraText,
            lumiText = lumiText,
            outFileName = outFileName,
            #outFileName_suffix = "",
        )

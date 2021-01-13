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


suffix = "_tauTau_analysis"

rootFileName = "custom_all_analyzed.root"

era_2016 = "2016"
inputFiles_DYJetsToLL_2016 = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era_2016], suffix, rootFileName)

era_2017 = "2017"
inputFiles_DYJetsToLL_2017 = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era_2017], suffix, rootFileName)


plotDir = "plots/DYJetsToLL_compareEra"
os.system("mkdir -p %s" %(plotDir))


debug = False

histStyle_data = "E"
histStyle_mc = "hist E"

l_pTbin = [0, 30, 50, 80, 150, 300, 500]

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))

l_pTbin_b = [0, 20, 80, 150, 300, 500]

l_mT2bin = [0, 40, 80, 120, 200, 300, 500]

l_HTbin = [0, 100, 300, 700, 1200, 1700]

l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]

l_METbin = [0, 50, 100, 150, 200, 300, 500]


inputFiles_2016 = inputFiles_DYJetsToLL_2016
inputFiles_2017 = inputFiles_DYJetsToLL_2017


crossSections_mc_2016 = Details.crossSection_DYJetsToLL[era_2016]
crossSections_mc_2017 = Details.crossSection_DYJetsToLL[era_2017]

labels_mc = Details.label_DYJetsToLL[0]


class PlotQuantity :
    
    name = ""
    
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
plotQuantity_temp.name = "tau1_pT_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_eta_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_pT_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_eta_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_MET_mT2_lsp0_reco"
plotQuantity_temp.xtitle = "m_{T2} (#tau^{1}_{h}, #tau^{2}_{h}, #slash{E}_{T}) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_mT2bin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_mT2bin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} (#tau^{1}_{h}, #tau^{2}_{h}, jet) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_m_reco"
plotQuantity_temp.xtitle = "m (#tau^{1}_{h}, #tau^{2}_{h}) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_invMassBin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "MET_E_reco"
plotQuantity_temp.xtitle = "#slash{E}_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_METbin[-1]
plotQuantity_temp.yMin = 1e-5
plotQuantity_temp.yMax = 2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


#plotQuantity_temp = PlotQuantity()
#plotQuantity_temp.name = "b1_pT_reco"
#plotQuantity_temp.xtitle = "b_{1} p_{T} [GeV]"
#plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.l_rebin = l_pTbin_b
#plotQuantity_temp.xMin = 0
#plotQuantity_temp.xMax = l_pTbin_b[-1]
#plotQuantity_temp.yMin = 1e-5
#plotQuantity_temp.yMax = 2
#plotQuantity_temp.logY = True
#l_plotQuantity.append(plotQuantity_temp)


##################################################

l_details = []

l_details.append({
    "Data": "tightTight_OS_baselineSRB",
    "Fake": "_OS_baselineSRB",
    "MC": "tightTight_OS_genMatched_baselineSRB",
    "Dir": "OS_baselineSRB",
})

l_details.append({
    "Data": "tightTight_OS_baselineSRB_nb0",
    "Fake": "_OS_baselineSRB_nb0",
    "MC": "tightTight_OS_genMatched_baselineSRB_nb0",
    "Dir": "OS_baselineSRB_nb0",
})


for iDetail in range(0, len(l_details)) :
    
    for iQuantity in range(0, len(l_plotQuantity)) :
        
        plotQuantity = l_plotQuantity[iQuantity]
        
        
        detailStr = l_details[iDetail]["MC"]
        histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
        nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
        
        if ("WJets" in inputFiles_2016[0].GetName() or "DYJets" in inputFiles_2016[0].GetName()) :
            
            nEventHistName = ""
        
        # 2016
        h1_2016 = Common.HistogramDetails(l_rootFile = inputFiles_2016, l_xs = crossSections_mc_2016, histName = histName)
        h1_2016.getHist(
            xsNormalize = True,
            nEventHistName = nEventHistName,
            nRebin = plotQuantity.nRebin,
            l_rebin = plotQuantity.l_rebin
        )
        h1_2016.normalize()
        h1_2016.histLabel = labels_mc + " 2016"
        h1_2016.color = ROOT.kRed
        h1_2016.drawOption = histStyle_mc
        
        print ""
        
        # 2017
        h1_2017 = Common.HistogramDetails(l_rootFile = inputFiles_2017, l_xs = crossSections_mc_2017, histName = histName)
        h1_2017.getHist(
            xsNormalize = True,
            nEventHistName = nEventHistName,
            nRebin = plotQuantity.nRebin,
            l_rebin = plotQuantity.l_rebin
        )
        h1_2017.normalize()
        h1_2017.histLabel = labels_mc + " 2017"
        h1_2017.color = ROOT.kBlue
        h1_2017.drawOption = histStyle_mc
        
        print ""
        
        
        
        ChiSqTestResult = h1_2016.hist.Chi2Test(h1_2017.hist, "WW CHI2")
        ChiSqByNDOF = h1_2016.hist.Chi2Test(h1_2017.hist, "WW CHI2/NDF")
        
        #print ChiSqTestResult / ChiSqByNDOF
        
        
        plotDir_mod = "%s/%s" %(plotDir, l_details[iDetail]["Dir"])
        os.system("mkdir -p %s" %(plotDir_mod))
        
        outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name)
        
        Common.plot1D(
            l_histDetail_data = [h1_2016],
            l_histDetail_mc = [h1_2017],
            stackDrawOption = "nostack",
            #stackDrawOption = "",
            ratioPlot = True,
            title = "[#chi^{2} = %0.4f, #chi^{2}/n_{dof} = %0.4f]" %(ChiSqTestResult, ChiSqByNDOF),
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            ratioYtitle = "2017 / 2016",
            xMin = plotQuantity.xMin,
            xMax = plotQuantity.xMax,
            yMin = plotQuantity.yMin,
            yMax = plotQuantity.yMax,
            logY = plotQuantity.logY,
            gridX = plotQuantity.gridX, gridY = plotQuantity.gridX,
            #centerLabelsX = False, centerLabelsY = False,
            drawLegend = True,
            #legendTextSize = -1,
            legendPos = plotQuantity.legendPos,
            #fixAlphanumericBinLabels = False,
            outFileName = outFileName,
            #outFileName_suffix = "",
        )

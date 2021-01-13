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

era = "2017"

luminosity = Details.luminosity_data[era]


inputFiles_DYJetsToLL_withZpT = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)

l_dir_noZpT = [
    "DYJetsToLL_mc/output_analyzed/dR03_noZpTreweighting/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/dR03_noZpTreweighting/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/dR03_noZpTreweighting/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/dR03_noZpTreweighting/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
    "DYJetsToLL_mc/output_analyzed/dR03_noZpTreweighting/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17",
]

inputFiles_DYJetsToLL_noZpT = Common.getRootFiles(l_dir_noZpT, suffix, rootFileName)


plotDir = "plots/DYJetsToLL_compareZpTreweighting/%s" %(era)
os.system("mkdir -p %s" %(plotDir))


debug = False

histStyle_data = "E"
histStyle_mc = "hist E"

l_pTbin = [0, 30, 50, 80, 150, 300, 500]

l_tauTau_pTbin = range(0, 260, 10)

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))

l_pTbin_b = [0, 20, 80, 150, 300, 500]

l_mT2bin = [0, 40, 80, 120, 200, 300, 500]

l_HTbin = [0, 100, 300, 700, 1200, 1700]

l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]

l_METbin = [0, 50, 100, 150, 200, 300, 500]


inputFiles_withZpT = inputFiles_DYJetsToLL_withZpT
inputFiles_noZpT = inputFiles_DYJetsToLL_noZpT


crossSections_mc_withZpT = Details.crossSection_DYJetsToLL[era]
crossSections_mc_noZpT = Details.crossSection_DYJetsToLL[era]

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
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_eta_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
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
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_eta_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
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
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
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
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_m_reco"
plotQuantity_temp.xtitle = "m (#tau^{1}_{h}, #tau^{2}_{h}) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_invMassBin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_invMassBin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_pT_reco"
plotQuantity_temp.xtitle = "p_{T} (#tau^{1}_{h}, #tau^{2}_{h}) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_tauTau_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_tauTau_pTbin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
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
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.yMax = 100
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


#plotQuantity_temp = PlotQuantity()
#plotQuantity_temp.name = "b1_pT_reco"
#plotQuantity_temp.xtitle = "b_{1} p_{T} [GeV]"
#plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.l_rebin = l_pTbin_b
#plotQuantity_temp.xMin = 0
#plotQuantity_temp.xMax = l_pTbin_b[-1]
#plotQuantity_temp.yMin = 1e-2
#plotQuantity_temp.yMax = 100
#plotQuantity_temp.logY = True
#l_plotQuantity.append(plotQuantity_temp)


##################################################

l_details = []

l_details.append({
    "Data": "tightTight_OS_baselineSRB",
    "Fake": "_OS_baselineSRB",
    "MC": "tightTight_OS_genMatched_baselineSRB",
    "Dir": "tightTight_OS_genMatched_baselineSRB",
})

l_details.append({
    "Data": "tightTight_OS_baselineSRB_nb0",
    "Fake": "_OS_baselineSRB_nb0",
    "MC": "tightTight_OS_genMatched_baselineSRB_nb0",
    "Dir": "tightTight_OS_genMatched_baselineSRB_nb0",
})


for iDetail in range(0, len(l_details)) :
    
    for iQuantity in range(0, len(l_plotQuantity)) :
        
        plotQuantity = l_plotQuantity[iQuantity]
        
        
        detailStr = l_details[iDetail]["MC"]
        histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
        nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
        
        #if ("WJets" in inputFiles_withZpT[0].GetName() or "DYJets" in inputFiles_withZpT[0].GetName()) :
        #    
        #    nEventHistName = ""
        
        # With reweighting
        h1_withZpT = Common.HistogramDetails(l_rootFile = inputFiles_withZpT, l_xs = crossSections_mc_withZpT, histName = histName)
        h1_withZpT.getHist(
            xsNormalize = True,
            nEventHistName = nEventHistName,
            nRebin = plotQuantity.nRebin,
            l_rebin = plotQuantity.l_rebin
        )
        #h1_withZpT.normalize()
        h1_withZpT.hist.Scale(luminosity)
        h1_withZpT.histLabel = labels_mc + " (with Z-p_{T} corr.)"
        h1_withZpT.color = ROOT.kRed
        h1_withZpT.drawOption = histStyle_mc
        
        print ""
        
        # Without reweighting
        h1_noZpT = Common.HistogramDetails(l_rootFile = inputFiles_noZpT, l_xs = crossSections_mc_noZpT, histName = histName)
        h1_noZpT.getHist(
            xsNormalize = True,
            nEventHistName = nEventHistName,
            nRebin = plotQuantity.nRebin,
            l_rebin = plotQuantity.l_rebin
        )
        #h1_noZpT.normalize()
        h1_noZpT.hist.Scale(luminosity)
        h1_noZpT.histLabel = labels_mc + " (without Z-p_{T} corr.)"
        h1_noZpT.color = ROOT.kBlue
        h1_noZpT.drawOption = histStyle_mc
        
        print ""
        
        
        
        #ChiSqTestResult = h1_withZpT.hist.Chi2Test(h1_noZpT.hist, "WW CHI2")
        #ChiSqByNDOF = h1_withZpT.hist.Chi2Test(h1_noZpT.hist, "WW CHI2/NDF")
        
        #print ChiSqTestResult / ChiSqByNDOF
        
        
        plotDir_mod = "%s/%s" %(plotDir, l_details[iDetail]["Dir"])
        os.system("mkdir -p %s" %(plotDir_mod))
        
        outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name)
        
        Common.plot1D(
            l_histDetail_data = [h1_withZpT],
            l_histDetail_mc = [h1_noZpT],
            stackDrawOption = "nostack",
            #stackDrawOption = "",
            ratioPlot = True,
            ratioHistDrawOption = "hist",
            ratioHist_ymin = 0.8,
            ratioHist_ymax = 1.2,
            #title = "[#chi^{2} = %0.4f, #chi^{2}/n_{dof} = %0.4f]" %(ChiSqTestResult, ChiSqByNDOF),
            title = "",
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            ratioYtitle = "Corr. / No corr.",
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

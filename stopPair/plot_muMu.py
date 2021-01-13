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


suffix = "_muMu_analysis"
#suffix = "_muMu_analysis_DYCR"

rootFileName = "custom_all_analyzed.root"

era = "2016"
#era = "2017"

inputFiles_data = Common.getRootFiles(Details.cutFlowDir_muMu_data[era], suffix, rootFileName)

inputFiles_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)
#inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix+"_withZpTreweighting", rootFileName)
inputFiles_VH = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
inputFiles_VV = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
inputFiles_WG = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix, rootFileName)
inputFiles_singleTop = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)


#lumi_data = 8.347e3
lumi_data = Details.luminosity_data[era]


plotDir = "plots/muMu/%s" %(era)
os.system("mkdir -p %s" %(plotDir))

debug = False

histStyle_data = "E"
histStyle_mc = "hist"

l_pTbin = [0, 30, 50, 80, 150, 300, 500]
#l_pTbin = [0, 40, 500]

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))

l_pTbin_b = [0, 20, 80, 150, 300, 500]

l_mT2bin = [0, 40, 80, 120, 200, 300, 500]

l_HTbin = [0, 100, 300, 700, 1200, 1700]

#l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]
l_invMassBin = [0, 20, 40, 60, 70, 80, 90, 100, 110, 120, 150, 200]

l_METbin = [0, 50, 100, 150, 200, 300, 500]




inputFiles_mc = [
    inputFiles_ttbar,
    inputFiles_DYJetsToLL,
    
    (
        inputFiles_WJetsToLNu +
        inputFiles_VH +
        inputFiles_VV +
        inputFiles_WG +
        inputFiles_singleTop
    ),
]


crossSections_mc = [
    Details.crossSection_ttbar[era],
    Details.crossSection_DYJetsToLL[era],
    
    (
        Details.crossSection_WJetsToLNu[era] +
        Details.crossSection_VH[era] +
        Details.crossSection_VV[era] +
        Details.crossSection_WG[era] +
        Details.crossSection_singleTop[era]
    ),
]

labels_mc = [
    Details.latex_ttbar,
    Details.latex_DYJetsToLL,
    
    Details.latex_otherSM,
    
    #Details.label_WJetsToLNu[0],
    #Details.label_VH[0],
    #Details.label_VV[0],
    #Details.label_WG[0],
    #Details.label_singleTop[0],
]

colors_mc = [
    Details.color_ttbar,
    Details.color_DYJetsToLL,
    
    Details.color_otherSM,
    
    #Details.color_WJetsToLNu,
    #Details.color_VH,
    #Details.color_VV,
    #Details.color_WG,
    #Details.color_singleTop,
]


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
    
    gridX = False
    gridY = False
    
    legendPos = "UR"


l_plotQuantity = []

plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "muMu_mu1_pT_reco"
plotQuantity_temp.xtitle = "#mu_{1} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "muMu_mu1_eta_reco"
plotQuantity_temp.xtitle = "#mu_{1} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "UR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "muMu_mu2_pT_reco"
plotQuantity_temp.xtitle = "#mu_{2} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "muMu_mu2_eta_reco"
plotQuantity_temp.xtitle = "#mu_{2} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "UR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "muMu_MET_mT2_lsp0_reco"
plotQuantity_temp.xtitle = "m_{T2} (#mu_{1}, #mu_{2}, p^{miss}_{T}) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_mT2bin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_mT2bin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "muMu_jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "UR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "muMu_m_reco"
plotQuantity_temp.xtitle = "m (#mu_{1}, #mu_{2}) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_invMassBin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "UR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "MET_E_reco"
plotQuantity_temp.xtitle = "p^{miss}_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_METbin[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "b1_pT_reco"
plotQuantity_temp.xtitle = "b_{1} p_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin_b[-1]
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "b_n_medium_reco"
plotQuantity_temp.xtitle = "n_{b}"
plotQuantity_temp.ytitle = "Events / bin"
#plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


#plotQuantity_temp = PlotQuantity()
#plotQuantity_temp.name = "jet_n_reco"
#plotQuantity_temp.xtitle = "n_{jet}"
#plotQuantity_temp.ytitle = "Events / bin"
##plotQuantity_temp.l_rebin = l_pTbin_b
#plotQuantity_temp.xMin = 1
#plotQuantity_temp.xMax = 10
#plotQuantity_temp.yMin = 1e-2
#plotQuantity_temp.logY = True
#l_plotQuantity.append(plotQuantity_temp)


##################################################

l_details = []

l_details.append({
    #"Data": "OS",
    #"MC": "OS",
    
    "Data": "OS_baselineTTCRB",
    "MC": "OS_baselineTTCRB",
    
    "Dir": "",
})

#l_details.append({
#    #"Data": "OS",
#    #"MC": "OS",
#    
#    "Data": "OS_baselineDYCR",
#    "MC": "OS_baselineDYCR",
#    
#    "Dir": "OS_baselineDYCR",
#})


for iDetail in range(0, len(l_details)) :
    
    for iQuantity in range(0, len(l_plotQuantity)) :
        
        plotQuantity = l_plotQuantity[iQuantity]
        
        ##########
        detailStr = l_details[iDetail]["Data"]
        histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
        h1_data = Common.HistogramDetails(l_rootFile = inputFiles_data, histName = histName)
        h1_data.getHist(nRebin = plotQuantity.nRebin, l_rebin = plotQuantity.l_rebin)
        #h1_data.hist = h1_data.hist.Rebin(len(plotQuantity.l_rebin)-1, "", array.array("d", plotQuantity.l_rebin))
        #h1_data.hist.Scale(1.0, "width")
        h1_data.histLabel = "Data"
        h1_data.color = 1
        h1_data.drawOption = histStyle_data
        
        print "\n"
        
        
        l_histDetail_mc = []
        
        
        ##########
        
        for iMC in range(0, len(inputFiles_mc)) :
            
            detailStr = l_details[iDetail]["MC"]
            histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
            nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
            
            #if ("WJets" in inputFiles_mc[iMC][0].GetName() or "DYJets" in inputFiles_mc[iMC][0].GetName()) :
            #    
            #    nEventHistName = ""
            
            h1_temp = Common.HistogramDetails(l_rootFile = inputFiles_mc[iMC], l_xs = crossSections_mc[iMC], histName = histName)
            h1_temp.getHist(
                xsNormalize = True,
                nEventHistName = nEventHistName,
                nRebin = plotQuantity.nRebin,
                l_rebin = plotQuantity.l_rebin
            )
            h1_temp.hist.Scale(lumi_data)
            h1_temp.histLabel = labels_mc[iMC]
            h1_temp.color = colors_mc[iMC]
            h1_temp.drawOption = histStyle_mc
            
            l_histDetail_mc.append(h1_temp)
            
            print ""
        
        
        plotDir_mod = "%s/%s" %(plotDir, l_details[iDetail]["Dir"])
        os.system("mkdir -p %s" %(plotDir_mod))
        
        outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name)
        
        Common.plot1D(
            l_histDetail_data = [h1_data],
            l_histDetail_mc = l_histDetail_mc,
            #stackDrawOption = "nostack",
            stackDrawOption = "",
            ratioPlot = True,
            title = era,
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            ratioYtitle = "Data / Pred.",
            xMin = plotQuantity.xMin, xMax = plotQuantity.xMax,
            yMin = plotQuantity.yMin,
            logY = plotQuantity.logY,
            gridX = plotQuantity.gridX,
            gridY = plotQuantity.gridX,
            #centerLabelsX = False, centerLabelsY = False,
            d_colorRatioGridY = {1: {"color": 2}},
            drawLegend = True,
            legendBorder = 0,
            #legendTextSize = -1,
            legendPos = plotQuantity.legendPos,
            legendTitle = "#mu#mu CR",
            #fixAlphanumericBinLabels = False,
            CMSextraText = Common.getCMSextraText(),
            lumiText = Common.getLumitext(era),
            outFileName = outFileName,
            #outFileName_suffix = "",
        )

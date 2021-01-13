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

isNoStack = True

noStackStr = ""

if (isNoStack) :
    
    noStackStr = "noStack"


CMSextraText = Common.getCMSextraText()
lumiText = Common.getLumitext(era)


suffix = "_tauTau_analysis"
suffix_fakeEstimation = "_tauTau_fakeEstimation"

rootFileName = "custom_all_analyzed.root"
rootFileName_fakeEstimation = "custom_all_fakeEstimation_tauTau.root"

#inputFiles_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data[era], suffix, rootFileName)
inputFiles_fakeEstimation = Common.getRootFiles(Details.cutFlowDir_tauTau_fakeEstimation[era], suffix_fakeEstimation + "_noBaseline", rootFileName_fakeEstimation)

#inputFiles_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix + "_noBaseline", rootFileName)
#inputFiles_VH = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
#inputFiles_VV = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
#inputFiles_WG = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix + "_noBaseline", rootFileName)
#inputFiles_singleTop = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)
#inputFiles_TTX = Common.getRootFiles(Details.cutFlowDir_TTX[era], suffix, rootFileName)

xStr = "0.5"
inputFiles_sig = Common.getRootFiles(["stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16"], suffix + "_noBaseline", rootFileName)

l_massPoint = [
    [400, 100],
    [800, 400],
    [1000, 100],
]


#lumi_data = 8.347e3
#lumi_data = 35.9e3
lumi_data = Details.luminosity_data[era]


plotDir = "plots/tauTau/%s/%s" %(noStackStr, era)
os.system("mkdir -p %s" %(plotDir))

debug = False

histStyle_data = "E"
histStyle_mc = "hist"

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
l_HTbin = range(0, 1800, 100)

#l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]
l_invMassBin = [0, 20, 40, 60, 100, 120, 150, 200, 300]

#l_METbin = [0, 50, 100, 150, 200, 300, 500]
l_METbin = range(0, 620, 20)# + [600, 700]


inputFiles_mc = [
    inputFiles_ttbar,
    inputFiles_DYJetsToLL,
    
    #(
    #    inputFiles_WJetsToLNu +
    #    inputFiles_VH +
    #    inputFiles_VV +
    #    inputFiles_WG +
    #    inputFiles_singleTop +
    #    inputFiles_TTX
    #),
]


crossSections_mc = [
    Details.crossSection_ttbar[era],
    Details.crossSection_DYJetsToLL[era],
    
    #(
    #    Details.crossSection_WJetsToLNu[era] +
    #    Details.crossSection_VH[era] +
    #    Details.crossSection_VV[era] +
    #    Details.crossSection_WG[era] +
    #    Details.crossSection_singleTop[era] +
    #    Details.crossSection_TTX[era]
    #),
]

labels_mc = [
    Details.latex_ttbar,
    Details.latex_DYJetsToLL,
    
   # Details.latex_otherSM,
    
    #Details.label_WJetsToLNu[0],
    #Details.label_VH[0],
    #Details.label_VV[0],
    #Details.label_WG[0],
    #Details.label_singleTop[0],
    #Details.label_TTX[0],
]

colors_mc = [
    Details.color_ttbar,
    Details.color_DYJetsToLL,
    
    #Details.color_otherSM,
    
    #Details.color_WJetsToLNu,
    #Details.color_VH,
    #Details.color_VV,
    #Details.color_WG,
    #Details.color_singleTop,
    #Details.color_TTX,
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
    
    gridX = True
    gridY = True
    
    nDivisionsX = [0, 0, 0]
    
    legendPos = "UR"


l_plotQuantity = []

plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_pT_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} p_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_eta_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} #eta"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_phi_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} #phi"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_phiBin
plotQuantity_temp.xMin = l_phiBin[0]
plotQuantity_temp.xMax = 3.6
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_pT_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} p_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_pTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_eta_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} #eta"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_phi_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} #phi"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_phiBin
plotQuantity_temp.xMin = l_phiBin[0]
plotQuantity_temp.xMax = 3.6
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_MET_mT2_lsp0_reco"
#plotQuantity_temp.xtitle = "m_{T2} (#tau^{1}_{h}, #tau^{2}_{h}, p^{miss}_{T}) [GeV]"
plotQuantity_temp.xtitle = "m_{T2} [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_mT2bin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_mT2bin[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} (jet) [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_jet_HT_reco"
#plotQuantity_temp.xtitle = "H_{T} (#tau^{1}_{h}, #tau^{2}_{h}, jet) [GeV]"
plotQuantity_temp.xtitle = "H_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.nDivisionsX = [5, 5, 0]
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_m_reco"
plotQuantity_temp.xtitle = "m (#tau^{1}_{h}, #tau^{2}_{h}) [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_invMassBin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_invMassBin[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "MET_E_reco"
plotQuantity_temp.xtitle = "p^{miss}_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_METbin[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_n_reco"
plotQuantity_temp.xtitle = "n_{jet}"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LL"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "b_n_medium_reco"
plotQuantity_temp.xtitle = "n_{b}"
plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "UR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "b1_pT_reco"
plotQuantity_temp.xtitle = "b_{1} p_{T} [GeV]"
plotQuantity_temp.ytitle = "a.u."
plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_pTbin_b[-1]
plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


#plotQuantity_temp = PlotQuantity()
#plotQuantity_temp.name = "jet_MET_deltaPhi_min_reco"
#plotQuantity_temp.xtitle = "min(#Delta#phi(jet_{1 to 4}, p^{miss}_{T}))"
#plotQuantity_temp.ytitle = "a.u."
#plotQuantity_temp.l_rebin = l_phiBin
#plotQuantity_temp.xMin = l_phiBin[0]
#plotQuantity_temp.xMax = 3.6
#plotQuantity_temp.yMin = 1e-4
plotQuantity_temp.yMax = 10
#plotQuantity_temp.logY = True
#l_plotQuantity.append(plotQuantity_temp)


##################################################

l_details = []

l_details.append({
    #"Data": "tightTight_OS",
    "Fake": "OS",
    "MC": "tightTight_OS_genMatched",
    "Dir": "OS_noBaseline",
})

#l_details.append({
#    "Data": "tightTight_OS_baselineSRB_nb0_nJetGeq1",
#    "Fake": "OS_baselineSRB_nb0_nJetGeq1",
#    "MC": "tightTight_OS_genMatched_baselineSRB_nb0_nJetGeq1",
#    "Dir": "OS_baselineSRB_nb0_nJetGeq1",
#})


for iDetail in range(0, len(l_details)) :
    
    for iQuantity in range(0, len(l_plotQuantity)) :
        
        plotQuantity = l_plotQuantity[iQuantity]
        
        ###########
        #detailStr = l_details[iDetail]["Data"]
        #histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
        #h1_data = Common.HistogramDetails(l_rootFile = inputFiles_data, histName = histName)
        #h1_data.getHist(nRebin = plotQuantity.nRebin, l_rebin = plotQuantity.l_rebin)
        ##h1_data.hist = h1_data.hist.Rebin(len(plotQuantity.l_rebin)-1, "", array.array("d", plotQuantity.l_rebin))
        ##h1_data.hist.Scale(1.0, "width")
        #h1_data.histLabel = "Data"
        #h1_data.color = 1
        #h1_data.drawOption = histStyle_data
        #
        #print "\n"
        
        
        l_histDetail_mc = []
        
        
        ##########
        histName = plotQuantity.name
        #h1_fakeEstimation = Common.HistogramDetails()
        #h1_fakeEstimation.hist = getFakeEstimationHistogram(
        #    l_rootFile = inputFiles_fakeEstimation,
        #    histName = histName,
        #    suffix = l_details[iDetail]["Fake"],
        #    nRebin = plotQuantity.nRebin,
        #    l_rebin = plotQuantity.l_rebin,
        #    debug = True
        #)
        h1_fakeEstimation = Common.HistogramDetails(l_rootFile = inputFiles_fakeEstimation, histName = histName)
        h1_fakeEstimation.getFakeEstimationHistogram(
            suffix = l_details[iDetail]["Fake"],
            nRebin = plotQuantity.nRebin,
            l_rebin = plotQuantity.l_rebin,
            component = "total",
            debug = True,
        )
        h1_fakeEstimation.normalize()#byBinWidth = (sum(plotQuantity.nDivisionsX) > 0))
        #h1_fakeEstimation.hist.Scale(1.0, "width")
        h1_fakeEstimation.histLabel = "Fake"
        h1_fakeEstimation.color = Details.color_QCD
        h1_fakeEstimation.lineWidth = 4
        h1_fakeEstimation.drawOption = histStyle_mc
        
        l_histDetail_mc.append(h1_fakeEstimation)
        
        
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
            h1_temp.normalize()#byBinWidth = (sum(plotQuantity.nDivisionsX) > 0))
            h1_temp.histLabel = labels_mc[iMC]
            h1_temp.color = colors_mc[iMC]
            h1_temp.lineWidth = 4
            h1_temp.drawOption = histStyle_mc
            
            l_histDetail_mc.append(h1_temp)
            
            print ""
        
        
        ##########
        
        l_histDetail_sig = []
        
        for iSig in range(0, len(l_massPoint)) :
            
            massPoint_str = "%s_%s" %(l_massPoint[iSig][0], l_massPoint[iSig][1])
            
            detailStr = "%s_%s" %(l_details[iDetail]["MC"], massPoint_str)
            
            histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
            nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
            
            h1_temp = Common.HistogramDetails(l_rootFile = inputFiles_sig, l_xs = [], histName = histName)
            h1_temp.getHist(
                xsNormalize = False,
                nEventHistName = nEventHistName,
                nRebin = plotQuantity.nRebin,
                l_rebin = plotQuantity.l_rebin
            )
            h1_temp.hist.Scale(lumi_data)
            h1_temp.normalize()#byBinWidth = (sum(plotQuantity.nDivisionsX) > 0))
            h1_temp.histLabel = "x=%s [%s, %s]" %(xStr, l_massPoint[iSig][0], l_massPoint[iSig][1])
            h1_temp.color = ROOT.TColor.GetColorDark(2 + iSig)
            h1_temp.lineWidth = 4
            h1_temp.drawOption = histStyle_mc
            h1_temp.lineStyle = 2
            
            l_histDetail_sig.append(h1_temp)
            
            print ""
        
        
        
        plotDir_mod = "%s/%s" %(plotDir, l_details[iDetail]["Dir"])
        os.system("mkdir -p %s" %(plotDir_mod))
        
        outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name)
        
        Common.plot1D(
            #l_histDetail_data = [l_histDetail_sig[0]],
            l_histDetail_mc = l_histDetail_mc,
            l_histDetail_sig = l_histDetail_sig,
            stackDrawOption = "nostack",
            ratioPlot = False,
            title = era,
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            ratioYtitle = "Data / Prediction",
            xMin = plotQuantity.xMin,
            xMax = plotQuantity.xMax,
            yMin = plotQuantity.yMin,
            yMax = plotQuantity.yMax,
            logY = plotQuantity.logY,
            nDivisionsX = plotQuantity.nDivisionsX,
            #gridX = plotQuantity.gridX,
            #gridY = plotQuantity.gridX,
            #centerLabelsX = False, centerLabelsY = False,
            drawLegend = True,
            legendTextSize = 0.0325,
            legendPos = plotQuantity.legendPos,
            #fixAlphanumericBinLabels = False,
            CMSextraText = CMSextraText,
            lumiText = lumiText,
            outFileName = outFileName,
            #outFileName_suffix = "",
        )

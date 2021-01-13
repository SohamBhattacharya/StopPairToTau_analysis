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
suffix_appendage = "gtr1sigmaBins2016"

suffix = "_tauTau_analysis_%s" %(suffix_appendage)
suffix_fakeEstimation = "_tauTau_fakeEstimation_%s" %(suffix_appendage)

rootFileName = "custom_all_analyzed.root"
rootFileName_fakeEstimation = "custom_all_fakeEstimation_tauTau.root"

inputFiles_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data[era], suffix, rootFileName)
inputFiles_fakeEstimation = Common.getRootFiles(Details.cutFlowDir_tauTau_fakeEstimation[era], suffix_fakeEstimation, rootFileName_fakeEstimation)

inputFiles_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)
inputFiles_VH = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
inputFiles_VV = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
inputFiles_WG = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix, rootFileName)
inputFiles_singleTop = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)
inputFiles_TTX = Common.getRootFiles(Details.cutFlowDir_TTX[era], suffix, rootFileName)


#lumi_data = 8.347e3
#lumi_data = 35.9e3
lumi_data = Details.luminosity_data[era]


plotDir = "plots/tauTau_gtr1sigmaBins/%s" %(era)
os.system("mkdir -p %s" %(plotDir))

debug = False

histStyle_data = "E"
histStyle_mc = "hist"

l_pTbin = [0, 40, 80, 150, 300, 500]
#l_pTbin = [0, 40, 500]

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))
l_phiBin = list(numpy.arange(-3.6, 4.2, 0.6))
l_deltaPhiBin = list(numpy.arange(-3.6, 4.2, 0.4))
#l_deltaPhiBin = list(numpy.arange(-3.6, 4.2, 0.3))

l_pTbin_b = [0, 20, 80, 150, 300, 500]

l_mT2bin = [0, 40, 80, 120, 200, 300, 500]

l_HTbin = [0, 100, 300, 700, 1200, 1700]
#l_HTbin = [0, 100, 300, 500, 700, 1200, 1700]

#l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]
l_invMassBin = [0, 20, 40, 60, 100, 120, 150, 200, 300]

l_METbin = [0, 50, 100, 150, 200, 300, 500]


inputFiles_mc = [
    inputFiles_WJetsToLNu,
    inputFiles_DYJetsToLL,
    inputFiles_VH,
    inputFiles_VV,
    inputFiles_WG,
    inputFiles_ttbar,
    inputFiles_singleTop,
    inputFiles_TTX,
]


crossSections_mc = [
    Details.crossSection_WJetsToLNu[era],
    Details.crossSection_DYJetsToLL[era],
    Details.crossSection_VH[era],
    Details.crossSection_VV[era],
    Details.crossSection_WG[era],
    Details.crossSection_ttbar[era],
    Details.crossSection_singleTop[era],
    Details.crossSection_TTX[era],
]

labels_mc = [
    Details.label_WJetsToLNu[0],
    Details.label_DYJetsToLL[0],
    Details.label_VH[0],
    Details.label_VV[0],
    Details.label_WG[0],
    Details.label_ttbar[0],
    Details.label_singleTop[0],
    Details.label_TTX[0],
]

colors_mc = [
    Details.color_WJetsToLNu,
    Details.color_DYJetsToLL,
    Details.color_VH,
    Details.color_VV,
    Details.color_WG,
    Details.color_ttbar,
    Details.color_singleTop,
    Details.color_TTX,
]


def printNegativeBins(hist, newBinVal = 0, setBinVal = False) :
    
    for iBin in range(1, hist.GetNbinsX()+1) :
        
        if (hist.GetBinContent(iBin) < 0) :
            
            print "Negative bin content: Bin %d, content %0.2f" %(iBin, hist.GetBinContent(iBin))
            
            if (setBinVal) :
                
                hist.SetBinContent(iBin, newBinVal)


def getFakeEstimationHistogram(l_rootFile, histName, suffix = "", nRebin = 1, l_rebin = [], debug = False, component = "total") :
    
    if (nRebin > 1 and len(l_rebin)) :
        
        print "Error in plotTauFakeEstimation.getFakeEstimationHistogram(...): Provide either \"nRebin\" OR \"l_rebin\"."
        exit(1)
    
    hist = 0
    
    d_detail = {
        "total": [
            ["Nff_Nll", +1.0],
            ["Nff_Nlt", -1.0],
            ["Nff_Ntl", -1.0],
            ["Nff_Ntt", +1.0],
            
            ["Nfp_Nll", -1.0],
            ["Nfp_Nlt", +1.0],
            ["Nfp_Ntl", +1.0],
            ["Nfp_Ntt", -1.0],
        ],
        
        "pos": [
            ["Nff_Nll", +1.0],
            ["Nff_Ntt", +1.0],
            
            ["Nfp_Nlt", +1.0],
            ["Nfp_Ntl", +1.0],
        ],
        
        "neg": [
            ["Nff_Nlt", -1.0],
            ["Nff_Ntl", -1.0],
            
            ["Nfp_Nll", -1.0],
            ["Nfp_Ntt", -1.0],
        ],
    }
    
    l_detail = d_detail[component]
    
    for iFile in range(0, len(l_rootFile)) :
        
        #rootFile = TFile(l_rootFileName[iFile])
        rootFile = l_rootFile[iFile]
        
        iFile_hist = 0
        
        if (debug) :
            
            print "\n"
            print "********************"
            print "getFakeEstimationHistogram(...): File: %s" %(rootFile.GetName())
            print "********************"
        
        tempSum = 0
        
        intermediateHist = 0
        
        for iDetail in range(0, len(l_detail)) :
            
            if (iDetail == 0 or iDetail == 4) :
                
                tempSum = 0
            
            detailStr = l_detail[iDetail][0] + "_" + suffix
            sign = l_detail[iDetail][1]
            
            histName_mod = "%s/%s_%s" %(detailStr, histName, detailStr)
            
            if (debug) :
                
                print ""
                print "getFakeEstimationHistogram(...): Getting histogram %s" %(histName_mod)
            
            h_temp = rootFile.Get(histName_mod).Clone()
            
            if (nRebin > 1) :
                
                h_temp = h_temp.Rebin(nRebin)
            
            if (len(l_rebin)) :
                
                h_temp = h_temp.Rebin(len(l_rebin)-1, "", array.array("d", l_rebin))
            
            if (debug) :
                
                print "getFakeEstimationHistogram(...): Sign %d, Integral %0.2f" %(int(sign), h_temp.Integral())
            
            h_temp.Sumw2()
            h_temp.Scale(sign)
            
            #print "Fake %s %0.4f, %0.4f \n" %(detailStr, h_temp.GetBinContent(4), h_temp.GetBinError(4))
            
            
            if (not iFile_hist) :
                
                iFile_hist = h_temp.Clone()
                
                #if (component == "total") :
                #    
                #    iFile_hist.Reset()
                
                iFile_hist.SetDirectory(0)
                iFile_hist.Sumw2()
            
            else :
            #if (component != "total") :
                
                iFile_hist.Add(h_temp)
            
            if (iDetail == 0 or iDetail == 4) :
                
                intermediateHist = h_temp.Clone()
                intermediateHist.SetDirectory(0)
            
            else :
                
                intermediateHist.Add(h_temp)
            
            tempSum += h_temp.Integral()
            
            #if (component == "total" and (iDetail == 3 or iDetail == 7)) :
            #    
            #    print "Intermediate (iDetail = %s)" %(iDetail)
            #    printNegativeBins(intermediateHist, newBinVal = 0, setBinVal = True)
            #    
            #    #iFile_hist.Add(intermediateHist)
            #    
            #    print "iDetail = %s" %(iDetail)
            #    print "Integral: %f" %(tempSum)
            #    printNegativeBins(iFile_hist, newBinVal = 0, setBinVal = True) 
        
        #print "Fake %0.4f, %0.4f \n" %(iFile_hist.GetBinContent(2), iFile_hist.GetBinError(2))
        
        printNegativeBins(iFile_hist, newBinVal = 0, setBinVal = True)
        
        if (not hist) :
            
            hist = iFile_hist.Clone()
            hist.SetDirectory(0)
            hist.Sumw2()
        
        else :
            
            hist.Add(iFile_hist)
            
        
        #rootFile.Close()
        
        print "getFakeEstimationHistogram(...): File %d integral: %0.2f" %(iFile+1, iFile_hist.Integral())
    
    integralOption = ""
    
    if (len(l_rebin)) :
        
        hist.Scale(1.0, "width")
        integralOption = "width"
    
    print "getFakeEstimationHistogram(...): Final integral %0.2f" %(hist.Integral(integralOption))
    print "\n"
    
    return hist


print "\n"


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
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_phi_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} #phi"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_phiBin
plotQuantity_temp.xMin = l_phiBin[0]
plotQuantity_temp.xMax = 3.6
plotQuantity_temp.yMin = 1e-2
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
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_phi_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} #phi"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_phiBin
plotQuantity_temp.xMin = l_phiBin[0]
plotQuantity_temp.xMax = 3.6
plotQuantity_temp.yMin = 1e-2
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
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_HT_reco"
plotQuantity_temp.xtitle = "H_{T} (jet) [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = 1e-2
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
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_n_reco"
plotQuantity_temp.xtitle = "n_{jet}"
plotQuantity_temp.ytitle = "Events"
#plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
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
plotQuantity_temp.name = "jet_MET_deltaPhi_min_reco"
plotQuantity_temp.xtitle = "min(#Delta#phi(jet_{1 to 4}, #slash{E}_{T}))"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_deltaPhiBin
plotQuantity_temp.xMin = l_deltaPhiBin[0]
plotQuantity_temp.xMax = 3.6
plotQuantity_temp.yMin = 1e-2
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


l_histname = [
    "jet_MET_deltaPhi_jetEta0to2p4",
    "jet_MET_deltaPhi_jetEta2p4to3p139",
    "jet_MET_deltaPhi_jetEta0to5",
    "jet_MET_deltaPhi_jetEta2p65to3p139",
    "jet_MET_deltaPhi_jetEta0to2p65and3p139to5",
    
    "jet_MET_deltaPhiMin_jetEta0to2p4",
    "jet_MET_deltaPhiMin_jetEta2p4to3p139",
    "jet_MET_deltaPhiMin_jetEta0to5",
    "jet_MET_deltaPhiMin_jetEta2p65to3p139",
    "jet_MET_deltaPhiMin_jetEta0to2p65and3p139to5",
]

for iHist in range(0, len(l_histname)) :
    
    histname = l_histname[iHist]
    
    plotQuantity_temp = PlotQuantity()
    plotQuantity_temp.name = "%s_reco" %(histname)
    plotQuantity_temp.xtitle = histname
    plotQuantity_temp.ytitle = "Events / bin-width"
    plotQuantity_temp.l_rebin = l_deltaPhiBin
    plotQuantity_temp.xMin = l_deltaPhiBin[0]
    plotQuantity_temp.xMax = 3.6
    plotQuantity_temp.yMin = 1e-2
    plotQuantity_temp.logY = True
    plotQuantity_temp.legendPos = "LR"
    l_plotQuantity.append(plotQuantity_temp)


##################################################

l_details = []

#l_details.append({
#    "Data": "tightTight_SS_baselineSRB_nbAny",
#    "Fake": "SS_baselineSRB_nbAny",
#    "MC": "tightTight_SS_genMatched_baselineSRB_nbAny",
#    "Dir": "SS_baselineSRB_nbAny"
#})
#
#l_details.append({
#    "Data": "tightTight_OS_baselineSRB_nb0",
#    "Fake": "OS_baselineSRB_nb0",
#    "MC": "tightTight_OS_genMatched_baselineSRB_nb0",
#    "Dir": "OS_baselineSRB_nb0",
#})

l_details.append({
    "Data": "tightTight_OS_baselineSRB_%s" %(suffix_appendage),
    "Fake": "OS_baselineSRB_%s" %(suffix_appendage),
    "MC": "tightTight_OS_genMatched_baselineSRB_%s" %(suffix_appendage),
    "Dir": "OS_baselineSRB_%s" %(suffix_appendage),
})


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
        #h1_fakeEstimation.hist.Scale(1.0, "width")
        h1_fakeEstimation.histLabel = "Fake + Non-prompt"
        h1_fakeEstimation.color = Details.color_QCD
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
            ratioYtitle = "Data / Prediction",
            xMin = plotQuantity.xMin, xMax = plotQuantity.xMax,
            yMin = plotQuantity.yMin,
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

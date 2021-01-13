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


d_file = {
    "500_300": TFile.Open("tempOutput/custom_all_analyzed_stopPair0p75_500_300.root"),
    "800_300": TFile.Open("tempOutput/custom_all_analyzed_stopPair0p75_800_300.root"),
    "1000_300": TFile.Open("tempOutput/custom_all_analyzed_stopPair0p75_1000_300.root"),
    
    
}

rootFileName = "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis_L1prefiringCheck/custom_all_analyzed.root"

rootFile = TFile.Open(rootFileName)

l_massPoint = [
    ["500", "300"],
    ["800", "300"],
    ["1000", "300"],
]


outDir = "plots/L1-prefiring/stopPair_mc/%s" %(era)


##################################################

for iMassPoint in range(0, len(l_massPoint)) :
    
    stop1_m = l_massPoint[iMassPoint][0]
    neutralino1_m = l_massPoint[iMassPoint][1]
    
    plotDir = "tightTight_OS_genMatched_baselineSRB_%s_%s" %(stop1_m, neutralino1_m)
    
    outDir_mod = "%s/%s" %(outDir, plotDir)
    os.system("mkdir -p %s" %(outDir_mod))
    
    ####################
    histName = "jet_pT_eta2p1to2p4_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist(
        nRebin = 3,
        #l_rebin = [],
    )
    
    histDetails.drawOption = "hist E"
    
    Common.plot1D(
        l_histDetail_data = [],
        l_histDetail_mc = [histDetails],
        title = "Jet p_{T} (2.1 < |#eta| < 2.4) [%s, %s]" %(stop1_m, neutralino1_m),
        xTitle = "p^{jet}_{T} [GeV]",
        yTitle = "# events",
        xMin = 0,
        xMax = 500,
        #logY = True,
        gridX = True,
        gridY = True,
        #nDivisionsX = [0, 0, 0], nDivisionsY = [0, 0, 0],
        drawLegend = False,
        legendTextSize = -1,
        legendPos = "UR",
        outFileName = "%s/%s" %(outDir_mod, histName),
    )
    
    
    ####################
    histName = "jet_pT_eta2p1to3_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist(
        nRebin = 3,
        #l_rebin = [],
    )
    
    histDetails.drawOption = "hist E"
    
    Common.plot1D(
        l_histDetail_data = [],
        l_histDetail_mc = [histDetails],
        title = "Jet p_{T} (2.1 < |#eta| < 3) [%s, %s]" %(stop1_m, neutralino1_m),
        xTitle = "p^{jet}_{T} [GeV]",
        yTitle = "# events",
        xMin = 0,
        xMax = 500,
        #logY = True,
        gridX = True,
        gridY = True,
        #nDivisionsX = [0, 0, 0], nDivisionsY = [0, 0, 0],
        drawLegend = False,
        legendTextSize = -1,
        legendPos = "UR",
        outFileName = "%s/%s" %(outDir_mod, histName),
    )
    
    
    ####################
    histName = "jet_HT_eta2p1to2p4_by_jet_HT_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist(
        nRebin = 2,
        #l_rebin = [],
    )
    
    histDetails.drawOption = "hist E"
    
    Common.plot1D(
        l_histDetail_data = [],
        l_histDetail_mc = [histDetails],
        title = "Jet H_{T} fraction in 2.1 < |#eta| < 2.4 [%s, %s]" %(stop1_m, neutralino1_m),
        xTitle = "H^{jet}_{T} (2.1 < |#eta| < 2.4) / H^{jet}_{T} (0 < |#eta| < 2.4)",
        yTitle = "# events",
        #logY = True,
        gridX = True,
        gridY = True,
        #nDivisionsX = [0, 0, 0], nDivisionsY = [0, 0, 0],
        drawLegend = False,
        legendTextSize = -1,
        legendPos = "UR",
        outFileName = "%s/%s" %(outDir_mod, histName),
    )
    
    
    ####################
    histName = "jet_HT_eta2p1to3_by_jet_HT_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist(
        nRebin = 2,
        #l_rebin = [],
    )
    
    histDetails.drawOption = "hist E"
    
    Common.plot1D(
        l_histDetail_data = [],
        l_histDetail_mc = [histDetails],
        title = "Jet H_{T} fraction in 2.1 < |#eta| < 3 [%s, %s]" %(stop1_m, neutralino1_m),
        xTitle = "H^{jet}_{T} (2.1 < |#eta| < 3) / H^{jet}_{T} (0 < |#eta| < 2.4)",
        yTitle = "# events",
        #logY = True,
        gridX = True,
        gridY = True,
        #nDivisionsX = [0, 0, 0], nDivisionsY = [0, 0, 0],
        drawLegend = False,
        legendTextSize = -1,
        legendPos = "UR",
        outFileName = "%s/%s" %(outDir_mod, histName),
    )
    
    
    ####################
    histName = "jet_n_eta2p1to2p4_vs_jet_n_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist()
    
    histDetails.histTitle = "n_{jet} (2.1 < |#eta| < 2.4) vs. n_{jet} (0 < |#eta| < 2.4) [%s, %s]" %(stop1_m, neutralino1_m)
    histDetails.xTitle = "n_{jet} (0 < |#eta| < 2.4)"
    histDetails.yTitle = "n_{jet} (2.1 < |#eta| < 2.4)"
    histDetails.yMax = 5
    histDetails.nDivisionsX = [10, 1, 0]
    histDetails.nDivisionsY = [5, 1, 0]
    histDetails.gridX = True
    histDetails.gridY = True
    histDetails.centerLabelsX = True
    histDetails.centerLabelsY = True
    histDetails.drawOption = "colz text45"
    histDetails.outFileName = "%s/%s" %(outDir_mod, histName)
    
    Common.plot2D(histDetails)
    
    
    ####################
    histName = "jet_n_eta2p1to3_vs_jet_n_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist()
    
    histDetails.histTitle = "n_{jet} (2.1 < |#eta| < 3) vs. n_{jet} (0 < |#eta| < 2.4) [%s, %s]" %(stop1_m, neutralino1_m)
    histDetails.xTitle = "n_{jet} (0 < |#eta| < 2.4)"
    histDetails.yTitle = "n_{jet} (2.1 < |#eta| < 3)"
    histDetails.yMax = 5
    histDetails.nDivisionsX = [10, 1, 0]
    histDetails.nDivisionsY = [5, 1, 0]
    histDetails.gridX = True
    histDetails.gridY = True
    histDetails.centerLabelsX = True
    histDetails.centerLabelsY = True
    histDetails.drawOption = "colz text45"
    histDetails.outFileName = "%s/%s" %(outDir_mod, histName)
    
    Common.plot2D(histDetails)
    
    
    ####################
    histName = "b_n_eta2p1to2p4_vs_b_n_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist()
    
    histDetails.histTitle = "n_{b} (2.1 < |#eta| < 2.4) vs. n_{b} (0 < |#eta| < 2.4) [%s, %s]" %(stop1_m, neutralino1_m)
    histDetails.xTitle = "n_{b} (0 < |#eta| < 2.4)"
    histDetails.yTitle = "n_{b} (2.1 < |#eta| < 2.4)"
    histDetails.yMax = 5
    histDetails.nDivisionsX = [10, 1, 0]
    histDetails.nDivisionsY = [5, 1, 0]
    histDetails.gridX = True
    histDetails.gridY = True
    histDetails.centerLabelsX = True
    histDetails.centerLabelsY = True
    histDetails.drawOption = "colz text45"
    histDetails.outFileName = "%s/%s" %(outDir_mod, histName)
    
    Common.plot2D(histDetails)
    
    
    ####################
    histName = "b_n_eta2p1to3_vs_b_n_reco"
    
    histDetails = Common.HistogramDetails(
        l_rootFile = [rootFile],
        histName = "reco/%s/%s_%s" %(plotDir, histName, plotDir),
    )
    
    histDetails.getHist()
    
    histDetails.histTitle = "n_{b} (2.1 < |#eta| < 3) vs. n_{b} (0 < |#eta| < 2.4) [%s, %s]" %(stop1_m, neutralino1_m)
    histDetails.xTitle = "n_{b} (0 < |#eta| < 2.4)"
    histDetails.yTitle = "n_{b} (2.1 < |#eta| < 3)"
    histDetails.yMax = 5
    histDetails.nDivisionsX = [10, 1, 0]
    histDetails.nDivisionsY = [5, 1, 0]
    histDetails.gridX = True
    histDetails.gridY = True
    histDetails.centerLabelsX = True
    histDetails.centerLabelsY = True
    histDetails.drawOption = "colz text45"
    histDetails.outFileName = "%s/%s" %(outDir_mod, histName)
    
    Common.plot2D(histDetails)
    
    

import array
import os

import ROOT
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TLegend
from ROOT import THStack
from ROOT import TStyle


import Common


ROOT.gStyle.SetPaintTextFormat("0.2f")


era = "2016"

d_inputFileName = {
    "2016": {
        "fast": "ttbar_mc/output_tauIdIsoEfficiency/TTJets_13TeV-madgraphMLM_FastSim_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
        "full": "ttbar_mc/output_tauIdIsoEfficiency/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
    },
    
    "2017": {
        "fast": "ttbar_mc/output_tauIdIsoEfficiency/TTJets_DiLept_TuneCP2_13TeV-madgraphMLM-pythia8_FastSim_Fall17_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
        "full": "ttbar_mc/output_tauIdIsoEfficiency/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
    },
}

d_histName = {
    "2016": {
        "num": "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_eta_reco",
        "den": "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_all_pT_vs_eta_reco",
    },
    
    "2017": {
        "num": "TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_eta_reco",
        "den": "TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_againstElectronLooseMVA6_againstMuonLoose3/tau_all_pT_vs_eta_reco",
    },
}

outDir = "plots/tauFastFullSF/%s" %(era)
os.system("mkdir -p " + outDir)

inputFile_fast = TFile.Open(d_inputFileName[era]["fast"])
inputFile_full = TFile.Open(d_inputFileName[era]["full"])


l_pTbin = [0, 40, 60, 80, 100, 150, 300, 2000]
l_etaBin = [-3, -2.1, -1.2, -0.6, 0, 0.6, 1.2, 2.1, 3]

debug = True

histName_num = d_histName[era]["num"]
histName_den = d_histName[era]["den"]

# Fast num
histDetail_num_fast = Common.HistogramDetails(
    l_rootFile = [inputFile_fast],
    histName = histName_num,
)

histDetail_num_fast.getHist()
histDetail_num_fast.hist = Common.rebin2Dhistogram(
    hist = histDetail_num_fast.hist,
    rebinX = len(l_pTbin) > 0,
    l_xBin_lwrEdge = l_etaBin, 
    rebinY = len(l_etaBin) > 0,
    l_yBin_lwrEdge = l_pTbin,
    debug = debug
)

# Fast den
histDetail_den_fast = Common.HistogramDetails(
    l_rootFile = [inputFile_fast],
    histName = histName_den,
)

histDetail_den_fast.getHist()
histDetail_den_fast.hist = Common.rebin2Dhistogram(
    hist = histDetail_den_fast.hist,
    rebinX = len(l_pTbin) > 0,
    l_xBin_lwrEdge = l_etaBin, 
    rebinY = len(l_etaBin) > 0,
    l_yBin_lwrEdge = l_pTbin,
    debug = debug
)


# Full num
histDetail_num_full = Common.HistogramDetails(
    l_rootFile = [inputFile_full],
    histName = histName_num,
)

histDetail_num_full.getHist()
histDetail_num_full.hist = Common.rebin2Dhistogram(
    hist = histDetail_num_full.hist,
    rebinX = len(l_pTbin) > 0,
    l_xBin_lwrEdge = l_etaBin, 
    rebinY = len(l_etaBin) > 0,
    l_yBin_lwrEdge = l_pTbin,
    debug = debug
)

# Full den
histDetail_den_full = Common.HistogramDetails(
    l_rootFile = [inputFile_full],
    histName = histName_den,
)

histDetail_den_full.getHist()
histDetail_den_full.hist = Common.rebin2Dhistogram(
    hist = histDetail_den_full.hist,
    rebinX = len(l_pTbin) > 0,
    l_xBin_lwrEdge = l_etaBin, 
    rebinY = len(l_etaBin) > 0,
    l_yBin_lwrEdge = l_pTbin,
    debug = debug
)


# Ratio
histDetail_num_fast.hist.Divide(histDetail_den_fast.hist)
histDetail_num_full.hist.Divide(histDetail_den_full.hist)


# Full / Fast
histDetail_num_full.hist.Divide(histDetail_num_fast.hist)

histDetail_num_full.hist.SetMarkerSize(0.8*histDetail_num_full.hist.GetMarkerSize())

histDetail_num_full.histTitle = "FullSim efficiency / FastSim efficiency (%s)" %(era)

#histDetail_num_full.rebinX = 1
#histDetail_num_full.rebinY = 1

histDetail_num_full.xTitle = "#tau_{h} #eta"
histDetail_num_full.yTitle = "#tau_{h} p_{T}"

histDetail_num_full.gridX = True
histDetail_num_full.gridY = True

histDetail_num_full.xMin = -2.1
histDetail_num_full.xMax = 2.1

histDetail_num_full.yMin = 40
histDetail_num_full.yMax = 300

#nDivisionsX = [0, 0, 0]
#nDivisionsY = [0, 0, 0]

histDetail_num_full.drawOption = "colz E text"

histDetail_num_full.outFileName = "%s/tauFastFullSF" %(outDir)
#outFileName_suffix = ""

Common.plot2D(histDetail_num_full)

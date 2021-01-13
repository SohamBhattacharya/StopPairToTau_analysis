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

import CMS_lumi
import tdrstyle


era = "2016"

computeFraction = False


d_inputFile = {
    #"2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
    
    #"2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
    #"2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency_noMETcutForTauFakeComposition/custom_all_tauIdIsoEfficiency.root",
    #"2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency_noTauPairSelection-withMETcutForTauFakeComposition/custom_all_tauIdIsoEfficiency.root",
    #"2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency_noTauPairSelection-noMETcutForTauFakeComposition/custom_all_tauIdIsoEfficiency.root",
    "2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency_withPromptElMu-withTauPairSelection-withMETcutForTauFakeComposition/custom_all_tauIdIsoEfficiency.root",
    #"2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency_withPromptElMu-withExclusiveElMuMatching-withTauPairSelection-withMETcutForTauFakeComposition/custom_all_tauIdIsoEfficiency.root",
    
    #"2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency_antiElMuTight_withTauPairSelection-withMETcutForTauFakeComposition/custom_all_tauIdIsoEfficiency.root",
    
    #"2017": "ttbar_mc/output_tauIdIsoEfficiency/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
}


d_histDir = {
    "2016": "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3",
    #"2016": "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronTightMVA6_againstMuonTight3",
    
    #"2017": "TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_againstElectronLooseMVA6_againstMuonLoose3",

}


outDir = "plots/fakeTauComposition/%s" %(era)
#outDir = "plots/fakeTauComposition_noMETcutForTauFakeComposition/%s" %(era)
#outDir = "plots/fakeTauComposition_noTauPairSelection-withMETcutForTauFakeComposition/%s" %(era)
#outDir = "plots/fakeTauComposition_noTauPairSelection-noMETcutForTauFakeComposition/%s" %(era)
#outDir = "plots/fakeTauComposition_withPromptElMu-withTauPairSelection-withMETcutForTauFakeComposition/%s" %(era)
#outDir = "plots/fakeTauComposition_withPromptElMu-withExclusiveElMuMatching-withTauPairSelection-withMETcutForTauFakeComposition/%s" %(era)

#outDir = "plots/fakeTauComposition_antiElMuTight_withTauPairSelection-withMETcutForTauFakeComposition/%s" %(era)

os.system("mkdir -p " + outDir)
inputFile = TFile.Open(d_inputFile[era])


l_pTbin = [0, 40, 60, 80, 100, 150, 300]
#l_pTbin = [40, 60, 80, 100, 150, 300]
#l_pTbin = [0, 40, 80, 120, 160, 200]
l_DM = [0, 1, 10]


####################################################################################################


#histStyle_mc = "hist E"
histStyle_mc = "hist E1"

l_histDetail = []


histName = "%s/tau_genNotMatched_pT_reco" %(d_histDir[era])
print histName
h1_tau_genNotMatched = inputFile.Get(histName).Clone()
h1_tau_genNotMatched.Sumw2()
h1_tau_genNotMatched.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))

histDetail_tau_genNotMatched = Common.HistogramDetails()
histDetail_tau_genNotMatched.hist = h1_tau_genNotMatched
histDetail_tau_genNotMatched.histLabel = "All fake #tau_{h}"
histDetail_tau_genNotMatched.color = 1
histDetail_tau_genNotMatched.linewidth = 3
histDetail_tau_genNotMatched.drawOption = histStyle_mc
histDetail_tau_genNotMatched.markerStyle = 1
print "%s integral: %f" %(histName, h1_tau_genNotMatched.Integral(h1_tau_genNotMatched.FindBin(40.0), h1_tau_genNotMatched.GetNbinsX()))


#####
histName = "%s/tau_genNotMatched_genElMatched_pT_reco" %(d_histDir[era])
print histName
h1_tau_genNotMatched_genElMatched = inputFile.Get(histName).Clone()
h1_tau_genNotMatched_genElMatched.Sumw2()
h1_tau_genNotMatched_genElMatched.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
#h1_tau_genNotMatched_genElMatched.Divide(h1_tau_genNotMatched)
h1_tau_genNotMatched_genElMatched.SetLineColor(2)
h1_tau_genNotMatched_genElMatched.SetLineWidth(3)

histDetail_tau_genNotMatched_genElMatched = Common.HistogramDetails()
histDetail_tau_genNotMatched_genElMatched.hist = h1_tau_genNotMatched_genElMatched
histDetail_tau_genNotMatched_genElMatched.histLabel = "e^{gen}-matched fake #tau_{h}"
histDetail_tau_genNotMatched_genElMatched.color = 2
histDetail_tau_genNotMatched_genElMatched.linewidth = 3
histDetail_tau_genNotMatched_genElMatched.drawOption = histStyle_mc
print "%s integral: %f" %(histName, h1_tau_genNotMatched_genElMatched.Integral(h1_tau_genNotMatched_genElMatched.FindBin(40.0), h1_tau_genNotMatched_genElMatched.GetNbinsX()))

l_histDetail.append(histDetail_tau_genNotMatched_genElMatched)


#####
histName = "%s/tau_genNotMatched_genMuMatched_pT_reco" %(d_histDir[era])
print histName
h1_tau_genNotMatched_genMuMatched = inputFile.Get(histName).Clone()
h1_tau_genNotMatched_genMuMatched.Sumw2()
h1_tau_genNotMatched_genMuMatched.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
#h1_tau_genNotMatched_genMuMatched.Divide(h1_tau_genNotMatched)
h1_tau_genNotMatched_genMuMatched.SetLineColor(4)
h1_tau_genNotMatched_genMuMatched.SetLineWidth(3)

histDetail_tau_genNotMatched_genMuMatched = Common.HistogramDetails()
histDetail_tau_genNotMatched_genMuMatched.hist = h1_tau_genNotMatched_genMuMatched
histDetail_tau_genNotMatched_genMuMatched.histLabel = "#mu^{gen}-matched fake #tau_{h}"
histDetail_tau_genNotMatched_genMuMatched.color = 4
histDetail_tau_genNotMatched_genMuMatched.linewidth = 3
histDetail_tau_genNotMatched_genMuMatched.drawOption = histStyle_mc
print "%s integral: %f" %(histName, h1_tau_genNotMatched_genMuMatched.Integral(h1_tau_genNotMatched_genMuMatched.FindBin(40.0), h1_tau_genNotMatched_genMuMatched.GetNbinsX()))

l_histDetail.append(histDetail_tau_genNotMatched_genMuMatched)


#####
histName = "%s/tau_genNotMatched_genBmatched_pT_reco" %(d_histDir[era])
print histName
h1_tau_genNotMatched_genBmatched = inputFile.Get(histName).Clone()
h1_tau_genNotMatched_genBmatched.Sumw2()
h1_tau_genNotMatched_genBmatched.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
#h1_tau_genNotMatched_genBmatched.Divide(h1_tau_genNotMatched)
h1_tau_genNotMatched_genBmatched.SetLineColor(6)
h1_tau_genNotMatched_genBmatched.SetLineWidth(3)

histDetail_tau_genNotMatched_genBmatched = Common.HistogramDetails()
histDetail_tau_genNotMatched_genBmatched.hist = h1_tau_genNotMatched_genBmatched
histDetail_tau_genNotMatched_genBmatched.histLabel = "b^{gen}-matched fake #tau_{h}"
histDetail_tau_genNotMatched_genBmatched.color = 6
histDetail_tau_genNotMatched_genBmatched.linewidth = 3
histDetail_tau_genNotMatched_genBmatched.drawOption = histStyle_mc
print "%s integral: %f" %(histName, h1_tau_genNotMatched_genBmatched.Integral(h1_tau_genNotMatched_genBmatched.FindBin(40.0), h1_tau_genNotMatched_genBmatched.GetNbinsX()))

l_histDetail.append(histDetail_tau_genNotMatched_genBmatched)


yMax = 0
yTitle = ""
outFileName = ""

if (computeFraction) :
    
    histDetail_tau_genNotMatched_genElMatched.hist.Divide(histDetail_tau_genNotMatched.hist)
    histDetail_tau_genNotMatched_genMuMatched.hist.Divide(histDetail_tau_genNotMatched.hist)
    histDetail_tau_genNotMatched_genBmatched.hist.Divide(histDetail_tau_genNotMatched.hist)
    
    yMax = 1.2
    yTitle = "Fraction of fake #tau_{h}"
    outFileName = "%s/fakeTauComposition_ratio_pT" %(outDir)

else :
    
    l_histDetail = [histDetail_tau_genNotMatched] + l_histDetail
    
    yMax = 2e3
    yTitle = "No. of #tau_{h}"
    outFileName = "%s/fakeTauComposition_pT" %(outDir)


Common.plot1D(
    #l_histDetail_data = [histDetail_tau_genNotMatched],
    l_histDetail_mc = l_histDetail,
    stackDrawOption = "nostack",
    useDataHistDrawOption = True,
    #ratioPlot = False,
    #ratioHistDrawOption = "E1",
    #ratioHist_ymin = 0,
    #ratioHist_ymax = 1,
    title = "",
    xTitle = "#tau_{h} p_{T}",
    yTitle = yTitle,
    ratioYtitle = "fraction",
    xMin = 40, xMax = l_pTbin[-1],
    #yMin = initVal,
    yMax = yMax,
    logX = False, logY = False,
    gridX = True, gridY = True,
    #nDivisionsX = [5, 5, 1],
    #centerLabelsX = True, centerLabelsY = True,
    drawLegend = True,
    legendTitle = "",
    legendTextSize = 0.0325,
    legendPos = "UR",
    CMSextraText = Common.getCMSextraText(era, isSimOnly = True),
    lumiText = Common.getLumitext(era),
    outFileName = outFileName,
)

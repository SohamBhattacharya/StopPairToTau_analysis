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
import Details


inputFileName = "ttbar_mc/output_miscellaneous/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_miscellaneous/custom_all_miscellaneous.root"


outDir = "plots/miscellaneous/ttbar"
os.system("mkdir -p %s" %(outDir))


##################################################
histName = "mu1_pT_gen"
h1_mu1_pT_gen = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h1_mu1_pT_gen.getHist()
#h1_mu1_pT_gen.normalize()
h1_mu1_pT_gen.histLabel = "#mu^{gen}_{1}"

histName = "mu1_genMatched_pT_reco"
h1_mu1_genMatched_pT_reco = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h1_mu1_genMatched_pT_reco.getHist()
#h1_mu1_genMatched_pT_reco.normalize()
h1_mu1_genMatched_pT_reco.histLabel = "#mu^{reco}_{1}"
h1_mu1_genMatched_pT_reco.color = 1

outFileName = "%s/mu1_gen-reco_pT" %(outDir)

Common.plot1D(
    l_histDetail_data = [h1_mu1_genMatched_pT_reco],
    l_histDetail_mc = [h1_mu1_pT_gen],
    stackDrawOption = "nostack",
    ratioPlot = True,
    title = "",
    xTitle = "p_{T} [GeV]", yTitle = "",
    ratioYtitle = "reco / gen",
    xMin = 0, xMax = 600,
    #yMin = initVal, yMax = initVal,
    logY = True,
    gridX = True, gridY = True,
    #centerLabelsX = False, centerLabelsY = False,
    drawLegend = True,
    #legendTextSize = -1,
    #legendPos = "UR",
    #fixAlphanumericBinLabels = False,
    outFileName = outFileName,
    #outFileName_suffix = "",
)


##################################################
histName = "mu1_genMatched_pT_reco"
#histName = "mu1_pT_reco"
h1_mu1_genMatched_pT_reco = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h1_mu1_genMatched_pT_reco.getHist()
h1_mu1_genMatched_pT_reco.normalize()
h1_mu1_genMatched_pT_reco.histLabel = "#mu^{reco}_{1}"

histName = "tau1_pT_gen"
h1_tau1_pT_gen = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h1_tau1_pT_gen.getHist()
h1_tau1_pT_gen.normalize()
h1_tau1_pT_gen.histLabel = "#tau^{gen}_{1}"
h1_tau1_pT_gen.color = 1

outFileName = "%s/tau1gen-mu1reco_pT" %(outDir)

Common.plot1D(
    l_histDetail_data = [h1_tau1_pT_gen],
    l_histDetail_mc = [h1_mu1_genMatched_pT_reco],
    stackDrawOption = "nostack",
    ratioPlot = True,
    title = "",
    xTitle = "p_{T} [GeV]", yTitle = "",
    ratioYtitle = "#tau / #mu",
    xMin = 0, xMax = 600,
    #yMin = initVal, yMax = initVal,
    logY = True,
    gridX = True, gridY = True,
    #centerLabelsX = False, centerLabelsY = False,
    drawLegend = True,
    #legendTextSize = -1,
    #legendPos = "UR",
    #fixAlphanumericBinLabels = False,
    outFileName = outFileName,
    #outFileName_suffix = "",
)


##################################################
histName = "mu1_pT_gen"
h1_mu1_pT_gen = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h1_mu1_pT_gen.getHist()
#h1_mu1_pT_gen.normalize()
h1_mu1_pT_gen.histLabel = "#mu^{gen}_{1}"

histName = "tau1_pT_gen"
h1_tau1_pT_gen = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h1_tau1_pT_gen.getHist()
#h1_tau1_pT_gen.normalize()
h1_tau1_pT_gen.histLabel = "#tau^{gen}_{1}"
h1_tau1_pT_gen.color = 1

outFileName = "%s/tau1-mu1_pT" %(outDir)

Common.plot1D(
    l_histDetail_data = [h1_tau1_pT_gen],
    l_histDetail_mc = [h1_mu1_pT_gen],
    stackDrawOption = "nostack",
    ratioPlot = True,
    title = "",
    xTitle = "p_{T} [GeV]", yTitle = "",
    ratioYtitle = "#tau / #mu",
    xMin = 0, xMax = 600,
    #yMin = initVal, yMax = initVal,
    logY = True,
    gridX = True, gridY = True,
    #centerLabelsX = False, centerLabelsY = False,
    drawLegend = True,
    #legendTextSize = -1,
    #legendPos = "UR",
    #fixAlphanumericBinLabels = False,
    outFileName = outFileName,
    #outFileName_suffix = "",
)


##################################################
histName = "mu1_resolution_pT"
h1_mu1_resolution_pT = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h1_mu1_resolution_pT.getHist()
h1_mu1_resolution_pT.normalize()
h1_mu1_resolution_pT.histLabel = "#splitline{#mu = %0.4f}{#sigma = %0.4f}" %(h1_mu1_resolution_pT.hist.GetMean(), h1_mu1_resolution_pT.hist.GetStdDev())

outFileName = "%s/mu1_resolution_pT" %(outDir)

Common.plot1D(
    l_histDetail_mc = [h1_mu1_resolution_pT],
    stackDrawOption = "nostack",
    title = "",
    xTitle = "p^{reco-#mu_{1}}_{T} / p^{gen-#mu_{1}}_{T}", yTitle = "a.u.",
    #xMin = 0, xMax = 600,
    #yMin = initVal, yMax = initVal,
    logY = True,
    gridX = True, gridY = True,
    #centerLabelsX = False, centerLabelsY = False,
    drawLegend = True,
    #legendTextSize = -1,
    #legendPos = "UR",
    #fixAlphanumericBinLabels = False,
    outFileName = outFileName,
    #outFileName_suffix = "",
)


##################################################
histName = "tau_n_gen_vs_reco"
h2_tau_n_gen_vs_reco = Common.HistogramDetails(rootFileName = inputFileName, histName = histName)
h2_tau_n_gen_vs_reco.getHist()
h2_tau_n_gen_vs_reco.histTitle = "n_{#tau^{gen}_{h}} vs. n_{#tau^{reco}_{h}}"
h2_tau_n_gen_vs_reco.xTitle = "n_{#tau^{reco}_{h}}"
h2_tau_n_gen_vs_reco.yTitle = "n_{#tau^{gen}_{h}}"
h2_tau_n_gen_vs_reco.centerLabelsX = True
h2_tau_n_gen_vs_reco.centerLabelsY = True
h2_tau_n_gen_vs_reco.logZ = True
h2_tau_n_gen_vs_reco.gridY = True
h2_tau_n_gen_vs_reco.drawOption = "colz text89"
h2_tau_n_gen_vs_reco.outFileName = "%s/%s" %(outDir, histName)

h2_tau_n_gen_vs_reco.hist.GetYaxis().SetNdivisions(5, 0, 0)

for iVal in range(0, 3) :
    
    xBin = h2_tau_n_gen_vs_reco.hist.GetXaxis().FindBin(iVal)
    print xBin
    
    binLabel = "%d" %(iVal)
    h2_tau_n_gen_vs_reco.hist.GetXaxis().SetBinLabel(xBin, binLabel)
    
    if (not iVal) :
        
        continue
    
    for jVal in range(0, iVal+1) :
        
        xVal = (iVal + 0.5) + float(jVal)/(iVal+1)*0.5
        
        xBin = h2_tau_n_gen_vs_reco.hist.GetXaxis().FindBin(xVal)
        print xVal, xBin
        
        binLabel = "%d/%d" %(jVal, iVal)
        h2_tau_n_gen_vs_reco.hist.GetXaxis().SetBinLabel(xBin, binLabel)

h2_tau_n_gen_vs_reco.hist.LabelsOption("v", "X")
h2_tau_n_gen_vs_reco.hist.GetXaxis().SetLabelSize(0.05)

print h2_tau_n_gen_vs_reco.hist.GetTitleSize()

Common.plot2D(h2_tau_n_gen_vs_reco)

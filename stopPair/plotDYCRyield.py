import numpy
import os
import subprocess

import ROOT
from ROOT import TCanvas
from ROOT import TFile
from ROOT import THStack
from ROOT import TH1F
from ROOT import TLegend
from ROOT import TStyle

import Common
import Details

import CMS_lumi
import tdrstyle


ROOT.gStyle.SetTitleH(0.085)


era = "2016"

rootFileName = "custom_all_analyzed.root"

applyDYSF = True

suffix = ""
inputFiles_data_DYSF = 0
label_data = ""
sampleLabel_DYSF = ""
sampleLabelLatex = ""


#lumi_data = 35.9e3
lumi_data = Details.luminosity_data[era]


plotDir = "plots/DYCR_yields/%s" %(era)
os.system("mkdir -p %s" %(plotDir))



#nCR = 6
#cutFlowNameBase = "CRA"

nCR = 18
cutFlowNameBase = "DYCR"

details_data_DYSF = "OS_baselineDYCR"
details_mc_DYSF = "OS_baselineDYCR"

nEventHistName = "nEvent"

debug = False

histStyle_data = "E"
histStyle_mc = "hist"


ll_regionNumber_CR = [
    [1], [2], [3],
    [4, 5, 6],
    [7], [8], [9],
    [10, 11, 12],
    [13], [14], [15],
    [16, 17, 18],
    #[16, 17, 18],
]

nCR_merged = len(ll_regionNumber_CR)


inputFiles_mc = []

crossSections_mc = [
    Details.crossSection_ttbar[era],
    Details.crossSection_DYJetsToLL[era],
    
    (
        Details.crossSection_WJetsToLNu[era] +
        Details.crossSection_VH[era] +
        Details.crossSection_VV[era] +
        Details.crossSection_WG[era] +
        Details.crossSection_singleTop[era] +
        Details.crossSection_TTX[era]
    ),
]

labels_mc = [
    Details.label_ttbar[0],
    Details.label_DYJetsToLL[0],
    
    Details.label_otherSM[0],
]

latex_mc = [
    Details.latex_ttbar,
    Details.latex_DYJetsToLL,
    
    Details.latex_otherSM,
]

colors_mc = [
    Details.color_ttbar,
    Details.color_DYJetsToLL,
    
    Details.color_otherSM,
]


def getInputFiles() :
    
    inputFiles_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
    #inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)
    inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix+"_withZpTreweighting", rootFileName)
    inputFiles_VH = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
    inputFiles_VV = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
    inputFiles_WG = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
    inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix, rootFileName)
    inputFiles_singleTop = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)
    inputFiles_TTX = Common.getRootFiles(Details.cutFlowDir_TTX[era], suffix, rootFileName)
    
    inputFiles_mc = [
        inputFiles_ttbar,
        inputFiles_DYJetsToLL,
        
        (
            inputFiles_WJetsToLNu +
            inputFiles_VH +
            inputFiles_VV +
            inputFiles_WG +
            inputFiles_singleTop +
            inputFiles_TTX
        ),
    ]
    return inputFiles_mc


#inputFile_sig = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_elMu_analysis/custom_all_analyzed.root", "READ")
#
#massPointFile = "stopPair_mc/output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"
#massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")
#
#l_selectMassPoint = [
#    [500, 1],
#    [500, 300],
#    [800, 1],
#    [800, 400],
#    #[1000, 1],
#]


def plot_DYSF(inputFiles_mc, legendTitle) :

    list_DYSF_info = []
    
    h1_yield_data = TH1F(label_data, label_data, nCR_merged, 0, nCR_merged)
    h1_yield_data.SetLineColorAlpha(1, 1)
    h1_yield_data.SetLineWidth(2)
    
    list_h1_yield_mc = []
    h1_yieldSum_mc = TH1F("MC", "MC", nCR_merged, 0, nCR_merged)
    
    
    for iMC in range(0, len(labels_mc)) :
        
        color = colors_mc[iMC]
        
        h1_temp = TH1F(labels_mc[iMC], labels_mc[iMC], nCR_merged, 0, nCR_merged)
        
        h1_temp.SetFillColorAlpha(color, 1)
        h1_temp.SetLineColorAlpha(0, 0)
        
        list_h1_yield_mc.append(h1_temp)
        
    
    
    DYSF_info = Common.getTTbarSF_multibin(
        cutFlowNameBase = cutFlowNameBase,
        inputFiles_data = inputFiles_data_DYSF,
        lumi_data = lumi_data,
        label_data = label_data,
        details_data = details_data_DYSF,
        inputFiles_mc = inputFiles_mc,
        crossSections_mc = crossSections_mc,
        labels_mc = labels_mc,
        details_mc = details_mc_DYSF,
        ll_regionNumber = ll_regionNumber_CR,
        nEventHistName = nEventHistName,
        expand = False,
        debug = debug,
    )
    
    print DYSF_info["dataYield"]
    print DYSF_info["mcYield"]
    
    
    #l_h1_sig = []
    #l_histDetail_sig = []
    #
    #for iMass in range(0, len(massPointInfo)) :
    #    
    #    stop1_m = massPointInfo[iMass, 0]
    #    neutralino1_m = massPointInfo[iMass, 1]
    #    xs_sig = massPointInfo[iMass, 3]
    #    xsUnc_sig = massPointInfo[iMass, 4]
    #    
    #    if ([int(stop1_m), int(neutralino1_m)] not in l_selectMassPoint) :
    #        
    #        continue
    #    
    #    h1_temp = TH1F("%d_%d" %(stop1_m, neutralino1_m), "%d_%d" %(stop1_m, neutralino1_m), nCR_merged, 0, nCR_merged)
    #    
    #    
    #    detailStr_sig = "tightTight_OS_genMatched_baselineTTCRB_%d_%d" %(stop1_m, neutralino1_m)
    #    
    #    yieldResult_nominal_sig = Common.getYields(
    #        l_rootFile = [inputFile_sig],
    #        l_xs = [xs_sig],
    #        suffix = "_elMu_analysis",
    #        systStr = "",
    #        histName_base = cutFlowNameBase,
    #        detailStr = detailStr_sig,
    #        nRegion = 18,
    #        yieldBinNumber = 6,
    #        ll_regionNumber = ll_regionNumber_CR,
    #        scale = lumi_data,
    #        debug = debug,
    #    )
    #    
    #    for iCR in range(0, nCR_merged) :
    #        
    #        h1_temp.SetBinContent(iCR+1, yieldResult_nominal_sig["yield"][iCR])
    #        h1_temp.SetBinError(iCR+1, yieldResult_nominal_sig["error"][iCR])
    #        h1_temp.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    #    
    #    l_h1_sig.append(h1_temp)
    #    
    #    histDetail_sig = Common.HistogramDetails()
    #    
    #    histDetail_sig.hist = l_h1_sig[-1]
    #    histDetail_sig.histLabel = "x=0.5, [%d, %d]" %(stop1_m, neutralino1_m)
    #    histDetail_sig.color = ROOT.kMagenta + 2*(len(l_h1_sig)-1)
    #    histDetail_sig.lineStyle = 2
    #    
    #    l_histDetail_sig.append(histDetail_sig)
    #
    
    for iCR in range(0, nCR_merged) :
        
        #cutFlowName = "reco/" + cutFlowNameBase + str(int(iCR+1))
        #cutFlowName = "reco/%s/%s%d_%s" %(details_data_DYSF, cutFlowNameBase, int(iCR+1), details_data_DYSF)
        #
        #DYSF_info = Common.getTTbarSF(
        #    cutFlowName,
        #    inputFiles_data_DYSF, lumi_data, label_data, "",
        #    inputFiles_mc, crossSections_mc, labels_mc, "",
        #    debug
        #)
        #
        #list_DYSF_info.append(DYSF_info)
        #
        #print (cutFlowNameBase + str(int(iCR+1))), \
        #    ", SF", ("%0.2f" % DYSF_info[0][0]), ("[%0.2f]" % DYSF_info[0][1]), \
        #    ", purity", ("%0.2f" % DYSF_info[1][0]), ("[%0.2f]" % DYSF_info[1][1])
        
        
        #dict_h1 = DYSF_info[-1]
        
        #h1_temp = dict_h1[label_data]
        
        #nBin = h1_temp.GetNbinsX()
        #print h1_temp.GetBinContent(nBin), h1_temp.GetBinError(nBin)
        
        h1_yield_data.SetBinContent(iCR+1, DYSF_info["dataYield"][iCR])
        h1_yield_data.SetBinError(iCR+1, DYSF_info["dataError"][iCR])
        h1_yield_data.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
        
        #print h1_yield_data.GetBinContent(iCR+1), h1_yield_data.GetBinError(iCR+1), h1_yield_data.Integral()
        
        for iMC in range(0, len(labels_mc)) :
            
            #h1_temp = dict_h1[labels_mc[iMC]]
            
            list_h1_yield_mc[iMC].SetBinContent(iCR+1, DYSF_info["mc"]["yield"][labels_mc[iMC]][iCR])
            list_h1_yield_mc[iMC].SetBinError(iCR+1, DYSF_info["mc"]["error"][labels_mc[iMC]][iCR])
            list_h1_yield_mc[iMC].GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    
    
    histDetail_data = Common.HistogramDetails()
    histDetail_data.hist = h1_yield_data
    histDetail_data.color = 1
    
    l_histDetail_mc = []
    
    for iMC in range(0, len(labels_mc)) :
        
        histDetail_mc = Common.HistogramDetails()
        
        histDetail_mc.hist = list_h1_yield_mc[iMC]
        histDetail_mc.histLabel = latex_mc[iMC]
        histDetail_mc.color = colors_mc[iMC]
        histDetail_mc.drawOption = histStyle_mc
        
        l_histDetail_mc.append(histDetail_mc)
    
    plotDir_mod = "%s/%s" %(plotDir, sampleLabel_DYSF)
    os.system("mkdir -p %s" %(plotDir_mod))
    
    outFileName = "%s/%s_yield_%s" %(plotDir_mod, cutFlowNameBase, sampleLabel_DYSF)
    
    Common.plot1D(
        l_histDetail_data = [histDetail_data],
        l_histDetail_mc = l_histDetail_mc,
        #l_histDetail_sig = l_histDetail_sig,
        #stackDrawOption = "nostack",
        stackDrawOption = "",
        ratioPlot = True,
        title = era,
        xTitle = "Bin number", yTitle = "Events",
        ratioYtitle = "Data / Prediction",
        #xMin = 0,
        #xMax = 0,
        yMin = 1,
        #yMax = 1e6,
        logY = True,
        gridX = True, gridY = True,
        #centerLabelsX = False, centerLabelsY = False,
        drawLegend = True,
        #legendTextSize = 0.045,
        legendTitle = legendTitle,
        legendPos = "UR",
        fixAlphanumericBinLabels = True,
        CMSextraText = Common.getCMSextraText(),
        lumiText = Common.getLumitext(era),
        outFileName = outFileName,
        #outFileName_suffix = "",
    )
    
    #canvas = TCanvas("canvas", "canvas")
    #canvas.SetCanvasSize(800, 800)
    #canvas.Divide(1, 2)
    #
    #(canvas.cd(1)).SetPad(-0.0175, 0.25, 1.08, 1)
    #(canvas.cd(2)).SetPad(-0.0175, 0.02, 1.08, 0.25)
    #
    #legend = TLegend(0.65, 0.63, 0.895, 0.895)
    ##stack = THStack("TT " + cutFlowNameBase, "TT " + cutFlowNameBase)
    #stack = THStack("stack", "t#bar{t} %s CR yields (%s)" %(sampleLabelLatex, era))
    #
    #canvas.cd(1)
    #
    #legend.AddEntry(h1_yield_data, "Data")
    #
    #
    #for iMC in range(0, len(labels_mc)) :
    #    
    #    h1_temp = list_h1_yield_mc[iMC]
    #    
    #    stack.Add(h1_temp, histStyle_mc)
    #    legend.AddEntry(h1_temp, labels_mc[iMC])
    #    
    #    h1_yieldSum_mc.Add(h1_temp)
    #
    #
    #(canvas.cd(1)).SetLogy()
    #(canvas.cd(1)).SetBottomMargin(0)
    #
    #stack.SetMinimum(1.0)
    #stack.Draw()
    #stack.GetXaxis().SetLabelSize(0)
    #
    #h1_yield_data.SetMinimum(1.0)
    #h1_yield_data.Draw("E same")
    #
    #legend.Draw()
    #
    #
    #canvas.cd(2)
    #
    #h1_dataMCratio = h1_yield_data.Clone()
    #h1_dataMCratio.Divide(h1_yieldSum_mc)
    #
    #h1_dataMCratio.SetStats(0)
    #h1_dataMCratio.SetMinimum(0)
    #h1_dataMCratio.SetMaximum(2)
    #
    #h1_dataMCratio.GetXaxis().SetLabelSize(0.125)
    #h1_dataMCratio.GetXaxis().SetTickLength(0.09)
    #h1_dataMCratio.GetXaxis().SetLabelSize(0.175)
    #
    #h1_dataMCratio.GetYaxis().SetNdivisions(-502)
    #h1_dataMCratio.GetYaxis().SetLabelSize(0.1)
    #
    #h1_dataMCratio.SetTitle("")
    #h1_dataMCratio.GetYaxis().SetTitle("Data / MC")
    #h1_dataMCratio.GetYaxis().SetTitleSize(0.1)
    #h1_dataMCratio.GetYaxis().SetTitleOffset(0.3)
    #h1_dataMCratio.GetYaxis().CenterTitle()
    #
    #(canvas.cd(2)).SetGridy()
    #(canvas.cd(2)).SetTopMargin(0)
    #
    #h1_dataMCratio.Draw("E")
    #
    ##canvas.SaveAs("TTSF_" + cutFlowNameBase + "_" + sampleLabel_DYSF + ".pdf")
    #canvas.SaveAs("%s/TTSF_%s_%s.pdf" %(plotDir, cutFlowNameBase, sampleLabel_DYSF))
    
    #return list_DYSF_info
    
    return DYSF_info


####################################################################################################


#####
suffix = "_muMu_analysis_DYCR"
inputFiles_data_DYSF = Common.getRootFiles(Details.cutFlowDir_muMu_data[era], suffix, rootFileName)
label_data = "Data" #Details.label_muMu_data[0]
sampleLabel_DYSF = "muMu"
sampleLabelLatex = "DY+jets CR (#mu#mu)"

DYSF_info = plot_DYSF(getInputFiles(), legendTitle = sampleLabelLatex)


sampleLabel = "tauTau"

suffix_data = "_tauTau_analysis_DYCR"
suffix_mc = "_tauTau_analysis_DYCR"
suffix_fakeEstimation = "_tauTau_fakeEstimation_DYCR"
#suffix_ttbarCR_elMu = "_elMu_analysis"
#suffix_ttbarCR_muMu = "_muMu_analysis"

rootFileName_data = "custom_all_analyzed.root"
rootFileName_mc = "custom_all_analyzed.root"
rootFileName_fakeEstimation = "custom_all_fakeEstimation_tauTau.root"
#rootFileName_ttbarCR = "custom_all_analyzed.root"

detailStr_data = "tightTight_OS_baselineDYCR"
detailStr_mc = "tightTight_OS_genMatched_baselineDYCR"
detailStr_fakeEstimation = "OS_baselineDYCR"
#detailStr_ttbarCR = "OS_baselineTTCRB"


details_otherSM = (
    Details.cutFlowDir_WJetsToLNu[era] +
    Details.cutFlowDir_VH[era] +
    Details.cutFlowDir_VV[era] +
    Details.cutFlowDir_WG[era] +
    Details.cutFlowDir_singleTop[era] +
    Details.cutFlowDir_TTX[era]
)


l_xs_otherSM = (
    Details.crossSection_WJetsToLNu[era] +
    Details.crossSection_VH[era] +
    Details.crossSection_VV[era] +
    Details.crossSection_WG[era] +
    Details.crossSection_singleTop[era] +
    Details.crossSection_TTX[era]
)


inputFiles_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data[era], suffix_data, rootFileName_data)

inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix_mc, rootFileName_mc)
#inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix_mc+"_withZpTreweighting", rootFileName_mc)
inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix_mc, rootFileName_mc)
inputFiles_otherSM = Common.getRootFiles(details_otherSM, suffix_mc, rootFileName_mc)
inputFiles_fake = Common.getRootFiles(Details.cutFlowDir_tauTau_fakeEstimation[era], suffix_fakeEstimation, rootFileName_fakeEstimation)

finalYieldBin = 6


yieldResult_data = Common.getYields(
    l_rootFile = inputFiles_data,
    l_xs = [],
    suffix = suffix_data,
    systStr = "",
    histName_base = cutFlowNameBase,
    detailStr = detailStr_data,
    nRegion = nCR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_CR,
    #scale = lumi_data,
    negToZero = True,
    debug = debug,
)

yieldResult_nominal_ttbar = Common.getYields(
    l_rootFile = inputFiles_ttbar,
    l_xs = Details.crossSection_ttbar[era],
    suffix = suffix_mc,
    systStr = "",
    histName_base = cutFlowNameBase,
    detailStr = detailStr_mc,
    nRegion = nCR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_CR,
    scale = lumi_data,
    negToZero = True,
    era = era,
    debug = debug,
)

yieldResult_nominal_DYJetsToLL = Common.getYields(
    l_rootFile = inputFiles_DYJetsToLL,
    l_xs = Details.crossSection_DYJetsToLL[era],
    suffix = suffix_mc,
    systStr = "",
    histName_base = cutFlowNameBase,
    detailStr = detailStr_mc,
    nRegion = nCR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_CR,
    scale = lumi_data,
    negToZero = True,
    era = era,
    debug = debug,
)

yieldResult_nominal_otherSM = Common.getYields(
    l_rootFile = inputFiles_otherSM,
    l_xs = l_xs_otherSM,
    suffix = suffix_mc,
    systStr = "",
    histName_base = cutFlowNameBase,
    detailStr = detailStr_mc,
    nRegion = nCR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_CR,
    scale = lumi_data,
    negToZero = True,
    era = era,
    debug = debug,
)

yieldResult_nominal_fake = Common.getYields(
    l_rootFile = inputFiles_fake,
    l_xs = [],
    suffix = suffix_mc,
    systStr = "",
    histName_base = cutFlowNameBase,
    detailStr = detailStr_fakeEstimation,
    nRegion = nCR,
    yieldBinNumber = finalYieldBin,
    ll_regionNumber = ll_regionNumber_CR,
    scale = 1.0,
    negToZero = True,
    debug = debug,
)



l_histDetail_data = []
l_histDetail = []

#
histDetail_temp = Common.HistogramDetails()
histDetail_temp.hist = Common.getYieldHistFromYieldInfo(yieldResult_data)
histDetail_temp.histLabel = "Data"
histDetail_temp.color = 1
l_histDetail_data.append(histDetail_temp)

#
histDetail_temp = Common.HistogramDetails()
histDetail_temp.hist = Common.getYieldHistFromYieldInfo(yieldResult_nominal_ttbar)
histDetail_temp.histLabel = "t#bar{t}"
histDetail_temp.color = Details.color_ttbar
l_histDetail.append(histDetail_temp)

#
histDetail_temp = Common.HistogramDetails()
h1_DYJetsToLL = Common.getYieldHistFromYieldInfo(yieldResult_nominal_DYJetsToLL)

# Apply the DYSF
if(applyDYSF) :
    
    for iCR in range(0, nCR_merged) :
        
        h1_DYJetsToLL.SetBinContent(
            iCR+1,
            h1_DYJetsToLL.GetBinContent(iCR+1) * DYSF_info["SF"][iCR]
        )

histDetail_temp.hist = h1_DYJetsToLL
histDetail_temp.histLabel = "DY+jets"
histDetail_temp.color = Details.color_DYJetsToLL
l_histDetail.append(histDetail_temp)

#
histDetail_temp = Common.HistogramDetails()
histDetail_temp.hist = Common.getYieldHistFromYieldInfo(yieldResult_nominal_otherSM)
histDetail_temp.histLabel = "Other SM"
histDetail_temp.color = Details.color_otherSM
l_histDetail.append(histDetail_temp)

#
histDetail_temp = Common.HistogramDetails()
histDetail_temp.hist = Common.getYieldHistFromYieldInfo(yieldResult_nominal_fake)
histDetail_temp.histLabel = "Fake"
histDetail_temp.color = Details.color_QCD
l_histDetail.append(histDetail_temp)


plotDir_mod = "%s/%s" %(plotDir, sampleLabel)
os.system("mkdir -p %s" %(plotDir_mod))

outFileName = "%s/%s_yield_%s%s" %(plotDir_mod, cutFlowNameBase, sampleLabel, "_noDYSF"*(not applyDYSF))

Common.plot1D(
    l_histDetail_data = l_histDetail_data,
    l_histDetail_mc = l_histDetail,
    #histDetail_mc_statErrPos = histDetail_mc_statErrPos,
    #histDetail_mc_statErrNeg = histDetail_mc_statErrNeg,
    #histDetail_mc_systErrPos = histDetail_mc_systErrPos,
    #histDetail_mc_systErrNeg = histDetail_mc_systErrNeg,
    #l_histDetail_sig = l_histDetail_sig,
    stackDrawOption = "",
    #drawMCerr = True,
    ratioPlot = True,
    #ratioStatErr = True,
    #ratioTotalErr = True,
    #title = "SR yields (%s)" %(era),
    xTitle = "Bin number", yTitle = "Events",
    ratioYtitle = "Data / Prediction",
    d_colorRatioGridY = {1: {"color": 2}},
    #xMin = plotQuantity.xMin, xMax = plotQuantity.xMax,
    yMin = 1e-3,
    yMax = 1e5,
    logY = True,
    ratioHist_ymax = 2,
    #fitRatio = "pol0",
    #fitRatioLineColor = 4,
    #plotFitResult = True,
    gridX = True, gridY = True,
    centerLabelsX = True,
    #nDivisionsX = [nSR, 1, 1],
    drawLegend = True,
    legendTextSize = 0.03,
    legendPos = "UR",
    fixAlphanumericBinLabels = True,
    CMSextraText = Common.getCMSextraText(),
    lumiText = Common.getLumitext(era),
    outFileName = outFileName,
    #outFileName_suffix = "",
)



#h1_purity = TH1F("purity", "purity", nCR_merged, 0, nCR_merged)
#h1_SF = TH1F("SF", "SF", nCR_merged, 0, nCR_merged)
#
#SF_list = []
#
#for iCR in range(0, nCR_merged) :
#    
#    SF_syst[iCR] -= DYSF_info["SF"][iCR]
#    print (cutFlowNameBase + str(int(iCR+1))), SF_syst[iCR]
#    SF_list.append(DYSF_info["SF"][iCR])
#    
#    h1_purity.SetBinContent(iCR+1, DYSF_info["purity"][iCR])
#    h1_purity.SetBinError(iCR+1, DYSF_info["purityErr"][iCR])
#    h1_purity.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
#    
#    h1_SF.SetBinContent(iCR+1, DYSF_info["SF"][iCR])
#    h1_SF.SetBinError(iCR+1, DYSF_info["SFerr"][iCR])
#    h1_SF.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
#
#print numpy.average(SF_list)
#
#print numpy.average(SF_syst)
#
#h1_purity.SetLineColor(4)
#h1_purity.SetMarkerColor(4)
#
#h1_SF.SetLineColor(4)
#h1_SF.SetMarkerColor(4)
#
#h1_purity.SetLineWidth(3)
#h1_SF.SetLineWidth(3)
#
#stack_purity.Add(h1_purity)
#stack_SF.Add(h1_SF)
#legend.AddEntry(h1_purity, sampleLabelLatex)
#
#
######
#h1_SF_diff.Add(h1_SF, -1)
#h1_SF_diff.SetMarkerColor(1)
#h1_SF_diff.SetLineColor(1)
#h1_SF_diff.SetLineWidth(3)
#stack_SF_diff.Add(h1_SF_diff)
#
#
###########  Plot ########## 
#
#tdrstyle.setTDRStyle()
#
#canvas = TCanvas("canvas", "canvas")
##canvas.SetCanvasSize(800, 800)
#
#canvas.Divide(1, 3)
#
#canvas.SetLeftMargin(0.1)
#
#canvas.cd(1).SetPad(0, 0.66, 1, 0.96);
#canvas.cd(1).SetLeftMargin(0.1)
#
#canvas.cd(2).SetPad(0, 0.33, 1, 0.66);
#canvas.cd(2).SetLeftMargin(0.1)
#
#canvas.cd(3).SetPad(0, 0.0, 1, 0.33);
#canvas.cd(3).SetLeftMargin(0.1)
#
#
#canvas.cd(1)
#stack_purity.SetMinimum(0)
#stack_purity.SetMaximum(2)
#stack_purity.Draw("nostack")
#stack_purity.GetXaxis().SetLabelSize(0.15)
#stack_purity.GetYaxis().SetNdivisions(-504)
#stack_purity.GetYaxis().SetLabelSize(0.1)
#stack_purity.GetYaxis().SetTitle("t#bar{t} purity")
#stack_purity.GetYaxis().SetTitleSize(0.11)
#stack_purity.GetYaxis().SetTitleOffset(0.35*stack_purity.GetYaxis().GetTitleOffset())
#stack_purity.GetYaxis().CenterTitle(True)
#legend.Draw()
#(canvas.cd(1)).SetGridy()
#
#
#canvas.cd(2)
#stack_SF.SetMinimum(0)
#stack_SF.SetMaximum(2)
#stack_SF.Draw("nostack")
#stack_SF.GetXaxis().SetLabelSize(0.15)
#stack_SF.GetYaxis().SetNdivisions(-504)
#stack_SF.GetYaxis().SetLabelSize(0.11)
#stack_SF.GetYaxis().SetTitle("Scale-factor (SF)")
#stack_SF.GetYaxis().SetTitleSize(0.1)
#stack_SF.GetYaxis().SetTitleOffset(0.35*stack_SF.GetYaxis().GetTitleOffset())
#stack_SF.GetYaxis().CenterTitle(True)
#(canvas.cd(2)).SetGridy()
#
#canvas.cd(3)
#stack_SF_diff.SetMinimum(-1)
#stack_SF_diff.SetMaximum(1)
#stack_SF_diff.Draw("nostack")
#stack_SF_diff.GetXaxis().SetLabelSize(0.15)
#stack_SF_diff.GetYaxis().SetNdivisions(-504)
#stack_SF_diff.GetYaxis().SetLabelSize(0.11)
#stack_SF_diff.GetYaxis().SetTitle("SF^{e#mu} - SF^{#mu#mu}")
#stack_SF_diff.GetYaxis().SetTitleSize(0.1)
#stack_SF_diff.GetYaxis().SetTitleOffset(0.35*stack_SF_diff.GetYaxis().GetTitleOffset())
#stack_SF_diff.GetYaxis().CenterTitle(True)
#(canvas.cd(3)).SetGridy()
#
## CMS label
#CMS_lumi.CMS_lumi(pad = canvas, iPeriod = 0, iPosX = 0, CMSextraText = Common.getCMSextraText(), lumiText = Common.getLumitext(era))
#
#canvas.SaveAs("%s/TTpuritySF_%s.pdf" %(plotDir, cutFlowNameBase))

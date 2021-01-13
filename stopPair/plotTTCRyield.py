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


noPrelim = True
noPrelimStr = "_noPrelim"*(noPrelim)


ROOT.gStyle.SetTitleH(0.085)


l_era = ["2016"]
#l_era = ["2017"]
#l_era = ["2016", "2017"]

eraStr = "+".join(l_era)

rootFileName = "custom_all_analyzed.root"

#suffix = "_elMu_analysis"
#inputFiles_data = Common.getRootFiles(Details.cutFlowDir_elMu_data, suffix, rootFileName)
#label_data = Details.label_elMu_data[0]
#sampleLabel = "elMu"

suffix = ""
inputFiles_data = 0
label_data = ""
sampleLabel = ""
sampleLabelLatex = ""


#lumi_data = 35.9e3
d_lumi_data = Details.luminosity_data


plotDir = "plots/TTCR_yields/%s%s" %(eraStr, noPrelimStr)
#plotDir = "plots/TTCR_yields/%s_merged" %(eraStr)
#plotDir = "plots/TTCR_yields/%s_withSig" %(eraStr)
os.system("mkdir -p %s" %(plotDir))



#nCR = 6
#cutFlowNameBase = "CRA"

nCR = 18
cutFlowNameBase = "CRB"

details_data = "OS_baselineTTCRB"
details_mc = "OS_baselineTTCRB"

debug = False

histStyle_data = "P E1"
histStyle_mc = "hist"


ll_regionNumber_CR = [
    [1], [2], [3],
    [4, 5], [6],
    [7], [8], [9],
    [10, 11], [12],
    [13], [14], [15],
    [16, 17], [18],
    #[16, 17, 18],
]

nCR_merged = len(ll_regionNumber_CR)


inputFiles_mc = []

d_crossSections_mc = {}

for era in l_era :
    
    d_crossSections_mc[era] = [
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
    Details.label_ttbar[0],
    Details.label_DYJetsToLL[0],
    
    Details.label_otherSM[0],
    
    #Details.label_WJetsToLNu[0],
    #Details.label_VH[0],
    #Details.label_VV[0],
    #Details.label_WG[0],
    #Details.label_singleTop[0],
]

latex_mc = [
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


def getInputFiles(era) :
    
    inputFiles_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
    inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)
    inputFiles_VH = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
    inputFiles_VV = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
    inputFiles_WG = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
    inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix, rootFileName)
    inputFiles_singleTop = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)
    
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


def plot_ttbar_SF(inputFiles_mc, legendTitle, era) :

    list_ttbar_SF_info = []
    
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
        
    
    
    ttbar_SF_info = Common.getTTbarSF_multibin(
        cutFlowNameBase = cutFlowNameBase,
        inputFiles_data = inputFiles_data,
        lumi_data = d_lumi_data[era],
        label_data = label_data,
        details_data = details_data,
        inputFiles_mc = inputFiles_mc,
        crossSections_mc = d_crossSections_mc[era],
        labels_mc = labels_mc,
        details_mc = details_mc,
        ll_regionNumber = ll_regionNumber_CR,
        expand = False,
        debug = debug,
    )
    
    print ttbar_SF_info["dataYield"]
    print ttbar_SF_info["mcYield"]
    
    
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
        #cutFlowName = "reco/%s/%s%d_%s" %(details_data, cutFlowNameBase, int(iCR+1), details_data)
        #
        #ttbar_SF_info = Common.getTTbarSF(
        #    cutFlowName,
        #    inputFiles_data, lumi_data, label_data, "",
        #    inputFiles_mc, d_crossSections_mc[era], labels_mc, "",
        #    debug
        #)
        #
        #list_ttbar_SF_info.append(ttbar_SF_info)
        #
        #print (cutFlowNameBase + str(int(iCR+1))), \
        #    ", SF", ("%0.2f" % ttbar_SF_info[0][0]), ("[%0.2f]" % ttbar_SF_info[0][1]), \
        #    ", purity", ("%0.2f" % ttbar_SF_info[1][0]), ("[%0.2f]" % ttbar_SF_info[1][1])
        
        
        #dict_h1 = ttbar_SF_info[-1]
        
        #h1_temp = dict_h1[label_data]
        
        #nBin = h1_temp.GetNbinsX()
        #print h1_temp.GetBinContent(nBin), h1_temp.GetBinError(nBin)
        
        h1_yield_data.SetBinContent(iCR+1, ttbar_SF_info["dataYield"][iCR])
        h1_yield_data.SetBinError(iCR+1, ttbar_SF_info["dataError"][iCR])
        h1_yield_data.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
        
        #print h1_yield_data.GetBinContent(iCR+1), h1_yield_data.GetBinError(iCR+1), h1_yield_data.Integral()
        
        for iMC in range(0, len(labels_mc)) :
            
            #h1_temp = dict_h1[labels_mc[iMC]]
            
            list_h1_yield_mc[iMC].SetBinContent(iCR+1, ttbar_SF_info["mc"]["yield"][labels_mc[iMC]][iCR])
            list_h1_yield_mc[iMC].SetBinError(iCR+1, ttbar_SF_info["mc"]["error"][labels_mc[iMC]][iCR])
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
    
    outFileName = "%s/TTSF_%s_%s" %(plotDir, cutFlowNameBase, sampleLabel)
    
    if (len(l_era) == 1) :
        
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
            legendPos = "LL",
            fixAlphanumericBinLabels = True,
            CMSextraText = Common.getCMSextraText(isPrelim = (not noPrelim)),
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
    ##canvas.SaveAs("TTSF_" + cutFlowNameBase + "_" + sampleLabel + ".pdf")
    #canvas.SaveAs("%s/TTSF_%s_%s.pdf" %(plotDir, cutFlowNameBase, sampleLabel))
    
    #return list_ttbar_SF_info
    
    return ttbar_SF_info


####################################################################################################

#stack_purity = THStack("TT purity " + cutFlowNameBase, "TT purity " + cutFlowNameBase)
stack_purity = THStack("stack_purity", "t#bar{t} CR purity (%s)" %(era))
#stack_SF = THStack("TT SF " + cutFlowNameBase, "TT SF " + cutFlowNameBase)
stack_SF = THStack("stack_SF", "t#bar{t} SF (%s)" %(era))
#stack_SF_diff = THStack("SF diff" + cutFlowNameBase, "SF^{#mu#mu} - SF^{e#mu} " + cutFlowNameBase)
stack_SF_diff = THStack("stack_SF_diff", "t#bar{t} SF^{#mu#mu} - SF^{e#mu} (%s)" %(era))

legend = TLegend(0.55, 0.72, 0.95, 0.895)
#legend.SetFillStyle(0)
legend.SetBorderSize(1)


h1_purity_elMu = TH1F("purity", "purity", nCR_merged, 0, nCR_merged)
h1_purity_muMu = TH1F("purity", "purity", nCR_merged, 0, nCR_merged)

h1_SF_elMu = TH1F("SF", "SF", nCR_merged, 0, nCR_merged)
h1_SF_muMu = TH1F("SF", "SF", nCR_merged, 0, nCR_merged)

h1_SF_diff = TH1F("SF_diff", "SF_diff", nCR_merged, 0, nCR_merged)


for iCR in range(0, nCR_merged) :
    
    
    h1_purity_elMu.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    h1_purity_muMu.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    
    h1_SF_elMu.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    h1_SF_muMu.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    
    h1_SF_diff.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))


lumiSum = 0

for iEra in range(0, len(l_era)) :
    
    era = l_era[iEra]
    
    lumiSum += d_lumi_data[era]
    
    ##### elMu #####
    suffix = "_elMu_analysis"
    inputFiles_data = Common.getRootFiles(Details.cutFlowDir_elMu_data[era], suffix, rootFileName)
    label_data = "Data"#Details.label_elMu_data[0]
    sampleLabel = "elMu"
    sampleLabelLatex_elMu = "e#mu CR"
    
    ttbar_SF_info = plot_ttbar_SF(getInputFiles(era), legendTitle = "e#mu CR", era = era)
    
    h1_purity_elMu_temp = h1_purity_elMu.Clone()
    h1_SF_elMu_temp = h1_SF_elMu.Clone()
    
    SF_syst = []
    SF_list = []
    
    for iCR in range(0, nCR_merged) :
        
        SF_syst.append(ttbar_SF_info["SF"][iCR])
        SF_list.append(ttbar_SF_info["SF"][iCR])
        
        h1_purity_elMu_temp.SetBinContent(iCR+1, ttbar_SF_info["purity"][iCR])
        h1_purity_elMu_temp.SetBinError(iCR+1, ttbar_SF_info["purityErr"][iCR])
        h1_purity_elMu_temp.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
        
        h1_SF_elMu_temp.SetBinContent(iCR+1, ttbar_SF_info["SF"][iCR])
        h1_SF_elMu_temp.SetBinError(iCR+1, ttbar_SF_info["SFerr"][iCR])
        h1_SF_elMu_temp.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    
    print numpy.average(SF_list)
    
    
    ##### muMu #####
    suffix = "_muMu_analysis"
    inputFiles_data = Common.getRootFiles(Details.cutFlowDir_muMu_data[era], suffix, rootFileName)
    label_data = "Data" #Details.label_muMu_data[0]
    sampleLabel = "muMu"
    sampleLabelLatex_muMu = "#mu#mu CR"
    
    ttbar_SF_info = plot_ttbar_SF(getInputFiles(era), legendTitle = "#mu#mu CR", era = era)
    
    h1_purity_muMu_temp = h1_purity_muMu.Clone()
    h1_SF_muMu_temp = h1_SF_muMu.Clone()
    
    SF_list = []
    
    for iCR in range(0, nCR_merged) :
        
        SF_syst[iCR] -= ttbar_SF_info["SF"][iCR]
        print (cutFlowNameBase + str(int(iCR+1))), SF_syst[iCR]
        SF_list.append(ttbar_SF_info["SF"][iCR])
        
        h1_purity_muMu_temp.SetBinContent(iCR+1, ttbar_SF_info["purity"][iCR])
        h1_purity_muMu_temp.SetBinError(iCR+1, ttbar_SF_info["purityErr"][iCR])
        h1_purity_muMu_temp.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
        
        h1_SF_muMu_temp.SetBinContent(iCR+1, ttbar_SF_info["SF"][iCR])
        h1_SF_muMu_temp.SetBinError(iCR+1, ttbar_SF_info["SFerr"][iCR])
        h1_SF_muMu_temp.GetXaxis().SetBinLabel(iCR+1, str(int(iCR+1)))
    
    print numpy.average(SF_list)
    
    print numpy.average(SF_syst)
    
    
    # Difference
    h1_SF_diff_temp = h1_SF_elMu_temp.Clone()
    h1_SF_diff_temp.Add(h1_SF_muMu_temp, -1)
    
    # Add up (lumi weighted average)
    h1_purity_elMu.Add(h1_purity_elMu_temp, d_lumi_data[era])
    h1_SF_elMu.Add(h1_SF_elMu_temp, d_lumi_data[era])
    
    h1_purity_muMu.Add(h1_purity_muMu_temp, d_lumi_data[era])
    h1_SF_muMu.Add(h1_SF_muMu_temp, d_lumi_data[era])
    
    h1_SF_diff.Add(h1_SF_diff_temp, d_lumi_data[era])


# Divide (lumi weighted average)
h1_purity_elMu.Scale(1.0 / lumiSum)
h1_purity_muMu.Scale(1.0 / lumiSum)

h1_SF_elMu.Scale(1.0 / lumiSum)
h1_SF_muMu.Scale(1.0 / lumiSum)

h1_SF_diff.Scale(1.0 / lumiSum)


# Set color, line, etc.
h1_purity_elMu.SetLineColor(2)
h1_purity_elMu.SetLineWidth(3)
h1_purity_elMu.SetMarkerStyle(20)
h1_purity_elMu.SetMarkerColor(2)

h1_purity_muMu.SetLineColor(4)
h1_purity_muMu.SetLineWidth(3)
h1_purity_muMu.SetMarkerStyle(20)
h1_purity_muMu.SetMarkerColor(4)

h1_SF_elMu.SetLineColor(2)
h1_SF_elMu.SetLineWidth(3)
h1_SF_elMu.SetMarkerStyle(20)
h1_SF_elMu.SetMarkerColor(2)

h1_SF_muMu.SetLineColor(4)
h1_SF_muMu.SetLineWidth(3)
h1_SF_muMu.SetMarkerStyle(20)
h1_SF_muMu.SetMarkerColor(4)

h1_SF_diff.SetLineColor(1)
h1_SF_diff.SetLineWidth(3)
h1_SF_diff.SetMarkerStyle(20)
h1_SF_diff.SetMarkerColor(1)


# Add to stack, etc.
sampleLabelLatex_elMu = "e#mu CR"
sampleLabelLatex_muMu = "#mu#mu CR"

stack_purity.Add(h1_purity_elMu, histStyle_data)
stack_SF.Add(h1_SF_elMu, histStyle_data)
legend.AddEntry(h1_purity_elMu, sampleLabelLatex_elMu)

stack_purity.Add(h1_purity_muMu, histStyle_data)
stack_SF.Add(h1_SF_muMu, histStyle_data)
legend.AddEntry(h1_purity_muMu, sampleLabelLatex_muMu)

stack_SF_diff.Add(h1_SF_diff, histStyle_data)


##########  Plot ########## 

tdrstyle.setTDRStyle()

canvas = TCanvas("canvas", "canvas")
#canvas.SetCanvasSize(800, 800)

canvas.Divide(1, 3)

canvas.SetLeftMargin(0.12)
canvas.SetBottomMargin(0.25)

canvas.cd(1).SetPad(0, 0.66, 1, 0.96);
canvas.cd(1).SetLeftMargin(0.12)

canvas.cd(2).SetPad(0, 0.33, 1, 0.66);
canvas.cd(2).SetLeftMargin(0.12)

canvas.cd(3).SetPad(0, 0, 1, 0.33);
canvas.cd(3).SetLeftMargin(0.12)
canvas.cd(3).SetBottomMargin(0.25)


canvas.cd(1)
stack_purity.SetMinimum(0.5)
stack_purity.SetMaximum(1.5)
stack_purity.Draw("nostack")
stack_purity.GetXaxis().SetLabelSize(0.175)
stack_purity.GetYaxis().SetNdivisions(-504)
stack_purity.GetYaxis().SetLabelSize(0.11)
stack_purity.GetYaxis().SetTitle("t#bar{t} purity")
stack_purity.GetYaxis().SetTitleSize(0.13)
stack_purity.GetYaxis().SetTitleOffset(0.385*stack_purity.GetYaxis().GetTitleOffset())
stack_purity.GetYaxis().CenterTitle(True)
legend.SetNColumns(2)
legend.Draw()
(canvas.cd(1)).SetGridy()


canvas.cd(2)
stack_SF.SetMinimum(0)
stack_SF.SetMaximum(2)
stack_SF.Draw("nostack")
stack_SF.GetXaxis().SetLabelSize(0.175)
stack_SF.GetYaxis().SetNdivisions(-504)
stack_SF.GetYaxis().SetLabelSize(0.11)
stack_SF.GetYaxis().SetTitle("Scale factor (SF)")
stack_SF.GetYaxis().SetTitleSize(0.125)
stack_SF.GetYaxis().SetTitleOffset(0.375*stack_SF.GetYaxis().GetTitleOffset())
stack_SF.GetYaxis().CenterTitle(True)
(canvas.cd(2)).SetGridy()

canvas.cd(3)
stack_SF_diff.SetMinimum(-1)
stack_SF_diff.SetMaximum(1)
stack_SF_diff.Draw("nostack")
stack_SF_diff.GetXaxis().SetLabelSize(0.175)
stack_SF_diff.GetXaxis().SetTitle("t#bar{t} CR bin number")
stack_SF_diff.GetXaxis().SetTitleSize(0.125)
stack_SF_diff.GetXaxis().CenterTitle(True)
stack_SF_diff.GetYaxis().SetNdivisions(-504)
stack_SF_diff.GetYaxis().SetLabelSize(0.11)
stack_SF_diff.GetYaxis().SetTitle("SF^{e#mu} - SF^{#mu#mu}")
stack_SF_diff.GetYaxis().SetTitleSize(0.125)
stack_SF_diff.GetYaxis().SetTitleOffset(0.375*stack_SF_diff.GetYaxis().GetTitleOffset())
stack_SF_diff.GetYaxis().CenterTitle(True)
(canvas.cd(3)).SetGridy()


# CMS label
CMS_lumi.CMS_lumi(pad = canvas, iPeriod = 0, iPosX = 0, CMSextraText = Common.getCMSextraText(isPrelim = (not noPrelim)), lumiText = Common.getLumitext(eraStr))

canvas.SaveAs("%s/TTpuritySF_%s.pdf" %(plotDir, cutFlowNameBase))

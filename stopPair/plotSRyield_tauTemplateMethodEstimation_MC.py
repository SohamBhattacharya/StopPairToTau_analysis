import numpy
import os
import sys

import ROOT
from ROOT import TCanvas
from ROOT import TFile
from ROOT import THStack
from ROOT import TH1F
from ROOT import TLegend
from ROOT import TStyle

import Array2LatexTable
import Common
import Details


# Select options
plotYield = True
printTable = True

histSuffix = "tightTight_OS"
histSuffix_templateMethod = "OS_baselineSRB"

suffix = "_tauTau_analysis"
suffix_templateMethod = "_tauTau_tauTemplateMethodEstimation"

rootFileName = "custom_all_analyzed.root"
rootFileName_templateMethod = "custom_all_tauTemplateMethodEstimation.root"

#inputFiles_data = Common.getRootFiles(Details.cutFlowDir_tauTau_data, suffix, rootFileName)
#inputFiles_templateMethod = Common.getRootFiles(Details.cutFlowDir_muMu_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)

inputFiles_WJetsToLNu = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu, suffix, rootFileName)
inputFiles_DYJetsToLL = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL, suffix, rootFileName)
inputFiles_VH = Common.getRootFiles(Details.cutFlowDir_VH, suffix, rootFileName)
inputFiles_VV = Common.getRootFiles(Details.cutFlowDir_VV, suffix, rootFileName)
inputFiles_WG = Common.getRootFiles(Details.cutFlowDir_WG, suffix, rootFileName)
inputFiles_ttbar = Common.getRootFiles(Details.cutFlowDir_ttbar, suffix, rootFileName)
inputFiles_singleTop = Common.getRootFiles(Details.cutFlowDir_singleTop, suffix, rootFileName)

inputFiles_WJetsToLNu_templateMethod = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)
inputFiles_DYJetsToLL_templateMethod = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)
inputFiles_VH_templateMethod = Common.getRootFiles(Details.cutFlowDir_VH_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)
inputFiles_VV_templateMethod = Common.getRootFiles(Details.cutFlowDir_VV_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)
inputFiles_WG_templateMethod = Common.getRootFiles(Details.cutFlowDir_WG_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)
inputFiles_ttbar_templateMethod = Common.getRootFiles(Details.cutFlowDir_ttbar_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)
inputFiles_singleTop_templateMethod = Common.getRootFiles(Details.cutFlowDir_singleTop_tauTemplateMethodEstimation, suffix_templateMethod, rootFileName_templateMethod)


lumi_data = 8.347e3
luminosity_templateMethod = 8.347e3


plotDir = "plots/SR_yields"
os.system("mkdir -p %s" %(plotDir))


cutFlowDir = "cutFlowTables_tauTemplateMethodEstimation_allMC"
os.system("mkdir -p cutFlowTables_tauTemplateMethodEstimation_allMC")


#nSR = 6
#cutFlowNameBase = "SRA"
#cutFlowNameBase_TTCR = "CRA"

nSR = 18
cutFlowNameBase = "SRB"
cutFlowNameBase_TTCR = "CRB"

debug = True

histStyle_data = "E"
histStyle_mc = "hist"
histStyle_stopPair = "hist"


inputFiles_mc = [
    inputFiles_WJetsToLNu,
    inputFiles_DYJetsToLL,
    inputFiles_VH,
    inputFiles_VV,
    inputFiles_WG,
    inputFiles_ttbar,
    inputFiles_singleTop,
]

inputFiles_templateMethod = [
    inputFiles_WJetsToLNu_templateMethod,
    inputFiles_DYJetsToLL_templateMethod,
    inputFiles_VH_templateMethod,
    inputFiles_VV_templateMethod,
    inputFiles_WG_templateMethod,
    inputFiles_ttbar_templateMethod,
    inputFiles_singleTop_templateMethod,
]


crossSections_mc = [
    Details.crossSection_WJetsToLNu,
    Details.crossSection_DYJetsToLL,
    Details.crossSection_VH,
    Details.crossSection_VV,
    Details.crossSection_WG,
    Details.crossSection_ttbar,
    Details.crossSection_singleTop,
]

labels_mc = [
    Details.label_WJetsToLNu[0],
    Details.label_DYJetsToLL[0],
    Details.label_VH[0],
    Details.label_VV[0],
    Details.label_WG[0],
    Details.label_ttbar[0],
    Details.label_singleTop[0],
    #Details.label_QCD[0],
]


# Signal
inputFiles_stopPair = [
    Common.getRootFiles(
        ["stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_400_100"],
        suffix, rootFileName
    ),
    
    Common.getRootFiles(
        ["stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_800_400"],
        suffix, rootFileName
    ),
    
    Common.getRootFiles(
        ["stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1100_100"],
        suffix, rootFileName
    ),
]

crossSections_stopPair = [
    [1.83537],
    [0.0283338],
    [0.00307413],
]

labels_stopPair = [
    "0.25, [400, 100]",
    "0.25, [800, 400]",
    "0.25, [1100, 100]",
]



#h1_yield_data = TH1F(Details.label_tauTau_data[0], Details.label_tauTau_data[0], nSR, 0, nSR)
#h1_yield_data.SetLineColorAlpha(1, 1)
#h1_yield_data.SetLineWidth(3)

h1_yield_data = TH1F("#tau-template method", "#tau-template method", nSR, 0, nSR)
h1_yield_data.SetLineColorAlpha(1, 1)
h1_yield_data.SetLineWidth(3)


# MC histograms
list_h1_yield_mc = []
h1_yieldSum_mc = TH1F("MC", "MC", nSR, 0, nSR)
h1_yieldSum_mc.Sumw2()

for iMC in range(0, len(labels_mc)) :
    
    color = iMC+2
    
    h1_temp = TH1F(labels_mc[iMC], labels_mc[iMC], nSR, 0, nSR)
    
    h1_temp.SetFillColorAlpha(color, 0.75)
    h1_temp.SetLineColorAlpha(0, 0)
    
    list_h1_yield_mc.append(h1_temp)


# Signal histograms
list_h1_yield_stopPair = []

for iSig in range(0, len(labels_stopPair)) :
    
    color = ROOT.kMagenta + 2*iSig
    
    h1_temp = TH1F(labels_stopPair[iSig], labels_stopPair[iSig], nSR, 0, nSR)
    
    h1_temp.SetLineColor(color)
    h1_temp.SetLineWidth(3)
    h1_temp.SetLineStyle(2)
    
    list_h1_yield_stopPair.append(h1_temp)


# Yield table
table_yield_allSR_str = []
table_yield_data_allSR = numpy.zeros((nSR, 1))
table_yield_data_allSR = numpy.zeros((nSR, len(labels_mc)))
table_yield_stopPair_allSR = numpy.zeros((nSR, len(labels_stopPair)))

columnLabels = []


# Get histograms
for iSR in range(0, nSR) :
    
    cutFlowName = "reco/" + cutFlowNameBase + str(int(iSR+1))
    
    columnLabels = []
    
    # Template
    
    #h1_cutFlow_templateMethod = Common.getCombinedCutFlow(
    #    inputFiles = inputFiles_data,
    #    cutFlowName = cutFlowName,
    #    details = histSuffix,
    #    debug = debug
    #)
    
    h1_cutFlow_templateMethod = 0
    
    for iMC in range(0, len(inputFiles_templateMethod)) :
        
        h1_temp = Common.getCombinedCutFlow(
            inputFiles = inputFiles_templateMethod[iMC],
            cutFlowName = cutFlowName,
            details = histSuffix_templateMethod,
            debug = debug,
            crossSections = crossSections_mc[iMC],
            lumi_data = lumi_data,
            option = "MC"
        )
        
        if (iMC == 0) :
            
            h1_cutFlow_templateMethod = h1_temp.Clone()
        
        else :
            
            h1_cutFlow_templateMethod.Add(h1_temp.Clone())
    
    arr_binContent = Common.histToArray(h1_cutFlow_templateMethod, "binContent")
    binContent = arr_binContent[0][-1]
    
    arr_binError = Common.histToArray(h1_cutFlow_templateMethod, "binError")
    binError = arr_binError[0][-1]
    
    # Yield table for each SR
    table_yield_data = numpy.zeros((len(arr_binContent[0]), 1))
    table_yield_mc = numpy.zeros((len(arr_binContent[0]), len(labels_mc)))
    table_yield_stopPair = numpy.zeros((len(arr_binContent[0]), len(labels_stopPair)))
    
    # Fill histogram
    h1_yield_data.SetBinContent(iSR+1, binContent)
    h1_yield_data.SetBinError(iSR+1, binError)
    h1_yield_data.GetXaxis().SetBinLabel(iSR+1, str(int(iSR+1)))
    
    # Fill table
    table_yield_data[:, 0] = arr_binContent[0]
    
    
    # MC
    for iMC in range(0, len(labels_mc)) :
        
        if (labels_mc[iMC] == Details.label_QCD[0]) :
            
            h1_temp = Common.getCombinedCutFlow_QCD(
                cutFlowName,
                "tightTight_OS", "looseLoose_OS",
                "tightTight_SS", "looseLoose_SS",
                inputFiles_data, lumi_data,
                inputFiles_mc, crossSections_mc,
                debug
            )
        
        else :
            
            h1_temp = Common.getCombinedCutFlow(
                inputFiles = inputFiles_mc[iMC],
                cutFlowName = cutFlowName,
                details = histSuffix,
                debug = debug,
                crossSections = crossSections_mc[iMC],
                lumi_data = lumi_data,
                option = "MC"
            )
        
        arr_binContent = Common.histToArray(h1_temp, "binContent")
        binContent = arr_binContent[0][-1]
        
        arr_binError = Common.histToArray(h1_temp, "binError")
        binError = arr_binError[0][-1]
        
        # Fill histogram
        list_h1_yield_mc[iMC].SetBinContent(iSR+1, binContent)
        list_h1_yield_mc[iMC].SetBinError(iSR+1, binError)
        
        # Fill table
        table_yield_mc[:, iMC] = arr_binContent[0]
    
    
    # Signal
    for iSig in range(0, len(labels_stopPair)) :
        
        h1_temp = Common.getCombinedCutFlow(
            inputFiles = inputFiles_stopPair[iSig],
            cutFlowName = cutFlowName,
            details = histSuffix,
            debug = debug,
            crossSections = crossSections_stopPair[iSig],
            lumi_data = lumi_data,
            option = "MC"
        )
        
        arr_binContent = Common.histToArray(h1_temp, "binContent")
        binContent = arr_binContent[0][-1]
        
        arr_binError = Common.histToArray(h1_temp, "binError")
        binError = arr_binError[0][-1]
        
        #print "sig", iSig, ", SR", iSR+1, ", yield", ("%0.4f" %binContent), ", error%", ("%0.2f" %(binError/binContent*100))
        
        # Fill histogram
        list_h1_yield_stopPair[iSig].SetBinContent(iSR+1, binContent)
        list_h1_yield_stopPair[iSig].SetBinError(iSR+1, binContent)
        
        # Fill table
        print "**********"
        print "********** Warning: Change code when the nJet selection is removed from signal **********"
        print "**********"
        #table_yield_stopPair[:, iSig] = arr_binContent[0][:-1]
        table_yield_stopPair[:, iSig] = numpy.append(arr_binContent[0][: -2], [arr_binContent[0][-1]])
    
    
    if (printTable) :
        
        with numpy.errstate(divide = "ignore", invalid = "ignore") :
        
            table_yield = numpy.empty((table_yield_data.shape[0], 0))
            
            #print cutFlowNameBase + str(int(iSR+1)), "Data", table_yield_data
            #print cutFlowNameBase + str(int(iSR+1)), "All MC", numpy.sum(table_yield_mc, axis = 1)
            #print cutFlowNameBase + str(int(iSR+1)), "ttbar", table_yield_mc[:, labels_mc.index(Details.label_ttbar[0])]
            #print cutFlowNameBase + str(int(iSR+1)), "Signal", table_yield_stopPair
            
            
            # Data
            table_yield = numpy.append(table_yield, table_yield_data, axis = 1)
            #print cutFlowNameBase + str(int(iSR+1)), "Added data",  table_yield
            columnLabels += ["#tau-template method"]
            
            
            # MC
            table_yield = numpy.append(table_yield, table_yield_mc, axis = 1)
            #print cutFlowNameBase + str(int(iSR+1)), "Added MC", table_yield
            columnLabels += labels_mc
            
            
            # all MC
            allMC = numpy.sum(table_yield_mc, axis = 1)
            #print cutFlowNameBase + str(int(iSR+1)), "allMC", allMC
            table_yield = numpy.concatenate(
                (table_yield,
                    numpy.transpose([allMC])
                ),
                axis = 1
            )
            #print cutFlowNameBase + str(int(iSR+1)), "Added ttbar/MC", table_yield
            columnLabels += ["all MC"]
            
            # ttbar / all MC
            ttbarAllMCratio = table_yield_mc[:, labels_mc.index(Details.label_ttbar[0])] / numpy.sum(table_yield_mc, axis = 1)
            #print cutFlowNameBase + str(int(iSR+1)), "ttbar/MC", ttbarAllMCratio
            table_yield = numpy.concatenate(
                (table_yield,
                    numpy.transpose([ttbarAllMCratio])
                ),
                axis = 1
            )
            #print cutFlowNameBase + str(int(iSR+1)), "Added ttbar/MC", table_yield
            columnLabels += ["TT / all MC"]
            
            
            ## Data / all MC
            #dataMCratio = numpy.sum(table_yield_data, axis = 1) / numpy.sum(table_yield_mc, axis = 1)
            ##print cutFlowNameBase + str(int(iSR+1)), "Data/MC", dataMCratio
            #table_yield = numpy.concatenate(
            #    (table_yield,
            #        numpy.transpose([dataMCratio])
            #    ),
            #    axis = 1
            #)
            ##print cutFlowNameBase + str(int(iSR+1)), "Added data/MC", table_yield
            #columnLabels += ["Data / all MC"]
            
            
            # Signal
            table_yield = numpy.append(table_yield, table_yield_stopPair, axis = 1)
            #print cutFlowNameBase + str(int(iSR+1)), "Added signal",  table_yield
            columnLabels += labels_stopPair
            
            
            # Replace nan and inf
            table_yield[numpy.where(numpy.isnan(table_yield))] = 0
            table_yield[numpy.where(numpy.isinf(table_yield))] = 0
            #print cutFlowNameBase + str(int(iSR+1)), table_yield
            
            
            # Stringify and table
            table_yield_str = Common.stringify2DArray(table_yield, doFormatting = True, latexify = True)
            #print cutFlowNameBase + str(int(iSR+1)),  table_yield_str
            
            
            # Add final stage to allSR table
            table_yield_allSR_str.append([cutFlowNameBase + str(int(iSR+1))] + table_yield_str[-1])
            
            
            table_yield_str.insert(0, columnLabels)
            #print table_yield_str
            
            table_yield_latex = Array2LatexTable.array2LatexTable(
                table_yield_str,
                isColumnTitled = True,
                table_caption = cutFlowNameBase + str(int(iSR+1)),
            )
            
            cutFlowFileName = "%s/cutFlow_%s%d.txt" %(cutFlowDir, cutFlowNameBase, int(iSR+1))
            print "Writing:", cutFlowFileName
            
            with open(cutFlowFileName, "w") as outfile :
                
                outfile.write(table_yield_latex)


if (printTable) :
    
    columnLabels = [""] + columnLabels
    table_yield_allSR_str.insert(0, columnLabels)
    #print table_yield_allSR_str
    
    columnColorDict = {}
    
    columnColorDict[columnLabels.index("TT / all MC")] = ["red", 25]
    
    for iSig in range(0, len(labels_stopPair)) :
        
        columnColorDict[columnLabels.index(labels_stopPair[iSig])] = ["blue", 25]
    
    table_yield_allSR_latex = Array2LatexTable.array2LatexTable(
        table_yield_allSR_str,
        isColumnTitled = True,
        table_caption = "all " + cutFlowNameBase,
        columnColorDict = columnColorDict
    )
    
    cutFlowFileName = "%s/cutFlow_%sall.txt" %(cutFlowDir, cutFlowNameBase)
    print "Writing:", cutFlowFileName
    
    with open(cutFlowFileName, "w") as outfile :
        
        outfile.write(table_yield_allSR_latex)


if (plotYield) :
    
    canvas = TCanvas("canvas", "canvas")
    canvas.SetCanvasSize(800, 800)
    canvas.Divide(1, 2)
    
    (canvas.cd(1)).SetPad(-0.0175, 0.25, 1.08, 1)
    (canvas.cd(2)).SetPad(-0.0175, 0.02, 1.08, 0.25)
    
    legend = TLegend(0.625, 0.60, 0.895, 0.895)
    legend.SetFillStyle(0)
    
    stack = THStack(cutFlowNameBase, "#tau_{h}#tau_{h} " + cutFlowNameBase)
    
    
    canvas.cd(1)
    
    # Add data
    #legend.AddEntry(h1_yield_data, Details.label_tauTau_data[0])
    legend.AddEntry(h1_yield_data, "#tau-template method")
    
    
    # Add MC
    for iMC in range(0, len(labels_mc)) :
        
        h1_temp = list_h1_yield_mc[iMC]
        
        stack.Add(h1_temp, histStyle_mc)
        legend.AddEntry(h1_temp, labels_mc[iMC])
        
        h1_yieldSum_mc.Add(h1_temp)
    
    stack.SetMinimum(1.0e-3)
    stack.SetMaximum(1.0e3)
    stack.Draw()
    stack.GetXaxis().SetLabelSize(0)
    
    
    # Add signal
    for iSig in range(0, len(labels_stopPair)) :
        
        h1_temp = list_h1_yield_stopPair[iSig]
        
        #stack.Add(h1_temp, histStyle_stopPair)
        h1_temp.Draw(histStyle_stopPair + " same")
        legend.AddEntry(h1_temp, labels_stopPair[iSig])
    
    
    (canvas.cd(1)).SetGridy()
    (canvas.cd(1)).SetLogy()
    (canvas.cd(1)).SetBottomMargin(0)
    
    #h1_yield_data.SetMinimum(1.0)
    h1_yield_data.Draw("E same")
    
    legend.Draw()
    
    
    # Plot ratio
    canvas.cd(2)
    
    print "*****"
    print "bin 1: %0.2f, %0.8f" %(h1_yield_data.GetBinContent(1), h1_yield_data.GetBinError(1))
    print "bin 1: %0.2f, %0.8f" %(h1_yieldSum_mc.GetBinContent(1), h1_yieldSum_mc.GetBinError(1))
    print "bin 2: %0.2f, %0.8f" %(h1_yield_data.GetBinContent(2), h1_yield_data.GetBinError(2))
    print "bin 2: %0.2f, %0.8f" %(h1_yieldSum_mc.GetBinContent(2), h1_yieldSum_mc.GetBinError(2))
    print "bin 3: %0.2f, %0.8f" %(h1_yield_data.GetBinContent(3), h1_yield_data.GetBinError(3))
    print "bin 3: %0.2f, %0.8f" %(h1_yieldSum_mc.GetBinContent(3), h1_yieldSum_mc.GetBinError(3))
    print "*****"
    
    h1_dataMCratio = h1_yield_data.Clone()
    h1_dataMCratio.Divide(h1_yieldSum_mc)
    
    h1_dataMCratio.SetStats(0)
    h1_dataMCratio.SetMinimum(0)
    h1_dataMCratio.SetMaximum(2)
    
    h1_dataMCratio.GetXaxis().SetLabelSize(0.125)
    h1_dataMCratio.GetXaxis().SetTickLength(0.09)
    
    h1_dataMCratio.GetYaxis().SetNdivisions(-502)
    h1_dataMCratio.GetYaxis().SetLabelSize(0.1)
    
    h1_dataMCratio.SetTitle("")
    h1_dataMCratio.GetXaxis().SetLabelSize(0.175)
    h1_dataMCratio.GetYaxis().SetTitle("Template / MC")
    h1_dataMCratio.GetYaxis().SetTitleSize(0.1)
    h1_dataMCratio.GetYaxis().SetTitleOffset(0.3)
    h1_dataMCratio.GetYaxis().CenterTitle()
    
    (canvas.cd(2)).SetGridy()
    (canvas.cd(2)).SetTopMargin(0)
    
    h1_dataMCratio.Draw("E")
    
    
    
    canvas.SaveAs("%s/SRyield_tauTemplateMethodEstimation_%s_allMC.pdf" %(plotDir, cutFlowNameBase))

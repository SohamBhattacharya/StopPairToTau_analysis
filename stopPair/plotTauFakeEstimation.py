import array
import copy
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

ROOT.gROOT.SetBatch(1)


noPrelim = False
#noPrelim = True
noPrelimStr = "_noPrelim"*(noPrelim)


#withSig = True
withSig = False


l_era = ["2016"]
#l_era = ["2017"]
#l_era = ["2016", "2017"]

eraStr = "+".join(l_era)


CMSextraText = Common.getCMSextraText(isPrelim = (not noPrelim))
lumiText = Common.getLumitext(eraStr)
#lumiText = Common.getLumitext(era, eraDetail = "BtoE")
#lumiText = Common.getLumitext(era, eraDetail = "F")


suffix = "_tauTau_analysis"
#suffix = "_tauTau_analysis_baselineSRB_METleq50"
#suffix = "_tauTau_analysis_nJetGeq1"

suffix_fakeEstimation = "_tauTau_fakeEstimation"
#suffix_fakeEstimation = "_tauTau_fakeEstimation_baselineSRB_METleq50"
#suffix_fakeEstimation = "_tauTau_fakeEstimation_nJetGeq1"

rootFileName = "custom_all_analyzed.root"
rootFileName_fakeEstimation = "custom_all_fakeEstimation_tauTau.root"


d_inputFiles_data = {}
d_inputFiles_fakeEstimation = {}

d_inputFiles_WJetsToLNu = {}
d_inputFiles_DYJetsToLL = {}
d_inputFiles_VH = {}
d_inputFiles_VV = {}
d_inputFiles_WG = {}
d_inputFiles_ttbar = {}
d_inputFiles_singleTop = {}
d_inputFiles_TTX = {}

d_inputFile_sig = {}
d_inputFile_sig_genMET = {}
d_massPointFile = {}

d_massPointInfo = {}


d_inputFiles_otherSM = {}
d_crossSections_otherSM = {}
d_inputFiles_mc = {}
d_crossSections_mc = {}
d_inputFileDirs_otherSM = {}
d_inputFileDirs_mc = {}



for iEra in range(0, len(l_era)) :
    
    era = l_era[iEra]
    
    d_inputFiles_data[era] = Common.getRootFiles(Details.cutFlowDir_tauTau_data[era], suffix, rootFileName)
    d_inputFiles_fakeEstimation[era] = Common.getRootFiles(Details.cutFlowDir_tauTau_fakeEstimation[era], suffix_fakeEstimation, rootFileName_fakeEstimation)
    
    d_inputFiles_WJetsToLNu[era] = Common.getRootFiles(Details.cutFlowDir_WJetsToLNu[era], suffix, rootFileName)
    d_inputFiles_DYJetsToLL[era] = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], suffix, rootFileName)
    d_inputFiles_VH[era] = Common.getRootFiles(Details.cutFlowDir_VH[era], suffix, rootFileName)
    d_inputFiles_VV[era] = Common.getRootFiles(Details.cutFlowDir_VV[era], suffix, rootFileName)
    d_inputFiles_WG[era] = Common.getRootFiles(Details.cutFlowDir_WG[era], suffix, rootFileName)
    d_inputFiles_ttbar[era] = Common.getRootFiles(Details.cutFlowDir_ttbar[era], suffix, rootFileName)
    d_inputFiles_singleTop[era] = Common.getRootFiles(Details.cutFlowDir_singleTop[era], suffix, rootFileName)
    d_inputFiles_TTX[era] = Common.getRootFiles(Details.cutFlowDir_TTX[era], suffix, rootFileName)
    
    #inputFiles_DYJetsToLL_fake = Common.getRootFiles(Details.cutFlowDir_DYJetsToLL[era], "_tauTau_analysis_baselineSRB_METleq50_nFakeTauGeq1", rootFileName)
    #inputFiles_ttbar_fake = Common.getRootFiles(Details.cutFlowDir_ttbar[era], "_tauTau_analysis_baselineSRB_METleq50_nFakeTauGeq1", rootFileName)
    
    
    inputFile_sig = ""
    inputFile_sig_genMET = ""
    massPointFile = ""
    
    if (era == "2016") :
        
        #inputFile_sig = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis_genMatched_baselineSRB_nb0/custom_all_analyzed.root")
        inputFile_sig = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/custom_all_analyzed.root")
        inputFile_sig_genMET = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis_withGenMET/custom_all_analyzed.root")
        
        massPointFile = "stopPair_mc/output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"
        
    
    elif (era == "2017") :
        
        inputFile_sig = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/custom_all_analyzed.root")
        inputFile_sig_genMET = ROOT.TFile.Open("stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis_withGenMET/custom_all_analyzed.root")
        
        massPointFile = "stopPair_mc/output_genParam/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"
    
    d_inputFile_sig[era] = inputFile_sig
    d_inputFile_sig_genMET[era] = inputFile_sig_genMET
    d_massPointFile[era] = massPointFile
    
    d_massPointInfo[era] = numpy.loadtxt(massPointFile, delimiter = ",")
    
    
    d_inputFiles_otherSM[era] = (
        d_inputFiles_WJetsToLNu[era] +
        d_inputFiles_VH[era] +
        d_inputFiles_VV[era] +
        d_inputFiles_WG[era] +
        d_inputFiles_singleTop[era] +
        d_inputFiles_TTX[era]
    )
    
    
    d_crossSections_otherSM[era] = (
        Details.crossSection_WJetsToLNu[era] +
        Details.crossSection_VH[era] +
        Details.crossSection_VV[era] +
        Details.crossSection_WG[era] +
        Details.crossSection_singleTop[era] +
        Details.crossSection_TTX[era]
    )
    
    
    d_inputFiles_mc[era] = [
        d_inputFiles_ttbar[era],
        d_inputFiles_DYJetsToLL[era],
        d_inputFiles_otherSM[era],
    ]
    
    
    d_crossSections_mc[era] = [
        Details.crossSection_ttbar[era],
        Details.crossSection_DYJetsToLL[era],
        d_crossSections_otherSM[era],
    ]
    
    
    d_inputFileDirs_otherSM[era] = (
        Details.cutFlowDir_WJetsToLNu[era] +
        Details.cutFlowDir_VH[era] +
        Details.cutFlowDir_VV[era] +
        Details.cutFlowDir_WG[era] +
        Details.cutFlowDir_singleTop[era] +
        Details.cutFlowDir_TTX[era]
    )
    
    d_inputFileDirs_mc[era] = [
        Details.cutFlowDir_ttbar[era],
        Details.cutFlowDir_DYJetsToLL[era],
        d_inputFileDirs_otherSM[era],
    ]


l_selectMassPoint = [
    #[500, 300],
    #[800, 1],
    #[800, 400],
    
    #[400, 100],
    #[800, 400],
    #[1000, 100],
    
    [300, 100], [500, 350], [800, 300],
]

#lumi_data = 8.347e3
#lumi_data = 35.9e3
d_lumi_data = Details.luminosity_data


plotDir = "plots/tauTau_fakeEstimation/%s" %(eraStr)
#plotDir = "plots/tauTau_fakeEstimation/%sBtoE" %(era)
#plotDir = "plots/tauTau_fakeEstimation/%sF" %(era)

if (withSig) :
    
    plotDir = "plots/tauTau_fakeEstimation_withSig/%s" %(eraStr)

plotDir = "%s%s" %(plotDir, noPrelimStr)

os.system("mkdir -p %s" %(plotDir))

debug = False

histStyle_data = "PE1"
histStyle_mc = "hist"
histStyle_sig = "hist"

l_pTbin = [0, 40, 80, 150, 300, 500]
#l_pTbin = [0, 40, 500]

l_etaBin = list(numpy.arange(-3, 3.6, 0.6))
l_phiBin = list(numpy.arange(-3.6, 4.2, 0.6))

l_pTbin_b = [0, 20, 80, 150, 300, 500]

l_mT2bin = [0, 40, 80, 120, 200, 350, 380] if withSig else [0, 40, 80, 120, 200, 300]
#l_mT2bin = [0, 40, 80, 100, 200, 300, 500]
#l_mT2bin = []

l_HTbin = [0, 100, 300, 700, 1100, 1500, 2000, 2100] if withSig else [0, 100, 300, 700, 1200, 1700]
#l_HTbin = [0, 100, 300, 500, 700, 1200, 1700]

#l_invMassBin = [0, 20, 40, 60, 80, 100, 120, 150, 200]
l_invMassBin = [0, 20, 40, 50, 60, 70, 80, 90, 100, 120, 150, 200]
#l_invMassBin = [0, 20, 40, 60, 100, 120, 150, 200, 300]

#l_METbin = [0, 10, 20, 30, 40, 50]
l_METbin = [0, 50, 100, 150, 200, 300, 500, 900, 1000] if withSig else [0, 50, 100, 150, 200, 300, 500]


yMin = 1e-3 if withSig else 1e-2


labels_mc = [
    Details.latex_ttbar,
    Details.latex_DYJetsToLL,
    
    Details.latex_otherSM,
    
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
    
    Details.color_otherSM,
    
    #Details.color_WJetsToLNu,
    #Details.color_VH,
    #Details.color_VV,
    #Details.color_WG,
    #Details.color_singleTop,
    #Details.color_TTX,
]



# [[name, isCorreleted], ...]
l_systStr_commonMC = [
    #["tauES", False],
    #["pileupReweight", False],
    #["tauIDisoSF", False],
    #["bTaggingSF", False],
    #["JEC", True],
    #["JER", False],
    #["unclusteredEnergy", False],
    #["scale", True],
    ["normalization", True],
]


l_systStr_ttbar_toInclude = [
    #["tauES", False],
    #["tauIDisoSF", False],
]


d_syst_DY = [
    #["ZpTreweight", False],
]


l_systStr_fake = [
    ["tauFakeRateRegion", True],
    ["tauFakeRateJetPartonFlav", True],
]


# In %
d_systStr_flat = {
    "normalization": {
        "up": 0.0,
        "down": 0.0,
    },
}


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
    yMax = 1e4 #Common.initVal
    
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
plotQuantity_temp.yMin = yMin
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau1_eta_reco"
plotQuantity_temp.xtitle = "#tau^{1}_{h} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = yMin
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
plotQuantity_temp.yMin = yMin
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
plotQuantity_temp.yMin = yMin
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tau2_eta_reco"
plotQuantity_temp.xtitle = "#tau^{2}_{h} #eta"
plotQuantity_temp.ytitle = "Events / bin-width"
plotQuantity_temp.l_rebin = l_etaBin
plotQuantity_temp.xMin = -2.5
plotQuantity_temp.xMax = 2.5
plotQuantity_temp.yMin = yMin
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
plotQuantity_temp.yMin = yMin
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_MET_mT2_lsp0_reco"
#plotQuantity_temp.xtitle = "m_{T2} (#tau^{1}_{h}, #tau^{2}_{h}, p^{miss}_{T}) [GeV]"
plotQuantity_temp.xtitle = "m_{T2} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_mT2bin
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = l_mT2bin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
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
plotQuantity_temp.yMin = yMin
plotQuantity_temp.logY = True
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "tauTau_jet_HT_reco"
#plotQuantity_temp.xtitle = "H_{T} (#tau^{1}_{h}, #tau^{2}_{h}, jet) [GeV]"
plotQuantity_temp.xtitle = "H_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_HTbin
plotQuantity_temp.xMin = 100 if withSig else 0
plotQuantity_temp.xMax = l_HTbin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 1000
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
plotQuantity_temp.yMin = yMin
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "UR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "MET_E_reco"
plotQuantity_temp.xtitle = "p^{miss}_{T} [GeV]"
plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.nRebin = 3
plotQuantity_temp.l_rebin = l_METbin
plotQuantity_temp.xMin = 50 if withSig else 0
plotQuantity_temp.xMax = l_METbin[-1]
plotQuantity_temp.yMin = yMin
#plotQuantity_temp.yMax = 500
plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "LR"
l_plotQuantity.append(plotQuantity_temp)


plotQuantity_temp = PlotQuantity()
plotQuantity_temp.name = "jet_n_reco"
plotQuantity_temp.xtitle = "n_{jet}"
plotQuantity_temp.ytitle = "Events"
#plotQuantity_temp.l_rebin = l_pTbin_b
plotQuantity_temp.xMin = 0
plotQuantity_temp.xMax = 10
plotQuantity_temp.yMin = yMin
plotQuantity_temp.logY = True
plotQuantity_temp.legendPos = "LL"
l_plotQuantity.append(plotQuantity_temp)


#plotQuantity_temp = PlotQuantity()
#plotQuantity_temp.name = "b_n_medium_reco"
#plotQuantity_temp.xtitle = "n_{b}"
#plotQuantity_temp.ytitle = "Events"
#plotQuantity_temp.xMin = 0
#plotQuantity_temp.xMax = 7
#plotQuantity_temp.yMin = yMin
##plotQuantity_temp.yMax = 1e5
#plotQuantity_temp.logY = True
#plotQuantity_temp.legendPos = "UR"
#l_plotQuantity.append(plotQuantity_temp)
#
#
#plotQuantity_temp = PlotQuantity()
#plotQuantity_temp.name = "b1_pT_reco"
#plotQuantity_temp.xtitle = "b_{1} p_{T} [GeV]"
#plotQuantity_temp.ytitle = "Events / GeV"
#plotQuantity_temp.l_rebin = l_pTbin_b
#plotQuantity_temp.xMin = 0
#plotQuantity_temp.xMax = l_pTbin_b[-1]
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.logY = True
#l_plotQuantity.append(plotQuantity_temp)


#plotQuantity_temp = PlotQuantity()
#plotQuantity_temp.name = "jet_MET_deltaPhi_min_reco"
#plotQuantity_temp.xtitle = "min(#Delta#phi(jet_{1 to 4}, p^{miss}_{T}))"
#plotQuantity_temp.ytitle = "Events / bin-width"
#plotQuantity_temp.l_rebin = l_phiBin
#plotQuantity_temp.xMin = l_phiBin[0]
#plotQuantity_temp.xMax = 3.6
#plotQuantity_temp.yMin = yMin
#plotQuantity_temp.logY = True
#l_plotQuantity.append(plotQuantity_temp)


##################################################

l_details = []

l_details.append({
    "Data": "tightTight_SS_baselineSRB_nbAny",
    "Fake": "SS_baselineSRB_nbAny",
    "MC": "tightTight_SS_genMatched_baselineSRB_nbAny",
    "Dir": "SS_baselineSRB_nbAny"
})

#l_details.append({
#    "Data": "tightTight_OS_baselineSRB_nb0",
#    "Fake": "OS_baselineSRB_nb0",
#    "MC": "tightTight_OS_genMatched_baselineSRB_nb0",
#    "Dir": "OS_baselineSRB_nb0",
#})

#l_details.append({
#    "Data": "tightTight_OS_baselineSRB",
#    "Fake": "OS_baselineSRB",
#    "MC": "tightTight_OS_genMatched_baselineSRB",
#    "Dir": "OS_baselineSRB",
#})

#l_details.append({
#    "Data": "tightTight_OS_baselineSRB",
#    "Fake": "OS_baselineSRB",
#    "MC": "tightTight_OS_genMatched_baselineSRB",
#    "Dir": "OS_baselineSRB_METleq50",
#})

#l_details.append({
#    "Data": "tightTight_OS_baselineSRB_nb0_nJetGeq1",
#    "Fake": "OS_baselineSRB_nb0_nJetGeq1",
#    "MC": "tightTight_OS_genMatched_baselineSRB_nb0_nJetGeq1",
#    "Dir": "OS_baselineSRB_nb0_nJetGeq1",
#})


for iDetail in range(0, len(l_details)) :
    
    for iQuantity in range(0, len(l_plotQuantity)) :
        
        d_histDetail_data = {}
        d_histDetail_mc = {}
        d_histDetail_sig = {}
        
        l_systInfo = []
        
        for iEra in range(0, len(l_era)) :
            
            era = l_era[iEra]
            
            plotQuantity = l_plotQuantity[iQuantity]
            
            ##########
            detailStr = l_details[iDetail]["Data"]
            histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
            h1_data = Common.HistogramDetails(l_rootFile = d_inputFiles_data[era], histName = histName)
            h1_data.getHist(nRebin = plotQuantity.nRebin, l_rebin = plotQuantity.l_rebin)
            #h1_data.hist = h1_data.hist.Rebin(len(plotQuantity.l_rebin)-1, "", array.array("d", plotQuantity.l_rebin))
            #h1_data.hist.Scale(1.0, "width")
            h1_data.histLabel = "Data"
            h1_data.color = 1
            h1_data.lineWidth = 2
            h1_data.drawOption = histStyle_data
            
            print "\n"
            
            d_histDetail_data[era] = h1_data
            
            
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
            h1_fakeEstimation = Common.HistogramDetails(l_rootFile = d_inputFiles_fakeEstimation[era], histName = histName)
            h1_fakeEstimation.getFakeEstimationHistogram(
                suffix = l_details[iDetail]["Fake"],
                nRebin = plotQuantity.nRebin,
                l_rebin = plotQuantity.l_rebin,
                component = "total",
                debug = True,
            )
            #h1_fakeEstimation.hist.Scale(1.0, "width")
            h1_fakeEstimation.histLabel = "Misid. #tau_{h}"
            h1_fakeEstimation.color = Details.color_QCD
            h1_fakeEstimation.drawOption = histStyle_mc
            
            l_histDetail_mc.append(h1_fakeEstimation)
            
            
            ##########
            
            h1_systErrPos = h1_data.hist.Clone()
            h1_systErrPos.Reset()
            h1_systErrPos.SetDirectory(0)
            
            h1_systErrNeg = h1_data.hist.Clone()
            h1_systErrNeg.Reset()
            h1_systErrNeg.SetDirectory(0)
            
            
            nEventHistName = ""
            
            for iMC in range(0, len(d_inputFiles_mc[era])) :
                
                detailStr = l_details[iDetail]["MC"]
                histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
                nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
                
                #if ("WJets" in inputFiles_mc[iMC][0].GetName() or "DYJets" in inputFiles_mc[iMC][0].GetName()) :
                #    
                #    nEventHistName = ""
                
                h1_temp = Common.HistogramDetails(l_rootFile = d_inputFiles_mc[era][iMC], l_xs = d_crossSections_mc[era][iMC], histName = histName)
                h1_temp.getHist(
                    xsNormalize = True,
                    nEventHistName = nEventHistName,
                    nRebin = plotQuantity.nRebin,
                    l_rebin = plotQuantity.l_rebin
                )
                h1_temp.hist.Scale(d_lumi_data[era])
                h1_temp.histLabel = labels_mc[iMC]
                h1_temp.color = colors_mc[iMC]
                h1_temp.drawOption = histStyle_mc
                
                l_histDetail_mc.append(h1_temp)
                
                print ""
                
                #l_systStr_temp = []
                l_systStr_temp = l_systStr_commonMC
                
                if ("ttbar" in d_inputFileDirs_mc[era][iMC][0]) :
                    
                    l_systStr_temp = l_systStr_ttbar_toInclude
                
                elif  ("DYJets" in d_inputFileDirs_mc[era][iMC][0]) :
                    
                    l_systStr_temp += d_syst_DY
                
                l_syst_name = [ele[0] for ele in l_systStr_temp]
                l_syst_corr = [ele[1] for ele in l_systStr_temp]
                
                d_syst_info = Common.getSystematicsHist(
                    l_rootFileDir = d_inputFileDirs_mc[era][iMC],
                    rootFileName = rootFileName,
                    l_xs = d_crossSections_mc[era][iMC],
                    suffix = suffix,
                    l_systStr = l_syst_name,
                    l_systStr_isEraCorr = l_syst_corr,
                    d_systStr_flat = d_systStr_flat,
                    histName = histName,
                    nEventHistName = nEventHistName,
                    detailStr = "",
                    nRebin = plotQuantity.nRebin,
                    l_rebin = plotQuantity.l_rebin,
                    era = "",
                    scale = d_lumi_data[era],
                    negToZero = True,
                    returnSystListOnly = True,
                    #debug = False,
                )
                
                l_systInfo.extend(d_syst_info)
                
                #h1_systErrPos = Common.histAdd(h1_systErrPos, d_syst_info["histPos"].Clone(), "quad")
                #h1_systErrNeg = Common.histAdd(h1_systErrNeg, d_syst_info["histNeg"].Clone(), "quad")
                
                
                d_histDetail_mc[era] = l_histDetail_mc
            
            
            l_histDetail_sig = []
            
            if (withSig) :
                
                for iMass in range(0, len(d_massPointInfo[era])) :
                    
                    stop1_m = d_massPointInfo[era][iMass, 0]
                    neutralino1_m = d_massPointInfo[era][iMass, 1]
                    xs_sig = d_massPointInfo[era][iMass, 3]
                    xsUnc_sig = d_massPointInfo[era][iMass, 4]
                    
                    if ([int(stop1_m), int(neutralino1_m)] not in l_selectMassPoint) :
                        
                        continue
                    
                    detailStr = "%s_%d_%d" %(l_details[iDetail]["MC"], stop1_m, neutralino1_m)
                    histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
                    nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
                    
                    h1_temp = Common.HistogramDetails(l_rootFile = [d_inputFile_sig[era]], l_xs = [xs_sig], histName = histName)
                    h1_temp.getHist(
                        xsNormalize = True,
                        nEventHistName = nEventHistName,
                        nRebin = plotQuantity.nRebin,
                        l_rebin = plotQuantity.l_rebin
                    )
                    
                    h1_temp_genMET = Common.HistogramDetails(l_rootFile = [d_inputFile_sig_genMET[era]], l_xs = [xs_sig], histName = histName)
                    h1_temp_genMET.getHist(
                        xsNormalize = True,
                        nEventHistName = nEventHistName,
                        nRebin = plotQuantity.nRebin,
                        l_rebin = plotQuantity.l_rebin
                    )
                    
                    h1_temp.hist.Add(h1_temp_genMET.hist)
                    h1_temp.hist.Scale(0.5)
                    
                    h1_temp.hist.Scale(d_lumi_data[era])
                    h1_temp.histLabel = "x = 0.5, [%d, %d]" %(stop1_m, neutralino1_m)
                    #h1_temp.color = ROOT.kCyan + 2*len(l_histDetail_sig)
                    #h1_temp.color = ROOT.kMagenta + 2*(len(l_histDetail_sig)+1)
                    h1_temp.color = Details.l_color_sig[len(l_histDetail_sig)]
                    h1_temp.drawOption = histStyle_sig
                    h1_temp.lineStyle = Details.l_lineStyle_sig[len(l_histDetail_sig)]
                    h1_temp.lineWidth = 5
                    
                    l_histDetail_sig.append(h1_temp)
                    
                    print ""
                    
                    d_histDetail_sig[era] = l_histDetail_sig
            
            
            ##################################################
            ##################################################
            #
            ######
            #detailStr = l_details[iDetail]["MC"]
            #histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
            #nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
            #
            #h1_temp = Common.HistogramDetails(l_rootFile = inputFiles_DYJetsToLL_fake, l_xs = Details.crossSection_DYJetsToLL[era], histName = histName)
            #h1_temp.getHist(
            #    xsNormalize = True,
            #    nEventHistName = nEventHistName,
            #    nRebin = plotQuantity.nRebin,
            #    l_rebin = plotQuantity.l_rebin
            #)
            #h1_temp.hist.Scale(lumi_data)
            #h1_temp.histLabel = "DY+jets fake (MC)"
            #h1_temp.color = 9
            #h1_temp.drawOption = histStyle_mc
            #h1_temp.lineStyle = 2
            #
            #l_histDetail_sig.append(h1_temp)
            #
            #
            ######
            #detailStr = l_details[iDetail]["MC"]
            #histName = "reco/%s/%s_%s" %(detailStr, plotQuantity.name, detailStr)
            #nEventHistName = "reco/%s/nEvent_%s" %(detailStr, detailStr)
            #
            #h1_temp = Common.HistogramDetails(l_rootFile = inputFiles_ttbar_fake, l_xs = Details.crossSection_ttbar[era], histName = histName)
            #h1_temp.getHist(
            #    xsNormalize = True,
            #    nEventHistName = nEventHistName,
            #    nRebin = plotQuantity.nRebin,
            #    l_rebin = plotQuantity.l_rebin
            #)
            #h1_temp.hist.Scale(lumi_data)
            #h1_temp.histLabel = "t#bar{t} fake (MC)"
            #h1_temp.color = 30
            #h1_temp.drawOption = histStyle_mc
            #h1_temp.lineStyle = 2
            #
            #l_histDetail_sig.append(h1_temp)
            #
            ##################################################
            ##################################################
            
            l_syst_name = [ele[0] for ele in l_systStr_fake]
            l_syst_corr = [ele[1] for ele in l_systStr_fake]
            
            
            d_fakeSyst_info = Common.getSystematicsHist(
                l_rootFileDir = Details.cutFlowDir_tauTau_fakeEstimation[era],
                rootFileName = rootFileName_fakeEstimation,
                l_xs = [],
                suffix = suffix_fakeEstimation,
                l_systStr = l_syst_name,
                l_systStr_isEraCorr = l_syst_corr,
                histName = plotQuantity.name,
                detailStr = l_details[iDetail]["Fake"],
                nRebin = plotQuantity.nRebin,
                l_rebin = plotQuantity.l_rebin,
                era = "",
                scale = 1,
                #negToZero = False,
                returnSystListOnly = True,
                #debug = False,
            )
            
            l_systInfo.extend(d_fakeSyst_info)
        
        
        # Initialize
        l_histDetail_mc = []
        l_histDetail_sig = []
        
        h1_data = copy.deepcopy(d_histDetail_data[l_era[0]])
        h1_data.hist = d_histDetail_data[l_era[0]].hist.Clone()
        h1_data.hist.Reset()
        h1_data.hist.Sumw2()
        
        for iMC in range(0, len(d_histDetail_mc[l_era[0]])) :
            
            histDetail_temp = copy.deepcopy(d_histDetail_mc[l_era[0]][iMC])
            histDetail_temp.hist = d_histDetail_mc[l_era[0]][iMC].hist.Clone()
            histDetail_temp.hist.Reset()
            histDetail_temp.hist.Sumw2()
            
            l_histDetail_mc.append(histDetail_temp)
        
        if (withSig) :
            
            for iSig in range(0, len(d_histDetail_sig[l_era[0]])) :
                
                histDetail_temp = copy.deepcopy(d_histDetail_sig[l_era[0]][iSig])
                histDetail_temp.hist = d_histDetail_sig[l_era[0]][iSig].hist.Clone()
                histDetail_temp.hist.Reset()
                histDetail_temp.hist.Sumw2()
                
                l_histDetail_sig.append(histDetail_temp)
        
        # Add yields
        for iEra in range(0, len(l_era)) :
            
            era = l_era[iEra]
            
            h1_data.hist.Add(d_histDetail_data[era].hist)
            
            for iMC in range(0, len(d_histDetail_mc[l_era[0]])) :
                
                h1_temp = d_histDetail_mc[era][iMC].hist.Clone()
                
                l_histDetail_mc[iMC].hist.Add(h1_temp)
            
            if (withSig) :
                
                for iSig in range(0, len(d_histDetail_sig[l_era[0]])) :
                    
                    h1_temp = d_histDetail_sig[era][iSig].hist.Clone()
                    
                    l_histDetail_sig[iSig].hist.Add(h1_temp)
        
        
        # Add systematics
        
        #h1_systErrPos = Common.histAdd(h1_systErrPos, d_fakeSyst_info["histPos"].Clone(), "quad")
        #h1_systErrNeg = Common.histAdd(h1_systErrNeg, d_fakeSyst_info["histNeg"].Clone(), "quad")
        
        h1_systErrPos = Common.getEraCombinedErrorHist(l_histInfo = l_systInfo, sign = +1)#, debug = True)
        h1_systErrNeg = Common.getEraCombinedErrorHist(l_histInfo = l_systInfo, sign = -1)#, debug = True)
        
        histDetail_systErrPos = Common.HistogramDetails()
        histDetail_systErrPos.hist = h1_systErrPos.Clone()
        
        histDetail_systErrNeg = Common.HistogramDetails()
        histDetail_systErrNeg.hist = h1_systErrNeg.Clone()
        
        
        plotDir_mod = "%s/%s" %(plotDir, l_details[iDetail]["Dir"])
        os.system("mkdir -p %s" %(plotDir_mod))
        
        outFileName = "%s/%s" %(plotDir_mod, plotQuantity.name)
        
        
        # Rearrange for the SR plots
        if (withSig and l_details[iDetail]["MC"] == "tightTight_OS_genMatched_baselineSRB") :
            
            # Reverse the order of prompt backgrounds (ttbar last)
            # Fake at last
            l_histDetail_mc = l_histDetail_mc[1:][::-1] + [l_histDetail_mc[0]]
        
        Common.plot1D(
            l_histDetail_data = [h1_data],
            l_histDetail_mc = l_histDetail_mc,
            ##histDetail_mc_statErrPos = histDetail_mc_statErrPos,
            ##histDetail_mc_statErrNeg = histDetail_mc_statErrNeg,
            histDetail_mc_systErrPos = histDetail_systErrPos,
            histDetail_mc_systErrNeg = histDetail_systErrNeg,
            l_histDetail_sig = l_histDetail_sig,
            #stackDrawOption = "nostack",
            stackDrawOption = "",
            drawMCerr = True,
            ratioPlot = True,
            ratioLegendTextSizeScale = 2,
            ratioStatErr = True,
            ratioTotalErr = True,
            drawRatioStatErr = False,
            drawRatioTotalErr = True,
            #ratioStatErrLabel = "Stat.",
            ratioTotalErrLabel = "Bkg. uncertainty",
            title = era,
            xTitle = plotQuantity.xtitle, yTitle = plotQuantity.ytitle,
            ratioYtitle = "Data / Pred.",
            ratioHist_ymax = 2,
            d_colorRatioGridY = {1: {"color": 2}},
            xMin = plotQuantity.xMin,
            xMax = plotQuantity.xMax,
            yMin = plotQuantity.yMin,
            yMax = plotQuantity.yMax,
            logY = plotQuantity.logY,
            gridX = False, #plotQuantity.gridX,
            gridY = False, #plotQuantity.gridX,
            #centerLabelsX = False, centerLabelsY = False,
            drawLegend = True,
            legendBorder = 0,
            legendTextSize = 0.05 if withSig else 0.045,
            legendPos = plotQuantity.legendPos,
            legendNcolumn = 2,
            dataLegendFirst = True,
            drawRatioLegend = False,
            #fixAlphanumericBinLabels = False,
            CMSextraText = CMSextraText,
            lumiText = lumiText,
            outFileName = outFileName,
            #outFileName_suffix = "",
        )

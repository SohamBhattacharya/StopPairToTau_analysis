import array
import numpy
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

outDir = "plots/tauFakeRate/%s" %(era)
os.system("mkdir -p " + outDir)

suffix = ""
#suffix = "_METleq20"

l_inputFileName = {}

l_inputFileName["2016"] = [
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-07Aug17_ver2-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-07Aug17-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-07Aug17-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-07Aug17-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-07Aug17-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-07Aug17-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    #"tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-07Aug17-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-17Jul2018_ver2-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-17Jul2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
]

#l_inputFileName["2016"+suffix] = [
#    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-07Aug17_ver2-v1_MINIAOD_tauTau_fakeRate_METleq20/custom_all_fakeRate_tauTau.root",
#    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-07Aug17-v1_MINIAOD_tauTau_fakeRate_METleq20/custom_all_fakeRate_tauTau.root",
#    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-07Aug17-v1_MINIAOD_tauTau_fakeRate_METleq20/custom_all_fakeRate_tauTau.root",
#    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-07Aug17-v1_MINIAOD_tauTau_fakeRate_METleq20/custom_all_fakeRate_tauTau.root",
#    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-07Aug17-v1_MINIAOD_tauTau_fakeRate_METleq20/custom_all_fakeRate_tauTau.root",
#    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-07Aug17-v1_MINIAOD_tauTau_fakeRate_METleq20/custom_all_fakeRate_tauTau.root",
#    "tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-07Aug17-v1_MINIAOD_tauTau_fakeRate_METleq20/custom_all_fakeRate_tauTau.root",
#]

l_inputFileName["2017"] = [
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017B-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017C-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017D-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017E-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
    "tauTau_data/output_tauTau_fakeRate/Tau_Run2017F-31Mar2018-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
]


l_inputFileName = l_inputFileName[era+suffix]


#inputFile = TFile.Open("tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root")


l_pTbin = [0, 40, 80, 150, 500]
#l_pTbin = [0, 40, 80, 120, 160, 200]
l_etaBin = numpy.array(list(range(-24, 25, 3))) / 10.0
l_nPVbin = numpy.append(numpy.arange(0, 40, 10), [60, 100])
l_METbin = numpy.arange(0, 60, 10)
l_mT2bin = numpy.append(numpy.arange(0, 80, 20), [100])
l_HTbin = numpy.append(numpy.arange(0, 400, 100), [500])

l_DM = [0, 1, 10, 11]


class PlotInfo :
    
    histName = ""
    
    l_rebin = []
    
    setXmin = False
    xMin = 0
    xTitle = ""
    
    isXinteger = False
    centerLabelsX = False
    
    outFileName = ""


def getHist(l_fileName, histName) :
    
    l_inputFile = [TFile.Open(f) for f in l_fileName]
    
    print "File: %s" %(l_inputFile[0].GetName())
    print "Histogram: %s" %(histName)
    
    hist = l_inputFile[0].Get(histName).Clone()
    hist.Sumw2()
    
    for iFile in range(1, len(l_inputFile)) :
        
        print "File: %s" %(l_inputFile[iFile].GetName())
        print "Histogram: %s" %(histName)
        
        h_temp = l_inputFile[iFile].Get(histName).Clone()
        h_temp.Sumw2()
        
        hist.Add(h_temp)
        
        #print l_fileName[iFile]
    
    hist.SetDirectory(0)
    
    print ""
    
    return hist


####################################################################################################


def plot(plotInfo) :
    
    #tdrstyle.setTDRStyle()
    #ROOT.gROOT.ForceStyle()
    ROOT.gROOT.LoadMacro("tdrstyle.C")
    ROOT.gROOT.ProcessLine("setTDRStyle();")
    
    canvas = TCanvas("canvas", "canvas")
    #canvas.SetCanvasSize(600, 600)
    
    #canvas.SetLeftMargin(0.125)
    canvas.SetRightMargin(0.04)
    #canvas.SetBottomMargin(0.105)
    
    legend = ROOT.TLegend(0.5, 0.65, 0.925, 0.925)
    #legend.SetFillStyle(0)
    legend.SetBorderSize(0)
    #legend.SetBorderSize(1)
    legend.SetTextSize(0.0425)
    
    
    stack = THStack("stack", "stack")
    stack.SetTitle("#tau_{h} fake rate (%s)" %(era))
    
    
    # Loose-Loose
    info_str = "looseLoose_dR03_SS"
    #h2_LL = inputFile.Get("%s/tau_pT_vs_DM_reco_%s" %(info_str, info_str)).Clone()
    h2_LL = getHist(l_inputFileName, "%s/%s_%s" %(info_str, plotInfo.histName, info_str))
    h2_LL.Sumw2()
    
    # Tight-Loose
    info_str = "tightLoose_dR03_SS"
    #h2_TL = inputFile.Get("%s/tau_pT_vs_DM_reco_%s" %(info_str, info_str)).Clone()
    h2_TL = getHist(l_inputFileName, "%s/%s_%s" %(info_str, plotInfo.histName, info_str))
    h2_TL.Sumw2()
    
    # Tight-Tight
    info_str = "tightTight_dR03_SS"
    #h2_TT = inputFile.Get("%s/tau_pT_vs_DM_reco_%s" %(info_str, info_str)).Clone()
    h2_TT = getHist(l_inputFileName, "%s/%s_%s" %(info_str, plotInfo.histName, info_str))
    h2_TT.Sumw2()
    
    l_h1_LLtoTL = []
    l_h1_TLtoTT = []
    
    for iDM in range(0, len(l_DM)) :
        
        DM = l_DM[iDM]
        
        iBin = h2_LL.GetXaxis().FindBin(DM)
        
        h1_LL = h2_LL.ProjectionY("_py", iBin, iBin)
        h1_LL.Sumw2()
        h1_LL = h1_LL.Rebin(len(plotInfo.l_rebin)-1, "", array.array("d", plotInfo.l_rebin))
        #print "h1_LL %f" %(h1_LL.GetBinContent(h1_LL.GetNbinsX()))
        
        h1_TL = h2_TL.ProjectionY("_py", iBin, iBin)
        h1_TL.Sumw2()
        h1_TL = h1_TL.Rebin(len(plotInfo.l_rebin)-1, "", array.array("d", plotInfo.l_rebin))
        #print "h1_TL %f" %(h1_TL.GetBinContent(h1_TL.GetNbinsX()))
        
        h1_TT = h2_TT.ProjectionY("_py", iBin, iBin)
        h1_TT.Sumw2()
        h1_TT = h1_TT.Rebin(len(plotInfo.l_rebin)-1, "", array.array("d", plotInfo.l_rebin))
        #print "h1_TT %f" %(h1_TT.GetBinContent(h1_TT.GetNbinsX()))
        
        # LL to TL
        h1_temp = h1_TL.Clone()
        h1_temp.Divide(h1_LL)
        h1_temp.SetLineColor(iDM+1)
        h1_temp.SetLineWidth(3)
        h1_temp.SetLineStyle(2)
        
        l_h1_LLtoTL.append(h1_temp.Clone())
        stack.Add(l_h1_LLtoTL[-1], "hist E")
        legend.AddEntry(l_h1_LLtoTL[-1], "LL #rightarrow TL (DM %d)" %(DM))
        
        # TL to TT
        h1_temp = h1_TT.Clone()
        h1_temp.Divide(h1_TL)
        h1_temp.SetLineColor(iDM+1)
        h1_temp.SetLineWidth(3)
        
        l_h1_TLtoTT.append(h1_temp.Clone())
        stack.Add(l_h1_TLtoTT[-1], "hist E")
        legend.AddEntry(l_h1_TLtoTT[-1], "TL #rightarrow TT (DM %d)" %(DM))
        
    
    stack.Draw("nostack")
    legend.Draw()
    
    stack.GetXaxis().SetTitle(plotInfo.xTitle)
    stack.GetYaxis().SetTitle("#tau_{h} misid. probability")
    
    stack.GetXaxis().SetLabelSize(0.05)
    stack.GetYaxis().SetLabelSize(0.05)
    
    stack.GetXaxis().SetTitleOffset(1.05)
    stack.GetYaxis().SetTitleOffset(1.25)
    
    stack.GetXaxis().SetTitleSize(0.055)
    stack.GetYaxis().SetTitleSize(0.055)
    
    stack.GetXaxis().CenterTitle(True)
    stack.GetYaxis().CenterTitle(True)
    
    if (plotInfo.setXmin) :
        
        stack.GetXaxis().SetRangeUser(plotInfo.xMin, plotInfo.l_rebin[-1])
    
    if (plotInfo.centerLabelsX) :
        
        stack.GetXaxis().CenterLabels()
    
    stack.SetMinimum(0)
    stack.SetMaximum(1.5)
    
    if (len(plotInfo.l_rebin)) :
        
        if ( plotInfo.isXinteger) :
            
            stack.GetXaxis().SetNdivisions(len(plotInfo.l_rebin), 1, 1)
        
        else :
            
            stack.GetXaxis().SetNdivisions(len(plotInfo.l_rebin), 5, 1)
    
    #canvas.SetGridx()
    #canvas.SetGridy()
    
    # CMS label
    CMS_lumi.CMS_lumi(pad = canvas, iPeriod = 0, iPosX = 0, CMSextraText = Common.getCMSextraText(era), lumiText = Common.getLumitext(era))
    
    canvas.SaveAs(outDir + "/%s%s.pdf" %(plotInfo.outFileName, suffix))
    
    canvas.Clear()
    legend.Clear()
    stack.Clear()



#plotInfo = PlotInfo()
#plotInfo.histName = "tau_pT_vs_DM_reco"
#plotInfo.l_rebin = l_pTbin
#plotInfo.setXmin = True
#plotInfo.xMin = 40
#plotInfo.xTitle = "#tau_{h} p_{T} [GeV]"
#plotInfo.outFileName = "tauFakeRate_pT"
#plot(plotInfo)


plotInfo = PlotInfo()
plotInfo.histName = "tau_eta_reco"
plotInfo.l_rebin = l_etaBin
plotInfo.setXmin = True
plotInfo.xMin = l_etaBin[0]
plotInfo.xTitle = "#tau_{h} #eta"
plotInfo.outFileName = "tauFakeRate_eta"
plot(plotInfo)


#plotInfo = PlotInfo()
#plotInfo.histName = "tau_nPV_vs_DM_reco"
#plotInfo.l_rebin = l_nPVbin
#plotInfo.xTitle = "Number of vertices"
#plotInfo.outFileName = "tauFakeRate_nPV"
#plot(plotInfo)
#
#
#plotInfo = PlotInfo()
#plotInfo.histName = "MET_vs_DM_reco"
#plotInfo.l_rebin = l_METbin
#plotInfo.xTitle = "#slash{E}_{T} [GeV]"
#plotInfo.outFileName = "tauFakeRate_MET"
#plot(plotInfo)
#
#
#plotInfo = PlotInfo()
#plotInfo.histName = "tauTau_MET_mT2_vs_DM_reco"
#plotInfo.l_rebin = l_mT2bin
#plotInfo.xTitle = "m_{T2} (#tau^{1}_{h}, #tau^{2}_{h}, #slash{E}_{T}) [GeV]"
#plotInfo.outFileName = "tauFakeRate_mT2"
#plot(plotInfo)
#
#
#plotInfo = PlotInfo()
#plotInfo.histName = "tauTau_jet_HT_vs_DM_reco"
#plotInfo.l_rebin = l_HTbin
#plotInfo.xTitle = "H_{T} (#tau^{1}_{h}, #tau^{2}_{h}, jet) [GeV]"
#plotInfo.outFileName = "tauFakeRate_HT"
#plot(plotInfo)
#
#
#plotInfo = PlotInfo()
#plotInfo.histName = "b_n_vs_DM_reco"
#plotInfo.l_rebin = range(0, 7)
#plotInfo.xTitle = "n_{b}"
#plotInfo.isXinteger = True
#plotInfo.centerLabelsX = True
#plotInfo.outFileName = "tauFakeRate_b_n"
#plot(plotInfo)

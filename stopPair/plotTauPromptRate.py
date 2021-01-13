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
#era = "2017"


d_inputFile = {
    "2016": "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
    "2017": "ttbar_mc/output_tauIdIsoEfficiency/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
}


d_histName = {
    "2016": {
        #"L": "LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_DM_reco",
        #"T": "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_DM_reco",
        
        "L": "LooseDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_DM_reco",
        "T": "TightDeepTau2017v2p1VSjet_LooseDeepTau2017v2p1VSe_TightDeepTau2017v2p1VSmu/tau_pT_vs_DM_reco",
    },
    
    "2017": {
        "L": "LooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_DM_reco",
        "T": "TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_DM_reco",
    },
}


outDir = "plots/tauPromptRate/%s" %(era)
os.system("mkdir -p " + outDir)
inputFile = TFile.Open(d_inputFile[era])


l_pTbin = [0, 40, 80, 150, 500]
#l_pTbin = [0, 40, 80, 120, 160, 200]
l_DM = [0, 1, 10, 11]


####################################################################################################

tdrstyle.setTDRStyle()

canvas = TCanvas("canvas", "canvas")
#canvas.SetCanvasSize(600, 600)

#canvas.SetLeftMargin(0.125)
canvas.SetRightMargin(0.04)
#canvas.SetBottomMargin(0.105)

legend = ROOT.TLegend(0.6, 0.65, 0.925, 0.925)
#legend.SetFillStyle(0)
legend.SetBorderSize(0)
#legend.SetBorderSize(1)
legend.SetTextSize(0.0425)

stack = THStack("stack", "stack")
stack.SetTitle("#tau_{h} prompt rate (%s)" %(era))

# Loose
h2_tau_pT_L = inputFile.Get(d_histName[era]["L"]).Clone()
h2_tau_pT_L.Sumw2()

# Tight
h2_tau_pT_T = inputFile.Get(d_histName[era]["T"]).Clone()
h2_tau_pT_T.Sumw2()


l_h1 = []

for iDM in range(0, len(l_DM)) :
    
    DM = l_DM[iDM]
    
    iBin = h2_tau_pT_L.GetXaxis().FindBin(DM)
    
    h1_tau_pT_L = h2_tau_pT_L.ProjectionY("_py", iBin, iBin)
    h1_tau_pT_L.Sumw2()
    h1_tau_pT_L = h1_tau_pT_L.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
    
    h1_tau_pT_T = h2_tau_pT_T.ProjectionY("_py", iBin, iBin)
    h1_tau_pT_T.Sumw2()
    h1_tau_pT_T = h1_tau_pT_T.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
    
    #
    h1_temp = h1_tau_pT_T.Clone()
    h1_temp.Divide(h1_tau_pT_L)
    h1_temp.SetLineColor(iDM+1)
    h1_temp.SetLineWidth(3)
    
    l_h1.append(h1_temp.Clone())
    stack.Add(l_h1[-1], "hist E")
    legend.AddEntry(l_h1[-1], "DM %d" %(DM))


stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("#tau_{h} p_{T} [GeV]")
stack.GetYaxis().SetTitle("#tau_{h} prompt rate")

stack.GetXaxis().SetLabelSize(0.05)
stack.GetYaxis().SetLabelSize(0.05)

stack.GetXaxis().SetTitleOffset(1.05)
stack.GetYaxis().SetTitleOffset(1.25)

stack.GetXaxis().SetTitleSize(0.055)
stack.GetYaxis().SetTitleSize(0.055)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

stack.GetXaxis().SetRangeUser(40, l_pTbin[-1])
stack.SetMinimum(0)
stack.SetMaximum(2)

stack.GetXaxis().SetNdivisions(5, 5, 1)

#canvas.SetGridx()
#canvas.SetGridy()

CMSextraText = "#scale[0.8]{%s}" %(Common.getCMSextraText(isSimOnly = True))

# CMS label
CMS_lumi.CMS_lumi(
    pad = canvas,
    iPeriod = 0,
    iPosX = 0,
    CMSextraText = CMSextraText,
    lumiText = Common.getLumitext(era)
)

canvas.SaveAs(outDir + "/tauPromptRate_pT.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()

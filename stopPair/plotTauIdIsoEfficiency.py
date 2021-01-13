import os

import ROOT
from ROOT import TCanvas
from ROOT import TFile
from ROOT import TH1F
from ROOT import TH2F
from ROOT import TLegend
from ROOT import THStack
from ROOT import TStyle




#outDir = "plots/tauIdIsoEfficiency/ttbar_mc"
#os.system("mkdir -p " + outDir)
#inputFile = TFile.Open("ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root")
#process = "TTJets"

outDir = "plots/tauIdIsoEfficiency/DYJetsToLL_mc"
os.system("mkdir -p " + outDir)
inputFile = TFile.Open("DYJetsToLL_mc/output_tauIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root")
process = "DYJetsToLL"

####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.5, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#tau^{gen}_{h} p_{T} fraction [%s]" %(process))

tauTemplate_pTbin = [20, 30, 50, 100]

for iBin in range(0, len(tauTemplate_pTbin)) :
    
    histName = ""
    histLabel = ""
    
    lineColor = iBin+1
    
    if (iBin < len(tauTemplate_pTbin)-1) :
        
        histName = "tauh_pTfraction_gen_pT-%dto%d" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
        histLabel = "%d < p^{#tau^{gen}}_{T} < %d GeV" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
    
    else :
        
        histName = "tauh_pTfraction_gen_pT-%d" %(tauTemplate_pTbin[iBin])
        histLabel = "p^{#tau^{gen}}_{T} > %d GeV" %(tauTemplate_pTbin[iBin])
    
    h1_tauh_pTfraction_gen = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    h1_tauh_pTfraction_gen.Sumw2()
    h1_tauh_pTfraction_gen.Scale(1.0/h1_tauh_pTfraction_gen.Integral())
    h1_tauh_pTfraction_gen.SetLineColor(lineColor)
    h1_tauh_pTfraction_gen.SetLineStyle(1)
    h1_tauh_pTfraction_gen.SetLineWidth(3)
    stack.Add(h1_tauh_pTfraction_gen, "hist")
    legend.AddEntry(h1_tauh_pTfraction_gen, "%s" %(histLabel))

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("p^{#tau^{gen}_{h}}_{T}/p^{#tau^{gen}}_{T}")
stack.GetYaxis().SetTitle("a.u.")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

#stack.SetMinimum(10**-3)
stack.SetMaximum(0.1)

canvas.SetGridx()
canvas.SetGridy()

#canvas.SetLogy()

canvas.SaveAs(outDir + "/tauh_pTfraction_gen.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()


####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.5, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#tau^{gen}_{h} E fraction [%s]" %(process))

tauTemplate_pTbin = [20, 30, 50, 100]

for iBin in range(0, len(tauTemplate_pTbin)) :
    
    histName = ""
    histLabel = ""
    
    lineColor = iBin+1
    
    if (iBin < len(tauTemplate_pTbin)-1) :
        
        histName = "tauh_Efraction_gen_pT-%dto%d" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
        histLabel = "%d < p^{#tau^{gen}}_{T} < %d GeV" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
    
    else :
        
        histName = "tauh_Efraction_gen_pT-%d" %(tauTemplate_pTbin[iBin])
        histLabel = "p^{#tau^{gen}}_{T} > %d GeV" %(tauTemplate_pTbin[iBin])
    
    h1_tauh_Efraction_gen = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    h1_tauh_Efraction_gen.Sumw2()
    h1_tauh_Efraction_gen.Scale(1.0/h1_tauh_Efraction_gen.Integral())
    h1_tauh_Efraction_gen.SetLineColor(lineColor)
    h1_tauh_Efraction_gen.SetLineStyle(1)
    h1_tauh_Efraction_gen.SetLineWidth(3)
    stack.Add(h1_tauh_Efraction_gen, "hist")
    legend.AddEntry(h1_tauh_Efraction_gen, "%s" %(histLabel))

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("E^{#tau^{gen}_{h}}/E^{#tau^{gen}}")
stack.GetYaxis().SetTitle("a.u.")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

#stack.SetMinimum(10**-3)
stack.SetMaximum(0.1)

canvas.SetGridx()
canvas.SetGridy()

#canvas.SetLogy()

canvas.SaveAs(outDir + "/tauh_Efraction_gen.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()


####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.55, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#tau_{h} efficiency [MVArun2v1DBoldDMwLT] [%s]" %(process))

h1_tau_vis_pT_gen = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_vis_pT_gen").Clone()
h1_tau_vis_pT_gen.Sumw2()

# Loose
h1_tau_genMatched_pT_reco_loose = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_reco").Clone()
h1_tau_genMatched_pT_reco_loose.Sumw2()
h1_tau_genMatched_pT_reco_loose.Divide(h1_tau_vis_pT_gen)
h1_tau_genMatched_pT_reco_loose.SetLineColor(2)
h1_tau_genMatched_pT_reco_loose.SetLineWidth(2)
stack.Add(h1_tau_genMatched_pT_reco_loose, "hist E")
legend.AddEntry(h1_tau_genMatched_pT_reco_loose, "dR03 Loose")

h1_tau_genMatched_pT_reco_loose = inputFile.Get("LooseIsolationMVArun2v1DBoldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_reco").Clone()
h1_tau_genMatched_pT_reco_loose.Sumw2()
h1_tau_genMatched_pT_reco_loose.Divide(h1_tau_vis_pT_gen)
h1_tau_genMatched_pT_reco_loose.SetLineColor(2)
h1_tau_genMatched_pT_reco_loose.SetLineWidth(2)
h1_tau_genMatched_pT_reco_loose.SetLineStyle(2)
stack.Add(h1_tau_genMatched_pT_reco_loose, "hist E")
legend.AddEntry(h1_tau_genMatched_pT_reco_loose, "dR05 Loose")

# Medium
h1_tau_genMatched_pT_reco_medium = inputFile.Get("MediumIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_reco").Clone()
h1_tau_genMatched_pT_reco_medium.Sumw2()
h1_tau_genMatched_pT_reco_medium.Divide(h1_tau_vis_pT_gen)
h1_tau_genMatched_pT_reco_medium.SetLineColor(4)
h1_tau_genMatched_pT_reco_medium.SetLineWidth(2)
stack.Add(h1_tau_genMatched_pT_reco_medium, "hist E")
legend.AddEntry(h1_tau_genMatched_pT_reco_medium, "dR03 Medium")

h1_tau_genMatched_pT_reco_medium = inputFile.Get("MediumIsolationMVArun2v1DBoldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_reco").Clone()
h1_tau_genMatched_pT_reco_medium.Sumw2()
h1_tau_genMatched_pT_reco_medium.Divide(h1_tau_vis_pT_gen)
h1_tau_genMatched_pT_reco_medium.SetLineColor(4)
h1_tau_genMatched_pT_reco_medium.SetLineWidth(2)
h1_tau_genMatched_pT_reco_medium.SetLineStyle(2)
stack.Add(h1_tau_genMatched_pT_reco_medium, "hist E")
legend.AddEntry(h1_tau_genMatched_pT_reco_medium, "dR05 Medium")

# Tight
h1_tau_genMatched_pT_reco_tight = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_reco").Clone()
h1_tau_genMatched_pT_reco_tight.Sumw2()
h1_tau_genMatched_pT_reco_tight.Divide(h1_tau_vis_pT_gen)
h1_tau_genMatched_pT_reco_tight.SetLineColor(6)
h1_tau_genMatched_pT_reco_tight.SetLineWidth(2)
stack.Add(h1_tau_genMatched_pT_reco_tight, "hist E")
legend.AddEntry(h1_tau_genMatched_pT_reco_tight, "dR03 Tight")

h1_tau_genMatched_pT_reco_tight = inputFile.Get("TightIsolationMVArun2v1DBoldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_reco").Clone()
h1_tau_genMatched_pT_reco_tight.Sumw2()
h1_tau_genMatched_pT_reco_tight.Divide(h1_tau_vis_pT_gen)
h1_tau_genMatched_pT_reco_tight.SetLineColor(6)
h1_tau_genMatched_pT_reco_tight.SetLineWidth(2)
h1_tau_genMatched_pT_reco_tight.SetLineStyle(2)
stack.Add(h1_tau_genMatched_pT_reco_tight, "hist E")
legend.AddEntry(h1_tau_genMatched_pT_reco_tight, "dR05 Tight")

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("p^{#tau^{gen}_{h}}_{T} [GeV]")
stack.GetYaxis().SetTitle("efficiency")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

stack.GetXaxis().SetRangeUser(0, 150)
stack.SetMinimum(0)
stack.SetMaximum(1)

canvas.SetGridx()
canvas.SetGridy()

canvas.SaveAs(outDir + "/tauIdIsoEfficiency_pT.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()


####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.55, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#tau_{h} efficiency [MVArun2v1DBoldDMwLT] [%s]" %(process))

h1_tau_vis_eta_gen = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_vis_eta_gen").Clone()
h1_tau_vis_eta_gen.Sumw2()

# Loose
h1_tau_genMatched_eta_reco_loose = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_eta_reco").Clone()
h1_tau_genMatched_eta_reco_loose.Sumw2()
h1_tau_genMatched_eta_reco_loose.Divide(h1_tau_vis_eta_gen)
h1_tau_genMatched_eta_reco_loose.SetLineColor(2)
h1_tau_genMatched_eta_reco_loose.SetLineWidth(2)
stack.Add(h1_tau_genMatched_eta_reco_loose, "hist E")
legend.AddEntry(h1_tau_genMatched_eta_reco_loose, "dR03 Loose")

h1_tau_genMatched_eta_reco_loose = inputFile.Get("LooseIsolationMVArun2v1DBoldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_eta_reco").Clone()
h1_tau_genMatched_eta_reco_loose.Sumw2()
h1_tau_genMatched_eta_reco_loose.Divide(h1_tau_vis_eta_gen)
h1_tau_genMatched_eta_reco_loose.SetLineColor(2)
h1_tau_genMatched_eta_reco_loose.SetLineWidth(2)
h1_tau_genMatched_eta_reco_loose.SetLineStyle(2)
stack.Add(h1_tau_genMatched_eta_reco_loose, "hist E")
legend.AddEntry(h1_tau_genMatched_eta_reco_loose, "dR05 Loose")

# Medium
h1_tau_genMatched_eta_reco_medium = inputFile.Get("MediumIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_eta_reco").Clone()
h1_tau_genMatched_eta_reco_medium.Sumw2()
h1_tau_genMatched_eta_reco_medium.Divide(h1_tau_vis_eta_gen)
h1_tau_genMatched_eta_reco_medium.SetLineColor(4)
h1_tau_genMatched_eta_reco_medium.SetLineWidth(2)
stack.Add(h1_tau_genMatched_eta_reco_medium, "hist E")
legend.AddEntry(h1_tau_genMatched_eta_reco_medium, "dR03 Medium")

h1_tau_genMatched_eta_reco_medium = inputFile.Get("MediumIsolationMVArun2v1DBoldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_eta_reco").Clone()
h1_tau_genMatched_eta_reco_medium.Sumw2()
h1_tau_genMatched_eta_reco_medium.Divide(h1_tau_vis_eta_gen)
h1_tau_genMatched_eta_reco_medium.SetLineColor(4)
h1_tau_genMatched_eta_reco_medium.SetLineWidth(2)
h1_tau_genMatched_eta_reco_medium.SetLineStyle(2)
stack.Add(h1_tau_genMatched_eta_reco_medium, "hist E")
legend.AddEntry(h1_tau_genMatched_eta_reco_medium, "dR05 Medium")

# Tight
h1_tau_genMatched_eta_reco_tight = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_eta_reco").Clone()
h1_tau_genMatched_eta_reco_tight.Sumw2()
h1_tau_genMatched_eta_reco_tight.Divide(h1_tau_vis_eta_gen)
h1_tau_genMatched_eta_reco_tight.SetLineColor(6)
h1_tau_genMatched_eta_reco_tight.SetLineWidth(2)
stack.Add(h1_tau_genMatched_eta_reco_tight, "hist E")
legend.AddEntry(h1_tau_genMatched_eta_reco_tight, "dR03 Tight")

h1_tau_genMatched_eta_reco_tight = inputFile.Get("TightIsolationMVArun2v1DBoldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_eta_reco").Clone()
h1_tau_genMatched_eta_reco_tight.Sumw2()
h1_tau_genMatched_eta_reco_tight.Divide(h1_tau_vis_eta_gen)
h1_tau_genMatched_eta_reco_tight.SetLineColor(6)
h1_tau_genMatched_eta_reco_tight.SetLineWidth(2)
h1_tau_genMatched_eta_reco_tight.SetLineStyle(2)
stack.Add(h1_tau_genMatched_eta_reco_tight, "hist E")
legend.AddEntry(h1_tau_genMatched_eta_reco_tight, "dR05 Tight")

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("#eta^{#tau^{gen}_{h}}")
stack.GetYaxis().SetTitle("efficiency")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

stack.GetXaxis().SetRangeUser(-3, 3)
stack.SetMinimum(0)
stack.SetMaximum(1)

canvas.SetGridx()
canvas.SetGridy()

canvas.SaveAs(outDir + "/tauIdIsoEfficiency_eta.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()


####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.55, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("di-#tau invariant mass [%s]" %(process))

h1_tauTau_m_gen = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tauTau_m_gen").Clone()
h1_tauTau_m_gen.Sumw2()
h1_tauTau_m_gen.Scale(1.0 / h1_tauTau_m_gen.Integral())
h1_tauTau_m_gen.SetLineColor(1)
h1_tauTau_m_gen.SetLineWidth(2)
stack.Add(h1_tauTau_m_gen, "hist")
legend.AddEntry(h1_tauTau_m_gen, "di-#tau^{gen}")

h1_tauhTauh_m_gen = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tauhTauh_m_gen").Clone()
h1_tauhTauh_m_gen.Sumw2()
h1_tauhTauh_m_gen.Scale(1.0 / h1_tauhTauh_m_gen.Integral())
h1_tauhTauh_m_gen.SetLineColor(2)
h1_tauhTauh_m_gen.SetLineWidth(2)
stack.Add(h1_tauhTauh_m_gen, "hist")
legend.AddEntry(h1_tauhTauh_m_gen, "di-#tau^{gen}_{h}")

h1_tauTau_m_reco_tight = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tauTau_m_reco").Clone()
h1_tauTau_m_reco_tight.Sumw2()
h1_tauTau_m_reco_tight.Scale(1.0 / h1_tauTau_m_reco_tight.Integral())
h1_tauTau_m_reco_tight.SetLineColor(3)
h1_tauTau_m_reco_tight.SetLineWidth(2)
stack.Add(h1_tauTau_m_reco_tight, "hist")
legend.AddEntry(h1_tauTau_m_reco_tight, "di-#tau^{reco}_{h} [dR03 Tight]")


stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("di-#tau invariant mass [GeV]")
stack.GetYaxis().SetTitle("a.u.")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

stack.GetXaxis().SetRangeUser(0, 500)

#stack.SetMinimum(0)
#stack.SetMaximum(1)

canvas.SetGridx()
canvas.SetGridy()

canvas.SaveAs(outDir + "/tauTau_m.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()


####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.5, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#tau_{h} p_{T} response [MVArun2v1DBdR03oldDMwLT] [%s]" %(process))

tauTemplate_pTbin = [20, 30, 50, 100]

for iBin in range(0, len(tauTemplate_pTbin)) :
    
    histName = ""
    histLabel = ""
    
    lineColor = iBin+1
    
    if (iBin < len(tauTemplate_pTbin)-1) :
        
        histName = "tauh_response_pT-%dto%d" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
        histLabel = "%d < p^{#tau^{gen}}_{T} < %d GeV" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
    
    else :
        
        histName = "tauh_response_pT-%d" %(tauTemplate_pTbin[iBin])
        histLabel = "p^{#tau^{gen}}_{T} > %d GeV" %(tauTemplate_pTbin[iBin])
    
    ## Loose
    #h1_tauh_response_loose = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    #h1_tauh_response_loose.Sumw2()
    #h1_tauh_response_loose.Scale(1.0/h1_tauh_response_loose.Integral())
    #h1_tauh_response_loose.SetLineColor(lineColor)
    #h1_tauh_response_loose.SetLineStyle(3)
    #h1_tauh_response_loose.SetLineWidth(3)
    #stack.Add(h1_tauh_response_loose, "hist")
    #legend.AddEntry(h1_tauh_response_loose, "Loose [%s]" %(histLabel))
    #
    ## Medium
    #h1_tauh_response_medium = inputFile.Get("MediumIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    #h1_tauh_response_medium.Sumw2()
    #h1_tauh_response_medium.Scale(1.0/h1_tauh_response_medium.Integral() * 10)
    #h1_tauh_response_medium.SetLineColor(lineColor)
    #h1_tauh_response_medium.SetLineStyle(2)
    #h1_tauh_response_medium.SetLineWidth(3)
    #stack.Add(h1_tauh_response_medium, "hist")
    #legend.AddEntry(h1_tauh_response_medium, "Medium [%s] #times 10" %(histLabel))
    
    # Tight
    h1_tauh_response_tight = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    h1_tauh_response_tight.Sumw2()
    h1_tauh_response_tight.AddBinContent(1, h1_tauh_response_tight.GetBinContent(0))
    h1_tauh_response_tight.Scale(1.0/h1_tauh_response_tight.Integral())
    h1_tauh_response_tight.SetLineColor(lineColor)
    h1_tauh_response_tight.SetLineStyle(1)
    h1_tauh_response_tight.SetLineWidth(3)
    stack.Add(h1_tauh_response_tight, "hist")
    legend.AddEntry(h1_tauh_response_tight, "Tight [%s]" %(histLabel))

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("p^{#tau^{reco}_{h}}_{T}/p^{#tau^{gen}}_{T}")
stack.GetYaxis().SetTitle("a.u.")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

stack.SetMinimum(10**-3)
#stack.SetMaximum(0.16)
stack.SetMaximum(1)

canvas.SetGridx()
canvas.SetGridy()

canvas.SetLogy()

canvas.SaveAs(outDir + "/tauh_response_dR03.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()


####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.5, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#tau_{h} p_{T} resolution [MVArun2v1DBdR03oldDMwLT] [%s]" %(process))

tauTemplate_pTbin = [20, 30, 50, 100]

for iBin in range(0, len(tauTemplate_pTbin)) :
    
    histName = ""
    histLabel = ""
    
    lineColor = iBin+1
    
    if (iBin < len(tauTemplate_pTbin)-1) :
        
        histName = "tauh_resolution_pT-%dto%d" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
        histLabel = "%d < p^{#tau^{gen}_{h}}_{T} < %d GeV" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
    
    else :
        
        histName = "tauh_resolution_pT-%d" %(tauTemplate_pTbin[iBin])
        histLabel = "p^{#tau^{gen}_{h}}_{T} > %d GeV" %(tauTemplate_pTbin[iBin])
    
    ## Loose
    #h1_tauh_resolution_loose = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    #h1_tauh_resolution_loose.Sumw2()
    #h1_tauh_resolution_loose.Scale(1.0/h1_tauh_resolution_loose.Integral())
    #h1_tauh_resolution_loose.SetLineColor(lineColor)
    #h1_tauh_resolution_loose.SetLineStyle(3)
    #h1_tauh_resolution_loose.SetLineWidth(3)
    #stack.Add(h1_tauh_resolution_loose, "hist")
    #legend.AddEntry(h1_tauh_resolution_loose, "Loose [%s]" %(histLabel))
    #
    ## Medium
    #h1_tauh_resolution_medium = inputFile.Get("MediumIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    #h1_tauh_resolution_medium.Sumw2()
    #h1_tauh_resolution_medium.Scale(1.0/h1_tauh_resolution_medium.Integral() * 10)
    #h1_tauh_resolution_medium.SetLineColor(lineColor)
    #h1_tauh_resolution_medium.SetLineStyle(2)
    #h1_tauh_resolution_medium.SetLineWidth(3)
    #stack.Add(h1_tauh_resolution_medium, "hist")
    #legend.AddEntry(h1_tauh_resolution_medium, "Medium [%s] #times 10" %(histLabel))
    
    # Tight
    h1_tauh_resolution_tight = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    h1_tauh_resolution_tight.Sumw2()
    h1_tauh_resolution_tight.Scale(1.0/h1_tauh_resolution_tight.Integral())
    h1_tauh_resolution_tight.SetLineColor(lineColor)
    h1_tauh_resolution_tight.SetLineStyle(1)
    h1_tauh_resolution_tight.SetLineWidth(3)
    stack.Add(h1_tauh_resolution_tight, "hist")
    legend.AddEntry(h1_tauh_resolution_tight, "Tight [%s]" %(histLabel))

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("p^{#tau^{reco}_{h}}_{T}/p^{#tau^{gen}_{h}}_{T}")
stack.GetYaxis().SetTitle("a.u.")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

#stack.SetMinimum(10**-3)
stack.SetMaximum(0.4)

canvas.SetGridx()
canvas.SetGridy()

#canvas.SetLogy()

canvas.SaveAs(outDir + "/tauh_resolution_dR03.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()



####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.5, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#DeltaR(#tau^{reco}_{h}, #tau^{gen}_{h}) [MVArun2v1DBdR03oldDMwLT] [%s]" %(process))

histName = "tau_nearestGen_deltaR"

# Loose
h1_tauh_nearestGenh_deltaR_loose = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
h1_tauh_nearestGenh_deltaR_loose.Sumw2()
h1_tauh_nearestGenh_deltaR_loose.Scale(1.0/h1_tauh_nearestGenh_deltaR_loose.Integral())
h1_tauh_nearestGenh_deltaR_loose.SetLineColor(1)
h1_tauh_nearestGenh_deltaR_loose.SetLineWidth(3)
stack.Add(h1_tauh_nearestGenh_deltaR_loose, "hist")
legend.AddEntry(h1_tauh_nearestGenh_deltaR_loose, "Loose")

# Medium
h1_tauh_nearestGenh_deltaR_medium = inputFile.Get("MediumIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
h1_tauh_nearestGenh_deltaR_medium.Sumw2()
h1_tauh_nearestGenh_deltaR_medium.Scale(1.0/h1_tauh_nearestGenh_deltaR_medium.Integral())
h1_tauh_nearestGenh_deltaR_medium.SetLineColor(2)
h1_tauh_nearestGenh_deltaR_medium.SetLineWidth(3)
stack.Add(h1_tauh_nearestGenh_deltaR_medium, "hist")
legend.AddEntry(h1_tauh_nearestGenh_deltaR_medium, "Medium")

# Tight
h1_tauh_nearestGenh_deltaR_tight = inputFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
h1_tauh_nearestGenh_deltaR_tight.Sumw2()
h1_tauh_nearestGenh_deltaR_tight.Scale(1.0/h1_tauh_nearestGenh_deltaR_tight.Integral())
h1_tauh_nearestGenh_deltaR_tight.SetLineColor(3)
h1_tauh_nearestGenh_deltaR_tight.SetLineWidth(3)
stack.Add(h1_tauh_nearestGenh_deltaR_tight, "hist")
legend.AddEntry(h1_tauh_nearestGenh_deltaR_tight, "Tight")

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("#DeltaR(#tau^{reco}_{h}, #tau^{gen}_{h})")
stack.GetYaxis().SetTitle("a.u.")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

stack.GetXaxis().SetRangeUser(0, 1)

stack.SetMinimum(10**-6)
stack.SetMaximum(1)

canvas.SetGridx()
canvas.SetGridy()

canvas.SetLogy()

canvas.SaveAs(outDir + "/tauh_nearestGenh_deltaR.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()



####################################################################################################

canvas = TCanvas("canvas", "canvas")
canvas.SetCanvasSize(800, 800)

legend = TLegend(0.55, 0.5, 0.895, 0.895)

stack = THStack("stack", "stack")
stack.SetTitle("#tau_{h} p_{T} response with AK4 jets [%s]" %(process))

tauTemplate_pTbin = [20, 30, 50, 100]

for iBin in range(0, len(tauTemplate_pTbin)) :
    
    histName = ""
    histLabel = ""
    
    lineColor = iBin+1
    
    if (iBin < len(tauTemplate_pTbin)-1) :
        
        histName = "tauh_jetResponse_pT-%dto%d" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
        histLabel = "%d < p^{#tau^{gen}}_{T} < %d GeV" %(tauTemplate_pTbin[iBin], tauTemplate_pTbin[iBin+1])
    
    else :
        
        histName = "tauh_jetResponse_pT-%d" %(tauTemplate_pTbin[iBin])
        histLabel = "p^{#tau^{gen}}_{T} > %d GeV" %(tauTemplate_pTbin[iBin])
    
    # Loose
    h1_tauh_resolution_loose = inputFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/%s" %(histName)).Clone()
    h1_tauh_resolution_loose.Sumw2()
    h1_tauh_resolution_loose.Scale(1.0/h1_tauh_resolution_loose.Integral())
    h1_tauh_resolution_loose.SetLineColor(lineColor)
    h1_tauh_resolution_loose.SetLineStyle(1)
    h1_tauh_resolution_loose.SetLineWidth(3)
    stack.Add(h1_tauh_resolution_loose, "hist")
    legend.AddEntry(h1_tauh_resolution_loose, histLabel)

stack.Draw("nostack")
legend.Draw()

stack.GetXaxis().SetTitle("p^{jet}_{T}/p^{#tau^{gen}}_{T}")
stack.GetYaxis().SetTitle("a.u.")

stack.GetXaxis().SetTitleOffset(1.15)
stack.GetYaxis().SetTitleOffset(1.15)

stack.GetXaxis().CenterTitle(True)
stack.GetYaxis().CenterTitle(True)

#stack.SetMinimum(10**-3)
stack.SetMaximum(0.07)

canvas.SetGridx()
canvas.SetGridy()

#canvas.SetLogy()

canvas.SaveAs(outDir + "/tauh_jetResponse.pdf")

canvas.Clear()
legend.Clear()
stack.Clear()


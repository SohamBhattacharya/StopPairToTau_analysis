import array
import time

import ROOT


l_pTbin = [0, 40, 80, 150, 500]


inFileName = "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root"
#inFileName = "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency_withPromptElMu-withExclusiveElMuMatching-withTauPairSelection-withMETcutForTauFakeComposition/custom_all_tauIdIsoEfficiency.root"

inFile = ROOT.TFile(inFileName)


h1_tau_genNotMatched_pT_reco_L              = inFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genNotMatched_pT_reco")
h1_tau_genNotMatched_gelElMatched_pT_reco_L = inFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genNotMatched_genElMatched_pT_reco")
h1_tau_genNotMatched_gelMuMatched_pT_reco_L = inFile.Get("LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genNotMatched_genMuMatched_pT_reco")

h1_tau_genNotMatched_pT_reco_T              = inFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genNotMatched_pT_reco")
h1_tau_genNotMatched_gelElMatched_pT_reco_T = inFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genNotMatched_genElMatched_pT_reco")
h1_tau_genNotMatched_gelMuMatched_pT_reco_T = inFile.Get("TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genNotMatched_genMuMatched_pT_reco")


h1_tau_genNotMatched_pT_reco_L.Sumw2()
h1_tau_genNotMatched_gelElMatched_pT_reco_L.Sumw2()
h1_tau_genNotMatched_gelMuMatched_pT_reco_L.Sumw2()

h1_tau_genNotMatched_pT_reco_T.Sumw2()
h1_tau_genNotMatched_gelElMatched_pT_reco_T.Sumw2()
h1_tau_genNotMatched_gelMuMatched_pT_reco_T.Sumw2()


h1_tau_genNotMatched_pT_reco_L              = h1_tau_genNotMatched_pT_reco_L.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
h1_tau_genNotMatched_gelElMatched_pT_reco_L = h1_tau_genNotMatched_gelElMatched_pT_reco_L.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
h1_tau_genNotMatched_gelMuMatched_pT_reco_L = h1_tau_genNotMatched_gelMuMatched_pT_reco_L.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))

h1_tau_genNotMatched_pT_reco_T              = h1_tau_genNotMatched_pT_reco_T.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
h1_tau_genNotMatched_gelElMatched_pT_reco_T = h1_tau_genNotMatched_gelElMatched_pT_reco_T.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))
h1_tau_genNotMatched_gelMuMatched_pT_reco_T = h1_tau_genNotMatched_gelMuMatched_pT_reco_T.Rebin(len(l_pTbin)-1, "", array.array("d", l_pTbin))


h1_tau_genNotMatched_gelLepMatched_pT_reco_L = h1_tau_genNotMatched_gelElMatched_pT_reco_L.Clone()
h1_tau_genNotMatched_gelLepMatched_pT_reco_L.Add(h1_tau_genNotMatched_gelMuMatched_pT_reco_L)

h1_tau_genNotMatched_gelLepMatched_pT_reco_T = h1_tau_genNotMatched_gelElMatched_pT_reco_T.Clone()
h1_tau_genNotMatched_gelLepMatched_pT_reco_T.Add(h1_tau_genNotMatched_gelMuMatched_pT_reco_T)

h1_tau_genNotMatched_gelHadMatched_pT_reco_L = h1_tau_genNotMatched_pT_reco_L.Clone()
h1_tau_genNotMatched_gelHadMatched_pT_reco_L.Add(h1_tau_genNotMatched_gelLepMatched_pT_reco_L, -1)

h1_tau_genNotMatched_gelHadMatched_pT_reco_T = h1_tau_genNotMatched_pT_reco_T.Clone()
h1_tau_genNotMatched_gelHadMatched_pT_reco_T.Add(h1_tau_genNotMatched_gelLepMatched_pT_reco_T, -1)


h1_tau_fakeRate_lep = h1_tau_genNotMatched_gelLepMatched_pT_reco_T.Clone()
h1_tau_fakeRate_lep.Divide(h1_tau_genNotMatched_gelLepMatched_pT_reco_L)
h1_tau_fakeRate_lep.SetLineWidth(2)
h1_tau_fakeRate_lep.SetLineColor(2)


h1_tau_fakeRate_had = h1_tau_genNotMatched_gelHadMatched_pT_reco_T.Clone()
h1_tau_fakeRate_had.Divide(h1_tau_genNotMatched_gelHadMatched_pT_reco_L)
h1_tau_fakeRate_had.SetLineWidth(2)
h1_tau_fakeRate_had.SetLineColor(4)


canvas = ROOT.TCanvas()
canvas.cd()


stack = ROOT.THStack("stack", "stack")


stack.Add(h1_tau_fakeRate_lep, "E1")
#stack.Add(h1_tau_fakeRate_had, "E1")

stack.Draw("nostack")

stack.SetMinimum(0)
stack.SetMaximum(1)

time.sleep(10000)

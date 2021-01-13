# include "TMVA_treeContent_tauTau.h"


namespace TMVA_treeContent_tauTau
{
    Info::Info(const char *fileName, const char *treeName)
    {
        file = TFile::Open(fileName, "RECREATE");
        
        tree = new TTree(treeName, treeName);
        
        linkBranch();
    }
    
    
    void Info::linkBranch()
    {
        tree->Branch("tau1_pT", &tau1_pT);
        tree->Branch("tau1_eta", &tau1_eta);
        
        tree->Branch("tau2_pT", &tau2_pT);
        tree->Branch("tau2_eta", &tau2_eta);
        
        tree->Branch("tauTau_m", &tauTau_m);
        
        tree->Branch("MET_E", &MET_E);
        tree->Branch("MET_phi", &MET_phi);
        
        tree->Branch("tauTau_MET_mT2_lsp0", &tauTau_MET_mT2_lsp0);
        tree->Branch("tauBtauB_MET_mT2_lsp0", &tauBtauB_MET_mT2_lsp0);
        tree->Branch("tauBtauB_MET_mT2_lsp0_mod1", &tauBtauB_MET_mT2_lsp0_mod1);
        tree->Branch("tauTau_MET_Dzeta", &tauTau_MET_Dzeta);
        
        tree->Branch("tauTau_jet_HT", &tauTau_jet_HT);
        tree->Branch("tauTau_jet_MHT", &tauTau_jet_MHT);
        
        tree->Branch("nonBjet_n", &nonBjet_n);
        
        tree->Branch("b_n", &b_n);
        
        tree->Branch("b1_pT", &b1_pT);
        tree->Branch("b1_eta", &b1_eta);
        
        tree->Branch("bb_MET_mT2_lsp0", &bb_MET_mT2_lsp0);
        
        tree->Branch("tau1_b1_deltaPhi", &tau1_b1_deltaPhi);
    }
    
    
    void Info::clear()
    {
        tau1_pT = 0;
        tau1_eta = 0;
        
        tau2_pT = 0;
        tau2_eta = 0;
        
        tauTau_m = 0;
        
        MET_E = 0;
        MET_phi = 0;
        
        tauTau_MET_mT2_lsp0 = 0;
        tauBtauB_MET_mT2_lsp0 = 0;
        tauBtauB_MET_mT2_lsp0_mod1 = 0;
        tauTau_MET_Dzeta = 0;
        
        tauTau_jet_HT = 0;
        tauTau_jet_MHT = 0;
        
        nonBjet_n = 0;
        
        b_n = 0;
        
        b1_pT = 0;
        b1_eta = 0;
        
        bb_MET_mT2_lsp0 = 0;
        
        tau1_b1_deltaPhi = 0;
    }
    
    
    void Info::fillTree()
    {
        tree->Fill();
    }
    
    
    void Info::freeMemory()
    {
        delete tree;
        delete file;
    }
    
    
    void Info::writeData()
    {
        file->cd();
        
        tree->Write();
    }
}

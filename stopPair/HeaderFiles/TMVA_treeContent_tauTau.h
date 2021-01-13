# ifndef TMVA_treeContent_tauTau_H
# define TMVA_treeContent_tauTau_H


# include <iostream>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTree.h>

# include "Common.h"


namespace TMVA_treeContent_tauTau
{
    class Info
    {
        public:
        
        
        double tau1_pT;
        double tau1_eta;
        
        double tau2_pT;
        double tau2_eta;
        
        double tauTau_m;
        
        double MET_E;
        double MET_phi;
        
        double tauTau_MET_mT2_lsp0;
        double tauBtauB_MET_mT2_lsp0;
        double tauBtauB_MET_mT2_lsp0_mod1;
        double tauTau_MET_Dzeta;
        
        double tauTau_jet_HT;
        double tauTau_jet_MHT;
        
        double nonBjet_n;
        
        double b_n;
        
        double b1_pT;
        double b1_eta;
        
        double bb_MET_mT2_lsp0;
        
        double tau1_b1_deltaPhi;
        
        TFile *file;
        TTree *tree;
        
        
        Info(const char *fileName, const char *treeName);
        
        void linkBranch();
        
        void clear();
        
        void fillTree();
        
        void freeMemory();
        
        void writeData();
    };
}


# endif

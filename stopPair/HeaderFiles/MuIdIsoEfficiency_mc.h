# ifndef MuIdIsoEfficiency_mc_H
# define MuIdIsoEfficiency_mc_H


# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <utility>
# include <vector>

# include "TFile.h"
# include "TH1F.h"
# include "TH2F.h"
# include "TTree.h"

# include "Common.h"
# include "CustomInfo_mc.h"


namespace MuIdIsoEfficiency_mc
{
    class Output
    {
        public :
        
        
        std::vector <double> v_bin_pT;
        std::vector <double> v_bin_eta;
        
        std::vector <int> v_template_pTbin;
        
        
        TH1F *h1_mu_pT_gen;
        TH1F *h1_mu_eta_gen;
        TH2F *h2_mu_pT_vs_eta_gen;
        
        TH1F *h1_muMu_m_gen;
        
        TH1F *h1_mu_genMatched_pT_reco;
        TH1F *h1_mu_genMatched_eta_reco;
        TH2F *h2_mu_genMatched_pT_vs_eta_reco;
        
        TH1F *h1_mu_nearestGen_deltaR;
        
        TH1F *h1_muMu_m_reco;
        
        
        Output();
        
        void writeData();
        void freeMemory();
    };
    
    
    void run(
        std::string process,
        std::string dir,
        std::string sourceFileName
    );
    
    
    void analyze(
        CustomInfo_mc::Info *input,
        Output *output,
        double mu_pTcut_gen, double mu_etaCut_gen,
        double mu_pTcut_reco, double mu_etaCut_reco,
        double mu_dxyCut_reco, std::vector <double> *v_mu_dxy_reco,
        double mu_dzCut_reco, std::vector <double> *v_mu_dz_reco,
        std::string mu_WPoption, std::vector <double> *v_mu_WP,
        std::string mu_isoOption, std::vector <double> *v_mu_isolation,
        double deltaRcut
    );
}


# endif

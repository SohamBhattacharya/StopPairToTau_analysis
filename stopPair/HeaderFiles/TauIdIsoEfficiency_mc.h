# ifndef TauIdIsoEfficiency_mc_H
# define TauIdIsoEfficiency_mc_H


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


namespace TauIdIsoEfficiency_mc
{
    class Output
    {
        public :
        
        
        std::vector <double> v_bin_pT;
        std::vector <double> v_bin_eta;
        
        std::vector <int> v_template_pTbin;
        std::vector <int> v_template_pxyBin;
        
        std::vector <double> v_template_responseBin;
        
        
        TH1F *h1_tau_vis_pT_gen;
        TH1F *h1_tau_vis_eta_gen;
        TH2F *h2_tau_vis_pT_vs_eta_gen;
        
        
        TH1F *h1_tauTau_m_gen;
        TH1F *h1_tauhTauh_m_gen;
        
        
        TH1F *h1_tau_all_pT_reco;
        TH1F *h1_tau_all_eta_reco;
        TH2F *h2_tau_all_pT_vs_eta_reco;
        
        TH2F *h2_tau_all_pT_vs_DM_reco;
        
        TH1F *h1_tau_pT_reco;
        TH1F *h1_tau_eta_reco;
        TH2F *h2_tau_pT_vs_eta_reco;
        
        TH2F *h2_tau_pT_vs_DM_reco;
        
        TH1F *h1_tau_genMatched_pT_reco;
        TH1F *h1_tau_genMatched_eta_reco;
        TH2F *h2_tau_genMatched_pT_vs_eta_reco;
        
        
        TH1F *h1_tau_genNotMatched_n_reco;
        TH1F *h1_tau_genNotMatched_pT_reco;
        TH1F *h1_tau_genNotMatched_eta_reco;
        TH2F *h2_tau_genNotMatched_pT_vs_eta_reco;
        
        TH1F *h1_tau_genNotMatched_genElMatched_n_reco;
        TH1F *h1_tau_genNotMatched_genElMatched_pT_reco;
        TH1F *h1_tau_genNotMatched_genElMatched_eta_reco;
        TH2F *h2_tau_genNotMatched_genElMatched_pT_vs_eta_reco;
        
        TH1F *h1_tau_genNotMatched_genMuMatched_n_reco;
        TH1F *h1_tau_genNotMatched_genMuMatched_pT_reco;
        TH1F *h1_tau_genNotMatched_genMuMatched_eta_reco;
        TH2F *h2_tau_genNotMatched_genMuMatched_pT_vs_eta_reco;
        
        TH1F *h1_tau_genNotMatched_genBmatched_n_reco;
        TH1F *h1_tau_genNotMatched_genBmatched_pT_reco;
        TH1F *h1_tau_genNotMatched_genBmatched_eta_reco;
        TH2F *h2_tau_genNotMatched_genBmatched_pT_vs_eta_reco;
        
        
        TH1F *h1_tau_nearestGen_deltaR;
        
        TH1F *h1_tauTau_m_reco;
        
        std::vector <TH1F*> v_h1_tauh_pTfraction_gen_pTbin;
        std::vector <TH1F*> v_h1_tauh_Efraction_gen_pTbin;
        
        std::vector <TH1F*> v_h1_tauh_resolution_pTbin;
        
        //
        std::vector <TH1F*> v_h1_tauh_response_pTbin;
        
        std::vector <TH1F*> v_h1_tauh_response_posPxBin;
        std::vector <TH1F*> v_h1_tauh_response_negPxBin;
        
        std::vector <TH1F*> v_h1_tauh_response_posPyBin;
        std::vector <TH1F*> v_h1_tauh_response_negPyBin;
        
        //
        TH1F *h1_jet_nearestGen_deltaR;
        
        std::vector <TH1F*> v_h1_tauh_jetResolution_pTbin;
        std::vector <TH1F*> v_h1_tauh_jetResponse_pTbin;
        
        
        Output();
        
        void writeData();
        void freeMemory();
    };
    
    
    void run(
        std::string process,
        std::string dir,
        std::string sourceFileName,
        std::string era
    );
    
    
    void analyze(
        CustomInfo_mc::Info *input,
        Output *output,
        double tau_pTcut_gen, double tau_etaCut_gen,
        double tau_pTcut_reco, double tau_etaCut_reco,
        double tau_dzCut_reco, std::vector <double> *v_tau_dz_reco,
        std::string tau_isoOption, std::vector <double> *v_tau_isolation,
        std::string tau_antiElOption, std::vector <double> *v_tau_antiElectron,
        std::string tau_antiMuOption, std::vector <double> *v_tau_antiMuon,
        double deltaRcut,
        bool isDeepTau
    );
}


# endif

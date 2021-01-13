# ifndef Output_GEN_H
# define Output_GEN_H


namespace Output_GEN
{
    class Output
    {
        public:
        
        
        char *nameAddon, \
            *titleAddon;
        
        
        bool \
            output_el, \
            output_mu, \
            output_tau, \
            output_tau_vis, \
            
            output_t, \
            output_b, \
            
            output_W, \
            output_Z, \
            
            output_stau1, \
            output_stop1, \
            output_chargino1, \
            
            output_jet, \
            output_MET;
        
        // el
        TH1F \
            *h1_el_n, \
            *h1_lep1_el_pT, \
            *h1_lep1_el_eta, \
            *h1_lep1_el_phi;
        
        // mu
        TH1F \
            *h1_mu_n, \
            *h1_lep1_mu_pT, \
            *h1_lep1_mu_eta, \
            *h1_lep1_mu_phi;
        
        // tau
        TH1F \
            *h1_tau_n, \
            *h1_tau_pT, \
            *h1_tau_eta, \
            *h1_tau_phi;
        
        std::vector <TH1F*> \
            v_h1_tau_pT, \
            v_h1_tau_eta, \
            v_h1_tau_phi;
        
        // tau-vis
        TH1F \
            *h1_tau_vis_n, \
            *h1_tau_vis_pT, \
            *h1_tau_vis_eta, \
            *h1_tau_vis_phi, \
            \
            *h1_tau_vis1_tau_vis2_m, \
            *h1_tau_vis1_tau_vis2_deltaPhi, \
            *h1_tau_vis1_tau_vis2_deltaR, \
            *h1_tau_vis1_tau_vis2_MET_mT2, \
            \
            *h1_MET_pZeta, \
            *h1_tau_vis1_tau_vis2_pZeta, \
            *h1_tau_vis1_tau_vis2_MET_pZeta, \
            *h1_tau_vis1_tau_vis2_MET_Dzeta;
        
        std::vector <TH1F*> \
            v_h1_tau_vis_pT, \
            v_h1_tau_vis_eta, \
            v_h1_tau_vis_phi, \
            \
            v_h1_tau_vis_m, \
            v_h1_tau_vis_MET_deltaPhi;
        
        // b
        TH1F \
            *h1_b_n, \
            *h1_b_pT, \
            *h1_b_eta, \
            *h1_b_phi;
        
        std::vector <TH1F*> \
            v_h1_b_pT, \
            v_h1_b_eta, \
            v_h1_b_phi;
        
        // jet
        TH1F \
            *h1_jet_n, \
            *h1_jet_HT, \
            *h1_jet_MHT, \
            *h1_jet_Meff;
        
        std::vector <TH1F*> \
            v_h1_jet_pT, \
            v_h1_jet_eta, \
            v_h1_jet_phi;
        
        // MET
        TH1F \
            *h1_MET_E, \
            *h1_MET_phi;
        
        // Cut-flow
        std::vector <std::vector <int> > v_cutFlow;
    
        Output(std::vector <const char*> &v_option, const char *details);
        
        void addTauHist(int n);
        
        void addTauVisHist(int n);
        
        void addbHist(int n);
        
        void addJetHist(int n);
        
        void addCutFlow(int n);
        
        void writeData();
        
        void freeMemory();
    };
}


# endif

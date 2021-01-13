# include <string>
# include <stdio.h>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TH1F.h>

# include "Common.h"
# include "Output_GEN.h"


namespace Output_GEN
{
    Output::Output(std::vector <const char*> &v_option, const char *details)
    {
        nameAddon = (char*) malloc(Common::str_len * sizeof(char));
        titleAddon = (char*) malloc(Common::str_len * sizeof(char));
        
        sprintf(nameAddon, "%s", "");
        sprintf(titleAddon, "%s", "");
        
        if(strcmp(details, ""))
        {
            sprintf(nameAddon, "_%s", details);
            sprintf(titleAddon, " [%s]", details);
        }
        
        
        output_el = false;
        output_mu = false;
        output_tau = false;
        output_tau_vis = false;
        
        output_t = false;
        output_b = false;
        
        output_W = false;
        output_Z = false;
        
        output_stau1 = false;
        output_stop1 = false;
        output_chargino1 = false;
        
        output_jet = false;
        output_b = false;
        output_MET = false;
        
        
        for(int iOption = 0; iOption < v_option.size(); iOption++)
        {
            if(!strcmp(v_option[iOption], "el"))
            {
                output_el = true;
            }
            
            else if(!strcmp(v_option[iOption], "mu"))
            {
                output_mu = true;
            }
            
            else if(!strcmp(v_option[iOption], "tau"))
            {
                output_tau = true;
            }
            
            else if(!strcmp(v_option[iOption], "tau_vis"))
            {
                output_tau_vis = true;
            }
            
            else if(!strcmp(v_option[iOption], "t"))
            {
                output_t = true;
            }
            
            else if(!strcmp(v_option[iOption], "b"))
            {
                output_b = true;
            }
            
            else if(!strcmp(v_option[iOption], "W"))
            {
                output_W = true;
            }
            
            else if(!strcmp(v_option[iOption], "Z"))
            {
                output_Z = true;
            }
            
            else if(!strcmp(v_option[iOption], "stau1"))
            {
                output_stau1 = true;
            }
            
            else if(!strcmp(v_option[iOption], "stop1"))
            {
                output_stop1 = true;
            }
            
            else if(!strcmp(v_option[iOption], "chargino1"))
            {
                output_chargino1 = true;
            }
            
            else if(!strcmp(v_option[iOption], "jet"))
            {
                output_jet = true;
            }
            
            else if(!strcmp(v_option[iOption], "MET"))
            {
                output_MET = true;
            }
        }
        
        
        if(output_el)
        {
            h1_el_n = new TH1F(("el_n_gen" + std::string(nameAddon)).c_str(), ("n_{e} GEN" + std::string(titleAddon)).c_str(), 9, 1, 10);
            h1_lep1_el_pT = new TH1F(("lep1_el_pT_gen" + std::string(nameAddon)).c_str(), ("p_{T, lep1-e} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_lep1_el_eta = new TH1F(("lep1_el_eta_gen" + std::string(nameAddon)).c_str(), ("#eta_{lep1-e} GEN" + std::string(titleAddon)).c_str(), 24, -3, 3);
            h1_lep1_el_phi = new TH1F(("lep1_el_phi_gen" + std::string(nameAddon)).c_str(), ("#phi_{lep1-e} GEN" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
        }
        
        if(output_mu)
        {
            h1_mu_n = new TH1F(("mu_n_gen" + std::string(nameAddon)).c_str(), ("n_{#mu} GEN" + std::string(titleAddon)).c_str(), 9, 1, 10);
            h1_lep1_mu_pT = new TH1F(("lep1_mu_pT_gen" + std::string(nameAddon)).c_str(), ("p_{T, lep1-#mu} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_lep1_mu_eta = new TH1F(("lep1_mu_eta_gen" + std::string(nameAddon)).c_str(), ("#eta_{lep1-#mu} GEN" + std::string(titleAddon)).c_str(), 24, -3, 3);
            h1_lep1_mu_phi = new TH1F(("lep1_mu_phi_gen" + std::string(nameAddon)).c_str(), ("#phi_{lep1-#mu} GEN" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
        }
        
        if(output_tau)
        {
            h1_tau_n = new TH1F(("tau_n_gen" + std::string(nameAddon)).c_str(), ("n_{#tau} GEN" + std::string(titleAddon)).c_str(), 9, 1, 10);
            h1_tau_pT = new TH1F(("tau_pT_gen" + std::string(nameAddon)).c_str(), ("p_{T, #tau} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_tau_eta = new TH1F(("tau_eta_gen" + std::string(nameAddon)).c_str(), ("#eta_{#tau} GEN" + std::string(titleAddon)).c_str(), 24, -3, 3);
            h1_tau_phi = new TH1F(("tau_phi_gen" + std::string(nameAddon)).c_str(), ("#phi_{#tau} GEN" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
        }
        
        if(output_tau_vis)
        {
            h1_tau_vis_n = new TH1F(("tau_vis_n_gen" + std::string(nameAddon)).c_str(), ("n_{#tau_{vis}} GEN" + std::string(titleAddon)).c_str(), 9, 1, 10);
            h1_tau_vis_pT = new TH1F(("tau_vis_pT_gen" + std::string(nameAddon)).c_str(), ("p_{T, #tau_{vis}} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_tau_vis_eta = new TH1F(("tau_vis_eta_gen" + std::string(nameAddon)).c_str(), ("#eta_{#tau_{vis}} GEN" + std::string(titleAddon)).c_str(), 24, -3, 3);
            h1_tau_vis_phi = new TH1F(("tau_vis_phi_gen" + std::string(nameAddon)).c_str(), ("#phi_{#tau_{vis}} GEN" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
            
            h1_tau_vis1_tau_vis2_m = new TH1F(("tau_vis1_tau_vis2_m_gen" + std::string(nameAddon)).c_str(), ("m_{#tau_{vis}1-#tau_{vis}2} GEN" + std::string(titleAddon)).c_str(), 50, 0, 500);
            h1_tau_vis1_tau_vis2_deltaPhi = new TH1F(("tau_vis1_tau_vis2_deltaPhi_gen" + std::string(nameAddon)).c_str(), ("#Delta#phi_{#tau_{vis}1-#tau_{vis}2} GEN" + std::string(titleAddon)).c_str(), 50, -2*M_PI, 2*M_PI);
            h1_tau_vis1_tau_vis2_deltaR = new TH1F(("tau_vis1_tau_vis2_deltaR_gen" + std::string(nameAddon)).c_str(), ("#DeltaR_{#tau_{vis}1-#tau_{vis}2} GEN" + std::string(titleAddon)).c_str(), 100, 0, 10);
            h1_tau_vis1_tau_vis2_MET_mT2 = new TH1F(("tau_vis1_tau_vis2_MET_mT2_gen" + std::string(nameAddon)).c_str(), ("m_{T2 (#tau_{vis}1-#tau_{vis}2-MET)} GEN" + std::string(titleAddon)).c_str(), 100, 0, 1000);
            
            h1_MET_pZeta = new TH1F(("MET_pZeta_gen" + std::string(nameAddon)).c_str(), ("p_{#zeta (MET)} GEN" + std::string(titleAddon)).c_str(), 100, -500, 500);
            h1_tau_vis1_tau_vis2_pZeta = new TH1F(("tau_vis1_tau_vis2_pZeta_gen" + std::string(nameAddon)).c_str(), ("p_{#zeta (#tau_{vis}1-#tau_{vis}2)} GEN" + std::string(titleAddon)).c_str(), 100, -500, 500);
            h1_tau_vis1_tau_vis2_MET_pZeta = new TH1F(("tau_vis1_tau_vis2_MET_pZeta_gen" + std::string(nameAddon)).c_str(), ("p_{#zeta (#tau_{vis}1-#tau_{vis}2-MET)} GEN" + std::string(titleAddon)).c_str(), 100, -500, 500);
            h1_tau_vis1_tau_vis2_MET_Dzeta = new TH1F(("tau_vis1_tau_vis2_MET_Dzeta_gen" + std::string(nameAddon)).c_str(), ("D_{#zeta (#tau_{vis}1-#tau_{vis}2-MET)} GEN" + std::string(titleAddon)).c_str(), 100, -500, 500);
        }
        
        if(output_jet)
        {
            h1_jet_n = new TH1F(("jet_n_gen" + std::string(nameAddon)).c_str(), ("n_{jet} GEN" + std::string(titleAddon)).c_str(), 9, 1, 10);
            h1_jet_HT = new TH1F(("jet_HT_gen" + std::string(nameAddon)).c_str(), ("H_{T, jet} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_jet_MHT = new TH1F(("jet_MHT_gen" + std::string(nameAddon)).c_str(), ("#slash{H}_{T, jet} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_jet_Meff = new TH1F(("jet_Meff_gen" + std::string(nameAddon)).c_str(), ("#M_{eff, jet} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
        }
        
        if(output_b)
        {
            h1_b_n = new TH1F(("b_n_gen" + std::string(nameAddon)).c_str(), ("n_{b} GEN" + std::string(titleAddon)).c_str(), 9, 1, 10);
            h1_b_pT = new TH1F(("b_pT_gen" + std::string(nameAddon)).c_str(), ("p_{T, b} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_b_eta = new TH1F(("b_eta_gen" + std::string(nameAddon)).c_str(), ("#eta_{b} GEN" + std::string(titleAddon)).c_str(), 24, -3, 3);
            h1_b_phi = new TH1F(("b_phi_gen" + std::string(nameAddon)).c_str(), ("#phi_{b} GEN" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
        }
        
        if(output_MET)
        {
            h1_MET_E = new TH1F(("MET_E_gen" + std::string(nameAddon)).c_str(), ("#vec{#slash{E}}_{T, E} GEN" + std::string(titleAddon)).c_str(), 100, 0, 2000);
            h1_MET_phi = new TH1F(("MET_phi_gen" + std::string(nameAddon)).c_str(), ("#vec{#slash{E}}_{T, #phi} GEN" + std::string(titleAddon)).c_str(), 25, -M_PI, M_PI);
        }
    }
    
    
    void Output::addTauHist(int n)
    {
        for(int i = v_h1_tau_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "tau%d_pT_gen%s", i+1, nameAddon);
            sprintf(title, "p_{T, #tau%d} GEN%s", i+1, titleAddon);
            v_h1_tau_pT.push_back(new TH1F(name, title, 100, 0, 2000));
            
            sprintf(name, "tau%d_eta_gen%s", i+1, nameAddon);
            sprintf(title, "#eta_{#tau%d} GEN%s", i+1, titleAddon);
            v_h1_tau_eta.push_back(new TH1F(name, title, 24, -3, 3));
            
            sprintf(name, "tau%d_phi_gen%s", i+1, nameAddon);
            sprintf(title, "#phi_{#tau%d} GEN%s", i+1, titleAddon);
            v_h1_tau_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
        }
    }
    
    
    void Output::addTauVisHist(int n)
    {
        for(int i = v_h1_tau_vis_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "tau_vis%d_pT_gen%s", i+1, nameAddon);
            sprintf(title, "p_{T, #tau_{vis}%d} GEN%s", i+1, titleAddon);
            v_h1_tau_vis_pT.push_back(new TH1F(name, title, 100, 0, 2000));
            
            sprintf(name, "tau_vis%d_eta_gen%s", i+1, nameAddon);
            sprintf(title, "#eta_{#tau_{vis}%d} GEN%s", i+1, titleAddon);
            v_h1_tau_vis_eta.push_back(new TH1F(name, title, 24, -3, 3));
            
            sprintf(name, "tau_vis%d_phi_gen%s", i+1, nameAddon);
            sprintf(title, "#phi_{#tau_{vis}%d} GEN%s", i+1, titleAddon);
            v_h1_tau_vis_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
            
            sprintf(name, "tau_vis%d_m_gen%s", i+1, nameAddon);
            sprintf(title, "m_{#tau_{vis}%d} GEN%s", i+1, titleAddon);
            v_h1_tau_vis_m.push_back(new TH1F(name, title, 25, 0, 5));
            
            sprintf(name, "tau_vis%d_MET_deltaPhi_gen%s", i+1, nameAddon);
            sprintf(title, "#Delta#phi_{#tau_{vis}%d-MET} GEN%s", i+1, titleAddon);
            v_h1_tau_vis_MET_deltaPhi.push_back(new TH1F(name, title, 50, -2*M_PI, 2*M_PI));
        }
    }
    
    
    void Output::addbHist(int n)
    {
        for(int i = v_h1_b_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "b%d_pT_gen%s", i+1, nameAddon);
            sprintf(title, "p_{T, b%d} GEN%s", i+1, titleAddon);
            v_h1_b_pT.push_back(new TH1F(name, title, 100, 0, 2000));
            
            sprintf(name, "b%d_eta_gen%s", i+1, nameAddon);
            sprintf(title, "#eta_{b%d} GEN%s", i+1, titleAddon);
            v_h1_b_eta.push_back(new TH1F(name, title, 24, -3, 3));
            
            sprintf(name, "b%d_phi_gen%s", i+1, nameAddon);
            sprintf(title, "#phi_{b%d} GEN%s", i+1, titleAddon);
            v_h1_b_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
        }
    }
    
    
    void Output::addJetHist(int n)
    {
        for(int i = v_h1_jet_pT.size(); i < n; i++)
        {
            char name[Common::str_len], title[Common::str_len];
            
            sprintf(name, "jet%d_pT_gen%s", i+1, nameAddon);
            sprintf(title, "p_{T, #jet%d} GEN%s", i+1, titleAddon);
            v_h1_jet_pT.push_back(new TH1F(name, title, 100, 0, 2000));
            
            sprintf(name, "jet%d_eta_gen%s", i+1, nameAddon);
            sprintf(title, "#eta_{#jet%d} GEN%s", i+1, titleAddon);
            v_h1_jet_eta.push_back(new TH1F(name, title, 24, -3, 3));
            
            sprintf(name, "jet%d_phi_gen%s", i+1, nameAddon);
            sprintf(title, "#phi_{#jet%d} GEN%s", i+1, titleAddon);
            v_h1_jet_phi.push_back(new TH1F(name, title, 25, -M_PI, M_PI));
        }
    }
    
    
    void Output::addCutFlow(int n)
    {
        std::vector <int> cutFlow(n, 0);
        
        v_cutFlow.push_back(cutFlow);
    }
    
    
    void Output::writeData()
    {
        if(output_el)
        {
            h1_el_n->Write();
            h1_lep1_el_pT->Write();
            h1_lep1_el_eta->Write();
            h1_lep1_el_phi->Write();
        }
        
        if(output_mu)
        {
            h1_mu_n->Write();
            h1_lep1_mu_pT->Write();
            h1_lep1_mu_eta->Write();
            h1_lep1_mu_phi->Write();
        }
        
        if(output_tau)
        {
            h1_tau_n->Write();
            h1_tau_pT->Write();
            h1_tau_eta->Write();
            h1_tau_phi->Write();
            
            for(int i = 0; i < v_h1_tau_pT.size(); i++)
            {
                v_h1_tau_pT[i]->Write();
                v_h1_tau_eta[i]->Write();
                v_h1_tau_phi[i]->Write();
            }
        }
        
        if(output_tau_vis)
        {
            h1_tau_vis_n->Write();
            h1_tau_vis_pT->Write();
            h1_tau_vis_eta->Write();
            h1_tau_vis_phi->Write();
            
            h1_tau_vis1_tau_vis2_m->Write();
            h1_tau_vis1_tau_vis2_deltaPhi->Write();
            h1_tau_vis1_tau_vis2_deltaR->Write();
            h1_tau_vis1_tau_vis2_MET_mT2->Write();
            
            h1_MET_pZeta->Write();
            h1_tau_vis1_tau_vis2_pZeta->Write();
            h1_tau_vis1_tau_vis2_MET_pZeta->Write();
            h1_tau_vis1_tau_vis2_MET_Dzeta->Write();
            
            for(int i = 0; i < v_h1_tau_vis_pT.size(); i++)
            {
                v_h1_tau_vis_pT[i]->Write();
                v_h1_tau_vis_eta[i]->Write();
                v_h1_tau_vis_phi[i]->Write();
                
                v_h1_tau_vis_m[i]->Write();
                v_h1_tau_vis_MET_deltaPhi[i]->Write();
            }
        }
        
        if(output_b)
        {
            h1_b_n->Write();
            h1_b_pT->Write();
            h1_b_eta->Write();
            h1_b_phi->Write();
            
            for(int i = 0; i < v_h1_b_pT.size(); i++)
            {
                v_h1_b_pT[i]->Write();
                v_h1_b_eta[i]->Write();
                v_h1_b_phi[i]->Write();
            }
        }
        
        if(output_jet)
        {
            h1_jet_n->Write();
            h1_jet_HT->Write();
            h1_jet_MHT->Write();
            h1_jet_Meff->Write();
            
            for(int i = 0; i < v_h1_jet_pT.size(); i++)
            {
                v_h1_jet_pT[i]->Write();
                v_h1_jet_eta[i]->Write();
                v_h1_jet_phi[i]->Write();
            }
        }
        
        if(output_MET)
        {
            h1_MET_E->Write();
            h1_MET_phi->Write();
        }
    }
    
    
    void Output::freeMemory()
    {
        if(output_el)
        {
            delete h1_el_n;
            delete h1_lep1_el_pT;
            delete h1_lep1_el_eta;
            delete h1_lep1_el_phi;
        }
        
        if(output_mu)
        {
            delete h1_mu_n;
            delete h1_lep1_mu_pT;
            delete h1_lep1_mu_eta;
            delete h1_lep1_mu_phi;
        }
        
        if(output_tau)
        {
            delete h1_tau_n;
            delete h1_tau_pT;
            delete h1_tau_eta;
            delete h1_tau_phi;
            
            for(int i = 0; i < v_h1_tau_pT.size(); i++)
            {
                delete v_h1_tau_pT[i];
                delete v_h1_tau_eta[i];
                delete v_h1_tau_phi[i];
            }
        }
        
        if(output_tau_vis)
        {
            delete h1_tau_vis_n;
            delete h1_tau_vis_pT;
            delete h1_tau_vis_eta;
            delete h1_tau_vis_phi;
            
            delete h1_tau_vis1_tau_vis2_m;
            delete h1_tau_vis1_tau_vis2_deltaPhi;
            delete h1_tau_vis1_tau_vis2_deltaR;
            delete h1_tau_vis1_tau_vis2_MET_mT2;
            
            delete h1_MET_pZeta;
            delete h1_tau_vis1_tau_vis2_pZeta;
            delete h1_tau_vis1_tau_vis2_MET_pZeta;
            delete h1_tau_vis1_tau_vis2_MET_Dzeta;
            
            for(int i = 0; i < v_h1_tau_vis_pT.size(); i++)
            {
                delete v_h1_tau_vis_pT[i];
                delete v_h1_tau_vis_eta[i];
                delete v_h1_tau_vis_phi[i];
                
                delete v_h1_tau_vis_m[i];
                delete v_h1_tau_vis_MET_deltaPhi[i];
            }
        }
        
        if(output_b)
        {
            delete h1_b_n;
            delete h1_b_pT;
            delete h1_b_eta;
            delete h1_b_phi;
            
            for(int i = 0; i < v_h1_b_pT.size(); i++)
            {
                delete v_h1_b_pT[i];
                delete v_h1_b_eta[i];
                delete v_h1_b_phi[i];
            }
        }
        
        if(output_jet)
        {
            delete h1_jet_n;
            delete h1_jet_HT;
            delete h1_jet_MHT;
            delete h1_jet_Meff;
            
            for(int i = 0; i < v_h1_jet_pT.size(); i++)
            {
                delete v_h1_jet_pT[i];
                delete v_h1_jet_eta[i];
                delete v_h1_jet_phi[i];
            }
        }
        
        if(output_MET)
        {
            delete h1_MET_E;
            delete h1_MET_phi;
        }
    }
}

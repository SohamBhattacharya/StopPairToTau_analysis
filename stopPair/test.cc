# include <algorithm>
# include <iostream>
# include <vector>

# include <boost/algorithm/string/replace.hpp>
# include <CLHEP/Vector/LorentzVector.h>

# include <TH1F.h>

# include "HeaderFiles/exprtk.hpp"
# include "HeaderFiles/lester_mt2_bisect_mod.h"
//# include "HeaderFiles/ElMuScaleFactor.h"
# include "HeaderFiles/Common.h"
//# include "HeaderFiles/TemplateSmearing.h"
//# include "HeaderFiles/TauEfficiencyAndSF.h"
# include "HeaderFiles/TauPromptAndFakeRate.h"

# include "HeaderFiles/json.h"

std::vector <int> func1()
{
    return {};
}


/*std::vector <int> get_SRpos(int findBin, std::vector <std::vector <double> > vv_cut)
{
    int nSR = Common::get_nSR(vv_cut);
    
    if(findBin > nSR)
    {
        printf("Error in Common::get_SRpos(...): bin# (%d) > nSR (%d). \n", findBin, nSR);
        
        exit(EXIT_FAILURE);
    }
    
    if(findBin < 1)
    {
        printf("Error in Common::get_SRpos(...): bin# (%d) < 1. \n", findBin);
        
        exit(EXIT_FAILURE);
    }
    
    std::vector <int> v_pos;
    
    // Subtract the extra 1 as SR # starts from 1
    findBin--;
    
    //if(vv_cut.size() == 1)
    //{
    //    v_pos.push_back(std::min(findBin, vv_cut.at(0).size()));
    //}
    //
    //else
    //{
    //    for(int iBin = 0; iBin < vv_cut.at(0).size(); iBin++)
    //    {
    //        std::vector <std::vector <double> > vv_cut_temp(vv_cut.begin()+1, vv_cut.end());
    //        nSR = Common::get_nSR(vv_cut_temp);
    //        
    //        getPos(findBin - nSR*iBin, vv_cut_temp);
    //    }
    //}
    
    for(int iSel = 0; iSel < vv_cut.size(); iSel++)
    {
        std::vector <std::vector <double> > vv_cut_temp(vv_cut.begin()+iSel+1, vv_cut.end());
        nSR = Common::get_nSR(vv_cut_temp);
        
        int pos = 0;
        
        if(nSR > 0)
        {
            pos = findBin / nSR;
            
            v_pos.push_back(pos);
            findBin %= nSR;
        }
    }
    
    return v_pos;
}*/


int main()
{
    //std::string str = "root://se01.indiacms.res.in//store/user/sobhatta/TT_TuneCUETP8M1_13TeV-powheg-pythia8/crab_TT_TuneCUETP8M1_13TeV-powheg-pythia8/170202_175736/0000/custom_1.root";
    //std::string str = "custom_1.root";
    
    //std::cout << str.rfind(".root") << "\n";
    //std::cout << str.substr(str.rfind("/")+1, str.rfind(".root")-str.rfind("/")-1) << "\n";
    
    //std::vector <int> v1 = func1();
    
    //std::cout << v1.size() << "\n";
    
    
    //std::vector <int> v2 = {1, 3, 2};
    //std::vector <int> :: iterator pos = std::find(v2.begin(), v2.end(), 5);
    //std::cout << *pos << "\n";
    
    //const double massOfSystemA =  0.7; // GeV
    //const double pxOfSystemA   =  100; // GeV
    //const double pyOfSystemA   =   75; // GeV
    //
    //// The input parameters associated with the particle
    //// (or collection of particles) associated with the 
    //// second "side" of the event:
    //const double massOfSystemB =  0.7; // GeV
    //const double pxOfSystemB   = -100; // GeV
    //const double pyOfSystemB   = -150; // GeV
    //
    //// The missing transverse momentum:
    //const double pxMiss        = -200; // GeV
    //const double pyMiss        =  280; // GeV
    //
    //// The mass of the "inivisible" particle presumed to have
    //// been produced at the end of the decay chain in each
    //// "half" of the event:
    //const double invis_mass    = 0; // GeV
    //
    //
    //double mT2 = asymm_mt2_lester_bisect::get_mT2( \
    //    massOfSystemA, pxOfSystemA, pyOfSystemA, \
    //    massOfSystemB, pxOfSystemB, pyOfSystemB, \
    //    pxMiss, pyMiss, \
    //    invis_mass, invis_mass);
    //
    //printf("massOfSystemA = %f \n", massOfSystemA);
    //printf("pxOfSystemA = %f \n", pxOfSystemA);
    //printf("pyOfSystemA = %f \n", pyOfSystemA);
    //printf("\n");
    //printf("massOfSystemB = %f \n", massOfSystemB);
    //printf("pxOfSystemB = %f \n", pxOfSystemB);
    //printf("pyOfSystemB = %f \n", pyOfSystemB);
    //printf("\n");
    //printf("invis_mass = %f \n", invis_mass);
    //printf("\n");
    //printf("mT2 = %f \n", mT2);
    
    //ElMuScaleFactor::ScaleFactor *myScaleFactor = new ElMuScaleFactor::ScaleFactor();
    ////myScaleFactor->init_ScaleFactor("HTT-utilities/LepEffInterface/data/Muon/Muon_IdIso0p15_eff.root");
    //myScaleFactor->init_ScaleFactor("HTT-utilities/LepEffInterface/data/Muon/Run2016BtoH/Muon_IdIso_IsoLt0p2_2016BtoH_eff_update1407.root");
    //double scaleFactor = myScaleFactor->get_ScaleFactor(50, 2.4);
    //printf("myScaleFactor %f \n", scaleFactor);
    //return 0;
    
    
    //std::pair <double, double> p_tauSF = Common::getTauSF(55, 1.2, "MediumIsolationMVArun2v1DBdR03oldDMwLT");
    //printf("%f, %f \n", p_tauSF.first, p_tauSF.second);
    
    
    //int cmd1 = system("ls xxx");
    //int cmd2 = system("ls stopPair_mc");
    //
    //printf("%d %d \n", cmd1, cmd2);
    
    //TH1F *h1 = new TH1F("h1", "h1", 10, 0, 10);
    //h1->Sumw2();
    //
    //TH1F *h2 = new TH1F("h2", "h2", 10, 0, 10);
    //
    //h1->SetBinContent(3, 0.0);
    //h1->SetBinError(3, 0.1234);
    //
    //h2->SetBinContent(3, 3.0);
    //h2->SetBinError(3, 1.43647);
    //
    //h1->Fill(2, 0.5);
    //h1->Fill(2);
    //
    //h2->Fill(2);
    //
    //int bin;
    //
    //bin = 3;
    //
    //printf("%f, %f \n",
    //    h1->GetBinContent(bin),
    //    h1->GetBinError(bin)
    //);
    //
    //h1->SetBinContent(bin, 0.0);
    //
    //printf("%f, %f \n",
    //    h1->GetBinContent(bin),
    //    h1->GetBinError(bin)
    //);
    
    //h1->Multiply(h2);
    //
    //printf("%f, %f \n",
    //    h1->GetBinContent(3),
    //    h1->GetBinError(3)
    //);
    
    //const std::vector <double> v_tauTau_MET_mT2cut_SRA = {0, 40, 80};
    //const std::vector <double> v_METcut_SRA = {50, 200};
    //const std::vector <double> v_tauTau_jet_HTcut_SRA = {100, 300, 700};
    //
    //const std::vector <std::vector <double> > v_cut_SRA = {
    //    v_tauTau_MET_mT2cut_SRA,
    //    v_METcut_SRA
    //};
    //
    //printf("%d %d %d\n", (int) v_cut_SRA.size(), (int) v_cut_SRA.at(0).size(), (int) v_cut_SRA.at(1).size());
    
    
    //std::vector <double> v1 = {1, 2, 3, 4, 5};
    
    //std::vector <double> v2(v1.begin()+1, v1.end());
    //printf("%d, %f, %f \n", (int) v2.size(), v2.at(0), v2.at(v2.size()-1));
    
    //std::vector <double> v2(v1.begin()+v1.size(), v1.end());
    //printf("%d \n", (int) v2.size());
    
    
    //int findBin = 5;
    //std::vector <std::vector <double> > vv_cut = Common::vv_cut_SRA;
    //
    //std::vector <int> v_pos = get_SRpos(findBin, vv_cut);
    //
    //printf("SR%d \n", findBin);
    //
    //for(int i = 0; i < v_pos.size(); i++)
    //{
    //    printf("%d: >= %f \n", v_pos.at(i), vv_cut.at(i).at(v_pos.at(i)));
    //    //printf("%d \n", v_pos.at(i));
    //}
    
    
    //CLHEP::HepLorentzVector v1(10, 2, 9, 8);
    //
    //CLHEP::HepLorentzVector v2 = v1;
    //
    //printf("%f, %f, %f, %f \n", v1.t(), v1.x(), v1.y(), v1.z());
    //printf("%f, %f, %f, %f \n", v2.t(), v2.x(), v2.y(), v2.z());
    //printf("\n");
    //
    //v1.setY(-7);
    //v2.setX(-5);
    //
    //printf("%f, %f, %f, %f \n", v1.t(), v1.x(), v1.y(), v1.z());
    //printf("%f, %f, %f, %f \n", v2.t(), v2.x(), v2.y(), v2.z());
    //printf("\n");
    
    /*CLHEP::HepLorentzVector obj_4mom;
    obj_4mom.setT(100);
    obj_4mom.setX(34);
    obj_4mom.setY(-56);
    obj_4mom.setZ(8);
    
    TemplateSmearing::TemplateSmearedInfo *info = Common::getSmearedInfo(
        obj_4mom,
        "resources/templateMethod/hist_taugun_aditee.root",
        "central"
    );
    
    for(int iBin = 0; iBin < info->nBin; iBin++)
    {
        CLHEP::HepLorentzVector temp = info->v_obj_smeared4mom.at(iBin);
        double weight = info->v_weight.at(iBin);
        double response = info->v_response.at(iBin);
        
        printf("(%0.2f, %0.2f, %0.2f, %0.2f) --> (%0.2f, %0.2f, %0.2f, %0.2f), pT %0.2f, w %0.4f, r %0.4f \n",
            obj_4mom.e(), obj_4mom.px(), obj_4mom.py(), obj_4mom.pz(),
            temp.t(), temp.x(), temp.y(), temp.z(),
            obj_4mom.perp(), weight, response
        );
    }*/
    
    /*std::cout << std::ifstream("nonexistantfile.txt").good() << "\n";
    std::cout << Common::doesFileExist("nonexistantfile.txt") << "\n";
    
    std::cout << std::ifstream("test.cc").good() << "\n";
    std::cout << Common::doesFileExist("test.cc") << "\n";
    
    
    TauEfficiencyAndSF::TauEfficiencyAndSF *tauEff = new TauEfficiencyAndSF::TauEfficiencyAndSF(
        "DYJetsToLL_mc/output_tauIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root",
        "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_genMatched_pT_vs_eta_reco",
        "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_vis_pT_vs_eta_gen"
    );
    
    printf("eff %f \n", tauEff->getEfficiency(3000, 1.1));*/
    
    
    /*std::vector <std::vector <double> > vv_double;
    
    vv_double.push_back({1.0, 2.0, 3.0});
    vv_double.push_back({1.5, 2.5});
    
    std::vector <std::vector <double> > vv_double_temp = vv_double;
    
    vv_double.at(1).at(1) = 7.3;
    vv_double_temp.at(0).at(1) = 9.4;
    
    printf("%f, %f \n", vv_double.at(1).at(1), vv_double_temp.at(1).at(1));
    printf("%f, %f \n", vv_double.at(0).at(1), vv_double_temp.at(0).at(1));*/
    
    
    //double vis1x = 50, vis1y = 65;
    //double vis2x = 49, vis2y = 56;
    //double invx = 23, invy = -35;
    //
    //double vis_pZeta = Common::getPzeta(
    //    {{vis1x, vis1y},
    //     {vis2x, vis2y}
    //    },
    //    
    //    {vis1x, vis1y},
    //    {vis2x, vis2y}
    //);
    //
    //double vis_inv_pZeta = Common::getPzeta(
    //    {{vis1x, vis1y},
    //     {vis2x, vis2y},
    //     {invx, invy}
    //    },
    //    
    //    {vis1x, vis1y},
    //    {vis2x, vis2y}
    //);
    //
    //double vis_inv_Dzeta = vis_inv_pZeta - 1.85*vis_pZeta;
    //
    //printf("%f \n", vis_inv_Dzeta);
    //
    //
    //double vis_inv_Dzeta_new = Common::getDzeta(
    //    {{vis1x, vis1y},
    //     {vis2x, vis2y}
    //    },
    //    
    //    {invx, invy},
    //    
    //    {vis1x, vis1y},
    //    {vis2x, vis2y}
    //);
    //
    //printf("%f \n", vis_inv_Dzeta_new);
    
    //CLHEP::HepLorentzVector mom1(1000, 50, 40, 10);
    //CLHEP::HepLorentzVector mom2(2000, 90, 10, 0);
    //
    //printf("mom1: E %f, pT %f \n", mom1.e(), mom1.perp());
    //printf("mom2: E %f, pT %f \n", mom2.e(), mom2.perp());
    //
    //CLHEP::HepLorentzVector temp;
    //
    //temp = mom2;
    //mom2 = mom1;
    //mom1 = temp;
    //
    //printf("After exchange: \n");
    //
    //printf("mom1: E %f, pT %f \n", mom1.e(), mom1.perp());
    //printf("mom2: E %f, pT %f \n", mom2.e(), mom2.perp());
    
    
    /*TauPromptAndFakeRate::TauPromptAndFakeRate *tauPandF = new TauPromptAndFakeRate::TauPromptAndFakeRate(
        {
            "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauIdIsoEfficiency/custom_all_tauIdIsoEfficiency.root"
        },
        "TightIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_DM_reco",
        "LooseIsolationMVArun2v1DBdR03oldDMwLT_againstElectronLooseMVA6_againstMuonLoose3/tau_pT_vs_DM_reco",
        
        {
            "tauTau_data/output_tauTau_fakeRate/Tau_Run2016B-18Apr2017_ver2-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
            "tauTau_data/output_tauTau_fakeRate/Tau_Run2016C-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
            "tauTau_data/output_tauTau_fakeRate/Tau_Run2016D-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
            "tauTau_data/output_tauTau_fakeRate/Tau_Run2016E-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
            "tauTau_data/output_tauTau_fakeRate/Tau_Run2016F-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
            "tauTau_data/output_tauTau_fakeRate/Tau_Run2016G-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root",
            "tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-18Apr2017-v1_MINIAOD_tauTau_fakeRate/custom_all_fakeRate_tauTau.root"
        },
        "tightLoose_dR03_SS/tau_pT_vs_DM_reco_tightLoose_dR03_SS",
        "looseLoose_dR03_SS/tau_pT_vs_DM_reco_looseLoose_dR03_SS",
        "tightTight_dR03_SS/tau_pT_vs_DM_reco_tightTight_dR03_SS",
        "tightLoose_dR03_SS/tau_pT_vs_DM_reco_tightLoose_dR03_SS",
        
        Common::v_tau_promptFake_pTbin
    );
    
    
    std::vector <double> v_pT1 = {100};
    std::vector <double> v_pT2 = {200};
    double DM = 0;
    
    for(int i = 0; i < v_pT1.size(); i++)
    {
        printf("\n");
        printf("***** \n");
        
        double p1 = tauPandF->getPromptRate(v_pT1.at(i), DM).first;
        double p2 = tauPandF->getPromptRate(v_pT2.at(i), DM).first;
        
        printf("\n");
        
        double f1 = tauPandF->getFakeRate(v_pT1.at(i), DM).first;
        double f2 = tauPandF->getFakeRate(v_pT2.at(i), DM).first;
        
        std::string expression = "(p1*p2*f2*(1-f1) + f1*f2*p2*(1-p1))";
        std::string expression_sub = expression;
        
        std::string str_p1 = "p1";
        std::string str_f1 = "f1";
        
        std::string str_p2 = "p2";
        std::string str_f2 = "f2";
        
        double result = Common::evaluateExpression(
            expression,
            {
                std::make_pair(str_p1, p1),
                std::make_pair(str_f1, f1),
                std::make_pair(str_p2, p2),
                std::make_pair(str_f2, f2)
            },
            true
        );
        
        printf("Result: %f \n", result);
    }*/
    
    
    /*std::vector <int> v_b_n = {0, 1, 2, 3};
    
    double MET = 150;
    
    for(int i = 0; i < v_b_n.size(); i++)
    {
        bool result;
        
        printf("\n");
        printf("***** \n");
        
        result = Common::evaluateExpression(
            "b_n >= 1 and MET > 50",
            {
                std::make_pair("b_n", v_b_n.at(i)),
                std::make_pair("MET", MET)
            },
            true
        );
        
        printf("Result: %d \n", result);
        
        
        result = Common::evaluateExpression(
            "b_n == 1 and MET >= 200",
            {
                std::make_pair("b_n", v_b_n.at(i)),
                std::make_pair("MET", MET)
            },
            true
        );
        
        printf("Result: %d \n", result);
    }*/
    
    //"mc_genuine_TightIso_dm0": {
    //    "alpha": 4.862445750387961, 
    //    "m_{0}": 38.083905839292164, 
    //    "sigma": 6.202388502948717, 
    //    "norm": 0.9321292524169671, 
    //    "n": 3.397804647368993
    //}, 
    
    std::ifstream i("resources/diTauTrigger/fitresults_tt_moriond2017.json");
    nlohmann::json j;
    i >> j;
    
    i.close();
    
    std::vector <std::string> v_WPname = {
        "data_genuine_TightIso_dm10",
        "mc_genuine_TightIso_dm10",
        
        "data_genuine_LooseIso_dm10",
        "mc_genuine_LooseIso_dm10"
    };
    
    std::vector <double> v_pT = {
        40, 50, 60, 70, 100, 150, 200, 300, 500
    };
    
    for(int iWP = 0; iWP < v_WPname.size(); iWP++)
    {
        std::string WPname = v_WPname.at(iWP);
        
        double alpha = j[WPname]["alpha"];
        double m0 = j[WPname]["m_{0}"];
        double sigma = j[WPname]["sigma"];
        double norm = j[WPname]["norm"];
        double n = j[WPname]["n"];
        
        printf("********** %s ********** \n", WPname.c_str());
        printf("alpha: % 0.4f \n", alpha);
        printf("m_{0}: % 0.4f \n", m0);
        printf("sigma: % 0.4f \n", sigma);
        printf("norm: % 0.4f \n", norm);
        printf("n: % 0.4f \n", n);
        printf("\n");
        
        for(int iPt = 0; iPt < v_pT.size(); iPt++)
        {
            double result = Common::crystalballEfficiency(
                v_pT.at(iPt),
                m0,
                sigma,
                alpha,
                n,
                norm
            );
            
            printf("pT: %0.2f, Result: %0.4f \n", v_pT.at(iPt), result);
        }
        
        printf("\n\n");
    }
}

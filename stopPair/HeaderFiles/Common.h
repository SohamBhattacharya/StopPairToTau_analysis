# ifndef Common_H
# define Common_H


# include <iostream>
# include <map>
//# include <Python.h>
# include <stdlib.h>
# include <string>
# include <type_traits>
# include <utility>
# include <vector>

# include <boost/algorithm/string/replace.hpp>
# include <CLHEP/Vector/LorentzVector.h>

# include "TFile.h"
# include "TH1F.h"
# include "TH2F.h"
# include "TH3F.h"
# include "TColor.h"

# include "RooWorkspace.h"
# include "RooRealVar.h"

# include "json.h"
# include "lester_mt2_bisect_mod.h"

# include "BTagCalibrationStandalone.h"
//# include "TauPromptAndFakeRate.h"
# include "TauTriggerSFs2017.h"


namespace Common
{
    extern const int str_len;
    
    extern const char delimiter[];
    
    extern const std::vector <int> v_colorIndex_bg;
    extern const std::vector <int> v_colorIndex_sig;
    
    extern const std::string process_str_template;
    extern const std::string dir_str_template;
    extern const std::string otherInfoDir_str_template;
    extern const std::string sourceFileName_str_template;
    extern const std::string era_str_template;
    extern const std::string syst_name_template;
    
    extern const std::string stop1_m_str_template;
    extern const std::string neutralino_m_str_template;
    
    extern const std::vector <double> v_eventWeight_nJetBin_DYJetsToLL_2016;
    extern const std::vector <double> v_eventWeight_nJetBin_DYJetsToLL_2017;
    
    extern const std::vector <double> v_eventWeight_nJetBin_WJetsToLNu_2016;
    extern const std::vector <double> v_eventWeight_nJetBin_WJetsToLNu_2017;
    
    extern const std::map <std::string, std::vector <double> > m_eventWeight_nJetBin_DYJetsToLL;
    extern const std::map <std::string, std::vector <double> > m_eventWeight_nJetBin_WJetsToLNu;
    
    extern const std::string topPtReweighting_str;
    extern const std::string ZptReweighting_str;
    
    extern const std::map <std::string, bool> m_correction;
    
    extern const std::vector <double> v_ISRweight;
    
    extern const std::vector <std::string> v_bDiscriminatorName;
    extern const std::vector <std::vector <std::string> > vv_bDiscriminatorWPname;
    extern const std::vector <double> v_pT_bin_bTaggingEfficiency;
    extern const std::vector <double> v_eta_bin_bTaggingEfficiency;
    
    extern const std::vector <double> v_pT_bin_tauFastFullSF;
    extern const std::vector <double> v_eta_bin_tauFastFullSF;
    
    
    enum SYST_TYPE{
        SYST_UP = 1,
        SYST_CENTRAL = 0,
        SYST_DOWN = -1,
        
        SYST_ONESIDED = 9999
    };
    
    
    // GEN ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    extern const double
        el_pTcut_gen,
        el_etaCut_gen,
        
        mu_pTcut_gen,
        mu_etaCut_gen,
        
        tau_vis_pTcut_gen,
        tau_vis_etaCut_gen,
        
        t_pTcut_gen,
        t_etaCut_gen,
        
        b_pTcut_gen,
        b_etaCut_gen,
        
        W_pTcut_gen,
        W_etaCut_gen,
        
        Z_pTcut_gen,
        Z_etaCut_gen,
        
        jet_pTcut_gen,
        jet_etaCut_gen;
    
    // RECO ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    extern const double
        el_pTcut_elMu_reco,
        el_etaCut_elMu_reco,
        
        el_pTcut_elTau_reco,
        el_etaCut_elTau_reco,
        
        el_dxyCut_reco,
        el_dzCut_reco,
        
        el_missingInnerHitsCut_reco,
        
        mu_pTcut_elMu_reco,
        mu_etaCut_elMu_reco,
        
        mu_pTcut_muMu_reco,
        mu_etaCut_muMu_reco,
        
        mu_pTcut_muTau_reco,
        mu_etaCut_muTau_reco,
        
        mu_dxyCut_reco,
        mu_dzCut_reco,
        
        elMu_deltaRcut_reco,
        muMu_deltaRcut_reco,
        
        tau_pTcut_tauTau_reco,
        tau_etaCut_tauTau_reco,
        
        tau_pTcut_muTau_reco,
        tau_etaCut_muTau_reco,
        
        tau_dzCut_reco,
        
        tauTau_deltaRcut_reco,
        muTau_deltaRcut_reco,
        
        jet_pTcut_reco,
        jet_etaCut_reco,
        
        b_pTcut_reco,
        b_etaCut_reco;
    
    
    extern const std::vector <double> v_tau_promptFake_pTbin;
    
    
    extern const std::vector <double> v_tau_n_SRA;
    extern const std::vector <double> v_tauTau_MET_mT2cut_SRA;
    extern const std::vector <double> v_METcut_SRA;
    extern const std::vector <std::vector <double> > vv_cut_SRA;
    extern const std::vector <double> v_b_n_SRA;
    
    
    extern const std::vector <double> v_tau_n_SRB;
    extern const std::vector <double> v_tauTau_MET_mT2cut_SRB;
    extern const std::vector <double> v_METcut_SRB;
    extern const std::vector <double> v_tauTau_jet_HTcut_SRB;
    extern const std::vector <std::vector <double> > vv_cut_SRB;
    extern const std::vector <double> v_b_n_SRB;
    
    
    extern const std::vector <double> v_tau_n_SRC;
    extern const std::vector <double> v_tauBtauB_MET_mT2cut_SRC;
    extern const std::vector <double> v_METcut_SRC;
    extern const std::vector <double> v_tauTau_jet_HTcut_SRC;
    extern const std::vector <std::vector <double> > vv_cut_SRC;
    extern const std::vector <double> v_b_n_SRC;
    
    
    extern const std::vector <double> v_tau_n_SRD;
    extern const std::vector <double> v_tauTau_MET_mT2cut_SRD;
    extern const std::vector <double> v_tauBtauB_MET_mT2cut_SRD;
    extern const std::vector <double> v_METcut_SRD;
    extern const std::vector <std::vector <double> > vv_cut_SRD;
    extern const std::vector <double> v_b_n_SRD;
    
    
    extern const std::vector <double> v_tau_n_DYCR;
    extern const std::vector <double> v_tauTau_MET_mT2cut_DYCR;
    extern const std::vector <double> v_METcut_DYCR;
    extern const std::vector <double> v_tauTau_jet_HTcut_DYCR;
    extern const std::vector <std::vector <double> > vv_cut_DYCR;
    extern const std::vector <double> v_b_n_DYCR;
    
    
    std::string getSystSuffix(std::string syst_name, Common::SYST_TYPE syst);
    
    
    std::string getScaleVariationSuffix(int scaleVariationIndex);
    
    
    // If str1 = str2, will return syst; else SYST_CENTRAL
    SYST_TYPE chooseSystType(std::string str1, std::string str2, SYST_TYPE syst);
    int chooseTauTrigger2017systType(std::string str1, std::string str2, SYST_TYPE syst);
    std::string chooseTauIDsystType(std::string str1, std::string str2, SYST_TYPE syst);
    std::string chooseBTaggingSFsystType(std::string str1, std::string str2, SYST_TYPE syst);
    
    
    void scaleObject4mom(
        std::vector <std::vector <double>*> *vv_obj,
        double scale
    );
    
    
    void scaleObject4mom(
        std::vector <std::vector <double>*> *vv_obj,
        std::vector <double> *v_scale
    );
    
    
    void copy(std::vector <std::vector <double> *> *input, std::vector <std::vector <double> *> *output);
    
    
    void deleteElement(std::vector <std::vector <double> *> *obj, int index);
    
    
    TH1F* sumHistogram(std::vector <TH1F*> *v_hist);
    
    
    double getPileUpReweightFactor(TH1F *h_pileUp_mc, TH1F *h_pileUp_data, int pileUp_n);//, SYST_TYPE syst = SYST_CENTRAL);
    
    
    double getEventWeight_nJetBin(std::vector <double> v_eventWeight_nJetBin, int outgoingParton_n_gen);
    
    
    std::vector <double> get_eventWeight_nJetBin_DYJetsToLL(std::string era);
    
    
    std::vector <double> get_eventWeight_nJetBin_WJetsToLNu(std::string era);
    
    
    double getDeltaPhi(double phi1, double phi2);
    
    
    double getMagnitude(std::vector <double> v);
    
    
    std::vector <double> getBisector(std::vector <double> v1, std::vector <double> v2);
    
    
    double getMT(CLHEP::HepLorentzVector obj1_4mom, CLHEP::HepLorentzVector obj2_4mom);
    
    
    double getMT_massless(CLHEP::Hep3Vector obj1_3mom, CLHEP::Hep3Vector obj2_3mom);
    
    
    std::pair <std::pair <double, double>, std::pair <double, double> > getTopPtReweightFactor(
        std::vector <std::vector <double>*> *vv_top,
        SYST_TYPE syst
    );
    
    
    std::pair <double, double> getTopPtReweightFactor(double pT1, double pT2, SYST_TYPE syst = SYST_CENTRAL);
    
    
    std::pair <double, double> getZpTreweightFactor(CLHEP::HepLorentzVector Z_4mom, RooWorkspace *htt_scaleFactorWS, std::string era, SYST_TYPE syst = SYST_CENTRAL);
    
    
    double getPzeta(
        std::vector <std::vector <double> > vv,
        std::vector <double> vProj1,
        std::vector <double> vProj2
    );
    
    
    double getDzeta(
        std::vector <std::vector <double> > vv_vis,
        std::vector <double> v_inv,
        std::vector <double> vProj1,
        std::vector <double> vProj2
    );
    
    
    bool isEventSelected(
        std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        bool selection
    );
    
    
    std::vector <CLHEP::HepLorentzVector> objVectorTo4mom(
        std::vector <std::vector <double> *> *v_obj
    );
    
    
    /*std::vector <bool> isObjSelected(
        std::vector <CLHEP::HepLorentzVector> v_obj_4mom,
        std::vector <std::vector <double> > v_obj_selection,
        double obj_pTcut, double obj_etaCut
    );
    
    
    std::vector <std::vector <bool> > isMatched(
        std::vector <std::vector <double> *> *v_obj1,
        std::vector <std::vector <double> *> *v_obj2,
        
        std::vector <std::vector <double> > v_obj1_selection,
        std::vector <std::vector <double> > v_obj2_selection,
        
        double obj2_pTcut, double obj2_etaCut,
        double obj1_pTcut, double obj1_etaCut,
        
        double dRcut
    );
    
    
    std::vector <std::vector <bool> > isMatched(
        std::vector <CLHEP::HepLorentzVector> v_obj1_4mom,
        std::vector <CLHEP::HepLorentzVector> v_obj2_4mom,
        
        std::vector <std::vector <double> > v_obj1_selection,
        std::vector <std::vector <double> > v_obj2_selection,
        
        double obj2_pTcut, double obj2_etaCut,
        double obj1_pTcut, double obj1_etaCut,
        
        double dRcut
    );*/
    
    
    template <typename T1> bool isInJsonLumiRange(T1 list, long long lumiNumber)
    {
        for(int i = 0; i < list.size(); i++)
        {
            long long lwr = list[i][0];
            long long upr = list[i][1];
            
            bool isFound = (lwr <= lumiNumber && lumiNumber <= upr);
            
            if(isFound)
            {
                return true;
            }
        }
        
        return false;
    }
    
    
    bool isInRunJson(
        nlohmann::json jsonContent,
        long long runNumber,
        long long lumiNumber,
        bool debug = false
    );
    
    
    template <typename T1> int get_nSR(std::vector <std::vector <T1> > vv_info)
    {
        int nSR = 1;
        
        if(!vv_info.size())
        {
            //printf("Empty vector in Common::get_nSR(...). \n");
            //exit(EXIT_FAILURE);
            //return 0;
        }
        
        for(int i = 0; i < vv_info.size(); i++)
        {
            nSR *= vv_info.at(i).size();
        }
        
        return nSR;
    }
    
    
    template <typename T1> void setBinLwrThreshold(T1 *hist, double thr_lwr, double newBinVal)
    {
        for(int iBinX = 1; iBinX <= hist->GetNbinsX(); iBinX++)
        {
            for(int iBinY = 1; iBinY <= hist->GetNbinsY(); iBinY++)
            {
                if(hist->GetBinContent(iBinX, iBinY) < thr_lwr)
                {
                    hist->SetBinContent(iBinX, iBinY, newBinVal);
                    hist->SetBinError(iBinX, iBinY, sqrt(newBinVal));
                }
            }
        }
    }
    
    
    template <typename T1> void setBinUprThreshold(T1 *hist, double thr_upr, double newBinVal)
    {
        for(int iBinX = 1; iBinX <= hist->GetNbinsX(); iBinX++)
        {
            for(int iBinY = 1; iBinY <= hist->GetNbinsY(); iBinY++)
            {
                if(hist->GetBinContent(iBinX, iBinY) > thr_upr)
                {
                    hist->SetBinContent(iBinX, iBinY, newBinVal);
                    hist->SetBinError(iBinX, iBinY, sqrt(newBinVal));
                }
            }
        }
    }
    
    
    template <typename T1> T1* rebin2Dhistogram(T1 *hist,
        bool rebinX,
        std::vector <double> v_xBin_lwrEdge, 
        bool rebinY,
        std::vector <double> v_yBin_lwrEdge,
        bool replaceHist,
        bool debug = false
    )
    {
        TAxis *xAxis = hist->GetXaxis();
        TAxis *yAxis = hist->GetYaxis();
        
        if(!rebinX)
        {
            v_xBin_lwrEdge.clear();
            v_xBin_lwrEdge.resize(hist->GetNbinsX());
            xAxis->GetLowEdge(&v_xBin_lwrEdge[0]);
        }
        
        if(!rebinY)
        {
            v_yBin_lwrEdge.clear();
            v_yBin_lwrEdge.resize(hist->GetNbinsY());
            yAxis->GetLowEdge(&v_yBin_lwrEdge[0]);
        }
        
        if(debug)
        {
            printf("x-binning: %d --> %d \n", hist->GetNbinsX(), (int) v_xBin_lwrEdge.size());
            printf("y-binning: %d --> %d \n", hist->GetNbinsY(), (int) v_yBin_lwrEdge.size());
        }
        
        T1 *histNew = new T1(
            hist->GetName(), hist->GetTitle(),
            v_xBin_lwrEdge.size()-1, &v_xBin_lwrEdge[0],
            v_yBin_lwrEdge.size()-1, &v_yBin_lwrEdge[0]
        );
        
        histNew->SetDirectory(0);
        histNew->Sumw2();
        
        // INCLUDING over/underflow bins
        for(int iBinX = 0; iBinX <= hist->GetNbinsX()+1; iBinX++)
        {
            for(int iBinY = 0; iBinY <= hist->GetNbinsY()+1; iBinY++)
            {
                double binContent = hist->GetBinContent(iBinX, iBinY);
                double binErr = hist->GetBinError(iBinX, iBinY);
                
                double binLocationX = xAxis->GetBinCenter(iBinX);
                double binLocationY = yAxis->GetBinCenter(iBinY);
                
                //if((!iBinX && !iBinY) || (iBinX == hist->GetNbinsX()+1 && iBinY == hist->GetNbinsY()+1))
                //{
                //    printf("binLocationX %f, binLocationY %f \n", binLocationX, binLocationY);
                //}
                
                //histNew->Fill(binLocationX, binLocationY, binContent);
                
                int binX_histNew = histNew->GetXaxis()->FindBin(binLocationX);
                int binY_histNew = histNew->GetYaxis()->FindBin(binLocationY);
                
                double binErr_histNew = histNew->GetBinError(binX_histNew, binY_histNew);
                
                histNew->Fill(binLocationX, binLocationY, binContent);
                histNew->SetBinError(
                    binX_histNew, binY_histNew,
                    sqrt(binErr*binErr+binErr_histNew*binErr_histNew)
                );
            }
        }
        
        if(replaceHist)
        {
            hist->SetDirectory(0);
            delete hist;
            
            hist = histNew;
        }
        
        return histNew;
    }
    
    
    // h_type only used to determine the histogram type
    // So, simply passing "new TH1F()" or "new TH2F()" is enough
    template <typename T1> T1* getHistogram(std::vector <std::string> v_fileName, std::string histName, T1 *h_type)
    {
        if (!v_fileName.size())
        {
            printf("Error in Common::getHistogram(...): File list cannot be empty. \n");
            exit(EXIT_FAILURE);
        }
        
        printf("Common::getHistogram(...): Getting histogram %s \n", histName.c_str());
        
        T1 *hist;
        //hist = 0;
        
        for(int iFile = 0; iFile < v_fileName.size(); iFile++)
        {
            TFile *tempFile = TFile::Open(v_fileName.at(iFile).c_str(), "READ");
            
            printf("Opening file: %s \n", v_fileName.at(iFile).c_str());
            
            if(!iFile)
            {
                hist = (T1*) tempFile->Get(histName.c_str())->Clone();
                hist->Sumw2();
                hist->SetDirectory(0);
            }
            
            else
            {
                hist->Add((T1*) tempFile->Get(histName.c_str())->Clone());
            }
            
            tempFile->Close();
            delete tempFile;
            
            hist->Print();
        }
        
        //hist->Print();
        
        delete h_type;
        
        printf("Common::getHistogram(...): Got histogram %s \n", histName.c_str());
        return hist;
    }
    
    
    double getBTaggingEventWeight(std::vector <std::vector <double>* > *v_jet,
        double pTcut, double etaCut,
        std::vector <double> *v_jet_flavour,
        std::vector <double> *v_jet_isTagged,
        BTagCalibrationReader *bTagCalibReader,
        std::string sysType,
        std::string effFileName,
        std::string effHistName_b,
        std::string effHistName_c,
        std::string effHistName_udsg,
        std::vector <std::pair <std::vector <CLHEP::HepLorentzVector>, double> > vp_obj4mom_deltaR_min);
    
    
    std::vector <int> getElMuPair(std::vector <std::vector <double>* > *v_el_reco,
        std::vector <std::vector <double>* > *v_mu_reco,
        std::vector <std::vector <double>* > v_elSelection,
        std::vector <std::vector <double>* > v_muSelection,
        double deltaR_min,
        const char *signOption);
    
    
    bool isTauNewDM(int tauDM);
    bool isTauNewDM(bool byNewDM, int tauDM);
    
    // If preserveOrder is true then obj1 and obj2 are treated as leading and subleading respectively in the pair.
    // That is, obj1 is subleading, then the pair is rejected.
    std::vector <int> getObjPair(
        std::vector <std::vector <double>* > *v_obj1_reco, 
        std::vector <std::vector <double>* > *v_obj2_reco,
        bool areObjsSame,
        std::vector <std::vector <double>* > v_obj1Selection,
        std::vector <std::vector <double>* > v_obj2Selection,
        double deltaR_min,
        const char *signOption,
        bool preserveOrder = false
    );
    
    
    std::vector <std::vector <int> > getTauPair(std::vector <std::vector <double>* > *v_tau_reco,
        std::vector <double> v_eventSelection,
        std::vector <std::vector <double>* > v_tauSelection,
        double deltaR_min,
        const char *signOption);
    
    
    bool isSeparated(CLHEP::HepLorentzVector object1_4mom,
        std::vector <std::vector <double>* > *v_object2,
        double dR_min,
        std::vector <int> v_object2_index = {});
    
    
    std::pair <double, double> getTauSF(
        double tau_pT, double tau_eta,
        std::string WPname
    );
    
    
    void parseCSVto2Dvector(std::string fileName,
        std::vector <std::vector <double> > *vv_info
    );
    
    
    double get_lepBlepB_mT2(
        CLHEP::HepLorentzVector lep1_4mom,
        CLHEP::HepLorentzVector b1_4mom,
        CLHEP::HepLorentzVector lep2_4mom,
        CLHEP::HepLorentzVector b2_4mom,
        double MET_x, double MET_y
    );
    
    
    std::vector <int> get_SRpos(
        int findBin,
        std::vector <std::vector <double> > vv_cut
    );
    
    
    bool doesFileExist(std::string fileName);
    
    
    double evaluateExpression(
        std::string expression,
        std::vector <std::pair <std::string, double> > vp_info,
        bool debug = false
    );
    
    
    // For di-tau trigger
    // From https://github.com/rmanzoni/triggertools/blob/master/objects/FitFunctions.py
    double crystalballEfficiency(
        double m,
        double m0,
        double sigma,
        double alpha,
        double n,
        double norm
    );
    
    
    double getTauTriggerEffFromJson(
        nlohmann::json jsonContent,
        std::string WPname,
        double pT
    );
    
    
    double getTauTriggerEffFromJson_data(
        nlohmann::json jsonContent,
        std::string WPname,
        double decayMode,
        double pT
    );
    
    
    double getTauTriggerEffFromJson_mc(
        nlohmann::json jsonContent,
        std::string WPname,
        double decayMode,
        double pT
    );
    
    
    double getTauTriggerSFfromJson(
        nlohmann::json jsonContent,
        std::string WPname,
        double decayMode,
        double pT
    );
}


# endif

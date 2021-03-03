# include <algorithm>
# include <fstream>
# include <iostream>
# include <sstream>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include "TH1F.h"
# include "TMath.h"
# include "TVector2.h"

# include "exprtk.hpp"
# include "Common.h"


namespace Common
{
    const int str_len = 1000;
    
    const char delimiter[] = "@@@";
    
    //const std::vector <int> v_colorIndex = {
    //    2, 4, 5, 6, 7, 8,
    //    28, 41, 46
    //};
    
    const std::vector <int> v_colorIndex_bg = {
        kRed-9, kRed,
        kMagenta,
        kBlue-10, kBlue,
        kCyan,
        kGreen-10, kGreen,
        kOrange-3, kOrange,
    };
    
    const std::vector <int> v_colorIndex_sig = {
        kRed,
        kMagenta,
        kBlue,
        kCyan,
        kGreen
    };
    
    
    const std::string process_str_template = "@process@";
    const std::string dir_str_template = "@dir@";
    const std::string otherInfoDir_str_template = "@otherInfoDir@";
    const std::string sourceFileName_str_template = "@sourceFileName@";
    const std::string era_str_template = "@era@";
    const std::string syst_name_template = "@syst_name@";
    
    const std::string stop1_m_str_template = "@stop1_m@";
    const std::string neutralino_m_str_template = "@neutralino1_m@";
    
    const std::vector <double> v_eventWeight_nJetBin_DYJetsToLL_2016 = {
        0.0596468347,
        0.0143028993,
        0.0146362526,
        0.0151027234,
        0.0121014445
    };
    
    //const std::vector <double> v_eventWeight_nJetBin_DYJetsToLL_2017 = {
    //    0.1173604918,
    //    0.0241086398,
    //    0.0278500867,
    //    0.0575406755,
    //    0.0107531353
    //};
    
    const std::vector <double> v_eventWeight_nJetBin_DYJetsToLL_2017 = {
        //0.1173604918,
        //0.0269577152,
        //0.0297907646,
        //0.0548647629,
        //0.0130817693
        
        //0.1267246597,
        //0.0260322628,
        //0.030072239,
        //0.0621318333,
        //0.0116111256
        
        0.126890154,
        0.0245354431,
        0.0284100681,
        0.0598188062,
        0.0108522237
    };
    
    
    const std::vector <double> v_eventWeight_nJetBin_WJetsToLNu_2016 = {
        1.0789225515,
        0.2092672861,
        0.1148469207,
        0.055848229,
        0.0610123474
    };
    
    const std::vector <double> v_eventWeight_nJetBin_WJetsToLNu_2017 = {
        1.3786816112,
        0.1613827828,
        0.376836314,
        0.0588695484,
        0.0562572808
    };
    
    
    const std::map <std::string, std::vector <double> > m_eventWeight_nJetBin_DYJetsToLL = {
        {"2016", v_eventWeight_nJetBin_DYJetsToLL_2016},
        {"2017", v_eventWeight_nJetBin_DYJetsToLL_2017}
    };
    
    
    const std::map <std::string, std::vector <double> > m_eventWeight_nJetBin_WJetsToLNu = {
        {"2016", v_eventWeight_nJetBin_WJetsToLNu_2016},
        {"2017", v_eventWeight_nJetBin_WJetsToLNu_2017}
    };
    
    
    const std::string topPtReweighting_str = "topPtReweighting";
    const std::string ZptReweighting_str = "ZptReweighting";
    
    const std::map <std::string, bool> m_correction = {
        {topPtReweighting_str, false},
        {ZptReweighting_str, false},
    };
    
    
    const std::vector <double> v_ISRweight = {
        1.000,
        0.920,
        0.821,
        0.715,
        0.662,
        0.561,
        0.511
    };
    
    
    const std::vector <std::string> v_bDiscriminatorName = {
        //"pfCombinedInclusiveSecondaryVertexV2BJetTags"
        "pfDeepFlavourJetTags"
    };
    
    const std::vector <std::vector <std::string> > vv_bDiscriminatorWPname = {
        //{"CSVv2L", "CSVv2M", "CSVv2T"}
        {"DeepJetL", "DeepJetM", "DeepJetT"}
    };
    
    const std::vector <double> v_pT_bin_bTaggingEfficiency = {
        0, 20, 30, 50, 70, 100, 140, 200, 300, 600, 1000, 2000
    };
    
    const std::vector <double> v_eta_bin_bTaggingEfficiency = {
        -3, -2.4, -1.2, 0, 1.2, 2.4, 3
    };
    
    
    extern const std::vector <double> v_pT_bin_tauFastFullSF = {
        0, 40, 60, 80, 100, 150, 300, 2000
    };
    
    extern const std::vector <double> v_eta_bin_tauFastFullSF = {
        -3, -2.1, -1.2, -0.6, 0, 0.6, 1.2, 2.1, 3
    };
    
    
    // GEN ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    const double
        el_pTcut_gen = 30,
        el_etaCut_gen = 2.4,
        
        mu_pTcut_gen = 30,
        mu_etaCut_gen = 2.4,
        
        tau_vis_pTcut_gen = 40,
        tau_vis_etaCut_gen = 2.1,
        
        t_pTcut_gen = 20,
        t_etaCut_gen = 2.4,
        
        b_pTcut_gen = 20,
        b_etaCut_gen = 2.4,
        
        W_pTcut_gen = 20,
        W_etaCut_gen = 2.4,
        
        Z_pTcut_gen = 20,
        Z_etaCut_gen = 2.4,
        
        jet_pTcut_gen = 20,
        jet_etaCut_gen = 2.4;
    
    
    // RECO ////////////////////////////////////////////////////////////////////////////////////////////////////
    
    const double
        el_pTcut_elMu_reco = 30,
        el_etaCut_elMu_reco = 2.4,
        
        // cm
        el_dxyCut_reco = 0.045,
        el_dzCut_reco = 0.2,
        
        el_missingInnerHitsCut_reco = 1,
        
        mu_pTcut_elMu_reco = 30,
        mu_etaCut_elMu_reco = 2.4,
        
        mu_pTcut_muMu_reco = 30,
        mu_etaCut_muMu_reco = 2.4,
        
        mu_pTcut_muTau_reco = 30,
        mu_etaCut_muTau_reco = 2.1,
        
        // cm
        mu_dxyCut_reco = 0.045,
        mu_dzCut_reco = 0.2,
        
        elMu_deltaRcut_reco = 0.3,
        muMu_deltaRcut_reco = 0.3,
        
        tau_pTcut_tauTau_reco = 40,
        tau_etaCut_tauTau_reco = 2.1,
        
        tau_pTcut_muTau_reco = 30,
        tau_etaCut_muTau_reco = 2.3,
        
        // cm
        tau_dzCut_reco = 0.2,
        
        tauTau_deltaRcut_reco = 0.5,
        muTau_deltaRcut_reco = 0.5,
        
        jet_pTcut_reco = 20,
        jet_etaCut_reco = 2.4, 
        
        b_pTcut_reco = 20,
        b_etaCut_reco = 2.4;
    
    
    const std::vector <double> v_tau_promptFake_pTbin = {0, 40, 80, 150, 300, 500};
    
    
    const std::vector <double> v_tau_n_SRA = {2};
    const std::vector <double> v_tauTau_MET_mT2cut_SRA = {0, 40, 80};
    const std::vector <double> v_METcut_SRA = {50, 200};
    const std::vector <double> v_jet_n_SRA = {2};
    const std::vector <double> v_b_n_SRA = {1};
    
    const std::vector <std::vector <double> > vv_cut_SRA = {
        v_tau_n_SRA,
        v_tauTau_MET_mT2cut_SRA,
        v_METcut_SRA,
        //v_jet_n_SRA,
        v_b_n_SRA
    };
    
    
    const std::vector <double> v_tau_n_SRB = {2};
    const std::vector <double> v_tauTau_MET_mT2cut_SRB = {0, 40, 80};
    const std::vector <double> v_METcut_SRB = {50, 200};
    const std::vector <double> v_tauTau_jet_HTcut_SRB = {100, 300, 700};
    const std::vector <double> v_jet_n_SRB = {2};
    const std::vector <double> v_b_n_SRB = {1};
    
    const std::vector <std::vector <double> > vv_cut_SRB = {
        v_tau_n_SRB,
        v_tauTau_MET_mT2cut_SRB,
        v_METcut_SRB,
        v_tauTau_jet_HTcut_SRB,
        //v_jet_n_SRB,
        v_b_n_SRB
    };
    
    
    const std::vector <double> v_tau_n_SRC = {2};
    const std::vector <double> v_tauBtauB_MET_mT2cut_SRC = {0, 85, 170};
    const std::vector <double> v_METcut_SRC = {50, 200};
    const std::vector <double> v_tauTau_jet_HTcut_SRC = {100, 300, 700};
    const std::vector <double> v_jet_n_SRC = {2};
    const std::vector <double> v_b_n_SRC = {1};
    
    const std::vector <std::vector <double> > vv_cut_SRC = {
        v_tau_n_SRC,
        v_tauBtauB_MET_mT2cut_SRC,
        v_METcut_SRC,
        v_tauTau_jet_HTcut_SRC,
        //v_jet_n_SRC,
        v_b_n_SRC
    };
    
    
    const std::vector <double> v_tau_n_SRD = {2};
    const std::vector <double> v_tauTau_MET_mT2cut_SRD = {0, 40, 80};
    const std::vector <double> v_tauBtauB_MET_mT2cut_SRD = {0, 85, 170};
    const std::vector <double> v_METcut_SRD = {50, 200};
    const std::vector <double> v_jet_n_SRD = {2};
    const std::vector <double> v_b_n_SRD = {1};
    
    const std::vector <std::vector <double> > vv_cut_SRD = {
        v_tau_n_SRD,
        v_tauTau_MET_mT2cut_SRD,
        v_METcut_SRD,
        v_tauBtauB_MET_mT2cut_SRD,
        //v_jet_n_SRD,
        v_b_n_SRD
    };
    
    
    const std::vector <double> v_tau_n_DYCR = {2};
    const std::vector <double> v_tauTau_MET_mT2cut_DYCR = {0, 40, 80};
    const std::vector <double> v_METcut_DYCR = {30, 100};
    const std::vector <double> v_tauTau_jet_HTcut_DYCR = {100, 300, 700};
    const std::vector <double> v_b_n_DYCR = {0};
    
    const std::vector <std::vector <double> > vv_cut_DYCR = {
        v_tau_n_DYCR,
        v_tauTau_MET_mT2cut_DYCR,
        v_METcut_DYCR,
        v_tauTau_jet_HTcut_DYCR,
        v_b_n_DYCR
    };
    
    
    std::string getSystSuffix(std::string syst_name, SYST_TYPE syst)
    {
        std::string suffix = "";
        
        switch(syst)
        {
            case SYST_CENTRAL: 
                suffix = "";
                break;
            
            case SYST_UP:
                suffix = "_" + syst_name + "-systUp";
                break;
            
            case SYST_DOWN:
                suffix = "_" + syst_name + "-systDown";
                break;
            
            case SYST_ONESIDED:
                suffix = "_" + syst_name;
                break;
            
            default:
                printf("Error in Common::getSystSuffix(...): Invalid systematic type provided.");
                exit(EXIT_FAILURE);
        }
        
        return suffix;
    }
    
    
    std::string getScaleVariationSuffix(int scaleVariationIndex)
    {
        std::string suffix = "";
        
        switch(scaleVariationIndex)
        {
            case 0: 
                suffix = "";
                break;
            
            default:
                suffix = "_scale" + std::to_string(scaleVariationIndex);
                break;
        }
        
        return suffix;
    }
    
    
    SYST_TYPE chooseSystType(std::string str1, std::string str2, SYST_TYPE syst)
    {
        if(!str1.compare(str2))
        {
            return syst;
        }
        
        else
        {
            return SYST_CENTRAL;
        }
    }
    
    
    std::string chooseTauIDsystType(std::string str1, std::string str2, SYST_TYPE syst)
    {
        if(!str1.compare(str2))
        {
            switch(syst)
            {
                case SYST_CENTRAL: 
                    return "";
                
                case SYST_UP:
                    return "Up";
                
                case SYST_DOWN:
                    return "Down";
                
                default:
                    printf("Error in Common::chooseTauIDsystType(...): Invalid systematic type provided.");
                    exit(EXIT_FAILURE);
            }
        }
        
        else
        {
            return "";
        }
    }
    
    
    int chooseTauTrigger2017systType(std::string str1, std::string str2, SYST_TYPE syst)
    {
        if(!str1.compare(str2))
        {
            switch(syst)
            {
                case SYST_CENTRAL: 
                    return TauTriggerSFs2017::kCentral;
                
                case SYST_UP:
                    return TauTriggerSFs2017::kStatUp;
                
                case SYST_DOWN:
                    return TauTriggerSFs2017::kStatDown;
                
                default:
                    printf("Error in Common::chooseTauTrigger2017systType(...): Invalid systematic type provided.");
                    exit(EXIT_FAILURE);
            }
        }
        
        else
        {
            return TauTriggerSFs2017::kCentral;
        }
    }
    
    
    std::string chooseBTaggingSFsystType(std::string str1, std::string str2, SYST_TYPE syst)
    {
        if(!str1.compare(str2))
        {
            switch(syst)
            {
                case SYST_CENTRAL: 
                    return "central";
                
                case SYST_UP:
                    return "up";
                
                case SYST_DOWN:
                    return "down";
                
                default:
                    printf("Error in Common::chooseTauTrigger2017systType(...): Invalid systematic type provided.");
                    exit(EXIT_FAILURE);
            }
        }
        
        else
        {
            return "central";
        }
    }
    
    
    void scaleObject4mom(
        std::vector <std::vector <double>*> *vv_obj,
        double scale
    )
    {
        for(int iObj = 0; iObj < vv_obj->at(0)->size(); iObj++)
        {
            vv_obj->at(0)->at(iObj) *= scale;
            vv_obj->at(1)->at(iObj) *= scale;
            vv_obj->at(2)->at(iObj) *= scale;
            vv_obj->at(3)->at(iObj) *= scale;
        }
    }
    
    
    void scaleObject4mom(
        std::vector <std::vector <double>*> *vv_obj,
        std::vector <double> *v_scale
    )
    {
        if(vv_obj->at(0)->size() != v_scale->size())
        {
            printf("Error in Common::scaleObject4mom(...): Size mismatch.");
            printf("Size of vv_obj: %d \n", vv_obj->size());
            printf("Size of v_scale: %d \n", v_scale->size());
            exit(EXIT_FAILURE);
        }
        
        for(int iObj = 0; iObj < vv_obj->at(0)->size(); iObj++)
        {
            double scale = v_scale->at(iObj);
            
            //printf("obj %d/%d: scale %0.4f \n", iObj+1, vv_obj->at(0)->size(), scale);
            
            vv_obj->at(0)->at(iObj) *= scale;
            vv_obj->at(1)->at(iObj) *= scale;
            vv_obj->at(2)->at(iObj) *= scale;
            vv_obj->at(3)->at(iObj) *= scale;
        }
    }
    
    
    void copy(std::vector <std::vector <double> *> *input, std::vector <std::vector <double> *> *output)
    {
        for(int i = 0; i < input->size(); i++)
        {
            for(int j = 0; j < input->at(i)->size(); j++)
            {
                output->at(i)->push_back(input->at(i)->at(j));
            }
        }
    }
    
    
    void deleteElement(std::vector <std::vector <double> *> *obj, int index)
    {
        for(int i = 0; i < obj->size(); i++)
        {
            obj->at(i)->erase(obj->at(i)->begin() + index);
        }
    }
    
    
    TH1F* sumHistogram(std::vector <TH1F*> *v_hist)
    {
        if (!v_hist->size())
        {
            return 0;
        }
        
        TH1F *histSum = (TH1F*) v_hist->at(0)->Clone();
    
        for(int iHist = 1; iHist < v_hist->size(); iHist++)
        {
            histSum->Add(v_hist->at(iHist));
        }
        
        return histSum;
    }
    
    
    double getPileUpReweightFactor(TH1F *h_pileUp_mc, TH1F *h_pileUp_data, int pileUp_n)//, SYST_TYPE syst)
    {
        int pileUpBin_data = h_pileUp_data->FindBin(pileUp_n);
        int pileUpBin_mc = h_pileUp_mc->FindBin(pileUp_n);
        
        double num = h_pileUp_data->GetBinContent(pileUpBin_data);
        double den = h_pileUp_mc->GetBinContent(pileUpBin_mc);
        
        //double numErr = h_pileUp_data->GetBinError(pileUpBin_data);
        //double denErr = h_pileUp_mc->GetBinError(pileUpBin_mc);
        
        double factor = 1;
        //double err = 0;
        
        if(den > 0 && num > 0)
        {
            factor = num / den;
            
            //if(syst != SYST_CENTRAL)
            //{
            //    // Z = X/Y
            //    // dZ/Z = sqrt((dX/X)^2 + (dY/Y)^2)
            //    double numErrRel = numErr / num;
            //    double denErrRel = denErr / den;
            //    
            //    err = factor * sqrt(numErrRel*numErrRel + denErrRel*denErrRel);
            //    
            //    factor += syst*err;
            //}
        }
        
        return factor;
    }
    
    
    double getEventWeight_nJetBin(std::vector <double> v_eventWeight_nJetBin, int outgoingParton_n_gen)
    {
        if(outgoingParton_n_gen < 0)
        {
            printf("ERROR: Common::getEventWeight_nJetBin(...): outgoingParton_n_gen < 0 \n");
            
            exit(EXIT_FAILURE);
        }
        
        double eventWeight = 1;
        
        if(outgoingParton_n_gen < v_eventWeight_nJetBin.size())
        {
            eventWeight = v_eventWeight_nJetBin[outgoingParton_n_gen];
        }
        
        return eventWeight;
    }
    
    
    std::vector <double> get_eventWeight_nJetBin_DYJetsToLL(std::string era)
    {
        if(m_eventWeight_nJetBin_DYJetsToLL.find(era) == m_eventWeight_nJetBin_DYJetsToLL.end())
        {
            printf("Error in Common::get_eventWeight_nJetBin_DYJetsToLL(...): Key \"%s\" not found. \n", era.c_str());
            exit(EXIT_FAILURE);
        }
        
        printf("\n");
        printf("Using DYJetsToLL n-jet event-weight for %s. \n\n", era.c_str());
        
        return m_eventWeight_nJetBin_DYJetsToLL.at(era);
    }
    
    
    std::vector <double> get_eventWeight_nJetBin_WJetsToLNu(std::string era)
    {
        if(m_eventWeight_nJetBin_WJetsToLNu.find(era) == m_eventWeight_nJetBin_WJetsToLNu.end())
        {
            printf("Error in Common::get_eventWeight_nJetBin_WJetsToLNu(...): Key \"%s\" not found. \n", era.c_str());
            exit(EXIT_FAILURE);
        }
        
        printf("\n");
        printf("Using WJetsToLNu n-jet event-weight for %s. \n\n", era.c_str());
        
        return m_eventWeight_nJetBin_WJetsToLNu.at(era);
    }
    
    
    double getDeltaPhi(double phi1, double phi2)
    {
        double deltaPhi = phi1 - phi2;
        
        //deltaPhi = (deltaPhi > M_PI)? (deltaPhi - M_PI): deltaPhi;
        //deltaPhi = (deltaPhi < -M_PI)? (deltaPhi + M_PI): deltaPhi;
        
        deltaPhi = TVector2::Phi_mpi_pi(deltaPhi);
        
        return deltaPhi;
    }
    
    
    double getMagnitude(std::vector <double> v)
    {
        double mag = 0;
        
        for(int i = 0; i < v.size(); i++)
        {
            mag += v[i]*v[i];
        }
        
        mag = sqrt(mag);
        
        return mag;
    }
    
    
    double getMT(CLHEP::HepLorentzVector obj1_4mom, CLHEP::HepLorentzVector obj2_4mom)
    {
        double mT = 0;
        
        double ET1 = obj1_4mom.mt();
        double ET2 = obj2_4mom.mt();
        
        mT = sqrt(pow(ET1+ET2, 2) - (obj1_4mom+obj2_4mom).perp2());
        
        
        return mT;
    }
    
    
    double getMT_massless(CLHEP::Hep3Vector obj1_3mom, CLHEP::Hep3Vector obj2_3mom)
    {
        double mT = 0;
        
        double deltaPhi = getDeltaPhi(obj1_3mom.phi(), obj2_3mom.phi());
        
        mT = sqrt(2.0*obj1_3mom.perp()*obj2_3mom.perp()*(1.0 - cos(deltaPhi)));
        
        return mT;
    }
    
    
    std::vector <double> getBisector(std::vector <double> v1, std::vector <double> v2)
    {
        if(v1.size() != v2.size())
        {
            printf("Error in getBisector: vector dimensions must be equal. \n");
            
            exit(EXIT_FAILURE);
        }
        
        double mag1 = getMagnitude(v1);
        double mag2 = getMagnitude(v2);
        
        if(mag1 == 0)
        {
            printf("Error in Common::getBisector: vector 1 magnitude is zero. \n");
            
            exit(EXIT_FAILURE);
        }
        
        if(mag2 == 0)
        {
            printf("Error in Common::getBisector: vector 2 magnitude is zero. \n");
            
            exit(EXIT_FAILURE);
        }
        
        
        int nElement = v1.size();
        
        std::vector <double> bisector(nElement, 0);
        
        for(int iElement = 0; iElement < nElement; iElement++)
        {
            bisector[iElement] = v1[iElement]/mag1 + v2[iElement]/mag2;
        }
        
        double magBisector = getMagnitude(bisector);
        
        for(int iElement = 0; iElement < nElement; iElement++)
        {
            bisector[iElement] /= magBisector;
        }
        
        return bisector;
    }
    
    
    double getPzeta(
        std::vector <std::vector <double> > vv,
        std::vector <double> v_proj1,
        std::vector <double> v_proj2)
    {
        if(vv[0].size() != v_proj1.size() || v_proj1.size() != v_proj2.size())
        {
            printf("Error in Common::getPzeta: vector dimensions must be equal. \n");
            
            exit(EXIT_FAILURE);
        }
        
        int nElement = v_proj1.size();
        
        std::vector <double> bisector = getBisector(v_proj1, v_proj2);
        
        double pZeta = 0;
        
        for(int iElement = 0; iElement < nElement; iElement++)
        {
            double vvSum = 0;
            
            for(int iVector = 0; iVector < vv.size(); iVector++)
            {
                vvSum += vv[iVector][iElement];
            }
            
            pZeta += vvSum * bisector[iElement];
        }
        
        return pZeta;
    }
    
    
    double getDzeta(
        std::vector <std::vector <double> > vv_vis,
        std::vector <double> v_inv,
        std::vector <double> v_proj1,
        std::vector <double> v_proj2
    )
    {
        std::vector <std::vector <double> > vv_temp = vv_vis;
        
        vv_temp.push_back(v_inv);
        
        double vis_pZeta = getPzeta(
            vv_vis,
            v_proj1,
            v_proj2
        );
        
        double vis_inv_pZeta = getPzeta(
            vv_temp,
            v_proj1,
            v_proj2
        );
        
        double vis_inv_Dzeta = vis_inv_pZeta - 1.85*vis_pZeta;
        
        return vis_inv_Dzeta;
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
        std::vector <std::pair <std::vector <CLHEP::HepLorentzVector>, double> > vp_obj4mom_deltaR_min)
    {
        int jet_n = v_jet->at(0)->size();
        
        double eventWeight = 1;
        
        // Probability of finding a configuration in MC
        double P_MC = 1;
        // Probability of finding the same configuration in DATA
        double P_DATA = 1;
        
        std::vector <double> v_efficiency;
        std::vector <double> v_scaleFactor;
        
        TFile *effFile = TFile::Open(effFileName.c_str(), "READ");
        
        TH1F *effHist_b = (TH1F*) effFile->Get(effHistName_b.c_str())->Clone();
        TH1F *effHist_c = (TH1F*) effFile->Get(effHistName_c.c_str())->Clone();
        TH1F *effHist_udsg = (TH1F*) effFile->Get(effHistName_udsg.c_str())->Clone();
        
        for(int iJet = 0; iJet < jet_n; iJet++)
        {
            CLHEP::HepLorentzVector jet_4mom;
            
            jet_4mom.setT(fabs(v_jet->at(0)->at(iJet)));
            jet_4mom.setX(v_jet->at(1)->at(iJet));
            jet_4mom.setY(v_jet->at(2)->at(iJet));
            jet_4mom.setZ(v_jet->at(3)->at(iJet));
            
            double jet_pT = jet_4mom.perp();
            double jet_eta = jet_4mom.eta();
            
            if(jet_pT < pTcut || fabs(jet_eta) > etaCut)
            {
                continue;
            }
            
            // Check for overlap with the given objects
            bool isOverlap = false;
            
            for(int iObjVec = 0; iObjVec < vp_obj4mom_deltaR_min.size() && !isOverlap; iObjVec++)
            {
                std::vector <CLHEP::HepLorentzVector> v_obj4mom = vp_obj4mom_deltaR_min.at(iObjVec).first;
                double deltaR_min = vp_obj4mom_deltaR_min.at(iObjVec).second;
                
                for(int iObj = 0; iObj < v_obj4mom.size(); iObj++)
                {
                    CLHEP::HepLorentzVector obj_4mom = v_obj4mom.at(iObj);
                    
                    if(jet_4mom.deltaR(obj_4mom) < deltaR_min)
                    {
                        isOverlap = true;
                        break;
                    }
                }
            }
            
            if(isOverlap)
            {
                continue;
            }
            
            int binX;
            int binY;
            
            double efficiency = 0;
            
            BTagEntry::JetFlavor jetFlavor;
            
            // b
            if(abs(v_jet_flavour->at(iJet)) == 5)
            {
                jetFlavor = BTagEntry::FLAV_B;
                
                binX = effHist_b->GetXaxis()->FindBin(jet_eta);
                binY = effHist_b->GetYaxis()->FindBin(jet_pT);
                efficiency = effHist_b->GetBinContent(binX, binY);
            }
            
            // c
            else if(abs(v_jet_flavour->at(iJet)) == 4)
            {
                jetFlavor = BTagEntry::FLAV_C;
                
                binX = effHist_c->GetXaxis()->FindBin(jet_eta);
                binY = effHist_c->GetYaxis()->FindBin(jet_pT);
                efficiency = effHist_c->GetBinContent(binX, binY);
            }
            
            // udsg
            else
            {
                jetFlavor = BTagEntry::FLAV_UDSG;
                
                binX = effHist_udsg->GetXaxis()->FindBin(jet_eta);
                binY = effHist_udsg->GetYaxis()->FindBin(jet_pT);
                efficiency = effHist_udsg->GetBinContent(binX, binY);
            }
            
            double scaleFactor = 0;
            double scalefactor = bTagCalibReader->eval_auto_bounds(
                sysType, 
                jetFlavor, 
                jet_eta, 
                jet_pT
            );
            
            //printf("pT %f, eta %f, isTagged %d, flavour %d, bTaggingEff %f, bTaggingEffSF %f \n",
            //    jet_pT, jet_eta, (int) v_jet_isTagged->at(iJet), abs(v_jet_flavour->at(iJet)), efficiency, scalefactor);
            
            if(v_jet_isTagged->at(iJet))
            {
                P_MC *= efficiency;
                P_DATA *= scalefactor*efficiency;
            }
            
            else
            {
                double temp;
                
                temp = 1 - efficiency;
                
                // May be redundant as eff cannot (should not!) be more than 1
                if(temp < 0)
                {
                    temp = 1;
                }
                
                P_MC *= temp;
                
                // Needed as SF*eff "can" overshoot 1: 1.15*0.9 = 1.035
                temp = 1 - scalefactor*efficiency;
                
                if(temp < 0)
                {
                    temp = 1;
                }
                
                P_DATA *= temp;
            }
        }
        
        // Check when denominator is zero
        if(P_MC == 0)
        {
            eventWeight = 1;
        }
        
        else
        {
            eventWeight = P_DATA/P_MC;
        }
        
        delete effHist_b;
        delete effHist_c;
        delete effHist_udsg;
        
        effFile->Close();
        delete effFile;
        
        return eventWeight;
    }
    
    
    std::vector <int> getElMuPair(std::vector <std::vector <double>* > *v_el,
        std::vector <std::vector <double>* > *v_mu,
        std::vector <std::vector <double>* > v_elSelection,
        std::vector <std::vector <double>* > v_muSelection,
        double deltaR_min,
        const char *signOption)
    {
        std::vector <int> v_selectedEl_pos;
        std::vector <int> v_selectedMu_pos;
        
        // El selection
        for(int iEl = 0; iEl < v_el->at(0)->size(); iEl++)
        {
            bool isSelected = true;
            
            for(int iSelection = 0; iSelection < v_elSelection.size(); iSelection++)
            {
                if(!v_elSelection.at(iSelection)->at(iEl))
                {
                    isSelected = false;
                    break;
                }
            }
            
            if(isSelected)
            {
                v_selectedEl_pos.push_back(iEl);
            }
        }
        
        if(!v_selectedEl_pos.size())
        {
            return {};
        }
        
        // Mu selection
        for(int iMu = 0; iMu < v_mu->at(0)->size(); iMu++)
        {
            bool isSelected = true;
            
            for(int iSelection = 0; iSelection < v_muSelection.size(); iSelection++)
            {
                if(!v_muSelection.at(iSelection)->at(iMu))
                {
                    isSelected = false;
                    
                    break;
                }
            }
            
            if(isSelected)
            {
                v_selectedMu_pos.push_back(iMu);
            }
        }
        
        if(!v_selectedMu_pos.size())
        {
            return {};
        }
        
        
        double elMuPair_HT = 0;
        std::vector <int> v_elMuPair_pos(2, -1);
        
        // El-Mu pair selection
        for(int iEl = 0; iEl < v_selectedEl_pos.size(); iEl++)
        {
            int iSelectedEl = v_selectedEl_pos.at(iEl);
            
            for(int iMu = 0; iMu < v_selectedMu_pos.size(); iMu++)
            {
                int iSelectedMu = v_selectedMu_pos.at(iMu);
                
                CLHEP::HepLorentzVector el_4mom;
                el_4mom.setT(fabs(v_el->at(0)->at(iSelectedEl)));
                el_4mom.setX(v_el->at(1)->at(iSelectedEl));
                el_4mom.setY(v_el->at(2)->at(iSelectedEl));
                el_4mom.setZ(v_el->at(3)->at(iSelectedEl));
                
                CLHEP::HepLorentzVector mu_4mom;
                mu_4mom.setT(fabs(v_mu->at(0)->at(iSelectedMu)));
                mu_4mom.setX(v_mu->at(1)->at(iSelectedMu));
                mu_4mom.setY(v_mu->at(2)->at(iSelectedMu));
                mu_4mom.setZ(v_mu->at(3)->at(iSelectedMu));
                
                if(!strcmp(signOption, "OS") && v_el->at(0)->at(iSelectedEl) * v_mu->at(0)->at(iSelectedMu) > 0)
                {
                    continue;
                }
                
                else if(!strcmp(signOption, "SS") && v_el->at(0)->at(iSelectedEl) * v_mu->at(0)->at(iSelectedMu) < 0)
                {
                    continue;
                }
                
                if(deltaR_min > 0 && el_4mom.deltaR(mu_4mom) < deltaR_min)
                {
                    continue;
                }
                
                double HT = el_4mom.perp() + mu_4mom.perp();
                
                if(HT > elMuPair_HT)
                {
                    v_elMuPair_pos.at(0) = iSelectedEl;
                    v_elMuPair_pos.at(1) = iSelectedMu;
                    
                    elMuPair_HT = HT;
                }
            }
        }
        
        if(v_elMuPair_pos.at(0) >= 0 && v_elMuPair_pos.at(1) >= 0)
        {
            return v_elMuPair_pos;
        }
        
        return {};
    }
    
    
    bool isTauNewDM(int tauDM)
    {
        std::vector <int> v_validTauDMs = {0, 1, 10, 11};
        
        bool result = std::find(v_validTauDMs.begin(), v_validTauDMs.end(), tauDM) != v_validTauDMs.end();
        
        return result;
    }
    
    bool isTauNewDM(bool byNewDM, int tauDM)
    {
        bool result = (byNewDM && tauDM != 5 && tauDM != 6);
        
        return result;
    }
    
    
    std::vector <int> getObjPair(std::vector <std::vector <double>* > *v_obj1,
        std::vector <std::vector <double>* > *v_obj2,
        bool areObjsSame,
        std::vector <std::vector <double>* > vv_obj1Selection,
        std::vector <std::vector <double>* > vv_obj2Selection,
        double deltaR_min,
        const char *signOption,
        bool preserveOrder // Look at function declaration for explanation
    )
    {
        std::vector <int> v_selectedObj1_pos;
        std::vector <int> v_selectedObj2_pos;
        
        // Obj1 selection
        for(int iObj1 = 0; iObj1 < v_obj1->at(0)->size(); iObj1++)
        {
            bool isSelected = true;
            
            for(int iSelection = 0; iSelection < vv_obj1Selection.size(); iSelection++)
            {
                if(!vv_obj1Selection.at(iSelection)->at(iObj1))
                {
                    isSelected = false;
                    break;
                }
            }
            
            if(isSelected)
            {
                v_selectedObj1_pos.push_back(iObj1);
            }
        }
        
        if(!v_selectedObj1_pos.size())
        {
            return {};
        }
        
        // Obj2 selection
        for(int iObj2 = 0; iObj2 < v_obj2->at(0)->size(); iObj2++)
        {
            bool isSelected = true;
            
            for(int iSelection = 0; iSelection < vv_obj2Selection.size(); iSelection++)
            {
                if(!vv_obj2Selection.at(iSelection)->at(iObj2))
                {
                    isSelected = false;
                    
                    break;
                }
            }
            
            if(isSelected)
            {
                v_selectedObj2_pos.push_back(iObj2);
            }
        }
        
        if(!v_selectedObj2_pos.size())
        {
            return {};
        }
        
        
        //printf("Obj1 [%d]: ", v_obj1->at(0)->size());
        //
        //for(int iObj1 = 0; iObj1 < v_selectedObj1_pos.size(); iObj1++)
        //{
        //    int iSelectedObj1 = v_selectedObj1_pos.at(iObj1);
        //    
        //    printf("%d, ", iSelectedObj1+1);
        //}
        //
        //printf("\n");
        //
        //printf("Obj2 [%d]: ", v_obj2->at(0)->size());
        //
        //for(int iObj2 = 0; iObj2 < v_selectedObj2_pos.size(); iObj2++)
        //{
        //    int iSelectedObj2 = v_selectedObj2_pos.at(iObj2);
        //    
        //    printf("%d, ", iSelectedObj2+1);
        //}
        //
        //printf("\n");
        
        
        bool isPtSorted = false;
        double objPair_HT = 0;
        std::vector <int> v_objPair_pos(2, -1);
        
        // Pair selection
        for(int iObj1 = 0; iObj1 < v_selectedObj1_pos.size(); iObj1++)
        {
            int iSelectedObj1 = v_selectedObj1_pos.at(iObj1);
            
            for(int iObj2 = 0; iObj2 < v_selectedObj2_pos.size(); iObj2++)
            {
                int iSelectedObj2 = v_selectedObj2_pos.at(iObj2);
                
                // If obj1 and obj2 are same (eg. mu and mu), then skip the obj1 = obj2 pair
                //if(areObjsSame && iObj1 == iObj2)
                if(areObjsSame && iSelectedObj1 == iSelectedObj2)
                {
                    continue;
                }
                
                CLHEP::HepLorentzVector obj1_4mom;
                obj1_4mom.setT(fabs(v_obj1->at(0)->at(iSelectedObj1)));
                obj1_4mom.setX(v_obj1->at(1)->at(iSelectedObj1));
                obj1_4mom.setY(v_obj1->at(2)->at(iSelectedObj1));
                obj1_4mom.setZ(v_obj1->at(3)->at(iSelectedObj1));
                
                CLHEP::HepLorentzVector obj2_4mom;
                obj2_4mom.setT(fabs(v_obj2->at(0)->at(iSelectedObj2)));
                obj2_4mom.setX(v_obj2->at(1)->at(iSelectedObj2));
                obj2_4mom.setY(v_obj2->at(2)->at(iSelectedObj2));
                obj2_4mom.setZ(v_obj2->at(3)->at(iSelectedObj2));
                
                if(preserveOrder && obj1_4mom.perp() < obj2_4mom.perp())
                {
                    //printf("Not ordered: obj1 %d, obj2 %d \n", iSelectedObj1+1, iSelectedObj2+1);
                    continue;
                }
                
                if(!strcmp(signOption, "OS") && v_obj1->at(0)->at(iSelectedObj1) * v_obj2->at(0)->at(iSelectedObj2) > 0)
                {
                    continue;
                }
                
                else if(!strcmp(signOption, "SS") && v_obj1->at(0)->at(iSelectedObj1) * v_obj2->at(0)->at(iSelectedObj2) < 0)
                {
                    continue;
                }
                
                if(deltaR_min > 0 && obj1_4mom.deltaR(obj2_4mom) < deltaR_min)
                {
                    continue;
                }
                
                double HT = obj1_4mom.perp() + obj2_4mom.perp();
                
                if(HT > objPair_HT)
                {
                    v_objPair_pos.at(0) = iSelectedObj1;
                    v_objPair_pos.at(1) = iSelectedObj2;
                    
                    objPair_HT = HT;
                    
                    if(obj1_4mom.perp() > obj2_4mom.perp())
                    {
                        isPtSorted = true;
                    }
                    
                    else
                    {
                        isPtSorted = false;
                    }
                }
            }
        }
        
        if(v_objPair_pos.at(0) >= 0 && v_objPair_pos.at(1) >= 0)
        {
            // Sort by pT if Obj1 and Obj2 are same objects (like tau-tau)
            if(areObjsSame && !isPtSorted)
            {
                int temp = v_objPair_pos.at(0);
                v_objPair_pos.at(0) = v_objPair_pos.at(1);
                v_objPair_pos.at(1) = temp;
            }
            
            return v_objPair_pos;
        }
        
        return {};
    }
    
    
    std::vector <std::vector <int> > getTauPair(std::vector <std::vector <double> *> *v_tau,
        std::vector <double> v_eventSelection,
        std::vector <std::vector <double>* > vv_tauSelection,
        double deltaR_min,
        const char *signOption)
    {
        std::vector <std::vector <int> > v_tauPair_pos;
        
        int selectionStage_eventSelection = 1;
        int selectionStage_tauSelection = selectionStage_eventSelection + v_eventSelection.size();
        int selectionStage_tauPairSelection = selectionStage_eventSelection + v_eventSelection.size() + vv_tauSelection.size();
        
        int tauPair_nSelection = 1 + (int) (deltaR_min > 0);
        
        std::vector <int> v_nTau(selectionStage_tauPairSelection + tauPair_nSelection, 0);
        
        std::vector <int> v_selectedTau_pos;
        
        
        // Start
        v_nTau[0] = v_tau->at(0)->size();
        
        
        // Check event selection
        for(int iEventSelection = 0; iEventSelection < v_eventSelection.size(); iEventSelection++)
        {
            if(!v_eventSelection[iEventSelection])
            {
                return {(std::vector <int>) {}, v_nTau};
            }
            
            v_nTau[selectionStage_eventSelection+iEventSelection] = v_tau->at(0)->size();
        }
        
        
        // Check tau selection
        for(int iTau = 0; iTau < v_tau->at(0)->size(); iTau++)
        {
            bool isTauSelected = true;
            
            for(int iTauSelection = 0; iTauSelection < vv_tauSelection.size(); iTauSelection++)
            {
                if(!vv_tauSelection[iTauSelection]->at(iTau))
                {
                    isTauSelected = false;
                    continue;
                }
                
                if(isTauSelected)
                {
                    v_nTau[selectionStage_tauSelection+iTauSelection]++;
                }
            }
            
            if(isTauSelected)
            {
                v_selectedTau_pos.push_back(iTau);
            }
        }
        
        
        // Check tau pair selection
        bool isPtSorted = false;
        int tauPair_pos = 0;
        double tauPair_HT = 0;
        
        for(int iSelectedTau1 = 0; iSelectedTau1 < v_selectedTau_pos.size(); iSelectedTau1++)
        {
            int iTau1 = v_selectedTau_pos[iSelectedTau1];
            
            for(int iSelectedTau2 = iSelectedTau1+1; iSelectedTau2 < v_selectedTau_pos.size(); iSelectedTau2++)
            {
                int iTau2 = v_selectedTau_pos[iSelectedTau2];
                
                CLHEP::HepLorentzVector tau1_4mom;
                
                tau1_4mom.setT(fabs(v_tau->at(0)->at(iTau1)));
                tau1_4mom.setX(v_tau->at(1)->at(iTau1));
                tau1_4mom.setY(v_tau->at(2)->at(iTau1));
                tau1_4mom.setZ(v_tau->at(3)->at(iTau1));
                
                
                CLHEP::HepLorentzVector tau2_4mom;
                
                tau2_4mom.setT(fabs(v_tau->at(0)->at(iTau2)));
                tau2_4mom.setX(v_tau->at(1)->at(iTau2));
                tau2_4mom.setY(v_tau->at(2)->at(iTau2));
                tau2_4mom.setZ(v_tau->at(3)->at(iTau2));
                
                // Tau sign
                if(!strcmp(signOption, "OS") && v_tau->at(0)->at(iTau1) * v_tau->at(0)->at(iTau2) > 0)
                {
                    continue;
                }
                
                else if(!strcmp(signOption, "SS") && v_tau->at(0)->at(iTau1) * v_tau->at(0)->at(iTau2) < 0)
                {
                    continue;
                }
                
                v_nTau[selectionStage_tauPairSelection+0] = 2;
                
                // deltaR > deltaR_min
                if(deltaR_min > 0)
                {
                    if(tau1_4mom.deltaR(tau2_4mom) < deltaR_min)
                    {
                        continue;
                    }
                    
                    v_nTau[selectionStage_tauPairSelection+1] = 2;
                }
                
                // tau1_pT > tau1_pT_min && tau2_pT > tau2_pT_min
                /*if(tau1_4mom.perp() > tau2_4mom.perp())
                {
                    if(tau1_4mom.perp() < tau1_pT_min || tau2_4mom.perp() < tau2_pT_min)
                    {
                        continue;
                    }
                }
                
                else
                {
                    if(tau2_4mom.perp() < tau1_pT_min || tau1_4mom.perp() < tau2_pT_min)
                    {
                        continue;
                    }
                }
                
                v_nTau[selectionStage_tauPairSelection+2] = 2;*/
                
                v_tauPair_pos.push_back({iTau1, iTau2});
                
                // Select hardest pair
                if(tau1_4mom.perp() + tau2_4mom.perp() > tauPair_HT)
                {
                    tauPair_pos = v_tauPair_pos.size()-1;
                    tauPair_HT = tau1_4mom.perp() + tau2_4mom.perp();
                    
                    if(tau1_4mom.perp() > tau2_4mom.perp())
                    {
                        isPtSorted = true;
                    }
                    
                    else
                    {
                        isPtSorted = false;
                    }
                }
            }
        }
        
        
        // Return pT sorted pair
        if(v_tauPair_pos.size())
        {
            if(isPtSorted)
            {
                return {v_tauPair_pos[tauPair_pos], v_nTau};
            }
            
            else
            {
                return {{v_tauPair_pos[tauPair_pos][1], v_tauPair_pos[tauPair_pos][0]}, v_nTau};
            }
        }
        
        else
        {
            return {(std::vector <int>) {}, v_nTau};;
        }
    }
    
    
    
    bool isSeparated(CLHEP::HepLorentzVector object1_4mom,
        std::vector <std::vector <double> *> *v_object2,
        double dR_min,
        std::vector <int> v_object2_index)
    {
        for(int iObj = 0; iObj < v_object2->at(0)->size(); iObj++)
        {
            // Check against given indices only if the list of indices is not empty
            if(v_object2_index.size() &&
                std::find(v_object2_index.begin(), v_object2_index.end(), iObj) == v_object2_index.end())
            {
                continue;
            }
            
            CLHEP::HepLorentzVector obj2_4mom;
            
            obj2_4mom.setT(fabs(v_object2->at(0)->at(iObj)));
            obj2_4mom.setX(v_object2->at(1)->at(iObj));
            obj2_4mom.setY(v_object2->at(2)->at(iObj));
            obj2_4mom.setZ(v_object2->at(3)->at(iObj));
            
            if(object1_4mom.deltaR(obj2_4mom) < dR_min)
            {
                return false;
            }
        }
        
        return true;
    }
    
    
    /*std::pair <double, double> getTauSF(
        double tau_pT, double tau_eta,
        std::string WPname
    )
    {
        // <SF, +-uncertainty>
        std::pair <double, double> p_tauSF(1, 0);
        
        std::map <std::string, std::vector <double> > m_tauSFetaBin;
        std::map <std::string, std::vector <std::pair <double, double> > > m_tauSFdetail;
        
        //
        m_tauSFetaBin["LooseIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail["LooseIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.99, 0.05)
        };
        
        m_tauSFetaBin["MediumIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail["MediumIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.96, 0.05)
        };
        
        m_tauSFetaBin["TightIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail["TightIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.94, 0.05)
        };
        
        m_tauSFetaBin["VTightIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail["VTightIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.91, 0.05)
        };
        
        //
        //m_tauSFetaBin["againstElectronVLooseMVA6"] = {0, 1.460, 1.558};
        //m_tauSFdetail["againstElectronVLooseMVA6"] = {
        //    std::make_pair(1.21, 0.06),
        //    std::make_pair(1.00, 0.00),
        //    std::make_pair(1.38, 0.04)
        //};
        //
        //m_tauSFetaBin["againstElectronLooseMVA6"] = {0, 1.460, 1.558};
        //m_tauSFdetail["againstElectronLooseMVA6"] = {
        //    std::make_pair(1.32, 0.03),
        //    std::make_pair(1.00, 0.00),
        //    std::make_pair(1.38, 0.04)
        //};
        //
        //m_tauSFetaBin["againstElectronMediumMVA6"] = {0, 1.460, 1.558};
        //m_tauSFdetail["againstElectronMediumMVA6"] = {
        //    std::make_pair(1.32, 0.07),
        //    std::make_pair(1.00, 0.00),
        //    std::make_pair(1.53, 0.13)
        //};
        //
        //m_tauSFetaBin["againstElectronTightMVA6"] = {0, 1.460, 1.558};
        //m_tauSFdetail["againstElectronTightMVA6"] = {
        //    std::make_pair(1.40, 0.12),
        //    std::make_pair(1.00, 0.00),
        //    std::make_pair(1.90, 0.30)
        //};
        //
        //m_tauSFetaBin["againstElectronTightMVA6"] = {0, 1.460, 1.558};
        //m_tauSFdetail["againstElectronTightMVA6"] = {
        //    std::make_pair(1.21, 0.17),
        //    std::make_pair(1.00, 0.00),
        //    std::make_pair(1.97, 0.45)
        //};
        
        
        if(m_tauSFetaBin.find(WPname) == m_tauSFetaBin.end())
        {
            printf("No WP called %s in Common::getTauSF(...). \n", WPname.c_str());
            exit(EXIT_FAILURE);
        }
        
        
        std::vector <double> v_tauSFetaBin;
        std::vector <std::pair <double, double> > v_tauSFdetail;
        
        v_tauSFetaBin = m_tauSFetaBin[WPname];
        v_tauSFdetail = m_tauSFdetail[WPname];
        
        for(int iBin = 0; iBin < v_tauSFetaBin.size(); iBin++)
        {
            if(fabs(tau_eta) >= v_tauSFetaBin.at(iBin) &&
                (iBin == v_tauSFetaBin.size()-1 || fabs(tau_eta) < v_tauSFetaBin.at(iBin+1)))
            {
                p_tauSF = v_tauSFdetail.at(iBin);
            }
        }
        
        return p_tauSF;
    }
   */ 
    
    void parseCSVto2Dvector(std::string fileName, 
        std::vector <std::vector <double> > *vv_info
    )
    {
        std::ifstream data(fileName);
        std::string line;
        std::vector <std::vector <std::string> > parsedCsv;
        
        while(std::getline(data, line))
        {
            // Skip comments (start with #)
            if(line.at(0) == '#')
            {
                continue;
            }
            
            std::stringstream lineStream(line);
            std::string cell;
            std::vector <std::string> parsedRow;
            
            while(std::getline(lineStream, cell, ','))
            {
                parsedRow.push_back(cell);
            }
            
            parsedCsv.push_back(parsedRow);
            
            std::vector <double> v_temp;
            
            for(int iEle = 0; iEle < parsedRow.size(); iEle++)
            {
                v_temp.push_back(std::stof(parsedRow.at(iEle)));
            }
            
            vv_info->push_back(v_temp);
        }
    }
    
    
    double get_lepBlepB_mT2(
        CLHEP::HepLorentzVector lep1_4mom,
        CLHEP::HepLorentzVector b1_4mom,
        CLHEP::HepLorentzVector lep2_4mom,
        CLHEP::HepLorentzVector b2_4mom,
        double MET_x, double MET_y
    )
    {
        CLHEP::HepLorentzVector lep_b_4mom1_comb1;
        CLHEP::HepLorentzVector lep_b_4mom2_comb1;
        
        CLHEP::HepLorentzVector lep_b_4mom1_comb2;
        CLHEP::HepLorentzVector lep_b_4mom2_comb2;
        
        CLHEP::HepLorentzVector lep_b_4mom1;
        CLHEP::HepLorentzVector lep_b_4mom2;
        
        double bb_MET_mT2_lsp0 = 0;
        double lepBlepB_MET_mT2_lsp0 = 0;
        double lepBlepB_MET_mT2_lsp0_mod1 = 0;
        
        lep_b_4mom1_comb1 = lep1_4mom + b1_4mom;
        lep_b_4mom1_comb1 = lep2_4mom + b2_4mom;
        
        lep_b_4mom1_comb2 = lep1_4mom + b2_4mom;
        lep_b_4mom1_comb2 = lep2_4mom + b1_4mom;
        
        //bb_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2(
        //    b1_4mom.m(), b1_4mom.px(), b1_4mom.py(),
        //    b2_4mom.m(), b2_4mom.px(), b2_4mom.py(),
        //    MET_x, MET_y,
        //    0, 0);
        
        
        //// Select the combination whose max. invariant mass is lower
        //double comb1_m_max = std::max(lep_b_4mom1_comb1.m(), lep_b_4mom2_comb1.m());
        //double comb2_m_max = std::max(lep_b_4mom1_comb2.m(), lep_b_4mom2_comb2.m());
        //
        //if(comb1_m_max < comb2_m_max)
        //{
        //    lep_b_4mom1 = lep_b_4mom1_comb1;
        //    lep_b_4mom2 = lep_b_4mom2_comb1;
        //}
        //
        //else
        //{
        //    lep_b_4mom1 = lep_b_4mom1_comb2;
        //    lep_b_4mom2 = lep_b_4mom2_comb2;
        //}
        //
        //
        //lepBlepB_MET_mT2_lsp0 = asymm_mt2_lester_bisect::get_mT2(
        //    lep_b_4mom1.m(), lep_b_4mom1.px(), lep_b_4mom1.py(),
        //    lep_b_4mom2.m(), lep_b_4mom2.px(), lep_b_4mom2.py(),
        //    MET_x, MET_y,
        //    0, 0);
        //
        //printf("lepBlepB_MET_mT2_lsp0 %f \n", lepBlepB_MET_mT2_lsp0);
        
        
        double lepBlepB_MET_mT2_lsp0_comb1 = asymm_mt2_lester_bisect::get_mT2(
            lep_b_4mom1_comb1.m(), lep_b_4mom1_comb1.px(), lep_b_4mom1_comb1.py(),
            lep_b_4mom2_comb1.m(), lep_b_4mom2_comb1.px(), lep_b_4mom2_comb1.py(),
            MET_x, MET_y,
            0, 0);
        
        double lepBlepB_MET_mT2_lsp0_comb2 = asymm_mt2_lester_bisect::get_mT2(
            lep_b_4mom1_comb2.m(), lep_b_4mom1_comb2.px(), lep_b_4mom1_comb2.py(),
            lep_b_4mom2_comb2.m(), lep_b_4mom2_comb2.px(), lep_b_4mom2_comb2.py(),
            MET_x, MET_y,
            0, 0);
        
        // Select the combination with lower mT2
        if(lepBlepB_MET_mT2_lsp0_comb1 < lepBlepB_MET_mT2_lsp0_comb2)
        {
            lepBlepB_MET_mT2_lsp0_mod1 = lepBlepB_MET_mT2_lsp0_comb1;
        }
        
        else
        {
            lepBlepB_MET_mT2_lsp0_mod1 = lepBlepB_MET_mT2_lsp0_comb2;
        }
        
        //printf("lepBlepB_MET_mT2_lsp0_mod1 %f \n", lepBlepB_MET_mT2_lsp0_mod1);
        
        return lepBlepB_MET_mT2_lsp0_mod1;
    }
    
    
    bool isEventSelected(
        std::map <std::string, bool> m_eventSelection,
        std::string eventSelectionStr,
        bool selection
    )
    {
        if(m_eventSelection.find(eventSelectionStr) == m_eventSelection.end())
        {
            printf("Error in Common::isEventSelected(...): Event selection string \"%s\" not found. \n", eventSelectionStr.c_str());
            exit(EXIT_FAILURE);
        }
        
        if(m_eventSelection[eventSelectionStr] && !selection)
        {
            return false;
        }
        
        return true;
    }
    
    
    // findBin >= 1
    std::vector <int> get_SRpos(int findBin, std::vector <std::vector <double> > vv_cut)
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
    }
    
    
    bool doesFileExist(std::string fileName)
    {
        return std::ifstream(fileName).good();
    }
    
    
    std::vector <CLHEP::HepLorentzVector> objVectorTo4mom(
        std::vector <std::vector <double> *> *v_obj
    )
    {
        std::vector <CLHEP::HepLorentzVector> v_obj_4mom;
        
        for(int iObj = 0; iObj < v_obj->size(); iObj++)
        {
            CLHEP::HepLorentzVector obj_4mom;
            
            obj_4mom.setT(fabs(v_obj->at(0)->at(iObj)));
            obj_4mom.setX(v_obj->at(1)->at(iObj));
            obj_4mom.setY(v_obj->at(2)->at(iObj));
            obj_4mom.setZ(v_obj->at(3)->at(iObj));
            
            v_obj_4mom.push_back(obj_4mom);
        }
        
        return v_obj_4mom;
    }
    
    
    bool isInRunJson(
        nlohmann::json jsonContent,
        long long runNumber,
        long long lumiNumber,
        bool debug
    )
    {
        //if(debug)
        //{
        //    printf("JSON content: \n");
        //    std::cout << jsonContent << "\n\n";
        //}
        
        std::string key = std::to_string(runNumber);
        
        if(jsonContent.find(key) == jsonContent.end())
        {
            if(debug)
            {
                printf("Run %lld not found. \n", runNumber);
                //printf("\n");
            }
            
            return false;
        }
        
        auto list = jsonContent.at(key);
        
        if(debug)
        {
            printf("Lumi ranges in run %lld: \n", runNumber);
            std::cout << list << "\n";
        }
        
        bool isFound = isInJsonLumiRange(list, lumiNumber);
        
        if(debug)
        {
            printf("Found lumi %lld in run %lld: %d \n", lumiNumber, runNumber, isFound);
            //printf("\n");
        }
        
        return isFound;
    }
    
    
    double evaluateExpression(
        std::string expression,
        std::vector <std::pair <std::string, double> > vp_symbolVal,
        bool debug
    )
    {
        std::string expression_sub = expression;
        
        for(int iSymbol = 0; iSymbol < vp_symbolVal.size(); iSymbol++)
        {
            std::string symbol_str = vp_symbolVal.at(iSymbol).first;
            std::string symbol_val = std::to_string(vp_symbolVal.at(iSymbol).second);
            
            boost::replace_all(expression_sub, symbol_str, symbol_val);
            
        }
        
        if(debug)
        {
            printf("Expression: %s \n", expression.c_str());
            printf("Substituted expression: %s \n", expression_sub.c_str());
        }
        
        exprtk::expression <double> exprtk_expression;
        exprtk::parser <double> exprtk_parser;
        
        if(exprtk_parser.compile(expression_sub, exprtk_expression))
        {
            double result = exprtk_expression.value();
            
            if(debug)
            {
                printf("Result: %f \n", result);
            }
            
            return result;
        }
        
        else
        {
            printf("Error in Common::evaluateExpression(...): Could not parse string with exprtk. \n");
            printf("Expression: %s \n", expression.c_str());
            printf("Substituted expression: %s \n", expression_sub.c_str());
            
            exit(EXIT_FAILURE);
        }
        
        //return result;
    }
    
    
    double crystalballEfficiency(
        double m,
        double m0,
        double sigma,
        double alpha,
        double n,
        double norm
    )
    {
        double sqrtPiOver2 = std::sqrt(TMath::PiOver2());
        double sqrt2       = std::sqrt(2.);
        double sig         = std::fabs(sigma);
        double t           = (m - m0)/sig * alpha / abs(alpha);
        double absAlpha    = std::fabs(alpha/sig);
        double a           = TMath::Power(n/absAlpha, n) * TMath::Exp(-0.5 * absAlpha * absAlpha);
        double b           = absAlpha - n/absAlpha;
        double arg         = absAlpha / sqrt2;
        
        double ApproxErf;
        
        if( arg >  5.)
        {
            ApproxErf =  1.;
        }
        
        else if(arg < -5.)
        {
            ApproxErf = -1.;
        }
        
        else
        {
            ApproxErf = TMath::Erf(arg);
        }
        
        double leftArea    = (1. + ApproxErf) * sqrtPiOver2;
        double rightArea   = ( a * 1./TMath::Power(absAlpha-b, n-1) ) / (n - 1);
        double area        = leftArea + rightArea;
        
        if(t <= absAlpha)
        {
            arg = t / sqrt2;
            
            if(arg >  5.)
            {
                ApproxErf =  1.;
            }
            
            else if(arg < -5.)
            {
                ApproxErf = -1.;
            }
            
            else
            {
                ApproxErf = TMath::Erf(arg);
            }
            
            return norm * (1 + ApproxErf) * sqrtPiOver2 / area;
        }
        
        else
        {
            return norm * (leftArea + a * (1/TMath::Power(t-b,n-1) - \
                1/TMath::Power(absAlpha - b,n-1)) / (1 - n)) / area;
        }
    }
    
    
    double getTauTriggerEffFromJson(
        nlohmann::json jsonContent,
        std::string WPname,
        double pT
    )
    {
        double alpha = jsonContent[WPname]["alpha"];
        double m0 = jsonContent[WPname]["m_{0}"];
        double sigma = jsonContent[WPname]["sigma"];
        double norm = jsonContent[WPname]["norm"];
        double n = jsonContent[WPname]["n"];
        
        double eff = crystalballEfficiency(
            pT,
            m0,
            sigma,
            alpha,
            n,
            norm
        );
        
        //printf("********** %s ********** \n", WPname.c_str());
        //printf("alpha: % 0.4f \n", alpha);
        //printf("m_{0}: % 0.4f \n", m0);
        //printf("sigma: % 0.4f \n", sigma);
        //printf("norm: % 0.4f \n", norm);
        //printf("n: % 0.4f \n", n);
        //printf("pT: % 0.2f, eff: %0.4f \n", pT, eff);
        //printf("\n");
        
        return eff;
    }
    
    
    double getTauTriggerEffFromJson_data(
        nlohmann::json jsonContent,
        std::string WPname,
        double decayMode,
        double pT
    )
    {
        char WPname_data[500];
        
        sprintf(WPname_data, "data_%s_dm%d", WPname.c_str(), (int) decayMode);
        
        double eff_data = getTauTriggerEffFromJson(
            jsonContent,
            WPname_data,
            pT
        );
        
        return eff_data;
    }
    
    
    double getTauTriggerEffFromJson_mc(
        nlohmann::json jsonContent,
        std::string WPname,
        double decayMode,
        double pT
    )
    {
        char WPname_mc[500];
        
        sprintf(WPname_mc, "mc_%s_dm%d", WPname.c_str(), (int) decayMode);
        
        double eff_mc = getTauTriggerEffFromJson(
            jsonContent,
            WPname_mc,
            pT
        );
        
        return eff_mc;
    }
    
    
    double getTauTriggerSFfromJson(
        nlohmann::json jsonContent,
        std::string WPname,
        double decayMode,
        double pT
    )
    {
        //char WPname_data[500];
        //char WPname_mc[500];
        //
        //sprintf(WPname_data, "data_%s_dm%d", WPname.c_str(), (int) decayMode);
        //sprintf(WPname_mc, "mc_%s_dm%d", WPname.c_str(), (int) decayMode);
        //
        //double eff_data = getTauTriggerEffFromJson(
        //    jsonContent,
        //    WPname_data,
        //    pT
        //);
        //
        //double eff_mc = getTauTriggerEffFromJson(
        //    jsonContent,
        //    WPname_mc,
        //    pT
        //);
        
        double eff_data = getTauTriggerEffFromJson_data(
            jsonContent,
            WPname,
            decayMode,
            pT
        );
        
        double eff_mc = getTauTriggerEffFromJson_mc(
            jsonContent,
            WPname,
            decayMode,
            pT
        );
        
        double SF = eff_data / eff_mc;
        
        return SF;
    }
    
    // Returns:
    // <
    //    <SF + SYST_TYPE*error, error>,
    //    <top1_pT, top2_pT>
    // >
    std::pair <std::pair <double, double>, std::pair <double, double> > getTopPtReweightFactor(
        std::vector <std::vector <double>*> *vv_top,
        SYST_TYPE syst
    )
    {
        int t_n = vv_top->at(0)->size();
        
        if(t_n >= 2)
        {
            CLHEP::HepLorentzVector top1_4mom_gen(0, 0, 0, 0), top2_4mom_gen(0, 0, 0, 0);
            
            for(int iTop = 0; iTop < t_n; iTop++)
            {
                CLHEP::HepLorentzVector temp_4mom;
                
                temp_4mom.setT(fabs(vv_top->at(0)->at(iTop)));
                temp_4mom.setX(vv_top->at(1)->at(iTop));
                temp_4mom.setY(vv_top->at(2)->at(iTop));
                temp_4mom.setZ(vv_top->at(3)->at(iTop));
                
                if(temp_4mom.perp() > top1_4mom_gen.perp())
                {
                    top1_4mom_gen = temp_4mom;
                }
                
                else if(temp_4mom.perp() > top2_4mom_gen.perp())
                {
                    top2_4mom_gen = temp_4mom;
                }
            }
            
            return std::make_pair(
                getTopPtReweightFactor(top1_4mom_gen.perp(), top2_4mom_gen.perp(), syst),
                std::make_pair(top1_4mom_gen.perp(), top2_4mom_gen.perp())
            );
        }
        
        else
        {
            printf("Warning in Common::getTopPtReweightFactor(...): Less than two top quarks in the event. \n");
        }
        
        return std::make_pair(
            std::make_pair(1.0, 0.0),
            std::make_pair(-1.0, -1.0)
        );
    }
    
    
    // Returns <SF + SYST_TYPE*error, error>
    std::pair <double, double> getTopPtReweightFactor(double pT1, double pT2, SYST_TYPE syst)
    {
        double corr1 = std::exp(0.0615-0.0005*pT1);
        double corr2 = std::exp(0.0615-0.0005*pT2);
        
        double corr = std::sqrt(corr1*corr2);
        
        // Error = Correction = |1 - f|
        // Mentioned in the HTT AN
        double err = fabs(1 - corr);
        
        std::pair <double, double> p_info(
            corr + syst*err,
            err
        );
        
        return p_info;
    }
    
    
    std::pair <double, double> getZpTreweightFactor(CLHEP::HepLorentzVector Z_4mom, RooWorkspace *htt_scaleFactorWS, std::string era, SYST_TYPE syst)
    {
        if(!era.compare("2016"))
        {
            htt_scaleFactorWS->var("z_gen_mass")->setVal(Z_4mom.m());
        }
        
        htt_scaleFactorWS->var("z_gen_pt")->setVal(Z_4mom.perp());
        
        double corr = htt_scaleFactorWS->function("zpt_weight_nom")->getVal();
        
        // Error = Correction = |1 - f|
        // Mentioned in the stau->ditauh AN
        double err = fabs(1 - corr);
        
        std::pair <double, double> p_info(
            corr + syst*err,
            err
        );
        
        return p_info;
    }
    
    
    /*std::vector <bool> isObjSelected(
        std::vector <CLHEP::HepLorentzVector> v_obj_4mom,
        std::vector <std::vector <double> > v_obj_selection,
        double obj_pTcut, double obj_etaCut
    )
    {
        std::vector <bool> v_obj_isSelected(v_obj_4mom.size(), true);
        
        for(int iObj = 0; iObj < v_obj_4mom.size(); iObj++)
        {
            if(v_obj_4mom.perp() < obj_pTcut)
            {
                v_obj_isSelected.at(iObj) = false;
                
                continue;
            }
            
            if(fabs(v_obj_4mom.eta()) > obj_etaCut)
            {
                v_obj_isSelected.at(iObj) = false;
                
                continue;
            }
            
            for(int iSel = 0; iSel < v_obj_selection.size(); iSel++)
            {
                if(!v_obj_selection.at(iSel).at(iObj))
                {
                    v_obj_isSelected.at(iObj) = false;
                    
                    break;
                }
            }
        }
        
        return v_obj_isSelected;
    }
    
    
    std::vector <std::vector <bool> > isMatched(
        std::vector <std::vector <double> *> *v_obj1,
        std::vector <std::vector <double> *> *v_obj2,
        
        std::vector <std::vector <double> > v_obj1_selection,
        std::vector <std::vector <double> > v_obj2_selection,
        
        double obj2_pTcut, double obj2_etaCut,
        double obj1_pTcut, double obj1_etaCut,
        
        double dRcut
    )
    {
        std::vector <CLHEP::HepLorentzVector> v_obj1_4mom = objVectorTo4mom(v_obj1);
        std::vector <CLHEP::HepLorentzVector> v_obj2_4mom = objVectorTo4mom(v_obj2);
        
        std::vector <std::vector <bool> > isMatched(
            v_obj1_4mom,
            v_obj2_4mom,
            
            v_obj1_selection,
            v_obj2_selection,
            
            obj2_pTcut, obj2_etaCut,
            obj1_pTcut, obj1_etaCut,
            
            dRcut
        );
    }
    
    
    std::vector <std::vector <bool> > isMatched(
        std::vector <CLHEP::HepLorentzVector> v_obj1_4mom,
        std::vector <CLHEP::HepLorentzVector> v_obj2_4mom,
        
        std::vector <std::vector <double> > v_obj1_selection,
        std::vector <std::vector <double> > v_obj2_selection,
        
        double obj2_pTcut, double obj2_etaCut,
        double obj1_pTcut, double obj1_etaCut,
        
        double dRcut
    )
    {
        std::vector <bool> v_obj1_isSelected = (isObjSelected(
            v_obj1_4mom,
            v_obj1_selection,
            obj2_pTcut, obj2_etaCut
        );
        
        std::vector <bool> v_obj2_isSelected = (isObjSelected(
            v_obj2_4mom,
            v_obj2_selection,
            obj2_pTcut, obj2_etaCut
        );
        
        
        std::vector <bool> v_obj1_isMatched(v_obj1_4mom.size(), false);
        std::vector <bool> v_obj2_isMatched(v_obj2_4mom.size(), false);
        
        for(int iObj1 = 0; iObj1 < v_obj1_4mom.size(); iObj1++)
        {
            if(!v_obj1_isSelected.at(iObj1))
            {
                continue;
            }
            
            int nearestObj2_index = -1;
            double dR_min = 9999;
            
            CLHEP::HepLorentzVector obj1_4mom = v_obj1_4mom.at(iObj1);
            
            for(int iObj2 = 0; iObj1 < v_obj2_4mom.size(); iObj2++)
            {
                if(!v_obj2_isSelected.at(iObj2))
                {
                    continue;
                }
                
                // Do not use if already used for matching
                if(v_obj2_isMatched.at(iObj2))
                {
                    continue;
                }
                
                CLHEP::HepLorentzVector obj2_4mom = v_obj2_4mom.at(iObj2);
                
                double dR = obj1_4mom.deltaR(obj2_4mom);
                
                if(dR < dR_min)
                {
                    nearestObj2_index = iObj2;
                    dR_min = dR;
                }
            }
            
            if(dR_min < dRcut)
            {
                v_obj1_isMatched.at(iObj1) = true;
                v_obj2_isMatched.at(nearestObj2_index) = true;
            }
        }
        
        return {v_obj1_isMatched, v_obj2_isMatched};
    }*/
}

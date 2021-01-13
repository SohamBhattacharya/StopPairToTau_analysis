# include "TauEfficiencyAndSF.h"


namespace TauEfficiencyAndSF
{
    TauEfficiencyAndSF::TauEfficiencyAndSF(
        std::string inputFileName,
        std::string histName_num,
        std::string histName_den
    )
    {
        this->inputFileName = inputFileName;
        this->histName_num = histName_num;
        this->histName_den = histName_den;
        
        printf("TauEfficiencyAndSF::TauEfficiencyAndSF(...): Opening file %s \n", inputFileName.c_str());
        
        if(!Common::doesFileExist(inputFileName))
        {
            printf("Error in TauEfficiencyAndSF::TauEfficiencyAndSF(...): input file does not exist. \n");
            exit(EXIT_FAILURE);
        }
        
        inputFile = (TFile*) TFile::Open(inputFileName.c_str(), "READ");
        
        printf("TauEfficiencyAndSF::TauEfficiencyAndSF(...): Getting histogram %s \n", histName_num.c_str());
        h2_efficiency_num = (TH2F*) inputFile->Get(histName_num.c_str())->Clone();
        h2_efficiency_num->Sumw2();
        
        //std::cout << h2_efficiency_num << "\n";
        //if(!h2_efficiency_num)
        //{
        //    printf("Error in TauEfficiencyAndSF::TauEfficiencyAndSF(...): Error getting histogram %s \n", histName_num.c_str());
        //    exit(EXIT_FAILURE);
        //}
        
        printf("TauEfficiencyAndSF::TauEfficiencyAndSF(...): Getting histogram %s \n", histName_den.c_str());
        h2_efficiency_den = (TH2F*) inputFile->Get(histName_den.c_str())->Clone();
        h2_efficiency_den->Sumw2();
        
        //if(!h2_efficiency_den)
        //{
        //    printf("Error in TauEfficiencyAndSF::TauEfficiencyAndSF(...): Error getting histogram %s \n", histName_den.c_str());
        //    exit(EXIT_FAILURE);
        //}
        
        h2_efficiency = (TH2F*) h2_efficiency_num->Clone();
        h2_efficiency->Sumw2();
        h2_efficiency->Divide(h2_efficiency_den);
    }
    
    
    double TauEfficiencyAndSF::getEfficiency(double pT, double eta)
    {
        int binX = h2_efficiency_den->GetXaxis()->FindBin(eta);
        int binY = h2_efficiency_den->GetYaxis()->FindBin(pT);
        
        if(binX == h2_efficiency_den->GetNbinsX()+1)
        {
            binX = h2_efficiency_den->GetNbinsX();
        }
        
        if(binY == h2_efficiency_den->GetNbinsY()+1)
        {
            binY = h2_efficiency_den->GetNbinsY();
        }
        
        //printf("pT: %f, eta: %f \n", pT, eta);
        //printf("BinX: %d, BinY: %d \n", binX, binY);
        //printf("Numerator: %f \n", h2_efficiency_num->GetBinContent(binX, binY));
        //printf("Denominator: %f \n", h2_efficiency_den->GetBinContent(binX, binY));
        
        return h2_efficiency->GetBinContent(binX, binY);
    }
    
    
    TauFastFullSF::TauFastFullSF(
        std::string inputFileName_fast,
        std::string histName_num_fast,
        std::string histName_den_fast,
        std::string inputFileName_full,
        std::string histName_num_full,
        std::string histName_den_full,
        std::vector <double> v_reBinX,
        std::vector <double> v_reBinY,
        bool debug
    )
    {
        this->inputFileName_fast = inputFileName_fast;
        this->histName_num_fast = histName_num_fast;
        this->histName_den_fast = histName_den_fast;
        
        this->inputFileName_full = inputFileName_full;
        this->histName_num_full = histName_num_full;
        this->histName_den_full = histName_den_full;
        
        // FastSim input file
        printf("TauFastFullSF::TauFastFullSF(...): Opening file %s \n", inputFileName_fast.c_str());
        
        if(!Common::doesFileExist(inputFileName_fast))
        {
            printf("Error in TauFastFullSF::TauFastFullSF(...): input file does not exist. \n");
            exit(EXIT_FAILURE);
        }
        
        inputFile_fast = (TFile*) TFile::Open(inputFileName_fast.c_str(), "READ");
        
        // FullSim input file
        if(!Common::doesFileExist(inputFileName_full))
        {
            printf("Error in TauFastFullSF::TauFastFullSF(...): input file does not exist. \n");
            exit(EXIT_FAILURE);
        }
        
        inputFile_full = (TFile*) TFile::Open(inputFileName_full.c_str(), "READ");
        
        // Get FastSim histograms
        printf("TauFastFullSF::TauFastFullSF(...): Getting histogram %s \n", histName_num_fast.c_str());
        h2_efficiency_num_fast = (TH2F*) inputFile_fast->Get(histName_num_fast.c_str())->Clone();
        h2_efficiency_num_fast->Sumw2();
        
        h2_efficiency_num_fast = Common::rebin2Dhistogram(
            h2_efficiency_num_fast,
            (v_reBinX.size() > 0),
            v_reBinX, 
            (v_reBinY.size() > 0),
            v_reBinY,
            true,
            debug
        );
        
        printf("TauFastFullSF::TauFastFullSF(...): Getting histogram %s \n", histName_den_fast.c_str());
        h2_efficiency_den_fast = (TH2F*) inputFile_fast->Get(histName_den_fast.c_str())->Clone();
        h2_efficiency_den_fast->Sumw2();
        
        h2_efficiency_den_fast = Common::rebin2Dhistogram(
            h2_efficiency_den_fast,
            (v_reBinX.size() > 0),
            v_reBinX, 
            (v_reBinY.size() > 0),
            v_reBinY,
            true,
            debug
        );
        
        // Get FullSim histograms
        printf("TauFastFullSF::TauFastFullSF(...): Getting histogram %s \n", histName_num_full.c_str());
        h2_efficiency_num_full = (TH2F*) inputFile_full->Get(histName_num_full.c_str())->Clone();
        h2_efficiency_num_full->Sumw2();
        
        h2_efficiency_num_full = Common::rebin2Dhistogram(
            h2_efficiency_num_full,
            (v_reBinX.size() > 0),
            v_reBinX, 
            (v_reBinY.size() > 0),
            v_reBinY,
            true,
            debug
        );
        
        printf("TauFastFullSF::TauFastFullSF(...): Getting histogram %s \n", histName_den_full.c_str());
        h2_efficiency_den_full = (TH2F*) inputFile_full->Get(histName_den_full.c_str())->Clone();
        h2_efficiency_den_full->Sumw2();
        
        h2_efficiency_den_full = Common::rebin2Dhistogram(
            h2_efficiency_den_full,
            (v_reBinX.size() > 0),
            v_reBinX, 
            (v_reBinY.size() > 0),
            v_reBinY,
            true,
            debug
        );
        
        
        // Ratios
        h2_efficiency_fast = (TH2F*) h2_efficiency_num_fast->Clone();
        h2_efficiency_fast->Divide(h2_efficiency_den_fast);
        
        h2_efficiency_full = (TH2F*) h2_efficiency_num_full->Clone();
        h2_efficiency_full->Divide(h2_efficiency_den_full);
        
        h2_SF = (TH2F*) h2_efficiency_full->Clone();
        h2_SF->Divide(h2_efficiency_fast);
    }
    
    
    // Will return <SF+-unc, unc>
    std::pair <double, double> TauFastFullSF::getSF(
        double pT, double eta,
        Common::SYST_TYPE syst
    )
    {
        int binX = h2_SF->GetXaxis()->FindBin(eta);
        int binY = h2_SF->GetYaxis()->FindBin(pT);
        
        if(binX == h2_SF->GetNbinsX()+1)
        {
            binX = h2_SF->GetNbinsX();
        }
        
        if(binY == h2_SF->GetNbinsY()+1)
        {
            binY = h2_SF->GetNbinsY();
        }
        
        double SF = h2_SF->GetBinContent(binX, binY);
        double SF_err = h2_SF->GetBinError(binX, binY);
        
        SF += syst*SF_err;
        
        return std::make_pair(SF, SF_err);
    }
    
    
    // Will return <SF+-unc, %unc>
    std::pair <double, double> getTauSF(
        double tau_pT, double tau_eta,
        std::string WPname,
        std::string era,
        Common::SYST_TYPE syst
    )
    {
        std::map <std::string, std::map <std::string, std::vector <double> > > m_tauSFetaBin;
        std::map <std::string, std::map <std::string, std::vector <std::pair <double, double> > > > m_tauSFdetail;
        
        // <SF, +-%uncertainty>
        std::pair <double, double> p_tauSF(1, 0);
        
        
        // 2016
        std::map <std::string, std::vector <double> > m_tauSFetaBin_2016;
        std::map <std::string, std::vector <std::pair <double, double> > > m_tauSFdetail_2016;
        
        m_tauSFetaBin_2016["LooseIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail_2016["LooseIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.99, 0.05)
        };
        
        m_tauSFetaBin_2016["MediumIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail_2016["MediumIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.96, 0.05)
        };
        
        m_tauSFetaBin_2016["TightIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail_2016["TightIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.94, 0.05)
        };
        
        m_tauSFetaBin_2016["VTightIsolationMVArun2v1DBdR03oldDMwLT"] = {0};
        m_tauSFdetail_2016["VTightIsolationMVArun2v1DBdR03oldDMwLT"] = {
            std::make_pair(0.91, 0.05)
        };
        
        m_tauSFetaBin["2016"] = m_tauSFetaBin_2016;
        m_tauSFdetail["2016"] = m_tauSFdetail_2016;
        
        
        // 2017
        // Have used the dR05 SF for now (dR03 not derived yet)
        // However in 2016 dR03 and dR05 SFs were very close
        std::map <std::string, std::vector <double> > m_tauSFetaBin_2017;
        std::map <std::string, std::vector <std::pair <double, double> > > m_tauSFdetail_2017;
        
        m_tauSFetaBin_2017["LooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {0};
        m_tauSFdetail_2017["LooseIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {
            std::make_pair(0.89, 0.03)
        };
        
        m_tauSFetaBin_2017["MediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {0};
        m_tauSFdetail_2017["MediumIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {
            std::make_pair(0.89, 0.03)
        };
        
        m_tauSFetaBin_2017["TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {0};
        m_tauSFdetail_2017["TightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {
            std::make_pair(0.89, 0.03)
            //std::make_pair(1.00, 0.10)
        };
        
        m_tauSFetaBin_2017["VTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {0};
        m_tauSFdetail_2017["VTightIsolationMVArun2017v2DBoldDMdR0p3wLT2017"] = {
            std::make_pair(0.86, 0.03)
        };
        
        m_tauSFetaBin["2017"] = m_tauSFetaBin_2017;
        m_tauSFdetail["2017"] = m_tauSFdetail_2017;
        
        
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
        
        
        if(m_tauSFetaBin.at(era).find(WPname) == m_tauSFetaBin.at(era).end())
        {
            printf("No WP called %s in Common::getTauSF(...). \n", WPname.c_str());
            exit(EXIT_FAILURE);
        }
        
        
        std::vector <double> v_tauSFetaBin;
        std::vector <std::pair <double, double> > v_tauSFdetail;
        
        v_tauSFetaBin = m_tauSFetaBin.at(era).at(WPname);
        v_tauSFdetail = m_tauSFdetail.at(era).at(WPname);
        
        for(int iBin = 0; iBin < v_tauSFetaBin.size(); iBin++)
        {
            if(fabs(tau_eta) >= v_tauSFetaBin.at(iBin) &&
                (iBin == v_tauSFetaBin.size()-1 || fabs(tau_eta) < v_tauSFetaBin.at(iBin+1)))
            {
                p_tauSF = v_tauSFdetail.at(iBin);
            }
        }
        
        //p_tauSF.first = p_tauSF.first * (1 + syst*p_tauSF.second/100.0);
        p_tauSF.first = p_tauSF.first + syst*p_tauSF.second;
        
        return p_tauSF;
    }
    
    
    std::pair <double, double> getTauES(
        int decayMode,
        std::string era,
        Common::SYST_TYPE syst
    )
    {
        std::map <std::string, std::map <int, std::pair <double, double> > > m_tauESdetail;
        
        std::map <int, std::pair <double, double> > m_tauESdetail_2016 = {
            {0, std::make_pair(-0.5, 1.2)},
            {1, std::make_pair(1.1, 1.2)},
            {10, std::make_pair(0.6, 1.2)}
        };
        
        std::map <int, std::pair <double, double> > m_tauESdetail_2017 = {
            {0, std::make_pair(0.7, 0.8)},
            {1, std::make_pair(-0.2, 0.9)},
            {10, std::make_pair(0.1, 0.9)}
        };
        
        m_tauESdetail["2016"] = m_tauESdetail_2016;
        m_tauESdetail["2017"] = m_tauESdetail_2017;
        
        if(m_tauESdetail.at(era).find(decayMode) == m_tauESdetail.at(era).end())
        {
            return std::make_pair(1.0, 0.0);
        }
        
        std::pair <double, double> p_tauES = m_tauESdetail.at(era).at(decayMode);
        
        p_tauES.first = 1 + (p_tauES.first + syst*p_tauES.second)/100.0;
        
        return p_tauES;
    }
}

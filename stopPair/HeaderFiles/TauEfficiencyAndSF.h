# ifndef TauEfficiencyAndSF_H
# define TauEfficiencyAndSF_H


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


namespace TauEfficiencyAndSF
{
    class TauEfficiencyAndSF
    {
        public:
        
        std::string inputFileName;
        TFile *inputFile;
        
        std::string histName_num;
        TH2F *h2_efficiency_num;
        
        std::string histName_den;
        TH2F *h2_efficiency_den;
        
        TH2F *h2_efficiency;
        
        
        TauEfficiencyAndSF(
            std::string inputFileName,
            std::string histName_num,
            std::string histName_den
        );
        
        
        double getEfficiency(double pT, double eta);
    };
    
    
    class TauFastFullSF
    {
        public:
        
        //
        std::string inputFileName_fast;
        TFile *inputFile_fast;
        
        std::string histName_num_fast;
        TH2F *h2_efficiency_num_fast;
        
        std::string histName_den_fast;
        TH2F *h2_efficiency_den_fast;
        
        TH2F *h2_efficiency_fast;
        
        //
        std::string inputFileName_full;
        TFile *inputFile_full;
        
        std::string histName_num_full;
        TH2F *h2_efficiency_num_full;
        
        std::string histName_den_full;
        TH2F *h2_efficiency_den_full;
        
        TH2F *h2_efficiency_full;
        
        //
        TH2F *h2_SF;
        
        
        TauFastFullSF(
            std::string inputFileName_fast,
            std::string histName_num_fast,
            std::string histName_den_fast,
            std::string inputFileName_full,
            std::string histName_num_full,
            std::string histName_den_full,
            std::vector <double> v_reBinX = {},
            std::vector <double> v_reBinY = {},
            bool debug = false
        );
        
        
        std::pair <double, double> getSF(
            double pT, double eta,
            Common::SYST_TYPE syst = Common::SYST_CENTRAL
        );
    };
    
    
    std::pair <double, double> getTauSF(
        double tau_pT, double tau_eta,
        std::string WPname,
        std::string era,
        Common::SYST_TYPE syst = Common::SYST_CENTRAL
    );
    
    
    std::pair <double, double> getTauES(
        int decayMode,
        std::string era,
        Common::SYST_TYPE syst = Common::SYST_CENTRAL
    );
}


# endif

# ifndef TauPromptAndFakeRate_H
# define TauPromptAndFakeRate_H


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


namespace TauPromptAndFakeRate
{
    class TauPromptAndFakeRate
    {
        public:
        
        // Prompt
        std::vector <std::string> v_inputFileName_prompt;
        TFile *inputFile_prompt;
        
        std::string histName_num_prompt;
        TH2F *h2_efficiency_num_prompt;
        
        std::string histName_den_prompt;
        TH2F *h2_efficiency_den_prompt;
        
        TH2F *h2_efficiency_prompt;
        
        
        // Fake
        std::vector <std::string> v_inputFileName_fake;
        TFile *inputFile_fake;
        
        // 1
        std::string histName_num_fake_1;
        TH2F *h2_efficiency_num_fake_1;
        
        std::string histName_den_fake_1;
        TH2F *h2_efficiency_den_fake_1;
        
        TH2F *h2_efficiency_fake_1;
        
        // 2
        std::string histName_num_fake_2;
        TH2F *h2_efficiency_num_fake_2;
        
        std::string histName_den_fake_2;
        TH2F *h2_efficiency_den_fake_2;
        
        TH2F *h2_efficiency_fake_2;
        
        
        TauPromptAndFakeRate(
            std::vector <std::string> v_inputFileName_prompt,
            std::string histName_num_prompt,
            std::string histName_den_prompt,
            
            std::vector <std::string> v_inputFileName_fake,
            std::string histName_num_fake_1,
            std::string histName_den_fake_1,
            std::string histName_num_fake_2,
            std::string histName_den_fake_2,
            
            std::vector <double> v_pTbin = {}
        );
        
        
        std::pair <double, double> getPromptRate(double pT, double DM, Common::SYST_TYPE syst = Common::SYST_CENTRAL);
        std::pair <double, double> getFakeRate(
            double pT,
            double DM,
            std::string syst_name = "nominal",
            Common::SYST_TYPE syst_type = Common::SYST_CENTRAL
        );
    };
}


# endif

# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTable.h>
# include <TTree.h>
# include <TVector.h>

# include "HeaderFiles/Analyze_tauTau.h"
# include "HeaderFiles/Common.h"
# include "HeaderFiles/CustomInfo_data.h"
# include "HeaderFiles/Output_RECO.h"


int main()
{
    std::string process = "@process@";
    std::string dir = "@dir@";
    std::string otherInfoDir = "@otherInfoDir@";
    std::string sourceFileName = "@sourceFileName@";
    std::string era = "@era@";
    
    std::string syst_name = "@syst_name@";
    Common::SYST_TYPE syst_type = Common::SYST_CENTRAL;
    
    if(
        !process.compare(Common::process_str_template) ||
        !dir.compare(Common::dir_str_template) ||
        !otherInfoDir.compare(Common::otherInfoDir_str_template) ||
        !sourceFileName.compare(Common::sourceFileName_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        //process = "Tau_Run2016H-18Apr2017-v1_MINIAOD";
        //dir = "tauTau_data/output_analyzed/Tau_Run2016H-18Apr2017-v1_MINIAOD_tauTau_analysis";
        //otherInfoDir = "tauTau_data";
        //sourceFileName = "sourceFiles/Tau_Run2016H-18Apr2017-v1_MINIAOD/Tau_Run2016H-18Apr2017-v1_MINIAOD_custom.txt";
        //era = "2016";
        
        //process = "Tau_Run2016H-07Aug17-v1_MINIAOD";
        //dir = "tauTau_data/output_analyzed/Tau_Run2016H-07Aug17-v1_MINIAOD_tauTau_analysis";
        //otherInfoDir = "tauTau_data";
        //sourceFileName = "sourceFiles/Tau_Run2016H-07Aug17-v1_MINIAOD/Tau_Run2016H-07Aug17-v1_MINIAOD_custom.txt";
        //era = "2016";
        
        process = "Tau_Run2017F-31Mar2018-v1_MINIAOD";
        dir = "tauTau_data/output_analyzed/Tau_Run2017F-31Mar2018-v1_MINIAOD_tauTau_analysis";
        otherInfoDir = "tauTau_data";
        sourceFileName = "sourceFiles/Tau_Run2017F-31Mar2018-v1_MINIAOD/Tau_Run2017F-31Mar2018-v1_MINIAOD_custom.txt";
        era = "2017";
        
        syst_name = "";
        syst_type = Common::SYST_CENTRAL;
    }
    
    int scaleVariationIndex = 0;
    
    bool isMC = false;
    bool isSUSY = false;
    
    Analyze_tauTau::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        isMC,
        isSUSY,
        era.c_str(),
        Common::m_correction,
        syst_name,
        syst_type,
        scaleVariationIndex
    );
    
    
    return 0;
}

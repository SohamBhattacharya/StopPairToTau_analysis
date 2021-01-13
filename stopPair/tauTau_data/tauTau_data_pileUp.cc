# include "HeaderFiles/PileUpCalc.h"


int main()
{
    std::string process = "@process@";
    std::string dir = "@dir@";
    std::string otherInfoDir = "@otherInfoDir@";
    std::string sourceFileName = "@sourceFileName@";
    std::string era = "@era@";
    
    if(
        !process.compare(Common::process_str_template) ||
        !dir.compare(Common::dir_str_template) ||
        !otherInfoDir.compare(Common::otherInfoDir_str_template) ||
        !sourceFileName.compare(Common::sourceFileName_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        process = "Tau_Run2017F-31Mar2018-v1_MINIAOD";
        dir = "tauTau_data/output_pileUp/Tau_Run2017F-31Mar2018-v1_MINIAOD";
        otherInfoDir = "tauTau_data";
        sourceFileName = "sourceFiles/Tau_Run2017F-31Mar2018-v1_MINIAOD/Tau_Run2017F-31Mar2018-v1_MINIAOD_custom.txt";
        era = "2017";
    }
    
    bool isMC = false;
    
    PileUpCalc::initialize(
        process,
        dir,
        sourceFileName,
        isMC
    );
    
    return 0;
}

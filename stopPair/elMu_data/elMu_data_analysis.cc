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

# include "HeaderFiles/Analyze_elMu.h"
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
    
    if(
        !process.compare(Common::process_str_template) ||
        !dir.compare(Common::dir_str_template) ||
        !otherInfoDir.compare(Common::otherInfoDir_str_template) ||
        !sourceFileName.compare(Common::sourceFileName_str_template) ||
        !era.compare(Common::era_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        process = "MuonEG_Run2017F-31Mar2018-v1_MINIAOD";
        dir = "elMu_data/output_analyzed/MuonEG_Run2017F-31Mar2018-v1_MINIAOD_elMu_analysis";
        otherInfoDir = "elMu_data";
        sourceFileName = "sourceFiles/MuonEG_Run2017F-31Mar2018-v1_MINIAOD/MuonEG_Run2017F-31Mar2018-v1_MINIAOD_custom.txt";
        era = "2017";
    }
    
    bool isMC = false;
    bool isSUSY = false;
    
    Analyze_elMu::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        era.c_str(),
        isMC,
        isSUSY,
        Common::m_correction
    );
    
    return 0;
}

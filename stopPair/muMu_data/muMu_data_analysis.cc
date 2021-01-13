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

# include "HeaderFiles/Analyze_muMu.h"
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
        
        process = "SingleMuon_Run2017F-31Mar2018-v1_MINIAOD";
        dir = "muMu_data/output_analyzed/SingleMuon_Run2017F-31Mar2018-v1_MINIAOD_muMu_analysis";
        otherInfoDir = "muMu_data";
        sourceFileName = "sourceFiles/SingleMuon_Run2017F-31Mar2018-v1_MINIAOD/SingleMuon_Run2017F-31Mar2018-v1_MINIAOD_custom.txt";
        era = "2017";
    }
    
    bool isMC = false;
    
    Analyze_muMu::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        era.c_str(),
        isMC,
        Common::m_correction
    );
    
    return 0;
}

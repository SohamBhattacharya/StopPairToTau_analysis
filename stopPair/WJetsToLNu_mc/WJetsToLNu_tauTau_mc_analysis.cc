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

# include "HeaderFiles/Common.h"
# include "HeaderFiles/CustomInfo_mc.h"
# include "HeaderFiles/Output_GEN.h"
# include "HeaderFiles/Output_RECO.h"
# include "HeaderFiles/Analyze_tauTau.h"


int main()
{
    std::string process = "@process@";
    std::string dir = "@dir@";
    std::string otherInfoDir = "@otherInfoDir@";
    std::string sourceFileName = "@sourceFileName@";
    std::string era = "@era@";
    
    std::string syst_name = "@syst_name@";
    Common::SYST_TYPE syst_type = Common::SYST_CENTRAL;
    
    std::string scaleVariationIndex_str = "@scaleVariationIndex@";
    
    if(
        !process.compare(Common::process_str_template) ||
        !dir.compare(Common::dir_str_template) ||
        !otherInfoDir.compare(Common::otherInfoDir_str_template) ||
        !sourceFileName.compare(Common::sourceFileName_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        process = "WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8";
        dir = "WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis";
        otherInfoDir = "WJetsToLNu_mc";
        sourceFileName = "sourceFiles/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_custom.txt";
        era = "2016";
        
        scaleVariationIndex_str = "0";
    }
    
    bool isMC = true;
    bool isSUSY = false;
    
    int scaleVariationIndex = std::stoi(scaleVariationIndex_str);
    
    Analyze_tauTau::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        isMC,
        isSUSY,
        era.c_str(),
        Common::m_eventWeight_nJetBin_WJetsToLNu.at(era),
        Common::m_correction,
        syst_name,
        syst_type,
        scaleVariationIndex
    );
    
    return 0;
}

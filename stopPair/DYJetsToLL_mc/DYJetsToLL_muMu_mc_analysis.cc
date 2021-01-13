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
        !sourceFileName.compare(Common::sourceFileName_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        process = "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16";
        dir = "DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_muMu_analysis";
        otherInfoDir = "DYJetsToLL_mc";
        sourceFileName = "sourceFiles/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_custom.txt";
        era = "2016";
    }
    
    bool isMC = true;
    
    std::vector <double> v_eventWeight_nJetBin = Common::m_eventWeight_nJetBin_DYJetsToLL.at(era);
    
    std::map <std::string, bool> m_correction = Common::m_correction;
    
    m_correction.at(Common::ZptReweighting_str) = true;
    
    Analyze_muMu::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        era.c_str(),
        isMC,
        v_eventWeight_nJetBin,
        m_correction
    );
    
    return 0;
}

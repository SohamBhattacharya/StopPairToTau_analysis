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
# include "HeaderFiles/Analyze_muTau.h"


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
        
        //process = "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16";
        //dir = "DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_muTau_analysis";
        //otherInfoDir = "DYJetsToLL_mc";
        //sourceFileName = "sourceFiles/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_custom.txt";
        //era = "2016";
        
        //process = "DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16";
        //dir = "DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_muTau_analysis";
        //otherInfoDir = "DYJetsToLL_mc";
        //sourceFileName = "sourceFiles/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_custom.txt";
        //era = "2016";
        
        process = "DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17";
        dir = "DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_muTau_analysis";
        otherInfoDir = "DYJetsToLL_mc";
        sourceFileName = "sourceFiles/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_Fall17_custom.txt";
        era = "2017";
        
        scaleVariationIndex_str = "0";
    }
    
    bool isMC = true;
    bool isSUSY = false;
    
    int scaleVariationIndex = std::stoi(scaleVariationIndex_str);
    
    
    std::map <std::string, bool> m_correction = Common::m_correction;
    
    m_correction.at(Common::ZptReweighting_str) = true;
    
    Analyze_muTau::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        isMC,
        isSUSY,
        era.c_str(),
        Common::m_eventWeight_nJetBin_DYJetsToLL.at(era),
        m_correction,
        syst_name,
        syst_type,
        scaleVariationIndex
    );
    
    return 0;
}

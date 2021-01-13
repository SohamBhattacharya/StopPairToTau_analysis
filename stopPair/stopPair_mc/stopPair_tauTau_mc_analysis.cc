# include <iostream>
# include <fstream>
# include <string>
# include <utility>
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
    
    std::string stop1_m_str = "@stop1_m@";
    std::string neutralino1_m_str = "@neutralino1_m@";
    
    std::string scaleVariationIndex_str = "@scaleVariationIndex@";
    
    if(
        !process.compare(Common::process_str_template) ||
        !dir.compare(Common::dir_str_template) ||
        !otherInfoDir.compare(Common::otherInfoDir_str_template) ||
        !sourceFileName.compare(Common::sourceFileName_str_template)
        // !stop1_m_str.compare(Common::stop1_m_str_template) ||
        // !neutralino1_m_str.compare(Common::neutralino_m_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        process = "SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16";
        dir = "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis";
        otherInfoDir = "stopPair_mc";
        sourceFileName = "sourceFiles/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_custom.txt";
        era = "2016";
        
        
        //process = "SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17";
        //dir = "stopPair_mc/output_analyzed/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis";
        //otherInfoDir = "stopPair_mc";
        //sourceFileName = "sourceFiles/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_custom.txt";
        //era = "2017";
        
        stop1_m_str = "500";
        neutralino1_m_str = "100";
        
        scaleVariationIndex_str = "0";
    }
    
    stop1_m_str = "500";
    neutralino1_m_str = "100";
    
    int stop1_m = std::stoi(stop1_m_str);
    int neutralino1_m = std::stoi(neutralino1_m_str);
    
    std::pair <int, int> massPoint_stop1_neutralino1(stop1_m, neutralino1_m);
    
    bool isMC = true;
    bool isSUSY = true;
    
    int scaleVariationIndex = std::stoi(scaleVariationIndex_str);
    
    Analyze_tauTau::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        isMC,
        isSUSY,
        era.c_str(),
        massPoint_stop1_neutralino1,
        Common::m_correction,
        syst_name,
        syst_type,
        scaleVariationIndex
    );
    
    return 0;
}

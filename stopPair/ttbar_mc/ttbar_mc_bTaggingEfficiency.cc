# include <string>
# include <vector>

# include "HeaderFiles/Common.h"
# include "HeaderFiles/BTaggingEfficiencyCalc.h"


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
        
        process = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16";
        dir = "ttbar_mc/output_bTaggingEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_bTaggingEfficiency";
        otherInfoDir = "ttbar_mc";
        sourceFileName = "sourceFiles/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_custom.txt";
        era = "2016";
        
        //process = "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17";
        //dir = "ttbar_mc/output_bTaggingEfficiency/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_bTaggingEfficiency";
        //otherInfoDir = "ttbar_mc";
        //sourceFileName = "sourceFiles/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_custom.txt";
        //era = "2017";
    }
    
    bool isMC = true;
    
    
    BTaggingEfficiencyCalc::calculateEfficiency(
        process,
        dir,
        otherInfoDir,
        sourceFileName,
        isMC,
        era,
        Common::v_bDiscriminatorName,
        Common::vv_bDiscriminatorWPname,
        Common::v_pT_bin_bTaggingEfficiency,
        Common::v_eta_bin_bTaggingEfficiency
    );
    
    return 0;
}

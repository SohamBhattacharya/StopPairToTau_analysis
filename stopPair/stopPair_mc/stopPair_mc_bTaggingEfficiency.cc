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
        
        process = "SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16";
        dir = "stopPair_mc/output_bTaggingEfficiency/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_bTaggingEfficiency";
        otherInfoDir = "stopPair_mc";
        sourceFileName = "sourceFiles/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_custom.txt";
        era = "2016";
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

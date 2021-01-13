# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include "HeaderFiles/Common.h"
# include "HeaderFiles/TauIdIsoEfficiency_mc.h"


int main()
{
    std::string process = "@process@";
    std::string dir = "@dir@";
    std::string sourceFileName = "@sourceFileName@";
    std::string era = "@era@";
    
    if(
        !process.compare(Common::process_str_template) ||
        !dir.compare(Common::dir_str_template) ||
        !sourceFileName.compare(Common::sourceFileName_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        process = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16";
        dir = "ttbar_mc/output_tauIdIsoEfficiency/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauIdIsoEfficiency";
        sourceFileName = "sourceFiles/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_custom.txt";
        era = "2016";
        
        //process = "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17";
        //dir = "ttbar_mc/output_tauIdIsoEfficiency/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_tauIdIsoEfficiency";
        //sourceFileName = "sourceFiles/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_Fall17_custom.txt";
        //era = "2017";
    }
    
    
    TauIdIsoEfficiency_mc::run(
        process,
        dir,
        sourceFileName,
        era
    );
    
    return 0;
}

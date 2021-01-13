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
        
        process = "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8";
        dir = "output_tauIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauIdIsoEfficiency";
        sourceFileName = "sourceFiles/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_custom.txt";
        era = "2016";
    }
    
    
    TauIdIsoEfficiency_mc::run(
        process,
        dir,
        sourceFileName,
        era
    );
    
    return 0;
}

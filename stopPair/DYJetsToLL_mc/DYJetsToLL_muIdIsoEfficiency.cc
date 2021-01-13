# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include "HeaderFiles/Common.h"
# include "HeaderFiles/MuIdIsoEfficiency_mc.h"


int main()
{
    std::string process = "@process@";
    std::string dir = "@dir@";
    std::string sourceFileName = "@sourceFileName@";
    
    if(
        !process.compare(Common::process_str_template) ||
        !dir.compare(Common::dir_str_template) ||
        !sourceFileName.compare(Common::sourceFileName_str_template)
    )
    {
        std::printf("Warning!!! \n");
        std::printf("Invalid configuration. Using default options. \n\n");
        
        process = "DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8";
        dir = "DYJetsToLL_mc/output_muIdIsoEfficiency/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muIdIsoEfficiency";
        sourceFileName = "sourceFiles/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_custom.txt";
    }
    
    
    MuIdIsoEfficiency_mc::run(
        process,
        dir,
        sourceFileName
    );
    
    return 0;
}

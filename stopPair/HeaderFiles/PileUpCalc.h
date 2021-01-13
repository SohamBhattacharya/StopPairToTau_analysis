# ifndef PileUpCalc_H
# define PileUpCalc_H


# include <iostream>
# include <string>
# include <vector>

# include <TFile.h>
# include <TH1F.h>
# include <TTree.h>

# include "Common.h"
# include "CustomInfo_mc.h"


namespace PileUpCalc
{
    void initialize(
        std::string process,
        std::string dir,
        std::string sourceFileName,
        bool isMC
    );
    
    
    void getPileUpDistribution(
        CustomInfo_mc::Info *input,
        TFile *outputFile,
        bool isMC
    );
}



# endif

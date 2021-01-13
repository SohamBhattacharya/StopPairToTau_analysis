# ifndef BTaggingEfficiencyCalc_H
# define BTaggingEfficiencyCalc_H


# include <iostream>
# include <string>
# include <utility>
# include <vector>

# include <TFile.h>
# include <TH2F.h>

# include "Common.h"


namespace BTaggingEfficiencyCalc
{
    void calculateEfficiency(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::vector <std::string> v_bDiscriminatorName,
        std::vector <std::vector <std::string> > v_bDiscriminatorWPname,
        std::vector <double> v_pT_bin,
        std::vector <double> v_eta_bin
    );
}



# endif

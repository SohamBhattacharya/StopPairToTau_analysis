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

# include "HeaderFiles/PileUpCalc.h"


int main()
{
    std::string process = "@process@";
    std::string dir = "@dir@";
    std::string otherInfoDir = "@otherInfoDir@";
    std::string sourceFileName = "@sourceFileName@";
    std::string era = "@era@";
    
    bool isMC = true;
    
    PileUpCalc::initialize(
        process,
        dir,
        sourceFileName,
        isMC
    );
    
    return 0;
}

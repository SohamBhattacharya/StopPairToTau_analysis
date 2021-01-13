# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTable.h>
# include <TTree.h>
# include <TVector.h>

# include "HeaderFiles/Common.h"
# include "HeaderFiles/FakeRate_tauTau.h"


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
        
        
        //process = "Tau_Run2016H-17Jul2018-v1_MINIAOD";
        //dir = "tauTau_data/output_tauTau_fakeRate/Tau_Run2016H-17Jul2018-v1_MINIAOD_tauTau_fakeRate";
        //otherInfoDir = "tauTau_data";
        //sourceFileName = "sourceFiles/Tau_Run2016H-17Jul2018-v1_MINIAOD/Tau_Run2016H-17Jul2018-v1_MINIAOD_custom.txt";
        //era = "2016";
        
        
        process = "Tau_Run2017B-31Mar2018-v1_MINIAOD";
        dir = "tauTau_data/output_tauTau_fakeEstimation/Tau_Run2017B-31Mar2018-v1_MINIAOD_tauTau_fakeEstimation";
        otherInfoDir = "tauTau_data";
        sourceFileName = "sourceFiles/Tau_Run2017B-31Mar2018-v1_MINIAOD/Tau_Run2017B-31Mar2018-v1_MINIAOD_custom.txt";
        era = "2017";
    }
    
    bool isMC = false;
    
    FakeRate_tauTau::initialize(
        process,
        dir,
        otherInfoDir,
        sourceFileName,
        isMC,
        era
    );
    
    return 0;
}

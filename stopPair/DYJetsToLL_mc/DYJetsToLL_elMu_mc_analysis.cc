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

# include "HeaderFiles/Analyze_elMu.h"
# include "HeaderFiles/Common.h"
# include "HeaderFiles/CustomInfo_data.h"
# include "HeaderFiles/Output_RECO.h"


int main()
{
    std::string process = "@process@";
    std::string dir = "@dir@";
    std::string otherInfoDir = "@otherInfoDir@";
    std::string sourceFileName = "@sourceFileName@";
    std::string era = "@era@";
    
    bool isMC = true;
    bool isSUSY = false;
    
    std::vector <double> v_eventWeight_nJetBin = Common::m_eventWeight_nJetBin_DYJetsToLL.at(era);
    
    Analyze_elMu::initialize(
        process.c_str(),
        dir.c_str(),
        otherInfoDir.c_str(),
        sourceFileName.c_str(),
        era.c_str(),
        isMC,
        isSUSY,
        v_eventWeight_nJetBin,
        Common::m_correction
    );
    
    return 0;
}

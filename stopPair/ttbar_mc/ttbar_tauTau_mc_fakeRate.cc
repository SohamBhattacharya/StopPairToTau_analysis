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
        
        process = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16";
        dir = "ttbar_mc/output_tauTau_fakeRate/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_tauTau_fakeRate";
        otherInfoDir = "ttbar_mc";
        sourceFileName = "sourceFiles/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_Summer16_custom.txt";
        era = "2016";
    }
    
    bool isMC = true;
    
    FakeRate_tauTau::initialize(
        process,
        dir,
        otherInfoDir,
        sourceFileName,
        isMC,
        era,
        Common::m_eventWeight_nJetBin_DYJetsToLL.at(era)
    );
    
    return 0;
}

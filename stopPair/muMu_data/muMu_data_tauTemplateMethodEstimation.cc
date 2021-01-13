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
# include "HeaderFiles/TemplateMethodEstimation.h"


int main()
{
    char process[] = "@process@";
    char dir[] = "@dir@";
    char otherInfoDir[] = "@otherInfoDir@";
    char sourceFileName[] = "@sourceFileName@";
    
    //char process[] = "SingleMuon_Run2016H-18Apr2017-v1_MINIAOD";
    //char dir[] = "muMu_data/output_tauTemplateMethodEstimation/SingleMuon_Run2016H-18Apr2017-v1_MINIAOD_muMu_tauTemplateMethodEstimation";
    //char otherInfoDir[] = "muMu_data";
    //char sourceFileName[] = "sourceFiles/SingleMuon_Run2016H-18Apr2017-v1_MINIAOD/SingleMuon_Run2016H-18Apr2017-v1_MINIAOD_custom.txt";

    bool isMC = false;
    
    TemplateMethodEstimation::initialize(
        process,
        dir,
        otherInfoDir,
        sourceFileName,
        isMC
    );
    
    return 0;
}

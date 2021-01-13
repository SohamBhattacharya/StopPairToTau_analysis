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
# include "HeaderFiles/CustomInfo_mc.h"
# include "HeaderFiles/Output_GEN.h"
# include "HeaderFiles/Output_RECO.h"
# include "HeaderFiles/TemplateMethodEstimation.h"


int main()
{
    char process[] = "@process@";
    char dir[] = "@dir@";
    char otherInfoDir[] = "@otherInfoDir@";
    char sourceFileName[] = "@sourceFileName@";
    
    bool isMC = true;
    
    TemplateMethodEstimation::initialize(
        process,
        dir,
        otherInfoDir,
        sourceFileName,
        isMC,
        Common::v_eventWeight_nJetBin_WJetsToLNu
    );
    
    return 0;
}

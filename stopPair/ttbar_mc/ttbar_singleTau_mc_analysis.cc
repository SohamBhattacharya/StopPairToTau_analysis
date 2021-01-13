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

# include "../HeaderFiles/Analyze_singleTau.h"
# include "../HeaderFiles/Common.h"
# include "../HeaderFiles/CustomInfo_mc.h"
# include "../HeaderFiles/Output_GEN.h"
# include "../HeaderFiles/Output_RECO.h"


int main()
{
    //char process[] = "@1@";
    //char dir[] = "@2@";
    
    char process[] = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8";
    char dir[] = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_singleTau_analysis";
    char otherInfoDir[] = "ttbar_mc";
    
    bool isMC = true;
    bool isSUSY = false;
    
    Analyze_singleTau::initialize(
        process,
        dir,
        otherInfoDir,
        isMC,
        isSUSY
    );
    
    return 0;
}

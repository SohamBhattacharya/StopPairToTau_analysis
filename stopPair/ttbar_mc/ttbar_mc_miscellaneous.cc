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
# include "HeaderFiles/Miscellaneous.h"


int main()
{
    //char process[] = "@process@";
    //char dir[] = "@dir@";
    //char otherInfoDir[] = "@otherInfoDir@";
    //char sourceFileName[] = "@sourceFileName@";
    
    char process[] = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8";
    char dir[] = "ttbar_mc/output_miscellaneous/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_miscellaneous";
    char otherInfoDir[] = "ttbar_mc";
    char sourceFileName[] = "sourceFiles/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_custom.txt";
    
    bool isMC = true;
    
    Miscellaneous::initialize(
        process,
        dir,
        otherInfoDir,
        sourceFileName
    );
    
    return 0;
}

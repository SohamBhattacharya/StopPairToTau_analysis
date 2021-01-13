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

# include "../HeaderFiles/Common.h"
# include "../HeaderFiles/CustomInfo_mc.h"
# include "../HeaderFiles/Output_GEN.h"
# include "../HeaderFiles/Output_RECO.h"
# include "../HeaderFiles/Analyze_SM_mc.h"


int main()
{
    char process[] = "@1@";
    
    Analyze_SM_mc::initialize(process);
    
    return 0;
}

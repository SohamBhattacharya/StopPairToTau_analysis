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
# include "HeaderFiles/TemplateMethodEstimation_singleMuon.h"


int main()
{
    //char process[] = "@process@";
    //char dir[] = "@dir@";
    //char otherInfoDir[] = "@otherInfoDir@";
    //char sourceFileName[] = "@sourceFileName@";
    
    char process[] = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8";
    char dir[] = "ttbar_mc/output_tauTemplateMethodEstimation/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauTemplateMethodEstimation_singleMuon";
    char otherInfoDir[] = "ttbar_mc";
    char sourceFileName[] = "sourceFiles/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_custom.txt";
    
    bool isMC = true;
    
    TemplateMethodEstimation_singleMuon::initialize(
        process,
        dir,
        otherInfoDir,
        sourceFileName,
        isMC
    );
    
    return 0;
}

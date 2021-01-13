# include "../HeaderFiles/TMVA_treeMaker_tauTau.h"


int main()
{
    char process[] = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8";//"@1@";
    char dir[] = "TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauTau_TMVAtree";//"@2@";
    
    bool isSUSY = false;
    
    TMVA_treeMaker_tauTau::initialize(process, dir,
        isSUSY);
    
    return 0;
}

# include "../HeaderFiles/TMVA_treeMaker_tauTau.h"


int main()
{
    char process[] = "@process@";//"SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8";
    char dir[] = "@dir@";//"SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_500_325_tauTau";
    
    bool isSUSY = true;
    
    int stop1_m = @stop1_m@;
    int neutralino1_m = @neutralino1_m@;
    
    std::pair <int, int> massPoint_stop1_neutralino1(stop1_m, neutralino1_m);
    
    std::string sourceFile = "@sourceFile@";
    
    TMVA_treeMaker_tauTau::initialize(process, dir,
        isSUSY,
        massPoint_stop1_neutralino1,
        sourceFile
    );
    
    return 0;
}

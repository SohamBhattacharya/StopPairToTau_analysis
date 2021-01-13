# ifndef TMVA_treeMaker_tauTau_H
# define TMVA_treeMaker_tauTau_H


# include <iostream>
# include <fstream>
# include <string>
# include <utility>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TTree.h>

# include "Common.h"
# include "CustomInfo_mc.h"
# include "TMVA_treeContent_tauTau.h"


namespace TMVA_treeMaker_tauTau
{
    void initialize(const char *process, const char *dir,
        bool isSUSY
    );
    
    
    void initialize(const char *process, const char *dir,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1,
        std::string sourceFile
    );
    
    
    void makeTree(CustomInfo_mc::Info *input,
        TMVA_treeContent_tauTau::Info *output,
        const char *tau_isoOption,
        const char *tauPair_signOption,
        bool isSUSY,
        std::pair <int, int> massPoint_stop1_neutralino1
    );
}


# endif

# ifndef GetISRinfo_H
# define GetISRinfo_H


# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <utility>
# include <vector>

# include "CustomInfo_mc.h"


namespace GetISRinfo
{
    class Output_ISRinfo
    {
        public:
        
        char *details;
        char *nameAddon;
        char *titleAddon;
        
        TH1F *h1_jet_nISR_reco;
        
        
        Output_ISRinfo(const char *details);
        
        
        void writeData();
        
        
        void freeMemory();
    };
    
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        std::string era
    );
    
    
    void analyze(
        CustomInfo_mc::Info *input,
        std::map <std::pair <int, int>, Output_ISRinfo*> *m_output
    );
}


# endif

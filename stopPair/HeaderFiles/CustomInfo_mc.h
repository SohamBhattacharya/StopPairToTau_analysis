# ifndef CustomInfo_mc_H
# define CustomInfo_mc_H


# include <iostream>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TH1F.h>
# include <TTree.h>

# include "Common.h"
# include "CustomInfo_common.h"


namespace CustomInfo_mc
{
    class Info : public CustomInfo_common::Info
    {
        public:
        
        
        Info(
            const char *fileName,
            const char *treeName_gen,
            std::vector <const char*> v_object_gen,
            const char *treeName_reco,
            std::vector <const char*> v_object_reco,
            const char *mode,
            const char *fileName_pileUp_mc, const char *histName_pileUp_mc,
            const char *fileName_pileUp_data, const char *histName_pileUp_data,
            const char *fileName_pileUp_data_systUp = 0, const char *histName_pileUp_data_systUp = 0,
            const char *fileName_pileUp_data_systDown = 0, const char *histName_pileUp_data_systDown = 0
        );
        
        
        void clear();
        
        TH1F* getPileUp(const char *fileName_pileUp, \
            const char *histName_pileUp) override;
        
        TH1F* choosePileUpHist_data(Common::SYST_TYPE syst);
        
        void linkBranch_gen(const char *mode) override;
        
        void linkBranch_reco(const char *mode) override;
        
        void freeMemory() override;
        
        void writeData() override;
        
        void sort_pT(const char *opt) override;
        
        void checkSeparation(const char *opt1, const char *opt2, double dRcut, const char *del_opt) override;
        
        bool isGenMatched(CLHEP::HepLorentzVector object_4mom, const char *object, \
            double dR, double object_pTcut = 0, double object_etaCut = 999) override;
    };
}


# endif

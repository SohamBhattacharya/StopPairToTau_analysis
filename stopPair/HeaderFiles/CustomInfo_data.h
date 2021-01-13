# ifndef CustomInfo_data_H
# define CustomInfo_data_H


# include "Common.h"
# include "CustomInfo_common.h"


namespace CustomInfo_data
{
    class Info : public CustomInfo_common::Info
    {
        public:
        
        
        Info( \
            const char *fileName, \
            const char *treeName_reco, \
            std::vector <const char*> v_object_reco, \
            const char *mode);
        
        
        void clear() override;
        
        void linkBranch_reco(const char *mode) override;
        
        void freeMemory() override;
        
        void writeData() override;
    };
}


# endif

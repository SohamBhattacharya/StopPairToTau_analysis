# ifndef GetGenParamInfo_H
# define GetGenParamInfo_H


# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <utility>
# include <vector>

# include "CustomInfo_mc.h"


namespace GetGenParamInfo
{
    extern std::map <std::pair <int, int>, int> v_massPoint;
    
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        std::string era
    );
    
    
    void getMassPointInfo(CustomInfo_mc::Info *input);
}


# endif

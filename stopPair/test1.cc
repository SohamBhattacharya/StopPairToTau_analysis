# include <algorithm>
# include <fstream>
# include <iostream>
# include <stdlib.h>
# include <vector>

//# include "HeaderFiles/json.h"
//# include "HeaderFiles/Common.h"


/*template <typename T1> bool isInJsonLumiRange(T1 list, long lumiNumber)
{
    for(int i = 0; i < list.size(); i++)
    {
        long lwr = list[i][0];
        long upr = list[i][1];
        
        bool isFound = (lwr <= lumiNumber && lumiNumber <= upr);
        
        if(isFound)
        {
            return true;
        }
    }
    
    return false;
}


bool isInJson(
    nlohmann::json jsonContent,
    long runNumber,
    long lumiNumber,
    bool debug = false
)
{
    if(debug)
    {
        std::cout << jsonContent << "\n\n";
    }
    
    std::string key = std::to_string(runNumber);
    
    if(jsonContent.find(key) == jsonContent.end())
    {
        if(debug)
        {
            printf("Key \"%s\" not found. \n", key.c_str());
        }
        
        return false;
    }
    
    auto list = jsonContent.at(key);
    
    if(debug)
    {
        std::cout << list << "\n\n";
    }
    
    bool isFound = isInJsonLumiRange(list, lumiNumber);
    
    return isFound;
}*/


int main(int argc, char **v_arg)
{
    //std::ifstream jsonFileStream("resources/unblindingJson/2017/unblindingJson_2017BCDE.json");
    //std::ifstream jsonFileStream("resources/unblindingJson/2017/unblindingJson_2017F.json");
    //nlohmann::json jsonContent;
    //jsonFileStream >> jsonContent;
    //jsonFileStream.close();
    //
    //long long run = std::strtoll(v_arg[0], NULL, 0);
    //long long lumi = std::strtoll(v_arg[1], NULL, 0);
    //
    //bool isFound = Common::isInRunJson(
    //    jsonContent,
    //    run,
    //    lumi,
    //    true
    //);
    //
    //printf("Found lumi %lld in run %lld: %d \n", lumi, run, isFound);
    
    
    std::vector <double> vec = {1, 2, 3, 4, 5};
    
    printf("%d: %f %f \n", vec.size(), vec.at(0), vec.at(1));
    
    vec.erase(vec.begin()+0);
    
    printf("%d: %f %f \n", vec.size(), vec.at(0), vec.at(1));
    
    return 0;
}

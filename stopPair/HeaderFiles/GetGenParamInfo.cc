# include <iostream>
# include <iterator>
# include <fstream>
# include <string>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TFile.h>
# include <TTree.h>


# include "Common.h"
# include "CustomInfo_mc.h"
# include "GetGenParamInfo.h"


namespace GetGenParamInfo
{
    std::map <std::pair <int, int>, int> v_massPoint;
    
    
    void initialize(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        std::string era
    )
    {
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process, process);
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName);
        
        std::string inFile;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        //sprintf(outDir, "output_genParam/%s", process);
        sprintf(outDir, "%s", dir.c_str());
        
        sprintf(command, "mkdir -p %s", outDir);
        system(command);
        
        
        char treePath_gen[Common::str_len];
        char treePath_reco[Common::str_len];
        
        sprintf(treePath_gen, "miniaodsim2custom/gen");
        sprintf(treePath_reco, "miniaodsim2custom/reco");
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {//n++; if(n > 1) break;
            printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("\n");
            
            // Input root file
            std::vector <const char*> v_object_mc_gen = { \
                "genParam"};
            
            std::vector <const char*> v_object_reco = {};
            
            CustomInfo_mc::Info *input_mc;
            
            input_mc = new CustomInfo_mc::Info( \
                inFile.c_str(), \
                treePath_gen, v_object_mc_gen, \
                treePath_reco, v_object_reco, \
                "read", \
                0, 0, \
                0, 0);
            
            
            GetGenParamInfo::getMassPointInfo(input_mc);
            
            printf("\n\n");
            
            
            // Release memory
            input_mc->freeMemory();
            delete input_mc;
        }
        
        
        char outFileName[Common::str_len];
        sprintf(outFileName, "%s/massPointInfo.txt", outDir);
        printf("Output file: %s \n", outFileName);
        
        FILE *outFile = fopen(outFileName, "w");
        
        for(std::map <std::pair <int, int>, int>::iterator iPoint = GetGenParamInfo::v_massPoint.begin(); iPoint != v_massPoint.end(); iPoint++)
        {
            fprintf(outFile, "%d,%d,%d", iPoint->first.first, iPoint->first.second, iPoint->second);
            fprintf(outFile, "\n");
        }
        
        fclose(outFile);
    }
    
    
    void getMassPointInfo(CustomInfo_mc::Info *input)
    {
        int nEvent = input->T_gen->GetEntries();
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if(iEvent == 0 || (iEvent+1) % 1000 == 0 || iEvent == nEvent-1)
            {
                printf("Processing event no. %d / %d \n", iEvent+1, nEvent);
                fflush(stdout);
            }
            
            input->T_gen->GetEntry(iEvent);
            
            std::pair <int, int> p_massPoint((int) input->stop1_m_genParam, (int) input->neutralino1_m_genParam);
            
            // If not-existing already, then create
            if(GetGenParamInfo::v_massPoint.find(p_massPoint) == GetGenParamInfo::v_massPoint.end())
            {
                GetGenParamInfo::v_massPoint[p_massPoint] = 0;
            }
            
            GetGenParamInfo::v_massPoint[p_massPoint]++;
            //printf("stop1_m_genParam %d, neutralino1_m_genParam %d, nEvent %d \n", \
                (int) input->stop1_m_genParam, (int) input->neutralino1_m_genParam, GetGenParamInfo::v_massPoint[p_massPoint]);
        }
    }
}

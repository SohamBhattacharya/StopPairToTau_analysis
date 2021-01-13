# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include <TFile.h>
# include <TH1F.h>

# include "PileUpCalc.h"


namespace PileUpCalc
{
    void initialize(
        std::string process,
        std::string dir,
        std::string sourceFileName,
        bool isMC
    )
    {
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_preAnalyzed.txt", process, process);
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process, process);
        
        std::ifstream sourceFileList;
        sourceFileList.open(sourceFileName.c_str());
        
        std::string inFile;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        //sprintf(outDir, "output_pileUp/%s", process);
        sprintf(outDir, "%s", dir.c_str());
        
        sprintf(command, "mkdir -p %s", outDir);
        system(command);
        
        char treePath_gen[Common::str_len], treePath_reco[Common::str_len];
        sprintf(treePath_gen, "miniaodsim2custom/gen");
        sprintf(treePath_reco, "miniaodsim2custom/reco");
        
        //int n = 0;
        while(std::getline(sourceFileList, inFile))
        {//n++; if(n > 1) break;
            char fileNameStripped[Common::str_len];
            
            sprintf(fileNameStripped, "%s", (inFile.substr(inFile.rfind("/")+1, inFile.rfind(".root")-inFile.rfind("/")-1)).c_str());
            
            char outFile[Common::str_len];
            sprintf(outFile, "%s/%s_pileUp.root", outDir, fileNameStripped);
            
            printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("Output: %s \n", outFile);
            printf("\n");
            
            // Input root file
            std::vector <const char*> v_object_gen = {};
            
            std::vector <const char*> v_object_reco;
            
            if(isMC)
            {
                v_object_reco = {"PU", "vertex"};
            }
            
            else
            {
                v_object_reco = {"vertex"};
            }
            
            CustomInfo_mc::Info *input;
            input = new CustomInfo_mc::Info(
                inFile.c_str(),
                treePath_gen, v_object_gen,
                treePath_reco, v_object_reco,
                "read",
                0, 0,
                0, 0);
            
            
            // Output root file
            TFile *outputFile;
            outputFile = TFile::Open(outFile, "RECREATE");
            
            
            // Get pileup
            getPileUpDistribution(
                input,
                outputFile,
                isMC
            );
            
            printf("\n\n");
            
            // Release memory
            delete outputFile;
            
            input->freeMemory();
            delete input;
        }
    }
    
    
    void getPileUpDistribution(
        CustomInfo_mc::Info *input,
        TFile *outputFile,
        bool isMC
    )
    {
        TH1F *h1_pileUp = new TH1F("pileup", "pileup", 100, 0, 100);
        TH1F *h1_vertex_n = new TH1F("vertex_n", "vertex_n", 100, 0, 100);
        
        int nEvent = input->T_gen->GetEntries();
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            if(iEvent == 0 || (iEvent+1) % 1000 == 0 || iEvent == nEvent-1)
            {
                printf("Processing event %d/%d. \n", iEvent+1, nEvent);
                fflush(stdout);
            }
            
            input->T_reco->GetEntry(iEvent);
            
            if(isMC)
            {
                h1_pileUp->Fill(input->pileUp_n_reco);
            }
            
            h1_vertex_n->Fill(input->vertex_n_reco);
        }
        
        outputFile->cd();
        
        h1_pileUp->Write();
        h1_vertex_n->Write();
        
        delete h1_pileUp;
        delete h1_vertex_n;
    }
}

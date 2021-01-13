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
# include "GetISRinfo.h"


namespace GetISRinfo
{
    Output_ISRinfo::Output_ISRinfo(const char *details)
    {
        this->details = (char*) malloc(Common::str_len * sizeof(char));
        nameAddon = (char*) malloc(Common::str_len * sizeof(char));
        titleAddon = (char*) malloc(Common::str_len * sizeof(char));
        
        sprintf(this->details, "%s", details);
        
        sprintf(nameAddon, "%s", "");
        sprintf(titleAddon, "%s", "");
        
        if(strcmp(details, ""))
        {
            sprintf(nameAddon, "_%s", details);
            sprintf(titleAddon, " [%s]", details);
        }
        
        char histName[Common::str_len];
        char histTitle[Common::str_len];
        
        sprintf(histName, "jet_nISR_reco%s", nameAddon);
        sprintf(histTitle, "jet_nISR_reco %s", titleAddon);
        h1_jet_nISR_reco = new TH1F(histName, histTitle, 20, 0, 20);
        h1_jet_nISR_reco->Sumw2();
    }
    
    
    void Output_ISRinfo::writeData()
    {
        h1_jet_nISR_reco->Write();
    }
    
    
    void Output_ISRinfo::freeMemory()
    {
        delete h1_jet_nISR_reco;
    }
    
    
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
        
        char fileName_massPointInfo[Common::str_len];
        std::vector <std::vector <double> > vv_massPointInfo;
        
        sprintf(fileName_massPointInfo, "%s/output_genParam/%s/XSweightInfo.txt", otherInfoDir.c_str(), process.c_str());
        printf("Mass-point info file: %s \n", fileName_massPointInfo);
        fflush(stdout);
        
        Common::parseCSVto2Dvector(std::string(fileName_massPointInfo), &vv_massPointInfo);
        
        //for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
        //{
        //    if(vv_massPointInfo.at(iMassPoint).at(0) > 1500 || vv_massPointInfo.at(iMassPoint).at(1) > 650)
        //    {
        //        vv_massPointInfo.erase(vv_massPointInfo.begin()+iMassPoint);
        //    }
        //}
        
        printf("# mass-point: %d \n", vv_massPointInfo.size());
        fflush(stdout);
        
        
        char outFile[Common::str_len];
        sprintf(outFile, "%s/ISRinfo.root", outDir);
        printf("Output root file: %s \n", outFile);
        
        TFile *output_analyzed;
        output_analyzed = TFile::Open(outFile, "RECREATE");
        
        
        std::map <std::pair <int, int>, Output_ISRinfo*> m_output;
        
        for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
        {
            std::pair <int, int> p_temp(
                (int) vv_massPointInfo.at(iMassPoint).at(0),
                (int) vv_massPointInfo.at(iMassPoint).at(1)
            );
            
            //printf("Initializing mass-point [%d, %d]. \n", p_temp.first, p_temp.second);
            
            char details_temp[Common::str_len];
            
            sprintf(details_temp, "%d_%d", p_temp.first, p_temp.second);
            m_output[p_temp] = new Output_ISRinfo(details_temp);
        }
        
        
        int n = 0;
        while(std::getline(sourceFileList, inFile))
        {
            n++; if(n > 1) break;
            
            //printf("Analyzing... \n");
            printf("Input: %s \n", inFile.c_str());
            printf("\n");
            
            // Input root file
            std::vector <const char*> v_object_mc_gen = { \
                "genParam"};
            
            std::vector <const char*> v_object_reco = {"jet"};
            
            CustomInfo_mc::Info *input_mc;
            
            input_mc = new CustomInfo_mc::Info(
                inFile.c_str(),
                treePath_gen, v_object_mc_gen,
                treePath_reco, v_object_reco,
                "read",
                0, 0,
                0, 0
            );
            
            
            GetISRinfo::analyze(input_mc, &m_output);
            
            printf("\n\n");
            
            
            // Release memory
            input_mc->freeMemory();
            delete input_mc;
        }
        
        
        char outFileName[Common::str_len];
        sprintf(outFileName, "%s/ISRinfo.txt", outDir);
        printf("Output text file: %s \n", outFileName);
        
        FILE *outTextFile = fopen(outFileName, "w");
        
        fprintf(outTextFile, "#stop1_m,neutralino1_m,normFactor");
        fprintf(outTextFile, "\n");
        
        for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
        {
            std::pair <int, int> p_temp(
                (int) vv_massPointInfo.at(iMassPoint).at(0),
                (int) vv_massPointInfo.at(iMassPoint).at(1)
            );
            
            if(m_output.find(p_temp) == m_output.end())
            {
                continue;
            }
            
            Output_ISRinfo *output = m_output.at(p_temp);
            
            double integral = 0;
            double integral_ISRweighted = 0;
            
            // Include the overflow bin
            for(int iBin = 0; iBin <= (int) output->h1_jet_nISR_reco->GetNbinsX(); iBin++)
            {
                int nWeight = Common::v_ISRweight.size();
                
                double ISRweight;
                
                if(iBin < nWeight)
                {
                    ISRweight = Common::v_ISRweight.at(iBin);
                }
                
                else
                {
                    ISRweight = Common::v_ISRweight.at(nWeight-1);
                }
                
                double binContent = output->h1_jet_nISR_reco->GetBinContent(iBin+1);
                
                integral += binContent;
                integral_ISRweighted += ISRweight * binContent;
                
                printf("[%d, %d] \n", p_temp.first, p_temp.second);
                printf("n-ISRjet: %d, bin content: %0.2f, ISR-weight: %f \n", iBin, binContent, ISRweight);
            }
            
            double normFactor = 1;
            
            if(integral_ISRweighted > 0)
            {
                normFactor = integral / integral_ISRweighted;
            }
            
            fprintf(outTextFile, "%d,%d,%f", p_temp.first, p_temp.second, normFactor);
            fprintf(outTextFile, "\n");
            
            printf("Norm-factor: %f \n", normFactor);
            printf("\n");
        }
        
        for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
        {
            std::pair <int, int> p_temp(
                (int) vv_massPointInfo.at(iMassPoint).at(0),
                (int) vv_massPointInfo.at(iMassPoint).at(1)
            );
            
            char dirName[Common::str_len];
            
            sprintf(dirName, "reco/%s", m_output.at(p_temp)->details);
            output_analyzed->mkdir(dirName);
            output_analyzed->cd(dirName);
            m_output.at(p_temp)->writeData();
        }
        
        for(int iMassPoint = 0; iMassPoint < vv_massPointInfo.size(); iMassPoint++)
        {
            std::pair <int, int> p_temp(
                (int) vv_massPointInfo.at(iMassPoint).at(0),
                (int) vv_massPointInfo.at(iMassPoint).at(1)
            );
            
            m_output.at(p_temp)->freeMemory();
        }
        
        
        fclose(outTextFile);
        
        delete output_analyzed;
    }
    
    
    void analyze(
        CustomInfo_mc::Info *input,
        std::map <std::pair <int, int>, Output_ISRinfo*> *m_output
    )
    {
        int nEvent = input->T_gen->GetEntries();
        
        for (int iEvent = 0; iEvent < nEvent; iEvent++)
        {
            input->T_gen->GetEntry(iEvent);
            input->T_reco->GetEntry(iEvent);
            
            std::pair <int, int> p_temp(
                (int) input->stop1_m_genParam,
                (int) input->neutralino1_m_genParam
            );
            
            //printf("Event mass-point [%d, %d]. \n", p_temp.first, p_temp.second);
            
            if(m_output->find(p_temp) == m_output->end())
            {
                continue;
            }
            
            Output_ISRinfo *output = m_output->at(p_temp);
            
            
            if(iEvent == 0 || (iEvent+1) % 1000 == 0 || iEvent == nEvent-1)
            {
                printf("[%s] Processing event no. %d / %d \n", output->nameAddon, iEvent+1, nEvent);
                fflush(stdout);
            }
            
            
            int jet_n_reco = input->jet_n_reco;
            
            int jet_nISR = 0;
            
            for(int iJet = 0; iJet < jet_n_reco; iJet++)
            {
                if(!input->v_jet_isISR_reco->at(iJet))
                {
                    continue;
                }
                
                CLHEP::HepLorentzVector jet_4mom_reco;
                
                jet_4mom_reco.setT(fabs(input->v_jet_E_reco->at(iJet)));
                jet_4mom_reco.setX(input->v_jet_px_reco->at(iJet));
                jet_4mom_reco.setY(input->v_jet_py_reco->at(iJet));
                jet_4mom_reco.setZ(input->v_jet_pz_reco->at(iJet));
                
                if(jet_4mom_reco.perp() < Common::jet_pTcut_reco || fabs(jet_4mom_reco.eta()) > Common::jet_etaCut_reco)
                {
                    continue;
                }
                
                jet_nISR++;
            }
            
            output->h1_jet_nISR_reco->Fill(jet_nISR);
        }
    }
}

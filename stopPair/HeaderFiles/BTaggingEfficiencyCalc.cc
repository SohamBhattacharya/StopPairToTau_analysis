# include <iostream>
# include <fstream>
# include <string>
# include <vector>

# include <TFile.h>
# include <TH2F.h>

# include "BTaggingEfficiencyCalc.h"


namespace BTaggingEfficiencyCalc
{
    void calculateEfficiency(
        std::string process,
        std::string dir,
        std::string otherInfoDir,
        std::string sourceFileName,
        bool isMC,
        std::string era,
        std::vector <std::string> v_bDiscriminatorName,
        std::vector <std::vector <std::string> > v_bDiscriminatorWPname,
        std::vector <double> v_pT_bin,
        std::vector <double> v_eta_bin
    )
    {
        printf("\n");
        printf("********** Era: %s ********** \n", era.c_str());
        printf("\n");
        
        //char sourceFileName[Common::str_len];
        //sprintf(sourceFileName, "../sourceFiles/%s/%s_custom.txt", process.c_str(), process.c_str());
        
        printf("Source file: %s \n\n", sourceFileName.c_str());
        
        std::string inFileName;
        
        char command[Common::str_len];
        
        char outDir[Common::str_len];
        //sprintf(outDir, "output_tauFakeEstimation_tauTau/%s", dir.c_str());
        //sprintf(outDir, "%s", dir.c_str());
        sprintf(outDir, "%s", dir.c_str());
        
        sprintf(command, "mkdir -p %s", outDir);
        system(command);
        
        char outFileName[Common::str_len];
        sprintf(outFileName, "%s/bTaggingEfficiency.root", outDir);
        printf("Ouput: %s \n\n", outFileName);
        TFile *outFile = TFile::Open(outFileName, "RECREATE");
        
        
        for(int iDisc = 0; iDisc < v_bDiscriminatorName.size(); iDisc++)
        {
            std::string bDiscriminatorName = v_bDiscriminatorName.at(iDisc);
            
            for(int iWP = 0; iWP < v_bDiscriminatorWPname.at(iDisc).size(); iWP++)
            {
                TH2F *h2_bTaggingEff_num_b;
                TH2F *h2_bTaggingEff_num_c;
                TH2F *h2_bTaggingEff_num_udsg;
                
                TH2F *h2_bTaggingEff_den_b;
                TH2F *h2_bTaggingEff_den_c;
                TH2F *h2_bTaggingEff_den_udsg;
                
                TH2F *h2_bTaggingEff_eff_b;
                TH2F *h2_bTaggingEff_eff_c;
                TH2F *h2_bTaggingEff_eff_udsg;
                
                char histName[Common::str_len];
                char histTitle[Common::str_len];
                
                std::string bDiscriminatorWPname = v_bDiscriminatorWPname.at(iDisc).at(iWP);
                
                std::ifstream sourceFileList;
                sourceFileList.open(sourceFileName.c_str());
                
                int nFile = 0;
                int nFileValid = 0;
                
                while(std::getline(sourceFileList, inFileName))
                {
                    nFile++;
                    
                    //if(nFile > 2) continue;
                    
                    printf("\n\n");
                    printf("Input: %s \n", inFileName.c_str());
                    
                    TFile *inFile = 0;
                    
                    try
                    {
                        inFile = TFile::Open(inFileName.c_str(), "READ");
                    }
                    
                    catch(...)
                    {
                        printf("Error opening input file: skipping. \n");
                        fflush(stdout);
                        continue;
                    }
                    
                    //std::cout << inFile << std::endl;
                    //fflush(stdout);
                    
                    if(!inFile || inFile == NULL || inFile->IsZombie())
                    {
                        printf("Error opening input file: skipping. \n");
                        fflush(stdout);
                        continue;
                    }
                    
                    nFileValid++;
                    
                    // Numerator
                    
                    //
                    sprintf(histName, "miniaodsim2custom/bTaggingEff_%s/bTaggingEff_num_b_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    sprintf(histTitle, "#epsilon^{num}_{b} p_{T} vs. #eta [%s, %s]", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    printf("Num: %s \n", histName);
                    
                    if(nFileValid == 1)
                    {
                        h2_bTaggingEff_num_b = (TH2F*) inFile->Get(histName)->Clone();
                        h2_bTaggingEff_num_b->Sumw2();
                        h2_bTaggingEff_num_b->SetDirectory(0);
                    }
                    
                    else
                    {
                        h2_bTaggingEff_num_b->Add((TH2F*) inFile->Get(histName)->Clone());
                    }
                    
                    //
                    sprintf(histName, "miniaodsim2custom/bTaggingEff_%s/bTaggingEff_num_c_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    sprintf(histTitle, "#epsilon^{num}_c} p_{T} vs. #eta [%s, %s]", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    printf("Num: %s \n", histName);
                    
                    if(nFileValid == 1)
                    {
                        h2_bTaggingEff_num_c = (TH2F*) inFile->Get(histName)->Clone();
                        h2_bTaggingEff_num_c->Sumw2();
                        h2_bTaggingEff_num_c->SetDirectory(0);
                    }
                    
                    else
                    {
                        h2_bTaggingEff_num_c->Add((TH2F*) inFile->Get(histName)->Clone());
                    }
                    
                    //
                    sprintf(histName, "miniaodsim2custom/bTaggingEff_%s/bTaggingEff_num_udsg_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    sprintf(histTitle, "#epsilon^{num}_{udsg} p_{T} vs. #eta [%s, %s]", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    printf("Num: %s \n", histName);
                    
                    if(nFileValid == 1)
                    {
                        h2_bTaggingEff_num_udsg = (TH2F*) inFile->Get(histName)->Clone();
                        h2_bTaggingEff_num_udsg->Sumw2();
                        h2_bTaggingEff_num_udsg->SetDirectory(0);
                    }
                    
                    else
                    {
                        h2_bTaggingEff_num_udsg->Add((TH2F*) inFile->Get(histName)->Clone());
                    }
                    
                    
                    // Denominator
                    
                    //
                    sprintf(histName, "miniaodsim2custom/bTaggingEff_%s/bTaggingEff_den_b_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    sprintf(histTitle, "#epsilon^{den}_{b} p_{T} vs. #eta [%s, %s]", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    printf("Den: %s \n", histName);
                    
                    if(nFileValid == 1)
                    {
                        h2_bTaggingEff_den_b = (TH2F*) inFile->Get(histName)->Clone();
                        h2_bTaggingEff_den_b->Sumw2();
                        h2_bTaggingEff_den_b->SetDirectory(0);
                    }
                    
                    else
                    {
                        h2_bTaggingEff_den_b->Add((TH2F*) inFile->Get(histName)->Clone());
                    }
                    
                    //
                    sprintf(histName, "miniaodsim2custom/bTaggingEff_%s/bTaggingEff_den_c_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    sprintf(histTitle, "#epsilon^{den}_c} p_{T} vs. #eta [%s, %s]", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    printf("Den: %s \n", histName);
                    
                    if(nFileValid == 1)
                    {
                        h2_bTaggingEff_den_c = (TH2F*) inFile->Get(histName)->Clone();
                        h2_bTaggingEff_den_c->Sumw2();
                        h2_bTaggingEff_den_c->SetDirectory(0);
                    }
                    
                    else
                    {
                        h2_bTaggingEff_den_c->Add((TH2F*) inFile->Get(histName)->Clone());
                    }
                    
                    //
                    sprintf(histName, "miniaodsim2custom/bTaggingEff_%s/bTaggingEff_den_udsg_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    sprintf(histTitle, "#epsilon^{den}_{udsg} p_{T} vs. #eta [%s, %s]", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                    printf("Den: %s \n", histName);
                    
                    if(nFileValid == 1)
                    {
                        h2_bTaggingEff_den_udsg = (TH2F*) inFile->Get(histName)->Clone();
                        h2_bTaggingEff_den_udsg->Sumw2();
                        h2_bTaggingEff_den_udsg->SetDirectory(0);
                    }
                    
                    else
                    {
                        h2_bTaggingEff_den_udsg->Add((TH2F*) inFile->Get(histName)->Clone());
                    }
                    
                    
                    // Close file
                    inFile->Close();
                    delete inFile;
                    
                    fflush(stdout);
                }
                
                // Rebin
                h2_bTaggingEff_num_b = Common::rebin2Dhistogram(h2_bTaggingEff_num_b, true, v_eta_bin, true, v_pT_bin, false);
                h2_bTaggingEff_num_c = Common::rebin2Dhistogram(h2_bTaggingEff_num_c, true, v_eta_bin, true, v_pT_bin, false);
                h2_bTaggingEff_num_udsg = Common::rebin2Dhistogram(h2_bTaggingEff_num_udsg, true, v_eta_bin, true, v_pT_bin, false);
                
                h2_bTaggingEff_den_b = Common::rebin2Dhistogram(h2_bTaggingEff_den_b, true, v_eta_bin, true, v_pT_bin, false);
                h2_bTaggingEff_den_c = Common::rebin2Dhistogram(h2_bTaggingEff_den_c, true, v_eta_bin, true, v_pT_bin, false);
                h2_bTaggingEff_den_udsg = Common::rebin2Dhistogram(h2_bTaggingEff_den_udsg, true, v_eta_bin, true, v_pT_bin, false);
                
                
                // Efficiency (Numerator / Denominator)
                sprintf(histName, "bTaggingEff_eff_b_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                sprintf(histTitle, "#epsilon_{b} p_{T} vs. #eta [%s, %s]", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                printf("Eff: %s \n", histName);
                h2_bTaggingEff_eff_b = (TH2F*) h2_bTaggingEff_num_b->Clone();
                h2_bTaggingEff_eff_b->Sumw2();
                h2_bTaggingEff_eff_b->SetName(histName);
                h2_bTaggingEff_eff_b->SetTitle(histTitle);
                
                sprintf(histName, "bTaggingEff_eff_c_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                sprintf(histTitle, "epsilon_{c} p_{T} vs. #eta [%s, %s]}", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                printf("Eff: %s \n", histName);
                h2_bTaggingEff_eff_c = (TH2F*) h2_bTaggingEff_num_c->Clone();
                h2_bTaggingEff_eff_c->Sumw2();
                h2_bTaggingEff_eff_c->SetName(histName);
                h2_bTaggingEff_eff_c->SetTitle(histTitle);
                
                sprintf(histName, "bTaggingEff_eff_udsg_%s_%s", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                sprintf(histTitle, "#epsilon_{udsg} p_{T} vs. #eta [%s, %s]}", bDiscriminatorName.c_str(), bDiscriminatorWPname.c_str());
                printf("Eff: %s \n", histName);
                h2_bTaggingEff_eff_udsg = (TH2F*) h2_bTaggingEff_num_udsg->Clone();
                h2_bTaggingEff_eff_udsg->Sumw2();
                h2_bTaggingEff_eff_udsg->SetName(histName);
                h2_bTaggingEff_eff_udsg->SetTitle(histTitle);
                
                fflush(stdout);
                
                
                
                //h2_bTaggingEff_eff_b = Common::rebin2Dhistogram(h2_bTaggingEff_eff_b, true, v_eta_bin, true, v_pT_bin, false);
                //h2_bTaggingEff_eff_c = Common::rebin2Dhistogram(h2_bTaggingEff_eff_c, true, v_eta_bin, true, v_pT_bin, false);
                //h2_bTaggingEff_eff_udsg = Common::rebin2Dhistogram(h2_bTaggingEff_eff_udsg, true, v_eta_bin, true, v_pT_bin, false);
                
                
                // Divide
                h2_bTaggingEff_eff_b->Divide(h2_bTaggingEff_den_b);
                h2_bTaggingEff_eff_c->Divide(h2_bTaggingEff_den_c);
                h2_bTaggingEff_eff_udsg->Divide(h2_bTaggingEff_den_udsg);
                
                // Write
                outFile->cd();
                
                h2_bTaggingEff_num_b->Write();
                h2_bTaggingEff_num_c->Write();
                h2_bTaggingEff_num_udsg->Write();
                
                h2_bTaggingEff_den_b->Write();
                h2_bTaggingEff_den_c->Write();
                h2_bTaggingEff_den_udsg->Write();
                
                h2_bTaggingEff_eff_b->Write();
                h2_bTaggingEff_eff_c->Write();
                h2_bTaggingEff_eff_udsg->Write();
                
                // Delete
                delete h2_bTaggingEff_num_b;
                delete h2_bTaggingEff_num_c;
                delete h2_bTaggingEff_num_udsg;
                
                delete h2_bTaggingEff_den_b;
                delete h2_bTaggingEff_den_c;
                delete h2_bTaggingEff_den_udsg;
                
                delete h2_bTaggingEff_eff_b;
                delete h2_bTaggingEff_eff_c;
                delete h2_bTaggingEff_eff_udsg;
                
                
                //printf("\n\n");
            }
        }
        
        outFile->Close();
        delete outFile;
    }
}

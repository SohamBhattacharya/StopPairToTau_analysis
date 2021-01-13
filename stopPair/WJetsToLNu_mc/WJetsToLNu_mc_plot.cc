# include <iostream>
# include <vector>

# include <TCanvas.h>
# include <TFile.h>
# include <TH1F.h>
# include <THStack.h>
# include <TLegend.h>
# include <TTree.h>

# include "../HeaderFiles/Common.h"
# include "../../../misc/Plot.h"


const char plotDir[] = "plots";


void plot_b(TFile *input_file);
void plot_tau(TFile *input_file);


int main()
{
    TFile *input_file;
    
    system("mkdir -p plots");
    
    char process[] = "WJetsToLNu_mc";
    
    char inDir[Common::str_len];
    sprintf(inDir, "../../../data_analyzed/%s_analyzed", process);
    
    char inFileName[Common::str_len];
    sprintf(inFileName, "%s/WJetsToLNu_HT-100To200_mc_analyzed.root", inDir);
    
    input_file = TFile::Open(inFileName, "READ");
    
    plot_tau(input_file);
    plot_b(input_file);
}


// tau and tau jet
void plot_tau(TFile *input_file)
{
    std::vector <const char*> v_label;
    
    std::vector <const char*> v_name_prefix = {"", "", ""};
    std::vector <const char*> v_name_suffix = {"n", "pT", "eta"};
    
    std::vector <bool> v_normalize = {true, false, false};
    
    std::vector <double> v_xMin = {0, 0, 0};
    std::vector <double> v_xMax = {-1, 500, -1};
    
    std::vector <double> v_yMin = {0, 0, 0};
    std::vector <double> v_yMax = {1, -1, -1};
    
    std::vector <bool> v_setLogX = {false, false, false};
    std::vector <bool> v_setLogY = {false, true, false};
    
    std::vector <const char*> v_title = {"n_{#tau}", "p_{T, #tau}", "#eta_{#tau}"};
    
    std::vector <const char*> v_iso = {"looseIso", "mediumIso", "tightIso"};
    //std::vector <const char*> v_iso_str = {"looseIso", "mediumIso", "tightIso"};
    
    
    for(int iPrefix = 0; iPrefix < v_name_prefix.size(); iPrefix++)
    {
        char \
            hist_name_gen[Common::str_len], \
            
            fileName[Common::str_len];
        
        std::vector <TH1F*> v_hist;
        
        sprintf(hist_name_gen, "gen/%stau_vis_%s_gen", v_name_prefix[iPrefix], v_name_suffix[iPrefix]);
        //std::cout << hist_name_gen << "\n";
        
        v_hist.push_back((TH1F*) input_file->Get(hist_name_gen));
        v_label.push_back("vis GEN");
        
        for(int iIso = 0; iIso < v_iso.size(); iIso++)
        {
            char hist_name_reco[Common::str_len];
            
            char str_temp[Common::str_len];
            
            if(strlen(v_iso[iIso]))
            {
                sprintf(str_temp, "_");
            }
            
            else
            {
                sprintf(str_temp, "");
            }
            
            sprintf(hist_name_reco, "reco/%stau_%s%s%s_reco", v_name_prefix[iPrefix], v_name_suffix[iPrefix], str_temp, v_iso[iIso]);
            //std::cout << hist_name_reco << "\n";
            
            v_hist.push_back((TH1F*) input_file->Get(hist_name_reco));
            v_label.push_back(v_iso[iIso]);
        }
        
        sprintf(fileName, "%s/%stau_%s.pdf", plotDir, v_name_prefix[iPrefix], v_name_suffix[iPrefix]);
        
        Plot::plot( \
            &v_hist, \
            v_label, \
            v_normalize[iPrefix], \
            v_xMin[iPrefix], v_xMax[iPrefix], \
            v_yMin[iPrefix], v_yMax[iPrefix], \
            v_setLogX[iPrefix], \
            v_setLogY[iPrefix], \
            v_title[iPrefix], \
            fileName);
        
        
        // Efficiency
        if(iPrefix == 1)
        {
            for(int iHist = 1; iHist < v_hist.size(); iHist++)
            {
                v_hist[iHist]->Divide(v_hist[0]);
            }
            
            v_hist.erase(v_hist.begin() + 0);
            v_label.erase(v_label.begin() + 0);
            
            sprintf(fileName, "%s/%stau_efficiency_%s.pdf", plotDir, v_name_prefix[iPrefix], v_name_suffix[iPrefix]);
            
            Plot::plot( \
                &v_hist, \
                v_label, \
                false, \
                0, 200, \
                0, 1, \
                false, \
                false, \
                "RECO p_{T, #tau} / GEN p_{T, #tau}", \
                fileName);
        }
    }
}


// b and b jet
void plot_b(TFile *input_file)
{
    std::vector <const char*> v_label;
    
    std::vector <const char*> v_name_prefix = {"", "", ""};
    std::vector <const char*> v_name_suffix = {"n", "pT", "eta"};
    
    std::vector <bool> v_normalize = {true, false, false};
    
    std::vector <double> v_xMin = {0, 0, 0};
    std::vector <double> v_xMax = {-1, 500, -1};
    
    std::vector <double> v_yMin = {0, 0, 0};
    std::vector <double> v_yMax = {1, -1, -1};
    
    std::vector <bool> v_setLogX = {false, false, false};
    std::vector <bool> v_setLogY = {false, true, false};
    
    std::vector <const char*> v_title = {"n_{b}", "p_{T, b}", "eta_{b}"};
    
    std::vector <const char*> v_bDisc = {"loose", "medium", "tight"};
    
    
    for(int iPrefix = 0; iPrefix < v_name_prefix.size(); iPrefix++)
    {
        char \
            hist_name_gen[Common::str_len], \
            
            fileName[Common::str_len];
        
        std::vector <TH1F*> v_hist;
        
        sprintf(hist_name_gen, "gen/%sb_%s_gen", v_name_prefix[iPrefix], v_name_suffix[iPrefix]);
        //std::cout << hist_name_gen << "\n";
        
        v_hist.push_back((TH1F*) input_file->Get(hist_name_gen));
        v_label.push_back("GEN");
        
        for(int ibDisc = 0; ibDisc < v_bDisc.size(); ibDisc++)
        {
            char hist_name_reco[Common::str_len];
            
            char str_temp[Common::str_len];
            
            if(strlen(v_bDisc[ibDisc]))
            {
                sprintf(str_temp, "_");
            }
            
            else
            {
                sprintf(str_temp, "");
            }
            
            sprintf(hist_name_reco, "reco/%sb_%s%s%s_reco", v_name_prefix[iPrefix], v_name_suffix[iPrefix], str_temp, v_bDisc[ibDisc]);
            //std::cout << hist_name_reco << "\n";
            
            v_hist.push_back((TH1F*) input_file->Get(hist_name_reco));
            v_label.push_back(v_bDisc[ibDisc]);
        }
        
        sprintf(fileName, "%s/%sb_%s.pdf", plotDir, v_name_prefix[iPrefix], v_name_suffix[iPrefix]);
        
        Plot::plot( \
            &v_hist, \
            v_label, \
            v_normalize[iPrefix], \
            v_xMin[iPrefix], v_xMax[iPrefix], \
            v_yMin[iPrefix], v_yMax[iPrefix], \
            v_setLogX[iPrefix], \
            v_setLogY[iPrefix], \
            v_title[iPrefix], \
            fileName);
        
        
        // Efficiency
        if(iPrefix == 1)
        {
            for(int iHist = 1; iHist < v_hist.size(); iHist++)
            {
                v_hist[iHist]->Divide(v_hist[0]);
            }
            
            v_hist.erase(v_hist.begin() + 0);
            v_label.erase(v_label.begin() + 0);
            
            sprintf(fileName, "%s/%sb_efficiency_%s.pdf", plotDir, v_name_prefix[iPrefix], v_name_suffix[iPrefix]);
            
            Plot::plot( \
                &v_hist, \
                v_label, \
                false, \
                0, 300, \
                0, 1, \
                false, \
                false, \
                "RECO p_{T, b} / GEN p_{T, b}", \
                fileName);
        }
    }
}

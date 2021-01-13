# include <iostream>
# include <fstream>
# include <string>
# include <utility>
# include <vector>

# include <CLHEP/Vector/LorentzVector.h>

# include <TCanvas.h>
# include <TFile.h>
# include <TH2.h>
# include <TGraph.h>
# include <TGraph2D.h>
# include <TLegend.h>
# include <TList.h>
# include <TPaveLabel.h>
# include <TStyle.h>
# include <TTree.h>

# include "HeaderFiles/Common.h"


struct LimitInfo
{
    std::vector <double> v_stop1_m;
    std::vector <double> v_neutralino1_m;
    std::vector <double> v_xs;
    
    std::vector <double> v_observedLimit;
    std::vector <double> v_expectedLimit;
    std::vector <double> v_expectedLimit_1sigLwr;
    std::vector <double> v_expectedLimit_1sigUpr;
    std::vector <double> v_expectedLimit_2sigLwr;
    std::vector <double> v_expectedLimit_2sigUpr;
    
    int lineColor;
    int lineStyle;
    
    std::string label;
};


void plot(std::vector <LimitInfo> *v_limitInfo, std::string era, const char *outDir);


int main()
{
    //std::string era = "2016";
    std::string era = "2017";
    //std::string era = "combined";
    
    char outDir[500];
    sprintf(outDir, "plots/limits/%s", era.c_str());
    
    char command[500];
    
    sprintf(command, "mkdir -p %s", outDir);
    system(command);
    
    std::vector <std::string> v_limitFileName = {
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/limitInfo_SRA.txt",
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/limitInfo_SRB.txt",
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/limitInfo_SRC.txt",
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/limitInfo_SRD.txt",
        
        
        
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
        
        "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
        "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
        "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
        
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_combined_tauTau_analysis/limitInfo_SRB.txt",
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_combined_tauTau_analysis/limitInfo_SRB.txt",
        //"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_combined_tauTau_analysis/limitInfo_SRB.txt",
        
    };
    
    std::vector <std::string> v_label = {
        //"x=0.25, SRA: #slash{E}_{T}-m_{T2}",
        //"x=0.25, SRB: #slash{E}_{T}-m^{#tau#tau}_{T2}-H^{#tau#tau jet}_{T}",
        //"x=0.25, SRC: #slash{E}_{T}-m^{#taub#taub}_{T2}-H^{#tau#tau jet}_{T}",
        //"x=0.25, SRD: #slash{E}_{T}-m^{#tau#tau}_{T2}-m^{#taub#taub}_{T2}",
        
        "x=0.25",
        "x=0.5",
        "x=0.75",
        
        //"x=0.75, SRA: #slash{E}_{T}-m_{T2}",
        //"x=0.75, SRB: #slash{E}_{T}-m_{T2}-H^{#tau#tau jet}_{T}"
    };
    
    std::vector <int> v_lineColor = {
        2,
        4,
        6,
        //8,
    };
    
    std::vector <int> v_lineStyle = {
        1,
        1,
        1,
        //1,
    };
    
    std::vector <LimitInfo> v_limitInfo;
    
    
    for(int iFile = 0; iFile < v_limitFileName.size(); iFile++)
    {
        printf("File: %s \n", v_limitFileName.at(iFile).c_str());
        
        std::vector <std::vector <double> > vv_info;
        
        Common::parseCSVto2Dvector(
            v_limitFileName.at(iFile),
            &vv_info
        );
        
        std::vector <double> v_stop1_m;
        std::vector <double> v_neutralino1_m;
        std::vector <double> v_xs;
        std::vector <double> v_expectedLimit;
        std::vector <double> v_expectedLimit_1sigLwr;
        std::vector <double> v_expectedLimit_1sigUpr;
        std::vector <double> v_expectedLimit_2sigLwr;
        std::vector <double> v_expectedLimit_2sigUpr;
        
        LimitInfo struct_limitInfo;
        
        int nMass = vv_info.size();
        
        for(int iMass = 0; iMass < nMass; iMass++)
        {
            std::vector <double> v_info_iMass = vv_info.at(iMass);
            
            v_stop1_m.push_back(v_info_iMass.at(0));
            v_neutralino1_m.push_back(v_info_iMass.at(1));
            v_xs.push_back(v_info_iMass.at(3));
            
            //if(v_info_iMass.at(v_info_iMass.size()-1) < 1)
            {
                //v_expectedLimit.push_back(v_info_iMass.at(v_info_iMass.size()-1));
                
                v_expectedLimit.push_back(v_info_iMass.at(7));
                v_expectedLimit_1sigLwr.push_back(v_info_iMass.at(8));
                v_expectedLimit_1sigUpr.push_back(v_info_iMass.at(9));
                v_expectedLimit_2sigLwr.push_back(v_info_iMass.at(10));
                v_expectedLimit_2sigUpr.push_back(v_info_iMass.at(11));
            }
            
            //else
            //{
            //    v_expectedLimit.push_back(2.0);
            //}
        }
        
        struct_limitInfo.v_stop1_m = v_stop1_m;
        struct_limitInfo.v_neutralino1_m = v_neutralino1_m;
        struct_limitInfo.v_xs = v_xs;
        struct_limitInfo.v_expectedLimit = v_expectedLimit;
        struct_limitInfo.v_expectedLimit_1sigLwr = v_expectedLimit_1sigLwr;
        struct_limitInfo.v_expectedLimit_1sigUpr = v_expectedLimit_1sigUpr;
        struct_limitInfo.v_expectedLimit_2sigLwr = v_expectedLimit_2sigLwr;
        struct_limitInfo.v_expectedLimit_2sigUpr = v_expectedLimit_2sigUpr;
        struct_limitInfo.lineColor = v_lineColor.at(iFile);
        struct_limitInfo.lineStyle = v_lineStyle.at(iFile);
        struct_limitInfo.label = v_label.at(iFile);
        
        v_limitInfo.push_back(struct_limitInfo);
        
        printf("filled: %d \n", (int) v_stop1_m.size());
    }
    
    printf("Plotting... \n");
    plot(&v_limitInfo, era, outDir);
    
    return 0;
}


void plot(std::vector <LimitInfo> *v_limitInfo, std::string era, const char *outDir)
{
    gStyle->SetOptStat(0);
    
    TCanvas *canvas = new TCanvas("canvas", "canvas", 400, 400);
    
    //gStyle->SetOptTitle(0);
    //TPaveLabel *title = new TPaveLabel(0.11, 0.95, 0.35, 0.99, "Exclusion", "brndc");
    //title->Draw(); 
    
    //TLegend *legend = new TLegend(0.63, 0.63, 0.895, 0.895);
    TLegend *legend = new TLegend(0.105, 0.63, 0.45, 0.895);
    legend->SetFillStyle(0);
    //legend->SetTextSize(0.02);
    legend->SetTextSize(0.8 * legend->GetTextSize());
    
    //TH2F *h2_blank = new TH2F("Exclusion", "Exclusion", 10, 200, 1500, 10, 0, 650);
    //
    //h2_blank->GetXaxis()->SetTitle("m_{#tilde{t}_{1}} [GeV]");
    //h2_blank->GetYaxis()->SetTitle("m_{#tilde{#chi}^{0}_{1}} [GeV]");
    //h2_blank->GetZaxis()->SetTitle("95% CL upper limit on cross-section [pb]");
    //h2_blank->GetXaxis()->SetTitleOffset(1.3);
    //h2_blank->GetYaxis()->SetTitleOffset(1.3);
    //h2_blank->GetZaxis()->SetTitleOffset(0);
    //h2_blank->Draw();
    
    for(int iLimit = 0; iLimit < v_limitInfo->size(); iLimit++)
    {
        LimitInfo struct_limitInfo = v_limitInfo->at(iLimit);
        
        std::vector <double> v_stop1_m = struct_limitInfo.v_stop1_m;
        std::vector <double> v_neutralino1_m = struct_limitInfo.v_neutralino1_m;
        std::vector <double> v_xs = struct_limitInfo.v_xs;
        std::vector <double> v_expectedLimit = struct_limitInfo.v_expectedLimit;
        std::vector <double> v_expectedLimit_1sigLwr = struct_limitInfo.v_expectedLimit_1sigLwr;
        std::vector <double> v_expectedLimit_1sigUpr = struct_limitInfo.v_expectedLimit_1sigUpr;
        std::vector <double> v_expectedLimit_2sigLwr = struct_limitInfo.v_expectedLimit_2sigLwr;
        std::vector <double> v_expectedLimit_2sigUpr = struct_limitInfo.v_expectedLimit_2sigUpr;
        
        std::string label = struct_limitInfo.label;
        
        printf("%d \n", (int) v_stop1_m.size());
        
        TGraph2D *graph_expectedLimit = new TGraph2D(label.c_str(), label.c_str(), v_stop1_m.size(), &v_stop1_m.at(0), &v_neutralino1_m.at(0), &v_expectedLimit.at(0));
        TGraph2D *graph_expectedLimit_1sigLwr = new TGraph2D(label.c_str(), label.c_str(), v_stop1_m.size(), &v_stop1_m.at(0), &v_neutralino1_m.at(0), &v_expectedLimit_1sigLwr.at(0));
        TGraph2D *graph_expectedLimit_1sigUpr = new TGraph2D(label.c_str(), label.c_str(), v_stop1_m.size(), &v_stop1_m.at(0), &v_neutralino1_m.at(0), &v_expectedLimit_1sigUpr.at(0));
        TGraph2D *graph_expectedLimit_2sigLwr = new TGraph2D(label.c_str(), label.c_str(), v_stop1_m.size(), &v_stop1_m.at(0), &v_neutralino1_m.at(0), &v_expectedLimit_2sigLwr.at(0));
        TGraph2D *graph_expectedLimit_2sigUpr = new TGraph2D(label.c_str(), label.c_str(), v_stop1_m.size(), &v_stop1_m.at(0), &v_neutralino1_m.at(0), &v_expectedLimit_2sigUpr.at(0));
        
        graph_expectedLimit->SetNpx(500);
        graph_expectedLimit->SetNpy(500);
        
        graph_expectedLimit_1sigLwr->SetNpx(500);
        graph_expectedLimit_1sigLwr->SetNpy(500);
        
        graph_expectedLimit_1sigUpr->SetNpx(500);
        graph_expectedLimit_1sigUpr->SetNpy(500);
        
        graph_expectedLimit_2sigLwr->SetNpx(500);
        graph_expectedLimit_2sigLwr->SetNpy(500);
        
        graph_expectedLimit_2sigUpr->SetNpx(500);
        graph_expectedLimit_2sigUpr->SetNpy(500);
        
        
        if(iLimit == 0)
        {
            std::vector <double> v_xsLimit;
            
            for(int iMass  = 0; iMass < v_stop1_m.size(); iMass++)
            {
                double xsLimit = v_xs.at(iMass) * v_expectedLimit.at(iMass);// * 0.67*0.67;
                
                printf("%d, \t %d: \t %0.4e, %0.4e \n", (int) v_stop1_m.at(iMass), (int) v_neutralino1_m.at(iMass), v_xs.at(iMass), v_expectedLimit.at(iMass));
                
                v_xsLimit.push_back(xsLimit);
            }
            
            TGraph2D *graph_xs = new TGraph2D("xs", "xs", v_stop1_m.size(), &v_stop1_m.at(0), &v_neutralino1_m.at(0), &v_xsLimit.at(0));
            
            graph_xs->SetNpx(500);
            graph_xs->SetNpy(500);
            
            char temp[500];
            sprintf(temp, "Exclusion (%s)", era.c_str());
            
            graph_xs->GetHistogram()->SetTitle(temp);
            graph_xs->GetHistogram()->GetXaxis()->SetTitle("m_{#tilde{t}_{1}} [GeV]");
            graph_xs->GetHistogram()->GetYaxis()->SetTitle("m_{#tilde{#chi}^{0}_{1}} [GeV]");
            graph_xs->GetHistogram()->GetZaxis()->SetTitle("95% CL upper limit on cross-section [pb]");
            
            graph_xs->GetHistogram()->GetXaxis()->SetTitleOffset(1.3);
            graph_xs->GetHistogram()->GetYaxis()->SetTitleOffset(1.3);
            graph_xs->GetHistogram()->GetZaxis()->SetTitleOffset(1.4);
            
            //graph_xs->Draw("colz same");
            graph_xs->GetHistogram()->Draw("colz");
            
            //graph_xs->GetZaxis()->SetRangeUser(1e-5, 1e2);
            graph_xs->SetMinimum(1e-4);
            graph_xs->SetMaximum(1e2);
        }
        
        //
        TList *contourList_expectedLimit = (TList*) graph_expectedLimit->GetContourList(1.0);
        printf("%d \n", contourList_expectedLimit->GetSize());
        
        TGraph *contour_expectedLimit = (TGraph*) contourList_expectedLimit->First();
        
        contour_expectedLimit->SetLineWidth(3);
        contour_expectedLimit->SetLineColor(struct_limitInfo.lineColor);
        contour_expectedLimit->SetLineStyle(struct_limitInfo.lineStyle);
        contour_expectedLimit->SetFillColor(0);
        legend->AddEntry(contour_expectedLimit, label.c_str());
        contour_expectedLimit->Draw("C");
        
        
        //
        TList *contourList_expectedLimit_1sigLwr = (TList*) graph_expectedLimit_1sigLwr->GetContourList(1.0);
        printf("%d \n", contourList_expectedLimit_1sigLwr->GetSize());
        
        TGraph *contour_expectedLimit_1sigLwr = (TGraph*) contourList_expectedLimit_1sigLwr->First();
        
        contour_expectedLimit_1sigLwr->SetLineWidth(3);
        contour_expectedLimit_1sigLwr->SetLineColor(struct_limitInfo.lineColor);
        contour_expectedLimit_1sigLwr->SetLineStyle(2);
        contour_expectedLimit_1sigLwr->SetFillColor(0);
        //legend->AddEntry(contour_expectedLimit_1sigLwr, label.c_str());
        contour_expectedLimit_1sigLwr->Draw("C");
        
        
        //
        TList *contourList_expectedLimit_1sigUpr = (TList*) graph_expectedLimit_1sigUpr->GetContourList(1.0);
        printf("%d \n", contourList_expectedLimit_1sigUpr->GetSize());
        
        TGraph *contour_expectedLimit_1sigUpr = (TGraph*) contourList_expectedLimit_1sigUpr->First();
        
        contour_expectedLimit_1sigUpr->SetLineWidth(3);
        contour_expectedLimit_1sigUpr->SetLineColor(struct_limitInfo.lineColor);
        contour_expectedLimit_1sigUpr->SetLineStyle(2);
        contour_expectedLimit_1sigUpr->SetFillColor(0);
        //legend->AddEntry(contour_expectedLimit_1sigUpr, label.c_str());
        contour_expectedLimit_1sigUpr->Draw("C");
        
        
        
        
        //graph_expectedLimit->GetHistogram()->GetZaxis()->SetRangeUser(0, 1);
        //graph_expectedLimit->SetMaximum(1.0);
        //graph_expectedLimit->SetMinimum(0.0);
        
        //graph_expectedLimit->SetMarkerSize(0);
        //graph_expectedLimit->Draw("colz");
    }
    
    legend->Draw();
    
    canvas->RedrawAxis();
    canvas->SetLogz(true);
    canvas->SetRightMargin(1.5*canvas->GetRightMargin());
    
    char outFileName[500];
    sprintf(outFileName, "%s/exclusion2D.pdf", outDir, era.c_str());
    
    canvas->SaveAs(outFileName);
}

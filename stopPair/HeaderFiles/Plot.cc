# include <iostream>
# include <vector>

# include <TCanvas.h>
# include <TFile.h>
# include <TH1F.h>
# include <TH2F.h>
# include <THStack.h>
# include <TLegend.h>
# include <TLine.h>
# include <TStyle.h>
# include <TPad.h>

# include "Plot.h"
# include "Common.h"


// ****************************************
// ***** Note: Use the "hist" option for drawing histograms when Sumw2() is enabled.
// ***** Otherwise, it is always drawn with option the "E" no matter what other option the user gives
// ****************************************

namespace Plot
{
    void plot(std::vector <TH1F*> *v_hist_mc, std::vector <std::string> *v_label_mc, \
        std::string hist_mc_drawOption, \
        std::vector <TH1F*> *v_hist_sig, std::vector <std::string> *v_label_sig, \
        TH1F *hist_data, const char* label_data, \
        bool nostack, \
        bool normalize, \
        double xMin, bool set_xMin, double xMax, bool set_xMax, \
        double yMin, bool set_yMin, double yMax, bool set_yMax, \
        bool setLogX, bool setLogY, \
        const char *label_xAxis, const char *label_yAxis, \
        const char *title, \
        const char *fileName)
    {
        /*double sum = 0;
        for(int iHist = 0; iHist < v_hist_mc.size(); iHist++)
        {
            sum += v_hist_mc[iHist]->Integral();
        }
        for(int iHist = 0; iHist < v_hist_mc.size(); iHist++)
        {
            v_hist_mc[iHist]->Scale(hist_data->Integral() / sum);
        }*/
        TCanvas *canvas = new TCanvas("canvas", "canvas");
        canvas->SetCanvasSize(800, 800);
        
        if(hist_data)
        {
            canvas->Divide(1, 2);
            
            (canvas->cd(1))->SetPad(-0.0175, 0.25, 1.08, 1);
            (canvas->cd(2))->SetPad(-0.0175, 0.05, 1.08, 0.315);
        }
        
        TLegend *legend = new TLegend(0.65, 0.63, 0.895, 0.895);
        THStack *stack = new THStack();
        
        int nHist = v_hist_mc->size();
        
        
        // Draw MC histograms
        canvas->cd(1);
        
        for(int iHist = 0; iHist < nHist; iHist++)
        {
            int color = Common::v_colorIndex_bg.at(iHist);//iHist+2;
            
            double lineAlpha = 1;
            double fillAlpha = 0;
            double lineWidth = 3;
            
            if(!nostack)
            {
                lineAlpha = 1;
                fillAlpha = 0.75;
                lineWidth = 0;
            }
            
            v_hist_mc->at(iHist)->SetLineWidth(lineWidth);
            v_hist_mc->at(iHist)->SetLineColorAlpha(color, lineAlpha);
            v_hist_mc->at(iHist)->SetFillColorAlpha(color, fillAlpha);
            
            if(normalize)
            {
                v_hist_mc->at(iHist)->Scale(1.0 / v_hist_mc->at(iHist)->Integral());
            }
            
            legend->AddEntry(v_hist_mc->at(iHist), v_label_mc->at(iHist).c_str());
            stack->Add(v_hist_mc->at(iHist), ("hist " + hist_mc_drawOption).c_str());
        }
        
        stack->SetTitle(title);
        //gStyle->SetTitleH(1.01);
        
        if(nostack)
        {
            stack->Draw("nostack");
        }
        
        else
        {
            stack->Draw();
        }
        
        if(xMin < xMax)
        {
            stack->GetXaxis()->SetRangeUser(xMin, xMax);
        }
        
        if(set_xMin)
        {
            //stack->GetXaxis()->SetMinimum(xMin);
        }
        
        if(set_xMax)
        {
            //stack->GetXaxis()->SetMaximum(xMax);
        }
        
        if(set_yMin)
        {
            stack->SetMinimum(yMin);
        }
        
        if(set_yMax)
        {
            stack->SetMaximum(yMax);
        }
        
        if(label_xAxis)
        {
            stack->GetXaxis()->SetTitle(label_xAxis);
        }
        
        if(label_yAxis)
        {
            stack->GetYaxis()->SetTitle(label_yAxis);
        }
        
        
        // Draw signal histogram
        for(int iHist = 0; v_hist_sig && iHist < v_hist_sig->size(); iHist++)
        {
            TH1F *hist_sig = v_hist_sig->at(iHist);
            
            int lineColor = Common::v_colorIndex_sig.at(iHist); //6+iHist;
            
            /*if(lineColor >= 10)
            {
                lineColor++;
            }*/
            
            hist_sig->SetStats(0);
            
            hist_sig->SetLineWidth(3);
            hist_sig->SetLineColor(lineColor);
            hist_sig->SetLineStyle(2);
            
            if(normalize)
            {
                hist_sig->Scale(1.0 / hist_sig->Integral());
            }
            
            legend->AddEntry(hist_sig, v_label_sig->at(iHist).c_str());
            
            hist_sig->Draw("same hist");
        }
        
        
        // Draw DATA histogram
        if(hist_data)
        {
            stack->GetXaxis()->SetLabelSize(0);
            
            hist_data->SetMarkerStyle(20);
            hist_data->SetMarkerColor(1);
            
            hist_data->SetLineWidth(3);
            hist_data->SetLineColor(1);
            
            if(normalize)
            {
                hist_data->Scale(1.0 / hist_data->Integral());
            }
            
            legend->AddEntry(hist_data, label_data);
            
            hist_data->Draw("same");
        }
        
        
        if(setLogX)
        {
            (canvas->cd(1))->SetLogx();
        }
        
        if(setLogY)
        {
            (canvas->cd(1))->SetLogy();
        }
        
        //canvas->cd(1)->SetGridx();
        //canvas->cd(1)->SetGridy();
        
        legend->SetFillStyle(0);
        legend->Draw();
        
        
        // Ratio ((Data / MC) plot
        if(hist_data)
        {
            canvas->cd(2);
            
            TH1F *histSum = Common::sumHistogram(v_hist_mc);
            TH1F *histRatio = (TH1F*) hist_data->Clone();
            printf("all MC: %f, Data: %f \n", histSum->Integral(), hist_data->Integral());
            
            histRatio->Divide(histSum);
            
            histRatio->SetMarkerStyle(20);
            histRatio->SetMarkerColor(1);
            histRatio->SetLineWidth(3);
            histRatio->SetLineColor(1);
            
            histRatio->Draw("E");//("P");
            
            if(xMin < xMax)
            {
                histRatio->GetXaxis()->SetRangeUser(xMin, xMax);
            }
            
            histRatio->SetMinimum(0);
            histRatio->SetMaximum(2);
            
            //histRatio->GetXaxis()->SetLabelSize(0);
            histRatio->GetXaxis()->SetLabelSize(0.09);
            histRatio->GetXaxis()->SetTickLength(0.09);
            
            histRatio->GetYaxis()->SetNdivisions(5);
            histRatio->GetYaxis()->SetLabelSize(0.09);
            
            histRatio->SetTitle("");
            histRatio->GetYaxis()->SetTitle("Data / MC");
            histRatio->GetYaxis()->SetTitleSize(0.1);
            histRatio->GetYaxis()->SetTitleOffset(0.3);
            histRatio->GetYaxis()->CenterTitle();
            
            histRatio->SetStats(0);
            
            //(canvas->cd(2))->SetGridx();
            (canvas->cd(2))->SetGridy();
        }
        
        // Save plot
        canvas->SaveAs(fileName);
        canvas->Close();
        
        std::cout << "\n";
    }
    
    
    void plot(TH2F *h2, \
        std::string h2_drawOption, \
        bool normalize, \
        double xMin, bool set_xMin, double xMax, bool set_xMax, \
        double yMin, bool set_yMin, double yMax, bool set_yMax, \
        double zMin, bool set_zMin, double zMax, bool set_zMax, \
        bool setLogX, bool setLogY, bool setLogZ, \
        const char *label_xAxis, const char *label_yAxis, \
        std::vector <TLine*> v_line, \
        const char *title, \
        const char *fileName)
    {
        TCanvas *canvas = new TCanvas("canvas", "canvas");
        canvas->SetCanvasSize(800, 800);
        
        if(normalize)
        {
            h2->Scale(1.0 / h2->Integral());
        }
        
        if(title)
        {
            h2->SetTitle(title);
        }
        
        h2->SetStats(0);
        h2->SetMarkerSize(0.65);
        
        h2->Draw(h2_drawOption.c_str());
        
        gStyle->SetPaintTextFormat("2.2f");
        
        for(int iLine = 0; iLine < v_line.size(); iLine++)
        {
            v_line.at(iLine)->Draw("same");
        }
        
        if(xMin < xMax)
        {
            h2->GetXaxis()->SetRangeUser(xMin, xMax);
        }
        
        if(yMin < yMax)
        {
            h2->GetYaxis()->SetRangeUser(yMin, yMax);
        }
        
        if(set_zMin)
        {
            h2->SetMinimum(zMin);
        }
        
        if(set_zMax)
        {
            h2->SetMaximum(zMax);
        }
        
        if(label_xAxis)
        {
            h2->GetXaxis()->SetTitle(label_xAxis);
        }
        
        if(label_yAxis)
        {
            h2->GetYaxis()->SetTitle(label_yAxis);
        }
        
        if(setLogX)
        {
            canvas->SetLogx();
        }
        
        if(setLogY)
        {
            canvas->SetLogy();
        }
        
        if(setLogZ)
        {
            canvas->SetLogz();
        }
        
        canvas->SetRightMargin(0.135);
        
        
        canvas->SaveAs(fileName);
        canvas->Close();
        
        std::cout << "\n";
    }
}

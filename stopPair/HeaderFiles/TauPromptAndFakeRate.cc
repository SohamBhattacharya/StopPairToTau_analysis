# include "TauPromptAndFakeRate.h"


namespace TauPromptAndFakeRate
{
    TauPromptAndFakeRate::TauPromptAndFakeRate(
        std::vector <std::string> v_inputFileName_prompt,
        std::string histName_num_prompt,
        std::string histName_den_prompt,
        
        std::vector <std::string> v_inputFileName_fake,
        std::string histName_num_fake_1,
        std::string histName_den_fake_1,
        std::string histName_num_fake_2,
        std::string histName_den_fake_2,
        
        std::vector <double> v_pTbin
    )
    {
        // Prompt
        this->v_inputFileName_prompt = v_inputFileName_prompt;
        this->histName_num_prompt = histName_num_prompt;
        this->histName_den_prompt = histName_den_prompt;
        
        h2_efficiency_num_prompt = Common::getHistogram(v_inputFileName_prompt, histName_num_prompt, new TH2F());
        h2_efficiency_num_prompt->Sumw2();
        
        h2_efficiency_num_prompt = Common::rebin2Dhistogram(
            h2_efficiency_num_prompt,
            false,
            {}, 
            true,
            v_pTbin,
            true
        );
        
        //
        h2_efficiency_den_prompt = Common::getHistogram(v_inputFileName_prompt, histName_den_prompt, new TH2F());
        h2_efficiency_den_prompt->Sumw2();
        
        h2_efficiency_den_prompt = Common::rebin2Dhistogram(
            h2_efficiency_den_prompt,
            false,
            {}, 
            true,
            v_pTbin,
            true
        );
        
        // Divide
        h2_efficiency_prompt = (TH2F*) h2_efficiency_num_prompt->Clone();
        h2_efficiency_prompt->Sumw2();
        h2_efficiency_prompt->Divide(h2_efficiency_den_prompt);
        
        
        // Fake
        this->v_inputFileName_fake = v_inputFileName_fake;
        this->histName_num_fake_1 = histName_num_fake_1;
        this->histName_den_fake_1 = histName_den_fake_1;
        this->histName_num_fake_2 = histName_num_fake_2;
        this->histName_den_fake_2 = histName_den_fake_2;
        
        // 1
        h2_efficiency_num_fake_1 = Common::getHistogram(v_inputFileName_fake, histName_num_fake_1, new TH2F());
        h2_efficiency_num_fake_1->Sumw2();
        
        h2_efficiency_num_fake_1 = Common::rebin2Dhistogram(
            h2_efficiency_num_fake_1,
            false,
            {}, 
            true,
            v_pTbin,
            true
        );
        
        //
        h2_efficiency_den_fake_1 = Common::getHistogram(v_inputFileName_fake, histName_den_fake_1, new TH2F());
        h2_efficiency_den_fake_1->Sumw2();
        
        h2_efficiency_den_fake_1 = Common::rebin2Dhistogram(
            h2_efficiency_den_fake_1,
            false,
            {}, 
            true,
            v_pTbin,
            true
        );
        
        
        // 2
        h2_efficiency_num_fake_2 = Common::getHistogram(v_inputFileName_fake, histName_num_fake_2, new TH2F());
        h2_efficiency_num_fake_2->Sumw2();
        
        h2_efficiency_num_fake_2 = Common::rebin2Dhistogram(
            h2_efficiency_num_fake_2,
            false,
            {}, 
            true,
            v_pTbin,
            true
        );
        
        //
        h2_efficiency_den_fake_2 = Common::getHistogram(v_inputFileName_fake, histName_den_fake_2, new TH2F());
        h2_efficiency_den_fake_2->Sumw2();
        
        h2_efficiency_den_fake_2 = Common::rebin2Dhistogram(
            h2_efficiency_den_fake_2,
            false,
            {}, 
            true,
            v_pTbin,
            true
        );
        
        // Divide
        h2_efficiency_fake_1 = (TH2F*) h2_efficiency_num_fake_1->Clone();
        h2_efficiency_fake_1->Sumw2();
        h2_efficiency_fake_1->Divide(h2_efficiency_den_fake_1);
        
        h2_efficiency_fake_2 = (TH2F*) h2_efficiency_num_fake_2->Clone();
        h2_efficiency_fake_2->Sumw2();
        h2_efficiency_fake_2->Divide(h2_efficiency_den_fake_2);
    }
    
    
    std::pair <double, double> TauPromptAndFakeRate::getPromptRate(double pT, double DM, Common::SYST_TYPE syst)
    {
        int binX = h2_efficiency_prompt->GetXaxis()->FindBin(DM);
        int binY = h2_efficiency_prompt->GetYaxis()->FindBin(pT);
        
        // Use the last pT bin instead of the overflow bin
        if(binY == h2_efficiency_prompt->GetNbinsY()+1)
        {
            binY = h2_efficiency_prompt->GetNbinsY();
        }
        
        double promptRate = h2_efficiency_prompt->GetBinContent(binX, binY);
        double error = h2_efficiency_prompt->GetBinError(binX, binY);
        double errorPercent = 0;//error / promptRate * 100;
        
        //printf("pT: %f, DM: %f \n", pT, DM);
        //printf("BinX: %d, BinY: %d \n", binX, binY);
        //printf("Prompt-rate: %f \n", promptRate);
        //printf("%% error: %f \n", errorPercent);
        
        return std::make_pair(promptRate, errorPercent);
    }
    
    
    std::pair <double, double> TauPromptAndFakeRate::getFakeRate(
        double pT,
        double DM,
        std::string syst_name,
        Common::SYST_TYPE syst_type
    )
    {
        int binX = h2_efficiency_fake_1->GetXaxis()->FindBin(DM);
        int binY = h2_efficiency_fake_1->GetYaxis()->FindBin(pT);
        
        // Use the last pT bin instead of the overflow bin
        if(binY == h2_efficiency_fake_1->GetNbinsY()+1)
        {
            binY = h2_efficiency_fake_1->GetNbinsY();
        }
        
        double fakeRate_1 = h2_efficiency_fake_1->GetBinContent(binX, binY);
        double fakeRate_2 = h2_efficiency_fake_2->GetBinContent(binX, binY);
        
        double fakeRate = (fakeRate_1+fakeRate_2) / 2.0;
        double error = 0;
        double errorPercent = 0;
        
        if(!syst_name.compare("tauFakeRateRegion"))
        {
            syst_type = Common::chooseSystType(syst_name, "tauFakeRateRegion", syst_type);
            
            error = fabs(fakeRate-fakeRate_1);
        }
        
        else if(!syst_name.compare("tauFakeRateJetPartonFlav"))
        {
            syst_type = Common::chooseSystType(syst_name, "tauFakeRateJetPartonFlav", syst_type);
            
            // Taken from the stau AN
            // ~30%; so +-15%
            error = 0.15*fabs(fakeRate);
            //error = 0.3*fabs(fakeRate);
        }
        
        //printf(
        //    "DM %d, "
        //    "pT %0.2f, "
        //    "fakeRate %0.4f, "
        //    "fakeRate err (%s, %d) %0.4f "
        //    "\n",
        //    
        //    (int) DM,
        //    pT,
        //    fakeRate,
        //    syst_name.c_str(),
        //    (int) syst_type,
        //    error
        //);
        
        fakeRate += syst_type*error;
        errorPercent = (fabs(fakeRate) > 0)? error / fakeRate * 100: 0;
        
        //printf("pT: %f, DM: %f \n", pT, DM);
        //printf("BinX: %d, BinY: %d \n", binX, binY);
        ////printf("num 1: %f \n", h2_efficiency_num_fake_1->GetBinContent(binX, binY));
        ////printf("den 1: %f \n", h2_efficiency_den_fake_1->GetBinContent(binX, binY));
        ////printf("num 2: %f \n", h2_efficiency_num_fake_2->GetBinContent(binX, binY));
        ////printf("den 2: %f \n", h2_efficiency_den_fake_2->GetBinContent(binX, binY));
        //printf("Fake-rate 1: %f \n", fakeRate_1);
        //printf("Fake-rate 2: %f \n", fakeRate_2);
        //printf("Fake-rate: %f \n", fakeRate);
        //printf("%% error: %f \n", errorPercent);
        
        return std::make_pair(fakeRate, errorPercent);
    }
}

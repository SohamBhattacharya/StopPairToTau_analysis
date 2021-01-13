# ifndef Plot_H
# define Plot_H


# include <TCanvas.h>
# include <TFile.h>
# include <TH1F.h>
# include <TH2F.h>
# include <THStack.h>
# include <TLegend.h>
# include <TLine.h>
# include <TStyle.h>
# include <TPad.h>


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
        const char *fileName);
    
    
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
        const char *fileName);
}


# endif

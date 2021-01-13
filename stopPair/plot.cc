# include <iostream>
# include <string>
# include <vector>

# include <TCanvas.h>
# include <TFile.h>
# include <TH1F.h>
# include <THStack.h>
# include <TLegend.h>
# include <TTree.h>

# include "HeaderFiles/Common.h"
# include "HeaderFiles/Plot.h"



// Data
const char *rootFileName_tau_data = \
    "tauTau_data/output_analyzed/Tau_tauTau_analysis/custom_all_analyzed.root";

TFile *rootFile_tau_data;

double luminosity_tau_data = 8.347 * pow(10, 3); // pb^-1


const char *rootFileName_singleMuon_data = \
    "muTau_data/output_analyzed/SingleMuon_muTau/custom_all_analyzed.root";

TFile *rootFile_singleMuon_data;

double luminosity_singleMuon_data = 8.347 * pow(10, 3); // pb^-1


const char *rootFileName_muonEG_data = \
    "elMu_data/output_analyzed/MuonEG_elMu/custom_all_analyzed.root";

TFile *rootFile_muonEG_data;

double luminosity_muonEG_data = 8.347 * pow(10, 3);//3.102 * pow(10, 3); // pb^-1



// stopPair_mc
std::vector <std::string> v_rootFileName_stopPair_tauTau_mc = { \
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_400_100_tauTau_analysis/custom_all_analyzed.root",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_800_400_tauTau_analysis/custom_all_analyzed.root",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1100_100_tauTau_analysis/custom_all_analyzed.root"
};

std::vector <std::vector <TFile*> > vv_rootFile_stopPair_tauTau_mc(v_rootFileName_stopPair_tauTau_mc.size());

std::vector <std::string> v_rootFileName_stopPair_muTau_mc = { \
    //"stopPair_mc/output_analyzed/stopPair_mc_1_muTau/stopPair_mc_1_custom_analyzed.root",
    
    //"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_200_100_muTau/custom_all_analyzed.root",
    //"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_300_150_muTau/custom_all_analyzed.root",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_500_325_muTau/custom_all_analyzed.root",
    
    //"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_200_100_muTau/custom_all_analyzed.root",
    //"stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_300_150_muTau/custom_all_analyzed.root",
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_500_325_muTau/custom_all_analyzed.root"
};

std::vector <std::vector <TFile*> > vv_rootFile_stopPair_muTau_mc(v_rootFileName_stopPair_muTau_mc.size());

std::vector <double> v_crossSection_stopPair_mc = {
    1.83537,
    0.0283338,
    0.00307413
};

std::vector <double> v_nEvent_stopPair_mc = {
    88301,
    43524,
    39956
};

std::vector <std::string> v_label_stopPair_mc = {
    "0.25, [400, 100]",
    "0.25, [800, 400]",
    "0.25, [1100, 100]"
};

/*// SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
std::vector <std::string> v_rootFileName_XStau0p25_mc = { \
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/custom_all_analyzed.root"};
std::vector <TFile*> v_rootFile_XStau0p25_mc(v_rootFileName_XStau0p25_mc.size());
std::vector <double> v_crossSection_XStau0p25_mc = {1};
std::vector <double> v_nEvent_XStau0p25_mc = {21847544};


// SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
std::vector <std::string> v_rootFileName_XStau0p5_mc = { \
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/custom_all_analyzed.root"};
std::vector <TFile*> v_rootFile_XStau0p5_mc(v_rootFileName_XStau0p5_mc.size());
std::vector <double> v_crossSection_XStau0p5_mc = {1};
std::vector <double> v_nEvent_XStau0p5_mc = {16008616};


// SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8
std::vector <std::string> v_rootFileName_XStau0p75_mc = { \
    "stopPair_mc/output_analyzed/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/custom_all_analyzed.root"};
std::vector <TFile*> v_rootFile_XStau0p75_mc(v_rootFileName_XStau0p75_mc.size());
std::vector <double> v_crossSection_XStau0p75_mc = {1};
std::vector <double> v_nEvent_XStau0p75_mc = {21421255};*/


// WJetsToLNu_mc
std::vector <std::string> v_rootFileName_WJetsToLNu_tauTau_mc = { \
    "WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_WJetsToLNu_tauTau_mc;

std::vector <std::string> v_rootFileName_WJetsToLNu_muTau_mc = { \
    "WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_WJetsToLNu_muTau_mc;

std::vector <std::string> v_rootFileName_WJetsToLNu_elMu_mc = { \
    "WJetsToLNu_mc/output_analyzed/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "WJetsToLNu_mc/output_analyzed/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_WJetsToLNu_elMu_mc;

std::vector <double> v_crossSection_WJetsToLNu_mc = { \
    //1.21*50380,
    //0*1.21*9644.5,
    //0*1.21*3144.5,
    //0*1.21*954.8,
    //0*1.21*485.6
    1.0/1000.0,
    1.0/1000.0,
    1.0/1000.0,
    1.0/1000.0,
    1.0/1000.0
};

std::vector <double> v_nEvent_WJetsToLNu_mc = { \
    //57026058,
    //45367044,
    //29878415,
    //19798117,
    //9170576
    1,
    1,
    1,
    1,
    1
};


// DYJetsToLL_mc
std::vector <std::string> v_rootFileName_DYJetsToLL_tauTau_mc = { \
    //"DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_tauTau_analysis/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_DYJetsToLL_tauTau_mc;

std::vector <std::string> v_rootFileName_DYJetsToLL_muTau_mc = { \
    //"DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_muTau/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_DYJetsToLL_muTau_mc;

std::vector <std::string> v_rootFileName_DYJetsToLL_elMu_mc = { \
    //"DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root",
    "DYJetsToLL_mc/output_analyzed/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_elMu/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_DYJetsToLL_elMu_mc;

std::vector <double> v_crossSection_DYJetsToLL_mc = { \
    //0*1.16*18610,
    //1.16*4954,
    //0*1.16*1012.5,
    //0*1.16*332.8,
    //0*1.16*101.8,
    //0*1.16*54.8
    1.0/1000.0,
    1.0/1000.0,
    1.0/1000.0,
    1.0/1000.0,
    1.0/1000.0
};

std::vector <double> v_nEvent_DYJetsToLL_mc = { \
    //35291566,
    //96658943,
    //62627174,
    //19970551,
    //5856110,
    //4197868
    1,
    1,
    1,
    1,
    1
};



// VH_mc
std::vector <std::string> v_rootFileName_VH_tauTau_mc = { \
    "VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VH_mc/output_analyzed/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_VH_tauTau_mc;

std::vector <std::string> v_rootFileName_VH_muTau_mc = { \
    "VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root",
    "VH_mc/output_analyzed/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_VH_muTau_mc;

std::vector <std::string> v_rootFileName_VH_elMu_mc = { \
    "VH_mc/output_analyzed/ZH_HToBB_ZToLL_M125_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root",
    "VH_mc/output_analyzed/WH_HToBB_WToLNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_VH_elMu_mc;

std::vector <double> v_crossSection_VH_mc = { \
    0.0515,
    0.2580
};

std::vector <double> v_nEvent_VH_mc = { \
    //2982520
    2159030,
    2179687
};


// VV_mc
std::vector <std::string> v_rootFileName_VV_tauTau_mc = { \
    "VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VV_mc/output_analyzed/ZZTo4L_13TeV-amcatnloFXFX-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_tauTau_analysis/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_VV_tauTau_mc;

std::vector <std::string> v_rootFileName_VV_muTau_mc = { \
    "VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root",
    "VV_mc/output_analyzed/ZZTo4L_13TeV-amcatnloFXFX-pythia8_muTau/custom_all_analyzed.root",
    "VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_muTau/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_muTau/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_VV_muTau_mc;

std::vector <std::string> v_rootFileName_VV_elMu_mc = { \
    "VV_mc/output_analyzed/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root",
    "VV_mc/output_analyzed/ZZTo4L_13TeV-amcatnloFXFX-pythia8_elMu/custom_all_analyzed.root",
    "VV_mc/output_analyzed/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZJToLLLNu_TuneCUETP8M1_13TeV-amcnlo-pythia8_elMu/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root",
    "VV_mc/output_analyzed/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_elMu/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_VV_elMu_mc;

std::vector <double> v_crossSection_VV_mc = { \
    11.95,
    49.997,
    1.212,
    3.22,
    4.708,
    5.595,
    3.05,
    10.71
};

std::vector <double> v_nEvent_VV_mc = { \
    6888511,
    5176114,
    10709784,
    15345572,
    1930828,
    26517272,
    1703772,
    24221923
};


// WG
std::vector <std::string> v_rootFileName_WG_tauTau_mc = { \
    "WG_mc/output_analyzed/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_tauTau_analysis/custom_all_analyzed.root",
    "WG_mc/output_analyzed/WGstarToLNuMuMu_012Jets_13TeV-madgraph_tauTau_analysis/custom_all_analyzed.root",
    "WG_mc/output_analyzed/WGstarToLNuEE_012Jets_13TeV-madgraph_tauTau_analysis/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_WG_tauTau_mc;

std::vector <std::string> v_rootFileName_WG_muTau_mc = { \
    "WG_mc/output_analyzed/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_muTau/custom_all_analyzed.root",
    "WG_mc/output_analyzed/WGstarToLNuMuMu_012Jets_13TeV-madgraph_muTau/custom_all_analyzed.root",
    "WG_mc/output_analyzed/WGstarToLNuEE_012Jets_13TeV-madgraph_muTau/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_WG_muTau_mc;

std::vector <std::string> v_rootFileName_WG_elMu_mc = { \
    "WG_mc/output_analyzed/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_elMu/custom_all_analyzed.root",
    "WG_mc/output_analyzed/WGstarToLNuMuMu_012Jets_13TeV-madgraph_elMu/custom_all_analyzed.root",
    "WG_mc/output_analyzed/WGstarToLNuEE_012Jets_13TeV-madgraph_elMu/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_WG_elMu_mc;

std::vector <double> v_crossSection_WG_mc = { \
    489.0,
    2.793,
    3.526
};

std::vector <double> v_nEvent_WG_mc = { \
    12146754,
    2218596,
    2249800
};



// ttbar_mc
std::vector <std::string> v_rootFileName_ttbar_tauTau_mc = { \
    "ttbar_mc/output_analyzed/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_tauTau_analysis/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_ttbar_tauTau_mc;

std::vector <std::string> v_rootFileName_ttbar_muTau_mc = { \
    "ttbar_mc/output_analyzed/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_muTau/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_ttbar_muTau_mc;

std::vector <std::string> v_rootFileName_ttbar_elMu_mc = { \
    "ttbar_mc/output_analyzed/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_elMu/custom_all_analyzed.root"
};

std::vector <TFile*> v_rootFile_ttbar_elMu_mc;

std::vector <double> v_crossSection_ttbar_mc = { \
    831.76
};

std::vector <double> v_nEvent_ttbar_mc = { \
    //92925926
    77081156
};


// singleTop
std::vector <std::string> v_rootFileName_singleTop_tauTau_mc = { \
    "singleTop_mc/output_analyzed/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_tauTau_analysis/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_tauTau_analysis/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_tauTau_analysis/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_tauTau_analysis/custom_all_analyzed.root",
};

std::vector <TFile*> v_rootFile_singleTop_tauTau_mc;

std::vector <std::string> v_rootFileName_singleTop_muTau_mc = { \
    "singleTop_mc/output_analyzed/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_muTau/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_muTau/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_muTau/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_muTau/custom_all_analyzed.root",
};

std::vector <TFile*> v_rootFile_singleTop_muTau_mc;

std::vector <std::string> v_rootFileName_singleTop_elMu_mc = { \
    "singleTop_mc/output_analyzed/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_elMu/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1_elMu/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_elMu/custom_all_analyzed.root",
    "singleTop_mc/output_analyzed/ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1_elMu/custom_all_analyzed.root",
};

std::vector <TFile*> v_rootFile_singleTop_elMu_mc;

std::vector <double> v_crossSection_singleTop_mc = { \
    35.6,
    35.6,
    80.95,
    136.02
};

std::vector <double> v_nEvent_singleTop_mc = { \
    6933094,
    6952830,
    38811017,
    67240808
};



// QCD
//std::vector <std::string> v_rootFileName_QCD_mc = {
//    "QCD_mc/output_analyzed/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root",
//    "QCD_mc/output_analyzed/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/custom_all_analyzed.root"
//};
//
//std::vector <TFile*> v_rootFile_QCD_mc;//(v_rootFileName_QCD_mc.size());
//
//std::vector <double> v_crossSection_QCD_mc = { \
//    1837410000.0, \
//    140932000.0, \
//    19204300.0, \
//    2762530.0, \
//    471100.0, \
//    117276.0, \
//    7823.0, \
//    648.2, \
//    186.9, \
//    32.293, \
//    9.4183, \
//    0.84265, \
//    0.114943, \
//    0.00682981, \
//    0.000165445};
//
//std::vector <double> v_nEvent_QCD_mc = { \
//    39898460, \
//    9980050, \
//    9954370, \
//    6986740, \
//    6708572, \
//    6958708, \
//    4150588, \
//    3959986, \
//    3896412, \
//    3992112, \
//    2999069, \
//    396409, \
//    397660, \
//    399226, \
//    391735};


void plotHistogram_efficiency(std::vector <const char*> v_histNumName, \
    std::vector <std::string> v_label, \
    const char *histDenName, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName);


void plotHistogram_gen_tauTau(const char *histName_mc, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName);


void plotHistogram_reco_elMu(const char *histName_mc, \
    const char *histName_data, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName);


void plotHistogram_reco_tauTau(const char *histName_mc, \
    const char *histName_data, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName);


void plotHistogram_reco_muTau(const char *histName_mc, \
    const char *histName_data, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName);


void getRootFiles(std::vector <std::string> *v_rootFileName, \
    std::vector <TFile*> *v_rootFile);


TH1F* getHistogram_data(const char *histName, \
    const char *details, \
    TFile *rootFile);


TH1F* getHistogram_mc(const char *histName, \
    const char *details, \
    std::vector <TFile*> *v_rootFile, \
    std::vector <double> *v_crossSection, \
    std::vector <double> *v_nEvent, \
    double lumi_data);


TH1F* getHistogram_QCD(const char *histName, \
    const char *details_sig, \
    const char *details_bg, \
    const char *details_scaleNum, \
    const char *details_scaleDen, \
    TFile *rootFile_data, \
    double lumi_data, \
    std::vector <std::vector <TFile*>* > v_rootFile_mc, \
    std::vector <std::vector <double>* > v_crossSection_mc, \
    std::vector <std::vector <double>* > v_nEvent_mc);


void freeMemory(std::vector <TFile*> v_rootFile);
void plotElMu();
void plotTauTau();
void plotMuTau();


int main()
{
    //plotElMu();
    //plotMuTau();
    plotTauTau();
}


void plotElMu()
{
    getRootFiles( \
        &v_rootFileName_WJetsToLNu_elMu_mc, \
        &v_rootFile_WJetsToLNu_elMu_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_DYJetsToLL_elMu_mc, \
        &v_rootFile_DYJetsToLL_elMu_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_VH_elMu_mc, \
        &v_rootFile_VH_elMu_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_VV_elMu_mc, \
        &v_rootFile_VV_elMu_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_WG_elMu_mc, \
        &v_rootFile_WG_elMu_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_ttbar_elMu_mc, \
        &v_rootFile_ttbar_elMu_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_singleTop_elMu_mc, \
        &v_rootFile_singleTop_elMu_mc);
    
    //
    rootFile_muonEG_data = TFile::Open(rootFileName_muonEG_data, "READ");
    
    plotHistogram_reco_elMu( \
        "reco/b_n_medium_reco", \
        "reco/b_n_medium_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/b1_pT_reco", \
        "reco/b1_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/b1_eta_reco", \
        "reco/b1_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/elMu_el_pT_reco", \
        "reco/elMu_el_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/elMu_el_eta_reco", \
        "reco/elMu_el_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/elMu_mu_pT_reco", \
        "reco/elMu_mu_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/elMu_mu_eta_reco", \
        "reco/elMu_mu_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/elMu_m_reco", \
        "reco/elMu_m_reco", \
        false, \
        0, true, 600, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/elMu_MET_Dzeta_reco", \
        "reco/elMu_MET_Dzeta_reco", \
        false, \
        -300, true, 300, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/elMu_MET_mT2_reco", \
        "reco/elMu_MET_mT2_reco", \
        false, \
        0, true, 200, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_elMu( \
        "reco/MET_E_reco", \
        "reco/MET_E_reco", \
        false, \
        0, true, 600, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
}


void plotTauTau()
{
    for(int iSet = 0; iSet < vv_rootFile_stopPair_tauTau_mc.size(); iSet++)
    {
        std::vector <std::string> v_temp_rootFileName_stopPair_mc = {v_rootFileName_stopPair_tauTau_mc.at(iSet)};
        
        getRootFiles( \
            &v_temp_rootFileName_stopPair_mc, \
            &vv_rootFile_stopPair_tauTau_mc.at(iSet));
    }
    /*getRootFiles( \
        &v_rootFileName_stopPair_tauTau_mc, \
        &v_rootFile_stopPair_mc);
    
    getRootFiles( \
        &v_rootFileName_XStau0p25_mc, \
        &v_rootFile_XStau0p25_mc);
    
    getRootFiles( \
        &v_rootFileName_XStau0p5_mc, \
        &v_rootFile_XStau0p5_mc);
    
    getRootFiles( \
        &v_rootFileName_XStau0p75_mc, \
        &v_rootFile_XStau0p75_mc);*/
    
    //
    getRootFiles( \
        &v_rootFileName_WJetsToLNu_tauTau_mc, \
        &v_rootFile_WJetsToLNu_tauTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_DYJetsToLL_tauTau_mc, \
        &v_rootFile_DYJetsToLL_tauTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_VH_tauTau_mc, \
        &v_rootFile_VH_tauTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_VV_tauTau_mc, \
        &v_rootFile_VV_tauTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_WG_tauTau_mc, \
        &v_rootFile_WG_tauTau_mc);
    
    //
    //getRootFiles( \
        &v_rootFileName_QCD_mc, \
        &v_rootFile_QCD_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_ttbar_tauTau_mc, \
        &v_rootFile_ttbar_tauTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_singleTop_tauTau_mc, \
        &v_rootFile_singleTop_tauTau_mc);
    
    //
    rootFile_tau_data = TFile::Open(rootFileName_tau_data, "READ");
    
    // b n
    //plotHistogram_gen_tauTau( \
    //    "gen/b_n_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/b_n_medium_reco", \
        "reco/b_n_medium_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // b1 pT
    //plotHistogram_gen_tauTau( \
    //    "gen/b1_pT_gen", \
    //    false, \
    //    0, true, 500, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/b1_pT_reco", \
        "reco/b1_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // b1 eta
    //plotHistogram_gen_tauTau( \
    //    "gen/b1_eta_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/b1_eta_reco", \
        "reco/b1_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    // b2 pT
    //plotHistogram_gen_tauTau( \
    //    "gen/b2_pT_gen", \
    //    false, \
    //    0, true, 500, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/b2_pT_reco", \
        "reco/b2_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // b2 eta
    //plotHistogram_gen_tauTau( \
    //    "gen/b2_eta_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/b2_eta_reco", \
        "reco/b2_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/b_tauOverlap_n_by_b_n_reco", \
        "reco/b_tauOverlap_n_by_b_n_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/b_n_by_jet_n_reco", \
        "reco/b_n_by_jet_n_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/b1_pT_by_jet_HT_reco", \
        "reco/b1_pT_by_jet_HT_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/nonBjet1_pT_by_b1_pT_reco", \
        "reco/nonBjet1_pT_by_b1_pT_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau n
    //plotHistogram( \
        "gen/tau_vis_n_gen", \
        "reco/tau_n_mediumIso_reco", \
        false, \
        0, -1, \
        0, -1, \
        false, true, \
        "tau vis n gen", \
        "plots/tau_vis_n_gen.pdf");
    
    //plotHistogram( \
        "reco/tau_n_mediumIso_reco", \
        "reco/tau_n_mediumIso_reco", \
        false, \
        0, -1, \
        0, -1, \
        false, true, \
        "tau n mediumIso reco", \
        "plots/tau_n_mediumIso_reco.pdf");
    
    // tau pT effciency
    //plotHistogram_efficiency( \
    //    {"reco/tau_pT_looseIso_reco", \
    //        "reco/tau_pT_mediumIso_reco", \
    //        "reco/tau_pT_tightIso_reco"}, \
    //    {"looseIso", "mediumIso", "tightIso"}, \
    //    "gen/tau_vis_pT_gen", \
    //    false, \
    //    0, false, 500, false, \
    //    0, true, 1, true, \
    //    false, false, \
    //    /*"p_{T, #tau_{RECO}} / p_{T, #tau_{vis-GEN}}", \*/
    //    "Efficiency vs. p_{T, #tau_{vis-GEN}}", \
    //    "plots/reco/tau_efficiency_pT.pdf");
    
    // tau1 tau2 deltaPhi
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_tau_vis2_deltaPhi_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tauTau_deltaPhi_reco", \
        "reco/tauTau_deltaPhi_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 tau2 deltaR
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_tau_vis2_deltaR_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tauTau_deltaR_reco", \
        "reco/tauTau_deltaR_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
        
    // tau1 MET deltaPhi
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_MET_deltaPhi_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tau1_MET_deltaPhi_reco", \
        "reco/tau1_MET_deltaPhi_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 tau2 m
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_tau_vis2_m_gen", \
    //    false, \
    //    0, true, 600, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tauTau_m_reco", \
        "reco/tauTau_m_reco", \
        false, \
        0, true, 600, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 tau2 MET mT2
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_tau_vis2_MET_mT2_gen", \
    //    false, \
    //    0, true, 200, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tauTau_MET_mT2_lsp0_reco", \
        "reco/tauTau_MET_mT2_lsp0_reco", \
        false, \
        0, true, 200, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/tauBtauB_MET_mT2_lsp0_reco", \
        "reco/tauBtauB_MET_mT2_lsp0_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/bb_MET_mT2_lsp0_reco", \
        "reco/bb_MET_mT2_lsp0_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    TLine *l_MET_50 = new TLine(50, 0, 50, 200);
    l_MET_50->SetLineColor(2);
    TLine *l_MET_200 = new TLine(200, 0, 200, 200);
    l_MET_200->SetLineColor(2);
    
    TLine *l_mT2_40 = new TLine(0, 40, 600, 40);
    l_mT2_40->SetLineColor(2);
    TLine *l_mT2_80 = new TLine(0, 80, 600, 80);
    l_mT2_80->SetLineColor(2);
    
    std::vector <TLine*> v_line = {l_MET_50, l_MET_200, l_mT2_40, l_mT2_80};
    
    Plot::plot( \
        (TH2F*) v_rootFile_ttbar_tauTau_mc.at(0)->Get("reco/tauTau_MET_mT2_vs_MET_E_reco_tightTight_OS")->Clone(), \
        "colz text89", \
        true, \
        0, true, 600, true, \
        0, true, 200, true, \
        0, true, 0.1, true, \
        false, false, false, \
        0, 0, \
        v_line, \
        0, \
        "plots/tauTau/reco/tauTau_MET_mT2_vs_MET_E_reco_tightTight_OS_ttbar.pdf");
    
    Plot::plot( \
        (TH2F*) vv_rootFile_stopPair_tauTau_mc.at(1).at(0)->Get("reco/tauTau_MET_mT2_vs_MET_E_reco_tightTight_OS")->Clone(), \
        "colz text89", \
        true, \
        0, true, 600, true, \
        0, true, 200, true, \
        0, true, 0.1, true, \
        false, false, false, \
        0, 0, \
        v_line, \
        0, \
        "plots/tauTau/reco/tauTau_MET_mT2_vs_MET_E_reco_tightTight_OS_stopPair.pdf");
    
    TH2F *h2_temp1 = (TH2F*) vv_rootFile_stopPair_tauTau_mc.at(1).at(0)->Get("reco/tauTau_MET_mT2_vs_MET_E_reco_tightTight_OS")->Clone();
    h2_temp1->Scale(1.0/h2_temp1->Integral());
    TH2F *h2_temp2 = (TH2F*) v_rootFile_ttbar_tauTau_mc.at(0)->Get("reco/tauTau_MET_mT2_vs_MET_E_reco_tightTight_OS")->Clone();
    h2_temp2->Scale(1.0/h2_temp2->Integral());
    h2_temp1->Divide(h2_temp2);
    
    Plot::plot( \
        h2_temp1, \
        "colz text89", \
        false, \
        0, true, 600, true, \
        0, true, 200, true, \
        0, false, 0, false, \
        false, false, true, \
        0, 0, \
        v_line, \
        0, \
        "plots/tauTau/reco/tauTau_MET_mT2_vs_MET_E_reco_tightTight_OS_stopPair_by_ttbar.pdf");
    
    delete h2_temp1;
    delete h2_temp2;
    
    
    // tau1 tau2 MET Dzeta
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_tau_vis2_MET_Dzeta_gen", \
    //    false, \
    //    -300, true, 300, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tauTau_MET_Dzeta_reco", \
        "reco/tauTau_MET_Dzeta_reco", \
        false, \
        -300, true, 300, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 tau2 b HT
    plotHistogram_reco_tauTau( \
        "reco/tauTau_b_HT_reco", \
        "reco/tauTau_b_HT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 tau2 b MHT
    plotHistogram_reco_tauTau( \
        "reco/tauTau_b_MHT_reco", \
        "reco/tauTau_b_MHT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 tau2 jet HT
    plotHistogram_reco_tauTau( \
        "reco/tauTau_jet_HT_reco", \
        "reco/tauTau_jet_HT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 tau2 jet MHT
    plotHistogram_reco_tauTau( \
        "reco/tauTau_jet_MHT_reco", \
        "reco/tauTau_jet_MHT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // (tau1 tau2 b HT) by (tau1 tau2 jet HT)
    plotHistogram_reco_tauTau( \
        "reco/tauTau_b_HT_by_tauTau_jet_HT_reco", \
        "reco/tauTau_b_HT_by_tauTau_jet_HT_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // (tau1 tau2 b MHT) by (tau1 tau2 jet HT)
    plotHistogram_reco_tauTau( \
        "reco/tauTau_b_MHT_by_tauTau_jet_MHT_reco", \
        "reco/tauTau_b_MHT_by_tauTau_jet_MHT_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 m
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_m_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tau1_m_reco", \
        "reco/tau1_m_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 pT
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_pT_gen", \
    //    false, \
    //    0, true, 500, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tau1_pT_reco", \
        "reco/tau1_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 eta
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis1_eta_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tau1_eta_reco", \
        "reco/tau1_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau1 chHad1
    plotHistogram_reco_tauTau( \
        "reco/tau1_chHad1_pT_by_tau1_pT_reco", \
        "reco/tau1_chHad1_pT_by_tau1_pT_reco", \
        false, \
        0, false, 1.2, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau2 m
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis2_m_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tau2_m_reco", \
        "reco/tau2_m_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau2 pT
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis2_pT_gen", \
    //    false, \
    //    0, true, 500, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tau2_pT_reco", \
        "reco/tau2_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau2 eta
    //plotHistogram_gen_tauTau( \
    //    "gen/tau_vis2_eta_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/tau2_eta_reco", \
        "reco/tau2_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    // jet n
    //plotHistogram_gen_tauTau( \
    //    "gen/jet_n_gen", \
    //    false, \
    //    0, false, 0, false, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/jet_n_reco", \
        "reco/jet_n_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet HT
    //plotHistogram_gen_tauTau( \
    //    "gen/jet_HT_gen", \
    //    false, \
    //    0, false, 1000, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/jet_HT_reco", \
        "reco/jet_HT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet MHT
    //plotHistogram_gen_tauTau( \
    //    "gen/jet_MHT_gen", \
    //    false, \
    //    0, false, 1000, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/jet_MHT_reco", \
        "reco/jet_MHT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet Meff
    plotHistogram_reco_tauTau( \
        "reco/jet_Meff_reco", \
        "reco/jet_Meff_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/jet1_jet2_mT_reco", \
        "reco/jet1_jet2_mT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/nonBjet1_pT_by_jet_HT_reco", \
        "reco/nonBjet1_pT_by_jet_HT_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/nonBjet_tauOverlap_n_by_nonBjet_n_reco", \
        "reco/nonBjet_tauOverlap_n_by_nonBjet_n_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_tauTau( \
        "reco/jet1_MET_deltaPhi_reco", \
        "reco/jet1_MET_deltaPhi_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // nonBjet1 pT
    plotHistogram_reco_tauTau( \
        "reco/nonBjet1_pT_reco", \
        "reco/nonBjet1_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // nonBjet1 eta
    plotHistogram_reco_tauTau( \
        "reco/nonBjet1_eta_reco", \
        "reco/nonBjet1_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    // nonBjet2 pT
    plotHistogram_reco_tauTau( \
        "reco/nonBjet2_pT_reco", \
        "reco/nonBjet2_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // nonBjet2 eta
    plotHistogram_reco_tauTau( \
        "reco/nonBjet2_eta_reco", \
        "reco/nonBjet2_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet1 pT
    /*//plotHistogram( \
        "gen/jet1_pT_gen", \
        "reco/jet1_pT_reco", \
        false, \
        0, 2000, \
        0, -1, \
        false, true, \
        "jet1 pT gen", \
        "plots/jet1_pT_gen.pdf");
    
    plotHistogram( \
        "reco/jet1_pT_reco", \
        "reco/jet1_pT_reco", \
        false, \
        0, 2000, \
        0, -1, \
        false, true, \
        "jet1 pT reco", \
        "plots/jet1_pT_reco.pdf");
    
    // jet2 pT
    plotHistogram( \
        "gen/jet2_pT_gen", \
        "reco/jet2_pT_reco", \
        false, \
        0, 2000, \
        0, -1, \
        false, true, \
        "jet2 pT gen", \
        "plots/jet2_pT_gen.pdf");
    
    plotHistogram( \
        "reco/jet2_pT_reco", \
        "reco/jet2_pT_reco", \
        false, \
        0, 2000, \
        0, -1, \
        false, true, \
        "jet2 pT reco", \
        "plots/jet2_pT_reco.pdf");*/
    
    
    // MET E
    //plotHistogram_gen_tauTau( \
    //    "gen/MET_E_gen", \
    //    false, \
    //    0, true, 600, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/MET_E_reco", \
        "reco/MET_E_reco", \
        false, \
        0, true, 600, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // MET phi
    //plotHistogram_gen_tauTau( \
    //    "gen/MET_phi_gen", \
    //    false, \
    //    -2*M_PI, true, 2*M_PI, true, \
    //    pow(10, -4), true, 0, false, \
    //    false, true, \
    //    0, \
    //    0);
    
    plotHistogram_reco_tauTau( \
        "reco/MET_phi_reco", \
        "reco/MET_phi_reco", \
        false, \
        -2*M_PI, true, 2*M_PI, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
}


void plotMuTau()
{
    for(int iSet = 0; iSet < vv_rootFile_stopPair_muTau_mc.size(); iSet++)
    {
        std::vector <std::string> v_temp_rootFileName_stopPair_mc = {v_rootFileName_stopPair_muTau_mc.at(iSet)};
        
        getRootFiles( \
            &v_temp_rootFileName_stopPair_mc, \
            &vv_rootFile_stopPair_muTau_mc.at(iSet));
    }
    
    //
    getRootFiles( \
        &v_rootFileName_WJetsToLNu_muTau_mc, \
        &v_rootFile_WJetsToLNu_muTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_DYJetsToLL_muTau_mc, \
        &v_rootFile_DYJetsToLL_muTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_VH_muTau_mc, \
        &v_rootFile_VH_muTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_VV_muTau_mc, \
        &v_rootFile_VV_muTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_WG_muTau_mc, \
        &v_rootFile_WG_muTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_ttbar_muTau_mc, \
        &v_rootFile_ttbar_muTau_mc);
    
    //
    getRootFiles( \
        &v_rootFileName_singleTop_muTau_mc, \
        &v_rootFile_singleTop_muTau_mc);
    
    //
    rootFile_singleMuon_data = TFile::Open(rootFileName_singleMuon_data, "READ");
    
    // b n
    plotHistogram_reco_muTau( \
        "reco/b_n_medium_reco", \
        "reco/b_n_medium_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // b1 pT
    plotHistogram_reco_muTau( \
        "reco/b1_pT_reco", \
        "reco/b1_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // b1 eta
    plotHistogram_reco_muTau( \
        "reco/b1_eta_reco", \
        "reco/b1_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    // b2 pT
    plotHistogram_reco_muTau( \
        "reco/b2_pT_reco", \
        "reco/b2_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // b2 eta
    plotHistogram_reco_muTau( \
        "reco/b2_eta_reco", \
        "reco/b2_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_muTau( \
        "reco/b_n_by_jet_n_reco", \
        "reco/b_n_by_jet_n_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_muTau( \
        "reco/b1_pT_by_jet_HT_reco", \
        "reco/b1_pT_by_jet_HT_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_muTau( \
        "reco/nonBjet1_pT_by_b1_pT_reco", \
        "reco/nonBjet1_pT_by_b1_pT_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau deltaPhi
    plotHistogram_reco_muTau( \
        "reco/muTau_deltaPhi_reco", \
        "reco/muTau_deltaPhi_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau deltaR
    plotHistogram_reco_muTau( \
        "reco/muTau_deltaR_reco", \
        "reco/muTau_deltaR_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau m
    plotHistogram_reco_muTau( \
        "reco/muTau_m_reco", \
        "reco/muTau_m_reco", \
        false, \
        0, true, 600, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau MET mT2
     plotHistogram_reco_muTau( \
        "reco/muTau_MET_mT2_lsp0_reco", \
        "reco/muTau_MET_mT2_lsp0_reco", \
        false, \
        0, true, 200, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    TLine *l_MET_50 = new TLine(50, 0, 50, 200);
    l_MET_50->SetLineColor(2);
    TLine *l_MET_200 = new TLine(200, 0, 200, 200);
    l_MET_200->SetLineColor(2);
    
    TLine *l_mT2_40 = new TLine(0, 40, 600, 40);
    l_mT2_40->SetLineColor(2);
    TLine *l_mT2_80 = new TLine(0, 80, 600, 80);
    l_mT2_80->SetLineColor(2);
    
    std::vector <TLine*> v_line = {l_MET_50, l_MET_200, l_mT2_40, l_mT2_80};
    
    Plot::plot( \
        (TH2F*) v_rootFile_ttbar_muTau_mc.at(0)->Get("reco/muTau_MET_mT2_vs_MET_E_reco_tightTightIso_OS")->Clone(), \
        "colz text89", \
        true, \
        0, true, 600, true, \
        0, true, 200, true, \
        0, true, 0.1, true, \
        false, false, false, \
        0, 0, \
        v_line, \
        0, \
        "plots/muTau/reco/muTau_MET_mT2_vs_MET_E_reco_tightTightIso_OS_ttbar.pdf");
    
    Plot::plot( \
        (TH2F*) vv_rootFile_stopPair_muTau_mc.at(1).at(0)->Get("reco/muTau_MET_mT2_vs_MET_E_reco_tightTightIso_OS")->Clone(), \
        "colz text89", \
        true, \
        0, true, 600, true, \
        0, true, 200, true, \
        0, true, 0.1, true, \
        false, false, false, \
        0, 0, \
        v_line, \
        0, \
        "plots/muTau/reco/muTau_MET_mT2_vs_MET_E_reco_tightTightIso_OS_stopPair.pdf");
    
    TH2F *h2_temp1 = (TH2F*) vv_rootFile_stopPair_muTau_mc.at(1).at(0)->Get("reco/muTau_MET_mT2_vs_MET_E_reco_tightTightIso_OS")->Clone();
    h2_temp1->Scale(1.0/h2_temp1->Integral());
    TH2F *h2_temp2 = (TH2F*) v_rootFile_ttbar_muTau_mc.at(0)->Get("reco/muTau_MET_mT2_vs_MET_E_reco_tightTightIso_OS")->Clone();
    h2_temp2->Scale(1.0/h2_temp2->Integral());
    h2_temp1->Divide(h2_temp2);
    
    Plot::plot( \
        h2_temp1, \
        "colz text89", \
        false, \
        0, true, 600, true, \
        0, true, 200, true, \
        pow(10, -1), true, 200, true, \
        false, false, true, \
        0, 0, \
        v_line, \
        0, \
        "plots/muTau/reco/muTau_MET_mT2_vs_MET_E_reco_tightTightIso_OS_stopPair_by_ttbar.pdf");
    
    delete h2_temp1;
    delete h2_temp2;
    
    
    // mu-tau MET Dzeta
    plotHistogram_reco_muTau( \
        "reco/muTau_MET_Dzeta_reco", \
        "reco/muTau_MET_Dzeta_reco", \
        false, \
        -300, true, 300, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau b HT
    plotHistogram_reco_muTau( \
        "reco/muTau_b_HT_reco", \
        "reco/muTau_b_HT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau b MHT
    plotHistogram_reco_muTau( \
        "reco/muTau_b_MHT_reco", \
        "reco/muTau_b_MHT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau jet HT
    plotHistogram_reco_muTau( \
        "reco/muTau_jet_HT_reco", \
        "reco/muTau_jet_HT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu-tau jet MHT
    plotHistogram_reco_muTau( \
        "reco/muTau_jet_MHT_reco", \
        "reco/muTau_jet_MHT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // (mu-tau b HT) by (mu-tau jet HT)
    plotHistogram_reco_muTau( \
        "reco/muTau_b_HT_by_muTau_jet_HT_reco", \
        "reco/muTau_b_HT_by_muTau_jet_HT_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // (mu-tau b MHT) by (mu-tau jet HT)
    plotHistogram_reco_muTau( \
        "reco/muTau_b_MHT_by_muTau_jet_MHT_reco", \
        "reco/muTau_b_MHT_by_muTau_jet_MHT_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu pT
    plotHistogram_reco_muTau( \
        "reco/muTau_mu_pT_reco", \
        "reco/muTau_mu_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // mu eta
    plotHistogram_reco_muTau( \
        "reco/muTau_mu_eta_reco", \
        "reco/muTau_mu_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau m
    plotHistogram_reco_muTau( \
        "reco/muTau_tau_m_reco", \
        "reco/muTau_tau_m_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau pT
    plotHistogram_reco_muTau( \
        "reco/muTau_tau_pT_reco", \
        "reco/muTau_tau_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // tau eta
    plotHistogram_reco_muTau( \
        "reco/muTau_tau_eta_reco", \
        "reco/muTau_tau_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet n
    plotHistogram_reco_muTau( \
        "reco/jet_n_reco", \
        "reco/jet_n_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet HT
    plotHistogram_reco_muTau( \
        "reco/jet_HT_reco", \
        "reco/jet_HT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet MHT
    plotHistogram_reco_muTau( \
        "reco/jet_MHT_reco", \
        "reco/jet_MHT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // jet Meff
    plotHistogram_reco_muTau( \
        "reco/jet_Meff_reco", \
        "reco/jet_Meff_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_muTau( \
        "reco/jet1_jet2_mT_reco", \
        "reco/jet1_jet2_mT_reco", \
        false, \
        0, false, 1000, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_muTau( \
        "reco/nonBjet1_pT_by_jet_HT_reco", \
        "reco/nonBjet1_pT_by_jet_HT_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_muTau( \
        "reco/nonBjet_tauOverlap_n_by_nonBjet_n_reco", \
        "reco/nonBjet_tauOverlap_n_by_nonBjet_n_reco", \
        false, \
        0, false, 1.2, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    plotHistogram_reco_muTau( \
        "reco/jet1_MET_deltaPhi_reco", \
        "reco/jet1_MET_deltaPhi_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // nonBjet1 pT
    plotHistogram_reco_muTau( \
        "reco/nonBjet1_pT_reco", \
        "reco/nonBjet1_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // nonBjet1 eta
    plotHistogram_reco_muTau( \
        "reco/nonBjet1_eta_reco", \
        "reco/nonBjet1_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    // nonBjet2 pT
    plotHistogram_reco_muTau( \
        "reco/nonBjet2_pT_reco", \
        "reco/nonBjet2_pT_reco", \
        false, \
        0, true, 500, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // nonBjet2 eta
    plotHistogram_reco_muTau( \
        "reco/nonBjet2_eta_reco", \
        "reco/nonBjet2_eta_reco", \
        false, \
        0, false, 0, false, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    
    // MET E
    plotHistogram_reco_muTau( \
        "reco/MET_E_reco", \
        "reco/MET_E_reco", \
        false, \
        0, true, 600, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
    
    // MET phi
    plotHistogram_reco_muTau( \
        "reco/MET_phi_reco", \
        "reco/MET_phi_reco", \
        false, \
        -2*M_PI, true, 2*M_PI, true, \
        pow(10, -1), true, 0, false, \
        false, true, \
        0, \
        0);
}


void plotHistogram_gen_tauTau(const char *histName_mc, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName)
{
    std::vector <TH1F*> v_hist_sig;
    std::vector <std::string> v_label_sig;
    
    /*for(int iSet = 0; iSet < vv_rootFile_stopPair_tauTau_mc.size(); iSet++)
    {
        printf("%s \n", v_label_stopPair_mc.at(iSet).c_str());
        v_label_sig.push_back(v_label_stopPair_mc.at(iSet));
        
        std::vector <double> v_temp_crossSection_stopPair_mc = {v_crossSection_stopPair_mc.at(iSet)};
        std::vector <int> v_temp_nEvent_stopPair_mc = {v_nEvent_stopPair_mc.at(iSet)};
        
        v_hist_sig.push_back(getHistogram_mc( \
            histName_mc, \
            "OS", \
            &vv_rootFile_stopPair_tauTau_mc.at(iSet), \
            &v_temp_crossSection_stopPair_mc, \
            &v_temp_nEvent_stopPair_mc, \
            1));
    }*/
    /*printf("stopPair_mc \n");
    v_label_sig.push_back("stopPair");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_stopPair_mc, \
        &v_crossSection_stopPair_mc, \
        &v_nEvent_stopPair_mc, \
        1));
    
    
    printf("XStau0p25_mc \n");
    v_label_sig.push_back("XStau0p25");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_XStau0p25_mc, \
        &v_crossSection_XStau0p25_mc, \
        &v_nEvent_XStau0p25_mc, \
        1));
    
    
    printf("XStau0p5_mc \n");
    v_label_sig.push_back("XStau0p5");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_XStau0p5_mc, \
        &v_crossSection_XStau0p5_mc, \
        &v_nEvent_XStau0p5_mc, \
        1));
    
    
    printf("XStau0p75_mc \n");
    v_label_sig.push_back("XStau0p75");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_XStau0p75_mc, \
        &v_crossSection_XStau0p75_mc, \
        &v_nEvent_XStau0p75_mc, \
        1));*/
    
    
    std::vector <TH1F*> v_hist_mc;
    std::vector <std::string> v_label_mc;
    
    printf("WJetsToLNu \n");
    v_label_mc.push_back("WJetsToLNu");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_WJetsToLNu_tauTau_mc, \
        &v_crossSection_WJetsToLNu_mc, \
        &v_nEvent_WJetsToLNu_mc, \
        1));
    
    
    printf("DYJetsToLL \n");
    v_label_mc.push_back("DYJetsToLL");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_DYJetsToLL_tauTau_mc, \
        &v_crossSection_DYJetsToLL_mc, \
        &v_nEvent_DYJetsToLL_mc, \
        1));
    
    
    printf("VH \n");
    v_label_mc.push_back("VH");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_VH_tauTau_mc, \
        &v_crossSection_VH_mc, \
        &v_nEvent_VH_mc, \
        1));
    
    
    printf("VV \n");
    v_label_mc.push_back("VV");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_VV_tauTau_mc, \
        &v_crossSection_VV_mc, \
        &v_nEvent_VV_mc, \
        1));
    
    
    printf("WG \n");
    v_label_mc.push_back("WG");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_WG_tauTau_mc, \
        &v_crossSection_WG_mc, \
        &v_nEvent_WG_mc, \
        1));
    
    
    //printf("QCD \n");
    //v_label_mc.push_back("QCD");
    
    //v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_QCD_mc, \
        &v_crossSection_QCD_mc, \
        &v_nEvent_QCD_mc, \
        1));
    
    
    printf("ttbar \n");
    v_label_mc.push_back("TT");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_ttbar_tauTau_mc, \
        &v_crossSection_ttbar_mc, \
        &v_nEvent_ttbar_mc, \
        1));
    
    
    printf("singleTop \n");
    v_label_mc.push_back("ST");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "OS", \
        &v_rootFile_singleTop_tauTau_mc, \
        &v_crossSection_singleTop_mc, \
        &v_nEvent_singleTop_mc, \
        1));
    
    
    std::string title_mod;
    std::string fileName_mod;
    
    if(!title)
    {
        title_mod = v_hist_mc.at(0)->GetTitle();
    }
    
    else
    {
        title_mod = title;
    }
    
    
    if(!fileName)
    {
        system("mkdir -p plots/tauTau/gen");
        fileName_mod = "plots/tauTau/gen/" + std::string(v_hist_mc.at(0)->GetName()) + ".pdf";
    }
    
    else
    {
        fileName_mod = fileName;
    }
    
    
    Plot::plot( \
        &v_hist_mc, &v_label_mc, \
        "", \
        &v_hist_sig, &v_label_sig, \
        0, 0, \
        true, \
        normalize, \
        xMin, set_xMin, xMax, set_xMax, \
        yMin, set_yMin, yMax, set_yMax, \
        setLogX, setLogY, \
        0, 0, \
        title_mod.c_str(), \
        fileName_mod.c_str());
}


void plotHistogram_reco_elMu(const char *histName_mc, \
    const char *histName_data, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName)
{
    std::vector <std::string> v_suffix = {
        "OS",
        "OS_elMu_DzetaCut",
        "OS_METcut",
        "OS_elMu_mCut",
        "OS_CSVv2Mcut1",
        "OS_CSVv2Mcut2"
    };
    
    
    for(int iSuffix = 0; iSuffix < v_suffix.size(); iSuffix++)
    {
        std::string suffix = v_suffix.at(iSuffix);
        
        // DATA histogram
        printf("Data \n");
        
        TH1F *hist_data = getHistogram_data( \
            histName_data, \
            suffix.c_str(), \
            rootFile_muonEG_data);
        
        
        // MC histograms
        std::vector <TH1F*> v_hist_mc;
        std::vector <std::string> v_label_mc;
        
        printf("WJetsToLNu \n");
        v_label_mc.push_back("WJetsToLNu");
        
        v_hist_mc.push_back(getHistogram_mc( \
            histName_mc, \
            suffix.c_str(), \
            &v_rootFile_WJetsToLNu_elMu_mc, \
            &v_crossSection_WJetsToLNu_mc, \
            &v_nEvent_WJetsToLNu_mc, \
            luminosity_muonEG_data));
        
        
        printf("DYJetsToLL \n");
        v_label_mc.push_back("DYJetsToLL");
        
        v_hist_mc.push_back(getHistogram_mc( \
            histName_mc, \
            suffix.c_str(), \
            &v_rootFile_DYJetsToLL_elMu_mc, \
            &v_crossSection_DYJetsToLL_mc, \
            &v_nEvent_DYJetsToLL_mc, \
            luminosity_muonEG_data));
        
        printf("VH \n");
        v_label_mc.push_back("VH");
        
        
        v_hist_mc.push_back(getHistogram_mc( \
            histName_mc, \
            suffix.c_str(), \
            &v_rootFile_VH_elMu_mc, \
            &v_crossSection_VH_mc, \
            &v_nEvent_VH_mc, \
            luminosity_muonEG_data));
        
        printf("VV \n");
        v_label_mc.push_back("VV");
        
        
        v_hist_mc.push_back(getHistogram_mc( \
            histName_mc, \
            suffix.c_str(), \
            &v_rootFile_VV_elMu_mc, \
            &v_crossSection_VV_mc, \
            &v_nEvent_VV_mc, \
            luminosity_muonEG_data));
        
        printf("WG \n");
        v_label_mc.push_back("WG");
        
        
        v_hist_mc.push_back(getHistogram_mc( \
            histName_mc, \
            suffix.c_str(), \
            &v_rootFile_WG_elMu_mc, \
            &v_crossSection_WG_mc, \
            &v_nEvent_WG_mc, \
            luminosity_muonEG_data));
        
        
        printf("singleTop \n");
        v_label_mc.push_back("ST");
        
        v_hist_mc.push_back(getHistogram_mc( \
            histName_mc, \
            suffix.c_str(), \
            &v_rootFile_singleTop_elMu_mc, \
            &v_crossSection_singleTop_mc, \
            &v_nEvent_singleTop_mc, \
            luminosity_muonEG_data));
        
        
        printf("ttbar \n");
        v_label_mc.push_back("TT");
        
        v_hist_mc.push_back(getHistogram_mc( \
            histName_mc, \
            suffix.c_str(), \
            &v_rootFile_ttbar_elMu_mc, \
            &v_crossSection_ttbar_mc, \
            &v_nEvent_ttbar_mc, \
            luminosity_muonEG_data));
        
        
        std::string title_mod;
        std::string fileName_mod;
        
        if(!title)
        {
            title_mod = hist_data->GetTitle();
        }
        
        else
        {
            title_mod = title;
        }
        
        
        if(!fileName)
        {
            system("mkdir -p plots/elMu/reco");
            fileName_mod = "plots/elMu/reco/" + std::string(hist_data->GetName()) + ".pdf";
        }
        
        else
        {
            fileName_mod = fileName;
        }
        
        bool noStack = false;
        
        //noStack = true;
        //normalize = true;
        //yMin = pow(10, -3); set_yMin = true;
        //yMax = 1.0; set_yMax = true;
        //setLogY = true;
        //hist_data = 0;
        
        Plot::plot( \
            &v_hist_mc, &v_label_mc, \
            "", \
            0, 0, \
            hist_data, "data", \
            noStack, \
            normalize, \
            xMin, set_xMin, xMax, set_xMax, \
            yMin, set_yMin, yMax, set_yMax, \
            setLogX, setLogY, \
            0, 0, \
            title_mod.c_str(), \
            fileName_mod.c_str());
    }
}


void plotHistogram_reco_tauTau(const char *histName_mc, \
    const char *histName_data, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName)
{
    // DATA histogram
    printf("Data \n");
    
    TH1F *hist_data = getHistogram_data( \
        histName_data, \
        "tightTight_OS", \
        rootFile_tau_data);
    
    
    // MC histograms
    /*TH1F *hist_sig = getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_stopPair_mc, \
        &v_crossSection_stopPair_mc, \
        &v_nEvent_stopPair_mc, \
        luminosity_tau_data);*/
    
    std::vector <TH1F*> v_hist_sig;
    std::vector <std::string> v_label_sig;
    /*char histName_temp[Common::str_len];
    if(!strcmp(histName_mc, "reco/tauTau_MET_mT2_reco"))
    {
        sprintf(histName_temp, "reco/tauTau_MET_mT2_lsp0_reco");
    }
    else
    {
        sprintf(histName_temp, "%s", histName_mc);
    }*/
    
    for(int iSet = 0; iSet < vv_rootFile_stopPair_tauTau_mc.size(); iSet++)
    {
        printf("%s \n", v_label_stopPair_mc.at(iSet).c_str());
        v_label_sig.push_back(v_label_stopPair_mc.at(iSet));
        
        std::vector <double> v_temp_crossSection_stopPair_mc = {v_crossSection_stopPair_mc.at(iSet)};
        std::vector <double> v_temp_nEvent_stopPair_mc = {v_nEvent_stopPair_mc.at(iSet)};
        
        v_hist_sig.push_back(getHistogram_mc( \
            histName_mc, \
            "tightTight_OS", \
            &vv_rootFile_stopPair_tauTau_mc.at(iSet), \
            &v_temp_crossSection_stopPair_mc, \
            &v_temp_nEvent_stopPair_mc, \
            luminosity_tau_data));
    }
    
    /*printf("stopPair_mc \n");
    v_label_sig.push_back("stopPair");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_stopPair_mc, \
        &v_crossSection_stopPair_mc, \
        &v_nEvent_stopPair_mc, \
        luminosity_tau_data));
    
    
    printf("XStau0p25_mc \n");
    v_label_sig.push_back("XStau0p25");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_XStau0p25_mc, \
        &v_crossSection_XStau0p25_mc, \
        &v_nEvent_XStau0p25_mc, \
        luminosity_tau_data));
    
    
    printf("XStau0p5_mc \n");
    v_label_sig.push_back("XStau0p5");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_XStau0p5_mc, \
        &v_crossSection_XStau0p5_mc, \
        &v_nEvent_XStau0p5_mc, \
        luminosity_tau_data));
    
    
    printf("XStau0p75_mc \n");
    v_label_sig.push_back("XStau0p75");
    
    v_hist_sig.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_XStau0p75_mc, \
        &v_crossSection_XStau0p75_mc, \
        &v_nEvent_XStau0p75_mc, \
        luminosity_tau_data));*/
    
    
    std::vector <TH1F*> v_hist_mc;
    std::vector <std::string> v_label_mc;
    
    //printf("WJetsToLNu \n");
    //v_label_mc.push_back("WJetsToLNu");
    //
    //v_hist_mc.push_back(getHistogram_mc( \
    //    histName_mc, \
    //    "tightTight_OS", \
    //    &v_rootFile_WJetsToLNu_tauTau_mc, \
    //    &v_crossSection_WJetsToLNu_mc, \
    //    &v_nEvent_WJetsToLNu_mc, \
    //    luminosity_tau_data));
    
    
    printf("DYJetsToLL \n");
    v_label_mc.push_back("DYJetsToLL");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_DYJetsToLL_tauTau_mc, \
        &v_crossSection_DYJetsToLL_mc, \
        &v_nEvent_DYJetsToLL_mc, \
        luminosity_tau_data));
    
    
    //printf("VH \n");
    //v_label_mc.push_back("VH");
    //
    //v_hist_mc.push_back(getHistogram_mc( \
    //    histName_mc, \
    //    "tightTight_OS", \
    //    &v_rootFile_VH_tauTau_mc, \
    //    &v_crossSection_VH_mc, \
    //    &v_nEvent_VH_mc, \
    //    luminosity_tau_data));
    //
    //
    //printf("VV \n");
    //v_label_mc.push_back("VV");
    //
    //v_hist_mc.push_back(getHistogram_mc( \
    //    histName_mc, \
    //    "tightTight_OS", \
    //    &v_rootFile_VV_tauTau_mc, \
    //    &v_crossSection_VV_mc, \
    //    &v_nEvent_VV_mc, \
    //    luminosity_tau_data));
    //
    //
    //printf("WG \n");
    //v_label_mc.push_back("WG");
    //
    //v_hist_mc.push_back(getHistogram_mc( \
    //    histName_mc, \
    //    "tightTight_OS", \
    //    &v_rootFile_WG_tauTau_mc, \
    //    &v_crossSection_WG_mc, \
    //    &v_nEvent_WG_mc, \
    //    luminosity_tau_data));
    
    
    printf("QCD \n");
    v_label_mc.push_back("QCD");
    
    v_hist_mc.push_back(getHistogram_QCD( \
        histName_data, \
        "tightTight_OS", \
        "looseLoose_OS", \
        "tightTight_SS", \
        "looseLoose_SS", \
        rootFile_tau_data, \
        luminosity_tau_data, \
        {&v_rootFile_DYJetsToLL_tauTau_mc, \
            &v_rootFile_WJetsToLNu_tauTau_mc, \
            &v_rootFile_VH_tauTau_mc, \
            &v_rootFile_VV_tauTau_mc, \
            &v_rootFile_WG_tauTau_mc, \
            &v_rootFile_ttbar_tauTau_mc, \
            &v_rootFile_singleTop_tauTau_mc
        }, \
        {&v_crossSection_DYJetsToLL_mc, \
            &v_crossSection_WJetsToLNu_mc, \
            &v_crossSection_VH_mc, \
            &v_crossSection_VV_mc, \
            &v_crossSection_WG_mc, \
            &v_crossSection_ttbar_mc, \
            &v_crossSection_singleTop_mc
        }, \
        {&v_nEvent_DYJetsToLL_mc, \
            &v_nEvent_WJetsToLNu_mc, \
            &v_nEvent_VH_mc, \
            &v_nEvent_VV_mc, \
            &v_nEvent_WG_mc, \
            &v_nEvent_ttbar_mc, \
            &v_nEvent_singleTop_mc
        }));
    
    
    //v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_QCD_mc, \
        &v_crossSection_QCD_mc, \
        &v_nEvent_QCD_mc, \
        luminosity_tau_data));
    
    
    printf("ttbar \n");
    v_label_mc.push_back("TT");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTight_OS", \
        &v_rootFile_ttbar_tauTau_mc, \
        &v_crossSection_ttbar_mc, \
        &v_nEvent_ttbar_mc, \
        luminosity_tau_data));
    
    
    //printf("singleTop \n");
    //v_label_mc.push_back("ST");
    //
    //v_hist_mc.push_back(getHistogram_mc( \
    //    histName_mc, \
    //    "tightTight_OS", \
    //    &v_rootFile_singleTop_tauTau_mc, \
    //    &v_crossSection_singleTop_mc, \
    //    &v_nEvent_singleTop_mc, \
    //    luminosity_tau_data));
    
    
    std::string title_mod;
    std::string fileName_mod;
    
    if(!title)
    {
        title_mod = hist_data->GetTitle();
    }
    
    else
    {
        title_mod = title;
    }
    
    
    if(!fileName)
    {
        system("mkdir -p plots/tauTau_noStack/reco");
        fileName_mod = "plots/tauTau_noStack/reco/" + std::string(hist_data->GetName()) + ".pdf";
    }
    
    else
    {
        fileName_mod = fileName;
    }
    
    bool noStack = false;
    
    //noStack = false;
    //normalize = true;
    //setLogY = false;
    //hist_data = 0;
    
    noStack = true;
    normalize = true;
    yMin = pow(10, -3); set_yMin = true;
    yMax = 1.0; set_yMax = true;
    setLogY = true;
    hist_data = 0;
    
    Plot::plot( \
        &v_hist_mc, &v_label_mc, \
        "", \
        &v_hist_sig, &v_label_sig, \
        hist_data, "data", \
        noStack, \
        normalize, \
        xMin, set_xMin, xMax, set_xMax, \
        yMin, set_yMin, yMax, set_yMax, \
        setLogX, setLogY, \
        0, 0, \
        title_mod.c_str(), \
        fileName_mod.c_str());
}


void plotHistogram_reco_muTau(const char *histName_mc, \
    const char *histName_data, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName)
{
    // DATA histogram
    printf("Data \n");
    
    TH1F *hist_data = getHistogram_data( \
        histName_data, \
        "tightTightIso_OS", \
        rootFile_singleMuon_data);
    
    
    // MC histograms
    
    std::vector <TH1F*> v_hist_sig;
    std::vector <std::string> v_label_sig;
    
    for(int iSet = 0; iSet < vv_rootFile_stopPair_muTau_mc.size(); iSet++)
    {
        printf("%s \n", v_label_stopPair_mc.at(iSet).c_str());
        v_label_sig.push_back(v_label_stopPair_mc.at(iSet));
        
        std::vector <double> v_temp_crossSection_stopPair_mc = {v_crossSection_stopPair_mc.at(iSet)};
        std::vector <double> v_temp_nEvent_stopPair_mc = {v_nEvent_stopPair_mc.at(iSet)};
        
        v_hist_sig.push_back(getHistogram_mc( \
            histName_mc, \
            "tightTightIso_OS", \
            &vv_rootFile_stopPair_muTau_mc.at(iSet), \
            &v_temp_crossSection_stopPair_mc, \
            &v_temp_nEvent_stopPair_mc, \
            luminosity_tau_data));
    }
    
    
    std::vector <TH1F*> v_hist_mc;
    std::vector <std::string> v_label_mc;
    
    printf("WJetsToLNu \n");
    v_label_mc.push_back("WJetsToLNu");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTightIso_OS", \
        &v_rootFile_WJetsToLNu_muTau_mc, \
        &v_crossSection_WJetsToLNu_mc, \
        &v_nEvent_WJetsToLNu_mc, \
        luminosity_tau_data));
    
    
    printf("DYJetsToLL \n");
    v_label_mc.push_back("DYJetsToLL");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTightIso_OS", \
        &v_rootFile_DYJetsToLL_muTau_mc, \
        &v_crossSection_DYJetsToLL_mc, \
        &v_nEvent_DYJetsToLL_mc, \
        luminosity_tau_data));
    
    
    printf("VH \n");
    v_label_mc.push_back("VH");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTightIso_OS", \
        &v_rootFile_VH_muTau_mc, \
        &v_crossSection_VH_mc, \
        &v_nEvent_VH_mc, \
        luminosity_tau_data));
    
    
    printf("VV \n");
    v_label_mc.push_back("VV");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTightIso_OS", \
        &v_rootFile_VV_muTau_mc, \
        &v_crossSection_VV_mc, \
        &v_nEvent_VV_mc, \
        luminosity_tau_data));
    
    
    printf("WG \n");
    v_label_mc.push_back("WG");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTightIso_OS", \
        &v_rootFile_WG_muTau_mc, \
        &v_crossSection_WG_mc, \
        &v_nEvent_WG_mc, \
        luminosity_tau_data));
    
    
    printf("QCD \n");
    v_label_mc.push_back("QCD");
    
    v_hist_mc.push_back(getHistogram_QCD( \
        histName_data, \
        "tightTightIso_OS", \
        "looseMediumIso_OS", \
        "tightTightIso_SS", \
        "looseMediumIso_SS", \
        rootFile_singleMuon_data, \
        luminosity_singleMuon_data, \
        {&v_rootFile_DYJetsToLL_muTau_mc, \
            &v_rootFile_WJetsToLNu_muTau_mc, \
            &v_rootFile_VH_muTau_mc, \
            &v_rootFile_VV_muTau_mc, \
            &v_rootFile_WG_muTau_mc, \
            &v_rootFile_ttbar_muTau_mc, \
            &v_rootFile_singleTop_muTau_mc
        }, \
        {&v_crossSection_DYJetsToLL_mc, \
            &v_crossSection_WJetsToLNu_mc, \
            &v_crossSection_VH_mc, \
            &v_crossSection_VV_mc, \
            &v_crossSection_WG_mc, \
            &v_crossSection_ttbar_mc, \
            &v_crossSection_singleTop_mc
        }, \
        {&v_nEvent_DYJetsToLL_mc, \
            &v_nEvent_WJetsToLNu_mc, \
            &v_nEvent_VH_mc, \
            &v_nEvent_VV_mc, \
            &v_nEvent_WG_mc, \
            &v_nEvent_ttbar_mc, \
            &v_nEvent_singleTop_mc
        }
    ));
    
    
    printf("ttbar \n");
    v_label_mc.push_back("TT");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTightIso_OS", \
        &v_rootFile_ttbar_muTau_mc, \
        &v_crossSection_ttbar_mc, \
        &v_nEvent_ttbar_mc, \
        luminosity_tau_data));
    
    
    printf("singleTop \n");
    v_label_mc.push_back("ST");
    
    v_hist_mc.push_back(getHistogram_mc( \
        histName_mc, \
        "tightTightIso_OS", \
        &v_rootFile_singleTop_muTau_mc, \
        &v_crossSection_singleTop_mc, \
        &v_nEvent_singleTop_mc, \
        luminosity_tau_data));
    
    
    std::string title_mod;
    std::string fileName_mod;
    
    if(!title)
    {
        title_mod = hist_data->GetTitle();
    }
    
    else
    {
        title_mod = title;
    }
    
    
    if(!fileName)
    {
        system("mkdir -p plots/muTau/reco");
        fileName_mod = "plots/muTau/reco/" + std::string(hist_data->GetName()) + ".pdf";
    }
    
    else
    {
        fileName_mod = fileName;
    }
    
    bool noStack = false;
    
    //noStack = true;
    //normalize = false;
    //setLogY = false;
    //hist_data = 0;
    
    //noStack = true;
    //normalize = true;
    //yMin = pow(10, -3); set_yMin = true;
    //yMax = 1.0; set_yMax = true;
    //setLogY = true;
    //hist_data = 0;
    
    Plot::plot( \
        &v_hist_mc, &v_label_mc, \
        "", \
        &v_hist_sig, &v_label_sig, \
        hist_data, "data", \
        noStack, \
        normalize, \
        xMin, set_xMin, xMax, set_xMax, \
        yMin, set_yMin, yMax, set_yMax, \
        setLogX, setLogY, \
        0, 0, \
        title_mod.c_str(), \
        fileName_mod.c_str());
}


void plotHistogram_efficiency(std::vector <const char*> v_histNumName, \
    std::vector <std::string> v_label, \
    const char *histDenName, \
    bool normalize, \
    double xMin, bool set_xMin, double xMax, bool set_xMax, \
    double yMin, bool set_yMin, double yMax, bool set_yMax, \
    bool setLogX, bool setLogY, \
    const char *title, \
    const char *fileName)
{
    TH1F *histDen;
    std::vector <TH1F*> v_hist;
    
    printf("ttbar \n");
    
    histDen = getHistogram_mc( \
        histDenName, \
        "noTauPairSelection", \
        &v_rootFile_ttbar_tauTau_mc, \
        &v_crossSection_ttbar_mc, \
        &v_nEvent_ttbar_mc, \
        luminosity_tau_data);
    
    for(int iHist = 0; iHist < v_histNumName.size(); iHist++)
    {
        v_hist.push_back(getHistogram_mc( \
            v_histNumName.at(iHist), \
            "noTauPairSelection", \
            &v_rootFile_ttbar_tauTau_mc, \
            &v_crossSection_ttbar_mc, \
            &v_nEvent_ttbar_mc, \
            luminosity_tau_data));
        
        v_hist.at(iHist)->Divide(histDen);
    }
    
    std::string title_mod;
    std::string fileName_mod;
    
    title_mod = std::string(title) + " [t #bar{t}] ";
    
    // Append process name before the extension
    fileName_mod = std::string(fileName, fileName+strlen(fileName)-4) + \
        "_ttbar" + std::string(fileName+strlen(fileName)-4, fileName+strlen(fileName));
    
    Plot::plot( \
        &v_hist, &v_label, \
        "EP", \
        0, 0, \
        0, 0, \
        true, \
        normalize, \
        xMin, set_xMin, xMax, set_xMax, \
        yMin, set_yMin, yMax, set_yMax, \
        setLogX, setLogY, \
        0, 0, \
        title_mod.c_str(), \
        fileName_mod.c_str());
}


void getRootFiles(std::vector <std::string> *v_rootFileName, \
    std::vector <TFile*> *v_rootFile)
{
    for(int iFile = 0; iFile < v_rootFileName->size(); iFile++)
    {
        //v_rootFile[iFile] = TFile::Open( \
            v_rootFileName->at(iFile).c_str(), \
            "READ");
        
        printf("Reading file: %s \n", v_rootFileName->at(iFile).c_str());
        v_rootFile->push_back(TFile::Open( \
            v_rootFileName->at(iFile).c_str(), \
            "READ"));
    }
}


TH1F* getHistogram_mc(const char *histName, \
    const char *details, \
    std::vector <TFile*> *v_rootFile, \
    std::vector <double> *v_crossSection, \
    std::vector <double> *v_nEvent, \
    double lumi_data)
{
    int nEvent_total = std::accumulate(v_nEvent->begin(), v_nEvent->end(), 0);
    double crossSection_total = std::accumulate(v_crossSection->begin(), v_crossSection->end(), 0.0);
    
    char histName_full[Common::str_len];
    
    if(strcmp(details, ""))
    {
        sprintf(histName_full, "%s_%s", histName, details);
    }
    
    else
    {
        sprintf(histName_full, "%s", histName);
    }
    
    printf("MC %s \n", histName_full);
    
    TH1F *hist = (TH1F*) v_rootFile->at(0)->Get(histName_full)->Clone();
    hist->Sumw2();
    
    for(int iFile = 0; iFile < v_rootFile->size(); iFile++)
    {
        double f = 0;
        
        TH1F *temp = (TH1F*) v_rootFile->at(iFile)->Get(histName_full)->Clone();
        
        f = v_crossSection->at(iFile) / v_nEvent->at(iFile);
        
        if(iFile == 0)
        {
            hist->Scale(f);
        }
        
        else
        {
            hist->Add(temp, f);
        }
        
        delete temp;
    }
    
    hist->Scale(lumi_data);
    
    printf("MC %s %f \n", histName_full, hist->Integral());
    
    return hist;
}


TH1F* getHistogram_data(const char *histName, \
    const char *details, \
    TFile *rootFile)
{
    char histName_full[Common::str_len];
    
    if(strcmp(details, ""))
    {
        sprintf(histName_full, "%s_%s", histName, details);
    }
    
    else
    {
        sprintf(histName_full, "%s", histName);
    }
    
    printf("Data %s \n", histName_full);
    
    TH1F *hist = (TH1F*) rootFile->Get(histName_full)->Clone();
    hist->Sumw2();
    
    printf("Data %s %f \n", histName_full, hist->Integral());
    
    return hist;
}


TH1F* getHistogram_QCD(const char *histName, \
    const char *details_sig, \
    const char *details_shape, \
    const char *details_scaleNum, \
    const char *details_scaleDen, \
    TFile *rootFile_data, \
    double lumi_data, \
    std::vector <std::vector <TFile*>* > v_rootFile_mc, \
    std::vector <std::vector <double>* > v_crossSection_mc, \
    std::vector <std::vector <double>* > v_nEvent_mc)
{
    printf("QCD estimation: \n");
    
    TH1F *h_shape;
    TH1F *h_sig;
    TH1F *h_scaleNum;
    TH1F *h_scaleDen;
    
    h_sig = getHistogram_data(histName, details_sig, rootFile_data);
    h_shape = getHistogram_data(histName, details_shape, rootFile_data);
    h_scaleNum = getHistogram_data(histName, details_scaleNum, rootFile_data);
    h_scaleDen = getHistogram_data(histName, details_scaleDen, rootFile_data);
    
    // Subtract nonQCD from Data
    for(int iBg = 0; iBg < v_rootFile_mc.size(); iBg++)
    {
        TH1F *h_temp;
        
        
        // shape region
        h_temp = getHistogram_mc( \
            histName, details_shape, \
            v_rootFile_mc[iBg], \
            v_crossSection_mc[iBg], \
            v_nEvent_mc[iBg], \
            lumi_data);
        
        h_shape->Add(h_temp, -1);
        delete h_temp;
        
        // signal region
        h_temp = getHistogram_mc( \
            histName, details_sig, \
            v_rootFile_mc[iBg], \
            v_crossSection_mc[iBg], \
            v_nEvent_mc[iBg], \
            lumi_data);
        
        h_sig->Add(h_temp, -1);
        delete h_temp;
        
        
        // ScaleNum
        h_temp = getHistogram_mc( \
            histName, details_scaleNum, \
            v_rootFile_mc[iBg], \
            v_crossSection_mc[iBg], \
            v_nEvent_mc[iBg], \
            lumi_data);
        
        h_scaleNum->Add(h_temp, -1);
        delete h_temp;
        
        
        // ScaleDen
        h_temp = getHistogram_mc( \
            histName, details_scaleDen, \
            v_rootFile_mc[iBg], \
            v_crossSection_mc[iBg], \
            v_nEvent_mc[iBg], \
            lumi_data);
        
        h_scaleDen->Add(h_temp, -1);
        delete h_temp;
    }
    
    Common::setBinLwrThreshold(h_shape, 0, 0);
    Common::setBinLwrThreshold(h_sig, 0, 0);
    Common::setBinLwrThreshold(h_scaleNum, 0, 0);
    Common::setBinLwrThreshold(h_scaleDen, 0, 0);
    
    // Subtract signal region
    h_shape->Add(h_sig, -1);
    h_scaleDen->Add(h_scaleNum, -1);
    
    Common::setBinLwrThreshold(h_shape, 0, 0);
    Common::setBinLwrThreshold(h_sig, 0, 0);
    Common::setBinLwrThreshold(h_scaleNum, 0, 0);
    Common::setBinLwrThreshold(h_scaleDen, 0, 0);
    
    // Get scale factor
    h_scaleNum->Divide(h_scaleDen);
    
    // Scale shape to signal region
    h_shape->Multiply(h_scaleNum);
    
    
    // Free memory
    delete h_sig;
    delete h_scaleNum;
    delete h_scaleDen;
    
    printf("QCD %s %f \n", histName, h_shape->Integral());
    
    return h_shape;
}


void freeMemory(std::vector <TFile*> v_rootFile)
{
}

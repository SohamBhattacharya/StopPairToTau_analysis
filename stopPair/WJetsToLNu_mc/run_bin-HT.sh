#!/bin/bash

option="$1"

preAnalysisFile="WJetsToLNu_mc_preAnalysis"
preAnalysisFile_mod="WJetsToLNu_HT-@@@_mc_preAnalysis"
preAnalysis_logFile="logs/WJetsToLNu-HT-@@@_mc_preAnalysis.log"

analysisFile="WJetsToLNu_mc_analysis"
analysisFile_mod="WJetsToLNu_HT-@@@_mc_analysis"
analysis_logFile="logs/WJetsToLNu-HT-@@@_mc_analysis.log"

declare -a HT_bins_arr=( \
    "100To200" \
    "200To400" \
    "400To600" \
    "600To800" \
    "800To1200" \
    "1200To2500" \
    "2500ToInf" )

mkdir -p logs

for iHT_bin in "${!HT_bins_arr[@]}"; do
    
    if [ "$1" = "pa" ]; then
        
        preAnalysisFile_mod_temp=`sed -e "s/@@@/${HT_bins_arr[$iHT_bin]}/g" <<< "$preAnalysisFile_mod"`
        preAnalysis_logFile_temp=`sed -e "s/@@@/${HT_bins_arr[$iHT_bin]}/g" <<< "$preAnalysis_logFile"`
        
        echo "$preAnalysisFile_mod_temp"
        echo "$preAnalysis_logFile_temp"
        
        cp "$preAnalysisFile".cc "$preAnalysisFile_mod_temp".cc
        
        sed -i -e "s/@@@/${HT_bins_arr[$iHT_bin]}/g" "$preAnalysisFile_mod_temp".cc
        
        echo "Running $preAnalysisFile_mod_temp"
        
        g++mod "$preAnalysisFile_mod_temp"
        ./"$preAnalysisFile_mod_temp" > "$preAnalysis_logFile_temp" &
    
    elif [ "$1" = "an" ]; then
        
        analysisFile_mod_temp=`sed -e "s/@@@/${HT_bins_arr[$iHT_bin]}/g" <<< "$analysisFile_mod"`
        analysis_logFile_temp=`sed -e "s/@@@/${HT_bins_arr[$iHT_bin]}/g" <<< "$analysis_logFile"`
        
        echo "$analysisFile_mod_temp"
        echo "$analysis_logFile_temp"
        
        cp "$analysisFile".cc "$analysisFile_mod_temp".cc
        
        sed -i -e "s/@@@/${HT_bins_arr[$iHT_bin]}/g" "$analysisFile_mod_temp".cc
        
        echo "Running $analysisFile_mod_temp"
        
        g++mod "$analysisFile_mod_temp"
        ./"$analysisFile_mod_temp" > "$analysis_logFile_temp" &
        
    else
        
        echo ""
        echo "Enter a valid option."
        echo "pa: pre-analysis"
        echo "an: analysis"
        
        break
        
    fi
    
    echo ""

done

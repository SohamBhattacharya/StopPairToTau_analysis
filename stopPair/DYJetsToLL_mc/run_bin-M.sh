#!/bin/bash

option="$1"

preAnalysisFile="DYJetsToLL_mc_preAnalysis"
preAnalysisFile_mod="DYJetsToLL_M-@1@_mc_preAnalysis"
preAnalysis_logFile="logs/DYJetsToLL-M-@1@_mc_preAnalysis.log"

analysisFile="DYJetsToLL_mc_analysis"
analysisFile_mod="DYJetsToLL_M-@1@_mc_analysis"
analysis_logFile="logs/DYJetsToLL-M-@1@_mc_analysis.log"

declare -a M_bins_arr=( \
    "10to50" \
    "50" )

mkdir -p logs

for iM_bin in "${!M_bins_arr[@]}"; do
    
    if [ "$1" = "pa" ]; then
        
        preAnalysisFile_mod_temp=`sed -e "s/@1@/${M_bins_arr[$iM_bin]}/g" <<< "$preAnalysisFile_mod"`
        preAnalysis_logFile_temp=`sed -e "s/@1@/${M_bins_arr[$iM_bin]}/g" <<< "$preAnalysis_logFile"`
        
        echo "$preAnalysisFile_mod_temp"
        echo "$preAnalysis_logFile_temp"
        
        cp "$preAnalysisFile".cc "$preAnalysisFile_mod_temp".cc
        
        sed -i -e "s/@1@/${M_bins_arr[$iM_bin]}/g" "$preAnalysisFile_mod_temp".cc
        
        echo "Running $preAnalysisFile_mod_temp"
        
        g++mod "$preAnalysisFile_mod_temp"
        ./"$preAnalysisFile_mod_temp" > "$preAnalysis_logFile_temp" &
    
    elif [ "$1" = "an" ]; then
        
        analysisFile_mod_temp=`sed -e "s/@1@/${M_bins_arr[$iM_bin]}/g" <<< "$analysisFile_mod"`
        analysis_logFile_temp=`sed -e "s/@1@/${M_bins_arr[$iM_bin]}/g" <<< "$analysis_logFile"`
        
        echo "$analysisFile_mod_temp"
        echo "$analysis_logFile_temp"
        
        cp "$analysisFile".cc "$analysisFile_mod_temp".cc
        
        sed -i -e "s/@1@/${M_bins_arr[$iM_bin]}/g" "$analysisFile_mod_temp".cc
        
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

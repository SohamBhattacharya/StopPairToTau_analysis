#!/bin/bash

option="$1"

preAnalysisFile="DYJetsToLL_mc_preAnalysis"
preAnalysisFile_mod="DYJetsToLL_M-@1@_HT-@2@_mc_preAnalysis"
preAnalysis_logFile="logs/DYJetsToLL-M-@1@_HT-@2@_mc_preAnalysis.log"

analysisFile="DYJetsToLL_mc_analysis"
analysisFile_mod="DYJetsToLL_M-@1@_HT-@2@_mc_analysis"
analysis_logFile="logs/DYJetsToLL-M-@1@_HT-@2@_mc_analysis.log"

declare -a M_bins_arr=( \
    "5to50" \
    "50" )

declare -a HT_bins_arr=( \
    "100to200" \
    "200to400" \
    "400to600" \
    "600toInf" )

mkdir -p logs

for M_bin in "${M_bins_arr[@]}"; do
    
    for iHT_bin in "${!HT_bins_arr[@]}"; do
        
        if [ "$1" = "pa" ]; then
            
            preAnalysisFile_mod_temp=`sed -e "s/@1@/$M_bin/g" <<< "$preAnalysisFile_mod"`
            preAnalysisFile_mod_temp=`sed -e "s/@2@/${HT_bins_arr[$iHT_bin]}/g" <<< "$preAnalysisFile_mod_temp"`
            
            preAnalysis_logFile_temp=`sed -e "s/@1@/$M_bin/g" <<< "$preAnalysis_logFile"`
            preAnalysis_logFile_temp=`sed -e "s/@2@/${HT_bins_arr[$iHT_bin]}/g" <<< "$preAnalysis_logFile_temp"`
            
            echo "$preAnalysisFile_mod_temp"
            echo "$preAnalysis_logFile_temp"
            
            cp "$preAnalysisFile".cc "$preAnalysisFile_mod_temp".cc
            
            sed -i -e "s/@1@/$M_bin/g" "$preAnalysisFile_mod_temp".cc
            sed -i -e "s/@2@/${HT_bins_arr[$iHT_bin]}/g" "$preAnalysisFile_mod_temp".cc
            
            echo "Running $preAnalysisFile_mod_temp"
            
            g++mod "$preAnalysisFile_mod_temp"
            ./"$preAnalysisFile_mod_temp" > "$preAnalysis_logFile_temp" &
        
        elif [ "$1" = "an" ]; then
            
            analysisFile_mod_temp=`sed -e "s/@1@/$M_bin/g" <<< "$analysisFile_mod"`
            analysisFile_mod_temp=`sed -e "s/@2@/${HT_bins_arr[$iHT_bin]}/g" <<< "$analysisFile_mod_temp"`
            
            analysis_logFile_temp=`sed -e "s/@1@/$M_bin/g" <<< "$analysis_logFile"`
            analysis_logFile_temp=`sed -e "s/@2@/${HT_bins_arr[$iHT_bin]}/g" <<< "$analysis_logFile_temp"`
            
            echo "$analysisFile_mod_temp"
            echo "$analysis_logFile_temp"
            
            cp "$analysisFile".cc "$analysisFile_mod_temp".cc
            
            sed -i -e "s/@1@/$M_bin/g" "$analysisFile_mod_temp".cc
            sed -i -e "s/@2@/${HT_bins_arr[$iHT_bin]}/g" "$analysisFile_mod_temp".cc
            
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
    
done

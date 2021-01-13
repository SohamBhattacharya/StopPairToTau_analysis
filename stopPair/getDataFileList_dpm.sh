#/bin/bash

#sourcePrefix="/dpm/indiacms.res.in/home/cms/store"
sourcePrefix="/cms/store/user/sobhatta"

jobID="@1@"
#sourceDir="user/sobhatta/@2@/crab_@3@"
sourceDir="$sourcePrefix/@2@/crab_@3@"
outDir="sourceFiles/@3@"
outFile="@3@_custom"

#filePrefix="root://se01.indiacms.res.in//store"
filePrefix="root://se01.indiacms.res.in"


mkdir -p $outDir


#sourceDir_temp="$sourcePrefix"/"$sourceDir"/"$jobID"
sourceDir_temp=$sourceDir"/"$jobID
outFile_temp=$outDir"/"$outFile".txt"

tempFile=$outDir/temp.txt

echo "Source: $sourceDir_temp"
echo "Output file: $outFile_temp"
echo "Temporary file: $tempFile"

#/usr/bin/rfdir "$sourceDir_temp" > "$tempFile"
#
#declare -a pathList=($(awk '{print $9}' "$tempFile"))

pathList=$(xrdfs $filePrefix ls $sourceDir_temp)

rm -f $tempFile
touch $tempFile

rm -f $outFile_temp
touch $outFile_temp

echo ""

for path in $pathList; do
    
    #if [ "$path" = "failed" ] && [ "$path" = "log" ]; then
    #    
    #    continue
    #    
    #fi
    #
    #path_temp="$sourceDir_temp"/"$path"
    #prefix_temp="$filePrefix"/"$sourceDir"/"$jobID"/"$path"
    #
    #echo "Source: $path_temp"
    #echo "Source (xrootd): $prefix_temp"
    #
    #/usr/bin/rfdir "$path_temp" > "$tempFile"
    #
    #temp="$(awk '{print $9}' "$tempFile")"
    #echo "$temp" > "$tempFile"
    #
    ## Remove failed and log directories
    #sed -i -e "/failed/d" "$tempFile"
    #sed -i -e "/log/d" "$tempFile"
    #
    ## Add prefix to each line
    #sed -i -e "s%^%$prefix_temp/%g" "$tempFile"
    #
    #cat "$tempFile" >> "$outFile_temp"
    
    
    echo "Source: $path"
    
    xrdfs $filePrefix ls $path > $tempFile
    
    # Add prefix to each line
    sed -i -e "s%^%$filePrefix/%g" $tempFile
    
    # Append to output file
    cat $tempFile | grep .root | grep -v /log | grep -v failed >> $outFile_temp
    
    
    echo ""
    
done

# Sort
cat $outFile_temp | sort -V > $tempFile
cat $tempFile > $outFile_temp

echo "Number of files: " `wc -l $outFile_temp`

rm -f $tempFile

echo ""



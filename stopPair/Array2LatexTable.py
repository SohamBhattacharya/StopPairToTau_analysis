def getLineBreak(line, d_line_break, default) :
    
    for key in d_line_break :
        
        if (key in line) :
            
            return d_line_break[key]
    
    return default


def array2LatexTable(
    arr,
    isColumnTitled = False,
    centerTable = True,
    table_caption = "",
    table_label = "",
    table_width = 1,
    headerVspace = True,
    vLine = True,
    vSpace = True,
    vSpace_str = "",
    vSpaceAfterLine_str = "",
    columnColorDict = {},
    columnHorOrientDict = {},
    rowGap = False,
    lastRowSeparate = False,
    line_break = r"\\",
    d_line_break = {"lineBreakTrigger": r"\\"},
    includeTable = False,
    adjustBox = True,
    ) :
    
    # columnColorInfo = {
    #     iCol: ["color", opacity in %], ...}
    #
    # iCol >= 0
    #
    # Example: {
    #     0: ["red", 25],
    #     5: ["blue", 10]
    # }
    
    nRow = len(arr)
    nCol = len(arr[0])
    
    vLine_str = "|" * vLine
    
    vertical_spacing =  "&"*(nCol-1) + " " + line_break + "\n"
    
    if (len(vSpace_str)) :
        
        vertical_spacing = vSpace_str + "\n"
    
    if (not len(vSpaceAfterLine_str)) :
        
        vSpaceAfterLine_str = vertical_spacing
    
    else :
        
        vSpaceAfterLine_str += "\n"
    
    horizontal_line = "\\hline" + "\n"
    
    latexTable = ""
    
    if (includeTable) :
        
        latexTable += "\\begin{table}" + "\n"
        
        if (centerTable) :
            
            latexTable += "\\centering" + "\n"
    
    if (adjustBox) :
    
        latexTable += "\\begin{adjustbox}{width=" + str(table_width) + "\\textwidth}" + "\n"
    
    latexTable += "\\begin{tabular}"
    
    columnColor = ">{\columncolor{red!25}}"
    
    #temp = "{|" + (" c |"*nCol) + "}" + "\n"
    temp = "{%s" %(vLine_str)
    
    # Columns
    for iCol in range(0, nCol) :
        
        addedCol = False
        
        if (iCol in columnColorDict or (iCol-nCol) in columnColorDict):
            
            temp += ">{\columncolor{%s!%d}} c %s" %(columnColorDict[iCol][0], columnColorDict[iCol][1], vLine_str)
            addedCol = True
        
        if (iCol in columnHorOrientDict or (iCol-nCol) in columnHorOrientDict):
            
            temp += " %s %s" %(columnHorOrientDict[iCol], vLine_str)
            addedCol = True
        
        if (not addedCol) :
            
            temp += " c %s" %(vLine_str)
    
    temp += "}" + "\n"
    latexTable += temp
    
    latexTable += horizontal_line
    latexTable += vSpaceAfterLine_str# * (headerVspace)
    
    for iRow in range(0, nRow) :
        
        tempList = arr[iRow]
        
        #if (iRow == 0 and isColumnTitled) :
        #    
        #    tempList = ["\\multicolumn{1}{%s c %s}{%s}" %(vLine_str, vLine_str, ele) for ele in arr[iRow]]
        
        row = " & \n".join(tempList)
        
        row += " " + getLineBreak(line = row, d_line_break = d_line_break, default = line_break) + "\n\n"
        
        if (iRow == 0 and isColumnTitled) :
            
            #latexTable += vertical_spacing
            latexTable += row
            latexTable += vertical_spacing * (vSpace)
            
            latexTable += horizontal_line
            latexTable += vSpaceAfterLine_str# * (vSpace)
            
        
        elif (lastRowSeparate and iRow == nRow-1) :
            
            latexTable += vertical_spacing * (vSpace)
            latexTable += horizontal_line
            
            latexTable += vertical_spacing * (vSpace)
            latexTable += row
            
        else :
            
            latexTable += row
            
            if (rowGap and iRow < nRow-1) :
                
                latexTable += vertical_spacing * (vSpace)
    
    latexTable += vertical_spacing * (headerVspace)
    latexTable += horizontal_line
    
    #latexTable += "\\end{tabular}" + "\n" + \
    #    "\\end{center}" + "\n" + \
    #    "\\caption{" + table_caption + "}" + "\n" + \
    #    "\\label{" + table_label + "}" + "\n" + \
    #    "\\end{table}" + "\n"
    
    latexTable += "\\end{tabular}" + "\n"
    
    if (adjustBox) :
        
        latexTable += "\\end{adjustbox}" + "\n"
    
    if (includeTable) :
        
        latexTable += "\\caption{" + table_caption + "}" + "\n" + \
            "\\label{" + table_label + "}" + "\n" + \
            "\\end{table}" + "\n"
    
    return latexTable

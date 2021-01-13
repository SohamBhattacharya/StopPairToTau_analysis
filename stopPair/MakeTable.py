import numpy


def makeTable( \
    column_titles, \
    cut_flow_fileNames, \
    cut_flow_str_fileName, \
    crossSection_fileNames) :
    
    cut_flow_data = [[numpy.loadtxt(f, usecols = [1], delimiter = "@@@") for f in s] for s in cut_flow_fileNames]
    #print cut_flow_data
    
    
    cut_flow_str = numpy.loadtxt(cut_flow_str_fileName, delimiter = "@@@", dtype = str)
    # print cut_flow_str
    
    
    crossSection_data = [numpy.loadtxt(f, ndmin = 1) for f in crossSection_fileNames]
    #print crossSection_data
    
    table = []
    
    
    # Add column titles
    table.append(column_titles)
    
    
    # Add row titles
    for iCut in range(0, cut_flow_str.shape[0]) :
        
        table.append([cut_flow_str[iCut]])
    
    
    # Add table entries
    for iCut in range(0, cut_flow_str.shape[0]) :
        
        row = []
        
        #print "Cut", iCut, ":"
        
        for iSet in range(0, len(cut_flow_fileNames)) :
            
            val = [crossSection_data[iSet][iFile] * cut_flow_data[iSet][iFile][iCut] / cut_flow_data[iSet][iFile][0] \
                for iFile in range(0, len(cut_flow_fileNames[iSet]))]
            
            val = sum(val)
            #print val
            row.append(str("%0.4f" % val))
        
        table[iCut+1].extend(row)
    
    #print table
    
    return table

import numpy


l_info = []


# 2016
massPointFile = "output_genParam/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/massPointInfo.txt"
outfile = "output_genParam/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"
l_info.append([massPointFile, outfile])

massPointFile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/massPointInfo.txt"
outfile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"
l_info.append([massPointFile, outfile])

massPointFile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/massPointInfo.txt"
outfile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16/XSweightInfo.txt"
l_info.append([massPointFile, outfile])



# 2017
#massPointFile = "output_genParam/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/massPointInfo.txt"
#outfile = "output_genParam/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/XSweightInfo.txt"
#l_info.append([massPointFile, outfile])
#
#massPointFile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/massPointInfo.txt"
#outfile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/XSweightInfo.txt"
#l_info.append([massPointFile, outfile])
#
#massPointFile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/massPointInfo.txt"
#outfile = "output_genParam/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17/XSweightInfo.txt"
#l_info.append([massPointFile, outfile])


XSfile = "stopPair_XS.txt"


for iInfo in l_info :
    
    massPointFile = iInfo[0]
    outfile = iInfo[1]
    
    print "massPointFile:", massPointFile
    print "outfile:", outfile
    print "XSfile:", XSfile
    
    
    massPointInfo = numpy.loadtxt(massPointFile, delimiter = ",")
    XSinfo = numpy.loadtxt(XSfile, delimiter = ",", dtype = float)
    
    XSweightInfo = []
    
    
    for iMass in range(0, massPointInfo.shape[0]) :
        
        stop1_m = massPointInfo[iMass, 0]
        neutralino_m = massPointInfo[iMass, 1]
        nEvent = massPointInfo[iMass, 2]
        
        if (stop1_m > 1500 or neutralino_m > 650) :
            
            continue
        
        # Find position of the mass point in the XS list
        pos = numpy.where(XSinfo[:, 0] == stop1_m)[0][0]
        
        xs = XSinfo[pos, 1]
        xs_uncertainty = XSinfo[pos, 2]
        
        # Compute weight
        weight = xs / float(nEvent)
        
        temp = [
            str(int(stop1_m)),
            str(int(neutralino_m)),
            str(int(nEvent)),
            str(xs),
            str(xs_uncertainty),
            str(weight)
        ]
        
        # Fill the list
        XSweightInfo.append(temp)
    
    
    #print XSweightInfo[0]
    
    # Write output file
    temp_strList = [",".join(ele) for ele in XSweightInfo]
    output_str = "\n".join(temp_strList) + "\n"
    
    
    with open(outfile, "w") as f :
        
        temp_str = ("# "
            "stop1_m, "
            "neutralino_m, "
            "nEvent, "
            "XS [pb], "
            "% uncertainty, "
            "weight (XS/nEvent) [pb^-1]"
            "\n")
        
        f.write(temp_str)
        f.write(output_str)
        

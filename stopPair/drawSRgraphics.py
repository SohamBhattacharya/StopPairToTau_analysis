import matplotlib.pyplot
import numpy
import os

matplotlib.pyplot.rc("text", usetex = True)
matplotlib.rcParams["text.latex.preamble"] += [r"\usepackage{amsmath}"]
matplotlib.rcParams["text.latex.preamble"] += [r"\usepackage{slashed}"]

vertical_space = 10
horizontal_space = 10

fig = matplotlib.pyplot.figure(figsize = [9, 7])

xMax = 350
yMax = 120

xIntervals = [50, 200] # MET
yIntervals = [0, 40, 80] # mT2
zIntervals = [100, 300, 700] # HT


vertical_shift = -2.5


l_SR_merge = [
    # SR bins to merge
    [4, 5],
    [10, 11],
    [16, 17],
]

# N.B. These are the bin numbers after merging
l_shiftBinsUp = [4, 9, 14]
l_shiftBinsDown = [5, 10, 15]

#l_SR_merge = [
#    # SR bins to merge
#    [4, 5, 6],
#    [10, 11, 12],
#    [16, 17, 18],
#]


iSR = 0

for iY in range(0, len(yIntervals)) :
    
    for iX in range(0, len(xIntervals)) :
        
        for iZ in range(0, len(zIntervals)) :
            
            iSR = len(xIntervals)*len(zIntervals)*iY + \
                len(zIntervals)*iX + \
                iZ + \
                1
            
            iSR_mod = iSR
            iZ_upr = iZ+1
            
            skip = False
            
            for iGroup in range(0, len(l_SR_merge)) :
                
                if (iSR in l_SR_merge[iGroup][1:]) :
                    
                    skip = True
                    break
                
                if (l_SR_merge[iGroup][0] == iSR) :
                    
                    iZ_upr += len(l_SR_merge[iGroup][1:])
                
                if (l_SR_merge[iGroup][0] < iSR) :
                    
                    iSR_mod -= len(l_SR_merge[iGroup][1:])
            
            if (skip) :
                
                continue
            
            iSR = iSR_mod
            
            print iSR, xIntervals[iX], yIntervals[iY], zIntervals[iZ]
            
            print "iSR %d, iZ %d, iZ_upr %d" %(iSR, iZ, iZ_upr)
            
            if (iZ < len(zIntervals)-1 and iZ_upr < len(zIntervals)) :
                
                binStr = (
                    #r"$ \boldsymbol{%d:\ %d \leq H^{\tau_{h}\tau_{h}jet}_{T} < %d} $"
                    r"$ \boldsymbol{%d:\ %d \leq H_{\rm{T}} < %d} $"
                    % (iSR, zIntervals[iZ], zIntervals[iZ_upr])
                )
            
            else :
                
                binStr = (
                    #r"$ \boldsymbol{%d:\ H^{\tau_{h}\tau_{h}jet}_{T} \geq %d} $"
                    r"$ \boldsymbol{%d:\ H_{\rm{T}} \geq %d} $"
                    % (iSR, zIntervals[iZ])
                )
            
            print "binStr:", binStr
            
            vertical_space_mod = vertical_space
            
            if (iSR in l_shiftBinsUp) :
                
                vertical_space_mod *= 1.5
            
            #elif (iSR in l_shiftBinsDown) :
            #    
            #    vertical_space_mod *= 0.83
            
            posX = xIntervals[iX] + horizontal_space
            #posY = yIntervals[iY] + (len(zIntervals)-iZ)*vertical_space
            posY = vertical_shift + yIntervals[iY] + (iZ+1)*vertical_space_mod
            
            print binStr
            
            matplotlib.pyplot.text(posX, posY, binStr, fontsize = 20)
            
            ##### Needed for bin-merging
            #iZ = iZ_mod
            #####

matplotlib.pyplot.xticks(xIntervals, fontsize = 25)
matplotlib.pyplot.yticks(yIntervals, fontsize = 25)

matplotlib.pyplot.xlim(xmin = 0, xmax = xMax)
matplotlib.pyplot.ylim(ymin = 0, ymax = yMax)

matplotlib.pyplot.xlabel(r"$ \boldsymbol{p^{\text{\rm{miss}}}_{\rm{T}}} $ [GeV]", fontsize = 30)
matplotlib.pyplot.ylabel(r"$ \boldsymbol{m_{\rm{T2}}} $ [GeV]", fontsize = 30)

#matplotlib.pyplot.title("Search region binning", fontsize = 25)
#matplotlib.pyplot.title(r"$ H_{T} $ [GeV]", fontsize = 25, loc = "right")
titleText = matplotlib.pyplot.title(r"Search region binning", fontsize = 25)

matplotlib.pyplot.text(
    xIntervals[-1]+(xMax-xIntervals[-1])/1.9,
    yIntervals[0] + 1,
    r"[$ \boldsymbol{H_{\rm{T}}} $ in GeV]",
    fontsize = 20
)

matplotlib.pyplot.grid(True)
matplotlib.pyplot.tight_layout()


matplotlib.pyplot.savefig("SRBgraphics.pdf")
#matplotlib.pyplot.savefig("DYCRgraphics.pdf")
matplotlib.pyplot.close(fig)


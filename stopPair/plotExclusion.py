import array
import copy
import datetime
import matplotlib
import matplotlib.pyplot
import numpy
import os
import scipy
import scipy.interpolate
#import root_numpy

import ROOT

import Common

import CMS_lumi
import tdrstyle


noPrelim = False
noPrelimStr = "_noPrelim"*(noPrelim)

extraSuffix = ""
#extraSuffix = "_test"

#drawObserved = True
drawObserved = False

nInterpolate = 150
#####nInterpolate_obs = 200

NRGBs = 5
NCont = 255


# PAPER version
#nSmooth_central_obs = 10
#nSmooth_central_exp = 5
#
#nSmooth_1sig_obs = 1
#nSmooth_1sig_exp = 5


# PAS version
#nSmooth_central_obs = 20
#nSmooth_central_exp = 5
#
#nSmooth_1sig_obs = 1
#nSmooth_1sig_exp = 5


# TEST!!!
nSmooth_central_obs = 5
nSmooth_central_exp = 5

nSmooth_1sig_obs = 5
nSmooth_1sig_exp = 5

#l_stops = [0.00, 0.34, 0.61, 0.84, 1.00]
l_stops = [0.00, 0.15, 0.27, 0.55, 1.00]
#l_stops = [0.00, 0.30, 0.37, 0.67, 1.00]
l_red   = [0.50, 0.50, 1.00, 1.00, 1.00]
l_green = [0.50, 1.00, 1.00, 0.60, 0.50]
l_blue  = [1.00, 1.00, 0.50, 0.40, 0.50]

isSmooth = True


class LimitInfo :
    
    def __init__(self) :
        
        self.l_stop1_m = []
        self.l_neutralino1_m = []
        self.l_xs = []
        self.l_xs_uncPercent = []
        
        self.l_observedLimit = []
        self.l_observedLimit_1sigLwr = []
        self.l_observedLimit_1sigUpr = []
        
        self.l_expectedLimit = []
        self.l_expectedLimit_1sigLwr = []
        self.l_expectedLimit_1sigUpr = []
        self.l_expectedLimit_2sigLwr = []
        self.l_expectedLimit_2sigUpr = []
        
        self.fInter_xs = 0
        self.fInter_xs_upr = 0
        self.fInter_xs_lwr = 0
        
        self.lineColor = 1
        self.lineStyle = 1
        
        self.label = ""


def getContourListFromHist(hist, contourVal, nSmooth = 0) :
    
    #print "*****", hist.GetNbinsX(), hist.GetNbinsY()
    
    #current_pad = ROOT.gROOT.GetSelectedPad()
    
    if (nSmooth > 0) :
        
        #hist.Smooth(1, "k5a")
        
        for iSmooth in range(0, nSmooth) :
            
            hist.Smooth(1, "k5b")
            hist.Smooth(1, "kba")
    
    canvas_temp = ROOT.TCanvas("canvas_temp", "canvas_temp")
    canvas_temp.cd()
    
    l_contourVal = [contourVal]
    
    hist_temp = hist.Clone()
    ROOT.SetOwnership(hist_temp, 0)
    
    # Set contours
    hist_temp.SetContour(len(l_contourVal), array.array("d", l_contourVal))
    hist_temp.Draw("CONT Z LIST")
    canvas_temp.Update()
    
    # Get contours
    ROOT.gROOT.GetListOfSpecials().Print()
    l_contour = ROOT.gROOT.GetListOfSpecials().FindObject("contours").Clone()
    
    if (not l_contour.GetEntries()) :
        
        print "Error: No contours found."
        exit(1)
    
    canvas_temp.Clear()
    canvas_temp.Close()
    
    # Switch back to the original pad
    #current_pad.cd()
    
    return l_contour.At(0)


def getContourListFromGraph(graph, contourVal, nSmooth = 0) :
    
    return getContourListFromHist(graph.GetHistogram().Clone(), contourVal, nSmooth)


def clearDiagonal(graph, replace = False, replaceVal = -9999) :
    
    #d_diag = {}
    #
    #for iPoint in range(0, graph.GetN()) :
    #    
    #    x = graph.GetX()[iPoint]
    #    y = graph.GetY()[iPoint]
    #    
    #    if (x not in d_diag) :
    #        
    #        d_diag[int(x)] = [y]
    #    
    #    else :
    #        
    #        d_diag[int(x)].append(y)
    
    iPoint = 0
    
    while(iPoint < graph.GetN()) :
        
        isRemoved = False
        
        x = graph.GetX()[iPoint]
        y = graph.GetY()[iPoint]
        
        if (abs(x-y) < 110 and not replace) :
            
            isRemoved = True
        
        #if (x < 400 and int(x) in d_diag and len(d_diag[int(x)]) > 1) :
        #    
        #    print x, y
        #    isRemoved = True
        
        if (isRemoved) :
            
            if (replace) :
                
                graph.SetPoint(iPoint, x, y, replaceVal)
            
            else :
                
                graph.RemovePoint(iPoint)
                iPoint = -1
        
        iPoint += 1


def plot(limitInfo, era, outDir, label, lumiText, suffix) :
    
    l_xs = limitInfo.l_xs
    l_stop1_m = limitInfo.l_stop1_m
    l_neutralino1_m = limitInfo.l_neutralino1_m
    
    l_observedLimit = copy.deepcopy(limitInfo.l_observedLimit)
    l_observedLimit_1sigLwr = copy.deepcopy(limitInfo.l_observedLimit_1sigLwr)
    l_observedLimit_1sigUpr = copy.deepcopy(limitInfo.l_observedLimit_1sigUpr)
    
    l_expectedLimit = copy.deepcopy(limitInfo.l_expectedLimit)
    l_expectedLimit_1sigLwr = copy.deepcopy(limitInfo.l_expectedLimit_1sigLwr)
    l_expectedLimit_1sigUpr = copy.deepcopy(limitInfo.l_expectedLimit_1sigUpr)
    l_expectedLimit_2sigLwr = copy.deepcopy(limitInfo.l_expectedLimit_2sigLwr)
    l_expectedLimit_2sigUpr = copy.deepcopy(limitInfo.l_expectedLimit_2sigUpr)
    
    # Exclude the problematic low mass points
    #for iPoint in range(0, len(l_observedLimit)) :
    #    
    #    if (abs(l_observedLimit[iPoint] - l_expectedLimit[iPoint]) > 100) :
    #        
    #        l_observedLimit[iPoint] = 0
    
    #
    graph_observedLimit = ROOT.TGraph2D(label+"_obs", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_observedLimit))
    graph_observedLimit_1sigLwr = ROOT.TGraph2D(label+"_obs1lwr", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_observedLimit_1sigLwr))
    graph_observedLimit_1sigUpr = ROOT.TGraph2D(label+"_obs1upr", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_observedLimit_1sigUpr))
    
    graph_expectedLimit = ROOT.TGraph2D(label+"_exp", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_expectedLimit))
    graph_expectedLimit_1sigLwr = ROOT.TGraph2D(label+"_exp1lwr", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_expectedLimit_1sigLwr))
    graph_expectedLimit_1sigUpr = ROOT.TGraph2D(label+"_exp1upr", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_expectedLimit_1sigUpr))
    graph_expectedLimit_2sigLwr = ROOT.TGraph2D(label+"_exp2lwr", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_expectedLimit_2sigLwr))
    graph_expectedLimit_2sigUpr = ROOT.TGraph2D(label+"_exp2upr", label, len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_expectedLimit_2sigUpr))
    
    
    # Revert back to the original values
    #l_observedLimit = copy.deepcopy(limitInfo.l_observedLimit)
    
    
    for iMass in range(0, len(l_stop1_m)) :
        
        if ([l_stop1_m[iMass], l_neutralino1_m[iMass]] not in [[1000, 1]]) :
            
            continue
        
        print l_stop1_m[iMass], l_neutralino1_m[iMass], l_observedLimit[iMass]
    
    
    graph_observedLimit.SetNpx(nInterpolate)
    graph_observedLimit.SetNpy(nInterpolate)
    
    graph_observedLimit_1sigLwr.SetNpx(nInterpolate)
    graph_observedLimit_1sigLwr.SetNpy(nInterpolate)
    
    graph_observedLimit_1sigUpr.SetNpx(nInterpolate)
    graph_observedLimit_1sigUpr.SetNpy(nInterpolate)
    
    
    graph_expectedLimit.SetNpx(nInterpolate)
    graph_expectedLimit.SetNpy(nInterpolate)
    
    graph_expectedLimit_1sigLwr.SetNpx(nInterpolate)
    graph_expectedLimit_1sigLwr.SetNpy(nInterpolate)
    
    graph_expectedLimit_1sigUpr.SetNpx(nInterpolate)
    graph_expectedLimit_1sigUpr.SetNpy(nInterpolate)
    
    graph_expectedLimit_2sigLwr.SetNpx(nInterpolate)
    graph_expectedLimit_2sigLwr.SetNpy(nInterpolate)
    
    graph_expectedLimit_2sigUpr.SetNpx(nInterpolate)
    graph_expectedLimit_2sigUpr.SetNpy(nInterpolate)
    
    
    #graph_observedLimit_1sigUpr = graph_observedLimit.Clone()
    #graph_observedLimit_1sigUpr.SetName(label+"_obs1upr")
    #graph_observedLimit_1sigUpr.SetTitle(label)
    #
    #iPoint = 0
    #
    #print "*"*50, graph_observedLimit_1sigUpr.GetN()
    #
    #while(iPoint < graph_observedLimit_1sigUpr.GetN()) :
    #    
    #    x = graph_observedLimit_1sigUpr.GetX()[iPoint]
    #    y = graph_observedLimit_1sigUpr.GetY()[iPoint]
    #    z = graph_observedLimit_1sigUpr.GetZ()[iPoint]
    #    
    #    #print x, y, z
    #    
    #    #print limitInfo.fInter_xs(x), limitInfo.fInter_xs_lwr(x)
    #    
    #    graph_observedLimit_1sigUpr.SetPoint(
    #        iPoint,
    #        x, y,
    #        z * limitInfo.fInter_xs(x) / limitInfo.fInter_xs_lwr(x)
    #    )
    #    
    #    iPoint += 1
    
    
    # Observed
    graph_observedLimit.Print()
    #print l_observedLimit
    #print graph_observedLimit.GetMinimum(), graph_observedLimit.GetMaximum()
    #print ROOT.TMath.MinElement(graph_observedLimit.GetN(), graph_observedLimit.GetZ()), ROOT.TMath.MaxElement(graph_observedLimit.GetN(), graph_observedLimit.GetZ())
    #print graph_expectedLimit.GetMinimum(), graph_expectedLimit.GetMaximum()
    #print graph_observedLimit.GetXmax(), graph_observedLimit.GetYmax()
    #print graph_observedLimit.GetContourList(2.0)
    #print graph_observedLimit.GetZ()
    #print graph_observedLimit.GetN(), len(l_observedLimit)
    
    #for i in range(0, graph_observedLimit.GetN()) :
    #    
    #    print "%0.2f, " %(graph_observedLimit.GetZ()[i]-limitInfo.l_observedLimit[i]),
    #    
    #print ""
    
    contourList_observedLimit = getContourListFromGraph(graph_observedLimit, 1.0, nSmooth = nSmooth_central_obs)
    #contourList_observedLimit = graph_observedLimit.GetContourList(1.0)
    #contourList_observedLimit = graph_expectedLimit.GetContourList(1.0)
    #print graph_observedLimit.GetContourList(1.0)
    #print graph_observedLimit
    #print graph_observedLimit.GetN()
    print "contourList_observedLimit: No. of contours: %d \n" %(contourList_observedLimit.GetSize())
    
    contour_observedLimit = contourList_observedLimit[0]
    #contour_observedLimit = contourList_observedLimit.First()
    
    clearDiagonal(contour_observedLimit)
    
    contour_observedLimit.SetMarkerColor(1)
    contour_observedLimit.SetMarkerSize(0)
    contour_observedLimit.SetLineColor(1)
    contour_observedLimit.SetLineWidth(3)
    contour_observedLimit.SetLineStyle(1)
    contour_observedLimit.SetFillColor(0)
    
    
    # Observed -1 sigma
    #clearDiagonal(graph_observedLimit_1sigLwr, replace = True, replaceVal = 100)
    contourList_observedLimit_1sigLwr = getContourListFromGraph(graph_observedLimit_1sigLwr, 1.0, nSmooth = nSmooth_1sig_obs)
    #contourList_observedLimit_1sigLwr = graph_observedLimit_1sigLwr.GetContourList(1.0)
    
    print "contourList_observedLimit_1sigLwr: No. of contours: %d \n" %(contourList_observedLimit_1sigLwr.GetSize())
    
    contour_observedLimit_1sigLwr = contourList_observedLimit_1sigLwr[0]
    #contour_observedLimit_1sigLwr = contourList_observedLimit_1sigLwr.First()
    
    clearDiagonal(contour_observedLimit_1sigLwr)
    
    contour_observedLimit_1sigLwr.SetMarkerColor(1)
    contour_observedLimit_1sigLwr.SetMarkerSize(0)
    contour_observedLimit_1sigLwr.SetLineColor(1)
    contour_observedLimit_1sigLwr.SetLineWidth(3)
    contour_observedLimit_1sigLwr.SetLineStyle(2)
    contour_observedLimit_1sigLwr.SetFillColor(0)
    
    
    # Observed +1 sigma
    #clearDiagonal(graph_observedLimit_1sigUpr, replace = True, replaceVal = 100)
    contourList_observedLimit_1sigUpr = getContourListFromGraph(graph_observedLimit_1sigUpr, 1.0, nSmooth = nSmooth_1sig_obs)
    #contourList_observedLimit_1sigUpr = graph_observedLimit_1sigUpr.GetContourList(1.0)
    
    print "contourList_observedLimit_1sigUpr: No. of contours: %d \n" %(contourList_observedLimit_1sigUpr.GetSize())
    
    contour_observedLimit_1sigUpr = contourList_observedLimit_1sigUpr[0]
    #contour_observedLimit_1sigUpr = contourList_observedLimit_1sigUpr.First()
    
    clearDiagonal(contour_observedLimit_1sigUpr)
    
    contour_observedLimit_1sigUpr.SetMarkerColor(1)
    contour_observedLimit_1sigUpr.SetMarkerSize(0)
    contour_observedLimit_1sigUpr.SetLineColor(1)
    contour_observedLimit_1sigUpr.SetLineWidth(3)
    contour_observedLimit_1sigUpr.SetLineStyle(2)
    contour_observedLimit_1sigUpr.SetFillColor(0)
    
    
    #removeIntersection(contour_observedLimit_1sigLwr, contour_observedLimit_1sigUpr)
    
    
    # Expected
    contourList_expectedLimit = getContourListFromGraph(graph_expectedLimit, 1.0, nSmooth = nSmooth_central_exp)
    #contourList_expectedLimit = graph_expectedLimit.GetContourList(1.0)
    print "No. of contours: %d \n" %(contourList_expectedLimit.GetSize())
    
    contour_expectedLimit = contourList_expectedLimit[0]
    #contour_expectedLimit = contourList_expectedLimit.First()
    
    clearDiagonal(contour_expectedLimit)
    
    contour_expectedLimit.SetMarkerColor(ROOT.kRed+1)
    contour_expectedLimit.SetMarkerSize(0)
    contour_expectedLimit.SetLineColor(ROOT.kRed+1)
    contour_expectedLimit.SetLineWidth(3)
    contour_expectedLimit.SetLineStyle(1)
    contour_expectedLimit.SetFillColor(0)
    
    
    # Expected -1 sigma
    contourList_expectedLimit_1sigLwr = getContourListFromGraph(graph_expectedLimit_1sigLwr, 1.0, nSmooth = nSmooth_1sig_exp)
    #contourList_expectedLimit_1sigLwr = graph_expectedLimit_1sigLwr.GetContourList(1.0)
    print "No. of contours: %d \n" %(contourList_expectedLimit_1sigLwr.GetSize())
    
    contour_expectedLimit_1sigLwr = contourList_expectedLimit_1sigLwr[0]
    #contour_expectedLimit_1sigLwr = contourList_expectedLimit_1sigLwr.First()
    
    clearDiagonal(contour_expectedLimit_1sigLwr)
    
    contour_expectedLimit_1sigLwr.SetMarkerColor(ROOT.kRed+1)
    contour_expectedLimit_1sigLwr.SetMarkerSize(0)
    contour_expectedLimit_1sigLwr.SetLineColor(ROOT.kRed+1)
    contour_expectedLimit_1sigLwr.SetLineWidth(3)
    contour_expectedLimit_1sigLwr.SetLineStyle(2)
    contour_expectedLimit_1sigLwr.SetFillColor(0)
    
    
    # Expected +1 sigma
    contourList_expectedLimit_1sigUpr = getContourListFromGraph(graph_expectedLimit_1sigUpr, 1.0, nSmooth = nSmooth_1sig_exp)
    #contourList_expectedLimit_1sigUpr = graph_expectedLimit_1sigUpr.GetContourList(1.0)
    print "No. of contours: %d \n" %(contourList_expectedLimit_1sigUpr.GetSize())
    
    contour_expectedLimit_1sigUpr = contourList_expectedLimit_1sigUpr[0]
    #contour_expectedLimit_1sigUpr = contourList_expectedLimit_1sigUpr.First()
    
    clearDiagonal(contour_expectedLimit_1sigUpr)
    
    contour_expectedLimit_1sigUpr.SetMarkerColor(ROOT.kRed+1)
    contour_expectedLimit_1sigUpr.SetMarkerSize(0)
    contour_expectedLimit_1sigUpr.SetLineColor(ROOT.kRed+1)
    contour_expectedLimit_1sigUpr.SetLineWidth(3)
    contour_expectedLimit_1sigUpr.SetLineStyle(2)
    contour_expectedLimit_1sigUpr.SetFillColor(0)
    
    
    
    ##############################################
    #################### Plot ####################
    ##############################################
    
    ROOT.gStyle.SetOptStat(0)
    
    tdrstyle.setTDRStyle()
    
    if (isSmooth) :
        
        ROOT.TColor.CreateGradientColorTable(
            NRGBs,
            numpy.array(l_stops),
            numpy.array(l_red),
            numpy.array(l_green),
            numpy.array(l_blue),
            NCont
        )
        
        ROOT.gStyle.SetNumberContours(NCont)
    
    #canvas = ROOT.TCanvas("canvas", "canvas", 400, 400)
    canvas = ROOT.TCanvas("canvas", "canvas", 1000, 800)
    
    canvas.SetLeftMargin(0.125)
    canvas.SetRightMargin(0.17)
    #canvas.SetTopMargin(0.05)
    canvas.SetBottomMargin(0.12)
    
    #legend = ROOT.TLegend(0.125, 0.53, 0.83, 0.95)
    legend = ROOT.TLegend(0.125, 0.65, 0.83, 0.95)
    #legend.SetFillStyle(0)
    legend.SetBorderSize(1)
    #legend.SetTextSize(0.045)
    legend.SetTextSize(0.035)
    legend.SetNColumns(2)
    #legend.SetTextAlign(12)
    
    # VERY important
    # Otherwise, seg-faults when accessing GetListOfPrimitives(), etc.
    ROOT.SetOwnership(legend, 0)
    
    #legend.SetMargin(0.5)
    
    #legend.SetHeader(
    #    "#lower[0.35]{#splitline{" +
    #        "#splitline{" +
    #            " "*27 +
    #            "#scale[1.3]{#font[22]{%s}}" %(label) +
    #        "}{" +
    #            "#scale[1.0]{#font[22]{" +
    #                "pp#rightarrow#tilde{t}_{1}#tilde{t}_{1}, " +
    #                "#tilde{t}_{1}#rightarrowb#tilde{#chi}^{#pm}_{1}, " +
    #                "#tilde{#chi}^{#pm}_{1}#rightarrow#tilde{#tau}^{#pm}_{1}#nu (50%) or #tilde{#nu}_{#tau}#tau^{#pm} (50%), " +
    #                "#tilde{#tau}^{#pm}_{1}#rightarrow#tau^{#pm}#tilde{#chi}^{0}_{1}, " +
    #                "#tilde{#nu}_{#tau}#rightarrow#nu#tilde{#chi}^{0}_{1} " +
    #            "}}" +
    #        "}" +
    #    "}{" +
    #        "#scale[1.0]{#font[22]{" +
    #            " "*7 +
    #            "m_{#tilde{#chi}^{#pm}_{1}}#minus m_{#tilde{#chi}^{0}_{1}} = 0.5 (m_{#tilde{t}_{1}}#minus m_{#tilde{#chi}^{0}_{1}}),  " +
    #            "m_{#tilde{#tau}^{#pm}_{1}}#minus m_{#tilde{#chi}^{0}_{1}} = x (m_{#tilde{#chi}^{#pm}_{1}}#minus m_{#tilde{#chi}^{0}_{1}}),  " +
    #            "m_{#tilde{#nu}_{#tau}} = m_{#tilde{#tau}^{#pm}_{1}}" +
    #        "}}" +
    #    "}}"
    #)
    
    #legend.SetHeader(
    #    "#lower[0.435]{#splitline{" +
    #        "#splitline{" +
    #            " "*22 +
    #            "#scale[1.35]{#font[22]{%s}}" %(label) +
    #        "}{" +
    #            "#scale[1.2]{#font[22]{#splitline{#lower[-0.05]{" +
    #                "pp#rightarrow#tilde{t}_{1}#tilde{t}_{1},  " +
    #                "#tilde{t}_{1}#rightarrowb#tilde{#chi}^{+}_{1},  " +
    #                "#tilde{#chi}^{+}_{1}#rightarrow#tilde{#tau}^{+}_{1}#nu (50%) or #tilde{#nu}_{#tau}#tau^{+} (50%)" +
    #            "}}{#lower[-0.05]{" +
    #                " "*11 +
    #                "#tilde{#tau}^{+}_{1}#rightarrow#tau^{+}#tilde{#chi}^{0}_{1},  " +
    #                "#tilde{#nu}_{#tau}#rightarrow#nu#tilde{#chi}^{0}_{1} " +
    #            "}}}}" +
    #        "}" +
    #    "}{" +
    #        "#scale[1.2]{#font[22]{" +
    #            "#splitline{#lower[-0.06]{" +
    #                " "*20 +
    #                "m_{#tilde{#chi}^{+}_{1}}#minus m_{#tilde{#chi}^{0}_{1}} = 0.5 (m_{#tilde{t}_{1}}#minus m_{#tilde{#chi}^{0}_{1}}) " +
    #            "}}{#lower[-0.05]{" +
    #                " "*12 +
    #                "m_{#tilde{#tau}^{+}_{1}}#minus m_{#tilde{#chi}^{0}_{1}} = x (m_{#tilde{#chi}^{+}_{1}}#minus m_{#tilde{#chi}^{0}_{1}}),   " +
    #                "m_{#tilde{#nu}_{#tau}} = m_{#tilde{#tau}^{+}_{1}}" +
    #            "}}" +
    #        "}}" +
    #    "}}"
    #)
    
    legend.SetHeader(
        "#lower[0.65]{#splitline{" +
            "#splitline{" +
                " "*29 +
                "#scale[1.45]{#font[22]{%s}}" %(label) +
            "}{" +
                " "*5 +
                "#scale[1.2]{#font[22]{#splitline{#lower[-0.05]{" +
                    "pp#rightarrow#tilde{t}_{1}#tilde{t}_{1},  " +
                    "#tilde{t}_{1}#rightarrowb#tilde{#chi}^{+}_{1},  " +
                    "#tilde{#chi}^{+}_{1}#rightarrow#tilde{#tau}^{+}_{1}#nu (50%) or #tilde{#nu}_{#tau}#tau^{+} (50%)" +
                "}}{#lower[-0.05]{" +
                    " "*13 +
                    "#tilde{#tau}^{+}_{1}#rightarrow#tau^{+}#tilde{#chi}^{0}_{1},  " +
                    "#tilde{#nu}_{#tau}#rightarrow#nu#tilde{#chi}^{0}_{1} " +
                "}}}}" +
            "}" +
        "}{" +
            "#scale[1.2]{#font[22]{" +
                "#lower[-0.05]{" +
                    #" "*20 +
                    "m_{#tilde{#chi}^{+}_{1}}#minus m_{#tilde{#chi}^{0}_{1}} = 0.5 (m_{#tilde{t}_{1}}#minus m_{#tilde{#chi}^{0}_{1}}),  " +
                "}#lower[-0.05]{" +
                    #" "*12 +
                    "m_{#tilde{#tau}^{+}_{1}}#minus m_{#tilde{#chi}^{0}_{1}} = x (m_{#tilde{#chi}^{+}_{1}}#minus m_{#tilde{#chi}^{0}_{1}}),   " +
                    "m_{#tilde{#nu}_{#tau}} = m_{#tilde{#tau}^{+}_{1}}" +
                "}" +
            "}}" +
        "}}"
    )
    
    legendHeader = legend.GetListOfPrimitives().First()
    legendHeader.SetTextAlign(22)
    #legendHeader.SetTextSize(0.035)
    legendHeader.SetTextSize(0.0275)
    
    
    # Blank entries required fot shifting the true entries lower
    # Otherwise the header overlaps with the entries
    legend.AddEntry(0, "", "")
    legend.AddEntry(0, "", "")
    legend.AddEntry(0, "", "")
    legend.AddEntry(0, "", "")
    legend.AddEntry(0, "", "")
    legend.AddEntry(0, "", "")
    
    #################### x-sec #################### 
    
    if (isSmooth) :
        
        if (drawObserved) :
            
            l_xsLimit = [l_xs[iMass] * l_observedLimit[iMass] for iMass in range(0, len(l_stop1_m))]
        
        else :
            
            l_xsLimit = [l_xs[iMass] * l_expectedLimit[iMass] for iMass in range(0, len(l_stop1_m))]
    
    else :
        
        l_xsLimit = [l_observedLimit[iMass] for iMass in range(0, len(l_stop1_m))]
    
    #l_xsLimit = [l_xs[iMass] * l_expectedLimit[iMass] for iMass in range(0, len(l_stop1_m))]
    
    graph_xs = ROOT.TGraph2D("xs", "xs", len(l_stop1_m), array.array("d", l_stop1_m), array.array("d", l_neutralino1_m), array.array("d", l_xsLimit))
    
    if (isSmooth) :
        
        graph_xs.SetNpx(nInterpolate)
        graph_xs.SetNpy(nInterpolate)
    
    
    h2_xs = graph_xs.GetHistogram().Clone()
    
    #####
    #h2_axisRange = ROOT.TH2F("h2_axisRange", "h2_axisRange", 1, 200, 1500, 1, 1, 850)
    #h2_axisRange = ROOT.TH2F("h2_axisRange", "h2_axisRange", 1, 200, 1500, 1, 1, 1000)
    h2_axisRange = ROOT.TH2F("h2_axisRange", "h2_axisRange", 1, 200, 1500, 1, 1, 800)
    
    h2_axisRange.SetTitle("Exclusion (%s) (%s)" %(label, era))
    h2_axisRange.GetXaxis().SetTitle("m_{#tilde{t}_{1}} [GeV]")
    h2_axisRange.GetYaxis().SetTitle("m_{#tilde{#chi}^{0}_{1}} [GeV]")
    
    h2_axisRange.GetXaxis().SetTitleSize(0.06)
    h2_axisRange.GetXaxis().SetTitleOffset(0.85)
    h2_axisRange.GetXaxis().CenterTitle(True)
    h2_axisRange.GetXaxis().SetLabelSize(0.0425)
    
    h2_axisRange.GetYaxis().SetTitleSize(0.06)
    h2_axisRange.GetYaxis().SetTitleOffset(0.9)
    h2_axisRange.GetYaxis().CenterTitle(True)
    h2_axisRange.GetYaxis().SetLabelSize(0.0425)
    
    h2_axisRange.Draw()
    
    #####
    #h2_xs.Smooth(10)
    
    if (isSmooth) :
        
        h2_xs.GetZaxis().SetTitle("95% CL upper limit on cross-section [pb]")
    
    else :
        
        h2_xs.GetZaxis().SetTitle("95% CL upper limit on signal strength")
    
    
    h2_xs.GetZaxis().SetTitleSize(0.045)
    h2_xs.GetZaxis().SetTitleOffset(1.35)
    h2_xs.GetZaxis().CenterTitle(True)
    h2_xs.GetZaxis().SetLabelSize(0.0425)
    
    
    if (isSmooth) :
        
        h2_xs.SetMinimum(1e-3)
        h2_xs.SetMaximum(1e2)
    
    else :
        
        h2_xs.SetMinimum(1)
        h2_xs.SetMaximum(10)
    
    h2_xs.Draw("colz same")
    
    
    #graph_xs.Draw("colz same")
    #graph_xs.Draw("colz")
    
    #graph_xs.GetYaxis().SetLimits(1, 900)
    
    #graph_xs.GetZaxis()->SetRangeUser(1e-5, 1e2)
    #graph_xs.SetMinimum(1e-4)
    #graph_xs.SetMaximum(1e2)
    
    #graph_xs.Draw("colz")
    #canvas.Update()
    
    ########################################
    
    
    if (isSmooth) :
        
        contour_expectedLimit.Draw("C same")
        contour_expectedLimit_1sigLwr.Draw("C same")
        contour_expectedLimit_1sigUpr.Draw("C same")
    
    if (drawObserved) :
        
        contour_observedLimit.Draw("C same")
        
        if (isSmooth) :
            
            contour_observedLimit_1sigLwr.Draw("C same")
            contour_observedLimit_1sigUpr.Draw("C same")
        
        legend.AddEntry(contour_observedLimit, "Observed")
        legend.AddEntry(contour_observedLimit_1sigLwr, "Observed #pm 1#sigma_{theory}")
    
    if (isSmooth) :
        
        #legend.AddEntry(contour_observedLimit_1sigLwr, "#lower[0.2]{Observed #pm 1#sigma_{theory}}")
        
        legend.AddEntry(contour_expectedLimit, "Expected")
        #legend.AddEntry(contour_expectedLimit_1sigLwr, "#lower[0.1]{Expected #pm 1#sigma_{experiment}}")
        legend.AddEntry(contour_expectedLimit_1sigLwr, "Expected #pm 1#sigma_{experiment}")
    
    canvas.RedrawAxis()
    
    if (isSmooth) :
        
        canvas.SetLogz(True)
    
    #canvas.SetRightMargin(2*canvas.GetRightMargin())
    
    legend.Draw()
    
    #print canvas.GetRightMargin()
    
    # CMS label
    CMS_lumi.CMS_lumi(
        pad = canvas,
        iPeriod = 0,
        iPosX = 0,
        CMSextraText = Common.getCMSextraText(isPrelim = (not noPrelim)),
        #lumiText = Common.getLumitext(era)
        lumiText = "#lower[-0.1]{%s}" %(lumiText)
    )
    
    
    if (isSmooth) :
        
        outFileName = "%s/exclusion2D_%s.pdf" %(outDir, suffix)
    
    else :
        
        outFileName = "%s/exclusion2D_%s_coarse.pdf" %(outDir, suffix)
    
    outRootFile = ROOT.TFile.Open("%s/exclusion2D_%s.root" %(outDir, suffix), "RECREATE")
    
    
    graph_expectedLimit.Write("expectedXsecLimit")
    contour_expectedLimit.Write("expectedExclusion")
    contour_expectedLimit_1sigLwr.Write("expectedExclusion_1sigLwr")
    contour_expectedLimit_1sigUpr.Write("expectedExclusion_1sigUpr")
    
    if (drawObserved) :
        
        graph_observedLimit.Write("observedXsecLimit")
        contour_observedLimit.Write("observedExclusion")
        contour_observedLimit_1sigLwr.Write("observedExclusion_1sigLwr")
        contour_observedLimit_1sigUpr.Write("observedExclusion_1sigUpr")
    
    canvas.Write()
    
    outRootFile.Close()
    
    canvas.SaveAs(outFileName)
    
    canvas.Clear()
    canvas.Close()
    
    contourList_observedLimit.Delete()


def main() :
    
    d_info = {
        "2016": {
            "l_limitFileName": [
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis/limitInfo_SRB.txt",
            ],
            
            "l_label": [
                "x = 0.25",
                "x = 0.5",
                "x = 0.75",
            ],
            
            "l_suffix": [
                "x0p25",
                "x0p5",
                "x0p75",
            ],
        },
        
        "2016to300fbInv": {
            "l_limitFileName": [
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis_2016to300fbInv/limitInfo_SRB.txt",
            ],
            
            "l_label": [
                "x = 0.5",
            ],
            
            "l_suffix": [
                "x0p5",
            ],
        },
        
        "2016to3000fbInv": {
            "l_limitFileName": [
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Summer16_tauTau_analysis_2016to3000fbInv/limitInfo_SRB.txt",
            ],
            
            "l_label": [
                "x = 0.5",
            ],
            
            "l_suffix": [
                "x0p5",
            ],
        },
        
        "2017": {
            "l_limitFileName": [
                #"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
                #"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
                #"stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
                
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_mStop-200to1800_XStau0p25_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
                "stopPair_mc/output_combine/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p5_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
                "stopPair_mc/output_combine/SMS-T8bbstausnu_mStop-200to1800_XCha0p5_XStau0p75_TuneCP2_13TeV-madgraphMLM-pythia8_Fall17_tauTau_analysis/limitInfo_SRB.txt",
            ],
            
            "l_label": [
                "x = 0.25",
                "x = 0.5",
                "x = 0.75",
            ],
            
            "l_suffix": [
                "x0p25",
                "x0p5",
                "x0p75",
            ],
        },
        
        "combined": {
            "l_limitFileName": [
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p25_combined_tauTau_analysis/limitInfo_SRB.txt",
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p5_combined_tauTau_analysis/limitInfo_SRB.txt",
                "stopPair_mc/output_combine/SMS-T8bbstausnu_XCha0p5_XStau0p75_combined_tauTau_analysis/limitInfo_SRB.txt",
            ],
            
            "l_label": [
                "x = 0.25",
                "x = 0.5",
                "x = 0.75",
            ],
            
            "l_suffix": [
                "x0p25",
                "x0p5",
                "x0p75",
            ],
        },
    }
    
    #era = "2016"
    #era = "2017"
    #era = "combined"
    
    era = "2016to300fbInv"
    #era = "2016to3000fbInv"
    
    #lumiText = Common.getLumitext(era)
    lumiText = "300 fb^{-1}"
    #lumiText = "3000 fb^{-1}"
    
    outDir = "plots/limits/%s%s%s" % (era, noPrelimStr, extraSuffix)
    #outDir = "plots/limits/%s%s_notSmoothed" % (era, noPrelimStr)
    os.system("mkdir -p %s" %(outDir))
    
    l_limitFileName = d_info[era]["l_limitFileName"]
    
    for iFile in range(0, len(l_limitFileName)) :
        
        limitFile = l_limitFileName[iFile]
        
        print "*"*50
        print "File: %s" %(limitFile)
        
        limitFileInfo = numpy.loadtxt(limitFile, delimiter = ",")
        
        nMass = limitFileInfo.shape[0]
        
        iLimitInfo = LimitInfo()
        
        print len(iLimitInfo.l_observedLimit)
        print len(iLimitInfo.l_expectedLimit)
        print len(iLimitInfo.l_expectedLimit_1sigLwr)
        print len(iLimitInfo.l_expectedLimit_1sigUpr)
        
        l_stop1_m_unique = []
        
        l_xs = []
        l_xs_upr = []
        l_xs_lwr = []
        
        for iMass in range(0, nMass) :
            
            #if (limitFileInfo[iMass][0] % 50) :
            #    
            #    continue
            
            stop1_m = limitFileInfo[iMass][0]
            neutralino1_m = limitFileInfo[iMass][1]
            
            iLimitInfo.l_stop1_m.append(stop1_m)
            iLimitInfo.l_neutralino1_m.append(neutralino1_m)
            
            
            xs = limitFileInfo[iMass][3]
            xs_uncPercent = limitFileInfo[iMass][4]
            
            xs_upr = xs * (1.0 + xs_uncPercent/100.0)
            xs_lwr = xs * (1.0 - xs_uncPercent/100.0)
            
            iLimitInfo.l_xs.append(xs)
            iLimitInfo.l_xs_uncPercent.append(xs_uncPercent)
            
            
            obsLimit = limitFileInfo[iMass][6]
            obsLimit_1sigLwr = obsLimit / (1.0 + xs_uncPercent/100.0)
            obsLimit_1sigUpr = obsLimit / (1.0 - xs_uncPercent/100.0)
            
            iLimitInfo.l_observedLimit.append(obsLimit)
            iLimitInfo.l_observedLimit_1sigLwr.append(obsLimit_1sigLwr)
            iLimitInfo.l_observedLimit_1sigUpr.append(obsLimit_1sigUpr)
            
            iLimitInfo.l_expectedLimit.append(limitFileInfo[iMass][7])
            iLimitInfo.l_expectedLimit_1sigLwr.append(limitFileInfo[iMass][8])
            iLimitInfo.l_expectedLimit_1sigUpr.append(limitFileInfo[iMass][9])
            iLimitInfo.l_expectedLimit_2sigLwr.append(limitFileInfo[iMass][10])
            iLimitInfo.l_expectedLimit_2sigUpr.append(limitFileInfo[iMass][11])
            
            if (limitFileInfo[iMass][0] not in l_stop1_m_unique) :
                
                l_stop1_m_unique.append(stop1_m)
                
                l_xs.append(xs)
                l_xs_upr.append(xs_upr)
                l_xs_lwr.append(xs_lwr)
            
            if (stop1_m == 800 and neutralino1_m == 100) :
                
                print xs, limitFileInfo[iMass][7], xs*limitFileInfo[iMass][7]
        
        #matplotlib.pyplot.plot(l_stop1_m_unique, l_xs_upr)
        #matplotlib.pyplot.plot(l_stop1_m_unique, l_xs_lwr)
        #matplotlib.pyplot.show()
        
        iLimitInfo.fInter_xs = scipy.interpolate.InterpolatedUnivariateSpline(l_stop1_m_unique, l_xs, k = 1, ext = "zeros")
        iLimitInfo.fInter_xs_upr = scipy.interpolate.InterpolatedUnivariateSpline(l_stop1_m_unique, l_xs_upr, k = 1, ext = "zeros")
        iLimitInfo.fInter_xs_lwr = scipy.interpolate.InterpolatedUnivariateSpline(l_stop1_m_unique, l_xs_lwr, k = 1, ext = "zeros")
        
        #print iLimitInfo.l_stop1_m
        #print iLimitInfo.l_neutralino1_m
        
        #print iLimitInfo.l_observedLimit
        #print iLimitInfo.l_observedLimit_1sigLwr
        #print iLimitInfo.l_observedLimit_1sigUpr
        
        print "Filled: %d \n" %(nMass)
        
        plot(
            limitInfo = iLimitInfo,
            era = era,
            outDir = outDir,
            label = d_info[era]["l_label"][iFile],
            lumiText = lumiText,
            suffix = d_info[era]["l_suffix"][iFile]
        )
        
        ##ROOT.gROOT.Reset()
        
        print "\n"


if (__name__ == "__main__") :
    
    main()

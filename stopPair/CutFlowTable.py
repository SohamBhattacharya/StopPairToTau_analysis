import numpy
import os

import Array2LatexTable
import MakeTable


latexDocument = ""

with open("../../misc/latex_headers.txt", "r") as f :
    
    latexDocument = f.read()


latexDocument += "\n" + "\\begin{document}" + "\n\n"


latexDocument += "$ m_{\\tilde{t}_{1}} = 392.137 \\ \\text{GeV} $" + "\\\\ \n"
latexDocument += "$ m_{\\tilde{\\tau}_{1}} = 297.878 \\ \\text{GeV} $" + "\\\\ \n"
latexDocument += "$ m_{\\tilde{\\nu}_{\\tau}} = 298.077 \\ \\text{GeV} $" + "\\\\ \n"
latexDocument += "$ m_{\\tilde{\\chi}^{0}_{1}} = 250.537 \\ \\text{GeV} $" + "\\\\ \n"
latexDocument += "$ m_{\\tilde{\\chi}^{\\pm}_{1}} = 301.953 \\ \\text{GeV} $" + "\\\\ \n"

latexDocument += "\n"


# Cut-flow files and data
cutFlow_fileNames_gen = [ \
    ["../../data_analyzed/stopPair_mc_analyzed/stopPair_mc_cutFlow_1_gen.txt"], \
    \
    ["../../data_analyzed/stopPair_mc_1_analyzed/stopPair_mc_1_cutFlow_1_gen.txt"], \
    \
    ["../../data_analyzed/ttbar_diLepton_mc_analyzed/ttbar_diLepton_mc_cutFlow_1_gen.txt"], \
    \
    ["../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-100To200_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-200To400_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-400To600_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-600To800_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-800To1200_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-1200To2500_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-2500ToInf_mc_cutFlow_1_gen.txt"], \
     \
    ["../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-100to200_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-200to400_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-400to600_mc_cutFlow_1_gen.txt", \
     "../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-600toInf_mc_cutFlow_1_gen.txt"]]

cutFlow_fileNames_reco = [ \
    ["../../data_analyzed/stopPair_mc_analyzed/stopPair_mc_cutFlow_1_reco.txt"], \
    \
    ["../../data_analyzed/stopPair_mc_1_analyzed/stopPair_mc_1_cutFlow_1_reco.txt"], \
    \
    ["../../data_analyzed/ttbar_diLepton_mc_analyzed/ttbar_diLepton_mc_cutFlow_1_reco.txt"], \
    \
    ["../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-100To200_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-200To400_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-400To600_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-600To800_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-800To1200_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-1200To2500_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/WJetsToLNu_mc_analyzed/WJetsToLNu_HT-2500ToInf_mc_cutFlow_1_reco.txt"], \
     \
    ["../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-100to200_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-200to400_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-400to600_mc_cutFlow_1_reco.txt", \
     "../../data_analyzed/DYJetsToLL_mc_analyzed/DYJetsToLL_M-50_HT-600toInf_mc_cutFlow_1_reco.txt"]]



# Cross-section files and data
crossSection_fileNames = [ \
    "stopPair_mc/stopPair_mc_crossSection.txt", \
    "stopPair_mc/stopPair_mc_1_crossSection.txt", \
    "ttbar_diLepton_mc/ttbar_diLepton_mc_crossSection.txt", \
    "WJetsToLNu_mc/WJetsToLNu_mc_crossSection.txt", \
    "DYJetsToLL_mc/DYJetsToLL_mc_crossSection.txt"]


cutFlow_str_fileName_gen = "cutFlows/cutFlow_1_gen.txt"
cutFlow_str_fileName_reco = "cutFlows/cutFlow_1_reco.txt"


column_titles = [ \
    "cuts", \
    "$ \\tilde{t}_{1} \\tilde{t}^{*}_{1} $", \
    "$ \\tilde{t}_{1} \\tilde{t}^{*}_{1} $ sample 1", \
    "$ t \\bar{t} \\  di \\text{-} Lepton $", \
    "$ W + jets $", \
    "$ DY \\ jets $ to $ LL $"]


# GEN
table = MakeTable.makeTable( \
    column_titles, \
    cutFlow_fileNames_gen, \
    cutFlow_str_fileName_gen, \
    crossSection_fileNames)


latexTable = Array2LatexTable.array2LatexTable( \
    table, \
    isColumnTitled = True, \
    table_caption = "GEN: $ \\sum\\limits_{H_{T} \\ \\text{bins} \ b} \\frac{n^{b}_{c}}{N^{b}_{ev}} \\sigma^{b} \\ [\\text{pb}] $")   

#print latexTable
latexDocument += latexTable + "\n\n"


# RECO
table = MakeTable.makeTable( \
    column_titles, \
    cutFlow_fileNames_reco, \
    cutFlow_str_fileName_reco, \
    crossSection_fileNames)

latexTable = Array2LatexTable.array2LatexTable( \
    table, \
    isColumnTitled = True, \
    table_caption = "RECO: $ \\sum\\limits_{H_{T} \\ \\text{bins} \ b} \\frac{n^{b}_{c}}{N^{b}_{ev}} \\sigma^{b} \\ [\\text{pb}] $")   

#print latexTable
latexDocument += latexTable + "\n\n"


latexDocument += "\n" + "\\end{document}" + "\n"

#print latexDocument

outfileName = "cutFlow.tex"
outfileNamePdf = "cutFlow.pdf"

with open(outfileName, "w") as f :
    
    f.write(latexDocument)

os.system("pdflatex " + outfileName)
os.system("kill -KILL `pgrep -f \"okular " + outfileNamePdf + "\"`")
os.system("okular " + outfileNamePdf + " &")

import numpy
import os


fileName = "logs/DY1JetsToLL_mc_analysis.log"
lineDelimiter = "###"

#with open(fileName, "r") as f :
#    
#    fileContent = f.read()

lines = numpy.loadtxt(fileName, delimiter = "SomeNonExistentString", comments = "SomeNonExistentString", dtype = str)

lines = [l.rstrip(lineDelimiter).split(lineDelimiter) for l in lines if (lineDelimiter in l)]

lines1 = numpy.array([lines[iLine] for iLine in range(0, len(lines), 2)]).astype(int)
lines2 = numpy.array([lines[iLine] for iLine in range(1, len(lines), 2)]).astype(int)

print lines1.shape
print numpy.sum(lines1, axis = 0)

print lines2.shape
print numpy.sum(lines2, axis = 0)

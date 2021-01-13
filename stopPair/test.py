import os
import sys
import time


var = 9999
globVar = 2222

#for i in range(0, 10) :
#    
#    time.sleep(1)
#    print "Printing %d \t\t\t\t \r" %(i),
#    #sys.stdout.flush()
#    
#    #sys.stdout.write("Printing %d    \r" %(i))
#
#print ""

#def mod(dict) :
#    
#    dict["xx"] = 1
#
#def main() :
#    
#    d = {}
#    print d
#    
#    mod(d)
#    print d
#
#
#if (__name__ == "__main__") :
#   
#    main()

def testStuff(var) :
    
    global globVar
    
    globVar = 3333
    
    print "Inside testStuff(...): var = %f" %(var)
    print "Inside testStuff(...): globVar = %f" %(globVar)


print "var = %f" %(var)
testStuff(1111)
print "globVar = %f" %(globVar)

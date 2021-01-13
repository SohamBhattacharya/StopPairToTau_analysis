info = [
    #[0.25, 1100, 25],
    #[0.25, 1100, 200],
    #[0.25, 1100, 400],
    #[0.25, 1100, 500],
    
    [0.25, 400, 100]
]

for iEntry in range(0, len(info)) :
    
    x = info[iEntry][0]
    
    stop1_m = info[iEntry][1]
    neutralino1_m = info[iEntry][2]
    
    deltaM = stop1_m - neutralino1_m
    
    chargino1_m = neutralino1_m + 0.5*deltaM
    stau1_m = neutralino1_m + 0.5*x*deltaM
    
    print "x =", x
    print "stop1_m =", stop1_m
    print "chargino1_m =", chargino1_m
    print "stau1_m =", stau1_m
    print "neutralino1_m =", neutralino1_m
    print "[%s, %d, %d, %d, %d]" %(x, stop1_m, chargino1_m, stau1_m, neutralino1_m)
    print ""

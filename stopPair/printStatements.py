import os


outfileName = "statements.txt"

toReplace = "$$$"

l_str = [
    "JetResUp",
    "JetResDown",
    
    "JetEnUp",
    "JetEnDown",
    
    "UnclusteredEnUp",
    "UnclusteredEnDown",
]


templateStr = (
    "MET_%s_E_reco = 0; MET_%s_phi_reco = 0;"
)
linegaps = 0


#templateStr = (
#    "T_reco->SetBranchAddress(\"MET_%s_E_reco\", &MET_%s_E_reco);\n"
#    "T_reco->SetBranchAddress(\"MET_%s_phi_reco\", &MET_%s_phi_reco);\n"
#)
#linegaps = 0



with open(outfileName, "w") as f :
    
    for iEntry in range(0, len(l_str)) :
        
        #temp_str = templateStr %(l_str[iEntry])
        temp_str = templateStr
        temp_str = temp_str.replace("%s", l_str[iEntry])
        
        print temp_str + "\n" * linegaps
        
        temp_str += "\n"
        temp_str += "\n" * linegaps
        
        f.write(temp_str)
        


import condorDiagnose


process = "SMS-T8bbstausnu_XCha0p5_XStau0p25_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"

suffix = "_tauTau_analysis"

faultyMassIndexList = condorDiagnose.getFaultyMassIndexList(process, suffix)

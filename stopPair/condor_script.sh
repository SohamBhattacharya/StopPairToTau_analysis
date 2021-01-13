#!/bin/sh

DIR="/home/sobhatta/t3store3/stopPairToTau/analysis/CMSSW_10_5_0/src/stopPair"

cd $DIR

export SCRAM_ARCH=slc6_amd64_gcc530
export CPATH=$CPATH:$DIR

# Proxy path must be common to all nodes
# Default path is /tmp/, but thatis not common for all nodes
export X509_USER_PROXY=/home/sobhatta/proxies/x509up_u56529

source /cvmfs/cms.cern.ch/cmsset_default.sh

eval cmsenv

#echo "Creating voms-proxy..."
#eval vpxy
echo "Proxy info:"
voms-proxy-info -all
echo ""

if ./compile.sh ch @infile@ ; then
    ./@exe@
else
    echo "Compilation failed."
fi
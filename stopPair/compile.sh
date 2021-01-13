#!/bin/bash

OPT=$1
FILE=$2
DEBUG=$3

NAME="${FILE##*/}"
EXT="${FILE##*.}"
NAME="${FILE%.*}"

echo "Full file name:" $FILE
echo "File name:" $NAME
echo "File extension:" $EXT

eval `scramv1 runtime -sh`

ROOT_FLAGS=`root-config --libs --cflags --ldflags`" -lRooFitCore"
CLHEP_FLAGS="-I/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/include -L/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/lib -lCLHEP -ldl -Wl,-rpath /cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/clhep/2.3.4.2/lib"
BOOST_FLAGS="-I/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/boost/1.57.0-ikhhed/include -L/cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/boost/1.57.0-ikhhed/lib -ldl -Wl,-rpath /cvmfs/cms.cern.ch/slc6_amd64_gcc530/external/boost/1.57.0-ikhhed/lib"

CUSTOM_HEADER_PATH="/home/sobhatta/t3store3/stopPairToTau/analysis/CMSSW_10_5_0/src/stopPair"
CUSTOM_HEADERS=`find $CUSTOM_HEADER_PATH/HeaderFiles | grep ".cc$"`

GPP_FLAGS="-std=c++11 -O2"

if [ "$DEBUG" == "d" ]; then
    GPP_FLAGS=$GPP_FLAGS" -g"
fi

if [ "$OPT" == "n" ]; then
    g++ $GPP_FLAGS $NAME"."$EXT -o $NAME
elif [ "$OPT" == "h" ]; then
    g++ $GPP_FLAGS $NAME"."$EXT -o $NAME $ROOT_FLAGS $CLHEP_FLAGS $BOOST_FLAGS # -Wl,-rpath,$(root-config --libs)
elif [ "$OPT" == "ch" ]; then
    g++ $GPP_FLAGS $NAME"."$EXT $CUSTOM_HEADERS -o $NAME $ROOT_FLAGS $CLHEP_FLAGS $BOOST_FLAGS -I$CUSTOM_HEADER_PATH
else
    echo "Wrong g++mod option."
fi

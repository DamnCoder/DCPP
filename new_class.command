#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
FILE_OUTPUT="${DIR}/project"
TEMPLATES_PATH="${DIR}/utilities/NewClassProject/Templates"

cd $DIR/utilities/NewClassProject/NewClass/bin/Debug

mono NewClass.exe $TEMPLATES_PATH $FILE_OUTPUT assetloader DCPP "Jorge López González" CAssetLoader dc persist/assets
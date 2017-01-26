#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
FILE_OUTPUT="${DIR}"
TEMPLATES_PATH="${DIR}/utilities/CMakeConfigure/Templates"

cd $DIR/utilities/CMakeConfigure/Build

mono CMakeConfigure.exe $TEMPLATES_PATH $FILE_OUTPUT STATIC DCPP Debug
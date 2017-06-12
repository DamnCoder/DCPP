#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

FILE_OUTPUT="${DIR}/../project"
TEMPLATES_PATH="${DIR}/../utilities/CMakeConfigure/Templates"

cd $DIR/../utilities/CMakeConfigure/Build

mono CMakeConfigure.exe $TEMPLATES_PATH $FILE_OUTPUT STATIC DCPP Debug dcpp_signals dcpp_math stb_image rapidjson
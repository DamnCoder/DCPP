#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/utilities/Release
mono CMakeConfigure.exe SHARED_LIB DCPP Debug
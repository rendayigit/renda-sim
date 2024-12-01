# Initialization
cd `dirname $0`
SCRIPTDIR=`pwd`
cd -

mkdir -p $SCRIPTDIR/build/

# Configure Project
cmake \
-DCMAKE_BUILD_TYPE:STRING=Release \
-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
-S$SCRIPTDIR/ \
-B$SCRIPTDIR/build/ \
-G "Unix Makefiles"

# Build
cmake \
--build $SCRIPTDIR/build/ \
--config Release \
--target all \
-j$((`nproc`+2)) --
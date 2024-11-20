# Initialization
cd `dirname $0`
SCRIPTDIR=`pwd`
cd -

# Configure Project
cmake \
-DCMAKE_BUILD_TYPE:STRING=Debug \
-DCMAKE_CC_COMPILER:FILEPATH=/usr/bin/gcc \
-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
-DENABLE_COVERAGE=ON \
-S$SCRIPTDIR/../tests/  \
-B$SCRIPTDIR/../build/ \
-G "Unix Makefiles"

# Build
cmake \
--build $SCRIPTDIR/../build/ \
--config Debug \
--target all \
-j$((`nproc`+2)) --

# Run unit tests
cd $SCRIPTDIR/../bin/
./tests
# Initialization
cd `dirname $0`
SCRIPTDIR=`pwd`
cd -

rm -rf $SCRIPTDIR/../build/
mkdir -p $SCRIPTDIR/../build/

# Configure Project
cmake \
-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
-DCMAKE_BUILD_TYPE:STRING=Debug \
-DCMAKE_CC_COMPILER:FILEPATH=/usr/bin/gcc \
-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
-DENABLE_COVERAGE=ON \
-S$SCRIPTDIR/../ \
-B$SCRIPTDIR/../build/ \
--no-warn-unused-cli \
-G "Unix Makefiles"

# Build
cmake \
--build $SCRIPTDIR/../build/ \
--config Debug \
--target all \
-j$((`nproc`+2)) --

# Run unit tests
cd $SCRIPTDIR/../bin/
./model-tests

# Generate coverage
mkdir $SCRIPTDIR/../coverage/
python3 -m gcovr --config $SCRIPTDIR/gcovr.cfg

# Open coverage report
open "$SCRIPTDIR/../coverage/index.html" > /dev/null 2>&1 &
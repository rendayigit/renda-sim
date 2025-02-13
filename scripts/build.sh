# Initialization
cd `dirname $0`
SCRIPTDIR=`pwd`
cd -

# Build Engine
cd $SCRIPTDIR/../Engine
make -j$((`nproc`+2))

# Build Models
cd $SCRIPTDIR/../Models
make -j$((`nproc`+2))

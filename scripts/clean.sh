# Initialization
cd `dirname $0`
SCRIPTDIR=`pwd`
cd -

# Build Engine
cd $SCRIPTDIR/Engine
make clean

# Build Models
cd $SCRIPTDIR/Models
make clean

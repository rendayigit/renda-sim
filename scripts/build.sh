# Initialization
cd `dirname $0`
SCRIPTDIR=`pwd`
cd -

# Build Engine
cd $SCRIPTDIR/../Engine
./scripts/build.sh

# Build Models
cd $SCRIPTDIR/../Models
./scripts/build.sh

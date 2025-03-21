# Initialization
cd `dirname $0`
SCRIPTDIR=`pwd`
cd -

# Build Engine
cd $SCRIPTDIR/../Engine
./scripts/clean.sh

# Build Models
cd $SCRIPTDIR/../Models
./scripts/clean.sh

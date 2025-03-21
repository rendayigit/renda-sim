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

# Extract coverage percentage from coverage.xml using grep and awk
LINE_RATE=$(grep -o 'line-rate="[^"]*"' "$SCRIPTDIR/../coverage/coverage.xml" | head -n 1 | awk -F'"' '{print $2}')

# Convert the line rate to a percentage
COVERAGE_PERCENTAGE=$(echo "$LINE_RATE * 100" | bc | awk '{printf "%.0f", $1}')

# Create SVG badge
BADGE_COLOR="green"
if [[ "$COVERAGE_PERCENTAGE" -lt 70 ]]; then
  BADGE_COLOR="red"
elif [[ "$COVERAGE_PERCENTAGE" -lt 90 ]]; then
  BADGE_COLOR="yellow"
fi

SVG_CONTENT="<svg xmlns='http://www.w3.org/2000/svg' width='100' height='20' viewBox='0 0 100 20'>
  <defs>
    <mask id='round-mask'>
      <rect width='100' height='20' rx='3' fill='white'/>
    </mask>
  </defs>
  <g mask='url(#round-mask)'>
    <rect width='60' height='20' fill='#5A5A5A'/>
    <text x='30' y='14' font-family='Verdana,Geneva,DejaVu Sans,sans-serif' font-size='11' fill='#fff' text-anchor='middle'>Coverage</text>
  </g>
  <g mask='url(#round-mask)'>
    <rect x='60' width='40' height='20' fill='$BADGE_COLOR'/>
    <text x='80' y='14' font-family='Verdana,Geneva,DejaVu Sans,sans-serif' font-size='11' fill='#fff' text-anchor='middle'>$COVERAGE_PERCENTAGE%</text>
  </g>
</svg>"

echo "$SVG_CONTENT" > "$SCRIPTDIR/../.github/workflows/coverage.svg"

# Open coverage report
open "$SCRIPTDIR/../coverage/index.html" > /dev/null 2>&1 &
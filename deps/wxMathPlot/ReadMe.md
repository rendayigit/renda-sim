# How I Installed deps/wxMathPlot

1. Download and unzip https://unlimited.dl.sourceforge.net/project/wxmathplot/wxmathplot/0.2.0/wxMathPlot_0.2.0.zip?viasf=1
1. Copy the `mathplot.cpp` and `mathplot.h` into `src/` and `include/` respectively.
1. Then I created the `CMakeLists.txt` in the root directory of this project. Check it out for the more details.
1. Then I compiled the library using the `build.sh` script I placed in the root directory of this project.
1. The compiled library is in `lib/`.
1. I also modified the library code a little for the plots of the simulation.
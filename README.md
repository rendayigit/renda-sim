# Renda-Sim

## How to build the project

### Install GNU compilers

``` bash
sudo apt install build-essential    # Install GNU compilers.
sudo apt install libboost-all-dev   # Install boost libraries.
```

### Install clangd language server

``` bash
sudo apt install clangd             # Install clangd language server.
```

### Install GTest for unit testing

``` bash
sudo apt install libgtest-dev       # Install gtest unit testing framework
```

### Install Gcovr for code coverage

``` bash
cd ~
sudo apt install python3-pip        # Install python package manager.
pip install gcovr                   # Install gcovr code coverage tool.
```

### Install GDB for debugging

``` bash
sudo apt install gdb                # Install GNU GDB debugger.
```

### Install clang-format and pre-commit for code formatting

``` bash
sudo apt install clang-format       # Install clang-format.
sudo apt install pre-commit         # Install pre-commit to run clang-format on commit.
pre-commit install                  # Activate pre-commit hooks
```

### Use the scripts under `scripts/`

- `build.sh`: Build the sample application.
- `clean.sh`: Clean the sample application.
- `coverage.sh`: Generate unit test code coverage.
- `run.sh`: Run the sample application.
- `test.sh`: Run the unit tests without code coverage.

## For Developers

### How I created deps/wxwidgets

1. Run `sudo apt install libgtk-3-dev`
1. Download and unzip https://github.com/wxWidgets/wxWidgets/releasesdownload/v3.2.6/wxWidgets-3.2.6.tar.bz2
1. cd into this downloaded dir
1. Create a dir called `gtk-build` and cd into it
1. Run `../configure`
1. Run `make -j3`
1. Delete the links in the generated `lib/` dir
1. Rename all the .so files in this lib dir from ...`.so.0.3.0` to ...`.so.0`
1. Copy this `lib` dir into the projects `deps` dir
1. Copy the `include` dir from the zip downloaded earlier into the projects `deps` dir
1. Run `./wx-config --cxxflags` (`wx-config` was generated somewhere inside `gtk-build`) and use the outputs of this command to determine include directories, link libraries and compile definitions
1. I know this is hideous but it works lol :P
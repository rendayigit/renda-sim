# Sample Cpp Project

### Install GNU compilers

``` bash
sudo apt install build-essential                                    # Install GNU compilers.
sudo apt install libboost-all-dev                                   # Install boost libraries.
```

### Install clangd language server

``` bash
sudo apt install clangd                                             # Install clangd language server.
```

### Install GTest for unit testing

``` bash
sudo apt install libgtest-dev                                       # Install gtest unit testing framework
```

### Install Gcovr for code coverage

``` bash
cd ~
sudo apt install python3-pip                                        # Install python package manager.
pip install gcovr                                                   # Install gcovr code coverage tool.
```

### Install GDB for debugging

``` bash
sudo apt install gdb                                                # Install GNU GDB debugger.
```

### Install clang-format and pre-commit for code formatting

``` bash
sudo apt install clang-format                                       # Install clang-format.
sudo apt install pre-commit                                         # Install pre-commit to run clang-format on commit.
pre-commit install                                                  # Activate pre-commit hooks
```

### Use the scripts under `scripts/`

- `build.sh`: Build the sample application.
- `clean.sh`: Clean the sample application.
- `coverage.sh`: Generate unit test code coverage.
- `run.sh`: Run the sample application.
- `test.sh`: Run the unit tests without code coverage.
# Renda-Sim

## How to build the project

### Install dependencies

```bash
cd ~
sudo apt install python3            # Install python.
sudo apt install python3-pip        # Install python package manager.
pip install wxPython                # Install wxPython UI framework.
pip install matplotlib              # Install matplotlib for plotting.
pip install pyzmq                   # Install zeromq message queue library for gui.
pip install pyqtgraph               # Install PyQtGraph Scientific Graphics and GUI Library for Python
pip install PyQt5                   # Install Qt 5 GUI Library for Python
sudo apt-get install libzmq3-dev    # Install zeromq message queue library for engine.
sudo apt install build-essential    # Install GNU compilers.
sudo apt install libboost-all-dev   # Install boost libraries.
sudo apt install nlohmann-json3-dev # Install nlohmann json library.
sudo apt install libspdlog-dev      # Install spdlog logging library.
```

### Build the project

- `./scripts/build.sh`: To build the engine, the models and the tests.
- `./scripts/clean.sh`: To clean all projects.

## For Developers

### Developer dependencies

```bash
cd ~
pip install gcovr                   # Install gcovr code coverage tool.
sudo apt install gdb                # Install GNU GDB debugger.
sudo apt install libgtest-dev       # Install gtest unit testing framework.
sudo apt install clangd             # Install clangd language server.
sudo apt install clang-format       # Install clang-format.
sudo apt install pre-commit         # Install pre-commit to run clang-format on commit.
pre-commit install                  # Activate pre-commit hooks
```

See the readmes in `deps/` for more details about some of the project dependencies.

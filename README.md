# Renda-Sim

## How to build the project

```bash
cd ~
sudo apt install python3            # Install python.
sudo apt install python3-pip        # Install python package manager.
pip install wxPython                # Install wxPython UI framework.
pip install matplotlib              # Install matplotlib for plotting.
pip install pyzmq                   # Install zeromq message queue library for gui.
sudo apt-get install libzmq3-dev    # Install zeromq message queue library for engine.
sudo apt install build-essential    # Install GNU compilers.
sudo apt install libboost-all-dev   # Install boost libraries.
sudo apt install nlohmann-json3-dev # Install nlohmann json library.
sudo apt install libspdlog-dev      # Install spdlog logging library.
```

### Developers might need to install these as well

```bash
cd ~
pip install gcovr                   # Install gcovr code coverage tool.
sudo apt install gdb                # Install GNU GDB debugger.
sudo apt install libgtest-dev       # Install gtest unit testing framework.
sudo apt install clangd             # Install clangd language server.
sudo apt install clang-format       # Install clang-format.
sudo apt install pre-commit         # Install pre-commit to run clang-format on commit.
```

### Use the scripts under `scripts/`

- `build.sh`: Build the sample application.
- `clean.sh`: Clean the sample application.
- `coverage.sh`: Generate unit test code coverage.
- `run.sh`: Run the sample application.
- `test.sh`: Run the unit tests without code coverage.

## For Developers

- See the readmes in `deps/` for more details about some of the project dependencies.
- Run `pre-commit install` to activate pre-commit hooks.

# Deterministic 6G Simulation Framework

## Compatibility
This version of the D6G framework is compatible with OMNeT++ 6.0 and INET 4.5.2.

## Getting Started
The following guide assumes you already have a working OMNeT++ installation (see [here](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf) for instructions).


### Workspace Setup
Your workspace should have the following structure:
```
[path_to_your_workspace]
├── deterministic6g
└── inet
```

### INET installation
If you already have INET installed, you can skip this step.

1. Clone the INET repository with the correct version (make sure to follow the correct [Workspace Setup](#workspace-setup)):
```shell
git clone --branch v4.5.2 https://github.com/inet-framework/inet.git
```

2. Build INET:
```shell
cd inet
src setenv
make makefiles
make -j$(nproc)
```

### Deterministic6G installation
1. Make sure this project is in your workspace (see [Workspace Setup](#workspace-setup)).
2. Build the Deterministic6G framework:
```shell
cd deterministic6g
make makefiles
make -j$(nproc)
```

### Working in the OMNeT++ IDE
1. Open/Create the workspace located at `[path_to_your_workspace]`.
2. Open the INET project (File > Open Projects from File System... > Directory... > `[path_to_your_workspace]/inet` > Finish)
3. Open the D6G project (File > Open Projects from File System... > Directory... > `[path_to_your_workspace]/deterministic6g` > Finish)

## Run simulations

### Using the IDE
1. Open the `omnetpp.ini` file of the simulation you want to run.
2. Click on the green run button in the top toolbar.

### Using the command line

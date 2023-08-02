# Deterministic 6G Simulation Framework

## Compatibility
This version of the D6G framework is compatible with OMNeT++ 6.0 and INET 4.5.

## Getting Started
The following guide assumes you already have a working OMNeT++ installation (see [here](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf) for instructions).


### Workspace Setup
Your workspace should have the following structure:
```
<workspace>
├── d6g
└── inet
```

### INET installation
If you already have INET installed, you can skip this step.

1. Clone the INET repository with the correct version (make sure to follow the correct [Workspace Setup](#workspace-setup)):
```shell
git clone --branch v4.5.0 https://github.com/inet-framework/inet.git
```

2. Build INET:
```shell
cd inet
source setenv
make makefiles
make -j$(nproc)
```

### D6G installation
1. Make sure this project is in your workspace (see [Workspace Setup](#workspace-setup)).
2. Build the D6G framework:
```shell
cd d6g
make makefiles
make -j$(nproc)
```
# snspd-rcsj

A one-dimensional SNSPD model.

## Requirements

The following is needed to run the project.

- g++ (tested with 9.3.0)
- CMake 3.12 or later
- Conan

## Installation

The easiest way to get started is to download the binary from github using

```shell script
wget https://github.com/afsa/snspd-rcsj/releases/latest/download/release.zip
unzip release.zip
```

To start the simulation then run

```shell script
./bin/snspd-rcsj [options]
```

### Build from source

The easiest way to build the project is cloning and running the build script

```shell script
git clone git@github.com:afsa/snspd-rcsj.git
./build.sh
```

A binary is built in the `bin` directory and the simulation can be started using

```shell script
./bin/snspd-rcsj [options]
```

### Development build

To manually configure the build run

```shell script
ccmake .
```

and select appropriate settings for the build. Then build the project using

```shell script
cmake --build .
```

The binary outputs are found in the directory `bin`.

## Options

The options can be printed with

```shell script
./bin/snspd-rcsj -h
```

The result is shown below

```
Usage:
  snspd-rcsj [options]

Options:
  -h, --help              Show the help screen.
  -V, --version           Display the version.
  -v, --verbose           Run program in verbose mode.
  -s, --silent            Run program in silent mode (without progress bar).
  -c, --config=<CONFIG>   Path to the JSON config file [default: settings.json].
  -o, --output=<OUTPUT>   HDF5 file to store output data.
```

## Configuration

The JSON configuration file contains all information about simulation parameters and similar information. Available
options are

```json5
{
  
  // General simulation settings
  "settings": {

    // The HDF5 file to write the output to. The file may contain a fmt format placeholder for the date.
    "output": "data/iv/{:%Y-%m-%d_%H%M%S}.h5",
    
    // If phase slips should be saved
    "savePhaseSlips": true
  },

  // Initial parameters
  "parameters": {
  
    // The boundary condition used in the simulation. The following options are available:
    // * simple   - The bias current is set directly with the parameter ib
    // * current  - The boundary condition includes a shunt resistor and the total bias current is ib.  
    // * voltage  - The boundary condition includes a shunt resistor. The total bias current is calculated with the 
    // bias voltage vb and the resistance rt.
    "boundaryCondition": "simple",
  
    // The number of configuration steps to run the simulation. The total time might be larger than this if the number
    // of averages is larger than one.
    "maxSteps": 2000,

    // How many times each configuration should be averaged. Useful for IV curves. 
    "average": 10000,

    // Size of the system.
    "size": 400,
    
    // Time step.
    "dt": 0.1,

    // Quality factor.
    "q": 1.1107,

    // Capacitance to ground in terms of the shunt capacitance.
    "c0": 0.01,
  
    // Gap voltage.
    "vg": 1,
  
    // Noise level.
    "nl": 0.0058,

    // Segment resistance.
    "r": 1,
  
    // Current.
    "i": 0,
  
    // Bias current.
    "ib": 0,
    
    // Bias voltage.
    "vb": 0,
  
    // Resistance in series with system
    "rt": 200,
    
    // Shunt resistance.
    "rs": 0.125,

    // Shunt capacitance.
    "cs": 0,

    // Critical current. 
    "ic": 1,

    // Phase.
    "x": {
      
      // Set the phase to be stationary at the start of the simulation.
      "stationaryPhase": true,

      // Enable random phases taken from a uniform distribution on the interval [0, 6.28].
      "random": false,
      "min": 0,
      "max": 6.28
    },
    
    // Voltage.
    "v": 0,

    // Quasiparticle resistance.
    "rqp": 1000
  },

  // Update the parameters during the simulation.
  "updates": [{

    // Start update at step 0.
    "start": 0,

    // End update at step 1000.
    "end": 1000,

    // Update the values below. The updates use linear interpolation.
    "values": {
      "ib": {
        "from": 0,
        "to": 5
      }
    }
  }, 

  // Another update.
  {
    "start": 1001,
    "end": 2000,
    "values": {
      "ib": {
        "from": 5,
        "to": 0
      }
    }
  }]
}
```

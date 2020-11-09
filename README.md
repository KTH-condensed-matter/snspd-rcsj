# snspd-rcsj

A one-dimensional SNSPD model using the resistively and capacitively shunted Josephson junction model.

## Installation

The easiest way to get started is to download the binary from github using

```shell script
wget https://github.com/KTH-condensed-matter/snspd-rcsj/releases/latest/download/release.zip
unzip release.zip
```

To start the simulation then run

```shell script
./bin/snspd-rcsj [options]
```

### Build from source

The following is needed to run the project.

- g++ (tested with 9.3.0)
- CMake 3.12 or later
- Conan

The easiest way to build the project is cloning and running the build script

```shell script
git clone git@github.com:KTH-condensed-matter/snspd-rcsj.git
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
    
    // If phase slips should be saved.
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

    // Critical current (space dependent). 
    "ic": 1,

    // Phase (space dependent).
    "x": {
      
      // Set the phase to be stationary at the start of the simulation.
      "stationaryPhase": true,

      // Enable random phases taken from a uniform distribution on the interval [0, 6.28].
      "random": false,
      "min": 0,
      "max": 6.28
    },
    
    // Voltage (space dependent).
    "v": 0,

    // Quasiparticle resistance (space dependent).
    "rqp": 1000
  },

  // Update the parameters during the simulation.
  "updates": [{

    // Start update at step 0.
    "start": 0,

    // End update at step 1000.
    "end": 1000,

    // Update the values below. The updates use linear interpolation between "from" and "to" values.
    "values": {

      "ib": {
        
        // Value before update.
        "from": 0, 
        
        // Value after update.
        "to": 1
      },

      "ic": {
          
        // The site to update (only for space dependent properties).
        "index": [100, 200],
        "from": 1,
        "to": 0.5
      },

      "x": {
        
        // Sites can also be selected with a range (only for space dependent properties).
        "range": [10, 20],
        "from": 0,
        "to": 10
      }     
    }
  }]
}
```

## Output

Simulation data is stored in the HDF5 format and can be read using for example 
[Python](https://docs.h5py.org/en/latest/quick.html) or [Matlab](https://se.mathworks.com/help/matlab/ref/h5read.html). 
Another good tool to quickly go through the data is HDF Compass which can be installed on Debian/Ubuntu using

```shell script
sudo apt install hdf-compass
```

The saved data is structured with HDF5 datasets as follows:

- `bias_current` - Contains the bias current going into the SNSPD every step.
- `voltage` - The voltage over the SNSPD.
- `time` - The time in dimensionless units since the start of the simulation.
- `phase_slips` - Information where phase slips occur.
- `json_config` - The configuration file used to run the simulation.

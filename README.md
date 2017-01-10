# MathematicalBilliards

Mathematical blliards numerical modelling project.

Recommended to use the build script provided to build the executable, which will be output to the images directory.

## BilliardSimulation

The main simulation executable for the project. This is used to produce the .dat files for analysis using the DimensionCalculator and Plotter scripts. Usage should be fairly straightforward.

## Build Script

The build script can be used to build the project, it requires python to be installed. If running it as an executable fails (particularly on non-linux systems) try invoking the python interpreter with the script as an argument. In almost every case the build script can be run with no arguments, but extra functionality is available; run the script with the -h flag to see a full list of options.

## DimensionCalculator

The dimensions calculator script can be used in a similar way to the build script (and again if it fails try invoking python directly). It requires a fractal data set, as output from the main executable, as its first argument and a grid size integer as its second argument. It will produce data to use with the plotter script.

## Plotter

The plotting script takes a .dat data file as its first (and only important) argument. It will draw graphs based on the name of the data file passed to it. For this reason it is recommended not to rename data files produced by any part of this project. The graphs are output as .pdf files. It uses the .plot.pgi script as its internal command list, and the user is invited to modify this as necessary to produce desired results.

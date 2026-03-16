# MOTS, a tool for the in-silico evaluation of mosquito control trial designs based on inundative releases

# Configuration guide

## Requisites

You must have the following software installed in order to run the GMM model(MCMC/scenarios) core code:

- git
- A C++ compiler
- The [GNU Scientific Library (GSL)](https://www.gnu.org/software/gsl/)

Additionally, to reproduce all results from the papers, you may need:

- python (version **need to be checked** was used in the development)
- Required python libraries (see **need to be checked** [requirements.in](/requirements.in))

## Downloading the necessary files

Clone this repository and its submodules using git:

```bash
git clone https://github.com/jagadeesh-chitturi/gmm-model-project.git
```

## Compiling the GMM model source code

Once you have downloaded all the required source code, header files and input files, you need to configure the required input parameters
for the model present in /data/constant_release_trial_in/model_input_config.csv (template). once the template is configured for all required parameters
you can compile source code using 'CMakeLists.txt' as below, given you have installed required vcpkg, CMAKE tools

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="D:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

to build an executable file for the model

```bash
cmake --build . --config Release
```

 pass the input parameters file as below to the executale file

 ```bash
 ./build/Debug/mosquito_sim.exe data/inputs/model_in/constant_release_trial_in/model_input_config.csv
 ```
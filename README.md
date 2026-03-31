# IRIS (Inundative mosquito Release Intervention Simulator), a tool for the in-silico evaluation of mosquito control trial designs based on inundative releases

# Configuration guide

## Requisites

You must have the following software installed in order to run the GMM model(MCMC/scenarios) core code:

- git
- A C++ compiler
- The [GNU Scientific Library (GSL)](https://www.gnu.org/software/gsl/)

Additionally, to reproduce all results from the papers, you may need:

- python (version **need to be checked** was used in the development)
- Required python libraries (see **need to be checked** [requirements.in](/requirements.in))

For easily building (compiling) the C++ code, you may want to also have [CMake](https://cmake.org/) installed. 

## Downloading the necessary files

Clone this repository and its submodules using git:

```bash
git clone https://github.com/jagadeesh-chitturi/iris-model.git
```

## Compiling the GMM model source code

**Once you have downloaded all the required source code, header files and input files, you can follow any of below two methods to run the IRIS model, although we recommend 2nd method as it requires least effort in adjusting input variables like paths and other parameters.**

### Common steps for both the execution methods to build the executable file


You can compile source code and build executable using CMake and the 'CMakeLists.txt' file.

### .env file setup
Please set up your .env file for following parametrs
```bash
# .env sample file
PROJECT_ROOT=root/project_name # please adjust this as per you root path to the project folder
OUTPUT_DIR=root/project_name/output # path to store the outputs 
```

#### On Windows

On a Windows system, run the code below from the root of the repository, replacing the path to your vcpkg path, to setup and building the executable file:

```bash
cmake . -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build . --config Release
```

The executable should be created at `./build/Release/mosquito_sim.exe`

#### On Linux/MacOS

In a Unix environment, run the following commands from the root of the repository:

```bash
cmake . -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release 
```

The executable should be created directly on the repository root as `mosquito_sim`.


### Method 1 (manual tweaking of input parameters to run the model)

You need to configure the required input parameters
for the model present in /data/constant_release_trial_in/model_input_config.csv (template). once the template is configured for all required parameters pass the input parameters file path as below to the executable file:

 ```bash
 ./build/Release/mosquito_sim.exe data/inputs/model_in/constant_release_trial_in/model_input_config.csv
 ```

 Replace `./build/Release/mosquito_sim.exe` with the proper executable file path if necessary.

### Method 2 (recommended approach)
Alternately from root folder you can run the provided python script which uses the template file and generates the input file for each scenario and run the c++ executable file(model)
 for all possible combinations coded in the py script.

This python take two arguments as inputs
- '-a' if you want to run adaptive scenario or if left blank it run constant scenario
- '-o' is to set the name for the output folder, so that all the outputs generated on this run are stored in provided folder_name

As described in the paper you can either run constant insertion scenario where the number of insertions for a given day is average of last 2 months.
```bash
python ./scripts/clean_test_run.py -o output_folder_name
```

You can run adaptive scenario as below
```bash
python ./scripts/clean_test_run.py -a -o output_folder_name
```

So for example, the final output path where the simulations will be stored based on .env variable OUTPUT_DIR ('root/project_name/output') and arguments from python commandline ('output_folder_name') is:
```bash
root/project_name/output/output_folder_name/'{constant/adaptive _insertion_scenario}'/'{trails_starting_year}'/'scenario_identifier'
```
each scenario creates its own sub-folder each containing given number of simulation csv files of experiment outcome over defined period of trial(usually 5 years) and copy of variables that is used to run that scenario.

The scenario sub-folder name consists of four variables
```bash
var1_var2_var3_var4
example: 1.0_31_7_180
var1 is ratio of insertion ( 1.0 )
var2 is start day of insertion ( 31 - begin of february)
var3 is frequency of insertion( 7- every 7 days)
var4 is duration of insertion(180 - 6 months of insertion)
```



### sample input parameters
For example, a scenario starting the model in year 2019 and its release of modified mosquitoes under constant release(0) design in year 2022 for duration of 180 days(6 months) with a frequency of every 7 days with collection factor of 0.246 for release ratios of [1.0,2.0,4.0]
would be as below.

```bash
intervention_start_year = 2022  # year to start the release of modified mosquito
baseline_year           = 2019  # the simulation's calendar epoch (the year corresponding to day 0)
num_sims                = 100   # number of stochastic simulations to run per parameter combination
is_non_constant_scenario = 0    # 0 for constant, 1 for non-constant(adaptive) insertions scenario
scale_factor            = 0.246  # collection factor to convert from number of mosquitoes to trap counts in the surveillance data
random_seed             = 42    # random seed for reproducibility

insertion_ratios        = np.round([1.0, 2.0, 4.0], decimals=1).tolist() # This is the list of insertion ratios to calculate number of mosquitoes to be released with respect to surveillance data
intervention_durations  = [180]  # duration of the intervention in days (e.g., 180 days = 6 months)
insertion_frequencies   = [7]  # number of days between insertions (e.g., 7 = weekly)
```
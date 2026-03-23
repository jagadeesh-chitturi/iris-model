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

## Downloading the necessary files

Clone this repository and its submodules using git:

```bash
git clone https://github.com/jagadeesh-chitturi/gmm-model-project.git
```

## Compiling the GMM model source code

Once you have downloaded all the required source code, header files and input files, you need to configure the required input parameters
for the model present in /data/constant_release_trial_in/model_input_config.csv (template). once the template is configured for all required parameters
you can compile source code and build executable using 'CMakeLists.txt' as below, given you have installed required vcpkg, CMAKE tools

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

 alternately from root folder you can run the provided python script to create a input file by changing required parameters in code which also uses template and runs the model executable file.


```bash
python ./scripts/clean_test_run.py
```

### sample input parameters
For example, a scenario starting the model in year 2019 and its release of modified mosquitoes under constant release(0) design in year 2021 for duration of 180 days(6 months) with a frequency of every 7 days with collection factor of 0.246 for release ratios of [1.0,2.0,4.0]
would be as below.

```bash
intervention_start_year = 2021  # year to start the release of modified mosquito
baseline_year           = 2019  # the simulation's calendar epoch (the year corresponding to day 0)
num_sims                = 100   # number of stochastic simulations to run per parameter combination
is_non_constant_scenario = 0    # 0 for constant, 1 for non-constant(adaptive) insertions scenario
scale_factor            = 0.246  # collection factor to convert from number of mosquitoes to trap counts in the surveillance data
random_seed             = 42    # random seed for reproducibility

output_sub_folder = (
    f"test_2026_script_test_1/constant_insertion_scenario/"
    f"trails_starting_2021/all_months_1_2_4_ratios"

    intervention_durations  = [180]                     # duration of the intervention in days (e.g., 180 days = 6 months)
insertion_frequencies   = [7]                       # number of days between insertions (e.g., 7 = weekly)
```
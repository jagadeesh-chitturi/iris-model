

import pandas as pd
from datetime import datetime
import subprocess
import os
import numpy as np


def run_cpp_with_args(args):
    # Get the directory where the script is located (D:\CEPH_LAB\gmm-model-project\scripts)
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # Move up one level to the project root and then into the build folder
    # This creates: D:\CEPH_LAB\gmm-model-project\build\Debug\mosquito_sim.exe
    cpp_executable = os.path.join(script_dir, "..", "build", "Release", "mosquito_sim.exe")
    
    # Normalize the path for Windows (turns / into \)
    cpp_executable = os.path.normpath(cpp_executable)

    if not os.path.exists(cpp_executable):
        print(f"Error: Executable not found at {cpp_executable}")
        return

    command = [cpp_executable] + args

    try:
        # Changed capture_output to True so you can actually see the C++ error if it fails
        result = subprocess.run(command, capture_output=True, text=True, check=True)
        print(f"C++ simulation finished for: {args[0]}")
    except subprocess.CalledProcessError as e:
        print(f"Error running the C++ code for {args[0]}:", e)
        print("C++ Error Output:", e.stderr)


def is_leap_year(year):
    if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
        return True
    else:
        return False

intervention_start_year=2021

days_before_intervention_start_year=0
for year_val in range(2019,intervention_start_year):
    if is_leap_year(year_val):
        days_before_intervention_start_year+=366
    else:
        days_before_intervention_start_year += 365

num_sims_to_run=100
experiment_sub_folder=f"test_2026_re/sensitivity/trails_starting_{intervention_start_year}/all_months_1_2_4_ratios"
sim_output_file_path=f"D:/CEPH_LAB/mosquito_simulation_starting_2022_output_files/ordered_mcmc_analysis/ordered_MCMC_seed_controlled_outputs/{experiment_sub_folder}/"
# Check if the folder exists
if os.path.exists(sim_output_file_path) and os.path.isdir(sim_output_file_path):
    # Raise an exception if the folder exists
    raise Exception(f"The folder '{sim_output_file_path}' already exists.")
else:
    print(f"The folder '{sim_output_file_path}' does not exist.")

duration_of_intervention=[180]
insertion_frequency=[7]
equilibrium_start_date=[0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334]
# equilibrium_start_date=[59]

day_indices = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334]
month_names_list = [
    'January', 'February', 'March', 'April', 'May', 'June',
    'July', 'August', 'September', 'October', 'November', 'December'
]


df=pd.read_csv(r"D:\CEPH_LAB\mosquito_simulation_starting_2022_output_files\ordered_mcmc_analysis\required_ordered_mcmc_docs\constant_scenario_cpp_input_files\variables_2019_2023_monthly_agg.csv",header=None)
ndf=df.copy()

# input file paths
miami_temperature_file_path = "D:/CEPH_LAB/mosquito_simulation_starting_2022_output_files/ordered_mcmc_analysis/required_ordered_mcmc_docs/constant_scenario_cpp_input_files/19_23_temperature_altered.csv"
miami_carrying_capacity_dates_file_path = "D:/CEPH_LAB/mosquito_simulation_starting_2022_output_files/ordered_mcmc_analysis/required_ordered_mcmc_docs/constant_scenario_cpp_input_files/Miami_carryingcapacity_dates.csv"
miami_mcmc_file_path = "D:/CEPH_LAB/mosquito_simulation_starting_2022_output_files/ordered_mcmc_analysis/required_ordered_mcmc_docs/constant_scenario_cpp_input_files/ordered_rand_100_mcmc.csv"

constant_scenario_surveillance_100_sims_file_path="D:/CEPH_LAB/mosquito_simulation_starting_2022_output_files/ordered_mcmc_analysis/required_ordered_mcmc_docs/constant_scenario_cpp_input_files/supporting_files/sens_2020_2021/2021_each_month_60_day_surveillance_100_sims_vals"
is_non_constant_scenario=0

# Collection factor
scale_factor = 0.246
seed_from_external_input=42

# The grid we want to show in the heatmap
heatmap_ratio_array = np.array([1.0,2.0,4.0])
heatmap_ratio_array = np.round(heatmap_ratio_array, decimals=1)
insertion_ratios=heatmap_ratio_array.tolist()

total_iterations = len(insertion_ratios) * len(equilibrium_start_date) * len(duration_of_intervention) * len(insertion_frequency)
current_iteration = 0

# to-do
#use ratios as first loop then months next
fixed_insertion_val = 0
for insertion_ratio in insertion_ratios:
    for eq in equilibrium_start_date:
        for dur in duration_of_intervention:
            for freq in insertion_frequency:

                ndf.iloc[18,1]=eq+days_before_intervention_start_year ### as the intervention start date should account for the years before as well
                ndf.iloc[29,1]=fixed_insertion_val
                ndf.iloc[22,1]=num_sims_to_run
                ndf.iloc[14,1]=freq
                ndf.iloc[28,1]=dur

                ndf.iloc[34,1]=miami_temperature_file_path
                ndf.iloc[35,1]=miami_carrying_capacity_dates_file_path
                ndf.iloc[36,1]=miami_mcmc_file_path

                ndf.iloc[62,1]=is_non_constant_scenario
                ndf.iloc[63,1]="not_required"
                ndf.iloc[64,1]=insertion_ratio
                ndf.iloc[65,1]=scale_factor

                surveillance_data_matrix_file_path_constant_scenario = f'{constant_scenario_surveillance_100_sims_file_path}/{month_names_list[day_indices.index(eq)]}_surveillance.csv'
                ndf.iloc[66,1]=surveillance_data_matrix_file_path_constant_scenario
                ndf.iloc[67,1]=seed_from_external_input

                fi_name=f"{insertion_ratio}_{eq}_{freq}_{dur}"
                new_folder_path=sim_output_file_path+fi_name
                ndf.iloc[27,1]=new_folder_path+'/'

                # Create the folder
                os.makedirs(new_folder_path)
                csv_filepath=new_folder_path+'/'+'variables_'+fi_name+'.csv'
                ndf.to_csv(csv_filepath,index=False,header=False)
                arguments_to_send = [csv_filepath, "arg1", "arg2","arg3"]  # Replace with your desired command-line arguments
                run_cpp_with_args(arguments_to_send)

                current_iteration += 1
                print(f"Progress: {current_iteration}/{total_iterations} simulations completed.")
                # print(f"{eq}-------{insertion_val}")

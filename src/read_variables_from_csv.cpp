#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <mosq_vars_header.h>
#include <read_variables_from_csv.h>
using namespace std;


/**
 * @brief Function for reading variable values from CSV files.
 *
 * @param filename_csv Name of the CSV file to read from.
 * @param env_1 Reference to the mosq_vars object to store the read values in.
 *
 * This function reads the values from the CSV file and assigns them to the variables in the env_1 object.
 * The function also checks if the file can be opened and prints an error message if not.
 * The function then reads the values from the CSV file and assigns them to the variables in the env_1 object.
 * The function finally prints out the values that were read from the CSV file.
 */
void read_variables(string filename_csv,mosq_vars& env_1) //function for reading varible values from CSV files.
{
	string fname;
	cout << "\n enter the variables file name with .csv extension: ";
	vector<string> vals;
	vector<string> vals1;
	string line, word;

	fstream file(filename_csv, ios::in);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			stringstream str(line);
			while (getline(str, word, ','))
				vals.push_back(word);
		}
	}
	else
		cout << "Could not open the file\n";


	//reading positional values from csv file and assigning to variables in env_1 
	cout << "\n starting to read data from CSV";

	env_1.initial_mosqs = stoi(vals.at(1));
	env_1.max_larve_cap = stoi(vals.at(3));
	env_1.mate_prob = stof(vals.at(5));
	env_1.treated_prob = stof(vals.at(7));
	env_1.female_death_prob = stof(vals.at(9));
	env_1.male_death_prob = stof(vals.at(11));
	env_1.egg_death_prob = stof(vals.at(13));
	env_1.larve_death_prob = stof(vals.at(15));
	env_1.pupe_death_prob = stof(vals.at(17));
	env_1.gender_prob = stof(vals.at(19));
	env_1.find_male_prob = stof(vals.at(21));
	env_1.egg_next_stg_prob = stof(vals.at(23));
	env_1.larve_next_stage_prob = stof(vals.at(25));
	env_1.pupe_next_stage_prob = stof(vals.at(27));
	env_1.intrvl_of_days_to_add_treated_mosq = stoi(vals.at(29));
	env_1.ratio_males_DD_add = stof(vals.at(31));
	env_1.num_of_days_to_expmnt = stoi(vals.at(33));
	env_1.num_of_times_in_each_day = stoi(vals.at(35));
	env_1.equlibrium_days = stoi(vals.at(37));
	env_1.max_egg_cap = stoi(vals.at(39));
	env_1.linear_egg_cap = stoi(vals.at(41));
	env_1.output_filename = (string)(vals.at(43));
	env_1.num_of_simulations_to_run = stoi(vals.at(45));
	env_1.sim_initial_egg_ratio = stof(vals.at(47));
	env_1.sim_initial_larve_ratio = stof(vals.at(49));
	env_1.sim_initial_pupe_ratio = stof(vals.at(51));
	env_1.sim_initial_adult_ratio = stof(vals.at(53));
	env_1.output_filepath = (string)(vals.at(55));
	env_1.duration_intervention = stoi(vals.at(57));
	env_1.fixed_num_DD_insertions = stoi(vals.at(59));
	env_1.larve_insertion_start_day = stoi(vals.at(61));
	env_1.larve_insertion_end_day = stoi(vals.at(63));
	env_1.proportion_larve_to_kill = stof(vals.at(65));
	env_1.freq_days_of_larve_ciding = stoi(vals.at(67));
	env_1.miami_temperature_file_path = (string)(vals.at(69));
	env_1.miami_carrying_capacity_dates_file_path = (string)(vals.at(71));
	env_1.miami_mcmc_file_path = (string)(vals.at(73));
	env_1.is_mcmc_simulation = stoi(vals.at(75));
	env_1.week_length = stoi(vals.at(77));
	env_1.start_mcmc_day = stoi(vals.at(79));
	env_1.end_mcmc_day = stoi(vals.at(81));
	env_1.emperical_data_file_path = (string)(vals.at(83));
	env_1.CC_1 = stod(vals.at(85));
	env_1.CC_2 = stod(vals.at(87));
	env_1.CC_3 = stod(vals.at(89));
	env_1.CC_4 = stod(vals.at(91));
	env_1.CC_eggs = stod(vals.at(93));
	env_1.std_dev_CC_1 = stod(vals.at(95));
	env_1.std_dev_CC_2 = stod(vals.at(97));
	env_1.std_dev_CC_3 = stod(vals.at(99));
	env_1.std_dev_CC_4 = stod(vals.at(101));
	env_1.std_dev_CC_eggs = stod(vals.at(103));
	env_1.std_dev_over_disp = stod(vals.at(105));
	env_1.read_over_disperssion = stod(vals.at(107));
	env_1.num_mcmc_iters = stoi(vals.at(109));
	env_1.mcmc_outputfile_path = (string)(vals.at(111));
	env_1.max_mcmc_cand_reject_cap = stoi(vals.at(113));
	env_1.weekly_mcmc_female_file_path = (string)(vals.at(115));
	env_1.monthly_imperical_data_file_path = (string)(vals.at(117));
	env_1.model_monthly_female_file_path_output = (string)(vals.at(119));
	env_1.model_start_year = stoi(vals.at(121));
	env_1.all_years_max_emp_year_month_row_count_value = stoi(vals.at(123));
	env_1.is_non_constant_insertion_scenario = stoi(vals.at(125));
	env_1.surveillance_data_matrix_file_path = (string)(vals.at(127));
	env_1.ratio_of_insertion = stod(vals.at(129));
	env_1.andre_scaling_value = stod(vals.at(131));
	env_1.constant_scenario_specific_month_100_sims_surveil_data_csv_filepath = (string)(vals.at(133));
	env_1.seed_from_external_input = stoi(vals.at(135));
	env_1.male_fitness = stof(vals.at(137));
	env_1.step_size = 0.1;// to calculate step size.
}

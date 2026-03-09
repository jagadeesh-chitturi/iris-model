
#pragma warning(suppress : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include <gsl/gsl_version.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_randist.h>

#include <chrono> // Precise time reporting
#include<vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <chrono>
#include<iomanip>


#include <mosq_vars_header.h>

#include <add_mosqs_function.h>
using namespace std;
using std::cout;

int mosq_count = 0;
//--checking--int pause_for_interupt;
//--checking--int file_counter = 0;
int global_zero_mosq = 0;

//struct Parameters* p2;



vector <mosq*> male_vector;
vector <mosq*> egg_vector;
vector <mosq*> larve_vector;
vector <mosq*> pupe_vector;
vector <mosq*> female_vector;

vector <int> male_count;
vector <int> female_count;
vector <int> egg_count;
vector <int> larve_count;
vector <int> pupe_count;
vector <int> time_count;

vector <int> DD_mate_count_vect;
vector <int> DR_mate_count_vect;
vector <int> RR_mate_count_vect;


vector <int> larve_ids;
vector <int> egg_ids;

vector <int> Male_DD;
vector <int> Male_count_DD;
vector <int> Male_DR;
vector <int> Male_count_DR;
vector <int> Male_RR;
vector <int> Male_count_RR;

vector <int> eggs_female_vector;
vector <int> eggs_male_RR_vector;
vector <int> eggs_male_DR_vector;

vector <double> female_ratio;
vector <double> male_ratio;
vector <double> larve_ratio;
vector <double> pupe_ratio;

vector <int> emp_data_weekly_female;
vector <int> emp_data_week_number;



struct mosq* prev_mosq;



struct mosq* curr_mosq;
struct mosq* last_mosq;

struct mosq* head = NULL; //the head of the mosquito list
struct mosq* temp = NULL;	//the tail of mosquito list
struct mosq* next_mosq = NULL;


mosq_vars env_1;
MCMC_vars env_mcmc;

std::map<std::string, std::vector<double>> CC_map; //vector for storing  
std::vector<std::string> column_names_vect;






int main(int argc, char* argv[]) {	// 	main function to run the model and takes path to the input csv file from argv[1]

	// to check the runtime of the model for efficiency tracking
	auto start_time_main_bfor_MCMC = std::chrono::high_resolution_clock::now();

	//reading files.
	cout << "\n variables read..";
	read_variables(argv[1],env_1); //to read input variables from csv file through arguments

	cout << "\n reading of variables completed";

	// checking if initial eggs are greater than zero
	if (env_1.initial_mosqs < 0) {
		cout << "\n initial mosquitoes are less than zero. so stoping program";
		return 0;
	}

	// for reading monthly imperical data
	vector <int> emp_data_monthly_female;
	vector <int> emp_data_month_number;
	vector <int> emp_data_year_number;
	vector <int> emp_data_monthly_row_count;

	// if it is mcmc simulation, read imperical data for likelihood calculation and then run MCMC, else run the model with CC vals from csv file.
	if (env_1.is_mcmc_simulation == 1) {
		read_imperical_monthly_data_frm_csv(env_1.monthly_imperical_data_file_path, emp_data_year_number, emp_data_month_number, emp_data_monthly_female, emp_data_monthly_row_count);
		cout << "\n month numbers are and emperical values are: ";
		for (int icheck = 0; icheck < emp_data_month_number.size(); icheck++) {
			cout << "\n " << emp_data_year_number[icheck] << "\t" << emp_data_month_number[icheck] << " ---- " << emp_data_monthly_female[icheck] << "\t" << emp_data_monthly_row_count[icheck];
		}
	}

	//for Carrying capacity(CC) and dates reading 
	std::vector<string> vect_CC_list;
	std::vector<string> vect_date_string_start;
	std::vector<std::chrono::system_clock::time_point> date_vector_start;

	std::vector<string> vect_date_string_end;
	std::vector<std::chrono::system_clock::time_point> date_vector_end;
	import_care_cap_and_dates_data(env_1.miami_carrying_capacity_dates_file_path.c_str(), vect_CC_list, vect_date_string_start, vect_date_string_end, date_vector_start, date_vector_end);
	cout << "\n reading care_cap and dates is done\n";

	// checking epoch values of cc and dates file
	// for start date of carrying capacity to allign with model start date using epoch time
	std::time_t start_date_CC_for_epoch = std::chrono::system_clock::to_time_t(date_vector_start.at(0));
	std::tm* local_time_start_date_for_epoch = std::gmtime(&start_date_CC_for_epoch);
	std::cout << "\n the start date is: " << std::put_time(local_time_start_date_for_epoch, "%d-%m-%Y") << " ";
	std::cout << "\nEpoch start date value in main is: " << start_date_CC_for_epoch << std::endl;

	std::time_t end_date_CC_for_epoch = std::chrono::system_clock::to_time_t(date_vector_end.at(0));
	std::tm* local_time_end_date_for_epoch = std::gmtime(&end_date_CC_for_epoch);
	std::cout << "\n the end date is: " << std::put_time(local_time_end_date_for_epoch, "%d-%m-%Y") << " ";
	std::cout << "\nEpoch end date value in main is: " << end_date_CC_for_epoch << std::endl;

	// to store date and temperature values read from csv.
	vector<double> vect_temp;
	vector<string> vect_date_string;
	vector<std::chrono::system_clock::time_point> date_vector;

	//to read temperature and dates
	import_date_and_temp_data(env_1.miami_temperature_file_path.c_str(), vect_date_string, vect_temp, date_vector);		
	cout << "\n the number of temp readings are : " << env_1.num_of_temperature_values << endl;

	for (auto ir = vect_temp.rbegin(); ir != vect_temp.rend(); ++ir)
	{
		//cout << *ir << " ";
		env_1.num_of_temperature_values++;
	}

	cout << "\n the number of temp readings are : " << env_1.num_of_temperature_values << endl;

	//checking if it is MCMC simulation or not, if yes then run MCMC, else run the model with CC vals from csv file.
	if (env_1.is_mcmc_simulation == true) { 

		//for first run
		std::string temp_col_name;
		using double_vector = std::vector<double>;
		
		cout << "\n the unique CC vals are: \n";
		//set data_struc for getting unique values if CC's names
		set<string> unique_CC_vals(vect_CC_list.begin(), vect_CC_list.end()); 
		for (const auto& str : unique_CC_vals) {
			std::cout << str << std::endl;
		}

		for (const auto& str : unique_CC_vals) {// creating map for each unique
			std::cout << str << std::endl;
			env_mcmc.mcmc_column_names_vect.push_back(str);
		}
		env_mcmc.mcmc_column_names_vect.push_back("eggs");


		/*env_mcmc.mcmc_column_names_vect.push_back("CC_1");
		env_mcmc.mcmc_column_names_vect.push_back("CC_2");
		env_mcmc.mcmc_column_names_vect.push_back("CC_3");
		env_mcmc.mcmc_column_names_vect.push_back("CC_4");
		env_mcmc.mcmc_column_names_vect.push_back("eggs");*/ //pausing for unique cc val

		int num_of_columns = env_mcmc.mcmc_column_names_vect.size();// num of columns in csv file

		for (int col_iter = 0; col_iter < num_of_columns; col_iter++) {
			temp_col_name = env_mcmc.mcmc_column_names_vect.at(col_iter);
			env_mcmc.mcmc_values_map_vector[temp_col_name] = double_vector();
		}

		//vector for cc_vals from csv file for first run of MCMC
		env_mcmc.mcmc_values_map_vector["CC_1"].push_back(env_1.CC_1);
		env_mcmc.mcmc_values_map_vector["CC_2"].push_back(env_1.CC_2);
		env_mcmc.mcmc_values_map_vector["CC_3"].push_back(env_1.CC_3);
		env_mcmc.mcmc_values_map_vector["CC_4"].push_back(env_1.CC_4);
		//env_mcmc.mcmc_values_map_vector["CC_5"].push_back(env_1.CC_5);
		env_mcmc.mcmc_values_map_vector["eggs"].push_back(env_1.CC_eggs);
		env_mcmc.over_disperssion_cand = env_1.read_over_disperssion;
		
		//getting values for std_dev_from csv
		env_mcmc.std_dev_cc1 = env_1.std_dev_CC_1;
		env_mcmc.std_dev_cc2 = env_1.std_dev_CC_2;
		env_mcmc.std_dev_cc3 = env_1.std_dev_CC_3;
		env_mcmc.std_dev_cc4 = env_1.std_dev_CC_4;
		//env_mcmc.std_dev_cc5 = env_1.std_dev_CC_5;
		env_mcmc.std_dev_eggs = env_1.std_dev_CC_eggs;
		env_mcmc.std_dev_over_disp = env_1.std_dev_over_disp;


		//making the initial values as candidate values for MCMC for first run
		env_mcmc.cc1_cand = env_1.CC_1;
		env_mcmc.cc2_cand = env_1.CC_2;
		env_mcmc.cc3_cand = env_1.CC_3;
		env_mcmc.cc4_cand = env_1.CC_4;
		//env_mcmc.cc5_cand = env_1.CC_5;
		env_mcmc.eggs_cand = env_1.CC_eggs;

		//assigning latest mcmc values to run model
		column_names_vect = env_mcmc.mcmc_column_names_vect;
		CC_map = env_mcmc.mcmc_values_map_vector;

		int num_cols_in_MCMC_csv = column_names_vect.size();
		cout << "\n\n\nfirst run in main func, the egg vector has values\n\n\n";
		for (int icheck = 0; icheck < CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].size(); icheck++) {
			cout << " \n -  " << CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].at(icheck);
		}

		//running the model for first run of MCMC with initial values from csv file
		main_function_logic(vect_CC_list,vect_date_string_start,date_vector_start, vect_date_string_end,date_vector_end, vect_temp, vect_date_string, date_vector, emp_data_year_number, emp_data_month_number, emp_data_monthly_female,emp_data_monthly_row_count);

		//checking if cand is nan or value
		try {
			if (isnan(env_mcmc.cand_like_lihod)) {
				throw runtime_error("Error value is NaN..... it is negative infifnity");
			}
			
		}
		catch (const runtime_error& e) {
			cerr << "\ncaught runtime_error for NaN error: ..... it is negative infifnity" << e.what();
		}

		//Since it is first run, we will assign cand values to curr values and then start the MCMC iterations, for next runs, cand and curr values will be updated inside the RUN_MCMC function based on acceptance or rejection of candidate values.
		//assigning cand to curr
		env_mcmc.curr_like_lihod = env_mcmc.cand_like_lihod;

		cout << "\n\n\n\n updating MCMC values\n\n\n\n";


		//updating other curr vals.
		env_mcmc.cc1_curr = env_mcmc.cc1_cand;
		env_mcmc.cc2_curr = env_mcmc.cc2_cand;
		env_mcmc.cc3_curr = env_mcmc.cc3_cand;
		env_mcmc.cc4_curr = env_mcmc.cc4_cand;
		//env_mcmc.cc5_curr = env_mcmc.cc5_cand;
		env_mcmc.eggs_curr = env_mcmc.eggs_cand;
		env_mcmc.over_disperssion_curr = env_mcmc.over_disperssion_cand;

		cout << "\n " << env_mcmc.cc1_cand << "\t " << env_mcmc.cc1_curr << "\t " << env_mcmc.cc2_cand << "\t " << env_mcmc.cc2_curr << "\t " << env_mcmc.cc3_cand << "\t " << env_mcmc.cc3_curr << "\t " << env_mcmc.cc4_cand << "\t " << env_mcmc.cc4_curr << "\t " <<env_mcmc.cc5_cand << "\t " << env_mcmc.cc5_curr << "\t " << env_mcmc.eggs_cand << "\t " << env_mcmc.eggs_curr << "\t " << env_mcmc.over_disperssion_cand << "\t " << env_mcmc.over_disperssion_curr << "\t " << env_mcmc.cand_like_lihod << "\t " << env_mcmc.curr_like_lihod;


		// writing the first run values to csv file before starting MCMC iterations
		std::ofstream csvFile_mcmc_1st_run(env_1.mcmc_outputfile_path, ios::out);

		if (!csvFile_mcmc_1st_run.is_open()) {
			std::cerr << "Error opening file! MCMC writer error in main()" << std::endl;
			return 0;
		}

			//csvFile << "iter_num" << "," << "CC1_cand" << "," << "cc1_curr" << "," << "cc2_cand" << "," << "cc2_curr" << "," << "cc3_cand" << "," << "cc3_curr" << "," << "cc4_cand" << "," << "cc4_curr" << "," << "cc5_cand" << "," << "cc5_curr" << "," << "egg_cand" << "," << "egg_curr" << "," << "over_disp_cand" << "," << "over_disp_curr" << "," << "cand_liklihood" << "," << "curr_likelihood" << "\n";

		csvFile_mcmc_1st_run << "iter_num" << "," << "CC1_cand" << "," << "cc1_curr" << "," << "cc2_cand" << "," << "cc2_curr" << "," << "cc3_cand" << "," << "cc3_curr" << "," << "cc4_cand" << "," << "cc4_curr" << "," << "egg_cand" << "," << "egg_curr" << "," << "over_disp_cand" << "," << "over_disp_curr" << "," << "cand_liklihood" << "," << "curr_likelihood" << "\n";


		csvFile_mcmc_1st_run.close();


		//Starting MCMC iterations
		for(int mcmc_iter=1;mcmc_iter<env_1.num_mcmc_iters;mcmc_iter++){

			env_mcmc.itr_num = mcmc_iter;
			RUN_MCMC(vect_CC_list, vect_date_string_start, date_vector_start, vect_date_string_end, date_vector_end, vect_temp, vect_date_string, date_vector, emp_data_year_number, emp_data_month_number, emp_data_monthly_female, emp_data_monthly_row_count);
			cout << "\n " <<env_mcmc.itr_num<<"\t" << env_mcmc.cc1_cand << "\t " << env_mcmc.cc1_curr << "\t " << env_mcmc.cc2_cand << "\t " << env_mcmc.cc2_curr << "\t " << env_mcmc.cc3_cand << "\t " << env_mcmc.cc3_curr << "\t " << env_mcmc.cc4_cand << "\t " << env_mcmc.cc4_curr << "\t " << env_mcmc.eggs_cand << "\t " << env_mcmc.eggs_curr << "\t " << env_mcmc.over_disperssion_cand << "\t " << env_mcmc.over_disperssion_curr << "\t " << env_mcmc.cand_like_lihod << "\t " << env_mcmc.curr_like_lihod;
			if (global_zero_mosq == 1) {// try catch throw : when there are zero mosq, this will exit the loop and send data to files.
				cout << "\n exiting the MAIN function as RUN_mcmc has values that leads to early death of mosquiotes\n";
			}
			MCMC_csv_writer();

			// testing monthly
			cout << "\n after the " << env_mcmc.itr_num << " ---is :\n";
			for (int icheck = 0; icheck < emp_data_month_number.size(); icheck++) {
				cout << "\n " << emp_data_month_number[icheck] << " ---- " << emp_data_monthly_female[icheck];
			}
			
		}
	}
	else {
		read_CC_vals_by_map(column_names_vect, CC_map);
		main_function_logic(vect_CC_list, vect_date_string_start, date_vector_start, vect_date_string_end, date_vector_end, vect_temp, vect_date_string, date_vector, emp_data_year_number, emp_data_month_number, emp_data_monthly_female, emp_data_monthly_row_count);
	}

	auto end_time_main_after_MCMC = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time_main_after_MCMC - start_time_main_bfor_MCMC);
	cout << "\n the time to run entire MCMC iters :" << duration.count() << " seconds";
}
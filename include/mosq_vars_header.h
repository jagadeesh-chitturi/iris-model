#pragma once
#ifndef MOSQ_VARS_HEADER_H
#define MOSQ_VARS_HEADER_H
#include<string>
#include<iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_randist.h>
#include<vector>
#include <map>
#include<cmath>
#include <fstream>
#include <sstream>
using namespace std;

struct mosq {
	int mosq_id;
	short int status; //stage of mosquito like larve, eggs, male... egg=0, larve=1, pupa=2, adult=3.
	bool is_female; //is mosquito male or female
	bool is_treated; //if the mosquito is treated or not(wild or treated)
	bool is_mated;	//if the mosquito is ever mated
	short int gene_stat; //checks status of genes of mosquito like DD(Treated)=2, DR(gen_1)=1, RR(Wild)=0
	struct mosq* next;	//pointer for next location
};

struct mosq_vars {
	int initial_mosqs = 40;
	int total_time = 2; //initial value to loop over time
	unsigned int k = 1;	// randomness of initial mosquito death
	unsigned int mate_oc, next_stg_oc;
	unsigned int treated_oc, gender_oc, death_oc, find_male_oc, linear_egg_oc;
	unsigned long int male_rndm_mosq, no_of_male, max_larve_cap = 15; //caring capacity larve cap 10000
	float mate_prob = 0.9;
	float treated_prob = 0.8, female_death_prob = 0.2, male_death_prob = 0.2, egg_death_prob = 0.2, larve_death_prob = 0.2, pupe_death_prob = 0.2, initial_mate_prob = 0.001;
	float gender_prob = 0.5, death_prob = 0.2, find_male_prob = 0.8, next_stg_prob = 0.9, egg_next_stg_prob = 0.9, larve_next_stage_prob = 0.9, pupe_next_stage_prob = 0.9;
	int death_count = 0;
	int intrvl_of_days_to_add_treated_mosq, num_of_days_to_expmnt, num_of_times_in_each_day;
	int num_of_mosq_to_add;
	double step_size;
	int equlibrium_days, max_egg_cap, adult_males_on_equibrilium = 0, DR_mate_cntr = 0, DD_mate_cntr = 0, RR_mate_cntr = 0, linear_egg_cap = 0, global_egg_count = 0;
	string output_filename, output_filepath;
	int num_of_simulations_to_run; //num of simulations to loop
	int num_of_temperature_values = 0, duration_intervention;
	float sim_initial_egg_ratio, sim_initial_larve_ratio, sim_initial_pupe_ratio, sim_initial_adult_ratio, ratio_males_DD_add;
	int fixed_num_DD_insertions = 0;

	//for larve ciding
	int larve_insertion_start_day = 0, larve_insertion_end_day = 0, freq_days_of_larve_ciding;
	float proportion_larve_to_kill;


	// for mcmc
	string miami_temperature_file_path,miami_carrying_capacity_dates_file_path,miami_mcmc_file_path;
	const char* car_cap_file;
	bool is_mcmc_simulation;
	int week_length, start_mcmc_day, end_mcmc_day;
	string emperical_data_file_path;
	double CC_1, CC_2, CC_3, CC_4, CC_eggs, std_dev_CC_1, std_dev_CC_2, std_dev_CC_3, std_dev_CC_4, std_dev_CC_eggs,std_dev_over_disp, CC_5, std_dev_CC_5;
	double read_over_disperssion;
	int num_mcmc_iters;
	string mcmc_outputfile_path;
	int max_mcmc_cand_reject_cap;
	int model_start_day;
	string weekly_mcmc_female_file_path;
	string monthly_emperical_data_file_path;
	string model_monthly_female_file_path_output;
	int model_start_year;
	int all_years_max_emp_year_month_row_count_value = 0;
	bool is_non_constant_insertion_scenario;
	string surveillance_data_matrix_file_path;
	double ratio_of_insertion, andre_scaling_value;
	string constant_scenario_specific_month_100_sims_surveil_data_csv_filepath;
	int seed_from_external_input;
	float male_fitness;
};




struct MCMC_vars {
	//mcmc variables
	double std_dev_cc1 = 0, std_dev_cc2 = 0, std_dev_cc3 = 0, std_dev_cc4 = 0, std_dev_cc5 = 0, std_dev_eggs = 0, std_dev_over_disp=0; //5

	string mcmc_output_filepath;
	int itr_num=0;
	long double curr_like_lihod=0, cand_like_lihod=0;
	double cc1_curr, cc2_curr, cc3_curr, cc4_curr, cc5_curr, eggs_curr;
	double cc1_cand, cc2_cand, cc3_cand, cc4_cand, cc5_cand, eggs_cand;
	std::map<std::string, std::vector<double>> mcmc_values_map_vector;
	std::vector<std::string> mcmc_column_names_vect;
	double over_disperssion_curr,over_disperssion_cand;
	int mcmc_cand_reject_cntr=0;
};

struct month_year {
	int year;
	int month;
};


extern int mosq_count;
extern int global_zero_mosq;

extern struct Parameters* p2;





extern vector <mosq*> male_vector;
extern vector <mosq*> egg_vector;
extern vector <mosq*> larve_vector;
extern vector <mosq*> pupe_vector;
extern vector <mosq*> female_vector;

extern vector <int> male_count;
extern vector <int> female_count;
extern vector <int> egg_count;
extern vector <int> larve_count;
extern vector <int> pupe_count;
extern vector <int> time_count;

extern vector <int> DD_mate_count_vect;
extern vector <int> DR_mate_count_vect;
extern vector <int> RR_mate_count_vect;


extern vector <int> larve_ids;
extern vector <int> egg_ids;

extern vector <int> Male_DD;
extern vector <int> Male_count_DD;
extern vector <int> Male_DR;
extern vector <int> Male_count_DR;
extern vector <int> Male_RR;
extern vector <int> Male_count_RR;

extern vector <int> eggs_female_vector;
extern vector <int> eggs_male_RR_vector;
extern vector <int> eggs_male_DR_vector;

extern vector <double> female_ratio;
extern vector <double> male_ratio;
extern vector <double> larve_ratio;
extern vector <double> pupe_ratio;

extern vector <int> emp_data_weekly_female;
extern vector <int> emp_data_week_number;



extern struct mosq* prev_mosq;



extern struct mosq* curr_mosq;
extern struct mosq* last_mosq;

extern struct mosq* head; //the head of the mosquito list
extern struct mosq* temp;	//the tail of mosquito list
extern struct mosq* next_mosq;


extern mosq_vars env_1;
extern MCMC_vars env_mcmc;


extern std::map<std::string, std::vector<double>> CC_map; //vector for storing  
extern std::vector<std::string> column_names_vect;


#endif



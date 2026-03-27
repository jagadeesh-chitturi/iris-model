#ifndef ADD_MOSQS_FUNCTION_H
#define ADD_MOSQS_FUNCTION_H

#pragma warning(suppress : 4996)
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<string>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_randist.h>
#include <chrono> // Precise time reporting.
#include<vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <chrono>
#include<iomanip>
#include <filesystem>
namespace fs = std::filesystem;

#include"mosq_vars_header.h"
#include <map>

#include <vector>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include<string>
#include <chrono>
#include<iomanip>
#include<limits>
#include <set>

#include"read_variables_from_csv.h"

#include <stdexcept>
#define SEED_NONE 0
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


struct Parameters {
    double d_E = 0, d_L = 0, d_P = 0, d_A = 0, m_E = 0, m_L = 0, m_P = 0, m_A = 0, t_delta = 0.1;

};

using int_gsl_seed = unsigned long int;




void add_mosq(int new_status, bool is_female_new, bool is_treated_new, bool is_mated_new, int gene_stat_new);
void prnt_vectr(vector <mosq*> inp_vect, string gender);
void prnt_all_vect();
void show_mosqs();
std::string doubleToString(double value);
void write_double_CSV(const std::vector<double>& data, const std::string& filename);
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset);
void write_d_csv(std::string filename, std::vector<std::pair<std::string, std::vector<double>>> dataset);
void will_mosq_die(gsl_rng* _RNG_P);
void mosq_nxt_stg(gsl_rng* _RNG_P);
void female_mating(gsl_rng* _RNG_P);
void larve_id_coll_and_shuff();
void egg_id_coll_and_shuff();
void kill_excess_larve(gsl_rng* _RNG_P);
void kill_excess_eggs(gsl_rng* _RNG_P);
void kill_excess_rndm_eggs(gsl_rng* _RNG_P);
void deleteList(mosq*& del_head);
void add_treated_male(int mosq_count);
bool comparePtrToNode(mosq* a, mosq* b);
void create_initial_mosquitoes(int initial_larve_agents_frm_ratio, int initial_pupe_agents_frm_ratio, int initial_adult_female_agents_frm_ratio, int initial_adult_male_agents_frm_ratio, gsl_rng* _RNG_P);
void kill_by_larve_ciding(gsl_rng* _RNG_P);


int alloc_and_setup_gsl_random_generator();
int_gsl_seed seed_gsl_random_generator(int_gsl_seed seed);
uint64_t get_time_microsseconds();

void main_function_logic(std::vector<string>& vect_CC_list, std::vector<string>& vect_date_string_start, std::vector<std::chrono::system_clock::time_point>& date_vector_start, std::vector<string>& vect_date_string_end, std::vector<std::chrono::system_clock::time_point>& date_vector_end, vector<double>& vect_temp, vector<string>& vect_date_string, vector<std::chrono::system_clock::time_point>& date_vector, vector <int>& emp_data_year_number, vector <int>& emp_data_month_number, vector <int>& emp_data_monthly_female_main, vector <int>& emp_data_monthly_row_count);

int get_num_lines_csv(std::string file_name);
void import_care_cap_and_dates_data(const char* fname, std::vector<string>& vect_CC_list, std::vector<string>& vect_date_string_start, std::vector<string>& vect_date_string_end, std::vector<std::chrono::system_clock::time_point>& date_vector_start, std::vector<std::chrono::system_clock::time_point>& date_vector_end);
void read_line_check_size_CC(char* buf, int size, FILE* fp);


void eggDevelopmentAegypti(Parameters* p, double temperature); /* Function for Calculating the Egg development rate - Aegypti */
void larvaeDevelopmentAegypti(Parameters* p, double temperature); /* Function for Calculating the Larvae development rate - Aegypti */
void pupaeDevelopmentAegypti(Parameters* p, double temperature); /* Function for Calculating the Pupae development rate - Aegypti */
void adultDevelopmentAegypti(Parameters* p, double temperature); /* Function for Calculating the Adult development rate - Aegypti */

void eggMortalityAegypti(Parameters* p, double temperature); /* Function for Calculating the Egg mortality rate - Aegypti */
void larvaeMortalityAegypti(Parameters* p, double temperature); /* Function for Calculating the Larvae mortality rate - Aegypti */
void pupaeMortalityAegypti(Parameters* p, double temperature); /* Function for Calculating the Pupae mortality rate - Aegypti */
void adultMortalityAegypti(Parameters* p, double temperature); /* Function for Calculating the Adult mortality rate - Aegypti */


#define MAX_DAYS 365

void import_date_and_temp_data(const char* fname, vector<string>& vect_date_string, std::vector<double>& vect_temps, std::vector<std::chrono::system_clock::time_point>& date_vector);

class FileNotOpenedException : public std::runtime_error {
public:
    explicit FileNotOpenedException(const std::string& message)
        : std::runtime_error(message) {}
};

class InputException : public std::runtime_error {
public:
    explicit InputException(const std::string& message)
        : std::runtime_error(message) {}
};

int line_counter_in_csv(std::string file_name);

//not using this function any more
//void read_CC_vals(std::vector<std::vector<double>>& CC_list_vectors);
void read_CC_vals_by_map(std::vector<std::string>& column_names_vect, std::map<std::string, std::vector<double>>& CC_map);
void read_line_check_size(char* buf, int size, FILE* fp);


void RUN_MCMC(std::vector<string>& vect_CC_list, std::vector<string>& vect_date_string_start, std::vector<std::chrono::system_clock::time_point>& date_vector_start, std::vector<string>& vect_date_string_end, std::vector<std::chrono::system_clock::time_point>& date_vector_end, vector<double>& vect_temp, vector<string>& vect_date_string, vector<std::chrono::system_clock::time_point>& date_vector, vector <int>& emp_data_year_number, vector <int>& emp_data_month_number, vector <int>& emp_data_monthly_female, vector <int>& emp_data_monthly_row_count);

void calc_likelihood();
void read_emperical_data_frm_csv(string filename);
void MCMC_csv_writer();


void weekly_MCMC_female_csv_writer(vector<int>& model_weekly_calc_female);

//for reading monthly emperical data
void read_imperical_monthly_data_frm_csv(string filename, vector <int>& emp_data_year_number, vector<int>& emp_data_month_number, vector<int>& emp_data_monthly_female, vector <int>& emp_data_monthly_row_count);
bool isLeapYear(int year);
int getMonthFromDay(int dayNumber, int year);
int get_adult_female_count();
void monthly_MCMC_female_csv_writer(map<int, map<int, int>>& model_year_month_value);
month_year getDateFromDayNumber(int dayNumber);
bool isLeapYear_for_month_agg(int year);
vector<vector<double>> read_surveil_data_matrix_from_csv(const string& filePath);
bool get_value_from_surveil_data_matrix(const vector<vector<double>>& matrix, int rowIndex, int colIndex, double& specific_day_surveil_value);
vector<double> read_constant_scenario_specific_month_100_sims_surveil_data_from_csv(const string& filePath);
#endif // !ADD_MOSQS_FUNCTION_H

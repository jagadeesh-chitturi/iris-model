#include <add_mosqs_function.h>
#include <mosq_vars_header.h>
#include <gsl/gsl_rng.h>



static gsl_rng* _RNG_P;

/************* 
 * @brief Adds a mosquito to the environment
 * @details This function adds a mosquito or egg to the environment.
 * It updates the status of the mosquito and adds it to the correct
 * vector based on its status.
 * @param new_status The status of the mosquito (0 = egg, 1 = larva, 2 = pupa, 3 = adult)
 * @param is_female_new Whether the mosquito is female or not
 * @param is_treated_new Whether the mosquito has been treated or not
 * @param is_mated_new Whether the mosquito has mated or not
 * @param gene_stat_new The status of the mosquito's genes (0 = wild, 1 = resistant, 2 = susceptible)

/*******  f1ff6505-d994-419c-a382-01d0a42ab083  *******/	
void add_mosq(int new_status, bool is_female_new, bool is_treated_new, bool is_mated_new, int gene_stat_new) { //adds mosquioes or eggs to the environment
	mosq* new_mosq = new mosq;
	mosq_count += 1;
	new_mosq->mosq_id = mosq_count;
	new_mosq->status = new_status;
	new_mosq->is_female = is_female_new;
	new_mosq->is_treated = is_treated_new;
	new_mosq->is_mated = is_mated_new;
	new_mosq->gene_stat = gene_stat_new;

	new_mosq->next = NULL;

	//updating each vector of their own status
	switch (new_status) {
	case 0:
		egg_vector.push_back(new_mosq);
		break;
	case 1:
		larve_vector.push_back(new_mosq);
		break;
	case 2:
		pupe_vector.push_back(new_mosq);
		break;
	case 3:
		if (is_female_new == true) {
			female_vector.push_back(new_mosq);
		}
		else {
			male_vector.push_back(new_mosq);
		}
		break;
	}

	if (head == NULL) { //adding mosquito to the head if it is first mosq
		head = new_mosq;
		last_mosq = new_mosq;

	}
	else { //appending mosquitoes
		last_mosq->next = new_mosq;
		last_mosq = new_mosq;

	}


}


// void prnt_vectr(vector <mosq*> inp_vect, string gender) { //printing vectors fo each type of mosquitoes
// 	/*cout << "\n" << gender<<" vector size = " << inp_vect.size()<<"\n";
// 	for (int i = 0; i < inp_vect.size(); i++) {
// 		cout << inp_vect.at(i)->mosq_id << " ";
// 	}*/

// }

// void prnt_all_vect() { // printing all types at once in vector
// 	/*prnt_vectr(male_vector, "Male");
// 	prnt_vectr(female_vector, "Female");
// 	prnt_vectr(egg_vector, "Egg");
// 	prnt_vectr(larve_vector, "Larve");
// 	prnt_vectr(pupe_vector, "Pupe");*/
// }

/**
 * @brief Shows the mosquito linked list
 * @details This function prints all the mosquito details in the linked list.
 * It shows the total population of all mosquitoes, the number of male, female, egg, larve, and pupe mosquitoes.
 * If the linked list is empty, it prints a message saying so.
 * It then prints the mosquito ID, stage, is_female status, treated status, and mated status for each mosquito in the linked list.
 * Finally, it prints the mosquito ID of the head and last mosquito in the linked list.
 * */
void show_mosqs() { //printing mosquito linked list
	struct mosq* ptr;
	cout << "\n ********** entered mosquito showwww ***********";
	ptr = head;
	int total_pop = egg_vector.size() + larve_vector.size() + pupe_vector.size() + male_vector.size() + female_vector.size(); //finding the population of all mosquitoes
	cout << "\n the total population of all mosquitoes is: " << total_pop;
	cout << "\n the number of male mosquitos are: " << male_vector.size();
	cout << "\n the number of female mosquitos are: " << female_vector.size();
	cout << "\n the number of egg mosquitos are: " << egg_vector.size();
	cout << "\n the number of lavre mosquitos are: " << larve_vector.size();
	cout << "\n the number of pupe mosquitos are: " << pupe_vector.size();
	if (head == NULL) {
		cout << "\n linked list is empty";
		return;
	}

	cout << "\n the mosquitos added so --------------------------- far are \n";
	cout << "\n Mosquito ID: ";
	cout << " Mosquito stage: ";
	cout << " is_female ";
	cout << " treated status: ";
	cout << " mated status: ";
	while (ptr != NULL) {
		cout << "\n " << ptr->mosq_id;
		cout << "\t\t " << ptr->status;
		cout << "\t\t " << ptr->is_female;
		cout << "\t\t " << ptr->is_treated;
		cout << "\t\t " << ptr->is_mated;
		ptr = ptr->next;
	}

	cout << "\n " << head->mosq_id;
	cout << "\n " << last_mosq->mosq_id;
	cout << "\n ********** mosquito show completed ***********";
}

std::string doubleToString(double value) {
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

// void write_double_CSV(const std::vector<double>& data, const std::string& filename) {
// 	std::ofstream file(filename);

// 	// Write the header
// 	file << "Values" << std::endl;

// 	// Write the data
// 	for (const auto& value : data) {
// 		file << doubleToString(value) << std::endl;
// 	}

// 	file.close();
// }

/*
 * @brief Write a CSV file from a dataset
 * @details This function makes a CSV file columns of integer values of mosquito population on each day in model.
 * Each column of data is represented by the pair <column name, column data> as std::pair<std::string, std::vector<int>>.
 * The dataset is represented as a vector of these columns.
 * Note that all columns should be the same size.
 * @param filename The name of the file to write to.
 * @param dataset The dataset to write to the file.
 * */
void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset) {
	// Make a CSV file with one or more columns of integer values
	// Each column of data is represented by the pair <column name, column data>
	//   as std::pair<std::string, std::vector<int>>
	// The dataset is represented as a vector of these columns
	// Note that all columns should be the same size

	// Create an output filestream object
	std::ofstream myFile(filename);

	// Send column names to the stream
	for (int j = 0; j < dataset.size(); ++j)
	{
		myFile << dataset.at(j).first;
		if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
	}
	myFile << "\n";

	// Send data to the stream
	for (int i = 0; i < dataset.at(0).second.size(); ++i)
	{
		for (int j = 0; j < dataset.size(); ++j)
		{
			myFile << dataset.at(j).second.at(i);
			if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
		}
		myFile << "\n";
	}

	// Close the file
	myFile.close();
}

// void write_d_csv(std::string filename, std::vector<std::pair<std::string, std::vector<double>>> dataset) {
// 	// Make a CSV file with one or more columns of integer values
// 	// Each column of data is represented by the pair <column name, column data>
// 	//   as std::pair<std::string, std::vector<int>>
// 	// The dataset is represented as a vector of these columns
// 	// Note that all columns should be the same size

// 	// Create an output filestream object
// 	std::ofstream myFile(filename);

// 	// Send column names to the stream
// 	for (int j = 0; j < dataset.size(); ++j)
// 	{
// 		myFile << dataset.at(j).first;
// 		if (j != dataset.size() - 1) myFile << ","; // No comma at end of line
// 	}
// 	myFile << "\n";

// 	// Send data to the stream
// 	for (int i = 0; i < dataset.at(0).second.size(); ++i)
// 	{
// 		for (int j = 0; j < dataset.size(); ++j)
// 		{
// 			myFile << dataset.at(j).second.at(i);
// 			if (j != dataset.size() - 1) myFile << ","; // No comma at end of line.
// 		}
// 		myFile << "\n";
// 	}

// 	// Close the file
// 	myFile.close();
// }

/**
 * @brief Check if a mosquito will die or not based on its status and the death probability of that status. It also removes the mosquito from the linked list and the corresponding vector if it dies.
 * @details This function checks if the mosquito will die or not based on its status and the death probability of that status. It also removes the mosquito from the linked list and the corresponding vector if it dies.
 * @param[in] _RNG_P Pointer to the GSL random number generator
 * @return void
 * */
void will_mosq_die(gsl_rng* _RNG_P) {
	float status_death_prob;
	int m_die_vect_cntr = -1;
	int f_die_vect_cntr = -1;
	int e_die_vect_cntr = -1;
	int l_die_vect_cntr = -1;
	int p_die_vect_cntr = -1;
	int death_cntr = 0;
	int total_pop;

	cout << "M_E value is \n" << env_1.egg_death_prob << "\n" << env_1.larve_death_prob << "\n" << env_1.pupe_death_prob << "\n" << env_1.female_death_prob << "\n\n\n";

	//checking death of all mosquitos in the list except last one to avoid error of null pointer while checking next of last mosq
	while (temp != NULL) {
		total_pop = egg_vector.size() + larve_vector.size() + pupe_vector.size() + male_vector.size() + female_vector.size();
		if (total_pop < 2) {
			global_zero_mosq = 1;
			cout << "\n\n\n\n zero mosqutoes alive in 1st try: \n\n\n\n";
			return;
		}

		switch (curr_mosq->status) {
		case 0:
			e_die_vect_cntr++;
			status_death_prob = env_1.egg_death_prob * env_1.step_size;
			break;
		case 1:
			l_die_vect_cntr++;
			status_death_prob = env_1.larve_death_prob * env_1.step_size;
			break;
		case 2:
			p_die_vect_cntr++;
			status_death_prob = env_1.pupe_death_prob * env_1.step_size;
			break;
		case 3:
			if (curr_mosq->is_female == true) {
				f_die_vect_cntr++;
				status_death_prob = env_1.female_death_prob * env_1.step_size;
			}
			else {
				m_die_vect_cntr++;
				status_death_prob = env_1.male_death_prob * env_1.step_size;
			}
			break;
		}

		env_1.death_oc = gsl_ran_bernoulli(_RNG_P, status_death_prob);
		//erasing mosquitos from individual vectors if they die
		if (env_1.death_oc == 1) {
			death_cntr++;
			env_1.death_count++;
			switch (curr_mosq->status) {
			case 0:
				egg_vector.erase(egg_vector.begin() + e_die_vect_cntr);
				e_die_vect_cntr--;
				break;
			case 1:
				larve_vector.erase(larve_vector.begin() + l_die_vect_cntr);
				l_die_vect_cntr--;
				break;
			case 2:
				pupe_vector.erase(pupe_vector.begin() + p_die_vect_cntr);
				p_die_vect_cntr--;
				break;
			case 3:
				if (curr_mosq->is_female == true) {
					female_vector.erase(female_vector.begin() + f_die_vect_cntr);
					f_die_vect_cntr--;
				}
				else {
					male_vector.erase(male_vector.begin() + m_die_vect_cntr);
					m_die_vect_cntr--;

				}
				break;
			}

			if (curr_mosq == head) {
				head = head->next;
				delete curr_mosq;
				curr_mosq = head;
				prev_mosq = head;
			}
			else {
				prev_mosq->next = curr_mosq->next;
				delete curr_mosq;
				curr_mosq = prev_mosq->next;

			}
		}
		else {

			prev_mosq = curr_mosq;
			curr_mosq = curr_mosq->next;
		}

		temp = curr_mosq->next; //to check if curr's next is null to execute seperate case for last mosq in list
	}//while loop

	//--------------for last mosq in list---------
	//checking death of last mosquito in the list to avoid error of null pointer while checking next of last mosq
	//updating the indiv counters
	switch (curr_mosq->status) {
	case 0:
		e_die_vect_cntr++;
		break;
	case 1:
		l_die_vect_cntr++;
		break;
	case 2:
		p_die_vect_cntr++;
		break;
	case 3:
		if (curr_mosq->is_female == true) {
			f_die_vect_cntr++;
		}
		else {
			m_die_vect_cntr++;
		}
	}
	//die_vect_cntr++;
	total_pop = egg_vector.size() + larve_vector.size() + pupe_vector.size() + male_vector.size() + female_vector.size();
	if (total_pop < 2) {
		global_zero_mosq = 1;
		cout << "\n\n\n\n zero mosqutoes alive in 1st try: \n\n\n\n";
		return;
	}

	env_1.death_oc = gsl_ran_bernoulli(_RNG_P, env_1.death_prob);
	//removing from vector for last mosq
	if (env_1.death_oc == 1) {
		switch (curr_mosq->status) {
		case 0:
			egg_vector.erase(egg_vector.begin() + e_die_vect_cntr);
			e_die_vect_cntr--;
			break;
		case 1:
			larve_vector.erase(larve_vector.begin() + l_die_vect_cntr);
			l_die_vect_cntr--;
			break;
		case 2:
			pupe_vector.erase(pupe_vector.begin() + p_die_vect_cntr);
			p_die_vect_cntr--;
			break;
		case 3:
			if (curr_mosq->is_female == true) {
				female_vector.erase(female_vector.begin() + f_die_vect_cntr);
				f_die_vect_cntr--;
			}
			else {
				male_vector.erase(male_vector.begin() + m_die_vect_cntr);
				m_die_vect_cntr--;
			}
		}

		cout << "\n the mosquito in last loop " << curr_mosq->mosq_id;
		prev_mosq->next = NULL;
		last_mosq = prev_mosq;//adjusting last_mosq to avoid eerror while adding new mosq
		delete curr_mosq;
		cout << "\nKi;;ed last mosq in list";

	}

	total_pop = egg_vector.size() + larve_vector.size() + pupe_vector.size() + male_vector.size() + female_vector.size();
	if (total_pop < 2) {
		global_zero_mosq = 1;
		cout << "\n\n\n\n zero mosqutoes alive in 1st try: \n\n\n\n";
		return;
	}

}
/*
 * @brief This function checks if a mosquito is ready for the next stage and if it is, it adds it to the next stage vector and removes it from the current stage vector and updates the status in linked list
 * @param[in] _RNG_P pointer to the GSL random number generator
 * @return void
 */
void mosq_nxt_stg(gsl_rng* _RNG_P) { // This check if a mosquito is ready for the next stage and if it is, it adds it to the next stage vector and removes it from the current stage vector and updates the status in linked list
	float status_next_stage_prob;
	int m_die_vect_cntr = -1;
	int f_die_vect_cntr = -1;
	int e_die_vect_cntr = -1;
	int l_die_vect_cntr = -1;
	int p_die_vect_cntr = -1;
	while (curr_mosq->next != NULL) {


		switch (curr_mosq->status) {
		case 0:
			e_die_vect_cntr++;
			status_next_stage_prob = env_1.egg_next_stg_prob * env_1.step_size;
			break;
		case 1:
			l_die_vect_cntr++;
			status_next_stage_prob = env_1.larve_next_stage_prob * env_1.step_size;
			break;
		case 2:
			p_die_vect_cntr++;
			status_next_stage_prob = env_1.pupe_next_stage_prob * env_1.step_size;
			break;
		case 3:
			if (curr_mosq->is_female == true) {
				f_die_vect_cntr++;
				status_next_stage_prob = 0;
			}
			else {
				m_die_vect_cntr++;
				status_next_stage_prob = 0;
			}
			break;
		}

		env_1.next_stg_oc = gsl_ran_bernoulli(_RNG_P, status_next_stage_prob);
		if (env_1.next_stg_oc == 1 && curr_mosq->status != 3) {

			//counter for position in the vector to delete it
			switch (curr_mosq->status) {
			case 0://eggs
				curr_mosq->status = +1;
				larve_vector.push_back(curr_mosq);
				egg_vector.erase(egg_vector.begin() + e_die_vect_cntr);
				e_die_vect_cntr--;
				//checking the max number of pupa availble
				break;
			case 1://larve
				curr_mosq->status = 2;

				pupe_vector.push_back(curr_mosq);
				larve_vector.erase(larve_vector.begin() + l_die_vect_cntr);
				l_die_vect_cntr--;
				break;
			case 2://pupa
				curr_mosq->status = 3;
				if (curr_mosq->is_female == true) {
					female_vector.push_back(curr_mosq);
				}
				else {
					male_vector.push_back(curr_mosq);
				}

				pupe_vector.erase(pupe_vector.begin() + p_die_vect_cntr);
				p_die_vect_cntr--;
				break;
			}
		}

		curr_mosq = curr_mosq->next;
	}
}

/*
 * @brief This function checks if a Adult female mosquito is ready for mating and if it is, it checks if it finds a male and if it does, it mates with it and adds the offspring based on male type to the environment.
 * It also checks if the female mosquito has found a male and if it has, it checks if the mating was successful or not and if it was, it adds the offspring to the environment based on the type of the male mosquito.
 * @param[in] _RNG_P pointer to the GSL random number generator
 */
void female_mating(gsl_rng* _RNG_P) { // This function checks if a Adult female mosquito is ready for mating and if it is, it checks if it finds a male and if it does, it mates with it and adds the offspring based on male type to the environment.
	int linear_egg_flag = 0;
	double linear_egg_prob = (double)((double)1.0 - ((double)env_1.global_egg_count / (double)env_1.linear_egg_cap)); //global egg count is initally zero as there are no eggs at start of loop
	cout << "\n-------------- in female mating";
	while (curr_mosq->next != NULL) {
		if (curr_mosq->status == 3 && curr_mosq->is_female == 1 && curr_mosq->is_mated == false) { //if the mosquito is female and it is not mated
			//checking if a female mosquito is looking for a male
			env_1.find_male_oc = gsl_ran_bernoulli(_RNG_P, env_1.find_male_prob);
			if (env_1.find_male_oc == 1) {
				// if the mosquito mates sucessfully or not
				env_1.mate_oc = gsl_ran_bernoulli(_RNG_P, env_1.mate_prob * env_1.step_size);
				if (env_1.mate_oc == 1) {

					if (env_1.linear_egg_cap > 0) { // this only works if linear egg cap is greater than zero
						if (linear_egg_prob < 0) {
							linear_egg_prob = 0;
						}
						env_1.linear_egg_oc = gsl_ran_bernoulli(_RNG_P, linear_egg_prob);

						if (env_1.linear_egg_oc == 0) {
							continue;

						}
					}
					env_1.no_of_male = male_vector.size();
					if (env_1.no_of_male == 0)
						break; //check

					int male_found = 0;
					while (male_found == 0) {
						env_1.male_rndm_mosq = gsl_rng_uniform_int(_RNG_P, env_1.no_of_male);
						if (male_vector[env_1.male_rndm_mosq]->gene_stat == 2) {
							male_found = gsl_ran_bernoulli(_RNG_P, env_1.male_fitness);
						}
						else {
							male_found = 1;
						}
					}
					if (male_vector[env_1.male_rndm_mosq]->gene_stat == 2 && male_found == 1) {
						env_1.DD_mate_cntr++;
						//treated male mosquito mating of DD(male) with RR(female)
						for (int cntr = 0; cntr < 50; cntr++) {
							add_mosq(0, 0, 1, 0, 1);
						}
					}

					else if (male_vector[env_1.male_rndm_mosq]->gene_stat == 1 && male_found == 1) {
						env_1.DR_mate_cntr++;
						//if the mating male is of DR(male)
						for (int cntr = 0; cntr < 25; cntr++) {
							add_mosq(0, 0, 1, 0, 1);
							add_mosq(0, 1, 0, 0, 0);
							add_mosq(0, 0, 1, 0, 0);
						}
					}
					else if (male_vector[env_1.male_rndm_mosq]->gene_stat == 0 && male_found == 1) {
						env_1.RR_mate_cntr++;
						//wild male mosquito mating with wild male
						for (int cntr = 0; cntr < 50; cntr++) { ///changed 50 to 25 to check

							add_mosq(0, 1, 0, 0, 0); //adding 50 female
							add_mosq(0, 0, 0, 0, 0); //adding 50 male
						}
					}
					curr_mosq->is_mated = 1;
					male_vector[env_1.male_rndm_mosq]->is_mated = 1;
				}
			}
		}
		curr_mosq = curr_mosq->next;
	}

}

/*
 * @brief This function collects the larve ids from the list and shuffles them to kill excess larve if the larve population is greater than the max larve capacity of the environment
 * @details It collects all the larve ids from the list and if the larve population is greater than the max larve capacity of the environment, it shuffles the collected ids and kills the excess larve to maintain the max larve capacity
 */
void larve_id_coll_and_shuff() { // this function is for collecting larve ids and shuffle them to kill excess larve if the larve population is greater than the max larve capacity of the environment
	curr_mosq = head;
	prev_mosq = head;
	larve_ids.clear();
	while (curr_mosq->next != NULL) {
		if (curr_mosq->status == 1) {
			larve_ids.push_back(curr_mosq->mosq_id);
		}
		prev_mosq = curr_mosq;
		curr_mosq = curr_mosq->next;
	}
}

/*
 * @brief This function collects the egg ids from the list and shuffles them to kill excess eggs if the egg population is greater than the max egg capacity of the environment
 * @details It collects all the egg ids from the list and if the egg population is greater than the max egg capacity of the environment, it shuffles the collected ids and kills the excess eggs to maintain the max egg capacity
 */
void egg_id_coll_and_shuff() {
	curr_mosq = head;
	prev_mosq = head;
	egg_ids.clear();
	eggs_female_vector.clear();
	eggs_male_DR_vector.clear();
	eggs_male_RR_vector.clear();

	while (curr_mosq->next != NULL) {
		if (curr_mosq->status == 0) {
			egg_ids.push_back(curr_mosq->mosq_id);

			//code for collection gene and gender of eggs
			if (curr_mosq->is_female == 1 && curr_mosq->gene_stat == 0) {//for female eggs
				eggs_female_vector.push_back(curr_mosq->mosq_id);

			}

			//code for coll of male RR eggs
			else if (curr_mosq->is_female == 0 && curr_mosq->gene_stat == 0) {
				eggs_male_RR_vector.push_back(curr_mosq->mosq_id);
			}

			//code for coll of male DR eggs
			else if (curr_mosq->is_female == 0 && curr_mosq->gene_stat == 1) {
				eggs_male_DR_vector.push_back(curr_mosq->mosq_id);
			}

		}
		prev_mosq = curr_mosq;
		curr_mosq = curr_mosq->next;
	}
}

void kill_excess_larve(gsl_rng* _RNG_P) {
	int l_die_vect_cntr = -1;
	curr_mosq = head;
	prev_mosq = head;
	int larve_counter = -1; // to keep track for iteration in loop to start killing
	int total_pop = egg_vector.size() + larve_vector.size() + pupe_vector.size() + male_vector.size() + female_vector.size(); //finding the population of all mosquitoes
	cout << "\n the total population of all mosquitoes is: " << total_pop;



	int arr_size = larve_ids.size();
	int* larve_id_array = larve_ids.data();
	int mosq_id_check = 0;

	gsl_ran_shuffle(_RNG_P, larve_id_array, arr_size, sizeof(int));


	while (curr_mosq->next != NULL) {

		if (curr_mosq->status == 1) {

			for (int i = 0; i < env_1.max_larve_cap; i++) {
				if (curr_mosq->mosq_id == larve_id_array[i]) { //safe mosq
					mosq_id_check = 1;
					break;
				}
			}

			l_die_vect_cntr++;

			if (mosq_id_check == 1) {//mosq is in safe list
				mosq_id_check = 0;
				prev_mosq = curr_mosq;
				curr_mosq = curr_mosq->next;
			}
			else {
				if (curr_mosq == head) {
					head = head->next;
					delete curr_mosq;
					curr_mosq = head;
					prev_mosq = head;
				}
				else {
					prev_mosq->next = curr_mosq->next;
					delete curr_mosq;
					curr_mosq = prev_mosq->next;
				}

				larve_vector.erase(larve_vector.begin() + l_die_vect_cntr);
				l_die_vect_cntr--;
			}

		}

		else {
			prev_mosq = curr_mosq;
			curr_mosq = curr_mosq->next;
		}

	}
}


void kill_excess_eggs(gsl_rng* _RNG_P) {//
	int e_die_vect_cntr = -1;
	curr_mosq = head;
	prev_mosq = head;
	int egg_counter = -1; // to keep track for iteration in loop to start killing

	int female_egg_arr_size = eggs_female_vector.size();
	int male_RR_eggs_arr_size = eggs_male_RR_vector.size();
	int male_DR_eggs_arr_size = eggs_male_DR_vector.size();

	int* female_egg_id_array = eggs_female_vector.data();
	int* male_RR_egg_id_array = eggs_male_RR_vector.data();
	int* male_DR_egg_id_array = eggs_male_DR_vector.data();

	int arr_size = egg_ids.size();
	int* egg_id_array = egg_ids.data();
	int mosq_id_check = 0;

	cout << "\n the proportions are Female: " << eggs_female_vector.size() << "::" << female_egg_arr_size << " DR: " << eggs_male_DR_vector.size() << "::" << male_DR_eggs_arr_size << " RR: " << eggs_male_RR_vector.size() << "::" << male_RR_eggs_arr_size << " total mosqs: " << egg_ids.size();
	cout << "\n\n before shuffle\n";
	cout << "\n the proprtions are: female " << (double)female_egg_arr_size / (double)arr_size;
	cout << "\nmale DR " << (double)male_DR_eggs_arr_size / (double)arr_size;
	cout << "\n Male RR " << (double)male_RR_eggs_arr_size / (double)arr_size;

	gsl_ran_shuffle(_RNG_P, egg_id_array, arr_size, sizeof(int));

	while (curr_mosq->next != NULL) {

		if (curr_mosq->status == 0) {

			for (int i = 0; i < env_1.max_egg_cap; i++) {
				if (curr_mosq->mosq_id == egg_id_array[i]) { //safe mosq
					mosq_id_check = 1;
					break;
				}
			}

			e_die_vect_cntr++;

			if (mosq_id_check == 1) {//mosq is in safe list
				mosq_id_check = 0;
				prev_mosq = curr_mosq;
				curr_mosq = curr_mosq->next;
			}
			else {
				if (curr_mosq == head) {
					head = head->next;
					delete curr_mosq;
					curr_mosq = head;
					prev_mosq = head;
				}
				else {
					prev_mosq->next = curr_mosq->next;
					delete curr_mosq;
					curr_mosq = prev_mosq->next;
				}

				egg_vector.erase(egg_vector.begin() + e_die_vect_cntr);
				e_die_vect_cntr--;
			}

		}

		else {
			prev_mosq = curr_mosq;
			curr_mosq = curr_mosq->next;
		}

	}
	egg_id_coll_and_shuff();

	int female_egg_arr_size1 = eggs_female_vector.size();
	int male_RR_eggs_arr_size1 = eggs_male_RR_vector.size();
	int male_DR_eggs_arr_size1 = eggs_male_DR_vector.size();

	int* female_egg_id_array1 = eggs_female_vector.data();
	int* male_RR_egg_id_array1 = eggs_male_RR_vector.data();
	int* male_DR_egg_id_array1 = eggs_male_DR_vector.data();

	int arr_size1 = egg_ids.size();
	int* egg_id_array1 = egg_ids.data();

	cout << "\n the proportions are Female: " << eggs_female_vector.size() << "::" << female_egg_arr_size1 << " DR: " << eggs_male_DR_vector.size() << "::" << male_DR_eggs_arr_size1 << " RR: " << eggs_male_RR_vector.size() << "::" << male_RR_eggs_arr_size1 << " total mosqs: " << egg_ids.size();
	cout << "\n after shuffle\n";
	cout << "\n the proprtions are: female " << (double)female_egg_arr_size1 / (double)arr_size1;
	cout << "\nmale DR " << (double)male_DR_eggs_arr_size1 / (double)arr_size1;
	cout << "\n Male RR " << (double)male_RR_eggs_arr_size1 / (double)arr_size1;




}



// void kill_excess_rndm_eggs(gsl_rng* _RNG_P) {// function to kill random eggs based on proportion of male RR and RD amd female

// 	//adult=3,0=male,is_treated=0, is_mated=0, gene_stat=0 RR /1 DR

// 	int e_die_vect_cntr = -1;
// 	curr_mosq = head;
// 	prev_mosq = head;
// 	int egg_counter = -1; // to keep track for iteration in loop to start killing
// 	int arr_size = egg_ids.size();
// 	int* egg_id_array = egg_ids.data();
// 	int mosq_id_check = 0;
// 	cout << "\nbefore shuffle\n";


// 	gsl_ran_shuffle(_RNG_P, egg_id_array, arr_size, sizeof(int));

// 	cout << "\nafter shuffle\n";

// 	while (curr_mosq->next != NULL) {

// 		if (curr_mosq->status == 0) {

// 			for (int i = 0; i < env_1.max_egg_cap; i++) {
// 				if (curr_mosq->mosq_id == egg_id_array[i]) { //safe mosq
// 					mosq_id_check = 1;
// 					break;
// 				}
// 			}

// 			e_die_vect_cntr++;

// 			if (mosq_id_check == 1) {//mosq is in safe list

// 				mosq_id_check = 0;
// 				prev_mosq = curr_mosq;
// 				curr_mosq = curr_mosq->next;
// 			}
// 			else {
// 				if (curr_mosq == head) {
// 					head = head->next;
// 					delete curr_mosq;
// 					curr_mosq = head;
// 					prev_mosq = head;
// 				}
// 				else {
// 					prev_mosq->next = curr_mosq->next;
// 					delete curr_mosq;
// 					curr_mosq = prev_mosq->next;

// 				}

// 				egg_vector.erase(egg_vector.begin() + e_die_vect_cntr);
// 				e_die_vect_cntr--;
// 			}

// 		}

// 		else {
// 			prev_mosq = curr_mosq;
// 			curr_mosq = curr_mosq->next;
// 		}

// 	}
// }


void deleteList(mosq*& del_head) { //to delete entire linked list
	mosq* prev = del_head;
	while (del_head) {
		del_head = del_head->next;
		//cout << "Deleting " << prev->mosq_id << endl;
		delete(prev);
		prev = head;
	}
}



void add_treated_male(int mosq_count) {
	for (int i = 0; i < mosq_count; i++) {
		add_mosq(3, 0, 1, 0, 2);
	}
}

bool comparePtrToNode(mosq* a, mosq* b) { return (a->mosq_id < b->mosq_id); }

void create_initial_mosquitoes(int initial_larve_agents_frm_ratio, int initial_pupe_agents_frm_ratio, int initial_adult_female_agents_frm_ratio, int initial_adult_male_agents_frm_ratio, gsl_rng* _RNG_P) {
	for (int larve_agents = 0; larve_agents < initial_larve_agents_frm_ratio; larve_agents++) {
		env_1.gender_oc = gsl_ran_bernoulli(_RNG_P, env_1.gender_prob);
		if (env_1.gender_oc == 1) {
			add_mosq(1, 1, 0, 0, 0);//adding female
		}
		else {
			add_mosq(1, 0, 0, 0, 0);//addiong male
		}
	}

	for (int pupe_agents = 0; pupe_agents < initial_pupe_agents_frm_ratio; pupe_agents++) {
		env_1.gender_oc = gsl_ran_bernoulli(_RNG_P, env_1.gender_prob);
		if (env_1.gender_oc == 1) {
			add_mosq(2, 1, 0, 0, 0);
		}
		else {
			add_mosq(2, 0, 0, 0, 0);
		}
	}

	for (int adult_female_agents = 0; adult_female_agents < initial_adult_female_agents_frm_ratio; adult_female_agents++) {
		add_mosq(3, 1, 0, 0, 0);
	}

	for (int adult_male_agents = 0; adult_male_agents < initial_larve_agents_frm_ratio; adult_male_agents++) {
		add_mosq(3, 0, 0, 0, 0);
	}
}

//function to kill larve by larve-ciding
void kill_by_larve_ciding(gsl_rng* _RNG_P) {

	float status_death_prob;
	int l_die_vect_cntr = -1;

	temp = head;
	curr_mosq = head;
	prev_mosq = head;
	int larve_pop = 0;
	/*cout << "\n the larve are: ";
	for (int i = 0; i < larve_vector.size(); i++) {
		std::cout << larve_vector[i]->mosq_id << " ,";
	}*/
	while (temp != NULL) {

		larve_pop = larve_vector.size();
		if (larve_pop < 2) {
			cout << "There are leass than 2 larve in the list";
			return;
		}


		if (curr_mosq->status == 1) {
			//cout << "\n\nin larve ciding larve count now is:" << larve_vector.size();
			//cout << "\n the current larve is: " << curr_mosq->mosq_id;
			switch (curr_mosq->status) {
			case 1:
				l_die_vect_cntr++;
				status_death_prob = env_1.proportion_larve_to_kill * 0.01; //* env_1.step_size; multiplying by 0.01 to convert to percentage
				break;
			}

			env_1.death_oc = gsl_ran_bernoulli(_RNG_P, status_death_prob);
			//erasing larve from vector if they die
			if (env_1.death_oc == 1) {
				//cout << "\n\nkilling mosq:" << curr_mosq->mosq_id;
				env_1.death_count++;
				switch (curr_mosq->status) {
				case 1:
					larve_vector.erase(larve_vector.begin() + l_die_vect_cntr);
					l_die_vect_cntr--;
					//cout << "\nin second switch";
				}

				if (curr_mosq == head) {
					head = head->next;
					delete curr_mosq;
					curr_mosq = head;
					prev_mosq = head;
				}
				else {
					prev_mosq->next = curr_mosq->next;
					delete curr_mosq;
					curr_mosq = prev_mosq->next;

				}
			}
			else {

				prev_mosq = curr_mosq;
				curr_mosq = curr_mosq->next;
			}
		}
		else {

			prev_mosq = curr_mosq;
			curr_mosq = curr_mosq->next;
		}

		temp = curr_mosq->next; //to check if curr's next is null to execute seperate case for last mosq in list
	}//while lo

}


int alloc_and_setup_gsl_random_generator() {
	gsl_rng_env_setup(); // Gathers environment variables.
	_RNG_P = gsl_rng_alloc(gsl_rng_default); // Allocates the rnd generator.
	if (!_RNG_P) { return 1; }
	return 0;
}



uint64_t get_time_microsseconds()
{
	uint64_t us = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::high_resolution_clock::now().time_since_epoch())
		.count();
	return us;

}

int_gsl_seed seed_gsl_random_generator(int_gsl_seed seed) {

	if (seed == SEED_NONE) {
		seed = (int_gsl_seed)get_time_microsseconds();
		// seed = time(0); // In seconds; not enough time resolution.
	}
	gsl_rng_set(_RNG_P, seed);
	return seed;

}


/**
 * RUN_MCMC: main MCMC function that will run the MCMC chain based on the given data.
 * It will generate new candidates, check if they are valid and run the model.
 * If the candidate is valid it will update the MCMC values and write the data to csv file.
 * If the candidate is invalid it will reject the iteration and increase the rejection counter.
 * When the rejection counter reaches the maximum cap, it will update the MCMC values with the latest valid candidate and reset the rejection counter.
 */
void RUN_MCMC(std::vector<string>& vect_CC_list, std::vector<string>& vect_date_string_start, std::vector<std::chrono::system_clock::time_point>& date_vector_start, std::vector<string>& vect_date_string_end, std::vector<std::chrono::system_clock::time_point>& date_vector_end, vector<double>& vect_temp, vector<string>& vect_date_string, vector<std::chrono::system_clock::time_point>& date_vector, vector <int>& emp_data_year_number, vector <int>& emp_data_month_number, vector <int>& emp_data_monthly_female, vector <int>& emp_data_monthly_row_count) {

	//env_mcmc.mcmc_values_map_vector["CC_1"].push_back(137.413952);
	//env_mcmc.mcmc_values_map_vector["CC_2"].push_back(363.462822);
	//env_mcmc.mcmc_values_map_vector["CC_3"].push_back(489.61136);
	//env_mcmc.mcmc_values_map_vector["CC_4"].push_back(289.840739);
	//env_mcmc.mcmc_values_map_vector["eggs"].push_back(78);


	//creting dynaimc map of vectors
	cout << "\n the unique CC vals are: \n";
	set<string> unique_CC_vals(vect_CC_list.begin(), vect_CC_list.end()); //set data_struc for getting unique values if CC's names
	for (const auto& str : unique_CC_vals) {
		std::cout << str << std::endl;
	}

	cout << "\n\n\n before cleaning the egg vector has values in mcmc\n\n\n";
	for (int icheck = 0; icheck < env_mcmc.mcmc_values_map_vector["eggs"].size(); icheck++) {
		cout << " \n -  " << env_mcmc.mcmc_values_map_vector["eggs"].at(icheck);
	}


	//unique values clearing
	for (const auto& str : unique_CC_vals) {
		env_mcmc.mcmc_values_map_vector[str].clear();
	}
	env_mcmc.mcmc_values_map_vector["eggs"].clear();

	//clearing vector
	/*env_mcmc.mcmc_values_map_vector["CC_1"].clear();
	env_mcmc.mcmc_values_map_vector["CC_2"].clear();
	env_mcmc.mcmc_values_map_vector["CC_3"].clear();
	env_mcmc.mcmc_values_map_vector["CC_4"].clear();
	env_mcmc.mcmc_values_map_vector["eggs"].clear();*/ // pause for unique vals

	cout << "\n\n\n after cleaning the egg vector has values in mcmc\n\n\n";
	for (int icheck = 0; icheck < env_mcmc.mcmc_values_map_vector["eggs"].size(); icheck++) {
		cout << " \n -  " << env_mcmc.mcmc_values_map_vector["eggs"].at(icheck);

	}

	//avoiding useless rejects
	if (env_mcmc.mcmc_cand_reject_cntr == env_1.max_mcmc_cand_reject_cap) {
		env_mcmc.cand_like_lihod = env_mcmc.curr_like_lihod; 
		cout << "\n\n\n\n updating MCMC values after many rejections\n\n\n\n";

		//updating other curr vals
		env_mcmc.cc1_cand = env_mcmc.cc1_curr;
		env_mcmc.cc2_cand = env_mcmc.cc2_curr;
		env_mcmc.cc3_cand = env_mcmc.cc3_curr;
		env_mcmc.cc4_cand = env_mcmc.cc4_curr;
		//env_mcmc.cc5_cand = env_mcmc.cc5_curr;
		env_mcmc.eggs_cand = env_mcmc.eggs_curr;
		env_mcmc.over_disperssion_cand = env_mcmc.over_disperssion_curr;

		env_mcmc.mcmc_cand_reject_cntr = 0;
	}

	cout << "\n\n egg mcmc val before gaussian === " << env_mcmc.eggs_cand;

	//finding new candidates for all
	//env_mcmc.cc1_cand = env_mcmc.cc1_curr + gsl_ran_gaussian(_RNG_P, env_mcmc.std_dev_cc1);
	env_mcmc.cc2_cand = env_mcmc.cc2_curr + gsl_ran_gaussian(_RNG_P, env_mcmc.std_dev_cc2);
	env_mcmc.cc3_cand = env_mcmc.cc3_curr + gsl_ran_gaussian(_RNG_P, env_mcmc.std_dev_cc3);
	env_mcmc.cc4_cand = env_mcmc.cc4_curr + gsl_ran_gaussian(_RNG_P, env_mcmc.std_dev_cc4);
	//env_mcmc.cc5_cand = env_mcmc.cc5_curr + gsl_ran_gaussian(_RNG_P, env_mcmc.std_dev_cc5);
	env_mcmc.eggs_cand = env_mcmc.eggs_curr + gsl_ran_gaussian(_RNG_P, env_mcmc.std_dev_eggs);
	env_mcmc.over_disperssion_cand = env_mcmc.over_disperssion_curr + gsl_ran_gaussian(_RNG_P, env_mcmc.std_dev_over_disp);
	env_mcmc.cc1_cand = env_mcmc.cc4_cand; //test
	//env_mcmc.cc2_cand = env_mcmc.cc4_cand; // for experiment 2 of paper

	cout << "\n\n egg mcmc val after gaussian === " << env_mcmc.eggs_cand;


	//assigning candidates to vector
	env_mcmc.mcmc_values_map_vector["CC_1"].push_back(env_mcmc.cc1_cand);
	env_mcmc.mcmc_values_map_vector["CC_2"].push_back(env_mcmc.cc2_cand);
	env_mcmc.mcmc_values_map_vector["CC_3"].push_back(env_mcmc.cc3_cand);
	env_mcmc.mcmc_values_map_vector["CC_4"].push_back(env_mcmc.cc4_cand);
	//env_mcmc.mcmc_values_map_vector["CC_5"].push_back(env_mcmc.cc5_cand);
	env_mcmc.mcmc_values_map_vector["eggs"].push_back(env_mcmc.eggs_cand);

	cout << "\n\n\nthe egg vector has values in mcmc\n\n\n";
	for (int icheck = 0; icheck < env_mcmc.mcmc_values_map_vector["eggs"].size(); icheck++) {
		cout << "  - egg val in vec at pos" << icheck << "  is = " << env_mcmc.mcmc_values_map_vector["eggs"].at(icheck);
	}

	//assigning latest mcmc values to run model
	column_names_vect = env_mcmc.mcmc_column_names_vect;
	CC_map = env_mcmc.mcmc_values_map_vector;

	cout << "\n colnames in RUN_MCMC of vect\n";
	for (auto x : column_names_vect) {
		std::cout << x << " ";
	}
	cout << endl;

	int num_cols_in_MCMC_csv = column_names_vect.size();
	cout << "\n\n\nthe egg vector has values\n\n\n";
	for (int icheck = 0; icheck < CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].size(); icheck++) {
		cout << " \n -  " << CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].at(icheck);
	}



//if cand is valid run model
// else if invalid value 
// ---make a note of the cand and curr and reject/skip the iteration 
// ---cand liklihood should be negative infifnity.
	long double neg_infinity = numeric_limits<long double>::infinity();
	neg_infinity = neg_infinity * -1;

	int skip_main_func_logic = 0;

	if (env_mcmc.cc1_cand < 0) {
		env_mcmc.cand_like_lihod = neg_infinity;
		skip_main_func_logic = 1;
	}

	if (env_mcmc.cc2_cand < 0) {
		env_mcmc.cand_like_lihod = neg_infinity;
		skip_main_func_logic = 1;
	}

	if (env_mcmc.cc3_cand < 0) {
		env_mcmc.cc3_cand = neg_infinity;
		skip_main_func_logic = 1;
	}

	if (env_mcmc.cc4_cand < 0) {
		env_mcmc.cand_like_lihod = neg_infinity;
		skip_main_func_logic = 1;
	}

	/*if (env_mcmc.cc5_cand < 0) {
		env_mcmc.cand_like_lihod = neg_infinity;
		skip_main_func_logic = 1;
	}*/

	// making it less than 5 as the values like 0.5 are too small to genereate mosqs
	if (env_mcmc.eggs_cand < 5) {
		cout << "\n\n the egg value is " << env_mcmc.eggs_cand;

		env_mcmc.cand_like_lihod = neg_infinity;
		if (isinf(env_mcmc.cand_like_lihod) && env_mcmc.cand_like_lihod < 0) {
			cout << "\n\n cand liklihood is negativie infinity in egg cand liklihood";
		}
		skip_main_func_logic = 1;
	}

	if (env_mcmc.over_disperssion_cand <= 0) {
		env_mcmc.cand_like_lihod = neg_infinity;
		skip_main_func_logic = 1;

	}

	if (isinf(env_mcmc.cand_like_lihod) && env_mcmc.cand_like_lihod < 0) {
		cout << "\n\n cand liklihood is negativie infinity";
	}


	if (skip_main_func_logic == 0) {
		cout << "\n\n calling main func_logic";
		main_function_logic(vect_CC_list, vect_date_string_start, date_vector_start, vect_date_string_end, date_vector_end, vect_temp, vect_date_string, date_vector, emp_data_year_number, emp_data_month_number, emp_data_monthly_female, emp_data_monthly_row_count);
	}

	if (global_zero_mosq == 1) {// try catch throw : when there are zero mosq, this will exit the loop and send data to files.
		cout << "\n exiting the run_mcmc_func as mosquiotes died too early\n";
		env_mcmc.cand_like_lihod = neg_infinity;
	}


	cout << "\n\n\n\n before updating MCMC values\n\n\n\n";
	if (gsl_ran_flat(_RNG_P, 0, 1) < exp(env_mcmc.cand_like_lihod - env_mcmc.curr_like_lihod)) {
		env_mcmc.curr_like_lihod = env_mcmc.cand_like_lihod;

		//
		// 
		cout << "\n\n\n\n updating MCMC values\n\n\n\n";


		//updating other curr val
		env_mcmc.cc1_curr = env_mcmc.cc1_cand;
		env_mcmc.cc2_curr = env_mcmc.cc2_cand;
		env_mcmc.cc3_curr = env_mcmc.cc3_cand;
		env_mcmc.cc4_curr = env_mcmc.cc4_cand;
		//env_mcmc.cc5_curr = env_mcmc.cc5_cand;
		env_mcmc.eggs_curr = env_mcmc.eggs_cand;
		env_mcmc.over_disperssion_curr = env_mcmc.over_disperssion_cand;

		cout << "\n accepted";
		env_mcmc.mcmc_cand_reject_cntr = 0;
	}
	else {
		env_mcmc.mcmc_cand_reject_cntr++;
	}


	//streaming data into csv file
}

/* This is where model runs for defined number of days and number of iterations for each day.
	- This is the main function that runs the model for each MCMC candidate and generates the mosquito population count for each day of the simulation. 
	- It will output daily mosquito population count and other details to csv file.


*/
void main_function_logic(std::vector<string>& vect_CC_list, std::vector<string>& vect_date_string_start, std::vector<std::chrono::system_clock::time_point>& date_vector_start, std::vector<string>& vect_date_string_end, std::vector<std::chrono::system_clock::time_point>& date_vector_end, vector<double>& vect_temp, vector<string>& vect_date_string, vector<std::chrono::system_clock::time_point>& date_vector, vector <int>& emp_data_year_number, vector <int>& emp_data_month_number, vector<int>& emp_data_monthly_female_main, vector <int>& emp_data_monthly_row_count) {
	auto start_time_main = std::chrono::high_resolution_clock::now();
	// checking epoch values of cc and dates file
	std::time_t start_date_CC_for_epoch = std::chrono::system_clock::to_time_t(date_vector_start.at(0));
	std::tm* local_time_start_date_for_epoch = std::gmtime(&start_date_CC_for_epoch);
	std::cout << "\n the start date is: " << std::put_time(local_time_start_date_for_epoch, "%d-%m-%Y") << " ";
	std::cout << "\nEpoch start date value in main is: " << start_date_CC_for_epoch << std::endl;

	std::time_t end_date_CC_for_epoch = std::chrono::system_clock::to_time_t(date_vector_end.at(0));
	std::tm* local_time_end_date_for_epoch = std::gmtime(&end_date_CC_for_epoch);
	std::cout << "\n the end date is:: " << std::put_time(local_time_end_date_for_epoch, "%d-%m-%Y") << " ";
	std::cout << "\nEpoch end date value in main is:: " << end_date_CC_for_epoch << std::endl;

	cout << "\n the number of rows in MCMC csv is: ";
	//read_CC_vals_by_map(column_names_vect, CC_map);
	string temp_col_name;
	temp_col_name = column_names_vect.at(0);
	int num_rows_in_MCMC_csv = CC_map[temp_col_name].size();
	int num_cols_in_MCMC_csv = column_names_vect.size();
	cout << "\n\n the month and year of **' " << env_1.end_mcmc_day << " '** is" << getDateFromDayNumber(env_1.end_mcmc_day).year << " month: " << getDateFromDayNumber(env_1.end_mcmc_day).month << "\n";

	for (auto x : column_names_vect) {
		std::cout << x << " ";
	}
	cout << endl;

	cout << "\n ------";
	for (auto cc1 : vect_CC_list) {
		std::cout << cc1 << '\n';
	}
	cout << "\n ------";

	string file_names_list;

	string temp_file_names;

	auto sim_start_time = std::chrono::high_resolution_clock::now();
	cout << "\n simulation about to start";

	// code for reading data for surveil_data_matrix
	vector<vector<double>> surveil_data_matrix;
	if (env_1.is_non_constant_insertion_scenario == 1) {
		surveil_data_matrix = read_surveil_data_matrix_from_csv(env_1.surveillance_data_matrix_file_path);

	}

	vector<double> constant_intervention_surveil_data_vector;
	if (env_1.is_non_constant_insertion_scenario == 0) {
		constant_intervention_surveil_data_vector = read_constant_scenario_specific_month_100_sims_surveil_data_from_csv(env_1.constant_scenario_specific_month_100_sims_surveil_data_csv_filepath);

		if (constant_intervention_surveil_data_vector.size() < env_1.num_of_simulations_to_run) {
			cout << "\n\n error \n error\n specific month has less surveil values than number of simulations";
		}
	}

	for (int sim_cnt = 0; sim_cnt < env_1.num_of_simulations_to_run; sim_cnt++) {


		//resetting the global variables for multiple simulations.
		mosq_count = 0;

		global_zero_mosq = 0;

		alloc_and_setup_gsl_random_generator();

		//seed_gsl_random_generator(0);

		// get seed from params and add it to sim_cnt and use it as seed
		// setting seed from input params + current simulation value, so each simulation is reproducable
		int calculated_seed_number = 0;
		if (env_1.seed_from_external_input != 0) {
			calculated_seed_number = sim_cnt + env_1.seed_from_external_input;
		}
		//calculated_seed_number = sim_cnt + env_1.seed_from_external_input;

		seed_gsl_random_generator(calculated_seed_number);


		//cout << "\n\n current simulation and constant_scenario value ---" << sim_cnt << " --- value--- " << constant_intervention_surveil_data_vector[sim_cnt];
		cout << "the intialized count :";
		curr_mosq = head;
		prev_mosq = head;
		int day_cntr = 0;
		//int Male_DD = 0, Male_DR = 0, Male_RR = 0;

		double divs;
		//read_variables();
		file_names_list.assign(env_1.output_filename);
		cout << "\n the initial mosqs count is :" << env_1.mate_prob;
		cout << "\n" << env_1.initial_mosqs;
		cout << "\n" << env_1.max_larve_cap;
		cout << "\n" << env_1.mate_prob;
		cout << "\n" << env_1.treated_prob;
		cout << "\n" << env_1.female_death_prob;
		cout << "\n" << env_1.male_death_prob;
		cout << "\n" << env_1.egg_death_prob;
		cout << "\n" << env_1.larve_death_prob;
		cout << "\n" << env_1.pupe_death_prob;
		cout << "\n" << env_1.gender_prob;
		cout << "\n" << env_1.find_male_prob;
		cout << "\n" << env_1.egg_next_stg_prob;
		cout << "\n" << env_1.larve_next_stage_prob;
		cout << "\n" << env_1.pupe_next_stage_prob;

		//------------//code block for picking random nmber by gsl_rng_uniform_int for intial egg value and assigning
		// int random_row_num_frm_MCMC = gsl_rng_uniform_int(_RNG_P, num_rows_in_MCMC_csv);
		// 
		// changing from picking random out of 100 to using same row number for its own simulation
		// i.e 1st simulation uses 1st row of mcmc params
		int current_row_from_MCMC = sim_cnt;

		cout << "\n number of rows are :" << num_rows_in_MCMC_csv << endl << "\n number of cols are: " << num_cols_in_MCMC_csv;
		cout << "\nthe current row val is :" << current_row_from_MCMC;
		cout << "\n first value is " << CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].at(0);
		cout << "\n current egg value is: " << CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].at(current_row_from_MCMC);
		int random_egg_value_frm_MCMC = int(CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].at(current_row_from_MCMC));
		env_1.initial_mosqs = random_egg_value_frm_MCMC;

		cout << "\n\n\nthe egg vector has values\n\n\n";
		for (int icheck = 0; icheck < CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].size(); icheck++) {
			cout << "  -  " << CC_map[column_names_vect.at(num_cols_in_MCMC_csv - 1)].at(icheck);
		}

		// initial ratio conditions for each simulation
		int initial_larve_agents_frm_ratio = (int)(random_egg_value_frm_MCMC * env_1.sim_initial_larve_ratio);
		int initial_pupe_agents_frm_ratio = (int)(random_egg_value_frm_MCMC * env_1.sim_initial_pupe_ratio);
		int initial_adult_female_agents_frm_ratio = (int)(random_egg_value_frm_MCMC * env_1.sim_initial_adult_ratio);
		int initial_adult_male_agents_frm_ratio = (int)(random_egg_value_frm_MCMC * env_1.sim_initial_adult_ratio);

		cout << "\n inital mosquitoes larve,pupe,adult_male,adult_female are: " << initial_larve_agents_frm_ratio << " " << initial_pupe_agents_frm_ratio << " " << initial_adult_male_agents_frm_ratio << " " << initial_adult_female_agents_frm_ratio;
		// vector for storing caring cap values
		vector <int> all_dates_caring_cap_vector;
		cout << "/n-----------------------";

		cout << "\n column_names are";
		for (int names_iter = 0; names_iter < column_names_vect.size(); names_iter++) {
			cout << "\n " << column_names_vect.at(names_iter);


		}

		for (const auto& date : date_vector) {
			std::time_t time = std::chrono::system_clock::to_time_t(date);
			std::tm* local_time = std::gmtime(&time);



			// to store Caring Cap vals for each day from date_temps files in int vector
			for (int start_date_i = 0; start_date_i < date_vector_start.size(); start_date_i++) {
				std::time_t start_date_from_CC_dates = std::chrono::system_clock::to_time_t(date_vector_start.at(start_date_i));
				std::time_t end_date_from_CC_dates = std::chrono::system_clock::to_time_t(date_vector_end.at(start_date_i));

				std::tm* local_start_date_frm_CC_top = std::gmtime(&start_date_from_CC_dates);

				std::tm* local_end_date_frm_CC_top = std::gmtime(&end_date_from_CC_dates);

				if (start_date_from_CC_dates <= time) {
					std::time_t time1 = std::chrono::system_clock::to_time_t(date);
					std::tm* local_time_if = std::gmtime(&time1);
					if (end_date_from_CC_dates >= time) {


						for (int names_iter = 0; names_iter < column_names_vect.size() - 1; names_iter++) {
							int cmp_output = (vect_CC_list.at(start_date_i)).compare(column_names_vect.at(names_iter));
							cout << "\n vect CC is " << vect_CC_list.at(start_date_i);
							cout << "\n current iter column_name is" << column_names_vect.at(names_iter);
							if (cmp_output == 0) {
								double my_val = CC_map[column_names_vect.at(names_iter)].at(current_row_from_MCMC);
								cout << "\n\n cc_val selected is " << int(my_val);
								cout << "\n day is: " << start_date_i;
								all_dates_caring_cap_vector.push_back(int(my_val));
							}
						}
					}
				}
			}
			
		}

		for (int icheck = 0; icheck < all_dates_caring_cap_vector.size(); icheck++) {
			cout << "\n  " << icheck << " -----caring cap value is- " << all_dates_caring_cap_vector[icheck];
		}

		// show_mosqs();
		int temp_female_cnt = get_adult_female_count();
		cout << "\n the female count from func is " << temp_female_cnt;


		//function to create initial mosquitoes larve pupe and adults
		create_initial_mosquitoes(initial_larve_agents_frm_ratio, initial_pupe_agents_frm_ratio, initial_adult_female_agents_frm_ratio, initial_adult_male_agents_frm_ratio, _RNG_P);


		// show_mosqs();
		temp_female_cnt = get_adult_female_count();
		cout << "\n the female count from func is " << temp_female_cnt;
		cout << "\n Male vector size" << male_vector.size();


		//to calculate seperate count for DD, DR,RR
		cout << "\n Male vector size" << male_vector.size();
		Male_DD.clear();
		Male_DR.clear();
		Male_RR.clear();
		for (int si = 0; si < male_vector.size(); si++) {
			cout << "\n" << male_vector[si]->mosq_id << "  ----  " << male_vector[si]->gene_stat;
			if (male_vector[si]->gene_stat == 2) {
				Male_DD.push_back(male_vector[si]->mosq_id);
			}
			else if (male_vector[si]->gene_stat == 1) {
				Male_DR.push_back(male_vector[si]->mosq_id);
			}
			else if (male_vector[si]->gene_stat == 0) {
				Male_RR.push_back(male_vector[si]->mosq_id);
			}

		}

		Male_count_DD.push_back(Male_DD.size());
		Male_count_DR.push_back(Male_DR.size());
		Male_count_RR.push_back(Male_RR.size());



		int males_add_after_equi = 0;

		cout << "\n count is";
		cout << Male_DD.size() << "\n" << Male_DR.size() << "\n" << Male_RR.size();


		cout << "\n===============" << mosq_count;


		//variables for calculating daily female count for MCMC monthly.
		struct adult_female_day_count {
			int dayNumber;
			int value;
		};
		std::vector<adult_female_day_count> adult_female_daily_vect;

		//loooping over time
		int temp_vect_looper = 0;
		for (int day = 0; day < env_1.num_of_days_to_expmnt; day++) {


			//edited this line as num of days in equlibrium is irrespective to current day 
			if (/*day >= env_1.equlibrium_days &&*/ day < env_1.num_of_temperature_values && temp_vect_looper <= env_1.num_of_temperature_values) {

				// individual mortality and dev rate calc
				Parameters params;
				double temp_test = vect_temp.at(temp_vect_looper);
				temp_vect_looper++;
				eggDevelopmentAegypti(&params, temp_test);
				larvaeDevelopmentAegypti(&params, temp_test);
				pupaeDevelopmentAegypti(&params, temp_test);
				adultDevelopmentAegypti(&params, temp_test);

				eggMortalityAegypti(&params, temp_test);
				larvaeMortalityAegypti(&params, temp_test);
				pupaeMortalityAegypti(&params, temp_test);
				adultMortalityAegypti(&params, temp_test);

				cout << "\n temperature is value: " << temp_test << endl;
				cout << "D_E value is \n" << params.d_E << "\n" << params.d_L << "\n" << params.d_P << "\n" << params.d_A << "\n\n\n";
				cout << "M_E value is \n" << params.m_E << "\n" << params.m_L << "\n" << params.m_P << "\n" << params.m_A << "\n\n\n";

				env_1.mate_prob = params.d_A;
				env_1.female_death_prob = params.m_A;
				env_1.male_death_prob = params.m_A;
				env_1.egg_death_prob = params.m_E;
				env_1.larve_death_prob = params.m_L;
				env_1.pupe_death_prob = params.m_P;
				env_1.egg_next_stg_prob = params.d_E;
				env_1.larve_next_stage_prob = params.d_L;
				env_1.pupe_next_stage_prob = params.d_P;

			}
			cout << "\n about to read linear_egg_cap\n: ";
			//assigning variable caring cap based on current day number in loop
			env_1.linear_egg_cap = all_dates_caring_cap_vector.at(day);
			cout << "\n day is : " << day << "  ------- caring cap is " << env_1.linear_egg_cap;


			//for is_non_constant_scenario to get the value
			double specific_day_surveil_value = 0;
			double specific_simulation_constant_scenario_surveil_val = 0;
			if (env_1.is_non_constant_insertion_scenario == 1) {

				int rowIndex = sim_cnt; // Change this to the desired row index
				//adding +1 to ignore the first column which is index of each row
				int colIndex = day + 1; // Change this to the desired column index

				cout << "value of ratio: " << env_1.ratio_of_insertion;
				cout << endl << "scaling_value: " << env_1.andre_scaling_value;
				if (get_value_from_surveil_data_matrix(surveil_data_matrix, rowIndex, colIndex, specific_day_surveil_value)) {
					cout << "Value at row " << rowIndex << ", column " << colIndex << " is: " << specific_day_surveil_value << endl;
				}
			}

			if (env_1.is_non_constant_insertion_scenario == 0) {
				specific_simulation_constant_scenario_surveil_val = constant_intervention_surveil_data_vector[sim_cnt];
			}

			for (int time = 0; time < env_1.num_of_times_in_each_day; time++) {
				cout << "\n loop counter itr_num " << env_mcmc.itr_num << "day:" << day << " ------- time:" << time;
				cout << "\n male vector size : " << male_vector.size();
				int i = 0;
				temp = head;
				curr_mosq = head;
				prev_mosq = head;
				cout << "\n-----------killing started------------\n";
				cout << "\n male vector size : " << male_vector.size();
				will_mosq_die(_RNG_P);//checking each mosquito survives each time loop and killing them based on probability

				if (global_zero_mosq == 1) {// try catch throw : when there are zero mosq, this will exit the loop and send data to files.
					cout << "\n exiting the inner ---for--- loop to write data to files\n";
					break;
				}

				// prnt_all_vect();
				//adding l* implementation for larve to kill excess
				temp = head;
				i = 0;
				temp = head;
				curr_mosq = head;
				prev_mosq = head;
				mosq_nxt_stg(_RNG_P);// checkimg if mosquito forwards to next stage like from egg to larve
				std::sort(male_vector.begin(), male_vector.end(), comparePtrToNode);
				std::sort(female_vector.begin(), female_vector.end(), comparePtrToNode);
				std::sort(egg_vector.begin(), egg_vector.end(), comparePtrToNode);
				std::sort(larve_vector.begin(), larve_vector.end(), comparePtrToNode);
				std::sort(pupe_vector.begin(), pupe_vector.end(), comparePtrToNode);
				// prnt_all_vect();

				// for all mosquitos
				curr_mosq = head;

				if (male_vector.size() > 0 && female_vector.size() > 0) {
					female_mating(_RNG_P);// checking if female mates with male and lays eggs
				}
				else {
					cout << "\n\n\n\n\n\n no adult mosqitoes left for mating\n";
				}


				if (egg_vector.size() > env_1.max_egg_cap) {
					egg_id_coll_and_shuff();
					kill_excess_eggs(_RNG_P);
				}


				cout << "\n curr larve count: " << larve_vector.size();
				if (larve_vector.size() > env_1.max_larve_cap) {
					larve_id_coll_and_shuff();
					kill_excess_larve(_RNG_P);
				}
				env_1.global_egg_count = egg_vector.size(); // to keep track of egg count after each time step.
			}

			if (global_zero_mosq == 1) {// try catch throw : when there are zero mosq, this will exit the loop and send data to files.
				cout << "\n exiting the outer ---for--- DAY loop to write data to files\n";
				break;
			}

			//just to know the number of adults on equilibrium day
			if (day == env_1.equlibrium_days) {
				env_1.adult_males_on_equibrilium = male_vector.size();
				males_add_after_equi = (int)((double)env_1.adult_males_on_equibrilium * (double)env_1.ratio_males_DD_add);// *(double)0.01);
				cout << "\n the adults are: " << env_1.adult_males_on_equibrilium << "\n the ratio is: " << env_1.ratio_males_DD_add << "\n the males adding are :" << males_add_after_equi;
			}

			//to add "DD" mosquitoes in particualr interval based on if 
			//->current day is greater than required number of equilibrium days
			//->if day is divisible by interval
			//->if current day is less than the provided run of duration

			if (day >= env_1.equlibrium_days && (day - env_1.equlibrium_days) % env_1.intrvl_of_days_to_add_treated_mosq == 0 && day <= (env_1.duration_intervention + env_1.equlibrium_days)) {
				cout << "\n male vector size : \n\n\n\n\n\n" << male_vector.size();
				cout << "\n ------------adding treated mosqs";
				cout << "\n the value of weekly remainder" << (day - env_1.equlibrium_days) % env_1.intrvl_of_days_to_add_treated_mosq << endl;
				//add_treated_male(env_1.num_of_mosq_to_add);
				if (env_1.is_non_constant_insertion_scenario == 0) {
					// this is for each simaualtion with its matching insertion number from surveillance data vector
					env_1.fixed_num_DD_insertions = static_cast<int>(round(specific_simulation_constant_scenario_surveil_val * env_1.andre_scaling_value * env_1.ratio_of_insertion));
					cout << endl << "\n $$$$$$$_____the day, simulation number, simulation_insertion_value and number of insertions are $$$$$$$_____ \n\n" << day << "------" << sim_cnt << "------" << specific_simulation_constant_scenario_surveil_val << "------" << env_1.fixed_num_DD_insertions << "endl";
					if (env_1.fixed_num_DD_insertions > 0) { //checking for manual input/fixed DD insertions and updating the males_add_after_equi to fixed DD_insertions value.
						males_add_after_equi = env_1.fixed_num_DD_insertions;
					}

					for (int i = 0; i < males_add_after_equi; i++) {
						add_mosq(3, 0, 0, 0, 2);
					}
				}

				if (env_1.is_non_constant_insertion_scenario == 1) {


					env_1.fixed_num_DD_insertions = static_cast<int>(round(specific_day_surveil_value * env_1.andre_scaling_value * env_1.ratio_of_insertion));
					cout << endl << "\n $$$$$$$_____the day and number of insertions are $$$$$$$_____" << day << "------" << env_1.fixed_num_DD_insertions << "endl";
					if (env_1.fixed_num_DD_insertions > 0) { //checking for manual input/fixed DD insertions and updating the males_add_after_equi to fixed DD_insertions value.
						males_add_after_equi = env_1.fixed_num_DD_insertions;
					}
					for (int i = 0; i < males_add_after_equi; i++) {
						add_mosq(3, 0, 0, 0, 2);
					}
				}
			}


			// killing larve by larve-ciding method
			cout << "\n the number before killing larve: " << larve_vector.size();
			if (larve_vector.size() < 2) {
				cout << "There are leass than 2 larve in the list";
			}
			else {
				if (day >= env_1.larve_insertion_start_day && day < env_1.larve_insertion_end_day && day % env_1.freq_days_of_larve_ciding == 0) {
					cout << "\n\n\n\nThe larve count before killing: " << larve_vector.size();
					kill_by_larve_ciding(_RNG_P);
					cout << "\nThe larve count after killing: " << larve_vector.size();
				}
			}
			cout << "\n the number after killing larve: " << larve_vector.size();
			cout << "\n male vector size : " << male_vector.size();

			male_count.push_back(male_vector.size());
			female_count.push_back(female_vector.size());
			egg_count.push_back(egg_vector.size());
			larve_count.push_back(larve_vector.size());
			pupe_count.push_back(pupe_vector.size());
			time_count.push_back(day_cntr++);
			female_ratio.push_back((double)female_vector.size() / (double)larve_vector.size());
			male_ratio.push_back((double)male_vector.size() / (double)larve_vector.size());
			larve_ratio.push_back((double)larve_vector.size() / (double)larve_vector.size());
			pupe_ratio.push_back((double)pupe_vector.size() / (double)larve_vector.size());

			Male_DD.clear();
			Male_DR.clear();
			Male_RR.clear();
			for (int si = 0; si < male_vector.size(); si++) {
				if (male_vector[si]->gene_stat == 2) {
					Male_DD.push_back(male_vector[si]->mosq_id);
				}
				else if (male_vector[si]->gene_stat == 1) {
					Male_DR.push_back(male_vector[si]->mosq_id);
				}
				else if (male_vector[si]->gene_stat == 0) {
					Male_RR.push_back(male_vector[si]->mosq_id);
				}

			}

			Male_count_DD.push_back(Male_DD.size());
			Male_count_DR.push_back(Male_DR.size());
			Male_count_RR.push_back(Male_RR.size());

			cout << "\n count is";
			cout << Male_DD.size() << "\n" << Male_DR.size() << "\n" << Male_RR.size();


			//mate counting for each day for DD,DR,RR with female
			DD_mate_count_vect.push_back(env_1.DD_mate_cntr);
			env_1.DD_mate_cntr = 0;
			DR_mate_count_vect.push_back(env_1.DR_mate_cntr);
			env_1.DR_mate_cntr = 0;
			RR_mate_count_vect.push_back(env_1.RR_mate_cntr);
			env_1.RR_mate_cntr = 0;

			temp_female_cnt = get_adult_female_count();
			cout << "\n the female count from func is " << temp_female_cnt << "----- from vect " << female_vector.size();
			adult_female_daily_vect.push_back({ day,temp_female_cnt });
			int total_pop = egg_vector.size() + larve_vector.size() + pupe_vector.size() + male_vector.size() + female_vector.size(); //finding the population of all mosquitoes
			cout << "\n the total population of all mosquitoes is: " << total_pop;
		}





		// running only when MCMC needs to be calculated
		if (env_1.is_mcmc_simulation == 1) {

			//monthly female for multiple years
			map<int, map<int, int>> model_year_month_value;
			map<int, map<int, int>> emp_year_month_value;
			map<int, map<int, int>> emp_year_month_row_count;
			int max_emp_year_month_row_count_value = 0;
			model_year_month_value.clear();
			emp_year_month_value.clear();
			emp_year_month_row_count.clear();

			month_year mon_year;
			month_year start_mon_year = getDateFromDayNumber(env_1.start_mcmc_day);
			month_year end_mon_year = getDateFromDayNumber(env_1.end_mcmc_day);


			for (const auto& day_itr : adult_female_daily_vect) {


				if (day_itr.dayNumber < env_1.start_mcmc_day) {
					continue;
				}
				if (day_itr.dayNumber > env_1.end_mcmc_day) {
					break;
				}
				mon_year = getDateFromDayNumber(day_itr.dayNumber);
				//int month_num = getMonthFromDay(day_itr.dayNumber, 2021);

				// Aggregate data for the month
				model_year_month_value[mon_year.year][mon_year.month] += day_itr.value;

			}


			cout << "\n start and end years and month";
			cout << "\n start_year: " << start_mon_year.year << "  month: " << start_mon_year.month;
			cout << "\n end_year: " << end_mon_year.year << " month: " << end_mon_year.month;
			cout << "\n the values from month_year are\n\n";

			// finding maximum emperical monthly row value for given year 
			if (start_mon_year.year == end_mon_year.year) {
				for (int imonth = start_mon_year.month; imonth <= end_mon_year.month; imonth++) {
					//for (int imonth = 1; imonth <= 12; imonth++) {
					cout << "\n" << start_mon_year.year << "\t" << imonth << "\t" << model_year_month_value[start_mon_year.year][imonth];
					for (int ivec = 0; ivec < emp_data_year_number.size(); ivec++) {
						if (emp_data_year_number[ivec] == start_mon_year.year && emp_data_month_number[ivec] == imonth) {
							emp_year_month_value[start_mon_year.year][imonth] = emp_data_monthly_female_main[ivec];
							emp_year_month_row_count[start_mon_year.year][imonth] = emp_data_monthly_row_count[ivec];
							if (max_emp_year_month_row_count_value < emp_data_monthly_row_count[ivec]) {
								max_emp_year_month_row_count_value = emp_data_monthly_row_count[ivec];
							}
						}
					}
				}
			}
			else {

				for (int iyear = start_mon_year.year; iyear <= end_mon_year.year; iyear++) {
					if (iyear == end_mon_year.year) {
						for (int imonth = 1; imonth <= end_mon_year.month; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << model_year_month_value[iyear][imonth];
							for (int ivec = 0; ivec < emp_data_year_number.size(); ivec++) {
								if (emp_data_year_number[ivec] == iyear && emp_data_month_number[ivec] == imonth) {
									emp_year_month_value[iyear][imonth] = emp_data_monthly_female_main[ivec];
									emp_year_month_row_count[iyear][imonth] = emp_data_monthly_row_count[ivec];
									if (max_emp_year_month_row_count_value < emp_data_monthly_row_count[ivec]) {
										max_emp_year_month_row_count_value = emp_data_monthly_row_count[ivec];
									}
								}
							}
						}
					}
					else if (iyear == start_mon_year.year) {
						for (int imonth = start_mon_year.month; imonth <= 12; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << model_year_month_value[iyear][imonth];
							for (int ivec = 0; ivec < emp_data_year_number.size(); ivec++) {
								if (emp_data_year_number[ivec] == iyear && emp_data_month_number[ivec] == imonth) {
									emp_year_month_value[iyear][imonth] = emp_data_monthly_female_main[ivec];
									emp_year_month_row_count[iyear][imonth] = emp_data_monthly_row_count[ivec];
									if (max_emp_year_month_row_count_value < emp_data_monthly_row_count[ivec]) {
										max_emp_year_month_row_count_value = emp_data_monthly_row_count[ivec];
									}
								}
							}
						}
					}
					else {
						for (int imonth = 1; imonth <= 12; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << model_year_month_value[iyear][imonth];
							for (int ivec = 0; ivec < emp_data_year_number.size(); ivec++) {
								if (emp_data_year_number[ivec] == iyear && emp_data_month_number[ivec] == imonth) {
									emp_year_month_value[iyear][imonth] = emp_data_monthly_female_main[ivec];
									emp_year_month_row_count[iyear][imonth] = emp_data_monthly_row_count[ivec];
									if (max_emp_year_month_row_count_value < emp_data_monthly_row_count[ivec]) {
										max_emp_year_month_row_count_value = emp_data_monthly_row_count[ivec];
									}
								}
							}
						}
					}
				}
			}

			cout << "\n\n the maximum value in row count vector is: " << max_emp_year_month_row_count_value;
			cout << "\n\n the emperical values are\n\n";

			if (start_mon_year.year == end_mon_year.year) {
				for (int imonth = start_mon_year.month; imonth <= end_mon_year.month; imonth++) {
					//for (int imonth = 1; imonth <= 12; imonth++) {
					cout << "\n" << start_mon_year.year << "\t" << imonth << "\t" << emp_year_month_value[start_mon_year.year][imonth] << "\t" << emp_year_month_row_count[start_mon_year.year][imonth];
				}
			}
			else {
				for (int iyear = start_mon_year.year; iyear <= end_mon_year.year; iyear++) {
					if (iyear == end_mon_year.year) {
						for (int imonth = 1; imonth <= end_mon_year.month; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << emp_year_month_value[iyear][imonth] << "\t" << emp_year_month_row_count[iyear][imonth];
						}
					}
					else if (iyear == start_mon_year.year) {
						for (int imonth = start_mon_year.month; imonth <= 12; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << emp_year_month_value[iyear][imonth] << "\t" << emp_year_month_row_count[iyear][imonth];
						}
					}
					else {
						for (int imonth = 1; imonth <= 12; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << emp_year_month_value[iyear][imonth] << "\t" << emp_year_month_row_count[iyear][imonth];
						}
					}
				}
			}

			monthly_MCMC_female_csv_writer(model_year_month_value);
			long double loglike_total = 0;
			long double l_k = 0;
			cout << "\nweek\tmodel_week_mean\t\temperical_data";


			//checkinh if we are using any pre-value for max_emp_year_month_row_count_value
			if (env_1.all_years_max_emp_year_month_row_count_value > 0) {
				max_emp_year_month_row_count_value = env_1.all_years_max_emp_year_month_row_count_value;
			}


			//if strart yeaar= end_year
			if (start_mon_year.year == end_mon_year.year) {
				for (int imonth = start_mon_year.month; imonth <= end_mon_year.month; imonth++) {
					//for (int imonth = 1; imonth <= 12; imonth++) {
					cout << "\n" << start_mon_year.year << "\t" << imonth << "\t" << model_year_month_value[start_mon_year.year][imonth] << "\t\t" << emp_year_month_value[start_mon_year.year][imonth] << "\t" << emp_year_month_row_count[start_mon_year.year][imonth];
					double prob_succ = env_mcmc.over_disperssion_cand / (env_mcmc.over_disperssion_cand + model_year_month_value[start_mon_year.year][imonth] * (static_cast<double>(emp_year_month_row_count[start_mon_year.year][imonth]) / max_emp_year_month_row_count_value)); //  n/(n+mu) :: mu= simulation model weekly value

					l_k = static_cast<long double>(gsl_ran_negative_binomial_pdf(emp_year_month_value[start_mon_year.year][imonth], prob_succ, env_mcmc.over_disperssion_cand));

					loglike_total += log(l_k);
				}
			}
			else {

				for (int iyear = start_mon_year.year; iyear <= end_mon_year.year; iyear++) {
					if (iyear == end_mon_year.year) {
						for (int imonth = 1; imonth <= end_mon_year.month; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << model_year_month_value[iyear][imonth] << "\t\t" << emp_year_month_value[iyear][imonth] << "\t" << emp_year_month_row_count[iyear][imonth];
							double prob_succ = env_mcmc.over_disperssion_cand / (env_mcmc.over_disperssion_cand + model_year_month_value[iyear][imonth] * (static_cast<double>(emp_year_month_row_count[iyear][imonth]) / max_emp_year_month_row_count_value)); //  n/(n+mu) :: mu= simulation model weekly value

							l_k = static_cast<long double>(gsl_ran_negative_binomial_pdf(emp_year_month_value[iyear][imonth], prob_succ, env_mcmc.over_disperssion_cand));

							loglike_total += log(l_k);
						}
					}
					else if (iyear == start_mon_year.year) {
						for (int imonth = start_mon_year.month; imonth <= 12; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << model_year_month_value[iyear][imonth] << "\t\t" << emp_year_month_value[iyear][imonth] << "\t" << emp_year_month_row_count[iyear][imonth];
							double prob_succ = env_mcmc.over_disperssion_cand / (env_mcmc.over_disperssion_cand + model_year_month_value[iyear][imonth] * (static_cast<double>(emp_year_month_row_count[iyear][imonth]) / max_emp_year_month_row_count_value)); //  n/(n+mu) :: mu= simulation model weekly value

							l_k = static_cast<long double>(gsl_ran_negative_binomial_pdf(emp_year_month_value[iyear][imonth], prob_succ, env_mcmc.over_disperssion_cand));

							loglike_total += log(l_k);
						}
					}
					else {
						for (int imonth = 1; imonth <= 12; imonth++) {
							//for (int imonth = 1; imonth <= 12; imonth++) {
							cout << "\n" << iyear << "\t" << imonth << "\t" << model_year_month_value[iyear][imonth] << "\t\t" << emp_year_month_value[iyear][imonth] << "\t" << emp_year_month_row_count[iyear][imonth];
							double prob_succ = env_mcmc.over_disperssion_cand / (env_mcmc.over_disperssion_cand + model_year_month_value[iyear][imonth] * (static_cast<double>(emp_year_month_row_count[iyear][imonth]) / max_emp_year_month_row_count_value)); //  n/(n+mu) :: mu= simulation model weekly value

							l_k = static_cast<long double>(gsl_ran_negative_binomial_pdf(emp_year_month_value[iyear][imonth], prob_succ, env_mcmc.over_disperssion_cand));

							loglike_total += log(l_k);
						}
					}
				}
			}

			//checking if it is first run of mcmc
				//assigning to candi_log_like and curr_log_likelihood
			env_mcmc.cand_like_lihod = loglike_total;
			cout << "\n cand/loglike is: " << env_mcmc.cand_like_lihod;



			cout << "\n the real values from vector main() at the end";
			for (int icheck = 0; icheck < emp_data_monthly_female_main.size(); icheck++) {
				cout << "\n " << emp_data_monthly_female_main[icheck];
			}
		}

		if (global_zero_mosq == 1) {// try catch throw : when there are zero mosq, this will exit the loop and send data to files.
			cout << "\n exiting the simulation ---for--- loop to write data to files\n";
			if (sim_cnt < env_1.num_of_simulations_to_run) {// if there are more simulations left to run, this will continue the process
				global_zero_mosq = 0;
			}
			else {
				break;
			}
		}
		cout << "\n files in write";
		std::vector<std::pair<std::string, std::vector<int>>> vals3 = { {"time",time_count }, {"Eggies", egg_count}, {"Larve", larve_count},{"Pupe",pupe_count},{"Adult_male",male_count},{"Adult_female",female_count},{"MALE_DD",Male_count_DD},{"MALE_DR",Male_count_DR},{"MALE_RR",Male_count_RR},{"DD_mate_count",DD_mate_count_vect},{"DR_mate_count",DR_mate_count_vect},{"RR_mate_count",RR_mate_count_vect},{"Caring_capcity",all_dates_caring_cap_vector} };
		std::vector<std::pair<std::string, std::vector<double>>> ratios = { { "Larve_ratio",larve_ratio }, { "Pupe_ratio",pupe_ratio}, { "Male_ratio",male_ratio}, { "Female_ratio",female_ratio} };
		cout << "\n number of adults on equibrilium day: " << env_1.adult_males_on_equibrilium << "\n added with percent " << males_add_after_equi;

		temp_file_names = env_1.output_filepath + file_names_list + to_string(sim_cnt) + ".csv";
		cout << temp_file_names;
		write_csv(temp_file_names, vals3);
		//--checking--file_counter++;

		cout << "\n files in write";
		// write_d_csv("data1.csv", ratios);
		cout << "\n files in writing completed";
		male_count.clear();
		male_count.erase(male_count.begin(), male_count.end());
		male_count.shrink_to_fit();

		female_count.clear();
		female_count.erase(female_count.begin(), female_count.end());
		female_count.shrink_to_fit();

		egg_count.clear();
		egg_count.erase(egg_count.begin(), egg_count.end());
		egg_count.shrink_to_fit();

		larve_count.clear();
		larve_count.erase(larve_count.begin(), larve_count.end());
		larve_count.shrink_to_fit();

		pupe_count.clear();
		pupe_count.erase(pupe_count.begin(), pupe_count.end());
		pupe_count.shrink_to_fit();

		time_count.clear();
		time_count.erase(time_count.begin(), time_count.end());
		time_count.shrink_to_fit();


		male_vector.clear();
		male_vector.erase(male_vector.begin(), male_vector.end());
		male_vector.shrink_to_fit();

		larve_vector.clear();
		larve_vector.erase(larve_vector.begin(), larve_vector.end());
		larve_vector.shrink_to_fit();

		egg_vector.clear();
		egg_vector.erase(egg_vector.begin(), egg_vector.end());
		egg_vector.shrink_to_fit();

		pupe_vector.clear();
		pupe_vector.erase(pupe_vector.begin(), pupe_vector.end());
		pupe_vector.shrink_to_fit();

		female_vector.clear();
		female_vector.erase(female_vector.begin(), female_vector.end());
		female_vector.shrink_to_fit();

		female_ratio.clear();
		female_ratio.erase(female_ratio.begin(), female_ratio.end());
		female_ratio.shrink_to_fit();

		male_ratio.clear();
		male_ratio.erase(male_ratio.begin(), male_ratio.end());
		male_ratio.shrink_to_fit();

		larve_ratio.clear();
		larve_ratio.erase(larve_ratio.begin(), larve_ratio.end());
		larve_ratio.shrink_to_fit();

		pupe_ratio.clear();
		pupe_ratio.erase(pupe_ratio.begin(), pupe_ratio.end());
		pupe_ratio.shrink_to_fit();


		Male_DD.clear();
		Male_DD.erase(Male_DD.begin(), Male_DD.end());
		Male_DD.shrink_to_fit();

		Male_DR.clear();
		Male_DR.erase(Male_DR.begin(), Male_DR.end());
		Male_DR.shrink_to_fit();

		Male_RR.clear();
		Male_RR.erase(Male_RR.begin(), Male_RR.end());
		Male_RR.shrink_to_fit();

		Male_count_DD.clear();
		Male_count_DD.erase(Male_count_DD.begin(), Male_count_DD.end());
		Male_count_DD.shrink_to_fit();

		Male_count_DR.clear();
		Male_count_DR.erase(Male_count_DR.begin(), Male_count_DR.end());
		Male_count_DR.shrink_to_fit();

		Male_count_RR.clear();
		Male_count_RR.erase(Male_count_RR.begin(), Male_count_RR.end());
		Male_count_RR.shrink_to_fit();

		larve_ids.clear();
		larve_ids.erase(larve_ids.begin(), larve_ids.end());
		larve_ids.shrink_to_fit();


		egg_ids.clear();
		egg_ids.erase(egg_ids.begin(), egg_ids.end());
		egg_ids.shrink_to_fit();

		eggs_female_vector.clear();
		eggs_female_vector.erase(eggs_female_vector.begin(), eggs_female_vector.end());
		eggs_female_vector.shrink_to_fit();

		eggs_male_RR_vector.clear();
		eggs_male_RR_vector.erase(eggs_male_RR_vector.begin(), eggs_male_RR_vector.end());
		eggs_male_RR_vector.shrink_to_fit();

		eggs_male_DR_vector.clear();
		eggs_male_DR_vector.erase(eggs_male_DR_vector.begin(), eggs_male_DR_vector.end());
		eggs_male_DR_vector.shrink_to_fit();

		DD_mate_count_vect.clear();
		DD_mate_count_vect.erase(DD_mate_count_vect.begin(), DD_mate_count_vect.end());
		DD_mate_count_vect.shrink_to_fit();

		DR_mate_count_vect.clear();
		DR_mate_count_vect.erase(DR_mate_count_vect.begin(), DR_mate_count_vect.end());
		DR_mate_count_vect.shrink_to_fit();

		RR_mate_count_vect.clear();
		RR_mate_count_vect.erase(RR_mate_count_vect.begin(), RR_mate_count_vect.end());
		RR_mate_count_vect.shrink_to_fit();



		curr_mosq = head;

		cout << "\n " << head->mosq_id;
		cout << "\n " << curr_mosq->mosq_id;
		cout << "\n " << last_mosq->mosq_id;
		//}
		deleteList(head);
	}
	auto sim_end_time = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::seconds>(sim_start_time - start_time_main);
	cout << "\n the time to start simulation after main starts :" << duration.count() << " seconds";
	auto sim_duration = std::chrono::duration_cast<std::chrono::seconds>(sim_end_time - sim_start_time);
	cout << "\n the time to took for all " << env_1.num_of_simulations_to_run << " simulations is " << sim_duration.count() << " seconds";

	if (global_zero_mosq == 1) {// try catch throw : when there are zero mosq, this will exit the loop and send data to files.
		cout << "\n exiting the main_func_logic as there are no mosquiotes left\n";
		return;
	}
}



int get_num_lines_csv(std::string file_name) {
	std::ifstream inputFile(file_name);  // Replace "data.csv" with the actual filename

	if (!inputFile.is_open()) {
		std::cout << "Failed to open the file line count." << std::endl;
	}

	std::string line;
	int lineCount = 0;

	while (std::getline(inputFile, line)) {
		lineCount++;
	}

	std::cout << "Number of lines in the CSV file: " << lineCount << std::endl;

	inputFile.close();
	return lineCount;
}


void read_line_check_size_CC(char* buf, int size, FILE* fp) {
	fgets(buf, size, fp);
	size_t len = strlen(buf);
	if (buf[len - 1] != '\n' && len >= size - 1) {
		std::stringstream err_msg;
		err_msg << "Line greater than buffer size = " << size << ".\n";
		throw InputException(err_msg.str());
	}
}


//void import_age_data(const char* fname, std::vector<double>& sympt_probab)
void import_care_cap_and_dates_data(const char* fname, std::vector<string>& vect_CC_list, std::vector<string>& vect_date_string_start, std::vector<string>& vect_date_string_end, std::vector<std::chrono::system_clock::time_point>& date_vector_start, std::vector<std::chrono::system_clock::time_point>& date_vector_end) {

	FILE* fp;
	//int max_line_size = 256;
	constexpr int max_line_size = 256;
	cout << "\n inside the date and carecap func\n";
	int max_days2 = get_num_lines_csv(fname);
	constexpr int err_buf_size{ 1024 };
	char err_msg[err_buf_size];
	int i_line = 1;
	//char str1[30];
	char CC_str[50], date_start_str[50], date_end_str[50];



	// Initialization
	// --------------

	// Open file and check, raise error if unsucceded.
	fp = fopen(fname, "r");
	if (!fp) {
		snprintf(err_msg, err_buf_size, "Hey, age data file \"%s\" could not be opened.", fname);
		throw FileNotOpenedException(err_msg);
	}

	// File parsing
	// ------------

	try {

		// --- Ignore first line
		{
			char line[max_line_size + 1];
			read_line_check_size(line, max_line_size, fp);
			i_line++;
		}


		// --- Contents
		int line_c = get_num_lines_csv(env_1.miami_mcmc_file_path);
		//int this_file_lines_count = get_num_lines_csv("Miami_mcmc_results.csv");
		cout << "\n line count in csv of mcmc values is------------" << max_days2;
		int temporary_line_count = 0;
		for (int i_age = 0; i_age < max_days2 - 1; i_age++) { //subtracting -1 from max_days as this count conatins the colum header count as well
			char line[max_line_size + 1];
			// char* token;
			cout << "\n curreent day_number= " << temporary_line_count;
			temporary_line_count++;
			if (feof(fp)) {  // Premature end of file.
				snprintf(err_msg, err_buf_size, "Hey, parsing ended before expected (%d lines were expected).\n",
					max_days2 + 1);
				throw(InputException(err_msg));
			}

			read_line_check_size_CC(line, max_line_size, fp);  // LINE READING OCCURS HERE
			if (ferror(fp)) {  // Error after/while reading the line 
				throw(InputException("Hey, there was a problem reading a line.\n"));
			}
			cout << "\n the line about to read is : " << line;
			// Direct scan of parameters 
			int num_reads = sscanf(line, "%4s,%10s,%10s\n", CC_str, date_start_str, date_end_str);  // LINE PARSE OCCURS HERE!
			cout << CC_str << endl << date_start_str << endl << num_reads;

			vect_CC_list.push_back(CC_str);
			cout << "\n " << CC_str;
			vect_date_string_start.push_back(date_start_str);
			vect_date_string_end.push_back(date_end_str);

			//-----------------------
			//start date converting
			std::string string_date_start = date_start_str;

			// Convert string to date
			std::istringstream iss1(string_date_start);
			std::tm time1 = {};
			iss1 >> std::get_time(&time1, "%d-%m-%Y");
			std::chrono::system_clock::time_point start_date_value = std::chrono::system_clock::from_time_t(std::mktime(&time1));
			std::time_t epoch_value1 = std::chrono::system_clock::to_time_t(start_date_value);
			std::cout << "\n Epoch value: " << epoch_value1 << std::endl;
			epoch_value1 += 20000;
			start_date_value = std::chrono::system_clock::from_time_t(epoch_value1);

			date_vector_start.push_back(start_date_value);


			//end date converting
			std::string string_date_end = date_end_str;

			// Convert string to date
			std::istringstream iss2(string_date_end);
			std::tm time2 = {};
			iss2 >> std::get_time(&time2, "%d-%m-%Y");
			std::chrono::system_clock::time_point end_date_value = std::chrono::system_clock::from_time_t(std::mktime(&time2));

			// Store dates in a vector

			std::time_t epoch_value2 = std::chrono::system_clock::to_time_t(end_date_value);
			std::cout << "\n Epoch value: " << epoch_value2 << std::endl;
			epoch_value2 += 20000;
			end_date_value = std::chrono::system_clock::from_time_t(epoch_value2);


			date_vector_end.push_back(end_date_value);
			if (num_reads < 2)
				throw InputException("Hey, could not read all parameters of a line.\n");

			++i_line;
		}

		cout << "Date vects are from start===================";
		for (auto it = vect_CC_list.begin(); it != vect_CC_list.end(); it++)
		{
			cout << *it << " ";
		}

		cout << "\n the unique CC vals are: \n";
		set<string> unique_CC_vals(vect_CC_list.begin(), vect_CC_list.end()); //set data_struc for getting unique values if CC's names
		for (const auto& str : unique_CC_vals) {
			std::cout << str << std::endl;
		}
	}  // \try

	catch (InputException& e) {
		std::stringstream err_msg;
		err_msg << e.what();
		err_msg << "Problem occurred in line " << i_line << " of age data file \""
			<< fname << "\".\n";
		throw InputException(err_msg.str());
	}

	fclose(fp);
}


void eggDevelopmentAegypti(Parameters* p, double temperature) {

	double b0 = -0.7935988064;
	double b1 = 0.0652120418;
	double b2 = -0.0008103752;

	double T = temperature;
	double T2 = T * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->d_E = b0 + (b1 * T) + (b2 * T2);
	}
	else {
		p->d_E = 0.0001;
	}

	if (p->d_E < 0 | p->d_E > 1) {
		fprintf(stderr, "Error: Aegypti egg development rate is not between 0 and 1.\n");
		exit(0);
	}

}

/* Function for Calculating the Larvae development rate */
void larvaeDevelopmentAegypti(Parameters* p, double temperature) {

	double b0 = -3.314869;
	double b1 = 5.694568E-1;
	double b2 = -3.549990E-2;
	double b3 = 9.714943E-4;
	double b4 = -9.706293E-6;

	double T = temperature;
	double T2 = T * T;
	double T3 = T2 * T;
	double T4 = T3 * T;
	double T5 = T4 * T;
	double T6 = T5 * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->d_L = (b0 + (b1 * T) + (b2 * T2) + (b3 * T3) + (b4 * T4));
	}
	else {
		p->d_L = 0.0001;
	}

	if ((p->d_L * p->t_delta) < 0 | (p->d_L * p->t_delta) > 1) {
		fprintf(stderr, "Error: Aegypti larvae development rate is not between 0 and 1.\n");
		exit(0);
	}

}

/* Function for Calculating the Pupae development rate */
void pupaeDevelopmentAegypti(Parameters* p, double temperature) {

	double b0 = -8.219540;
	double b1 = 1.489082;
	double b2 = -9.733781E-2;
	double b3 = 2.771496E-3;
	double b4 = -2.846482E-5;

	double T = temperature;
	double T2 = T * T;
	double T3 = T2 * T;
	double T4 = T3 * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->d_P = b0 + (b1 * T) + (b2 * T2) + (b3 * T3) + (b4 * T4);
	}
	else {
		p->d_P = 0.0001;
	}

	if (p->d_P < 0 | p->d_P > 1) {
		fprintf(stderr, "Error: Aegypti pupae development rate is not between 0 and 1.\n");
		exit(0);
	}

}

/* Function for Calculating the Adult development rate */
void adultDevelopmentAegypti(Parameters* p, double temperature) {

	double b0 = 4.245790;
	double b1 = -0.291939;
	double b2 = 0.005087;
	double b3 = 0.;
	double b4 = 0.;

	double T = temperature;
	double T2 = T * T;
	double T3 = T2 * T;
	double T4 = T3 * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->d_A = b0 + (b1 * T) + (b2 * T2);
	}
	else {
		p->d_A = 0.0001;
	}

	if ((p->d_A * p->t_delta) < 0 | (p->d_A * p->t_delta) > 1) {
		fprintf(stderr, "Error: Aegypti adult development rate is not between 0 and 1.\n");
		exit(0);
	}

}

/* Function for Calculating the Egg mortality rate */
void eggMortalityAegypti(Parameters* p, double temperature) {

	double b0 = 0.04481102;
	double b1 = -0.01516262;
	double b2 = 0.00105380;

	double T = temperature;
	double T2 = T * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->m_E = b0 + (b1 * T) + (b2 * T2);
	}
	else {
		p->m_E = 0.9999;
	}

	if (p->m_E < 0 | p->m_E > 1) {
		fprintf(stderr, "Error: Aegypti egg mortality rate is not between 0 and 1.\n");
		exit(0);
	}

}

/* Function for Calculating the Larvae mortality rate */
void larvaeMortalityAegypti(Parameters* p, double temperature) {

	double b0 = 2.224551;
	double b1 = -3.711882E-1;
	double b2 = 2.239631E-2;
	double b3 = -5.744944E-4;
	double b4 = 5.402667E-6;
	double r = 1;

	double T = temperature;
	double T2 = T * T;
	double T3 = T2 * T;
	double T4 = T3 * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->m_L = (b0 + (b1 * T) + (b2 * T2) + (b3 * T3) + (b4 * T4)) * r;
	}
	else {
		p->m_L = 0.9999;
	}

	if (p->m_L < 0 | p->m_L > 1) {
		fprintf(stderr, "Error: Aegypti larvae mortality rate is not between 0 and 1.\n");
		exit(0);
	}

}

/* Function for Calculating the Pupae mortality rate */
void pupaeMortalityAegypti(Parameters* p, double temperature) {

	double b0 = 0.0267266094;
	double b1 = 0.0003277987;
	double b2 = 0.0001095109;
	double r = 1;

	double T = temperature;
	double T2 = T * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->m_P = (b0 + (b1 * T) + (b2 * T2)) * r;
	}
	else {
		p->m_P = 0.9999;
	}

	if (p->m_P < 0 | p->m_P > 1) {
		fprintf(stderr, "Error: Aegypti pupae mortality rate is not between 0 and 1.\n");
		exit(0);
	}

}

/* Function for Calculating the Adult mortality rate */
void adultMortalityAegypti(Parameters* p, double temperature) {

	double b0 = 8.594566E-1;
	double b1 = -1.539282E-1;
	double b2 = 1.059943E-2;
	double b3 = -3.182785E-4;
	double b4 = 3.510619E-6;
	double r = 4;

	double T = temperature;
	double T2 = T * T;
	double T3 = T2 * T;
	double T4 = T3 * T;

	if (p == NULL) {
		fprintf(stderr, "Error: NULL parameters.\n");
		exit(0);
	}

	if (T >= 15 && T <= 35) {
		p->m_A = (b0 + (b1 * T) + (b2 * T2) + (b3 * T3) + (b4 * T4)) * r;
	}
	else {
		p->m_A = 0.9999;
	}

	if (p->m_A < 0 | p->m_A > 1) {
		fprintf(stderr, "Error: Aegypti adult mortality rate is not between 0 and 1.\n");
		exit(0);
	}

}

int line_counter_in_csv(std::string file_name) {
	std::ifstream inputFile(file_name);  // Replace "data.csv" with the actual filename

	if (!inputFile.is_open()) {
		std::cout << "Failed to open the file." << std::endl;
	}

	std::string line;
	int lineCount = -1;

	while (std::getline(inputFile, line)) {
		lineCount++;
	}

	std::cout << "Number of lines in the CSV file: " << lineCount << std::endl;

	inputFile.close();
	return lineCount;
}


//void import_age_data(const char* fname, std::vector<double>& sympt_probab)
void import_date_and_temp_data(const char* fname, std::vector<string>& vect_date_string, std::vector<double>& vect_temps, std::vector<std::chrono::system_clock::time_point>& date_vector) {

	FILE* fp;
	//int max_line_size = 256;
	constexpr int max_line_size = 256;

	int max_days1 = line_counter_in_csv(fname);
	cout << "\n number of days in csv are: " << max_days1;
	constexpr int err_buf_size{ 1024 };
	char err_msg[err_buf_size];
	int i_line = 1;
	char str1[30];
	double tmp_temperature;


	// Initialization
	// --------------

	// Open file and check, raise error if unsucceded.
	fp = fopen(fname, "r");
	if (!fp) {
		snprintf(err_msg, err_buf_size, "Hey, age data file \"%s\" could not be opened.", fname);
		throw FileNotOpenedException(err_msg);
	}

	// File parsing
	// ------------

	try {

		// --- Ignore first line
		{
			char line[max_line_size + 1];
			read_line_check_size(line, max_line_size, fp);
			i_line++;
		}


		// --- Contents
		for (int i_age = 0; i_age < max_days1; i_age++) {
			char line[max_line_size + 1];
			// char* token;

			if (feof(fp)) {  // Premature end of file.
				snprintf(err_msg, err_buf_size, "Hey, parsing ended before expected (%d lines were expected).\n",
					max_days1 + 1);
				throw(InputException(err_msg));
			}

			read_line_check_size(line, max_line_size, fp);  // LINE READING OCCURS HERE
			if (ferror(fp)) {  // Error after/while reading the line 
				throw(InputException("Hey, there was a problem reading a line.\n"));
			}
			cout << "\n the line about to read is in temp data: " << line;
			// Direct scan of parameters 
			int num_reads = sscanf(line, "%10s,%lf\n", str1, &tmp_temperature);  // LINE PARSE OCCURS HERE!
			cout << "\n\n the temp is: " << tmp_temperature;
			cout << "\n\n the date is " << str1;
			vect_temps.push_back(tmp_temperature);
			vect_date_string.push_back(str1);

			//-----------------------

			std::string string_date = str1;

			// Convert string to date
			std::istringstream iss(string_date);
			std::tm time = {};
			iss >> std::get_time(&time, "%d-%m-%Y");
			std::chrono::system_clock::time_point date_value = std::chrono::system_clock::from_time_t(std::mktime(&time));


			// adding 20,000 to epoch value to set the time zone and match csv file--&*&*&*&*&*&*&*&
			std::time_t epoch_value = std::chrono::system_clock::to_time_t(date_value);
			std::cout << "\n Epoch value: " << epoch_value << std::endl;
			epoch_value += 20000;
			date_value = std::chrono::system_clock::from_time_t(epoch_value);
			// Store date in a vector
			//cout << "\n the date in func string is " << string_date;
			date_vector.push_back(date_value);
			if (num_reads < 2)
				throw InputException("Hey, could not read all parameters of a line.\n");

			++i_line;
		}


		/*       for (const auto& date : date_vector) {
				   std::time_t time = std::chrono::system_clock::to_time_t(date);
				   std::tm* local_time = std::gmtime(&time);
				   std::cout << "\n the date in func is: " << std::put_time(local_time, "%d-%m-%Y") << " ";
			   }*/
	}  // \try

	catch (InputException& e) {
		std::stringstream err_msg;
		err_msg << e.what();
		err_msg << "Problem occurred in line " << i_line << " of age data file \""
			<< fname << "\".\n";
		throw InputException(err_msg.str());
	}

	fclose(fp);
}


void read_CC_vals_by_map(std::vector<std::string>& column_names_vect, std::map<std::string, std::vector<double>>& CC_map) {
	std::ifstream inputFile(env_1.miami_mcmc_file_path);  // Replace "data.csv" with the actual filename

	using double_vector = std::vector<double>;
	//using map_of_vectors = std::map<std::string, double_vector>;


	if (!inputFile.is_open()) {
		std::cout << "Failed to open the file map mcmc." << std::endl;

	}

	std::string line;
	//std::vector<std::vector<double>> columns;
	std::vector<int> integerColumn;

	// to read coulm names from csv
	//std::vector<std::vector<std::string>> column_names;
	std::getline(inputFile, line);
	std::istringstream iss(line);
	std::string value;
	//std::vector<std::string> column_names_vect;
	std::string temp_col_name;

	while (std::getline(iss, value, ',')) {
		//cout << " \n the valu from func is" << value;
		std::string result;
		for (char c : value) {
			if (c != '"') {
				result.push_back(c);
			}
		}
		//cout << " \n the result from func is" << result;
		column_names_vect.push_back(result);
	}

	int num_of_columns = column_names_vect.size();// num of columns in csv file

	for (int col_iter = 0; col_iter < num_of_columns; col_iter++) {
		temp_col_name = column_names_vect.at(col_iter);
		CC_map[temp_col_name] = double_vector();
	}

	while (std::getline(inputFile, line)) {
		std::istringstream iss(line);
		std::string value;
		std::vector<double> column;
		int col_iter2 = 0;

		while (std::getline(iss, value, ',')) {
			double number;
			std::istringstream(value) >> number;
			//column.push_back(number);

			temp_col_name = column_names_vect.at(col_iter2);
			CC_map[temp_col_name].push_back(number);
			col_iter2++;
		}	
	}
	inputFile.close();
}

void read_line_check_size(char* buf, int size, FILE* fp) {
	fgets(buf, size, fp);
	size_t len = strlen(buf);
	if (buf[len - 1] != '\n' && len >= size - 1) {
		std::stringstream err_msg;
		err_msg << "Line greater than buffer size = " << size << ".\n";
		throw InputException(err_msg.str());
	}
}



void calc_likelihood(vector <int>& female_count_vect) {

}

void read_emperical_data_frm_csv(string filename) {
	string filePath = filename;

	// Open the CSV file
	ifstream file(filePath);

	// Check if the file is open
	if (!file.is_open()) {
		cerr << "Error opening file read_emperical_data_frm_csv: " << filePath << std::endl;
		return;
	}

	// Read the first line to skip column names
	string header;
	getline(file, header);

	// Read the file line by line
	string line;
	while (std::getline(file, line)) {
		// Use a stringstream to split the line into columns
		istringstream ss(line);
		int value1, value2;

		// Read values from the stringstream
		char delimiter;
		if (ss >> value1 >> delimiter >> value2) {
			// Add values to the vectors
			emp_data_week_number.push_back(value1);
			emp_data_weekly_female.push_back(value2);
		}
		else {
			cerr << "Error parsing line: " << line << std::endl;
		}
	}

	// Close the file
	file.close();
}

void read_imperical_monthly_data_frm_csv(string filename, vector <int>& emp_data_year_number, vector<int>& emp_data_month_number, vector<int>& emp_data_monthly_female, vector <int>& emp_data_monthly_row_count) {
	string filePath = filename;

	// file should contain in this order only year,month and value
	// Open the CSV file
	ifstream file(filePath);

	// Check if the file is open
	if (!file.is_open()) {
		cerr << "Error opening file: " << filePath << std::endl;
		return;
	}

	// Read the first line to skip column names
	string header;
	getline(file, header);

	// Read the file line by line
	string line;
	while (std::getline(file, line)) {
		// Use a stringstream to split the line into columns
		istringstream ss(line);
		int value1, value2, year, month_row_count;

		// Read values from the stringstream
		char delimiter;
		if (ss >> year >> delimiter >> value1 >> delimiter >> value2 >> delimiter >> month_row_count) {
			// Add values to the vectors
			emp_data_year_number.push_back(year);
			emp_data_month_number.push_back(value1);
			emp_data_monthly_female.push_back(value2);
			emp_data_monthly_row_count.push_back(month_row_count);
		}
		else {
			cerr << "Error parsing line: " << line << std::endl;
		}
	}

	// Close the file
	file.close();
}

void MCMC_csv_writer() {
	std::ofstream csvFile(env_1.mcmc_outputfile_path, ios::app);

	if (!csvFile.is_open()) {
		std::cerr << "Error opening file! MCMC_CSV_writer" << std::endl;
		return;
	}
	csvFile << env_mcmc.itr_num << "," << env_mcmc.cc1_cand << "," << env_mcmc.cc1_curr << "," << env_mcmc.cc2_cand << "," << env_mcmc.cc2_curr << "," << env_mcmc.cc3_cand << "," << env_mcmc.cc3_curr << "," << env_mcmc.cc4_cand << "," << env_mcmc.cc4_curr << "," << env_mcmc.eggs_cand << "," << env_mcmc.eggs_curr << "," << env_mcmc.over_disperssion_cand << "," << env_mcmc.over_disperssion_curr << "," << env_mcmc.cand_like_lihod << "," << env_mcmc.curr_like_lihod << "\n";

	csvFile.close();

	return;
}


void weekly_MCMC_female_csv_writer(vector<int>& model_weekly_calc_female) {



	if (env_mcmc.itr_num == 0) {
		std::ofstream csvFile(env_1.weekly_mcmc_female_file_path, ios::out);
		int log_like_start_week = env_1.start_mcmc_day / env_1.week_length;
		for (int icheck = 0; icheck < model_weekly_calc_female.size(); icheck++) {
			csvFile << log_like_start_week++;
			if (icheck != model_weekly_calc_female.size() - 1) {
				csvFile << ",";
			}
		}
		csvFile << "\n";
	}


	std::ofstream csvFile(env_1.weekly_mcmc_female_file_path, ios::app);

	if (!csvFile.is_open()) {
		std::cerr << "Error opening file! weekly_mcm_female_csv_writer" << std::endl;
		return;
	}




	for (int icheck = 0; icheck < model_weekly_calc_female.size(); icheck++) {
		csvFile << model_weekly_calc_female.at(icheck);
		if (icheck != model_weekly_calc_female.size() - 1) {
			csvFile << ",";
		}

	}
	csvFile << "\n";

	csvFile.close();

	return;
}


bool isLeapYear(int year) {
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
		return true;
	}
	return false;
}


int getMonthFromDay(int dayNumber, int year) {

	if (isLeapYear(year)) {

		if (dayNumber <= 30) return 1;      // January
		if (dayNumber <= 59) return 2;      // February (leap year)
		if (dayNumber <= 90) return 3;      // March
		if (dayNumber <= 120) return 4;     // April
		if (dayNumber <= 151) return 5;     // May
		if (dayNumber <= 181) return 6;     // June
		if (dayNumber <= 212) return 7;     // July
		if (dayNumber <= 243) return 8;     // August
		if (dayNumber <= 273) return 9;     // September
		if (dayNumber <= 304) return 10;    // October
		if (dayNumber <= 334) return 11;    // November
		return 12;                          // December

	}
	else {
		if (dayNumber <= 30) return 1;
		if (dayNumber <= 58) return 2;
		if (dayNumber <= 89) return 3;
		if (dayNumber <= 119) return 4;
		if (dayNumber <= 150) return 5;
		if (dayNumber <= 180) return 6;
		if (dayNumber <= 211) return 7;
		if (dayNumber <= 242) return 8;
		if (dayNumber <= 272) return 9;
		if (dayNumber <= 303) return 10;
		if (dayNumber <= 333) return 11;
		return 12;
	}
}

int get_adult_female_count() {
	int adult_female_counter = 0;
	struct mosq* ptr_fe;
	ptr_fe = head;
	if (head == NULL) {
		cout << "\n linked list is empty";
		return -1;
	}

	while (ptr_fe != NULL) {
		if (ptr_fe->is_female == 1 && ptr_fe->status == 3) {
			adult_female_counter++;
		}
		ptr_fe = ptr_fe->next;
	}

	return adult_female_counter;
}


void monthly_MCMC_female_csv_writer(map<int, map<int, int>>& model_year_month_value) {


	cout << "\n inside writer monthly: ";
	month_year start_mon_year = getDateFromDayNumber(env_1.start_mcmc_day);
	month_year end_mon_year = getDateFromDayNumber(env_1.end_mcmc_day);

	if (env_mcmc.itr_num == 0) {

		std::ofstream csvFile(env_1.model_monthly_female_file_path_output, ios::out);

		string header;



		if (start_mon_year.year == end_mon_year.year) {
			for (int imonth = start_mon_year.month; imonth <= end_mon_year.month; imonth++) {
				//for (int imonth = 1; imonth <= 12; imonth++) {
				header = to_string(start_mon_year.year) + "_" + to_string(imonth);
				csvFile << header;
				if (imonth != end_mon_year.month) {
					csvFile << ",";
				}
			}
		}
		else {
			for (int iyear = start_mon_year.year; iyear <= end_mon_year.year; iyear++) {
				if (iyear == end_mon_year.year) {
					for (int imonth = 1; imonth <= end_mon_year.month; imonth++) {
						//for (int imonth = 1; imonth <= 12; imonth++) {
						header = to_string(iyear) + "_" + to_string(imonth);
						csvFile << header;
						if (imonth != end_mon_year.month) {
							csvFile << ",";
						}
					}
				}
				else if (iyear == start_mon_year.year) {
					for (int imonth = start_mon_year.month; imonth <= 12; imonth++) {
						//for (int imonth = 1; imonth <= 12; imonth++) {
						header = to_string(iyear) + "_" + to_string(imonth);
						csvFile << header;
						csvFile << ",";
					}
				}
				else {
					for (int imonth = 1; imonth <= 12; imonth++) {
						//for (int imonth = 1; imonth <= 12; imonth++) {
						header = to_string(iyear) + "_" + to_string(imonth);
						csvFile << header;
						csvFile << ",";
					}
				}
			}
		}
		csvFile << "\n";
	}


	std::ofstream csvFile(env_1.model_monthly_female_file_path_output, ios::app);

	if (!csvFile.is_open()) {
		std::cerr << "Error opening file! monthly_MCMC_female_csv_writer" << std::endl;
		return;
	}


	if (start_mon_year.year = end_mon_year.year) {
		for (int imonth = start_mon_year.month; imonth <= end_mon_year.month; imonth++) {
			//for (int imonth = 1; imonth <= 12; imonth++) {
			csvFile << model_year_month_value[start_mon_year.year][imonth];
			if (imonth != end_mon_year.month) {
				csvFile << ",";
			}
		}
	}							
	else {
		for (int iyear = start_mon_year.year; iyear <= end_mon_year.year; iyear++) {
			if (iyear == end_mon_year.year) {
				for (int imonth = 1; imonth <= end_mon_year.month; imonth++) {
					//for (int imonth = 1; imonth <= 12; imonth++) {
					csvFile << model_year_month_value[iyear][imonth];
					if (imonth != end_mon_year.month) {
						csvFile << ",";
					}
				}
			}
			else if (iyear == start_mon_year.year) {
				for (int imonth = start_mon_year.month; imonth <= 12; imonth++) {
					//for (int imonth = 1; imonth <= 12; imonth++) {
					csvFile << model_year_month_value[iyear][imonth];
					csvFile << ",";
				}
			}
			else {
				for (int imonth = 1; imonth <= 12; imonth++) {
					//for (int imonth = 1; imonth <= 12; imonth++) {
					csvFile << model_year_month_value[iyear][imonth];
					csvFile << ",";
				}
			}
		}
	}


	csvFile << "\n";


	csvFile.close();

	return;
}


bool isLeapYear_for_month_agg(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

month_year getDateFromDayNumber(int dayNumber) {
	month_year mon_year;
	int model_start_year = env_1.model_start_year;
	int daysInYear = isLeapYear_for_month_agg(model_start_year) ? 366 : 365; // 2021 is a starting reference year.

	int yearDifference = dayNumber / daysInYear;
	mon_year.year = model_start_year + yearDifference;

	dayNumber -= yearDifference * daysInYear;

	int daysInMonth[12] = { 31, 28 + isLeapYear_for_month_agg(mon_year.year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	for (int i = 0; i < 12; ++i) {
		if (dayNumber < daysInMonth[i]) {
			mon_year.month = i + 1;
			break;
		}
		dayNumber -= daysInMonth[i];
	}

	return mon_year;
}

// Function to read the matrix from a CSV file
vector<vector<double>> read_surveil_data_matrix_from_csv(const string& filePath) {
	ifstream file(filePath);
	vector<vector<double>> surveil_data_matrix;
	string line;

	if (!file.is_open()) {
		cerr << "Failed to open file." << endl;
		return surveil_data_matrix;  // Return an empty matrix on failure
	}

	while (getline(file, line)) {
		stringstream ss(line);
		string value;
		vector<double> row;

		while (getline(ss, value, ',')) {
			row.push_back(stod(value));
		}

		surveil_data_matrix.push_back(row);
	}

	file.close();
	return surveil_data_matrix;
}


bool get_value_from_surveil_data_matrix(const vector<vector<double>>& matrix, int rowIndex, int colIndex, double& specific_day_surveil_value) {
	if (rowIndex >= 0 && rowIndex < matrix.size() &&
		colIndex >= 0 && colIndex < matrix[rowIndex].size()) {
		specific_day_surveil_value = matrix[rowIndex][colIndex];
		return true;
	}
	else {
		cerr << "Index out of bounds." << endl;
		return false;
	}
}


vector<double> read_constant_scenario_specific_month_100_sims_surveil_data_from_csv(const string& filePath) {
	ifstream file(filePath);
	vector<double> surveil_data_vector;
	string line;

	if (!file.is_open()) {
		cerr << "Failed to open file specific month 100 sims csv file." << endl;
		return surveil_data_vector;  // Return an empty matrix on failure
	}

	while (getline(file, line)) {

		try {
			// Convert the line to a double and add to the vector
			surveil_data_vector.push_back(stod(line));
		}
		catch (const invalid_argument& e) {
			cerr << "Invalid data in file: " << line << endl;
			// You can choose to handle or skip invalid lines here
		}
	}

	file.close();
	return surveil_data_vector;
}

#ifndef SIMULATOR_H_
#define SIMULATOR_H_
#include "Emergency_Room.h"
#include "Check_In.h"
#include "Random.h"
#include <map>
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <ios>
#include <string>

Random ran;

class Simulator {
private:
	int total_time = 10080;
	int clock;
	Check_In* check;
	Emergency_Room* em;

	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}
public:
	Simulator(std::vector<Patient*> people) {
		check = new Check_In(people);
		em = new Emergency_Room();
	}

	void enter_data() {
		std::cout << "Welcome to CS273ville Hospital\n";
		int rate = read_int("Please enter arrival rate (patients/hour): ", 1, 60);
		double arrival_rate = rate / 60.0;
		check->set_arriving_time(arrival_rate);
		int num_nurses = read_int("Please enter number of nurses working: ", 1, 20);
		em->set_Nurse_available(num_nurses);
		int num_doctors = read_int("Please enter number of doctors working: ", 1, 20);
		em->set_Doctors_available(num_doctors);
		em->setWaitingRoom(check);
	}

	void run_simulation() {
		for (clock = 0; clock < total_time; clock++) {
			check->update(clock);
			em->run_emergency(clock);
		}
	}

	void show_stats() {
		std::cout << "Number of patients served: " << em->get_served() << std::endl;
		std::cout << "Total time waited by patients (min): " << em->get_wait() << std::endl;
		double average_time = 1.0 * em->get_wait() / em->get_served();
		std::cout << "Average visit time per patient (min): " << average_time  << std::endl;
		std::cout << std::endl;
	}

	void post_simulation(){
		int user;
		do {
			std::cout << "Would you Like to see the patients served at the hospital? Enter: 1" << std::endl;
			std::cout << "Else search for an individual served at the hospital? Enter: 2 " << std::endl;
			std::cout << "Enter 3 to exit the program" << endl;
			cin >> user;
			std::cout << std::endl;

			if (user == 1) {
				em->seeserved();
			}
			if(user == 2) {
				em->findbyname();
			}
		} while (user != 3);
			
			
	}
};
#endif
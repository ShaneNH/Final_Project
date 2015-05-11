#include <iostream>
#include <vector>
#include <stdexcept>
#include "Get_names.h"
#include "Simulator.h"
#include "Random.h"
#include "Patient.h"
#include <string>
using namespace std;

int main() {
	cin.exceptions(ios_base::failbit);
		
	Random ran;
	get_names names;
	vector<Patient*> town = names.town_names();
			Simulator h(town);
			h.enter_data();
			h.run_simulation();
			h.show_stats();
				try {
					h.post_simulation();
				}

				catch (ios_base::failure &exp) {
					cout << "Bad input." << endl;
					cin.clear();
					cin.ignore(1024);
				}
				catch (...) {
					cout << "Error..." << endl;
				}
			 
	} 
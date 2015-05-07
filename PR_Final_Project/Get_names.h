#ifndef GET_NAMES_H
#include "Patient.h"
#include <vector>
#include <fstream>
#include <string>
#define GET_NAMES_H_

class get_names {
private:
	vector <Patient*> names;

public:
	vector<Patient*> town_names() {
		ifstream input("residents_273ville.txt");
		if (input.fail())
		{
			cout << "File does not exist!" << endl; 
		}

		std::string patient_name;

		while (!input.eof()) {
			getline(input, patient_name);
			names.push_back(new Patient(patient_name));
		}
		return names;
	}
};
#endif
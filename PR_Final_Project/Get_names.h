#ifndef GET_NAMES_H
#include "Patient.h"
#include <vector>
#include <fstream>
#include <string>
#define GET_NAMES_H_
using namespace std;

class get_names {
private:
	// vector container to add patient objects, used to check in all patients from the txt file to the hospital.
	vector <Patient*> names;

public:
	// funtion to return a vector of patient objects.
	vector<Patient*> town_names() {
		ifstream input("residents_273ville.txt");
		if (input.fail())
		{
			cout << "File does not exist!" << endl; 
		}

		std::string patient_name;

		while (!input.eof()) {
			// Get every single line
			getline(input, patient_name);
			// create a patient with the name read to create an new patient object
			names.push_back(new Patient(patient_name));
		}
		// return the vector
		return names;
	}
};
#endif
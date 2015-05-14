#ifndef PATIENT_H_
#define PATIENT_H_
#include <iostream>
#include <string>
using namespace std;

class Patient {
public:
	/// Properties found on Patients.
	string name;
	int start_treatment;
	int finished_treatment;
	bool serving;
	int illness_rank;
	int total_time;
	int arrival_patient;
	friend class Patient_Compare;

	// Default constructor that sets the properties when we create a patient object
	Patient(string name) : name(name), serving(false), start_treatment(-1), 
		arrival_patient(-1), finished_treatment(-1), illness_rank(-1),
		total_time(-1) {

	}
	// Our Getters for the properties we said that a patient will have.
	string getname() {
		return name;
	}
	int getstart() {
		return start_treatment;
	}
	int getfinsished(){
		return finished_treatment;
	}
	bool getserving() {
		return serving;
	}
	int getillness() {
		return illness_rank;
	}
	int gettotal() {
		return total_time;
	}
	int getarrival() {
		return arrival_patient;
	}

};
#endif
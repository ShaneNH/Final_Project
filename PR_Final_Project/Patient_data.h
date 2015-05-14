#ifndef PATIENT_DATA_H
#define	PATIENT_DATA_H	
#include <string>
#include <vector>
using namespace std;


class Patient_data {
public:
	// Properties
	string name;
	int patient_visits;
	int total_wait_time_patient;
	// vector to push all the illness numbers to a container so we can keep track of every illness rank they
	//recieved when visting the hospital multiple times.
	vector<int> injury;
	friend class Emergency_Room;

	// Default constructor
	Patient_data() {
		name = " ";
		patient_visits = 0;
		total_wait_time_patient = 0;
	}
	// return the average wait time of the patient
	double average_waiting() {
		return 1.0 * total_wait_time_patient / patient_visits;
	}
	// Overload constructor
	Patient_data(std::string name, int time, int severity){
		this->name = name;
		patient_visits = 1;
		total_wait_time_patient = time;
		injury.push_back(severity);

	}
};
#endif
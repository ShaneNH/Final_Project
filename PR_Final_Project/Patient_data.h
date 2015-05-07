#ifndef PATIENT_DATA_H
#define	PATIENT_DATA_H	
#include <string>
#include <vector>
using namespace std;


class Patient_data {
public:
	string name;
	int patient_visits;
	int total_wait_time_patient;
	vector<int> injury;


	Patient_data() {
		name = " ";
		patient_visits = 0;
		total_wait_time_patient = 0;
	}
	/*double average_waiting() {
		return 1.0 * total_wait_time_patient / patient_visits;
	}*/
	Patient_data(std::string name, int time, int severity){
		this->name = name;
		patient_visits = 1;
		total_wait_time_patient = time;
		injury.push_back(severity);

	}
};
#endif
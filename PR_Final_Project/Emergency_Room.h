#ifndef EMERGENCY_ROOM_H_
#define EMERGENCY_ROOM_H_
#include "Check_In.h"
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <stdexcept>
#include "Patient_data.h"
#include "Fantastic_Two.h"
#include "Doctor_Nurse.h"
#include "Simulator.h"
using namespace std;


class Emergency_Room {
private:
	// Properties of an emergency room
	int amount_doctors;
	int amount_nurses;
	Check_In* check;
	int amount_served;
	int accum_wait;
	// map to contain a key with the name and pair it with objects of patient_data.
	map<string, Patient_data*> patient_info;
	// Vector to hold the number of doctors and nurses the user wants in the hospital.
	vector<Fantastic_Two*> team;
	
	
public:
	// Default constructor
	Emergency_Room() {
		amount_served = 0;
		accum_wait = 0;
	}

	// Getter and setters
	int get_wait() {
		return accum_wait;
	}

	int get_served() {
		return amount_served;
	}
	void setWaitingRoom(Check_In* wait) {
		check = wait;
	}
	void addmoreTime(int more) {
		accum_wait += more;
	}

	void inc_served() {
		amount_served++;
	}
	// add the doctor objects to the vector
	void set_Doctors_available(int PH) {
		amount_doctors = PH;
		for (int i = 0; i < amount_doctors; i++) {
			team.push_back(new Doctor);
		}
	}
	// add the nurses object to the vector team
	void set_Nurse_available(int total) {
		amount_nurses = total;
		for (int i = 0; i < amount_nurses; i++) {
			team.push_back(new Nurse);
		}
	}
	// run the emergenct room
	void run_emergency(int clock) {
		for (int j = 0; j < team.size(); j++) {
			// return the patient data object after either the doctor or nurse completed the job.
			Patient_data* data = team[j]->beginpatients(clock, check);
			if (data->total_wait_time_patient != 0)
			{
				// add to the accumalated wait time for all patients
				addmoreTime(data->total_wait_time_patient);
				// increment amount served
				amount_served++;
				// create an iterator to go through the map
				map<string, Patient_data*>::iterator it;
				// find the patients name
				it = patient_info.find(data->name);
				if (it == patient_info.end())
				{
					// if the iterator did not find the patient at all, then insert a new key with the name of the patient
			  // and the return object from above
					patient_info.insert(make_pair(data->name, data));
				}
				else {
					// if the patient is not a new patient then set the follwing properties 
					it->second->patient_visits++;
					it->second->injury.push_back(data->injury[0]);
					it->second->total_wait_time_patient += data->total_wait_time_patient; 
				}

			}
			
			team[j]->startnewpatient(clock, check);
		}
	}
	// function to see everyone who is inserted inside the map. The iterator does all the work so we can output the names,
	// of the patients served.
	void seeserved() {
		map<string, Patient_data*>::iterator it;
		it = patient_info.begin();
		while (it != patient_info.end()) {
			cout << "Name: " << it->first << endl;
			it++;
		}
		cout << endl;
	}
	/// function so the user can enter the patient they want to find. 
	void findbyname() {
		string s;
		cout << "Enter the name of the patient." << endl;
		cin >> s;
		

		map<string, Patient_data*>::iterator it;
		it = patient_info.find(s);

		if (it != patient_info.end()) {
			cout << "Name: " << it->first << endl;
			// number of times visited
			cout << "Number of times visited: " << it->second->patient_visits << endl;
			cout << "List of profile severities: " << endl;
			// output the illness rank from every hospital visit
			for (int s = 0; s < it->second->injury.size(); s++) {
				cout << it->second->injury[s] << endl;
			}
			cout << "Average visit time is: " << it->second->average_waiting() << " min" <<  endl;
			cout << endl;
		}
		else {
			cout << "Name not found!" << endl;
			cout << endl;
		}
	}

};
#endif
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
	int amount_doctors;
	int amount_nurses;
	Check_In* check;
	int amount_served;
	int accum_wait;
	map<string, Patient_data*> patient_info;
	vector<Fantastic_Two*> team;
	
	
public:
	Emergency_Room() {
		amount_served = 0;
		accum_wait = 0;
	}

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

	void set_Doctors_available(int PH) {
		amount_doctors = PH;
		for (int i = 0; i < amount_doctors; i++) {
			team.push_back(new Doctor);
		}
	}
	void set_Nurse_available(int total) {
		amount_nurses = total;
		for (int i = 0; i < amount_nurses; i++) {
			team.push_back(new Nurse);
		}
	}

	void run_emergency(int clock) {
		for (int j = 0; j < team.size(); j++) {
			Patient_data* data = team[j]->beginpatients(clock, check);
			if (data->total_wait_time_patient != 0)
			{
				addmoreTime(data->total_wait_time_patient);
				amount_served++;
				map<string, Patient_data*>::iterator it;
				it = patient_info.find(data->name);
				if (it == patient_info.end())
				{
					
					patient_info.insert(make_pair(data->name, data));
				}
				else {
					it->second->patient_visits++;
					it->second->injury.push_back(data->injury[0]);
					it->second->total_wait_time_patient += data->total_wait_time_patient; 
				}

			}
			team[j]->startnewpatient(clock, check);
		}
	}

	void seeserved() {
		map<string, Patient_data*>::iterator it;
		it = patient_info.begin();
		while (it != patient_info.end()) {
			cout << "Name: " << it->first << endl;
			it++;
		}
		cout << endl;
	}

	void findbyname() {
		string s;
		cout << "Enter the name of the patient." << endl;
		cin >> s;
		

		map<string, Patient_data*>::iterator it;
		it = patient_info.find(s);

		if (it != patient_info.end()) {
			cout << "Name: " << it->first << endl;
			cout << "Number of times visited: " << it->second->patient_visits << endl;
			cout << "List of profile severities: " << endl;
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
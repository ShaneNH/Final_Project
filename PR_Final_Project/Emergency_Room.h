#ifndef EMERGENCY_ROOM_H_
#define EMERGENCY_ROOM_H_
#include "Check_In.h"
#include <vector>
#include <map>
#include <string>
#include "Patient_data.h"
#include "Fantastic_Two.h"
#include "Doctor_Nurse.h"
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
		amount_served = 1;
		accum_wait = 0;
	}

	int get_wait() {
		return accum_wait;
	}

	int get_served() {
		return amount_served;
	}
	void setWaitingRoom(Check_In * wait){
		check = wait;
	}
	void addmoreTime(int more){
		accum_wait += more;
	}

	void inc_served(){
		amount_served++;
	}

	void set_Doctors_available(int PH){
		amount_doctors = PH;
		for (int i = 0; i < amount_doctors; i++){
			team.push_back(new Doctor);
		}
	}
	void set_Nurse_available(int total){
		amount_nurses = total;
		for (int i = 0; i < amount_nurses; i++){
			team.push_back(new Nurse);
		}
	}

	void run_emergency(int clock) {
		for (int j = 0; j < team.size(); j++) {
			Patient_data* data = team[j]->beginpatients(clock,check);
			if (data->total_wait_time_patient != 0)
			{
				addmoreTime(data->total_wait_time_patient);
				inc_served();
				pair<string, Patient_data*> info(data->name, data);
				patient_info.insert(info);
			}
			team[j]->startnewpatient(clock, check);
		}
		
	}

};
#endif
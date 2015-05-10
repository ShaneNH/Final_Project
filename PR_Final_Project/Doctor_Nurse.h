#ifndef DOCTOR_NURSE_H
#define DOCTOR_NURSE_H
#include "Fantastic_Two.h"
#include "Patient_data.h"
#include "Check_In.h"
#include "Patient.h"
#include "Random.h"
#include <queue>
using namespace std;
extern Random ran;

class Doctor : public Fantastic_Two {
public:
	Doctor() {

	}

	Patient_data* beginpatients(int clock, Check_In* check) {
		if (!currentpatient.empty())
		{
			Patient* guy = currentpatient.front();
			if ((clock - guy->start_treatment) > guy->total_time)
			{
				check->dropserved();
				guy->finished_treatment = clock;
				guy->serving = false;
				int time;
				time = clock - guy->arrival_patient;
				currentpatient.pop();
				return new Patient_data(guy->name, time, guy->illness_rank);
			}
		}
		return new Patient_data;
	}
	
	
	void startnewpatient(int clock, Check_In* check) {
		if (currentpatient.empty()) {
			if (!check->empty2()) {
				Patient* guy = check->front1();
				check->pop1();
				guy->start_treatment = clock;
				guy->total_time = ran.next_int(19) + 1;
				currentpatient.push(guy);
			}
			else {
				if (!check->empty()) {
					Patient *patient = check->front();
					check->pop2();
					patient->start_treatment = clock;
					patient->total_time = ran.next_int(19) + 1;
					currentpatient.push(patient);
				}
			}
		}
	}

};

class Nurse : public Fantastic_Two {
public:
	Nurse() {}

	Patient_data* beginpatients(int clock, Check_In* check) {
		if (!currentpatient.empty())
		{
			Patient* patient = currentpatient.front();
			if ((clock - patient->start_treatment) > patient->total_time) {
				check->dropserved();
				patient->finished_treatment = clock;
				patient->serving = false;
				int time;
				time = clock - patient->arrival_patient;
				currentpatient.pop();
				return new Patient_data(patient->getname(), time, patient->getillness());
			}
		}
		return new Patient_data;
	}

	void startnewpatient(int clock, Check_In* check) {
		if (currentpatient.empty()) {
			if (!check->empty()) {
				Patient* patient = check->front();
				check->pop2();
				patient->start_treatment = clock;
				patient->total_time = ran.next_int(9) + 1;
				currentpatient.push(patient);
			}
		}
	}
};
#endif


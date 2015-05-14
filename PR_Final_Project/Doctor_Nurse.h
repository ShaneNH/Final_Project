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
	// No argument constructor for the object Doctor.
	Doctor() {

	}

	// Function of what a doctor does when there are patients in the current serving queue. Function returns
	// an information object with the different properties found in the Patient_Data class. 
	Patient_data* beginpatients(int clock, Check_In* check) {
		if (!currentpatient.empty())
		{
			// Returns the person who is first in line to use as a object to set its properties found in the Patient Class.
			Patient* guy = currentpatient.front();
			if ((clock - guy->start_treatment) > guy->total_time)
			{
				// decrement the amount served
				check->dropserved();
				// set the time the patient was finshed
				guy->finished_treatment = clock;
				// set the patients boolean to false because it just got served.
				guy->serving = false;
				int time;
				// Sets the total wait time for the patient when he or she visited the hospital
				time = clock - guy->arrival_patient;
				// Pop the patient that just got served from the currentpatients queue.
				currentpatient.pop();
				// return and create with the overload constructor found in Patient_data.
				return new Patient_data(guy->name, time, guy->illness_rank);
			}
		}
		// return its default constructor that is not a overload.
		return new Patient_data;
	}
	
	// function to get a new patient and put them into the currentpatient serving queue.
	void startnewpatient(int clock, Check_In* check) {
		if (currentpatient.empty()) {
			if (!check->empty2()) {
				// Get patient from Check-In
				Patient* guy = check->front1();
				// Pop the patient we just grabed from the serious priority queue.
				check->pop1();
				// Set the the time the patient started the process of being treated
				guy->start_treatment = clock;
				// Set the amount of time the Doctor is going to take on seeing this patient
				guy->total_time = ran.next_int(19) + 1;
				//Push the patient into the current patient queue
				currentpatient.push(guy);
			}
			else {
				if (!check->empty()) {
					// return the patient found on the top of the minor priority queue.
					Patient *patient = check->front();
					// Pop the patient we just grabed from the minor priority queue.
					check->pop2();
					// set the properties found in the patient class
					patient->start_treatment = clock;
					// Random time that the doctor will spend on seeing the patient
					patient->total_time = ran.next_int(19) + 1;
					// Push the patient to the currentpatient queue.
					currentpatient.push(patient);
				}
			}
		}
	}

};

class Nurse : public Fantastic_Two {
public:
	// no argument constructor
	Nurse() {}
	// Same process as above accept now its a nurse doing the work
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
				// Pop patient from minor priority queue
				check->pop2();
				patient->start_treatment = clock;
				// set the total treatment time to a random number stated on our problem 1 paper.
				patient->total_time = ran.next_int(9) + 1;
				currentpatient.push(patient);
			}
		}
	}
};
#endif


#ifndef CHECK_IN_H
#define CHECK_IN_H
#include <queue>
#include <vector>
#include "Patient.h"
#include "Emergency_Room.h"
#include "Patient_Compare.h"
#include "Random.h"
using namespace std;

extern Random ran;

class Check_In {
public:
	// Properties we need when checking in every patient 
	double arrival_rate;
	int numbeingserved;
	// Our two priority queues to add the patients in the right place
	priority_queue<Patient*, vector<Patient*>, Patient_Compare> minor;
	priority_queue<Patient*, vector<Patient*>, Patient_Compare> serious;
	vector<Patient *> humans;
	friend class Emergency_Room;
	// Default constructor
	Check_In(vector<Patient*> humans) : humans(humans) {
		numbeingserved = 0;
	}
	// Setter and getters + pop functions
	void set_arriving_time(double arrival_rate) {
		this->arrival_rate = arrival_rate;
	}
	void dropserved() {
		numbeingserved--;
	}
	bool empty(){
		return minor.empty();
	}
	bool empty2() {
		return serious.empty();
	}
	Patient* front() {
		return minor.top();
	}
	Patient* front1() {
	return serious.top();
	
	}
	void pop1() {
		 serious.pop();
	}
	void pop2() {
		minor.pop();
	}
	
	// Used for our simulator
	void update(int clock) {
		// return a double from the function found in Random header file
		double bum = ran.next_double();
		if (bum < arrival_rate && numbeingserved < 2000)
		{
			numbeingserved++;
			int index_patient;
			do {
				// return a random number to grab a patient from the check in vector
				index_patient = ran.next_int(humans.size() - 1);
			} while (humans[index_patient]->serving);
			// set the serving to true
			humans[index_patient]->serving = true;
			// set that one persons arrival to what the clock is
			humans[index_patient]->arrival_patient = clock;
			int serverity;
			int serverity1;
			// return a random number to set the probablity for patients to recieve their illness rank
			serverity = ran.next_int(10);
			if (serverity < 7) {
				// get a random number from 1 to 10 for illness rank
				serverity1 = ran.next_int(10) + 1;
				// set the patients illness rank we grabed to what we go from above
				humans[index_patient]->illness_rank = serverity1;
				//push the patient to the minor 
				minor.push(humans[index_patient]);
			}
			else if (serverity < 9) {
				// number from 11 to 15
				serverity1 = ran.next_int(5) + 11;
				// set the illness rank of the patient
				humans[index_patient]->illness_rank = serverity1;
				//push to the serious
				serious.push(humans[index_patient]);
			}
			else {
				// number from 16 to 20
				serverity1 = ran.next_int(5) + 16;
				// set the current grabed patient illness rank
				humans[index_patient]->illness_rank = serverity1;
				//push the patient to the serious.
				serious.push(humans[index_patient]);
			}
		}
	}
	
};
#endif
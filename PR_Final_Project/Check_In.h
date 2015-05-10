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
	double arrival_rate;
	int numbeingserved;
	priority_queue<Patient*, vector<Patient *>, Patient_Compare> minor;
	priority_queue<Patient*, vector<Patient*>, Patient_Compare> serious;
	vector<Patient *> humans;
	friend class Emergency_Room;

	Check_In(vector<Patient*> humans) : humans(humans) {
		numbeingserved = 0;
	}
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


	void update(int clock) {
		int bum = ran.next_double();
		if (bum < arrival_rate && numbeingserved < 2000)
		{
			numbeingserved++;
			int index_patient;
			do {
				index_patient = ran.next_int(humans.size() - 1);
			} while (humans[index_patient]->serving);
			humans[index_patient]->serving = true;
			humans[index_patient]->arrival_patient = clock;
			int serverity;
			int serverity1;
			serverity = ran.next_int(9);
			if (serverity < 7) {
				serverity1 = ran.next_int(9) + 1;
				humans[index_patient]->illness_rank = serverity1;
				minor.push(humans[index_patient]);
			}
			else if (serverity < 9) {
				serverity1 = ran.next_int(4) + 11;
				humans[index_patient]->illness_rank = serverity1;
				serious.push(humans[index_patient]);
			}
			else {
				serverity1 = ran.next_int(4) + 16;
				humans[index_patient]->illness_rank = serverity1;
				serious.push(humans[index_patient]);
			}
		}
	}
	
};
#endif
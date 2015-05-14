#ifndef PATIENT_COMPARE_H
#define PATIENT_COMPARE_H
#include <iostream>
#include "Patient.h"
using namespace std;

class Patient_Compare{
public:
	// Used to keep our heap priority queue with the object that has the highest illness rank at the top of the tree,
	//  for both our minor and series priority queue.
	bool operator() (Patient* a,Patient* b) {
		return (a->illness_rank < b->illness_rank);
	}
};
#endif
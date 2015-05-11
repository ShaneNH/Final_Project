#ifndef PATIENT_COMPARE_H
#define PATIENT_COMPARE_H
#include <iostream>
#include "Patient.h"
using namespace std;

class Patient_Compare{
public:
	bool operator() (Patient* a,Patient* b) {
		return (a->illness_rank < b->illness_rank);
	}
};
#endif
#ifndef PATIENT_COMPARE_H
#define PATIENT_COMPARE_H
#include <iostream>
#include "Patient.h"

class Patient_Compare{
public:
	bool operator() (Patient* a, Patient* b) {
		return (a->getillness() < b->getillness());
	}
};
#endif
#ifndef	FANTASTIC_TWO_H
#define	FANTASTIC_TWO_H
#include "Patient_data.h"
#include "Check_In.h"
#include "Patient.h"
#include <queue>
using namespace std;

class Fantastic_Two {
protected:
	queue<Patient*> currentpatient;
public:
	virtual Patient_data* beginpatients(int clock, Check_In* check) = 0;
	virtual void startnewpatient(int clock, Check_In* check) = 0;
};
#endif
#include <iostream>
#include <vector>
#include "Get_names.h"
#include "Simulator.h"
#include "Random.h"
#include "Patient.h"
using namespace std;

int main() {
	Random ran;
	get_names names;
	vector<Patient*> town = names.town_names();
	Simulator h(town);
	h.enter_data();
	h.run_simulation();
	h.show_stats();
	h.post_simulation();


}
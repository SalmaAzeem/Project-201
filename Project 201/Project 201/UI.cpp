#include <iostream>
#include "UI.h"

void UI::interface(Station** array, int num) const {
	int waiting_sp = array[num]->Special_Passengers_Backward.Count() + array[num]->Special_Passengers_Forward.Count();
	int waiting_np = array[num]->Normal_Passengers_Backward.Count() + array[num]->Normal_Passengers_Forward.Count();
	int waiting_wp = array[num]->Wheel_Passengers_Backward.Count() + array[num]->Wheel_Passengers_Forward.Count();
	Passenger** array_sp_f = array[num]->Array_Special_Passengers_Forward();
	Passenger** array_sp_b = array[num]->Array_Special_Passengers_Backward();
	Passenger** array_np_f = array[num]->Array_Normal_Passengers_Forward();
	Passenger** array_np_b = array[num]->Array_Normal_Passengers_Backward();
	Passenger** array_wp_f = array[num]->Array_Wheel_Passengers_Forward();
	Passenger** array_wp_b = array[num]->Array_Wheel_Passengers_Backward();
	std::cout << "================ Station#" << num << " =====================\n";
	std::cout << waiting_sp << " Waiting SP: FWD[ ";
	for (int i = 0; i < array[num]->Special_Passengers_Forward.Count(); i++) {
		std::cout << array_sp_f[i]->getId() << ", ";
	}
	std::cout << "] ";
	std::cout << " BCK[ ";
	for (int i = 0; i < array[num]->Special_Passengers_Backward.Count(); i++) {
		std::cout << array_sp_b[i]->getId() << ", ";
	}
	std::cout << "] " << std::endl;
	std::cout << waiting_np << " Waiting NP: FWD[ ";
	for (int i = 0; i < array[num]->Normal_Passengers_Forward.Count(); i++) {
		std::cout << array_np_f[i]->getId() << ", ";
	}
	std::cout << "] ";
	std::cout << " BCK[ ";
	for (int i = 0; i < array[num]->Normal_Passengers_Backward.Count(); i++) {
		std::cout << array_np_b[i]->getId() << ", ";
	}
	std::cout << "] " << std::endl;
	std::cout << waiting_wp << " Waiting WP: FWD[ ";
	for (int i = 0; i < array[num]->Wheel_Passengers_Forward.Count(); i++) {
		std::cout << array_wp_f[i]->getId() << ", ";
	}
	std::cout << "] ";
	std::cout << " BCK[ ";
	for (int i = 0; i < array[num]->Wheel_Passengers_Backward.Count(); i++) {
		std::cout << array_wp_b[i]->getId() << ", ";
	}
	std::cout << "] " << std::endl;
}

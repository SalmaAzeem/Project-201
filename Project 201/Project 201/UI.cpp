#include <iostream>
#include "UI.h"

void UI::interface(Station** array, int num, int hours, int minutes, Passenger** removed, int count_removed) const {
	//create arrays for each station to include the passengers stored in every queue
	int waiting_sp = array[num]->Special_Passengers_Backward.Count() + array[num]->Special_Passengers_Forward.Count();
	int waiting_np = array[num]->Normal_Passengers_Backward.Count() + array[num]->Normal_Passengers_Forward.Count();
	int waiting_wp = array[num]->Wheel_Passengers_Backward.Count() + array[num]->Wheel_Passengers_Forward.Count();
	int total_number_of_buses = array[num]->Buses_Mixed_Backward.Count() + array[num]->Buses_Mixed_Forward.Count() + array[num]->Buses_Wheel_Backward.Count() + array[num]->Buses_Wheel_Forward.Count();
	int number_buses_zero_station = array[0]->Buses_Mixed_Backward.Count() + array[0]->Buses_Mixed_Forward.Count() + array[0]->Buses_Wheel_Backward.Count() + array[0]->Buses_Wheel_Forward.Count();
	Passenger** array_sp_f = array[num]->Array_Special_Passengers_Forward();
	Passenger** array_sp_b = array[num]->Array_Special_Passengers_Backward();
	Passenger** array_np_f = array[num]->Array_Normal_Passengers_Forward();
	Passenger** array_np_b = array[num]->Array_Normal_Passengers_Backward();
	Passenger** array_wp_f = array[num]->Array_Wheel_Passengers_Forward();
	Passenger** array_wp_b = array[num]->Array_Wheel_Passengers_Backward();
	Bus** array_mix_f = array[num]->Array_Mixed_Forward();
	Bus** array_mix_b = array[num]->Array_Mixed_Backward();
	Bus** array_wheel_f = array[num]->Array_Wheel_Forward();
	Bus** array_wheel_b = array[num]->Array_Mixed_Backward();
	std::cout << "Current Time (Hour:Min)==> " << hours << ":" << minutes << std::endl;
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
	std::cout << total_number_of_buses << " Buses at this station:" << std::endl;
	if (array[num]->Buses_Mixed_Forward.Count() > 0) {
		for (int i = 0; i < array[num]->Buses_Mixed_Forward.Count(); i++) {
			std::cout << "B" << array_mix_f[i]->getId() << "[FWD, MBus, " << array_mix_f[i]->get_capacity() << "] " << " {";
			for (int j = 0; j < array_mix_f[i]->Bus_passengers.count_passengers(); j++) {
				std::cout << array_mix_f[i]->Bus_passengers.GetPassenger()->getvalue()->getId() << ", ";
			}
			std::cout << "}" << std::endl;
		}
	}
	if (array[num]->Buses_Mixed_Backward.Count() > 0) {
		for (int i = 0; i < array[num]->Buses_Mixed_Backward.Count(); i++) {
			std::cout << "B" << array_mix_b[i]->getId() << "[BCK, MBus, " << array_mix_b[i]->get_capacity() << "] " << " {";
			for (int j = 0; j < array_mix_b[i]->Bus_passengers.count_passengers(); j++) {
				std::cout << array_mix_b[i]->Bus_passengers.GetPassenger()->getvalue()->getId() << ", ";
			}
			std::cout << "}" << std::endl;
		}
	}
	if (array[num]->Buses_Wheel_Forward.Count() > 0) {
		for (int i = 0; i < array[num]->Buses_Wheel_Forward.Count(); i++) {
			std::cout << "B" << array_wheel_f[i]->getId() << "[FWD, WBus, " << array_wheel_f[i]->get_capacity() << "] " << " {";
			for (int j = 0; j < array_wheel_f[i]->Bus_passengers.count_passengers(); j++) {
				std::cout << array_wheel_f[i]->Bus_passengers.GetPassenger()->getvalue()->getId() << ", ";
			}
			std::cout << "}" << std::endl;
		}
	}
	if (array[num]->Buses_Wheel_Backward.Count() > 0) {
		for (int i = 0; i < array[num]->Buses_Wheel_Backward.Count(); i++) {
			std::cout << "B" << array_wheel_b[i]->getId() << "[BCK, WBus, " << array_wheel_b[i]->get_capacity() << "] " << " {";
			for (int j = 0; j < array_wheel_b[i]->Bus_passengers.count_passengers(); j++) {
				std::cout << array_wheel_b[i]->Bus_passengers.GetPassenger()->getvalue()->getId() << ", ";
			}
			std::cout << "}" << std::endl;
		}
	}
	
	if (num == 0) {
		std::cout << "----------------------------------------------------------------------" << std::endl;
		std::cout << number_buses_zero_station << " In-Checkup buses: ";
		if (array[0]->Buses_Mixed_Forward.Count() > 0) {
			for (int i = 0; i < array[0]->Buses_Mixed_Forward.Count(); i++) {
				std::cout << array_mix_f[i]->getId() << ", ";
			}
		}
		if (array[0]->Buses_Mixed_Backward.Count() > 0) {
			for (int i = 0; i < array[0]->Buses_Mixed_Backward.Count(); i++) {
				std::cout << array_mix_b[i]->getId() << ", ";
			}
		}
		if (array[0]->Buses_Wheel_Forward.Count() > 0) {
			for (int i = 0; i < array[0]->Buses_Wheel_Forward.Count(); i++) {
				std::cout << array_wheel_f[i]->getId() << ", ";
			}
		}
		if (array[0]->Buses_Wheel_Backward.Count() > 0) {
			for (int i = 0; i < array[0]->Buses_Wheel_Backward.Count(); i++) {
				std::cout << array_wheel_b[i]->getId() << ", ";
			}
		}
		std::cout << std::endl;
	}
	
	std::cout << "----------------------------------------------------------------------" << std::endl;
	std::cout << count_removed << " Finished Passengers: ";
	//takes the removed array of the finished passengers 
	for (int i = 0; i < count_removed; i++) {
		std::cout << removed[i]->getId() << " , ";
	}
	std::cout << "\n";
}

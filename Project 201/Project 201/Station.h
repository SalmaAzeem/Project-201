#pragma once
#ifndef STATION_H
#define STATION_H
#include "Queue.h"
#include "Bus.h"
#include "Passenger.h"
#include <iostream>


class Station {
private:
	int Station_Number;

public:
	PriorityQueuePassenger Special_Passengers;
	PriorityQueuePassenger Normal_Passengers;
	BusQueue Queue_Buses;
	PriorityQueuePassenger Wheel_Passengers;
	Station(int number) : Station_Number(number) {}
	void Add_to_Station(Passenger* obj, string type) {
		if (type == "SP") {
			if (obj->getPassengerspecial() == 'A') { Special_Passengers.enQueue(obj, 3); }
			else if (obj->getPassengerspecial() == 'P') { Special_Passengers.enQueue(obj, 2); }
			else if (obj->getPassengerspecial() == 'O') { Special_Passengers.enQueue(obj, 1); }
			else { std::cout << "Incorrect Special Type. " << "\n"; }
		}
		else if (type == "NP") {
			Normal_Passengers.enQueue(obj, 0);
		}
		else if (type == "WP") { Wheel_Passengers.enQueue(obj, 0); }
		else { std::cout << "Incorrect Type." << "\n"; }
	}
	void Leave_Station(Passenger* obj) {
		Normal_Passengers.Leave_Passenger(obj);
	}
	void Print_Station() {
		std::cout << "\nSpecial Passengers: " << "\n";
		Special_Passengers.Print_Queue();
		std::cout << "\nNormal Passengers: " << "\n";
		Normal_Passengers.Print_Queue();
		std::cout << "\nWheel Passengers: " << "\n";
		Wheel_Passengers.Print_Queue();
		//int count_f_s = count_forward(Special_Passengers.get_array_passengers(), Special_Passengers.Count());
		//int count_f_n = count_forward(Normal_Passengers.get_array_passengers(), Normal_Passengers.Count());
		//int count_f_w = count_forward(Wheel_Passengers.get_array_passengers(), Wheel_Passengers.Count());
		//int count_b_w = count_backward(Wheel_Passengers.get_array_passengers(), Wheel_Passengers.Count());
		//int count_b_s = count_backward(Special_Passengers.get_array_passengers(), Special_Passengers.Count());
		//int count_b_n = count_backward(Normal_Passengers.get_array_passengers(), Normal_Passengers.Count());
		//Passenger** array_f_s = passenger_forward(Special_Passengers.get_array_passengers(), Special_Passengers.Count());
		//Passenger** array_f_n = passenger_forward(Normal_Passengers.get_array_passengers(), Normal_Passengers.Count());
		//Passenger** array_f_w = passenger_forward(Wheel_Passengers.get_array_passengers(), Wheel_Passengers.Count());
		//Passenger** array_b_s = passenger_backward(Special_Passengers.get_array_passengers(), Special_Passengers.Count());
		//Passenger** array_b_n = passenger_backward(Normal_Passengers.get_array_passengers(), Normal_Passengers.Count());
		//Passenger** array_b_w = passenger_backward(Wheel_Passengers.get_array_passengers(), Wheel_Passengers.Count());
		//std::cout << "\n===============  Station #" << Station_Number << "  ===================" << std::endl;
		//std::cout << Special_Passengers.Count() << " Waiting SP: FWD[";
		//for (int i = 0; i < count_f_s; i++) { std::cout << array_f_s[i]->getId() << ", "; }
		//std::cout << "]" << std::endl;
		//std::cout << Normal_Passengers.Count() << " Waiting NP: FWD--> " << count_f_n << " BCK--> " << count_b_n << std::endl;
		//std::cout << Wheel_Passengers.Count() << " Waiting WP: FWD--> " << count_f_w << " BCK--> " << count_b_w << std::endl;

	}
	int Count_Station() {
		int total_count{}, count1{}, count2{}, count3{};
		count1 = Special_Passengers.Count();
		count2 = Normal_Passengers.Count();
		count3 = Wheel_Passengers.Count();
		total_count = count1 + count2 + count3;
		return total_count;
	}
	void Add_Bus(Bus* obj) {
		Queue_Buses.enQueue(obj, 0);
	}
	void Print_Bus_At_Station() { Queue_Buses.Print_Queue(); }
	void Count_Bus_At_Station() { Queue_Buses.Count(); }
	int get_station_number() const { return Station_Number; }
	Passenger** Array_Special_Passengers() {
		return Special_Passengers.get_array_passengers();
	}
	Passenger** Array_Normal_Passengers() {
		return Normal_Passengers.get_array_passengers();
	}
	Passenger** Array_Wheel_Passengers() {
		return Wheel_Passengers.get_array_passengers();
	}
	int count_forward(Passenger** array, int num) {
		int count{};
		for (int i = 0; i < num; i++) {
			if (array[i]->getLeaveStationId() > get_station_number()) {
				count++;
			}
		}
		return count;
	}
	int count_backward(Passenger** array, int num) {
		int count{};
		for (int i = 0; i < num; i++) {
			if (array[i]->getLeaveStationId() < get_station_number()) {
				count++;
			}
		}
		return count;
	}
	Passenger** passenger_forward(Passenger** array, int num) {
		int count = count_forward(array, num);
		Passenger** forwardarray = new Passenger * [count];
		for (int i = 0; i < num; i++) {
			if (array[i]->getLeaveStationId() > get_station_number()) {
				forwardarray[i] = array[i];
			}
		}
		return forwardarray;
	}
	Passenger** passenger_backward(Passenger** array, int num) {
		int count = count_backward(array, num);
		Passenger** backwardarray = new Passenger * [count];
		for (int i = 0; i < num; i++) {
			if (array[i]->getLeaveStationId() < get_station_number()) {
				backwardarray[i] = array[i];
			}
		}
		return backwardarray;
	}
};

#endif // !STATION


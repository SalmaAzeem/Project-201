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
	PriorityQueuePassenger Special_Passengers_Forward;
	PriorityQueuePassenger Normal_Passengers_Forward;
	PriorityQueuePassenger Wheel_Passengers_Forward;
	PriorityQueuePassenger Special_Passengers_Backward;
	PriorityQueuePassenger Normal_Passengers_Backward;
	PriorityQueuePassenger Wheel_Passengers_Backward;
	BusQueue Buses_Mixed_Forward;
	BusQueue Buses_Wheel_Forward;
	BusQueue Buses_Mixed_Backward;
	BusQueue Buses_Wheel_Backward;
public:
	
	Station(int number) : Station_Number(number) {}
	//--------------------------------------Modify the code-----------------------------------------------

	/*void Add_to_Station(Passenger* obj) {
		if (obj->getPassengertype() == "SP") {
			if (obj->getPassengerspecial() == 'A') { Special_Passengers.enQueue(obj, 3); }
			else if (obj->getPassengerspecial() == 'P') { Special_Passengers.enQueue(obj, 2); }
			else if (obj->getPassengerspecial() == 'O') { Special_Passengers.enQueue(obj, 1); }
			else { std::cout << "Incorrect Special Type. " << "\n"; }
		}
		else if (obj->getPassengertype() == "NP") {
			Normal_Passengers.enQueue(obj, 0);
		}
		else if (obj->getPassengertype() == "WP") { Wheel_Passengers.enQueue(obj, 0); }
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
	}*/
};

#endif // !STATION


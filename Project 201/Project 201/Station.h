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
	int count_promoted = 0;
	Station(int number) : Station_Number(number) {}
	Station(){}

	bool Promote(Passenger* obj) {
		bool promotion = obj->waiting_time_increase(obj->get_Maximum_Waiting_Time());
		if (promotion) {
			if (obj->getDirection() == 'F') {
				Normal_Passengers_Forward.Leave_Passenger(obj); //same complexity as the deque
				Special_Passengers_Forward.enQueue(obj, 3);
				count_promoted++;
				cout <<"count_promoted is ================" << count_promoted;
			}
			else {
				Normal_Passengers_Backward.Leave_Passenger(obj);
				Special_Passengers_Backward.enQueue(obj, 3);
				count_promoted++;
			}
			return true;
		}
		return false;
	}
	void Add_to_Station(Passenger* obj) {
		if (obj->getPassengertype() == "SP" && obj->getDirection() == 'B') {
			if (obj->getPassengerspecial() == 'A') { Special_Passengers_Backward.enQueue(obj, 3); }
			else if (obj->getPassengerspecial() == 'P') { Special_Passengers_Backward.enQueue(obj, 2); }
			else if (obj->getPassengerspecial() == 'O') { Special_Passengers_Backward.enQueue(obj, 1); }
			else { std::cout << "Incorrect Special Type. " << "\n"; }
		}
		else if (obj->getPassengertype() == "SP" && obj->getDirection() == 'F') {
			if (obj->getPassengerspecial() == 'A') { Special_Passengers_Backward.enQueue(obj, 3); }
			else if (obj->getPassengerspecial() == 'P') { Special_Passengers_Backward.enQueue(obj, 2); }
			else if (obj->getPassengerspecial() == 'O') { Special_Passengers_Backward.enQueue(obj, 1); }
			else { std::cout << "Incorrect Special Type. " << "\n"; }
		}
		else if (obj->getPassengertype() == "NP" && obj->getDirection() == 'B') { Normal_Passengers_Backward.enQueue(obj, 0); }
		else if (obj->getPassengertype() == "NP" && obj->getDirection() == 'F') { Normal_Passengers_Forward.enQueue(obj, 0); }

		else if (obj->getPassengertype() == "WP" && obj->getDirection() == 'B') { Wheel_Passengers_Backward.enQueue(obj, 0); }
		else if (obj->getPassengertype() == "WP" && obj->getDirection() == 'F') { Wheel_Passengers_Forward.enQueue(obj, 0); }
		else { std::cout << "Incorrect Type." << "\n"; }
	}
	void Leave_Station(Passenger* obj) {
		Normal_Passengers_Backward.Leave_Passenger(obj);
		Normal_Passengers_Forward.Leave_Passenger(obj);
	}
	void Print_Station() {
		std::cout << "Station #" << get_station_number() << std::endl;
		std::cout << "Foward Special Passengers: ";
		Special_Passengers_Forward.Print_Queue();
		std::cout << "\n";
		std::cout << "Backward Special Passengers: ";
		Special_Passengers_Backward.Print_Queue();
		std::cout << "\n";
		std::cout << "Foward Normal Passengers: ";
		Normal_Passengers_Forward.Print_Queue();
		std::cout << "\n";		
		std::cout << "Backward Normal Passengers: ";
		Normal_Passengers_Backward.Print_Queue();
		std::cout << "\n";		
		std::cout << "Foward Wheel Passengers: ";
		Wheel_Passengers_Forward.Print_Queue();
		std::cout << "\n";
		std::cout << "Backward Wheel Passengers: ";
		Wheel_Passengers_Backward.Print_Queue();
		std::cout << "\n";
	}
	int Count_Station() {
		int total_count{}, count1{}, count2{}, count3{}, count4{}, count5{}, count6{};
		count1 = Special_Passengers_Forward.Count();
		count2 = Special_Passengers_Backward.Count();
		count3 = Normal_Passengers_Forward.Count();
		count4 = Normal_Passengers_Backward.Count();
		count5 = Wheel_Passengers_Forward.Count();
		count6 = Wheel_Passengers_Backward.Count();
		total_count = count1 + count2 + count3 + count4 + count5 + count6;
		return total_count;
	}
	void Add_Bus(Bus* obj) {
		if (obj->get_reverse() == false && obj->GetType() == 'W') { Buses_Wheel_Forward.enQueue(obj, 0); }
		else if (obj->get_reverse() == false && obj->GetType() == 'M') { Buses_Mixed_Forward.enQueue(obj, 0); }
		else if (obj->get_reverse() == true && obj->GetType() == 'W') { Buses_Wheel_Backward.enQueue(obj, 0); }
		else if (obj->get_reverse() == true && obj->GetType() == 'M') { Buses_Mixed_Forward.enQueue(obj, 0); }
		else { std::cout << "wrong parameters\n"; } //change this message / condition
	}	
	void Remove_Bus(Bus* obj) {
		if (obj->get_reverse() == false && obj->GetType() == 'W') { Buses_Wheel_Forward.deQueue(); }
		else if (obj->get_reverse() == false && obj->GetType() == 'M') { Buses_Mixed_Forward.deQueue(); }
		else if (obj->get_reverse() == true && obj->GetType() == 'W') { Buses_Wheel_Backward.deQueue(); }
		else if (obj->get_reverse() == true && obj->GetType() == 'M') { Buses_Mixed_Forward.deQueue(); }
		else { std::cout << "wrong parameters\n"; } //change this message / condition
	}

	Bus* Remove_Bus(char type,char direction)
	{
		cout << "I am in remove bus " << endl;
		if (type == 'M' && direction == 'F') return Buses_Mixed_Forward.deQueue();
		if (type == 'M' && direction == 'B') return Buses_Mixed_Backward.deQueue();
		if (type == 'W' && direction == 'F') return Buses_Wheel_Forward.deQueue();
		if (type == 'W' && direction == 'B') return Buses_Wheel_Backward.deQueue();
		return nullptr;
	}
	void Print_Bus_At_Station() { 
		std::cout << "Printing the buses at the station: " << std::endl;
		std::cout << "Forward Mixed Bus: ";
		Buses_Mixed_Forward.Print_Queue();
		std::cout << "\n";
		std::cout << "Forward Wheel Bus: ";
		Buses_Wheel_Forward.Print_Queue();
		std::cout << "\n";
		std::cout << "Backward Mixed Bus: ";
		Buses_Mixed_Backward.Print_Queue();
		std::cout << "\n";
		std::cout << "Backward Wheel Bus: ";
		Buses_Wheel_Backward.Print_Queue();
		std::cout << "\n";
	}
	int Count_Bus_At_Station() { 
		int total_count{}, count1{}, count2{}, count3{}, count4{};
		count1 = Buses_Mixed_Backward.Count(); 
		count2 = Buses_Wheel_Backward.Count(); 
		count3 = Buses_Mixed_Forward.Count(); 
		count4 = Buses_Wheel_Forward.Count(); 
		total_count = count1 + count2 + count3 + count4;
		return total_count;
	}


	int Count_Bus_Of_Type(char type,char direction)
	{
		if(type == 'M' && direction == 'F') return Buses_Mixed_Forward.Count();
		if (type == 'M' && direction == 'B') return Buses_Mixed_Backward.Count();
		if(type == 'W' && direction == 'F') return Buses_Wheel_Forward.Count();
		else return Buses_Wheel_Backward.Count();
	}

	
	int get_station_number() const { return Station_Number; }
	Passenger** Array_Special_Passengers_Forward() {
		return Special_Passengers_Forward.get_array_passengers();
	}
	Passenger** Array_Special_Passengers_Backward() {
		return Special_Passengers_Backward.get_array_passengers();
	}
	Passenger** Array_Normal_Passengers_Forward() {
		return Normal_Passengers_Forward.get_array_passengers();
	}
	Passenger** Array_Normal_Passengers_Backward() {
		return Normal_Passengers_Backward.get_array_passengers();
	}
	Passenger** Array_Wheel_Passengers_Forward() {
		return Wheel_Passengers_Forward.get_array_passengers();
	}
	Passenger** Array_Wheel_Passengers_Backward() {
		return Wheel_Passengers_Backward.get_array_passengers();
	}
	Bus** Array_Mixed_Backward() {
		return Buses_Mixed_Backward.get_array_buses();
	}
	Bus** Array_Wheel_Backward() {
		return Buses_Wheel_Backward.get_array_buses();
	}
	Bus** Array_Mixed_Forward() {
		return Buses_Mixed_Forward.get_array_buses();
	}
	Bus** Array_Wheel_Forward() {
		return Buses_Wheel_Forward.get_array_buses();
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


#ifndef BUS_H
#define BUS_H

#include "Passenger.h"
#include "LinkedList.h"

class Bus
{
	int capacity;
	int count_inside;
	int current_station;
	int next_station;
	int num_journey;
	char type;
	bool reverse;
	int bus_number;
	int timer;
	char status;
	int time_mentainance;
	LinkedList<Passenger*> Bus_passengers;
public:
	char GetType();
	void set_bus_id(int new_id);
	int getId() const;
	Bus(int new_capacity, char new_type, int new_bus_number);
	bool Move_Bus(bool reverse);
	bool Is_Full();
	bool Add_Passenger(Passenger* passenger);
	//bool Shift_Bus();
	bool Add_Time(int time);
	bool Remove_Passenger(int station_num);
	bool Reverse_Bus(int station, int num_of_journies, int time);
	bool Mentain(int num_of_journies, int time);
	bool Get_out_of_Mentainance(int time);
	bool get_reverse() const;

};

#endif

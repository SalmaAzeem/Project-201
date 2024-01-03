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
public:
	LinkedList<Passenger*> Bus_passengers;
	bool IsAvailable();
	char GetType();
	void set_bus_id(int new_id);
	int get_current_station();
	int getId() const;
	Bus(int new_capacity, char new_type, int new_bus_number);
	bool Move_Bus(bool reverse);
	bool Is_Full();
	bool Add_Passenger(Passenger* passenger,char direction);
	//bool Shift_Bus();
	bool Add_Time(int time,int num_of_stations);
	int Remove_Passenger(int station_num);
	bool Reverse_Bus(int station, int num_of_journies, int time);
	bool Mentain(int num_of_journies, int time);
	bool Get_out_of_Mentainance(int time);
	bool get_reverse() const;
	bool Is_Busy();
	int get_capacity() const;
	int get_next_station();
};

#endif

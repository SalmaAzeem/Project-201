#pragma once
#ifndef EVENT_H
#define EVENT_H
#include "Passenger.h"
#include <iostream>
#include "Station.h"

using namespace std;
class Event {
protected:
	char event_type; //'l' , 'a'
	std::string type_of_passenger;
	char type_passenger_special;
	int hour;
	int minute;
	int second;
	int id;
	int sstation;
	char type;
	int l_station;


public:
	virtual void execute(Station**array) = 0;
	char get_type();
	int get_l_station();


	void set_type(char t);
	void set_l_station(int l_st);


	void set_event_type(char newEventType);

	char get_event_type();

	void set_hour(int h);

	int get_hour() const;

	void set_minute(int m);

	int get_minute();

	void set_second(int s);

	int get_second() const;

	void set_id(int ID);

	int get_id() const;

	void set_sstation(int ss);

	int get_sstation();

	std::string get_type_of_passenger();
	char get_special_type();

};
#endif

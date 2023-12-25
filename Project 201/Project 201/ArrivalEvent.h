#pragma once
#include "Event.h"
#include "Passenger.h"
#include <iostream>
#ifndef ARRIVALEVENT_H
#define ARRIVALEVENT_H
using namespace std;

class ArrivalEvent : public Event
{
public:
	ArrivalEvent(char et, string type_of_pass, char special, int h, int m, int s, int i, int ss, int ls);

	void execute(Station** array) override;

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
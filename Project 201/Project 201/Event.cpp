#include "Event.h"
#include <iostream>
using namespace std;

Passenger* Event::execute() {
	return nullptr;
}
void Event::set_event_type(char newEventType) {
	event_type = newEventType;
}

char Event::get_event_type() { return event_type; }

void Event::set_hour(int h) { hour = h; }

int Event::get_hour() const { return hour; }

void Event::set_minute(int m) { minute = m; }

int Event::get_minute() { return minute; }

void Event::set_second(int s) { second = s; }

int Event::get_second() const { return second; }

void Event::set_id(int ID) { id = ID; }

int Event::get_id() const { return id; }

void Event::set_sstation(int ss) { sstation = ss; }

int Event::get_sstation() { return sstation; }

char Event::get_type() { return type; }

int Event::get_l_station() { return l_station; }

void Event::set_type(char t) { type = t; }

void Event::set_l_station(int l_st) { l_station = l_st; }

string Event::get_type_of_passenger() { return type_of_passenger; }
char Event::get_special_type() { return type_passenger_special; }
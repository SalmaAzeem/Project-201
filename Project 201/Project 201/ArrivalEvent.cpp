#include "ArrivalEvent.h"
#include "Passenger.h"

#include <iostream>
using namespace std;

ArrivalEvent::ArrivalEvent(char et, string type_of_pass, char special, int h,
    int m, int s, int i, int ss, int ls) {
    event_type = et;
    hour = h;
    minute = m;
    second = s;
    id = i;
    sstation = ss;
    l_station = ls;
    type_of_passenger = type_of_pass;
    type_passenger_special = special;
}
Passenger* ArrivalEvent::execute() {
    Passenger* one =
        new Passenger(id, hour, minute, second, sstation, l_station, type_of_passenger, type_passenger_special);
    ///object from the station and call addpassenger
    std::cout
        << "id is " << id << endl
        << "start station is " << sstation << endl
        << "last station is " << l_station << endl
        << "Hour is: " << hour << std::endl
        << "Minute is: " << minute << std::endl
        << "type is: " << type_of_passenger << endl
        << "Special Type is " << type_passenger_special << std::endl
        << "direction: " << one->getDirection() << std::endl
        << '\n';
    return one;
}
void ArrivalEvent::set_event_type(char newEventType) {
    event_type = newEventType;
}

char ArrivalEvent::get_event_type() { return event_type; }

void ArrivalEvent::set_hour(int h) { hour = h; }

int ArrivalEvent::get_hour() const { return hour; }

void ArrivalEvent::set_minute(int m) { minute = m; }

int ArrivalEvent::get_minute() { return minute; }

void ArrivalEvent::set_second(int s) { second = s; }

int ArrivalEvent::get_second() const { return second; }

void ArrivalEvent::set_id(int ID) { id = ID; }

int ArrivalEvent::get_id() const { return id; }

void ArrivalEvent::set_sstation(int ss) { sstation = ss; }

int ArrivalEvent::get_sstation() { return sstation; }

char ArrivalEvent::get_type() { return type; }

int ArrivalEvent::get_l_station() { return l_station; }

void ArrivalEvent::set_type(char t) { type = t; }

void ArrivalEvent::set_l_station(int l_st) { l_station = l_st; }

string ArrivalEvent::get_type_of_passenger() { return type_of_passenger; }
char ArrivalEvent::get_special_type() { return type_passenger_special; }
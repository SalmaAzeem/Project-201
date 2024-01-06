#include "Passenger.h"
#include <iostream>
using namespace std;

Passenger::Passenger()
    : id(0), arrival_hour(0), arrival_minutes(0), arrival_seconds(0),
    arrival_station_id(0), leave_station_id(0), type_of_passenger(" "), waiting_time_minutes(0) {}

Passenger::Passenger(int newId, int newArrivalHour, int newArrivalMinutes,
    int newArrivalSeconds, int newArrivalStationId,
    int newLeaveStationId, std::string type, char special, int Max_Waiting_Time)
{
    id = newId;
    arrival_hour = newArrivalHour;
    arrival_minutes = newArrivalMinutes;
    arrival_seconds = newArrivalSeconds;
    arrival_station_id = newLeaveStationId;
    leave_station_id = newLeaveStationId;
    type_of_passenger = type;
    special_type = special;
    waiting_time_hour = 0;
    waiting_time_minutes = 0;
    finish_time_minutes = 0;
    finish_time_hour = 0;
    move_time_hour = 0;
    move_time_minutes = 0;
    trip_time_hour = 0;
    trip_time_minutes = 0;
    max_waiting_time = Max_Waiting_Time;
    if (newArrivalStationId > newLeaveStationId)
    {
        direction = 'B';
    }
    else if (newArrivalStationId < newLeaveStationId)
    {
        direction = 'F';
    }
}
    
int Passenger::get_Maximum_Waiting_Time() const { return max_waiting_time; }

void Passenger::setWaitingTime(int Time_minutes) {
    waiting_time_minutes = Time_minutes;
}

// Getters
int Passenger::getId() const
{
    return id;
}
int Passenger::getArrivalHour() const
{
    return arrival_hour;
}
int Passenger::getArrivalMinutes() const
{
    return arrival_minutes;
}
int Passenger::getArrivalSeconds() const
{
    return arrival_seconds;
}
int Passenger::getArrivalStationId() const
{
    return arrival_station_id;
}
int Passenger::getLeaveStationId() const
{
    return leave_station_id;
}
int Passenger::getWaitingTime() const
{
    return waiting_time_minutes;
}
char Passenger::getDirection() const { return direction; }

std::string Passenger::getPassengertype()const
{
    return type_of_passenger;
}
char Passenger::getPassengerspecial() const
{
    return special_type;
}

Passenger::Passenger(int newid, int start_station)
{
    id = newid;
    arrival_station_id = start_station;
}

bool Passenger::waiting_time_increase(int max_waiting_time)
{
    if (waiting_time_minutes == max_waiting_time)
    {
        waiting_time_minutes = 0;
        type_of_passenger = "SP";
        special_type = 'A'; //a3la priority
        return true;
    }
    waiting_time_minutes++;
    //cout << "Ana waiting time: " << waiting_time_minutes << endl;
    return false;

}
void Passenger::calculate_Passenger_waiting_time()
{
    waiting_time_hour = move_time_hour - arrival_hour;
    waiting_time_minutes = arrival_minutes - move_time_minutes;
}
void Passenger::calculate_Passenger_trip_time()
{
    trip_time_hour = finish_time_hour - move_time_hour;
    trip_time_minutes = finish_time_minutes - move_time_minutes;
}

int Passenger::get_finish_time_hour() { return finish_time_hour; }

int Passenger::get_finish_time_minutes() { return finish_time_minutes; }

int Passenger::get_arrival_time_hour() { return arrival_hour; }
int Passenger::get_arrival_time_minutes() { return arrival_minutes; }

int Passenger::get_waiting_time_hour() { return waiting_time_hour; }
int Passenger::get_waiting_time_minutes() { return waiting_time_minutes; }

int Passenger::get_trip_time_hour() { return trip_time_hour; }
int Passenger::get_trip_time_minutes() { return trip_time_minutes; }


void Passenger::set_get_on_bus(int hour,int minute)
{
    get_on_bus_hour = hour;
    get_on_bus_minute = minute;
}

void Passenger::set_get_off_bus(int hour,int minute)
{
    get_off_bus_hour = hour;
    get_off_bus_minute = minute;
}

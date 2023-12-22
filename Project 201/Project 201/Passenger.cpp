#include "Passenger.h"

#include <iostream>
using namespace std;

Passenger::Passenger()
    : id(0), arrival_hour(0), arrival_minutes(0), arrival_seconds(0),
    arrival_station_id(0), leave_station_id(0), type_of_passenger(" "), waiting_time(0) {}

Passenger::Passenger(int newId, int newArrivalHour, int newArrivalMinutes,
    int newArrivalSeconds, int newArrivalStationId,
    int newLeaveStationId, std::string type, char special)
{
    id = newId;
    arrival_hour = newArrivalHour;
    arrival_minutes = newArrivalMinutes;
    arrival_seconds = newArrivalSeconds;
    arrival_station_id = newLeaveStationId;
    leave_station_id = newLeaveStationId;
    type_of_passenger = type;
    special_type = special;
    waiting_time = 0;
    if (arrival_station_id > leave_station_id)
    {
        direction = 'B';
    }
    else if (arrival_station_id < leave_station_id)
    {
        direction = 'F';
    }
}
    


void Passenger::setWaitingTime(int newWaitingTime) {
    waiting_time = newWaitingTime;
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
    return waiting_time;
}

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
    if (waiting_time == max_waiting_time)
    {
        waiting_time = 0;
        type_of_passenger = "SP";
        special_type = 'A'; //a3la priority
        return true;
    }
    waiting_time++;
    return false;

}
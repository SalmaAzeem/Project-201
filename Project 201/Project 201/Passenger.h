#ifndef PASSENGER_H
#define PASSENGER_H
#include<iostream>

class Passenger
{
private:
    int id;
    std::string type_of_passenger;
    char special_type;
    int arrival_hour;
    int arrival_minutes;
    int arrival_seconds;
    int arrival_station_id;
    int leave_station_id;
    int waiting_time;
    char direction;

public:

    Passenger();

    Passenger(int newId, int newArrivalHour, int newArrivalMinutes,
        int newArrivalSeconds, int newArrivalStationId,
        int newLeaveStationId, std::string type, char special);

    Passenger(int newid, int start_station);
    bool waiting_time_increase(int max_waiting_time);

    void setWaitingTime(int newWaitingTime);

    // Getters
    int getId() const;
    int getArrivalHour() const;
    int getArrivalMinutes() const;
    int getArrivalSeconds() const;
    int getArrivalStationId() const;
    int getLeaveStationId() const;
    int getWaitingTime() const;
    std::string getPassengertype()const;
    char getPassengerspecial() const;

};
#endif

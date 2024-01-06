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
    int max_waiting_time;
    int leave_station_id;
    int waiting_time_hour;
    int waiting_time_minutes;
    int move_time_hour;
    int move_time_minutes;
    int finish_time_hour;
    int finish_time_minutes;
    int trip_time_hour;
    int trip_time_minutes;
    char direction;
    int get_on_bus_hour;
    int get_on_bus_minute;
    int get_off_bus_hour;
    int get_off_bus_minute;
public:

    Passenger();

    Passenger(int newId, int newArrivalHour, int newArrivalMinutes,
        int newArrivalSeconds, int newArrivalStationId,
        int newLeaveStationId, std::string type, char special, int mwt);

    Passenger(int newid, int start_station);
    bool waiting_time_increase(int max_waiting_time);


    // etters
    void setWaitingTime(int newWaitingTime);
    void set_get_on_bus(int hour,int minute);
    void set_get_off_bus(int hour,int minute);
    // Getters

    int get_finish_time_hour();
    int get_finish_time_minutes();
    int get_arrival_time_hour();
    int get_arrival_time_minutes();
    int get_waiting_time_hour();
    int get_waiting_time_minutes();
    int get_trip_time_hour();
    int get_trip_time_minutes();
    int getId() const;
    int getArrivalHour() const;
    int getArrivalMinutes() const;
    int getArrivalSeconds() const;
    int getArrivalStationId() const;
    int getLeaveStationId() const;
    int getWaitingTime() const;
    int get_Maximum_Waiting_Time() const;
    std::string getPassengertype()const;
    char getPassengerspecial() const;
    char getDirection() const;
    void calculate_Passenger_waiting_time();
    void calculate_Passenger_trip_time();
};
#endif

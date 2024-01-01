#ifndef COMPANY_H
#define COMPANY_H
#include "Bus.h"
#include "LinkedList.h"
#include "Station.h"
#include "LinkedQueue.h"
class Company {
private:
	int Number_of_stations;     // salma, mariam 100
	int between_stations;       // mariam
	int Wheel_buses;            // app
	int Mixed_buses;            // app
	int capacity_wheel_buses;   // app
	int capacity_mixed_buses;   // app
	int Journeys_befor_checkup; // mariam
	int chekup_duration_wheel;  // mariam
	int chekup_duration_mixed;  // mariam

	int max_waiting_time;        // salma 9
	int get_on_off_time_seconds; // mariam, app
	int number_of_events;
	int average_waiting_time;
	int average_trip_time_hour;
	int average_trip_time_minute;
	int num_of_promoted_passengers; //add num_of_promoted_passengers++ when promoting a passenger
	LinkedList<Passenger*> Finished_Passengers;  //to be removed


public:
	LinkedQueue<Event*> tot_events;
	Company();
	LinkedQueue<Event*> queue_of_events;
	void read_input();
	void read_events();
	void initialize_buses(Station** array);
	void Pass_Passenger(Station** array);
	void Place_in_Station_Zero(Station** array, Bus** arrayb);
	Station** Array_Of_Stations();
	void Move_Bus_to_Stations(Station** station, int Station_number, char bus_type, bool bus_direction);
	int get_station() const { return Number_of_stations; }
	void add_me(int Hour, int Minute, Station** array);
	void set_number_of_stations(int n);
	void Simulate_Branch(Station** array);
	void Simulate();
	void Remove_passenger(Station** array);
	void calculate_average_waiting_time();
	void calculate_average_trip_time();
	void output_file();
};
#endif
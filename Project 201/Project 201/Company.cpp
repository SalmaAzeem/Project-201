#include "Company.h"
#include "ArrivalEvent.h"
#include "Bus.h"
#include "Event.h"
#include "LeaveEvent.h"
#include "LinkedQueue.h"
#include "Station.h"
#include "UI.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


void Company::set_number_of_stations(int n)
{
    cout << "ay 7aga";
    Number_of_stations = n + 1;
    std::cout << Number_of_stations;
}

Company::Company() {}
void Company::read_input() {
    std::ifstream file("random.txt");

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return;
    }

    if (file >> Number_of_stations >> between_stations >> Wheel_buses >>
        Mixed_buses >> capacity_wheel_buses >> capacity_mixed_buses >>
        Journeys_befor_checkup >> chekup_duration_wheel >>
        chekup_duration_mixed >> max_waiting_time >> get_on_off_time_seconds >>
        number_of_events) {
        set_number_of_stations(Number_of_stations);
        /*std::cout << Number_of_stations << endl;
        cout << number_of_events << endl;*/

    }
    else {
        std::cerr
            << "Error: File does not contain enough lines or has invalid format."
            << std::endl;
        return;
    }
    file.close();
}

void Company::read_events() {
    std::ifstream file("random.txt");
    // Skip the first five lines
    for (int i = 0; i < 6; ++i) {
        std::string dummyLine;
        if (!std::getline(file, dummyLine)) {
            std::cerr << "Error: File does not contain enough lines." << std::endl;
            file.close();
        }
    }
    // initialize variables for everything
    string myText;
    char type_of_events = ' ', special_char = ' ';
    int id = 0, hours = 0, min = 0, min_1 = 0, minutes = 0, sec = 0,
        sstation_id = 0, lstation_id = 0;
    std::string time = " ", type = " ", type_special = " ";

    string sentence;

    // Counters jus to make sure of the number of each event
    int c = 0, c_2 = 0;

    for (int i = 0; i < number_of_events; i++) {
        file >> type_of_events;
        if (type_of_events == 'A') {
            if (file >> type >> time >> id >> sstation_id >> lstation_id) {

                // if there is sth at the end of the line get it else set type_special
                // to null
                getline(file, type_special);
                // special types are P -> Pregnant , O --> POD,  A--> Aged, " " -->
                // Normal
                if (type_special == " POD") {

                    special_char = std::toupper(type_special[2]);

                }
                else {
                    special_char = std::toupper(type_special[1]);
                }

                hours = (time[0] - '0');
                min = (time[2] - '0');
                min_1 = (time[3] - '0');
                if (min_1 == -48)
                {
                    minutes = min;
                }
                else
                {
                    minutes = min * 10 + min_1;

                }
                ArrivalEvent* event_arrival =
                    new ArrivalEvent(type_of_events, type, special_char, hours, minutes,
                        sec, id, sstation_id, lstation_id);

                // enqueue in the queue of events

                tot_events.enqueue(event_arrival);

                c++;
            }

        }
        else if (type_of_events == 'L') {

            if (file >> time >> id >> sstation_id) {
                hours = (time[0] - '0');
                minutes = (time[2] - '0');
                min_1 = (time[3] - '0');
                if (min_1 == -48)
                {
                    minutes = min;
                }
                else
                {
                    minutes = min * 10 + min_1;

                }
                LeaveEvent* event_leave =
                    new LeaveEvent(type_of_events, hours, minutes, 0, id, sstation_id);
                tot_events.enqueue(event_leave);
                c_2++;
            }
        }
    }
    file.close();
    //tot_events.Print_Queue();
    /*  std::cout << "Count of Arrival events is " << c << endl;
      std::cout << "Count of Leave events is " << c_2 << endl;*/

    return;
}

void Company::initialize_buses(Station** array) {
    int i = 0;
    int j = 0;

    while (i < Mixed_buses && j < Wheel_buses) {
        Bus* mixed_bus = new Bus(capacity_mixed_buses, 'M', i++);
        array[0]->Buses_Mixed_Forward.enQueue(mixed_bus, 0);

        Bus* wheel_bus = new Bus(capacity_wheel_buses, 'W', j++);
        array[0]->Buses_Wheel_Forward.enQueue(wheel_bus, 0);
    }

    // Add any remaining mixed buses
    while (i < Mixed_buses) {
        Bus* mixed_bus = new Bus(capacity_mixed_buses, 'M', i++);
        array[0]->Buses_Mixed_Forward.enQueue(mixed_bus, 0);
    }

    // Add any remaining wheel buses
    while (j < Wheel_buses) {
        Bus* wheel_bus = new Bus(capacity_wheel_buses, 'W', j++);
        array[0]->Buses_Wheel_Forward.enQueue(wheel_bus, 0);
    }
}

void Company::Pass_Passenger(Station** array) {
    Passenger* P = new Passenger;
    Event* one = tot_events.dequeue();
    one->execute(array);
   
}

Station** Company::Array_Of_Stations() {
    Station** Array_stations = new Station * [Number_of_stations];
    for (int i = 0; i < Number_of_stations; i++)
    {
        Array_stations[i] = new Station(i);
    }
    return Array_stations;
}


void Company::Place_in_Station_Zero(Station** array, Bus** arrayb) {
    Station* Szero = array[0];
    for (int i = 0; i < Wheel_buses + Mixed_buses; i++) {
        Szero->Add_Bus(arrayb[i]);   //done lama mariam te3adel
    }
}

void Company::Move_Bus_to_Stations(Station** array, int Station_number, char bus_type, bool bus_direction) {
    Station* Station_before = array[Station_number];
    Station* Station_after = array[Station_number + 1];
    Bus* B = new Bus(0, ' ', 0);

    if (bus_type == 'W' && bus_direction == false) {
        B = Station_before->Buses_Wheel_Forward.deQueue();
    }

    else if (bus_type == 'M' && bus_direction == false) {
        B = Station_before->Buses_Mixed_Forward.deQueue();
    }

    else if (bus_type == 'W' && bus_direction == true) {
        B = Station_before->Buses_Wheel_Backward.deQueue();
    }

    else if (bus_type == 'M' && bus_direction == true) {
        B = Station_before->Buses_Mixed_Backward.deQueue();
    }

    bool reverse = B->get_reverse();
    Station_after->Add_Bus(B); //lama mariam te3adel
    std::cout << B->Move_Bus(reverse);
}

void Company::add_me(int Hour, int Minute, Station** array) {
    Event* one_event;
    Event* two_event;

    one_event = tot_events.peek_Event();
    if (one_event != nullptr)
    {
        two_event = tot_events.peek_Next_Event();
        if ((one_event->get_hour() == Hour) && (one_event->get_minute() == Minute) && two_event != nullptr) {
            if (!((two_event->get_hour() == Hour) && (two_event->get_minute() == Minute)))
            {
                Pass_Passenger(array);
                return;
            }
        }
        if ((one_event->get_hour() == Hour) && (one_event->get_minute() == Minute) && two_event != nullptr) {
            if ((two_event->get_hour() == Hour) && (two_event->get_minute() == Minute))
            {
                Pass_Passenger(array);
                add_me(Hour, Minute, array);
            }
        }
    }
}



void Company::Remove_passenger(Station** array)
{
  
     tot_events.dequeue()->execute(array);

}

void Company::Simulate_Branch(Station** array_of_stations) {
    Event* one_event;
    UI test;
    int Hour = 0;
    int Minute = 0;
    int Second = 0;
    int c = 0;
    Passenger* one_passenger;
    for (int h = 0; h < 24; h++) {
        for (int m = 0; m < 60; m++) {
            if (tot_events.peek_Event() != nullptr) {
                one_event = tot_events.peek_Event();

                if (one_event->get_event_type() == 'A')
                {
                    add_me(Hour, Minute, array_of_stations);
                }
                else if (one_event->get_event_type() == 'L')
                {
                    cout << "Leave id is " << one_event->get_id() << endl;
                    Remove_passenger(array_of_stations);
                }

                Minute++;
            }
        }
        Minute = 0;
        Hour++;
    }
    //std: cout << "The Count of Passengers is " << c << endl;
        //--------------------------------------------
    for (int i = 0; i < Number_of_stations; i++) {
        test.interface(array_of_stations, i);
        std::cout << "\n-----------------------------------------------" << std::endl;
        std::cout << "Press any key to display the next station..." << std::endl;
        getchar();
        //array_of_stations[i]->Print_Station();
    }
}

void Company::Simulate() {
    read_input();
    read_events();
    Station** array_of_stations = Array_Of_Stations();
    initialize_buses(array_of_stations);
    Simulate_Branch(array_of_stations);
}
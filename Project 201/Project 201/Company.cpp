#include "Company.h"
#include "ArrivalEvent.h"
#include "Bus.h"
#include "Event.h"
#include "LeaveEvent.h"
#include "LinkedQueue.h"
#include "Station.h"
#include "UI.h"
#include "LinkedList.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


void Company::set_number_of_stations(int n)
{
    Number_of_stations = n + 1;
}

void Company::calculate_average_waiting_time()
{
    average_waiting_time = average_waiting_time / number_of_events;
    //eftekry te3mely el average_waiting_time_hour b zero
}

void Company::calculate_average_trip_time()
{
    average_trip_time_hour = average_trip_time_hour / number_of_events;
    average_trip_time_minute = average_trip_time_minute / number_of_events;
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
        //cout << "The Number of Mixed Buses is " << Mixed_buses << endl;
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
                if (type == "NP")
                {
                    number_of_normal_passengers++;
                }
                else if (type == "SP")
                {
                    number_of_special_passengers++;
                }
                else 
                {
                    number_of_wheel_passengers++;
                }
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
                        sec, id, sstation_id, lstation_id, max_waiting_time);

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

void Company::output_file()
{
    cout << "FT\t" << "ID\t" << "AT\t" << "WT\t" << "TT" << endl;

    /*for (int i = 0; i < number_of_events; i++)
    {
        cout << Finished_Passengers.gethead()->getvalue()->get_finish_time_hour() << ":" << Finished_Passengers.gethead()->getvalue()->get_finish_time_minutes() << '\t' <<
            Finished_Passengers.gethead()->getvalue()->getId() << '\t' <<
            Finished_Passengers.gethead()->getvalue()->get_arrival_time_hour() << ":" << Finished_Passengers.gethead()->getvalue()->get_arrival_time_minutes() << '\t' <<
            Finished_Passengers.gethead()->getvalue()->get_waiting_time_hour() << ":" << Finished_Passengers.gethead()->getvalue()->get_waiting_time_minutes() << '\t' <<
            Finished_Passengers.gethead()->getvalue()->get_trip_time_hour() << ":" << Finished_Passengers.gethead()->getvalue()->get_trip_time_minutes() << endl;
        Finished_Passengers.DeleteNode(Finished_Passengers.gethead()->getvalue());
    }*/
    Station S;
    cout << "Passengers: " << number_of_events << " [NP: " << number_of_normal_passengers << ", SP: " << number_of_special_passengers << ", WP: " << number_of_wheel_passengers << "]" << endl;
    cout << "Passenger avg waiting time= " << "0:" << average_waiting_time << endl;
    cout << "Passenger avg trip time= " << average_trip_time_hour << ":" << average_trip_time_minute << endl;
    cout << "Auto-promoted passengers: "<<S.count_promoted /  number_of_events<< "%"<<endl;
    cout << "Buses: " << Wheel_buses + Mixed_buses << " " << "[WBus: " << Wheel_buses << ", MBus " << Mixed_buses << "]" << endl;
    //
    //
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
    int removed;
    int* removed_person = new int[number_of_events];
    int counter_of_removed_people = 0;
    Station* CurruntStation;
    Station* NextStation;
    Bus* CurrentBus;
    Passenger* one_passenger;
    for (int h = 0; h < 24; h++) {
        for(int m = 0; m < 60; m++) {
            
           if (tot_events.peek_Event() != nullptr) {
                one_event = tot_events.peek_Event();

                if (one_event->get_event_type() == 'A')
                {
                    add_me(Hour, Minute, array_of_stations);

                }
                else if (one_event->get_event_type() == 'L')
                {
                    //cout << "Leave id is " << one_event->get_id() << endl;
                    Remove_passenger(array_of_stations);
                }
                 
           }
                /*if (Hour >= 4)
                {*/
                    //ELsign el mafrod btkon s7 wala 8alat???

           for (int st = 0; st < Number_of_stations; st++)
           {
                        
                      
              CurruntStation = array_of_stations[st];
              /*cout << "Wheel  ";
              CurruntStation->Buses_Wheel_Forward.Print_Queue();*/
              //cout << "Mixed ";
              CurruntStation->Buses_Mixed_Forward.Print_Queue();

              cout << st << " ";
              if (st == Number_of_stations)
              {

                  NextStation = array_of_stations[1];
              }
              else
              {
                  NextStation = array_of_stations[st + 1];
              }
              if (st == 0)
              {
                  if (Minute % 15 == 0)
                  {

                      /////////see if there is any thing inside the queue to be able to dequeue a bus of each type////////////
                      if (CurruntStation->Count_Bus_Of_Type('W', 'F') > 0 && !(CurruntStation->Buses_Wheel_Forward.Peek_Bus()->Is_Busy())) //wheel forwad  //check if in mentainance
                      {
                          CurrentBus = CurruntStation->Remove_Bus('W', 'F');
                          if (CurrentBus != nullptr)
                          {
                              //cout << "  " << CurrentBus->getId() << "Bus number wf" << endl;
                              Busy_Bus.insertend(CurrentBus);
                              CurrentBus->Move_Bus(false);
                          }
                         

                      }
                      if (CurruntStation->Count_Bus_Of_Type('W', 'B') > 0 && !(CurruntStation->Buses_Wheel_Backward.Peek_Bus()->Is_Busy()))//wheel backward
                      {
                          CurrentBus = CurruntStation->Remove_Bus('W', 'B');
                          if (CurrentBus != nullptr)
                          {
                              //cout << "  " << CurrentBus->getId() << "Bus number wb" << endl;

                              Busy_Bus.insertend(CurrentBus);
                              CurrentBus->Move_Bus(false);
                          }

                      }
                      if (CurruntStation->Count_Bus_Of_Type('M', 'F') > 0 && !(CurruntStation->Buses_Mixed_Forward.Peek_Bus()->Is_Busy()))//mixed forward
                      {
                          CurrentBus = CurruntStation->Remove_Bus('M', 'F');
                          if (CurrentBus != nullptr)
                          {
                              //cout << "  " << CurrentBus->getId() << "Bus number  mf" << endl;

                              Busy_Bus.insertend(CurrentBus);
                              CurrentBus->Move_Bus(false);

                          }

                      }
                      if (CurruntStation->Count_Bus_Of_Type('M', 'B') > 0 && !(CurruntStation->Buses_Mixed_Backward.Peek_Bus()->Is_Busy()))//mixed backward
                      {
                          CurrentBus = CurruntStation->Remove_Bus('M', 'B');
                          if (CurrentBus != nullptr)
                          {
                              //cout << "  " << CurrentBus->getId() << "Bus number mb" << endl;

                              Busy_Bus.insertend(CurrentBus);
                              CurrentBus->Move_Bus(false);

                          }
                      }
                  }
              }
              else if(st!=0)
              {     
                  for (int sc = 0; sc < 60; sc++)
                  {
                          /////////removing passengers alg//////////
              ////////////////////////////////for wheel forward/////

                      CurrentBus = CurruntStation->Buses_Wheel_Forward.Peek_Bus();
                          //cout << CurruntStation->get_station_number();
              

                          /* bool check = CurrentBus->Is_Busy();
                           cout << "I am checking " << check << endl;*/
                      if (CurrentBus != nullptr)
                      {
                          //cout << "notnull" << endl;


                          if (sc % 3 == 0 && sc != 0)
                          {

                              removed = CurrentBus->Remove_Passenger(st);
                              //cout << removed << "anaana" << endl;
                              if (removed != 0)
                              {
                                  //store people done with the journy to display in interface
                                  removed_person[counter_of_removed_people] = removed;
                                  counter_of_removed_people++;
                                  //cout << "ana removed" << removed << endl;
                              }
                              else
                              {
                                  cout << "notnot " << CurrentBus->IsAvailable() << endl;
                                  ///add passenger alg/////
                                             ///check if there are people///
                                  if (CurruntStation->Wheel_Passengers_Forward.Count() > 0 && !(CurrentBus->Is_Full()) && sc % 6 == 0 && CurrentBus->IsAvailable()) //gets on the bus in 3 sec + 3 sec of getting on 
                                  {
                                      //cout << "Trying2" << endl;
                                      CurrentBus->Add_Passenger(CurruntStation->Wheel_Passengers_Forward.deQueue(), 'F');

                                  }
                                  else if ((CurrentBus->Is_Full() || CurruntStation->Wheel_Passengers_Forward.Count() == 0) && CurrentBus->IsAvailable())////////the bus moves if its full  or no one exists
                                  {

                                      CurrentBus = CurruntStation->Remove_Bus('W', 'F');
                                      if (CurrentBus != nullptr)
                                      {
                                          //cout << " ID " << CurrentBus->getId() << " Bus number  wheel lsa bdry1" << endl;
                                          Busy_Bus.insertend(CurrentBus);
                                          CurrentBus->Move_Bus(false);

                                      }

                                  }

                              }

                          }
                      }


                          //                                 //////////////////////////////////for wheel backward///
                          //                                 CurrentBus = CurruntStation->Buses_Wheel_Backward.Peek_Bus()
                          //                                 
                          //                                 if (sc % 3 == 0 && sc != 0)
                          //                                 {
                          //                                     removed_person = CurrentBus->Remove_Passenger(st);
                          //                                     if (removed_person != nullptr)
                          //                                     {
                          //                                         ///store people done with the journy to display in interface
                          //                                         People_Done.insertend(removed_person);
                          //                                     }
                          //                                     if (removed_person == nullptr)
                          //                                     {
                          //                                         /////add passenger alg/////
                          //                                                    ///check if there are people///
                          //                                         if (CurruntStation->Wheel_Passengers_Backward.Count() > 0 && sc % 6 == 0 && !(CurrentBus->Is_Full())) //gets on the bus in 3 sec + 3 sec of getting on 
                          //                                         {
                          //                                             CurrentBus->Add_Passenger(CurruntStation->Wheel_Passengers_Backward.deQueue(), 'B');
                          //                                         }
                          //                                         else if (CurrentBus->Is_Full())////////the bus moves if its full 
                          //                                         {
                          //                                             CurrentBus = CurruntStation->Remove_Bus('W', 'B');
                          //                                             NextStation->Add_Bus(CurrentBus);
                          //                                         }
                          //                                         else if (CurruntStation->Wheel_Passengers_Backward.Count() == 0)//////move bus if no people left to add
                          //                                         {
                          //                                             CurrentBus = CurruntStation->Remove_Bus('W', 'B');
                          //                                             NextStation->Add_Bus(CurrentBus);
                          //                                             continue;
                          //                                         }
                          //                                         CurrentBus = CurruntStation->Buses_Wheel_Backward.Peek_Bus();

                          //                                     }
                          //                                 }
                          //                                 //////////////////////////////////for Mixed forward///
                     CurrentBus = CurruntStation->Buses_Mixed_Forward.Peek_Bus();
                     if (CurrentBus)
                     {
                         if (sc % 3 == 0 && sc != 0)
                         {
                             removed = CurrentBus->Remove_Passenger(st);
                             if (removed != 0)
                             {
                                 ///store people done with the journy to display in interface
                                 removed_person[counter_of_removed_people] = removed;
                             }
                             if (removed_person == 0)
                             {
                                 /////add passenger alg/////
                                            ///check if there are people begining with special for piority///
                                 if (CurruntStation->Special_Passengers_Forward.Count() > 0 && sc % 6 == 0 && !(CurrentBus->Is_Full())) //gets on the bus in 3 sec + 3 sec of getting on 
                                 {
                                     CurrentBus->Add_Passenger(CurruntStation->Special_Passengers_Forward.deQueue(), 'F');
                                 }
                                 else if (CurruntStation->Normal_Passengers_Forward.Count() > 0 && sc % 6 == 0 && !(CurrentBus->Is_Full()))
                                 {
                                     CurrentBus->Add_Passenger(CurruntStation->Normal_Passengers_Forward.deQueue(), 'F');
                                 }
                                 else if (CurrentBus->Is_Full() && CurrentBus->IsAvailable())////////the bus moves if its full 
                                 {
                                     CurrentBus = CurruntStation->Remove_Bus('M', 'F');
                                     if (CurrentBus != nullptr)
                                     {

                                     Busy_Bus.insertend(CurrentBus);
                                     CurrentBus->Move_Bus(false);
                                     }
                                 }
                                 else if (CurruntStation->Normal_Passengers_Forward.Count() == 0 && CurruntStation->Special_Passengers_Forward.Count() == 0 && CurrentBus->IsAvailable())//////move bus if no people left to add
                                 {
                                     CurrentBus = CurruntStation->Remove_Bus('M', 'F');
                                     if (CurrentBus != nullptr)
                                     {

                                     Busy_Bus.insertend(CurrentBus);
                                     CurrentBus->Move_Bus(false);
                                     }
                                 }


                             }
                         }
                     }
                       
                          //                                 //////////////////////////////////for Mixed backward///
                          //                                 CurrentBus = CurruntStation->Buses_Mixed_Backward.Peek_Bus();
                          //                                 if (sc % 3 == 0 && sc != 0)
                          //                                 {
                          //                                     removed_person = CurrentBus->Remove_Passenger(st);
                          //                                     if (removed_person != nullptr)
                          //                                     {
                          //                                         ///store people done with the journy to display in interface
                          //                                         People_Done.insertend(removed_person);
                          //                                     }
                          //                                     if (removed_person == nullptr)
                          //                                     {
                          //                                         /////add passenger alg/////
                          //                                         ///check if there are people begining with special for piority///

                          //                                         if (CurruntStation->Special_Passengers_Backward.Count() > 0 && sc % 6 == 0 && !(CurrentBus->Is_Full())) //gets on the bus in 3 sec + 3 sec of getting on 
                          //                                         {
                          //                                             CurrentBus->Add_Passenger(CurruntStation->Special_Passengers_Backward.deQueue(), 'B');
                          //                                         }
                          //                                         else if (CurruntStation->Normal_Passengers_Backward.Count() > 0 && sc % 6 == 0 && !(CurrentBus->Is_Full()))
                          //                                         {
                          //                                             CurrentBus->Add_Passenger(CurruntStation->Normal_Passengers_Backward.deQueue(), 'B');
                          //                                         }
                          //                                         else if (CurrentBus->Is_Full())////////the bus moves if its full 
                          //                                         {
                          //                                             CurrentBus = CurruntStation->Remove_Bus('M', 'B');
                          //                                             NextStation->Add_Bus(CurrentBus);
                          //                                         }
                          //                                         else if (CurruntStation->Normal_Passengers_Backward.Count() == 0 && CurruntStation->Special_Passengers_Backward.Count() == 0)//////move bus if no people left to add
                          //                                         {
                          //                                             CurrentBus = CurruntStation->Remove_Bus('M', 'B');
                          //                                             NextStation->Add_Bus(CurrentBus);
                          //                                         }

                          //                                     }
                          //                                 }
                          //                             
                      
                  }
                      
                  

              }

           }

                
           cout << "///////////////////////" << "Min" << Minute << "/////////////////////////" << endl;
           
           Node<Bus*>* ptr = Busy_Bus.gethead();
           if (ptr)

           {
           while (ptr->getnext())
           {

               if (ptr->getvalue()->Add_Time(between_stations))
               {
                   
                   //cout << ptr->getvalue()->get_next_station() << " station number" << endl;
                   array_of_stations[ptr->getvalue()->get_next_station()]->Add_Bus(ptr->getvalue());
                   Busy_Bus.sethead(ptr->getnext());
               }

               ptr = ptr->getnext();
           }
           if (ptr->getvalue()->Add_Time(between_stations))
           {
               array_of_stations[ptr->getvalue()->get_next_station()]->Add_Bus(ptr->getvalue());
           }
           Busy_Bus.RecPrint();

           }
           Minute++;
               
            }
            /* for (int st = 0; st < Number_of_stations; st++)
                {
                    CurruntStation = array_of_stations[st];
                    while ()
                    {
                        CurruntStation->Buses_Wheel_Forward.deQueue();

                    }
                }*/
            
            Minute = 0;
            Hour++;
        }

        
        
        //for (int i = 0; i < Number_of_stations; i++) {
        //    test.interface(array_of_stations, i);
        //    std::cout << "\n-----------------------------------------------" << std::endl;
        //    std::cout << "Press any key to display the next station..." << std::endl;
        //    getchar();
        //    //array_of_stations[i]->Print_Station();
        //}
  }
    //std: cout << "The Count of 
    // s is " << c << endl;
        //--------------------------------------------

//}

void Company::Simulate() {
    read_input();
    read_events();
    Station** array_of_stations = Array_Of_Stations();
    initialize_buses(array_of_stations);
    Simulate_Branch(array_of_stations);
    output_file();
}

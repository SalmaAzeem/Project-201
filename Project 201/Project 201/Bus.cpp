#include "Bus.h"

Bus::Bus(int new_capacity, char new_type, int new_bus_number)
{
	capacity = new_capacity;
	time_mentainance = 0;
	num_journey = 0;
	type = new_type;
	bus_number = new_bus_number;
	count_inside = 0;
	current_station = 0;
	next_station = 0;
	reverse = false;
	timer = 0;
	status = 'E';
	total_people = 0;
	total_get_off = 0;
	total_use_time = 0;
	total_trips = 0;
}


void Bus::set_bus_id(int new_id)
{
	bus_number = new_id;
}

bool Bus::Move_Bus()
{
	total_trips++;
	if (!reverse)
	{
		next_station++;
		status = 'B';
	}
	else
	{
		next_station--;
		status = 'B';
	}
	return true;
}

bool Bus::Is_Full()
{
	if (capacity == count_inside)
	{
		status = 'B';
		return true;
	}
	status = 'E';
	return false;
}


bool Bus::Add_Passenger(Passenger* passenger, char direction,int hour,int minute)
{
	passenger->set_get_on_bus(hour, minute);
	total_people++;
	if (direction == 'F')
	{
		Bus_passengers.InsertSorted(passenger);  //forward sort asc
		count_inside++;
		return true;
	}
	else if (direction == 'B')
	{
		Bus_passengers.InsertSortedDesc(passenger);  //backward sort desc
		count_inside++;
		return true;
	}
	return false;
}

int Bus::getId() const {
	return bus_number;
}


bool Bus::Add_Time(int time, int num_of_stations)
{

	if (timer == time)
	{
		current_station = next_station;
		timer = 0;

		return true;
	}
	timer++;
	return false;
}
Passenger* Bus::peek_Bus()
{
	if (Bus_passengers.gethead() == nullptr) return nullptr;
	return Bus_passengers.gethead()->getvalue();
}

Passenger* Bus::Remove_Passenger(int station_num, int hour,int minute)
{
	Node<Passenger*>* ptr = Bus_passengers.gethead();
	Passenger* passenger_to_remove = nullptr;
	if (ptr != nullptr)
	{

		if (station_num == ptr->getvalue()->getLeaveStationId())
		{
			total_get_off++;
			ptr->getvalue()->set_get_off_bus(hour, minute);
			passenger_to_remove = ptr->getvalue();
			Bus_passengers.GetPassenger();
			count_inside--;
			status = 'E';
			//// to remove only one person
		}
	}
	if (ptr == nullptr) return nullptr; /// handle null ptr as it errors with get value when nothing to remove
	return passenger_to_remove;
}



bool Bus::Reverse_Bus(int stations, int num_of_journies, int time,bool at_the_end)
{
	if (current_station == stations - 1)
	{
		reverse = true;
		next_station = stations - 1;
		num_journey++;
		return Mentain(num_of_journies, time);
	}
	else if (current_station == 1 && !at_the_end)
	{
		reverse = false;
		next_station = 1;
		num_journey++;
		return Mentain(num_of_journies, time);
	}
	return false;

}

bool Bus::Mentain(int num_of_journies, int time)
{
	if (num_journey == num_of_journies)
	{
		current_station = next_station = 0;
		status = 'B';

		if (Get_out_of_Mentainance(time))
		{
			status = 'E';
		}
		time_mentainance++;
		return true;
	}
	return false;
}

bool Bus::Get_out_of_Mentainance(int time)
{
	if (time_mentainance == time)
	{

		num_journey = 0;
		return true;
	}
	return false;
}

char Bus::GetType()
{
	return type;
}

bool Bus::get_reverse() const { return reverse; }

bool Bus::Is_Busy()
{
	return status == 'B';
}

int Bus::get_capacity() const { return capacity; }

int Bus::get_next_station()
{
	return next_station;
}


bool Bus::IsAvailable()
{
	return current_station == next_station;
}


int Bus::get_current_station()
{
	return current_station;
}


void Bus::set_reverse(bool direction)
{
	reverse = direction;
}

int Bus::get_number_of_j()
{
	return num_journey;
}

int Bus::get_count_inside()
{
	return count_inside;
}

void Bus::add_uti_time()
{
	if(count_inside > 0) total_use_time++;
}

double Bus::get_uti(int simuate_time)
{
	double calculations = (capacity * total_trips);
	//cout << calculations<< "ttt"<< calculations * ((total_use_time / 60) / simuate_time) << endl;
	if (calculations == 0) return 0;
	//cout << total_use_time << "rr" << endl;
	return (total_people / calculations) * ((total_use_time / 60)/simuate_time);
}

double Bus::get_busy()
{
	return total_use_time;
}
